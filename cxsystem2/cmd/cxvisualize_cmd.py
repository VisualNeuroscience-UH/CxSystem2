"""cxvisualize -- cxsystem visualizer

Usage:
  cxvisualize (-h | --help)
  cxvisualize  [ -d | -c ] FILEPATH
  cxvisualize --array-run FOLDERPATH TIMESTAMP [-s SAMPLINGRATE]

A tool for visualizing `CxSystem` spike data in ViSimpl.

Arguments:
  FILENAME      Path to results file
  FOLDERPATH    Path to folder containing array run files
  TIMESTAMP     Timestamp suffix of the arrayrun files
  SAMPLINGRATE  Sampling rate for the rasterplots

Options:
  -h --help         Show this screen
  --array-run       Generate a rasterplot pdf for arrayrun
  -c --convert      Convert results for use in ViSimpl
  -d --delete       Delete ViSimpl-related files after visualization
  -s                Sampling rate for raster plot (default is 0.05)

Description:

  cxvisualize ./results.gz
    converts the results file into two CSVs and one JSON for ViSimpl, visualizes the result and does not remove the temp files
    (actual visualization: ./visimpl -csv results_structure.csv results_spikes.csv -se results_subsets.json)

  cxvisualize -d ./results.gz
    converts the results file into two CSVs and one JSON for ViSimpl, visualizes the result and remove the temp files

  cxvisualize -c ./results.gz
    converts the results file into two CSVs and one JSON for ViSimpl (no visualization)

  cxvisualize --array-run ./cobaeif 20191123_1353509
    Generates a pdf of rasterplots of all groups in the array run

"""

import os
import sys
from pathlib import Path
from shutil import which

from docopt import docopt

from cxsystem2.visualization.spikedata_to_csvs import SpikeData
from cxsystem2.visualization.arrayrun_visualizer import arrayrun_visualizer


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
    run_visimpl_cmd = VISIMPL_BINARY + ' -csv ' + str(structure_csv) + ' ' + str(spikes_csv) + ' -se ' + str(
        subsets_json)
    os.system(run_visimpl_cmd)


def main():
    arguments = docopt(__doc__)
    # print(arguments)

    if arguments['--array-run']:
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
        sampling_rate = 0.05
        if arguments['SAMPLINGRATE']:
            if float(arguments['SAMPLINGRATE']) > 1 or float(arguments['SAMPLINGRATE']) <= 0 :
                print ("Sampling rate must be between 0 and 1")
                return
            sampling_rate = float(arguments['SAMPLINGRATE'])
        arrayrun_visualizer(folder_path, timestamp, sampling_rate)
    else:
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
