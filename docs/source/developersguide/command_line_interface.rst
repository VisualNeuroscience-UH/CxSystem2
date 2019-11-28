Command Line Interface
======================

CxSystem commands are defined under `cxsystem2/cmd` folder. Each command has a
separate file that includes a main function, which processes the arguments.
Each of those `main` functions are defined as an entry point in the `setup.py`
pypi configuration file:

.. code-block:: python

    entry_points={
        'console_scripts': [
            'cxsystem2 = cxsystem2.cmd.cxsystem_cmd:main',
            'cxconfig = cxsystem2.cmd.cxconfig_cmd:main',
            'cxcluster = cxsystem2.cmd.cxcluster_cmd:main',
            'cxvisualize = cxsystem2.cmd.cxvisualize_cmd:main',
            'cxserver = cxsystem2.cmd.cxserver_cmd:main'
        ],
    }

Another main component of the CLI is the `docopt` strings on top of each of the
files. These strings define the allowed arguments for that command. You can use the current commands as examples to create newer commands, but more examples are also available in the `docopt website <http://docopt.org/>`__.
