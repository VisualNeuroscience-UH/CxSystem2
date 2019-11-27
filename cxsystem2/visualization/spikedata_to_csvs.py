import json
import pickle
import re
import zlib
from pathlib import Path

import numpy as np
from brian2.units import *


class SpikeData:

    def __init__(self, filename):

        self.data_filename = filename
        self.filename_stem = Path(filename).stem
        self.file_dir = Path(filename).parent
        self.data = self.get_spike_data()

    def get_spike_data(self):
        """
        Reads data from a CxSystem results file

        :return: dict
        """

        fi = open(self.data_filename, 'rb')
        data_pickle = zlib.decompress(fi.read())
        data = pickle.loads(data_pickle)
        return data

    def _get_start_indices(self, return_names=False):
        """
        Returns the starting indices of each neuron group. Last value is the total number of neurons.
        The neuron group names are returned as a separate array if asked.
        Counting starts from 1 (unlike in Brian2/Python) to conform with ViSimpl/StackViz.

        :param return_names: True/False (default False), whether to get also group names
        :return:
        """

        a = np.cumsum(list(self.data['number_of_neurons'].values()))
        abs_start_index = [0]
        abs_start_index.extend(a)
        abs_start_index = np.array(abs_start_index)
        abs_start_index = abs_start_index + 1

        if return_names is False:
            return abs_start_index
        else:
            group_names = np.array(list(self.data['number_of_neurons'].keys()))
            return abs_start_index, group_names

    def get_spike_list(self):
        """
        Creates an N_spikes x 2 matrix of spikes, where N_spikes = number of spikes, column 0 = neuron index,
        and column 1 = spike time.
        Spike times saved in seconds since this is the default unit in ViSimpl.

        :return: numpy array
        """
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
            spikelist[list_ix:list_ix + N_spikes_in_group, 1] = self.data['spikes_all'][group]['t'] / second

            list_ix += N_spikes_in_group
            group_ix += 1

        return spikelist

    def _get_z_level(self, group_name):
        """
        Returns a (discrete) z coordinate for the group based on the group name.
        Neurons in CxSystem are not given a z coordinate but they are placed in discrete layers and
        the layer name is automatically added at the end of the neuron group's name.

        :param group_name: str, format NGi_NEURONTYPE_LAYER (layer can be "L5", or for PCs, "L5toL1")
        :return:
        """
        # Example of a fixed mapping
        # z_level = {'NG0_relay_vpm': 0, 'NG1_L1_L1I_L1': 0.01, 'NG2_L23_PC_L2toL1': 0.02, 'NG3_L23_BC_L2': 0.02,
        #            'NG4_L23_MC_L2': 0.02, 'NG5_L4_PC1_L4toL1': 0.03, 'NG6_L4_PC2_L4toL1': 0.03, 'NG7_L4_SS_L4': 0.03,
        #            'NG8_L4_BC_L4': 0.03, 'NG9_L4_MC_L4': 0.03, 'NG10_L5_PC_L5toL1': 0.04, 'NG11_L5_BC_L5': 0.04,
        #            'NG12_L5_MC_L5': 0.04, 'NG13_L6_PC1_L6toL6': 0.05, 'NG14_L6_PC2_L6toL4': 0.05,
        #            'NG15_L6_PC3_L6toL2': 0.05, 'NG16_L6_BC_L6': 0.05, 'NG17_L6_MC_L6': 0.05}
        try:
            layer_number = int(re.findall('^.*_L(\d)\w*$', group_name)[0])  # by convention, L2/3 is "L2"
        except IndexError:
            layer_number = 0

        # Layer thicknesses from Markram et al 2015 Cell:
        # L1 165um, L2/3 502um, L4 190um, L5 525um, L6 700um => total 2082um
        z_level = {6: 0, 5: 700e-3, 4: 1225e-3, 2: 1415e-3, 1: 1917e-3, 0: 2082e-3}

        return z_level[layer_number]

    def get_positions_list(self, xy_multiplier=(1500.0/50000), z_multiplier=(1500.0/50000), return_subsets=True):
        """
        Creates a N_neurons x 3 matrix of neurons, where N_neurons = number of neurons,
        column 0 = x position, column 1 = y position, and column 2 = z position.
        Neuron index implicitly encoded by row number (as expected by ViSimpl/StackViz).
        XY-multipliers set here for visually pleasing results in ViSimpl.

        :param xy_multiplier: scalar, how much to scale x-y coordinates
        :param xy_multiplier: scalar, how much to scale z coordinate
        :param return_subsets: True/False (default x),
        :return:
        """
        start_ix, group_names = self._get_start_indices(return_names=True)
        N_neurons = start_ix[-1]
        # In CxSystem, w = position in cortex, in millimeters (and z = position in retina)
        coords = self.data['positions_all']['w_coord']

        all_positions = np.zeros((N_neurons, 3))

        group_ix = 0
        for group in coords.keys():
            group_pos = np.array(coords[group])
            group_z = self._get_z_level(group)

            x = np.array([(xy_multiplier * neuron_pos.real, xy_multiplier * neuron_pos.imag, z_multiplier * group_z)
                          for neuron_pos in group_pos])

            all_positions[start_ix[group_ix]:start_ix[group_ix+1], :] = x

            group_ix += 1
            # for neuron_pos in group_pos:
            #     positions_df = positions_df.append({'x': neuron_pos.real, 'y': neuron_pos.imag,
            #                                         'z': z_level[group]}, ignore_index=True)

        if return_subsets is False:
            return all_positions
        else:
            subsets_dict = dict()
            for i, group_name in enumerate(group_names):
                subsets_dict[group_name] = np.array([start_ix[i], start_ix[i+1]-1])

            return all_positions, subsets_dict

    def _convert_subsets_dict_to_visimpl_json(self, subsets_dict):
        """
        Converts the subsets dict to ViSimpl/Stackviz-specific JSON format

        :param subsets_dict: dict with entries group_name: [start_ix, last_ix]
        :return:
        """

        visimpl_se_dict = {'subsets': [], 'timeframes': []}  # se = subsets & events
        for group in subsets_dict.keys():
            start_ix = subsets_dict[group][0]
            last_ix = subsets_dict[group][1]
            # In ViSimpl, subsets are given as first_index:last_index
            tmp_subset_dict = {group: str(start_ix) + ":" + str(last_ix)}
            visimpl_se_dict['subsets'].append(tmp_subset_dict)

        return json.dumps(visimpl_se_dict)

    def save_for_visimpl(self, structure_csv=None, spikes_csv=None, subsets_json=None):
        if structure_csv is None:
            structure_csv = self.file_dir.joinpath(Path(self.filename_stem + '_structure.csv'))
        if spikes_csv is None:
            spikes_csv = self.file_dir.joinpath(Path(self.filename_stem + '_spikes.csv'))
        if subsets_json is None:
            subsets_json = self.file_dir.joinpath(Path(self.filename_stem + '_subsets.json'))

        positions_list, subsets_dict = self.get_positions_list()
        np.savetxt(structure_csv, positions_list, delimiter=',', fmt='%.9f')

        spike_list = self.get_spike_list()
        np.savetxt(spikes_csv, spike_list, delimiter=',', fmt=['%d', '%.9f'])

        subsets_json_data = self._convert_subsets_dict_to_visimpl_json(subsets_dict)
        with open(subsets_json, 'w') as fi:
            fi.write(subsets_json_data)

        return structure_csv, spikes_csv, subsets_json


if __name__ == '__main__':

    x = SpikeData('/home/henhok/sim_results/step2_output.gz')
    x.save_for_visimpl()
