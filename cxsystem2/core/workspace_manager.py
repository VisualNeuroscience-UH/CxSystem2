# -*- coding: utf-8 -*-
__author__ = 'Andalibi, V., Hokkanen H., Vanni, S.'

'''
The preliminary version of this software has been developed at Aalto University 2012-2015, 
and the full version at the University of Helsinki 2013-2017. The software is distributed 
under the terms of the GNU General Public License. 
Copyright 2017 Vafa Andalibi, Henri Hokkanen and Simo Vanni.
'''


from brian2  import *
from numpy import *
import os
import ntpath
import pickle as pickle
import zlib
import bz2
from pathlib import Path

class workspace(object):
    '''
    As the name implies, this module is used for gathering the data and saving the result.
    '''
    def __init__(self, workspace_path,  suffix):
        '''
        Initializes the save_data object.

        :param save_path: The path for saving the data.
        :param suffix: the string containing date and time that is supposed to be unique for each simulation and is used as a suffix for file names.

        Main internal variables:

        * data: the main variable to be saved. It contains all the data about the positions of the NeuronGroup()s as well as the monitor results.
        * syntax_bank: Since the monitors are explicitly defined in the Globals(), extracting the data from them requires addressing their name explicitely. To automatize this process, the syntaxes for extracting the data from the target monitors are generated and saved in this variable, so that they can be run at the end of the simulation.
        '''
        self.workspace_path = Path(workspace_path).expanduser()
        assert self.workspace_path.is_absolute(), "workspace path must be absolute."
        if not self.workspace_path.is_dir():
            os.makedirs(self.workspace_path.as_posix())
        self.suffix = suffix
        self.output_extension = '.gz'
        self.compression_to_extension = {
            'gzip': '.gz',
            'bzip2': 'bz2',
            'pickle': '.pickle'
        }
        self.results = {}
        self.connections = {}
        self.syntax_bank = []

    def set_compression_method(self,compression_method):
        self.output_extension = self.compression_to_extension[compression_method]

    def create_simulation(self,sim_name):
        self.simulation_name = sim_name + self.suffix
        self.simulation_folder = self.workspace_path.joinpath(self.simulation_name)
        assert not self.simulation_folder.is_dir() , "simulation folder {} already exists, please run the simulation again, the suffix will change automatically".format(self.simulation_folder)
        os.makedirs(self.simulation_folder.as_posix())
        self.results_export_path = self.simulation_folder.joinpath('results').with_suffix(self.output_extension)
        print(" -  The output of the simulation is saved at: {}".format(self.results_export_path))
        self.connections_export_path = self.simulation_folder.joinpath('connections').with_suffix((self.output_extension))

    def get_simulation_folder(self):
        return self.simulation_folder

    def get_output_extension(self):
        return self.output_extension

    def set_imported_connection_path(self, path):
        self.imported_connections_path = Path(path)


    def import_connections(self):
        assert self.imported_connections_path.suffix in self.compression_to_extension.values(), \
            ' -  Compression method {} is not supported. Supported methods are gz, bz2 or pickle'.format(self.imported_connections_path.suffix)
        if not self.imported_connections_path.is_absolute():
            if self.workspace_path.joinpath(self.imported_connections_path).is_file():
                self.imported_connections_path = self.workspace_path.joinpath(self.imported_connections_path)
            elif Path.cwd().joinpath(self.imported_connections_path).is_file():
                self.imported_connections_path = Path.cwd().joinpath(self.imported_connections_path)
            else:
                raise FileNotFoundError(' -  Connection file not found: {}'.format(self.imported_connections_path.as_posix()))
        return self.load_from_file(self.imported_connections_path)


    def create_results_key(self, key):
        '''
        In case the user wants to save a peculiar variable, this method can be used to check and create a new key in data dictionary (if does not exist).

        :param key: name of the key to be created in the final data variable.
        '''
        if not key in self.results:
            self.results[key] = {}

    def create_connections_key(self, key):
        '''
        In case the user wants to save a peculiar variable, this method can be used to check and create a new key in data dictionary (if does not exist).

        :param key: name of the key to be created in the final data variable.
        '''
        if not key in self.connections:
            self.connections[key] = {}


    def save_results_to_file(self):
        print(" -  Saving results to file ...")
        self.results['Full path'] = self.results_export_path
        while os.path.isfile(self.results_export_path):
            idx = 1
            self.results_export_path = self.results_export_path.parent.joinpath(
                self.results_export_path.stem + '_{}'.format(idx) + self.results_export_path.suffix)
            idx +=1
        self.save_to_file(self.results, self.results_export_path)

    def save_connections_to_file(self):
        print(" -  Saving connections to file ...")
        self.connections['Full path'] = self.connections_export_path
        while os.path.isfile(self.connections_export_path):
            idx = 1
            self.connections_export_path = self.connections_export_path.parent.joinpath(
                self.connections_export_path.stem +  '_{}'.format(idx) + self.connections_export_path.suffix)
            idx +=1
        self.save_to_file(self.connections, self.connections_export_path)

    def save_to_file(self, data, filepath):
        if 'gz' in self.get_output_extension():
            with open(filepath, 'wb') as fb:
                fb.write(zlib.compress(pickle.dumps(data, pickle.HIGHEST_PROTOCOL), 9))
        elif 'bz2' in self.get_output_extension():
            with bz2.BZ2File(filepath, 'wb') as fb:
                pickle.dump(data, fb, pickle.HIGHEST_PROTOCOL)
        elif 'pickle' in self.get_output_extension():
            with open(filepath, 'wb') as fb:
                pickle.dump(data,fb , pickle.HIGHEST_PROTOCOL)


    def load_from_file(self, file_path):
        if file_path.suffix == '.gz':
            with open(file_path, 'rb') as fb:
                data = zlib.decompress(fb.read())
                loaded_data = pickle.loads(data)
        elif file_path.suffix == '.bz2':
            with bz2.BZ2File(file_path, 'rb') as fb:
                loaded_data = pickle.load(fb)
        elif file_path.suffix == '.pickle':
            with open(file_path, 'rb') as fb:
                loaded_data= pickle.load(fb)
        return loaded_data