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
from collections import defaultdict
import decimal

import numpy as np
import pandas as pd

from cxsystem2.core import cxsystem as cx
from cxsystem2.core.exceptions import InvalidConfigurationError
from cxsystem2.core.tools import write_to_file, parameter_finder, load_from_file
from cxsystem2.hpc.cluster_run import ClusterRun

class ArrayRun:

    def __init__(self,
                 anatomy_dataframe,
                 physiology_dataframe,
                 job_suffix,
                 cluster_start_idx,
                 cluster_step,
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
        self.suffix = job_suffix # At cluster this is global suffix (one for whole requested array)
        self.cluster_start_idx = int(cluster_start_idx)
        self.cluster_step = int(cluster_step)
        self.array_run_is_in_cluster = array_run_is_in_cluster
        self.array_run_stdout_file = None if array_run_stdout_file == 'None' else array_run_stdout_file

        self.metadata_filename = self._get_metadata_filename(self.cluster_start_idx, self.cluster_step, job_suffix)

        # these two are the original config files containing the array_run info:
        self.anatomy_df = pd.read_csv(anatomy_dataframe, header=None) if type(anatomy_dataframe) == str else anatomy_dataframe
        self.physiology_df = pd.read_csv(physiology_dataframe) if type(physiology_dataframe)==str else physiology_dataframe

        # finding array-run related parameters:
        self.multidimension_array_run = self._get_multidim_array_run_flag()
        self.number_of_process = self._get_num_of_process()
        self.benchmark = self._get_benchmark_flag()
        self.trials_per_config = self._get_trials_per_config()
        self.device = self._get_device()
        self.run_in_cluster = self._get_run_in_cluster_flag()
        self.cluster_job_file_path = self._get_cluster_job_file_path()
        self.cluster_number_of_nodes = self._get_cluster_number_of_nodes()

        # get indices of pandas cells containing the arrayruns
        self.anatomy_arrun_cell_indices = self._get_arrun_cell_indices_from_df(self.anatomy_df)
        self.physio_arrun_cell_indices = self._get_arrun_cell_indices_from_df(self.physiology_df)

        # lists containing final dataframes and experiment names
        self.list_of_anatomy_dfs = []
        self.list_of_physio_dfs = []
        self.final_namings = []

        self.param_search_num_of_params = len(self.anatomy_arrun_cell_indices) + len(self.physio_arrun_cell_indices)
        self.default_anatomy_df = self.default_df_extractor(self.anatomy_df)
        self.default_physio_df = self.default_df_extractor(self.physiology_df)

        # create a list of names of parameters with corresponding value in each experiment
        self.anat_titles = []
        self.physio_titles = []
        self.metadata_dict = {}

        # self.anat_titles and self.physio_titles are both set inside message_finder() which is called by the preparer functions
        if self.multidimension_array_run:
            self._prepare_multi_dim_arrun_metadata()
        else:
            self._prepare_one_dim_arrun_metadata()

        print(" -  array of Dataframes for anatomical and physiological configuration are ready")
        if self._should_submit_to_cluster():
            self.total_configs = len(self.list_of_anatomy_dfs) * self.trials_per_config
            self.config_per_node = math.ceil(self.total_configs / self.cluster_number_of_nodes)
            self.clipping_indices = np.arange(0, self.total_configs, self.config_per_node)
            ClusterRun(self, Path(anatomy_file_path), Path(physio_file_path), self.suffix)
            
            tmp_folder_path = Path(parameter_finder(self.anatomy_df, 'workspace_path')).expanduser().joinpath('.tmp' + self.suffix).as_posix()

            # Next we transfer tmp anat and phys csv files to downloads folder for future use
            self._save_tmp_anat_phys_to_downloads(tmp_folder_path)

            print (" -  removing .tmp folder")
            print("cleaning tmp folders " + tmp_folder_path)
            shutil.rmtree(tmp_folder_path)

        elif self._is_running_in_cluster():
            self.spawn_processes(self.cluster_start_idx, self.cluster_step)

        elif self._is_running_locally():
            self.spawn_processes(0, len(self.final_namings) * self.trials_per_config)  # this runs when not in cluster

    def _save_tmp_anat_phys_to_downloads(self, tmp_folder_path):
        # After ClusterRun call metadata master file has been created earlier, we read it here to get the downloads folder address
        local_workspace = Path(parameter_finder(self.anatomy_df, 'workspace_path')).expanduser()
        local_cluster_folder = local_workspace.joinpath('cluster_run' + self.suffix)
        metadata_pkl_fullfile = Path(local_cluster_folder.joinpath('cluster_metadata{}.pkl'.format(self.suffix)))
        metadata_dict = load_from_file(metadata_pkl_fullfile)
        downloads_folder = metadata_dict['local_cluster_run_download_folder']
        #Create downloads folder
        Path(downloads_folder).mkdir(parents=True, exist_ok=True)
            # Move anat and phys files to download folder
        tmp_folder_contents_list = os.listdir(tmp_folder_path)
        fullfile_source_list = []
        fullfile_target_list = []
        for this_file in tmp_folder_contents_list:
            fullfile_source_list.append(os.path.join(tmp_folder_path, this_file))
            fullfile_target_list.append(os.path.join(downloads_folder, this_file))
        [Path(s).replace(t) for s, t in zip(fullfile_source_list, fullfile_target_list) if 'anat' in s or 'phys' in s]

    def _should_submit_to_cluster(self):
        return self.run_in_cluster == 1 and self.cluster_start_idx == -1 and self.cluster_step == -1

    def _is_running_in_cluster(self):
        return self.cluster_start_idx != -1 and self.cluster_step != -1

    def _is_running_locally(self):
        return self.run_in_cluster != 1 and self.cluster_start_idx == -1 and self.cluster_step == -1

    def _prepare_multi_dim_arrun_metadata(self):
        meta_columns = []
        for meta_col_idx in range(1, 1 + len(self.anatomy_arrun_cell_indices) + len(self.physio_arrun_cell_indices)):
            meta_columns.append('Dimension-%d Parameter' % meta_col_idx)
            meta_columns.append('Dimension-%d Value' % meta_col_idx)
        meta_columns.extend(['Full path'])
        self.final_metadata_df = pd.DataFrame(index=[0], columns=meta_columns)
        anat_variations = []
        physio_variations = []
        anatomy_namings = []
        physio_namings = []
        if self.anatomy_arrun_cell_indices:
            anat_variations, anatomy_namings = self.generate_dataframes_for_param_search(self.anatomy_df,
                                                                                         self.anatomy_arrun_cell_indices,
                                                                                         df_type='anatomy')
        if self.physio_arrun_cell_indices:
            physio_variations, physio_namings = self.generate_dataframes_for_param_search(self.physiology_df,
                                                                                          self.physio_arrun_cell_indices,
                                                                                          df_type='physiology')
        if self.anatomy_arrun_cell_indices and self.physio_arrun_cell_indices:
            for anat_idx, anat_df in enumerate(anat_variations):
                for physio_idx, physio_df in enumerate(physio_variations):
                    self.list_of_anatomy_dfs.append(anat_df)
                    self.list_of_physio_dfs.append(physio_df)
                    physio_without_timeline = '_' + '_'.join(physio_namings[physio_idx].split('_')[3:])
                    self.final_namings.append(anatomy_namings[anat_idx] + physio_without_timeline)
        elif self.anatomy_arrun_cell_indices:
            for anat_idx, anat_df in enumerate(anat_variations):
                self.list_of_anatomy_dfs.append(anat_df)
                self.list_of_physio_dfs.append(self.default_physio_df)
                self.final_namings.append(anatomy_namings[anat_idx])
        elif self.physio_arrun_cell_indices:
            for physio_idx, physio_df in enumerate(physio_variations):
                self.list_of_physio_dfs.append(physio_df)
                self.list_of_anatomy_dfs.append(self.default_anatomy_df)
                self.final_namings.append(physio_namings[physio_idx])

        self._check_single_experiment_multi_trials()
        self._set_titles_and_metadata_dict()
        self.all_titles = self.anat_titles + self.physio_titles
        product_of_parameters = list(itertools.product(*list(self.metadata_dict.values())))
        self.tmp_df = pd.DataFrame(product_of_parameters, columns=list(self.metadata_dict.keys()))
        self.final_metadata_df = self.final_metadata_df.reindex(self.tmp_df.index)
        for col_idx, col_title in enumerate(self.all_titles):
            self.final_metadata_df['Dimension-%d Parameter' % (col_idx + 1)] = col_title
            self.final_metadata_df['Dimension-%d Value' % (col_idx + 1)] = self.tmp_df[col_title]

    def _prepare_one_dim_arrun_metadata(self):
        # since we are running the experiments in one dimension,
        # initializing the metadata :
        meta_columns = []
        meta_columns.extend(['Dimension-1 Parameter', 'Dimension-1 Value', 'Full path'])
        self.final_metadata_df = pd.DataFrame(index=[0], columns=meta_columns)
        if self.anatomy_arrun_cell_indices:
            df_anat_array, anatomy_namings = self.generate_dataframes_for_param_search(self.anatomy_df, self.anatomy_arrun_cell_indices, df_type='anatomy')
            self.list_of_anatomy_dfs.extend(df_anat_array)
            self.list_of_physio_dfs.extend([self.default_physio_df for _ in range(len(self.list_of_anatomy_dfs))])
            self.final_namings.extend(anatomy_namings)
        if self.physio_arrun_cell_indices:
            df_phys_array, physio_namings = self.generate_dataframes_for_param_search(self.physiology_df, self.physio_arrun_cell_indices, df_type='physiology')
            self.list_of_physio_dfs.extend(df_phys_array)
            self.list_of_anatomy_dfs.extend([self.default_anatomy_df for _ in range(len(self.list_of_physio_dfs))])
            self.final_namings.extend(physio_namings)

        self._check_single_experiment_multi_trials()
        self._set_titles_and_metadata_dict()
        self.all_titles = self.anat_titles + self.physio_titles

        index_len = len([item for sublist in list(self.metadata_dict.values()) for item in sublist])
        self.final_metadata_df = self.final_metadata_df.reindex(list(range(index_len)))
        counter = 0
        for par_idx, parameter in enumerate(self.all_titles):
            for val in self.metadata_dict[parameter]:
                self.final_metadata_df['Dimension-1 Parameter'][counter] = parameter
                self.final_metadata_df['Dimension-1 Value'][counter] = val
                counter += 1

    def _check_single_experiment_multi_trials(self):
        if not self.list_of_anatomy_dfs and not self.list_of_physio_dfs:
            print(" -  No parameter for array run found, the default configurations are going to be simulated %d times" % self.trials_per_config)
            self.list_of_anatomy_dfs = [self.default_anatomy_df] * self.trials_per_config
            self.list_of_physio_dfs = [self.default_physio_df] * self.trials_per_config
            self.final_namings = ['_default_config']
            self.metadata_dict['default_config'] = ['default_config']
            self.all_titles = ['default_config']

    def run_parameter_search(self, idx, working, paths, stdout_file):
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
        device = parameter_finder(self.list_of_anatomy_dfs[idx], 'device')
        if self.number_of_process == 1 and self.benchmark == 1 and device == 'Python':
            # this should be used to clear the cache of weave for benchmarking. otherwise weave will mess it up
            if sys.platform == 'win32':
                shutil.rmtree(os.path.join(os.environ['USERPROFILE'], 'AppData', 'Local', 'Temp', os.environ['USERNAME'], 'python27_compiled'))
            else:
                shutil.rmtree(os.path.join(os.environ['HOME'], '.cache/scipy'))
            print(" -  scipy cache deleted to prevent benchmarking issues.")
        print("################### Trial %d/%d started running for "
              "simulation number %d: %s ##########################" % (tr + 1,
                                                                       self.trials_per_config, idx, self.final_namings[idx][1:]))
        tr_suffix = ''
        if self.trials_per_config > 1:
             tr_suffix = '_' + str(tr).zfill(3)
        # The self.list_of_anatomy/physio_dfs[idx] contains the dataframes with final (single) parameter value for simulation.
        cm = cx.CxSystem(self.list_of_anatomy_dfs[idx], self.list_of_physio_dfs[idx], output_file_suffix=self.final_namings[idx]
                         + tr_suffix, instantiated_from_array_run=1, array_run_in_cluster=self.array_run_is_in_cluster)
        cm.run()
        paths[orig_idx] = cm.workspace.get_results_export_path()
        working.value -= 1

    def spawn_processes(self, start_idx, steps_from_start):
        """
        Spawns processes each dedicated to an instance of CxSystem.
        """
        print(" -  Following configurations are going to be simulated with "
              "%d processes using %s device (printed only in letters and numbers): "
              "\n %s" % (self.number_of_process, self.device,
                         str(self.final_namings).replace('_', '')))
        manager = multiprocessing.Manager()
        jobs = []
        working = manager.Value('i', 0)
        paths = manager.dict()
        # number_of_runs = len(self.final_messages) * self.trials_per_config
        self.final_metadata_df = self.final_metadata_df.loc[np.repeat(self.final_metadata_df.index.values, self.trials_per_config)].reset_index(
            drop=True)
        assert len(self.final_namings) < 1000, ' -  The array run is trying to run more than 1000 simulations, this is not allowed unless you' \
                                                ' REALLY want it and if you REALLY want it you should know what to do.'
        # while len(jobs) < number_of_runs:
        while len(jobs) < steps_from_start:
            time.sleep(1.5)
            if working.value < self.number_of_process:
                idx = start_idx + len(jobs)
                p = multiprocessing.Process(target=self.run_parameter_search, args=(idx, working, paths, self.array_run_stdout_file))
                jobs.append(p)
                p.start()
        for j in jobs:
            j.join()

        for item in list(paths.keys()):
            self.final_metadata_df['Full path'][item] = paths[item]
        write_to_file(os.path.join(os.path.dirname(paths[list(paths.keys())[0]]), self.metadata_filename), self.final_metadata_df)
        print(" -  Array run metadata saved at: %s" % os.path.join(
            os.path.dirname(paths[list(paths.keys())[0]]), self.metadata_filename))

        if self._is_running_locally() is True:
            tmp_folder_path = Path(parameter_finder(self.anatomy_df, 'workspace_path')).expanduser().joinpath('.tmp' + self.suffix).as_posix()
            print("cleaning tmp folders " + tmp_folder_path)
            shutil.rmtree(tmp_folder_path)
#        Moved to end of cxsystem init 
#        elif self._is_running_in_cluster() is True:
#            tmp_folder_path = Path(parameter_finder(self.anatomy_df, 'cluster_workspace')).expanduser().joinpath('.tmp' + self.suffix).as_posix()
#            print("cleaning tmp folders " + tmp_folder_path)
#            shutil.rmtree(tmp_folder_path)

    def generate_dataframes_for_param_search(self, original_df, index_of_array_variable, df_type, naming_prefix='', recursion_counter=1):
        """
        Generates new configuration dataframes for each of the scenarios from the original dataframe.

        :param original_df: original dataframe.
        :param index_of_array_variable: index of the cell with array variable.
        :param df_type: type of the dataframe (anatomy_and_system/physiology)
        :param naming_prefix: generated name from previous iteration (when recursion is needed)
        :param recursion_counter: counting the iteration (when recursion is needed)
        """
        array_of_dfs = []
        run_namings = []
        array_variable = original_df.loc[index_of_array_variable[0][0]][index_of_array_variable[0][1]]
        opening_braket_idx = array_variable.index('{')
        if (not self.multidimension_array_run and self.param_search_num_of_params > 1) or (self.param_search_num_of_params == 1 and ':' in array_variable):
            colon_idx = array_variable.index(':')
            array_variable = array_variable.replace(array_variable[opening_braket_idx + 1:colon_idx + 1], '')  # removing default value
        elif ':' in array_variable:
            print(" -  The default value set for %s is omitted since the "
                  "array run is multidimensional (multidimension_array_run "
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
            decimal_type_list = [decimal.Decimal(vv) for vv in changing_part.split(',')]
            variables_to_iterate = np.arange(decimal_type_list[0],decimal_type_list[1],decimal_type_list[2]).tolist()
        elif '&' in array_variable:
            variables_to_iterate = eval('["' + array_variable[opening_braket_idx + 1:closing_braket_idx].replace('&', '","') + '"]')
        variables_to_iterate = [template_of_variable.replace('^^^', str(vv)) for vv in variables_to_iterate]
        for var_idx, var in enumerate(variables_to_iterate): # this iteration is unclear, but seems to work
            if type(var) == str:
                var = var.strip()
            temp_df = original_df.copy()
            temp_df.iloc[index_of_array_variable[0][0], index_of_array_variable[0][1]] = var
            if self.multidimension_array_run and len(index_of_array_variable) > 1:
                tmp_title, tmp_value, tmp_naming = self.filename_generator(temp_df, index_of_array_variable, df_type)
                temp_df, namings = self.generate_dataframes_for_param_search(temp_df, index_of_array_variable[1:], df_type, tmp_naming.replace(self.suffix, ''),
                                                                              recursion_counter=recursion_counter + 1)
            else:
                temp_df = [self.default_df_extractor(temp_df)]
                tmp_title, tmp_value, tmp_naming = self.filename_generator(temp_df[0], index_of_array_variable, df_type)
                namings = [self.suffix + naming_prefix + tmp_naming.replace(self.suffix, '')]
            array_of_dfs.extend(temp_df)
            run_namings.extend(namings)

        if not self.multidimension_array_run and len(index_of_array_variable) > 1:
            temp_df, namings = self.generate_dataframes_for_param_search(original_df, index_of_array_variable[1:], df_type, naming_prefix='')
            array_of_dfs.extend(temp_df)
            run_namings.extend(namings)

        return array_of_dfs, run_namings

    def default_df_extractor(self, df_):
        if self.param_search_num_of_params == 1 or self.multidimension_array_run:
            # in case there is just one parameter for array run OR we are having a multidimension array_run then default finding is not needed
            return df_ 
        df = df_.copy()
        df_search_result = df[df.applymap(lambda x: True if ('|' in str(x) or '&' in str(x)) else False)]
        df_search_result = np.where(df_search_result.notnull())
        arrays_idx_ = [(df_search_result[0][i], df_search_result[1][i]) for i in range(len(df_search_result[0]))]
        for to_default_idx in arrays_idx_:
            value_to_default = df.loc[to_default_idx[0]][to_default_idx[1]]
            assert ':' in value_to_default, \
                " -  The default value should be defined for %s if the system is running for one-dimensional parameter search" % value_to_default
            default = value_to_default[value_to_default.index('{') + 1:value_to_default.index(':')]
            df.loc[to_default_idx[0]][to_default_idx[1]] = df.loc[to_default_idx[0]][to_default_idx[1]].replace(
                value_to_default[value_to_default.index('{'):value_to_default.index('}') + 1], default)
        return df

    def _set_titles_and_metadata_dict(self):
       
        def _get_title_and_unique_values(tmp_value_list):

            unique_values_raw = list(set(tmp_value_list)) # Unsorted list of strings
            # Check for unit stripping
            if '*' in unique_values_raw[0]:
                unique_values_numerical = [nn[:nn.find('*')] for nn in unique_values_raw]
            else:
                unique_values_numerical = unique_values_raw

            try:
                unique_values_sorted = np.sort(np.array([float(nn) for nn in unique_values_numerical])) # Sorted array of floats
            except:
                unique_values_sorted = sorted(unique_values_numerical) # Sorted array -- allows strings to be arrayed, such as input file names

            unique_values = [str(nn) for nn in unique_values_sorted] # Sorted list of strings
            title, value, naming = self.filename_generator(df, [idx], '') # this is for title only, df can be any df
            return title, unique_values

        tmp_value_list=[]
        for idx in self.anatomy_arrun_cell_indices:
            for df in self.list_of_anatomy_dfs:
                tmp_value_list.append(df.iloc[idx])
            
            title, unique_values = _get_title_and_unique_values(tmp_value_list)

            if title in list(self.metadata_dict.keys()):
                title = title + '_1'
            self.anat_titles.append(title)
            self.metadata_dict[title] = unique_values
            tmp_value_list=[]

        for idx in self.physio_arrun_cell_indices:
            for df in self.list_of_physio_dfs:
                tmp_value_list.append(df.iloc[idx])
            
            title, unique_values = _get_title_and_unique_values(tmp_value_list)

            if title in list(self.metadata_dict.keys()):
                title = title + '_1'
            self.physio_titles.append(title)
            self.metadata_dict[title] = unique_values
            tmp_value_list=[]
        
    def filename_generator(self, df, idx, df_type):
        """
        Generates filenames for each of the runs in ArrayRun.

        :param df: input dataframe.
        :param idx: index of the cell based on which the name is going to be generated.
        :param df_type: type of dataframe.
        """
        idx = idx[0]
        whitelist = set('abcdefghijklmnopqrstuvwxyABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890_-')

        if np.any(df.iloc[:, 0].str.contains('row_type')): # Anatomical conf
            definition_rows_indices = np.array(df[0][df[0] == 'row_type'].index.tolist())
            target_row_ix  = max(np.where(definition_rows_indices < idx[0])[0]) # get the index of the row containing the column info
            target_row = definition_rows_indices[target_row_ix]
            title = str(df.loc[target_row][idx[1]])
            value = str(df.loc[idx[0]][idx[1]])
            # naming = self.suffix + '_' + title + ''.join(filter(whitelist.__contains__, value))
        elif 'Variable' in df.columns: # Physiology conf
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
            # naming = self.suffix + '_' + title + ''.join(filter(whitelist.__contains__, value))
        else:
            raise InvalidConfigurationError("Configuration file format is not valid")

        naming = self.suffix + '_' + title + ''.join(filter(whitelist.__contains__, value))

        return title, value, naming

    def _get_multidim_array_run_flag(self):
        multi_dim_flag = 0
        try:
            multi_dim_flag = int(eval(parameter_finder(self.anatomy_df, 'multidimension_array_run')))
        except TypeError:
            pass
        return multi_dim_flag

    def _get_num_of_process(self):
        number_of_process = int(multiprocessing.cpu_count() * 3 / 4)
        try:
            number_of_process = int(parameter_finder(self.anatomy_df, 'number_of_process'))
        except TypeError:
            print(" -  number_of_process is not defined in the configuration file, the default number of processes are"
                  " 3/4*number of CPU cores: %d processes" % self.number_of_process)
        return number_of_process

    def _get_benchmark_flag(self):
        benchmark = 0
        try:
            benchmark = int(eval(parameter_finder(self.anatomy_df, 'benchmark')))
        except (TypeError, NameError):
            pass
        return benchmark

    def _get_trials_per_config(self):
        trials_per_config = 1
        try:
            trials_per_config = int(parameter_finder(self.anatomy_df, 'trials_per_config'))
        except TypeError:
            print(" - trials_per_config is not defined in the configuration "
                  "file, the default value is 1")
        return trials_per_config

    def _get_device(self):
        device = 'Python'
        try:
            device = parameter_finder(self.anatomy_df, 'device')
        except TypeError:
            print(" -    device is not defined in the configuration file, the default device is 'Python'")
        return device

    def _get_run_in_cluster_flag(self):
        run_in_cluster = 0
        try:
            run_in_cluster = int(eval(parameter_finder(self.anatomy_df, 'run_in_cluster')))
        except (TypeError, NameError):
            pass
        return run_in_cluster

    def _get_cluster_job_file_path(self):
        cluster_job_file_path = None
        try:
            cluster_job_file_path = parameter_finder(self.anatomy_df, 'cluster_job_file_path')
        except (TypeError, NameError):
            pass
        return cluster_job_file_path

    def _get_cluster_number_of_nodes(self):
        cluster_number_of_nodes = 1
        try:
            cluster_number_of_nodes = int(parameter_finder(self.anatomy_df, 'cluster_number_of_nodes'))
        except (TypeError, NameError):
            pass
        if cluster_number_of_nodes > 40:
            raise Exception(' -  Number of nodes cannot be higher than 40 for your own safety.')
        return cluster_number_of_nodes

    def _get_metadata_filename(self,cluster_start_idx, cluster_step, job_suffix):
        metadata_filename = 'metadata_' + job_suffix + '.gz'
        if cluster_start_idx != -1 and cluster_step != -1:
            metadata_filename = 'metadata_part_' + str((cluster_start_idx / cluster_step) + 1) + job_suffix + '.gz'
        return metadata_filename

    def _get_arrun_cell_indices_from_df (self, df):
        arrun_search_result = df[df.applymap(lambda x: True if ('|' in str(x) or '&' in str(x)) else False)]
        arrays_indices = np.where(arrun_search_result.isnull().values != True)
        arrays_indices = [(arrays_indices[0][i], arrays_indices[1][i]) for i in range(len(arrays_indices[0]))]
        return arrays_indices
        
        
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
