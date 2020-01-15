#!/usr/bin/env python
'''
CxSystem2 setup script
'''

from setuptools import find_packages, setup


requiers = """
wheel
requests
asn1crypto
bcrypt
brian2
brian2genn
cffi
cryptography
cycler
cython
django
django-extensions
django-sslserver
docopt
ipython
jinja2
kiwisolver
markupsafe
matplotlib
mpmath
numpy
pandas
ping3
paramiko
pycparser
pynacl
pyopenssl
pyparsing
python-dateutil
pycparser
pytz
scipy
scp
six
sqlparse
sympy
werkzeug
sphinx
sphinx-rtd-theme
pyyaml
""".split("\n")


with open('README.md') as f:
    long_description = f.read()
NAME = "cxsystem2"
DESCRIPTION = "A cerebral cortex simulation framework"
AUTHOR = "Vafa Andalibi, Henri Hokkanen, Simo Vanni"
AUTHOR_EMAIL = "vafa.andalibi@gmail.com"
URL = "https://github.com/VisualNeuroscience-UH/CxSystem2"
with open("cxsystem2/__init__.py",'r') as f :
    VERSION = f.readlines()
    VERSION = VERSION[-1]
    VERSION = VERSION.split('=')[1].strip(' ').strip('\n').strip('"')

setup(
    name=NAME,
    author=AUTHOR,
    author_email=AUTHOR_EMAIL,
    description=DESCRIPTION,
    long_description=long_description,
    long_description_content_type="text/markdown",
    version=VERSION,
    license="GPL v3.0",
    url=URL,
    setup_requires=['wheel'],
    python_requires='>=3.5',
    packages=find_packages(),
    classifiers=[
        "Development Status :: 3 - Alpha",
        "Environment :: Win32 (MS Windows)",
        "Environment :: MacOS X",
        "Environment :: X11 Applications",
        "Environment :: Console",
        "Intended Audience :: Information Technology",
        "Intended Audience :: Developers",
        "Intended Audience :: Education",
        "Intended Audience :: Science/Research",
        "License :: OSI Approved :: GNU General Public License v3 (GPLv3)",
        "Natural Language :: English",
        "Operating System :: OS Independent",
        "Operating System :: MacOS",
        "Operating System :: Microsoft :: Windows :: Windows 10",
        "Operating System :: Unix",
        "Programming Language :: Python",
        "Programming Language :: Python :: 3.7",
        "Topic :: Scientific/Engineering",
        "Topic :: Scientific/Engineering :: Medical Science Apps.",
        "Topic :: Software Development :: Libraries",
        "Topic :: Utilities",
    ],
    install_requires=requiers,
    include_package_data=True,
    zip_safe=False,
    entry_points={
        'console_scripts': [
            'cxsystem2 = cxsystem2.cmd.cxsystem_cmd:main',
            'cxconfig = cxsystem2.cmd.cxconfig_cmd:main',
            'cxcluster = cxsystem2.cmd.cxcluster_cmd:main',
            'cxvisualize = cxsystem2.cmd.cxvisualize_cmd:main',
            'cxserver = cxsystem2.cmd.cxserver_cmd:main'
        ],
    }
)
