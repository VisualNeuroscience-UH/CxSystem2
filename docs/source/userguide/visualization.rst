Visualization
=============

Visualization of simulation data often requires custom code, but we provide two ways to get a
general idea of the simulated spike data.

rasterplot-pdf
--------------
Rasterplot-pdf allows you to create a pdf file with rasterplots of a batch of simulations.
You can run it using the :code:`cxvisualize` command (:ref:`more on the command <cxvisualize>`).
For example,
to create raster plots of all simulations run on 13 December 2019 at 13:37 in a particular directory,
you can write

.. code-block:: console

    cxvisualize --rasterplot-pdf ~/CxWorkspace/my_simulation/ 20191213_1337

This creates a pdf file with the specified timestamp in the same directory.
Note that this script is very basic and is intended only for screening that there is not a
simple bug in the simulation configuration.

ViSimpl
-------
ViSimpl allows you to visualize the time course and geometry of spiking in a single simulation. First, download the
`ViSimpl binary <http://gmrv.es/gmrvvis/visimpl/>`_ (the .AppImage binary is for Linux and the .dmg binary is for macOS).
Then put the ViSimpl binary in a directory that is located in your system path. Also, remove version
numbering from the binary and make it executable:

.. code-block:: console

    mv visimpl-0.1.4-x86_64.AppImage visimpl.AppImage
    chmod +x visimpl.AppImage

After this you can visualize
CxSystem2 spike data in ViSimpl using the :code:`cxvisualize` :ref:`command <cxvisualize>`:

.. code-block:: console

    cxvisualize ~/CxWorkspace/my_simulation/my_simulation_results.gz

This opens up the ViSimpl main screen. You should be able to rotate the circuit and "play" the simulation
without further configuration. To learn how you can customize the visualization, please see the
`ViSimpl website <http://gmrv.es/gmrvvis/visimpl/>`_.


.. _custom_visualizations:

Custom visualizations
---------------------
Simulation data are stored in dictionaries in the results file. For example, to access spike data in a gzipped file,
you can write:

.. code-block:: python

    import zlib
    import pickle

    fi = open('my_simulation_results.gz', 'rb')
    data_pickle = zlib.decompress(fi.read())
    data = pickle.loads(data_pickle)

    spike_data = data['spikes_all']
    neuron_positions = data['positions_all]

After this, spikes are available in the :code:`spike_data` dictionary indexed by neuron group names.
Then, for each
neuron group, you have a dictionary with arrays :code:`i` (neuron index) and :code:`t` (spike time).

Similarly, neuron positions are available in the :code:`neuron_positions` dictionary containing two
subdictionaries: :code:`w_coord` (cortical position) and :code:`z_coord` (retinal position).
If you are not modelling the visual system, you can ignore the :code:`z_coord` subdictionary.
