Documentation
=============

Visual Studio Code
``````````````````

We strongly suggest to use the `vscode` for updating the documentation. After
installing the `vscode`, add the following useful extensions:

- `Code Spell Checker`: used for spell checking
- `reStructuredText`: shows the format errors in the `rst` files
- `rewrap`: fix the line wrap of a paragraph with `Alt+q` shortcut

At this point all the errors that corresponds to `reStructuredText` format will
be shown in the `vscode`. After adding paragraphs, make sure to press `Alt+q`
so that the long lines are wrapped. You can also go to setting and setting the
`Editor: Word Wrap` to `wordWrapColumn`. However, you will still need to press
`Alt+q` to fix the wrap for `rst` format, otherwise `reStructuredText`
extension will underline the line as a long line (`D001 error`).

Building the documentation
```````````````````````````

We highly recommend building the documentation locally specially when
updating/adding docstrings. After changes to the documentation you can use
`make html` to rebuild the documentation and check the `index.html` to make
sure your changes are reflected correctly.

Sphinx is well documented, yet we will provide the essentials for improving the
documentation of the CxSystem. The documentation for reStructuredText is
available `here <http://www.sphinx-doc.org/en/stable/rest.html>`__.

To build the documentation locally you will need the `sphinx` and
`sphinx-rtd-theme` packages which are already included in the `requirements`.
So if you have created an environment for setting up CxSystem2, you can
activate the environment, otherwise install the packages with `pip`.

When sphinx is installed, you can build the documentation using the following
command:

.. code-block:: bash

   $ cd CxSystem2/docs
   $ make html

After compiling the documentation, you can open the updated local documentation
by opening the following file in the browser:

.. code-block:: bash

   CxSystem2/docs/build/html/index.html

Docstrings and `reference.rst`
``````````````````````````````

Sphinx generates a documentation based on the docstrings of the functions,
methods and classes. The definition of the entities that are parsed are defined
in the `reference.rst`. The following example shows how we can show the target
methods and functions to `sphinx` for parsing:

.. code-block:: rst

      .. module:: cxsystem2.neurodynlib.tools.spike_tools
      .. autoclass:: PopulationSpikeStats
            :members:

            .. automethod:: PopulationSpikeStats.__init__

      .. autofunction:: get_spike_time
      .. autofunction:: get_spike_stats

The first line of this example defines the file that should be parsed. In this
case the filename is `spike_tools.py` and it's located at
`cxsystem2/neurodynlib/tools/spike_tools.py`. The `autoclass` directive defines
the class that should be parsed from that file and the `automethod` defines the
method of that class that should be parsed. In this case only `__init__()` will
be parsed. Next, the `autofunction` directive defines which functions from the
`spike_tools.py` should be parsed.

For the docstrings, make sure to use the `sphinxy` docstring for consistency.
Moreover, make sure at least you include the parameters and return names and
types and the description of the method/function. This is a simple example how
the docstring should be formatted:

.. code-block:: python

      def test_func(name, state=None):

            """This function does something.

            :param name: The name to use.
            :type name: str.
            :param state: Current state to be in.
            :type state: bool.
            :returns:  int -- the return code.
            :raises: AttributeError, KeyError

            """

Lots of more examples of docstrings are available `here <https://pythonhosted.org/an_example_pypi_project/sphinx.html#full-code-example>`__.
