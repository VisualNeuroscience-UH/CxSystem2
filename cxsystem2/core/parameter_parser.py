# Third-party
import numpy as np
import pandas as pd
from brian2.units import *  # noqa: F403

from cxsystem2.core.tools import value_extractor

__author__ = "Andalibi, V., Hokkanen H., Vanni, S."

"""
The preliminary version of this software has been developed at Aalto University 2012-2015, 
and the full version at the University of Helsinki 2013-2017. The software is distributed 
under the terms of the GNU General Public License. 
Copyright 2017 Vafa Andalibi, Henri Hokkanen and Simo Vanni.
"""

nan = np.nan
array = np.array


class NeuronParser:
    """This class embeds all parameter sets associated to all neuron types and will return it as a namespace in form of dictionary"""

    def __init__(self, output_neuron, physio_config_df):
        self.physio_config_df = physio_config_df
        NeuronParser.type_ref = np.array(
            ["PC", "SS", "BC", "MC", "L1i", "VPM", "HH_E", "HH_I", "NDNEURON", "CI"]
        )
        assert output_neuron["type"] in NeuronParser.type_ref, (
            " -  Cell type '%s' is not defined." % output_neuron["type"]
        )

        # Handling of "neuron subtype" parameters; new since Aug 2018
        if output_neuron["subtype"] == "--":
            neuron_type_to_find = output_neuron["type"]
        else:
            neuron_type_to_find = output_neuron["subtype"]
            # ...but fall back to neuron_type if subtype parameters are not defined
            try:
                variable_start_idx = self.physio_config_df["Variable"][
                    self.physio_config_df["Variable"] == neuron_type_to_find
                ].index[0]
            except IndexError:
                print(
                    " !  No parameters for %s found, using %s parameters instead"
                    % (output_neuron["subtype"], output_neuron["type"])
                )
                neuron_type_to_find = output_neuron["type"]

        self.output_namespace = {}
        variable_start_idx = self.physio_config_df["Variable"][
            self.physio_config_df["Variable"] == neuron_type_to_find
        ].index[0]
        try:
            variable_end_idx = (
                self.physio_config_df["Variable"]
                .dropna()
                .index.tolist()[
                    self.physio_config_df["Variable"]
                    .dropna()
                    .index.tolist()
                    .index(variable_start_idx)
                    + 1
                ]
            )
            cropped_df = self.physio_config_df.loc[
                variable_start_idx : variable_end_idx - 1
            ]
        except IndexError:
            cropped_df = self.physio_config_df.loc[variable_start_idx:]

        # "Root variables" extracted so that neuron parameters can refer to variables globals in physio config
        # Assumes that root variables have NaN in "Key" column
        root_variables = self.physio_config_df[
            self.physio_config_df["Key"].isnull()
        ].dropna(subset=["Variable"])
        cropped_with_root = pd.concat([root_variables, cropped_df])

        for neural_parameter in cropped_df["Key"].dropna():
            try:
                self.output_namespace[neural_parameter] = value_extractor(
                    cropped_with_root, neural_parameter
                )
            except (
                IndexError
            ):  # otherwise neuron parameters cannot be of the form reversal_potentials['E_nmda']

                self.output_namespace[neural_parameter] = value_extractor(
                    physio_config_df, neural_parameter
                )

        getattr(self, "_" + output_neuron["type"])(output_neuron)

    def _NDNEURON(self, output_neuron):
        pass

    def _CI(self, output_neuron):
        pass

    def _PC(self, output_neuron):
        """
        :param parameters_type: The type of parameters associated to compartmental neurons. 'Generic' is the common type.
                        Other types could be defined when discovered in literature.
        :type parameters_type: String
        :return:
        :rtype:
        """

        if "spine_factor" not in self.output_namespace:
            self.output_namespace["spine_factor"] = 2
            print(" ! Parameter spine_factor missing, using 2")

        # TODO - In this legacy version, only capacitance is corrected with spine_factor
        fract_areas = self.output_namespace["fract_areas"][
            output_neuron["dend_comp_num"]
        ]
        self.output_namespace["C"] = (
            fract_areas
            * self.output_namespace["Cm"]
            * self.output_namespace["Area_tot_pyram"]
            * self.output_namespace["spine_factor"]
        )
        self.output_namespace["gL"] = (
            fract_areas
            * self.output_namespace["gL"]
            * self.output_namespace["Area_tot_pyram"]
        )
        self.output_namespace["taum_soma"] = (
            self.output_namespace["C"][1] / self.output_namespace["gL"][1]
        )

    def _BC(self, output_neuron):
        pass

    def _L1i(self, output_neuron):
        pass

    def _VPM(self, output_neuron):
        pass

    def _MC(self, output_neuron):
        pass

    def _SS(self, output_neuron):
        pass

    def _HH_E(self, output_neuron):
        pass

    def _HH_I(self, output_neuron):
        pass


class SynapseParser:
    """
    This class contains all the variables that are required for the Synapses() object namespaces.
    There are several reference dictionaries in this class for:

    * cw: connection weights for any connection between NeuronGroup()s.
    * STDP: values for A_pre, A_post, tau_pre and tau_post for any connection between NeuronGroup()s.

    There are also some important internal variables:

    * Cp: Synaptic potentiation coefficient according to van Rossum J Neurosci 2000
    * Cd: Synaptic depression coefficient according to van Rossum J Neurosci 2000
    * stdp_Nsweeps: 60 in papers one does multiple trials to reach +-50% change in synapse strength. A-coefficient will be divided by this number
    * stdp_max_strength_coefficient: This value is to avoid runaway plasticity.
    * conn_prob_gain: This is used for compensation of small number of neurons and thus incoming synapses

    """

    # For _change_calcium()
    _excitatory_groups = ["PC", "SS", "CI"]
    _steep_post_inhibitory_groups = ["MC"]
    _shallow_post_inhibitory_groups = ["BC"]
    _steep_post = _excitatory_groups + _steep_post_inhibitory_groups
    _shallow_post = _shallow_post_inhibitory_groups

    def __init__(self, output_synapse, physio_config_df):
        """
        The initialization method for namespaces() object.

        :param output_synapse: This is the dictionary created in NeuronReference() in brian2_obj_namespaces module. This contains all the
                               information about the synaptic connection. In this class, Synaptic namespace parameters are directly added to
                               it. Following values are set after initialization:
                               Cp, Cd, spatial_decay. Other variables are then set based on the type of the synaptic connection.

        """
        self.output_synapse = output_synapse
        self.physio_config_df = physio_config_df

        SynapseParser.type_ref = np.array(
            [
                "STDP",
                "CPlastic",
                "Fixed_rand_wght",
                "Fixed_const_wght",
                "Fixed_multiply",
                "Depressing",
                "Facilitating",
            ]
        )
        assert output_synapse["type"] in SynapseParser.type_ref, (
            " -  Synapse type '%s' is not defined." % output_synapse["type"]
        )
        self.output_namespace = {}

        try:
            self.calcium_concentration = value_extractor(
                self.physio_config_df, "calcium_concentration"
            )
        except:  # noqa: E722
            self.calcium_concentration = 2.0  # default value that doesn't scale weights
        self._set_calcium_dependency()

        # Set (initial) weights for chosen synapse type
        getattr(SynapseParser, output_synapse["type"])(self)

    def _set_calcium_dependency(self):
        """
        Sets the dissociation constant for calcium-dependent modulation of synaptic weight
        # NB! It's not only E->E and E->I connections that get scaled. Goes both ways. See Markram suppl p16.
        """

        excitatory_groups = ["PC", "SS", "CI", "VPM"]
        steep_inhibitory_groups = ["MC"]
        shallow_inhibitory_groups = ["BC"]
        steep_post = excitatory_groups + steep_inhibitory_groups
        shallow_post = shallow_inhibitory_groups

        if (
            self.output_synapse["pre_group_type"] in excitatory_groups
            and self.output_synapse["post_group_type"] in steep_post
        ):
            self._K12 = 2.79
        elif (
            self.output_synapse["pre_group_type"] in steep_inhibitory_groups
            and self.output_synapse["post_group_type"] in excitatory_groups
        ):
            self._K12 = 2.79
        elif (
            self.output_synapse["pre_group_type"] in excitatory_groups
            and self.output_synapse["post_group_type"] in shallow_post
        ):
            self._K12 = 1.09
        elif (
            self.output_synapse["pre_group_type"] in shallow_inhibitory_groups
            and self.output_synapse["post_group_type"] in excitatory_groups
        ):
            self._K12 = 1.09
        else:
            self._K12 = np.average([2.79, 1.09])

    def scale_by_calcium(self, ca, cw=None):
        """
        Scales synaptic weight depending on calcium level

        :param ca: float, calcium concentration in mM
        :param cw: float, connection weight with calcium level 2.0mM (optional)
        :return: float, scaled synaptic weight
        """

        # if cw is None:
        #     original_synapse_strength = self.cw_baseline_calcium # this is already commented on definition, so this will be commented too
        # else:
        original_synapse_strength = cw

        ca0 = 2.0  # The Ca concentration in which cw_baseline_calcium is given

        calcium_factor = (pow(ca, 4) / (pow(self._K12, 4) + pow(ca, 4))) / (
            pow(ca0, 4) / (pow(self._K12, 4) + pow(ca0, 4))
        )
        final_synapse_strength = original_synapse_strength * calcium_factor

        return final_synapse_strength

    def _set_utilization_factor(self, is_facilitating=False, ca=2.0):
        excitatory_groups = ["PC", "SS", "CI", "in"]
        inhibitory_groups = ["BC", "MC", "L1i"]

        if is_facilitating is False:
            u_e = value_extractor(self.physio_config_df, "U_E")
            u_i = value_extractor(self.physio_config_df, "U_I")

            if self.output_synapse["pre_group_type"] in excitatory_groups:
                self.output_namespace["U"] = self.scale_by_calcium(ca, u_e)
            elif self.output_synapse["pre_group_type"] in inhibitory_groups:
                self.output_namespace["U"] = self.scale_by_calcium(ca, u_i)
            else:
                print(
                    "Warning! Unrecognized group type %s will have "
                    "outbound synapses with averaged utilization factor"
                    % self.output_synapse["pre_group_type"]
                )
                u = np.average([u_e, u_i])
                self.output_namespace["U"] = self.scale_by_calcium(ca, u)

        else:
            u_f = value_extractor(self.physio_config_df, "U_f")
            self.output_namespace["U_f"] = self.scale_by_calcium(ca, u_f)

    def STDP(self):
        """
        Method for assigning the spike timing dependent plasticity parameters to the customized_synapses() object.

        This contains all the information about the synaptic connection.
        Following values are set in this method: Apre, Apost, tau_pre, tau_post, wght_max, wght0.
        """
        self.output_namespace["Cp"] = value_extractor(self.physio_config_df, "Cp")
        self.output_namespace["Cd"] = value_extractor(self.physio_config_df, "Cd")
        self.output_namespace["Apre"] = value_extractor(self.physio_config_df, "Apre")
        self.output_namespace["Apost"] = value_extractor(self.physio_config_df, "Apost")
        self.output_namespace["taupre"] = value_extractor(
            self.physio_config_df, "taupre"
        )
        self.output_namespace["taupost"] = value_extractor(
            self.physio_config_df, "taupost"
        )
        self.output_namespace["wght_max"] = value_extractor(
            self.physio_config_df, "wght_max"
        )

        self.output_namespace["init_wght"] = value_extractor(
            self.physio_config_df, "init_wght"
        )

        delay = (
            value_extractor(
                self.physio_config_df,
                "delay_%s_%s"
                % (
                    self.output_synapse["pre_group_type"],
                    self.output_synapse["post_group_type"],
                ),
            )
            / ms  # noqa: F405
        )
        self.output_namespace["delay"] = f"{delay} * ms"

    def CPlastic(self):
        """
        The CPlastic method for assigning the parameters to the customized_synapses() object.

        This contains all the information about the synaptic connection. In this method, STDP parameters are directly added to this variable.
        Following values are set in this method: Apre, Apost, tau_pre, tau_post, wght_max, wght0.
        """
        self.output_namespace["A_LTD"], self.output_namespace["A_LTP"] = (
            value_extractor(
                self.physio_config_df,
                "cplastic_%s_%s"
                % (
                    self.output_synapse["pre_group_type"],
                    self.output_synapse["post_group_type"]
                    + self.output_synapse["post_comp_name"],
                ),
            )
        )

        self.output_namespace["Theta_low"] = value_extractor(
            self.physio_config_df, "Theta_low"
        )
        self.output_namespace["v_target"] = value_extractor(
            self.physio_config_df, "v_target"
        )
        self.output_namespace["ampa_max_cond"] = value_extractor(
            self.physio_config_df, "ampa_max_cond"
        )
        self.output_namespace["wght_max"] = value_extractor(
            self.physio_config_df, "w_max"
        )
        std_wght = (
            value_extractor(
                self.physio_config_df,
                "cw_%s_%s"
                % (
                    self.output_synapse["pre_group_type"],
                    self.output_synapse["post_group_type"],
                ),
            )
            / nS  # noqa: F405
        )
        self.output_namespace["init_wght"] = f"{std_wght} * nS"

        std_delay = (
            value_extractor(
                self.physio_config_df,
                "delay_%s_%s"
                % (
                    self.output_synapse["pre_group_type"],
                    self.output_synapse["post_group_type"],
                ),
            )
            / ms  # noqa: F405
        )
        self.output_namespace["delay"] = f"{std_delay} * ms"

    def Fixed_rand_wght(self):
        """
        Method for assigning the randomized fixed weight synaptic connection to the customized_synapses() object.
        """

        # Weight
        try:
            mean_wght = eval(self.output_synapse["custom_weight"]) / nS  # noqa: F405
            print(" ! Using custom weight: %f nS" % mean_wght)
        except:  # noqa: E722
            mean_wght = value_extractor(
                self.physio_config_df,
                "cw_%s_%s"
                % (
                    self.output_synapse["pre_group_type"],
                    self.output_synapse["post_group_type"],
                ),
            )
            mean_wght = mean_wght / nS  # noqa: F405
        min_wght = mean_wght / 2.0
        self.output_namespace["init_wght"] = "(%f * rand() + %f) * nS" % (
            mean_wght,
            min_wght,
        )

        # Delay
        mean_delay = (
            value_extractor(
                self.physio_config_df,
                "delay_%s_%s"
                % (
                    self.output_synapse["pre_group_type"],
                    self.output_synapse["post_group_type"],
                ),
            )
            / ms  # noqa: F405
        )
        min_delay = mean_delay / 2.0
        self.output_namespace["delay"] = "(%f * rand() + %f) * ms" % (
            mean_delay,
            min_delay,
        )

    def Fixed_const_wght(self):
        """
        Method for assigning constant weight synaptic connection to the customized_synapses() object.
        """

        # Weight
        try:
            mean_wght = eval(self.output_synapse["custom_weight"]) / nS  # noqa: F405
            print(" ! Using custom weight: %f nS" % mean_wght)
        except:  # noqa: E722
            mean_wght = (
                value_extractor(
                    self.physio_config_df,
                    "cw_%s_%s"
                    % (
                        self.output_synapse["pre_group_type"],
                        self.output_synapse["post_group_type"],
                    ),
                )
                / nS  # noqa: F405
            )
        self.output_namespace["init_wght"] = "%f * nS" % (mean_wght)

        # Delay
        mean_delay = (
            value_extractor(
                self.physio_config_df,
                "delay_%s_%s"
                % (
                    self.output_synapse["pre_group_type"],
                    self.output_synapse["post_group_type"],
                ),
            )
            / ms  # noqa: F405
        )
        self.output_namespace["delay"] = "(%f * rand() + %f) * ms" % (0, mean_delay)

    def Fixed_multiply(self):
        """
        Method using constant weight but assigning multiplier further on to synaptic weight. This enables array search for
        loaded connection strengths.
        """
        self.Fixed_const_wght()

    def Depressing(self):
        """
        Depressing synapse

        """

        # GET weight params
        try:
            mean_wght = eval(self.output_synapse["custom_weight"]) / nS  # noqa: F405
            print(" ! Using custom weight: %f nS" % mean_wght)
        except:  # noqa: E722
            mean_wght = (
                value_extractor(
                    self.physio_config_df,
                    "cw_%s_%s"
                    % (
                        self.output_synapse["pre_group_type"],
                        self.output_synapse["post_group_type"],
                    ),
                )
                / nS  # noqa: F405
            )

        min_wght = mean_wght / 2.0

        # GET time constant
        tau_d = value_extractor(self.physio_config_df, "tau_d")
        self.output_namespace["tau_d"] = tau_d

        # SET utilization factor & SCALE it wrt calcium level
        self._set_utilization_factor(ca=self.calcium_concentration)

        # SET the weight (uniform distribution [min_wght, min_wght+mean_wght])
        # NB!! You might think (min_wght, mean_wght) should be the other way around, but remember that rand gives
        # values between 0 and 1, NOT values with mean 0 like randn!
        self.output_namespace["init_wght"] = "(%f + %f * rand()) * nS" % (
            min_wght,
            mean_wght,
        )

        # SET the synaptic delay (uniform distribution [min_delay, min_delay+mean_delay])
        # NB!! Same applies here, see assignment of init_wght
        mean_delay = (
            value_extractor(
                self.physio_config_df,
                "delay_%s_%s"
                % (
                    self.output_synapse["pre_group_type"],
                    self.output_synapse["post_group_type"],
                ),
            )
            / ms  # noqa: F405
        )
        min_delay = mean_delay / 2.0
        self.output_namespace["delay"] = "(%f + %f * rand()) * ms" % (
            min_delay,
            mean_delay,
        )

    def Facilitating(self):
        """
        Facilitating synapse

        """

        try:
            mean_wght = eval(self.output_synapse["custom_weight"]) / nS  # noqa: F405
            print(" ! Using custom weight: %f nS" % mean_wght)
        except:  # noqa: E722
            mean_wght = (
                value_extractor(
                    self.physio_config_df,
                    "cw_%s_%s"
                    % (
                        self.output_synapse["pre_group_type"],
                        self.output_synapse["post_group_type"],
                    ),
                )
                / nS  # noqa: F405
            )

        min_wght = mean_wght / 2.0

        # GET time constants
        tau_fd = value_extractor(self.physio_config_df, "tau_fd")
        self.output_namespace["tau_fd"] = tau_fd
        tau_f = value_extractor(self.physio_config_df, "tau_f")
        self.output_namespace["tau_f"] = tau_f

        # SET utilization factor & SCALE it wrt calcium level
        self._set_utilization_factor(
            is_facilitating=True, ca=self.calcium_concentration
        )

        # SET the weight (uniform distribution [min_wght, min_wght+mean_wght])
        # NB!! You might think (min_wght, mean_wght) should be the other way around, but remember that rand gives
        # values between 0 and 1, NOT values with mean 0 like randn!
        self.output_namespace["init_wght"] = "(%f + %f * rand()) * nS" % (
            min_wght,
            mean_wght,
        )

        # SET the synaptic delay (uniform distribution [min_delay, min_delay+mean_delay])
        # NB!! Same applies here, see assignment of init_wght
        mean_delay = (
            value_extractor(
                self.physio_config_df,
                "delay_%s_%s"
                % (
                    self.output_synapse["pre_group_type"],
                    self.output_synapse["post_group_type"],
                ),
            )
            / ms  # noqa: F405
        )
        min_delay = mean_delay / 2.0
        self.output_namespace["delay"] = "(%f + %f * rand()) * ms" % (
            min_delay,
            mean_delay,
        )
