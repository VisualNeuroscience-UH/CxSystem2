__author__ = 'V_AD'
import numpy as np
import pandas as pd
import os

simo_data = pd.read_json(os.path.abspath('./pathways_anatomy_preprocessed.json'),  orient='index')
henri_data = pd.read_json(os.path.abspath('./pathways_single_microcircuit.json'), orient='index')
with open('./Markram_config_file.csv', 'w') as config_file:
    config_file.write('row_type,sys_mode,grid_radius, min_distance, do_init_vms,output_path, save_brian_data_path , #load_brian_data_path, #load_positions_only\n')
    config_file.write('params,local,210*um, 1*um,1,/opt3/CxOutput/CxOutput.gz,/opt3/CxOutput/brian_data.gz, /opt3/CxOutput/brian_data_20161028_142108.gz, 0\n')
    # config_file.write('row_type,idx,type,path,freq,monitors\n')
    # config_file.write('IN,video,0, ./V1_input_layer_2015_10_30_11_7_31.mat ,190*Hz ,[Sp]\n')
    config_file.write('row_type,idx,type,number_of_neurons,radius,spike_times,net_center,monitors\n')
    config_file.write('IN,0, VPM,10,92*um,[0.1 0.12 0.15 0.17 0.20 0.22 0.25 0.5]*second, -- ,[Sp]\n')
    config_file.write('row_type,idx,number_of_neurons,neuron_type,layer_idx,net_center,monitors\n')
    group_index=1
    NG_options = {
        'L1_I': 'L1i',
        '_BC': 'BC',
        '_MC': 'MC',
        '_PC': 'PC',
        '_SS': 'SS',
        '_UM_I': 'UMi',
    }
    layer_options = {
        '1': '1',
        '23': '2',
        '4': '4',
        '5': '5',
        '6': '6',
    }
    PC_layer_options = {
        '2' : '1',
        '41': '2',
        '42': '1',
        '5': '1',
        '61': '4',
        '62' : '1',
    }
    default_center = '--'
    default_NG_monitor = ',[Sp]'
    group_items = []
    UMi_dict = {}
    for item in simo_data['vanni_pre'].unique():
        layer_str = item[0:item.index('_')]
        layer_idx = [layer_options[lay] for lay in layer_options.keys() if lay in layer_str][0]
        N_type = [NG_options[opt] for opt in NG_options.keys() if opt in item][0]
        NN = sum(np.unique(simo_data.ix[np.where(simo_data['vanni_pre'] == item)[0]]['neuron_number_pre']))
        if N_type == 'UMi' or N_type == 'BC' or N_type == 'MC':
            try:
                if type(UMi_dict[layer_idx]) != dict:
                    UMi_dict[layer_idx] = {}
            except:
                UMi_dict[layer_idx] = {}
            if N_type == 'UMi':
                UMi_dict[layer_idx]['UMi'] = NN
            if N_type == 'BC' :
                UMi_dict[layer_idx]['BC'] = NN
            if N_type == 'MC':
                UMi_dict[layer_idx]['MC'] = NN
    for item in UMi_dict:
        UMi_dict[item]['BC'] = int(UMi_dict[item]['BC'] + (float(UMi_dict[item]['BC']) / (
            UMi_dict[item]['BC']+UMi_dict[item]['MC']))*UMi_dict[item]['UMi'])
        UMi_dict[item]['MC'] = int(UMi_dict[item]['MC'] + (float(UMi_dict[item]['MC']) / (
            UMi_dict[item]['BC'] + UMi_dict[item]['MC'])) * UMi_dict[item]['UMi'])
    all_groups = simo_data['vanni_pre'].unique()
    sorted_groups = []
    layers= np.unique([group[group.index('L')+1] for group in all_groups])
    for layer in layers:
        tmp_groups = [group for group in all_groups if group[group.index('L')+1] == layer]
        if len(tmp_groups)>1:
            SSs = [sub_group for sub_group in tmp_groups if 'SS' in sub_group]
            PCs = sorted([sub_group for sub_group in tmp_groups if 'PC' in sub_group],key=lambda x:sub_group[-1])
            BCs = [sub_group for sub_group in tmp_groups if 'BC' in sub_group]
            MCs = [sub_group for sub_group in tmp_groups if 'MC' in sub_group]

            if PCs:
                sorted_groups.extend(PCs)
            if SSs:
                sorted_groups.extend(SSs)
            if BCs:
                sorted_groups.extend(BCs)
            if MCs:
                sorted_groups.extend(MCs)
        else:
            sorted_groups.extend(tmp_groups)


    for item in sorted_groups:
        layer_str = item[0:item.index('_')]
        layer_idx = [layer_options[lay] for lay in layer_options.keys() if lay in layer_str][0]
        N_type = [NG_options[opt] for opt in NG_options.keys() if opt in item][0]
        if N_type == 'PC':
            # print(item)
            if len(item[item.index('_')+1:])>2:
                layer_idx = '[' + layer_idx + '->' + PC_layer_options[layer_idx+item[item.index('_')+1:][2]] + ']'
            else:
                layer_idx = '[' + layer_idx + '->1]'
        if N_type == 'BC' :
            NN = UMi_dict[layer_idx]['BC']
        elif N_type == 'MC':
            NN = UMi_dict[layer_idx]['MC']
        else:
            NN = sum(np.unique(simo_data.ix[np.where(simo_data['vanni_pre'] == item)[0]]['neuron_number_pre']))
        line = 'G,%d,%d,%s,%s,%s%s\n' %(group_index,NN,N_type,layer_idx,default_center, default_NG_monitor )
        if N_type == 'UMi':
            line+= 'Skipped because UMi group found'
        if not 'Skipped because UMi group found' in line :
            config_file.write(line)
            group_index += 1
            group_items.append(item)
    config_file.write('row_type,receptor,pre_syn_idx,post_syn_idx,syn_type,p,n,monitors,load_connection,save_connection\n')
    config_file.write('###########\n###########\n#*** input connections here***\n###########\n###########\n')
    syn_num = len(henri_data[:])
    receptor_options={
        '_I' : 'gi',
        '_BC' : 'gi',
        '_MC' : 'gi',
        '_SS' : 'ge',
        '_PC' : 'ge',
    }
    default_syn_type = 'Fixed'
    default_syn_monitor = '--'
    for syn_index in range(0,syn_num):
        line = 'S,ge,0,1,Fixed,0.043,--,[St]wght[rec](0-20),0.60'
        line = 'S,'
        syn_name = henri_data.ix[syn_index].name
        syn_name_pre = syn_name[0:syn_name.index(':')]
        syn_name_post = syn_name[syn_name.index(':')+1:]
        if 'UM' in syn_name_pre or 'UM' in syn_name_post :
            continue
        receptor =  [receptor_options[NG_type] for NG_type in receptor_options.keys() if NG_type in syn_name_pre][0]
        line += receptor + ','
        pre_group_item = [it for it in group_items if syn_name_pre == it][0]
        pre_group_idx = group_items.index(pre_group_item)
        post_group_item = [it for it in group_items if syn_name_post == it][0]
        post_group_idx = group_items.index(post_group_item)
        line += '%d' %(pre_group_idx+1)+ ','
        if 'PC' in post_group_item:
            line += '%d' % (post_group_idx+1)
            pre_layer_idx = pre_group_item[1:pre_group_item.index('_')]
            if '3' in pre_layer_idx :
                pre_layer_idx = '2'
            post_layer_start_idx = post_group_item[1:post_group_item.index('_')] if int(post_group_item[1:post_group_item.index('_')]) != 23 else '2'
            if post_layer_start_idx == '4' or post_layer_start_idx == '6':
                post_group_layers_list = range(int(post_layer_start_idx ), int(PC_layer_options[post_layer_start_idx + post_group_item[-1]])-1,-1)
                if 3 in post_group_layers_list :
                    del post_group_layers_list[post_group_layers_list.index(3)]
            else:
                post_group_layers_list = range(int(post_layer_start_idx ),int(PC_layer_options[post_layer_start_idx])-1,-1)
                if 3 in post_group_layers_list :
                    del post_group_layers_list[post_group_layers_list.index(3)]
            if receptor == 'gi':

                if pre_layer_idx == '1' and '_I' in pre_group_item: # for layer 1 inhibitory
                    # assert 1 in post_group_layers_list, 'presynaptic group is L1i but and is targetting a group which deos not have any compartment in layer1, is this normal?'
                    # if not 1 in post_group_layers_list:
                    #     line+= 'skip this line since there is no layer 1 compartment in the group'
                    line += '[C]%d,'%(len(post_group_layers_list)-1)
                elif '_MC' in pre_group_item:
                    line += '[C]%d,' %post_group_layers_list.index(post_group_layers_list[-1])
                elif '_BC' in pre_group_item:
                    line += '[C]0s,'
                else:
                    raise ValueError('receptor is gi but the cell group in not defined')
            elif receptor == 'ge':
                if pre_layer_idx == post_layer_start_idx :
                    line+='[C]0ab,'
                else:
                    closest_comp = min(post_group_layers_list, key=lambda x:abs(x-int(pre_layer_idx)))
                    line+='[C]%d' % post_group_layers_list.index(closest_comp)
                    if post_group_layers_list.index(closest_comp) == 0 :
                        line += 'ab'
                    line+=','
            else:
                raise ValueError('receptor type should be either ge or gi, but it is %s'%receptor)
        else:
            line+= '%d'%(post_group_idx+1) + ','
        line+= default_syn_type+ ','
        if '[C]0' in line:
            targ_comp_num = len(line[line.index('[C]0')+4:len(line[0:line.index('[C]0')])+line[line.index('[C]0'):].index(',')])
            line += '%s' % str(list(np.repeat(henri_data.ix[syn_index]['connection_probability']/targ_comp_num,targ_comp_num))).replace(', ','+').replace('[','').replace(']','') + ','
            line += '%s' % str(list(
                np.repeat(int(round(henri_data.ix[syn_index]['mean_number_of_synapses_per_connection'])), targ_comp_num))).replace(
                ', ', '+').replace('[', '').replace(']', '') + ','
        else:
            line+= '%f'%henri_data.ix[syn_index]['connection_probability']+ ','
            line += '%d' % int(round(henri_data.ix[syn_index]['mean_number_of_synapses_per_connection'])) + ','
        line += default_syn_monitor + ','
        line += '1' + ',' #load connection
        line += '1' + '\n'

        if not 'skip this line since there is no layer 1 compartment in the group' in line:
            config_file.write(line)


        # _mapping = {
#     u'L1_I': 'L1i',
#     u'L23_UM_I': 'UMi',
#     u'L23_BC' : 'BC',
#     u'L23_MC':'MC',
#     u'L23_PC':'PC',
#     u'L4_UM_I':'UMi',
#     u'L4_BC':'BC',
#     u'L4_MC':'MC',
#     u'L4_PC1':'PC',
#     u'L4_PC2':'PC',
#     u'L4_SS':'SS',
#     u'L5_UM_I':'UMi',
#     u'L5_BC':'BC',
#     u'L5_MC':'MC',
#     u'L5_PC':'PC',
#     u'L6_UM_I':'UMi',
#     u'L6_PC1':'PC1',
#     u'L6_BC':'BC',
#     u'L6_MC':'MC',
#     u'L6_PC2':'PC,'
# }