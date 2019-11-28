Browser User Interface (BUI)
============================

Folder Structure
----------------

For a better understanding of the BUI sub-module, let's first take a
look at the folder structure:

.. code-block:: bash

    ├── __init__.py
    ├── bui.py
    └── cx_bui
        ├── __init__.py
        ├── cx_bui
        │   ├── __init__.py
        │   └── settings.py
        ├── db.sqlite3
        ├── editor
        │   ├── __init__.py
        │   ├── admin.py
        │   ├── apps.py
        │   ├── migrations
        │   ├── models.py
        │   ├── templates
        |   |   └── editor
        |   |       └── index.html
        │   ├── tests.py
        │   ├── urls.py
        │   └── views.py
        ├── examples
        │   ├── cobaeif_anatomy_config.json
        │   ├── cobaeif_physiology_config.json
        │   ├── csv_configs
        │   ├── markram_step1_anatomy_config.json
        │   ├── markram_step1_physiology_config.json
        │   ├── markram_step2_anatomy_config.json
        │   ├── markram_step2_physiology_config.json
        │   ├── pytest_anatomy_config.json
        │   └── pytest_physiology_config.json
        ├── manage.py
        └── static
            ├── css
            ├── images
            └── scripts

The `bui.py` is the main file of the module that includes `RunServer` class.
The top `cx_bui` folder is the main django folder. The `settings.py` under nested `cx_bui` folder, includes the server settings.

The `editor` folder is the main application of the django server. Nested under
these folders, the important files are `views.py` which contain the view
functions. The `urls.py` includes the URLs of the server that have a view in the
`view.py`. The `static` folder contains the html page ingredients, including `css`, `scripts` and `images`. In the next sections, we learn some of the main points for improving CxSystem.

Adding Examples
---------------

The `examples` folder includes all examples that can be loaded on the client
side. Inside `views.py` we have the function that loads the examples and send
them back to the client. Checking the following snippet, we see that the view
looks for the examples based on the file names:

.. code-block:: python

    if config_type == 'anatomy':
        filename = example_name + '_anatomy_config.json'
    else:
        filename = example_name + '_physiology_config.json'

So, to add other examples, the configuration files should be in the following
file name formats:

.. code-block:: bash

    EXAMPLENAME_anatomy_config.json
    EXAMPLENAME_physiology_config.json

After adding the example, you can edit the `index.html` template and add the
example in the `Example` section in the following format:

.. code-block:: html

    <a href="#" onclick="load_example('EXAMPLENAME')">Click here</a> to load the configuration for the EXAMPLENAME.

