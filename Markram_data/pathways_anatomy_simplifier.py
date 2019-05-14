# Script for simplifying Human Brain Project's Neocortical Microcircuit connectivity data(*)
# as described in (**)
# Creates a json file similar to the original pathways_anatomy_factsheets_simplified.json from (*)
#
# Author Henri Hokkanen <henri.hokkanen@helsinki.fi>
# Created 21 July 2016, last updated 3 December 2016
#
# Refs:
# (*) https://bbp.epfl.ch/nmc-portal/downloads, for explanations see Markram et al. (Cell 2015)
# (**) Article on the simplified system


from __future__ import division
import pandas as pd
import re
import json
from math import floor



file_pathways_anatomy_markram = 'pathways_anatomy_factsheets_simplified.json'
default_json_output_file = 'pathways_anatomy_cxsystem.json'
default_csv_output_file = 'generated_config_file_henri.csv'

internal_synapse_numbers_markram = 'internal_synapse_numbers.csv'
internal_connectivity_output_file = 'pathways_single_microcircuit.json'

# Mapping from Markram cell groups to own/Vanni cell groups, see (**)
# Certain less meaningful inhibitory neuron-types in (*) are mapped to the UM_I group (unassigned Markram, inhibitory).
# UM_I cells are later divided layer-by-layer between BC and MC groups, respecting their relative amounts.
cell_group_dict = {
    'L1_DAC': 'L1_I', 'L1_DLAC': 'L1_I', 'L1_HAC': 'L1_I', 'L1_NGC-DA': 'L1_I', 'L1_NGC-SA': 'L1_I', 'L1_SLAC': 'L1_I',
    'L23_BP': 'L23_UM_I', 'L23_BTC': 'L23_UM_I', 'L23_ChC': 'L23_UM_I', 'L23_DBC': 'L23_UM_I', 'L23_LBC': 'L23_BC',
    'L23_MC': 'L23_MC', 'L23_NBC': 'L23_BC', 'L23_NGC': 'L23_UM_I', 'L23_PC': 'L23_PC', 'L23_SBC': 'L23_BC',
    'L4_BP': 'L4_UM_I', 'L4_BTC': 'L4_UM_I', 'L4_ChC': 'L4_UM_I', 'L4_DBC': 'L4_UM_I', 'L4_LBC': 'L4_BC',
    'L4_MC': 'L4_MC', 'L4_NBC': 'L4_BC', 'L4_NGC': 'L4_UM_I', 'L4_PC': 'L4_PC1', 'L4_SBC': 'L4_BC', 'L4_SP': 'L4_PC2',
    'L4_SS': 'L4_SS', 'L5_BP': 'L5_UM_I', 'L5_BTC': 'L5_UM_I', 'L5_ChC': 'L5_UM_I', 'L5_DBC': 'L5_UM_I',
    'L5_LBC': 'L5_BC', 'L5_MC': 'L5_MC', 'L5_NBC': 'L5_BC', 'L5_NGC': 'L5_UM_I', 'L5_SBC': 'L5_BC',
    'L5_STPC': 'L5_PC', 'L5_TTPC1': 'L5_PC', 'L5_TTPC2': 'L5_PC', 'L5_UTPC': 'L5_PC', 'L6_BP': 'L6_UM_I',
    'L6_BPC': 'L6_PC1', 'L6_BTC': 'L6_UM_I', 'L6_ChC': 'L6_UM_I', 'L6_DBC': 'L6_UM_I', 'L6_IPC': 'L6_PC1',
    'L6_LBC': 'L6_BC', 'L6_MC': 'L6_MC', 'L6_NBC': 'L6_BC', 'L6_NGC': 'L6_UM_I', 'L6_SBC': 'L6_BC',
    'L6_TPC_L1': 'L6_PC2', 'L6_TPC_L4': 'L6_PC1', 'L6_UTPC': 'L6_PC1',
    }

cell_group_order = [
    'L1_DAC', 'L1_DLAC', 'L1_HAC', 'L1_NGC-DA', 'L1_NGC-SA', 'L1_SLAC', 'L23_BP', 'L23_BTC',
    'L23_ChC', 'L23_DBC', 'L23_LBC', 'L23_MC', 'L23_NBC', 'L23_NGC', 'L23_PC', 'L23_SBC', 'L4_BP',
    'L4_BTC', 'L4_ChC', 'L4_DBC', 'L4_LBC', 'L4_MC', 'L4_NBC', 'L4_NGC', 'L4_PC', 'L4_SBC', 'L4_SP',
    'L4_SS', 'L5_BP', 'L5_BTC', 'L5_ChC', 'L5_DBC', 'L5_LBC', 'L5_MC', 'L5_NBC', 'L5_NGC', 'L5_SBC',
    'L5_STPC', 'L5_TTPC1', 'L5_TTPC2', 'L5_UTPC', 'L6_BP', 'L6_BPC', 'L6_BTC', 'L6_ChC', 'L6_DBC',
    'L6_IPC', 'L6_LBC', 'L6_MC', 'L6_NBC', 'L6_NGC', 'L6_SBC', 'L6_TPC_L1', 'L6_TPC_L4', 'L6_UTPC']

# Inhibitory Vanni cell groups are defined here,
# ie. anything with a suffix from the list here is considered inhibitory
inhibitory_types = ['BC', 'MC', 'I', 'UM_I']  # I is Layer 1 inhibitory

# Compartmental cell types
compartmental_types = ['PC', 'PC1', 'PC2']

# Number of neurons in each Markram cell group, from (*)
cell_N_dict = {
    'L1_DAC': 58, 'L1_DLAC': 24, 'L1_HAC': 91, 'L1_NGC-SA': 52, 'L1_NGC-DA': 72, 'L1_SLAC': 41, 'L23_DBC': 106+69,
    'L23_BP': 16+12, 'L23_LBC': 277+179, 'L23_NGC': 34+22, 'L23_NBC': 160+108, 'L23_SBC': 99+67, 'L23_ChC': 37+24,
    'L23_BTC': 63+41, 'L23_PC': 2421+3456, 'L23_MC': 202+131, 'L4_ChC': 8, 'L4_NBC': 96, 'L4_LBC': 122, 'L4_MC': 118,
    'L4_SS': 406, 'L4_SBC': 60, 'L4_DBC': 40, 'L4_SP': 1098, 'L4_PC': 2674, 'L4_BTC': 20, 'L4_BP': 8, 'L4_NGC': 6,
    'L5_DBC': 96, 'L5_BP': 34, 'L5_LBC': 210, 'L5_STPC': 302, 'L5_NGC': 8, 'L5_SBC': 25, 'L5_NBC': 201, 'L5_ChC': 19,
    'L5_BTC': 76, 'L5_TTPC1': 2403, 'L5_MC': 395, 'L5_UTPC': 342, 'L5_TTPC2': 2003, 'L6_MC': 336, 'L6_ChC': 16,
    'L6_SBC': 67, 'L6_NGC': 17, 'L6_LBC': 463, 'L6_BTC': 54, 'L6_NBC': 198, 'L6_BPC': 3174, 'L6_IPC': 3476,
    'L6_TPC_L1': 1637, 'L6_DBC': 31, 'L6_TPC_L4': 1440, 'L6_UTPC': 1735, 'L6_BP': 7
    }



# Default values for function create_csv_config_file
# TODO - These should be modifiable in config file
default_center = '5+0j'
default_NG_monitor = 'N/A'
default_syn_type = 'Fixed'
default_syn_monitor = 'N/A'
default_percentage = 'N/A'

# Due to different naming conventions in the JSON files and the CSV configuration file,
# the following dictionaries are needed (see function create_csv_config_file)
csv_group_options = {
    'I': 'L1i',
    'BC': 'BC',
    'MC': 'MC',
    'PC': 'PC',
    'PC1': 'PC',
    'PC2': 'PC',
    'SS': 'SS',
    'UM_I': 'UMi',
}
csv_layer_options = {
    'L1': '1',
    'L23': '2',
    'L4': '4',
    'L5': '5',
    'L6': '6',
}
csv_PC_layer_options = {
    'L23_PC': '[2->1]',
    'L4_PC1': '[4->2]',
    'L4_PC2': '[4->1]',
    'L5_PC': '[5->1]',
    'L6_PC1': '[6->4]',
    'L6_PC2': '[6->1]',
}

layer_as_int = {'L1': 1, 'L23': 2, 'L4': 4, 'L5': 5, 'L6': 6}
# int_as_layer =


def _preprocess_pathways_anatomy(data):
    '''Preprocesses HBP connectivity data for the 2nd step (computing simplified model config)

    This function goes through the data row-by-row (row corresponding to each connection between neuron groups) and
    extracts information from connection names, such as L6_UTPC:L6_IPC. From them, we get
    pre-/postsynaptic layers, Markram cell groups and the corresponding Vanni cell groups.

    Parameters
    ----------
    data - HBP connectivity data as a pandas DataFrame (read using pandas.read_json)

    Returns
    -------
    data - preprocessed data (as pandas DataFrame)
    '''

    # Split connection names (eg. L6_UTPC:L6_IPC) into two columns -> markram_pre, markram_post
    markram_to_vanni = data.index.str.extract('(.*):(.*)', expand=True)
    markram_to_vanni.index = data.index
    markram_to_vanni.columns = ['markram_pre', 'markram_post']

    # Get corresponding Vanni neuron groups & create "Vanni index, eg. L6_PC1:L6_PC1"
    markram_to_vanni['vanni_pre'] = markram_to_vanni['markram_pre'].map(cell_group_dict)
    markram_to_vanni['vanni_post'] = markram_to_vanni['markram_post'].map(cell_group_dict)
    markram_to_vanni['vanni_index'] = markram_to_vanni['vanni_pre'] + ':' + markram_to_vanni['vanni_post']

    # Get number of neurons pre and post Markram neuron groups
    markram_to_vanni['neuron_number_pre'] = markram_to_vanni['markram_pre'].map(cell_N_dict)
    markram_to_vanni['neuron_number_post'] = markram_to_vanni['markram_post'].map(cell_N_dict)

    # Extract layer & Markram cell type info
    pre_layers = markram_to_vanni['markram_pre'].str.extract('^(\w{2,3})_(.*)$', expand=True)
    post_layers = markram_to_vanni['markram_post'].str.extract('^(\w{2,3})_(.*)$', expand=True)

    pre_layers.columns = ['layer_pre', 'markram_pre_celltype']
    post_layers.columns = ['layer_post', 'markram_post_celltype']

    # Extract Vanni cell type info
    #celltypes_post = markram_to_vanni['vanni_pre'].str.extract('^(\w{2,3})_(.*)$', expand=False)
    #celltypes_pre =  markram_to_vanni['vanni_post'].str.extract('^\w{2,3}_(.*)$', expand=False)

    # Join em all!
    data = data.join(markram_to_vanni)
    data = data.join(pre_layers)
    data = data.join(post_layers)

    return data

def _compute_connection_parameters(connection_index, preprocessed_data): # TODO Some cleanup needed
    '''For a given connection, computes connectivity parameters based on preprocessed data

    For a given connection between Vanni neuron groups, this function sums the total number of synapses and
    computes connection probability based on preprocessed pathways_anatomy data. The function returns
    a pandas DataFrame corresponding to connection_index with relevant connection parameters.

    Parameters
    ----------
    connection_index - name of connection between Vanni neuron groups, eg. L4_PC1:L5_PC
    preprocessed_data - preprocessed connectivity data from function _preprocess_pathways_anatomy

    Returns
    -------
    conn_params - parameters corresponding to connection_index (connection between Vanni neuron groups)
    '''
    print('Working on ' + connection_index)

    data = preprocessed_data

    pre_group, post_group = connection_index.split(':')

    conn_groups = data[data.vanni_pre == pre_group][data.vanni_post == post_group]
    pre_groups = conn_groups.markram_pre.unique()
    post_groups = conn_groups.markram_post.unique()

    # Calculate number of neurons in pre & post Markram groups
    N_pre = 0
    N_post = 0

    for pre in pre_groups:
        N_pre += cell_N_dict[pre]

    for post in post_groups:
        N_post += cell_N_dict[post]

    N_possible = N_pre * N_post  # Total number of possible connections

    # Calculate total synapse count for Vanni pair
    tot_synapses = conn_groups.total_synapse_count.sum()

    # Calculate connection probability (*)
    N_subgroups = dict()

    for pre in pre_groups:
        for post in post_groups:
            conn = str(pre + ':' + post)
            try:
                N_subgroups[conn] = data.ix[conn].connection_probability * data.ix[conn].neuron_number_pre * data.ix[
                    conn].neuron_number_post
            except KeyError:
                N_subgroups[conn] = 0

    N_expected = sum(N_subgroups.values())
    conn_prob = N_expected / N_possible

    # IIa Calculate weighted average of the means of synapses per connection
    # (** weighing by N_neurons_pre * N_neurons_post, Simo & Vafa)
    weighted_spcs = dict()

    for pre in pre_groups:
        for post in post_groups:
            conn = str(pre + ':' + post)
            try:
                weighted_spcs[conn] = data.ix[conn].mean_number_of_synapse_per_connection * data.ix[
                    conn].neuron_number_pre * data.ix[conn].neuron_number_post
            except KeyError:
                weighted_spcs[conn] = 0

    sum_weighted_spc = sum(weighted_spcs.values())
    weighted_spc = sum_weighted_spc / N_possible

    po = tot_synapses / (weighted_spc * N_pre * N_post)

    # IIb Calculate weighted average of the means of synapses per connection
    # (*** weighing by N_neurons_pre * N_neurons_post, Henri)
    weighted_spcs2 = dict()

    for pre in pre_groups:
        for post in post_groups:
            conn = str(pre + ':' + post)
            try:
                weighted_spcs2[conn] = data.ix[conn].connection_probability * data.ix[
                    conn].mean_number_of_synapse_per_connection * data.ix[conn].neuron_number_pre * data.ix[
                                           conn].neuron_number_post
            except KeyError:
                weighted_spcs2[conn] = 0

    sum_weighted_spc2 = sum(weighted_spcs2.values())

    spc2_div = dict()
    for pre in pre_groups:
        for post in post_groups:
            conn = str(pre + ':' + post)
            try:
                spc2_div[conn] = data.ix[conn].connection_probability * data.ix[conn].neuron_number_pre * data.ix[
                    conn].neuron_number_post
            except KeyError:
                spc2_div[conn] = 0

    spc2_divider = sum(spc2_div.values())
    weighted_spc2 = sum_weighted_spc2 / spc2_divider

    # Testing... => IIa and IIb produce roughly the same results - why?
    po = tot_synapses / (N_possible * weighted_spc)
    po2 = tot_synapses / (N_possible * weighted_spc2)

    # Layer and cell type
    layer_pre, celltype_pre = re.split('(\w{2,3})_(.*)', pre_group)[1:3]
    layer_post, celltype_post = re.split('(\w{2,3})_(.*)', post_group)[1:3]

    # Aggregate everything

    conn_params = pd.DataFrame(index=[connection_index], data={
        'neurongroup_pre': pre_group,
        'neurongroup_post': post_group,
        'layer_pre': layer_pre,
        'layer_post': layer_post,
        'celltype_pre': celltype_pre,
        'celltype_post': celltype_post,
        'is_inhibitory_pre': celltype_pre in inhibitory_types,
        'is_inhibitory_post': celltype_post in inhibitory_types,
        'connection_probability': po,
        'mean_number_of_synapses_per_connection': weighted_spc,
        'total_synapse_count': tot_synapses,
    })

    return conn_params

def _compute_simplified_connections(preprocessed_data, with_UM_I = False):
    '''Given preprocessed Markram connectivity data, computes simplified/Vanni connections

    Parameters
    ----------
    preprocessed_data - preprocessed connectivity data from function _preprocess_pathways_anatomy

    Returns
    -------
    result - pandas DataFrame with connections between Vanni neuron groups
    '''

    # Get a list of possible connections between Vanni neuron groups
    vanni_connections = preprocessed_data.vanni_index.unique()
    if with_UM_I == False:
        new_connections = []
        for connection in vanni_connections:
            if connection.find('UM_I') == -1:  # ie. neither connecting group is UM_I
                new_connections.append(connection)

        vanni_connections = new_connections

    # Create a list of DataFrames each containing a single connection and its parameters. Then join them!
    frames = [_compute_connection_parameters(connection, preprocessed_data)
              for connection in vanni_connections]

    result = pd.concat(frames)

    return result

def create_simplified_json(filename=default_json_output_file, input_data=False):
    '''Create/update Vanni connectivity json file (similar to pathways_anatomy_simplified.json)

    Parameters
    ----------
    filename - name of the output json file

    Returns
    -------
    None
    '''
    if input_data is False:
        data = pd.read_json(file_pathways_anatomy_markram, orient='index')
    else:
        data = input_data
    preprocessed_data = _preprocess_pathways_anatomy(data)
    simplified_data = _compute_simplified_connections(preprocessed_data)


    # Write a json file using the json module.
    # pandas to_json also works, but produces ugly output without indentation:
    # data.astype(str).to_json(file_pathways_anatomy_vannilized, orient='index')
    data_as_dict = simplified_data.to_dict(orient='index')
    fi = open(filename, 'w')
    json.dump(data_as_dict, fi, indent=3)
    fi.close()

def read_simplified_json(filename=default_json_output_file):
    '''Read simplified connectivity data from default output json file

    Returns
    -------
    pandas DataFrame
    '''

    data = pd.read_json(filename, orient='index')
    sort_order = ['layer_pre', 'is_inhibitory_pre', 'celltype_pre', 'layer_post', 'is_inhibitory_post', 'celltype_post']
    data = data.sort_values(by=sort_order)

    return data

def _compute_own_cell_N_dict(with_UM_I = False):
    '''Compute cell_N_dict corresponding to simplified model

    Returns
    -------
    dict with elements of the form: neuron group -> number of neurons in that group
    '''

    cell_group_table = pd.DataFrame.from_dict(cell_group_dict, orient='index')
    cell_group_table.columns = ['own_group']
    cell_N_table = pd.DataFrame.from_dict(cell_N_dict, orient='index')
    cell_N_table.columns = ['N']
    cell_table = cell_group_table.join(cell_N_table)
    own_cell_N = cell_table.pivot_table('N', index='own_group', aggfunc='sum')

    # Remove UM_I rows and divide UM_I neurons to MC and BC groups layer-by-layer
    if with_UM_I == False:
        rows_to_remove = pd.DataFrame(own_cell_N[own_cell_N.index.str.contains('UM_I')])
        for row in rows_to_remove.iterrows():
            UM_I_count = row[1]['N']
            layer = row[0].split('_')[0]

            # TODO Slight discrepancy with Vafa's numbers! But I think mine is correct ;)
            BC_to_BC_plus_MC = own_cell_N[layer + '_BC'] / (own_cell_N[layer + '_BC'] + own_cell_N[layer + '_MC'])
            own_cell_N[layer + '_BC'] += round( BC_to_BC_plus_MC * UM_I_count, ndigits=0 )
            own_cell_N[layer + '_MC'] += round( (1-BC_to_BC_plus_MC) * UM_I_count, ndigits=0 )

        own_cell_N = own_cell_N[own_cell_N.index.str.contains('UM_I') == False]

    return own_cell_N.to_dict()

def _compute_postsynaptic_PC_target_compartment(layer_pre, celltype_pre, layer_post, celltype_post):

    target_group = layer_post + '_' + celltype_post

    # Most distal PC compartment; how many levels up from the soma the apical dendrite goes
    most_distal_PC_compartment = {'L23_PC': 1,
                                  'L4_PC1': 1,
                                  'L4_PC2': 2,
                                  'L5_PC': 3,
                                  'L6_PC1': 2,
                                  'L6_PC2': 4}

    # INHIBITORY presynaptic neurons
    if celltype_pre in inhibitory_types:
        if celltype_pre in ['I', 'MC']:
            # L1_Is and Martinottis connect to distal apical dendrites
            target_compartment = most_distal_PC_compartment[target_group]
        elif celltype_pre == 'BC':
            target_compartment = '0s'  # BCs form axosomatic connections
        else:
            target_compartment = 'ERROR'

    # EXCITATORY presynaptic neurons
    else:
        # Presynaptic neuron at least as deep as the postsynaptic neuron
        if layer_as_int[layer_pre] >= layer_as_int[layer_post]:
            target_compartment = '0ab'

        # Find out how far up the target neuron's dendrites go and target the closest part
        else:
            most_distal_PC_layer = layer_as_int[layer_post] - most_distal_PC_compartment[target_group]
            if most_distal_PC_layer == 3:  # correction because L2/3 is a single layer
                most_distal_PC_layer = 2
            elif most_distal_PC_layer == 2:
                most_distal_PC_layer = 1

            if layer_as_int[layer_pre] <= most_distal_PC_layer: # ie. presyn. neuron is above the dendritic tree
                target_compartment = most_distal_PC_compartment[target_group]
            else:
                target_compartment = layer_as_int[layer_post] - layer_as_int[layer_pre]
                if layer_as_int[layer_pre] <= 2:
                    target_compartment -= 1  # correction because L2/3 is a single layer


    return str(target_compartment)

def create_csv_config_file(filename=default_csv_output_file, update_json=False):  # OBSOLETE (3 Dec 2016)

    if update_json == True:
        create_simplified_json()

    data = read_simplified_json()
    fi = open(filename, 'w')

    # Write header
    #fi.write('row_type,sys_mode,do_optimize\n')
    #fi.write('params,local,0\n') # TODO Shouldn't be hard-coded
    fi.write('row_type,sys_mode,do_optimize,grid_radius, min_distance, output_path, brian_data_path\n')
    fi.write('params,local,0,210*um, 1*um,../CX_Output/output_data.mat,../CX_Output/brian_data.h5\n')
    # config_file.write('row_type,idx,type,path,freq,monitors\n') TODO Shouldn't be hard-coded
    # config_file.write('IN,video,0, ./V1_input_layer_2015_10_30_11_7_31.mat ,190*Hz ,[Sp]\n')
    fi.write('row_type,idx,type,number_of_neurons,radius,spike_times,net_center,monitors\n')
    fi.write('IN,0, VPM,10,92*um,[0.1 0.12 0.15 0.17 0.20 0.22 0.25 0.5]*second, N/A ,[Sp]\n')

    # Go through NEURON GROUPS
    fi.write('row_type,idx,number_of_neurons,neuron_type,layer_idx,net_center,monitors\n')
    pre_groups = dict(enumerate(data.neurongroup_pre.unique(), start=1)) # index 0 is for input
    # Not needed as there are no dead end connections in HBP data, ie pre_groups = post_groups
    # post_groups = set(data.neurongroup_post.unique())
    own_cell_N_dict = _compute_own_cell_N_dict()

    for group_index,group_name in pre_groups.iteritems():
        NN = own_cell_N_dict[group_name]
        N_type = data[data.neurongroup_pre == group_name].celltype_pre[0]
        N_type = csv_group_options[N_type]  # Due to different naming conventions (json vs. csv)

        # Layer names also require conversion due to different conventions
        if N_type == 'PC':
            layer_idx = csv_PC_layer_options[group_name]
        else:
            layer_idx = data[data.neurongroup_pre == group_name].layer_pre[0]
            layer_idx = csv_layer_options[layer_idx]

        net_center = default_center
        NG_monitors = default_NG_monitor

        line = 'G,%d,%d,%s,%s,%s,%s\n' % (group_index, NN, N_type, layer_idx, net_center, NG_monitors)
        fi.write(line)

    # Go through CONNECTIONS/SYNAPSES
    # Invert the group index -> group name mapping
    group_to_index = {group: str(index) for index,group in pre_groups.iteritems()}

    fi.write('row_type,receptor,pre_syn_idx,post_syn_idx,syn_type,p,n,monitors,percentage\n')
    # row_type, receptor, pre_syn_idx, post_syn_idx, syn_type, p, n, monitors, percentage
    # eg: S, gi, 1, 1, Fixed, 0.014016, 15, N / A, N / A
    receptor_options = {True: 'gi', False: 'ge'}  # No particular receptors implemented at this point

    for connection in data.iterrows(): # iterrows() -> connection[0] = connection index, connection[1] = the rest
        receptor = receptor_options[connection[1].is_inhibitory_pre]
        pre_syn_idx = group_to_index[connection[1].neurongroup_pre]
        post_syn_idx = group_to_index[connection[1].neurongroup_post] # For non-compartmental cells, this is enough
        if connection[1].celltype_post in compartmental_types:
            post_syn_idx += '[C]' + _compute_postsynaptic_PC_target_compartment(connection[1].layer_pre,
                                                                                connection[1].celltype_pre,
                                                                                connection[1].layer_post,
                                                                                connection[1].celltype_post)

        syn_type = default_syn_type  # "synapse type" means learning rule (ie. Fixed, STDP, ...)
        if post_syn_idx.find('ab') == -1:
            p = round(connection[1].connection_probability, ndigits=6)
        else:
            p_half = round(connection[1].connection_probability / 2, ndigits=6)
            p = str(p_half) + '+' + str(p_half)
        n = int(floor(connection[1].mean_number_of_synapses_per_connection))
        syn_monitors = default_syn_monitor
        percentage = default_percentage

        line = 'S,%s,%s,%s,%s,%s,%s,%s,%s\n' % (receptor, pre_syn_idx, post_syn_idx, syn_type, p, n,
                                              syn_monitors, percentage)
        fi.write(line)

    fi.close()

def create_json_from_synapse_numbers(input_file = internal_synapse_numbers_markram, output_file = internal_connectivity_output_file):


    ### Part I: Create dataframe with total_synapse_count & mean_number_of_synapse_per_connection
    syn_numbers_data = pd.read_csv(input_file, index_col=0, usecols=range(56))
    syn_numbers_dict = dict()

    mean_syns_per_conn_dict = dict()

    markram_data = pd.read_json(file_pathways_anatomy_markram, orient='index')

    print('Taking an intersection of original pathways_anatomy and Reimann '
          'data...')

    n_dropped_connections = 0
    for row in syn_numbers_data.iterrows():
        presynaptic_type = row[0]
        postsynaptic_groups = row[1]

        for post_group in postsynaptic_groups.iteritems():
            connection_key = presynaptic_type + ':' + post_group[0]

            syn_numbers_dict[connection_key] = post_group[1]
            try:
                mean_syns_per_conn_dict[connection_key] = \
                    markram_data.ix[connection_key].mean_number_of_synapse_per_connection
            except:
                # We will drop all connections for which no data is provided in "original" JSON file
                # print('No data in old Markram json for ' + connection_key)
                mean_syns_per_conn_dict[connection_key] = 0
                n_dropped_connections += 1


    new_markram_data = pd.DataFrame.from_dict(syn_numbers_dict, orient='index')
    new_markram_data.columns = ['total_synapse_count']

    mean_syns_df = pd.DataFrame.from_dict(mean_syns_per_conn_dict, orient='index')
    mean_syns_df.columns = ['mean_number_of_synapse_per_connection']

    new_markram_data = new_markram_data.join(mean_syns_df)  # -> DF with 3025 rows x 2 columns
    new_markram_data = new_markram_data[
        (new_markram_data.total_synapse_count != 0) & (new_markram_data.mean_number_of_synapse_per_connection != 0)]
        # -> DF with 1932 rows (1093 dropped)
        # total_synapse_count.sum() = 35 346 785 (vs 36 401 589 in Reimann's data => 1 054 804 dropped out)

    print('Total synapse count is ' + str(
        new_markram_data.total_synapse_count.sum()))
    print('Total connections dropped is ' + str(n_dropped_connections))


    ### Part II: Calculate connection probabilities
    conn_prob_dict = dict()

    print('Calculating connection probabilities...')
    for row in new_markram_data.iterrows():
        connection_key = row[0]
        pre_group, post_group = connection_key.split(':')
        N_total_connectivity = cell_N_dict[pre_group] * cell_N_dict[post_group]
        syn_count = row[1][0]
        mean_syns_per_conn = row[1][1]

        connection_probability = syn_count / mean_syns_per_conn / N_total_connectivity
        conn_prob_dict[connection_key] = connection_probability

    conn_prob_df = pd.DataFrame.from_dict(conn_prob_dict, orient='index')
    conn_prob_df.columns = ['connection_probability']
    new_markram_data = new_markram_data.join(conn_prob_df)

    print('Feeding new data to create_simplified_json()')
    create_simplified_json(filename = output_file, input_data = new_markram_data)

    print('DONE!')


if __name__ == '__main__':
    create_json_from_synapse_numbers()