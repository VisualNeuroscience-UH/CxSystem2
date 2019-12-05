Batch simulations
=================

Array run (Parallel runs) can be set using the curly braces around the target parameter. There are two special characters
indicating either an explicit vector of values (ampersand, \&) or numpy style range with step as the third value (vertical bar, \|).

For instance, to run 3 separate simulations\
with :code:`scale=1`, :code:`scale=2` and :code:`scale=3`, the parameter scale should be set to:

 .. csv-table:: 

	...,scale,...
	...,{1&2&3},...

This parallel run will use the number of processes (threads) that is set using the :code:`number_of_process` parameter, e.g. if :code:`number_of_process=3`, \
then each of the 3 simulations runs in their own threads. However, if :code:`number_of_process=2`, two processes run first the \
simulation for :code:`scale=1`, and :code:`scale=2`. The third simulation with :code:`scale=3` will start when the first of the two simulations are completed.

The array_run could also be set in range with defined step:

 .. csv-table:: 

	...,scale,...
	...,{1|5|1},...

This parallel run will use four simulations with :code:`scale=1`, :code:`scale=2`, :code:`scale=3` and :code:`scale=4`. Note the numpy style vector excluding the last index.

When two or more parameters are set to use array runs, CxSystem can run the parallel runs either as multi-dimensional runs \
or independent runs. For example: suppose a simulation is to be performed for scale :code:`{1&2&3}` with :code:`init_vms` set to :code:`{0,1}`. \
If :code:`multidimension_array_run` flag is set to 1, the following 6 simulations will be run separately:

::

	{scale=1, init_vms=0}, {scale=1, init_vms=1}, {scale=2, init_vms=0}, {scale=2, init_vms=1}, {scale=3, init_vms=0}, {scale=3, init_vms=1}

When :code:`multidimension_array_run flag` is set to 0, however, the array_run pattern is different and 5 simulations will be run in parallel:

::

	{scale=1}, {scale=2}, {scale=3}, {init_vms=0}, {init_vms=1}

One might want to run each of the parallel simulations several times, e.g. to observe an effect of random initialization on a particular parameter set.
For this purpose the :code:`trials_per_config` should be set to the desired number of runs per configuration.