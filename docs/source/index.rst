.. CxSystem2 documentation master file, created by
   sphinx-quickstart on Tue Nov 26 10:30:30 2019.
   You can adapt this file completely to your liking, but it should at least
   contain the root `toctree` directive.

Welcome to CxSystem2!
=====================================

CxSystem2 is a flexible cortical simulation framework, implemented in python over `Brian2 package
<http://briansimulator.org>`_.

The CxSystem is intended for easy and efficient numerical simulation of biomimetic spiking network **cortical** models.
The model is constructed in two files in either CSV or JSON format.

The CxSystem is open source, and can be freely used under GNU GPL3 (see `LICENSE
<https://github.com/VisualNeuroscience-UH/CxSystem2/blob/master/LICENSE>`_). The articles describing the details and
testing of the framework have been published in Neural Computation [1]_ [2]_.

Contents:

.. toctree::
   :maxdepth: 2

   introduction
   overview
   installation
   configs
   parallelism
   examples
   developersguide
   reference




Indices and tables
==================

* :ref:`genindex`
* :ref:`modindex`
* :ref:`search`


.. [1] Andalibi, V., Hokkanen, H., Vanni, S. (2019). Controlling complexity of cerebral cortex simulations: I CxSystem, a flexible cortical simulation framework. Neural Computation, 31, 1048-1065. https://doi.org/10.1162/neco_a_01120
.. [2] Hokkanen, H., Andalibi, V., Vanni, S. (2019). Controlling complexity of cerebral cortex simulations: II Streamlined microcircuits. Neural Computation, 31, 1066-1084. https://doi.org/10.1162/neco_a_01188
