import bz2
import pickle as pickle
import zlib
from pathlib import Path

import brian2 as b2
from matplotlib import pyplot as plt
from matplotlib.backends.backend_pdf import PdfPages


class arrayrun_visualizer:
    def __init__(self, folder_path, out_filename = None):
        self.arrayrun_folder = Path(folder_path)
        dir_file_list = self.arrayrun_folder.glob('**/*')
        self.files = [x for x in dir_file_list if x.is_file()]
        if out_filename is None:
            self.out_filename = self.arrayrun_folder.joinpath('arrayrun_plot.pdf')
        else:
            self.out_filename = Path(out_filename)
        self.generate_pdf()

    def generate_pdf(self):
        idx_in_fig = 0
        pdf_height = 12.69
        pdf_width = 8.27
        fig_x = 3
        fig_y = 2
        figs_per_page = fig_x * fig_y
        with PdfPages(self.out_filename) as pdf:
            f = plt.figure()
            f.set_figheight(pdf_height)
            f.set_figwidth(pdf_width)
            for file in self.files:
                all_axes = []
                idx_in_fig = -1
                tmp_dat = self.data_loader(file.as_posix())
                try:
                    spikes = tmp_dat['spikes_all']
                    for ng, spike_dat in spikes.items():
                        idx_in_fig += 1
                        if idx_in_fig > figs_per_page :
                            all_axes = []
                            plt.tight_layout()
                            plt.text(0.05, -0.05, file.as_posix(), transform=f.transFigure, size=24)
                            pdf.savefig(f)
                            f = plt.figure()
                            f.set_figheight(pdf_height)
                            f.set_figwidth(pdf_width)
                            idx_in_fig = -1

                        all_axes.append(plt.subplot2grid((fig_x,fig_y),(idx_in_fig // fig_y, idx_in_fig % fig_y)))
                        all_axes[-1].set_title(ng)
                        all_axes[-1].set_xlabel('Time (ms)')
                        all_axes[-1].set_ylabel('Neuron index')
                        all_axes[-1].plot(spike_dat['t']/b2.units.ms, spike_dat['i'],'.k')
                    if idx_in_fig > 0:
                        plt.tight_layout()
                        plt.text(0.05, 0.05, file.as_posix(), transform=f.transFigure, size=8)
                        pdf.savefig(f)
                except KeyError:
                    print("The file '{}' is not a brian data file, skipping ...".format(file.name))

    def data_loader(self, input_path):
        if '.gz' in input_path:
            with open(input_path, 'rb') as fb:
                data = zlib.decompress(fb.read())
                loaded_data = pickle.loads(data)
        elif '.bz2' in input_path:
            with bz2.BZ2File(input_path, 'rb') as fb:
                loaded_data = pickle.load(fb)
        elif 'pickle' in input_path:
            with open(input_path, 'rb') as fb:
                loaded_data = pickle.load(fb)
        else:
            loaded_data = {}
        return loaded_data



if __name__ == '__main__':
    viz = arrayrun_visualizer('/Users/vafandal/gitrepos/CxSystem2/sim_results')
