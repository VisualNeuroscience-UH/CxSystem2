import matplotlib.pyplot as plt
import numpy as np
import pickle as pickle
import zlib
import os
import bz2

def data_loader(path):
    if '.gz' in path:
        with open(path, 'rb') as fb:
            data = zlib.decompress(fb.read())
            loaded_data = pickle.loads(data)
    elif '.bz2' in path:
        with bz2.BZ2File(path, 'rb') as fb:
            loaded_data = pickle.load(fb)
    elif 'pickle' in path:
        with open(path, 'rb') as fb:
            loaded_data = pickle.load(fb)
    return loaded_data

path = '/opt3/CxOutput'
FileName = 'CxOutput_20161130_10421270_calcium_concentration3.0_GeNN_100ms.gz'
ThisTrial = data_loader(os.path.join(path,FileName))

# SS = ThisTrial['spikes_all'][ 'NG7_SS_L4']
# PC = ThisTrial['spikes_all'][ 'NG5_PC_L4toL2']
# PC6 = ThisTrial['spikes_all']['NG14_PC_L6toL1']
# PC64 = ThisTrial['spikes_all']['NG13_PC_L6toL4']
#
# PC5 = ThisTrial['spikes_all']['NG10_PC_L5toL1']
# BC = ThisTrial['spikes_all'][ 'NG3_BC_L2']
# MC = ThisTrial['spikes_all'][ 'NG9_MC_L4']

for pltkey in ThisTrial['spikes_all'].keys():
    plt.figure();plt.scatter(ThisTrial['spikes_all'][pltkey ][1],ThisTrial['spikes_all'][pltkey ][0],s=0.3);plt.title(pltkey)
# plt.figure();plt.scatter(PC[1],PC[0],s=0.4);plt.title('PC4-2 Noise 40mV')
# plt.figure();plt.scatter(BC[1],BC[0],s=0.4);plt.title('BC Noise 5mV')
# plt.figure();plt.scatter(PC6[1],PC6[0],s=0.4);plt.title('PC6-1 Noise 40mV')
# plt.figure();plt.scatter(PC64[1],PC64[0],s=0.4);plt.title('PC6-4 Noise 40mV')
# plt.figure();plt.scatter(PC5[1],PC5[0],s=0.4);plt.title('PC5 Noise 40mV')
# SSV = ThisTrial['vm_all'][ 'NG7_SS_L4']
# PCV = ThisTrial['vm_all'][ 'NG10_PC_L5toL1']
# BCV = ThisTrial['vm_all'][ 'NG3_BC_L2']
# plt.figure();[plt.plot(BCV[i]) for i in range(1,50)];plt.title('BC, noise ??')
# plt.figure();[plt.plot(PCV[i]) for i in range(1,50)];plt.title('PC, noise ??')
plt.show()