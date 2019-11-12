<a href="https://github.com/VisualNeuroscience-UH/CxSystem2/blob/master/README.md"><img src="https://github.com/VisualNeuroscience-UH/CxSystem2/blob/master/data_config/icon/cxsystem_logo.png?sanitize=true" width="60%"></a>

# CxSystem2, A Flexible Cortical Simulation Framework
> Warning: CxSystem2 GUI is developed for using in a local environment and should not be installed on a publicly accessible server unless extra security measures are added on top of it  

[![License](https://img.shields.io/badge/License-GPLv3-blue.svg)](https://github.com/VisualNeuroscience-UH/CxSystem2/blob/master/LICENSE) 
[![Github Issues](http://img.shields.io/github/issues/VisualNeuroscience-UH/CxSystem2/bug.svg)](https://github.com/VisualNeuroscience-UH/CxSystem2/issues?q=is%3Aopen+is%3Aissue+label%3Abug)
[![Github Issues](http://img.shields.io/github/issues/VisualNeuroscience-UH/CxSystem2/enhancement.svg)](https://github.com/VisualNeuroscience-UH/CxSystem2/issues?q=is%3Aopen+is%3Aissue+label%3Aenhancement)
[![Github Issues](http://img.shields.io/github/issues-pr/VisualNeuroscience-UH/CxSystem2.svg)](https://github.com/VisualNeuroscience-UH/CxSystem2/pulls)

## Table of Contents 

- [Synopsis](#synopsis)
- [Installation](#installation)
    * [Windows](#windows)
    * [Linux/Mac](#linuxmac)
- [Supported MUD Abstractions](#features)
- [Contributing](#contributing)
- [Team](#team)
- [FAQ](#faq)
- [Support](#support)
- [License](#license)

## Synopsis

CxSystem is a cerebral cortex simulation framework, which operates on personal computers. We have tested the simulation software with a simplified version of a comprehensive cortical microcircuit model [1], which is available as configuration file. 

The CxSystem aims at easy testing and buildup of diverse models at single cell resolution.  Implemented on the top of the Python-based [Brian2 simulator](https://github.com/brian-team/brian2), CxSystem supports the main goal of Brian, i.e. minimizing development time, by providing the user with a simplified interface.

The preliminary version of this software has been developed at Aalto University 2012-2015 [2], and the full version at the University of Helsinki 2013-2017. The software is distributed under the terms of the GNU General Public License, Copyright 2017 Vafa Andalibi, Henri Hokkanen and Simo Vanni.

To access the documentation of the CxSystem, please check out the [readthedocs page](http://cxsystem.readthedocs.io/en/master/) of the project.
<br></br>
<br></br>

<sub>[1] Markram, H., Muller, E., Ramaswamy, S., Reimann, M. W., Abdellah, M., Sanchez, C. A., … Schürmann, F. (2015). Reconstruction and Simulation of Neocortical Microcircuitry. Cell, 163(2), 456–492. http://doi.org/10.1016/j.cell.2015.09.029</sub>

<sub>[2]Heikkinen, H., Sharifian, F., Vigário, R., & Vanni, S. (2015). Feedback to distal dendrites links fMRI signals to neural receptive fields in a spiking network model of the visual cortex. Journal of Neurophysiology, 114(1), 57–69. http://doi.org/10.1152/jn.00169.2015</sub>

## Installation

We highly recommend installing `CxSystem2` on a virtual environment. Use the following commands to install a Python3 virtual environment and install CxSystem: 

### Windows

 Make sure you have python 3.5 or above. To create activate a `venv` in windows at `~/CX2` (you can deactivate the environment with the command `deactivate` and reactivate later by running the second command): 

```shell
C:\> python --version
Python 3.7.4
C:\> python3 -m venv %userprofile%\CX2
C:\> %userprofile%\CX2\Scripts\activate
(CX2) C:\> pip install cxsystem2
```



### Linux/Mac

Make sure you have python 3.5 or above. To create activate a `venv` in Linux/Mac at `~/CX2` (you can deactivate the environment with the command `deactivate` and reactivate later by running the second command): 

```shell
$ python --version
Python 3.7.4
$ python3 -m venv ~/CX2
$ source ~/CX2/bin/activate
$ pip install cxsystem2 
(CX2) user@DESKTOP:~$ pip install cxsystem2
```

### Development

To develop `CxSystem2`, after creating the repository install it with the following commands: 

```shell
(CX2) $ git clone https://github.com/VisualNeuroscience-UH/CxSystem2
(CX2) $ cd CxSystem2
(CX2) $ pip install -r requirements.txt
(CX2) $ pip install -e . 
```

With this method any change to the code will be reflected on the package immediately. 


# Documentation Status

[![Documentation Status](https://readthedocs.org/projects/cxsystem/badge/?version=master)](http://cxsystem.readthedocs.io/en/master/?badge=master)

