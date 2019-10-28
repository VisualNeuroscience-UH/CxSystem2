#! /usr/bin/env python3
# -*- coding: utf-8 -*-
__author__ = 'Andalibi, V., Hokkanen H., Vanni, S.'

'''
The preliminary version of this software has been developed at Aalto University 2012-2015,
and the full version at the University of Helsinki 2013-2017. The software is distributed
under the terms of the GNU General Public License.
Copyright 2017 Vafa Andalibi, Henri Hokkanen and Simo Vanni.
'''

from cxsystem2.core.physiology_reference import *
from cxsystem2.core.parameter_parser import synapse_parser
from cxsystem2.core.save_data import *
from cxsystem2.core.stimuli import *
import ast
import ntpath
from datetime import datetime
import pickle as pickle
import zlib
import bz2
import time
import builtins
import csv
import shutil
import pandas
import threading
from cxsystem2.hpc import array_run
import multiprocessing
from cxsystem2.core import equation_templates as eqt
from cxsystem2.configuration import config_file_converter as fileconverter
from cxsystem2.gui import gui
from pathlib import Path
from scipy.sparse import csr_matrix

prefs.devices.cpp_standalone.extra_make_args_unix = []

class CxSystem(object):
    '''
    The main object of cortical system module for building and running a customized model of cortical module based on \
    the configuration files.
    '''

    _NeuronGroup_prefix = 'NG'
    _NeuronNumber_prefix = 'NN'
    _NeuronEquation_prefix = 'NE'
    _NeuronThreshold_prefix = 'NT'
    _NeuronReset_prefix = 'NRes'
    _NeuronRef_prefix = 'NRef'
    _NeuronNS_prefix = 'NNs'  # name space prefix
    # _NeuronPos_prefix = 'NPos' # position prefix
    _Synapses_prefix = 'S'
    _SynapsesEquation_prefix = 'SE'
    _SynapsesPre_prefix = 'SPre'
    _SynapsesPost_prefix = 'SPost'
    _SynapsesNS_prefix = 'SNS'
    _SynapticConnection_prefix = 'SC'
    _SynapticWeight_prefix = 'SW'
    _SpikeMonitor_prefix = 'SpMon'
    _StateMonitor_prefix = 'StMon'

    def __init__(self, anatomy_and_system_config=None, physiology_config=None, output_file_suffix = "", instantiated_from_array_run = 0, cluster_run_start_idx=-1,cluster_run_step=-1, array_run_in_cluster =0, gui_port=None):
        '''
        Initialize the cortical system by parsing both of the configuration files.

        :param anatomy_and_system_config: could be either the path to the anatomy and system configuration file, or the dataframe containing the configuration data.
        :param output_path: could be either the path to the physiology configuration file, or the dataframe containing the configuration data.
        :param output_file_suffix: switch the GeNN mode on/off (1/0), by default GeNN is off
        :param instantiated_from_array_run: this flag, 0 by default, determines whether this instance of CxSystem is instantiated from another instance of CxSystem which is running an array run.

        Main internal variables:

        * customized_neurons_list: This list contains the neuron_reference instances. So for each neuron group target line, there would be an element in this list which contains all the information for that particular neuron group.
        * customized_synapses_list: This list contains the synapse_reference instances. Hence, for each synapse custom line, there would be an element in this list, containing all the necessary information.
        * neurongroups_list: This list contains name of the NeuronGroup() instances that are placed in the Globals().
        * synapses_name_list: This list contains name of the Synapses() instances that are placed in the Globals().
        * monitor_name_bank: The dictionary containing the name of the monitors that are defined for any NeuronGroup() or Synapses().
        * default_monitors: In case --> and <-- symbols are used in the configuration file, this default monitor will be applied on all the target lines in between those marks.
        * save_data: The save_data() object for saving the final data.

        '''
        self.port = gui_port
        if anatomy_and_system_config is None or physiology_config is None:
            self.runGUI()
            return

        self.start_time = time.time()
        self.prepare_workspace()
        self.main_module = sys.modules['__main__']
        try:  # try to find the Cxmodule in the sys.modules, to find if the __main__ is CxSystem.py or not
            self.Cxmodule = sys.modules['cxsystem2.core.cxsystem']
        except KeyError:
            pass
        self.parameter_to_method_mapping = {
            ### system parameter definitions:
            #Parameter_name : [set priority (0 is highest),function_to_run]
            'device': [0,self.set_device],
            'save_generated_video_input_flag': [1,self.save_generated_video_input_flag],
            'runtime': [2,self._set_runtime],
            'sys_mode': [3,self._set_sys_mode],  # either "local" or "expanded"
            'scale': [4,self._set_scale],
            'grid_radius': [5,self._set_grid_radius],
            'min_distance': [6,self._set_min_distance],
            'do_init_vms': [7,self.do_init_vms],
            'default_clock': [8, self.set_default_clock],
            'output_path_and_filename': [9,self._set_output_path],
            'connections_saving_path_and_filename': [10,self._set_save_brian_data_path],
            'connections_loading_path_and_filename': [11,self._set_load_brian_data_path],
            'load_positions_only': [12,self.load_positions_only],
            'do_benchmark': [13,self.set_do_benchmark],
            'profiling': [14, self.set_profiling],
            'multidimension_array_run': [15,self.passer],  # this parameter is used by array_run module, so here we just pass
            'number_of_process': [16,self.passer],  # this parameter is used by array_run module, so here we just pass
            'trials_per_config': [17,self.passer],
            'run_in_cluster': [18,self.passer],
            'cluster_job_file_path':[19,self.passer],
            'cluster_number_of_nodes':[20,self.passer],
            'cluster_address': [21,self.passer],
            'username':[22,self.passer],
            'remote_repo_path': [23,self.passer],
            'remote_output_folder': [24,self.passer],
            'integration': [25,self.integration],
            ####
            #### Line definitions:
            'G': [nan,self.neuron_group],
            'S': [nan,self.synapse],
            'IN': [nan,self.relay],
            'params': [nan,self.set_runtime_parameters],
        }
        self.StartTime_str = '_' + str(datetime.now()).replace('-', '').replace(' ', '_').replace(':', '')\
            [0:str(datetime.now()).replace('-', '').replace(' ', '_').replace(':', '').index('.')+3].replace('.','') + output_file_suffix
        print(" -  Current run filename suffix is: %s"%self.StartTime_str[1:])
        self.scale = 1
        self.do_benchmark = 0
        self.cluster_run_start_idx = cluster_run_start_idx
        self.cluster_run_step = cluster_run_step
        self.current_parameters_list = []
        self.current_parameters_list_orig_len = 0 # current_parameters_list is changing at some point in the code, so the original length of it is needed
        self.current_values_list = []
        self.NG_indices = []
        self.customized_neurons_list = []  # This list contains the neuron_reference instances. So for each neuron group target line, there would be an element in this list which contains all the information for that particular neuron group.
        self.customized_synapses_list = []  # This list contains the synapse_reference instances. Hence, for each synapse custom line, there would be an element in this list, containing all the necessary information.
        self.neurongroups_list = []  # This list contains name of the NeuronGroup() instances that are placed in the Globals().
        self.synapses_name_list = []  # This list contains name of the Synapses() instances that are placed in the Globals().
        self.monitor_name_bank = {}  # The dictionary containing the name of the monitors that are defined for any NeuronGroup() or Synapses().
        self.default_monitors = []  # In case --> and <-- symbols are used in the configuration file, this default monitor will be applied on all the target lines in between those marks.
        self.default_save_flag = -1
        self.default_load_flag = -1
        self.monitor_idx = 0
        self.total_synapses = 0
        self.sys_mode = ''
        self.total_number_of_synapses = 0
        self.total_number_of_connections = 0
        self.general_grid_radius = 0
        self.min_distance = 0
        self.do_init_vms = 0
        self.do_save_connections = 0 # if there is at least one connection to save, this flag will be set to 1
        self.load_positions_only = 0
        self.profiling = 0
        self.array_run_in_cluster = array_run_in_cluster
        self.awaited_conf_lines = []



        # self.physio_config_df = pandas.read_csv(physiology_config) if type(physiology_config) == str else physiology_config

        self.physio_config_df = self.read_config_file(physiology_config, header=True)
        self.physio_config_df = self.physio_config_df.applymap(lambda x: NaN if str(x)[0] == '#' else x)

        # self.anat_and_sys_conf_df = pandas.read_csv(anatomy_and_system_config,header=None) if type(anatomy_and_system_config) == str else anatomy_and_system_config
        self.anat_and_sys_conf_df = self.read_config_file(anatomy_and_system_config)
        self.anat_and_sys_conf_df = self.anat_and_sys_conf_df.applymap(lambda x: x.strip() if type(x) == str else x)

        ## dropping the commented lines :
        self.anat_and_sys_conf_df = self.anat_and_sys_conf_df.drop(self.anat_and_sys_conf_df[0].index[self.anat_and_sys_conf_df[0][self.anat_and_sys_conf_df[0].str.contains('#') == True].index.tolist()]).reset_index(drop=True)
        self.physio_config_df = self.physio_config_df.drop(self.physio_config_df['Variable'].index[self.physio_config_df['Variable'][self.physio_config_df['Variable'].str.contains('#') == True].index.tolist()]).reset_index(drop=True)
        # merging the params lines into one row:
        params_indices = where(self.anat_and_sys_conf_df.values == 'params')
        if params_indices[0].size > 1:
            for row_idx in params_indices[0][1:]:
                number_of_new_columns = len(self.anat_and_sys_conf_df.columns)
                number_of_rows = len(self.anat_and_sys_conf_df.index)
                existing_rows = self.anat_and_sys_conf_df.index
                new_columns = list(np.arange(number_of_new_columns, number_of_new_columns * 2))
                empty_dataframe = pandas.DataFrame(index=existing_rows, columns=new_columns)
                new_anat_and_sys_conf_df = pandas.concat([self.anat_and_sys_conf_df, empty_dataframe], axis=1)

                new_anat_and_sys_conf_df.iloc[params_indices[0][0] - 1] = self.anat_and_sys_conf_df.iloc[
                    params_indices[0][0] - 1].dropna().append(
                    self.anat_and_sys_conf_df.iloc[row_idx - 1][1:]).dropna().reset_index(drop=True)
                new_anat_and_sys_conf_df.iloc[params_indices[0][0]] = self.anat_and_sys_conf_df.iloc[
                    params_indices[0][0]].dropna().append(
                    self.anat_and_sys_conf_df.iloc[row_idx][1:]).dropna().reset_index(drop=True)
                self.anat_and_sys_conf_df = new_anat_and_sys_conf_df
            for row in reversed(params_indices[0][1:]):
                self.anat_and_sys_conf_df = self.anat_and_sys_conf_df.drop(row - 1).reset_index(drop=True)
                self.anat_and_sys_conf_df = self.anat_and_sys_conf_df.drop(row - 1).reset_index(drop=True)

        self.conf_df_to_save = self.anat_and_sys_conf_df
        self.physio_df_to_save =  self.physio_config_df
        self.array_run = 0
        try:
            self.numerical_integration_method = self.parameter_finder(self.anat_and_sys_conf_df, 'integration')
        except NameError:
            self.numerical_integration_method = 'euler'
        print(" -  The system is running with %s integration "
               "method"%self.numerical_integration_method)


        check_array_run_anatomy = self.anat_and_sys_conf_df.applymap(lambda x: True if ('|' in str(x) or '&' in str(x)) else False)
        check_array_run_physiology = self.physio_config_df.applymap(lambda x: True if ('|' in str(x) or '&' in str(x)) else False)
        try:
            trials_per_config = int(self.parameter_finder(self.anat_and_sys_conf_df,'trials_per_config'))
        except NameError:
            trials_per_config = 0
        # check for array_run and return
        if any(check_array_run_anatomy) or any(check_array_run_physiology) or (trials_per_config > 1 and not instantiated_from_array_run):
            if self.cluster_run_start_idx != -1 and self.cluster_run_step != -1 : # this means CxSystem is running in cluster and is trying to spawn an array run on a node
                print("spawning index: %d, step: %d" %(int(
                    cluster_run_start_idx),int(cluster_run_step)))
                array_run.array_run(self.anat_and_sys_conf_df, self.physio_config_df, self.StartTime_str, int(cluster_run_start_idx),
                                    int(cluster_run_step), anatomy_and_system_config, physiology_config, array_run_in_cluster=1)
            else: # CxSystem not in cluster
                array_run.array_run(self.anat_and_sys_conf_df, self.physio_config_df, self.StartTime_str, int(cluster_run_start_idx),
                                    int(cluster_run_step), anatomy_and_system_config, physiology_config, array_run_in_cluster=0)
            self.array_run = 1
            return
        try:
            self.conn_prob_gain = int(next(iter(self.physio_config_df.loc[where(self.physio_config_df.values=='conn_prob_gain')[0]]['Value']) , 'no match'))
        except ValueError:
            self.conn_prob_gain =1
        self.configuration_executor()
        if type(self.awaited_conf_lines) != list :
           if self.thr.is_alive()==True:
               print(" -  Waiting for the video input ...")
               self.thr.join()
           self.anat_and_sys_conf_df = self.awaited_conf_lines
           self.configuration_executor()
        print(" -  Cortical Module initialization Done.")

    def runGUI(self):
        gui.runserver(port = self.port)

    def prepare_workspace(self):
        self.workspace_path = Path.home().joinpath('CxWorkspace')
        if not self.workspace_path.is_dir():
            os.makedirs(self.workspace_path.as_posix())

    def configuration_executor(self):
        definition_lines_idx = self.anat_and_sys_conf_df.loc[:,0][self.anat_and_sys_conf_df.loc[:,0]=='row_type'].index
        order_of_lines = ['params','IN','G','S']
        for value_line_title in order_of_lines:
            for def_idx in definition_lines_idx:
                if value_line_title in self.anat_and_sys_conf_df.loc[def_idx+1,0]:
                    self.current_parameters_list = self.anat_and_sys_conf_df.loc[def_idx,1:].dropna()
                    self.current_parameters_list = self.current_parameters_list[~self.current_parameters_list.str.contains('#')]
                    self.current_parameters_list_orig_len = len(self.current_parameters_list)
                    try:
                        next_def_line_idx = definition_lines_idx[definition_lines_idx.tolist().index(def_idx)+1].item()
                    except IndexError:
                        next_def_line_idx = self.anat_and_sys_conf_df[0].__len__()
                    for self.value_line_idx in range(def_idx+1,next_def_line_idx):
                        if type(self.anat_and_sys_conf_df.loc[self.value_line_idx, 0]) == str:
                            if self.anat_and_sys_conf_df.loc[self.value_line_idx,0] in list(self.parameter_to_method_mapping.keys()) and self.anat_and_sys_conf_df.loc[self.value_line_idx, 0][0]!= '#':
                                self.current_parameters_list = self.anat_and_sys_conf_df.loc[def_idx,1:].dropna()
                                self.current_parameters_list = self.current_parameters_list[~self.current_parameters_list.str.contains('#')]
                                self.current_values_list = self.anat_and_sys_conf_df.loc[self.value_line_idx,self.current_parameters_list.index].dropna()
                                self.parameter_to_method_mapping[self.anat_and_sys_conf_df.loc[self.value_line_idx, 0]][1]()
                    break

    def parameter_finder(self,df,keyword):
        location = where(df.values == keyword)
        if location[0].size:
            counter = int(location[0])+1
            while counter < df.shape[0] :
                if '#' not in str(df.loc[counter][int(location[1])]):
                    value = df.loc[counter][int(location[1])]
                    break
                else:
                    counter+=1
            return value
        else:
            raise NameError(' -  Variable %s not found in the configuration file.'%keyword)

    def value_extractor(self, df, key_name):
        non_dict_indices = df['Variable'].dropna()[df['Key'].isnull()].index.tolist()
        for non_dict_idx in non_dict_indices:
            exec("%s=%s" % (df['Variable'][non_dict_idx], df['Value'][non_dict_idx]))
        try:
            return eval(key_name)
        except (NameError, TypeError):
            pass
        try:
            if type(key_name) == list:
                variable_start_idx = df['Variable'][df['Variable'] == key_name[0]].index[0]
                try:
                    variable_end_idx = df['Variable'].dropna().index.tolist()[
                        df['Variable'].dropna().index.tolist().index(variable_start_idx) + 1]
                    cropped_df = df.loc[variable_start_idx:variable_end_idx-1]
                except IndexError:
                    cropped_df = df.loc[variable_start_idx:]
                return eval(cropped_df['Value'][cropped_df['Key'] == key_name[1]].item())
            else:
                return eval(next(iter(df['Value'][df['Key'] == key_name])))
        except NameError:
            new_key = df['Value'][df['Key'] == key_name].item().replace("']", "").split("['")
            return self.value_extractor(df,new_key)
        except ValueError:
            raise ValueError("Parameter %s not found in the configuration file."%key_name)
        except Exception as e:
            print(e)

    def read_config_file(self, conf, header = False):
        '''
        This function reads the file and convert it to csv from json if necessary.
        It only works by loading the csv without headers. (header=none)
        If you need the first row as header, do it manually
        :param conf:
        :return:
        '''
        if type(conf) == str:
            if '.json' in conf.lower():
                converter = fileconverter.filetype_converter(conf)
                data = converter.get_csv()
            else:
                data = pandas.read_csv(conf, header=None)
        else:
            if type(conf) == dict: # it means we've received json data
                converter = fileconverter.filetype_converter(conf)
                data = converter.get_csv_from_json_data()
            else:
                data = conf
        if header is True and (type(conf) == dict or type(conf) == str):
            new_header = data.iloc[0]  # grab the first row for the header
            data = data[1:]  # take the data less the header row
            data.columns = new_header  # set the header row as the df header
        return data

    def set_default_clock(self,*args):
        defaultclock.dt = eval(args[0])
        print(" -  Default clock is set to %s" %str(defaultclock.dt))

    def passer(self,*args):
        pass

    def integration(self,*args):
        self.numerical_integration_method = args[0].lower()
        assert self.numerical_integration_method in ['exact','exponential_euler','euler','rk2','rk4','heun','milstein']


    def set_device(self,*args):
        self.device = args[0]
        assert self.device.lower() in ['cython', 'genn', 'cpp','python'], ' -  Device %s is not defined. ' % self.device
        if self.device.lower() == 'cython':
            self.device = "python"
            prefs.codegen.target = 'cython'
            print(" -  Brian Code Generator set to Cython")
        elif self.device.lower() == 'python':
            self.device = "python"
            prefs.codegen.target = 'numpy'
            print(" -  Brian Code Generator set to Numpy")
        if self.device.lower() == 'genn':
            print(" -  System is going to be run using GeNN devices, " \
                  "Errors may rise if Brian2/Brian2GeNN/GeNN is not installed correctly or the limitations are not " \
                  "taken in to account.")
        print(" -  CxSystem is running on {} device".format(self.device))

    def run(self):
        if not self.array_run:
            run(self.runtime, report='text',profile=True)
            if self.profiling == 1:
                print()
                if len(profiling_summary().names) < 20:
                    print(profiling_summary(show=len(profiling_summary().names)))
                else:
                    print(profiling_summary(show=20))
                self.save_output_data.data['profiling_data'] =  profiling_summary()
            if self.do_benchmark:
                try:
                    self.benchmarking_data = {}
                    titles= ['Computer Name','Device','File Suffix','Simulation Time','Python Compilation','Brian Code generation',\
                             'Device-Specific Compilation','Run','Extract and Save Result','Total Time']
                    self.benchmarking_data['Simulation Time'] = str(self.runtime)
                    self.benchmarking_data['Device'] = self.device
                    self.benchmarking_data['File Suffix'] = self.StartTime_str[1:]
                    if self.device.lower() != 'python':
                        self.benchmarking_data['Python Compilation'] = builtins.code_generation_start - self.start_time
                        self.benchmarking_data['Brian Code generation'] = builtins.compile_start - builtins.code_generation_start
                        self.benchmarking_data['Device-Specific Compilation'] = builtins.run_start - builtins.compile_start
                    else:
                        self.benchmarking_data['Python Compilation'] = builtins.run_start - self.start_time
                        self.benchmarking_data['Brian Code generation'] = '-'
                        self.benchmarking_data['Device-Specific Compilation'] = '-'
                    self.saving_start_time = time.time()
                    self.benchmarking_data['Run'] = self.saving_start_time -  builtins.run_start
                except AttributeError:
                    print(" -  The system could not perform the benchmarking since the brian2/brian2genn libraries are not modified to do so.")
                    self.do_benchmark = 0
            self.gather_result()
            self.end_time = time.time()
            if self.do_benchmark:
                self.benchmarking_data['Extract and Save Result'] = self.end_time - self.saving_start_time
                self.benchmarking_data['Total Time'] = self.end_time - self.start_time
                import platform
                self.benchmarking_data['Computer Name'] = platform.node()
                write_titles = 1 if not os.path.isfile(os.path.join(self.output_folder,'benchmark.csv')) else 0
                with open(os.path.join(self.output_folder,'benchmark.csv'), 'ab') as f:
                    w = csv.DictWriter(f, titles)
                    if write_titles:
                        w.writeheader()
                    w.writerow(self.benchmarking_data)
                    print(" -  Benchmarking data saved")
            print(" -  Simulating %s took in total %f s" % (str(
                self.runtime),self.end_time-self.start_time))
            if self.device.lower() == 'genn':
                shutil.rmtree(os.path.join(self.output_folder, self.StartTime_str[1:]))
            elif self.device.lower() == 'cpp':
                shutil.rmtree(os.path.join(self.output_folder, self.StartTime_str[1:]))

    def set_runtime_parameters(self):
        if not any(self.current_parameters_list.str.contains('runtime')):
            print(" -  Runtime duration is not defined in the configuration "
                   "file. The default runtime duratoin is 500*ms")
            self.runtime = 500*ms
        if not any(self.current_parameters_list.str.contains('device')):
            print(" -  Device is not defined in the configuration file. The "
                   "default device is Python.")
            self.device = 'Python'
        for ParamIdx, parameter in self.current_parameters_list.items():
            if parameter not in list(self.parameter_to_method_mapping.keys()):
                print(" -  System parameter %s not defined." % parameter)
        options_with_priority = [it for it in self.parameter_to_method_mapping if not isnan(self.parameter_to_method_mapping[it][0])]
        parameters_to_set_prioritized = [it for priority_idx in range(len(options_with_priority)) for it in self.parameter_to_method_mapping if self.parameter_to_method_mapping[it][0] == priority_idx]
        for correct_parameter_to_set in parameters_to_set_prioritized:
            for ParamIdx,parameter in self.current_parameters_list.items():
                if parameter == correct_parameter_to_set and str(self.current_values_list[ParamIdx])[0] != '#':
                    assert (parameter in list(self.parameter_to_method_mapping.keys())), ' -  The tag %s is not defined.' % parameter
                    self.parameter_to_method_mapping[parameter][1](self.current_values_list[ParamIdx])
                    break
        if self.sys_mode == '':
            raise NameError(" -  System mode is not defined.")
        else:
            print(" -  CxSystem is running in %s mode" %self.sys_mode)
        if self.do_benchmark:
            print(" -  CxSystem is performing benchmarking. The Brian2 "
                   "should be configured to use benchmarking.")
        if self.device.lower() == 'genn':
            set_device('genn', directory=os.path.join(self.output_folder, self.StartTime_str[1:]))
            prefs.codegen.cpp.extra_compile_args_gcc = ['-O3', '-pipe']
        elif self.device.lower() == 'cpp':
            set_device('cpp_standalone', directory=os.path.join(self.output_folder, self.StartTime_str[1:]))
#            if 'linux' in sys.platform and self.device.lower() == 'cpp':
#                print(" -  parallel compile flag set")
#                prefs['devices.cpp_standalone.extra_make_args_unix'] = ['-j']
#            prefs.codegen.cpp.extra_compile_args_gcc = ['-O3', '-pipe']

    def _set_runtime(self,*args):
        assert '*' in args[0], ' -  Please specify the unit for the runtime parameter, e.g. um , mm '
        self.runtime = eval(args[0])

    def _set_sys_mode(self, *args):
        assert args[0] in ['local','expanded'], " -  System mode should be either local or expanded. "
        self.sys_mode = args[0]

    def save_generated_video_input_flag(self, *args):
        assert int(args[0]) == 0 or int(args[0]) == 1, \
            ' -  The do_init_vm flag should be either 0 or 1 but it is %s .' % args[0]
        self.save_generated_video_input_flag = int(args[0])

    def _set_grid_radius(self, *args):
        assert '*' in args[0], ' -  Please specify the unit for the grid radius parameter, e.g. um , mm '
        self.general_grid_radius = eval(args[0])
        try:
            if self.scale!=1 :
                print(" -  Radius of the system scaled to %s from %s" % (str(
                    sqrt(self.scale)*self.general_grid_radius), str(self.general_grid_radius)))
            self.general_grid_radius = sqrt(self.scale)*self.general_grid_radius
            if self.sys_mode != 'expanded' and self.scale != 1:
                print(' -  System is scaled by factor of %f but the system '
                       'mode is local instead of expanded'%(self.scale))
        except AttributeError:
            pass

    def _set_min_distance(self, *args):
        assert '*' in args[0], ' -  Please specify the unit for the minimum distance parameter, e.g. um , mm '
        self.min_distance = eval(args[0])

    def _set_output_path(self, *args):
        print(" -  setting output path ...")
        self.output_path = args[0]
        output_filename = ntpath.basename(self.output_path)
        assert os.path.splitext(self.output_path)[1], " -  The output_path_and_filename should contain file extension (.gz, .bz2 or .pickle)"
        if self.cluster_run_start_idx == -1 and self.cluster_run_step == -1 and self.array_run_in_cluster==0 :
            self.output_folder = os.path.dirname(self.output_path)
        else: # this means CxSystem is in running in cluster so the output path should be changed to remote_output_path
            print(" -  CxSystem is running in Cluster ... ")
            self.output_folder = self.parameter_finder(self.anat_and_sys_conf_df, 'remote_output_folder')
            self.output_path = os.path.join(self.output_folder,output_filename)
            print(" -  CxSystem knows it's running in cluster and set the "
                   "output folder to : %s"%self.output_path)
        self.output_file_extension = '.'+self.output_path.split('.')[-1]
        self.StartTime_str += '_' + self.device.lower() + '_' + str(int((self.runtime / second) * 1000)) + 'ms'
        self.save_output_data = save_data(self.output_path,self.StartTime_str)  # This is for saving the output
        self.save_output_data.create_key('positions_all')
        self.save_output_data.create_key('Neuron_Groups_Parameters')
        self.save_output_data.data['Anatomy_configuration'] = self.conf_df_to_save
        self.save_output_data.data['Physiology_configuration'] = self.physio_df_to_save
        self.save_output_data.data['time_vector'] = arange(0,self.runtime,defaultclock.dt)
        self.save_output_data.data['positions_all']['w_coord'] = {}
        self.save_output_data.data['positions_all']['z_coord'] = {}
        self.save_output_data.data['number_of_neurons'] = {}
        self.save_output_data.data['runtime'] = self.runtime / self.runtime.get_best_unit()
        self.save_output_data.data['sys_mode'] = self.sys_mode
        try:
            self.save_output_data.data['scale'] = self.scale
        except AttributeError:
            pass

    def _set_load_brian_data_path(self, *args):
        if len(args) > 0 : # arguments exists if the path is to be set, but the loading won't happen until on of the connections needs it
            self.load_brian_data_path = args[0]
            return
        assert os.path.splitext(self.load_brian_data_path)[1], " -  The connections_loading_path_and_filename should contain file extension (.gz, .bz2 or .pickle)"
        self.load_brian_data_filename = ntpath.basename(self.load_brian_data_path)
        self.load_brian_data_folder = ntpath.dirname(self.load_brian_data_path)
        self.load_brian_data_extension = os.path.splitext(self.load_brian_data_path)[1]
        assert any(extension in self.load_brian_data_extension for extension in ['gz','bz2','pickle']), ' -  The extension of the brian_data input/output ' \
                                                         'should be gz, bz2 or pickle but it is %s'%self.load_brian_data_extension
        assert os.path.isfile(os.path.abspath(self.load_brian_data_path)),\
            ' -  The brian_data file cannot be found for loading: {}'.format(os.path.abspath(self.load_brian_data_path))
        if 'gz' in self.load_brian_data_extension:
            with open(self.load_brian_data_path, 'rb') as fb:
                data = zlib.decompress(fb.read())
                self.loaded_brian_data = pickle.loads(data)
        elif 'bz2' in self.load_brian_data_extension:
            with bz2.BZ2File(self.load_brian_data_path, 'rb') as fb:
                self.loaded_brian_data = pickle.load(fb)
        elif 'pickle' in self.load_brian_data_extension:
            with open(self.load_brian_data_path, 'rb') as fb:
                self.loaded_brian_data = pickle.load(fb)
        print(' -  Brian data file loaded from %s'%os.path.abspath(
            self.load_brian_data_path))
        if 'scale' in list(self.loaded_brian_data.keys()):
            self.scale = self.loaded_brian_data['scale']
            print(" -   scale of the system loaded from brian file")

    def _set_save_brian_data_path(self, *args):
        self.save_brian_data_path = args[0]
        assert os.path.splitext(self.save_brian_data_path)[1], " -  The connections_saving_path_and_filename should contain file extension (.gz, .bz2 or .pickle)"
        self.save_brian_data_filename = ntpath.basename(self.save_brian_data_path)
        self.save_brian_data_folder = ntpath.dirname(self.save_brian_data_path)
        self.save_brian_data_extension = os.path.splitext(self.save_brian_data_path)[1]
        assert any(extension in self.save_brian_data_extension for extension in ['gz','bz2','pickle']), ' -  The extension of the brian_data input/output ' \
                                                         'should be gz,bz2 or pickle, but it is %s'%self.save_brian_data_extension
        self.save_brian_data = save_data(self.save_brian_data_path,self.StartTime_str)

    def do_init_vms(self,*args):
        assert int(args[0]) == 0 or int(args[0]) == 1, \
            ' -  The do_init_vm flag should be either 0 or 1 but it is %s .'%args[0]
        self.do_init_vms = int(args[0])
        if self.do_init_vms:
            print(' -  Membrane voltages are being randomly initialized.')
        if not self.do_init_vms:
            print(' -  Membrane voltages are not initialized.')

    def _set_scale(self,*args):
        # if float(args[0])!=1.0:
        self.scale = float(args[0])
        if self.scale != 1 :
            print(" -  CxSystem is being build on the scale of %s" %args[0])

    def load_positions_only(self,*args):
        assert int(args[0]) == 0 or int(args[0]) == 1, ' -  The load_positions_only flag should be either 0 or 1 but it is %s .' % args[0]
        self.load_positions_only = int(args[0])
        if self.load_positions_only:
            self._set_load_brian_data_path()
            print(" -  only positions are being loaded from the brian_data_file")

    def set_do_benchmark(self,*args):
        assert int(args[0]) in [0,1] , " -  Do benchmark flag should be either 0 or 1"
        self.do_benchmark = int(args[0])

    def set_profiling(self,*args):
        assert int(args[0]) in [0,1] , " -  Profiling flag should be either 0 or 1"
        self.profiling = int(args[0])


    def neuron_group(self, *args):
        '''
        The method that creates the NeuronGroups() based on the parameters that are extracted from the configuration file in the __init__ method of the class.

        :param args: This method have at least 3 main positional arguments directly passed from the __init__ method: Number of Neurons in the group, Type of neuron in the group and layer index. Description of the layer index as well as other possible arguments can be found in the configuration file tutorial.

        Main internal variables:

        * mon_args: contains the monitor arguments extracted from the target line.
        * net_center: center position of the neuron group in visual field coordinates, description can be found in configuration file tutorial.
        * _dyn_neurongroup_name: Generated variable name for the NeuronGroup() object in brian2.
        * _dyn_neuronnumber_name: Generated variable name for corresponding Neuron Number.
        * _dyn_neuron_eq_name: Generated variable name for the NeuronGroup() equation.
        * _dyn_neuron_thres_name: Generated variable name for the NeuronGroup() threshold.
        * _dyn_neuron_reset_name: Generated variable name for the NeuronGroup() reset value.
        * _dyn_neuron_refra_name: Generated variable name for the NeuronGroup() refractory value.
        * _dyn_neuron_namespace_name: Generated variable name for the NeuronGroup() namespace.
        * NG_init: NeuronGroups() should be initialized with a random vm, ge and gi values. To address this, a 6-line code is generated and put in this variable, the running of which will lead to initialization of current NeuronGroup().
        '''


        #<editor-fold desc="...Parameter preprocessing">
        assert self.sys_mode != '', " -  System mode is not defined."
        _all_columns = ['idx', 'number_of_neurons', 'neuron_type', 'layer_idx', 'threshold',
                        'reset', 'refractory', 'net_center','monitors', 'tonic_current', 'n_background_inputs',
                        'n_background_inhibition', 'noise_sigma', 'gemean', 'gestd', 'gimean', 'gistd', 'neuron_subtype']
        _obligatory_params = [0, 1, 2, 3]
        assert len(self.current_values_list) <= len(_all_columns), ' -  One or more of of the columns for NeuronGroups definition \
        is missing. Following obligatory columns should be defined:\n%s\n ' \
                                                                % str([_all_columns[ii] for ii in _obligatory_params])
        obligatory_columns = list(array(_all_columns)[_obligatory_params])
        obligatory_indices = [next(iter(self.current_parameters_list[self.current_parameters_list == ii].index)) for ii in obligatory_columns]
        assert not any(self.current_values_list.loc[obligatory_indices] == '--'), \
            ' -  Following obligatory values cannot be "--":\n%s' % str([_all_columns[ii] for ii in _obligatory_params])
        assert len(self.current_values_list) == self.current_parameters_list_orig_len,\
            " -  One or more of of the columns for NeuronGroup definition is missing in the following line:\n %s " % str(list(self.anat_and_sys_conf_df.loc[self.value_line_idx].to_dict().values()))
        local_namespace = {}
        local_namespace['idx'] = -1
        local_namespace['net_center'] = 0 + 0j
        local_namespace['number_of_neurons'] = 0
        local_namespace['tonic_current'] = ''
        local_namespace['n_background_inputs'] = ''
        local_namespace['n_background_inhibition'] = ''
        local_namespace['noise_sigma'] = ''
        local_namespace['gemean'] = ''
        local_namespace['gestd'] = ''
        local_namespace['gimean'] = ''
        local_namespace['gistd'] = ''
        local_namespace['neuron_subtype'] = ''
        local_namespace['neuron_type'] = ''
        local_namespace['layer_idx'] = 0
        local_namespace['threshold'] = ''
        local_namespace['reset'] = ''
        local_namespace['refractory'] = ''
        local_namespace['monitors'] = ''


        for column in _all_columns:
            try:
                tmp_value_idx = int(next(iter(self.current_parameters_list[self.current_parameters_list==column].index), 'no match'))
                tmp_var_str = "local_namespace['%s']=self.current_values_list[tmp_value_idx]" % column
                exec(tmp_var_str)
            except ValueError:
                exec("local_namespace['%s']='--'" % column)

        idx = local_namespace['idx']
        net_center = local_namespace['net_center']
        number_of_neurons = local_namespace['number_of_neurons']
        tonic_current = local_namespace['tonic_current']
        n_background_inputs = local_namespace['n_background_inputs']
        n_background_inhibition = local_namespace['n_background_inhibition']
        noise_sigma = local_namespace['noise_sigma']
        gemean = local_namespace['gemean']
        gestd = local_namespace['gestd']
        gimean = local_namespace['gimean']
        gistd = local_namespace['gistd']
        neuron_type = local_namespace['neuron_type']
        neuron_subtype = local_namespace['neuron_subtype']
        threshold = local_namespace['threshold']
        reset = local_namespace['reset']
        refractory = local_namespace['refractory']
        monitors = local_namespace['monitors']

        assert idx not in self.NG_indices, \
            " -  Multiple indices with same values exist in the configuration file."
        self.NG_indices.append(idx)
        if net_center == '--':
            net_center = 0 + 0j  # center position of the neuron group in visual field coordinates,
            # description can be found in configuration file tutorial.
        net_center = complex(net_center)
        current_idx = len(self.customized_neurons_list)

        if tonic_current == '--':
            tonic_current = '0*pA'

        if noise_sigma == '--':
            noise_sigma = '0*mV'
        noise_sigma = eval(noise_sigma)

        if gemean == '--':
            gemean = '0*nS'
        if gestd == '--':
            gestd = '0*nS'
        if gimean == '--':
            gimean = '0*nS'
        if gistd == '--':
            gistd = '0*nS'

        if n_background_inputs == '--':
            n_background_inputs = '0'
        if n_background_inhibition == '--':
            n_background_inhibition = '0'

        assert 'V' in str(noise_sigma.get_best_unit()), ' -  The unit of noise_sigma should be volt'
        if neuron_type == 'PC':  # extract the layer index of PC neurons separately
            if local_namespace['layer_idx'].isdigit():
                local_namespace['layer_idx'] = local_namespace['layer_idx']
            else:
                local_namespace['layer_idx'] = eval(local_namespace['layer_idx'].replace('->', ',') )
        layer_idx = local_namespace['layer_idx']
        try:
            number_of_neurons = str(int(int(number_of_neurons) * self.scale))
        except AttributeError:
            pass
        #</editor-fold>

        # <editor-fold desc="...Generation of neuron reference">
        self.customized_neurons_list.append(neuron_reference(idx, number_of_neurons, neuron_type,
                                                             layer_idx, self.general_grid_radius, self.min_distance, self.physio_config_df,
                                                             network_center=net_center,cell_subtype=neuron_subtype).output_neuron)  # creating a
        # neuron_reference() object and passing the positional arguments to it. The main member of the class called
        # output_neuron is then appended to customized_neurons_list.
        # in case of threshold/reset/refractory overwrite
        if threshold != '--':
            self.customized_neurons_list[-1]['threshold'] = threshold
        if reset != '--':
            self.customized_neurons_list[-1]['reset'] = reset
        if refractory != '--':
            self.customized_neurons_list[-1]['refractory'] = refractory
        # Generating variable names for Groups, NeuronNumbers, Equations, Threshold, Reset, Refractory and Namespace
        if neuron_subtype == '--':
            _dyn_neurongroup_name = self._NeuronGroup_prefix + str(current_idx) + '_' + neuron_type + '_L' + str(layer_idx).replace\
                (', ', 'toL').replace('[', '').replace(']', '')
        else:
            _dyn_neurongroup_name = self._NeuronGroup_prefix + str(current_idx) + '_' + neuron_subtype + '_L' + str(layer_idx).replace\
                (', ', 'toL').replace('[', '').replace(']', '')
        self.neurongroups_list.append(_dyn_neurongroup_name)
        _dyn_neuronnumber_name = self._NeuronNumber_prefix + str(current_idx)
        _dyn_neuron_eq_name = self._NeuronEquation_prefix + str(current_idx)
        _dyn_neuron_thres_name = self._NeuronThreshold_prefix + str(current_idx)
        _dyn_neuron_reset_name = self._NeuronReset_prefix + str(current_idx)
        _dyn_neuron_refra_name = self._NeuronRef_prefix + str(current_idx)
        _dyn_neuron_namespace_name = self._NeuronNS_prefix + str(current_idx)

        # next  6 line create the variable that are needed for current target line NeuronGroup().
        self.save_output_data.data['Neuron_Groups_Parameters'][_dyn_neurongroup_name] = self.customized_neurons_list[-1]
        self.customized_neurons_list[current_idx]['object_name'] = _dyn_neurongroup_name
        exec("%s=self.customized_neurons_list[%d]['number_of_neurons']" % (_dyn_neuronnumber_name, current_idx))
        exec("%s=self.customized_neurons_list[%d]['equation']" % (_dyn_neuron_eq_name, current_idx))
        exec("%s=self.customized_neurons_list[%d]['threshold']" % (_dyn_neuron_thres_name, current_idx))
        exec("%s=self.customized_neurons_list[%d]['reset']" % (_dyn_neuron_reset_name, current_idx))
        exec("%s=self.customized_neurons_list[%d]['refractory']" % (_dyn_neuron_refra_name, current_idx))
        exec("%s=self.customized_neurons_list[%d]['namespace']" % (_dyn_neuron_namespace_name, current_idx))

        # // Background input code BEGINS
        # Adding tonic current to namespace
        #self.customized_neurons_list[current_idx]['namespace']['tonic_current'] = eval(tonic_current)
        # Adding the noise sigma to namespace
        self.customized_neurons_list[current_idx]['namespace']['noise_sigma'] = noise_sigma
        # Adding ge/gi mean/std to namespace
        self.customized_neurons_list[current_idx]['namespace']['gemean'] = eval(gemean)
        self.customized_neurons_list[current_idx]['namespace']['gestd'] = eval(gestd)
        self.customized_neurons_list[current_idx]['namespace']['gimean'] = eval(gimean)
        self.customized_neurons_list[current_idx]['namespace']['gistd'] = eval(gistd)

        # Creating the actual NeuronGroup() using the variables in the previous 6 lines
        exec("%s= NeuronGroup(%s, model=%s, method='%s', threshold=%s, reset=%s,refractory = %s, namespace = %s)" \
             % (_dyn_neurongroup_name, _dyn_neuronnumber_name, _dyn_neuron_eq_name,self.numerical_integration_method
                ,_dyn_neuron_thres_name, _dyn_neuron_reset_name, _dyn_neuron_refra_name, _dyn_neuron_namespace_name))
        # </editor-fold>

        # <editor-fold desc="...Poisson-distributed background input">
        # Add Poisson-distributed background input

        background_rate = next(iter(self.physio_config_df.loc[where(self.physio_config_df.values == 'background_rate')[0]]['Value']))
        background_rate_inhibition = next(iter(self.physio_config_df.loc[where(self.physio_config_df.values =='background_rate_inhibition')[0]]['Value']))

        # For changing connection weight of background input according to calcium level
        try:
            ca = self.value_extractor(self.physio_config_df, 'calcium_concentration')
        except ValueError:
            ca = 2.0  # default value that doesn't scale connection weights

        try:
            flag_bg_calcium_scaling = self.value_extractor(self.physio_config_df, 'flag_background_calcium_scaling')
        except ValueError:
            flag_bg_calcium_scaling = 0

        bg_synapse = synapse_parser({'type': 'Fixed', 'pre_group_type': 'SS', 'post_group_type': neuron_type},
                                    self.physio_config_df)
        bg_synapse_inh = synapse_parser({'type': 'Fixed', 'pre_group_type': 'BC', 'post_group_type': neuron_type},
                                        self.physio_config_df)

        if neuron_type in ['L1i', 'BC', 'MC']:
            background_weight = self.value_extractor(self.physio_config_df, 'background_E_I_weight')
            background_weight_inhibition = self.value_extractor(self.physio_config_df, 'background_E_I_weight')

            if flag_bg_calcium_scaling == 1:
                background_weight = \
                repr(bg_synapse._scale_by_calcium(ca, background_weight))

                background_weight_inhibition = \
                repr(bg_synapse_inh._scale_by_calcium(ca, background_weight_inhibition))
            else:
                background_weight = repr(background_weight)
                background_weight_inhibition = repr(background_weight_inhibition)

        else:
            background_weight = self.value_extractor(self.physio_config_df, 'background_E_E_weight')
            background_weight_inhibition = self.value_extractor(self.physio_config_df, 'background_I_E_weight')

            if flag_bg_calcium_scaling == 1:
                background_weight = \
                repr(bg_synapse._scale_by_calcium(ca, background_weight))

                background_weight_inhibition = \
                repr(bg_synapse_inh._scale_by_calcium(ca, background_weight_inhibition))
            else:
                background_weight = repr(background_weight)
                background_weight_inhibition = repr(background_weight_inhibition)

        if neuron_type != 'PC':
            try:
                excitation_model = self.value_extractor(self.physio_config_df, 'excitation_model')
            except ValueError:
                excitation_model = 'SIMPLE_E'

            try:
                inhibition_model = self.value_extractor(self.physio_config_df, 'inhibition_model')
            except ValueError:
                inhibition_model = 'SIMPLE_I'

            exc_receptors = eqt.EquationHelper.BackgroundReceptors[excitation_model]
            inh_receptors = eqt.EquationHelper.BackgroundReceptors[inhibition_model]

            # Background excitation for non-PC neurons
            # Go through all excitatory receptors (unfortunately different binomial distrib for every receptor)
            for receptor in exc_receptors:
                poisson_target = 'bg_%s_%s' % (receptor, _dyn_neurongroup_name)
                exec ("%s = PoissonInput(target=%s, target_var='%s_soma', N=%s, rate=%s, weight=%s)" \
                     % (poisson_target, _dyn_neurongroup_name, receptor, n_background_inputs,
                        background_rate, background_weight))

                try:
                    setattr(self.Cxmodule, poisson_target, eval(poisson_target))
                except AttributeError:
                    print('Error in generating PoissonInput')

            # Background inhibition for non-PC neurons
            # Go through all inhibitory receptors
            for receptor in inh_receptors:
                poisson_target_inh = 'bg_%s_%s' % (receptor, _dyn_neurongroup_name)
                exec ("%s = PoissonInput(target=%s, target_var='%s_soma', N=%s, rate=%s, weight=%s)" \
                     % (poisson_target_inh, _dyn_neurongroup_name, receptor, n_background_inhibition,
                        background_rate_inhibition, background_weight_inhibition))
                try:
                    setattr(self.Cxmodule, poisson_target_inh, eval(poisson_target_inh))
                except AttributeError:
                    print('Error in generating PoissonInput')

        else:
            try:
                pc_excitation_model = self.value_extractor(self.physio_config_df, 'pc_excitation_model')
            except ValueError:
                pc_excitation_model = 'SIMPLE_E'
            try:
                pc_inhibition_model = self.value_extractor(self.physio_config_df, 'pc_inhibition_model')
            except ValueError:
                pc_inhibition_model = 'SIMPLE_I'

            exc_receptors = eqt.EquationHelper.BackgroundReceptors[pc_excitation_model]
            inh_receptors = eqt.EquationHelper.BackgroundReceptors[pc_inhibition_model]

            # Background excitation for PC neurons (targeting all dendrite compartments equally)
            n_target_compartments = int(self.customized_neurons_list[-1]['total_comp_num']) -1  # No excitatory input to soma
            n_inputs_to_each_comp = int(int(n_background_inputs) / n_target_compartments)
            target_comp_list = ['basal', 'a0']
            target_comp_list.extend(['a'+str(i) for i in range(1, n_target_compartments-2+1)])

            for receptor in exc_receptors:
                for target_comp in target_comp_list:
                    poisson_target = 'bg_%s_%s_%s' % (receptor, _dyn_neurongroup_name, target_comp)
                    exec ("%s = PoissonInput(target=%s, target_var='%s_%s', N=%s, rate=%s, weight=%s)" \
                     % (poisson_target, _dyn_neurongroup_name, receptor, target_comp, n_inputs_to_each_comp,
                        background_rate, background_weight))
                    try:
                        setattr(self.Cxmodule, poisson_target, eval(poisson_target))
                    except AttributeError:
                        print('Error in generating PoissonInput')

            # Background inhibition for PC neurons (targeting soma)
            for receptor in inh_receptors:
                poisson_target_inh = 'bg_%s_%s' % (receptor, _dyn_neurongroup_name)
                exec ("%s = PoissonInput(target=%s, target_var='%s_soma', N=%s, rate=%s, weight=%s)" \
                     % (poisson_target_inh, _dyn_neurongroup_name, receptor, n_background_inhibition,
                        background_rate_inhibition, background_weight_inhibition))
                try:
                    setattr(self.Cxmodule, poisson_target_inh, eval(poisson_target_inh))
                except AttributeError:
                    print('Error in generating PoissonInput')

        # </editor-fold>

        #<editor-fold desc="...Loading neuron positions">
        if hasattr(self,'loaded_brian_data'):
            # in case the NG index are different.
            # for example a MC_L2 neuron might have had index 3 as NG3_MC_L2 and now it's NG10_MC_L2 :
            Group_type = _dyn_neurongroup_name[_dyn_neurongroup_name.index('_')+1:]
            GroupKeyName =[kk for kk in list(self.loaded_brian_data['positions_all']['w_coord'].keys()) if Group_type in kk][0]
            self.customized_neurons_list[current_idx]['w_positions'] = self.loaded_brian_data['positions_all']['w_coord'][GroupKeyName]
            self.customized_neurons_list[current_idx]['z_positions'] = self.loaded_brian_data['positions_all']['z_coord'][GroupKeyName]
            print(" -  Position for the group %s loaded"
                   %_dyn_neurongroup_name)
        # Setting the position of the neurons in the current NeuronGroup.
        try :
            exec("%s.x=real(self.customized_neurons_list[%d]['w_positions'])*mm\n%s.y=imag(self.customized_neurons_list[%d]['w_positions'])*mm" % (
                _dyn_neurongroup_name, current_idx, _dyn_neurongroup_name, current_idx))
        except ValueError as e:
            raise ValueError(e.message + ' -  You are probably trying to load the positions from a file that does not contain the same number of cells.')
        # Saving the neurons' positions both in visual field and cortical coordinates in save_data() object.
        self.save_output_data.data['positions_all']['z_coord'][_dyn_neurongroup_name] = \
            self.customized_neurons_list[current_idx]['z_positions']
        self.save_output_data.data['positions_all']['w_coord'][_dyn_neurongroup_name] = \
            self.customized_neurons_list[current_idx]['w_positions']
        self.save_output_data.data['number_of_neurons'][_dyn_neurongroup_name] = eval(_dyn_neuronnumber_name)
        # </editor-fold>

        # <editor-fold desc="Initialization of neuron group compartment potentials and conductances">
        # NeuronGroups() should be initialized with a random vm, ge and gi values.
        # To address this, a 6-line code is generated and put in NG_init variable,
        # the running of which will lead to initialization of current NeuronGroup().
        if self.do_init_vms:
            NG_init = 'Vr_offset = rand(len(%s))\n' % _dyn_neurongroup_name
            NG_init += "for _key in %s.variables.keys():\n" % _dyn_neurongroup_name
            NG_init += "\tif _key.find('vm')>=0:\n"
            NG_init += "\t\tsetattr(%s,_key,%s['V_init_min']+Vr_offset * (%s['V_init_max']-%s['V_init_min']))\n" % \
                       (_dyn_neurongroup_name, _dyn_neuron_namespace_name, _dyn_neuron_namespace_name, _dyn_neuron_namespace_name)

            # Commented out (didn't work with receptors) /HH
            # NG_init += "\telif ((_key.find('ge')>=0) or (_key.find('gi')>=0)):\n"
            # NG_init += "\t\tsetattr(%s,_key,0)" % _dyn_neurongroup_name
            exec (NG_init)
        else:
            NG_init = "for _key in %s.variables.keys():\n" % _dyn_neurongroup_name
            NG_init += "\tif _key.find('vm')>=0:\n"
            NG_init += "\t\tsetattr(%s,_key,%s['V_init'])\n" % (_dyn_neurongroup_name, _dyn_neuron_namespace_name)

            # Commented out (didn't work with receptors) /HH
            # NG_init += "\telif ((_key.find('ge')>=0) or (_key.find('gi')>=0)):\n"
            # NG_init += "\t\tsetattr(%s,_key,0)" % _dyn_neurongroup_name
            exec (NG_init)
        # </editor-fold>

        setattr(self.main_module, _dyn_neurongroup_name, eval(_dyn_neurongroup_name))
        try:
            setattr(self.Cxmodule, _dyn_neurongroup_name, eval(_dyn_neurongroup_name))
        except AttributeError:
            pass


        # passing remainder of the arguments to monitors() method to take care of the arguments.
        self.monitors(str(monitors).split(' '), _dyn_neurongroup_name, self.customized_neurons_list[-1]['equation'])

    def monitors(self, mon_args, object_name, equation):
        '''
        This method creates the Monitors() in brian2 based on the parameters that are extracted from a target line in configuration file.

        :param mon_args: The monitor arguments extracted from the target line.
        :param object_name: The generated name of the current object.
        :param equation: The equation of the NeuronGroup() to check if the target variable exist in it.

        Main internal variables:

        * mon_tag: The tag that is extracted from the target line every time.
        * Mon_name: Generated variable name for a specific monitor.
        * Mon_str: The syntax used for building a specific StateMonitor.
        * sub_mon_tags: The tags in configuration file that are specified for a StateMonitor(), e.g. in record=True which is specified by [rec]True in configuration file, [rec] is saved in sub_mon_tags
        * sub_mon_args: The corresponding arguments of sub_mon_tags for a StateMonitor(), e.g. in record=True which is specified by [rec]True in configuration file, True is saved in sub_mon_args.
        '''
        if '--' in mon_args:
            return
        if not mon_args and not self.default_monitors:
            return
        if not mon_args:
            mon_args = self.default_monitors
        # check if default monitor should be applied or not
        if '-->' in mon_args:
            del (mon_args[mon_args.index('-->')])
            self.default_monitors = mon_args
        if '<--' in mon_args:
            del (mon_args[mon_args.index('<--')])
            if not mon_args:
                mon_args = self.default_monitors
            self.default_monitors = []

        monitor_options = {
            '[Sp]': ['SpMon', 'SpikeMonitor'],
            '[St]': ['StMon', 'StateMonitor'],
            '[dt]': [',dt='],
            '[rec]': [',record=']
        }
        self.monitor_name_bank[object_name] = []
        for mon_arg in mon_args:
            # Extracting the monitor tag
            mon_tag = mon_arg[mon_arg.index('['):mon_arg.index(']') + 1]
            assert mon_tag in list(monitor_options.keys()),'%s is not recognized as a type of monitor ' %mon_tag
            mon_arg = mon_arg.replace(mon_tag, '').split('+')
            for sub_mon_arg in mon_arg:  # going through each state variable:
                Mon_str = "=%s(%s" % (str(monitor_options[mon_tag][1]),
                                       object_name) # The syntax used for building a specific StateMonitor.
                sub_mon_tags = []  # The tags in configuration file that are specified for a StateMonitor(), e.g.
                # in record=True which is specified by [rec]True in configuration file, [rec] is saved in sub_mon_tags
                if not ('[' in sub_mon_arg) and sub_mon_arg != '':  # if there is no tag,
                    # it means that the only tag that should be there is record = true
                    sub_mon_arg = sub_mon_arg.split()
                    sub_mon_arg.append('True')
                    sub_mon_tags.append('[rec]')
                else:
                    tag_open_indices = [idx for idx, ltr in enumerate(sub_mon_arg) if
                                        ltr == '[']  # find the start index of all tags
                    tag_close_indices = [idx for idx, ltr in enumerate(sub_mon_arg) if
                                         ltr == ']']  # find the end index of all tags
                    assert len(tag_open_indices) == len(
                        tag_close_indices), ' -  Wrong sets of tagging parentheses in monitor definitions. '
                    for tag_idx in range(len(tag_open_indices)):  # go through each StateMonitor tag:
                        sub_mon_tags.append(sub_mon_arg[sub_mon_arg.index('['):sub_mon_arg.index(']') + 1])
                        sub_mon_arg = sub_mon_arg.replace(sub_mon_tags[tag_idx], ' ')
                    sub_mon_arg = sub_mon_arg.split(' ')
                    if '[rec]' not in sub_mon_tags and sub_mon_arg != ['']:
                        # if some tags exist and [rec] is not present, it means record=True
                        sub_mon_tags.append('[rec]')
                        sub_mon_arg.append('True')
                    elif '[rec]' in sub_mon_tags:
                        sub_mon_arg[sub_mon_tags.index('[rec]')+1] = 'arange'+ sub_mon_arg[sub_mon_tags.index('[rec]')+1].replace('-', ',')
                        if self.scale >= 1:
                            assert int(sub_mon_arg[sub_mon_tags.index('[rec]')+1].split(',')[1]) < \
                                   self.customized_neurons_list[-1]['number_of_neurons'], \
                                " -  The stop index (%d) in the following monitor, is higher than the number of neurons in the group (%d): \n %s " %(int(sub_mon_arg[sub_mon_tags.index('[rec]')+1].split(',')[1]),self.customized_neurons_list[-1]['number_of_neurons'],str(self.current_values_list.tolist()),)
                        elif int(sub_mon_arg[sub_mon_tags.index('[rec]')+1].split(',')[1]) < self.customized_neurons_list[-1]['number_of_neurons']:
                            "\n Warning: The stop index (%d) in the following monitor, is higher than the number of neurons in the group (%d): \n %s . This is caused by using a scale < 1" % (
                            int(sub_mon_arg[sub_mon_tags.index('[rec]') + 1].split(',')[1]),
                            self.customized_neurons_list[-1]['number_of_neurons'],
                            str(self.current_values_list.tolist()),)


                    assert len(sub_mon_arg) == len(sub_mon_tags) + 1, ' -  Error in monitor tag definition.'
                if sub_mon_arg[0] == '':
                    assert mon_tag == '[Sp]', ' -  The monitor state variable is not defined properly'
                    self.save_output_data.create_key('spikes_all')  # Create a key in save_data() object
                    # for that specific StateMonitor variable.
                    Mon_name = monitor_options[mon_tag][0] + str(self.monitor_idx) + '_' + object_name
                    # self.save_output_data.syntax_bank.append(
                    #     "self.save_output_data.data['spikes_all']['%s'] = asarray(%s.it)" % (object_name, Mon_name))
                    self.save_output_data.syntax_bank.append(
                        "self.save_output_data.data['spikes_all']['%s'] = %s.get_states()" % (object_name, Mon_name))
                    Mon_str = Mon_name + Mon_str
                else:
                    self.save_output_data.create_key('%s_all' % sub_mon_arg[0])  # Create a key in save_data()
                    # object for that specific StateMonitor variable.
                    Mon_name = monitor_options[mon_tag][0] + \
                        str(self.monitor_idx) + '_' + object_name + '__' + sub_mon_arg[0]
                    # After simulation, the following syntax will be used to save this specific monitor's result:
                    # self.save_output_data.syntax_bank.append("self.save_output_data.data['%s_all']"
                    #                                          "['%s'] = %s.%s"
                    #                                          %(sub_mon_arg[0], object_name, Mon_name, sub_mon_arg[0]))
                    self.save_output_data.syntax_bank.append("self.save_output_data.data['%s_all']"
                                                             "['%s'] = %s.get_states()"
                                                             %(sub_mon_arg[0], object_name, Mon_name))
                    Mon_str = Mon_name + Mon_str + ",'" + sub_mon_arg[0] + "'"
                    del (sub_mon_arg[0])
                    # add each of the tag and their argument,
                    # e.g. "record" as tag and "True" as argument, to the Mon_str syntax string.
                    for idx, tag in enumerate(sub_mon_tags):
                        Mon_str += monitor_options[tag][0] + sub_mon_arg[idx]

                self.monitor_name_bank[object_name].append(Mon_name)
                Mon_str += ')'
                # create the Monitor() object
                exec(Mon_str)
                setattr(self.main_module, Mon_name, eval(Mon_name))
                try:
                    setattr(self.Cxmodule, Mon_name, eval(Mon_name))
                except AttributeError:
                    pass
                self.monitor_idx += 1

    def synapse(self, *args):
        '''
        The method that creates the Synapses() in brian2, based on the parameters that are extracted from the configuration file in the __init__ method of the class.

        :param args: This method will have at least 4 main positional arguments directly passed from __init__ method: The receptor, e.g. ge or gi, pre-synaptic NeuronGroup index, post synaptic group index, and type of Synaptic connection , i.e. STDP or Fixed. Description of other possible arguments can be found in Configuration file tutorial.

        Main internal variables:

        * mon_args: contains the monitor arguments extracted from the target line.
        * args: normally args contains a set of arguments for a single Synapses() object. However, this changes when the post-synaptic neuron is the first (with index of 0) compartment of a multi-compartmental neuron. In this case, one might intend to target all three sub-compartments, i.e. Basal dendrites, Soma and proximal apical dendrites. So the single set of arguments will be changed to 3 sets of arguments and a for loop will take care of every one of them.
        * dyn_syn_name: Generated variable name for the Synapses() object in brian2.
        * _dyn_syn_eq_name: Generated variable name for the Synapses() equation.
        * _dyn_syn_pre_eq_name: Generated variable name for pre_synaptic equations, i.e. "on_pre=..."
        * _dyn_syn_post_eq_name: Generated variable name for post_synaptic equations, i.e. "on_post= ..."
        * _dyn_syn_namespace_name: Generated variable name for the Synapses() namespace.
        * syn_con_str: The string containing the syntax for connect() method of a current Synapses() object. This string changes depending on using the [p] and [n] tags in the configuration file.
        '''
        _all_columns = ['receptor', 'pre_syn_idx', 'post_syn_idx', 'syn_type', 'p', 'n', 'monitors','load_connection',\
                        'save_connection', 'custom_weight']
        _obligatory_params = [0, 1, 2, 3]
        assert len(self.current_values_list) <= len(_all_columns), \
            ' -  One or more of the obligatory columns for input definition is missing. Obligatory columns are:\n%s\n ' \
                                                                % str([_all_columns[ii] for ii in _obligatory_params])
        obligatory_columns = list(array(_all_columns)[_obligatory_params])
        obligatory_indices = [next(iter(self.current_parameters_list[self.current_parameters_list == ii].index)) for ii in obligatory_columns]
        assert not any(self.current_values_list.loc[obligatory_indices].isnull()), \
            ' -  Following obligatory values cannot be "--":\n%s' % str([_all_columns[ii] for ii in _obligatory_params])
        assert len(self.current_values_list) == self.current_parameters_list_orig_len, \
        " -  One or more of of the columns for synapse definition is missing in the following line:\n %s " %str(list(self.anat_and_sys_conf_df.loc[self.value_line_idx].to_dict().values()))
        _options = {
            '[C]': self.neuron_group,
        }
        # getting the connection probability gain from the namespace and apply it on all the connections:
        index_of_receptor = int(where(self.current_parameters_list.values == 'receptor')[0])
        index_of_post_syn_idx = int(where(self.current_parameters_list.values == 'post_syn_idx')[0])
        index_of_pre_syn_idx = int(where(self.current_parameters_list.values=='pre_syn_idx')[0])
        index_of_syn_type = int(where(self.current_parameters_list.values=='syn_type')[0])
        try:
            index_of_p = int(where(self.current_parameters_list.values == 'p')[0])
        except TypeError:
            pass
        try:
            index_of_n = int(where(self.current_parameters_list.values == 'n')[0])
        except TypeError:
            pass
        try:
            index_of_monitors = int(where(self.current_parameters_list.values == 'monitors')[0])
        except TypeError:
            pass
        current_post_syn_idx = self.current_values_list.values[index_of_post_syn_idx]
        current_pre_syn_idx = self.current_values_list.values[index_of_pre_syn_idx]
        try:
            _current_probs = self.current_values_list.values[index_of_p]
        except (ValueError,NameError):
            pass
        try:
            _current_ns = self.current_values_list.values[index_of_n]
        except (ValueError,NameError):
            pass
        # When the post-synaptic neuron is a multi-compartmental PC neuron:
        if len(current_post_syn_idx) > 1 and '[' in current_post_syn_idx:
            try:
                _current_probs = list(map(float, _current_probs.split('+')))
            except NameError:
                pass
            except ValueError:
                assert _current_probs == '--', \
                    " -  When targeting multiple compartments near soma, their probability should be defined separately. Unless it's marked as '--'"
            try:
                _current_ns = list(map(float,_current_ns.split('+')))
            except NameError:
                pass
            except ValueError:
                assert _current_ns == '--', \
                    " -  When targeting multiple compartments near soma, their number of connections, i.e. 'n', should be defined separately. Unless it's marked as '--'"

            current_post_syn_tags = current_post_syn_idx[current_post_syn_idx.index('['):current_post_syn_idx.index(']') + 1]
            assert current_post_syn_tags in list(_options.keys()), \
                ' -  The synaptic tag %s is not defined.'% current_post_syn_tags
            if current_post_syn_tags == '[C]':  # [C] means the target is a compartment
                _post_group_idx, _post_com_idx = current_post_syn_idx.split('[' + 'C' + ']')
                assert int(_post_group_idx) < len(self.neurongroups_list),\
                ' -  The synapse in the following line is targeting a group index that is not defined:\n%s'%str(list(self.anat_and_sys_conf_df.loc[self.value_line_idx].to_dict().values()))
                self.current_values_list.values[index_of_post_syn_idx] = _post_group_idx
                pre_group_ref_idx = [self.customized_neurons_list.index(tmp_group) for tmp_group in
                                     self.customized_neurons_list if tmp_group['idx'] == int(current_pre_syn_idx)][0]
                post_group_ref_idx = [self.customized_neurons_list.index(tmp_group) for tmp_group in
                                      self.customized_neurons_list if tmp_group['idx'] == int(_post_group_idx)][0]
                assert self.customized_neurons_list[post_group_ref_idx]['type'] == 'PC', \
                    ' -  A compartment is targeted but the neuron group is not PC. Check Synapses in the configuration file.'
                _pre_type = self.customized_neurons_list[pre_group_ref_idx]['type']  # Pre-synaptic neuron type
                _post_type = self.customized_neurons_list[post_group_ref_idx]['type']  # Post-synaptic neuron type
                self.current_parameters_list = self.current_parameters_list.append(pandas.Series(['pre_type', 'post_type','post_comp_name']),ignore_index=True)
                self.current_values_list = self.current_values_list.append(pandas.Series([_pre_type, _post_type]), ignore_index=True)
                #  In case the target is from compartment 0 which has 3 compartments itself
                if str(_post_com_idx)[0] == '0':
                    assert len(_post_com_idx) > 1, \
                        ' -  The soma layer of a compartmental neuron is being targeted, but the exact compartment in the layer is not defined. After 0, use "b" for basal dendrites, "s" for soma and "a" for apical dendrites.'
                    if _current_probs != '--':
                        assert len(_post_com_idx[1:]) == len(_current_probs) , \
                            " -  When targeting multiple compartments near soma, their probability, i.e. 'p', should be defined separately. Unless it's marked as '--'"
                    if _current_ns != '--':
                        assert len(_post_com_idx[1:]) == len(_current_ns), \
                            " -  When targeting multiple compartments near soma, their number of connections, i.e. 'n', should be defined separately. Unless it's marked as '--'"
                    # creating the required synapses for targeting compartment 0, it can be at most 3 synapses (basal,
                    # soma or apical), hence the name triple_args
                    triple_args = []
                    for idx, tmp_idx in enumerate(_post_com_idx[1:]):
                        tmp_args = list(self.current_values_list)
                        if any(self.current_parameters_list.str.contains('p')):
                            tmp_args[index_of_p] = _current_probs[idx] if \
                                str(tmp_args[index_of_p])!= '--' else '--'
                        if any(self.current_parameters_list.str.contains('n')):
                            tmp_args[index_of_n] = _current_ns[idx] if \
                                str(tmp_args[index_of_n])!= '--' else '--'
                        if tmp_idx.lower() == 'b':
                            tmp_args.append('_basal')
                            triple_args.append(tmp_args)
                        elif tmp_idx.lower() == 's':
                            tmp_args.append('_soma')
                            triple_args.append(tmp_args)
                        elif tmp_idx.lower() == 'a':
                            tmp_args.append('_a0')
                            triple_args.append(tmp_args)
                    self.current_values_list = triple_args
                elif int(_post_com_idx) > 0:
                    self.current_values_list = self.current_values_list.append(pandas.Series(['_a' + str(_post_com_idx)]), ignore_index = True)
            if type(self.current_values_list[0]) != list : # type of self.current_values_list[0] would be list in case
                # of multiple synaptic targets in soma area
                self.current_values_list = [self.current_values_list]
        else:
            assert int(current_post_syn_idx) < len(self.neurongroups_list), \
                ' -  The synapse in the following line is targeting a group index that is not defined:\n%s' % str(list(self.anat_and_sys_conf_df.loc[self.value_line_idx].to_dict().values()))
            pre_group_ref_idx = [self.customized_neurons_list.index(tmp_group) for tmp_group in \
                                 self.customized_neurons_list if int(tmp_group['idx']) == \
                                 int(current_pre_syn_idx)][0]
            post_group_ref_idx = [self.customized_neurons_list.index(tmp_group) for tmp_group in \
                                  self.customized_neurons_list if int(tmp_group['idx']) == \
                                  int(current_post_syn_idx)][0]
            _pre_type = self.customized_neurons_list[pre_group_ref_idx]['type']   # Pre-synaptic neuron type
            _post_type = self.customized_neurons_list[post_group_ref_idx]['type']  # Post-synaptic neuron type
            assert _post_type!= 'PC', \
            ' -  The post_synaptic group is a multi-compartmental PC but the target compartment is not selected. Use [C] tag followed by compartment number.'
            self.current_values_list = self.current_values_list.append(pandas.Series([_pre_type, _post_type,'_soma']), ignore_index=True)
            self.current_parameters_list = self.current_parameters_list.append(pandas.Series(['pre_type', 'post_type','post_comp_name']), ignore_index=True)
            self.current_values_list = [self.current_values_list]
        for syn in self.current_values_list:
            receptor = syn[index_of_receptor]
            pre_syn_idx = syn[index_of_pre_syn_idx]
            post_syn_idx = syn[index_of_post_syn_idx]
            syn_type = syn[index_of_syn_type]
            try:
                p_arg = float(syn[index_of_p])*self.conn_prob_gain
            except (ValueError,NameError):
                p_arg = '--'
            try:
                n_arg = syn[index_of_n]
            except (ValueError,NameError):
                n_arg = '--'
            try:
                monitors = syn[index_of_monitors]
            except (ValueError, NameError):
                monitors = '--'
            pre_type_idx = next(iter(self.current_parameters_list[self.current_parameters_list=='pre_type'].index))
            pre_type = syn[pre_type_idx]
            post_type_idx = next(iter(self.current_parameters_list[self.current_parameters_list=='post_type'].index))
            post_type = syn[post_type_idx]
            post_comp_idx = next(iter(self.current_parameters_list[self.current_parameters_list=='post_comp_name'].index))
            post_comp_name= syn[post_comp_idx]

            # Get custom weight if defined
            try:
                custom_weight_idx = next(iter(self.current_parameters_list[self.current_parameters_list=='custom_weight'].index))
                custom_weight = syn[custom_weight_idx]
            except (ValueError, NameError):
                custom_weight = '--'


            # check monitors in line:
            current_idx = len(self.customized_synapses_list)
            # creating a synapse_reference object and passing the positional arguments to it. The main member of
            # the class called output_synapse is then appended to customized_synapses_list:
            self.customized_synapses_list.append(synapse_reference(receptor, pre_syn_idx, post_syn_idx, syn_type,
                                                                   pre_type, post_type, self.physio_config_df, post_comp_name, custom_weight).output_synapse)
            _pre_group_idx = self.neurongroups_list[self.customized_synapses_list[-1]['pre_group_idx']]
            _post_group_idx = self.neurongroups_list[self.customized_synapses_list[-1]['post_group_idx']]
            # Generated variable name for the Synapses(), equation, pre_synaptic and post_synaptic equation and Namespace
            _dyn_syn_name = self._Synapses_prefix + str(current_idx) + '_' + syn_type +'_'+_pre_group_idx + '__to__' +_post_group_idx
            self.synapses_name_list.append(_dyn_syn_name)
            _dyn_syn_eq_name = self._SynapsesEquation_prefix + str(current_idx)
            _dyn_syn_pre_eq_name = self._SynapsesPre_prefix + str(current_idx)
            _dyn_syn_post_eq_name = self._SynapsesPost_prefix + str(current_idx)
            _dyn_syn_namespace_name = self._SynapsesNS_prefix + str(current_idx)

            exec("%s=self.customized_synapses_list[%d]['equation']" % (_dyn_syn_eq_name, current_idx))
            exec("%s=self.customized_synapses_list[%d]['pre_eq']" % (_dyn_syn_pre_eq_name, current_idx))
            try:  # in case of a fixed synapse there is no "on_post = ...", hence the pass
                exec("%s=self.customized_synapses_list[%d]['post_eq']" % (_dyn_syn_post_eq_name, current_idx))
            except KeyError:
                pass
            exec("%s=self.customized_synapses_list[%d]['namespace']" % (_dyn_syn_namespace_name, current_idx))

            ### creating the initial synaptic connection :
            try:
                exec("%s = Synapses(%s,%s,model = %s, on_pre = %s, on_post = %s, namespace= %s)" \
                     % (_dyn_syn_name, _pre_group_idx, _post_group_idx,
                        _dyn_syn_eq_name,_dyn_syn_pre_eq_name, _dyn_syn_post_eq_name, _dyn_syn_namespace_name))
            except NameError:  # for when there is no "on_post =...", i.e. fixed connection
                exec("%s = Synapses(%s,%s,model = %s, on_pre = %s, "
                      "namespace= %s)" \
                     % (_dyn_syn_name, _pre_group_idx, _post_group_idx,
                        _dyn_syn_eq_name, _dyn_syn_pre_eq_name, _dyn_syn_namespace_name))

            ###############
            ############### Connecting synapses
            ###############

            # Technical preparations & parameter parsing first
            _syn_ref_name = self.neurongroups_list[int(current_pre_syn_idx)][self.neurongroups_list[int( \
                current_pre_syn_idx)].index('_')+1:] + "__to__" + self.neurongroups_list[self.\
                customized_synapses_list[-1]['post_group_idx']][self.neurongroups_list[self.\
                customized_synapses_list[-1]['post_group_idx']].index('_') + 1:] + \
                            self.customized_synapses_list[-1]['post_comp_name']
            try:
                index_of_load_connection = int(where(self.current_parameters_list.values == 'load_connection')[0])
                if '-->' in syn[index_of_load_connection ]:
                    self.default_load_flag = int(syn[index_of_load_connection ].replace('-->',''))
                elif '<--' in syn[index_of_load_connection ]:
                    self.default_load_flag = -1
                    _do_load = int(syn[index_of_load_connection].replace('<--', ''))
                    if _do_load ==1:
                        assert hasattr(self,'loaded_brian_data'), " -  Synaptic connection in the following line is set to be loaded, however the load_brian_data_path is not defined in the parameters. The connection is being created:\n%s"%str(list(self.anat_and_sys_conf_df.loc[self.value_line_idx].to_dict().values()))
                else:
                    load_connection_idx = next(iter(self.current_parameters_list[self.current_parameters_list=='load_connection'].index), 'no match')
                    _do_load = int(syn[load_connection_idx])
            except TypeError:
                _do_load = 0
                pass

            if (self.default_load_flag==1 or (self.default_load_flag==-1 and _do_load == 1 )) and not hasattr(self,'loaded_brian_data'):
                ## only load the file if it's not loaded already, and if the connections are supposed to tbe loaded frmo the file
                self._set_load_brian_data_path()

            try:
                index_of_save_connection = int(where(self.current_parameters_list.values=='save_connection')[0])
                if '-->' in syn[index_of_save_connection]:
                    self.default_save_flag = int(syn[index_of_save_connection].replace('-->',''))
                elif '<--' in syn[index_of_save_connection]:
                    self.default_save_flag = -1
                    _do_save = int(syn[index_of_save_connection].replace('<--', ''))
                else:
                    _do_save = int(syn[index_of_save_connection])
            except TypeError:
                _do_save = 0
                pass

            # Loading connections from file
            if (self.default_load_flag==1 or (self.default_load_flag==-1 and _do_load == 1 )) and \
                    hasattr(self,'loaded_brian_data') and not self.load_positions_only:
                assert _syn_ref_name in list(self.loaded_brian_data.keys()), \
                    " -  The data for the following connection was not found in the loaded brian data: %s" % _syn_ref_name

                # 1) Try-except necessary; run fails if no connections exist from 1 group to another
                # 2) Indexing changed in pandas >0.19.1 and thus ...['data'][0][0].tocoo() --> ...['data'].tocoo()
                #    Unfortunately pandas doesn't warn about this change in indexing
                try:
                    eval(_dyn_syn_name).connect(i=self.loaded_brian_data[_syn_ref_name]['data'].tocoo().row, \
                                         j=self.loaded_brian_data[_syn_ref_name]['data'].tocoo().col,\
                                         n = int(self.loaded_brian_data[_syn_ref_name]['n']))
                    # Weight is redeclared later, see line ~1200.
                    # Also, 1) "loading connections" leaves the impression of loading anatomical connections, not synaptic weights
                    #       2) we do not have need for saving/loading synaptic weights at this point
                    #       3) it doesn't work in pandas >0.19.1
                    # Therefore I commented:
                    # eval(_dyn_syn_name).wght = repeat(self.loaded_brian_data[_syn_ref_name]['data'][0][0].data/int(self.\
                    #     loaded_brian_data[_syn_ref_name]['n']),int(self.loaded_brian_data[_syn_ref_name]['n'])) * siemens
                    _load_str = 'Connection loaded from '
                except ValueError:
                    _load_str = ' ! No connections from '

            elif (self.default_load_flag==1 or (self.default_load_flag==-1 and _do_load == 1 )) and not \
                    hasattr(self,'loaded_brian_data') :
                print(" -  Synaptic connection is set to be loaded, however "
                       "the load_brian_data_path is not defined in the "
                       "parameters. The connection is being created.")

            # Generating new connections using
            #  - connection probability ("local mode")
            #  - connection probability scaled with distance ("expanded mode")
            #  - custom connection rule
            else:
                syn_con_str = "%s.connect(condition='i!=j', p= " % _dyn_syn_name

                try:
                    if self.sys_mode == 'local':
                        syn_con_str += "'%f'" % float(p_arg)

                    elif self.sys_mode == 'expanded':
                        # syn_con_str += "'%f*exp(-((sqrt((x_pre-x_post)**2+(y_pre-y_post)**2))*%f))/(sqrt((x_pre-x_post) \
                        #    **2+(y_pre-y_post)**2)/mm)'   " % (float(p_arg), self.customized_synapses_list[-1]['ilam'])
                        syn_con_str += "'%f*exp(-((sqrt((x_pre-x_post)**2+(y_pre-y_post)**2))*%f))'" % (
                        float(p_arg), self.customized_synapses_list[-1]['ilam']) # todo the divisoin by the distance is temporarily removed to avoid division by zeros, try to understand what is going on using Hanna's email and if it's needed, add a fixed version

                # If no connection probability is defined, then use "sparseness" values as connection probability and
                # possibly scale with distance
                except ValueError:
                    print(' !  No predefined connection probability, '
                           'using custom connection rule')
                    p_arg = self.customized_synapses_list[-1]['sparseness']

                    if '_relay_vpm' in self.neurongroups_list[int(current_pre_syn_idx)]:
                        syn_con_str += "'%f*exp(-((sqrt((x_pre-x_post)**2+(y_pre-y_post)**2)))/(2*0.025**2))'" \
                                       % (float(p_arg))

                    elif '_relay_spikes' in self.neurongroups_list[int(current_pre_syn_idx)]:

                        # Use exponential decay here
                        print('Exp decay here!')
                        decay_const = 10/mm  # Unit important here to remind of scale
                        syn_con_str += "'%f * exp(-%f * sqrt((x_pre-x_post)**2 + (y_pre-y_post)**2) )'" \
                                       % (float(p_arg), float(decay_const) )

                    elif self.sys_mode == 'local':
                        syn_con_str += "'%f'" % p_arg

                    elif self.sys_mode == 'expanded':
                        # syn_con_str += "'%f*exp(-((sqrt((x_pre-x_post)**2+(y_pre-y_post)**2))*%f))/(sqrt((x_pre-x_post)\
                        # **2+(y_pre-y_post)**2)/mm)'   " % (p_arg, self.customized_synapses_list[-1]['ilam'])
                        syn_con_str += "'%f*exp(-((sqrt((x_pre-x_post)**2+(y_pre-y_post)**2))*%f))'" % (
                        p_arg, self.customized_synapses_list[-1]['ilam']) # todo the divisoin by the distance is temporarily removed to avoid division by zeros, try to understand what is going on using Hanna's email and if it's needed, add a fixed version
                try:
                    syn_con_str += ',n=%d)' % int(n_arg)
                except ValueError:
                    syn_con_str += ')'
                exec(syn_con_str)

            # Weight set again (overrided) here if connections were loaded
            exec("%s.wght=%s['init_wght']" % (_dyn_syn_name,
                                               _dyn_syn_namespace_name) ) #
            # set the weights
            if syn_type == 'STDP': # A more sophisticated if: 'wght0' in self.customized_synapses_list[-1]['equation']
                exec("%s.wght0=%s['init_wght']" % (_dyn_syn_name,
                                                    _dyn_syn_namespace_name)
                      ) # set the weights
            exec("%s.delay=%s['delay']" % (_dyn_syn_name,
                                            _dyn_syn_namespace_name) ) # set
            # the delays
            setattr(self.main_module, _dyn_syn_name, eval(_dyn_syn_name))
            try:
                setattr(self.Cxmodule, _dyn_syn_name, eval(_dyn_syn_name))
            except AttributeError:
                pass

            self.monitors(monitors.split(' '), _dyn_syn_name, self.customized_synapses_list[-1]['equation'])

            if self.device.lower() == 'python' :
                tmp_namespace = {}
                tmp_namespace['num_tmp'] = 0
                exec("tmp_namespace['num_tmp'] = len(%s.i)" % _dyn_syn_name)
                num_tmp =tmp_namespace['num_tmp']
                self.total_number_of_synapses += num_tmp
                try:
                    n_idx = next(iter(self.current_parameters_list[self.current_parameters_list=='n'].index), 'no match')
                    _current_connections = int(num_tmp/float(syn[n_idx])) / len(self.current_values_list)
                except ValueError:
                    print(" -  number of synapses for last connection was "
                           "equal to number of connections")
                    _current_connections = num_tmp
                self.total_number_of_connections += _current_connections
                try:
                    print(" -  %s%s to %s: Number of synapses %d \t Number "
                           "of connections: %d \t Total synapses: %d \t " "Total connections: %d" \
                          %(_load_str ,_pre_group_idx, _post_group_idx,num_tmp,_current_connections, \
                            self.total_number_of_synapses,
                            self.total_number_of_connections))
                except (ValueError, UnboundLocalError):
                    print(" -  Connection created from %s to %s: Number of "
                           "synapses %d \t Number of connections: %d \t Total synapses: %d \t Total connections: %d" \
                      % (_pre_group_idx, _post_group_idx, num_tmp, _current_connections, \
                         self.total_number_of_synapses,
                         self.total_number_of_connections))
            else:
                try:
                    print(" -  %s%s to %s" %(_load_str ,_pre_group_idx,
                                              _post_group_idx))
                except UnboundLocalError:
                    print(" -  Connection created from %s to %s" % (
                        _pre_group_idx, _post_group_idx))
            if (self.default_save_flag == 1 or (self.default_save_flag == -1 and _do_save )) and \
                    hasattr(self, 'save_brian_data_path') :
                self.do_save_connections = 1
                self.save_brian_data.create_key(_syn_ref_name)
                self.save_brian_data.syntax_bank.append('self.save_brian_data.data["%s"]["data"] = \
                csr_matrix((%s.wght[:],(%s.i[:],%s.j[:])),shape=(len(%s.source),len(%s.target)))' \
                                                        %(_syn_ref_name,_dyn_syn_name,_dyn_syn_name,_dyn_syn_name,_dyn_syn_name,_dyn_syn_name))
                self.save_brian_data.syntax_bank.append('self.save_brian_data.data["%s"]["n"] = %d' \
                                                        %(_syn_ref_name,int(n_arg)))
            elif (self.default_save_flag==1 or (self.default_save_flag==-1 and _do_save )) and \
                    not hasattr(self,'save_brian_data_path') :
                raise ValueError(" -  Synaptic connection is set to be saved, however the save_brian_data_path parameter is not defined.")

    def relay(self, *args):
        '''
        The method that creates the relay NeuronGroups based on the parameters that are extracted from the configuration \
        file in the __init__ method of the class. Note that the SpikeGeneratorGroup() does not support the locations and \
        synaptic connection based on the distance between the input, and the target neuron group. For this reason, a "relay"\
         neuron group is created which is directly connected to the SpikeGeneratorGroup(). Unlike SpikeGeneratorGroup() this \
        relay group supports the locations. With this workaround, the synaptic connection between the input and the Neuron group can be implemented \
        based on the distance of the neurons then.

        Note: extracting the input spikes and time sequences for using in a SpikeGeneratorGroup() is done in this method. \
        This procedure needs using a "run()" method in brian2. However, one of the limitations of the Brian2GeNN is that \
        the user cannot use multiple "run()" methods in the whole script. To address this issue, the GeNN device should be \
        set after using the first run(), hence the unusual placement of "set_device('genn')" command in current method.

        Note2: The radius of the VPM input is determined based on the Markram et al. 2015: The radius of the system is 210 um \
        and the number of VPM input is 60 (page 19 of supplements). As for the radius of the VPM input, it is mentioned in the \
         paper (page 462) that "neurons were arranged in 310 mini-columns at horizontal positions". considering the area of the \
         circle with radius of 210um and 60/310 mini-columns, the radius will be equal to 92um.

        :param args: This method will have at least 4 main positional arguments directly passed from __init__ method: path to the input .mat file, and the frequency. Description of other possible arguments can be found in Configuration file tutorial.

        Main internal variables:

        * inp: an instance of stimuli() object from stimuli module.
        * relay_group: the dictionary containing the data for relay NeuronGroup()
        * _dyn_neurongroup_name: Generated variable name for the NeuronGroup() object in brian2.
        * _dyn_neuronnumber_name: Generated variable name for corresponding Neuron Number.
        * _dyn_neuron_eq_name: Generated variable name for the NeuronGroup() equation.
        * _dyn_neuron_thres_name: Generated variable name for the NeuronGroup() threshold.
        * _dyn_neuron_reset_name: Generated variable name for the NeuronGroup() reset value.
        * SGsyn_name: variable name for the Synapses() object that connects SpikeGeneratorGroup() and relay neurons.

        following four variables are build using the load_input_seq() method in stimuli object:

        * spikes_str: The string containing the syntax for Spike indices in the input neuron group.
        * times_str: The string containing the syntax for time indices in the input neuron group.
        * SG_str: The string containing the syntax for creating the SpikeGeneratorGroup() based on the input .mat file.
        * number_of_neurons: The number of neurons that exist in the input .mat file.
        '''
        _dyn_neurongroup_name = ''
        def video(self):
            print(" -  Creating an input based on the video input ...")
            input_mat_path = self.current_values_list[self.current_parameters_list[self.current_parameters_list=='path'].index.item()]
            freq = self.current_values_list[self.current_parameters_list[self.current_parameters_list=='freq'].index.item()]
            inp = stimuli(duration=self.runtime,input_mat_path=input_mat_path,output_folder=self.output_folder, \
                          output_file_suffix = self.StartTime_str ,output_file_extension = self.output_file_extension)
            proc = multiprocessing.Process(target=inp.generate_inputs, args=(freq,))
            proc.start()
            self.video_input_idx =len(self.neurongroups_list)
            self.neurongroups_list.append('awaiting_video_group')

            def waitress(self):
                time.sleep(3)
                while proc.is_alive():
                    time.sleep(1)
                SPK_GENERATOR_SP, SPK_GENERATOR_TI, thread_number_of_neurons = inp.load_input_seq(self.output_folder)
                if not self.save_generated_video_input_flag:
                    print(" - :  generated video output is NOT saved.")
                    os.remove(os.path.join(self.output_folder,'input'+self.StartTime_str+self.output_file_extension))
                SPK_GENERATOR = SpikeGeneratorGroup(thread_number_of_neurons , SPK_GENERATOR_SP, SPK_GENERATOR_TI)
                setattr(self.main_module, 'SPK_GENERATOR', SPK_GENERATOR)
                try:
                    setattr(self.Cxmodule, 'SPK_GENERATOR', SPK_GENERATOR)
                except AttributeError:
                    pass
                # Generated variable name for the NeuronGroup, Neuron_number,Equation, Threshold, Reset
                thread_NG_name = self._NeuronGroup_prefix + str(self.video_input_idx) + '_relay_video'
                self.neurongroups_list[self.video_input_idx] = thread_NG_name
                thread_NN_name = self._NeuronNumber_prefix + str(self.video_input_idx)
                thread_NE_name = self._NeuronEquation_prefix + str(self.video_input_idx)
                thread_NT_name = self._NeuronThreshold_prefix + str(self.video_input_idx)
                thread_NRes_name = self._NeuronReset_prefix + str(self.video_input_idx)
                Eq = """'''emit_spike : 1
                    x : meter
                    y : meter'''"""
                # In order to use the dynamic compiler in a sub-routine, the scope in which the syntax is going to be run
                # should be defined, hence the globals(), locals(). They indicate that the syntaxes should be run in both
                # global and local scope
                exec("%s=%s" % (thread_NN_name, thread_number_of_neurons),
                      globals(), locals())
                exec("%s=%s" % (thread_NE_name, Eq) , globals(), locals())
                exec("%s=%s" % (thread_NT_name, "'emit_spike>=1'") ,
                      globals(), locals())
                exec("%s=%s" % (thread_NRes_name, "'emit_spike=0'") ,
                      globals(), locals())
                exec("%s= NeuronGroup(%s, model=%s,method='%s', "
                      "threshold=%s, reset=%s)" \
                     % (thread_NG_name, thread_NN_name, thread_NE_name,
                        self.numerical_integration_method,thread_NT_name,
                        thread_NRes_name) , globals(), locals())
                if hasattr(self, 'loaded_brian_data'):
                    # in case the NG index are different. for example a MC_L2 neuron might have had
                    # index 3 as NG3_MC_L2 and now it's NG10_MC_L2 :
                    thread_Group_type = thread_NG_name[thread_NG_name.index('_') + 1:]
                    thread_GroupKeyName = \
                    [kk for kk in list(self.loaded_brian_data['positions_all']['w_coord'].keys()) if thread_Group_type in kk][0]
                    self.customized_neurons_list[self.video_input_idx]['w_positions'] = \
                    self.loaded_brian_data['positions_all']['w_coord'][thread_GroupKeyName]
                    self.customized_neurons_list[self.video_input_idx]['z_positions'] = \
                    self.loaded_brian_data['positions_all']['z_coord'][thread_GroupKeyName]
                    print(" -  Position for the group %s loaded" %
                          thread_NG_name)
                else: # load the positions:
                    self.customized_neurons_list[self.video_input_idx]['z_positions'] = squeeze(inp.get_input_positions())
                    self.customized_neurons_list[self.video_input_idx]['w_positions'] = 17 * log(relay_group['z_positions'] + 1)

                # setting the position of the neurons based on the positions in the .mat input file:
                exec("%s.x=real(self.customized_neurons_list[%d]["
                      "'w_positions'])*mm\n" \
                     "%s.y=imag(self.customized_neurons_list[%d]['w_positions'])*mm" % \
                     (thread_NG_name, self.video_input_idx, thread_NG_name,
                      self.video_input_idx) , globals(), locals())
                self.save_output_data.data['positions_all']['z_coord'][thread_NG_name] = \
                    self.customized_neurons_list[self.video_input_idx]['z_positions']
                self.save_output_data.data['positions_all']['w_coord'][thread_NG_name] = \
                    self.customized_neurons_list[self.video_input_idx]['w_positions']
                self.save_output_data.data['number_of_neurons'][thread_NG_name] = eval(thread_NN_name)
                thread_SGsyn_name = 'SGEN_Syn' # variable name for the Synapses() object
                # that connects SpikeGeneratorGroup() and relay neurons.
                exec("%s = Synapses(SPK_GENERATOR, %s, "
                      "on_pre='emit_spike+=1')" % \
                     (thread_SGsyn_name, thread_NG_name) , globals(),
                      locals())# connecting the SpikeGeneratorGroup() and relay group.
                exec("%s.connect(j='i')" % thread_SGsyn_name , globals(),
                      locals()) # SV change
                setattr(self.main_module, thread_NG_name, eval(thread_NG_name))
                setattr(self.main_module, thread_SGsyn_name, eval(thread_SGsyn_name))
                try:
                    setattr(self.Cxmodule, thread_NG_name, eval(thread_NG_name))
                    setattr(self.Cxmodule, thread_SGsyn_name, eval(thread_SGsyn_name))
                except AttributeError:
                    pass
                # taking care of the monitors:
                self.monitors(mons.split(' '), thread_NG_name, self.customized_neurons_list[-1]['equation'])

            input_neuron_group_idx = self.current_values_list[self.current_parameters_list[self.current_parameters_list=='idx'].index.item()]
            syn_lines = self.anat_and_sys_conf_df[self.anat_and_sys_conf_df[0].str.startswith('S') == True]
            input_synaptic_lines = syn_lines[syn_lines[2] == '0']
            row_type_lines = self.anat_and_sys_conf_df.loc[:input_synaptic_lines.index[0]][0].str.startswith('row_type') == True
            synapse_def_line = self.anat_and_sys_conf_df.loc[row_type_lines[row_type_lines == True].index[-1]]
            load_conn_idx = synapse_def_line[synapse_def_line=='load_connection'].index[0]
            save_conn_idx = synapse_def_line[synapse_def_line=='save_connection'].index[0]
            for conn_load_item in input_synaptic_lines[load_conn_idx]:
                if '<--' in conn_load_item or '-->' in conn_load_item:
                    for synaptic_row in range(input_synaptic_lines.index[0]+1 , self.anat_and_sys_conf_df[0].index[-1]):
                        if self.anat_and_sys_conf_df.loc[synaptic_row][0][0]!='#':
                            sign_to_add = '-->' if '-->' in conn_load_item else '<--'
                            self.anat_and_sys_conf_df.loc[input_synaptic_lines.index[0]+1,load_conn_idx] += sign_to_add
                            break
            for conn_save_item in input_synaptic_lines[save_conn_idx]:
                if '<--' in conn_save_item or '-->' in conn_save_item:
                    for synaptic_row in range (input_synaptic_lines.index[0]+1 , self.anat_and_sys_conf_df[0].index[-1]):
                        if self.anat_and_sys_conf_df.loc[synaptic_row][0][0]!='#':
                            sign_to_add = '-->' if '-->' in conn_save_item else '<--'
                            self.anat_and_sys_conf_df.loc[input_synaptic_lines.index[0]+1,save_conn_idx] += sign_to_add
                            break
            self.awaited_conf_lines = synapse_def_line.to_frame().transpose().reset_index(drop=True).append(input_synaptic_lines).reset_index(drop=True)
            self.anat_and_sys_conf_df = self.anat_and_sys_conf_df.drop(input_synaptic_lines.index.tolist()).reset_index(drop=True)
            self.thr = threading.Thread(target = waitress,args=(self,))
            self.thr.start()
            # if inp.file_exist_flag:
            #     self.thr.join()

        def VPM(self): #ventral posteromedial (VPM) thalamic nucleus
            spike_times_idx = next(iter(self.current_parameters_list[self.current_parameters_list=='spike_times'].index))
            spike_times = self.current_values_list[spike_times_idx].replace(' ',',')
            spike_times_list = ast.literal_eval(spike_times[0:spike_times.index('*')])
            spike_times_unit = spike_times[spike_times.index('*')+1:]
            tmp_namespace = {}
            tmp_namespace["spike_times_"] = []
            exec('tmp_namespace ["spike_times_"] = spike_times_list * %s' %(spike_times_unit),
                  locals(), globals())
            spike_times_ = tmp_namespace["spike_times_"]
            try:
                tmp_net_center_idx = next(iter(self.current_parameters_list[self.current_parameters_list=='net_center'].index), 'no match')
                net_center = self.current_values_list[tmp_net_center_idx]
                net_center = complex(net_center)
            except ValueError:
                net_center = 0 + 0j
            num_of_neurons_idx = next(iter(self.current_parameters_list[self.current_parameters_list == 'number_of_neurons'].index))
            number_of_neurons = self.current_values_list[num_of_neurons_idx]
            
            radius_idx = next(iter(self.current_parameters_list[self.current_parameters_list=='radius'].index))
            radius = self.current_values_list[radius_idx]
            print(" -  Creating an input based on the central %s neurons "
                   "..."%number_of_neurons)
            Spikes_Name = 'GEN_SP'
            Time_Name = 'GEN_TI'
            SG_Name = 'GEN'
            spikes_str = 'GEN_SP=tile(arange(%s),%d)'%(number_of_neurons,len(spike_times_))
            times_str = 'GEN_TI = repeat(%s,%s)*%s'%(spike_times[0:spike_times.index('*')],number_of_neurons,spike_times_unit)
            SG_str = 'GEN = SpikeGeneratorGroup(%s, GEN_SP, GEN_TI)'%number_of_neurons
            exec(spikes_str , globals(), locals())  # running the string
            # containing the syntax for Spike indices in the input neuron group.
            exec(times_str , globals(), locals() ) # running the string
            # containing the syntax for time indices in the input neuron group.
            exec(SG_str , globals(), locals())  # running the string
            # containing the syntax for creating the SpikeGeneratorGroup() based on the input .mat file.

            setattr(self.main_module, SG_Name, eval(SG_Name))
            try:
                setattr(self.Cxmodule, SG_Name, eval(SG_Name))
            except AttributeError:
                pass

            _dyn_neurongroup_name = self._NeuronGroup_prefix + str(current_idx) + '_relay_vpm'  # Generated variable name for the NeuronGroup() object in brian2.
            self.neurongroups_list.append(_dyn_neurongroup_name)
            _dyn_neuronnumber_name = self._NeuronNumber_prefix + str(current_idx)  # Generated variable name for corresponding Neuron Number.
            _dyn_neuron_eq_name = self._NeuronEquation_prefix + str(current_idx)  # Generated variable name for the NeuronGroup() equation.
            _dyn_neuron_thres_name = self._NeuronThreshold_prefix + str(current_idx)  # Generated variable name for the NeuronGroup() threshold.
            _dyn_neuron_reset_name = self._NeuronReset_prefix + str(current_idx)  # Generated variable name for the NeuronGroup() reset value.
            Eq = """'''emit_spike : 1
                            x : meter
                            y : meter'''"""
            exec("%s=%s" % (_dyn_neuronnumber_name, number_of_neurons) ,
                  globals(), locals())
            exec("%s=%s" % (_dyn_neuron_eq_name, Eq) , locals(),globals())
            exec("%s=%s" % (_dyn_neuron_thres_name, "'emit_spike>=1'") ,
                  globals(), locals())
            exec("%s=%s" % (_dyn_neuron_reset_name, "'emit_spike=0'") ,
                  globals(), locals())
            exec("%s= NeuronGroup(%s, model=%s, method='%s',threshold=%s, "
                  "reset=%s)" \
                 % (_dyn_neurongroup_name, _dyn_neuronnumber_name,
                    _dyn_neuron_eq_name, self.numerical_integration_method,
                    _dyn_neuron_thres_name, _dyn_neuron_reset_name) , globals(), locals())
            if hasattr(self, 'loaded_brian_data'): # load the positions if available
                # in case the NG index are different. for example a MC_L2 neuron might have had
                # index 3 as NG3_MC_L2 and now it's NG10_MC_L2 :
                Group_type = _dyn_neurongroup_name[_dyn_neurongroup_name.index('_') + 1:]
                GroupKeyName = \
                [kk for kk in list(self.loaded_brian_data['positions_all']['w_coord'].keys()) if Group_type in kk][0]
                self.customized_neurons_list[current_idx]['w_positions'] = self.loaded_brian_data['positions_all']['w_coord'][GroupKeyName]
                self.customized_neurons_list[current_idx]['z_positions'] = self.loaded_brian_data['positions_all']['z_coord'][GroupKeyName]
                print(" -  Positions for the group %s loaded" %
                      _dyn_neurongroup_name)
            else: # generating the positions:
                vpm_customized_neuron = neuron_reference(current_idx, int(number_of_neurons), 'VPM', '0', eval(radius),
                                                         self.min_distance, self.physio_config_df, network_center=net_center)
                self.customized_neurons_list[current_idx]['z_positions'] = vpm_customized_neuron.output_neuron[
                    'z_positions']
                self.customized_neurons_list[current_idx]['w_positions'] = vpm_customized_neuron.output_neuron[
                    'w_positions']
            # setting the position of the neurons:
            exec("%s.x=real(self.customized_neurons_list[%d]["
                  "'w_positions'])*mm\n"\
                 "%s.y=imag(self.customized_neurons_list[%d]['w_positions'])*mm" \
                 %(_dyn_neurongroup_name, current_idx, _dyn_neurongroup_name,
                   current_idx) , globals(), locals())
            # saving the positions :
            self.save_output_data.data['positions_all']['z_coord'][_dyn_neurongroup_name] = \
                self.customized_neurons_list[current_idx]['z_positions']
            self.save_output_data.data['positions_all']['w_coord'][_dyn_neurongroup_name] = \
                self.customized_neurons_list[current_idx]['w_positions']
            self.save_output_data.data['number_of_neurons'][_dyn_neurongroup_name] = eval(_dyn_neuronnumber_name)
            SGsyn_name = 'SGEN_Syn'  # variable name for the Synapses() object
            # that connects SpikeGeneratorGroup() and relay neurons.
            exec("%s = Synapses(GEN, %s, on_pre='emit_spike+=1')" \
                 % (SGsyn_name, _dyn_neurongroup_name) , globals(), locals()
                  ) # connecting the SpikeGeneratorGroup() and relay group.
            eval(SGsyn_name).connect(j='i')
            setattr(self.main_module, _dyn_neurongroup_name, eval(_dyn_neurongroup_name))
            setattr(self.main_module, SGsyn_name, eval(SGsyn_name))
            try:
                setattr(self.Cxmodule, _dyn_neurongroup_name, eval(_dyn_neurongroup_name))
                setattr(self.Cxmodule, SGsyn_name, eval(SGsyn_name))
            except AttributeError:
                pass
            # taking care of the monitors:
            self.monitors(mons.split(' '), _dyn_neurongroup_name,self.customized_neurons_list[-1]['equation'])

        def spikes(self):
            input_spikes_filename = self.current_values_list[self.current_parameters_list[self.current_parameters_list == 'input_spikes_filename'].index.item()]
            spikes_data = self.data_loader(os.path.join(self.output_folder, input_spikes_filename))
            print(" -   Spike file loaded from: %s" %os.path.join(
                self.output_folder, input_spikes_filename))
            SPK_GENERATOR_SP = spikes_data['spikes_0'][0]
            SPK_GENERATOR_TI = spikes_data['spikes_0'][1]
            number_of_neurons =  len(spikes_data['w_coord'])
            SPK_GENERATOR = SpikeGeneratorGroup(number_of_neurons, SPK_GENERATOR_SP, SPK_GENERATOR_TI)
            setattr(self.main_module, 'SPK_GENERATOR', SPK_GENERATOR)
            try:
                setattr(self.Cxmodule, 'SPK_GENERATOR', SPK_GENERATOR)
            except AttributeError:
                pass
            # Generated variable name for the NeuronGroup, Neuron_number,Equation, Threshold, Reset
            self.spike_input_group_idx = len(self.neurongroups_list)
            NG_name = self._NeuronGroup_prefix + str(self.spike_input_group_idx) + '_relay_spikes'
            self.neurongroups_list.append(NG_name)
            NN_name = self._NeuronNumber_prefix + str(self.spike_input_group_idx)
            NE_name = self._NeuronEquation_prefix + str(self.spike_input_group_idx)
            NT_name = self._NeuronThreshold_prefix + str(self.spike_input_group_idx)
            NRes_name = self._NeuronReset_prefix + str(self.spike_input_group_idx)
            Eq = """'''emit_spike : 1
                                x : meter
                                y : meter'''"""
            # In order to use the dynamic compiler in a sub-routine, the scope in which the syntax is going to be run
            # should be defined, hence the globals(), locals(). They indicate that the syntaxes should be run in both
            # global and local scope
            exec("%s=%s" % (NN_name, number_of_neurons) , globals(), locals())
            exec("%s=%s" % (NE_name, Eq) , globals(), locals())
            exec("%s=%s" % (NT_name, "'emit_spike>=1'") , globals(), locals())
            exec("%s=%s" % (NRes_name, "'emit_spike=0'") , globals(),
                  locals())
            exec("%s= NeuronGroup(%s, model=%s,method='%s', threshold=%s, "
                  "reset=%s)" \
                 % (NG_name, NN_name, NE_name, self.numerical_integration_method, NT_name,
                    NRes_name) , globals(), locals())
            if hasattr(self, 'loaded_brian_data'):
                # in case the NG index are different. for example a MC_L2 neuron might have had
                # index 3 as NG3_MC_L2 and now it's NG10_MC_L2 :
                Group_type = NG_name[NG_name.index('_') + 1:]
                GroupKeyName = \
                    [kk for kk in list(self.loaded_brian_data['positions_all']['w_coord'].keys()) if Group_type in kk][
                        0]
                self.customized_neurons_list[self.spike_input_group_idx]['w_positions'] = \
                    self.loaded_brian_data['positions_all']['w_coord'][GroupKeyName]
                self.customized_neurons_list[self.spike_input_group_idx]['z_positions'] = \
                    self.loaded_brian_data['positions_all']['z_coord'][GroupKeyName]
                print(" -  Position for the group %s loaded" % NG_name)
            else:  # load the positions:
                self.customized_neurons_list[self.spike_input_group_idx]['z_positions'] = squeeze(spikes_data['z_coord'])
                self.customized_neurons_list[self.spike_input_group_idx]['w_positions'] = squeeze(spikes_data['w_coord'])

            # setting the position of the neurons based on the positions in the .mat input file:
            exec("%s.x=real(self.customized_neurons_list[%d]["
                  "'w_positions'])*mm\n" \
                 "%s.y=imag(self.customized_neurons_list[%d]['w_positions'])*mm" % \
                 (NG_name, self.spike_input_group_idx, NG_name,
                  self.spike_input_group_idx) , globals(), locals())
            self.save_output_data.data['positions_all']['z_coord'][NG_name] = \
                self.customized_neurons_list[self.spike_input_group_idx]['z_positions']
            self.save_output_data.data['positions_all']['w_coord'][NG_name] = \
                self.customized_neurons_list[self.spike_input_group_idx]['w_positions']
            self.save_output_data.data['number_of_neurons'][NG_name] = eval(NN_name)
            SGsyn_name = 'SGEN_Syn'  # variable name for the Synapses() object
            # that connects SpikeGeneratorGroup() and relay neurons.
            exec("%s = Synapses(SPK_GENERATOR, %s, on_pre='emit_spike+=1')" % \
                 (SGsyn_name,
                  NG_name) , globals(), locals() ) # connecting the
            # SpikeGeneratorGroup() and relay group.
            exec("%s.connect(j='i')" % SGsyn_name , globals(), locals() ) #
            # SV change
            setattr(self.main_module, NG_name, eval(NG_name))
            setattr(self.main_module, SGsyn_name, eval(SGsyn_name))
            try:
                setattr(self.Cxmodule, NG_name, eval(NG_name))
                setattr(self.Cxmodule, SGsyn_name, eval(SGsyn_name))
            except AttributeError:
                pass
            # taking care of the monitors:
            self.monitors(mons.split(' '), NG_name, self.customized_neurons_list[-1]['equation'])


        assert self.sys_mode != '', " -  System mode not defined."
        assert any(self.current_parameters_list.str.contains('type')), ' -  The type of the input is not defined in the configuration file.'
        input_type_to_method_mapping = {
            # input type : [ columns , obligatory column indices,  sub-routine to call     ]
            'video': [['idx', 'type', 'path','freq', 'monitors'], [0, 1, 2], video],
            'VPM': [['idx', 'type', 'number_of_neurons', 'radius', 'spike_times', 'net_center', 'monitors'],[0, 1, 2, 3, 4], VPM],
            'spikes': [ ['idx','type','input_spikes_filename','monitors'] , [0,1,2] ,  spikes ]
        }
        param_idx = next(iter(self.current_parameters_list[self.current_parameters_list=='type'].index)) # this is equivalent to item() which is depricated
        _input_type = self.current_values_list[param_idx]
        _all_columns = input_type_to_method_mapping[_input_type][0] # all possible columns of parameters for the current type of input in configuration fil
        assert _input_type in list(input_type_to_method_mapping.keys()), ' -  The input type %s of the configuration file is ' \
            'not defined' % _input_type

        _obligatory_params = input_type_to_method_mapping[_input_type][1]
        assert len(self.current_values_list) >= len(_obligatory_params), \
            ' -  One or more of of the columns for input definition is missing. Following obligatory columns should be defined:\n%s\n' % str(
            [_all_columns[ii] for ii in _obligatory_params])
        assert len (self.current_parameters_list) <= len(input_type_to_method_mapping[_input_type][0]), ' -  Too many parameters for the\
         current %s input. The parameters should be consist of:\n %s'%(_input_type,input_type_to_method_mapping[_input_type][0])
        obligatory_columns = list(array(input_type_to_method_mapping[_input_type][0])[input_type_to_method_mapping[_input_type][1]])
        # next(iter()) is equivalent to item() which is depricated
        obligatory_indices = [next(iter(self.current_parameters_list[self.current_parameters_list==ii].index)) for ii in obligatory_columns]
        assert not any(self.current_values_list.loc[obligatory_indices]=='--'), \
            ' -  Following obligatory values cannot be "--":\n%s' % str([_all_columns[ii] for ii in _obligatory_params])
        assert len(self.current_parameters_list) == len(self.current_values_list), \
            ' -  The number of columns for the input are not equal to number of values in the configuration file.'
        try:
            # next(iter()) is equivalent to item() which is depricated
            mons = self.current_values_list[next(iter(self.current_parameters_list[self.current_parameters_list=='monitors'].index), 'no match')]
        except ValueError:
            mons = '--'
        # next(iter()) is equivalent to item() which is depricated
        group_idx = self.current_values_list[next(iter(self.current_parameters_list[self.current_parameters_list=='idx'].index))]

        assert group_idx not in self.NG_indices, \
            " -  Error: multiple indices with same values exist in the configuration file."
        self.NG_indices.append(group_idx)
        current_idx = len(self.customized_neurons_list)
        relay_group = {}
        relay_group['idx'] = int(group_idx)
        relay_group['type'] = 'in'
        relay_group['z_positions'] = []
        relay_group['w_positions'] = []
        relay_group['equation'] = ''
        self.customized_neurons_list.append(relay_group)
        input_type_to_method_mapping[_input_type][2](self)

    def data_loader(self,input_path):
        if '.gz' in input_path:
            with open(input_path, 'rb') as fb:
                data = zlib.decompress(fb.read())
                loaded_data = pickle.loads(data)
        elif '.bz2' in input_path:
            with bz2.BZ2File(input_path, 'rb') as fb:
                loaded_data = pickle.load(fb)
        elif 'pickle' in input_path:
            with open(input_path, 'rb') as fb:
                loaded_data= pickle.load(fb)
        return loaded_data

    def gather_result(self):
        '''
        After the simulation and using the syntaxes that are previously prepared in the syntax_bank of save_data() object, this method saves the collected data to a file.

        '''
        print(" -  Generating the syntaxes for saving CX output:")
        for syntax in self.save_output_data.syntax_bank:
            tmp_monitor = syntax.split(' ')[-1]
            print("     -> Gathering data for " + tmp_monitor.split('.')[0])
            exec(syntax)
        self.save_output_data.save_to_file()
        if hasattr(self,'save_brian_data') and self.do_save_connections:
            print(" -  Generating the syntaxes for saving connection data ...")
            for syntax in self.save_brian_data.syntax_bank:
                exec(syntax)
            self.save_brian_data.create_key('positions_all')
            self.save_brian_data.data['positions_all']['w_coord'] = self.save_output_data.data['positions_all']['w_coord']
            self.save_brian_data.data['positions_all']['z_coord'] = self.save_output_data.data['positions_all']['z_coord']
            self.save_brian_data.save_to_file()

    def visualise_connectivity(self,S):
        Ns = len(S.source)
        Nt = len(S.target)
        figure(figsize=(10, 4))
        subplot(121)
        plot(zeros(Ns), arange(Ns), 'ok', ms=10)
        plot(ones(Nt), arange(Nt), 'ok', ms=10)
        for i, j in zip(S.i, S.j):
            plot([0, 1], [i, j], '-k')
        xticks([0, 1], ['Source', 'Target'])
        ylabel('Neuron index')

    def multi_y_plotter(self,ax, len, variable,item,title):

        for i in range(len):
            tmp_str = 'ax.plot(item.t/ms, item.%s[%d])'%(variable,i)
            exec(tmp_str)
            tmp_str = "ax.set_title('%s')" % (title)
            exec(tmp_str)


if __name__ == '__main__' :
    root = Path(Path(os.getcwd()).parents[1])
    os.chdir(root)
    anatomy_path = root.joinpath('tests','config_files','pytest_Anatomy_config.json').as_posix()
    physio_path = root.joinpath('tests','config_files','pytest_Physiology_config.json').as_posix()
    CM = CxSystem(anatomy_path,physio_path)
    CM.run()
