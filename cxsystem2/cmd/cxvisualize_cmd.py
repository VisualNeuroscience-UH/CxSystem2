"""cxvisualize -- cxsystem visualizer

Usage:
  cxvisualize (-h | --help)
  cxvisualize  [ -d | -c ] FILEPATH
  cxvisualize --rasterplot-pdf FOLDERPATH TIMESTAMP [--sampling-rate SAMPLINGRATE]

A tool for visualizing `CxSystem` spike data in ViSimpl.

Arguments:
  FILENAME                                          Path to results file
  FOLDERPATH                                        Path to folder containing array run files
  TIMESTAMP                                         Timestamp suffix of the arrayrun files
  SAMPLINGRATE                                      Sampling rate for the rasterplots

Options:
  -h --help                                         Show this screen
  --rasterplot-pdf                                  Generate a rasterplot pdf for arrayrun
  -c --convert                                      Convert results for use in ViSimpl
  -d --delete                                       Delete ViSimpl-related files after visualization
  -s SAMPLINGRATE --sampling-rate=SAMPLINGRATE      Sampling rate for raster plot (default is 1%)

Description:

  cxvisualize ./results.gz
    converts the results file into two CSVs and one JSON for ViSimpl, visualizes the result and does not remove the temp files
    (actual visualization: ./visimpl -csv results_structure.csv results_spikes.csv -se results_subsets.json)

  cxvisualize -d ./results.gz
    converts the results file into two CSVs and one JSON for ViSimpl, visualizes the result and remove the temp files

  cxvisualize -c ./results.gz
    converts the results file into two CSVs and one JSON for ViSimpl (no visualization)

  cxvisualize --rasterplot-pdf ./cobaeif 20191123_1353509
    Generates a pdf of rasterplots of all groups in the folder with 20191123_1353509 timestamp with default sampling rate of 1%

  cxvisualize --rasterplot-pdf ./cobaeif 20191123_1353509 --sampling-rate=4%
    Generates a pdf of rasterplots of all groups in the folder with timestamp 20191123_1353509 and sampling rate or 4%

"""

import os
import sys
from pathlib import Path
from shutil import which

from docopt import docopt

from cxsystem2.visualization.spikedata_to_csvs import SpikeData
from cxsystem2.visualization.rasterplot_to_pdf import rasterplot_pdf_generator


VISIMPL_BINARY = ''
def check_visimpl():
    global VISIMPL_BINARY
    if which("visimpl.AppImage") is None:
        VISIMPL_BINARY = '~/visimpl/visimpl.AppImage'
        if not Path(VISIMPL_BINARY).is_file():
            raise FileNotFoundError("ViSimpl binary not found ")
    else:
        VISIMPL_BINARY = 'visimpl.AppImage'  # ViSimpl is already in path


def _convert(filepath):
    x = SpikeData(filepath)
    structure_csv, spikes_csv, subsets_json = x.save_for_visimpl()
    return structure_csv, spikes_csv, subsets_json


def _run_visimpl(structure_csv,
                 spikes_csv,
                 subsets_json):
    run_visimpl_cmd = VISIMPL_BINARY + ' -csv ' + str(structure_csv) + ' ' + str(spikes_csv) + ' -se ' + str(subsets_json)
    os.system(run_visimpl_cmd)


def main():
    arguments = docopt(__doc__)
    # print(arguments)

    if arguments['--rasterplot-pdf']:
        folder_path = Path(arguments['FOLDERPATH'])
        if not folder_path.is_dir():
            print("arrayrun folder not found. Make sure the path is correct.")
            return
        timestamp = arguments['TIMESTAMP'].strip('_')
        dir_file_list = folder_path.glob('**/*')
        files = [x for x in dir_file_list if x.is_file() and timestamp in x.as_posix() and 'results' in x.as_posix()]
        if len(files) == 0:
            print("arrayrun folder does not contain files with that timestamp.")
            return
        sampling_rate = '1%'
        if arguments['--sampling-rate']:
            try:
                if arguments['--sampling-rate'].count('%') != 1 or \
                    float(arguments['--sampling-rate'][:-1]) > 100 or \
                    float(arguments['--sampling-rate'][:-1]) <= 0 :
                    print ("Sampling rate not valid. It should be number greater than 0% and less than or equal to 100%")
                    return
            except ValueError:
                print("Sampling rate not valid. It should be number greater than 0% and less than or equal to 100%")
                return
            sampling_rate = arguments['--sampling-rate']
        rasterplot_pdf_generator(folder_path, timestamp, sampling_rate)
    else:
        check_visimpl()
        filepath = Path(arguments['FILEPATH'])
        if not filepath.is_file():
            print("Error: file {} not found".format(filepath.as_posix()))

        else:
            structure_csv, spikes_csv, subsets_json = _convert(filepath)
            if not arguments['--convert']:
                _run_visimpl(structure_csv, spikes_csv, subsets_json)
            if arguments['--delete']:
                os.remove(structure_csv)
                os.remove(spikes_csv)
                os.remove(subsets_json)


if __name__ == '__main__':
    if len(sys.argv) == 1:
        sys.argv.append('-h')
    main()
