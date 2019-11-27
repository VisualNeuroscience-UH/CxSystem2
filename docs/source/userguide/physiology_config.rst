Physiology configuration
========================

The physiological configuration consists of

* :ref:`General model parameters <general_params>`
* :ref:`Cell-type specific parameters <cell_params>`
* :ref:`Parameters related to connections and synapses <connection_params>`
* :ref:`Other simulation parameters <other_params>`

The pre-defined structure of the physiology configuration is loose compared to the anatomy configuration.
It consists of constants (*variable-values*) and dictionaries (*variable-key-values*).

There are five hard-coded cell types in CxSystem2 (two excitatory, SS and PC; three inhibitory, BC, MC and L1i),
but the user can easily define subtypes, e.g. L4_MC. Subtypes can have arbitrary names (e.g. MyFavouriteBasketCellType, L5_LBC).


.. _general_params:

General model parameters
------------------------
There are some pre-defined parameters that should be defined for every model. In particular, it is important to set
the desired neuron model here. Currently, PCs are restricted to a single neuron model.
Note that the model names must be surrounded by single-quotes.

These parameters are included in the template configuration files.

The parameters are:

    :Physiology:    :code:`model_variation{0,1}`: This should be 1. Value 0 is only for backwards compatibility.

        :code:`neuron_model{'string'}`: Specifies which neuron model to use for point neurons (other cells than PCs). :ref:`Available neuron models <neuron_models>`.

        :code:`excitation_model{'string'}`: Specifies the model for excitatory receptors in point neurons. :ref:`Available receptor models <receptor_models>`.

        :code:`inhibition_model{'string'}`: Specifies the model for inhibitory receptors in point neurons. :ref:`Available receptor models <receptor_models>`.

        :code:`pc_excitation_model{'string'}`: Specifies the model for excitatory receptors in pyramidal cells. :ref:`Available receptor models <receptor_models>`.

        :code:`pc_inhibition_model{'string'}`: Specifies the model for inhibitory receptors in pyramidal cells. :ref:`Available receptor models <receptor_models>`.

        :code:`background_rate{float*Hz}`: Sets the rate for excitatory background synapses (Poisson-distributed). Receptors will be modeled as :code:`excitation_model`.

        :code:`background_rate_inhibition{float*Hz}`: Sets the rate for inhibitory background synapses (Poisson-distributed). Receptors will be modeled as :code:`inhibition_model`.

        :code:`background_E_E_weight{float*unit}`: Weight of excitatory-to-excitatory synapses.

        :code:`background_E_I_weight{float*unit}`: Weight of excitatory-to-excitatory synapses.

        :code:`background_I_E_weight{float*unit}`: Weight of inhibitory-to-excitatory synapses.

        :code:`background_I_I_weight{float*unit}`: Weight of inhibitory-to-inhibitory synapses.


.. _cell_params:

Cell type-specific parameters
-----------------------------
Cell type-specific parameters are given as dictionaries. Subtype-specific parameters (e.g. L23_MC, L4_MC) will override
parameters for the hard-coded types (MC). Parameter names must match those defined in neurodynlib.
For example, to define parameters for BC cells that are modelled as exponential
integrate-and-fire (EIF) neurons, you would write:

 .. csv-table::
   :widths: 2, 5, 5

   BC	,C		,100 * pF
    ,gL		,10 * nS
    ,EL		,-70 * mV
    ,VT		,-40 * mV
    ,DeltaT		,2 * mV
    ,Ee		,0 * mV
    ,Ei		,-75 * mV
    ,tau_e		,3 * ms
    ,tau_i		,8 * ms
    ,V_res		,VT - 4 * mV
    ,Vcut		,VT + 5*DeltaT
    ,V_init_min, EL
    ,V_init_max, VT


This would define a general basket cell type. You could then continue by defining parameters for L23_NBC (L2/3 nest
basket cell) and setting the :code:`neuron_subtype` as L23_NBC for the corresponding group in the
:ref:`Anatomy configuration <neuron_groups>`.

As shown in the example, you can refer to parameters (and do computations using them!) defined earlier in the Physiology configuration.


.. _connection_params:

Parameters related to connections and synapses
----------------------------------------------
Connection weights and connections delays are also given as dictionaries (:code:`cw` and :code:`delay`, respectively).
These are given with reference to the hard-coded cell types. Pathway-specific connection weights can be set in
the anatomy configuration using the :code:`custom_weight` parameter. If there is no custom_weight defined,
then values in the :code:`cw` dictionary will be used. Currently there is no way to define pathway- or neuron
subtype-specific delays.

These dictionaries are included in the template configuration files. Even though you might not have all the
hard-coded cell types in your model, you don't need to delete the redundant lines.


.. _other_params:

Other simulation parameters
---------------------------
There are some additional parameters that are sometimes required. The most important are parameters related to
short-term plasticity (STP) and to connection weight scaling by extracellular calcium concentration.
To see how these are
implemented, please see Methods in `Hokkanen et al. 2019 Neural Computation <https://researchportal.helsinki.fi/files/126265461/Hokkanen_2019_NECO.pdf>`_.

For depressing synapses, you need the following parameters:

    :STP-Depressing:    :code:`U_E{float}`: Utilization factor for depressing excitatory synapses.

        :code:`U_I{float}`: Utilization factor for depressing inhibitory synapses.

        :code:`tau_d{float*unit}`: Recovery time constant (from depression).

For facilitating synapses:

    :STP-Facilitating:    :code:`U_f{float}`: Utilization increment for facilitating synapses.

        :code:`tau_f{float*unit}`: Facilitation decay time constant.

        :code:`tau_fd{float*unit}`: Recovery time constant for facilitating synapses.

If you want to scale synapse weights with respect to extracellular calcium level, you should define the following
parameters:

    :calcium:    :code:`calcium_concentration{float}`: Calcium concentration in mM. If set to 2.0, there is no scaling.

        :code:`flag_background_calcium_scaling{0,1}`: Sets whether background inputs are also scaled with respect to calcium level.

