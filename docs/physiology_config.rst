
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
There are some pre-defined constants that should be defined in every model.
Obligatory parameters (and their definitions):
neuron_model, excitation_model, inhibition_model, pc_excitation_model, pc_inhibition_model, background_rate, background_rate_inhibition


.. _cell_params:

Cell type-specific parameters
-----------------------------
Cell type-specific parameters are given as dictionaries. Subtype-specific parameters (e.g. L23_MC, L4_MC) will override parameters for the hard-coded types (MC).
Examples


.. _connection_params:

Parameters related to connections and synapses
----------------------------------------------
Cw, delay are given as dictionaries. These are given with reference to the hard-coded cell types. Pathway-specific connection weights can be set in the anatomy configuration using the custom_weight parameter. If there is no custom_weight defined, then values in the cw dictionary will be used.
Examples


.. _other_params:

Other simulation parameters
---------------------------
Other stuff like calcium_concentration, STP parameters


***********************************************************************

The format of the physiological configuration file is different from that of the network and model configuration file in a sense that the parameters in the configuration file are placed vertically. Typically there are four types of columns in a physiological configuration file:


* **Variables**: is the first column and contains the name of the variable. Some values are in form of key:value pairs and others are just a regular variable with a value. 

  .. csv-table::
     :widths: 7, 2, 2
	      
     calcium_concentration,  ,1

This line defines a variable called calcium_concentration and sets its value to 1. Note that the key is empty.

* **Keys**: The keys for the former type of variables, i.e. those that contain key:value pairs, are defined in this column. In case the variable does not have a key, this cell in front of the variable could be left empty. 
  
* **Values**: Value will be set for either a variable with no keys, or for keys of a variable where the variable itself does not have a value, i.e. is in form of a key:value pairs.

 .. csv-table::
   :widths: 2, 5, 5

   BC	,C		,100 * pF
   	,gL		,10 * nS
   	,Vr		,-67.66 * mV	
   	,EL		,-67.66 * mV
   	,VT		,-38.8 * mV
   	,DeltaT		,2 * mV	
   	,Ee		,0 * mV	
   	,Ei		,-75 * mV	
   	,tau_e		,3 * ms
   	,tau_i		,8.3 * ms
   	,taum_soma	,C/gL	
   	,V_res		,VT- 4 * mV	
   	,Vcut		,VT+ 5*DeltaT


This example defines the different parameters and corresponding values for a BC neuron. The variable in this example is BC, where keys are its parameters and values are corresponding values.

Note the following line in the above example:

.. csv-table::
   :widths: 2, 1
	    
   taum_soma , C/gL


The key defines the Tau_m of the soma in the BC neuron. The value however, is a formula that uses the other keys of the BC neuron, i.e. C and gL.  

* **comments**: any cell starting with # will be considered as a comment. We recommend to dedicate the fourth column to write a short description of the parameters, or key/value pairs.

**Note:** Unlike network and model configuration file, the variable and key names in physiological configuration files could be set to any desired value that is used in the backend of the CxSystem. Attempts have been made to make the name of the current variable/keys descriptive so to make them understandable. All of the implemented variable/keys can be found in physiological configuration files in the `Github
<https://github.com/sivanni/CxSystem/tree/master/config_files>`_ page. 
