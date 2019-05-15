from __future__ import division
import matplotlib.pyplot as plt
import matplotlib
import seaborn as sns; sns.set()
import scipy.io as spio
from collections import OrderedDict
import numpy as np
import re
import pandas as pd
import os.path
import zlib
import pickle as pickle
import bz2



class SimulationData(object):

    #default_data_file = '/home/henri/PycharmProjects/CX_Output/'
    default_data_file = '/opt3/CX_Output/calcium/calcium21_2s.gz'
    default_data_file_path = '/opt3/tmp/arraytest/'
    default_sampling_frequency = 1000

    group_numbering = {1: 'NG1_L1i_L1', 2: 'NG2_PC_L2toL1', 3: 'NG3_BC_L2', 4: 'NG4_MC_L2', 5: 'NG5_PC_L4toL2',
                       6: 'NG6_PC_L4toL1', 7: 'NG7_SS_L4', 8: 'NG8_BC_L4', 9: 'NG9_MC_L4', 10: 'NG10_PC_L5toL1',
                       11: 'NG11_BC_L5', 12: 'NG12_MC_L5', 13: 'NG13_PC_L6toL4', 14: 'NG14_PC_L6toL1',
                       15: 'NG15_BC_L6', 16: 'NG16_MC_L6'}

    def __init__(self, data_file=default_data_file, data_path=default_data_file_path):

        basename = os.path.basename(data_file)
        data_loc = data_path + data_file
        if basename[-2:] == 'gz':
            self.data = self._loadgz(data_loc)
        elif basename[-3:] == 'mat':
            self.data = self._loadmat(data_loc)
        elif basename[-3:] == 'bz2':
            self.data = self._loadbz2(data_loc)
        else:
            print('Format not supported so no file was loaded.')

        self.datafile = data_file

        self.spikedata = self.data['spikes_all']  # [0] -> neuron indices inside group, [1] -> spike times
        self.spikedata = OrderedDict(sorted(self.spikedata.items(), key=self._group_name_for_ordering ))  # TODO Order nicely
        self.runtime = self.data['runtime']
        self.neuron_groups = [row[0] for row in self.spikedata.items()[1:]]

    def _loadgz(self, filename):
        with open(filename, 'rb') as fb:
            d_pickle = zlib.decompress(fb.read())
            data = pickle.loads(d_pickle)

        return data

    def _loadbz2(self, filename):
        with bz2.BZ2File(filename, 'rb') as fb:
            data = pickle.load(fb)

        return data

    def _loadmat(self, filename):
        '''
        this function should be called instead of direct spio.loadmat
        as it cures the problem of not properly recovering python dictionaries
        from mat files. It calls the function check keys to cure all entries
        which are still mat-objects
        '''
        data = spio.loadmat(filename, struct_as_record=False, squeeze_me=True)
        return self._check_keys(data)

    def _check_keys(self, dict):
        '''
        checks if entries in dictionary are mat-objects. If yes
        todict is called to change them to nested dictionaries
        '''
        for key in dict:
            if isinstance(dict[key], spio.matlab.mio5_params.mat_struct):
                dict[key] = self._todict(dict[key])
        return dict

    def _todict(self, matobj):
        '''
        A recursive function which constructs from matobjects nested dictionaries
        '''
        dict = {}
        for strg in matobj._fieldnames:
            elem = matobj.__dict__[strg]
            if isinstance(elem, spio.matlab.mio5_params.mat_struct):
                dict[strg] = self._todict(elem)
            else:
                dict[strg] = elem
        return dict

    def _group_name_for_ordering(self, spikedata):
        corrected_name = re.sub(r'NG(\w{1})_', r'NG0\1_', spikedata[0])
        return str(corrected_name)

    def _check_group_name(self, group):
        if isinstance(group, int):
            return SimulationData.group_numbering[group]
        else:
            return group

    def rasterplot(self):

        runtime = self.runtime
        fig = plt.figure()
        fig.suptitle(self.datafile)
        for index,group_spikes in enumerate(self.spikedata.items()[1:], start=1):
            ax = plt.subplot(16,1,index)
            plt.xlim([0, runtime])
            ylabel = plt.ylabel(group_spikes[0])
            ylabel.set_rotation(0)
            ax.set_yticklabels([])

            try:
                ax.scatter(group_spikes[1][1], group_spikes[1][0], s=0.1)
            except IndexError:
                pass

        plt.show()

    def spikes_spectrum_group(self, neuron_group):

        neuron_group = self._check_group_name(neuron_group)

        sampling_frequency = SimulationData.default_sampling_frequency
        delta_t = float(1/sampling_frequency)

        bins = np.arange(0.0, self.runtime+delta_t, delta_t)
        counts_n = len(bins)-1
        spikes = self.spikedata[neuron_group]
        freqs = np.fft.rfftfreq(counts_n, delta_t)

        try:
            binned_spikes = pd.cut(spikes[1], bins)
            counts = pd.value_counts(binned_spikes)
            counts = counts.reindex(binned_spikes.categories)  # value_counts orders by count so re-ordering is needed
            counts_tf = np.fft.rfft(counts)
            pow_spectrum = [pow(np.linalg.norm(x), 2) / counts_n for x in counts_tf]

        except IndexError:
            print('No spikes in group ' + neuron_group + '.')
            pow_spectrum = freqs


        return freqs, pow_spectrum

    def plot_spikes_spectra(self):

        fig = plt.figure()

        for index, group in enumerate(self.neuron_groups, start=1):
            ax = plt.subplot(4, 4, index)
            ax.set_yticklabels([])
            plt.title(group, fontsize=8)
            freqs, spectrum = self.spikes_spectrum_group(group)
            if freqs is spectrum:
                ax.set_axis_bgcolor((0.8, 0.8, 0.8))
            else:
                plt.plot(freqs, spectrum)

        plt.tight_layout(pad=0.1)
        fig.suptitle(os.path.basename(self.datafile), fontsize=16)
        plt.show()

    def spikes_spectrum_all(self):
        pass

    def plot_voltage(self, neuron_group):

        neuron_group = self._check_group_name(neuron_group)

        voltage = self.data['vm_all'][neuron_group]
        [plt.plot(voltage[i]) for i in range(0,len(voltage))]
        plt.show()

    def voltage_spectrum_group(self, neuron_group):

        neuron_group = self._check_group_name(neuron_group)
        sampling_frequency = 1000000
        delta_t = float(1 / sampling_frequency)
        bins = np.arange(0.0, self.runtime, delta_t)
        counts_n = len(bins) # Broken?
        freqs = np.fft.rfftfreq(counts_n, delta_t)
        counts_n = len(freqs)

        voltage = pd.DataFrame(data=self.data['vm_all'][neuron_group])
        voltage_aggregate = voltage.mean()

        voltage_agg_tf = np.fft.rfft(voltage_aggregate)
        pow_spectrum = [pow(np.linalg.norm(x), 2) / counts_n for x in voltage_agg_tf]

        return freqs, pow_spectrum

    def rasterplot_compressed(self, neurons_per_group=20, ax=None):
        print('Working on ' + self.datafile)
        spike_dict = dict()
        indices_dict = dict()
        number_of_group = {value: key for (key,value) in SimulationData.group_numbering.items()}

        for group in self.neuron_groups:
            print('   Processing ' + group)
            group_sp = self.spikedata[group]
            N = len(group_sp[0])  # = len(group_sp[1])
            if N > 0:
                spike_tuples = [(int(group_sp[0][i]), group_sp[1][i], group) for i in range(N)]
                spikes = pd.DataFrame(spike_tuples)
                spikes.columns = ['neuron_index', 'time', 'group']

                if len(spikes.neuron_index.unique()) > neurons_per_group:
                    indices = np.random.choice(spikes.neuron_index.unique(), neurons_per_group, replace=False)
                    spikes = spikes[spikes.neuron_index.isin(indices)]
                    start_index = (16 - number_of_group[group]) * neurons_per_group + 1
                    fixed_indices = range(start_index, start_index+neurons_per_group+1)
                    fixed_ind_dict = {indices[i]: fixed_indices[i] for i in range(neurons_per_group)}
                    spikes.neuron_index = spikes.neuron_index.map(fixed_ind_dict)

                    spike_dict[group] = spikes
                else:
                    print('   Group ' + group + ' has too few spiking neurons (or sampling was too sparse)! Skipping...')


        spike_df = pd.concat(spike_dict)
        if ax is None:
            plt.scatter(spike_df.time, spike_df.neuron_index, s=0.8)
            q = neurons_per_group
            runtime = self.data['runtime']

            ticklabels = ['VI', 'V', 'IV', 'II/III', 'I']
            plt.yticks([4 * q, 7 * q, 12 * q, 15 * q, 16 * q], ticklabels)
            plt.xticks(np.arange(runtime + 0.1, step=1))
            plt.xlabel('Time (s)')

            plt.xlim([0, runtime])
            plt.ylim([0, 16 * q])

            plt.show()

        else:
            scatplot = ax.scatter(spike_df.time, spike_df.neuron_index, s=0.6, c='gray')
            return scatplot


def calciumplot(sim_files, sim_titles, runtime, neurons_per_group=20):

    sim_n = len(sim_files)
    q = neurons_per_group

    ticklabels = ['VI', 'V', 'IV', 'II/III', 'I']
    w, h = matplotlib.figure.figaspect(1 / sim_n)
    fig, ax = plt.subplots(ncols=sim_n, figsize=(w, h), dpi=600)
    plt.style.use('seaborn-whitegrid')


    fig.suptitle('$Ca^{2+}$ concentration (mM)', fontsize=16)
    fig.subplots_adjust(top=0.85, bottom=0.1, left=0.03, right=0.97)
    plt.setp(ax, xticks=np.arange(runtime + 0.1, step=1),
             yticks=[4 * q, 7 * q, 12 * q, 15 * q, 16 * q], yticklabels=ticklabels, xlim=[0, runtime],
             ylim=[0, 16 * q],
             xlabel='Time (s)')

    [SimulationData(sim_files[i]).rasterplot_compressed(40, ax[i]) for i in range(sim_n)]
    [ax[i].set_title(sim_titles[i]) for i in range(sim_n)]

    #plt.tight_layout()
    #plt.savefig('calciumplot.eps', dpi=600)
    plt.savefig('calciumplot.png')
    #plt.show()


# MAIN

if __name__ == '__main__':

    simulations = ['Reimann_20161217_calcium50.bz2', 'Reimann_20161217_calcium35.bz2', 'Reimann_20161217_calcium25.bz2', 'Reimann_20161216_clockchange.bz2']
    sim_title = ['5.0', '3.5', '2.5', '2.0']

    calciumplot(sim_files=simulations, sim_titles=sim_title, neurons_per_group=40, runtime=1.0)


