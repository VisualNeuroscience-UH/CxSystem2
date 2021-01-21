Continuous Integration
======================

Travis yaml file
----------------

CxSystem2 uses `Travis CI` for continuous integration. The configuration for
`Travis` is available in `.travis.yml` file in the root folder of the
repository. All the details of the `Travis` yaml file is available `here
<https://docs.travis-ci.com/user/customizing-the-build/>`__ in details.

Most of the used parameters are self-explanatory, e.g. `language`, `os`,
`python`. You can install dependencies `before_install` and install using
`install` keyword. You can run different scripts during the tests. We can run
all the tests using `pytest tests`. This way, all the tests that are
subsequently added to the tests folder will be automatically tested in travis.

Encrypted Parameters
--------------------

One might need some encrypted parameters during the testing process, for
instance to run cluster run tests, cluster password is required but cannot be
saved in the configuration file in the plain text. `Travis` provides a command
line client that allows us to encrypt parameters and add them to the
configuration file. Install the client using:

.. code-block:: bash

    sudo gem install travis

Then log into the client:

.. code-block:: bash

    travis login

After logging in and testing it with `travis whoami`, you can add encrypted
parameters to the configuration file:

.. code-block:: bash

    travis encrypt MY_SECRET_ENV=super_secret --add env.global

This way you can encrypt a value in an environment variable which would be
secure on Travis side and use it in the code.


