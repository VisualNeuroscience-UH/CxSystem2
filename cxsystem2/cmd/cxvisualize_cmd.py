"""cxvisualize -- cxsystem visualizer

Usage:
  cxvisualize (-h | --help)
  cxvisualize  [ -d | -c ] FILEPATH


A tool for visualizing `CxSystem` spike data in ViSimpl.

Arguments:
  FILENAME    Path to results file

Options:
  -h --help     Show this screen
  -c --convert     Convert results for use in ViSimpl
  -d --delete      Delete ViSimpl-related files after visualization

Description:

  cxvisualize ./results.gz

    converts the results file into two CSVs and one JSON for ViSimpl, visualizes the result and does not remove the temp files
    (actual visualization: ./visimpl -csv results_structure.csv results_spikes.csv -se results_subsets.json)

  cxvisualize -d ./results.gz

    converts the results file into two CSVs and one JSON for ViSimpl, visualizes the result and remove the temp files

  cxvisualize -c ./results.gz

    converts the results file into two CSVs and one JSON for ViSimpl (no visualization)

"""

import os
import sys
from pathlib import Path
from shutil import which

from docopt import docopt

from cxsystem2.visualization.spikedata_to_csvs import SpikeData

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
