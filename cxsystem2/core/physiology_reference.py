# Built-in
from copy import deepcopy

# Third-party
import brian2 as b2
import numpy as np
import pandas as pd
from brian2.units import *  # noqa: F403

# Local
from cxsystem2.core import equation_templates as eqt
from cxsystem2.core.parameter_parser import NeuronParser, SynapseParser, value_extractor
from cxsystem2.core.workspace_manager import RandomManager
from cxsystem2.neurodynlib.neuron_models import neuron_factory

__author__ = "Andalibi, V., Hokkanen H., Vanni, S."
"""
The preliminary version of this software has been developed at Aalto University 2012-2015, 
and the full version at the University of Helsinki 2013-2017. The software is distributed 
under the terms of the GNU General Public License. 
Copyright 2017 Vafa Andalibi, Henri Hokkanen and Simo Vanni.
"""
arange = np.arange


class NeuronReference:
    """
    Using this class, a dictionary object is created which contains all parameters and variables that are needed to \
    create a group of that customized cell. This dictionary will eventually be used in process of building the cortical module.\
    New types of neurons should be implemented in this class.
    """

    def __init__(
        self,
        idx: int,
        number_of_neurons: int,
        area: str,
        cell_type: str,
        layers_idx: np.ndarray,
        general_grid_radius: b2.units.Quantity,
        min_distance: b2.units.Quantity,
        physio_config_df: pd.DataFrame,
        unit_coords_df: pd.DataFrame | None = None,
        network_center: complex = 0 + 0j,
        cell_subtype: str = "--",
    ) -> None:
        """
        Initialize the NeuronReference based on the arguments.

        Parameters
        ----------
        number_of_neurons : int
            Number of neurons in the NeuronGroup() object.
        cell_type : str
            Type of cell in the NeuronGroup: currently PC, SS, BC, MC and L1i.
        layers_idx : array-like
            Layer(s) in which the cell group is located. For SS, BC, MC and L1i it is
            an integer; for PC (multi-compartmental) it is a tuple array defining the
            first and last layers of the neuron, e.g. ``np.array([4, 1])`` means soma
            in layer 4 and apical dendrites (2 compartments) extending to layers 2/3
            and 1 (layer 2 indicates layer 2/3).
        network_center : complex, optional
            Center of the NeuronGroup() in visual field coordinates. Default ``0+0j``.

        Notes
        -----
        Main internal variables:

        - ``output_neuron``: main dictionary with all data about the current customized
          neuron group: number of neurons, threshold, reset, refractory, neuron type,
          soma layer, dendrites layer, total compartments, namespace, equation, and
          positions (cortical and visual coordinates).
        """

        # Set random number generator
        # manager = RandomManager()
        # self.rng = manager.rng


        ############################################################
        ###        Initialization of general neuron model        ###
        ############################################################

        self.physio_config_df = physio_config_df
        NeuronReference._celltypes = np.array(
            ["PC", "SS", "BC", "MC", "L1i", "VPM", "HH_I", "HH_E", "NDNEURON", "CI"]
        )
        assert (
            general_grid_radius > min_distance
        ), " -  The distance between cells should be less than the grid radius"
        assert cell_type in NeuronReference._celltypes, (
            f" -  Cell type '{cell_type}' is not defined"
        )
        assert len(layers_idx) < 3, " -  Length of layers_idx array is larger than 2"
        if len(layers_idx) == 2:
            assert (
                layers_idx[1] <= layers_idx[0]
            ), " -  Indices of the layer_idx array are not descending"
        elif len(layers_idx) == 1:
            assert (
                cell_type != "PC"
            ), " -  Cell type is PC but the start and end of the neuron is not defined in layers_idx"

        # Add actual voltage threshold value, in mV
        V_threshold = value_extractor(self.physio_config_df, "VT")

        # final neuron is the output neuron containing equation, parameters
        self.output_neuron = {
            "idx": int(idx),
            "number_of_neurons": int(number_of_neurons),
            "area": area,
            "threshold": "vm>Vcut",
            "V_threshold": V_threshold,
            "reset": "vm=V_res",
            "refractory": "4 * ms",
            "type": cell_type,
            "subtype": cell_subtype,
            "soma_layer": int(layers_idx[0]),
        }
        if self.output_neuron["type"] == "PC":
            # N layers above soma. Only main layers 1, 2, 3, 4, 5 and 6 count.
            self.output_neuron["dends_layer"] = np.array(
                list(range(layers_idx[0] - 1, layers_idx[1] - 1, -1))
            )
            self.output_neuron["dend_comp_num"] = len(self.output_neuron["dends_layer"])
            self.output_neuron["total_comp_num"] = (
                self.output_neuron["dend_comp_num"] + 3
            )

        else:
            self.output_neuron["dends_layer"] = self.output_neuron["soma_layer"]
            self.output_neuron["dend_comp_num"] = np.array([0])
            self.output_neuron["total_comp_num"] = np.array([1])

        self.output_neuron["namespace"] = NeuronParser(
            self.output_neuron, physio_config_df
        ).output_namespace
        self.output_neuron["equation"] = ""

        # For pyramidal groups
        if cell_type == "PC":
            try:
                self.pc_neuron_model = value_extractor(
                    self.physio_config_df, "pc_neuron_model"
                ).upper()
            except:  # noqa: E722
                self.pc_neuron_model = self.neuron_model
                print(
                    f" !  No pyramidal cell neuron model defined, "
                    f"using {self.neuron_model}"
                )

            try:
                self.pc_excitation_model = value_extractor(
                    self.physio_config_df, "pc_excitation_model"
                ).upper()
            except:  # noqa: E722
                self.pc_excitation_model = self.excitation_model
                print(
                    f" !  No pyramidal cell excitation model defined, "
                    f"using {self.excitation_model}"
                )

            try:
                self.pc_inhibition_model = value_extractor(
                    self.physio_config_df, "pc_inhibition_model"
                ).upper()
            except:  # noqa: E722
                self.pc_inhibition_model = self.inhibition_model
                print(
                    f" !  No pyramidal cell inhibition model defined, "
                    f"using {self.inhibition_model}"
                )

        # For other non-pyramidal groups
        elif cell_type == "CI":
            try:
                self.ci_neuron_model = value_extractor(
                    self.physio_config_df, "ci_neuron_model"
                ).upper()
                print(f" -  CI neuron model is {self.ci_neuron_model} ")
            except:  # noqa: E722
                self.ci_neuron_model = "EIF"
                print(" !  No CI neuron model defined, using EIF")

            try:
                self.ci_excitation_model = value_extractor(
                    self.physio_config_df, "ci_excitation_model"
                ).upper()
            except:  # noqa: E722
                self.ci_excitation_model = "SIMPLE_E"
                print(" !  No CI neuron excitation model defined, using simple")

            try:
                self.ci_inhibition_model = value_extractor(
                    self.physio_config_df, "ci_inhibition_model"
                ).upper()
            except:  # noqa: E722
                self.ci_inhibition_model = "SIMPLE_I"
                print(" !  No CI neuron inhibition model defined, using simple")

        # For other non-pyramidal groups
        else:
            try:
                self.neuron_model = value_extractor(
                    self.physio_config_df, "neuron_model"
                ).upper()
                print(f" -  Neuron model is {self.neuron_model} ")
            except:  # noqa: E722
                self.neuron_model = "EIF"
                print(" !  No point neuron model defined, using EIF")

            try:
                self.excitation_model = value_extractor(
                    self.physio_config_df, "excitation_model"
                ).upper()
            except:  # noqa: E722
                self.excitation_model = "SIMPLE_E"
                print(" !  No point neuron excitation model defined, using simple")

            try:
                self.inhibition_model = value_extractor(
                    self.physio_config_df, "inhibition_model"
                ).upper()
            except:  # noqa: E722
                self.inhibition_model = "SIMPLE_I"
                print(" !  No point neuron inhibition model defined, using simple")

        ############################################################
        ### Extracting parameters from physiological config file ###
        ############################################################
        try:
            variable_start_idx = self.physio_config_df["Variable"][
                self.physio_config_df["Variable"] == self.output_neuron["subtype"]
            ].index[0]
        except:  # noqa: E722 falling back to general cell type
            variable_start_idx = self.physio_config_df["Variable"][
                self.physio_config_df["Variable"] == self.output_neuron["type"]
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
            self.cropped_df_for_current_type = self.physio_config_df.loc[
                variable_start_idx : variable_end_idx - 1
            ]
        except IndexError:
            self.cropped_df_for_current_type = self.physio_config_df.loc[
                variable_start_idx:
            ]
        getattr(self, self.output_neuron["type"])()

        ############################################################
        ###                Creating positions                   ###
        ############################################################

        if (
            unit_coords_df is not None
            and self.output_neuron.get("idx")
            in unit_coords_df["idx"].astype("int").values
        ):
            self.output_neuron["z_positions"] = unit_coords_df.loc[
                unit_coords_df["idx"].astype("int") == self.output_neuron.get("idx"),
                "z_coords",
            ].values[0]
            self.output_neuron["w_positions"] = unit_coords_df.loc[
                unit_coords_df["idx"].astype("int") == self.output_neuron.get("idx"),
                "w_coords",
            ].values[0]
        else:
            self.output_neuron["z_center"] = network_center
            self.output_neuron["w_center"] = 12.2 * np.log(
                self.output_neuron["z_center"] + 0.94
            )
            self.output_neuron["w_positions"] = self._get_w_positions(
                self.output_neuron["number_of_neurons"],
                "fixed_grid",
                general_grid_radius,
                min_distance,
            )
            self.output_neuron["z_positions"] = [
                np.e ** (x / 17) - 1 for x in self.output_neuron["w_positions"]
            ]

        print(
            " -  Customized "
            + str(cell_type)
            + " neuron in layer "
            + str(layers_idx)
            + " initialized with "
            + str(self.output_neuron["number_of_neurons"])
            + " neurons."
        )

    def _get_w_positions(
        self,
        n: int,
        layout: str,
        general_grid_radius: b2.units.Quantity,
        min_distance: b2.units.Quantity,
    ) -> list[complex]:
        # w position = position in cortex, in millimeters
        r = general_grid_radius / mm  # noqa: F405
        possible_pos_idx = arange(-r, r, min_distance / mm)  # noqa: F405
        _positions = []
        choice = self.rng.choice
        if layout == "fixed_grid":
            _positions = [
                (choice(possible_pos_idx), choice(possible_pos_idx))
                for _, _ in zip(list(range(n)), list(range(n)))
            ]
            for idx, item in enumerate(_positions):
                while np.sqrt(_positions[idx][0] ** 2 + _positions[idx][1] ** 2) > r:
                    _positions[idx] = (
                        choice(possible_pos_idx),
                        choice(possible_pos_idx),
                    )
            _positions = [
                complex(_itm[0], _itm[1]) + self.output_neuron["w_center"]
                for _itm in _positions
            ]
        return _positions

    def NDNEURON(self) -> None:
        """
        NDNEURON type, just for testing Neurodynlib.
        """

        x = neuron_factory().get_class(self.neuron_model)
        x.set_excitatory_receptors(self.excitation_model)
        x.set_inhibitory_receptors(self.inhibition_model)

        if "noise_sigma" in self.output_neuron["namespace"]:
            noise_sigma = self.output_neuron["namespace"]["noise_sigma"]
            x.add_vm_noise(noise_sigma)

        if "tonic_current" in self.output_neuron["namespace"]:
            tonic_current = self.output_neuron["namespace"]["tonic_current"]
            tau_tonic_rampup = self.output_neuron["namespace"]["tau_tonic_rampup"]
            x.add_tonic_current(tonic_current, tau_tonic_rampup)

        self.output_neuron["equation"] = x.get_compartment_equations("soma")
        self.output_neuron["threshold"] = x.get_threshold_condition()
        self.output_neuron["reset"] = x.get_reset_statements()
        self.output_neuron["refractory"] = x.get_refractory_period()

        self.output_neuron["equation"] += b2.Equations("""x : meter
            y : meter""")

    def PC(self) -> None:
        """
        Build the equation for PC neurons based on the number of compartments.

        The final equation is saved in ``output_neuron['equation']``.

        Notes
        -----
        Main internal variables:

        - ``eq_template_soma``: template somatic equation, whose variables are replaced
          later using brian2 ``Equations``::

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

        - ``eq_template_dend``: template dendritic equation::

            dvm/dt = (gL*(EL-vm) + gealpha * (Ee-vm) + gealphaX * (Ee-vm) + gialpha * (Ei-vm)
                     + I_dendr) / C : volt (unless refractory)
            dge/dt = -ge/tau_e : siemens
            dgealpha/dt = (ge-gealpha)/tau_e : siemens
            dgeX/dt = -geX/tau_eX : siemens
            dgealphaX/dt = (geX-gealphaX)/tau_eX : siemens
            dgi/dt = -gi/tau_i : siemens
            dgialpha/dt = (gi-gialpha)/tau_i : siemens
        """

        eq_template_soma = eqt.PCEquationHelper(
            neuron_model=self.pc_neuron_model,
            is_pyramidal=True,
            compartment="soma",
            exc_model=self.pc_excitation_model,
            inh_model=self.pc_inhibition_model,
        ).get_membrane_equation(return_string=True)
        eq_template_dend = eqt.PCEquationHelper(
            neuron_model=self.pc_neuron_model,
            is_pyramidal=True,
            compartment="dend",
            exc_model=self.pc_excitation_model,
            inh_model=self.pc_inhibition_model,
        ).get_membrane_equation(return_string=True)

        dendritic_extent = self.output_neuron["dend_comp_num"]

        self.output_neuron["equation"] = b2.Equations(
            eq_template_dend,
            vm="vm_basal",
            ge="ge_basal",
            gealpha="gealpha_basal",
            C=self.output_neuron["namespace"]["C"][0],
            gL=self.output_neuron["namespace"]["gL"][0],
            gi="gi_basal",
            geX="geX_basal",
            gialpha="gialpha_basal",
            gealphaX="gealphaX_basal",
            I_dendr="Idendr_basal",
            gealpha1="gealpha1_basal",
            gialpha1="gialpha1_basal",
            g_ampa="g_ampa_basal",
            g_ampa_alpha="g_ampa_alpha_basal",
            g_ampa_alpha1="g_ampa_alpha1_basal",
            g_nmda="g_nmda_basal",
            g_nmda_alpha="g_nmda_alpha_basal",
            g_nmda_alpha1="g_nmda_alpha1_basal",
            g_gabaa="g_gabaa_basal",
            g_gabaa_alpha="g_gabaa_alpha_basal",
            g_gabaa_alpha1="g_gabaa_alpha1_basal",
            g_gabab="g_gabab_basal",
            g_gabab_alpha="g_gabab_alpha_basal",
            g_gabab_alpha1="g_gabab_alpha1_basal",
            B="B_basal",
        )

        self.output_neuron["equation"] += b2.Equations(
            eq_template_soma,
            gL=self.output_neuron["namespace"]["gL"][1],
            ge="ge_soma",
            geX="geX_soma",
            gi="gi_soma",
            gealpha="gealpha_soma",
            gealphaX="gealphaX_soma",
            gialpha="gialpha_soma",
            C=self.output_neuron["namespace"]["C"][1],
            I_dendr="Idendr_soma",
            taum_soma=self.output_neuron["namespace"]["taum_soma"],
            gealpha1="gealpha1_soma",
            gialpha1="gialpha1_soma",
            g_ampa="g_ampa_soma",
            g_ampa_alpha="g_ampa_alpha_soma",
            g_ampa_alpha1="g_ampa_alpha1_soma",
            g_nmda="g_nmda_soma",
            g_nmda_alpha="g_nmda_alpha_soma",
            g_nmda_alpha1="g_nmda_alpha1_soma",
            g_gabaa="g_gabaa_soma",
            g_gabaa_alpha="g_gabaa_alpha_soma",
            g_gabaa_alpha1="g_gabaa_alpha1_soma",
            g_gabab="g_gabab_soma",
            g_gabab_alpha="g_gabab_alpha_soma",
            g_gabab_alpha1="g_gabab_alpha1_soma",
            B="B_soma",
        )

        for _ii in range(
            self.output_neuron["dend_comp_num"] + 1
        ):  # extra dendritic compartment in the same level of soma
            self.output_neuron["equation"] += b2.Equations(
                eq_template_dend,
                vm=f"vm_a{_ii}",
                C=self.output_neuron["namespace"]["C"][_ii],
                gL=self.output_neuron["namespace"]["gL"][_ii],
                ge=f"ge_a{_ii}",
                gi=f"gi_a{_ii}",
                geX=f"geX_a{_ii}",
                gealpha=f"gealpha_a{_ii}",
                gialpha=f"gialpha_a{_ii}",
                gealphaX=f"gealphaX_a{_ii}",
                I_dendr=f"Idendr_a{_ii}",
                gealpha1=f"gealpha1_a{_ii}",
                gialpha1=f"gialpha1_a{_ii}",
                g_ampa=f"g_ampa_a{_ii}",
                g_ampa_alpha=f"g_ampa_alpha_a{_ii}",
                g_ampa_alpha1=f"g_ampa_alpha1_a{_ii}",
                g_nmda=f"g_nmda_a{_ii}",
                g_nmda_alpha=f"g_nmda_alpha_a{_ii}",
                g_nmda_alpha1=f"g_nmda_alpha1_a{_ii}",
                g_gabaa=f"g_gabaa_a{_ii}",
                g_gabaa_alpha=f"g_gabaa_alpha_a{_ii}",
                g_gabaa_alpha1=f"g_gabaa_alpha1_a{_ii}",
                g_gabab=f"g_gabab_a{_ii}",
                g_gabab_alpha=f"g_gabab_alpha_a{_ii}",
                g_gabab_alpha1=f"g_gabab_alpha1_a{_ii}",
                B=f"B_a{_ii}",
            )

        # Defining decay between soma and basal dendrite & apical dendrites
        self.output_neuron["equation"] += b2.Equations(
            "I_dendr = gapre*(vmpre-vmself)  : amp",
            gapre=1 / (self.output_neuron["namespace"]["Ra"][0]),
            I_dendr="Idendr_basal",
            vmself="vm_basal",
            vmpre="vm",
        )
        self.output_neuron["equation"] += b2.Equations(
            "I_dendr = gapre*(vmpre-vmself)  + gapost*(vmpost-vmself) : amp",
            gapre=1 / (self.output_neuron["namespace"]["Ra"][1]),
            gapost=1 / (self.output_neuron["namespace"]["Ra"][0]),
            I_dendr="Idendr_soma",
            vmself="vm",
            vmpre="vm_a0",
            vmpost="vm_basal",
        )

        # If there's more than one apical dendrite compartment
        if dendritic_extent > 0:

            self.output_neuron["equation"] += b2.Equations(
                "I_dendr = gapre*(vmpre-vmself) + gapost*(vmpost-vmself) : amp",
                gapre=1 / (self.output_neuron["namespace"]["Ra"][2]),
                gapost=1 / (self.output_neuron["namespace"]["Ra"][1]),
                I_dendr="Idendr_a0",
                vmself="vm_a0",
                vmpre="vm_a1",
                vmpost="vm",
            )

            # Defining decay between apical dendrite compartments
            Ra_idx_add = 2  # Ra idx 0 is btw basal and soma, Ra idx 1 is btw soma and a0, so we start from Ra idx 2
            for _ii in arange(1, self.output_neuron["dend_comp_num"]):
                self.output_neuron["equation"] += b2.Equations(
                    "I_dendr = gapre*(vmpre-vmself) + gapost*(vmpost-vmself) : amp",
                    gapre=1 / (self.output_neuron["namespace"]["Ra"][_ii + Ra_idx_add]),
                    gapost=1
                    / (self.output_neuron["namespace"]["Ra"][_ii - 1 + Ra_idx_add]),
                    I_dendr=f"Idendr_a{_ii}",
                    vmself=f"vm_a{_ii}",
                    vmpre=f"vm_a{_ii + 1}",
                    vmpost=f"vm_a{_ii - 1}",
                )

            # Last compartment
            self.output_neuron["equation"] += b2.Equations(
                "I_dendr = gapost*(vmpost-vmself) : amp",
                I_dendr=f"Idendr_a{self.output_neuron['dend_comp_num']}",
                gapost=1
                / (
                    self.output_neuron["namespace"]["Ra"][
                        dendritic_extent - 1 + Ra_idx_add
                    ]
                ),
                vmself=f"vm_a{self.output_neuron['dend_comp_num']}",
                vmpost=f"vm_a{self.output_neuron['dend_comp_num'] - 1}",
            )

        # If dendritic_extent is zero ie. there's only one apical dendrite compartment
        else:
            self.output_neuron["equation"] += b2.Equations(
                "I_dendr = gapre*(vmpre-vmself)  : amp",
                gapre=1 / (self.output_neuron["namespace"]["Ra"][1]),
                I_dendr="Idendr_a0",
                vmself="vm_a0",
                vmpre="vm",
            )

        self.output_neuron["equation"] += b2.Equations("""x : meter
                            y : meter""")

    def BC(self) -> None:
        """
        Build the equation for BC neurons. The final equation is saved in
        ``output_neuron['equation']``.

        Notes
        -----
        The equation of the neuron is as follows::

            dvm/dt = (gL*(EL-vm) + gL * DeltaT * exp((vm-VT) / DeltaT) + ge_soma * (Ee-vm) + gi_soma * (Ei-vm)) / C : volt (unless refractory)
            dge_soma/dt = -ge_soma/tau_e : siemens
            dgi_soma/dt = -gi_soma/tau_i : siemens
            x : meter
            y : meter
        """

        x = neuron_factory().get_class(self.neuron_model)
        x.set_excitatory_receptors(self.excitation_model)
        x.set_inhibitory_receptors(self.inhibition_model)

        if "noise_sigma" in self.output_neuron["namespace"]:
            noise_sigma = self.output_neuron["namespace"]["noise_sigma"]
            x.add_vm_noise(noise_sigma)

        if "tonic_current" in self.output_neuron["namespace"]:
            tonic_current = self.output_neuron["namespace"]["tonic_current"]
            tau_tonic_rampup = self.output_neuron["namespace"]["tau_tonic_rampup"]
            x.add_tonic_current(tonic_current, tau_tonic_rampup)

        if "refractory_period" in self.output_neuron["namespace"]:
            refractory_period = self.output_neuron["namespace"]["refractory_period"]
            x.set_neuron_parameters(refractory_period=refractory_period)

        self.output_neuron["equation"] = x.get_compartment_equations("soma")
        self.output_neuron["threshold"] = x.get_threshold_condition()
        self.output_neuron["reset"] = x.get_reset_statements()
        self.output_neuron["refractory"] = x.get_refractory_period()

        self.output_neuron["equation"] += b2.Equations("""x : meter
            y : meter""")

    def L1i(self) -> None:
        """
        Build the equation for Layer 1 inhibitory (L1i) neurons. The final equation is
        saved in ``output_neuron['equation']``.

        Notes
        -----
        The equation of the neuron is as follows::

            dvm/dt = (gL*(EL-vm) + gL * DeltaT * exp((vm-VT) / DeltaT) + ge_soma * (Ee-vm) + gi_soma * (Ei-vm)) / C : volt (unless refractory)
            dge_soma/dt = -ge_soma/tau_e : siemens
            dgi_soma/dt = -gi_soma/tau_i : siemens
            x : meter
            y : meter
        """

        x = neuron_factory().get_class(self.neuron_model)
        x.set_excitatory_receptors(self.excitation_model)
        x.set_inhibitory_receptors(self.inhibition_model)

        if "noise_sigma" in self.output_neuron["namespace"]:
            noise_sigma = self.output_neuron["namespace"]["noise_sigma"]
            x.add_vm_noise(noise_sigma)

        if "tonic_current" in self.output_neuron["namespace"]:
            tonic_current = self.output_neuron["namespace"]["tonic_current"]
            tau_tonic_rampup = self.output_neuron["namespace"]["tau_tonic_rampup"]
            x.add_tonic_current(tonic_current, tau_tonic_rampup)

        if "refractory_period" in self.output_neuron["namespace"]:
            refractory_period = self.output_neuron["namespace"]["refractory_period"]
            x.set_neuron_parameters(refractory_period=refractory_period)

        self.output_neuron["equation"] = x.get_compartment_equations("soma")
        self.output_neuron["threshold"] = x.get_threshold_condition()
        self.output_neuron["reset"] = x.get_reset_statements()
        self.output_neuron["refractory"] = x.get_refractory_period()

        self.output_neuron["equation"] += b2.Equations("""x : meter
            y : meter""")

    def MC(self) -> None:
        """
        Build the equation for MC neurons. The final equation is saved in
        ``output_neuron['equation']``.

        Notes
        -----
        The equation of the neuron is as follows::

            dvm/dt = (gL*(EL-vm) + gL * DeltaT * exp((vm-VT) / DeltaT)
                    + ge_soma * (Ee-vm) + gi_soma * (Ei-vm)) / C : volt (unless refractory)
            dge_soma/dt = -ge_soma/tau_e : siemens
            dgi_soma/dt = -gi_soma/tau_i : siemens
            x : meter
            y : meter
        """

        x = neuron_factory().get_class(self.neuron_model)
        x.set_excitatory_receptors(self.excitation_model)
        x.set_inhibitory_receptors(self.inhibition_model)

        if "noise_sigma" in self.output_neuron["namespace"]:
            noise_sigma = self.output_neuron["namespace"]["noise_sigma"]
            x.add_vm_noise(noise_sigma)

        if "tonic_current" in self.output_neuron["namespace"]:
            tonic_current = self.output_neuron["namespace"]["tonic_current"]
            tau_tonic_rampup = self.output_neuron["namespace"]["tau_tonic_rampup"]
            x.add_tonic_current(tonic_current, tau_tonic_rampup)

        if "refractory_period" in self.output_neuron["namespace"]:
            refractory_period = self.output_neuron["namespace"]["refractory_period"]
            x.set_neuron_parameters(refractory_period=refractory_period)

        self.output_neuron["equation"] = x.get_compartment_equations("soma")
        self.output_neuron["threshold"] = x.get_threshold_condition()
        self.output_neuron["reset"] = x.get_reset_statements()
        self.output_neuron["refractory"] = x.get_refractory_period()

        self.output_neuron["equation"] += b2.Equations("""x : meter
            y : meter""")

    def SS(self) -> None:
        """
        Build the equation for SS neurons. The final equation is saved in
        ``output_neuron['equation']``.

        Notes
        -----
        The equation of the neuron is as follows::

            dvm/dt = (gL*(EL-vm) + gL * DeltaT * exp((vm-VT) / DeltaT) + ge_soma * (Ee-vm) + gi_soma * (Ei-vm)) / C : volt (unless refractory)
            dge_soma/dt = -ge_soma/tau_e : siemens
            dgi_soma/dt = -gi_soma/tau_i : siemens
            x : meter
            y : meter
        """

        x = neuron_factory().get_class(self.neuron_model)
        x.set_excitatory_receptors(self.excitation_model)
        x.set_inhibitory_receptors(self.inhibition_model)

        if "noise_sigma" in self.output_neuron["namespace"]:
            noise_sigma = self.output_neuron["namespace"]["noise_sigma"]
            x.add_vm_noise(noise_sigma)

        if "tonic_current" in self.output_neuron["namespace"]:
            tonic_current = self.output_neuron["namespace"]["tonic_current"]
            tau_tonic_rampup = self.output_neuron["namespace"]["tau_tonic_rampup"]
            x.add_tonic_current(tonic_current, tau_tonic_rampup)

        if "refractory_period" in self.output_neuron["namespace"]:
            refractory_period = self.output_neuron["namespace"]["refractory_period"]
            x.set_neuron_parameters(refractory_period=refractory_period)

        self.output_neuron["equation"] = x.get_compartment_equations("soma")
        self.output_neuron["threshold"] = x.get_threshold_condition()
        self.output_neuron["reset"] = x.get_reset_statements()
        self.output_neuron["refractory"] = x.get_refractory_period()

        self.output_neuron["equation"] += b2.Equations("""x : meter
            y : meter""")

    def CI(self) -> None:
        """
        Build the equation for CI neurons.

        CI stands for current injection as a timed array directly to the neuron model.
        The final equation is saved in ``output_neuron['equation']``.

        Notes
        -----
        The equation of the neuron is as follows::

            dvm/dt = (gL*(EL-vm)  + ge_soma * 1 * vm + gi_soma * 1 * vm + I_ext(t,i) / C : volt (unless refractory)
            dge_soma/dt = -ge_soma/tau_e : siemens
            dgi_soma/dt = -gi_soma/tau_i : siemens
            x : meter
            y : meter
            I_ext : amp
        """

        x = neuron_factory().get_class(self.ci_neuron_model)
        x.set_excitatory_receptors(self.ci_excitation_model)
        x.set_inhibitory_receptors(self.ci_inhibition_model)

        if "noise_sigma" in self.output_neuron["namespace"]:
            noise_sigma = self.output_neuron["namespace"]["noise_sigma"]
            x.add_vm_noise(noise_sigma)

        if "tonic_current" in self.output_neuron["namespace"]:
            tonic_current = self.output_neuron["namespace"]["tonic_current"]
            tau_tonic_rampup = self.output_neuron["namespace"]["tau_tonic_rampup"]
            x.add_tonic_current(tonic_current, tau_tonic_rampup)

        if "refractory_period" in self.output_neuron["namespace"]:
            refractory_period = self.output_neuron["namespace"]["refractory_period"]
            x.set_neuron_parameters(refractory_period=refractory_period)

        if "vclamp" in self.output_neuron["namespace"]:
            x.add_external_current(
                current_name="gclamp * (vclamp - vm) ",
                current_eqs="""
                                    gclamp : siemens
                                                """,
            )
            init_val = {"gclamp": self.output_neuron["namespace"]["gL"] * 500}
            x.initial_values.update(init_val)
            self.output_neuron["initial_values"] = x.initial_values

        # This part is not nicely integrated to the rest of the code, and not even trying to be.
        # It reads current injection from external file. Filepath and filenames are set in the
        # physiology.csv as neuron subtype-specific parameters cibasepath and cifilename. The
        # cimultiplier is used to multiply the current injection in an array run.
        if "cibasepath" in self.output_neuron["namespace"]:
            # Built-in
            import os

            # Third-party
            import scipy.io as sio

            cibasepath = self.output_neuron["namespace"]["cibasepath"]
            cifilename = self.output_neuron["namespace"]["cifilename"]
            cimultiplier = self.output_neuron["namespace"]["cimultiplier"]
            cidata_dict = {}
            cidata_fullpath_filename = os.path.join(cibasepath, cifilename)
            sio.loadmat(cidata_fullpath_filename, cidata_dict)

            cidata = cidata_dict["injected_current"]
            framedurations = cidata_dict["dt"]
            # NOTE scaling to picoamperes here
            I_ext = b2.TimedArray(
                cimultiplier * cidata * b2.pA, dt=framedurations * b2.ms
            )

            # Add I_ext to namespace
            self.output_neuron["namespace"]["I_ext"] = I_ext

            # Add external current to equations here
            x.add_external_current(current_name="I_ext(t,i)", current_eqs="timedarray")

        # In case some model type specific necessary values are missing from physiology csv file,
        # get the default values from neurodynlib neuron_models.py
        new_namespace_dict = deepcopy(
            x.default_neuron_parameters
        )  # keep original unchanged
        new_namespace_dict.update(self.output_neuron["namespace"])
        self.output_neuron["namespace"] = new_namespace_dict

        self.output_neuron["equation"] = x.get_compartment_equations("soma")
        self.output_neuron["threshold"] = x.get_threshold_condition()
        self.output_neuron["reset"] = x.get_reset_statements()
        self.output_neuron["refractory"] = x.get_refractory_period()

        self.output_neuron["equation"] += b2.Equations("""x : meter
            y : meter""")

    def VPM(self) -> None:
        """
        This method build up the equation for VPM neurons. No equation is needed.
        """
        self.output_neuron["equation"] = ""


class SynapseReference:
    """
        In this class, a dictionary object is created which contains all parameters and variables that are needed to \
        create a Synapses() object between two neuron group. This dictionary will eventually be used in process of \
        building the cortical module. New types of synapses should be implemented in this class.
    """

    def __init__(
        self,
        receptor: str,
        pre_group_idx: int,
        post_group_idx: int,
        syn_type: str,
        pre_type: str,
        post_type: str,
        physio_config_df: pd.DataFrame,
        post_comp_name: str = "_soma",
        custom_weight: str = "--",
        multiply_weight: float = 1,
    ) -> None:
        """
        Initialize the SynapseReference based on its arguments.

        Parameters
        ----------
        receptor : str
            Type of the receptor in the synaptic connection. Currently ``ge`` and ``gi``.
        pre_group_idx : int
            Index of the pre-synaptic group.
        post_group_idx : int
            Index of the post-synaptic group.
        syn_type : str
            Type of the synaptic connection.
        pre_type : str
            Type of the pre-synaptic NeuronGroup.
        post_type : str
            Type of the post-synaptic NeuronGroup.
        post_comp_name : str, optional
            Name of the target compartment in the post-synaptic NeuronGroup. Default is
            ``"_soma"``; for other PC compartments (basal/apical dendrites) use
            ``_basal`` or ``_apical``.

        Notes
        -----
        Main internal variables:

        - ``output_synapse``: main dictionary with all data about the current customized
          synapse group: synaptic equations (model, pre, post), synapse and receptor
          type, pre- and post-synaptic group indices and types, namespace for the
          Synapses() object, spatial_decay.
        - ``_name_space``: ``SynapseParser`` instance holding the constant parameters for
          this synaptic equation.
        """
        SynapseReference.syntypes = np.array(
            [
                "STDP",
                "Vogels",
                "deBrito",
                "mtSTDP",
                "mtSTDP_homeo",
                "Fixed_rand_wght",
                "Fixed_const_wght",
                "Fixed_multiply",
                "Depressing",
                "Facilitating",
                "Gap_junction",
            ]
        )
        assert syn_type in SynapseReference.syntypes, (
            f" -  Synapse type '{syn_type}' is not defined"
        )
        self.output_synapse = {
            "type": syn_type,
            "receptor": receptor,
            "pre_group_idx": int(pre_group_idx),
            "pre_group_type": pre_type,
            "post_group_idx": int(post_group_idx),
            "post_group_type": post_type,
            "post_comp_name": post_comp_name,
            "custom_weight": custom_weight,
            "multiply_weight": multiply_weight,
        }
        _name_space = SynapseParser(self.output_synapse, physio_config_df)
        self.output_synapse["namespace"] = {}
        self.output_synapse["namespace"] = _name_space.output_namespace

        ############################################################
        ###                Extract model names                  ###
        ############################################################

        # Just extract everything like in NeuronReference (otherwise many if-elses)
        # For non-pyramidal groups
        try:
            self.excitation_model = value_extractor(
                physio_config_df, "excitation_model"
            ).upper()
        except:  
            self.excitation_model = "SIMPLE_E"

        try:
            self.inhibition_model = value_extractor(
                physio_config_df, "inhibition_model"
            ).upper()
        except:  # noqa: E722
            self.inhibition_model = "SIMPLE_I"

        # For pyramidal groups
        try:
            self.pc_excitation_model = value_extractor(
                physio_config_df, "pc_excitation_model"
            ).upper()
        except:  # noqa: E722
            self.pc_excitation_model = self.excitation_model

        try:
            self.pc_inhibition_model = value_extractor(
                physio_config_df, "pc_inhibition_model"
            ).upper()
        except:  # noqa: E722
            self.pc_inhibition_model = self.inhibition_model

        # NOW the if-else jungle
        if self.output_synapse["post_group_type"] == "PC":
            if self.output_synapse["receptor"] == "ge":
                self.true_receptors = eqt.PCEquationHelper.Receptors[
                    self.pc_excitation_model
                ]
            else:
                self.true_receptors = eqt.PCEquationHelper.Receptors[
                    self.pc_inhibition_model
                ]
        else:
            if self.output_synapse["receptor"] == "ge":
                self.true_receptors = eqt.PCEquationHelper.Receptors[
                    self.excitation_model
                ]
            else:
                self.true_receptors = eqt.PCEquationHelper.Receptors[
                    self.inhibition_model
                ]

        getattr(self, self.output_synapse["type"])()

    def STDP(self) -> None:
        """
        The method for implementing the STDP synaptic connection.

        """

        self.output_synapse["equation"] = b2.Equations("""
            wght : siemens
            dapre/dt = -apre/taupre : siemens (event-driven) # r1 or x_moving_average_plus
            dapost/dt = -apost/taupost : siemens (event-driven) # o1 or y_moving_average_minus
            """)

        self.output_synapse["pre_eq"] = f"""
            {self.output_synapse["receptor"]             + self.output_synapse["post_comp_name"]             + "_post"}+=wght
            apre += Apre
            wght =- eta_ltd * apost
            """
        self.output_synapse["post_eq"] = """
            apost += Apost
            wght =+ eta_ltp * apre
            """

    def Vogels(self) -> None:
        """
        The method for implementing the Vogels_2011_Science synaptic connection.
        """

        self.output_synapse["equation"] = b2.Equations("""
            wght : siemens
            dapre/dt = -apre/taupre : siemens (event-driven)
            dapost/dt = -apost/taupost : siemens (event-driven)
            """)

        self.output_synapse["pre_eq"] = f"""
            {self.output_synapse["receptor"]             + self.output_synapse["post_comp_name"]             + "_post"}+=wght
            apre += Apre
            wght += eta * (apost - alpha)
            wght = clip(wght, 0 * siemens, wght_max)
            """
        self.output_synapse["post_eq"] = """
            apost += Apost
            wght += eta * apre
            wght = clip(wght, 0 * siemens, wght_max)
            """

    def deBrito(self) -> None:
        """
        The method for implementing the deBrito_2024_PLoSComputBiol synaptic connection.
        """

        self.output_synapse["equation"] = b2.Equations("""
            dwght/dt = -wght/tau_wght : siemens (clock-driven)    
            dx_dirac/dt = -x_dirac/tau_x : 1  (clock-driven) # apre
            dy_dirac/dt = -y_dirac/tau_y : 1  (clock-driven) # apost
            
            dx_avg/dt = (x_dirac - x_avg)/tau_x_avg : 1 (clock-driven)
            dy_avg/dt = (y_dirac - y_avg)/tau_y_avg : 1 (clock-driven)
            dahomeo/dt = (y_dirac * y_dirac - ahomeo)/tauhomeo : 1 (clock-driven)
            """)

        self.output_synapse["pre_eq"] = f"""
            {self.output_synapse["receptor"]             + self.output_synapse["post_comp_name"]             + "_post"}+=wght
            wght -= eta_ltd * ahomeo * x_dirac * y_avg * nS
            x_dirac += Apre
            wght = clip(wght, 0*nS, wght_max)
            """
        self.output_synapse[
            "post_eq"
        ] = """
            wght += eta_ltp * y_dirac * y_avg * x_avg * nS
            y_dirac += Apost
            wght = clip(wght, 0*nS, wght_max)
            """

    def mtSTDP(self) -> None:
        """
        The method for implementing the Pfister_2006_JNeurosci synaptic connection following Ruslim_2025_PLoSCB implementation.
        """

        self.output_synapse["equation"] = b2.Equations(
            """
            wght : siemens   
            dpre_trace/dt = -pre_trace/tau_pre : 1  (event-driven) # apre
            dpost_trace/dt = -post_trace/tau_post : 1  (event-driven) # apost
            dpost_trace_slow/dt = -post_trace_slow/tau_post_slow : 1 (event-driven)
            """
        )

        self.output_synapse["pre_eq"] = (
            f"""
            {self.output_synapse["receptor"]                 + self.output_synapse["post_comp_name"]                 + "_post"}+=wght
            wght -= eta_ltd * post_trace * nS
            pre_trace += Apre
            wght = clip(wght, 0*nS, wght_max)
            """
        )
        self.output_synapse[
            "post_eq"
        ] = """
            wght += eta_ltp * pre_trace * post_trace_slow * nS
            post_trace += Apost 
            post_trace_slow += Apost
            wght = clip(wght, 0*nS, wght_max)
            """

    def mtSTDP_homeo(self) -> None:
        """
        The method for implementing the Pfister_2006_JNeurosci synaptic connection with synaptic homeostatic factor.
        """

        self.output_synapse["equation"] = b2.Equations(

            """
            wght : siemens
            dpre_trace/dt = -pre_trace/tau_pre : 1  (event-driven) # apre
            dpost_trace/dt = -post_trace/tau_post : 1  (event-driven) # apost
            dpost_trace_slow/dt = -post_trace_slow/tau_post_slow : 1 (event-driven)
            dpost_trace_homeo/dt = (post_trace - post_trace_homeo)/tau_post_homeo : 1 (event-driven)
            """
        )

        self.output_synapse["pre_eq"] = (
            f"""
            {self.output_synapse["receptor"]                 + self.output_synapse["post_comp_name"]                 + "_post"}+=wght
            wght -= eta_ltd * post_trace * nS
            pre_trace += Apre
            wght = clip(wght, 0*nS, wght_max)
            """
        )
        self.output_synapse[
            "post_eq"
        ] = """
            wght += eta_ltp * pre_trace * post_trace_slow * nS
            wght -= eta_homeo * post_trace_homeo * wght
            post_trace += Apost 
            post_trace_slow += Apost
            wght = clip(wght, 0*nS, wght_max)
            """

    def Fixed_rand_wght(self) -> None:
        """
        The method for implementing the fixed randomized synaptic connection weights    .

        """

        self.output_synapse["equation"] = b2.Equations("""
            wght:siemens
            """)

        pre_eq_lines = [
            f'{true_receptor + str(self.output_synapse["post_comp_name"]) + "_post"} += wght\n'
            for true_receptor in self.true_receptors
        ]
        pre_eq = "".join(pre_eq_lines).rstrip()
        self.output_synapse["pre_eq"] = pre_eq

    def Fixed_const_wght(self) -> None:
        """
        The method for implementing one constant weight across all connections.

        """

        self.output_synapse["equation"] = b2.Equations("""
            wght:siemens
            """)

        pre_eq_lines = [
            f'{true_receptor + str(self.output_synapse["post_comp_name"]) + "_post"} += wght\n'
            for true_receptor in self.true_receptors
        ]
        pre_eq = "".join(pre_eq_lines).rstrip()
        self.output_synapse["pre_eq"] = pre_eq

    def Fixed_multiply(self) -> None:
        """
        The method for implementing the fixed random synaptic connection weights which are multiplied
        with factor coming from Anatomy csv.
        """

        self.output_synapse["equation"] = b2.Equations("""
            wght:siemens
            """)

        # Assigning the multiplier here enables later addition of wght equation into this method .

        pre_eq_lines = [
            f"{true_receptor}{self.output_synapse['post_comp_name']}_post += "
            f"{self.output_synapse['multiply_weight']} * wght\n"
            for true_receptor in self.true_receptors
        ]
        pre_eq = "".join(pre_eq_lines).rstrip()
        self.output_synapse["pre_eq"] = pre_eq

    def Depressing(self) -> None:
        """
        Depressing non-stochastic Tsodyks-Markram synapse

        """

        self.output_synapse["equation"] = b2.Equations("""
        dR/dt = (1-R)/tau_d : 1 (event-driven)
        wght : siemens
        """)

        pre_eq_lines = []
        for true_receptor in self.true_receptors:
            new_line = f'{true_receptor + str(self.output_synapse["post_comp_name"]) + "_post"} += R * U * wght\n'
            pre_eq_lines.append(new_line)
        pre_eq_lines.append("R = R - U * R")
        pre_eq = "".join(pre_eq_lines).rstrip()
        self.output_synapse["pre_eq"] = pre_eq

    def Facilitating(self) -> None:
        """
        Facilitating non-stochastic Tsodyks-Markram synapse

        """

        self.output_synapse["equation"] = b2.Equations("""
        dR/dt = (1-R)/tau_fd : 1 (event-driven)
        du/dt = (U_f-u)/tau_f : 1 (event-driven) 
        wght : siemens
        """)

        pre_eq_lines = []
        for true_receptor in self.true_receptors:
            new_line = f'{true_receptor + str(self.output_synapse["post_comp_name"]) + "_post"} += R * u * wght\n'
            pre_eq_lines.append(new_line)
        pre_eq_lines.append("""
        R = R - u * R
        u = u + U_f * (1-u)
        """)
        pre_eq = "".join(pre_eq_lines).strip()
        self.output_synapse["pre_eq"] = pre_eq

    def Gap_junction(self) -> None:
        """
        The method for implementing gap junctions.

        """

        self.output_synapse["equation"] = b2.Equations("""
            wght:siemens
            Igap_post = wght * (vm_pre - vm_post) : amp (summed)
            """)

        self.output_synapse["post_eq"] = ""
        self.output_synapse["pre_eq"] = ""
