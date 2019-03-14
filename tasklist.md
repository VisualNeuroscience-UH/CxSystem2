# CxSystem2 implementation task list 

Here's the suggested task list for implementing `CxSystem2`. The approximate priority of each task is written in front of each task to give some idea of what should be implemented first. Lower number means higher priority. 

## 1) Porting

* P1) [0] Find the answer to this question: 
  * Should we keep the same code structure? i.e. parsing the interface (whatever it is), set existing parameters, create neurongroups, create synapses, run as array or on cluster. 
* P2) [0] Depending on the answer of the P1, a lot of code could be directly copy pasted after considering step P2 and T1, followed by testing using step T2. 

## 2) Improvement 

* I1) [1] Get rid of all `CSV` parsing code and replace it with `json`, this will reduce a lot of errors. Temporarily use a `json` viewer/editor.  Step N1 will significantly improve this step after implementation. Also, replace pandas complex operations (big lines) with simpler `json` equivalent. 
* I2) [1] have a separate file for simulation configuration which contains 8 first lines of anatomy config and the global variables of physiology config. Global variables can then be referred from the anat/physio configs. Thus, the user can specify what will be shown to them when they are running simulations, hiding away the details they don't need to tinker with usually.
* I3) [1] Object-oriented Neuron-models where core functionalities can be inherited & need not be repeated for each neuron model
* I4) [1] This step is somewhere between improvement and new features: Add a sophisticated configuration file validator module. This step is very first important step to make `CxSystem2` error-free as well as having a interactive GUI.

## 3) New Features 

### 3.1) Continuous Integration 

* N1) [0] Create unit tests for `CxSystem` (old) components follow by:
* N2) [0] Start using `CircleCI` (we can use its free plan for more than 1,000 build minutes per month). This is very important in near future when you want to commit your changes and you start thinking maybe this breaks something. Using `CircleCI` you can sleep  well after committing your changes. This will prevent `GeNN` and `C++` standalone devices become broken after 100+ commits ([some link](https://realpython.com/python-continuous-integration/#what-is-continuous-integration)).
  * RULE: if you add feature, write test for it to make sure it works. 

### 3.2) Interface and API

* N3) [1] Create a simple `json` viewer/editor web application interface using flask and integrate it with `CxSystem2`. This can be a completely separate component that accompanies `CxSystem2`, yet it is not a generic `json` viewer/editor as in future will feature error/warning report during changing the parameters. 
* N4) [3] Integration with RTNeuron (Blue Brain Project's visualization tool), it seems that HBP has a whole bunch of visualization software in a separate repo: https://github.com/HBPVIS/ (@Henri, Could you please cherry-pick a few useful ones and put them as separate tasks)
* N5) [4] Support for Neurodata without Borders (NWB): [link](https://www.nwb.org/), [documentation](https://github.com/NeurodataWithoutBorders/pynwb)

### 3.3) Simulator

- N6) [2] eFel -> cost functions -> optimization of single neuron models using experimental traces (Henri please make this more clear for someone like Vafa whose knowledge is limited `=)`. If needed break it into multiple tasks)
- N7) [3] Ability to have multiple apically or basally oriented dendrites (for example L6 bipolar PCs in Markram model have two apical dendrites directed oppositely) (@Henri, please clarify)

### 3.4) Packaging

* N8) [2] Package `CxSystem2` and publish it on `pip` and test it on `pipenv` ([link](https://python-packaging.readthedocs.io/en/latest/minimal.html#creating-the-scaffolding) and [link](https://realpython.com/pipenv-guide/#yes-i-need-to-distribute-my-code-as-a-package)).
* N9) [3] Minimize package requirements 

### 3.5) Cluster and Cloud 

* N10) [0] Re-think array-run and cluster-run implementation and design
* N11) [3] Design `experiment` module which helps managing batch experiments and trials 
* N12) [2] Is some notion of scheduler required? (based on this:  `Slurm interface should divide trials between nodes in the same way it divides array runs. Currently it tries to run all the trials in the first node only.`) 
* N13) [2] Remote Slurm manager module (as a cluster interface), which will keep track of processes (which completed/failed/timed out; how much time it took; how much memory was used), (Slurm workload manager might already be able to report a lot of information, leverage those before implementing from scratch)

## 4) Testing 

T1) [0] Test `Brian2GeNN` and `C++` standalone device and make sure *magic* network is still a must for  using the standalone devices. If so, the same complex global playground is still required, otherwise A LOT of things should be changed to replace that. 

T2) [0] Create a simple test program that run a test on `CxSystem` and saves output and connection values in a file. Then it can test it against another file saved. (to compare `CxSystem` and `CxSystem2` on the same configuration file)

## 5) Documentation

* D1) [2] very simple guide to use CxSystem2 using very light package managers like pipenv and not anaconda 
* D2) [3] Add basic CI and unit test writing documentation
* D3) [3] Document contribution rules
* D4) [3] Document about how to document 

