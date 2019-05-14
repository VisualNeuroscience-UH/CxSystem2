import pandas as pd
import seaborn as sns
import numpy as np
import matplotlib.pyplot as plt

vanni_local_connectivity_json = 'pathways_anatomy_cxsystem.json'
markram_physiology_json = 'pathways_physiology_factsheets_simplified.json'
preprocessed_markram_anatomy_json = 'pathways_anatomy_preprocessed.json'
plot_directory = 'plots/'

mycmap = 'jet'
sort_order = ['layer_pre', 'is_inhibitory_pre', 'celltype_pre', 'layer_post', 'is_inhibitory_post', 'celltype_post']


def plot_local_connectivity(vanni_json = vanni_local_connectivity_json):

    data = pd.read_json(vanni_json, orient='index')

    # Saving & reading messes with correct order! >.<
    data = data.sort_values(by=sort_order)
    correct_order = data.neurongroup_pre.unique()

    # Create 2D data
    plotdata = dict()

    plotdata['vanni_mean_synapses'] = data.pivot_table('mean_number_of_synapses_per_connection',
                                                       index='neurongroup_pre', columns='neurongroup_post',
                                                       aggfunc = sum)
    plotdata['vanni_conn_probability'] = data.pivot_table('connection_probability',
                                                          index='neurongroup_pre', columns='neurongroup_post',
                                                          aggfunc=sum)*100

    #plot_these = ['vanni_mean_synapses', 'vanni_conn_probability']
    plot_these = ['vanni_conn_probability']

    # Plot it
    plt.close() # In case something is open
    plotobj = dict()
    sns.set()

    for p in plot_these:
        # Pivoting messes (=alphabetizes) the order
        plotdata[p] = plotdata[p].reindex(index=correct_order, columns=correct_order)

        plotdata[p].index.name = 'Presynaptic neuron group'
        plotdata[p].columns.name = 'Postsynaptic neuron group'
        plotobj[p] = sns.heatmap(plotdata[p], cmap=mycmap, vmin=0, vmax=5.0)
        plt.tick_params(axis="both", labelsize=8)
        plt.setp(plotobj[p].get_xticklabels(), rotation=90)
        plt.setp(plotobj[p].get_yticklabels(), rotation=0)
        plt.title('Simplified neural network')
        cbar = plotobj[p].collections[0].colorbar
        cbar.set_label('Connection probability')
        plt.tight_layout()
        #plt.savefig(plot_directory + p + '.eps', dpi=600)
        plt.show()
        plt.close()

def plot_markram_connectivity(markram_json = preprocessed_markram_anatomy_json):

    data = pd.read_json(markram_json, orient='index')

    plotdata = data.pivot_table('connection_probability',
                                index='markram_pre', columns='markram_post',
                                aggfunc='sum')

    plotdata.index.name = 'Presynaptic neuron group'
    plotdata.columns.name = 'Postsynaptic neuron group'
    plotobj = sns.heatmap(plotdata, cmap=mycmap, vmin=0, vmax=30.0)
    plt.tick_params(axis="both", labelsize=6)
    plt.setp(plotobj.get_xticklabels(), rotation=90)
    plt.setp(plotobj.get_yticklabels(), rotation=0)
    plt.title('Reference neural network')
    cbar = plotobj.collections[0].colorbar
    cbar.set_label('Connection probability')
    plt.tight_layout()
    plt.savefig(plot_directory + 'markram_conn_prob' + '.eps', dpi=600)
    plt.close()




def plot_mean_epsp(markram_json = markram_physiology_json):

    mdata = pd.read_json(markram_json, orient='index')

    # PREPROCESS data to get correct ordering etc
    group_names = mdata.index.str.extract('(.*):(.*)', expand=True)
    group_names.index = mdata.index
    group_names.columns = ['pregroup', 'postgroup']

    layers = mdata.index.str.extract('(L\w{1,2})_(.*):(L\w{1,2})_(.*)', expand=True)
    layers.index = mdata.index
    layers.columns = ['prelayer', 'pretype', 'postlayer', 'posttype']

    mdata = mdata.join(group_names)
    mdata = mdata.join(layers)
    sort_order = ['prelayer', 'synapse_type', 'pretype',
                     'postlayer', 'synapse_type', 'posttype']
    mdata = mdata.sort_values(by=sort_order)
    markram_group_order = mdata.pregroup

    epsp_data = mdata.pivot_table('epsp_mean', index='pregroup', columns='postgroup')
    epsp_data.index.name = 'Presynaptic neuron group'
    epsp_data.columns.name = 'Postsynaptic neuron group'
    # TODO For some reason messes up the plot
    #epsp_data = epsp_data.reindex(index=markram_group_order, columns=markram_group_order)

    sns.set()
    epsp_plot = sns.heatmap(epsp_data, cmap=mycmap)

    plt.tick_params(axis="both", labelsize=6)
    plt.setp(epsp_plot.get_xticklabels(), rotation=90)
    plt.setp(epsp_plot.get_yticklabels(), rotation=0)
    plt.title('Reference microcircuit')
    plt.tight_layout()
    plt.savefig(plot_directory + 'markram_epsp_mean' + '.png', dpi=100)
    plt.close()


plot_local_connectivity('pathways_single_microcircuit.json')