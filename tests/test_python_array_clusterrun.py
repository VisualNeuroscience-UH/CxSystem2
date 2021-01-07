import os
import sys

import pytest

[sys.path.append(i) for i in ['.', '..']]
from cxsystem2.core import cxsystem as cx, equation_templates as eqt
import cxsystem2.hpc.cluster_run as cluster
import numpy as np
from brian2.units import *
import brian2
import zlib
import pickle
import shutil
from scipy.stats import ks_2samp, wasserstein_distance
from pathlib import Path

'''
To use this test you need to pip install -U pytest. 
Note that the -U will upgrade necessary dependencies for pytest.

Run pytest at CxSystem root, such as git repo root. This 
file will test the cluster run.

Vafa Andalibi, Simo Vanni 2019
'''

cwd = os.getcwd()
path = Path(cwd)
anatomy_and_system_config = path.joinpath('tests', 'config_files', 'pytest_Anatomy_config_cluster.csv').as_posix()
physiology_config = path.joinpath('tests', 'config_files', 'pytest_Physiology_config_cluster.csv').as_posix()
CM = cx.CxSystem(anatomy_and_system_config, physiology_config)
workspace_folder = CM.workspace.get_workspace_folder()
simulation_folder = CM.workspace.get_simulation_folder()
simulation_suffix = CM.workspace.suffix
cluster_simulation_path = Path(workspace_folder.joinpath('cluster_run'+simulation_suffix))
cluster_download_path = cluster_simulation_path.joinpath('downloads')
cluster_metadata_path = cluster_simulation_path.joinpath('cluster_metadata{}.pkl'.format(simulation_suffix))


@pytest.fixture(scope='module')
def cxsystem_run_fixture3():
    # Executing setup code
    cluster.ClusterDownloader(cluster_metadata_path.as_posix(),clean_remote=True)

    yield  # Run the tests here

    # Executing teardown code
    shutil.rmtree(simulation_folder.as_posix())
    shutil.rmtree(cluster_simulation_path.as_posix())


@pytest.fixture(scope='module')
def get_spike_data():
    output_fullpath = path.joinpath('tests', 'output_files', 'pytest_spike_reference_data_200ms.gz')
    with open(output_fullpath.as_posix(), 'rb') as fb:
        d_pickle = zlib.decompress(fb.read())
        data = pickle.loads(d_pickle)
        spikes_all = data['spikes_all']

    new_output_name = [item for item in os.listdir(cluster_download_path.as_posix()) if 'tonic_depol_level155' in item and '_results_' in item]
    new_output_fullpath = cluster_download_path.joinpath(new_output_name[0])
    with open(new_output_fullpath, 'rb') as fb:
        new_d_pickle = zlib.decompress(fb.read())
        new_data = pickle.loads(new_d_pickle)
        new_spikes_all = new_data['spikes_all']

    return spikes_all, new_spikes_all


# @pytest.mark.skip(reason="too slow")
def test_outputfile(cxsystem_run_fixture3):
    '''Test for 5 existing outputfiles'''
    print("download path: " , cluster_download_path)
    outputfilelist = [item for item in os.listdir(cluster_download_path.as_posix()) if 'tonic_depol_level' in item]
    assert len([item for item in outputfilelist if os.access(cluster_download_path.joinpath(item), os.W_OK)]) == 6

    metafiles = [item for item in os.listdir(cluster_download_path.as_posix()) if 'metadata_' in item]
    assert len([item for item in metafiles if os.access(cluster_download_path.joinpath(item), os.W_OK)]) == 2

# @pytest.mark.xfail(reason='not identical spikes')
def test_spikecount_10percent_tolerance(cxsystem_run_fixture3,
                                        capsys,
                                        get_spike_data):
    spikes_all, new_spikes_all = get_spike_data
    keys = list(spikes_all.keys())  # dict_keys is not indexable directly
    for key in keys:
        spike_count_proportion = new_spikes_all[key]['N'] / spikes_all[key]['N']
        assert 0.9 <= spike_count_proportion <= 1.1


def test_spikecount_report(cxsystem_run_fixture3,
                           capsys,
                           get_spike_data):
    spikes_all, new_spikes_all = get_spike_data
    keys = list(spikes_all.keys())  # dict_keys is not indexable directly
    with capsys.disabled():
        print('\n')
    for key in keys:
        spike_count_proportion = new_spikes_all[key]['N'] / spikes_all[key]['N']
        with capsys.disabled():
            print('Proportion of spike counts (new/old) for {0} is {1:.2f}'.format(key, spike_count_proportion))
    # assert spike_count_proportion == 1.0


def test_spiketiming_report(cxsystem_run_fixture3,
                            capsys,
                            get_spike_data):
    spikes_all, new_spikes_all = get_spike_data
    keys = list(spikes_all.keys())  # dict_keys is not indexable directly

    time_resolution = 0.1 * msecond
    #	run_time = CM.runtime
    #	time_vector_length = run_time / time_resolution

    time_vector_length = 2000

    with capsys.disabled():
        print('\n')

    for key in keys:

        new_spikes_all[key]['N']
        spikes_all[key]['N']

        # find union of firing neurons in the two sets
        all_spiking_neurons = np.union1d(spikes_all[key]['i'], new_spikes_all[key]['i'])

        # create time vectors of zeros and ones for all neurons and both datasets
        spikes_index_time_matrix = np.zeros([max(all_spiking_neurons) + 1, int(time_vector_length)])  # +1 because indexing starts at 0
        spikes_time_indeces_float = spikes_all[key]['t'] / time_resolution
        spikes_index_time_matrix[spikes_all[key]['i'], spikes_time_indeces_float.astype(int)] = 1
        spikes_index_time_matrix = spikes_index_time_matrix[all_spiking_neurons, :]

        new_spikes_index_time_matrix = np.zeros([max(all_spiking_neurons) + 1, int(time_vector_length)])
        new_spikes_time_indeces_float = new_spikes_all[key]['t'] / time_resolution
        new_spikes_index_time_matrix[new_spikes_all[key]['i'], new_spikes_time_indeces_float.astype(int)] = 1
        new_spikes_index_time_matrix = new_spikes_index_time_matrix[all_spiking_neurons, :]

        cumulative_ks = 0
        cumulative_wd = 0
        for idx, neuron_idx in enumerate(all_spiking_neurons):
            spike_data = np.nonzero(spikes_index_time_matrix[idx, :])[0]
            new_spike_data = np.nonzero(new_spikes_index_time_matrix[idx, :])[0]

            ksstat = ks_2samp(spike_data, new_spike_data)
            wass_dist = wasserstein_distance(spike_data, new_spike_data)

            cumulative_ks += ksstat[0]
            cumulative_wd += wass_dist

        mean_ks = cumulative_ks / len(all_spiking_neurons)
        mean_wd = (time_resolution / msecond) * cumulative_wd / len(all_spiking_neurons)

        # report mean of these stats
        with capsys.disabled():
            # print('Mean KS statistics for {0} is {1:.2f}'.format(key,mean_ks)) # Quantified spiketiming similarity
            print('Mean Wasserstein Distance (spike shift) for {0} is {1:.2f} ms'.format(key, mean_wd))  # Quantified spiketiming similarity
