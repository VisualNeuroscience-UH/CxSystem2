.. _config_file:

Anatomy & simulation configuration
==================================

This configuration consists of

* :ref:`Simulation run parameters <sim_params>`
* :ref:`External inputs <external_input>`
* :ref:`Neuron groups (cell types) <neuron_groups>`
* :ref:`Connections (pathways) <connections>`

In the browser user interface these are divided into separate tabs, while in the
csv file interface, they are all located in the same “anatomy configuration file”. This configuration includes 
also :ref:`recording monitors <monitors>` for state variables.

If you are using the csv file interface to construct your model, please start from the anatomy and physiology
template csv files provided. If you still have trouble defining your model, please see
`CxSystem1 documentation <https://cxsystem.readthedocs.io/en/master/>`_ or contact us.

.. _sim_params:

Simulation run parameters
-------------------------

The necessary parameters for running simulations locally are:

    :Simulation:  :code:`runtime{int*unit}`: Sets the duration of the simulation, e.g. 200*ms.

        :code:`device{Python,Cython,Cpp,GeNN}`: Sets the device for Brian2 code generation.

        :code:`sys_mode{local, expanded}`: The system can be run in two modes: **local** and **expanded** mode. Expanded mode applies distance 
        dependence of connection probabilities.

        :code:`scale{int}`: Relative area of cortical surface. 

        :code:`grid_radius{float*unit}`: Sets the radius of the 2D circle from which the x-y coordinates are randomized, e.g. 210*um.

        :code:`min_distance{float*unit}`: Sets the minimum distance between neurons inside single layer, e.g. 1*um.

        :code:`workspace_path{string}`: The main working directory of CxSystem; other paths are given relative to this path.

        :code:`simulation_title{string}`: Title for the current batch of simulations.  

        :code:`compression_method{gzip,bzip2,pickle}`: Data compression method.

        :code:`import_connections_from`: Path and filename from where connections with synaptic weights are imported (relative to workspace path).

        :code:`number_of_process`: Number of CPU cores to use in parallel. For array runs only. A single simulation cannot be run in parallel.

        :code:`default_clock`: Simulation time step (e.g. 0.1*ms).

        :code:`trials_per_config{int}`: Number of trials for each set of parameters.

        :code:`init_vms{True, False}`: If True, randomize initial membrane voltages between V_init_min and V_init_max. If False, the initial membrane voltage is set as V_init.

        :code:`load_positions_only{True, False}`: Import unit positions from connectivity file but randomize connections.

        :code:`benchmark{True, False}`: Only for development. Needs modified copy of brian2 library.

        :code:`save_input_video{True, False}`: Defines whether the generated video input is to be saved or not. This is essential in case the users wants to use the identical input on different runs, so the input can be saved by setting this to 1 and used later.

        :code:`multidimension_array_run{True, False}`: Defines whether the array run is multi-dimensional or one-dimensional. In one-dimensional array run, each set of parameters is run separately, while the other set is fixed. In multidimensional run, the full matrix of parameter combinations are run.

        :code:`profiling{True, False}` Defines whether CxSystem should report the benchmark using the built-in Brian profiler.

        :code:`run_in_cluster{True, False}` Run the simulation on a cluster.


If you want to run simulations on a cluster, you will also need to define:

    :Simulation:  :code:`cluster_job_file_path{string}`: Absolute path and filename of the local batch file. Slurm example provided.

        :code:`cluster_number_of_nodes{int}`: Number of nodes to be employed on the HPC server.

        :code:`cluster_address{string}`: Address of the HPC server (e.g. daint.cscs.ch).

        :code:`cluster_login_node{string}`: Address of the login node in case there is one (e.g. ela.cscs.ch).

        :code:`cluster_username{string}`: Username on the HPC system.

        :code:`cluster_workspace{string}`: Workspace path on the HPC server.


.. _external_input:

External input
--------------

Currently, three types of inputs can be used, namely :code:`VPM` (referring to nucleus ventralis posteromedialis; produces synchronous spikes), \
:code:`Video`, and :code:`spikes`. Note that external inputs use common indexing with the unit groups. We recommend
using the index 0 for the input group and indexing unit groups from 1.

    :VPM: :code:`idx{int}`: Index of the unit group.

        :code:`type{VPM}`:

        :code:`number_of_neurons{int}`: number of thalamocortical fibers.

        :code:`radius{float*unit}`: Total radius of all thalamocortical fibers, e.g. 60*um.

        :code:`spike_times{float*unit}`: stimulation spike times, e.g. [1.0 3.0]*ms means input spikes at 1.0 and 3.0 ms.

        :code:`net_center`: defines the center of the thalamocortical fibers in complex coordinates float+floatj.

        :code:`monitors`: Monitors for recording spikes or state variables. :ref:`More information on monitors <monitors>`


    :Video: :code:`idx{int}`: Index of the :code:`NeuronGroup()`.

        :code:`type`: videos

        :code:`path`: relative path to the input .mat file.

        :code:`[freq]`

        :code:`[monitors]`


    :spikes: :code:`idx{int}`: Index of the :code:`NeuronGroup()`.

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
     IN,0,VPM,60,92*um,[0.5]*second, -- ,[Sp]


.. _neuron_groups:

Neuron groups
-------------

Neuron groups (cell types) are defined using the following parameters. Note that biophysical parameters of the
corresponding unit groups are defined in the :ref:`Physiology configuration <cell_params>`. If you add a subtype,
you need to add a corresponding entry to the physiology configuration file.

Brian uses name neurons for model neurons, we prefer to use units to separate them from biological neurons.

There are five hard-coded (neocortical) cell types in CxSystem2. The two excitatory cell types are spiny stellate (SS) and
PC (pyramidal cell). The three inhibitory cell types are basket cell (BC), Martinotti cell (MC) and
L1 inhibitory cell (L1i). The user can easily define subtypes, e.g. L4_MC. Subtypes can have arbitrary names (e.g. MyFavouriteBasketCellType, L5_LBC).

    :NeuronGroups: :code:`idx{int}`: Running index of the unit group.

        :code:`number_of_neurons{int}`: Number of neurons.

        :code:`neuron_type{L1i,PC,BC,MC,SS}`: Neuron type (one of the hard-coded types).

        :code:`neuron_subtype{string}`: Neuron subtype (can be an arbitrary string, or -- if no subtype is needed).

        :code:`layer_idx`: Layer where the unit population is located (layer 2/3 = 2). For PCs, please use the [X->Y] syntax, where 
        X is soma layer and Y is the most distal apical compartment. Note that PC the [X->Y] syntax creates X minus Y compartments above soma layer.
        E.g. for [4->1], the PC will have 3 compartments at soma layer [basal (b), soma (s) and apical0 (a)] and 3 apical dendrite
        compartments above soma layer [a1 at layer idx 3, a2 at layer idx 2 and a3 at layer idx 1]

        :code:`net_center{float+floatj}`: Center point of the unit population in complex coordinates (e.g. 0+0j).

        :code:`monitors`: Monitors for recording spikes and unit state variables, e.g. [Sp]. :ref:`More information on monitors <monitors>`

        :code:`n_background_inputs{int}`: Number of excitatory background synapses.

        :code:`n_background_inhibition{int}`: Number of inhibitory background synapses.


.. _connections:

Connections
-----------

Connections between unit groups are defined using the following parameters. We currently have the following
synapse types: *Fixed*, *Depressing* and *Facilitating*. Short-term plasticity (STP) parameters of the
depressing and facilitating synapses are defined in the :ref:`Physiology configuration <connection_params>`.

    :Connections: :code:`receptor{ge,gi}`: Sets whether the connection is excitatory or inhibitory.

        :code:`pre_syn_idx{int}`: Presynaptic unit group index.

        :code:`post_syn_idx`: Postsynaptic unit group index. When targeting a PC, please use the X[C]Y syntax, where X is the unit group index and Y is the compartment index. See below for an example.

        :code:`syn_type`: Synapse model.

        :code:`p{float<=1}`: Connection probability. For retinocortical or other thalamic connections, use "--". Here, the connection probability will be read from physiology file paramater `sp` for sparseness

        :code:`n{int}`: Number of synapses per connection.

        :code:`monitors`: Monitors for synaptic state variables. :ref:`More information on monitors <monitors>`

        :code:`load_connection{0,1}`: Flag for loading the connection and its parameters.

        :code:`save_connection{0,1}`: Flag for saving the connection and its parameters.

        :code:`custom_weight{float*unit}`: Synaptic weight for this specific connection, e.g. 1.5*nS. Overrides :ref:`more general weight definitions <connection_params>`.

        :code:`spatial_decay{float,[ij],float[ij]}`: When sys_mode is expanded, provides lambda (spatial decay parameter) for  weight * p * exp(-lambda * d); d is the distance between neurons in mm. [ij] stands for 1-to-1 connections, and useful only when you have the same N units in the pre- and postsynaptic groups.


If the postsynaptic unit is a multicompartmental neuron model, the target compartment must be defined using the :code:`[C]` tag.
Compartmental indexing starts from zero at the soma layer and increases towards the distal apical dendrite. The soma, and the basal
dendrites and the first apical dendrite compartment are located in the soma layer are distinguished with s, b and a tags, respectively.

For example, if you have PC unit with a :code:`layer_idx` of [6->1] (soma in layer 6 and apical dendrite extending up to layer 1),
the compartmental indexing is:

 .. csv-table::
    :widths: 5, 10, 5

    Comp. Index, Compartment type,   Layer
    4 ,          Apical dendrite (distal), 1
    3 ,          Apical dendrite, 2/3
    2 ,          Apical dendrite, 4
    1 ,          Apical dendrite, 5
    0a ,          Apical dendrite (proximal), 6
    0s,           Soma, 6
    0b, Basal dendrites, 6


Thus, if you want target the most distal apical compartment of this group, the :code:`post_syn_idx` should be
neuron_group_index[C]4.


.. _monitors:

Monitors
---------

Both unit groups (neuron groups) and synapses can be monitored, i.e. their state variables can be recorded and stored for
analysis. Most commonly users only need the spikes. Note that continuous state variables (like the membrane
voltage) are recorded with the same resolution as the time step, and thus large networks can quickly create
gigabytes of data.

The following tags can be used to define a specific monitor:

 :code:`[Sp]`:
  This tag defines a :code:`[Sp]` ike monitor.

 :code:`[St]`:
  This tag defines a :code:`[St]` ate monitor.


You can combine a spike monitor with multiple state monitors like this (note the space between [Sp] and [St]):

  :code:`[Sp] [St]ge_soma+gi_soma+vm`.

By default all neurons/synapses are being monitored. If you want to monitor specific neurons (or synapses),
you should use the :code:`[rec]` tag followed by indices of interest. For example, to monitor the membrane voltage (vm)
of the first 20 neurons (in the group) and the excitatory conductance (ge_soma) of every evenly indexed unit between 0 and 100,
you would write:

  :code:`[St]vm[rec](0-20)+ge_soma[rec](0-100-2)`


Often you want to assign a specific type of monitor to several consecutive unit groups (or connections). In this case, the monitor can be \
defined for the first unit group and a :code:`-->` tag should be written at the end of the line. :code:`-->` indicates that all the consecutive unit groups should be \
assigned with the same monitor. For finishing this assignment, a :code:`<--` symbol should be put at the last target line of interest. Note that it is \
possible to overwrite the defined monitors of some lines between the :code:`-->` and :code:`<--` symbols simply by adding the monitor of the interest.


.. csv-table::
   :widths: 5, 20

   G1,[St]ge_soma -->
   G2,--
   G3,
   G4,[Sp]
   G5, <--

In this example, a state monitor over *ge_soma* is assigned to unit groups 1, 3 and 5 by using the :code:`-->` and :code:`<--` tags. For the second group, \
the usage of default state monitor is over-written by using the :code:`--` keyword, indicating that the second line is not monitored. For the fourth group, \
however, the default monitor is overwritten by a spike monitor.
