.. CxSystem documentation master file, created by
   sphinx-quickstart on Mon Jun  6 14:36:08 2016.
   You can adapt this file completely to your liking, but it should at least
   contain the root `toctree` directive.

CxSystem2
=========
CxSystem2 is a simulation framework for cortical networks, which operates on personal computers. It is implemented in Python
on top of the popular `Brian2 simulator <https://brian2.readthedocs.io/en/stable/index.html>`_, and runs on Linux,
Windows and MacOS. There is also a :ref:`web-based version <usingbsp>` available via
the Human Brain Project `Brain Simulation Platform (BSP) <https://www.humanbrainproject.eu/en/brain-simulation/brain-simulation-platform/>`_.

CxSystem2 embraces the main goal of Brian -- minimizing development time -- by providing the user with
a simplified interface. While many simple models can be written in pure Brian code, more complex models can get
hard to manage due to the large number of biological details.

We currently provide two interfaces for constructing networks: a browser-based interface (locally or via the BSP),
and a file-based interface (json or csv). Before incorporating neuron models into a network,
the user can explore their behavior using the :ref:`neurodynlib` submodule. Spike output and 3D structure of network simulations can be
visualized using `ViSimpl <http://gmrv.es/gmrvvis/visimpl/>`_, a visualization tool developed by the
`GMRV Lab <http://gmrv.es/gmrvvis/>`_.

More information on the technical details and our motivation is available `here <https://researchportal.helsinki.fi/files/126265396/Andalibi_2019_NECO.pdf>`_.
We have used the simulator to construct `a simplified version of a comprehensive cortical microcircuit
<https://researchportal.helsinki.fi/files/126265461/Hokkanen_2019_NECO.pdf>`_.

The preliminary version of CxSystem2 was developed at the `Aalto University <https://www.aalto.fi/en>`_ in 2012-2015, and
the current version was developed at the `HUS Helsinki University Hospital <https://www.hus.fi/en/Pages/default.aspx>`_ and 
`University of Helsinki <https://www.helsinki.fi/en>`_ in 2013-2019. The software is distributed under the terms of the GNU GPL v3.

Contents:

.. toctree::
   :maxdepth: 2

   introduction
   tutorials
   userguide
   developersguide
   reference


Indices and tables
==================

* :ref:`genindex`
* :ref:`modindex`
* :ref:`search`

