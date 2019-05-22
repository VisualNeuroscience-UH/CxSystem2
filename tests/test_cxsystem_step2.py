import pytest
import os
import sys
import CxSystem as cx
import numpy as np
import pdb
from brian2.units import *
import brian2
import equation_templates as eqt
import zlib
import pickle



'''
To use this test you need to pip install -U pytest. 
Note that the -U will upgrade necessary dependencies for pytest.

Run pytest at CxSystem root, such as git repo root.
Only Python device is tested currently, cpp and GeNN devices are not tested.
Defaultclock cannot be tested, because I dont know how to access defaultclock.dt in CxSystem.set_default_clock
data_loader not tested
visualise_connectivity not tested
multi_y_plotter not tested

in physiology_reference.py
_get_w_positions not tested
value_extractor not tested -- the example conf file simulation never goes there
'''

cwd = os.getcwd()
path, file = os.path.split(cx.__file__)
# # anatomy_and_system_config = os.path.join(path, 'tests', 'config_files', 'pytest_COBAEIF_config.csv')
# anatomy_and_system_config = os.path.join(path, 'tests', 'config_files', 'pytest_COBAEIF_config_make_connection.csv')
# physiology_config = os.path.join(path, 'tests', 'config_files', 'pytest_Physiological_Parameters_for_COBAEIF.csv')
anatomy_and_system_config = os.path.join(path, 'tests', 'config_files', 'pytest_Rev2_Step2gamma_Anatomy_config_local.csv')
physiology_config = os.path.join(path, 'tests', 'config_files', 'pytest_Rev2_Step2gamma_Physiology_config.csv')
CM = cx.CxSystem(anatomy_and_system_config, physiology_config, instantiated_from_array_run=0)

def test_cwd():
	assert "CxSystem.py" in os.listdir(os.getcwd()) 

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
		assert CM.anat_and_sys_conf_df.shape[1] == 19
		

	def test_number_of_input_arguments(self):
		assert CM.__init__.__code__.co_argcount==8, "Number of arguments have changed"
		
	def test_local_variable_names(self):
		assert CM.__init__.__code__.co_varnames == \
		('self', 'anatomy_and_system_config', 'physiology_config', 'output_file_suffix', 
		'instantiated_from_array_run', 'cluster_run_start_idx', 'cluster_run_step', 'array_run_in_cluster', 
		'params_indices', 'row_idx', 'number_of_new_columns', 'number_of_rows', 
		'existing_rows', 'new_columns', 'empty_dataframe', 'new_anat_and_sys_conf_df', 
		'row', 'check_array_run_anatomy', 'check_array_run_physiology', 'trials_per_config'
		)
		
	def test_input_argument_types(self):
		assert isinstance(CM.StartTime_str, str) 
		# assert CM.array_run == bool(CM.array_run), "Indirect test for input arg instantiated_from_array_run"
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
				== np.array([0, 3, 7, 16]))
	
	def test_set_runtime_parameters(self):
		'''Note, cpp and GeNN devices are not tested '''
		assert CM.runtime == 200. * msecond
		assert CM.device.lower() == 'python'
		assert CM.sys_mode == 'local'
		
	def test_relay(self):
		''' This is expected to fail if corresponding parameters in the 
			configuration file changes'''
		# pdb.set_trace()
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
		# pdb.set_trace()
		assert CM.general_grid_radius.dim.__str__() == 'm'

	def test__set_min_distance(self):
		assert CM.min_distance.dim.__str__() == 'm'

	def test_do_init_vms(self):
		assert CM.do_init_vms in (0,1)
	
	# @pytest.mark.xfail()
	def test__set_save_brian_data_path(self):
		assert isinstance(CM.save_brian_data_path, str) 

	# @pytest.mark.xfail()	
	def test__set_load_brian_data_path(self):
		assert isinstance(CM.load_brian_data_path, str) 

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
		assert CM.customized_neurons_list[0]['z_positions'] == list(map(
			lambda x: np.e ** (x/17) - 1,CM.customized_neurons_list[0]['w_positions'] ))
		assert CM.customized_neurons_list[1]['z_positions'] == list(map(
			lambda x: np.e ** (x/17) - 1,CM.customized_neurons_list[1]['w_positions'] ))
		assert CM.customized_neurons_list[2]['z_positions'] == list(map(
			lambda x: np.e ** (x/17) - 1,CM.customized_neurons_list[2]['w_positions'] ))
			
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
			
#TAHAN JAIT TEST SYNAPSE REFERENCE

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
	[os.remove(os.path.join(CM.output_folder,item)) for item in os.listdir(CM.output_folder) if item.startswith('output')]
	os.rmdir(CM.output_folder)
	[os.remove(os.path.join(CM.save_brian_data_folder,item)) for item in os.listdir(CM.save_brian_data_folder) if item.startswith('connections')]
	os.rmdir(CM.save_brian_data_folder)

@pytest.fixture(scope='module')
def get_spike_data():
	output_fullpath = os.path.join(path, 'tests','output_files','output_20190522_20283767_python_200ms.gz')
	with open(output_fullpath, 'rb') as fb:
		d_pickle = zlib.decompress(fb.read())
		data = pickle.loads(d_pickle)
		spikes_all = data['spikes_all']
	new_output_name = [item for item in os.listdir(CM.output_folder) if item.startswith('output')] #Assuming just one outputfile in this folder
	new_output_fullpath = os.path.join(path, CM.output_folder, new_output_name[0])
	with open(new_output_fullpath, 'rb') as fb:
		new_d_pickle = zlib.decompress(fb.read())
		new_data = pickle.loads(new_d_pickle)
		new_spikes_all = new_data['spikes_all']

	return spikes_all, new_spikes_all

# @pytest.mark.skip(reason="too slow")
def test_outputfile(cxsystem_run_fixture):
	'''Test for existing outputfile'''
	outputfilelist = [item for item in os.listdir(CM.output_folder) if item.startswith('output')]
	assert os.access(os.path.join(CM.output_folder,outputfilelist[0]), os.W_OK)
	
# @pytest.mark.xfail(reason='not identical spikes')		
def test_spikecount_5percent_tolerance(cxsystem_run_fixture, capsys, get_spike_data):
	spikes_all, new_spikes_all = get_spike_data
	keys=list(spikes_all.keys()) # dict_keys is not indexable directly
	for key in keys:
		spike_count_proportion = new_spikes_all[key]['N'] / spikes_all[key]['N']
		assert 0.95 <= spike_count_proportion <= 1.05
		# with capsys.disabled():
			# print(f'\nProportion of spike counts (new/old) for {key} is {spike_count_proportion}')
		# import matplotlib.pyplot as plt
		# # key = 'NG1_L4_PC1_L4toL1'
		# plt.plot(new_spikes_all[key]['t'], new_spikes_all[key]['i'], 'k.')
		# plt.plot(spikes_all[key]['t'], spikes_all[key]['i'], 'r.')
		# plt.show()

def test_spikecount_strict(cxsystem_run_fixture, get_spike_data):
	spikes_all, new_spikes_all = get_spike_data
	keys=list(spikes_all.keys()) # dict_keys is not indexable directly
	for key in keys:
		spike_count_proportion = new_spikes_all[key]['N'] / spikes_all[key]['N']
		assert spike_count_proportion == 1.0

def test_spiketiming_strict(cxsystem_run_fixture, get_spike_data):
	spikes_all, new_spikes_all = get_spike_data
	keys=list(spikes_all.keys()) # dict_keys is not indexable directly
	for key in keys:
		# pdb.set_trace()
		assert all(new_spikes_all[key]['i'] == spikes_all[key]['i'])
		assert all(new_spikes_all[key]['t'] == spikes_all[key]['t'])
		
		
# # @pytest.mark.xfail(reason='not implemented yet')		
# def test__set_save_brian_data_path(cxsystem_run_fixture):
	# assert isinstance(CM.save_brian_data_path, str) 
	
# def test__set_load_brian_data_path(cxsystem_run_fixture):
	# assert isinstance(CM.load_brian_data_path, str) 
# @pytest.mark.xfail(reason='not implemented yet')		

 
