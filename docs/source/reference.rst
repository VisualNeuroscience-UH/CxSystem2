Reference Documentation
====================================

Core module
------------------------------------
.. module:: cxsystem2.core.cxsystem
.. autoclass:: CxSystem
   :members:

   .. automethod:: CxSystem.__init__


.. module:: cxsystem2.core.parameter_parser
.. autoclass:: NeuronParser
   :members:

   .. automethod:: NeuronParser.__init__

.. autoclass:: SynapseParser
   :members:

   .. automethod:: SynapseParser.__init__


.. module:: cxsystem2.core.physiology_reference
.. autoclass:: NeuronReference
   :members:

   .. automethod:: NeuronReference.__init__

.. autoclass:: SynapseReference
    :members:

    .. automethod:: SynapseReference.__init__


.. module:: cxsystem2.core.workspace_manager
.. autoclass:: Workspace
    :members:

    .. automethod:: Workspace.__init__

.. module:: cxsystem2.core.equation_templates
.. autoclass:: EquationHelper
    :members:

    .. automethod:: EquationHelper.__init__


.. module:: cxsystem2.core.stimuli
.. autoclass:: Stimuli
    :members:

    .. automethod:: Stimuli.__init__


.. module:: cxsystem2.core.tools
.. autofunction:: write_to_file
.. autofunction:: load_from_file
.. autofunction:: parameter_finder
.. autofunction:: change_parameter_value_in_file
.. autofunction:: read_config_file




neurodynlib module
------------------------------------

.. module:: cxsystem2.neurodynlib.multicompartment_models
.. autoclass:: LeakyCompartment
    :members:

    .. automethod:: LeakyCompartment.__init__


.. autoclass:: MulticompartmentNeuron
    :members:

    .. automethod:: MulticompartmentNeuron.__init__


.. autoclass:: LegacyPyramidalCell
    :members:

    .. automethod:: LegacyPyramidalCell.__init__



.. module:: cxsystem2.neurodynlib.neuron_models
.. autoclass:: PointNeuron
    :members:

    .. automethod:: PointNeuron.__init__


.. autoclass:: LifNeuron
    :members:

    .. automethod:: LifNeuron.__init__


.. autoclass:: EifNeuron
    :members:

    .. automethod:: EifNeuron.__init__

.. autoclass:: AdexNeuron
    :members:

    .. automethod:: AdexNeuron.__init__


.. autoclass:: HodgkinHuxleyNeuron
    :members:

    .. automethod:: HodgkinHuxleyNeuron.__init__


.. autoclass:: IzhikevichNeuron
    :members:

    .. automethod:: IzhikevichNeuron.__init__

.. autoclass:: LifAscNeuron
    :members:

    .. automethod:: LifAscNeuron.__init__

.. autoclass:: neuron_factory
    :members:

    .. automethod:: neuron_factory.__init__


.. module:: cxsystem2.neurodynlib.receptor_models
.. autoclass:: ReceptorModel
    :members:

    .. automethod:: ReceptorModel.__init__


.. module:: cxsystem2.neurodynlib.tools.input_factory
.. autofunction:: get_step_current
.. autofunction:: get_ramp_current
.. autofunction:: get_sinusoidal_current
.. autofunction:: get_zero_current
.. autofunction:: get_spikes_current
.. autofunction:: plot_step_current_example
.. autofunction:: plot_ramp_current_example
.. autofunction:: plot_sinusoidal_current_example
.. autofunction:: getting_started


.. module:: cxsystem2.neurodynlib.tools.plot_tools
.. autofunction:: plot_voltage_and_current_traces
.. autofunction:: plot_network_activity
.. autofunction:: plot_ISI_distribution
.. autofunction:: plot_spike_train_power_spectrum
.. autofunction:: plot_population_activity_power_spectrum


.. module:: cxsystem2.neurodynlib.tools.spike_tools

.. autofunction:: get_spike_time
.. autofunction:: get_spike_stats
.. autofunction:: pretty_print_spike_train_stats
.. autofunction:: filter_spike_trains
.. autofunction:: get_spike_train_stats
.. autofunction:: _spike_train_2_binary_vector
.. autofunction:: _get_spike_train_power_spectrum
.. autofunction:: get_averaged_single_neuron_power_spectrum
.. autofunction:: get_population_activity_power_spectrum




Configuration module
------------------------------------
.. module:: cxsystem2.configuration.config_file_converter
.. autoclass:: ConfigConverter
    :members:

    .. automethod:: ConfigConverter.__init__


gui module
------------------------------------
.. module:: cxsystem2.gui.gui
.. autoclass:: RunServer
    :members:

    .. automethod:: RunServer.__init__

visualization module
------------------------------------
.. module:: cxsystem2.visualization.spikedata_to_csvs
.. autoclass:: SpikeData
    :members:

    .. automethod:: SpikeData.__init__

.. module:: cxsystem2.visualization.rasterplot_to_pdf
.. autoclass:: rasterplot_pdf_generator
    :members:

    .. automethod:: rasterplot_pdf_generator.__init__
