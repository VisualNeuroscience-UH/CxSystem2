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

import argparse
import sys
from pathlib import Path

# Local
from cxsystem2.configuration.config_file_converter import ConfigConverter


def main():
    parser = argparse.ArgumentParser(
        description="Convert configuration files between JSON and CSV formats.\n\n"
        "Converts the specified file to the opposite format (JSON <-> CSV).",
        usage=""" cxconfig (-h | --help)
        cxconfig  FILEPATH
        """,
    )

    if len(sys.argv) == 1:
        parser.print_usage()
        sys.exit(1)

    parser.add_argument(
        "FILEPATH",
        type=Path,
        help="Path to the KUKKUU configuration file (JSON or CSV)",
    )

    args = parser.parse_args()

    filepath = args.FILEPATH
    if not filepath.is_file():
        print(f"Error: file {filepath.as_posix()} not found")
        sys.exit(1)

    if filepath.suffix == ".json":
        converted = ConfigConverter(filepath)
        converted.save_as_csv()

    if filepath.suffix == ".csv":
        converted = ConfigConverter(filepath)
        converted.save_as_json()


if __name__ == "__main__":
    if len(sys.argv) == 1:
        sys.argv.append("-h")
    main()
