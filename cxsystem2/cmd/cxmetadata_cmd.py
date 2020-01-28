"""cxmetadata -- cxsystem metadata information viewer

Usage:
  cxmetadata (-h | --help)
  cxmetadata META_FILE_PATH


Shows information about an array_run metadata file

Arguments:
  META_FILE_PATH            Path to array run metadata file

Options:
  -h --help                 Show this screen

Description:

  cxcluster ./sample_meta.tar.gz
    shows the information inside `sample_meta.tar.gz`

"""


import sys
from pathlib import Path

from docopt import docopt
import pandas as pd
pd.set_option('display.max_columns', 30)
pd.set_option('display.max_colwidth', -1)
from pprint import pprint

from cxsystem2.core.tools import load_from_file


def main():
    arguments = docopt(__doc__)
    # print(arguments)

    metadata_path = Path(arguments['META_FILE_PATH'])
    if not metadata_path.is_file():
        print("Error: metadata file {} not found".format(metadata_path.as_posix()))
    else:
        metadata_df = load_from_file(metadata_path.as_posix())
        print(metadata_df)

if __name__ == '__main__':
    if len(sys.argv) == 1:
        sys.argv.append('-h')
    main()


