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
import _pickle as pickle
import zlib
import bz2

class save_data(object):
    '''
    As the name implies, this module is used for gathering the data and saving the result.
    '''
    def __init__(self,save_path,datetime_str):
        '''
        Initializes the save_data object.

        :param save_path: The path for saving the data.
        :param datetime_str: the string containing date and time that is supposed to be unique for each simulation and is used as a suffix for file names.

        Main internal variables:

        * data: the main variable to be saved. It contains all the data about the positions of the NeuronGroup()s as well as the monitor results.
        * syntax_bank: Since the monitors are explicitly defined in the Globals(), extracting the data from them requires addressing their name explicitely. To automatize this process, the syntaxes for extracting the data from the target monitors are generated and saved in this variable, so that they can be run at the end of the simulation.
        '''
        self.save_path = save_path
        self.datetime_str = datetime_str
        self.save_filename = ntpath.basename(self.save_path)
        self.save_pure_filename = os.path.basename(os.path.splitext(self.save_path)[0])

        self.save_folder = ntpath.dirname(self.save_path)
        self.save_extension = os.path.splitext(self.save_path)[1]
        if os.getcwd() in self.save_path:
            print(" -  The output of the system is saved in %s"
                   %os.path.abspath(os.path.join(os.getcwd(), os.pardir)))
            self.save_folder = os.path.abspath(os.path.join(os.getcwd(), os.pardir))
            self.save_path = os.path.join(self.save_folder,self.save_filename)
        self.data = {}
        self.syntax_bank = []

    def create_key(self,key):
        '''
        In case the user wants to save a peculiar variable, this method can be used to check and create a new key in data dictionary (if does not exist).

        :param key: name of the key to be created in the final data variable.
        '''
        if not key in self.data:
            self.data[key] = {}

    def gather_result(self):
        '''
        Gather the result by running the syntaxes previously saved in the syntax bank before running the simulation.
        '''
        for syntax in self.syntax_bank:
            exec (syntax)
        self.save_to_file()

    def save_to_file(self):
        print(" -  Saving data to file ...")
        if not os.path.exists(self.save_folder):
            os.makedirs(self.save_folder)
        self.save_path = os.path.join(self.save_folder, self.save_pure_filename + self.datetime_str + self.save_extension)
        self.data['Full path'] = self.save_path
        while os.path.isfile(self.save_path):
            idx = 1
            self.save_path = os.path.join(self.save_folder, self.save_pure_filename + self.datetime_str  + '_%d'%idx + self.save_extension)
            idx +=1

        if 'gz' in self.save_extension:
            with open(self.save_path, 'wb') as fb:
                fb.write(zlib.compress(pickle.dumps(self.data, pickle.HIGHEST_PROTOCOL), 9))
        elif 'bz2' in self.save_extension:
            with bz2.BZ2File(self.save_path, 'wb') as fb:
                pickle.dump(self.data, fb, pickle.HIGHEST_PROTOCOL)
        elif 'pickle' in self.save_extension:
            with open(self.save_path, 'wb') as fb:
                pickle.dump(self.data,fb , pickle.HIGHEST_PROTOCOL)

