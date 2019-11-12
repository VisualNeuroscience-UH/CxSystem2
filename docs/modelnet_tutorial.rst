
.. _config_file:

Network & Model Configuration File 
=====================================

The Model & Network configuration file has two main types of lines:

* **Titles-line**: These lines, starting with *row_type* keyword, defines the column titles for all the lines between the the next line and the next *Titles-line*:


  .. csv-table::
     :widths: 10, 10, 15
     
     row_type,sys_mode,total_synapses




This Titles-line indicates that all the lines between the next line and the next Titles-line have three types of columns:  row_type,sys_mode,\
total_synapses. In the next sections, all of these parameters will be described thoroughly. 

* **Values-line**: These lines define the column values corresponding to column titles in the most recent Titles-line:

  .. csv-table::
     :widths: 5, 5, 5

     params,local,7000
  

These three values are in correspondence with the column titles of the previous Titles-line example. In other words, the last two examples defines \
the following values:

  .. csv-table::

	row_type = params
	sys_mode = local
	total_synapses = 7000

Currently there are three types of **row_type** implemented: 

* :code:`params`: defines the run-time parameters of the system run 
* :code:`IN`: defines the input type in the system
* :code:`G`: defines the NeuronGroup()s in the system
* :code:`S`: defines the Synapses() connecting the NeuronGroup()s in the system

In the next sections, each of these row_types has its own types of columns and are thoroughly explained with examples. Note that **mandatory** \
arguments are wrapped with **<>** whereas the **optional** ones are in :code:`[]`. The corresponding **data type** is also presented using :code:`{}`.

params
-------

This is the list of configurable run-time variables implemented in the system:

	:params:  :code:`runtime{int*unit}`: Sets the duration of simulation in number of defined unit, e.g. 3000*ms.

		:code:`device{Python,Cpp,GeNN}`: Sets the simulation device for Brian2.

		:code:`sys_mode{local, expanded}`: The system can be run in two modes: **local** and **expanded** mode.

		:code:`scale{int*unit}`: Sets the radius of cylindrical volume, e.g. 210*um.

		:code:`grid_radius{int*unit}`: Sets the grid radius on which the neurons are placed, e.g. 1*um.

		:code:`minimum_distance{int*unit}`: Sets the minimum distance between neurons, e.g. 1*um.

		:code:`init_vms{0,1}`: defines whether the membrane voltages are randomly initialized.

		:code:`import_connections_from`: sets the path for the file from which the synaptic connection and positions are to be loaded.

		:code:`load_positions_only{1,0}`: Defines whether the positions are only to be loaded from the data file, i.e. flag set to 1, or both positions and synaptic connections, i.e. flag is set to 0.

		:code:`benchmark{1,0}`: Defines whether the full benchmark is to be performed during the simulation. This benchmark, that was used for preparing the data for the CxSystem paper, is high probably not useful for non-developer users since it needs modified copy of brian2 library.

		:code:`save_input_video{1,0}`: Defines whether the generated video input is to be saved or not. This is essential in case the users wants to use the identical input on different runs, so the input can be saved by setting this to 1 and used later.

		:code:`number_of_process{int}`: Defines the number of processes to be spawned for array run.

		:code:`multidimension_array_run{1,0}`: Defines whether the array run is multi-dimensional or one-dimensional. In one-dimensional array run, each set of parameters is run separately, while the other set is fixed. In multidimensional run, the full matrix of parameter combinations are run.

		:code:`trials_per_config{int}`: Defines the number of trials for each simulation. Both in array-runs and single runs, if this flag is set, each of the runs will be repeated that number of times.

		:code:`run_in_cluster{0,1}` Defines whether the current run is going to be submitted to the cluster (this parameter has several parameters associated with it, more details are available in parallelism section of the documentation).

		:code:`profiling{0,1}` Defines whether CxSystem should report the benchmark using the built-in Brian profiler.


Example of the params Titles & Values-lines: 

.. csv-table::

   row_type,sys_mode,scale, grid_radius
   params,local,1,210*us


	
Monitors
---------

Before starting describing the different row_types in the Model & Network configuration file, it is important to understand how the monitors are defined in the system. In Brian2 monitors can be assigned to a :code:`NeuronGroup()` or :code:`Synapses()`. Similarly, when using the configuration file, you are able to set monitors for any target line, i.e. :code:`NeuronGroup()`s or :code:`Synapses()`. The monitors are defined in the following way:

If the monitor column is present in a Titles-line and the value in Values-line is not :code:`--` (without single quotation marks), a monitor object will be created for the :code:`NeuronGroup()` or :code:`Synapses()` of that specific line. Note that it is not possible to have different clocks for monitors in Brian2GeNN. Hence, try to use the monitors wisely to prevent generating bulk data. Following tags can be used for configuring a specific monitor:

 :code:`[Sp]`:
  This tag defines the :code:`[Sp]` ikeMonitor() in Brian2. Example:

  
  .. csv-table::

     ...,[Sp]

The ellipsis represents the predecessor keywords in the line.

 :code:`[St]`:
  This tag defines the :code:`[St]` ateMonitor() in Brian2. In this case, one should define the target variable in the following way: 


  .. csv-table::
     :widths: 5, 30
     
     ...,[St]<state variable1>+<state variable2>


Similar to :code:`[Sp]`, the ellipsis represents the predecessor keywords in the line. State variables are separated with *+*. An example of using :code:`[Sp]` \
alongside with a :code:`[St]` with three state variables of :code:`ge_soma`, :code:`gi_soma`, and :code:`vm`:

  .. csv-table::
     :widths: 5,20

     ..., [Sp] [St]ge_soma+gi_soma+vm 


By default all of the possible indices are being monitored :code:`(record = True)`. However, one might intend to monitor specific indices of \
:code:`NeuronGroup()` or :code:`Synapses()`. This can be achieved by using the :code:`[rec]` tag followed by the indices of interest. In the following example two state \
monitors are defined for :code:`apre` and :code:`wght` of the :code:`Synapses()` object. In the former state monitor the first 20 indices are being recorded while \
in the latter (:code:`wght`), only even indices between 0 and 20 are being recorded:



.. csv-table::
   :widths: 5, 40

   ..., [St]apre[rec](0-20)+wght[rec](0-20-2)



Occasionally, one might want to assign a specific type of monitor to several consecutive target lines. In this case, the generic :code:`monitor(s)` can be \
defined in the first target line and a :code:`-->` symbol should be written at the end of the line. :code:`-->` indicates that all the next lines should be \
assigned with the same monitor. For finishing this assignment, a :code:`<--` symbol should be put at the last target line of interest. Note that it is \
possible to overwrite the defined monitors of some lines between the :code:`-->` and :code:`<--` symbols simply by adding the monitor of the interest. 


.. csv-table::
   :widths: 5, 20
	    
   ...,[St]ge_soma -->
   ...,--
   ...,  
   ...,[Sp] 
   ..., <--

In this example, an :code:`StateMonitor()` over *ge_soma* is assigned on lines 1, 3 and 5 by using the :code:`-->` and :code:`<--` symbol. In the second line, \
the usage of default :code:`StateMonitor()` is over-written by using the :code:`--` keyword, indicating that the second line is not monitored. In the fourth line, \
however, this :code:`StateMonitor()` is overwritten by a :code:`SpikeMonitor()`.




Input
------

The input is defined with the :code:`IN` keyword. Currently, three types of inputs are defined in the CxSystem, namely :code:`VPM`, \
:code:`video`, and :code:`Spikes` from file.  The stimuli is created using a :code:`.mat` file. This stimuli is in form of spike and is passed \
to a :code:`SpikeGeneratorGroup()` . This group is then connected to a relay :code:`NeuronGroup()` with a :code:`synapses()` object. \
The main purpose of the relay neurons is to have positions for input neurons (:code:`SpikeGeneratorGroup` does not support \
positions). Each of the inputs have their specific keywords in the configuration file:

	:VPM params: :code:`idx{int}`: Index of the NeuronGroup().

		:code:`type`: VPM

		:code:`number_of_neurons{int}`: number of thalamocortical fibers.

		:code:`radius{int*unit}`: Total radius of all thalamocortical fibers, e.g. 60*um.

		:code:`spike_times{int*unit}`: stimulation spike timing, e.g. 0.5*ms means a stimulation every 0.5ms.

		:code:`[net_center]`: defines the center of the network

		:code:`[monitors]`


	:video params: **<idx>{int}:** Index of the NeuronGroup().

		:code:`type`: videos

		:code:`path`: relative path to the input .mat file.

		:code:`[freq]`

		:code:`[monitors]` 


	:spikes params: :code:`idx{int}`: Index of the :code:`NeuronGroup()`.

		:code:`type`: spikes

		:code:`input_spikes_filename`: path to the spike file.

		:code:`[monitors]`


This is an example of defining a video input for the system:

  .. csv-table::
     :widths: 10, 5, 10, 20, 10, 5

     row_type,idx,type,path,freq,monitors
     IN,0,video, ./V1_input_layer.mat ,190*Hz ,[Sp]

In this example an input :code:`NeuronGroup()` with index 0 is created based on the :code:`V1_input_layer_2015_10_30_11_7_31.mat` file with a frequency of :code:`190*Hz` and a :code:`SpikeMonitor()` is set on it.
Here's another example for :code:`VPM` input for the system:

  .. csv-table::
     :widths: 10, 5, 5, 10, 5, 10, 10, 10 

	row_type,idx,type,number_of_neurons,radius,spike_times,net_center,monitors
	IN,0, VPM,60,92*um,[0.5]*second, -- ,[Sp]



Neuron Group
------------

The :code:`NeuronGroup()`s are defined using the :code:`G` (as in Group) keyword. This row_type is basically used for defining the :code:`NeuronGroup()`s in Brian2. Following parameters are implemented for defining the :code:`NeuronGroup()`: 

	:param: :code:`idx{int}`: Index of the NeuronGroup().

		:code:`number_of_neurons{int}`: Number of neurons in the NeuronGroup(). 

		:code:`neuron_type{L1i,PC,BC,MC,SS}`: basic biophysical neuron category of the NeuronGroup().

		:code:`layer_idx:` Layer index of the cell groups. 

		:code:`[threshold]`: threshold value for the neurons in the NeuronGroup(). 

		:code:`[reset]`: reset value for the neurons in the NeuronGroup().

 		:code:`[refractory]`: refractory time for the neurons in the NeuronGroup().

 		:code:`[net_center]`: center location of the NeuronGroup().

 		:code:`[monitors]`: monitors of the NeuronGroup().

Examples
~~~~~~~~~

In this section, some of the above-mentioned parameters are clarified. 

:code:`idx`:

The index of the :code:`NeuronGroup()` s are important for creating the synaptic connections between them. As it will be described in the synaptic definitions, creating a synaptic connections needs a presynaptic and postsynaptic group index that should be used directly from this index value.   

:code:`neuron_type`:

The :code:`neuron_type` is the category of the cells of the group, which is one of the following groups:

 .. csv-table::
    :widths: 2, 5


	     type ,Cell  Category         
	     SS  , spiny stellate         
	     PC  , Pyramidal              
	     BC  , Basket                 
	     MC  , Martinotti             
	     L1i , Layer 1 inhibitory     


The :code:`layer index` argument defines the layer in which the :code:`NeuronGroup()` is located. Except for PC cells, all types of neurons are defined as a soma-only neuron, hence their layer is an integer. In case of layer 2/3 using 2 is sufficient. For instance the following example defines a group of 46 SS neurons in layer 2/3: 

 .. csv-table::
    :widths: 10, 5, 10, 10, 10

	row_type,idx,number_of_neurons,neuron_type,layer_idx
	G,1,46,SS,2

Currently PC cells are the only multi-compartmental neurons that could possibly cover more than one layer. In this case, the layer index should be defined as a list where the first element defines the soma location and the second element defines the farthest apical dendrite compartment. In the following example, a PC group of 55 neurons is defined in which the basal dendrites, soma and proximal apical dendrite is located in layer 6 and the apical dendrites covers layer 5 to 2: 

 .. csv-table::
    :widths: 10, 5, 10, 10, 10

	row_type,idx,number_of_neurons,neuron_type,layer_idx
	G,2,55,PC,[6->2]


The compartment formation is then as follows: 

 .. csv-table::
    :widths: 2, 5


	     Layer,Compartment  
	     2/3, Apical dendrite[3]
	     4 , Apical dendrite[2]
	     5 , Apical dendrite[1]
	     6 ,Apical dendrite[0]
	     6 ,        Soma   
	     6 , Basal dendrite   


:code:`[threshold]`, :code:`[reset]` and :code:`[refractory]`:

By default following values are assigned to threshold, reset and refractory of any :code:`NeuronGroup()`: 

- *threshold*: :code:`vm>Vcut`
- *reset*: :code:`vm=V_res`
- *refractory*: :code:`4 * ms`

Any of these variables could be overwritten by using the keyword arguments *threshold*, reset and *refractory*: 

 .. csv-table::
    :widths: 10, 5, 10, 10, 10, 10

	row_type,idx,number_of_neurons,neuron_type,layer_idx,refractory
	G,2,75,BC,2,6*ms 


:code:`[net_center]`:

The center of a :code:`NeuronGroup()` can be defined with the net-center tag in the *Titles-line* and corresponding center position in the *Value line*.  If not defined, the center will be the default value of :code:`0+0j`. The following example creates a :code:`NeuronGroup()` consist of 75 BC neurons located in :code:`5+0j`, with a spike monitors assigned to it: 

 .. csv-table::
    :widths: 10, 5, 10, 10, 10, 10, 10

	row_type,idx,number_of_neurons,neuron_type,layer_idx,net_center,monitors
	G,2,75,BC,2,5+0j,[Sp]

Synapses
--------

S keyword (as in Synapses)  defines the Brian2 Synapses() object.  Following parameters are implemented for defining the Synapses():


	:param: :code:`receptor{ge,gi}` 

		:code:`pre_syn_idx{int}`

		:code:`post_syn_idx{int}` 

		:code:`syn_type{Fixed,STDP}`

		:code:`[p]{float<=1}`: probability

		:code:`[n]{int}`: number of synapses per connection

		:code:`[load_connection]{0,1}`: determines whether this synaptic connection should be loaded from the file.

		:code:`[save_connection]{0,1}`: determines whether this synaptic connection should be saved to the connection file.

		:code:`[monitors]`


 

where the :code:`receptor` defines the receptor type, i.e. ge for excitatory and gi for inhibitory connections, \
*<presynaptic group index>* and *<postsynaptic group index>* defines the index of the presynaptic and postsynaptic group \
respectively. These indices should be determined using the *indexing tag* in the :code:`NeuronGroup()`s lines. The next \
field defines the type of the synapse. Currently there are three types of :code:`Synapses()` implemented: Fixed, STDP, STDP_with_scaling and STP.

Examples
~~~~~~~~

The following example defines a excitatory STDP synaptic connection between :code:`NeuronGroup()`s with
\indices of 2 and 4, in which the :code:`ge` is the receptor:

 .. csv-table::
    :widths: 10, 5, 10, 10, 10

	row_type,receptor,pre_syn_idx,post_syn_idx,syn_type
	S,ge,2,4,STDP 

In case the postsynaptic group is multi-compartmental, the target compartment should be defined using the :code:`[C]` tag. Let us review this concept with an example: 

 .. csv-table::
    :widths: 10, 5, 10, 10, 10

	row_type,idx,number_of_neurons,neuron_type,layer_idx
	G,0,46,SS,4
	G,1,50,PC,[4->1]
	row_type,receptor,pre_syn_idx,post_syn_idx,syn_type
	S,ge,0,1[C]1,STDP

Clearly :code:`NeuronGroup()` 0 is group of 46 :code:`SS` cells and :code:`NeuronGroup()` 1 is a group of 50 :code:`PC` cells. The latter is multi-compartmental with a layer index of :code:`[4,1]`. Hence the compartments formation are as follows: 



 .. csv-table::
    :widths: 5, 10, 5

    Comp. Index, Compartment type,   Layer
    2 ,          Apical dendrite[2], 1
    1 ,          Apical dendrite[1], 2/3
    0 ,          Apical dendrite[0], 4
    0,           Soma, 4
    0, Basal dendrite, 4


The :code:`synapses()` object is targeting the 1st compartment of the :code:`PC` cells, i.e.  Apical dendrite[1]. Consider the following example in which the target is the compartment number 0 in the target :code:`NeuronGroup()`:


 .. csv-table::
    :widths: 5, 5, 5, 5, 5


	row_type,receptor,pre_syn_idx,post_syn_idx,syn_type
	S,ge,0,1[C]0bsa,STDP


As you can see, the compartment :code:`[C]0` is followed by three characters *bsa*. This indicates that the among the three sub-compartments inside the compartment number 0, i.e. Basal dendrite, Soma and Apical dendrite[0], letters of b,s and a are being targeted. Regardless of the layer, the indices of these three compartments are always as (case insensitive):

 .. csv-table::
    :widths: 5, 5
	  
	     Comp. Index,  Compartment  type
	     a ,Apical dendrite[0]
	     s ,      Soma    
	     b , Basal dendrite 

So for instance, in case an inhibitory connection tends to target the soma only, the synaptic definition should be changed to:


 .. csv-table::
    :widths: 5, 5, 5, 5, 5


	row_type,receptor,pre_syn_idx,post_syn_idx,syn_type
	S,ge,0,1[C]0s,STDP


If both basal dendrite and apical dendrite[0] was being targeted, the syntax should change to: 


 .. csv-table::
    :widths: 5, 5, 5, 5, 5

	row_type,receptor,pre_syn_idx,post_syn_idx,syn_type
	S,ge,0,1[C]0ba,STDP

By default the probability of the synaptic connections are determined based on the distance between the neurons, which depends on sparseness and ilam (space constant lambda) variables in the physiology configuration file. In case the maximum probability of the connection should be overwritten, :code:`[p]` tag can be used. In the following example the maximum probability of the connection is overwritten as 0.06 (6%): 

 .. csv-table::
    :widths: 5, 5, 5, 5, 5, 5

	row_type,receptor,pre_syn_idx,post_syn_idx,syn_type,p
	S,ge,0,1[C]0ba,STDP,0.06

By default there are only one synapse for each connection between neurons. This can also be overwritten to another integer value by using the :code:`[n]` tag. So, for having a probability of 6% and 3 synapses per connection between two neurons: 

 .. csv-table::
    :widths: 5, 5, 5, 5, 5, 5, 5

	row_type,receptor,pre_syn_idx,post_syn_idx,syn_type,p,n
	S,ge,0,1[C]0ba,STDP,0.06,3 

