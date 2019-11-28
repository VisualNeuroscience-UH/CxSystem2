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
Equations for different neuron types are in the class *NeuronReference* in physiology_reference.py. Under this class, there is a separate method for each neuron group containing equation templates. Adding a new neuron group can be done by copy-pasting the method of eg. the BC neuron group and renaming it (ChC for chandelier cell):

.. code-block:: python

   def ChC(self):
      self.output_neuron['equation'] = Equations('''
      dvm/dt = ((gL*(EL-vm) + gL * DeltaT * exp((vm-VT) / DeltaT) + ge * (Ee-vm) + gi * (Ei-vm) / C): volt (unless refractory)
      dge/dt = -ge/tau_e : siemens
      dgi/dt = -gi/tau_i : siemens
      ''', ge='ge_soma', gi='gi_soma')
      self.output_neuron['equation'] += Equations('''x : meter
                                                     y : meter''')

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
```````````````````````````````````````````````````````
Typically you want to add an alternative neuron model to an existing neuron group. Suppose you wanted to have the adaptive exponential integrate-and-fire model (AdEx) alongside the regular exponential integrate-and-fire model (EIF). You want to flexibly switch between the models using a 0/1 flag in the physiological configuration file. First, you would add the AdEx equations to :code:`NeuronReference`:

.. code-block:: python

   def BC(self):

       self.output_neuron['equation'] = ...default model definition here...

       if self.flag_adex == 1:
            self.output_neuron['equation'] = Equations('''
                dvm/dt = ((gL*(EL-vm) + gL * DeltaT * exp((vm-VT) / DeltaT) + ge * (Ee-vm) + gi * (Ei-vm) -w) / C) : volt (unless refractory)
                dge/dt = -ge/tau_e : siemens
                dgi/dt = -gi/tau_i : siemens
                dw/dt = (a*(vm - EL)-w)/tau_w : amp
                ''', ge='ge_soma', gi='gi_soma')

Make a similar change to all the neuron groups you want to be affected. Then, extract :code:`flag_adex` in the init of :code:`NeuronReference`:

.. code-block:: python

   try:
      self.flag_adex = self.value_extractor(self.physio_config_df, 'flag_adex')
      if self.flag_adex == 1:
         self.output_neuron['reset'] += '; w=w+'+repr(self.output_neuron['namespace']['b'])
   except:
      self.flag_adex = 0

It is a good idea to extract any flag under :code:`try` unless you want it to be always explicitly defined (will cause an error if not defined). In the case of AdEx, also the reset condition needs to be modified here as it is not a part of the equation templates. After these changes, you can use :code:`flag_adex` in the physiological CSV file to switch between the two neuron models.


Adding Synapse Model
---------------------
Similarly to adding new neuron groups, you need to add the new synapse types to the lists of accepted types. Suppose you wanted to add a 'Depressing' synapse type (a form of short-term synaptic plasticity). First, in the init of :code:`SynapseReference` (:code:`physiology_reference.py`):

.. code-block:: python

   SynapseReference.syntypes = array([...existing synapse types..., 'Depressing'])

Then similarly in the init of *synapse_parser* (parameter_parser.py):

.. code-block:: python

   synapse_parser.type_ref = array ([...existing synapse types..., 'Depressing'])

Equations for the new synapse type can then be added as a method under *SynapseReference*:

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

After these changes, one can use the reference 'Depressing' in the anatomical CSV configuration file when defining connections between neuron groups. Definition of 'Facilitating' synapses could then be added in a similar way.

