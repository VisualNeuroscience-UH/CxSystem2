import os
import sys

import pytest

[sys.path.append(i) for i in ['.', '..']]
from cxsystem2.core import cxsystem as cx, equation_templates as eqt
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

Run pytest at CxSystem root, such as git repo root.

Simo Vanni 2019
'''

cwd = os.getcwd()
path = Path(os.getcwd())
anatomy_and_system_config = path.joinpath('tests', 'config_files', 'pytest_Anatomy_config.csv').as_posix()
physiology_config = path.joinpath('tests', 'config_files', 'pytest_Physiology_config.csv').as_posix()
CM = cx.CxSystem(anatomy_and_system_config, physiology_config)
workspace_folder = CM.workspace.get_workspace_folder()
simulation_folder = CM.workspace.get_simulation_folder()

def test_cwd():
	assert "cxsystem2" in os.listdir(os.getcwd())

def test_anatomy_and_system_config_file_exist():
	assert os.path.isfile(anatomy_and_system_config)
	
def test_physiology_config_file_exist():
	assert os.path.isfile(physiology_config)
	
def test_dataframe_delimiters():
	# Comma is the delimiter in csv and should not remain in dataframe
	assert not ',' in CM.anat_and_sys_conf_df.to_string() 
	# Windows local settings may save csv with semicolons
	assert not ';' in CM.anat_and_sys_conf_df.to_string() 
		
class TestInit:
	# @pytest.mark.xfail()
	def test_csv_shape(self):
		assert CM.anat_and_sys_conf_df.shape[1] == 27

	def test_number_of_input_arguments(self):
		assert CM.__init__.__code__.co_argcount == 9 , "Number of arguments have changed"
		
	# def test_local_variable_names(self):
	# 	assert CM.__init__.__code__.co_varnames == \
	# 	('self', 'anatomy_and_system_config', 'physiology_config', 'output_file_suffix', 'instantiated_from_array_run',
	# 	 'cluster_run_start_idx', 'cluster_run_step', 'array_run_in_cluster', 'array_run_stdout_file', 'now', 'params_indices', 'row_idx',
	# 	 'number_of_new_columns', 'existing_rows', 'new_columns', 'empty_dataframe',
	# 	 'new_anat_and_sys_conf_df', 'row', 'check_array_run_anatomy', 'check_array_run_physiology',
	# 	 'trials_per_config', 'suffix', 'tmp_folder_path', 'tmp_anat_path', 'tmp_physio_path', 'array_run_path',
	# 	 'cluster_flag', 'array_run_suffix', 'tmp_anat_path2', 'f', 'tmp_physio_path2', 'command', 'shell', 'tmp_cluster')
		
	def test_input_argument_types(self):
		assert isinstance(CM.timestamp, str) 
		assert isinstance(CM.array_run, int), "Indirect test for input arg instantiated_from_array_run"
		assert isinstance(CM.cluster_run_start_idx, int) 
		assert isinstance(CM.cluster_run_step, int) 
		assert isinstance(CM.array_run_in_cluster, int) 
		
class TestConfigurationExecutor:

	# @pytest.mark.xfail(reason='changes in csv file cause this to fail')
	def test_definition_lines_idx(self):
		'''Test that indeces are the same given the constant configuration file.
			If you add/remove items in the conf file, this is expected to fail.'''
		assert all(CM.anat_and_sys_conf_df.loc[:,0][CM.anat_and_sys_conf_df.loc[:,0]=='row_type'].index \
				== np.array([0, 2, 5, 12]))
	
	def test_set_runtime_parameters(self):
		'''Note, cpp and GeNN devices are not tested '''
		assert CM.runtime == 200. * msecond
		assert CM.device.lower() == 'python'
		assert CM.sys_mode == 'local'
		
	def test_relay(self):
		''' This is expected to fail if corresponding parameters in the 
			configuration file changes'''
		assert len(CM.customized_neurons_list) == 6
		assert len(CM.customized_neurons_list[0]['z_positions']) == 60
		assert len(CM.customized_neurons_list[1]['z_positions']) == 267
		assert len(CM.customized_neurons_list[2]['z_positions']) == 109
		assert type(CM.customized_neurons_list[0]['z_positions'][0]) == np.complex128
		assert len(CM.customized_neurons_list[0].keys()) == 5
		assert len(CM.customized_neurons_list[1].keys()) == 18
		assert len(CM.customized_neurons_list[2].keys()) == 18		

	def test__set_scale(self):
		# assert CM.scale == 1
		assert isinstance(CM.scale, float)

	def test__set_grid_radius(self):
		assert CM.general_grid_radius.dim.__str__() == 'm'

	def test__set_min_distance(self):
		assert CM.min_distance.dim.__str__() == 'm'

	def test_init_vms(self):
		assert CM.init_vms in (0,1)
	
	# @pytest.mark.xfail()
	def test__set_simulation_folder(self):
		assert isinstance(CM.workspace.get_simulation_folder_as_posix(), str)

	# @pytest.mark.xfail()	
	def test_set_import_connections_path(self):
		assert isinstance(CM.workspace.get_imported_connection_path(), str)

	def test_load_positions_only(self):
		assert CM.load_positions_only in (0,1)

	def test_set_profiling(self):
		assert CM.profiling in (0,1)
		
	def test_neuron_group(self):
		'''
		Test the types of obligatory neuron group variables 
		'''
		assert all(isinstance(x, np.complex128) for x in CM.customized_neurons_list[0]['z_positions'])
		assert all(isinstance(x, np.complex128) for x in CM.customized_neurons_list[0]['w_positions'])
		assert isinstance(CM.customized_neurons_list[0]['equation'],str)
		assert isinstance(CM.customized_neurons_list[0]['type'],str)
		assert isinstance(CM.customized_neurons_list[0]['idx'],int)

	def test_monitors(self):
		'''
		Test the monitor names. Expected to fail if the neurongroups are modified.
		'''
		assert CM.monitor_name_bank['NG1_L4_PC1_L4toL1'] == ['SpMon1_NG1_L4_PC1_L4toL1']
		assert CM.monitor_name_bank['NG3_L4_SS_L4'] == ['SpMon3_NG3_L4_SS_L4']
		assert CM.monitor_name_bank['NG2_L4_PC2_L4toL1'] == ['SpMon2_NG2_L4_PC2_L4toL1']
		assert CM.monitor_name_bank['NG5_L4_MC_L4'] == ['SpMon5_NG5_L4_MC_L4']
		assert CM.monitor_name_bank['NG4_L4_BC_L4'] == ['SpMon4_NG4_L4_BC_L4']
		assert CM.monitor_name_bank['NG0_relay_vpm'] == ['SpMon0_NG0_relay_vpm']
		
	def test_synapse(self):
		'''
		Test the types of obligatory synapse parameters. 
		'''
		assert isinstance(CM.customized_synapses_list[0]['pre_eq'],str)
		assert isinstance(CM.customized_synapses_list[0]['pre_group_type'],str)
		assert isinstance(CM.customized_synapses_list[0]['equation'],brian2.equations.equations.Equations)
		assert isinstance(CM.customized_synapses_list[0]['namespace'],dict)
		assert isinstance(CM.customized_synapses_list[0]['post_group_idx'],int)
		assert isinstance(CM.customized_synapses_list[0]['sparseness'],float)
		assert isinstance(CM.customized_synapses_list[0]['receptor'],str)
		assert isinstance(CM.customized_synapses_list[0]['pre_group_idx'],int)
		assert isinstance(CM.customized_synapses_list[0]['post_comp_name'],str)
		assert isinstance(CM.customized_synapses_list[0]['type'],str)
		assert isinstance(CM.customized_synapses_list[0]['post_group_type'],str)
		
class TestPhysiologyReference:
	
	def test_neuron_reference_init(self):
		assert all(np.round(CM.customized_neurons_list[0]['z_positions'],decimals=2) == np.round(list(map(
			lambda x: np.e ** (x/17) - 1,CM.customized_neurons_list[0]['w_positions'] )),decimals=2))
		assert all(np.round(CM.customized_neurons_list[1]['z_positions'],decimals=2) == np.round(list(map(
			lambda x: np.e ** (x/17) - 1,CM.customized_neurons_list[1]['w_positions'] )),decimals=2))
		assert all(np.round(CM.customized_neurons_list[2]['z_positions'],decimals=2) == np.round(list(map(
			lambda x: np.e ** (x/17) - 1,CM.customized_neurons_list[2]['w_positions'] )),decimals=2))
			
	def test_PC1(self):
		'''Testing one part of equation in soma and one in apical dendrite'''
		assert 'PC1' in CM.customized_neurons_list[1]['object_name']
		assert '-ge_soma/tau_e' in \
			str(CM.customized_neurons_list[1]['equation'].eq_expressions)
		assert 'vm_a2' in \
			str(CM.customized_neurons_list[1]['equation'].eq_expressions)
			
	def test_PC2(self):
		'''Testing one part of equation in soma and one in apical dendrite'''
		assert 'PC2' in CM.customized_neurons_list[2]['object_name']
		assert '-ge_soma/tau_e' in \
			str(CM.customized_neurons_list[2]['equation'].eq_expressions)
		assert 'vm_a2' in \
			str(CM.customized_neurons_list[2]['equation'].eq_expressions)

	def test_SS(self):
		'''Testing one part of equation'''
		assert 'SS' in CM.customized_neurons_list[3]['object_name']
		assert '-ge_soma/tau_e' in \
			str(CM.customized_neurons_list[3]['equation'].eq_expressions)
			
	def test_BC(self):
		'''Testing one part of equation'''
		assert 'BC' in CM.customized_neurons_list[4]['object_name']
		assert '-ge_soma/tau_e' in \
			str(CM.customized_neurons_list[4]['equation'].eq_expressions)
			
	def test_MC(self):
		'''Testing one part of equation'''
		assert 'MC' in CM.customized_neurons_list[5]['object_name']
		assert '-ge_soma/tau_e' in \
			str(CM.customized_neurons_list[5]['equation'].eq_expressions)
			

class TestEquationHelper:

	def test_neuron_model(self):
		assert len(eqt.EquationHelper.NeuronModels.keys()) == 4
		assert isinstance(eqt.EquationHelper.NeuronModels['EIF'],dict)
		
		
	excitation_model = CM.value_extractor(CM.physio_config_df, 'excitation_model')
	inhibition_model = CM.value_extractor(CM.physio_config_df, 'inhibition_model')

	def test_excitation_model(self):
		assert self.excitation_model == 'SIMPLE_E'
	def test_inhibition_model(self):
		assert self.inhibition_model == 'SIMPLE_I_GABAB'
	def test_exc_receptors(self):
		exc_receptors = eqt.EquationHelper.BackgroundReceptors[self.excitation_model]
		assert exc_receptors==['ge']
	def test_inh_receptors(self):
		inh_receptors = eqt.EquationHelper.BackgroundReceptors[self.inhibition_model]
		assert inh_receptors==['gi']

###################
# Integration tests
###################

@pytest.fixture(scope='module')
def cxsystem_run_fixture():

	#Executing setup code
	CM.run()
	
	yield # Run the tests here
	
	#Executing teardown code
	shutil.rmtree(CM.workspace.get_simulation_folder_as_posix())

@pytest.fixture(scope='module')
def get_spike_data():
	output_fullpath = path.joinpath('tests','output_files','pytest_spike_reference_data_200ms.gz')
	with open(output_fullpath, 'rb') as fb:
		d_pickle = zlib.decompress(fb.read())
		data = pickle.loads(d_pickle)
		spikes_all = data['spikes_all']
	new_output_name = [item for item in os.listdir(CM.workspace.get_simulation_folder_as_posix()) if '_results_' in item] #Assuming just one outputfile in this folder
	new_output_fullpath = path.joinpath(CM.workspace.get_simulation_folder_as_posix(), new_output_name[0])
	with open(new_output_fullpath, 'rb') as fb:
		new_d_pickle = zlib.decompress(fb.read())
		new_data = pickle.loads(new_d_pickle)
		new_spikes_all = new_data['spikes_all']

	return spikes_all, new_spikes_all

# @pytest.mark.skip(reason="too slow")
def test_outputfile(cxsystem_run_fixture):
	'''Test for existing outputfile'''
	outputfilelist = [item for item in os.listdir(CM.workspace.get_simulation_folder_as_posix()) if "_results_" in item]
	assert os.access(CM.workspace.get_simulation_folder().joinpath(outputfilelist[0]), os.W_OK)
	
# @pytest.mark.xfail(reason='not identical spikes')		
def test_spikecount_10percent_tolerance(cxsystem_run_fixture,
										capsys,
										get_spike_data):
	spikes_all, new_spikes_all = get_spike_data
	keys=list(spikes_all.keys()) # dict_keys is not indexable directly
	for key in keys:
		spike_count_proportion = new_spikes_all[key]['N'] / spikes_all[key]['N']
		assert 0.9 <= spike_count_proportion <= 1.1

@pytest.mark.xfail(reason='The same spikes not attainable in a distinct run')		
def test_spikecount_strict(cxsystem_run_fixture,
						   get_spike_data):
	spikes_all, new_spikes_all = get_spike_data
	keys=list(spikes_all.keys()) # dict_keys is not indexable directly
	for key in keys:
		spike_count_proportion = new_spikes_all[key]['N'] / spikes_all[key]['N']
		assert spike_count_proportion == 1.0

@pytest.mark.xfail(reason='The same spikes not attainable in a distinct run')		
def test_spiketiming_strict(cxsystem_run_fixture,
							get_spike_data):
	spikes_all, new_spikes_all = get_spike_data
	keys=list(spikes_all.keys()) # dict_keys is not indexable directly
	for key in keys:

		assert all(new_spikes_all[key]['i'] == spikes_all[key]['i'])
		assert all(new_spikes_all[key]['t'] == spikes_all[key]['t'])
		
def test_spikecount_report(cxsystem_run_fixture,
						   capsys,
						   get_spike_data):
	spikes_all, new_spikes_all = get_spike_data
	keys=list(spikes_all.keys()) # dict_keys is not indexable directly
	with capsys.disabled():
			print('\n')
	for key in keys:
		spike_count_proportion = new_spikes_all[key]['N'] / spikes_all[key]['N']
		with capsys.disabled():
			print('Proportion of spike counts (new/old) for {0} is {1:.2f}'.format(key, spike_count_proportion))
		# assert spike_count_proportion == 1.0

def test_spiketiming_report(cxsystem_run_fixture,
							capsys,
							get_spike_data):
	spikes_all, new_spikes_all = get_spike_data
	keys=list(spikes_all.keys()) # dict_keys is not indexable directly

	time_resolution = 0.1 * msecond
	run_time = CM.runtime
	time_vector_length = run_time / time_resolution
	
	with capsys.disabled():
			print('\n')
			
	for key in keys:
		
		new_spikes_all[key]['N']
		spikes_all[key]['N']
		
		# find union of firing neurons in the two sets
		all_spiking_neurons = np.union1d(spikes_all[key]['i'],new_spikes_all[key]['i'])
		
		#create time vectors of zeros and ones for all neurons and both datasets
		spikes_index_time_matrix = np.zeros([max(all_spiking_neurons)+1,int(time_vector_length)]) # +1 because indexing starts at 0
		spikes_time_indeces_float = spikes_all[key]['t']/time_resolution
		spikes_index_time_matrix[spikes_all[key]['i'],spikes_time_indeces_float.astype(int)] = 1
		spikes_index_time_matrix = spikes_index_time_matrix[all_spiking_neurons,:]

		new_spikes_index_time_matrix = np.zeros([max(all_spiking_neurons)+1,int(time_vector_length)])
		new_spikes_time_indeces_float = new_spikes_all[key]['t']/time_resolution
		new_spikes_index_time_matrix[new_spikes_all[key]['i'],new_spikes_time_indeces_float.astype(int)] = 1
		new_spikes_index_time_matrix = new_spikes_index_time_matrix[all_spiking_neurons,:]
				
		cumulative_ks = 0
		cumulative_wd = 0
		for idx, neuron_idx in enumerate(all_spiking_neurons):

			spike_data = np.nonzero(spikes_index_time_matrix[idx,:])[0]
			new_spike_data = np.nonzero(new_spikes_index_time_matrix[idx,:])[0]
			
			ksstat = ks_2samp(spike_data,new_spike_data)
			wass_dist = wasserstein_distance(spike_data,new_spike_data)
			
			cumulative_ks += ksstat[0]
			cumulative_wd += wass_dist
			
		mean_ks = cumulative_ks/len(all_spiking_neurons)
		mean_wd = (time_resolution / msecond ) * cumulative_wd/len(all_spiking_neurons)
		
		# report mean of these stats
		with capsys.disabled():
			# print('Mean KS statistics for {0} is {1:.2f}'.format(key,mean_ks)) # Quantified spiketiming similarity
			print('Mean Wasserstein Distance (spike shift) for {0} is {1:.2f} ms'.format(key,mean_wd)) # Quantified spiketiming similarity

		# np.save(key, spikes_index_time_matrix)
		# np.save('New_' + key, new_spikes_index_time_matrix)
		# if key == 'NG1_L4_PC1_L4toL1': # Put here the cell group whose spikes u want to see, and remove the comment marks
			# import matplotlib.pyplot as plt
			# plt.plot(new_spikes_all[key]['t'], new_spikes_all[key]['i'], 'k.')
			# plt.plot(spikes_all[key]['t'], spikes_all[key]['i'], 'r.')
			# plt.show()
