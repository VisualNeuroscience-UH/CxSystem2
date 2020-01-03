# -*- coding: utf-8 -*-
__author__ = 'Andalibi, V., Hokkanen H., Vanni, S.'

'''
The preliminary version of this software has been developed at Aalto University 2012-2015, 
and the full version at the University of Helsinki 2013-2017. The software is distributed 
under the terms of the GNU General Public License. 
Copyright 2017 Vafa Andalibi, Henri Hokkanen and Simo Vanni.
'''

import itertools
import math
import multiprocessing
import os
import shutil
import sys
import time
from pathlib import Path

import numpy as np
import pandas as pd

from cxsystem2.core import cxsystem as cx
from cxsystem2.core.exceptions import InvalidConfigurationError
from cxsystem2.core.tools import write_to_file, parameter_finder
from cxsystem2.hpc.cluster_run import ClusterRun

class ArrayRun:

    def __init__(self,
                 anatomy_dataframe,
                 physiology_dataframe,
                 job_suffix,
                 cluster_run_start_idx,
                 cluster_run_step,
                 anatomy_file_path,
                 physio_file_path,
                 array_run_is_in_cluster=0,
                 array_run_stdout_file = None):
        """
        Initialize the ArrayRun for running several instances of CxSystem in parallel.

        :param  anatomy_dataframe: The dataframe containing the anatomical and system configurations that has an instance for ArrayRun in it.
        :param physiology_dataframe: The dataframe containing the physiology configurations that has an instance for ArrayRun in it.
        :param job_suffix: The job_suffix for the metadata file containing the filename and changing parameters in each of the simulations.
        """
        self.suffix = job_suffix
        self.cluster_start_idx = cluster_run_start_idx
        self.cluster_step = cluster_run_step
        self.array_run_is_in_cluster = array_run_is_in_cluster
        if array_run_stdout_file == 'None':
            self.array_run_stdout_file = None
        else:
            self.array_run_stdout_file = array_run_stdout_file
        if self.cluster_start_idx == -1 and self.cluster_step == -1:
            # this means this instance of array run is actually trying to run a bunch of instances in the cluster
            from cxsystem2.hpc.cluster_run import ClusterRun
        if self.cluster_start_idx != -1 and self.cluster_step != -1:
            self.metadata_filename = 'metadata_part_' + str((self.cluster_start_idx / self.cluster_step) + 1) + job_suffix + '.gz'
        else:
            self.metadata_filename = 'metadata_' + job_suffix + '.gz'
        self.array_run_metadata = pd.DataFrame
        self.anatomy_df = anatomy_dataframe
        self.physiology_df = physiology_dataframe
        try:
            self.multidimension_array_run = int(eval(parameter_finder(self.anatomy_df, 'multidimension_array_run')))
        except TypeError:
            self.multidimension_array_run = 0
        try:
            self.number_of_process = int(parameter_finder(self.anatomy_df, 'number_of_process'))
        except TypeError:
            self.number_of_process = int(multiprocessing.cpu_count() * 3 / 4)
            print(" -  number_of_process is not defined in the configuration file, the default number of processes are"
                  " 3/4*number of CPU cores: %d processes" % self.number_of_process)
        try:
            self.benchmark = int(eval(parameter_finder(self.anatomy_df, 'benchmark')))
        except (TypeError, NameError):
            self.benchmark = 0
        try:
            self.trials_per_config = int(parameter_finder(self.anatomy_df, 'trials_per_config'))
        except TypeError:
            print(" - trials_per_config is not defined in the configuration "
                  "file, the default value is 1")
            self.trials_per_config = 1
        try:
            self.device = parameter_finder(self.anatomy_df, 'device')
        except TypeError:
            print(" -    device is not defined in the configuration file, "
                  "the default value is 'Python'")
            self.device = 'Python'
        try:
            self.run_in_cluster = int(eval(parameter_finder(self.anatomy_df, 'run_in_cluster')))
        except (TypeError, NameError):
            self.run_in_cluster = 0
        try:
            self.cluster_job_file_path = parameter_finder(self.anatomy_df, 'cluster_job_file_path')
        except (TypeError, NameError):
            pass
        try:
            self.cluster_number_of_nodes = int(parameter_finder(self.anatomy_df, 'cluster_number_of_nodes'))
        except (TypeError, NameError):
            self.cluster_number_of_nodes = 1

        if self.cluster_number_of_nodes > 30:
            raise Exception(' -  Number of nodes cannot be higher than 30 for your own safety.')

        anatomy_array_search_result = self.anatomy_df[self.anatomy_df.applymap(lambda x: True if ('|' in str(x) or '&' in str(x)) else False)]
        physio_array_search_result = self.physiology_df[self.physiology_df.applymap(lambda x: True if ('|' in str(x) or '&' in str(x)) else False)]
        arrays_idx_anatomy = np.where(anatomy_array_search_result.isnull().values != True)
        arrays_idx_anatomy = [(arrays_idx_anatomy[0][i], arrays_idx_anatomy[1][i]) for i in range(len(arrays_idx_anatomy[0]))]
        arrays_idx_physio = np.where(physio_array_search_result.isnull().values != True)
        arrays_idx_physio = [(arrays_idx_physio[0][i], arrays_idx_physio[1][i]) for i in range(len(arrays_idx_physio[0]))]
        self.df_anat_final_array = []
        self.df_phys_final_array = []
        self.final_messages = []

        self.sum_of_array_runs = len(arrays_idx_anatomy) + len(arrays_idx_physio)
        if self.sum_of_array_runs > 1 and not self.multidimension_array_run:
            anatomy_default = self.df_default_finder(self.anatomy_df)
            physio_default = self.df_default_finder(self.physiology_df)
        else:
            anatomy_default = anatomy_dataframe
            physio_default = physiology_dataframe
        # creating the array of dataframes for array run
        self.anat_titles = []
        self.physio_titles = []
        self.metadata_dict = {}
        if self.multidimension_array_run:
            # initializing the metadata :
            meta_columns = []
            for meta_col_idx in range(1, 1 + len(arrays_idx_anatomy) + len(arrays_idx_physio)):
                meta_columns.append('Dimension-%d Parameter' % meta_col_idx)
                meta_columns.append('Dimension-%d Value' % meta_col_idx)
            meta_columns.extend(['Full path'])
            self.final_metadata_df = pd.DataFrame(index=[0], columns=meta_columns)
            anat_variations = []
            physio_variations = []
            anat_messages = []
            physio_messages = []
            if arrays_idx_anatomy:
                anat_variations, anat_messages = self.df_builder_for_array_run(anatomy_dataframe, arrays_idx_anatomy, df_type='anatomy')
            if arrays_idx_physio:
                physio_variations, physio_messages = self.df_builder_for_array_run(physiology_dataframe, arrays_idx_physio, df_type='physiology')
            if arrays_idx_anatomy and arrays_idx_physio:
                for anat_idx, anat_df in enumerate(anat_variations):
                    for physio_idx, physio_df in enumerate(physio_variations):
                        self.df_anat_final_array.append(anat_df)
                        self.df_phys_final_array.append(physio_df)
                        self.final_messages.append(anat_messages[anat_idx] + physio_messages[physio_idx])
            elif arrays_idx_anatomy:
                for anat_idx, anat_df in enumerate(anat_variations):
                    self.df_anat_final_array.append(anat_df)
                    self.df_phys_final_array.append(physio_default)
                    self.final_messages.append(anat_messages[anat_idx])
            elif arrays_idx_physio:
                for physio_idx, physio_df in enumerate(physio_variations):
                    self.df_phys_final_array.append(physio_df)
                    self.df_anat_final_array.append(anatomy_default)
                    self.final_messages.append(physio_messages[physio_idx])

        else:
            # initializing the metadata :
            meta_columns = []
            meta_columns.extend(['Dimension-1 Parameter', 'Dimension-1 Value', 'Full path'])
            self.final_metadata_df = pd.DataFrame(index=[0], columns=meta_columns)
            if arrays_idx_anatomy:
                df_anat_array, anat_messages = self.df_builder_for_array_run(anatomy_dataframe, arrays_idx_anatomy, df_type='anatomy')
                self.df_anat_final_array.extend(df_anat_array)
                self.df_phys_final_array.extend([physio_default for _ in range(len(self.df_anat_final_array))])
                self.final_messages.extend(anat_messages)
            if arrays_idx_physio:
                df_phys_array, physio_messages = self.df_builder_for_array_run(physiology_dataframe, arrays_idx_physio, df_type='physiology')
                self.df_phys_final_array.extend(df_phys_array)
                self.df_anat_final_array.extend([anatomy_default for _ in range(len(self.df_phys_final_array))])
                self.final_messages.extend(physio_messages)

        self.all_titles = self.anat_titles + self.physio_titles

        if not self.df_anat_final_array and not self.df_phys_final_array:
            print(" -  no ArrayRun variable found, the default "
                  "configurations are going to be simulated %d "
                  "times" % self.trials_per_config)
            # trial_per_conf_idx = np.where(anatomy_default.values == 'trials_per_config')
            # anatomy_default[int(trial_per_conf_idx[1])][int(trial_per_conf_idx[0])] = ''
            self.df_anat_final_array = [anatomy_default] * self.trials_per_config
            self.df_phys_final_array = [physio_default] * self.trials_per_config
            self.final_messages = ['_default_config']
            self.metadata_dict['default_config'] = ['default_config']
            self.all_titles = ['default_config']

        if self.multidimension_array_run:
            self.tmp_df = pd.DataFrame(list(itertools.product(*list(self.metadata_dict.values()))), columns=list(self.metadata_dict.keys()))
            self.tmp_df = self.tmp_df[self.all_titles]
            self.tmp_df = self.tmp_df.sort_values(by=self.all_titles).reset_index(drop=True)
            self.final_metadata_df = self.final_metadata_df.reindex(self.tmp_df.index)
            for col_idx, col_title in enumerate(self.all_titles):
                self.final_metadata_df['Dimension-%d Parameter' % (col_idx + 1)] = col_title
                self.final_metadata_df['Dimension-%d Value' % (col_idx + 1)] = self.tmp_df[col_title]
        else:
            index_len = len([item for sublist in list(self.metadata_dict.values()) for item in sublist])
            self.final_metadata_df = self.final_metadata_df.reindex(list(range(index_len)))
            counter = 0
            for par_idx, parameter in enumerate(self.all_titles):
                for val in self.metadata_dict[parameter]:
                    self.final_metadata_df['Dimension-1 Parameter'][counter] = parameter
                    self.final_metadata_df['Dimension-1 Value'][counter] = val
                    counter += 1

        print(" -  array of Dataframes for anatomical and physiological configuration are ready")
        if self.run_in_cluster == 1 and self.cluster_start_idx == -1 and self.cluster_step == -1:  # to run the Cxsystems on the cluster
            self.total_configs = len(self.df_anat_final_array) * self.trials_per_config
            self.config_per_node = math.ceil(self.total_configs / self.cluster_number_of_nodes)
            self.clipping_indices = np.arange(0, self.total_configs, self.config_per_node)
            ClusterRun(self, Path(anatomy_file_path), Path(physio_file_path), self.suffix)

            print (" -  removing .tmp folder")
            tmp_folder_path = Path(parameter_finder(self.anatomy_df, 'workspace_path')).expanduser().joinpath('.tmp' + self.suffix).as_posix()
            print("cleaning tmp folders " + tmp_folder_path)
            shutil.rmtree(tmp_folder_path)
            return

        if cluster_run_start_idx != -1 and cluster_run_step != -1:  # this runs in cluster
            self.spawner(self.cluster_start_idx, self.cluster_step)
            return
        self.spawner(0, len(self.final_messages) * self.trials_per_config)  # this runs when not in cluster

    def arr_run(self, idx, working, paths, stdout_file):
        """
        The function that each spawned process runs and parallel instances of CxSystems are created here.

        :param idx: index of the requested parallel CxSystem.
        :param working: the index of the process that is being currently performed. This is to keep track of running processes
                to prevent spawning more than required processes.
        :param paths: The path for saving the output of the current instance of CxSystem.
        """
        if stdout_file:
            sys.stdout = open(stdout_file, "a+")
        orig_idx = idx
        working.value += 1
        np.random.seed(idx)
        tr = idx % self.trials_per_config
        idx = int(idx / self.trials_per_config)
        device = parameter_finder(self.df_anat_final_array[idx], 'device')
        if self.number_of_process == 1 and self.benchmark == 1 and device == 'Python':
            # this should be used to clear the cache of weave for benchmarking. otherwise weave will mess it up
            if sys.platform == 'win32':
                shutil.rmtree(os.path.join(os.environ['USERPROFILE'], 'AppData', 'Local', 'Temp', os.environ['USERNAME'], 'python27_compiled'))
            else:
                shutil.rmtree(os.path.join(os.environ['HOME'], '.cache/scipy'))
            print(" -  scipy cache deleted to prevent benchmarking issues.")
        print("################### Trial %d/%d started running for "
              "simulation number %d: %s ##########################" % (tr + 1,
                                                                       self.trials_per_config, idx, self.final_messages[idx][1:]))
        cm = cx.CxSystem(self.df_anat_final_array[idx], self.df_phys_final_array[idx], output_file_suffix=self.final_messages[idx],
                         instantiated_from_array_run=1, array_run_in_cluster=self.array_run_is_in_cluster)
        cm.run()
        paths[orig_idx] = cm.workspace.results['Full path']
        working.value -= 1

    def spawner(self, start_idx, steps_from_start):
        """
        Spawns processes each dedicated to an instance of CxSystem.
        """
        print(" -  Following configurations are going to be simulated with "
              "%d processes using %s device (printed only in letters and numbers): "
              "\n %s" % (self.number_of_process, self.device,
                         str(self.final_messages).replace('_', '')))
        manager = multiprocessing.Manager()
        jobs = []
        working = manager.Value('i', 0)
        paths = manager.dict()
        # number_of_runs = len(self.final_messages) * self.trials_per_config
        self.final_metadata_df = self.final_metadata_df.loc[np.repeat(self.final_metadata_df.index.values, self.trials_per_config)].reset_index(
            drop=True)
        assert len(self.final_messages) < 1000, ' -  The array run is trying to run more than 1000 simulations, this is not allowed unless you' \
                                                ' REALLY want it and if you REALLY want it you should konw what to do.'
        # while len(jobs) < number_of_runs:
        while len(jobs) < steps_from_start:
            time.sleep(1.5)
            if working.value < self.number_of_process:
                idx = start_idx + len(jobs)
                p = multiprocessing.Process(target=self.arr_run, args=(idx, working, paths, self.array_run_stdout_file))
                jobs.append(p)
                p.start()
        for j in jobs:
            j.join()

        for item in list(paths.keys()):
            self.final_metadata_df['Full path'][item] = paths[item]
        write_to_file(os.path.join(os.path.dirname(paths[list(paths.keys())[0]]), self.metadata_filename), self.final_metadata_df)
        print(" -  Array run metadata saved at: %s" % os.path.join(
            os.path.dirname(paths[list(paths.keys())[0]]), self.metadata_filename))

        tmp_folder_path = Path(parameter_finder(self.anatomy_df, 'workspace_path')).expanduser().joinpath('.tmp' + self.suffix).as_posix()
        print("cleaning tmp folders " + tmp_folder_path)
        shutil.rmtree(tmp_folder_path)

    def df_builder_for_array_run(self, original_df, index_of_array_variable, df_type, message='', recursion_counter=1):
        """
        Generates new configuration dataframes for each of the scenarios from the original dataframe.

        :param original_df: original dataframe.
        :param index_of_array_variable: index of the cell with array variable.
        :param df_type: type of the dataframe (anatomy_and_system/physiology)
        :param message: generated message from previous iteration (when recursion is needed)
        :param recursion_counter: counting the iteration (when recursion is needed)
        """
        array_of_dfs = []
        run_messages = []
        array_variable = original_df.loc[index_of_array_variable[0][0]][index_of_array_variable[0][1]]
        opening_braket_idx = array_variable.index('{')
        if (not self.multidimension_array_run and self.sum_of_array_runs > 1) or (self.sum_of_array_runs == 1 and ':' in array_variable):
            colon_idx = array_variable.index(':')
            array_variable = array_variable.replace(array_variable[opening_braket_idx + 1:colon_idx + 1], '')  # removing default value
        elif ':' in array_variable:
            print(" -  The default value set for %s is omitted since the "
                  "array run is multidimentional (multidimension_array_run "
                  "flag is set to 1)" % array_variable)
            colon_idx = array_variable.index(':')
            array_variable = array_variable.replace(array_variable[opening_braket_idx + 1:colon_idx + 1], '')  # removing default value
        closing_braket_idx = array_variable.index('}')
        template_of_variable = array_variable[:opening_braket_idx] + '^^^' + array_variable[closing_braket_idx + 1:]
        assert not ('|' in array_variable and '&' in array_variable), \
            " -  The following array run should be defined either using | or & not both of them:" % array_variable
        variables_to_iterate = []
        if '|' in array_variable:
            changing_part = array_variable[opening_braket_idx + 1:closing_braket_idx].replace('|', ',')
            tmp_str = 'np.arange(' + changing_part + ')'
            variables_to_iterate = eval(tmp_str)
        elif '&' in array_variable:
            variables_to_iterate = eval('["' + array_variable[opening_braket_idx + 1:closing_braket_idx].replace('&', '","') + '"]')
        variables_to_iterate = [template_of_variable.replace('^^^', str(vv)) for vv in variables_to_iterate]
        for var_idx, var in enumerate(variables_to_iterate):
            if type(var) == str:
                var = var.strip()
            temp_df = original_df.copy()
            temp_df.iloc[index_of_array_variable[0][0], index_of_array_variable[0][1]] = var
            if self.multidimension_array_run and len(index_of_array_variable) > 1:
                tmp_title, tmp_value, tmp_message = self.message_finder(temp_df, index_of_array_variable, df_type)
                temp_df, messages = self.df_builder_for_array_run(temp_df, index_of_array_variable[1:], df_type, tmp_message.replace(self.suffix,''),
                                                                  recursion_counter=recursion_counter + 1)
            else:
                temp_df = [self.df_default_finder(temp_df)]
                tmp_title, tmp_value, tmp_message = self.message_finder(temp_df[0], index_of_array_variable, df_type)
                messages = [self.suffix + message + tmp_message.replace(self.suffix,'')]
            array_of_dfs.extend(temp_df)
            run_messages.extend(messages)

        if not self.multidimension_array_run and len(index_of_array_variable) > 1:
            temp_df, messages = self.df_builder_for_array_run(original_df, index_of_array_variable[1:], df_type, message='')
            array_of_dfs.extend(temp_df)
            run_messages.extend(messages)
        return array_of_dfs, run_messages

    @staticmethod
    def df_default_finder(df_):
        df = df_.copy()
        df_search_result = df[df.applymap(lambda x: True if ('|' in str(x) or '&' in str(x)) else False)]
        df_search_result = np.where(df_search_result.notnull())
        arrays_idx_ = [(df_search_result[0][i], df_search_result[1][i]) for i in range(len(df_search_result[0]))]
        for to_default_idx in arrays_idx_:
            value_to_default = df.loc[to_default_idx[0]][to_default_idx[1]]
            assert ':' in value_to_default, " -  The default value should be defined for %s , or make sure multidimension_array_run in" \
                                            " configuration file is set to 1." % value_to_default
            default = value_to_default[value_to_default.index('{') + 1:value_to_default.index(':')]
            df.loc[to_default_idx[0]][to_default_idx[1]] = df.loc[to_default_idx[0]][to_default_idx[1]].replace(
                value_to_default[value_to_default.index('{'):value_to_default.index('}') + 1], default)
        return df

    def message_finder(self, df, idx, df_type):
        """
        Generates messages for each of the runs in ArrayRun.

        :param df: input dataframe.
        :param idx: index of the cell based on which the message is going to be generated.
        :param df_type: type of dataframe.
        """
        idx = idx[0]
        whitelist = set('abcdefghijklmnopqrstuvwxyABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890_-')

        if np.any(df.iloc[:, 0].str.contains('row_type')):
            definition_rows_indices = np.array(df[0][df[0] == 'row_type'].index.tolist())
            target_row = max(np.where(definition_rows_indices < idx[0])[0])
            title = str(df.loc[target_row][idx[1]])
            value = str(df.loc[idx[0]][idx[1]])
            message = self.suffix + '_' + title + ''.join(filter(whitelist.__contains__, value))
        elif 'Variable' in df.columns:
            try:
                if not math.isnan(df['Key'][idx[0]]):
                    title = str(df['Key'][idx[0]])
                    value = str(df[idx[0]][idx[1]])
                else:
                    title = str(df['Variable'][idx[0]])
                    value = str(df.loc[idx[0]][idx[1]])
            except TypeError:
                title = str(df['Key'][idx[0]])
                value = str(df.loc[idx[0]][idx[1]])
            message = self.suffix + '_' + title + ''.join(filter(whitelist.__contains__, value))
        else:
            raise InvalidConfigurationError("Configuration file format is not valid")
        # for metadata
        if df_type == 'anatomy':
            if title not in self.anat_titles:
                self.anat_titles.append(title)
        elif df_type == 'physiology':
            if title not in self.physio_titles:
                self.physio_titles.append(title)
        if title in list(self.metadata_dict.keys()):
            if value not in self.metadata_dict[title]:
                self.metadata_dict[title].append(value)
        else:
            self.metadata_dict[title] = [value]
        return title, value, message


if __name__ == '__main__':
    if len(sys.argv) != 10:
        print("Array run needs 9 arguments and is not built to be called separately")
        sys.exit(1)
    anatomy_df = pd.read_csv(sys.argv[1], header=None)
    physiology_df = pd.read_csv(sys.argv[2])
    suffix = sys.argv[3]
    cluster_start_idx = int(sys.argv[4])
    cluster_step = int(sys.argv[5])
    anat_file_address = sys.argv[6]
    physio_file_address = sys.argv[7]
    array_run_in_cluster = int(sys.argv[8])
    array_run_stdout_file = sys.argv[9]
    ArrayRun(anatomy_df, physiology_df, suffix, cluster_start_idx, cluster_step, anat_file_address, physio_file_address, array_run_in_cluster, array_run_stdout_file)
