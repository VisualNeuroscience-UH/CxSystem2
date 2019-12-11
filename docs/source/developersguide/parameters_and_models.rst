Parameters and Models
=====================


Adding parameters
-----------------

The parameters of the Model & Network configuration file are defined and
deployed in the main module, i.e. :code:`CxSystem.py`. There are two steps to
add a new parameter:

* **Defining a function:**

  This is usually a setter function that sets a module attribute using a given attribute:

.. code-block:: python

    def set_sample(self,*args):
        self.sample = eval(args[0])

In this example, :code:`set_sample()` will set the sample attribute based on a given argument.

* **Add the parameter name to "*parameter_to_method_mapping*" dictionary:**

This is where the defined function in the previous step is used: by just appending the variable and function name as a key:value pair to :code:`parameter_to_method_mapping` dictionary:

.. code-block:: python

	{
	...,
	'sample_parameter': [n,self.set_sample]}


Where :code:`n` is the priority value in setting the parameter. The priority value is useful when one wants to define a parameter based on another but they might not be inserted in the correct order. By default, the priority value could follow the last number in the :code:`parameter_to_method_mapping` dictionary. The priority value does not need to be unique, two values could have the same priority and they run one after another. For example:

.. code-block:: python

	    self.parameter_to_method_mapping = {
	    'device': [0,self.set_device],
            'save_input_video': [1,self.save_input_video],
	    }


Here, :code:`save_input_video` will be set using :code:`self.save_input_video` after :code:`device`, that is set using :code:`self.set_device`.


Adding Neuron Model
--------------------
Adding a new neuron group
`````````````````````````
The hard-coded neuron types (L1i, BC, MC, SS, PC) are in the class *NeuronReference* in physiology_reference.py.
Under this class, there is a separate method for each neuron group containing code that builds the membrane equation(s).
Adding a new neuron group can be done by copy-pasting the method of eg. the BC neuron group and renaming it (ChC for chandelier cell):

.. code-block:: python

   def ChC(self):
        x = neuron_factory().get_class(self.neuron_model)
        x.set_excitatory_receptors(self.excitation_model)
        x.set_inhibitory_receptors(self.inhibition_model)
        ...

You also need to add the neuron type to the list of accepted types under the init of *NeuronReference*:

.. code-block:: python

   NeuronReference._celltypes = array([...existing neuron types..., 'ChC'])

Similarly, add the neuron type also to the list of accepted types under the init of :code:`NeuronParser` (in :code:`parameter_parser.py`), and create a method for parameter processing. Often, parameters can be used as such in the equations, so the method becomes:

.. code-block:: python

   def _ChC(self, output_neuron):
      pass

Please note the underscore here before the neuron group name. Now, you can use the name 'ChC' to define the connectivity and biophysical parameters in the CSV configuration files.

Note that you might need to add connection weights and delays in physiological configuration file based on the synapses you are going to use with your new neuron model. Also, neuron group equations in CxSystem must have x and y coordinates, so adding the following at the end of the equation block is neccessary:

.. code-block:: python

		self.output_neuron['equation'] += Equations('''x : meter
		y : meter''')

After this, the neuron equation parameters should be added to Physiological configuration file.

Adding alternative neuron models to existing groups
```````````````````````````````````````````````````
Instead of adding a hard-coded neuron type, you typically need to add an alternative neuron model.
Point neuron models are now located in the :code:`cxsystem2.neurodynlib` submodule (soon multicompartment models as well), where
you can create a class for the new neuron model. Using :code:`PointNeuron` as a base class gives access to
basic functionalities for exploring the model behavior.

For example, to add the adaptive exponential integrate-and-fire (AdEx) model, we have written:

.. code-block:: python

    class AdexNeuron(PointNeuron):

        default_neuron_parameters = {
                'EL': -70.0 * mV,
                'V_res': -51.0 * mV,
                'VT': -50.0 * mV,
                'gL': 2 * nS,
                'C': 10 * pF,
                'DeltaT': 2 * mV,
                'a': 0.5 * nS,
                'b': 7.0 * pA,
                'tau_w': 100.0 * ms,
                'refractory_period': 2.0 * ms,
                'Vcut': -30.0 * mV
        }

        neuron_model_defns = {'I_NEURON_MODEL': 'gL*(EL-vm) - w + gL * DeltaT * exp((vm-VT) / DeltaT)',
                              'NEURON_MODEL_EQS': 'dw/dt = (a*(vm-EL) - w) / tau_w : amp'}
        model_info_url = 'http://neuronaldynamics.epfl.ch/online/Ch6.S1.html'

Then we added the init method:

.. code-block:: python

    def __init__(self):

        super().__init__()
        self.threshold_condition = 'vm > Vcut'
        self.reset_statements = 'vm = V_res; w += b'
        self.initial_values = {'vm': None, 'w': 0*pA}  # None in vm => vm initialized at EL
        self.states_to_monitor = ['vm', 'w']  # Which state variables to monitor by default

        # Parameters and their units that have not been defined in the base class:
        new_parameter_units = {'DeltaT': mV, 'Vcut': mV, 'a': nS, 'b': pA, 'tau_w': ms}
        self.parameter_units.update(new_parameter_units)

After these initial definitions, you can add model-specific methods. Finally, you need to add the neuron model to the
factory method via which CxSystem accesses neurodynlib:

.. code-block:: python

    class neuron_factory:
        def __init__(self):
            self.name_to_class = {...existing models... , 'ADEX': AdexNeuron}

After this you can use change the *neuron_model* parameter to 'ADEX' to use the AdEx equations in your point neurons.

Adding Synapse Model
---------------------
Synapse models are currently located in :code:`cxsystem2.core` in physiology_reference.py.
Similarly to adding new neuron groups, you need to add the new synapse types to the lists of accepted types.
For example, we wanted to add a 'Depressing' synapse type (a form of short-term synaptic plasticity).
First, in the init of :code:`SynapseReference` (:code:`physiology_reference.py`):

.. code-block:: python

   SynapseReference.syntypes = array([...existing synapse types..., 'Depressing'])

Then similarly in the init of *synapse_parser* (parameter_parser.py):

.. code-block:: python

   synapse_parser.type_ref = array ([...existing synapse types..., 'Depressing'])

Equations for the new synapse type were then added as a method under *SynapseReference*:

.. code-block:: python

    def Depressing(self):

        self.output_synapse['equation'] = Equations('''
        wght : siemens
        R : 1
        ''')

        self.output_synapse['pre_eq'] = '''
        R = R + (1-R)*(1 - exp(-(t-lastupdate)/tau_d))
        %s += R * U * wght
        R = R - U * R
        ''' % (self.output_synapse['receptor'] + self.output_synapse['post_comp_name'] + '_post')

After these changes, one can use the reference 'Depressing' in the Anatomy configuration when defining connections
between neuron groups.

