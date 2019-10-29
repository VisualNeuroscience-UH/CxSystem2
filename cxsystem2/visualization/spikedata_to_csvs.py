import zlib
import pickle
import numpy as np
import matplotlib.pyplot as plt
import pandas as pd
from brian2.units import *
from pathlib import Path


class SpikeData(object):

    def __init__(self, filename):

        self.data_filename = filename
        self.filename_stem = Path(filename).stem
        self.data = self.get_spike_data()

    def get_spike_data(self):
        fi = open(self.data_filename, 'rb')
        data_pickle = zlib.decompress(fi.read())
        data = pickle.loads(data_pickle)
        return data

    def _get_start_indices(self):
        a = np.cumsum(list(self.data['number_of_neurons'].values()))
        abs_start_index = [0]
        abs_start_index.extend(a)
        abs_start_index = np.array(abs_start_index)
        abs_start_index = abs_start_index + 1

        return abs_start_index

    def get_spike_list(self):
        # Create a list of start indices
        abs_start_index = self._get_start_indices()

        # Count all spikes
        N_spikes = 0
        for group in self.data['spikes_all'].keys():
            N_spikes += self.data['spikes_all'][group]['N']

        # Create an array of spikes
        spikelist = np.zeros((N_spikes, 2))

        list_ix = 0
        group_ix = 0
        for group in self.data['spikes_all'].keys():
            N_spikes_in_group = self.data['spikes_all'][group]['N']

            spikelist[list_ix:list_ix + N_spikes_in_group, 0] = self.data['spikes_all'][group]['i'] + abs_start_index[group_ix]
            spikelist[list_ix:list_ix + N_spikes_in_group, 1] = self.data['spikes_all'][group]['t'] / ms

            list_ix += N_spikes_in_group
            group_ix += 1

        return spikelist

    def _get_z_level(self, group_name):
        """

        :param group_name: str, format NGi_NEURONTYPE_LAYER
        :return:
        """
        z_level = {'NG0_relay_vpm': 0, 'NG1_L1_L1I_L1': 0.01, 'NG2_L23_PC_L2toL1': 0.02, 'NG3_L23_BC_L2': 0.02,
                   'NG4_L23_MC_L2': 0.02, 'NG5_L4_PC1_L4toL1': 0.03, 'NG6_L4_PC2_L4toL1': 0.03, 'NG7_L4_SS_L4': 0.03,
                   'NG8_L4_BC_L4': 0.03, 'NG9_L4_MC_L4': 0.03, 'NG10_L5_PC_L5toL1': 0.04, 'NG11_L5_BC_L5': 0.04,
                   'NG12_L5_MC_L5': 0.04, 'NG13_L6_PC1_L6toL6': 0.05, 'NG14_L6_PC2_L6toL4': 0.05,
                   'NG15_L6_PC3_L6toL2': 0.05, 'NG16_L6_BC_L6': 0.05, 'NG17_L6_MC_L6': 0.05}
        return z_level[group_name]

    def get_positions_list(self):
        start_ix = self._get_start_indices()
        N_neurons = start_ix[-1]
        coords = self.data['positions_all']['z_coord']

        all_positions = np.zeros((N_neurons, 3))

        group_ix = 0
        for group in coords.keys():
            group_pos = np.array(coords[group])
            group_z = self._get_z_level(group)

            x = np.array([(neuron_pos.real, neuron_pos.imag, group_z) for neuron_pos in group_pos])
            all_positions[start_ix[group_ix]:start_ix[group_ix+1], :] = x

            group_ix += 1
            # for neuron_pos in group_pos:
            #     positions_df = positions_df.append({'x': neuron_pos.real, 'y': neuron_pos.imag,
            #                                         'z': z_level[group]}, ignore_index=True)

        return all_positions


    def save_as_csvs(self, structure_csv=None, spikes_csv=None):
        if structure_csv is None:
            structure_csv = self.filename_stem + '_structure.csv'
        if spikes_csv is None:
            spikes_csv = self.filename_stem + '_spikes.csv'

        positions_list = self.get_positions_list()
        np.savetxt(structure_csv, positions_list, delimiter=',', fmt='%.9f')

        spike_list = self.get_spike_list()
        np.savetxt(spikes_csv, spike_list, delimiter=',', fmt=['%d', '%.1f'])


if __name__ == '__main__':
    x = SpikeData('/home/henhok/visimpl/markram_step2_data.gz')
    x.save_as_csvs()