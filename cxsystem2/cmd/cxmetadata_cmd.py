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

import argparse
import sys
from pathlib import Path

import pandas as pd

# Local
from cxsystem2.core.tools import load_from_file

pd.set_option("display.max_columns", 30)
pd.set_option("display.max_colwidth", None)


def main():
    parser = argparse.ArgumentParser(
        description="Load and display metadata from a file.",
        usage=""" cxmetadata (-h | --help)
        cxmetadata META_FILE_PATH
        """,
    )

    if len(sys.argv) == 1:
        parser.print_usage()
        sys.exit(1)

    parser.add_argument("META_FILE_PATH", type=Path, help="Path to the metadata file")

    args = parser.parse_args()

    metadata_path = args.META_FILE_PATH

    if not metadata_path.is_file():
        print("Error: metadata file {} not found".format(metadata_path.as_posix()))
        sys.exit(1)

    metadata_df = load_from_file(metadata_path.as_posix())
    print(metadata_df)


if __name__ == "__main__":
    if len(sys.argv) == 1:
        sys.argv.append("-h")
    main()
