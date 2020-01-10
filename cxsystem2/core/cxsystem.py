#! /usr/bin/env python3
# -*- coding: utf-8 -*-
__author__ = 'Andalibi, V., Hokkanen H., Vanni, S.'

'''
The preliminary version of this software has been developed at Aalto University 2012-2015,
and the full version at the University of Helsinki 2013-2017. The software is distributed
under the terms of the GNU General Public License.
Copyright 2017 Vafa Andalibi, Henri Hokkanen and Simo Vanni.
'''

import ast
import builtins
import csv
import json
import multiprocessing
import os
import shutil
import sys
import threading
import time
from datetime import datetime
from pathlib import Path

import brian2 as b2
import numpy as np
import pandas as pd
import scipy.sparse as scprs
from brian2 import rand
from brian2.units import *
from numpy import nan

from cxsystem2.core import equation_templates as eqt
from cxsystem2.core.exceptions import ParameterNotFoundError
from cxsystem2.core.parameter_parser import SynapseParser
from cxsystem2.core.physiology_reference import NeuronReference, SynapseReference
from cxsystem2.core.stimuli import Stimuli
from cxsystem2.core.workspace_manager import Workspace
from cxsystem2.bui import bui
from cxsystem2.core.tools import parameter_finder, read_config_file, load_from_file

b2.prefs.devices.cpp_standalone.extra_make_args_unix = []


class CxSystem:
    """
    The main object of cortical system module for building and running a customized model of cortical module based on \
    the configuration files.
    """

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

    def __init__(self, anatomy_and_system_config=None,
                 physiology_config=None,
                 output_file_suffix="",
                 instantiated_from_array_run=0,
                 cluster_run_start_idx=-1,
                 cluster_run_step=-1,
                 array_run_in_cluster=0,
                 array_run_stdout_file = None):
        """
        Initialize the cortical system by parsing both of the configuration files.

        :param anatomy_and_system_config: could be either the path to the anatomy and system configuration file,
                                          or the dataframe containing the configuration data.
        :param output_file_suffix: switch the GeNN mode on/off (1/0), by default GeNN is off
        :param instantiated_from_array_run: this flag, 0 by default, determines whether this instance of CxSystem is instantiated from
                                             another instance of CxSystem which is running an array run.
        :param stdout_file_path: this is only used for saving arrayrun stdout Main internal variables:

        * customized_neurons_list: This list contains the NeuronReference instances. So for each neuron group target line,
                                    there would be an element in this list which contains all the information for that particular neuron group.
        * customized_synapses_list: This list contains the SynapseReference instances. Hence, for each synapse custom line,
                                    there would be an element in this list, containing all the necessary information.
        * neurongroups_list: This list contains name of the NeuronGroup() instances that are placed in the Globals().
        * synapses_name_list: This list contains name of the Synapses() instances that are placed in the Globals().
        * monitor_name_bank: The dictionary containing the name of the monitors that are defined for any NeuronGroup() or Synapses().
        * default_monitors: In case --> and <-- symbols are used in the configuration file, this default monitor will be applied on all
                            the target lines in between those marks.
        * save_data: The save_data() object for saving the final data.

        """

        if anatomy_and_system_config is None or physiology_config is None:
            return

        self.start_time = time.time()
        self.main_module = sys.modules['__main__']
        try:  # try to find the Cxmodule in the sys.modules, to find if the __main__ is CxSystem.py or not
            self.Cxmodule = sys.modules['cxsystem2.core.cxsystem']
        except KeyError:
            pass
        self.parameter_to_method_mapping = {
            # system parameter definitions:
            # Parameter_name : [set priority (0 is highest),function_to_run]
            'device': [0, self.set_device],
            'save_input_video': [1, self.save_input_video],
            'runtime': [2, self._set_runtime],
            'sys_mode': [3, self._set_sys_mode],  # either "local" or "expanded"
            'scale': [4, self._set_scale],
            'grid_radius': [5, self._set_grid_radius],
            'min_distance': [6, self._set_min_distance],
            'init_vms': [7, self.init_vms],
            'default_clock': [8, self.set_default_clock],
            'workspace_path': [8, self.set_workspace],
            'compression_method': [9, self.set_compression_method],
            'simulation_title': [10, self.create_simulation],
            'import_connections_from': [11, self.set_import_connections_path],
            'load_positions_only': [12, self.load_positions_only],
            'benchmark': [13, self.set_benchmark],
            'profiling': [14, self.set_profiling],
            'multidimension_array_run': [15, self.passer],  # this parameter is used by array_run module, so here we just pass
            'number_of_process': [16, self.passer],  # this parameter is used by array_run module, so here we just pass
            'trials_per_config': [17, self.passer],
            'run_in_cluster': [18, self.passer],
            'cluster_job_file_path': [19, self.passer],
            'cluster_number_of_nodes': [20, self.passer],
            'cluster_address': [21, self.passer],
            'cluster_username': [22, self.passer],
            'cluster_workspace': [23, self.passer],
            'integration': [24, self.integration],
            # Line definitions:
            'G': [nan, self.neuron_group],
            'S': [nan, self.synapse],
            'IN': [nan, self.relay],
            'params': [nan, self.set_runtime_parameters],
        }
        now = datetime.now()
        self.timestamp = '_' + str(now).replace('-', '').replace(' ', '_').replace(':', '')
        self.timestamp = self.timestamp[0:str(now).replace('-', '').replace(' ', '_').replace(':', '').index('.') + 3].replace('.', '')
        if output_file_suffix == "":
            self.suffix = self.timestamp + output_file_suffix
        else:
            self.suffix = output_file_suffix
        print(" -  Current run filename suffix is: %s" % self.suffix[1:])
        self.scale = 1
        self.benchmark = 0
        self.cluster_run_start_idx = cluster_run_start_idx
        self.cluster_run_step = cluster_run_step
        self.current_parameters_list = []
        # current_parameters_list is changing at some point in the code, so the original length of it is needed
        self.current_parameters_list_orig_len = 0
        self.current_values_list = []
        self.NG_indices = []
        # Next list contains the NeuronReference instances. So for each neuron group target line, there would be an element in this list which
        # contains all the information for that particular neuron group.
        self.customized_neurons_list = []
        # Next list contains the SynapseReference instances. Hence, for each synapse custom line, there would be an element in this list,
        # containing all the necessary information.
        self.customized_synapses_list = []
        # This list contains name of the NeuronGroup() instances that are placed in the Globals().
        self.neurongroups_list = []
        # This list contains name of the Synapses() instances that are placed in the Globals().
        self.synapses_name_list = []
        # The dictionary containing the name of the monitors that are defined for any NeuronGroup() or Synapses().
        self.monitor_name_bank = {}
        # In case --> and <-- symbols are used in the configuration file, this default monitor will be applied on all
        # the target lines in between those marks.
        self.default_monitors = []
        self.default_save_flag = -1
        self.default_load_flag = -1
        self.monitor_idx = 0
        self.total_synapses = 0
        self.sys_mode = ''
        self.total_number_of_synapses = 0
        self.total_number_of_connections = 0
        self.general_grid_radius = 0
        self.min_distance = 0
        self.init_vms = 0
        self.do_save_connections = 0  # if there is at least one connection to save, this flag will be set to 1
        self.load_positions_only = 0
        self.profiling = 0
        self.array_run_in_cluster = array_run_in_cluster
        self.awaited_conf_lines = []
        self.array_run_stdout_file = array_run_stdout_file

        self.physio_config_df = read_config_file(physiology_config, header=True)
        self.physio_config_df = self.physio_config_df.applymap(lambda x: b2.NaN if str(x)[0] == '#' else x)

        self.anat_and_sys_conf_df = read_config_file(anatomy_and_system_config)
        self.anat_and_sys_conf_df = self.anat_and_sys_conf_df.applymap(lambda x: x.strip() if type(x) == str else x)

        # dropping the commented lines :
        self.anat_and_sys_conf_df = self.anat_and_sys_conf_df.drop(self.anat_and_sys_conf_df[0].index[self.anat_and_sys_conf_df[0][
            self.anat_and_sys_conf_df[0].str.contains('#') == True].index.tolist()]).reset_index(drop=True)
        self.physio_config_df = self.physio_config_df.drop(self.physio_config_df['Variable'].index[self.physio_config_df['Variable'][
            self.physio_config_df['Variable'].str.contains('#') == True].index.tolist()]).reset_index(drop=True)
        # merging the params lines into one row:
        params_indices = np.where(self.anat_and_sys_conf_df.values == 'params')
        if params_indices[0].size > 1:
            for row_idx in params_indices[0][1:]:
                number_of_new_columns = len(self.anat_and_sys_conf_df.columns)
                # number_of_rows = len(self.anat_and_sys_conf_df.index)
                existing_rows = self.anat_and_sys_conf_df.index
                new_columns = list(np.arange(number_of_new_columns, number_of_new_columns * 2))
                empty_dataframe = pd.DataFrame(index=existing_rows, columns=new_columns)
                new_anat_and_sys_conf_df = pd.concat([self.anat_and_sys_conf_df, empty_dataframe], axis=1)

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
        self.physio_df_to_save = self.physio_config_df
        self.array_run = 0
        try:
            self.numerical_integration_method = parameter_finder(self.anat_and_sys_conf_df, 'integration')
        except NameError:
            self.numerical_integration_method = 'euler'
        print(" -  The system is running with %s integration method" % self.numerical_integration_method)

        check_array_run_anatomy = self.anat_and_sys_conf_df.applymap(lambda x: True if ('|' in str(x) or '&' in str(x)) else False)
        check_array_run_physiology = self.physio_config_df.applymap(lambda x: True if ('|' in str(x) or '&' in str(x)) else False)
        try:
            trials_per_config = int(parameter_finder(self.anat_and_sys_conf_df, 'trials_per_config'))
        except NameError:
            trials_per_config = 0
        # check for array_run and return
        if np.any(check_array_run_anatomy) or np.any(check_array_run_physiology) or (trials_per_config > 1 and not instantiated_from_array_run):
            self.workspace = Workspace(parameter_finder(self.anat_and_sys_conf_df, 'workspace_path'), self.suffix)
            self.workspace.create_simulation(parameter_finder(self.anat_and_sys_conf_df, 'simulation_title'))
            suffix = self.suffix
            tmp_folder_path = self.workspace.get_workspace_folder().joinpath('.tmp' + suffix)
            if not tmp_folder_path.is_dir():
                os.mkdir(tmp_folder_path.as_posix())
            tmp_anat_path = tmp_folder_path.joinpath('tmp_anat' + self.suffix + '.csv').as_posix()
            tmp_physio_path = tmp_folder_path.joinpath('tmp_phys' + self.suffix + '.csv').as_posix()
            self.anat_and_sys_conf_df.to_csv(tmp_anat_path, index=False, header=False)
            self.physio_config_df.to_csv(tmp_physio_path, index=False, header=True)
            array_run_path = Path(Path(Path(__file__).parent).parent).joinpath('hpc').joinpath('array_run.py').as_posix()
            cluster_flag = 0

            # next condition means CxSystem is running in cluster and is trying to spawn an array run on a node
            if self.cluster_run_start_idx != -1 and self.cluster_run_step != -1:
                array_run_suffix = '_' + Path(anatomy_and_system_config).stem.split('_')[-2] + '_' + Path(anatomy_and_system_config).stem.split('_')[
                    -1]
                print("spawning index: %d, step: %d" % (int(cluster_run_start_idx), int(cluster_run_step)))
                cluster_flag = 1
                suffix = array_run_suffix

            if type(anatomy_and_system_config) == dict:
                tmp_anat_path2 = tmp_folder_path.joinpath('tmp_anat_2_' + self.suffix + '.json').as_posix()
                with open(tmp_anat_path2, 'w') as f:
                    json.dump(anatomy_and_system_config, f)
                anatomy_and_system_config = tmp_anat_path2
            if type(physiology_config) == dict:
                tmp_physio_path2 = tmp_folder_path.joinpath('tmp_phys_2_' + self.suffix + '.json').as_posix()
                with open(tmp_physio_path2, 'w') as f:
                    json.dump(physiology_config, f)
                physiology_config = tmp_physio_path2
            # this is vulnerable to code injection
            command = 'python {array_run} {anat_df} {physio_df} {suffix} {start} {step} {anat_path} {physio_path} {cluster} {stdout_file}'.format(
                array_run=array_run_path,
                anat_df=tmp_anat_path,
                physio_df=tmp_physio_path,
                suffix=suffix,
                start=int(cluster_run_start_idx),
                step=int(cluster_run_step),
                anat_path=anatomy_and_system_config,
                physio_path=physiology_config,
                cluster=cluster_flag,
                stdout_file=self.array_run_stdout_file
            )
            if sys.platform == 'linux' or sys.platform == 'darwin':
                command = '/bin/bash -c "' + command + '"'
            os.system(command)
            self.array_run = 1
            return
        try:
            self.conn_prob_gain = int(
                next(iter(self.physio_config_df.loc[np.where(self.physio_config_df.values == 'conn_prob_gain')[0]]['Value']), 'no match'))
        except ValueError:
            self.conn_prob_gain = 1

        if self.array_run == 0:
            try:
                tmp_cluster = parameter_finder(self.anat_and_sys_conf_df, 'run_in_cluster')
                if tmp_cluster == '1':
                    print(" -  Warning: Config file is set to run in cluster but it does not contain an array run; run_in_cluster will be ignored ")
            except NameError:
                pass
        self.configuration_executor()
        if type(self.awaited_conf_lines) != list:
            if self.thr.is_alive():
                print(" -  Waiting for the video input ...")
                self.thr.join()
            self.anat_and_sys_conf_df = self.awaited_conf_lines
            self.configuration_executor()
        print(" -  Cortical Module initialization Done.")

    @staticmethod
    def run_bui(ssl=False,
                port=None,
                nobrowser=False):
        bui.RunServer(ssl=ssl, port=port, nobrowser=nobrowser)

    def configuration_executor(self):
        definition_lines_idx = self.anat_and_sys_conf_df.loc[:, 0][self.anat_and_sys_conf_df.loc[:, 0] == 'row_type'].index
        order_of_lines = ['params', 'IN', 'G', 'S']
        for value_line_title in order_of_lines:
            for def_idx in definition_lines_idx:
                if value_line_title in self.anat_and_sys_conf_df.loc[def_idx + 1, 0]:
                    self.current_parameters_list = self.anat_and_sys_conf_df.loc[def_idx, 1:].dropna()
                    self.current_parameters_list = self.current_parameters_list[~self.current_parameters_list.str.contains('#')]
                    self.current_parameters_list_orig_len = len(self.current_parameters_list)
                    try:
                        next_def_line_idx = definition_lines_idx[definition_lines_idx.tolist().index(def_idx) + 1].item()
                    except IndexError:
                        next_def_line_idx = self.anat_and_sys_conf_df[0].__len__()
                    for self.value_line_idx in range(def_idx + 1, next_def_line_idx):
                        if type(self.anat_and_sys_conf_df.loc[self.value_line_idx, 0]) == str:
                            if self.anat_and_sys_conf_df.loc[self.value_line_idx, 0] in list(self.parameter_to_method_mapping.keys()) and \
                                    self.anat_and_sys_conf_df.loc[self.value_line_idx, 0][0] != '#':
                                self.current_parameters_list = self.anat_and_sys_conf_df.loc[def_idx, 1:].dropna()
                                self.current_parameters_list = self.current_parameters_list[~self.current_parameters_list.str.contains('#')]
                                self.current_values_list = self.anat_and_sys_conf_df.loc[
                                    self.value_line_idx, self.current_parameters_list.index].dropna()
                                self.parameter_to_method_mapping[self.anat_and_sys_conf_df.loc[self.value_line_idx, 0]][1]()
                    break

    def value_extractor(self,
                        df,
                        key_name):
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
                    cropped_df = df.loc[variable_start_idx:variable_end_idx - 1]
                except IndexError:
                    cropped_df = df.loc[variable_start_idx:]
                return eval(cropped_df['Value'][cropped_df['Key'] == key_name[1]].item())
            else:
                return eval(next(iter(df['Value'][df['Key'] == key_name])))
        except NameError:
            new_key = df['Value'][df['Key'] == key_name].item().replace("']", "").split("['")
            return self.value_extractor(df, new_key)
        except ValueError:
            raise ValueError("Parameter %s not found in the configuration file." % key_name)
        except Exception as e:
            print(e)

    @staticmethod
    def set_default_clock(*args):
        b2.defaultclock.dt = eval(args[0])
        print(" -  Default clock is set to %s" % str(b2.defaultclock.dt))

    def set_workspace(self, *args):
        if self.cluster_run_start_idx == -1 and self.cluster_run_step == -1 and self.array_run_in_cluster == 0:
            self.workspace = Workspace(args[0], self.suffix)
        else:  # this means cxsystem is running in cluster
            print(" -  CxSystem is running in Cluster ... ")
            self.workspace = Workspace(parameter_finder(self.anat_and_sys_conf_df, 'cluster_workspace'), self.suffix)
            print(" -  CxSystem knows it's running in cluster and set the output folder to : {}".format(self.workspace.get_workspace_folder()))

    def set_compression_method(self, *args):
        self.workspace.set_compression_method(args[0])

    def create_simulation(self, *args):
        self.workspace.create_simulation(args[0])
        self.workspace.create_results_key('positions_all')
        self.workspace.create_results_key('Neuron_Groups_Parameters')
        self.workspace.results['Anatomy_configuration'] = self.conf_df_to_save
        self.workspace.results['Physiology_configuration'] = self.physio_df_to_save
        self.workspace.results['time_vector'] = arange(0, self.runtime, b2.defaultclock.dt)
        self.workspace.results['positions_all']['w_coord'] = {}
        self.workspace.results['positions_all']['z_coord'] = {}
        self.workspace.results['number_of_neurons'] = {}
        self.workspace.results['runtime'] = self.runtime / self.runtime.get_best_unit()
        self.workspace.results['sys_mode'] = self.sys_mode
        try:
            self.workspace.results['scale'] = self.scale
        except AttributeError:
            pass

    def passer(self, *args):
        pass

    def integration(self, *args):
        self.numerical_integration_method = args[0].lower()
        assert self.numerical_integration_method in ['exact', 'exponential_euler', 'euler', 'rk2', 'rk4', 'heun', 'milstein']

    def set_device(self, *args):
        self.device = args[0]
        assert self.device.lower() in ['cython', 'genn', 'cpp', 'python'], ' -  Device %s is not defined. ' % self.device
        if self.device.lower() == 'cython':
            self.device = "python"
            b2.prefs.codegen.target = 'cython'
            print(" -  Brian Code Generator set to Cython")
        elif self.device.lower() == 'python':
            self.device = "python"
            b2.prefs.codegen.target = 'numpy'
            print(" -  Brian Code Generator set to Numpy")
        if self.device.lower() == 'genn':
            print(" -  System is going to be run using GeNN devices, "
                  "Errors may rise if Brian2/Brian2GeNN/GeNN is not installed correctly or the limitations are not "
                  "taken in to account.")
        print(" -  CxSystem is running on {} device".format(self.device))

    def run(self):
        if not self.array_run:

            if self.device != 'genn':
                b2.run(self.runtime, report='text', profile=True)
            else:
                b2.run(self.runtime, report='text')  # genn doesn't support detailed profiling

            if self.profiling == 1:
                print()
                if len(b2.profiling_summary().names) < 20:
                    print(b2.profiling_summary(show=len(b2.profiling_summary().names)))
                else:
                    print(b2.profiling_summary(show=20))
                self.workspace.results['profiling_data'] = b2.profiling_summary()
            if self.benchmark:
                try:
                    self.benchmarking_data = {}
                    titles = ['Computer Name', 'Device', 'File Suffix', 'Simulation Time', 'Python Compilation', 'Brian Code generation',
                              'Device-Specific Compilation', 'Run', 'Extract and Save Result', 'Total Time']
                    self.benchmarking_data['Simulation Time'] = str(self.runtime)
                    self.benchmarking_data['Device'] = self.device
                    self.benchmarking_data['File Suffix'] = self.suffix[1:]
                    if self.device.lower() != 'python':
                        self.benchmarking_data['Python Compilation'] = builtins.code_generation_start - self.start_time
                        self.benchmarking_data['Brian Code generation'] = builtins.compile_start - builtins.code_generation_start
                        self.benchmarking_data['Device-Specific Compilation'] = builtins.run_start - builtins.compile_start
                    else:
                        self.benchmarking_data['Python Compilation'] = builtins.run_start - self.start_time
                        self.benchmarking_data['Brian Code generation'] = '-'
                        self.benchmarking_data['Device-Specific Compilation'] = '-'
                    self.saving_start_time = time.time()
                    self.benchmarking_data['Run'] = self.saving_start_time - builtins.run_start
                except AttributeError:
                    print(" -  The system could not perform the benchmarking since the brian2/brian2genn libraries are not modified to do so.")
                    self.benchmark = 0
            self.gather_result()
            self.end_time = time.time()
            if self.benchmark:
                self.benchmarking_data['Extract and Save Result'] = self.end_time - self.saving_start_time
                self.benchmarking_data['Total Time'] = self.end_time - self.start_time
                import platform
                self.benchmarking_data['Computer Name'] = platform.node()
                write_titles = 1 if not self.workspace.get_simulation_folder().joinpath('benchmark.csv').is_file() else 0
                with open(self.workspace.get_simulation_folder().joinpath('benchmark.csv').as_posix(), 'ab') as f:
                    w = csv.DictWriter(f, titles)
                    if write_titles:
                        w.writeheader()
                    w.writerow(self.benchmarking_data)
                    print(" -  Benchmarking data saved")
            print(" -  Simulating %s took in total %f s" % (str(
                self.runtime), self.end_time - self.start_time))
            if self.device.lower() == 'genn':
                shutil.rmtree(self.workspace.get_simulation_folder().joinpath(self.suffix[1:]).as_posix())
            elif self.device.lower() == 'cpp':
                shutil.rmtree(self.workspace.get_simulation_folder().joinpath(self.suffix[1:]).as_posix())

    def set_runtime_parameters(self):
        if not np.any(self.current_parameters_list.str.contains('runtime')):
            print(" -  The parameter 'workspace_path' is not defined in the configuration file. The default workspace is ~/CxSystem")
            self.set_workspace('~/CxSystem')

        if not np.any(self.current_parameters_list.str.contains('runtime')):
            print(" -  Runtime duration is not defined in the configuration file. The default runtime duratoin is 500*ms")
            self.runtime = 500 * ms

        if not np.any(self.current_parameters_list.str.contains('device')):
            print(" -  Device is not defined in the configuration file. The default device is Python.")
            self.device = 'Python'

        if not np.any(self.current_parameters_list.str.contains('compression_method')):
            # gzip is default of workspace manager
            print(" -  compresison_method is not defined in the configuration file. Default compression method is gzip")

        for ParamIdx, parameter in self.current_parameters_list.items():
            if parameter not in list(self.parameter_to_method_mapping.keys()):
                print(" -  System parameter %s not defined." % parameter)
        options_with_priority = [it for it in self.parameter_to_method_mapping if not np.isnan(self.parameter_to_method_mapping[it][0])]
        parameters_to_set_prioritized = [it for priority_idx in range(len(options_with_priority)) for it in self.parameter_to_method_mapping if
                                         self.parameter_to_method_mapping[it][0] == priority_idx]
        for correct_parameter_to_set in parameters_to_set_prioritized:
            for ParamIdx, parameter in self.current_parameters_list.items():
                if parameter == correct_parameter_to_set and str(self.current_values_list[ParamIdx])[0] != '#':
                    assert (parameter in list(self.parameter_to_method_mapping.keys())), ' -  The tag %s is not defined.' % parameter
                    self.parameter_to_method_mapping[parameter][1](self.current_values_list[ParamIdx])
                    break
        if self.sys_mode == '':
            raise NameError(" -  System mode is not defined.")
        else:
            print(" -  CxSystem is running in %s mode" % self.sys_mode)
        if self.benchmark:
            print(" -  CxSystem is performing benchmarking. The Brian2 "
                  "should be configured to use benchmarking.")
        if self.device.lower() == 'genn':
            b2.set_device('genn', directory=self.workspace.get_simulation_folder().joinpath(self.suffix[1:]).as_posix())
            b2.prefs.codegen.cpp.extra_compile_args_gcc = ['-O3', '-pipe']
        elif self.device.lower() == 'cpp':
            b2.set_device('cpp_standalone', directory=self.workspace.get_simulation_folder().joinpath(self.suffix[1:]).as_posix())

    #            if 'linux' in sys.platform and self.device.lower() == 'cpp':
    #                print(" -  parallel compile flag set")
    #                b2.prefs['devices.cpp_standalone.extra_make_args_unix'] = ['-j']
    #            b2.prefs.codegen.cpp.extra_compile_args_gcc = ['-O3', '-pipe']

    def _set_runtime(self, *args):
        assert '*' in args[0], ' -  Please specify the unit for the runtime parameter, e.g. um , mm '
        self.runtime = eval(args[0])

    def _set_sys_mode(self, *args):
        assert args[0] in ['local', 'expanded'], " -  System mode should be either local or expanded. "
        self.sys_mode = args[0]

    def save_input_video(self, *args):
        assert int(eval(args[0])) == 0 or int(eval(args[0])) == 1, \
            ' -  The do_init_vm flag should be either 0 or 1 but it is %s .' % args[0]
        self.save_input_video = int(eval(args[0]))

    def _set_grid_radius(self, *args):
        assert '*' in args[0], ' -  Please specify the unit for the grid radius parameter, e.g. um , mm '
        self.general_grid_radius = eval(args[0])
        try:
            if self.scale != 1:
                print(" -  Radius of the system scaled to %s from %s" % (str(
                    np.sqrt(self.scale) * self.general_grid_radius), str(self.general_grid_radius)))
            self.general_grid_radius = np.sqrt(self.scale) * self.general_grid_radius
            if self.sys_mode != 'expanded' and self.scale != 1:
                print(' -  System is scaled by factor of %f but the system '
                      'mode is local instead of expanded' % self.scale)
        except AttributeError:
            pass

    def _set_min_distance(self, *args):
        assert '*' in args[0], ' -  Please specify the unit for the minimum distance parameter, e.g. um , mm '
        self.min_distance = eval(args[0])

    def set_import_connections_path(self, *args):
        if len(args) > 0:  # arguments exists if the path is to be set, but the loading won't happen until on of the connections needs it
            self.workspace.set_imported_connection_path(args[0])
            return
        self.imported_connections = self.workspace.import_connections()
        print(' -  Connection file loaded from {}'.format(self.workspace.imported_connections_path.as_posix()))
        if 'scale' in list(self.imported_connections.keys()):
            self.scale = self.imported_connections['scale']
            print(" -   scale of the system loaded from brian file")

    def init_vms(self, *args):
        assert int(eval(args[0])) == 0 or int(eval(args[0])) == 1, \
            ' -  The do_init_vm flag should be either 0 or 1 but it is %s .' % args[0]
        self.init_vms = int(eval(args[0]))
        if self.init_vms:
            print(' -  Membrane voltages are being randomly initialized.')
        if not self.init_vms:
            print(' -  Membrane voltages are not initialized.')

    def _set_scale(self, *args):
        # if float(args[0])!=1.0:
        self.scale = float(args[0])
        if self.scale != 1:
            print(" -  CxSystem is being build on the scale of %s" % args[0])

    def load_positions_only(self, *args):
        assert int(eval(args[0])) == 0 or int(eval(args[0])) == 1, ' -  The load_positions_only flag should be either 0 or 1 but it is %s .' % args[0]
        self.load_positions_only = int(eval(args[0]))
        if self.load_positions_only:
            self.set_import_connections_path()
            print(" -  only positions are being loaded from the brian_data_file")

    def set_benchmark(self, *args):
        assert int(eval(args[0])) in [0, 1], " -  Do benchmark flag should be either 0 or 1"
        self.benchmark = int(eval(args[0]))

    def set_profiling(self, *args):
        assert int(eval(args[0])) in [0, 1], " -  Profiling flag should be either 0 or 1"
        self.profiling = int(eval(args[0]))

    def neuron_group(self):
        """
        The method that creates the NeuronGroups() based on the parameters that are extracted from the
        configuration file in the __init__ method of the class.

        Main internal variables:

        * mon_args: contains the monitor arguments extracted from the target line.
        * net_center: center position of the neuron group in visual field coordinates, description can be found in
                        configuration file tutorial.
        * _dyn_neurongroup_name: Generated variable name for the NeuronGroup() object in brian2.
        * _dyn_neuronnumber_name: Generated variable name for corresponding Neuron Number.
        * _dyn_neuron_eq_name: Generated variable name for the NeuronGroup() equation.
        * _dyn_neuron_thres_name: Generated variable name for the NeuronGroup() threshold.
        * _dyn_neuron_reset_name: Generated variable name for the NeuronGroup() reset value.
        * _dyn_neuron_refra_name: Generated variable name for the NeuronGroup() refractory value.
        * _dyn_neuron_namespace_name: Generated variable name for the NeuronGroup() namespace.
        * ng_init: NeuronGroups() should be initialized with a random vm, ge and gi values. To address this, a 6-line code
                    is generated and put in this variable, the running of which will lead to initialization of current NeuronGroup().
        """

        # <editor-fold desc="...Parameter preprocessing">
        assert self.sys_mode != '', " -  System mode is not defined."
        _all_columns = ['idx', 'number_of_neurons', 'neuron_type', 'layer_idx', 'net_center', 'monitors',
                        'n_background_inputs', 'n_background_inhibition', 'neuron_subtype']
        # 'threshold', 'reset', 'refractory',
        # 'tonic_current', 'noise_sigma', 'gemean', 'gestd', 'gimean', 'gistd']
        _obligatory_params = [0, 1, 2, 3]
        assert len(self.current_values_list) >= len(_all_columns), ' -  One or more of of the columns for NeuronGroups definition \
        is missing. Following obligatory columns should be defined:\n%s\n ' \
                                                                   % str([_all_columns[ii] for ii in _obligatory_params])
        obligatory_columns = list(np.array(_all_columns)[_obligatory_params])
        obligatory_indices = [next(iter(self.current_parameters_list[self.current_parameters_list == ii].index)) for ii in obligatory_columns]
        assert not np.any(self.current_values_list.loc[obligatory_indices] == '--'), \
            ' -  Following obligatory values cannot be "--":\n%s' % str([_all_columns[ii] for ii in _obligatory_params])
        assert len(self.current_values_list) == self.current_parameters_list_orig_len, \
            " -  One or more of of the columns for NeuronGroup definition is missing in the following" \
            " line (lengths not equal: {} and {}):\n {} \n {}  ".format(
                len(self.current_values_list),
                self.current_parameters_list_orig_len,
                self.current_parameters_list,
                self.current_values_list)
        local_namespace = {'idx': -1,
                           'net_center': 0 + 0j,
                           'number_of_neurons': 0,
                           'n_background_inputs': '',
                           'n_background_inhibition': '',
                           'neuron_subtype': '',
                           'neuron_type': '',
                           'layer_idx': 0,
                           'monitors': ''}
        # local_namespace['threshold'] = ''
        # local_namespace['reset'] = ''
        # local_namespace['refractory'] = ''
        # local_namespace['noise_sigma'] = ''
        # local_namespace['gemean'] = ''
        # local_namespace['gestd'] = ''
        # local_namespace['gimean'] = ''
        # local_namespace['gistd'] = ''
        # local_namespace['tonic_current'] = ''

        for column in _all_columns:
            try:
                tmp_value_idx = int(next(iter(self.current_parameters_list[self.current_parameters_list == column].index), 'no match'))
                tmp_var_str = "local_namespace['%s']=self.current_values_list[%d]" % (column, tmp_value_idx)
                exec(tmp_var_str)
            except ValueError:
                exec("local_namespace['%s']='--'" % column)

        idx = local_namespace['idx']
        net_center = local_namespace['net_center']
        number_of_neurons = local_namespace['number_of_neurons']
        n_background_inputs = local_namespace['n_background_inputs']
        n_background_inhibition = local_namespace['n_background_inhibition']
        monitors = local_namespace['monitors']
        neuron_type = local_namespace['neuron_type']
        neuron_subtype = local_namespace['neuron_subtype']
        # noise_sigma = local_namespace['noise_sigma']
        # gemean = local_namespace['gemean']
        # gestd = local_namespace['gestd']
        # gimean = local_namespace['gimean']
        # gistd = local_namespace['gistd']
        # threshold = local_namespace['threshold']
        # reset = local_namespace['reset']
        # refractory = local_namespace['refractory']
        # tonic_current = local_namespace['tonic_current']

        assert idx not in self.NG_indices, \
            " -  Multiple indices with same values exist in the configuration file."
        self.NG_indices.append(idx)
        if net_center == '--':
            net_center = 0 + 0j  # center position of the neuron group in visual field coordinates,
            # description can be found in configuration file tutorial.
        net_center = complex(net_center)
        current_idx = len(self.customized_neurons_list)

        # if tonic_current == '--':
        #     tonic_current = '0*pA'
        #
        # if noise_sigma == '--':
        #     noise_sigma = '0*mV'
        # noise_sigma = eval(noise_sigma)
        #
        # if gemean == '--':
        #     gemean = '0*nS'
        # if gestd == '--':
        #     gestd = '0*nS'
        # if gimean == '--':
        #     gimean = '0*nS'
        # if gistd == '--':
        #     gistd = '0*nS'

        if n_background_inputs == '--':
            n_background_inputs = '0'
        if n_background_inhibition == '--':
            n_background_inhibition = '0'

        # assert 'V' in str(noise_sigma.get_best_unit()), ' -  The unit of noise_sigma should be volt'
        if neuron_type == 'PC':  # extract the layer index of PC neurons separately
            if local_namespace['layer_idx'].isdigit():
                local_namespace['layer_idx'] = local_namespace['layer_idx']
            else:
                local_namespace['layer_idx'] = eval(local_namespace['layer_idx'].replace('->', ','))
        layer_idx = local_namespace['layer_idx']
        try:
            number_of_neurons = str(int(int(number_of_neurons) * self.scale))
        except AttributeError:
            pass
        # </editor-fold>

        # <editor-fold desc="...Generation of neuron reference">
        self.customized_neurons_list.append(NeuronReference(idx, number_of_neurons, neuron_type,
                                                            layer_idx, self.general_grid_radius, self.min_distance, self.physio_config_df,
                                                            network_center=net_center, cell_subtype=neuron_subtype).output_neuron)  # creating a
        # NeuronReference() object and passing the positional arguments to it. The main member of the class called
        # output_neuron is then appended to customized_neurons_list.
        # in case of threshold/reset/refractory overwrite
        # if threshold != '--':
        #     self.customized_neurons_list[-1]['threshold'] = threshold
        # if reset != '--':
        #     self.customized_neurons_list[-1]['reset'] = reset
        # if refractory != '--':
        #     self.customized_neurons_list[-1]['refractory'] = refractory

        # Generating variable names for Groups, NeuronNumbers, Equations, Threshold, Reset, Refractory and Namespace
        if neuron_subtype == '--':
            _dyn_neurongroup_name = self._NeuronGroup_prefix + str(current_idx) + '_' + neuron_type + '_L' + \
                                    str(layer_idx).replace(', ', 'toL').replace('[', '').replace(']', '')
        else:
            _dyn_neurongroup_name = self._NeuronGroup_prefix + str(current_idx) + '_' + neuron_subtype + '_L' + \
                                    str(layer_idx).replace(', ', 'toL').replace('[', '').replace(']', '')
        self.neurongroups_list.append(_dyn_neurongroup_name)
        _dyn_neuronnumber_name = self._NeuronNumber_prefix + str(current_idx)
        _dyn_neuron_eq_name = self._NeuronEquation_prefix + str(current_idx)
        _dyn_neuron_thres_name = self._NeuronThreshold_prefix + str(current_idx)
        _dyn_neuron_reset_name = self._NeuronReset_prefix + str(current_idx)
        _dyn_neuron_refra_name = self._NeuronRef_prefix + str(current_idx)
        _dyn_neuron_namespace_name = self._NeuronNS_prefix + str(current_idx)

        # next  6 line create the variable that are needed for current target line NeuronGroup().
        self.workspace.results['Neuron_Groups_Parameters'][_dyn_neurongroup_name] = self.customized_neurons_list[-1]
        self.customized_neurons_list[current_idx]['object_name'] = _dyn_neurongroup_name
        exec("%s=self.customized_neurons_list[%d]['number_of_neurons']" % (_dyn_neuronnumber_name, current_idx))
        exec("%s=self.customized_neurons_list[%d]['equation']" % (_dyn_neuron_eq_name, current_idx))
        exec("%s=self.customized_neurons_list[%d]['threshold']" % (_dyn_neuron_thres_name, current_idx))
        exec("%s=self.customized_neurons_list[%d]['reset']" % (_dyn_neuron_reset_name, current_idx))
        exec("%s=self.customized_neurons_list[%d]['refractory']" % (_dyn_neuron_refra_name, current_idx))
        exec("%s=self.customized_neurons_list[%d]['namespace']" % (_dyn_neuron_namespace_name, current_idx))

        # // Background input code BEGINS
        # Adding tonic current to namespace
        # self.customized_neurons_list[current_idx]['namespace']['tonic_current'] = eval(tonic_current)
        # Adding the noise sigma to namespace
        # self.customized_neurons_list[current_idx]['namespace']['noise_sigma'] = noise_sigma
        # # Adding ge/gi mean/std to namespace
        # self.customized_neurons_list[current_idx]['namespace']['gemean'] = eval(gemean)
        # self.customized_neurons_list[current_idx]['namespace']['gestd'] = eval(gestd)
        # self.customized_neurons_list[current_idx]['namespace']['gimean'] = eval(gimean)
        # self.customized_neurons_list[current_idx]['namespace']['gistd'] = eval(gistd)

        # Creating the actual NeuronGroup() using the variables in the previous 6 lines
        exec("%s= b2.NeuronGroup(%s, model=%s, method='%s', threshold=%s, reset=%s,refractory = %s, namespace = %s)"
             % (_dyn_neurongroup_name, _dyn_neuronnumber_name, _dyn_neuron_eq_name, self.numerical_integration_method
                , _dyn_neuron_thres_name, _dyn_neuron_reset_name, _dyn_neuron_refra_name, _dyn_neuron_namespace_name))
        # </editor-fold>

        # <editor-fold desc="...Poisson-distributed background input">
        # TODO - Move this out of cxsystem.py & clean up

        try:
            background_rate = next(iter(self.physio_config_df.loc[np.where(self.physio_config_df.values == 'background_rate')[0]]['Value']))
            background_rate_inhibition = next(
                iter(self.physio_config_df.loc[np.where(self.physio_config_df.values == 'background_rate_inhibition')[0]]['Value']))
        except:
            background_rate = None
            background_rate_inhibition = None

        if (background_rate is not None) or (background_rate_inhibition is not None):
            # For changing connection weight of background input according to calcium level
            try:
                ca = self.value_extractor(self.physio_config_df, 'calcium_concentration')
            except ValueError:
                ca = 2.0  # default value that doesn't scale connection weights

            try:
                flag_bg_calcium_scaling = self.value_extractor(self.physio_config_df, 'flag_background_calcium_scaling')
            except ValueError:
                flag_bg_calcium_scaling = 0

            bg_synapse = SynapseParser({'type': 'Fixed', 'pre_group_type': 'SS', 'post_group_type': neuron_type},
                                       self.physio_config_df)
            bg_synapse_inh = SynapseParser({'type': 'Fixed', 'pre_group_type': 'BC', 'post_group_type': neuron_type},
                                           self.physio_config_df)

            if neuron_type in ['L1i', 'BC', 'MC']:
                background_weight = self.value_extractor(self.physio_config_df, 'background_E_I_weight')
                background_weight_inhibition = self.value_extractor(self.physio_config_df, 'background_E_I_weight')

                if flag_bg_calcium_scaling == 1:
                    background_weight = repr(bg_synapse.scale_by_calcium(ca, background_weight))

                    background_weight_inhibition = repr(bg_synapse_inh.scale_by_calcium(ca, background_weight_inhibition))
                else:
                    background_weight = repr(background_weight)
                    background_weight_inhibition = repr(background_weight_inhibition)

            else:
                background_weight = self.value_extractor(self.physio_config_df, 'background_E_E_weight')
                background_weight_inhibition = self.value_extractor(self.physio_config_df, 'background_I_E_weight')

                if flag_bg_calcium_scaling == 1:
                    background_weight = \
                        repr(bg_synapse.scale_by_calcium(ca, background_weight))

                    background_weight_inhibition = \
                        repr(bg_synapse_inh.scale_by_calcium(ca, background_weight_inhibition))
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
                    exec("%s = b2.PoissonInput(target=%s, target_var='%s_soma', N=%s, rate=%s, weight=%s)"
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
                    exec("%s = b2.PoissonInput(target=%s, target_var='%s_soma', N=%s, rate=%s, weight=%s)"
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
                n_target_compartments = int(self.customized_neurons_list[-1]['total_comp_num']) - 1  # No excitatory input to soma
                n_inputs_to_each_comp = int(int(n_background_inputs) / n_target_compartments)
                target_comp_list = ['basal', 'a0']
                target_comp_list.extend(['a' + str(i) for i in range(1, n_target_compartments - 2 + 1)])

                for receptor in exc_receptors:
                    for target_comp in target_comp_list:
                        poisson_target = 'bg_%s_%s_%s' % (receptor, _dyn_neurongroup_name, target_comp)
                        exec("%s = b2.PoissonInput(target=%s, target_var='%s_%s', N=%s, rate=%s, weight=%s)"
                             % (poisson_target, _dyn_neurongroup_name, receptor, target_comp, n_inputs_to_each_comp,
                                background_rate, background_weight))
                        try:
                            setattr(self.Cxmodule, poisson_target, eval(poisson_target))
                        except AttributeError:
                            print('Error in generating PoissonInput')

                # Background inhibition for PC neurons (targeting soma)
                for receptor in inh_receptors:
                    poisson_target_inh = 'bg_%s_%s' % (receptor, _dyn_neurongroup_name)
                    exec("%s = b2.PoissonInput(target=%s, target_var='%s_soma', N=%s, rate=%s, weight=%s)"
                         % (poisson_target_inh, _dyn_neurongroup_name, receptor, n_background_inhibition,
                            background_rate_inhibition, background_weight_inhibition))
                    try:
                        setattr(self.Cxmodule, poisson_target_inh, eval(poisson_target_inh))
                    except AttributeError:
                        print('Error in generating PoissonInput')

        # </editor-fold>

        # <editor-fold desc="...Loading neuron positions">
        if hasattr(self, 'imported_connections'):
            # in case the NG index are different.
            # for example a MC_L2 neuron might have had index 3 as NG3_MC_L2 and now it's NG10_MC_L2 :
            group_type = _dyn_neurongroup_name[_dyn_neurongroup_name.index('_') + 1:]
            group_key_name = [kk for kk in list(self.imported_connections['positions_all']['w_coord'].keys()) if group_type in kk][0]
            self.customized_neurons_list[current_idx]['w_positions'] = self.imported_connections['positions_all']['w_coord'][group_key_name]
            self.customized_neurons_list[current_idx]['z_positions'] = self.imported_connections['positions_all']['z_coord'][group_key_name]
            print(" -  Position for the group %s loaded"
                  % _dyn_neurongroup_name)
        # Setting the position of the neurons in the current NeuronGroup.
        try:
            exec("%s.x=b2.real(self.customized_neurons_list[%d]['w_positions'])*mm\n"
                 "%s.y=b2.imag(self.customized_neurons_list[%d]['w_positions'])*mm"
                 % (_dyn_neurongroup_name, current_idx, _dyn_neurongroup_name, current_idx))
        except ValueError as e:
            raise ValueError(
                e.message + ' -  You are probably trying to load the positions from a file that does not contain the same number of cells.')
        # Saving the neurons' positions both in visual field and cortical coordinates in save_data() object.
        self.workspace.results['positions_all']['z_coord'][_dyn_neurongroup_name] = \
            self.customized_neurons_list[current_idx]['z_positions']
        self.workspace.results['positions_all']['w_coord'][_dyn_neurongroup_name] = \
            self.customized_neurons_list[current_idx]['w_positions']
        self.workspace.results['number_of_neurons'][_dyn_neurongroup_name] = eval(_dyn_neuronnumber_name)
        # </editor-fold>

        # <editor-fold desc="Initialization of neuron group compartment potentials and conductances">
        # NeuronGroups() should be initialized with a random vm, ge and gi values.
        # To address this, a 6-line code is generated and put in ng_init variable,
        # the running of which will lead to initialization of current NeuronGroup().
        if self.init_vms:
            ng_init = 'Vr_offset = b2.rand(len(%s))\n' % _dyn_neurongroup_name
            ng_init += "for _key in %s.variables.keys():\n" % _dyn_neurongroup_name
            ng_init += "\tif _key.find('vm')>=0:\n"
            ng_init += "\t\tsetattr(%s,_key,%s['V_init_min']+Vr_offset * (%s['V_init_max']-%s['V_init_min']))\n" % \
                       (_dyn_neurongroup_name, _dyn_neuron_namespace_name, _dyn_neuron_namespace_name, _dyn_neuron_namespace_name)

            # Commented out (didn't work with receptors) /HH
            # ng_init += "\telif ((_key.find('ge')>=0) or (_key.find('gi')>=0)):\n"
            # ng_init += "\t\tsetattr(%s,_key,0)" % _dyn_neurongroup_name
            exec(ng_init)
        else:
            ng_init = "for _key in %s.variables.keys():\n" % _dyn_neurongroup_name
            ng_init += "\tif _key.find('vm')>=0:\n"
            ng_init += "\t\tsetattr(%s,_key,%s['V_init'])\n" % (_dyn_neurongroup_name, _dyn_neuron_namespace_name)

            # Commented out (didn't work with receptors) /HH
            # ng_init += "\telif ((_key.find('ge')>=0) or (_key.find('gi')>=0)):\n"
            # ng_init += "\t\tsetattr(%s,_key,0)" % _dyn_neurongroup_name
            exec(ng_init)
        # </editor-fold>

        setattr(self.main_module, _dyn_neurongroup_name, eval(_dyn_neurongroup_name))
        try:
            setattr(self.Cxmodule, _dyn_neurongroup_name, eval(_dyn_neurongroup_name))
        except AttributeError:
            pass

        # passing remainder of the arguments to monitors() method to take care of the arguments.
        self.monitors(str(monitors).split(' '), _dyn_neurongroup_name) # , self.customized_neurons_list[-1]['equation'])

    def monitors(self, mon_args, object_name):
        """
        This method creates the Monitors() in brian2 based on the parameters that are extracted from a target line in configuration file.

        :param mon_args: The monitor arguments extracted from the target line.
        :param object_name: The generated name of the current object.

        Main internal variables:

        * mon_tag: The tag that is extracted from the target line every time.
        * mon_name: Generated variable name for a specific monitor.
        * mon_str: The syntax used for building a specific StateMonitor.
        * sub_mon_tags: The tags in configuration file that are specified for a StateMonitor(), e.g. in record=True which is specified by
                        [rec]True in configuration file, [rec] is saved in sub_mon_tags
        * sub_mon_args: The corresponding arguments of sub_mon_tags for a StateMonitor(), e.g. in record=True which is specified by
                        [rec]True in configuration file, True is saved in sub_mon_args.
        """
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
            '[Sp]': ['SpMon', 'b2.SpikeMonitor'],
            '[St]': ['StMon', 'b2.StateMonitor'],
            '[dt]': [',dt='],
            '[rec]': [',record=']
        }
        self.monitor_name_bank[object_name] = []
        for mon_arg in mon_args:
            # Extracting the monitor tag
            mon_tag = mon_arg[mon_arg.index('['):mon_arg.index(']') + 1]
            assert mon_tag in list(monitor_options.keys()), '%s is not recognized as a type of monitor ' % mon_tag
            mon_arg = mon_arg.replace(mon_tag, '').split('+')
            for sub_mon_arg in mon_arg:  # going through each state variable:
                mon_str = "=%s(%s" % (str(monitor_options[mon_tag][1]),
                                      object_name)  # The syntax used for building a specific StateMonitor.
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
                        sub_mon_arg[sub_mon_tags.index('[rec]') + 1] = 'arange' + sub_mon_arg[sub_mon_tags.index('[rec]') + 1].replace('-', ',')
                        if self.scale >= 1:
                            assert int(sub_mon_arg[sub_mon_tags.index('[rec]') + 1].split(',')[1]) < \
                                   self.customized_neurons_list[-1]['number_of_neurons'], \
                                " -  The stop index (%d) in the following monitor, is higher than" \
                                " the number of neurons in the group (%d): \n %s " % \
                                (int(sub_mon_arg[sub_mon_tags.index('[rec]') + 1].split(',')[1]),
                                 self.customized_neurons_list[-1]['number_of_neurons'], str(self.current_values_list.tolist()),)

                        elif int(sub_mon_arg[sub_mon_tags.index('[rec]') + 1].split(',')[1]) < self.customized_neurons_list[-1]['number_of_neurons']:
                            "\n Warning: The stop index (%d) in the following monitor, is higher than the number of neurons in the group (%d):" \
                            " \n %s . This is caused by using a scale < 1" \
                            % (int(sub_mon_arg[sub_mon_tags.index('[rec]') + 1].split(',')[1]),
                               self.customized_neurons_list[-1]['number_of_neurons'],
                               str(self.current_values_list.tolist()),)

                    assert len(sub_mon_arg) == len(sub_mon_tags) + 1, ' -  Error in monitor tag definition.'
                if sub_mon_arg[0] == '':
                    assert mon_tag == '[Sp]', ' -  The monitor state variable is not defined properly'
                    self.workspace.create_results_key('spikes_all')  # Create a key in save_data() object
                    # for that specific StateMonitor variable.
                    mon_name = monitor_options[mon_tag][0] + str(self.monitor_idx) + '_' + object_name

                    self.workspace.syntax_bank.append(
                        "self.workspace.results['spikes_all']['%s'] = %s.get_states()" % (object_name, mon_name))
                    mon_str = mon_name + mon_str
                else:
                    self.workspace.create_results_key('%s_all' % sub_mon_arg[0])  # Create a key in save_data()
                    # object for that specific StateMonitor variable.
                    mon_name = monitor_options[mon_tag][0] + str(self.monitor_idx) + '_' + object_name + '__' + sub_mon_arg[0]
                    # After simulation, the following syntax will be used to save this specific monitor's result:
                    # self.workspace.syntax_bank.append("self.workspace.data['%s_all']"
                    #                                          "['%s'] = %s.%s"
                    #                                          %(sub_mon_arg[0], object_name, mon_name, sub_mon_arg[0]))
                    self.workspace.syntax_bank.append("self.workspace.results['%s_all']"
                                                      "['%s'] = %s.get_states()"
                                                      % (sub_mon_arg[0], object_name, mon_name))
                    mon_str = mon_name + mon_str + ",'" + sub_mon_arg[0] + "'"
                    del (sub_mon_arg[0])
                    # add each of the tag and their argument,
                    # e.g. "record" as tag and "True" as argument, to the mon_str syntax string.
                    for idx, tag in enumerate(sub_mon_tags):
                        mon_str += monitor_options[tag][0] + sub_mon_arg[idx]

                self.monitor_name_bank[object_name].append(mon_name)
                mon_str += ')'
                # create the Monitor() object
                exec(mon_str)
                setattr(self.main_module, mon_name, eval(mon_name))
                try:
                    setattr(self.Cxmodule, mon_name, eval(mon_name))
                except AttributeError:
                    pass
                self.monitor_idx += 1

    def synapse(self):
        """
        The method that creates the Synapses() in brian2, based on the parameters that are extracted from
        the configuration file in the __init__ method of the class.

        Main internal variables:

        * mon_args: contains the monitor arguments extracted from the target line.
        * args: normally args contains a set of arguments for a single Synapses() object.
                However, this changes when the post-synaptic neuron is the first (with index of 0) compartment of a
                multi-compartmental neuron. In this case, one might intend to target all three sub-compartments,
                i.e. Basal dendrites, Soma and proximal apical dendrites. So the single set of arguments will be changed
                to 3 sets of arguments and a for loop will take care of every one of them.
        * dyn_syn_name: Generated variable name for the Synapses() object in brian2.
        * _dyn_syn_eq_name: Generated variable name for the Synapses() equation.
        * _dyn_syn_pre_eq_name: Generated variable name for pre_synaptic equations, i.e. "on_pre=..."
        * _dyn_syn_post_eq_name: Generated variable name for post_synaptic equations, i.e. "on_post= ..."
        * _dyn_syn_namespace_name: Generated variable name for the Synapses() namespace.
        * syn_con_str: The string containing the syntax for connect() method of a current Synapses() object. This string
                        changes depending on using the [p] and [n] tags in the configuration file.
        """
        _all_columns = ['receptor', 'pre_syn_idx', 'post_syn_idx', 'syn_type', 'p', 'n', 'monitors', 'load_connection',
                        'save_connection', 'custom_weight','spatial_decay']
        _obligatory_params = [0, 1, 2, 3]
        assert len(self.current_values_list) <= len(_all_columns), \
            ' -  One or more of the obligatory columns for input definition is missing. Obligatory columns are:\n%s\n ' \
            % str([_all_columns[ii] for ii in _obligatory_params])
        obligatory_columns = list(np.array(_all_columns)[_obligatory_params])
        obligatory_indices = [next(iter(self.current_parameters_list[self.current_parameters_list == ii].index)) for ii in obligatory_columns]
        assert not np.any(self.current_values_list.loc[obligatory_indices].isnull()), \
            ' -  Following obligatory values cannot be "--":\n%s' % str([_all_columns[ii] for ii in _obligatory_params])
        assert len(self.current_values_list) == self.current_parameters_list_orig_len, \
            " -  One or more of of the columns for synapse definition is missing in the following line:\n %s " % str(
                list(self.anat_and_sys_conf_df.loc[self.value_line_idx].to_dict().values()))
        _options = {
            '[C]': self.neuron_group,
        }
        # getting the connection probability gain from the namespace and apply it on all the connections:
        index_of_receptor = int(np.where(self.current_parameters_list.values == 'receptor')[0])
        index_of_post_syn_idx = int(np.where(self.current_parameters_list.values == 'post_syn_idx')[0])
        index_of_pre_syn_idx = int(np.where(self.current_parameters_list.values == 'pre_syn_idx')[0])
        index_of_syn_type = int(np.where(self.current_parameters_list.values == 'syn_type')[0])
        try:
            index_of_p = int(np.where(self.current_parameters_list.values == 'p')[0])
        except TypeError:
            pass
        try:
            index_of_n = int(np.where(self.current_parameters_list.values == 'n')[0])
        except TypeError:
            pass
        try:
            index_of_monitors = int(np.where(self.current_parameters_list.values == 'monitors')[0])
        except TypeError:
            pass
        try:
            index_of_spatial_decay = int(np.where(self.current_parameters_list.values == 'spatial_decay')[0])
        except TypeError:
            pass 
        current_post_syn_idx = self.current_values_list.values[index_of_post_syn_idx]
        current_pre_syn_idx = self.current_values_list.values[index_of_pre_syn_idx]
        try:
            _current_probs = self.current_values_list.values[index_of_p]
        except (ValueError, NameError):
            pass
        try:
            _current_ns = self.current_values_list.values[index_of_n]
        except (ValueError, NameError):
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
                _current_ns = list(map(float, _current_ns.split('+')))
            except NameError:
                pass
            except ValueError:
                assert _current_ns == '--', \
                    " -  When targeting multiple compartments near soma, their number of connections, i.e. 'n', should be defined separately. Unless it's marked as '--'"

            current_post_syn_tags = current_post_syn_idx[current_post_syn_idx.index('['):current_post_syn_idx.index(']') + 1]
            assert current_post_syn_tags in list(_options.keys()), \
                ' -  The synaptic tag %s is not defined.' % current_post_syn_tags
            if current_post_syn_tags == '[C]':  # [C] means the target is a compartment
                _post_group_idx, _post_com_idx = current_post_syn_idx.split('[' + 'C' + ']')
                assert int(_post_group_idx) < len(self.neurongroups_list), \
                    ' -  The synapse in the following line is targeting a group index that is not defined:\n%s' % str(
                        list(self.anat_and_sys_conf_df.loc[self.value_line_idx].to_dict().values()))
                self.current_values_list.values[index_of_post_syn_idx] = _post_group_idx
                pre_group_ref_idx = [self.customized_neurons_list.index(tmp_group) for tmp_group in
                                     self.customized_neurons_list if tmp_group['idx'] == int(current_pre_syn_idx)][0]
                post_group_ref_idx = [self.customized_neurons_list.index(tmp_group) for tmp_group in
                                      self.customized_neurons_list if tmp_group['idx'] == int(_post_group_idx)][0]
                assert self.customized_neurons_list[post_group_ref_idx]['type'] == 'PC', \
                    ' -  A compartment is targeted but the neuron group is not PC. Check Synapses in the configuration file.'
                _pre_type = self.customized_neurons_list[pre_group_ref_idx]['type']  # Pre-synaptic neuron type
                _post_type = self.customized_neurons_list[post_group_ref_idx]['type']  # Post-synaptic neuron type
                self.current_parameters_list = self.current_parameters_list.append(pd.Series(['pre_type', 'post_type', 'post_comp_name']),
                                                                                   ignore_index=True)
                self.current_values_list = self.current_values_list.append(pd.Series([_pre_type, _post_type]), ignore_index=True)
                #  In case the target is from compartment 0 which has 3 compartments itself
                if str(_post_com_idx)[0] == '0':
                    assert len(_post_com_idx) > 1, ' -  The soma layer of a compartmental neuron is being targeted, but the exact ' \
                                                   'compartment in the layer is not defined. After 0, use "b" for basal dendrites, ' \
                                                   '"s" for soma and "a" for apical dendrites.'
                    if _current_probs != '--':
                        assert len(_post_com_idx[1:]) == len(_current_probs), \
                            " -  When targeting multiple compartments near soma, their probability," \
                            " i.e. 'p', should be defined separately. Unless it's marked as '--'"
                    if _current_ns != '--':
                        assert len(_post_com_idx[1:]) == len(_current_ns), \
                            " -  When targeting multiple compartments near soma, their number of connections," \
                            " i.e. 'n', should be defined separately. Unless it's marked as '--'"
                    # creating the required synapses for targeting compartment 0, it can be at most 3 synapses (basal,
                    # soma or apical), hence the name triple_args
                    triple_args = []
                    for idx, tmp_idx in enumerate(_post_com_idx[1:]):
                        tmp_args = list(self.current_values_list)
                        if np.any(self.current_parameters_list.str.contains('p')):
                            tmp_args[index_of_p] = _current_probs[idx] if \
                                str(tmp_args[index_of_p]) != '--' else '--'
                        if np.any(self.current_parameters_list.str.contains('n')):
                            tmp_args[index_of_n] = _current_ns[idx] if \
                                str(tmp_args[index_of_n]) != '--' else '--'
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
                    self.current_values_list = self.current_values_list.append(pd.Series(['_a' + str(_post_com_idx)]), ignore_index=True)
            if type(self.current_values_list[0]) != list:  # type of self.current_values_list[0] would be list in case
                # of multiple synaptic targets in soma area
                self.current_values_list = [self.current_values_list]
        else:
            assert int(current_post_syn_idx) < len(self.neurongroups_list), \
                ' -  The synapse in the following line is targeting a group index that is not defined:\n%s' % str(
                    list(self.anat_and_sys_conf_df.loc[self.value_line_idx].to_dict().values()))
            pre_group_ref_idx = [self.customized_neurons_list.index(tmp_group) for tmp_group in
                                 self.customized_neurons_list if int(tmp_group['idx']) == int(current_pre_syn_idx)][0]
            post_group_ref_idx = [self.customized_neurons_list.index(tmp_group) for tmp_group in
                                  self.customized_neurons_list if int(tmp_group['idx']) == int(current_post_syn_idx)][0]
            _pre_type = self.customized_neurons_list[pre_group_ref_idx]['type']  # Pre-synaptic neuron type
            _post_type = self.customized_neurons_list[post_group_ref_idx]['type']  # Post-synaptic neuron type
            assert _post_type != 'PC', \
                ' -  The post_synaptic group is a multi-compartmental PC but the target compartment is' \
                ' not selected. Use [C] tag followed by compartment number.'
            self.current_values_list = self.current_values_list.append(pd.Series([_pre_type, _post_type, '_soma']), ignore_index=True)
            self.current_parameters_list = self.current_parameters_list.append(pd.Series(['pre_type', 'post_type', 'post_comp_name']),
                                                                               ignore_index=True)
            self.current_values_list = [self.current_values_list]
        for syn in self.current_values_list:
            receptor = syn[index_of_receptor]
            pre_syn_idx = syn[index_of_pre_syn_idx]
            post_syn_idx = syn[index_of_post_syn_idx]
            syn_type = syn[index_of_syn_type]
            try:
                p_arg = float(syn[index_of_p]) * self.conn_prob_gain
            except (ValueError, NameError):
                p_arg = '--'
            try:
                n_arg = syn[index_of_n]
            except (ValueError, NameError):
                n_arg = '--'
            try:
                monitors = syn[index_of_monitors]
            except (ValueError, NameError):
                monitors = '--'
            pre_type_idx = next(iter(self.current_parameters_list[self.current_parameters_list == 'pre_type'].index))
            pre_type = syn[pre_type_idx]
            post_type_idx = next(iter(self.current_parameters_list[self.current_parameters_list == 'post_type'].index))
            post_type = syn[post_type_idx]
            post_comp_idx = next(iter(self.current_parameters_list[self.current_parameters_list == 'post_comp_name'].index))
            post_comp_name = syn[post_comp_idx]

            # Get custom weight if defined
            try:
                custom_weight_idx = next(iter(self.current_parameters_list[self.current_parameters_list == 'custom_weight'].index))
                custom_weight = syn[custom_weight_idx]
            except (ValueError, NameError):
                custom_weight = '--'

            # check monitors in line:
            current_idx = len(self.customized_synapses_list)
            # creating a SynapseReference object and passing the positional arguments to it. The main member of
            # the class called output_synapse is then appended to customized_synapses_list:
            self.customized_synapses_list.append(SynapseReference(receptor, pre_syn_idx, post_syn_idx, syn_type,
                                                                  pre_type, post_type, self.physio_config_df, post_comp_name,
                                                                  custom_weight).output_synapse)
            _pre_group_idx = self.neurongroups_list[self.customized_synapses_list[-1]['pre_group_idx']]
            _post_group_idx = self.neurongroups_list[self.customized_synapses_list[-1]['post_group_idx']]
            # Generated variable name for the Synapses(), equation, pre_synaptic and post_synaptic equation and Namespace
            _dyn_syn_name = self._Synapses_prefix + str(current_idx) + '_' + syn_type + '_' + _pre_group_idx + '__to__' + _post_group_idx
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

            # creating the initial synaptic connection :
            try:
                exec("%s = b2.Synapses(%s,%s,model = %s, on_pre = %s, on_post = %s, namespace= %s, delay= %s )"
                     % (_dyn_syn_name, _pre_group_idx, _post_group_idx,
                        _dyn_syn_eq_name, _dyn_syn_pre_eq_name, _dyn_syn_post_eq_name, _dyn_syn_namespace_name,
                        eval(_dyn_syn_namespace_name)['delay']))
            except NameError:  # for when there is no "on_post =...", i.e. fixed connection
                exec("%s = b2.Synapses(%s,%s,model = %s, on_pre = %s, "
                     "namespace= %s, delay = %s)"
                     % (_dyn_syn_name, _pre_group_idx, _post_group_idx,
                        _dyn_syn_eq_name, _dyn_syn_pre_eq_name, _dyn_syn_namespace_name, eval(_dyn_syn_namespace_name)['delay']))

            # Connecting synapses

            # Technical preparations & parameter parsing first
            _syn_ref_name = self.neurongroups_list[int(current_pre_syn_idx)][self.neurongroups_list[int(
                current_pre_syn_idx)].index('_') + 1:] + "__to__" + self.neurongroups_list[self.
                customized_synapses_list[-1]['post_group_idx']][self.neurongroups_list[self. \
                customized_synapses_list[-1]['post_group_idx']].index('_') + 1:] + \
                            self.customized_synapses_list[-1]['post_comp_name']
            try:
                index_of_load_connection = int(np.where(self.current_parameters_list.values == 'load_connection')[0])
                if '-->' in syn[index_of_load_connection]:
                    self.default_load_flag = int(syn[index_of_load_connection].replace('-->', ''))
                elif '<--' in syn[index_of_load_connection]:
                    self.default_load_flag = -1
                    _do_load = int(syn[index_of_load_connection].replace('<--', ''))
                    if _do_load == 1:
                        assert hasattr(self, 'imported_connections'), \
                            " -  Synaptic connection in the following line is set to be loaded, however the import_connection_from" \
                            " is not defined in the parameters. The connection is being created:\n%s" \
                            % str(list(self.anat_and_sys_conf_df.loc[self.value_line_idx].to_dict().values()))
                else:
                    load_connection_idx = next(iter(self.current_parameters_list[self.current_parameters_list == 'load_connection'].index),
                                               'no match')
                    _do_load = int(syn[load_connection_idx])
            except TypeError:
                _do_load = 0
                pass

            if (self.default_load_flag == 1 or (self.default_load_flag == -1 and _do_load == 1)) and not hasattr(self, 'imported_connections'):
                # only load the file if it's not loaded already, and if the connections are supposed to tbe loaded frmo the file
                self.set_import_connections_path()

            try:
                index_of_save_connection = int(np.where(self.current_parameters_list.values == 'save_connection')[0])
                if '-->' in syn[index_of_save_connection]:
                    self.default_save_flag = int(syn[index_of_save_connection].replace('-->', ''))
                elif '<--' in syn[index_of_save_connection]:
                    self.default_save_flag = -1
                    _do_save = int(syn[index_of_save_connection].replace('<--', ''))
                else:
                    _do_save = int(syn[index_of_save_connection])
            except TypeError:
                _do_save = 0
                pass

            # Loading connections from file
            if (self.default_load_flag == 1 or (self.default_load_flag == -1 and _do_load == 1)) and \
                    hasattr(self, 'imported_connections') and not self.load_positions_only:
                assert _syn_ref_name in list(self.imported_connections.keys()), \
                    " -  The data for the following connection was not found in the loaded brian data: %s" % _syn_ref_name

                # 1) Try-except necessary; run fails if no connections exist from 1 group to another
                # 2) Indexing changed in pd >0.19.1 and thus ...['data'][0][0].tocoo() --> ...['data'].tocoo()
                #    Unfortunately pd doesn't warn about this change in indexing
                try:
                    eval(_dyn_syn_name).connect(i=self.imported_connections[_syn_ref_name]['data'].tocoo().row,
                                                j=self.imported_connections[_syn_ref_name]['data'].tocoo().col,
                                                n=int(self.imported_connections[_syn_ref_name]['n']))
                    # Weight is redeclared later, see line ~1200.
                    # Also, 1) "loading connections" leaves the impression of loading anatomical connections, not synaptic weights
                    #       2) we do not have need for saving/loading synaptic weights at this point
                    #       3) it doesn't work in pd >0.19.1
                    # Therefore I commented:
                    # eval(_dyn_syn_name).wght = b2.repeat(self.imported_connections[_syn_ref_name]['data'][0][0].data/int(self.\
                    #     imported_connections[_syn_ref_name]['n']),int(self.imported_connections[_syn_ref_name]['n'])) * siemens
                    _load_str = 'Connection loaded from '
                except ValueError:
                    _load_str = ' ! No connections from '

            elif (self.default_load_flag == 1 or (self.default_load_flag == -1 and _do_load == 1)) and not \
                    hasattr(self, 'imported_connections'):
                print(" -  Synaptic connection is set to be loaded, however "
                      "the import_connections_from is not defined in the "
                      "parameters. The connection is being created.")

            # Generating new connections using
            #  - connection probability ("local mode")
            #  - connection probability scaled with distance ("expanded mode")
            #  - custom connection rule
            else:
                def exp_distance_function(p_arg=None, spatial_decay='0'):
                    if p_arg==None or p_arg == '--':
                        print(' !  No predefined connection probability, '
                            'using custom connection rule')
                        p_arg = self.customized_synapses_list[-1]['sparseness']

                    # spatial_decay is assumed to be in 1/mm. At 1/spatial_decay distance, the connection probability is about 37%

                    # Assume spatial_decay = '0', local connectivity, no decay with distance
                    if spatial_decay=='0':
                        syn_con_str = "%s.connect(condition='i!=j', p= " % _dyn_syn_name
                        syn_con_str += "'%f'" % float(p_arg)
                        return syn_con_str

                    # If spatial_decay=='[ij]', connect one to one only. Must be the same N neurons.
                    if spatial_decay=='[ij]':
                        syn_con_str = "%s.connect(j='i'" % _dyn_syn_name
                        return syn_con_str

                    # If spatial_decay includes '[i=j]' but also numerical value, connect one-to-one and lambda
                    if '[ij]' in spatial_decay and not spatial_decay=='[ij]':
                        syn_con_str = "%s.connect(p= " % _dyn_syn_name
                        spatial_decay=spatial_decay.replace('[ij]','') # Strip [ij] away
                        
                    # If spatial_decay does not include '[i=j]', exclude autoconnection, use only lambda
                    elif '[ij]' not in spatial_decay:
                        syn_con_str = "%s.connect(condition='i!=j', p= " % _dyn_syn_name

                    syn_con_str += "'%f*exp(-(%f*meter/mm)*(sqrt((x_pre-x_post)**2+(y_pre-y_post)**2)))'" % (
                        float(p_arg), float(spatial_decay))
                    return syn_con_str

                #Check if p_arg exists, set to None if not
                if 'p_arg' not in {**locals(), **globals()}:
                    p_arg=None

                # Check mode, catch missing spatial_decay
                if self.sys_mode == 'local':
                    spatial_decay = '0'

                elif self.sys_mode == 'expanded':
                    try:
                        spatial_decay=syn[index_of_spatial_decay]
                    except (ValueError, NameError):
                        # If the length constant has not been defined, set it to 0 corresponding to local mode, ie no decay with distance
                        spatial_decay = '0'                        

 
                if '_relay_vpm' in self.neurongroups_list[int(current_pre_syn_idx)] and p_arg==None:
                    spatial_decay = str(1/(2*0.025**2))

                elif '_relay_spikes' in self.neurongroups_list[int(current_pre_syn_idx)]:
                    spatial_decay = '10'
                # import pdb;pdb.set_trace()

                syn_con_str = exp_distance_function(p_arg=p_arg, spatial_decay=spatial_decay)

                try:
                    syn_con_str += ',n=%d)' % int(n_arg)
                except ValueError:
                    syn_con_str += ')'
                exec(syn_con_str)

            # Weight set again (overrided) here if connections were loaded
            exec("%s.wght=%s['init_wght']" % (_dyn_syn_name,
                                              _dyn_syn_namespace_name))  #
            # set the weights
            if syn_type == 'STDP':  # A more sophisticated if: 'wght0' in self.customized_synapses_list[-1]['equation']
                exec("%s.wght0=%s['init_wght']" % (_dyn_syn_name,
                                                   _dyn_syn_namespace_name)
                     )  # set the weights
            # # the next two lines are commented out for GeNN and are added as a parameter when creating syn
            # exec("%s.delay=%s['delay']" % (_dyn_syn_name,
            #                                 _dyn_syn_namespace_name) ) # set the delays
            setattr(self.main_module, _dyn_syn_name, eval(_dyn_syn_name))
            try:
                setattr(self.Cxmodule, _dyn_syn_name, eval(_dyn_syn_name))
            except AttributeError:
                pass

            self.monitors(monitors.split(' '), _dyn_syn_name) #, self.customized_synapses_list[-1]['equation'])

            if self.device.lower() == 'python':
                tmp_namespace = {'num_tmp': 0}
                exec("tmp_namespace['num_tmp'] = len(%s.i)" % _dyn_syn_name)
                num_tmp = tmp_namespace['num_tmp']
                self.total_number_of_synapses += num_tmp
                try:
                    n_idx = next(iter(self.current_parameters_list[self.current_parameters_list == 'n'].index), 'no match')
                    _current_connections = int(num_tmp / float(syn[n_idx])) / len(self.current_values_list)
                except ValueError:
                    print(" -  number of synapses for last connection was "
                          "equal to number of connections")
                    _current_connections = num_tmp
                self.total_number_of_connections += _current_connections
                try:
                    print(" -  %s%s to %s: Number of synapses %d \t Number "
                          "of connections: %d \t Total synapses: %d \t " "Total connections: %d"
                          % (_load_str, _pre_group_idx, _post_group_idx, num_tmp, _current_connections,
                             self.total_number_of_synapses,
                             self.total_number_of_connections))
                except (ValueError, UnboundLocalError):
                    print(" -  Connection created from %s to %s: Number of "
                          "synapses %d \t Number of connections: %d \t Total synapses: %d \t Total connections: %d"
                          % (_pre_group_idx, _post_group_idx, num_tmp, _current_connections,
                             self.total_number_of_synapses,
                             self.total_number_of_connections))
            else:
                try:
                    print(" -  %s%s to %s" % (_load_str, _pre_group_idx,
                                              _post_group_idx))
                except UnboundLocalError:
                    print(" -  Connection created from %s to %s" % (
                        _pre_group_idx, _post_group_idx))
            if self.default_save_flag == 1 or (self.default_save_flag == -1 and _do_save):
                self.do_save_connections = 1
                self.workspace.create_connections_key(_syn_ref_name)
                self.workspace.syntax_bank.append(
                    'self.workspace.connections["%s"]["data"] ='
                    ' scprs.csr_matrix((%s.wght[:],(%s.i[:],%s.j[:])),shape=(len(%s.source),len(%s.target)))'
                    % (_syn_ref_name, _dyn_syn_name, _dyn_syn_name, _dyn_syn_name, _dyn_syn_name, _dyn_syn_name))
                self.workspace.syntax_bank.append('self.workspace.connections["%s"]["n"] = %d' % (_syn_ref_name, int(n_arg)))
            # elif (self.default_save_flag==1 or (self.default_save_flag==-1 and _do_save )) and \
            #         not hasattr(self,'workspace') :
            #     raise ValueError(" -  Synaptic connection is set to be saved, however the save_brian_data_path parameter is not defined.")

    def relay(self):
        """
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

        Main internal variables:

        * inp: an instance of stimuli() object from stimuli module.
        * relay_group: the dictionary containing the data for relay NeuronGroup()
        * _dyn_neurongroup_name: Generated variable name for the NeuronGroup() object in brian2.
        * _dyn_neuronnumber_name: Generated variable name for corresponding Neuron Number.
        * _dyn_neuron_eq_name: Generated variable name for the NeuronGroup() equation.
        * _dyn_neuron_thres_name: Generated variable name for the NeuronGroup() threshold.
        * _dyn_neuron_reset_name: Generated variable name for the NeuronGroup() reset value.
        * sg_syn_name: variable name for the Synapses() object that connects SpikeGeneratorGroup() and relay neurons.

        following four variables are build using the load_input_seq() method in stimuli object:

        * spikes_str: The string containing the syntax for Spike indices in the input neuron group.
        * times_str: The string containing the syntax for time indices in the input neuron group.
        * sg_str: The string containing the syntax for creating the SpikeGeneratorGroup() based on the input .mat file.
        * number_of_neurons: The number of neurons that exist in the input .mat file.
        """
        _dyn_neurongroup_name = ''
        if not hasattr(self.workspace, 'simulation_name'):
            raise ParameterNotFoundError("The parameter 'simulation_title' is not defined in the configuration file ")

        def video(self):
            print(" -  Creating an input based on the video input ...")
            input_mat_path = self.current_values_list[self.current_parameters_list[self.current_parameters_list == 'path'].index.item()]
            freq = self.current_values_list[self.current_parameters_list[self.current_parameters_list == 'freq'].index.item()]
            inp = Stimuli(duration=self.runtime, input_mat_path=input_mat_path, output_folder=self.workspace.get_simulation_folder_as_posix(),
                          output_file_suffix=self.StartTime_str, output_file_extension=self.workspace.get_output_extension())
            proc = multiprocessing.Process(target=inp.generate_inputs, args=(freq,))
            proc.start()
            self.video_input_idx = len(self.neurongroups_list)
            self.neurongroups_list.append('awaiting_video_group')

            def waitress(self):
                time.sleep(3)
                while proc.is_alive():
                    time.sleep(1)
                spk_generator_sp, spk_generator_ti, thread_number_of_neurons = inp.load_input_seq(self.workspace.get_simulation_folder_as_posix())
                if not self.save_input_video:
                    print(" - :  generated video output is NOT saved.")
                    os.remove(self.workspace.get_simulation_folder().joinpath(
                        'input' + self.StartTime_str + self.workspace.get_output_extension()).as_posix())
                spk_generator = b2.SpikeGeneratorGroup(thread_number_of_neurons, spk_generator_sp, spk_generator_ti)
                setattr(self.main_module, 'spk_generator', spk_generator)
                try:
                    setattr(self.Cxmodule, 'spk_generator', spk_generator)
                except AttributeError:
                    pass
                # Generated variable name for the NeuronGroup, Neuron_number,Equation, Threshold, Reset
                thread_ng_name = self._NeuronGroup_prefix + str(self.video_input_idx) + '_relay_video'
                self.neurongroups_list[self.video_input_idx] = thread_ng_name
                thread_nn_name = self._NeuronNumber_prefix + str(self.video_input_idx)
                thread_ne_name = self._NeuronEquation_prefix + str(self.video_input_idx)
                thread_nt_name = self._NeuronThreshold_prefix + str(self.video_input_idx)
                thread_n_res_name = self._NeuronReset_prefix + str(self.video_input_idx)
                eq = """'''emit_spike : 1
                    x : meter
                    y : meter'''"""
                # In order to use the dynamic compiler in a sub-routine, the scope in which the syntax is going to be run
                # should be defined, hence the globals(), locals(). They indicate that the syntaxes should be run in both
                # global and local scope
                exec("%s=%s" % (thread_nn_name, thread_number_of_neurons),
                     globals(), locals())
                exec("%s=%s" % (thread_ne_name, eq), globals(), locals())
                exec("%s=%s" % (thread_nt_name, "'emit_spike>=1'"),
                     globals(), locals())
                exec("%s=%s" % (thread_n_res_name, "'emit_spike=0'"),
                     globals(), locals())
                exec("%s= b2.NeuronGroup(%s, model=%s,method='%s', "
                     "threshold=%s, reset=%s)" % (thread_ng_name,
                                                  thread_nn_name,
                                                  thread_ne_name,
                                                  self.numerical_integration_method,
                                                  thread_nt_name,
                                                  thread_n_res_name),
                     globals(),
                     locals())
                if hasattr(self, 'imported_connections'):
                    # in case the NG index are different. for example a MC_L2 neuron might have had
                    # index 3 as NG3_MC_L2 and now it's NG10_MC_L2 :
                    thread_group_type = thread_ng_name[thread_ng_name.index('_') + 1:]
                    thread_group_key_name = \
                        [kk for kk in list(self.imported_connections['positions_all']['w_coord'].keys()) if thread_group_type in kk][0]
                    self.customized_neurons_list[self.video_input_idx]['w_positions'] = \
                        self.imported_connections['positions_all']['w_coord'][thread_group_key_name]
                    self.customized_neurons_list[self.video_input_idx]['z_positions'] = \
                        self.imported_connections['positions_all']['z_coord'][thread_group_key_name]
                    print(" -  Position for the group %s loaded" %
                          thread_ng_name)
                else:  # load the positions:
                    self.customized_neurons_list[self.video_input_idx]['z_positions'] = np.squeeze(inp.get_input_positions())
                    self.customized_neurons_list[self.video_input_idx]['w_positions'] = 17 * log(relay_group['z_positions'] + 1)

                # setting the position of the neurons based on the positions in the .mat input file:
                exec("%s.x=b2.real(self.customized_neurons_list[%d]["
                     "'w_positions'])*mm\n"
                     "%s.y=b2.imag(self.customized_neurons_list[%d]['w_positions'])*mm" %
                     (thread_ng_name, self.video_input_idx, thread_ng_name,
                      self.video_input_idx), globals(), locals())
                self.workspace.results['positions_all']['z_coord'][thread_ng_name] = \
                    self.customized_neurons_list[self.video_input_idx]['z_positions']
                self.workspace.results['positions_all']['w_coord'][thread_ng_name] = \
                    self.customized_neurons_list[self.video_input_idx]['w_positions']
                self.workspace.results['number_of_neurons'][thread_ng_name] = eval(thread_nn_name)
                thread_sg_syn_name = 'SGEN_Syn'  # variable name for the Synapses() object
                # that connects b2.SpikeGeneratorGroup() and relay neurons.
                exec("%s = b2.Synapses(spk_generator, %s, "
                     "on_pre='emit_spike+=1')" %
                     (thread_sg_syn_name, thread_ng_name), globals(),
                     locals())  # connecting the b2.SpikeGeneratorGroup() and relay group.
                exec("%s.connect(j='i')" % thread_sg_syn_name, globals(),
                     locals())  # SV change
                setattr(self.main_module, thread_ng_name, eval(thread_ng_name))
                setattr(self.main_module, thread_sg_syn_name, eval(thread_sg_syn_name))
                try:
                    setattr(self.Cxmodule, thread_ng_name, eval(thread_ng_name))
                    setattr(self.Cxmodule, thread_sg_syn_name, eval(thread_sg_syn_name))
                except AttributeError:
                    pass
                # taking care of the monitors:
                self.monitors(mons.split(' '), thread_ng_name) #, self.customized_neurons_list[-1]['equation'])

            # input_neuron_group_idx = self.current_values_list[self.current_parameters_list[self.current_parameters_list=='idx'].index.item()]
            syn_lines = self.anat_and_sys_conf_df[self.anat_and_sys_conf_df[0].str.startswith('S') == True]
            input_synaptic_lines = syn_lines[syn_lines[2] == '0']
            row_type_lines = self.anat_and_sys_conf_df.loc[:input_synaptic_lines.index[0]][0].str.startswith('row_type') == True
            synapse_def_line = self.anat_and_sys_conf_df.loc[row_type_lines[row_type_lines == True].index[-1]]
            load_conn_idx = synapse_def_line[synapse_def_line == 'load_connection'].index[0]
            save_conn_idx = synapse_def_line[synapse_def_line == 'save_connection'].index[0]
            for conn_load_item in input_synaptic_lines[load_conn_idx]:
                if '<--' in conn_load_item or '-->' in conn_load_item:
                    for synaptic_row in range(input_synaptic_lines.index[0] + 1, self.anat_and_sys_conf_df[0].index[-1]):
                        if self.anat_and_sys_conf_df.loc[synaptic_row][0][0] != '#':
                            sign_to_add = '-->' if '-->' in conn_load_item else '<--'
                            self.anat_and_sys_conf_df.loc[input_synaptic_lines.index[0] + 1, load_conn_idx] += sign_to_add
                            break
            for conn_save_item in input_synaptic_lines[save_conn_idx]:
                if '<--' in conn_save_item or '-->' in conn_save_item:
                    for synaptic_row in range(input_synaptic_lines.index[0] + 1, self.anat_and_sys_conf_df[0].index[-1]):
                        if self.anat_and_sys_conf_df.loc[synaptic_row][0][0] != '#':
                            sign_to_add = '-->' if '-->' in conn_save_item else '<--'
                            self.anat_and_sys_conf_df.loc[input_synaptic_lines.index[0] + 1, save_conn_idx] += sign_to_add
                            break
            self.awaited_conf_lines = synapse_def_line.to_frame().transpose().reset_index(drop=True).append(input_synaptic_lines).reset_index(
                drop=True)
            self.anat_and_sys_conf_df = self.anat_and_sys_conf_df.drop(input_synaptic_lines.index.tolist()).reset_index(drop=True)
            self.thr = threading.Thread(target=waitress, args=(self,))
            self.thr.start()
            # if inp.file_exist_flag:
            #     self.thr.join()

        def VPM(self):  # ventral posteromedial (VPM) thalamic nucleus
            spike_times_idx = next(iter(self.current_parameters_list[self.current_parameters_list == 'spike_times'].index))
            spike_times = self.current_values_list[spike_times_idx].replace(' ', ',')
            spike_times_list = ast.literal_eval(spike_times[0:spike_times.index('*')])
            spike_times_unit = spike_times[spike_times.index('*') + 1:]
            tmp_namespace = {"spike_times_": []}
            exec('tmp_namespace ["spike_times_"] = spike_times_list * %s' % spike_times_unit,
                 locals(), globals())
            spike_times_ = tmp_namespace["spike_times_"]
            try:
                tmp_net_center_idx = next(iter(self.current_parameters_list[self.current_parameters_list == 'net_center'].index), 'no match')
                net_center = self.current_values_list[tmp_net_center_idx]
                net_center = complex(net_center)
            except ValueError:
                net_center = 0 + 0j
            num_of_neurons_idx = next(iter(self.current_parameters_list[self.current_parameters_list == 'number_of_neurons'].index))
            number_of_neurons = self.current_values_list[num_of_neurons_idx]

            radius_idx = next(iter(self.current_parameters_list[self.current_parameters_list == 'radius'].index))
            radius = self.current_values_list[radius_idx]
            print(" -  Creating an input based on the central %s neurons "
                  "..." % number_of_neurons)
            spikes_name = 'GEN_SP'
            time_name = 'GEN_TI'
            sg_name = 'GEN'
            spikes_str = 'GEN_SP=b2.tile(arange(%s),%d)' % (number_of_neurons, len(spike_times_))
            times_str = 'GEN_TI = b2.repeat(%s,%s)*%s' % (spike_times[0:spike_times.index('*')], number_of_neurons, spike_times_unit)
            sg_str = 'GEN = b2.SpikeGeneratorGroup(%s, GEN_SP, GEN_TI)' % number_of_neurons
            exec(spikes_str, globals(), locals())  # running the string
            # containing the syntax for Spike indices in the input neuron group.
            exec(times_str, globals(), locals())  # running the string
            # containing the syntax for time indices in the input neuron group.
            exec(sg_str, globals(), locals())  # running the string
            # containing the syntax for creating the b2.SpikeGeneratorGroup() based on the input .mat file.

            setattr(self.main_module, sg_name, eval(sg_name))
            try:
                setattr(self.Cxmodule, sg_name, eval(sg_name))
            except AttributeError:
                pass

            _dyn_neurongroup_name = self._NeuronGroup_prefix + str(
                current_idx) + '_relay_vpm'  # Generated variable name for the NeuronGroup() object in brian2.
            self.neurongroups_list.append(_dyn_neurongroup_name)
            _dyn_neuronnumber_name = self._NeuronNumber_prefix + str(current_idx)  # Generated variable name for corresponding Neuron Number.
            _dyn_neuron_eq_name = self._NeuronEquation_prefix + str(current_idx)  # Generated variable name for the NeuronGroup() equation.
            _dyn_neuron_thres_name = self._NeuronThreshold_prefix + str(current_idx)  # Generated variable name for the NeuronGroup() threshold.
            _dyn_neuron_reset_name = self._NeuronReset_prefix + str(current_idx)  # Generated variable name for the NeuronGroup() reset value.
            eq = """'''emit_spike : 1
                            x : meter
                            y : meter'''"""
            exec("%s=%s" % (_dyn_neuronnumber_name, number_of_neurons),
                 globals(), locals())
            exec("%s=%s" % (_dyn_neuron_eq_name, eq), locals(), globals())
            exec("%s=%s" % (_dyn_neuron_thres_name, "'emit_spike>=1'"),
                 globals(), locals())
            exec("%s=%s" % (_dyn_neuron_reset_name, "'emit_spike=0'"),
                 globals(), locals())
            exec("%s= b2.NeuronGroup(%s, model=%s, method='%s',threshold=%s, "
                 "reset=%s)"
                 % (_dyn_neurongroup_name, _dyn_neuronnumber_name,
                    _dyn_neuron_eq_name, self.numerical_integration_method,
                    _dyn_neuron_thres_name, _dyn_neuron_reset_name), globals(), locals())
            if hasattr(self, 'imported_connections'):  # load the positions if available
                # in case the NG index are different. for example a MC_L2 neuron might have had
                # index 3 as NG3_MC_L2 and now it's NG10_MC_L2 :
                group_type = _dyn_neurongroup_name[_dyn_neurongroup_name.index('_') + 1:]
                group_key_name = \
                    [kk for kk in list(self.imported_connections['positions_all']['w_coord'].keys()) if group_type in kk][0]
                self.customized_neurons_list[current_idx]['w_positions'] = self.imported_connections['positions_all']['w_coord'][group_key_name]
                self.customized_neurons_list[current_idx]['z_positions'] = self.imported_connections['positions_all']['z_coord'][group_key_name]
                print(" -  Positions for the group %s loaded" %
                      _dyn_neurongroup_name)
            else:  # generating the positions:
                vpm_customized_neuron = NeuronReference(current_idx, int(number_of_neurons), 'VPM', '0', eval(radius),
                                                        self.min_distance, self.physio_config_df, network_center=net_center)
                self.customized_neurons_list[current_idx]['z_positions'] = vpm_customized_neuron.output_neuron[
                    'z_positions']
                self.customized_neurons_list[current_idx]['w_positions'] = vpm_customized_neuron.output_neuron[
                    'w_positions']
            # setting the position of the neurons:
            exec("%s.x=b2.real(self.customized_neurons_list[%d]["
                 "'w_positions'])*mm\n"
                 "%s.y=b2.imag(self.customized_neurons_list[%d]['w_positions'])*mm"
                 % (_dyn_neurongroup_name, current_idx, _dyn_neurongroup_name,
                    current_idx), globals(), locals())
            # saving the positions :
            self.workspace.results['positions_all']['z_coord'][_dyn_neurongroup_name] = self.customized_neurons_list[current_idx]['z_positions']
            self.workspace.results['positions_all']['w_coord'][_dyn_neurongroup_name] = self.customized_neurons_list[current_idx]['w_positions']
            self.workspace.results['number_of_neurons'][_dyn_neurongroup_name] = eval(_dyn_neuronnumber_name)
            sg_syn_name = 'SGEN_Syn'  # variable name for the Synapses() object
            # that connects b2.SpikeGeneratorGroup() and relay neurons.
            exec("%s = b2.Synapses(GEN, %s, on_pre='emit_spike+=1')" % (sg_syn_name, _dyn_neurongroup_name), globals(), locals())
            # connecting the b2.SpikeGeneratorGroup() and relay group.
            eval(sg_syn_name).connect(j='i')
            setattr(self.main_module, _dyn_neurongroup_name, eval(_dyn_neurongroup_name))
            setattr(self.main_module, sg_syn_name, eval(sg_syn_name))
            try:
                setattr(self.Cxmodule, _dyn_neurongroup_name, eval(_dyn_neurongroup_name))
                setattr(self.Cxmodule, sg_syn_name, eval(sg_syn_name))
            except AttributeError:
                pass
            # taking care of the monitors:
            self.monitors(mons.split(' '), _dyn_neurongroup_name) # , self.customized_neurons_list[-1]['equation'])

        def spikes(self):
            input_spikes_filename = self.current_values_list[
                self.current_parameters_list[self.current_parameters_list == 'input_spikes_filename'].index.item()]
            spikes_data = load_from_file(self.workspace.get_simulation_folder().joinpath(input_spikes_filename))
            print(" -   Spike file loaded from: %s" % self.workspace.get_simulation_folder().joinpath(input_spikes_filename))
            spk_generator_sp = spikes_data['spikes_0'][0]
            spk_generator_ti = spikes_data['spikes_0'][1]
            number_of_neurons = len(spikes_data['w_coord'])
            spk_generator = b2.SpikeGeneratorGroup(number_of_neurons, spk_generator_sp, spk_generator_ti)
            setattr(self.main_module, 'spk_generator', spk_generator)
            try:
                setattr(self.Cxmodule, 'spk_generator', spk_generator)
            except AttributeError:
                pass
            # Generated variable name for the NeuronGroup, Neuron_number,Equation, Threshold, Reset
            self.spike_input_group_idx = len(self.neurongroups_list)
            ng_name = self._NeuronGroup_prefix + str(self.spike_input_group_idx) + '_relay_spikes'
            self.neurongroups_list.append(ng_name)
            nn_name = self._NeuronNumber_prefix + str(self.spike_input_group_idx)
            ne_name = self._NeuronEquation_prefix + str(self.spike_input_group_idx)
            nt_name = self._NeuronThreshold_prefix + str(self.spike_input_group_idx)
            n_res_name = self._NeuronReset_prefix + str(self.spike_input_group_idx)
            eq = """'''emit_spike : 1
                                x : meter
                                y : meter'''"""
            # In order to use the dynamic compiler in a sub-routine, the scope in which the syntax is going to be run
            # should be defined, hence the globals(), locals(). They indicate that the syntaxes should be run in both
            # global and local scope
            exec("%s=%s" % (nn_name, number_of_neurons), globals(), locals())
            exec("%s=%s" % (ne_name, eq), globals(), locals())
            exec("%s=%s" % (nt_name, "'emit_spike>=1'"), globals(), locals())
            exec("%s=%s" % (n_res_name, "'emit_spike=0'"), globals(),
                 locals())
            exec("%s= b2.NeuronGroup(%s, model=%s,method='%s', threshold=%s, "
                 "reset=%s)" % (ng_name, nn_name, ne_name, self.numerical_integration_method, nt_name, n_res_name), globals(), locals())
            if hasattr(self, 'imported_connections'):
                # in case the NG index are different. for example a MC_L2 neuron might have had
                # index 3 as NG3_MC_L2 and now it's NG10_MC_L2 :
                group_type = ng_name[ng_name.index('_') + 1:]
                group_key_name = \
                    [kk for kk in list(self.imported_connections['positions_all']['w_coord'].keys()) if group_type in kk][
                        0]
                self.customized_neurons_list[self.spike_input_group_idx]['w_positions'] = \
                    self.imported_connections['positions_all']['w_coord'][group_key_name]
                self.customized_neurons_list[self.spike_input_group_idx]['z_positions'] = \
                    self.imported_connections['positions_all']['z_coord'][group_key_name]
                print(" -  Position for the group %s loaded" % ng_name)
            else:  # load the positions:
                self.customized_neurons_list[self.spike_input_group_idx]['z_positions'] = np.squeeze(spikes_data['z_coord'])
                self.customized_neurons_list[self.spike_input_group_idx]['w_positions'] = np.squeeze(spikes_data['w_coord'])

            # setting the position of the neurons based on the positions in the .mat input file:
            exec("%s.x=b2.real(self.customized_neurons_list[%d]["
                 "'w_positions'])*mm\n"
                 "%s.y=b2.imag(self.customized_neurons_list[%d]['w_positions'])*mm" %
                 (ng_name, self.spike_input_group_idx, ng_name,
                  self.spike_input_group_idx), globals(), locals())
            self.workspace.results['positions_all']['z_coord'][ng_name] = \
                self.customized_neurons_list[self.spike_input_group_idx]['z_positions']
            self.workspace.results['positions_all']['w_coord'][ng_name] = \
                self.customized_neurons_list[self.spike_input_group_idx]['w_positions']
            self.workspace.results['number_of_neurons'][ng_name] = eval(nn_name)
            sg_syn_name = 'SGEN_Syn'  # variable name for the Synapses() object
            # that connects b2.SpikeGeneratorGroup() and relay neurons.
            exec("%s = b2.Synapses(spk_generator, %s, on_pre='emit_spike+=1')" %
                 (sg_syn_name, ng_name), globals(), locals())
            # connecting the b2.SpikeGeneratorGroup() and relay group.
            exec("%s.connect(j='i')" % sg_syn_name, globals(), locals())  #
            # SV change
            setattr(self.main_module, ng_name, eval(ng_name))
            setattr(self.main_module, sg_syn_name, eval(sg_syn_name))
            try:
                setattr(self.Cxmodule, ng_name, eval(ng_name))
                setattr(self.Cxmodule, sg_syn_name, eval(sg_syn_name))
            except AttributeError:
                pass
            # taking care of the monitors:
            self.monitors(mons.split(' '), ng_name) #, self.customized_neurons_list[-1]['equation'])

        assert self.sys_mode != '', " -  System mode not defined."
        assert np.any(self.current_parameters_list.str.contains('type')), ' -  The type of the input is not defined in the configuration file.'
        input_type_to_method_mapping = {
            # input type : [ columns , obligatory column indices,  sub-routine to call     ]
            'Video': [['idx', 'type', 'path', 'freq', 'monitors'], [0, 1, 2], video],
            'VPM': [['idx', 'type', 'number_of_neurons', 'radius', 'spike_times', 'net_center', 'monitors'], [0, 1, 2, 3, 4], VPM],
            'spikes': [['idx', 'type', 'input_spikes_filename', 'monitors'], [0, 1, 2], spikes]
        }
        param_idx = next(
            iter(self.current_parameters_list[self.current_parameters_list == 'type'].index))  # this is equivalent to item() which is deprecated
        _input_type = self.current_values_list[param_idx]
        _all_columns = input_type_to_method_mapping[_input_type][
            0]  # all possible columns of parameters for the current type of input in configuration fil
        assert _input_type in list(input_type_to_method_mapping.keys()), ' -  The input type %s of the configuration file is ' \
                                                                         'not defined' % _input_type

        _obligatory_params = input_type_to_method_mapping[_input_type][1]
        assert len(self.current_values_list) >= len(_obligatory_params), \
            ' -  One or more of of the columns for input definition is missing. Following obligatory columns should be defined:\n%s\n' % str(
                [_all_columns[ii] for ii in _obligatory_params])
        assert len(self.current_parameters_list) <= len(input_type_to_method_mapping[_input_type][0]), ' -  Too many parameters for the\
         current %s input. The parameters should be consist of:\n %s' % (_input_type, input_type_to_method_mapping[_input_type][0])
        obligatory_columns = list(np.array(input_type_to_method_mapping[_input_type][0])[input_type_to_method_mapping[_input_type][1]])
        # next(iter()) is equivalent to item() which is deprecated
        obligatory_indices = [next(iter(self.current_parameters_list[self.current_parameters_list == ii].index)) for ii in obligatory_columns]
        assert not np.any(self.current_values_list.loc[obligatory_indices] == '--'), \
            ' -  Following obligatory values cannot be "--":\n%s' % str([_all_columns[ii] for ii in _obligatory_params])
        assert len(self.current_parameters_list) == len(self.current_values_list), \
            ' -  The number of columns for the input are not equal to number of values in the configuration file.'
        try:
            # next(iter()) is equivalent to item() which is deprecated
            mons = self.current_values_list[next(iter(self.current_parameters_list[self.current_parameters_list == 'monitors'].index), 'no match')]
        except ValueError:
            mons = '--'
        # next(iter()) is equivalent to item() which is deprecated
        group_idx = self.current_values_list[next(iter(self.current_parameters_list[self.current_parameters_list == 'idx'].index))]

        assert group_idx not in self.NG_indices, \
            " -  Error: multiple indices with same values exist in the configuration file."
        self.NG_indices.append(group_idx)
        current_idx = len(self.customized_neurons_list)
        relay_group = {'idx': int(group_idx),
                       'type': 'in',
                       'z_positions': [],
                       'w_positions': [],
                       'equation': ''}
        self.customized_neurons_list.append(relay_group)
        input_type_to_method_mapping[_input_type][2](self)

    def gather_result(self):
        """
        After the simulation and using the syntaxes that are previously prepared in the syntax_bank of save_data() object,
        this method saves the collected data to a file.

        """
        print(" -  Generating the syntaxes for saving CX output:")
        for syntax in self.workspace.syntax_bank:
            if 'get_states' in syntax:
                tmp_monitor = syntax.split(' ')[-1]
                print(tmp_monitor)
                print("     -> Gathering data for " + tmp_monitor.split('.')[0])
                exec(syntax)
        self.workspace.save_results_to_file()
        if self.do_save_connections:
            print(" -  Generating the syntaxes for saving connection data ...")
            for syntax in self.workspace.syntax_bank:
                exec(syntax)
            self.workspace.create_connections_key('positions_all')
            self.workspace.connections['positions_all']['w_coord'] = self.workspace.results['positions_all']['w_coord']
            self.workspace.connections['positions_all']['z_coord'] = self.workspace.results['positions_all']['z_coord']
            self.workspace.save_connections_to_file()

    @staticmethod
    def import_optimizer():
        return [rand(), scprs.csr_matrix([])]


if __name__ == '__main__':
    root = Path(Path(os.getcwd()).parents[1])
    os.chdir(root)
    anatomy_path = root.joinpath('tests', 'config_files', 'pytest_Anatomy_config.json').as_posix()
    physio_path = root.joinpath('tests', 'config_files', 'pytest_Physiology_config.json').as_posix()
    CM = CxSystem(anatomy_path, physio_path)
    CM.run()
