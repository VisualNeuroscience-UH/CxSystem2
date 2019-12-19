from pathlib import Path

import brian2 as b2
import matplotlib
from matplotlib import pyplot as plt
from matplotlib.backends.backend_pdf import PdfPages

from cxsystem2.core.tools import load_from_file


class rasterplot_pdf_generator:
    def __init__(self, workspace_path, timestamp, sampling_rate):
        matplotlib.use('Agg')
        self.workspace_path = Path(workspace_path)
        self.timestamp = timestamp.strip('_')
        self.sampling_rate = float(sampling_rate[:-1])/100
        assert 0 < self.sampling_rate <= 1  , "sampling rate must be between 0 and 1"
        dir_file_list = self.workspace_path.glob('**/*')
        self.files = [x for x in dir_file_list if x.is_file() and timestamp in x.as_posix() and 'results' in x.as_posix()]
        self.out_filename = self.workspace_path.joinpath('plot_{}.pdf'.format(self.timestamp))
        self.generate_pdf()

    def generate_pdf(self):
        idx_in_fig = 0
        pdf_height = 12.69
        # pdf_height = 7.69
        pdf_width = 8.27
        # pdf_width = 4.27
        fig_x = 3
        fig_y = 2
        figs_per_page = fig_x * fig_y
        with PdfPages(self.out_filename.as_posix()) as pdf:
            f = plt.figure()
            f.set_figheight(pdf_height)
            f.set_figwidth(pdf_width)
            for file in self.files:
                print("Current file: {}".format(file))
                all_axes = []
                idx_in_fig = -1
                tmp_dat = load_from_file(file.as_posix())
                try:
                    spikes = tmp_dat['spikes_all']
                    for ng, spike_dat in spikes.items():
                        # print('Plotting group {}'.format(ng))
                        idx_in_fig += 1
                        if idx_in_fig >= figs_per_page :
                            all_axes = []
                            plt.tight_layout()
                            plt.text(0.05, -0.05, file.as_posix(), transform=f.transFigure, size=24)
                            pdf.savefig(f)
                            f = plt.figure()
                            f.set_figheight(pdf_height)
                            f.set_figwidth(pdf_width)
                            idx_in_fig = 0

                        all_axes.append(plt.subplot2grid((fig_x,fig_y),(idx_in_fig // fig_y, idx_in_fig % fig_y)))
                        all_axes[-1].set_title(ng)
                        all_axes[-1].set_xlabel('Time (ms)')
                        all_axes[-1].set_ylabel('Neuron index')
                        step = int((1 // self.sampling_rate) + 1)
                        s = spike_dat['t']/b2.units.ms
                        t = spike_dat['i']
                        all_axes[-1].plot(s[::step], t[::step],'.k',markersize=1)
                    if idx_in_fig > 0:
                        plt.tight_layout()
                        plt.text(0.4, 0.01, file.name, transform=f.transFigure, size=8, weight="bold")
                        pdf.savefig(f)
                except KeyError:
                    print("The file '{}' is not a brian data file, skipping ...".format(file.name))

    def get_output_file_path(self):
        return self.out_filename.as_posix()

if __name__ == '__main__':
    viz = rasterplot_pdf_generator('/Users/vafandal/CxWorkspace/step2', '20191125_1713122', '1%')
