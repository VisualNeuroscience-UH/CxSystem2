# -*- coding: utf-8 -*-
from __future__ import division

__author__ = 'Andalibi, V., Hokkanen H., Vanni, S.'

'''
The preliminary version of this software has been developed at Aalto University 2012-2015, 
and the full version at the University of Helsinki 2013-2017. The software is distributed 
under the terms of the GNU General Public License. 
Copyright 2017 Vafa Andalibi, Henri Hokkanen and Simo Vanni.
'''

from brian2  import *
import numpy as np
from matplotlib import pyplot
import sys
import pandas




class synapse_parser(object):
    '''
    This class contains all the variables that are required for the Synapses() object namespaces. There are several reference dictionaries in this class for:

    * cw: connection weights for any connection between NeuronGroup()s.
    * sp: Sparseness values for any connection between NeuronGroup()s.
    * STDP: values for A_pre, A_post, Tau_pre and Tau_post for any connection between NeuronGroup()s.
    * dist: distribution of the neurons for connection between NeuronGroup()s.

    There are also some important internal variables:

    * Cp: Synaptic potentiation coefficient according to van Rossum J Neurosci 2000
    * Cd: Synaptic depression coefficient according to van Rossum J Neurosci 2000
    * stdp_Nsweeps: 60 in papers one does multiple trials to reach +-50% change in synapse strength. A-coefficient will be divided by this number
    * stdp_max_strength_coefficient: This value is to avoid runaway plasticity.
    * conn_prob_gain: This is used for compensation of small number of neurons and thus incoming synapses

    '''

    # For _change_calcium()
    _excitatory_groups = ['PC', 'SS']
    _steep_post_inhibitory_groups = ['MC']
    _shallow_post_inhibitory_groups = ['BC']
    _steep_post = _excitatory_groups + _steep_post_inhibitory_groups
    _shallow_post = _shallow_post_inhibitory_groups

    def __init__(self,output_synapse,physio_config_df):
        '''
        The initialization method for namespaces() object.

        :param output_synapse: This is the dictionary created in neuron_reference() in brian2_obj_namespaces module. This contains all the information about the synaptic connection. In this class, Synaptic namespace parameters are directly added to it. Following values are set after initialization: Cp, Cd, sparseness, ilam. Other variables are then set based on the type of the synaptic connection (STDP,Fixed).
        '''
        self.output_synapse = output_synapse
        self.physio_config_df = physio_config_df

        synapse_parser.type_ref = array (['STDP','STDP_with_scaling', 'Fixed', 'Fixed_calcium', 'Fixed_normal', 'Depressing', 'Facilitating'])
        assert output_synapse['type'] in synapse_parser.type_ref, " -  Synapse type '%s' is not defined." % output_synapse['type']
        self.output_namespace = {}
        # self.output_namespace['Cp'] = self.value_extractor(self.physio_config_df,'Cp')
        # self.output_namespace['Cd'] = self.value_extractor(self.physio_config_df,'Cd')
        try:
            self.sparseness = self.value_extractor(self.physio_config_df,'sp_%s_%s' % (output_synapse['pre_group_type'], output_synapse['post_group_type']))
        except:
            pass
        # self.ilam = self.value_extractor(self.physio_config_df,'ilam_%s_%s' % (output_synapse['pre_group_type'], output_synapse['post_group_type']))

        self.calcium_concentration = self.value_extractor(self.physio_config_df, 'calcium_concentration' )
        self._set_calcium_dependency()

        # Set (initial) weights for chosen synapse type
        getattr(synapse_parser, output_synapse['type'])(self)

    def value_extractor(self, df, key_name):
        non_dict_indices = df['Variable'].dropna()[df['Key'].isnull()].index.tolist()
        for non_dict_idx in non_dict_indices:
            exec("%s=%s" % (df['Variable'][non_dict_idx], df['Value'][
                non_dict_idx]))
        try:
            return eval(key_name)
        except (NameError, TypeError):
            pass
        try:
            if type(key_name) == list:
                variable_start_idx = df['Variable'][df['Variable'] == key_name[0]].index[0]
                try:
                    variable_end_idx = df['Variable'].dropna().index.tolist()[
                        df['Variable'].dropna().index.tolist().index(variable_start_idx) + 1]
                    cropped_df = df.loc[variable_start_idx:variable_end_idx-1]
                except IndexError:
                    cropped_df = df.loc[variable_start_idx:]
                return eval(cropped_df['Value'][cropped_df['Key'] == key_name[1]].item())
            else:
                return eval(df['Value'][df['Key'] == key_name].item())
        except NameError:
            new_key = df['Value'][df['Key'] == key_name].item().replace("']", "").split("['")
            return self.value_extractor(df,new_key)
        except ValueError:
            raise ValueError("Parameter %s not found in the configuration file."%key_name)

    def _set_calcium_dependency(self):
        """
        Sets the dissociation constant for calcium-dependent modulation of synaptic weight
        # NB! It's not only E->E and E->I connections that get scaled. Goes both ways. See Markram suppl p16.
        """

        excitatory_groups = ['PC', 'SS', 'VPM']
        steep_inhibitory_groups = ['MC']
        shallow_inhibitory_groups = ['BC']
        steep_post = excitatory_groups + steep_inhibitory_groups
        shallow_post = shallow_inhibitory_groups

        if self.output_synapse['pre_group_type'] in excitatory_groups and self.output_synapse['post_group_type'] in steep_post:
            self._K12 = 2.79
        elif self.output_synapse['pre_group_type'] in steep_inhibitory_groups and self.output_synapse['post_group_type'] in excitatory_groups:
            self._K12 = 2.79
        elif self.output_synapse['pre_group_type'] in excitatory_groups and self.output_synapse['post_group_type'] in shallow_post:
            self._K12 = 1.09
        elif self.output_synapse['pre_group_type'] in shallow_inhibitory_groups and self.output_synapse['post_group_type'] in excitatory_groups:
            self._K12 = 1.09
        else:
            self._K12 = np.average([2.79, 1.09])

    def _scale_by_calcium(self, ca, cw=None):
        """
        Scales synaptic weight depending on calcium level

        :param ca: float, calcium concentration in mM
        :param cw: float, connection weight with calcium level 2.0mM (optional)
        :return: float, scaled synaptic weight
        """

        if cw is None:
            original_synapse_strength = self.cw_baseline_calcium
        else:
            original_synapse_strength = cw

        ca0 = 2.0  # The Ca concentration in which cw_baseline_calcium is given

        calcium_factor = (pow(ca,4)/(pow(self._K12,4) + pow(ca,4))) / (pow(ca0,4)/(pow(self._K12,4) + pow(ca0,4)))
        final_synapse_strength = original_synapse_strength * calcium_factor

        return final_synapse_strength

    def _set_utilization_factor(self, is_facilitating=False, ca=2.0):
        excitatory_groups = ['PC', 'SS', 'in']
        inhibitory_groups = ['BC', 'MC', 'L1i']

        if is_facilitating is False:
            U_E = self.value_extractor(self.physio_config_df, 'U_E')
            U_I = self.value_extractor(self.physio_config_df, 'U_I')

            if self.output_synapse['pre_group_type'] in excitatory_groups:
                self.output_namespace['U'] = self._scale_by_calcium(ca, U_E)
            elif self.output_synapse['pre_group_type'] in inhibitory_groups:
                self.output_namespace['U'] = self._scale_by_calcium(ca, U_I)
            else:
                print('Warning! Unrecognized group type %s will have '
                       'outbound synapses with averaged utilization factor' %
                       self.output_synapse['pre_group_type'])
                U = np.average([U_E, U_I])
                self.output_namespace['U'] = self._scale_by_calcium(ca, U)

        else:
            U_f = self.value_extractor(self.physio_config_df, 'U_f')
            self.output_namespace['U_f'] = self._scale_by_calcium(ca, U_f)

    def STDP(self):
        '''
        The STDP method for assigning the STDP parameters to the customized_synapses() object.

        :param output_synapse:  This is the dictionary created in neuron_reference() in brian2_obj_namespaces module. This contains all the information about the synaptic connection. In this method, STDP parameters are directly added to this variable. Following STDP values are set in this method: Apre, Apost, Tau_pre, Tau_post, wght_max, wght0.
        '''
        self.output_namespace['Apre'], self.output_namespace['Apost'], self.output_namespace['taupre'], \
        self.output_namespace['taupost'] = self.value_extractor(self.physio_config_df,'stdp_%s_%s' % (self.output_synapse['pre_group_type'], \
            self.output_synapse['post_group_type'] + self.output_synapse['post_comp_name']))
        stdp_max_strength_coefficient = self.value_extractor(self.physio_config_df,'stdp_max_strength_coefficient')
        self.output_namespace['wght_max'] = self.value_extractor(self.physio_config_df,'cw_%s_%s'% (self.output_synapse['pre_group_type'],self.output_synapse['post_group_type']))* stdp_max_strength_coefficient
        std_wght = self.value_extractor(self.physio_config_df,'cw_%s_%s' % (self.output_synapse['pre_group_type'], self.output_synapse['post_group_type'])) / nS
        mu_wght = std_wght / 2.
        self.output_namespace['init_wght'] = '(%f * rand() + %f) * nS' % (std_wght , mu_wght)
        std_delay = self.value_extractor(self.physio_config_df,'delay_%s_%s' % (self.output_synapse['pre_group_type'], self.output_synapse['post_group_type'])) / ms
        min_delay = std_delay / 2.
        self.output_namespace['delay'] = '(%f * rand() + %f) * ms' % (std_delay, min_delay)

    def STDP_with_scaling(self):
        '''
        The STDP method for assigning the STDP parameters to the customized_synapses() object.

        :param output_synapse:  This is the dictionary created in neuron_reference() in brian2_obj_namespaces module. This contains all the information about the synaptic connection. In this method, STDP parameters are directly added to this variable. Following STDP values are set in this method: Apre, Apost, Tau_pre, Tau_post, wght_max, wght0.
        '''
        self.output_namespace['Apre'], self.output_namespace['Apost'], self.output_namespace['taupre'], \
        self.output_namespace['taupost'] = self.value_extractor(self.physio_config_df,'stdp_%s_%s' % (self.output_synapse['pre_group_type'], \
            self.output_synapse['post_group_type'] + self.output_synapse['post_comp_name']))
        self.output_namespace['tau_synaptic_scaling'] = self.value_extractor(self.physio_config_df,
                                                                             'tau_synaptic_scaling')
        self.output_namespace['ap_target_frequency'] = self.value_extractor(self.physio_config_df,
                                                                             'ap_target_frequency')
        self.output_namespace['scaling_speed'] = self.value_extractor(self.physio_config_df,
                                                                             'scaling_speed')
        stdp_max_strength_coefficient = self.value_extractor(self.physio_config_df,'stdp_max_strength_coefficient')
        self.output_namespace['wght_max'] = self.value_extractor(self.physio_config_df,'cw_%s_%s'% (self.output_synapse['pre_group_type'],self.output_synapse['post_group_type']))* stdp_max_strength_coefficient
        std_wght = self.value_extractor(self.physio_config_df,'cw_%s_%s' % (self.output_synapse['pre_group_type'], self.output_synapse['post_group_type'])) / nS
        mu_wght = std_wght / 2.
        self.output_namespace['init_wght'] = '(%f * rand() + %f) * nS' % (std_wght , mu_wght)
        std_delay = self.value_extractor(self.physio_config_df,'delay_%s_%s' % (self.output_synapse['pre_group_type'], self.output_synapse['post_group_type'])) / ms
        min_delay = std_delay / 2.
        self.output_namespace['delay'] = '(%f * rand() + %f) * ms' % (std_delay, min_delay)


    def Fixed(self):
        '''
        The Fixed method for assigning the parameters for Fixed synaptic connection to the customized_synapses() object.

        :param output_synapse: This is the dictionary created in neuron_reference() in brian2_obj_namespaces module. This contains all the information about the synaptic connection. In this method, STDP parameters are directly added to this variable. Following STDP values are set in this method: wght_max, wght0.
        '''

        # Obviously you don't need STDP for a FIXED synapse
        # stdp_max_strength_coefficient = self.value_extractor(self.physio_config_df, 'stdp_max_strength_coefficient')
        self.output_namespace['wght_max'] = self.value_extractor(self.physio_config_df, 'cw_%s_%s' % (self.output_synapse['pre_group_type'], self.output_synapse['post_group_type'])) #* stdp_max_strength_coefficient
        std_wght = self.value_extractor(self.physio_config_df,'cw_%s_%s' % (self.output_synapse['pre_group_type'], self.output_synapse['post_group_type'])) / nS
        min_wght = std_wght / 2.

        # NB! This only scales std_wght, not min_wght! Thus commented out
        # if self.calcium_concentration > 0: # For change_calcium()
        #     self.cw_baseline_calcium = std_wght
        #     std_wght = self._scale_cw_by_calcium(self.calcium_concentration)

        self.output_namespace['init_wght'] = '(%f * rand() + %f) * nS' % (std_wght , min_wght)
        std_delay = self.value_extractor(self.physio_config_df,'delay_%s_%s' % (self.output_synapse['pre_group_type'], self.output_synapse['post_group_type'])) / ms
        min_delay = std_delay / 2.
        self.output_namespace['delay'] = '(%f * rand() + %f) * ms' % (std_delay, min_delay)

    def Fixed_calcium(self):
        '''
        The Fixed method for assigning the parameters for Fixed synaptic connection to the customized_synapses() object.
        This synapse was used in the 1st submitted version, but was later deemed non-valid in terms of calcium scaling

        :param output_synapse: This is the dictionary created in neuron_reference() in brian2_obj_namespaces module. This contains all the information about the synaptic connection. In this method, STDP parameters are directly added to this variable. Following STDP values are set in this method: wght_max, wght0.
        '''

        mean_wght = self.value_extractor(self.physio_config_df,'cw_%s_%s' % (self.output_synapse['pre_group_type'], self.output_synapse['post_group_type'])) / nS
        min_wght = mean_wght / 2.

        # SCALE the weight parameters wrt calcium
        # Calcium scaling is just multiplication by a constant so we can scale min and mean wght
        # instead of scaling individual weights separately after randomization
        if self.calcium_concentration > 0:
            mean_wght = self._scale_by_calcium(self.calcium_concentration, mean_wght)
            min_wght = self._scale_by_calcium(self.calcium_concentration, min_wght)

        # SET the weight (uniform distribution [min_wght, min_wght+mean_wght])
        # NB!! You might think (min_wght, mean_wght) should be the other way around, but remember that rand gives
        # values between 0 and 1, NOT values with mean 0 like randn!
        self.output_namespace['init_wght'] = '(%f + %f * rand()) * nS' % (min_wght, mean_wght)

        # SET the synaptic delay (uniform distribution [min_delay, min_delay+mean_delay])
        # NB!! Same applies here, see assignment of init_wght
        mean_delay = self.value_extractor(self.physio_config_df,'delay_%s_%s' % (self.output_synapse['pre_group_type'], self.output_synapse['post_group_type'])) / ms
        min_delay = mean_delay / 2.
        self.output_namespace['delay'] = '(%f + %f * rand()) * ms' % (min_delay, mean_delay)

    def Fixed_normal(self):
        '''
         The Fixed method for assigning the parameters for Fixed synaptic connection to the customized_synapses() object.

         :param output_synapse: This is the dictionary created in neuron_reference() in brian2_obj_namespaces module. This contains all the information about the synaptic connection. In this method, STDP parameters are directly added to this variable. Following STDP values are set in this method: wght_max, wght0.
         '''

        mean_wght = self.value_extractor(self.physio_config_df, 'cw_%s_%s' % (self.output_synapse['pre_group_type'], self.output_synapse['post_group_type'])) / nS
        sd_wght = mean_wght / 2.

        # SCALE mean & SD of weight wrt calcium level
        # Calcium scaling is just multiplication by a constant so we can scale mean and SD wght
        # instead of scaling individual weights separately after randomization (change of variables of the Gaussian PDF)
        if self.calcium_concentration > 0:
            mean_wght = self._scale_by_calcium(self.calcium_concentration, mean_wght)
            sd_wght  = self._scale_by_calcium(self.calcium_concentration, sd_wght) # we don't want to prescribe SDs separately in this model

        # SET the weight
        self.output_namespace['init_wght'] = '(%f + %f*randn()) * nS' % (mean_wght, sd_wght)
        # Note that we don't scale randomized weights individually, but the parameters going into the randomization

        # SET synaptic delay
        mean_delay = self.value_extractor(self.physio_config_df, 'delay_%s_%s' % (self.output_synapse['pre_group_type'], self.output_synapse['post_group_type'])) / ms
        sd_delay = mean_delay / 2.
        self.output_namespace['delay'] = '(%f + %f*randn()) * ms' % (mean_delay, sd_delay)

    def Depressing(self):
        '''
         Depressing synapse

         '''

        # GET weight params
        mean_wght = self.value_extractor(self.physio_config_df, 'cw_%s_%s' % (self.output_synapse['pre_group_type'], self.output_synapse['post_group_type'])) / nS
        min_wght = mean_wght / 2.

        # GET time constant
        tau_d = self.value_extractor(self.physio_config_df, 'tau_d')
        self.output_namespace['tau_d'] = tau_d

        # SET utilization factor & SCALE it wrt calcium level
        self._set_utilization_factor(ca=self.calcium_concentration)

        # SET the weight (uniform distribution [min_wght, min_wght+mean_wght])
        # NB!! You might think (min_wght, mean_wght) should be the other way around, but remember that rand gives
        # values between 0 and 1, NOT values with mean 0 like randn!
        self.output_namespace['init_wght'] = '(%f + %f * rand()) * nS' % (min_wght, mean_wght)

        # SET the synaptic delay (uniform distribution [min_delay, min_delay+mean_delay])
        # NB!! Same applies here, see assignment of init_wght
        mean_delay = self.value_extractor(self.physio_config_df,'delay_%s_%s' % (self.output_synapse['pre_group_type'], self.output_synapse['post_group_type'])) / ms
        min_delay = mean_delay / 2.
        self.output_namespace['delay'] = '(%f + %f * rand()) * ms' % (min_delay, mean_delay)


    def Facilitating(self):
        '''
         Facilitating synapse

         '''
        # GET weight params
        mean_wght = self.value_extractor(self.physio_config_df,'cw_%s_%s' % (self.output_synapse['pre_group_type'], self.output_synapse['post_group_type'])) / nS
        min_wght = mean_wght / 2.

        # GET time constants
        tau_fd = self.value_extractor(self.physio_config_df, 'tau_fd')
        self.output_namespace['tau_fd'] = tau_fd
        tau_f = self.value_extractor(self.physio_config_df, 'tau_f')
        self.output_namespace['tau_f'] = tau_f

        # SET utilization factor & SCALE it wrt calcium level
        self._set_utilization_factor(is_facilitating=True, ca=self.calcium_concentration)

        # SET the weight (uniform distribution [min_wght, min_wght+mean_wght])
        # NB!! You might think (min_wght, mean_wght) should be the other way around, but remember that rand gives
        # values between 0 and 1, NOT values with mean 0 like randn!
        self.output_namespace['init_wght'] = '(%f + %f * rand()) * nS' % (min_wght, mean_wght)

        # SET the synaptic delay (uniform distribution [min_delay, min_delay+mean_delay])
        # NB!! Same applies here, see assignment of init_wght
        mean_delay = self.value_extractor(self.physio_config_df,'delay_%s_%s' % (self.output_synapse['pre_group_type'], self.output_synapse['post_group_type'])) / ms
        min_delay = mean_delay / 2.
        self.output_namespace['delay'] = '(%f + %f * rand()) * ms' % (min_delay, mean_delay)


#############################################
##################### Neurons  #############
############################################


class neuron_parser (object):
    'This class embeds all parameter sets associated to all neuron types and will return it as a namespace in form of dictionary'
    def __init__(self, output_neuron,physio_config_df):
        self.physio_config_df = physio_config_df
        neuron_parser.type_ref = array(['PC', 'SS', 'BC', 'MC', 'L1i', 'VPM','HH_E','HH_I'])
        assert output_neuron['type'] in neuron_parser.type_ref, " -  Cell type '%s' is not defined." % output_neuron['category']
        self.output_namespace = {}
        variable_start_idx = self.physio_config_df['Variable'][self.physio_config_df['Variable'] == output_neuron['type']].index[0]
        try:
            variable_end_idx = self.physio_config_df['Variable'].dropna().index.tolist()[
                self.physio_config_df['Variable'].dropna().index.tolist().index(variable_start_idx) + 1]
            cropped_df = self.physio_config_df.loc[variable_start_idx:variable_end_idx-1]
        except IndexError:
            cropped_df = self.physio_config_df.loc[variable_start_idx:]

        root_variables = self.physio_config_df[self.physio_config_df['Key'].isnull()].dropna(subset=['Variable'])
        cropped_with_root = root_variables.append(cropped_df)


        for neural_parameter in cropped_df['Key'].dropna():
            self.output_namespace[neural_parameter] = self.value_extractor(cropped_with_root,neural_parameter)

        getattr(self, '_'+ output_neuron['type'])(output_neuron)

        # // AdEx-specific code BEGINS //
        try:
            flag_adex = self.value_extractor(self.physio_config_df, 'flag_adex')
            if flag_adex == 1:
                rheobase = self.output_namespace['rheobase_adex']
                depolarization_level = self.value_extractor(self.physio_config_df, 'depolarization_level')

                if output_neuron['type'] == 'PC':
                    rheobase = rheobase[output_neuron['dend_comp_num']-1]
                    # print('-> dend extent: '+str(output_neuron[
                    # 'dend_comp_num']))

                self.output_namespace['adex_depolarization'] = rheobase * depolarization_level
                # print('Rheobase: '+str(rheobase))
            else:
                # print('Using NON-adaptive EIF model')
                self.output_namespace['adex_depolarization'] = 0*pA
        except:
            self.output_namespace['adex_depolarization'] = 0 * pA
        # // AdEx-specific code ENDS //


    def _compute_adex_rheobase(self):
        a = self.output_namespace['a']
        gL = np.sum(self.output_namespace['gL'])
        tau_w = self.output_namespace['tau_w']
        tau_m = self.output_namespace['taum_soma']
        VT = self.output_namespace['VT']
        EL = self.output_namespace['EL']
        DeltaT = self.output_namespace['DeltaT']

        bif_type = (a / gL) * (tau_w / tau_m)

        if bif_type < 1:  # saddle-node bifurcation
            rheobase = (gL + a) * (VT - EL - DeltaT + DeltaT * log(1 + a / gL))

        elif bif_type > 1:  # Andronov-Hopf bifurcation
            rheobase = (gL + a) * (VT - EL - DeltaT + DeltaT * log(1 + tau_m / tau_w)) + DeltaT * gL * (
            (a / gL) - (tau_m / tau_w))

        else:
            print('Unable to compute rheobase!')
            rheobase = 0 * pA

        return rheobase

    def _PC(self,output_neuron):
        '''
        :param parameters_type: The type of parameters associated to compartmental neurons. 'Generic' is the common type. Other types could be defined when discovered in literature.
        :type parameters_type: String
        :return:
        :rtype:
        '''

        # total capacitance in compartments. The *2 comes from Markram et al Cell 2015: corrects for the dendritic spine area
        self.output_namespace['C']= self.output_namespace['fract_areas'][output_neuron['dend_comp_num']] * self.output_namespace['Cm'] * self.output_namespace['Area_tot_pyram'] *2
        # if output_neuron['soma_layer'] in [6]: # neuroelectro portal layer5/6 capacitance ??????
        #     self.output_namespace['C'] = self.output_namespace['fract_areas'][output_neuron['dend_comp_num']] * self.output_namespace['Cm'] * self.output_namespace['Area_tot_pyram']
        # total g_leak in compartments
        self.output_namespace['gL']= self.output_namespace['fract_areas'][output_neuron['dend_comp_num']] * self.output_namespace['gL'] * self.output_namespace['Area_tot_pyram']
        self.output_namespace['taum_soma'] = self.output_namespace['C'][1] / self.output_namespace['gL'][1]

    def _BC(self,output_neuron):
        pass

    def _L1i(self,output_neuron):
        pass

    def _VPM(self,output_neuron):
        pass

    def _MC(self,output_neuron):
        pass

    def _SS(self,output_neuron):
        pass

    def _HH_E(self, output_neuron):
        pass
    def _HH_I(self, output_neuron):
        pass

    def value_extractor(self, df, key_name):
        non_dict_indices = df['Variable'].dropna()[df['Key'].isnull()].index.tolist()
        for non_dict_idx in non_dict_indices:
            exec("%s=%s" % (df['Variable'][non_dict_idx], df['Value'][
                non_dict_idx]))
        try:
            return eval(key_name)
        except (NameError, TypeError):
            pass
        try:
            if type(key_name) == list:
                variable_start_idx = df['Variable'][df['Variable'] == key_name[0]].index[0]
                try:
                    variable_end_idx = df['Variable'].dropna().index.tolist()[
                        df['Variable'].dropna().index.tolist().index(variable_start_idx) + 1]
                    cropped_df = df.loc[variable_start_idx:variable_end_idx-1]
                except IndexError:
                    cropped_df = df.loc[variable_start_idx:]
                return eval(cropped_df['Value'][cropped_df['Key'] == key_name[1]].item())
            else:
                try:
                    return eval(df['Value'][df['Key'] == key_name].item())
                except NameError:
                    df_reset_index = df.reset_index(drop=True)
                    df_reset_index = df_reset_index[0:df_reset_index[df_reset_index['Key'] == key_name].index[0]]
                    for neural_parameter in df_reset_index['Key'].dropna():
                        if neural_parameter  in df['Value'][df['Key'] == key_name].item():
                            exec("%s =self.value_extractor(df,"
                                  "neural_parameter)" % (neural_parameter))
                    return eval(df['Value'][df['Key'] == key_name].item())
                except TypeError:
                    raise TypeError('The syntax %s is not a valid syntax for physiological configuration file or the elements that comprise this syntax are not defined.'%df['Value'][df['Key'] == key_name].item())

        except NameError:
            new_key = df['Value'][df['Key'] == key_name].item().replace("']", "").split("['")
            return self.value_extractor(df,new_key)

