# -*- coding: utf-8 -*-
__author__ = 'Andalibi, V., Hokkanen H., Vanni, S.'

'''
The preliminary version of this software has been developed at Aalto University 2012-2015, 
and the full version at the University of Helsinki 2013-2017. The software is distributed 
under the terms of the GNU General Public License. 
Copyright 2017 Vafa Andalibi, Henri Hokkanen and Simo Vanni.
'''

import random as rnd

import brian2 as b2
import numpy as np
from brian2.units import *
from numpy import nan

from cxsystem2.core import equation_templates as eqt
from cxsystem2.core.parameter_parser import SynapseParser, NeuronParser
from cxsystem2.neurodynlib.neuron_models import neuron_factory


class NeuronReference:
    """
    Using this class, a dictionary object is created which contains all parameters and variables that are needed to \
    create a group of that customized cell. This dictionary will eventually be used in process of building the cortical module.\
    New types of neurons should be implemented in this class.
    """

    def __init__(self,
                 idx,
                 number_of_neurons,
                 cell_type,
                 layers_idx,
                 general_grid_radius,
                 min_distance,
                 physio_config_df,
                 network_center=0 + 0j,
                 cell_subtype='--'):
        """
        initialize the NeuronReference based on the arguments.

        :param number_of_neurons: number of neurons in the NeuronGroup() object.
        :param cell_type: type of cell in the NeuronGroup: currently PC, SS, BC, MC and L1i.
        :param layers_idx: indicating the layer in which the cell group is located. In case of SS, BC, MC and L1i it is an integer but for PC
                            which is a multi-compartmental neuron, it is a tuple array. This tuple numpy array defines the first and last
                            layers in which the neuron resides. So np.array([4,1]) means that the soma resides in layer 4 and the apical
                            dendrites which are (2 compartments) extend to layer 2/3 and 1. To avoid confusion, layer 2 is used as the indicator
                            of layer 2/3. Hence, if the last compartment of a neuron is in layer 2/3, use number 2.
        :param network_center: as the name implies, this argument defines the center of teh NeuronGroup() in visual field coordinates.
                                The default value is 0+0j.
        :param resolution: resolution for formation of neurons in the grid. Default value is 0.1

        Main internal variables:

        * output_neuron: the main dictionary containing all the data about current Customized_neuron_group including: number of neurons, threshold,
                         reset, refractory, neuron type, soma position(layer), dendrites layer, total number of compartments, namespace, equation,
                         positions (both in cortical and visual coordinates).
        """

        # <editor-fold desc="...General neuron model initialization">
        self.physio_config_df = physio_config_df
        NeuronReference._celltypes = np.array(['PC', 'SS', 'BC', 'MC', 'L1i', 'VPM', 'HH_I', 'HH_E', 'NDNEURON'])
        assert general_grid_radius > min_distance, ' -  The distance between cells should be less than the grid radius'
        assert cell_type in NeuronReference._celltypes, " -  Cell type '%s' is not defined" % cell_type  # check cell type
        assert len(layers_idx) < 3, " -  Length of layers_idx array is larger than 2"  # check layer index
        if len(layers_idx) == 2:
            assert layers_idx[1] <= layers_idx[0], " -  Indices of the layer_idx array are not descending"
        elif len(layers_idx) == 1:
            assert cell_type != 'PC', " -  Cell type is PC but the start and end of the neuron is not defined in layers_idx"
        # final neuron is the output neuron containing equation, parameters
        self.output_neuron = {'idx': int(idx),
                              'number_of_neurons': int(number_of_neurons),
                              'threshold': 'vm>Vcut',
                              'reset': 'vm=V_res',
                              'refractory': '4 * ms',
                              'type': cell_type,
                              'subtype': cell_subtype,
                              'soma_layer': int(layers_idx[0])}
        # _comparts_tmp1 & 2 are for extracting the layer of the compartments if applicable
        if self.output_neuron['type'] == 'PC':
            self._comparts_tmp1 = np.array(list(range(layers_idx[0] - 1, layers_idx[1] - 1, -1)))
            self._comparts_tmp2 = np.delete(self._comparts_tmp1,
                                            np.where(self._comparts_tmp1 == 3)) if 3 in self._comparts_tmp1 else self._comparts_tmp1
            self.output_neuron['dends_layer'] = self._comparts_tmp2
            self.output_neuron['dend_comp_num'] = len(self.output_neuron['dends_layer'])
            self.output_neuron['total_comp_num'] = self.output_neuron['dend_comp_num'] + 3

        else:
            self.output_neuron['dends_layer'] = self.output_neuron['soma_layer']
            self.output_neuron['dend_comp_num'] = np.array([0])
            self.output_neuron['total_comp_num'] = np.array([1])
            # number of compartments if applicable

        self.output_neuron['namespace'] = NeuronParser(self.output_neuron, physio_config_df).output_namespace
        self.output_neuron['equation'] = ''
        # </editor-fold>

        # <editor-fold desc="...Model variation setup">
        try:
            self.model_variation = self.value_extractor(self.physio_config_df, 'model_variation')

            if self.model_variation == 1:
                # print(' -  Model variation is set ON')

                # For non-pyramidal groups
                if cell_type != 'PC':
                    try:
                        self.neuron_model = self.value_extractor(self.physio_config_df, 'neuron_model').upper()
                        print(' -  Neuron model is %s ' % self.neuron_model)
                        # if self.neuron_model == 'ADEX':
                        #     self.output_neuron['reset'] += '; w=w+'+repr(self.output_neuron['namespace']['b'])
                    except:
                        self.neuron_model = 'EIF'
                        print(' !  No point neuron model defined, using EIF')

                    try:
                        self.excitation_model = self.value_extractor(self.physio_config_df, 'excitation_model').upper()
                    except:
                        self.excitation_model = 'SIMPLE_E'
                        print(' !  No point neuron excitation model defined, using simple')

                    try:
                        self.inhibition_model = self.value_extractor(self.physio_config_df, 'inhibition_model').upper()
                    except:
                        self.inhibition_model = 'SIMPLE_I'
                        print(' !  No point neuron inhibition model defined, using simple')

                # For pyramidal groups
                else:
                    try:
                        self.pc_neuron_model = self.value_extractor(self.physio_config_df, 'pc_neuron_model').upper()
                        # if self.pc_neuron_model == 'ADEX':
                        #     self.output_neuron['reset'] += '; w=w+'+repr(self.output_neuron['namespace']['b'])
                    except:
                        self.pc_neuron_model = self.neuron_model
                        print(' !  No pyramidal cell neuron model defined, using %s' % self.neuron_model)

                    try:
                        self.pc_excitation_model = self.value_extractor(self.physio_config_df, 'pc_excitation_model').upper()
                    except:
                        self.pc_excitation_model = self.excitation_model
                        print(' !  No pyramidal cell excitation model defined, using %s' % self.excitation_model)

                    try:
                        self.pc_inhibition_model = self.value_extractor(self.physio_config_df, 'pc_inhibition_model').upper()
                    except:
                        self.pc_inhibition_model = self.inhibition_model
                        print(' !  No pyramidal cell inhibition model defined, using %s' % self.inhibition_model)

            else:
                self.model_variation = False

        except:
            self.model_variation = False
        # </editor-fold>

        # <editor-fold desc="...Extracting parameters from physiological config file">
        try:
            variable_start_idx = self.physio_config_df['Variable'][self.physio_config_df['Variable'] == self.output_neuron['subtype']].index[0]
        except:  # falling back to general cell type
            variable_start_idx = self.physio_config_df['Variable'][self.physio_config_df['Variable'] == self.output_neuron['type']].index[0]

        try:
            variable_end_idx = self.physio_config_df['Variable'].dropna().index.tolist()[
                self.physio_config_df['Variable'].dropna().index.tolist().index(variable_start_idx) + 1]
            self.cropped_df_for_current_type = self.physio_config_df.loc[variable_start_idx:variable_end_idx - 1]
        except IndexError:
            self.cropped_df_for_current_type = self.physio_config_df.loc[variable_start_idx:]
        getattr(self, self.output_neuron['type'])()
        # </editor-fold>

        # <editor-fold desc="...Creating positions">
        # w = position in cortex (in mm), z = position in retina (in mm)
        self.output_neuron['z_center'] = network_center
        self.output_neuron['w_center'] = 17 * np.log(self.output_neuron['z_center'] + 1)
        self.output_neuron['w_positions'] = self._get_w_positions(self.output_neuron['number_of_neurons'],
                                                                  'fixed_grid', general_grid_radius, min_distance)
        # self.output_neuron['w_positions'] = 17 * np.log(self.output_neuron['z_positions'] + 1)
        self.output_neuron['z_positions'] = list(map(lambda x: np.e ** (x / 17) - 1, self.output_neuron['w_positions']))
        print(" -  Customized " + str(cell_type) + " neuron in layer " + str(layers_idx) + " initialized with " +
              str(self.output_neuron['number_of_neurons']) + " neurons.")

    def _get_w_positions(self, n, layout, general_grid_radius, min_distance):

        # w position = position in cortex, in millimeters
        r = general_grid_radius / mm
        possible_pos_idx = arange(-r, r, min_distance / mm)
        _positions = []
        if layout == 'fixed_grid':
            _positions = [(rnd.choice(possible_pos_idx), rnd.choice(possible_pos_idx)) for _, _ in zip(list(range(n)), list(range(n)))]
            for idx, item in enumerate(_positions):
                while np.sqrt(_positions[idx][0] ** 2 + _positions[idx][1] ** 2) > r:
                    _positions[idx] = (rnd.choice(possible_pos_idx), rnd.choice(possible_pos_idx))
            # _positions =[tuple(map(operator.add,_itm, (float(real(_centre)),float(imag(_centre))))) for _itm in _positions]
            _positions = [complex(_itm[0], _itm[1]) + self.output_neuron['w_center'] for _itm in _positions]
        return _positions

    def NDNEURON(self):
        """
        NDNEURON type, just for testing Neurodynlib

        :return:
        """

        x = neuron_factory().get_class(self.neuron_model)
        x.set_excitatory_receptors(self.excitation_model)
        x.set_inhibitory_receptors(self.inhibition_model)

        if 'noise_sigma' in self.output_neuron['namespace'].keys():
            noise_sigma = self.output_neuron['namespace']['noise_sigma']
            x.add_vm_noise(noise_sigma)

        if 'tonic_current' in self.output_neuron['namespace'].keys():
            tonic_current = self.output_neuron['namespace']['tonic_current']
            tau_tonic_rampup = self.output_neuron['namespace']['tau_tonic_rampup']
            x.add_tonic_current(tonic_current, tau_tonic_rampup)

        self.output_neuron['equation'] = x.get_compartment_equations('soma')
        self.output_neuron['threshold'] = x.get_threshold_condition()
        self.output_neuron['reset'] = x.get_reset_statements()
        self.output_neuron['refractory'] = x.get_refractory_period()

        self.output_neuron['equation'] += b2.Equations('''x : meter
            y : meter''')

    def PC(self):
        """
        This method build up the equation for PC neurons based on the number of compartments.
        The final equation is then saved in output_neuron['equation'].

        Main internal variables:

        * eq_template_soma: Contains template somatic equation, the variables in side the equation could be
            replaced later using "Equation" function in brian2. :

            ::

                dvm/dt = (gL*(EL-vm) + gealpha * (Ee-vm) + gealphaX * (Ee-vm) + gialpha * (Ei-vm)
                         + gL * DeltaT * exp((vm-VT) / DeltaT) +I_dendr) / C : volt (unless refractory)
                dge/dt = -ge/tau_e : siemens
                dgealpha/dt = (ge-gealpha)/tau_e : siemens
                dgeX/dt = -geX/tau_eX : siemens
                dgealphaX/dt = (geX-gealphaX)/tau_eX : siemens
                dgi/dt = -gi/tau_i : siemens
                dgialpha/dt = (gi-gialpha)/tau_i : siemens
                x : meter
                y : meter

        * eq_template_dend: Contains template dendritic equation:

            ::

                dvm/dt = (gL*(EL-vm) + gealpha * (Ee-vm) + gealphaX * (Ee-vm) + gialpha * (Ei-vm)
                        + gL * DeltaT * exp((vm-VT) / DeltaT) +I_dendr) / C : volt (unless refractory)
                dge/dt = -ge/tau_e : siemens
                dgealpha/dt = (ge-gealpha)/tau_e : siemens
                dgeX/dt = -geX/tau_eX : siemens
                dgealphaX/dt = (geX-gealphaX)/tau_eX : siemens
                dgi/dt = -gi/tau_i : siemens
                dgialpha/dt = (gi-gialpha)/tau_i : siemens

        """

        if self.model_variation is False:  # For backwards compatibility

            assert 'noise_sigma' in self.output_neuron['namespace'].keys(), \
                "Noise sigma is used in model_variation model, but it is not defined in the configuration file. " \
                "Did you mean to set model_variation  in physiologyi configuration to 1? "
            # <editor-fold desc="...Fixed equations">
            eq_template_soma = '''
            dvm/dt = ((gL*(EL-vm) + gealpha * (Ee-vm) + gialpha * (Ei-vm) + gL * DeltaT * exp((vm-VT) / DeltaT) 
                     + I_dendr +tonic_current*(1-exp(-t/(50*msecond)))) / C) + noise_sigma*xi*taum_soma**-0.5 : volt (unless refractory)
            dge/dt = -ge/tau_e : siemens
            dgealpha/dt = (ge-gealpha)/tau_e : siemens
            dgi/dt = -gi/tau_i : siemens
            dgialpha/dt = (gi-gialpha)/tau_i : siemens
            '''
            eq_template_dend = '''
            dvm/dt = (gL*(EL-vm) + gealpha * (Ee-vm) + gialpha * (Ei-vm) +I_dendr) / C : volt
            dge/dt = -ge/tau_e : siemens
            dgealpha/dt = (ge-gealpha)/tau_e : siemens
            dgi/dt = -gi/tau_i : siemens
            dgialpha/dt = (gi-gialpha)/tau_i : siemens
            '''

            self.output_neuron['equation'] = b2.Equations(eq_template_dend, vm="vm_basal", ge="ge_basal",
                                                          gealpha="gealpha_basal",
                                                          C=self.output_neuron['namespace']['C'][0],
                                                          gL=self.output_neuron['namespace']['gL'][0],
                                                          gi="gi_basal", geX="geX_basal", gialpha="gialpha_basal",
                                                          gealphaX="gealphaX_basal", I_dendr="Idendr_basal")
            self.output_neuron['equation'] += b2.Equations(eq_template_soma, gL=self.output_neuron['namespace']['gL'][1],
                                                           ge='ge_soma', geX='geX_soma', gi='gi_soma',
                                                           gealpha='gealpha_soma',
                                                           gealphaX='gealphaX_soma',
                                                           gialpha='gialpha_soma',
                                                           C=self.output_neuron['namespace']['C'][1],
                                                           I_dendr='Idendr_soma',
                                                           taum_soma=self.output_neuron['namespace']['taum_soma'])
            for _ii in range(
                    self.output_neuron['dend_comp_num'] + 1):  # extra dendritic compartment in the same level of soma
                self.output_neuron['equation'] += b2.Equations(eq_template_dend, vm="vm_a%d" % _ii,
                                                               C=self.output_neuron['namespace']['C'][_ii],
                                                               gL=self.output_neuron['namespace']['gL'][_ii],
                                                               ge="ge_a%d" % _ii,
                                                               gi="gi_a%d" % _ii, geX="geX_a%d" % _ii,
                                                               gealpha="gealpha_a%d" % _ii, gialpha="gialpha_a%d" % _ii,
                                                               gealphaX="gealphaX_a%d" % _ii, I_dendr="Idendr_a%d" % _ii)

            # Defining decay between soma and basal dendrite & apical dendrites
            self.output_neuron['equation'] += b2.Equations('I_dendr = gapre*(vmpre-vmself)  : amp',
                                                           gapre=1 / (self.output_neuron['namespace']['Ra'][0]),
                                                           I_dendr="Idendr_basal", vmself="vm_basal", vmpre="vm")
            self.output_neuron['equation'] += b2.Equations(
                'I_dendr = gapre*(vmpre-vmself)  + gapost*(vmpost-vmself) : amp',
                gapre=1 / (self.output_neuron['namespace']['Ra'][1]),
                gapost=1 / (self.output_neuron['namespace']['Ra'][0]),
                I_dendr="Idendr_soma", vmself="vm",
                vmpre="vm_a0", vmpost="vm_basal")
            self.output_neuron['equation'] += b2.Equations('I_dendr = gapre*(vmpre-vmself) + gapost*(vmpost-vmself) : amp',
                                                           gapre=1 / (self.output_neuron['namespace']['Ra'][2]),
                                                           gapost=1 / (self.output_neuron['namespace']['Ra'][1]),
                                                           I_dendr="Idendr_a0", vmself="vm_a0", vmpre="vm_a1", vmpost="vm")

            # Defining decay between apical dendrite compartments
            for _ii in arange(1, self.output_neuron['dend_comp_num']):
                self.output_neuron['equation'] += b2.Equations(
                    'I_dendr = gapre*(vmpre-vmself) + gapost*(vmpost-vmself) : amp',
                    gapre=1 / (self.output_neuron['namespace']['Ra'][_ii]),
                    gapost=1 / (self.output_neuron['namespace']['Ra'][_ii - 1]),
                    I_dendr="Idendr_a%d" % _ii, vmself="vm_a%d" % _ii,
                    vmpre="vm_a%d" % (_ii + 1), vmpost="vm_a%d" % (_ii - 1))

            self.output_neuron['equation'] += b2.Equations('I_dendr = gapost*(vmpost-vmself) : amp',
                                                           I_dendr="Idendr_a%d" % self.output_neuron['dend_comp_num'],
                                                           gapost=1 / (self.output_neuron['namespace']['Ra'][-1]),
                                                           vmself="vm_a%d" % self.output_neuron['dend_comp_num'],
                                                           vmpost="vm_a%d" % (self.output_neuron['dend_comp_num'] - 1))
            # </editor-fold>

        else:

            # <editor-fold desc="...Model variation b2.Equations">
            # TODO - Figure out why this is different from old eqs
            # n_apical = self.output_neuron['dend_comp_num'] + 1
            # x = nd.LegacyPyramidalCell(n_apical)
            # x.set_excitatory_receptors(self.pc_excitation_model)
            # x.set_inhibitory_receptors(self.pc_inhibition_model)
            #
            # if 'noise_sigma' in self.output_neuron['namespace'].keys():
            #     noise_sigma = self.output_neuron['namespace']['noise_sigma']
            #     x.add_vm_noise(noise_sigma)
            #
            # if 'tonic_current' in self.output_neuron['namespace'].keys():
            #     tonic_current = self.output_neuron['namespace']['tonic_current']
            #     tau_tonic_rampup = self.output_neuron['namespace']['tau_tonic_rampup']
            #     x.add_tonic_current(tonic_current, tau_tonic_rampup)
            #
            # # Set parameters that are required to compile the equations
            # C_array = self.output_neuron['namespace']['C']
            # g_leak_array = self.output_neuron['namespace']['g_leak']
            # Ra_array = self.output_neuron['namespace']['Ra']
            # x.set_neuron_parameters(C=C_array, g_leak=g_leak_array, Ra=Ra_array)
            #
            # # Finally, get everything
            # self.output_neuron['equation'] = x.get_neuron_equations()
            # self.output_neuron['threshold'] = x.get_threshold_condition()
            # self.output_neuron['reset'] = x.get_reset_statements()
            # self.output_neuron['refractory'] = x.get_refractory_period()
            # </editor-fold>

            # <editor-fold desc="...Old model variation equations">
            # Old model variation equations using equation_templates (from November 2018)
            eq_template_soma = eqt.EquationHelper(neuron_model=self.pc_neuron_model, is_pyramidal=True,
                                                  compartment='soma', exc_model=self.pc_excitation_model,
                                                  inh_model=self.pc_inhibition_model).get_membrane_equation(return_string=True)
            eq_template_dend = eqt.EquationHelper(neuron_model=self.pc_neuron_model, is_pyramidal=True,
                                                  compartment='dend', exc_model=self.pc_excitation_model,
                                                  inh_model=self.pc_inhibition_model).get_membrane_equation(return_string=True)

            dendritic_extent = self.output_neuron['dend_comp_num']

            self.output_neuron['equation'] = b2.Equations(eq_template_dend, vm="vm_basal", ge="ge_basal",
                                                          gealpha="gealpha_basal",
                                                          C=self.output_neuron['namespace']['C'][0],
                                                          gL=self.output_neuron['namespace']['gL'][0],
                                                          gi="gi_basal", geX="geX_basal", gialpha="gialpha_basal",
                                                          gealphaX="gealphaX_basal", I_dendr="Idendr_basal",
                                                          gealpha1="gealpha1_basal", gialpha1="gialpha1_basal",
                                                          g_ampa="g_ampa_basal", g_ampa_alpha="g_ampa_alpha_basal",
                                                          g_ampa_alpha1="g_ampa_alpha1_basal",
                                                          g_nmda="g_nmda_basal", g_nmda_alpha="g_nmda_alpha_basal",
                                                          g_nmda_alpha1="g_nmda_alpha1_basal",
                                                          g_gabaa="g_gabaa_basal", g_gabaa_alpha="g_gabaa_alpha_basal",
                                                          g_gabaa_alpha1="g_gabaa_alpha1_basal",
                                                          g_gabab="g_gabab_basal", g_gabab_alpha="g_gabab_alpha_basal",
                                                          g_gabab_alpha1="g_gabab_alpha1_basal",
                                                          B="B_basal")

            self.output_neuron['equation'] += b2.Equations(eq_template_soma, gL=self.output_neuron['namespace']['gL'][1],
                                                           ge='ge_soma', geX='geX_soma', gi='gi_soma',
                                                           gealpha='gealpha_soma',
                                                           gealphaX='gealphaX_soma',
                                                           gialpha='gialpha_soma',
                                                           C=self.output_neuron['namespace']['C'][1],
                                                           I_dendr='Idendr_soma',
                                                           taum_soma=self.output_neuron['namespace']['taum_soma'],
                                                           gealpha1="gealpha1_soma", gialpha1="gialpha1_soma",
                                                           g_ampa="g_ampa_soma", g_ampa_alpha="g_ampa_alpha_soma",
                                                           g_ampa_alpha1="g_ampa_alpha1_soma",
                                                           g_nmda="g_nmda_soma", g_nmda_alpha="g_nmda_alpha_soma",
                                                           g_nmda_alpha1="g_nmda_alpha1_soma",
                                                           g_gabaa="g_gabaa_soma", g_gabaa_alpha="g_gabaa_alpha_soma",
                                                           g_gabaa_alpha1="g_gabaa_alpha1_soma",
                                                           g_gabab="g_gabab_soma", g_gabab_alpha="g_gabab_alpha_soma",
                                                           g_gabab_alpha1="g_gabab_alpha1_soma", B="B_soma")

            for _ii in range(
                    self.output_neuron['dend_comp_num'] + 1):  # extra dendritic compartment in the same level of soma
                self.output_neuron['equation'] += b2.Equations(eq_template_dend, vm="vm_a%d" % _ii,
                                                               C=self.output_neuron['namespace']['C'][_ii],
                                                               gL=self.output_neuron['namespace']['gL'][_ii],
                                                               ge="ge_a%d" % _ii,
                                                               gi="gi_a%d" % _ii, geX="geX_a%d" % _ii,
                                                               gealpha="gealpha_a%d" % _ii, gialpha="gialpha_a%d" % _ii,
                                                               gealphaX="gealphaX_a%d" % _ii, I_dendr="Idendr_a%d" % _ii,
                                                               gealpha1="gealpha1_a%d" % _ii,
                                                               gialpha1="gialpha1_a%d" % _ii,
                                                               g_ampa="g_ampa_a%d" % _ii,
                                                               g_ampa_alpha="g_ampa_alpha_a%d" % _ii,
                                                               g_ampa_alpha1="g_ampa_alpha1_a%d" % _ii,
                                                               g_nmda="g_nmda_a%d" % _ii,
                                                               g_nmda_alpha="g_nmda_alpha_a%d" % _ii,
                                                               g_nmda_alpha1="g_nmda_alpha1_a%d" % _ii,
                                                               g_gabaa="g_gabaa_a%d" % _ii,
                                                               g_gabaa_alpha="g_gabaa_alpha_a%d" % _ii,
                                                               g_gabaa_alpha1="g_gabaa_alpha1_a%d" % _ii,
                                                               g_gabab="g_gabab_a%d" % _ii,
                                                               g_gabab_alpha="g_gabab_alpha_a%d" % _ii,
                                                               g_gabab_alpha1="g_gabab_alpha1_a%d" % _ii,
                                                               B="B_a%d" % _ii)

            # Defining decay between soma and basal dendrite & apical dendrites
            self.output_neuron['equation'] += b2.Equations('I_dendr = gapre*(vmpre-vmself)  : amp',
                                                           gapre=1 / (self.output_neuron['namespace']['Ra'][0]),
                                                           I_dendr="Idendr_basal", vmself="vm_basal", vmpre="vm")
            self.output_neuron['equation'] += b2.Equations(
                'I_dendr = gapre*(vmpre-vmself)  + gapost*(vmpost-vmself) : amp',
                gapre=1 / (self.output_neuron['namespace']['Ra'][1]),
                gapost=1 / (self.output_neuron['namespace']['Ra'][0]),
                I_dendr="Idendr_soma", vmself="vm",
                vmpre="vm_a0", vmpost="vm_basal")

            # If there's more than one apical dendrite compartment
            if dendritic_extent > 0:

                self.output_neuron['equation'] += b2.Equations('I_dendr = gapre*(vmpre-vmself) + gapost*(vmpost-vmself) : amp',
                                                               gapre=1 / (self.output_neuron['namespace']['Ra'][2]),
                                                               gapost=1 / (self.output_neuron['namespace']['Ra'][1]),
                                                               I_dendr="Idendr_a0", vmself="vm_a0", vmpre="vm_a1", vmpost="vm")

                # Defining decay between apical dendrite compartments
                for _ii in arange(1, self.output_neuron['dend_comp_num']):
                    self.output_neuron['equation'] += b2.Equations(
                        'I_dendr = gapre*(vmpre-vmself) + gapost*(vmpost-vmself) : amp',
                        gapre=1 / (self.output_neuron['namespace']['Ra'][_ii]),
                        gapost=1 / (self.output_neuron['namespace']['Ra'][_ii - 1]),
                        I_dendr="Idendr_a%d" % _ii, vmself="vm_a%d" % _ii,
                        vmpre="vm_a%d" % (_ii + 1), vmpost="vm_a%d" % (_ii - 1))

                self.output_neuron['equation'] += b2.Equations('I_dendr = gapost*(vmpost-vmself) : amp',
                                                               I_dendr="Idendr_a%d" % self.output_neuron['dend_comp_num'],
                                                               gapost=1 / (self.output_neuron['namespace']['Ra'][dendritic_extent - 1]),
                                                               vmself="vm_a%d" % self.output_neuron['dend_comp_num'],
                                                               vmpost="vm_a%d" % (self.output_neuron['dend_comp_num'] - 1))

            # If dendritic_extent is zero ie. there's only one apical dendrite compartment
            else:
                self.output_neuron['equation'] += b2.Equations('I_dendr = gapre*(vmpre-vmself)  : amp',
                                                               gapre=1 / (self.output_neuron['namespace']['Ra'][1]),
                                                               I_dendr="Idendr_a0", vmself="vm_a0", vmpre="vm")

            # </editor-fold>

        self.output_neuron['equation'] += b2.Equations('''x : meter
                            y : meter''')

    def BC(self):
        """
        This method build up the equation for BC neurons. The final equation is then saved in output_neuron['equation'].

        * The equation of the neuron is as follows:

            ::

                dvm/dt = (gL*(EL-vm) + gL * DeltaT * exp((vm-VT) / DeltaT) + ge_soma * (Ee-vm) + gi_soma * (Ei-vm)) / C : volt (unless refractory)
                dge_soma/dt = -ge_soma/tau_e : siemens
                dgi_soma/dt = -gi_soma/tau_i : siemens
                x : meter
                y : meter
        """

        if self.model_variation is False:
            assert 'noise_sigma' in self.output_neuron['namespace'].keys(), \
                "Noise sigma is used in model_variation model, but it is not defined in the configuration file. " \
                "Did you mean to set model_variation  in physiologyi configuration to 1?"
            self.output_neuron['equation'] = b2.Equations('''
                dvm/dt = ((gL*(EL-vm) + gL * DeltaT * exp((vm-VT) / DeltaT) + ge * (Ee-vm) + gi * (Ei-vm) 
                + tonic_current*(1-exp(-t/(50*msecond)))) / C) + noise_sigma*xi*taum_soma**-0.5: volt (unless refractory)
                dge/dt = -ge/tau_e : siemens
                dgi/dt = -gi/tau_i : siemens
                ''', ge='ge_soma', gi='gi_soma')

        else:
            # self.output_neuron['equation'] = eqt.EquationHelper(neuron_model=self.neuron_model,
            #                                                     exc_model=self.excitation_model,
            #                                                     inh_model=self.inhibition_model).get_membrane_equation()
            x = neuron_factory().get_class(self.neuron_model)
            x.set_excitatory_receptors(self.excitation_model)
            x.set_inhibitory_receptors(self.inhibition_model)

            if 'noise_sigma' in self.output_neuron['namespace'].keys():
                noise_sigma = self.output_neuron['namespace']['noise_sigma']
                x.add_vm_noise(noise_sigma)

            if 'tonic_current' in self.output_neuron['namespace'].keys():
                tonic_current = self.output_neuron['namespace']['tonic_current']
                tau_tonic_rampup = self.output_neuron['namespace']['tau_tonic_rampup']
                x.add_tonic_current(tonic_current, tau_tonic_rampup)

            self.output_neuron['equation'] = x.get_compartment_equations('soma')
            self.output_neuron['threshold'] = x.get_threshold_condition()
            self.output_neuron['reset'] = x.get_reset_statements()
            self.output_neuron['refractory'] = x.get_refractory_period()

        self.output_neuron['equation'] += b2.Equations('''x : meter
            y : meter''')

    def L1i(self):
        """
        This method build up the equation for Layer 1 inhibitory (L1i) neurons. The final equation is then saved in output_neuron['equation'].

        * The equation of the neuron is as follows:

            ::

                dvm/dt = (gL*(EL-vm) + gL * DeltaT * exp((vm-VT) / DeltaT) + ge_soma * (Ee-vm) + gi_soma * (Ei-vm)) / C : volt (unless refractory)
                dge_soma/dt = -ge_soma/tau_e : siemens
                dgi_soma/dt = -gi_soma/tau_i : siemens
                x : meter
                y : meter
        """
        # eq_template = self.value_extractor(self.cropped_df_for_current_type, 'eq_template')
        # self.output_neuron['equation'] = Equations(eq_template, ge='ge_soma', gi='gi_soma')

        if self.model_variation is False:
            assert 'noise_sigma' in self.output_neuron['namespace'].keys(), \
                "Noise sigma is used in model_variation model, but it is not defined in the configuration file. " \
                "Did you mean to set model_variation  in physiologyi configuration to 1?"

            self.output_neuron['equation'] = b2.Equations('''
                dvm/dt = ((gL*(EL-vm) + gL * DeltaT * exp((vm-VT) / DeltaT) + ge * (Ee-vm) + gi * (Ei-vm) 
                + tonic_current*(1-exp(-t/(50*msecond)))) / C) + noise_sigma*xi*taum_soma**-0.5: volt (unless refractory)
                dge/dt = -ge/tau_e : siemens
                dgi/dt = -gi/tau_i : siemens
                ''', ge='ge_soma', gi='gi_soma')
        else:
            # self.output_neuron['equation'] = eqt.EquationHelper(neuron_model=self.neuron_model,
            #                                                     exc_model=self.excitation_model,
            #                                                     inh_model=self.inhibition_model).get_membrane_equation()
            x = neuron_factory().get_class(self.neuron_model)
            x.set_excitatory_receptors(self.excitation_model)
            x.set_inhibitory_receptors(self.inhibition_model)

            if 'noise_sigma' in self.output_neuron['namespace'].keys():
                noise_sigma = self.output_neuron['namespace']['noise_sigma']
                x.add_vm_noise(noise_sigma)

            if 'tonic_current' in self.output_neuron['namespace'].keys():
                tonic_current = self.output_neuron['namespace']['tonic_current']
                tau_tonic_rampup = self.output_neuron['namespace']['tau_tonic_rampup']
                x.add_tonic_current(tonic_current, tau_tonic_rampup)

            self.output_neuron['equation'] = x.get_compartment_equations('soma')
            self.output_neuron['threshold'] = x.get_threshold_condition()
            self.output_neuron['reset'] = x.get_reset_statements()
            self.output_neuron['refractory'] = x.get_refractory_period()

        self.output_neuron['equation'] += b2.Equations('''x : meter
            y : meter''')

    def MC(self):
        """
            This method build up the equation for MC neurons. The final equation is then saved in output_neuron['equation'].

            * The equation of the neuron is as follows:

                ::

                    dvm/dt = (gL*(EL-vm) + gL * DeltaT * exp((vm-VT) / DeltaT)
                            + ge_soma * (Ee-vm) + gi_soma * (Ei-vm)) / C : volt (unless refractory)
                    dge_soma/dt = -ge_soma/tau_e : siemens
                    dgi_soma/dt = -gi_soma/tau_i : siemens
                    x : meter
                    y : meter
            """
        # eq_template = self.value_extractor(self.cropped_df_for_current_type, 'eq_template')
        # self.output_neuron['equation'] = Equations(eq_template, ge='ge_soma', gi='gi_soma')

        if self.model_variation is False:
            assert 'noise_sigma' in self.output_neuron['namespace'].keys(), \
                "Noise sigma is used in model_variation model, but it is not defined in the configuration file. " \
                "Did you mean to set model_variation  in physiologyi configuration to 1?"

            self.output_neuron['equation'] = b2.Equations('''
                dvm/dt = ((gL*(EL-vm) + gL * DeltaT * exp((vm-VT) / DeltaT) + ge * (Ee-vm) + gi * (Ei-vm) 
                + tonic_current*(1-exp(-t/(50*msecond)))) / C) + noise_sigma*xi*taum_soma**-0.5: volt (unless refractory)
                dge/dt = -ge/tau_e : siemens
                dgi/dt = -gi/tau_i : siemens
                ''', ge='ge_soma', gi='gi_soma')

        else:
            # self.output_neuron['equation'] = eqt.EquationHelper(neuron_model=self.neuron_model,
            #                                                     exc_model=self.excitation_model,
            #                                                     inh_model=self.inhibition_model).get_membrane_equation()
            x = neuron_factory().get_class(self.neuron_model)
            x.set_excitatory_receptors(self.excitation_model)
            x.set_inhibitory_receptors(self.inhibition_model)

            if 'noise_sigma' in self.output_neuron['namespace'].keys():
                noise_sigma = self.output_neuron['namespace']['noise_sigma']
                x.add_vm_noise(noise_sigma)

            if 'tonic_current' in self.output_neuron['namespace'].keys():
                tonic_current = self.output_neuron['namespace']['tonic_current']
                tau_tonic_rampup = self.output_neuron['namespace']['tau_tonic_rampup']
                x.add_tonic_current(tonic_current, tau_tonic_rampup)

            self.output_neuron['equation'] = x.get_compartment_equations('soma')
            self.output_neuron['threshold'] = x.get_threshold_condition()
            self.output_neuron['reset'] = x.get_reset_statements()
            self.output_neuron['refractory'] = x.get_refractory_period()

        self.output_neuron['equation'] += b2.Equations('''x : meter
            y : meter''')

    def SS(self):
        """
            This method build up the equation for SS neurons. The final equation is then saved in output_neuron['equation'].

            * The equation of the neuron is as follows:

                ::

                    dvm/dt = (gL*(EL-vm) + gL * DeltaT * exp((vm-VT) / DeltaT) + ge_soma * (Ee-vm) + gi_soma * (Ei-vm)) / C : volt (unless refractory)
                    dge_soma/dt = -ge_soma/tau_e : siemens
                    dgi_soma/dt = -gi_soma/tau_i : siemens
                    x : meter
                    y : meter
            """

        if self.model_variation is False:
            assert 'noise_sigma' in self.output_neuron['namespace'].keys(), \
                "Noise sigma is used in model_variation model, but it is not defined in the configuration file. " \
                "Did you mean to set model_variation  in physiologyi configuration to 1?"

            self.output_neuron['equation'] = b2.Equations('''
                dvm/dt = ((gL*(EL-vm) + gL * DeltaT * exp((vm-VT) / DeltaT) + ge * (Ee-vm) + gi * (Ei-vm) 
                + tonic_current*(1-exp(-t/(50*msecond)))) / C) + noise_sigma*xi*taum_soma**-0.5: volt (unless refractory)
                dge/dt = -ge/tau_e : siemens
                dgi/dt = -gi/tau_i : siemens
                ''', ge='ge_soma', gi='gi_soma')

        else:
            # self.output_neuron['equation'] = eqt.EquationHelper(neuron_model=self.neuron_model,
            #                                                     exc_model=self.excitation_model,
            #                                                     inh_model=self.inhibition_model).get_membrane_equation()
            x = neuron_factory().get_class(self.neuron_model)
            x.set_excitatory_receptors(self.excitation_model)
            x.set_inhibitory_receptors(self.inhibition_model)

            if 'noise_sigma' in self.output_neuron['namespace'].keys():
                noise_sigma = self.output_neuron['namespace']['noise_sigma']
                x.add_vm_noise(noise_sigma)

            if 'tonic_current' in self.output_neuron['namespace'].keys():
                tonic_current = self.output_neuron['namespace']['tonic_current']
                tau_tonic_rampup = self.output_neuron['namespace']['tau_tonic_rampup']
                x.add_tonic_current(tonic_current, tau_tonic_rampup)

            self.output_neuron['equation'] = x.get_compartment_equations('soma')
            self.output_neuron['threshold'] = x.get_threshold_condition()
            self.output_neuron['reset'] = x.get_reset_statements()
            self.output_neuron['refractory'] = x.get_refractory_period()

        self.output_neuron['equation'] += b2.Equations('''x : meter
            y : meter''')

    def VPM(self):
        """
        This method build up the equation for VPM neurons. No equation is needed.
        """
        self.output_neuron['equation'] = ''

    def value_extractor(self, df, key_name):
        non_dict_indices = df['Variable'].dropna()[df['Key'].isnull()].index.tolist()
        for non_dict_idx in non_dict_indices:
            exec("%s=%s" % (df['Variable'][non_dict_idx], df['Value'][non_dict_idx]))
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
                    cropped_df = df.loc[variable_start_idx:variable_end_idx - 1]
                except IndexError:
                    cropped_df = df.loc[variable_start_idx:]
                return eval(next(iter(cropped_df['Value'][cropped_df['Key'] == key_name[1]])))
            else:
                try:
                    return eval(next(iter(df['Value'][df['Key'] == key_name])))
                except NameError:
                    df_reset_index = df.reset_index(drop=True)
                    df_reset_index = df_reset_index[0:df_reset_index[df_reset_index['Key'] == key_name].index[0]]
                    for neural_parameter in df_reset_index['Key'].dropna():
                        if neural_parameter in df['Value'][df['Key'] == key_name].item():
                            exec("%s =self.value_extractor(df,neural_parameter)" % neural_parameter)
                    return eval(next(iter(df['Value'][df['Key'] == key_name])))
                # else:
                #     raise (
                #                 'The syntax %s is not a valid syntax for physiological configuration file or
                #                 the elements that comprise this syntax are not defined.' % next(
                #             iter(df['Value'][df['Key'] == key_name])))

        except NameError:
            new_key = next(iter(df['Value'][df['Key'] == key_name])).replace("']", "").split("['")
            return self.value_extractor(df, new_key)


class SynapseReference:
    """
        In this class, a dictionary object is created which contains all parameters and variables that are needed to \
        create a Synapses() object between two neuron group. This dictionary will eventually be used in process of \
        building the cortical module. New types of synapses should be implemented in this class.
    """

    def __init__(self, receptor, pre_group_idx, post_group_idx, syn_type, pre_type, post_type, physio_config_df, post_comp_name='_soma',
                 custom_weight='--'):
        """
        initializes the SynapseReference based on its arguments.

        :param receptor: defines the type of the receptor in the synaptic connection. Currently ge and gi are implemented.
        :param pre_group_idx: The index of the pre-synaptic group.
        :param post_group_idx: The index of the post-synaptic group.
        :param syn_type: Type of the synaptic connection, currently STDP and Fixed are implemented.
        :param pre_type: Type of the pre-synaptic NeuronGroup.
        :param post_type: Type of the post-synaptic NeuronGroup.
        :param post_comp_name: Name of the target compartment in the cells of the post-synaptic NeuronGroup.
                                The default value is "_soma" as usually soma is being targeted. In case other compartments are targeted in a PC cell,
                                e.g. basal or apical dendrites, _basal or _apical will be used.

        Main internal variables:

        * output_synapse: the main dictionary containing all the data about current customized_synapse_group including: synaptic equations
                          (model, pre, post), type of synapse, type of receptor, index and type of pre- and post-synaptic group, namespace
                          for the Synapses() object, sparseness, spatial_decay.
        * _name_space: An instance of brian2_obj_namespaces() object which contains all the constant parameters for this synaptic equation.

        """
        SynapseReference.syntypes = np.array(['STDP', 'STDP_with_scaling', 'Fixed', 'Fixed_const_wght', 'Fixed_calcium', 'Depressing', 'Facilitating'])
        assert syn_type in SynapseReference.syntypes, " -  Synapse type '%s' is not defined" % syn_type
        self.output_synapse = {'type': syn_type,
                               'receptor': receptor,
                               'pre_group_idx': int(pre_group_idx),
                               'pre_group_type': pre_type,
                               'post_group_idx': int(post_group_idx),
                               'post_group_type': post_type,
                               'post_comp_name': post_comp_name,
                               'custom_weight': custom_weight}
        # self.output_synapse['namespace_type'] = namespace_type
        # self.output_synapse['pre_type'] = pre_group_type
        # self.output_synapse['post_type'] = post_group_type
        _name_space = SynapseParser(self.output_synapse, physio_config_df)
        self.output_synapse['namespace'] = {}
        self.output_synapse['namespace'] = _name_space.output_namespace
        try:
            self.output_synapse['sparseness'] = _name_space.sparseness
        except:
            pass
        # self.output_synapse['ilam'] = _name_space.ilam   # HH commented this, because it's not used right now

        # <editor-fold desc="...Model variation setup">
        try:
            self.model_variation = self.value_extractor(physio_config_df, 'model_variation')
            if self.model_variation == 1:
                # <editor-fold desc="Extract model names">
                # Just extract everything like in NeuronReference (otherwise many if-elses)
                # For non-pyramidal groups
                try:
                    self.excitation_model = self.value_extractor(physio_config_df, 'excitation_model').upper()
                except:
                    self.excitation_model = 'SIMPLE_E'

                try:
                    self.inhibition_model = self.value_extractor(physio_config_df, 'inhibition_model').upper()
                except:
                    self.inhibition_model = 'SIMPLE_I'

                # For pyramidal groups
                try:
                    self.pc_excitation_model = self.value_extractor(physio_config_df,
                                                                    'pc_excitation_model').upper()
                except:
                    self.pc_excitation_model = self.excitation_model

                try:
                    self.pc_inhibition_model = self.value_extractor(physio_config_df,
                                                                    'pc_inhibition_model').upper()
                except:
                    self.pc_inhibition_model = self.inhibition_model
                # </editor-fold>

                # NOW the if-else jungle
                if self.output_synapse['post_group_type'] == 'PC':
                    if self.output_synapse['receptor'] == 'ge':
                        self.true_receptors = eqt.EquationHelper.Receptors[self.pc_excitation_model]
                    else:
                        self.true_receptors = eqt.EquationHelper.Receptors[self.pc_inhibition_model]
                else:
                    if self.output_synapse['receptor'] == 'ge':
                        self.true_receptors = eqt.EquationHelper.Receptors[self.excitation_model]
                    else:
                        self.true_receptors = eqt.EquationHelper.Receptors[self.inhibition_model]

            else:
                self.model_variation = False

        except:
            self.model_variation = False
        # </editor-fold>

        getattr(self, self.output_synapse['type'])()

    def STDP(self):
        """
        The method for implementing the STDP synaptic connection.

        """

        self.output_synapse['equation'] = b2.Equations('''
            wght : siemens
            wght0 : siemens
            dapre/dt = -apre/taupre : siemens (event-driven)
            dapost/dt = -apost/taupost : siemens (event-driven)
            ''')

        if self.output_synapse['namespace']['Apre'] >= 0:
            self.output_synapse['pre_eq'] = '''
                        %s+=wght
                        apre += Apre * wght0 * Cp
                        wght = clip(wght + apost, 0, wght_max)
                        ''' % (self.output_synapse['receptor'] + self.output_synapse['post_comp_name'] + '_post')
        else:
            self.output_synapse['pre_eq'] = '''
                        %s+=wght
                        apre += Apre * wght * Cd
                        wght = clip(wght + apost, 0, wght_max)
                        ''' % (self.output_synapse['receptor'] + self.output_synapse['post_comp_name'] + '_post')
        if self.output_synapse['namespace']['Apost'] <= 0:
            self.output_synapse['post_eq'] = '''
                        apost += Apost * wght * Cd
                        wght = clip(wght + apre, 0, wght_max)
                        '''
        else:
            self.output_synapse['post_eq'] = '''
                        apost += Apost * wght0 * Cp
                        wght = clip(wght + apre, 0, wght_max)
                        '''

    def STDP_with_scaling(self):
        """
        The method for implementing the STDP synaptic connection.

        """
        # TODO scaling to all synapses in a cell. Invert for inhibitory synapses. Check hertz for spike monitor,
        # TODO check scaling factors with simulations.
        self.output_synapse['equation'] = b2.Equations('''
            wght0 : siemens
            dwght/dt = scaling_speed * wght * (ap_target_frequency - spike_sensor)  : siemens (event-driven)
            dapre/dt = -apre/taupre : siemens (event-driven)
            dapost/dt = -apost/taupost : siemens (event-driven)
            dspike_sensor/dt = -spike_sensor/tau_synaptic_scaling : hertz (event-driven)
            ''')

        if self.output_synapse['namespace']['Apre'] >= 0:
            self.output_synapse['pre_eq'] = '''
                        %s+=wght
                        apre += Apre * wght0 * Cp
                        wght = clip(wght + apost, 0, wght_max)
                        ''' % (self.output_synapse['receptor'] + self.output_synapse['post_comp_name'] + '_post')
        else:
            self.output_synapse['pre_eq'] = '''
                        %s+=wght
                        apre += Apre * wght * Cd
                        wght = clip(wght + apost, 0, wght_max)
                        ''' % (self.output_synapse['receptor'] + self.output_synapse['post_comp_name'] + '_post')
        if self.output_synapse['namespace']['Apost'] <= 0:
            self.output_synapse['post_eq'] = '''
                        apost += Apost * wght * Cd
                        wght = clip(wght + apre, 0, wght_max)
                        spike_sensor += 1 * hertz
                        '''
        else:
            self.output_synapse['post_eq'] = '''
                        apost += Apost * wght0 * Cp
                        wght = clip(wght + apre, 0, wght_max)
                        spike_sensor += 1 * hertz
                        '''

    def Fixed(self):
        """
        The method for implementing the Fixed synaptic connection.

        """

        self.output_synapse['equation'] = b2.Equations('''
            wght:siemens
            ''')

        if self.model_variation is False:
            self.output_synapse['pre_eq'] = '''
            %s+=wght
            ''' % (self.output_synapse['receptor'] + self.output_synapse['post_comp_name'] + '_post')

        else:
            pre_eq_lines = ['%s += wght\n' % (true_receptor + str(self.output_synapse['post_comp_name']) + '_post')
                            for true_receptor in self.true_receptors]
            pre_eq = ''.join(pre_eq_lines).rstrip()
            self.output_synapse['pre_eq'] = pre_eq

    def Fixed_const_wght(self):
        """
        The method for implementing the Fixed synaptic connection.

        """

        self.output_synapse['equation'] = b2.Equations('''
            wght:siemens
            ''')

        if self.model_variation is False:
            self.output_synapse['pre_eq'] = '''
            %s+=wght
            ''' % (self.output_synapse['receptor'] + self.output_synapse['post_comp_name'] + '_post')

        else:
            pre_eq_lines = ['%s += wght\n' % (true_receptor + str(self.output_synapse['post_comp_name']) + '_post')
                            for true_receptor in self.true_receptors]
            pre_eq = ''.join(pre_eq_lines).rstrip()
            self.output_synapse['pre_eq'] = pre_eq

    def Fixed_calcium(self):
        """
        The method for implementing the Fixed synaptic connection.

        """

        self.output_synapse['equation'] = b2.Equations('''
            wght:siemens
            ''')

        if self.model_variation is False:
            self.output_synapse['pre_eq'] = '''
            %s+=wght
            ''' % (self.output_synapse['receptor'] + self.output_synapse['post_comp_name'] + '_post')

        else:
            pre_eq_lines = ['%s += wght\n' % (true_receptor + str(self.output_synapse['post_comp_name']) + '_post')
                            for true_receptor in self.true_receptors]
            pre_eq = ''.join(pre_eq_lines).rstrip()
            self.output_synapse['pre_eq'] = pre_eq

    def Depressing(self):
        """
        Depressing non-stochastic Tsodyks-Markram synapse

        """

        self.output_synapse['equation'] = b2.Equations('''
        dR/dt = (1-R)/tau_d : 1 (event-driven)
        wght : siemens
        ''')

        if self.model_variation is False:
            self.output_synapse['pre_eq'] = '''
            %s += R * U * wght
            R = R - U * R
            ''' % (self.output_synapse['receptor'] + self.output_synapse['post_comp_name'] + '_post')
            # Old version, fixed in 5/2019 for Brian 2.1.3->
            # self.output_synapse['pre_eq'] = '''
            # R = R + (1-R)*(1 - exp(-(t-lastupdate)/tau_d))
            # %s += R * U * wght
            # R = R - U * R
            # ''' % (self.output_synapse['receptor'] + self.output_synapse['post_comp_name'] + '_post')
        else:
            # pre_eq_lines = ['R = R + (1-R)*(1 - exp(-(t-lastupdate)/tau_d))\n']
            pre_eq_lines = []
            for true_receptor in self.true_receptors:
                new_line = '%s += R * U * wght\n' % (true_receptor + str(self.output_synapse['post_comp_name']) + '_post')
                pre_eq_lines.append(new_line)
            pre_eq_lines.append('R = R - U * R')
            pre_eq = ''.join(pre_eq_lines).rstrip()
            self.output_synapse['pre_eq'] = pre_eq

    def Facilitating(self):
        """
        Facilitating non-stochastic Tsodyks-Markram synapse

        """

        self.output_synapse['equation'] = b2.Equations('''
        dR/dt = (1-R)/tau_fd : 1 (event-driven)
        du/dt = (U_f-u)/tau_f : 1 (event-driven) 
        wght : siemens
        ''')

        if self.model_variation is False:

            self.output_synapse['pre_eq'] = '''
            %s += R * u * wght
            R = R - u * R
            u = u + U_f * (1-u)
            ''' % (self.output_synapse['receptor'] + self.output_synapse['post_comp_name'] + '_post')
            # Old version, fixed in 5/2019 for Brian 2.1.3->
            # self.output_synapse['pre_eq'] = '''
            # R = R + (1-R)*(1 - exp(-(t-lastupdate)/tau_fd))
            # u = u + (U_f-u)*(1 - exp(-(t-lastupdate)/tau_f))
            # %s += R * u * wght
            # R = R - u * R
            # u = u + U_f * (1-u)
            # ''' % (self.output_synapse['receptor'] + self.output_synapse['post_comp_name'] + '_post')
        else:
            # pre_eq_lines = ['''
            # R = R + (1-R)*(1 - exp(-(t-lastupdate)/tau_fd))
            # u = u + (U_f-u)*(1 - exp(-(t-lastupdate)/tau_f))
            # ''']
            pre_eq_lines = []
            for true_receptor in self.true_receptors:
                new_line = '%s += R * u * wght\n' % (true_receptor + str(self.output_synapse['post_comp_name']) + '_post')
                pre_eq_lines.append(new_line)
            pre_eq_lines.append('''
            R = R - u * R
            u = u + U_f * (1-u)
            ''')
            pre_eq = ''.join(pre_eq_lines).strip()
            self.output_synapse['pre_eq'] = pre_eq

    def value_extractor(self, df, key_name):
        non_dict_indices = df['Variable'].dropna()[df['Key'].isnull()].index.tolist()
        for non_dict_idx in non_dict_indices:
            exec("%s=%s" % (df['Variable'][non_dict_idx], df['Value'][non_dict_idx]))
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
                    cropped_df = df.loc[variable_start_idx:variable_end_idx - 1]
                except IndexError:
                    cropped_df = df.loc[variable_start_idx:]
                return eval(next(iter(cropped_df['Value'][cropped_df['Key'] == key_name[1]])))
            else:
                try:
                    return eval(next(iter(df['Value'][df['Key'] == key_name])))
                except NameError:
                    df_reset_index = df.reset_index(drop=True)
                    df_reset_index = df_reset_index[0:df_reset_index[df_reset_index['Key'] == key_name].index[0]]
                    for neural_parameter in df_reset_index['Key'].dropna():
                        if neural_parameter in df['Value'][df['Key'] == key_name].item():
                            exec("%s =self.value_extractor(df,neural_parameter)" % neural_parameter)
                    return eval(next(iter(df['Value'][df['Key'] == key_name])))
                # else:
                #     raise (
                #                 'The syntax %s is not a valid syntax for physiological configuration file or the elements that
                #                 comprise this syntax are not defined.' % next(
                #             iter(df['Value'][df['Key'] == key_name])))

        except NameError:
            new_key = next(iter(df['Value'][df['Key'] == key_name])).replace("']", "").split("['")
            return self.value_extractor(df, new_key)

    @staticmethod
    def import_fix():
        return [nan]
