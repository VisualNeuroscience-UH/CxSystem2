from __future__ import division
import numpy as np
from matplotlib import pyplot
import seaborn as sns; sns.set()
import pandas as pd


class ChangeCalcium:
    """
    Change synaptic efficiency as a function of calcium concentration. Markram connections are grouped to three
    categories, steep, shallow and others, depending on how they change  synaptic efficiency as a function of external
    calcium concentration. The equation comes from Rozov_2001_JPhysiol. Check Markram cell 2015 suppl fig S11

    This class contains internal data from the Markram Cell 2015 paper:
        steep_group : connections between exc cells and DBC, BTC, MC,BP, and between 2 exc cells; K1/2 = 2.79
        shallow group : connections between exc cells and LBC, NBC, SBC, ChC; K1/2 = 1.09
        other connections : all other connections; K1/2  is the average of 2.79 and 1.09.

    This class has one method for changing the synapse strength:
    GetSynapseStrength  (original_synapse_strength (scalar without units), own_connection (string),Ca=2.0)

    Depends on pandas_playground/pathways_anatomy_preprocessed.json

    Author Simo Vanni 7/2016
    """

    def __init__(self):

        _excitatory_markram_groups = ['L23_PC','L4_PC','L4_SP','L4_SS','L5_STPC','L5_TTPC1','L5_TTPC2','L5_UTPC','L6_IPC',
                                      'L6_BPC', 'L6_TPC_L1','L6_TPC_L4','L6_UTPC']

        _steep_post_inhibitory_groups = ['L23_DBC','L4_DBC','L5_DBC','L6_DBC','L23_BTC','L4_BTC','L5_BTC','L6_BTC','L23_MC',
                                         'L4_MC','L5_MC','L6_MC','L23_BP','L4_BP','L5_BP','L6_BP']

        _shallow_post_inhibitory_groups = ['L23_LBC','L4_LBC','L5_LBC','L6_LBC','L23_NBC','L4_NBC','L5_NBC','L6_NBC','L23_SBC',
                                         'L4_SBC','L5_SBC','L6_SBC','L23_ChC','L4_ChC','L5_ChC','L6_ChC']

        self._excitatory_markram_groups = _excitatory_markram_groups

        self._synaptic_efficiency_dict = {
            'steep_post' : _excitatory_markram_groups + _steep_post_inhibitory_groups,
            'shallow_post' : _shallow_post_inhibitory_groups }

        file_pathways_anatomy_vannilized = 'pandas_playground/pathways_anatomy_preprocessed.json'  # OUTPUT FILE

        self._data = pd.read_json(file_pathways_anatomy_vannilized, orient='index')

    def GetSynapseStrength(self,original_synapse_strength, own_connection,Ca=2.0):
        # The original synapse strength (with no units) is assumed to represent the value at [Ca] = 2 mM
        # First map from own_connection (string) to markram connections. Next select DataFrame with markram_pre column =
        # _excitatory_markram_groups and markram_post column = either steep_post, shallow_post or other.
        #  These selections map to K12. Calculate the mean of K12 values. Finally calculate final_synapse_strength
        # for own connection and original synapse strength.

        data=self._data # shorten

        # Select data matching own connection
        markram_connections = data[data['vanni_index'] == own_connection]

        assert not markram_connections.empty, 'No matching connections, a typo or missing matching Markram connection'
        markram_pres = markram_connections['markram_pre']
        markram_posts = markram_connections['markram_post']

        if all(markram_pres.isin(self._excitatory_markram_groups)) and all(markram_posts.isin(self._synaptic_efficiency_dict['steep_post'])):
            K12 = 2.79
        elif all(markram_pres.isin(self._excitatory_markram_groups)) and all(markram_posts.isin(self._synaptic_efficiency_dict['shallow_post'])):
            K12 = 1.09
        else:
            K12 = np.average([2.79, 1.09])

        Ca0=2.0
        # Calculate final synapse strength
        final_synapse_strength =  original_synapse_strength * (np.power(Ca,4)/(np.power(K12,4) + np.power(Ca,4)))
        final_synapse_strength_at_Ca2 = original_synapse_strength * (np.power(Ca0, 4) / (np.power(K12, 4) + np.power(Ca0, 4)))

        relative_final_synapse_strength = final_synapse_strength / final_synapse_strength_at_Ca2

        # Return
        return Ca, final_synapse_strength, relative_final_synapse_strength


if __name__ == '__main__':

    # Testing
    Ca_obj= ChangeCalcium()
    Ca = np.arange(0.7, 5, 0.1)

    Ca, fss, rfss = Ca_obj.GetSynapseStrength(0.11e-9,'L23_PC:L23_BC',Ca)
    Ca2, fss2, rfss2 = Ca_obj.GetSynapseStrength(0.11e-9,'L23_PC:L23_PC',Ca)
    # Units are nano Siemens (nS), and range is 0.11 to 1.5 nS (Markram 2015 Cell, Figure 10)
    # Total conductance about 1 microS, 3/4 excitatory, 1/4 inhibitory

    # Testing
    pyplot.plot(Ca,rfss, color='blue', lw=2)
    pyplot.plot(Ca2, rfss2, color='red', lw=2)
    #pyplot.xscale('log')
    pyplot.yscale('log')
    pyplot.xlim([0.7, 5])
    pyplot.ylim([0.03, 10])
    pyplot.xlabel('$Ca^{2+}$ concentration (mM)')
    pyplot.ylabel('Relative synapse strength')
    pyplot.savefig('relative_strength.eps', dpi=600)