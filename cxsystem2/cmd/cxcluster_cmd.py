"""cxcluster -- cxsystem cluster result downloader

Usage:
  cxcluster (-h | --help)
  cxcluster META_FILE_PATH


Downloads result data of `CxSystem` from cluster.

Arguments:
  META_FILE_PATH            Path to cluster run metadata file

Options:
  -h --help                 Show this screen

Description:

  cxcluster ./sample_meta.pkl
    Uses the information in the  file to download the results if ready, and otherwise wait for the results.
    User will be prompted for the remote password.

"""

import argparse
import sys
from pathlib import Path

# Local
from cxsystem2.hpc.cluster_run import ClusterDownloader


def main():
    parser = argparse.ArgumentParser(
        description="cxcluster -- cxsystem cluster result downloader\n\n"
        "Downloads result data of `CxSystem` from cluster.\n"
        "User will be prompted for the remote password.",
        usage=""" cxcluster (-h | --help)
        cxcluster META_FILE_PATH""",
    )

    if len(sys.argv) == 1:
        parser.print_usage()
        sys.exit(1)

    parser.add_argument(
        "META_FILE_PATH", type=Path, help="Path to cluster run metadata file"
    )

    args = parser.parse_args()

    metadata_path = args.META_FILE_PATH

    if metadata_path.is_file():
        ClusterDownloader(metadata_path.as_posix())


if __name__ == "__main__":
    if len(sys.argv) == 1:
        sys.argv.append("-h")
    main()
