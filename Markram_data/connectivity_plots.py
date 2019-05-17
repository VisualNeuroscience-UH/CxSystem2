import pandas as pd
import seaborn as sns
import numpy as np
import matplotlib.pyplot as plt
import matplotlib
matplotlib.rcParams['pdf.fonttype'] = 42
matplotlib.rcParams['ps.fonttype'] = 42

cxs_local_connectivity_json = 'pathways_anatomy_cxsystem.json'
preprocessed_markram_anatomy_json = 'pathways_anatomy_preprocessed.json'
plot_directory = '/home/shohokka/PycharmProjects/cxs_plots/'

mycmap = 'viridis'
sort_order = ['layer_pre', 'is_inhibitory_pre', 'celltype_pre', 'layer_post', 'is_inhibitory_post', 'celltype_post']

markram_sort_order = ['L1_DAC', 'L1_DLAC', 'L1_HAC', 'L1_NGC-DA', 'L1_NGC-SA', 'L1_SLAC', 'L23_BP', 'L23_BTC', 'L23_ChC', 'L23_DBC', 'L23_LBC', 'L23_MC', 'L23_NBC', 'L23_NGC', 'L23_PC', 'L23_SBC', 'L4_BP', 'L4_BTC', 'L4_ChC', 'L4_DBC', 'L4_LBC', 'L4_MC', 'L4_NBC', 'L4_NGC', 'L4_PC', 'L4_SBC', 'L4_SP', 'L4_SS', 'L5_BP', 'L5_BTC', 'L5_ChC', 'L5_DBC', 'L5_LBC', 'L5_MC', 'L5_NBC', 'L5_NGC', 'L5_SBC', 'L5_STPC', 'L5_TTPC1', 'L5_TTPC2', 'L5_UTPC', 'L6_BP', 'L6_BPC', 'L6_BTC', 'L6_ChC', 'L6_DBC', 'L6_IPC', 'L6_LBC', 'L6_MC', 'L6_NBC', 'L6_NGC', 'L6_SBC', 'L6_TPC_L1', 'L6_TPC_L4', 'L6_UTPC']

def plot_local_connectivity(local_connectivity_json=cxs_local_connectivity_json):

    data = pd.read_json(local_connectivity_json, orient='index')

    # Saving & reading messes with correct order, so we need to save it
    data = data.sort_values(by=sort_order)
    correct_order = data.neurongroup_pre.unique()

    conn_p_table = data.pivot_table('connection_probability',
                                                          index='neurongroup_pre', columns='neurongroup_post',
                                                          aggfunc=sum)*100
    sns.set()
    # Pivoting messes (=alphabetizes) the order
    conn_p_table = conn_p_table.reindex(index=correct_order, columns=correct_order)

    conn_p_table.index.name = 'Presynaptic neuron group'
    conn_p_table.columns.name = 'Postsynaptic neuron group'
    ax = sns.heatmap(conn_p_table, cmap=mycmap, vmin=0, vmax=3.0)

    plt.tick_params(axis="both", labelsize=8)
    plt.setp(ax.get_xticklabels(), rotation=90)
    plt.setp(ax.get_yticklabels(), rotation=0)

    plt.title('Simplified neural network')
    cbar = ax.collections[0].colorbar
    cbar.set_label('Connection probability')
    plt.tight_layout()
    plt.savefig(plot_directory + 'cxs_local_connectivity' + '.pdf', dpi=600)
    # plt.savefig(plot_directory + 'cxs_local_connectivity' + '.png')
    plt.close()



def plot_markram_connectivity(markram_json = preprocessed_markram_anatomy_json):

    data = pd.read_json(markram_json, orient='index')

    plotdata = data.pivot_table('connection_probability',
                                index='markram_pre', columns='markram_post',
                                aggfunc='sum')
    plotdata = plotdata.reindex(index=markram_sort_order, columns=markram_sort_order)

    plotdata.index.name = 'Presynaptic neuron group'
    plotdata.columns.name = 'Postsynaptic neuron group'
    plotobj = sns.heatmap(plotdata, cmap=mycmap, vmin=0, vmax=30)
    plt.tick_params(axis="both", labelsize=6)
    plt.setp(plotobj.get_xticklabels(), rotation=90)
    plt.setp(plotobj.get_yticklabels(), rotation=0)
    plt.title('Reference neural network')
    cbar = plotobj.collections[0].colorbar
    cbar.set_label('Connection probability')
    plt.tight_layout()
    plt.savefig(plot_directory + 'markram_local_connectivity' + '.pdf', dpi=600)
    # plt.savefig(plot_directory + 'markram_local_connectivity' + '.png')
    plt.close()
    #plt.show()






plot_markram_connectivity()
plot_local_connectivity()
