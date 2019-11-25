# -*- coding: utf-8 -*-
__author__ = 'Andalibi, V., Hokkanen H., Vanni, S.'

'''
The preliminary version of this software has been developed at Aalto University 2012-2015, 
and the full version at the University of Helsinki 2013-2017. The software is distributed 
under the terms of the GNU General Public License. 
Copyright 2017 Vafa Andalibi, Henri Hokkanen and Simo Vanni.
'''

import os
import shutil

import brian2 as b2
import numpy as np
from brian2.units import *
from scipy import io

from cxsystem2.core.tools import write_to_file, load_from_file


class Stimuli:
    """
    [Extracted from VCXmodel] This is the stimulation object for applying the input to a particular NeuronGroup().
    Currently only video input is supported.
    """

    def __init__(self, duration, input_mat_path, output_folder, output_file_suffix, output_file_extension):
        """
        Initializes the input module for and instance of CxSystem.

        :param duration:
        :param input_mat_path: .mat file location
        :param output_folder: location of the saved output
        :param output_file_suffix: suffix for the output file
        :param output_file_extension: extension for the output file, i.e. gz, bz2, pickle
        """
        self.i_patterns = {}
        self.BaseLine = 0 * second
        self.input_mat_path = input_mat_path
        self.duration = duration
        self.output_folder = output_folder
        self.output_file_suffix = output_file_suffix
        self.output_file_extension = output_file_extension
        # print "\nWarning: Generated input spike sequence exist in %s/input%s " \
        #       "\nThe input will NOT be overwritten. " \
        #       "\nIf you need the spikes regenerated or permanently saved, \nplease rename or remove the previous spike sequence file.\n" % (
        #       self.output_folder,self.output_file_extension)

    def generate_inputs(self, freq):
        """
        The method for generating input based on the .mat file, using the internal _initialize_inputs() and _calculate_input_seqs() methods.

        :param freq: frequency.
        """
        self.initialize_inputs(freq)
        self.calculate_input_seqs()

    def initialize_inputs(self, freq):
        print(" -  Initializing stimuli ...")

        # type : video
        _V1_mats = {}

        io.loadmat(os.path.abspath(self.input_mat_path), _V1_mats)
        self.w_coord = _V1_mats['w_coord']
        self.z_coord = _V1_mats['z_coord']
        # Fill ISI with N-1 times frameduration of zeros
        soa = 60  # in ms
        stimulus_epoch_duration = 15  # in ms, duration of Burbank whole stimulus
        assert np.mod(soa, stimulus_epoch_duration) == 0, ' -  Stimulus onset asynchrony (soa) must be an integer times frameduration.'
        soa_in_n_frames = int(soa / stimulus_epoch_duration)
        dense_stimulus = _V1_mats['stimulus']
        sparse_stimulus = np.tile(np.zeros_like(dense_stimulus), (1, soa_in_n_frames))
        sparse_stimulus[:, 0::soa_in_n_frames] = dense_stimulus

        try:
            frameduration = b2.double(_V1_mats['frameduration'])
            raise NotImplementedError('Frameduration coming from actual video frame rate. This is not implemented yet for CxSystem')
        except:
            frameduration = stimulus_epoch_duration
        frames = b2.TimedArray(np.transpose(sparse_stimulus),
                               dt=frameduration * ms)  # video_data has to be shape (frames, neurons), dt=frame rate
        self.frames = frames
        exec('self.factor = %s' % freq)
        self.i_patterns[len(self.i_patterns)] = frames.values * self.factor  # These must be final firing rates
        _all_stim = np.squeeze(_V1_mats['stimulus'])
        if len(_all_stim.shape) == 2:
            slash_indices = [idx for idx, ltr in enumerate(self.input_mat_path) if ltr == '/']
            print(' -  One video stimulus found in file ' + self.input_mat_path[slash_indices[-1] + 1:])

    def calculate_input_seqs(self):
        """
        Calculating input sequence based on the video input.
        """
        b2.set_device('cpp_standalone', directory=os.path.join(self.output_folder, 'Input_cpp_run' + self.output_file_suffix))
        # inputdt = b2.defaultclock.dt
        spikemons = []
        n0 = len(self.i_patterns[0].T)
        # frames = self.frames
        # factor = self.factor
        tmp_group = b2.NeuronGroup(n0, 'rate = frames(t,i)*factor : Hz', threshold='b2.rand()<rate*dt')
        tmp_network = b2.Network()
        tmp_network.add(tmp_group)
        tmp_mon = b2.SpikeMonitor(tmp_group)
        tmp_network.add(tmp_mon)
        spikemons.append(tmp_mon)
        if self.BaseLine == 0 * second:
            tmp_network.run(self.duration, report='text')
        else:
            tmp_network.run(self.BaseLine)
            tmp_network.run(self.duration - self.BaseLine)
        self.save_input_sequence(spikemons, os.path.join(self.output_folder, 'input' + self.output_file_suffix))
        shutil.rmtree(os.path.join(self.output_folder, 'Input_cpp_run' + self.output_file_suffix))

    def save_input_sequence(self, spike_mons, save_path):
        print(" -  Saving the generated video input...")
        self.generated_input_folder = save_path + self.output_file_extension
        data_to_save = {}
        for ii in range(len(spike_mons)):
            data_to_save['spikes_' + str(ii)] = []
            data_to_save['spikes_' + str(ii)].append(spike_mons[ii].it[0].__array__())
            data_to_save['spikes_' + str(ii)].append(spike_mons[ii].it[1].__array__())
        data_to_save['w_coord'] = self.w_coord
        data_to_save['z_coord'] = self.z_coord
        write_to_file(save_path + self.output_file_extension, data_to_save)

    def load_input_seq(self, input_spike_file_location):
        """
        Loads spikes from file.

        :param input_spike_file_location: Location of the file to load spikes.
        """
        if os.path.isfile(input_spike_file_location):
            input_spike_file_location = input_spike_file_location
        else:
            input_spike_file_location = os.path.join(input_spike_file_location, 'input' + self.output_file_suffix + self.output_file_extension)
        self.loaded_data = load_from_file(input_spike_file_location)
        new_spikes = self.loaded_data['spikes_0']
        neuron_positions_in_cortex = io.loadmat(self.input_mat_path, variable_names='w_coord')
        number_of_neurons = len(neuron_positions_in_cortex['w_coord'])
        print(" -  Video input loaded")
        return new_spikes[0], new_spikes[1], number_of_neurons

    def get_input_positions(self):
        """
        Extract the positions from the .mat file.
        """
        neuron_positions = io.loadmat(self.input_mat_path, variable_names='z_coord')
        return neuron_positions['z_coord']
