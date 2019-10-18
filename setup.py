#!/usr/bin/env python
'''
CxSystem2 setup script
'''

from setuptools import find_packages, setup


requiers = """
brian2
brian2genn
django
matplotlib
pandas
pytest
paramiko
numpy
scipy
scp
""".split("\n")


with open('README.md') as f:
    long_description = f.read()
NAME = "cxsystem2"
DESCRIPTION = "A cerebral cortex simulation framework"
AUTHOR = "Vafa Andalibi, Henri Hokkanen, Simo Vanni"
AUTHOR_EMAIL = "vafa.andalibi@gmail.com"
URL = "https://github.com/VisualNeuroscience-UH/CxSystem2"
VERSION = '0.0-a2'

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
            'cxsystem2 = cxsystem2.core.cxsystem:CxSystem',
        ],
    }
)
