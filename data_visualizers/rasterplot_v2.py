"""
The program is distributed under the terms of the GNU General Public License
Copyright 2017 Vafa Andalibi, Simo Vanni, Henri Hokkanen.

Papers and books that are referenced in this file:
    Piwkowska et al. (2008). J Neurosci Met 169: 302-22.
    Potjans T. & Diesmann M. (2014) Cer Cor 24 (3): 785-806
    Sterratt et al. (2011) Principles of Computational Modelling in Neuroscience. Cambridge University Press.

Version 2 for 1) handling output in new format (Brian monitors saved as such),
              2) not caring about number of neuron groups

"""

from __future__ import division
import matplotlib.pyplot as plt
import matplotlib
import seaborn as sns
import scipy.io as spio
from collections import OrderedDict
import numpy as np
import re
import pandas as pd
import os.path
import zlib
import cPickle as pickle
import bz2
from brian2 import *
import random
import pathos.multiprocessing as mp
from multiprocess import Manager
import datetime
from tqdm import *

from matplotlib.animation import FuncAnimation

matplotlib.rcParams['pdf.fonttype'] = 42
matplotlib.rcParams['ps.fonttype'] = 42

mycmap = 'binary'


class SimulationData(object):
    """
    Class for holding data from a single simulation with methods for visualizing the results

    Certain constants related to the Markram model which are necessary for visualising results
    are stored here (group numbering, numbers of neurons etc). The constants are fixed,
    so the class is NOT agnostic about network structure.
    """
    # TODO - Make class agnostic about network structure, ie extract following constants from datafile

    default_data_file_path = ''
    default_sampling_frequency = 1000
    defaultclock_dt = 0.1 * ms

    # default_group_numbering = {1: 'NG1_L1i_L1', 2: 'NG2_PC_L2toL1', 3: 'NG3_BC_L2', 4: 'NG4_MC_L2', 5: 'NG5_PC_L4toL2',
    #                            6: 'NG6_PC_L4toL1', 7: 'NG7_SS_L4', 8: 'NG8_BC_L4', 9: 'NG9_MC_L4', 10: 'NG10_PC_L5toL1',
    #                            11: 'NG11_BC_L5', 12: 'NG12_MC_L5', 13: 'NG13_PC_L6toL4', 14: 'NG14_PC_L6toL1',
    #                            15: 'NG15_BC_L6', 16: 'NG16_MC_L6'}

    # default_group_neuroncounts = {1: 338, 2: 5877, 3: 1198, 4: 425, 5: 2674, 6: 1098, 7: 406, 8: 329, 9: 137, 10: 5050,
    #                               11: 558, 12: 491, 13: 9825, 14: 1637, 15: 813, 16: 372}

    # default_group_to_type = {1: 'L1i', 2: 'PC', 3: 'BC', 4: 'MC', 5: 'PC', 6: 'PC', 7: 'SS', 8: 'BC', 9: 'MC', 10: 'PC',
    #                          11: 'BC', 12: 'MC', 13: 'PC', 14: 'PC', 15:'BC', 16:'MC'}

    layers = [2, 4, 5, 6]

    # Per group returns an array of [[excitatory] and [inhibitory]] groups
    # groups_of_layer = {1: [[], [1]], 2: [[2], [3, 4]], 4: [[5, 6, 7], [8,9]], 5: [[10], [11,12]], 6:[[13, 14], [15, 16]]}

    def __init__(self, data_file, data_path=default_data_file_path, group_numbering=None, group_neuroncounts=None, group_to_type=None):
        """
        :param data_file: filename to open from data_path (or default data path set in class constants)
        :param data_path: path where data_file is located (with trailing / included), optional
        """
        basename = os.path.basename(data_file)
        data_loc = data_path + data_file
        if basename[-2:] == 'gz':
            self.data = self._loadgz(data_loc)
        elif basename[-3:] == 'mat':
            self.data = self._loadmat(data_loc)
        elif basename[-3:] == 'bz2':
            self.data = self._loadbz2(data_loc)
        else:
            pass

        self.datafile = data_file

        # Let's make plotting agnostic about neuron groups! Will need changes in methods as well...
        if group_numbering is None:
            #self.group_numbering = SimulationData.default_group_numbering
            group_names = self.data['number_of_neurons'].keys()
            self.group_numbering = {int(re.findall('NG(\d+)_\w+', group_names[i])[0]): group_names[i] for i in range(len(group_names))}
        else:
            self.group_numbering = group_numbering

        if group_neuroncounts is None:
            #self.group_neuroncounts = SimulationData.default_group_neuroncounts
            neuron_counts = self.data['number_of_neurons']
            self.group_neuroncounts = {group_ix: neuron_counts[group_name] for group_ix, group_name in self.group_numbering.items()}
        else:
            self.group_neuroncounts = group_neuroncounts

        # if group_to_type is None:
        #     self.group_to_type = SimulationData.default_group_to_type
        # else:
        #     self.group_to_type = group_to_type

        # Extract spike data
        try:
            self.spikedata = self.data['spikes_all']  # [group][0] -> neuron indices inside group, [group][1] -> spike times
            self.spikedata = OrderedDict(sorted(self.spikedata.items(), key=self._group_name_for_ordering ))
            self.runtime = self.data['runtime']
            #self.neuron_groups = [row[0] for row in self.spikedata.items()[1:]]
            self.neuron_groups = self.data['number_of_neurons'].keys()

            self.anatomy_df = self.data['Anatomy_configuration']
            self.physio_df = self.data['Physiology_configuration']
        except:
            raise

    def _group_name_for_ordering(self, spikedata):
        """
        Internal dummy function used in arranging groups in correct order in __init__

        :param spikedata:
        :return: corrected name, eg. NG7 -> NG07
        """
        corrected_name = re.sub(r'NG(\w{1})_', r'NG0\1_', spikedata[0])
        return str(corrected_name)

    def _loadgz(self, filename):
        """
        Method for opening gz-packed simulation files (not used in CxSystem anymore)

        :param filename:
        :return: data
        """
        with open(filename, 'rb') as fb:
            d_pickle = zlib.decompress(fb.read())
            data = pickle.loads(d_pickle)

        return data

    def _loadbz2(self, filename):
        """
        Method for opening bz2-packed simulation files. This is the current way of packing in CxSystem.

        :param filename:
        :return: data
        """
        with bz2.BZ2File(filename, 'rb') as fb:
            #data = pickle.load(fb)  <- due to pandas update; pandas.pydata.org/pandas-docs/stable/io.html#pickling
            data = pd.read_pickle(fb)

        return data

    def _flatten(self, l):
        return [item for sublist in l for item in sublist]

    def value_extractor(self, df, key_name):
        """
        Method for extracting simulation parameters from anatomy and physiology configurations inside data files.
        This method coexists in several classes - a Configuration class is needed?

        :param df: dataframe to go through (now either self.anatomy_df or self.physio_df)
        :param key_name: simulation parameter to extract
        :return: value of the specified simulation parameter
        """
        # TODO - separate class Configuration for anatomy/physiology configs

        non_dict_indices = df['Variable'].dropna()[df['Key'].isnull()].index.tolist()
        for non_dict_idx in non_dict_indices:
            exec "%s=%s" % (df['Variable'][non_dict_idx], df['Value'][non_dict_idx])
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
                return eval(df['Value'][df['Key'] == key_name].item())
        except NameError:
            new_key = df['Value'][df['Key'] == key_name].item().replace("']", "").split("['")
            return self.value_extractor(df,new_key)
        except ValueError:
            raise ValueError("Parameter %s not found in the configuration file."%key_name)

    def get_sim_parameter(self, param_name):
        """
        Get value of a given parameter from anatomy or physiology configuration (no need to specify which)

        :param param_name: str, parameter name to search for
        :return:
        """
        try:
            return self.value_extractor(self.physio_df, param_name)
        except:
            try:
                return self.value_extractor(self.anatomy_df, param_name)
            except:
                return '???'

    def _check_group_name(self, group):
        """
        Internal function used to convert group identifier (integer) to group name (string) if necessary.

        :param group: str or int, group identifier
        :return: str, group name
        """
        if isinstance(group, int):
            return self.group_numbering[group]
        else:
            return group

    def _get_group_leak(self, group_id):
        """
        Internal function to extract the gL value of a specified group from physiology configuration

        :param group_id:
        :return:
        """

        physio_config = self.data['Physiology_configuration']
        number_of_rows = len(physio_config['Variable'])

        # Find in self.data['Physiology_configuration'] the line where group_id config starts
        begin_ix = list(physio_config['Variable']).index(self.default_group_to_type[group_id])  # list() so that we can use index()

        # Find where the next group's config starts (or the config file ends)
        end_ix = 0
        try:
            end_ix = (i for i in range(begin_ix+1, number_of_rows)
                      if type(physio_config['Variable'][i]) == str).next()  # Empty rows are floats, non-empty are strings
        except StopIteration:
            end_ix = number_of_rows

        # Take data from lines between those -> dict
        # params = dict()
        # for i in range(begin_ix, end_ix):
        #     params[physio_config['Key'][i]] = physio_config['Value'][i]

        if self.default_group_to_type[group_id] == 'PC':
            gL_index = list(physio_config['Key'][begin_ix:end_ix]).index('gL_soma')
        else:
            gL_index = list(physio_config['Key'][begin_ix:end_ix]).index('gL')

        return eval(physio_config['Value'][begin_ix + gL_index])

    def rasterplot(self):
        """
        Plots all spikes, subplot per neuron group

        """

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

    def _spikes_spectrum_group(self, neuron_group):
        """
        Computes spectral power with FFT for a given neuron group

        :param neuron_group: int/str, group id or group name
        :return: list of frequencies, list of corresponding powers
        """

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
            print 'No spikes in group ' + neuron_group + '.'
            pow_spectrum = freqs


        return freqs, pow_spectrum

    def spectrumplot(self):
        """
        Plots spectral power for all neuron groups

        """
        fig = plt.figure()

        for index, group in enumerate(self.neuron_groups, start=1):
            ax = plt.subplot(4, 4, index)
            ax.set_yticklabels([])
            plt.title(group, fontsize=8)
            freqs, spectrum = self._spikes_spectrum_group(group)
            if freqs is spectrum:
                ax.set_axis_bgcolor((0.8, 0.8, 0.8))
            else:
                plt.plot(freqs, spectrum)

        plt.tight_layout(pad=0.1)
        fig.suptitle(os.path.basename(self.datafile), fontsize=16)
        plt.show()

    def global_osc_freq(self, bin_size=3*ms, t_limits=None, plot=False):

        # PREPROCESS spike data
        timebin = bin_size/second
        if t_limits is None:
            t_start = 0*second
            t_end = self.runtime * second
        elif t_limits[1] == -1:
            t_start = t_limits[0]
            t_end = self.runtime * second
        else:
            t_start = t_limits[0]
            t_end = t_limits[1]

        window_duration = t_end - t_start

        allspikes = []
        for group in self.group_numbering.values():
            spikes_gp = self.data['spikes_all'][group]['t'] / second
            allspikes.extend(spikes_gp)
        allspikes = np.array(allspikes)
        allspikes.sort()
        try:
            start_ix = min(where(allspikes >= t_start / second)[0])
            end_ix = max(where(allspikes <= t_end / second)[0])
        except:
            return 'NA'

        allspikes = allspikes[start_ix:end_ix+1]

        # MAKE spike count histogram & Fourier transform of it -- frequencies x2 for some reason, check
        # n_bins2 = int(window_duration/timebin)
        # spike_counts2, bin_edges2 = np.histogram(allspikes, bins=n_bins2, range=(t_start/second, t_end/second))
        #
        # spike_counts_f = np.fft.rfft(spike_counts)
        # pow_spectrum = [abs(x)**2/n_bins for x in spike_counts_f]
        # freqs = np.fft.fftfreq(n=spike_counts_f.size, d=timebin)
        #
        # max_ix = argmax(pow_spectrum[1:])

        bin_edges = np.arange(t_start/second, t_end/second + timebin, timebin)
        n_bins = len(bin_edges) - 1

        binned_spikes = pd.cut(allspikes, bin_edges)
        spike_counts = pd.value_counts(binned_spikes)
        spike_counts = spike_counts.reindex(binned_spikes.categories)  # value_counts orders by count so re-ordering is needed
        spike_counts_f = np.fft.rfft(spike_counts)
        pow_spectrum = [abs(x)**2/n_bins for x in spike_counts_f]
        freqs = np.fft.rfftfreq(n_bins, timebin)

        # Find fundamental frequency
        power_cutoff = 0.25
        pow_spectrum_nozero = np.array(pow_spectrum[1:])
        max_ix = argmax(pow_spectrum_nozero)+1
        max_power_freq = freqs[max_ix]
        peak_ix = np.where(pow_spectrum_nozero > power_cutoff*pow_spectrum[max_ix])[0] +1
        peak_freqs = freqs[peak_ix]
        fund_freq = min(peak_freqs)

        if plot is False:
            return fund_freq

        else:
            plt.subplots(1,2)

            plt.subplot(121)
            plt.title('Spike count histogram (bin '+repr(bin_size)+')')
            plt.plot(np.linspace(t_start/second, t_end/second, n_bins), spike_counts)

            plt.subplot(122)
            plt.title('Fourier transform')
            plt.plot(freqs, pow_spectrum)
            ax = plt.gca()
            ax.axhline(y=power_cutoff*pow_spectrum[max_ix], linestyle='--', color='red')
            ax.axvline(x=fund_freq, linestyle='--', color='grey')
            plt.show()


    def _isi_cdf_group(self, group_id, t_limits=None, ax=None):

        # if t_limits is None:
        #     t_start = 0*second
        #     t_end = self.runtime * second
        # elif t_limits[1] == -1:
        #     t_start = t_limits[0]
        #     t_end = self.runtime * second
        # else:
        #     t_start = t_limits[0]
        #     t_end = t_limits[1]

        isis, spiking_neurons = self._interspikeintervals_group(group_id)
        isis = self._flatten(isis.values())
        max_isi = max(isis)
        isihist, bin_edges = np.histogram(isis, bins=500, range=(0,max_isi))
        N_isis = sum(isihist)
        cdf = cumsum(isihist)/N_isis


        if ax is None:
            plt.subplots(1, 2)
            plt.subplot(121)
            plt.title('ISI histogram')
            plt.plot(bin_edges[:-1], isihist)

            plt.subplot(122)
            plt.title('Cumulative ISI distribution')
            plt.plot(bin_edges[:-1], cdf)
            plt.show()
        else:
            ax.plot(bin_edges[:-1], cdf)

    def rasterplot_compressed(self, neurons_per_group=20, ax=None):
        """
        Plots a simplified rasterplot with only layers labeled, not neuron groups. Possibly useful for publications.

        :param neurons_per_group: int, used to avoid the plot becoming too busy (default=20)
        :param ax: matplotlib Axes-object to draw plot on, optional
        :return: nothing
        """
        print 'Working on ' + self.datafile
        spike_dict = dict()
        indices_dict = dict()
        number_of_group = {value: key for (key,value) in SimulationData.default_group_numbering.items()}

        for group in self.neuron_groups:
            print '   Processing ' + group
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
                    print '   Group ' + group + ' has too few spiking neurons (or sampling was too sparse)! Skipping...'


        try:
            spike_df = pd.concat(spike_dict)
        except:
            spike_df = pd.DataFrame(columns=['time', 'neuron_index'])  # if there's nothing to concat, create an empty df

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
            ax.scatter(spike_df.time, spike_df.neuron_index, s=0.6, c='gray')


    def publicationplot(self, sampling_factor=30, time_rounding=3, time_limits=None, plot_type=2, ax=None):
        """
        Plots a simplified rasterplot with only layers labeled, not neuron groups. Takes relative amount of
        neurons in each group into account. Possibly useful for publications.

        :param sampling_factor: int, factor used to down-scale the amount of neurons to plot
        :param ax: matplotlib Axes-object to draw plot on, optional
        :return: nothing
        """
        print 'Working on ' + self.datafile
        spike_dict = dict()
        indices_dict = dict()
        runtime = self.data['runtime']
        if time_limits is None:
            time_limits = [0, runtime] * second

        number_of_group = {value: key for (key,value) in self.group_numbering.items()}
        N_neurongroups = len(self.group_numbering.keys())

        max_neurons_per_group = [int(self.group_neuroncounts[i] / sampling_factor) for i in range(1, N_neurongroups)]

        for group in self.neuron_groups:
            print '   Processing ' + group
            group_sp = self.spikedata[group]
            # N = len(group_sp[0])  # = len(group_sp[1])
            N = len(group_sp['i'])  # = len(group_sp[1])

            if N > 0:  # ie. if the group spiked at all
                spike_tuples = [(int(group_sp['i'][ix]), group_sp['t'][ix], group) for ix in range(N)]
                spikes = pd.DataFrame(spike_tuples)
                spikes.columns = ['neuron_index', 'time', 'group']

                neurons_per_group = max_neurons_per_group[number_of_group[group]-1]

                # TODO - fails at plotting non-spiking neurons
                if len(spikes.neuron_index.unique()) >= neurons_per_group:
                    indices = np.random.choice(spikes.neuron_index.unique(), neurons_per_group, replace=False)
                    spikes = spikes[spikes.neuron_index.isin(indices)]
                    #start_index = (16 - number_of_group[group]) * neurons_per_group + 1
                    start_index = int(sum(max_neurons_per_group[number_of_group[group]:N_neurongroups]) + 1)
                    fixed_indices = range(start_index, start_index+neurons_per_group+1)
                    fixed_ind_dict = {indices[i]: fixed_indices[i] for i in range(neurons_per_group)}
                    spikes.neuron_index = spikes.neuron_index.map(fixed_ind_dict)

                    # Just to make sure there is no extra data points floating around
                    # (appearing later in eg. Illustrator):
                    #spikes = spikes[spikes.time <= time_limits[1]][spikes.time >= time_limits[0]]
                    spike_dict[group] = spikes
                else:
                    print '   Group ' + group + ' has too few spiking neurons (or sampling was sparse)! Skipping...'


        try:
            spike_df = pd.concat(spike_dict)
            spike_df.time = numpy.round(spike_df.time/second, time_rounding)  # Decrease time-resolution here
        except:
            spike_df = pd.DataFrame(data={'time':[0], 'neuron_index':[0]})  # if there's nothing to concat, create an empty df

        #q = neurons_per_group
        if plot_type == 2:
            # NEEDS FIXIN
            q1 = sum(max_neurons_per_group[13-1:N_neurongroups])
            q2 = sum(max_neurons_per_group[10-1:N_neurongroups])
            q3 = sum(max_neurons_per_group[5-1:N_neurongroups])
            q4 = sum(max_neurons_per_group[2-1:N_neurongroups])
            q5 = sum(max_neurons_per_group[0:N_neurongroups])
            ticklabels = ['VI', 'V', 'IV', 'II/III', 'I']

        elif plot_type == 1:
            q1 = sum(max_neurons_per_group[42-1:N_neurongroups])
            q2 = sum(max_neurons_per_group[29-1:N_neurongroups])
            q3 = sum(max_neurons_per_group[17-1:N_neurongroups])
            q4 = sum(max_neurons_per_group[7-1:N_neurongroups])
            q5 = sum(max_neurons_per_group[0:N_neurongroups])
            ticklabels = ['VI', 'V', 'IV', 'II/III', 'I']

        if ax is None:

            plt.scatter(spike_df.time, spike_df.neuron_index, color='k', s=0.5)


            plt.yticks([q1, q2, q3, q4, q5], ticklabels, fontsize=16)
            plt.ylim([0, q5])

            plt.xticks(np.arange(runtime + 0.1, step=1), fontsize=12)
            plt.xlabel('Time (s)', fontsize=12)
            plt.xlim([time_limits[0]/second, time_limits[1]/second])
            plt.show()

        else:
            ax.scatter(spike_df.time, spike_df.neuron_index, color='k', s=0.5)
            #if plot_type == 0:
            ax.set_yticks([q1, q2, q3, q4, q5])
            ax.set_ylim([0, q5])
            ax.set_yticklabels(ticklabels, fontsize=12, fontweight='bold')

            ax.set_xticks(np.arange(runtime + 0.1, step=1))
            ax.set_xlabel('Time [s]', fontsize=12, fontweight='bold')
            ax.set_xlim([time_limits[0], time_limits[1]])



    def voltage_rasterplot(self, max_per_group=20, dt_downsampling_factor=10):
        """
        Plots voltage of neurons with membrane voltage represented on continuous colour scale.

        :param max_per_group: int, maximum number of neurons per group to include in plotting (default=20)
        :param dt_downsampling_factor: int, factor by which to reduce time-sampling (default=10)
        :return:
        """

        divider_height = 1

        tmp_group = self.data['vm_all'].keys()[0]
        t_samples = len(self.data['vm_all'][tmp_group][0])
        samplepoints = np.arange(0, t_samples, dt_downsampling_factor)
        T = len(samplepoints)

        # print 'Experiment duration ' + str(self.defaultclock_dt*t_samples)
        # print 'Experiment sampling rate ' + str(self.defaultclock_dt)
        # print 'Downsampling by a factor of ' + str(dt_downsampling_factor)

        N_groups = len(self.default_group_numbering)

        group_start_ix = [0]*(N_groups+2)
        yticklocations = [0]*(N_groups+1)

        combined_neurons_vm = []

        # Run through groups to downsample and to select which neurons to show (if too many sampled)
        for i in np.arange(1, N_groups+1):
            group_name = self.default_group_numbering[i]
            # print 'Processing group ' + group_name + ', start index is ' + str(group_start_ix[i])

            group_neurons_vm = self.data['vm_all'][group_name]
            N_neurons_in_group = len(group_neurons_vm)
            # print '# of neurons sampled is ' + str(N_neurons_in_group)

            if N_neurons_in_group > max_per_group:
                N_neurons_in_group = max_per_group  # Ie. make N_neurons_in_group the amount of neurons to *sample*

            # print '# of neurons to show is ' + str(N_neurons_in_group)
            group_start_ix[i + 1] = group_start_ix[i] + N_neurons_in_group + divider_height
            yticklocations[i] = int((group_start_ix[i+1]-group_start_ix[i])/2 + group_start_ix[i])

            # Time-downsampling
            downsampled_neurons_vm = ['-']*N_neurons_in_group
            for n in range(0,N_neurons_in_group):
                downsampled_neurons_vm[n] = [group_neurons_vm[n][t] for t in samplepoints]

            # Add v_m series of N_neurons_in_group/max_per_group (randomly selected) neurons
            combined_neurons_vm.extend(downsampled_neurons_vm[0:N_neurons_in_group])  # Selection should be randomized

            # After the data, add const series (one or many) as a divider between groups
            divider = [[0] * T for k in range(0, divider_height)]
            combined_neurons_vm.extend(divider)



        # Plot a heatmap
        # Annoying labeling issue: sns.heatmap has indices increasing from top-left, matplotlib from bottom-left
        # That's why label locations are inversed (but not the whole y axis)
        # plt.style.use('seaborn-whitegrid')

        fig = plt.figure()
        fig.suptitle(self.datafile)
        ax = sns.heatmap(combined_neurons_vm, cmap=mycmap, vmin=-0.07, vmax=-0.04)

        ax.xaxis.set_major_locator(plt.MaxNLocator(10))
        ax.set_xticklabels([self.defaultclock_dt/ms*dt_downsampling_factor*i for i in range(0,11)])
        ax.set_xlabel('Time (ms)')

        y_limit = ax.get_ylim()[1]
        yticklocs = [y_limit - yticklocations[i] for i in range(1,N_groups+1)]

        ax.yaxis.set_major_locator(plt.FixedLocator(yticklocs))
        ax.yaxis.set_major_formatter(plt.FixedFormatter(self.default_group_numbering.values()))
        plt.yticks(rotation=0)


        # plt.yticks(yticklocations, self.group_numbering.values(), rotation=0) # TODO Fix tick locations
        #plt.yticks(group_start_ix[1:N_groups + 1], group_start_ix[1:N_groups + 1], rotation=0)


        plt.show()

    def conductanceplot(self, group_id):
        """
        Plots v_m and, in particular, g_e and g_i conductance fluctuations. For pyramidal cell groups also
        dendritic current is shown. On the (g_e, g_i) plot the 'AP threshold line' is drawn, representing the line
        where dv_m/dt at VT is 0 (>0 is a necessary condition for spiking).
        For motivation, see eg. Piwkowska et al. (2008). J Neurosci Met 169: 302-22.

        :param group_id: int, group identifier

        """
        group = self.default_group_numbering[group_id]
        # Pick random neuron from group (assuming neuron indexing inside vm_all, ge_soma_all, gi_soma_all is the same
        # ie. that neurons have been sampled with same density for each status monitor)
        neuron_ix = np.random.randint(len(self.data['vm_all'][group]))

        # Deal with time range here

        vm = self.data['vm_all'][group][neuron_ix]
        ge = self.data['ge_soma_all'][group][neuron_ix]
        gi = self.data['gi_soma_all'][group][neuron_ix]
        if self.default_group_to_type[group_id] == 'PC':
            Idendr = self.data['Idendr_soma_all'][group][neuron_ix]
            N_columns = 4
        else:
            N_columns = 3

        runtime = len(vm)*self.defaultclock_dt
        t = np.arange(0, runtime, self.defaultclock_dt)

        # Get spikes for cell HERE
        # spikes_t = self.data['spikes_all'][group][neuron_ix] doesn't work unfortunately
        # self.spikedata[0] -> indices, [1] -> spike times

        # TODO - spikedata have real indices, status monitors don't!!!

        spiking_neuron_ix = self.spikedata[group][0]
        spiking_neuron_t = self.spikedata[group][1]
        spikes_t = []

        for i in range(len(spiking_neuron_ix)):
            if spiking_neuron_ix[i] == neuron_ix: spikes_t.append(spiking_neuron_t[i]*1000*ms)  # Unit in saved data is second

        #C =
        #tau_m =
        gL = self._get_group_leak(group_id)
        Ee = 0*mV
        VT = -45*mV
        EL = -70*mV
        Ei = -75*mV

        ### PLOTTING BEGINS
        plt.subplots(1, N_columns)
        plt.suptitle(self.default_group_numbering[group_id])

        ### Membrane voltage plot
        plt.subplot(1, N_columns, 1)
        plt.title('$V_m$ with spikes')
        plt.plot(t / ms, vm*pow(10,3), c='blue')
        plt.plot(spikes_t/ms, [0 * mV] * len(spikes_t), '.')
        xlabel('Time (ms)')
        ylabel('$V_m$ (mV)')
        ylim([-75, 20])

        ### Conductance plot
        plt.subplot(1, N_columns, 2)
        plt.title('Conductance')
        plt.plot(t / ms, ge*pow(10,9), label='ge', c='green')
        plt.plot(t / ms, gi*pow(10,9), label='gi', c='red')
        xlabel('Time (ms)')
        ylabel('Conductance (nS)')
        # ylim([0, 50e-9])
        plt.legend()

        if self.default_group_to_type[group_id] == 'PC':
            plt.title('Dendritic current in soma')
            plt.subplot(1, N_columns, 3)
            plt.plot(t/ms, Idendr*pow(10,12), label='Idendr', c='blue')
            xlabel('Time (ms)')
            ylabel('Current (pA)')
            plt.legend()

            plt.subplot(1,N_columns,4)
        else:
            plt.subplot(1,N_columns,3)

        ### ge/gi plot with AP threshold line
        plt.title('Exc vs inh conductance')

        def gi_line(x): return (-x * (Ee - VT) - gL * (EL - VT)) / (Ei - VT)

        x_values = np.arange(0 * nS, 50 * nS, 1 * nS)
        plt.plot(x_values*pow(10,9), [gi_line(x)*pow(10,9) for x in x_values], label='$dV_m/dt = 0$')

        for spike_time in spikes_t/self.defaultclock_dt:
             plt.plot(ge[spike_time]*pow(10,9), gi[spike_time]*pow(10,9), 'g.')

        plt.plot(ge*pow(10,9), gi*pow(10,9), 'y.', alpha=0.02)
        plt.axis('equal')
        plt.xlabel('ge (nS)')
        plt.ylabel('gi (nS)')
        plt.legend()

        plt.show()

    def _currentplot_group(self, group_id, ax=None):
        """
        Plots excitatory and inhibitory currents of a given group. Mean of sampled neurons is shown in black and
        trace of a randomly picked neuron is shown in gray.

        :param group_id: int, group identifier
        :param ax: matplotlib Axes-object, optional

        """

        ### Basic parameters
        group = self.default_group_numbering[group_id]
        gL = self._get_group_leak(group_id)
        Ee = 0*mV
        VT = -45*mV
        EL = -70*mV
        Ei = -75*mV
        DeltaT = 2*mV

        ### Random neuron data
        # Pick random neuron from group (assuming neuron indexing inside vm_all, ge_soma_all, gi_soma_all is the same
        # ie. that neurons have been sampled with same density for each status monitor)
        neuron_ix = np.random.randint(len(self.data['vm_all'][group]))

        vm = self.data['vm_all'][group][neuron_ix]
        ge = self.data['ge_soma_all'][group][neuron_ix]
        gi = self.data['gi_soma_all'][group][neuron_ix]
        if self.default_group_to_type[group_id] == 'PC':
            Idendr = self.data['Idendr_soma_all'][group][neuron_ix]
        else:
            Idendr = [0.0]*len(vm)

        ### Mean of all sampled neurons
        vm_all = self.data['vm_all'][group]*volt
        ge_all = self.data['ge_soma_all'][group]*siemens
        gi_all = self.data['gi_soma_all'][group]*siemens
        exc_drive = Ee-vm_all
        inh_drive = Ei-vm_all
        exc_current_all = ge_all * exc_drive
        inh_current_all = gi_all * inh_drive
        _exc_current_mean = np.mean(exc_current_all, axis=0)
        _inh_current_mean = np.mean(inh_current_all, axis=0)

        if self.default_group_to_type[group_id] == 'PC':
            Idendr_mean = np.mean(self.data['Idendr_soma_all'][group], axis=0)*amp
        else:
            Idendr_mean = [0.0*amp]*len(vm)


        ### Plotting
        n_samples = len(vm)
        runtime = n_samples * self.defaultclock_dt
        plotting_density = 10
        t = np.arange(0, runtime, self.defaultclock_dt)

        exc_current = [ge[i]*siemens * (Ee-vm[i]*volt)+max(0,Idendr[i])*amp for i in np.arange(0, n_samples, plotting_density)]
        inh_current = [-(gi[i]*siemens * (Ei - vm[i]*volt) + min(0, Idendr[i])*amp) for i in np.arange(0, n_samples, plotting_density)]

        exc_current_mean = [_exc_current_mean[s] + max(0, Idendr_mean[s])
                            for s in np.arange(0, n_samples, plotting_density)]
        inh_current_mean = [(_inh_current_mean[s] + min(0, Idendr_mean[s]))*(-1)
                            for s in np.arange(0, n_samples, plotting_density)]

        thr_line = lambda x: x + gL*(EL-VT) + gL*DeltaT
        x_params = [0*pA, max(exc_current_mean)]

        if ax is None:
            plt.suptitle(self.default_group_numbering[group_id])
            plt.title('Mean E/I current (trace of E/I of a random neuron)')
            plt.plot(exc_current/pA, inh_current/pA, c='g', alpha=0.1)
            plt.plot(exc_current_mean/pA, inh_current_mean/pA, c='black', lw=1)
            plt.axis('equal')
            plt.xlabel('Excitatory current (pA)')
            plt.ylabel('Inhibitory current (pA)')
            plt.show()
        else:
            ax.plot(exc_current/pA, inh_current/pA, c='g', alpha=0.1)
            ax.plot(exc_current_mean/pA, inh_current_mean/pA, c='black', lw=1)
            plt.plot(x_params/pA, [thr_line(x)/pA for x in x_params], 'r-', lw=1)
            ax.axis('equal')
            ax.set_xlabel('Excitatory current (pA)')
            ax.set_ylabel('Inhibitory current (pA)')

    def currentplot(self):
        """
        Plots excitatory and inhibitory currents of all groups. See _currentplot_group() for details.

        """
        fig, ax = plt.subplots(4, 4)
        fig.suptitle(self.datafile)

        for group_id in range(1, 16 + 1):
            plt.subplot(4, 4, group_id)
            plt.title(self.default_group_numbering[group_id])
            self._currentplot_group(group_id, plt.gca())

        plt.show()

    def _interspikeintervals_group(self, group_id):
        """
        Computes the interspike intervals (ISIs) of the neurons in a given neuron group.

        :param group_id: int, group identifier
        :return:
            dict of unitless ISIs in milliseconds (indexed by neuron id's)
            indices of spiking neurons (with at least 2 spikes)
        """
        # Get the group spikes. Remember: [0]->indices, [1]->spike times
        spikes = self.spikedata[self.group_numbering[group_id]]

        # Get indices of the neurons that are spiking
        spiking_neurons = unique(spikes['i'])

        # Pick each neuron and go through the times it has spiked
        spikeintervals = dict()
        spiking_neurons_2 = []  # Those with at least 2 spikes
        for neuron in spiking_neurons:
            spike_idx = sort(where(spikes['i'] == neuron)[0])

            if len(spike_idx) >= 2:
                spikeintervals[neuron] = []
                spiking_neurons_2.append(neuron)
                # Begin counting from 2nd spike and for each step calculate the duration between jth - (j-1)th spike time
                for j in range(1, len(spike_idx)):
                    interval = (spikes['t'][spike_idx[j]] - spikes['t'][spike_idx[j-1]])/second * 1000  # x1000 s->ms
                    spikeintervals[neuron].append(interval)

        return spikeintervals, spiking_neurons_2

    def _isihistogram_group(self, group_id, ax=None):
        """
        Plots the histogram of interspike intervals of a given group.

        :param group_id: int, group identifier
        :param ax: matplotlib Axes-object (optional)

        """
        # Collection of spike times for each neuron in the group - let's just flatten it now
        spikeintervals, spiking_neurons = self._interspikeintervals_group(group_id)
        group_spikeintervals = []
        [group_spikeintervals.extend(spikeintervals[neuron]) for neuron in spiking_neurons]

        # Show a histogram of the interspike intervals (ISIs)
        if ax is None:
            plt.hist(group_spikeintervals, bins='auto')
            plt.xlabel('Time (ms)')
            plt.ylabel('Count')
            plt.show()
        else:
            ax.hist(group_spikeintervals, bins=40)

    def isi_hist(self):
        """
        Plots the histograms of interspike intervals of all neuron groups.

        """
        fig, ax = plt.subplots(4, 4)
        fig.suptitle(self.datafile)

        for group_id in range(1,16+1):
            plt.subplot(4, 4, group_id)
            plt.title(self.default_group_numbering[group_id])
            self._isihistogram_group(group_id, plt.gca())
            plt.xlabel('ISI (ms)')
            plt.ylabel('Count')

        plt.show()

    # Calculation of single-neuron coefficient of variation of interspike intervals, see eg. Sterratt book p209
    def _isi_cv_neuron(self, isi_list):
        """
        Computes the coefficient of variation (CV; sd/mean) of interspike intervals of a single neuron.
        CV of ISIs can be used as a measure of spiking regularity. For explanation, see eg.
        the book by Sterratt et al. (2009).

        :param isi_list: list of interspike intervals
        :return: float
        """
        return std(isi_list)/mean(isi_list)

    def _isi_cv_group(self, group_id, return_list=False):
        """
        Computes the coefficients of variation of ISIs of the neurons in a given neuron group.
        By default, returns the mean of the CVs, but can be changed to return the list of CVs.

        :param group_id: int, group identifier
        :param return_list: bool, change this to True if you want a list of CVs (default=False)
        :return: float (mean of CVs) or list of floats (list of CVs)
        """
        spikeintervals, spiking_neurons = self._interspikeintervals_group(group_id)

        neuron_cv_list = []
        for neuron in spiking_neurons:
            neuron_cv = self._isi_cv_neuron(spikeintervals[neuron])
            neuron_cv_list.append(neuron_cv)

        if return_list is False:
            return mean(neuron_cv_list)
        else:
            return neuron_cv_list

    def isicov(self):
        """
        Prints the means of CVs of ISIs of all groups to stdout.

        """
        for group_id in range(1,16+1):
            print self.default_group_numbering[group_id] + ', mean of 1-neuron CoV of ISIs (irregularity): ' + str(self._isi_cv_group(group_id))

    def _spikecounthistogram_group(self, group_id, bin_size=3 * ms, ax=None):
        """
        Creates a spike count histogram for a given group with certain bin size.
        If no Axes-object is given, Fano factor (variance/mean) of the spike count histogram is returned.
        Fano factor of the spike count histogram can be used to assess population synchrony,
        see Potjans T. & Diesmann M. (2014) Cer Cor 24 (3): 785-806.

        :param group_id: int, group identifier
        :param bin_size: millisecond, length of time-bin (default=3*ms)
        :param ax: matplotlib Axes-object (optional)
        :return: float, the Fano factor of given group (if no ax is given)
        """

        # Collect spike counts (of the group) into runtime divided by (time-)bin_size many bins
        timebin = bin_size/second
        spikes = self.data['spikes_all'][self.group_numbering[group_id]]
        n_bins = int(self.runtime/timebin)
        spike_counts, bin_edges = np.histogram(spikes['t'], bins=n_bins)
        # Spike count divided by bin size could be called the "population firing rate", but we don't really need that here

        # Count how many time-bins with each firing rate/spike count -> spike count histogram
        if ax is None:
            sp_mean = mean(spike_counts)
            sp_var = np.var(spike_counts)
            return sp_var/sp_mean
        else:
            ax.hist(spike_counts, bins='auto')


    def spikecount_hist(self):
        """
        Plots the spike count histogram of all groups

        """
        fig, ax = plt.subplots(4, 4)
        fig.suptitle(self.datafile)

        for group_id in range(1, 16 + 1):
            plt.subplot(4, 4, group_id)
            plt.title(self.default_group_numbering[group_id])
            self._spikecounthistogram_group(group_id, ax=plt.gca())
            plt.xlabel('Spike count')
            plt.ylabel('Frequency (timebins)')

        plt.show()


    def _firingrates_group(self, group_id, bin_size=3*ms):
        """
        Compute instantaneous firing rates of a given neuron group, "instantaneous" being defined by bin_size

        :param group_id: int, group identifier
        :param bin_size: millisecond, definition of "an instant" (default=3*ms)
        :return:
            list of firing rates (in spikes/s) corresponding to bins [t_0, t_1), [t_2, t_3), ..., [t_N-1, t_N]
            list of bin edges (length +1 compared to list of firing rates)
        """
        # Collect spike counts (of the group) into runtime divided by (time-)bin_size many bins
        timebin = bin_size/second
        spikes = self.data['spikes_all'][self.group_numbering[group_id]]
        n_bins = int(self.runtime/timebin)
        spike_counts, bin_edges = np.histogram(spikes['t'], bins=n_bins)

        # Count instantaneous firing rates in spikes/s
        group_firing_rates = [count/timebin for count in spike_counts]

        return group_firing_rates, bin_edges  # bin_edges is of length len(group_firing_rates)+1

    def firingrates_layer(self, layer_number):
        """
        Plots the instantaneous firing rates of neuron groups in a given layer. Each neuron group is plotted
        separately.

        :param layer_number: int, layer number (L2/3 denoted by 2)

        """
        flatten = lambda l: [item for sublist in l for item in sublist]
        groups = flatten(self.groups_of_layer[layer_number])

        bin_size = 3*ms
        plt.title('Layer ' + str(layer_number))
        plt.xlabel('Time (s)')
        plt.ylabel('Group firing rate (spikes/s)')
        for group_id in groups:
            firing_rates, bin_edges = self._firingrates_group(group_id, bin_size)
            plt.plot(bin_edges[:-1], firing_rates, label=self.default_group_numbering[group_id])

        plt.legend()
        plt.show()

    def _firingrates_ei_layer(self, layer_number, ax=None):
        """
        Plots the summed instantaneous firing rates of excitatory and inhibitory neuron groups in a given layer.

        :param layer_number: int, layer number (L2/3 denoted by 2)
        :param ax: matplotlib Axes-object

        """
        groups = self.groups_of_layer[layer_number]
        e_groups = groups[0]
        i_groups = groups[1]
        bin_size = 3*ms

        e_firing_rates = [self._firingrates_group(e_group, bin_size)[0] for e_group in e_groups]
        i_firing_rates = [self._firingrates_group(i_group, bin_size)[0] for i_group in i_groups]
        bin_edges = self._firingrates_group(1, bin_size)[1]

        e_rates_sum = np.sum(e_firing_rates, axis=0)
        i_rates_sum = np.sum(i_firing_rates, axis=0)

        if ax is None:
            plt.title('Layer '+ str(layer_number))
            plt.plot(bin_edges[:-1], e_rates_sum, label='Excitatory', c='g')
            plt.plot(bin_edges[:-1], i_rates_sum, label='Inhibitory', c='r')
            plt.xlabel('Time (s)')
            plt.ylabel('Population firing rate (spikes/s)')

            plt.legend()
            plt.show()

        else:
            ax.plot(bin_edges[:-1], e_rates_sum, label='Excitatory', c='g')
            ax.plot(bin_edges[:-1], i_rates_sum, label='Inhibitory', c='r')
            ax.legend()

    def global_osc_freq_autocorr(self):

        bin_size = 3*ms

        e_groups = []
        for layer in [1,2,4,5,6]:
            e_groups.extend(self.groups_of_layer[layer][0])

        e_firing_rates = [self._firingrates_group(e_group, bin_size)[0] for e_group in e_groups]
        e_rates_sum = np.sum(e_firing_rates, axis=0)

        corrs = np.correlate(e_rates_sum, e_rates_sum, mode='same')
        N = len(corrs)
        corrs = corrs[int(N/2):]

        lag = corrs[10:].argmax() + 10
        period = (bin_size/second)*lag
        osc_freq = 1/period

        return osc_freq

    def firingrates_ei(self):
        """
        Plots the summed firing rates of excitatory and inhibitory groups, subplot per layer

        """
        n_layers = len(self.layers)

        fig, ax = plt.subplots(n_layers, 1)
        fig.suptitle('E/I population firing rates (spikes/s)')

        for i in range(0, n_layers):
            plt.subplot(n_layers, 1, i+1)
            plt.title('Layer '+str(self.layers[i]))
            self._firingrates_ei_layer(self.layers[i], ax=plt.gca())

        plt.show()

    def _eiplot_layer(self, layer_number):
        """
        Plots the percentage of activity in excitatory and inhibitory populations as (E_activity, I_activity)
        for a given layer.

        :param layer_number: int, layer number (L2/3 denoted by 2)

        """
        groups = self.groups_of_layer[layer_number]
        e_groups = groups[0]
        i_groups = groups[1]
        bin_size = 3*ms  # Refractory time is 3ms so a single neuron can fire only once in time bin

        e_pop_size = np.sum([self.default_group_neuroncounts[e_group] for e_group in e_groups])
        i_pop_size = np.sum([self.default_group_neuroncounts[i_group] for i_group in i_groups])


        e_firing_counts = [self._firingrates_group(e_group, bin_size)[0] * bin_size for e_group in e_groups]
        i_firing_counts = [self._firingrates_group(i_group, bin_size)[0] * bin_size for i_group in i_groups]
        bin_edges = self._firingrates_group(1, bin_size)[1]

        e_counts_sum = np.sum(e_firing_counts, axis=0)
        i_counts_sum = np.sum(i_firing_counts, axis=0)

        e_activity = [100*e_t/e_pop_size for e_t in e_counts_sum]
        i_activity = [100*i_t/i_pop_size for i_t in i_counts_sum]

        plt.plot(e_activity, i_activity, '.')
        plt.xlabel('Excitatory population activity')
        plt.ylabel('Inhibitory population activity')

        # plt.legend()
        plt.show()

    def _pairwise_synchrony(self, sp1, sp2, bin_size=3*ms, time_to_drop=500*ms):

        timebin = bin_size / second
        custombins = np.arange(time_to_drop/second, self.runtime+timebin, timebin)
        sp1_counts = np.histogram(sp1, bins=custombins)[0]  # [0] has spike counts, [1] has bin edges (custombins)
        sp2_counts = np.histogram(sp2, bins=custombins)[0]

        sp_covmatrix = np.cov([sp1_counts, sp2_counts])
        cov12 = sp_covmatrix[0][1]  # covariance of sp1 and sp2; is equal to [1][0]
        var1 = sp_covmatrix[0][0]  # variance of sp1
        var2 = sp_covmatrix[1][1]  # variance of sp2

        return cov12/np.sqrt(var1*var2)

    def _spiketrains_nogroups(self, fill_nonspiking=False, time_to_drop=500*ms):
        spiketrains = []

        # Go through every group
        # for group, neurons_and_spikes in self.spikedata:
        for group in self.group_numbering.values():
            neurons_and_spikes = self.spikedata[group]
            neuron_ids = unique(neurons_and_spikes['i'])

            # Add each sampled spike train as a separate array
            for nid in neuron_ids:
                single_train = neurons_and_spikes['t'][np.where(neurons_and_spikes['i'] == nid)] / second
                if len(np.where(single_train > time_to_drop/second)[0]) > 0:  # ...if there is at least 1 spike after time_to_drop
                    spiketrains.append(single_train)

        if fill_nonspiking:
            n_neurons_total = sum(SimulationData.default_group_neuroncounts.values())
            n_nonspiking = n_neurons_total - len(spiketrains)
            spiketrains.extend([[]]*n_nonspiking)

        return spiketrains

    def mean_synchrony(self, n_neuronpairs=250, time_to_drop=500*ms):

        spiketrains_all = self._spiketrains_nogroups(time_to_drop=time_to_drop)
        np.random.shuffle(spiketrains_all)
        pairwise_coeffs = []

        # Pick two neurons
        # Calculate pairwise synchrony and add it to the list
        # Do this until n_neuronpairs have been picked
        if len(spiketrains_all) >= n_neuronpairs*2:
            for i in range(n_neuronpairs):
                coeff = self._pairwise_synchrony(spiketrains_all[2*i], spiketrains_all[2*i+1])
                pairwise_coeffs.append(coeff)

            # Then calculate mean of pairwise synchronies
            return mean(pairwise_coeffs)
        else:
            return 'NA'

    def _pop_measures_group(self, group_id, time_to_drop=500*ms):
        """
        Computes measures of activity for a given neuron group

        :param group_id: int, group identifier
        :param time_to_drop: millisecond, amount of time to drop from the beginning of the simulation (default=500*ms)
        :return:
            int, number of neurons spiking (at least two spikes during measurement)
            list of floats, mean firing rates of all those neurons
            list of floats, coefficients of variation of ISIs for all spiking neurons
            float, Fano factor of the given group
        """

        true_runtime = self.runtime * second - time_to_drop

        # Get spikes of the corresponding group with the beginning removed
        spikes = self.spikedata[self.group_numbering[group_id]]  # [0]->indices, [1]->times
        try:
            # We can do this because indexing is chronological
            true_begin_idx = min(where(spikes['t']/second > time_to_drop/second)[0])
        except ValueError:
            # If no spikes, then return an "empty" measures array
            return [0, [], [], -1]

        spikes_new = []
        spikes_new.append(spikes['i'][true_begin_idx:])
        spikes_new.append(spikes['t'][true_begin_idx:]/second)

        # Count how many neurons are spiking (at least 1 spike)
        spiking_neurons = unique(spikes_new[0])
        n_spiking = len(spiking_neurons)

        # For every neuron with at least 2 spikes, calculate ISIs & mean firing rates.
        mean_firing_rates = []
        isicovs = []

        for neuron in spiking_neurons:
            spike_idx = sort(where(spikes_new[0] == neuron)[0])

            if len(spike_idx) >= 2:
                spikeintervals = []

                # Begin counting from 2nd spike and
                # for each step calculate the duration between jth - (j-1)th spike time
                for j in range(1, len(spike_idx)):
                    interval = (spikes_new[1][spike_idx[j]] - spikes_new[1][spike_idx[j-1]]) * second
                    spikeintervals.append(interval)

                # Calculate coefficient of variation for these neurons (and mean firing rates)
                isicovs.append(std(spikeintervals)/mean(spikeintervals))
                mean_firing_rates.append((len(spikeintervals)+1)/true_runtime)

        # Still, make spikecount histogram and calculate pop synchrony measure
        fanofactor = self._spikecounthistogram_group(group_id)

        return n_spiking, mean_firing_rates, isicovs, fanofactor

    def pop_measures(self, time_to_drop=500*ms):
        """
        Computes measures of activity for all neuron groups. See _pop_measures_group() for details.

        :param time_to_drop: millisecond, amount of time to drop from the beginning of the simulation (default=500*ms)
        :return: four dictionaries in the same order as in _pop_measures_group(), all indexed by group identifiers

        """
        n_spiking = dict()
        mean_firing_rates = dict()
        isicovs = dict()
        fanofactors = dict()

        for group_id in self.group_numbering.keys():
            n_spiking_gp, mean_firing_rates_gp, isicovs_gp, fanofactor_gp = self._pop_measures_group(group_id, time_to_drop)
            n_spiking[group_id] = n_spiking_gp
            mean_firing_rates[group_id] = mean_firing_rates_gp
            isicovs[group_id] = isicovs_gp
            fanofactors[group_id] = fanofactor_gp

        return n_spiking, mean_firing_rates, isicovs, fanofactors

    def import_ax(self, ax):
        self.ax = ax
        self.theplot, = ax.plot([], [], '.')

    def animate(self, i):
        t_res = 1*ms
        self.show_spikes_at_t(7, i*t_res)

    def show_spikes_at_t(self, group_id, t):

        t_abs = t/second
        t_res = 0.001  # 0.001 seems ok

        # group_name = self.group_numbering[group_id]
        group_name = 'NG0_relay_spikes'
        w_coord = self.data['positions_all']['w_coord'][group_name]
        spikes_i = self.data['spikes_all'][group_name]['i'].astype(int)
        spikes_t = self.data['spikes_all'][group_name]['t']

        who_are_spiking = np.unique(spikes_i[np.where(abs(spikes_t - t_abs) < t_res)])
        spikers_coord = np.array([w_coord[i] for i in who_are_spiking])

        # print who_are_spiking
        self.ax.set_title('Time ' + str(t), fontsize=18)

        self.theplot.set_data(spikers_coord.real, spikers_coord.imag)


class ExperimentData(object):
    """
    Class for managing and analysing data from multiple simulations (such as an experiment).

    """
    def __init__(self, experiment_path, experiment_name):
        """
        :param experiment_path: str, path to simulation files (with trailing /)
        :param experiment_name: str, identifier of the experiment, ie. string for identifying relevant simulation files
        """
        self.experiment_path = experiment_path
        self.experiment_name = experiment_name
        self.simulation_files = [sim_file for sim_file in os.listdir(experiment_path)
                                 if experiment_name in sim_file and os.path.splitext(sim_file)[1] == '.bz2']
        self.simulation_files.sort()

    def _computestats_single_sim(self, sim_file, settings=None, parameters_to_extract=[]):
        """
        Computes activity measures for a single simulation and based on given cutoff values returns frequency of
        eg. neurons firing 'irregularly' or with 'normal' firing rate. Also parameters can be extracted
        from configuration files.

        :param sim_file: str, the simulation file to examine
        :param settings: dict, analysis settings such as cutoff values for 'normalcy'
        :param parameters_to_extract: list, parameters whose values should be extracted from configurations
        :return: pandas DataFrame with sim_file as index
        """
        if settings is None:
            settings = {'time_to_drop': 500*ms, 'rate_min': 0*Hz, 'rate_max': 30*Hz, 'isicov_min': 0.5,
                        'isicov_max': 1.5, 'fanofactor_max': 10, 'active_group_min': 0.2, 'dec_places': 14}

        # OPEN simulation results file
        sim = SimulationData(sim_file, data_path=self.experiment_path)

        # BUILD DATAFRAME for collecting everything
        group_measures = ['p_' + group_name for group_name in sim.group_numbering.values()]
        group_measures.extend(['mfr_' + group_name for group_name in sim.group_numbering.values()])
        stats_to_compute = ['duration', 'n_spiking', 'p_spiking', 'n_firing_rate_normal', 'p_firing_rate_normal',
                            'n_irregular', 'p_irregular', 'irregularity_mean', 'n_groups_active',
                            'n_groups_asynchronous', 'n_groups_synchronous', 'mean_synchrony', 'mfr_all',
                            'mfr_spiking', 'osc_freq_ft', 'osc_freq_ac']
        stats = pd.DataFrame(index=[sim_file], columns=parameters_to_extract + stats_to_compute + group_measures)

        # Helper function
        flatten = lambda l: [item for sublist in l for item in sublist]


        try:

            # EXTRACT specified simulation parameters
            duration = (sim.runtime * second - settings['time_to_drop']) / second
            extracted_params = []
            for param_name in parameters_to_extract:
                param_value = sim.get_sim_parameter(param_name)
                try:
                    param_value = round(array([param_value])[0], settings['dec_places'])  # Get rid of unit
                except TypeError:
                    pass

                extracted_params.append(param_value)

            # COMPUTE population measures
            n_spiking, mean_firing_rates, isicovs, fanofactors = sim.pop_measures(settings['time_to_drop'])
            n_spiking_total = sum(n_spiking.values())
            osc_freq_ft = sim.global_osc_freq(t_limits=[settings['time_to_drop'], -1])
            osc_freq_ac = 0 #sim.global_osc_freq_autocorr()

            # TRANSFORM results into a readable form

            # -> Group activities (= n_spiking/n_total)
            group_activities = []
            for group_id in sim.group_numbering.keys():
                activity = round(n_spiking[group_id] / sim.group_neuroncounts[group_id], settings['dec_places'])
                group_activities.append(activity)

            # -> Firing rates
            group_firing_rates = []
            for group_id in sim.group_numbering.keys():
                with np.errstate(divide='raise'):
                    try:
                        firing_rate = round(mean(mean_firing_rates[group_id]), settings['dec_places'])
                    except:
                        firing_rate = 0
                group_firing_rates.append(firing_rate)

            n_firing_rate_normal = len([rate for rate in flatten(mean_firing_rates.values())
                                        if settings['rate_min'] < rate < settings['rate_max']])
            n_firing_rate_normal = np.int32(n_firing_rate_normal)

            neuron_count = sum(sim.group_neuroncounts.values())
            try:
                rates_sum = sum(rate for rate in flatten(mean_firing_rates.values()))
            except:
                rates_sum = 0

            mfr_all = round(rates_sum / neuron_count, settings['dec_places'])
            isicovs_flat = flatten(isicovs.values())
            n_atleast_twospikes = len(isicovs_flat)
            if n_atleast_twospikes > 0:
                mfr_spiking = round(rates_sum / n_atleast_twospikes, settings['dec_places'])
            else:
                mfr_spiking = 'NA'

            # -> Irregularity
            n_irregular = len([isicov for isicov in isicovs_flat
                               if settings['isicov_min'] < isicov < settings['isicov_max']])
            n_irregular = np.int32(n_irregular)
            try:
                irregularity_mean = round(mean(isicovs_flat), settings['dec_places'])
            except:
                irregularity_mean = 'NA'

            # -> Synchrony
            # Calculating the synchrony measure makes sense only if the group is active enough
            # So, first calculate n_groups_active and count asynchronous groups from those
            active_groups = [group_id for group_id, ng_spiking in n_spiking.items()
                             if ng_spiking / sim.group_neuroncounts[group_id] > settings['active_group_min']]
            n_groups_active = len(active_groups)
            n_groups_asynchronous = len([group_id for group_id, fanofactor in fanofactors.items()
                                         if 0 < fanofactor < settings['fanofactor_max'] and group_id in active_groups])
            n_groups_synchronous = n_groups_active - n_groups_asynchronous

            mean_synchrony = sim.mean_synchrony(time_to_drop=settings['time_to_drop'])

            # Finally, transform numbers into frequencies
            n_total_neurons = sum(sim.group_neuroncounts.values())
            p_spiking = round(n_spiking_total / n_total_neurons, settings['dec_places'])
            if n_spiking_total > 0:
                p_firing_rate_normal = round(n_firing_rate_normal / n_spiking_total, settings['dec_places'])
                p_irregular = round(n_irregular / n_spiking_total, settings['dec_places'])
            else:
                p_firing_rate_normal = ''
                p_irregular = ''

            # COMPILE DATAFRAME
            stats.loc[sim_file] = extracted_params + \
                                        [duration, n_spiking_total, p_spiking, n_firing_rate_normal, p_firing_rate_normal,
                                         n_irregular, p_irregular, irregularity_mean, n_groups_active, n_groups_asynchronous,
                                         n_groups_synchronous, mean_synchrony, mfr_all, mfr_spiking, osc_freq_ft, osc_freq_ac] + \
                                         group_activities + group_firing_rates
            return stats

        except KeyError:
            pass

    def computestats(self, output_filename='stats.csv', parameters_to_extract=[], settings=None):
        """
        Computes activity measures of all simulations belonging to the experiment and
        aggregates it to a single CSV file. Computation is done in parallel fashion.

        :param output_filename: filename of the resulting csv file in experiment path (default=stats.csv)
        :param parameters_to_extract: parameters to extract from configurations (default=[])
        :param settings: dict, analysis settings such as cutoff values for 'normalcy'
        :return: nothing (csv file is created automatically)
        """

        # Set default analysis parameters here
        if settings is None:
            settings = {'time_to_drop': 500*ms, 'rate_min': 0*Hz, 'rate_max': 30*Hz, 'isicov_min': 0.5,
                        'isicov_max': 1.5, 'fanofactor_max': 10, 'active_group_min': 0.2, 'dec_places': 14}

        # Go through simulation files
        n_files = len(self.simulation_files)
        print 'Beginning analysis of ' + str(n_files) + ' files'

        # Takes forever unless parallel-processed
        pool = mp.ProcessingPool(processes=int(mp.cpu_count()*0.75))
        results = []

        with tqdm(total=n_files, desc='Analysing simulations') as progress:
            for res in pool.uimap(self._computestats_single_sim, self.simulation_files,
                                  [settings for i in range(n_files)], [parameters_to_extract for i in range(n_files)]):
                results.append(res)
                progress.update()

        progress.close()
        pool.close()
        pool.join()

        try:
            stats = pd.concat(list(results))
            stats.to_csv(self.experiment_path + output_filename)
        except:
            print 'Nothing to analyse!'

    # TODO :: Function for automatic plotting of synchrony, irregularity & mean firing rate

    def rasterplot(self, n, sampling_factor=30, time_limits=None, ax=None):
        """
        Plots the n-th simulation of the experiment (as indexed in simulation_files)

        :param n:
        :return:
        """

        sim = SimulationData(self.simulation_files[n], data_path=self.experiment_path)
        sim.publicationplot(sampling_factor=sampling_factor, time_limits=time_limits, ax=ax)


class ExperimentStats(object):

    def __init__(self, csv_file_path):

        self.csv_file_path = csv_file_path
        self.stats = pd.read_csv(self.csv_file_path)

    def plot_ratesyncfano(self, y_var='background_rate', x_var='k', mfr_max=15, sync_max=0.05, irreg_max=1.0, plot_save_path=None):

        sns.set_style('whitegrid')
        plt.subplots(3,1)

        plt.subplot(311)
        a = self.stats.pivot_table('mfr_all', index=y_var, columns=x_var).sort_index(ascending=False)
        sns.heatmap(a, cmap=mycmap, vmin=0, vmax=mfr_max)
        plt.title('Mean firing rate')
        ax = plt.gca()
        ax.set_aspect('equal')

        plt.subplot(312)
        b = self.stats.pivot_table('mean_synchrony', index=y_var, columns=x_var).sort_index(ascending=False)
        sns.heatmap(b, cmap=mycmap, vmin=0, vmax=sync_max)
        plt.title('Synchrony')
        ax = plt.gca()
        ax.set_aspect('equal')

        plt.subplot(313)
        c = self.stats.pivot_table('irregularity_mean', index=y_var, columns=x_var).sort_index(ascending=False)
        sns.heatmap(c, cmap=mycmap, vmin=0, vmax=irreg_max)
        plt.title('Irregularity')
        ax = plt.gca()
        ax.set_aspect('equal')


        # plt.tight_layout()

        if plot_save_path is None:
            plt.show()
        else:
            plt.savefig(plot_save_path)



def calciumplot(sim_files, sim_titles, runtime, neurons_per_group=20, suptitle='Effect of increased $Ca^{2+}$ concentration (mM)'):
    """
    Plots simplified rasterplots of simulations next to each other. For publications.

    :param sim_files: list of filenames, simulation files to include
    :param sim_titles: list of strings, titles to show on top of each rasterplot
    :param runtime: float, runtime in seconds
    :param neurons_per_group: int, number of neurons per group to include (if less group will be discarded, if more a random selection will be made)
    :param suptitle: str, title for the whole figure

    """
    sim_n = len(sim_files)
    q = neurons_per_group

    ticklabels = ['VI', 'V', 'IV', 'II/III', 'I']
    w, h = matplotlib.figure.figaspect(1 / sim_n)
    fig, ax = plt.subplots(ncols=sim_n, figsize=(w, h), dpi=600)
    #plt.style.use('seaborn-whitegrid')


    fig.suptitle(suptitle, fontsize=16)
    fig.subplots_adjust(top=0.85, bottom=0.1, left=0.03, right=0.97)
    plt.setp(ax, xticks=np.arange(runtime + 0.1, step=1),
             yticks=[4 * q, 7 * q, 12 * q, 15 * q, 16 * q], yticklabels=ticklabels, xlim=[0, runtime],
             ylim=[0, 16 * q],
             xlabel='Time (s)')

    [SimulationData(sim_files[i]).rasterplot_compressed(40, ax[i]) for i in range(sim_n)]
    [ax[i].set_title(sim_titles[i]) for i in range(sim_n)]

    plt.tight_layout()
    fig.subplots_adjust(top=0.80, bottom=0.20, left=0.03, right=0.97)
    # plt.savefig('calciumplot.eps', dpi=600)
    # #plt.savefig('calciumplot.png')
    plt.show()


def combined_metrics_plot():
    """
    For plotting mean firing rate, degree of synchrony & degree of irregularity for a set of simulations

    :return:
    """
    ####### For figure 3 in the paper ######
    stats = pd.read_csv('/opt3/tmp/kumar/stats_elijah_figs.csv')
    stats = stats[stats.k < 3.5]
    mfr_pivot = stats.pivot_table('mfr_all', index='k', columns='background_rate').T.sort_index(ascending=False)
    sync_pivot = stats.pivot_table('mean_synchrony', index='k', columns='background_rate').T.sort_index(ascending=False)
    irreg_pivot = stats.pivot_table('irregularity_mean', index='k', columns='background_rate').T.sort_index(ascending=False)

    fig = plt.figure()
    plt.style.use('seaborn-whitegrid')

    ### LEFT PANEL
    axa = fig.add_subplot(321)
    g0 = sns.heatmap(mfr_pivot, vmin=0, vmax=15, ax=axa, cmap='binary',
                     xticklabels=False, yticklabels=2, cbar_kws={"ticks":[0,15]})
    axa.set_aspect(1)
    g0.set_title('Mean firing rate', fontsize=16, fontweight='bold')
    g0.set_ylabel('Background rate [Hz]', fontsize=12, fontweight='bold')
    plt.setp(g0.get_yticklabels(), rotation=0)
    g0.set_xlabel('')
    g0.collections[0].colorbar.set_label('spikes/s')

    axb = fig.add_subplot(323)
    g1 = sns.heatmap(sync_pivot, vmin=0, vmax=0.05, ax=axb, cmap='binary',
                     xticklabels=False, yticklabels=2, cbar_kws={"ticks":[0,0.05]})
    axb.set_aspect(1)
    g1.set_title('Synchrony', fontsize=16, fontweight='bold')
    g1.set_ylabel('Background rate [Hz]', fontsize=12, fontweight='bold')
    plt.setp(g1.get_yticklabels(), rotation=0)
    g1.set_xlabel('')

    axc = fig.add_subplot(325)
    g2 = sns.heatmap(irreg_pivot, vmin=0, vmax=1.0, ax=axc, cmap='binary',
                     xticklabels=2, yticklabels=2, cbar_kws={"ticks":[0,1]})
    axc.set_aspect(1)
    g2.set_title('Irregularity', fontsize=16, fontweight='bold')
    g2.set_ylabel('Background rate [Hz]', fontsize=12, fontweight='bold')
    plt.setp(g2.get_yticklabels(), rotation=0)
    g2.set_xlabel('Relative strength of inhibition [1]', fontsize=12, fontweight='bold')

    ### RIGHT PANEL

    axd = fig.add_subplot(324)
    sim_highca = SimulationData('kumar/cecilia_20170803_21521493_background_rate0.6H_k0.3_Cpp_3500ms.bz2')
    sim_highca.publicationplot(ax=axd, time_limits=[1,3])
    axd.set_title('High calcium', fontsize=16, fontweight='bold')

    axf = fig.add_subplot(326)
    sim_lowca = SimulationData('kumar/delia_20170808_10072677_background_rate0.6H_k0.3_Cpp_3500ms.bz2')
    sim_lowca.publicationplot(ax=axf, time_limits=[1,3])
    axf.set_title('Low calcium', fontsize=16, fontweight='bold')

    # fig.subplots_adjust(top=0.90, bottom=0.10, left=0.10, right=0.90)

    plt.tight_layout(pad=1)
    plt.show()




# MAIN
if __name__ == '__main__':


    # a = SimulationData('/opt3/tmp/rev2_test/betaconfig_test_20180919_17183215_background_rate0.2H_k0.2_python_5000ms.bz2')
    #a = SimulationData('/opt3/tmp/rev2_test/betaconfig_test2_20180919_19332474_background_rate0.6H_k1.4_python_5000ms.bz2')
    #a.publicationplot()

    exp = ExperimentData('/opt3/tmp/rev2_gamma/', 'step2_lowcalcium2_dep100_eifstp_gabab_Jeigeneric')
    exp.computestats('stats_step2_lowcalcium2_dep100_eifstp_gabab_Jeigeneric.csv', ['calcium_concentration', 'J', 'k', 'background_rate'])


    ###### Depol x calcium plot ######
    # exp = ExperimentData('/opt3/tmp/bigrun/depolxcalcium/', 'fepol')
    # time_limits = [1,3]
    #
    # fig = plt.figure()
    # plt.style.use('seaborn-whitegrid')
    #
    # axes = []
    # n_rows = 5
    # n_cols = 6
    # for row in range(1, n_rows+1):
    #     for col in range(1, n_cols+1):
    #         subplot_index = (row-1) * n_cols + col
    #         axes.append(fig.add_subplot(n_rows, n_cols, subplot_index))
    #         exp.rasterplot(subplot_index-1, sampling_factor=100, time_limits=time_limits, ax=axes[subplot_index-1])
    #
    # plt.show()

    ###### For analysing a set of runs ######
    # Seeing results in iPython for example:
    #  plt.figure(); a = data.pivot_table('irregularity_mean', index='background_rate', columns='k').sort_index(ascending=False); sns.heatmap(a, cmap='binary', vmax=1)

    # exp = ExperimentData('/opt3/tmp/modvartests2/', 'eifstp_excweights_pcinhsimple_40nmda_20gabab_17tauealpha')
    # custom_settings = {'time_to_drop': 0 * ms, 'rate_min': 0 * Hz, 'rate_max': 30 * Hz, 'isicov_min': 0.5,
    #             'isicov_max': 1.5, 'fanofactor_max': 10, 'active_group_min': 0.2, 'dec_places': 14}
    # exp.computestats('stats_eifstp_excweights_pcinhsimple_40nmda_20gabab_17tauealpha_taito.csv',
    #                 ['pc_inhibition_model', 'calcium_concentration', 'J', 'J_I', 'background_rate'])

    # ExperimentStats('/opt3/tmp/modvartests2/stats_eifstp_110depol_20gabab_40nmda_17tauealpha_pcinhalpha_taito.csv').plot_ratesyncfano(mfr_max=2)

    ###### For creating side-by-side rasterplots ######
    # simulations = ['depol_37_calcium_concentration1.0_Cpp_3000ms.bz2', 'depol_37_calcium_concentration1.4_Cpp_3000ms.bz2',
    #                'depol_37_calcium_concentration2.0_Cpp_3000ms.bz2']
    # sim_title = ['1.0', '1.4', '2.0']
    #
    # calciumplot(sim_files=simulations, sim_titles=sim_title, neurons_per_group=40, runtime=3.0)

    ### Animating data
    # simfile = 'corem_tests/oblique_grating_20171108_16512817_Python_1500ms.bz2'
    # a = SimulationData(simfile)
    #
    # fig,ax = plt.subplots()
    # plt.xlim([25,35])
    # plt.ylim([-3,3])
    # ax.scatter([],[])
    #
    # a.import_ax(ax)
    #
    # anim = FuncAnimation(fig, a.animate, frames=np.arange(1000), interval=40)
    #
    # # print a.show_spikes_at_t(ax,7, 0.0063*second)
    # plt.show()

    # a = SimulationData('/opt3/tmp/coba/01_testrun_20180216_11294826_k11.16_python_2000ms.bz2',
    #                    group_numbering={1: 'NG1_SS_L4', 2: 'NG2_BC_L4'}, group_neuroncounts={1: 3200, 2: 800},
    #                    group_to_type={1: 'SS', 2: 'BC'})
    # a.publicationplot(plot_type=1, sampling_factor=1, time_rounding=5)
