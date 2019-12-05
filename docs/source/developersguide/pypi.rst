`pypi` package
==============

To release a new version of the `cxsystem2` in `pypi`, you should first update
the version. The version of the `cxsystem2` are read from the `__version__`
variable available in `cxsystem2/__init__.py`. If you update this variable,
all other references to the version number will be updated globally.

We will use the following versioning format for the 3rd number, from `software
versioning in wiki <https://en.wikipedia.org/wiki/Software_versioning>`__:

.. code-block:: bash

      0 for alpha (status)
      1 for beta (status)
      2 for release candidate
      3 for (final) release

For instance:

.. code-block:: bash

      1.2.0.1 instead of 1.2-a1
      1.2.1.2 instead of 1.2-b2 (beta with some bug fixes)
      1.2.2.3 instead of 1.2-rc3 (release candidate)
      1.2.3.0 instead of 1.2-r (commercial distribution)
      1.2.3.5 instead of 1.2-r5 (commercial distribution with many bug fixes)

After updating the version number, make sure `twine` package is installed:

.. code-block:: bash

      $ pip install twine

Then go to the root of the repository, and create the new distribution:

.. code-block:: bash

      $ python setup.py sdist bdist_wheel

Finally upload the new package to `pypi`:

.. code-block:: bash

      $ twine upload dist/*

At this point you will be prompted for the username and password for the
`cxsystem2` pypi account.
