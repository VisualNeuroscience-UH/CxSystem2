"""cxconfig -- cxsystem config file converter

Usage:
  cxconfig (-h | --help)
  cxconfig  FILEPATH


A configuration file converter for `CxSystem`.

Arguments:
  FILENAME              Path to configuration file to convert

Options:
  -h --help             Show this screen

Description:

  cxconfig ./sample_conf.json
    converts the file `sample_conf.json` in current directory to csv and saves it as `sample_conf.csv`

  cxconfig ./sample_conf.csv
    converts the file `sample_conf.csv` in current directory to csv and saves it as `sample_conf.json`

"""

import sys
from pathlib import Path

from docopt import docopt

from cxsystem2.configuration.config_file_converter import ConfigConverter


def main():
    arguments = docopt(__doc__)
    # print(arguments)

    filepath = Path(arguments['FILEPATH'])
    if not filepath.is_file():
        print("Error: file {} not found".format(filepath.as_posix()))

    else:
        if filepath.suffix == '.json':
            converted = ConfigConverter(filepath)
            converted.save_as_csv()

        if filepath.suffix == '.csv':
            converted = ConfigConverter(filepath)
            converted.save_as_json()


if __name__ == '__main__':
    if len(sys.argv) == 1:
        sys.argv.append('-h')
    main()
