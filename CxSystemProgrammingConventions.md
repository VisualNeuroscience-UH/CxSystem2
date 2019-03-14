# ﻿Programming Conventions for CxSystem2
Understanding how brain process information is a wicked research question, which we can define only by solving it. We don’t know which structures or functions are critical. Thus, easy construction, documentation and evaluation of multiple models is a priority. Complexity must be hidden, while relevant parameters are clearly visualized and easily controlled.

## Basic design:
* Software framework on top of Brian2 simulator
* Revision control in GitHub, documentation (including UML diagrams) in Readthedocs
* Language Python 3 with Brian 2's CUDA and C++ device support and batch job submission to cluster (SLURM) 
* Independent but easily portable to HBP collaboratory, as well as between Linux and windows OSs
* Package management?

## Good design principles:

Minimize connections (modularity) between classes/objects. Isolate changing parts. 
Provide simple interfaces between classes/objects. Hide everything you do not need to expose
Minimize complexity/things to remember at any one time.
Readability counts. Readable code for easy maintenance, “like a book”
Avoid putting in methods because “somebody might need it”
When global variables cannot be avoided, name them consistently and list them in one place

## Conventions for names, comments and layout 
Consider https://www.python.org/dev/peps/pep-0008/ ,
example https://github.com/HumanBrainProject/hbp_archive/blob/master/hbp_archive.py 
Use biological parameter names in user interface; hint/ allowed range by hovering cursor/visible
-ClassName(), method_name(), function_name() ,variable_name, CONSTANTS, modulename, _non_public_method(), _non_public_instance_variable, g_global_variable_name
-for routines and variables use words which describe what is going on
-list input arguments and return variables under routine definitions

How error conditions are handled?
How to test the code?
Which steps to take before integrating to master branch? 

## Main issue with CxSystem: Globals
In several modules, we “from XXX import *” which results in namespace which is cluttered with hard-to-figure-out names. If these are used, it is very difficult to figure out where they came from and how to debug them. It slows down reading the code, and creates unnecessary complexity.
Consider replacing  “from XXX import *” by “import XXX as XX” (eg import numpy as np, import matplotlib.pyplot as plt)
Alternatively “from module import MyClass, YourClass, OurClass, TheirClass”
Or __all__ method for global variables 
Maybe limiting the * import of brian to units?, such as “from brian2.units import *” and otherwise follow above guidelines? “Import brian2 as b2”
Explicit list of used imported global variables at the top of the file?


Version 21st Feb 2019

