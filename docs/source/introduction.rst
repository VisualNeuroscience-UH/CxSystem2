.. |br| raw:: html

   <br />

Introduction
==============================

Recent development of high-level simulation engines, such as `brian
<http://briansimulator.org/>`_, `NEURON
<https://www.neuron.yale.edu/neuron/>`_ or `NEST
<http://www.nest-simulator.org/>`_, support coding of complex cell morphologies or large networks with few lines of code.
However, biologically meaningful modeling of cerebral cortex is challenging because the diversity of synapse types,
cell types and network structure as well as multiple biophysical parameters unavoidably create a code complexity
nightmare. As a result, complexity of nature becomes entangled with complexity of computer code.

The CxSystem2 is the upgraded and improved version of CxSystem, a simulation framework which is built on top of brian2
simulation engine, and is purposed to divide the complexity remaining on top of the high-level simulation engine in
two parts. The first part includes the code complexity. The model system and required complexity reduction is decided
at the beginning of a project and part of the model is coded into the simulation framework which runs on top of an
existing simulation engine. This part comprises the coding, and controls computational efficiency and parameter space
reduction. The second part is free to include the complexity of nature, given the restriction of the framework. Here,
the end user has a simple interface to the simulator, hiding the code. With appropriate filters, the life scientist can
start research from an existing complex model. The simple user interface, the spreadsheet, supports experimentation with
complex biological systems and aims at reduced development time without coding errors.

CxSystem  has been tested with a simplification of a recently published comprehensive cortical microcircuit model [1]_ and aims at easy testing and buildup of diverse models at single cell resolution. It reuses components of earlier work [2]_, but the code has been completely rewritten to be dynamically compiled from configuration files, and to run on C++ and GeNN [3]_ devices. Implemented on the top of the Python-based Brian2 simulator [4]_, CxSystem supports the main goal of Brian, i.e. minimizing development time, by providing the user with a simplified interface. |br| The two configuration files, easily modifiable with regular spreadsheet programs, have a biologically meaningful syntax and are appropriate for life scientists who are unaccustomed to computer programming. CxSystem is available in `Github
<https://github.com/VisualNeuroscience-UH/CxSystem>`_.

|br|
|br|

.. [1] Markram, H., Muller, E., Ramaswamy, S., Reimann, M. W., Abdellah, M., Sanchez, C. A., … Schürmann, F. (2015). Reconstruction and Simulation of Neocortical Microcircuitry. Cell, 163(2), 456–492. http://doi.org/10.1016/j.cell.2015.09.029
.. [2] Heikkinen, H., Sharifian, F., Vigário, R., & Vanni, S. (2015). Feedback to distal dendrites links fMRI signals to neural receptive fields in a spiking network model of the visual cortex. Journal of Neurophysiology, 114(1), 57–69. http://doi.org/10.1152/jn.00169.2015
.. [3] Yavuz, E., Turner, J., & Nowotny, T. (2016). GeNN: a code generation framework for accelerated brain simulations. Scientific Reports, 6(1), 18854. http://doi.org/10.1038/srep18854
.. [4] Goodman, D., & Brette, R. (2009). The Brian simulator   . Frontiers in Neuroscience
