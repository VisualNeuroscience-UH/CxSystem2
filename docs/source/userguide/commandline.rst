Command-line interface
======================

CxSystem2 has five commands associated with the main functionalities of CxSystem2. Each of this commands have descriptive help commands.

:code:`cxsystem2`
-----------------
This command can be used to run a simulation using anatomy and configuration files:

.. code-block:: console

    $ cxsystem2 -h
    cxsystem2 -- a cortex simulation software

    Usage:
      cxsystem2 (-h | --help)
      cxsystem2 -a ANATOMY_FILE -p PHYSIOLOGY_FILE
      cxsystem2 (-v | --version)

    A cortex simulation framework called `CxSystem`.

    Arguments:
      PORT                                              port number on which the BUI server runs

    Options:
      -h --help                                         Show this screen
      -v --version                                      Show current cxsystem version
      -a ANATOMY_FILE --anatomy=ANATOMY_FILE            Sets the anatomy file path
      -p PHYSIOLOGY_FILE --physiology=PHYSIOLOGY_FILE   Sets the physiology file path


    Description:

      cxsystem2 -a ./anatomy.csv -p ./physiology.csv
        runs the cxsystem using the anatomy file called anatomy.csv and physiology file called physiology.csv

      cxsystem2 --anatomy ./anatomy.csv --physiology ./physiology.csv
        runs the cxsystem using the anatomy file called anatomy.csv and physiology file called physiology.csv


:code:`cxvisualize`
-------------------
This command can be used to visualize the result of a simualtion using :code:`ViSimpl` (avaialble `here <https://gmrv.es/gmrvvis/visimpl/>`__
for download):

.. code-block:: console

    $ cxvisualize -h
    cxvisualize -- cxsystem visualizer

    Usage:
      cxvisualize (-h | --help)
      cxvisualize  [ -d | -c ] FILEPATH
      cxvisualize --rasterplot-pdf FOLDERPATH TIMESTAMP [--sampling-rate SAMPLINGRATE]

    A tool for visualizing `CxSystem` spike data in ViSimpl.

    Arguments:
      FILENAME                                          Path to results file
      FOLDERPATH                                        Path to folder containing array run files
      TIMESTAMP                                         Timestamp suffix of the arrayrun files
      SAMPLINGRATE                                      Sampling rate for the rasterplots

    Options:
      -h --help                                         Show this screen
      --rasterplot-pdf                                  Generate a rasterplot pdf for arrayrun
      -c --convert                                      Convert results for use in ViSimpl
      -d --delete                                       Delete ViSimpl-related files after visualization
      -s SAMPLINGRATE --sampling-rate=SAMPLINGRATE      Sampling rate for raster plot (default is 1%)

    Description:

      cxvisualize ./results.gz
        converts the results file into two CSVs and one JSON for ViSimpl, visualizes the result and does not remove the temp files
        (actual visualization: ./visimpl -csv results_structure.csv results_spikes.csv -se results_subsets.json)

      cxvisualize -d ./results.gz
        converts the results file into two CSVs and one JSON for ViSimpl, visualizes the result and remove the temp files

      cxvisualize -c ./results.gz
        converts the results file into two CSVs and one JSON for ViSimpl (no visualization)

      cxvisualize --rasterplot-pdf ./cobaeif 20191123_1353509
        Generates a pdf of rasterplots of all groups in the folder with 20191123_1353509 timestamp

      cxvisualize --rasterplot-pdf ./cobaeif 20191123_1353509 --sampling-rate=4%
        Generates a pdf of rasterplots of all groups in the folder with timestamp 20191123_1353509 and sampling rate or 4%

:code:`cxconfig`
----------------
CxSystem2 supports both `csv` and `json` file formats for the anatomy and physiology configurations. :code:`cxconfig` can be used
to convert the `json` configuration files to `csv` and vice versa:

.. code-block:: console

    $ cxconfig -h
    cxconfig -- cxsystem config file converter

    Usage:
      cxconfig (-h | --help)
      cxconfig  FILEPATH


    A configuration file converter for `CxSystem`.

    Arguments:
      FILENAME              Path to configuration file to convert

    Options:
      -h --help             Show this screen

    Description:

      cxconfig ./sample_conf.json
        converts the file `sample_conf.json` in current directory to csv and saves it as `sample_conf.csv`

      cxconfig ./sample_conf.csv
        converts the file `sample_conf.csv` in current directory to csv and saves it as `sample_conf.json`

:code:`cxcluster`
-----------------

After submitting jobs to cluster, `CxSystem` stores the data corresponding to the job to a metadata file. To retrieve the results
when they are ready, you can use the :code:`cxcluster` command as follows:

.. code-block:: console

    $ cxcluster -h
    cxcluster -- cxsystem cluster result downloader

    Usage:
      cxcluster (-h | --help)
      cxcluster META_FILE_PATH


    Downloads result data of `CxSystem` from cluster.

    Arguments:
      META_FILE_PATH            Path to cluster run metadata file

    Options:
      -h --help                 Show this screen

    Description:

      cxcluster ./sample_meta.pkl
        Uses the information in the metadata file to download the results if ready, and otherwise wait for the results.
        User will be prompted for the remote password.

:code:`cxserver`
----------------

You can use the :code:`cxserver` command to run the browser user interface of the CxSystem2 in either `http` or `https` mode.
Note that running it in `https` mode requires `oauth` configurations for authentication:

.. code-block:: console

    $ cxserver -h
    cxserver -- web server for cxsystem2

    Usage:
      cxserver (-h | --help)
      cxserver [--port=PORT] [--no-browser]
      cxserver --https [-p PROVIDERID -c CLIENTID -r REDIRECTURI -a AUTHORIZATION] [--port=PORT] [--no-browser]
      cxserver --config -p PROVIDERID -c CLIENTID -r REDIRECTURI -a AUTHORIZATION
      cxserver --config -w WORKSPACEPATH
      cxserver --config -l LOGPATH

    Web server for running the BUI for `cxsystem2`

    Arguments:
      PORT                                              port number on which the BUI server runs
      PROVIDERID                                        provider id for OAuth2 client for authentication
      CLIENTID                                          client id for OAuth2 client for authentication
      REDIRECTURI                                       redirect url for OAuth2 client for authentication
      AUTHORIZATION                                     authorization url for OAuth2 client for authentication
      WORKSPACEPATH                                     path to the main workspace folder
      LOGPATH                                           path to the log folder

    Options:
      -h --help                                         Show this screen
      -v --version                                      Show current cxsystem version
      --https                                           Run server with ssl certificate
      --port=PORT                                       Runs the server on port PORT
      --config                                       Rewrite the oauth config file with the new parameters
      --no-browser                                      Do not open browser after running the server
      -p PROVIDERID --provider-id=PROVIDERID            Sets the provider id
      -c CLIENTID --client-id=CLIENTID                  Sets the client id
      -r REDIRECTURI --redirect-uri=REDIRECTURI         Sets the redirect url
      -a AUTHORIZATION --authorization=AUTHORIZATION    Sets the authorization url
      -w WORKSPACE --workspace-path=WORKSPACE           Sets the workspace path
      -l LOGPATH --log-path=LOGPATH                     Sets the log path

    Description:

      cxserver
        runs the cxsystem2 server without SSL certificate on a random port

      cxserver --port=PORT
        runs the server on a specific port number PORT

      cxserver --https
        runs the cxsystem using the ssl certificate and other parameters previously saved in the configuraiton file using --config

      cxserver --config -p HBP -c f34780ff-7842-499c-8440-5777c28e360d -r https://127.0.0.1:4443 -a https://services.humanbrainproject.eu/oidc/authorize
        config the configuration yaml file with the new oauth parameters

      cxserver --config -w /cxworkspace
        config the configuration yaml file with the new workspace path

      cxserver --config -l /var/log/
        config the configuration yaml file with the new log path
