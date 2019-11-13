"""cxcluster -- cxsystem cluster result downloader

Usage:
  cxcluster (-h | --help)
  cxcluster META_FILE_PATH


Cluster result downlaoder for `CxSystem`. 

Arguments:
  META_FILE_PATH    Path to cluster run metadata file  

Options:
  -h --help     Show this screen

Description:

  cxcluster ./sample_meta.pkl

    Uses the information in the metadata file to download the results if ready, and otherwise wait for the results. 
    User will be prompted for the remote password. 

"""


from docopt import docopt
from cxsystem2.hpc.cluster_run import cluster_downlaoder
import sys
from pathlib import Path

def main():
    arguments = docopt(__doc__)
    # print(arguments)

    metapath = Path(arguments['META_FILE_PATH'])
    if not metapath.is_file():
        print("Error: metada file {} not found".format(metapath.as_posix()))
    else:
        cluster_downlaoder(metapath.as_posix())

if __name__=='__main__':
    if len(sys.argv) == 1:
        sys.argv.append('-h')
    main()
