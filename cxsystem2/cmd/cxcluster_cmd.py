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
    Uses the information in the metadata file to download the results if ready, and otherwise wait for the results. 
    User will be prompted for the remote password. 

"""

import sys
from pathlib import Path

from docopt import docopt

from cxsystem2.hpc.cluster_run import ClusterDownloader


def main():
    arguments = docopt(__doc__)
    # print(arguments)

    metadata_path = Path(arguments['META_FILE_PATH'])
    if not metadata_path.is_file():
        print("Error: metadata file {} not found".format(metadata_path.as_posix()))
    else:
        ClusterDownloader(metadata_path.as_posix())


if __name__ == '__main__':
    if len(sys.argv) == 1:
        sys.argv.append('-h')
    main()
