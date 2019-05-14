import numpy as np
import matplotlib
# matplotlib.use('Agg')
import os
import scipy.io as spio
import scipy.stats as st
from tabulate import tabulate
import matplotlib.pyplot as plt
import _pickle as pickle
import zlib
import bz2



class illustrator:
    def __init__(self, mode,CXOutputPath,FilePattern,IllustratorOutputFile,InputTime,latency_threshold):
        self.mode = mode
        assert mode in ['saving','loading'], 'Mode should be set as either saving or loading.'
        self.CXOutputPath = CXOutputPath
        self.FilePattern = FilePattern
        # self.PlotType = PlotType
        self.IllustratorOutputFile = IllustratorOutputFile
        self.IllustratorOutputFolder = os.path.dirname(self.IllustratorOutputFile)
        if mode == 'saving':
            self.final_data = {}
            self.final_data['LatencyThreshold'] = latency_threshold
            self.final_data['FileList'] = [fil for fil in os.listdir(self.CXOutputPath) if self.FilePattern in fil]
            # self.final_data['runtime'] = self.loadmat(os.path.join(self.CXOutputPath, self.final_data['FileList'][0]))['runtime']
            dict_ = self.data_loader(os.path.join(self.CXOutputPath, self.final_data['FileList'][0]))
            self.final_data['runtime'] = dict_['runtime']
            self.final_data['NeuronGroupList'] = [GroupName for GroupName in dict_['spikes_all'].keys() if not 'vpm' in GroupName]
            self.final_data['SortedGroupsList'] = []
            layers = np.unique([group[group.index('L') + 1] for group in self.final_data['NeuronGroupList']])
            for layer in layers:
                tmp_groups = [group for group in self.final_data['NeuronGroupList'] if group[group.index('L') + 1] == layer]
                if len(tmp_groups) > 1:
                    SSs = [sub_group for sub_group in tmp_groups if 'SS' in sub_group]
                    PCs = sorted([sub_group for sub_group in tmp_groups if 'PC' in sub_group],
                                 key=lambda x: sub_group[-1])
                    BCs = [sub_group for sub_group in tmp_groups if 'BC' in sub_group]
                    MCs = [sub_group for sub_group in tmp_groups if 'MC' in sub_group]

                    if PCs:
                        self.final_data['SortedGroupsList'].extend(PCs)
                    if SSs:
                        self.final_data['SortedGroupsList'].extend(SSs)
                    if BCs:
                        self.final_data['SortedGroupsList'].extend(BCs)
                    if MCs:
                        self.final_data['SortedGroupsList'].extend(MCs)
                else:
                    self.final_data['SortedGroupsList'].extend(tmp_groups)
            self.final_data['InputTime'] = InputTime
            print("Building up data for plots")
            self.final_data['GroupsSpikes'] = {}

            for Group in self.final_data['SortedGroupsList'] :
                self.final_data['GroupsSpikes'][Group] = []
                # if not os.path.isfile(os.path.join(self.CXOutputPath,'SpikesToPlot.mat')):
            # TmpTrial = self.loadmat(os.path.join(self.CXOutputPath, self.final_data['FileList'][0]))

            # Open gz files
            TmpTrial = self.data_loader(os.path.join(self.CXOutputPath, self.final_data['FileList'][0]))
            self.final_data['CellIndex'] = {}
            for Group in self.final_data['SortedGroupsList'] :
                self.final_data['CellIndex'][Group] = int(np.where(abs(np.array(TmpTrial['positions_all']['w_coord'][Group])) == min(abs(np.array(TmpTrial['positions_all']['w_coord'][Group]))))[0][0])
            self.final_data['GroupDelays'] = {}
            for Group in self.final_data['SortedGroupsList']:
                self.final_data['GroupDelays'][Group] = {}
            for idx, FileName in enumerate(self.final_data['FileList']):
                # ThisTrial = self.loadmat(os.path.join(self.CXOutputPath, FileName))
                ThisTrial = self.data_loader(os.path.join(self.CXOutputPath, FileName))
                for Group in self.final_data['SortedGroupsList'] :
                    try:
                        SpikeTimeIndices = np.where(ThisTrial['spikes_all'][Group][0] == self.final_data['CellIndex'][Group])
                        SpikeTimes = ThisTrial['spikes_all'][Group][1][SpikeTimeIndices]
                    except IndexError:
                        SpikeTimes = np.array([])
                    self.final_data['GroupsSpikes'][Group].append(SpikeTimes)
                    if len(ThisTrial['spikes_all'][Group]) > 0:
                        temp_tuple = [(tmp_idx, t - self.final_data['InputTime']) for tmp_idx, t in
                                      enumerate(ThisTrial['spikes_all'][Group][1]) if (t - self.final_data['InputTime'] > 0 \
                                                                                       and t - self.final_data['InputTime'] < self.final_data['LatencyThreshold'])]
                        if temp_tuple:
                            WithinThreshIdx = [row[0] for row in temp_tuple]
                            latency = [row[1] for row in temp_tuple]
                            NeuronsIdx = ThisTrial['spikes_all'][Group][0][WithinThreshIdx]
                            uniqued_NeuronIdx = []
                            uniqued_latency = []
                            for neuron_tpm in np.unique(NeuronsIdx):
                                repeated_indices = np.where(NeuronsIdx == neuron_tpm)[0]
                                if len(repeated_indices > 1):
                                    tmp_out = [(ind_, latency[ind_]) for ind_ in repeated_indices]
                                    idx_of_min = [xx[0] for xx in tmp_out][0]
                                    lat_min = [xx[1] for xx in tmp_out][0]
                                    uniqued_NeuronIdx.append(idx_of_min)
                                    uniqued_latency.append(lat_min)
                                else:
                                    uniqued_NeuronIdx.append(repeated_indices[0])
                                    uniqued_latency.append(latency[repeated_indices[0]])
                            for itemidx, Neuron in enumerate(uniqued_NeuronIdx):
                                Neuron = int(Neuron)
                                if not Neuron in self.final_data['GroupDelays'][Group]:
                                    self.final_data['GroupDelays'][Group][Neuron] = []
                                self.final_data['GroupDelays'][Group][Neuron].append(uniqued_latency[itemidx])
                    print('\r%d out of %d file finished.' % (idx + 1,
                    len(self.final_data['FileList'])))

            for group in self.final_data['GroupDelays'].keys():
                for neuron in self.final_data['GroupDelays'][group].keys():
                    self.final_data['GroupDelays'][group][neuron] = np.mean(self.final_data['GroupDelays'][group][neuron])
            self.final_data['box_data'] = []
            self.final_data['box_labels'] = []
            for group in self.final_data['SortedGroupsList'][::-1]:
                tmp_latencies = [self.final_data['GroupDelays'][group][key] for key in self.final_data['GroupDelays'][group].keys()]
                if tmp_latencies:
                    self.final_data['box_labels'].append(group[group.index('_') + 1:])
                    self.final_data['box_data'].append(np.array([self.final_data['GroupDelays'][group][key] for key in
                                                self.final_data['GroupDelays'][group].keys()]))
            if not os.path.isdir(self.IllustratorOutputFolder):
                os.mkdir(self.IllustratorOutputFolder)
            self.data_saver(self.IllustratorOutputFile,self.final_data)

        elif mode == 'loading':
            self.final_data = self.data_loader(IllustratorOutputFile)

    def Responses(self,PlotStartTime,PlotEndTime,DoSkip=[]):
        NotSkippedGroups = [G for G in self.final_data['SortedGroupsList'] if not any(ext in G for ext in DoSkip)]
        # spio.savemat(os.path.join(self.CXOutputPath,'SpikesToPlot.mat'),GroupsSpikes)
        # else:
        #     GroupsSpikes = self.loadmat(os.path.join(self.CXOutputPath,'SpikesToPlot.mat'))

        f, axarr = plt.subplots(int(round(len(NotSkippedGroups)/2.)), 2, sharex=True, figsize=(8, 17))
        axarr_twins = [col.twinx() for row in axarr for col in row]
        axarr_twins = np.reshape(axarr_twins, (int(round(len(NotSkippedGroups)/2.)), 2))
        PSTH_bin = 0.005
        statistics = []
        for idx, Group in enumerate(NotSkippedGroups):
            plt_y_idx = idx % (int(round(len(NotSkippedGroups)/2.)))
            plt_x_idx = int(idx / (int(round(len(NotSkippedGroups)/2.))))
            Scatter_Xs = np.concatenate(self.final_data['GroupsSpikes'][Group])
            Scatter_Ys = np.concatenate(
                [(np.ones(len(TimePoint)) * (int(TimePoint_idx) + 1)).astype(int) for TimePoint_idx, TimePoint in
                 enumerate(self.final_data['GroupsSpikes'][Group])])
            axarr[plt_y_idx, plt_x_idx].scatter(Scatter_Xs, Scatter_Ys, s=1, color='0.5')
            Step_Xs = np.arange(0, self.final_data['runtime'], PSTH_bin)
            Step_Ys = np.zeros_like(Step_Xs)
            for X in np.unique(Scatter_Xs):
                bin_idx = np.where(Step_Xs == min(Step_Xs, key=lambda x: abs(x - X)))
                Step_Ys[bin_idx] += len(np.where(Scatter_Xs == X)[0])
            axarr_twins[plt_y_idx, plt_x_idx].step(Step_Xs, Step_Ys, where='mid', c='b')
            axarr[plt_y_idx, plt_x_idx].plot([self.final_data['InputTime'], self.final_data['InputTime']], [0, len(self.final_data['FileList'])], color='r', linestyle='dotted',
                                             linewidth=2)
            axarr[plt_y_idx, plt_x_idx].spines['top'].set_color('none')
            axarr_twins[plt_y_idx, plt_x_idx].spines['top'].set_color('none')
            axarr[plt_y_idx, plt_x_idx].xaxis.set_ticks_position('bottom')
            axarr_twins[plt_y_idx, plt_x_idx].xaxis.set_ticks_position('bottom')
            axarr[plt_y_idx, plt_x_idx].set_ylim(0, len(self.final_data['FileList']))
            CurrentTitle = Group[Group.index('_') + 1:].replace('_L',' Layer ').replace('toL',' to Layer ')
            axarr[plt_y_idx, plt_x_idx].set_title(CurrentTitle)
            axarr[plt_y_idx, plt_x_idx].set_xlim(PlotStartTime, PlotEndTime)
            axarr_twins[plt_y_idx, plt_x_idx].set_xlim(PlotStartTime, PlotEndTime)
            if max(Step_Ys[int(np.where(np.array(Step_Xs)>=PlotStartTime)[0][0]):int(np.where(np.array(Step_Xs)<=PlotEndTime)[0][-1])]) == 0:
                axarr_twins[plt_y_idx, plt_x_idx].set_ylim(0, 1)
            else:
                axarr_twins[plt_y_idx, plt_x_idx].set_ylim(0, max(Step_Ys[int(np.where(np.array(Step_Xs)>=PlotStartTime)[0][0]):int(np.where(np.array(Step_Xs)<=PlotEndTime)[0][-1])]) )
            y_lower,y_upper = axarr_twins[plt_y_idx, plt_x_idx].get_ylim()
            if y_upper > 5 :
                axarr_twins[plt_y_idx, plt_x_idx].yaxis.set_ticks(np.arange(int(y_lower), int(y_upper)+1, (int(y_upper) - int(y_lower)) / 5))
            else:
                axarr_twins[plt_y_idx, plt_x_idx].yaxis.set_ticks(np.arange(int(y_lower), int(y_upper)+1))
            if plt_x_idx == 0 :
                axarr[plt_y_idx, plt_x_idx].set_ylabel('Trials')
            cropped_steps = Step_Ys[int(np.where(np.array(Step_Xs) >= PlotStartTime)[0][0]):int(np.where(np.array(Step_Xs) <= PlotEndTime)[0][-1])]
            statistics.append([CurrentTitle,st.chisquare(cropped_steps)[0],st.chisquare(cropped_steps)[1]])
        axarr[-1,0].set_xlabel('time (s)')
        axarr[-1,1].set_xlabel('time (s)')
        plt.locator_params(axis='x', nbins=5)
        plt.tight_layout()
        plt.show()
        f.savefig(os.path.join(self.IllustratorOutputFolder,'cell_type_response.eps'))
        with open (os.path.join(self.IllustratorOutputFolder,'table.txt'),'w') as table_file:
            table_file.write(tabulate(statistics,headers=['Group Name','Chi-Square','p-Value']))

    def ResponseLatency(self):
        inhib = ['L1i','BC','MC']
        exci = ['PC','SS']
        fig, axes = plt.subplots(1, 1)
        boxes = axes.boxplot(np.array(self.final_data['box_data']), 0, 'r', 0, labels=self.final_data['box_labels'])
        axes.set_xlim(0-0.001,axes.get_xlim()[1] + 0.002)
        axes.set_xticklabels((axes.get_xticks() * 1000).astype(str))
        for _idx , lab in enumerate(axes.get_ymajorticklabels()):
            label = lab.get_text()
            if any([it in str(label) for it in exci]):
                boxes['boxes'][_idx].set_color('red')
                boxes['fliers'][_idx].set_color('red')
                boxes['fliers'][_idx].set_markeredgecolor('red')
                boxes['medians'][_idx].set_color('red')
                boxes['whiskers'][_idx*2].set_color('red')
                boxes['whiskers'][_idx * 2 + 1].set_color('red')
                boxes['caps'][_idx * 2].set_color('red')
                boxes['caps'][_idx * 2 + 1].set_color('red')
            elif any([it in str(label) for it in inhib]):
                boxes['boxes'][_idx].set_color('blue')
                boxes['fliers'][_idx].set_color('blue')
                boxes['fliers'][_idx].set_markeredgecolor('blue')
                boxes['medians'][_idx].set_color('blue')
                boxes['whiskers'][_idx * 2].set_color('blue')
                boxes['whiskers'][_idx * 2 + 1].set_color('blue')
                boxes['caps'][_idx * 2].set_color('blue')
                boxes['caps'][_idx * 2 + 1].set_color('blue')
        plt.show()
        axes.set_title('Default', fontsize=10)
        fig.savefig(os.path.join(self.IllustratorOutputFolder, 'cell_type_response_delay.eps'))

    def data_loader(self,path):
        if '.gz' in path:
            with open(path, 'rb') as fb:
                data = zlib.decompress(fb.read())
                loaded_data = pickle.loads(data)
        elif '.bz2' in path:
            with bz2.BZ2File(path, 'rb') as fb:
                loaded_data = pickle.load(fb)
        elif 'pickle' in path:
            with open(path, 'rb') as fb:
                loaded_data= pickle.load(fb)
        return loaded_data

    def data_saver(self,save_path,data):
        if '.gz' in save_path:
            with open(save_path, 'wb') as fb:
                fb.write(zlib.compress(pickle.dumps(data, pickle.HIGHEST_PROTOCOL), 9))
        elif '.bz2' in save_path:
            with bz2.BZ2File(save_path, 'wb') as fb:
                pickle.dump(data, fb, pickle.HIGHEST_PROTOCOL)
        elif '.pickle' in save_path:
            with open(save_path, 'wb') as fb:
                pickle.dump(data, fb, pickle.HIGHEST_PROTOCOL)

if __name__ == '__main__':
    illus = illustrator(mode='saving',CXOutputPath='/opt3/Noise_Test/',FilePattern='CxOutput_',
                        IllustratorOutputFile='/opt3/CxOutput/Outputs/Illustrator_Output/Illus_out.gz',InputTime=0.5,latency_threshold=0.03)
    illus.Responses(PlotStartTime=0.46,PlotEndTime=0.56,DoSkip=['PC_L6toL1','PC_L6toL4'])
    illus.ResponseLatency()
    # rossert_fig9C = illustrator('/opt3/CxOutput/Ouputs', 'Gain-EE1EI1', 'cell_type_response_latency',InputTime=0.5)
