"""cxvisualize -- cxsystem visualizer

Usage:
  cxvisualize (-h | --help)
  cxvisualize  FILEPATH


A tool for visualizing `CxSystem` spike data in ViSimpl.

Arguments:
  FILENAME    Path to results file

Options:
  -h --help     Show this screen
  --convert     Convert results for use in ViSimpl TODO
  --delete      Delete ViSimpl-related files after visualization TODO

Description:

  cxvisualize ./results.gz

    converts the results file into two CSVs and one JSON for ViSimpl
    (actual visualization: ./visimpl -csv results_structure.csv results_spikes.csv -se results_subsets.json)

"""


from docopt import docopt
from cxsystem2.visualization.spikedata_to_csvs import SpikeData
import sys
from pathlib import Path
import os

VISIMPL_BINARY = '~/visimpl/visimpl.AppImage'  # TODO - This is probably not the right place for this

def _convert(filepath):
    x = SpikeData(filepath)
    structure_csv, spikes_csv, subsets_json = x.save_for_visimpl()
    return structure_csv, spikes_csv, subsets_json

def _run_visimpl(structure_csv, spikes_csv, subsets_json):
    run_visimpl_cmd = VISIMPL_BINARY + ' -csv ' + str(structure_csv) + ' ' + str(spikes_csv) + ' -se ' + str(subsets_json)
    os.system(run_visimpl_cmd)

def main():
    arguments = docopt(__doc__)
    # print(arguments)

    filepath = Path(arguments['FILEPATH'])
    if not filepath.is_file():
        print("Error: file {} not found".format(filepath.as_posix()))

    else:
        structure_csv, spikes_csv, subsets_json = _convert(filepath)
        _run_visimpl(structure_csv, spikes_csv, subsets_json)
        os.remove(structure_csv)
        os.remove(spikes_csv)
        os.remove(subsets_json)


if __name__ == '__main__':
    if len(sys.argv) == 1:
        sys.argv.append('-h')
    main()