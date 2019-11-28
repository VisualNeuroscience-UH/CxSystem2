<a href="https://github.com/VisualNeuroscience-UH/CxSystem2/blob/master/README.md"><img src="https://github.com/VisualNeuroscience-UH/CxSystem2/blob/master/data_config/icon/cxsystem_logo.png?sanitize=true" width="50%"></a>

# CxSystem2, A Flexible Cortical Simulation Framework
> Warning: CxSystem2 BUI is developed for using in a local environment and should not be installed on a publicly accessible server unless extra security measures are added on top of it

[![License](https://img.shields.io/badge/License-GPLv3-blue.svg)](https://github.com/VisualNeuroscience-UH/CxSystem2/blob/master/LICENSE)
[![Github Issues](http://img.shields.io/github/issues/VisualNeuroscience-UH/CxSystem2/bug.svg)](https://github.com/VisualNeuroscience-UH/CxSystem2/issues?q=is%3Aopen+is%3Aissue+label%3Abug)
[![Github Issues](http://img.shields.io/github/issues/VisualNeuroscience-UH/CxSystem2/enhancement.svg)](https://github.com/VisualNeuroscience-UH/CxSystem2/issues?q=is%3Aopen+is%3Aissue+label%3Aenhancement)
[![Github Issues](http://img.shields.io/github/issues-pr/VisualNeuroscience-UH/CxSystem2.svg)](https://github.com/VisualNeuroscience-UH/CxSystem2/pulls)
[![Documentation Status](https://readthedocs.org/projects/cxsystem2/badge/?version=latest)](https://cxsystem2.readthedocs.io/en/latest/?badge=latest)
[![PyPI version](https://badge.fury.io/py/cxsystem2.svg)](https://badge.fury.io/py/cxsystem2)
[![Build Status](https://travis-ci.org/VisualNeuroscience-UH/CxSystem2.svg?branch=master)](https://travis-ci.org/VisualNeuroscience-UH/CxSystem2)

## Table of Contents

- [Synopsis](#synopsis)
- [Installation](#installation)
    * [Windows](#windows)
    * [Linux/Mac](#linuxmac)
    * [Development](#development)
- [Interfaces](#interfaces)
    * [Browser User Interface (BUI)](#browser-user-interface-bui)
    * [Command Line Interface (CLI)](#command-line-interface-cli)
- [Documentation](#documentation)
- [Citation](#citation)
- [Support](#support)
- [Team](#team)
- [License](#license)

## Synopsis

CxSystem is a cerebral cortex simulation framework, which operates on personal computers. We have tested the simulation software with a simplified version of a comprehensive cortical microcircuit model [1], which is available as configuration file. 

The CxSystem aims at easy testing and buildup of diverse models at single cell resolution.  Implemented on the top of the Python-based [Brian2 simulator](https://github.com/brian-team/brian2), CxSystem supports the main goal of Brian, i.e. minimizing development time, by providing the user with a simplified interface.

The preliminary version of this software has been developed at Aalto University 2012-2015 [2], and the full version at the University of Helsinki 2013-2017. The software is distributed under the terms of the GNU General Public License, Copyright 2017 Vafa Andalibi, Henri Hokkanen and Simo Vanni.


## Installation

We highly recommend installing `CxSystem2` on a virtual environment. Use the following commands to install a Python3 virtual environment and install CxSystem: 

### Windows

 Make sure you have python 3.5 or above. To create activate a `venv` in windows at `~/CX2` (you can deactivate the environment with the command `deactivate` and reactivate later by running the second command):

```shell
C:\> python --version
Python 3.7.4
C:\> python3 -m venv %userprofile%\CX2
C:\> %userprofile%\CX2\Scripts\activate
(CX2) C:\> pip install --upgrade setuptools
(CX2) C:\> pip install -U cxsystem2
```

Moreover, to use the C++ standalone device on Windows, install the [Visual C++ Build Tools 2015](https://www.microsoft.com/en-us/download/details.aspx?id=48159).

### Linux/Mac

Make sure you have python 3.5 or above. To create activate a `venv` in Linux/Mac at `~/CX2` (you can deactivate the environment with the command `deactivate` and reactivate later by running the second command):

```shell
$ python --version
Python 3.7.4
$ python3 -m venv ~/CX2
$ source ~/CX2/bin/activate
(CX2) $ pip install --upgrade setuptools
(CX2) $ pip install -U cxsystem2
```

### Development

To develop `CxSystem2`, after cloning the repository install it with the following commands:

```shell
(CX2) $ git clone https://github.com/VisualNeuroscience-UH/CxSystem2
(CX2) $ cd CxSystem2
(CX2) $ pip install --upgrade setuptools
(CX2) $ pip install -r requirements.txt
(CX2) $ pip install -U -e .
```

With this method any change to the code will be reflected on the package immediately.

## Interfaces

`CxSystem2` comes with two interfaces:

### Browser User Interface (BUI)

CxSystem's BUI is built to provide users with an interactive environment for changing the parameters for simulations.

### Command Line Interface (CLI)

Beside the BUI, Some of the main functionalities of the `CxSystem2` are available in terminal, including the BUI itself. All of the following commands have built-in documentations available with `-h` or `--help` flags:

#### `cxsystem2`

This command (all in lower letters and case sensitive) can be used to run a simulation locally using anatomy and physiology configuration files.

#### `cxserver`

This command will run the `CxSystem2` BUI django server.

#### `cxconfig`

CxSystem2 supports `csv` and `json` for importing/exporting configuration files. To convert the configuration files, use the `cxconfig` and pass the path to the configuration file path as its argument. This command recognizes the file type and convert it to the alternative extension.

#### `cxcluster`

Use `cxcluster` to download the results from the cluster. `cxcluster` takes in one argument which is the path to the metadata file saved as a result of cluster-run submission. For convenience, at the end of a cluster-run job submission, `CxSystem2` prints the command that should be run to retrieve the result.

#### `cxvisualize`

This command can be used to visualize the result of the simulation using `visimpl` visualizer. ViSimpl binaries are available at the Modeling and Virtual Reality Group [download page](https://gmrv.es/gmrvvis/visimpl/) at  Universidad Rey Juan Carlos and Universidad Politécnica de Madrid. This command can also be used to generate a pdf of rasterplots from a set of simulations.



## Documentation

You can access the documentation of the CxSystem2 at [cxsystem2.readthedocs.io](https://cxsystem2.readthedocs.io).

## Citation

If you use CxSystem2 for your work, we kindly ask you to cite any of our related articles:

```
Andalibi, V., Hokkanen, H., Vanni, S., Controlling complexity of cerebral cortex simulations—I: CxSystem, a flexible cortical simulation framework, 2019, Neural computation
```
<br>

```
Hokkanen, H., Andalibi, V., Vanni, S., Controlling complexity of cerebral cortex simulations—II: Streamlined microcircuits, 2019, Neural computation
```

## Support

You are encouraged to use <a href="https://github.com/VisualNeuroscience-UH/CxSystem2/issues" target="_blank">Github's Issues</a> to report bugs, or request enhancements or new features.

## Team

- [Vafa Andalibi](https://www.andalibi.me)
- [Henri Hokkanen](https://github.com/henhok)
- [Simo Vanni](https://scholar.google.fi/citations?user=nRiUf30AAAAJ&hl=en)

## License

[![License](https://img.shields.io/badge/License-BSD%203--Clause-blue.svg)](https://opensource.org/licenses/BSD-3-Clause)

- **[GPL-3-Clause](https://www.gnu.org/licenses/gpl-3.0.en.html)**
- Copyright 2019 © <a href="http://www.helsinki.fi/visualneuroscience/" target="_blank">HUS Helsinki University Hospital</a>.

***
<sub>[1] Markram, H., Muller, E., Ramaswamy, S., Reimann, M. W., Abdellah, M., Sanchez, C. A., … Schürmann, F. (2015). Reconstruction and Simulation of Neocortical Microcircuitry. Cell, 163(2), 456–492. http://doi.org/10.1016/j.cell.2015.09.029</sub>

<sub>[2]Heikkinen, H., Sharifian, F., Vigário, R., & Vanni, S. (2015). Feedback to distal dendrites links fMRI signals to neural receptive fields in a spiking network model of the visual cortex. Journal of Neurophysiology, 114(1), 57–69. http://doi.org/10.1152/jn.00169.2015</sub>
