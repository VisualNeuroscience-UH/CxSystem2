Neurodynlib
===========

Neurodynlib is a submodule that contains all the point neuron models. It can be used independently of CxSystem2,
for example, inside a Jupyter notebook to explore the behaviour of single neuron models or small networks.
Neurodynlib grew out of the need to understand the behaviour of neuron models before incorporating them
in a larger network.

Neurodynlib is based on the exercise code repository accompanying the book
`Neuronal Dynamics <http://neuronaldynamics.epfl.ch>`_. The code repository can be found
`here <http://github.com/EPFL-LCN/neuronaldynamics-exercises>`_.

The book is also published in print:
Wulfram Gerstner, Werner M. Kistler, Richard Naud, and Liam Paninski.
*Neuronal Dynamics: From Single Neurons to Networks and Models of Cognition*. Cambridge University Press, 2014.

.. _neuron_models:

Available neuron models
-----------------------

The currently supported point neuron models are:

        :code:`LIF`: Leaky integrate-and-fire.

        :code:`EIF`: Exponential integrate-and-fire.

        :code:`ADEX`: Adaptive exponential integrate-and-fire.

        :code:`IZHIKEVICH`: Izhikevich model.

        :code:`LIFASC`: Leaky integrate-and-fire with after-spike currents.


In addition, there is a multicompartmental neuron type (PC, pyramidal cell) that follows exponential integrate-and-fire
dynamics.

.. _receptor_models:

Available receptor models
-------------------------

The currently supported receptor models are:

        :code:`SIMPLE_E`: Excitatory conductance with exponential decay.

        :code:`SIMPLE_I`: Inhibitory conductance with exponential decay.

        :code:`SIMPLE_E_NMDA`: AMPA and NMDA receptors.

        :code:`SIMPLE_I_GABAB`: GABA-A and GABA-B receptors.

        :code:`E_ALPHA`: Excitatory alpha synapse.

        :code:`I_ALPHA`: Inhibitory alpha synapse.