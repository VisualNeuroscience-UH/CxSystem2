.. |br| raw:: html

   <br />

Examples
==========



Building a new model
---------------------

A new network can be designed by using a regular spreadsheet program, such as Excel, whose output is readable by everyone taking part in the research project. The idea is that a scientist leading the project can consult an electrophysiologist or an anatomist without referring to implementation-level code. |br|
Practically, you first need to decide the system structure, e.g. how many of the six cortical layers you are going to model, and which cell groups you want to include in each layer. Cell group definition takes a single row in the Model and Network file. Connectivity parameters (connection probability, synapse type, number of synapses per connection) can then be set in the same file, with a single row for each axonal pathway. In the Physiology file, you can then set the electrophysiological parameters corresponding to each neuron group. |br|
Admittedly, a new project might need functionalities we have not implemented. New features can however be programmed in Python in the Physiology reference file (eg. synapse with STDP) and they can then be referenced in either of the two main configuration files. We try to hide away implementation details so that the complexity (amount of code) would not overwhelm project members, who are not familiar with programming. Thus, the configuration files themselves do not act as perfect blueprints of the new network. We believe such simple interfaces are necessary for fruitful interaction between scientists in any larger project. 



Porting an existing model
--------------------------

The first steps to port an existing model to CxSystem is to identify the required type of the target network and as well as define the cell group characteristics. CxSystem already has one type of multi-compartmental neuron and four types of point neurons built in which can be used as templates to replicate the neuron types in the target model. Each of the neuron groups will take a single line in the Model and Network file. The physiological parameters of the neurons should also be modified in the physiological file. In the next step, the type and direction of synaptic connections between the neuron groups should be determined. Finally, the required model and simulation parameters can be imported from one of the currently available Model and Network files in the github, or from other existing model (after filter construction) and the initial simulations can be run. |br|
As an example, we have ported the COBAHH example from Brian2 documentation originally described in a review paper by Brette et al. [1]_. In the brian2 implementation, this example was implemented with only a single neuron group containing 4000 neurons. We implemented this into two groups: a group containing 3200 excitatory HH cells (`HH_E`) and a second group containing 800 inhibitory HH cells (`HH_I`). 
Both excitatory and inhibitory cell sub-groups were fully connected to all the other cells. The following table is the network and model configuration file for COBAHH example:  


  .. csv-table::
     
     row_type,runtime,profiling,default_clock,init_vms,min_distance,scale
     params,1000 \*ms,1,0.1 \* ms,1,1\*um,1
     row_type,sys_mode,grid_radius,device,number_of_processes,
     params,local,210*um,cpp,1,
     row_type,idx,number_of_neurons,neuron_type,layer_idx,net_center,monitors
     G,0,3200,HH_E,4,--,[Sp]
     G,1,800,HH_I,4,--,[Sp]
     row_type,receptor,pre_syn_idx,post_syn_idx,syn_type,p,n
     S,ge,0,0,Fixed,0.02,1
     S,ge,0,1,Fixed,0.02,1
     S,gi,1,0,Fixed,0.02,1
     S,gi,1,1,Fixed,0.02,1

Next, we created a copy of physiological parameters and modified the `HH_E` and `HH_I` neuron parameters, e.g. Vr, El, Vt, etc., according to the COBAHH example. The synaptic weights were also set accordingly. Finally, the essential network parameters, e.g. simulation duration, device, system mode, output folder, was set and the CxSystem was run using the two new csv files. The physiological configuration file for COBAHH example is available in CxSystem Github page. The physiological configuration file is illustrated in the following table:

  .. csv-table::

     Variable,Key,Value
     calcium_concentration,,2
     # Connection weights #,,
     _weights,w_All_other_E-E_connections,6*nS
     ,w_All_other_E-I_connections,6\*nS
     ,w_All_other_I-E_connections,11 \* 6*nS
     ,w_All_I-I_connections,11 \* 6\*nS
     cw,cw_HH_E_HH_E,_weights['w_All_other_E-E_connections']
     ,cw_HH_E_HH_I,_weights['w_All_other_E-I_connections']
     ,cw_HH_I_HH_E,_weights['w_All_other_I-E_connections']
     ,cw_HH_I_HH_I,_weights['w_All_I-I_connections']
     # SYNAPTIC DELAYS #,,
     delay,delay_HH_E_HH_E,3.0\*ms
     ,delay_HH_E_HH_I,3.0\*ms
     ,delay_HH_I_HH_E,3.0\*ms
     ,delay_HH_I_HH_I,3.0\*ms
     # Parameters #,,
     HH_E,C,200\*pF
     ,gL,10\*nS
     ,g_na,20. \* usiemens
     ,g_kd,6. \* usiemens
     ,ENa,50\*mV
     ,EK,-90\*mV
     ,taum_soma,C/gL
     ,EL,-60 \* mV
     ,Vr,-60 \* mV
     ,Vcut,20 \* mV
     ,VT,-63 \* mV
     ,V_res,-80 \* mV
     ,Ee,0 \* mV
     ,Ei,-80 \* mV
     ,tau_e,5\*ms
     ,tau_i,10\*ms
     ,,
     HH_I,C,200\*pF
     ,gL,10\*nS
     ,g_na,20. \* usiemens
     ,g_kd,6. \* usiemens
     ,ENa,50\*mV
     ,EK,-90\*mV
     ,taum_soma,C/gL
     ,EL,-60 \* mV
     ,Vr,-60 \* mV
     ,Vcut,20 \* mV
     ,VT,-63 \* mV
     ,V_res,-80 \* mV
     ,Ee,0 \* mV
     ,Ei,-80 \* mV
     ,tau_e,5*ms
     ,tau_i,10\*ms

     
In this example, we used the built-in neurons types of CxSystem. In the next section, we have provided a guidelne for users who want to build a new type of neuron/synapse and use them in a network model file.

.. [1] Brette, R., Rudolph, M., Carnevale, T., Hines, M., Beeman, D., Bower, J.M., Diesmann, M., Morrison, A., Goodman, P.H., Harris, F.C. and Zirpe, M., 2007. Simulation of networks of spiking neurons: a review of tools and strategies. Journal of computational neuroscience, 23(3), pp.349-398.
