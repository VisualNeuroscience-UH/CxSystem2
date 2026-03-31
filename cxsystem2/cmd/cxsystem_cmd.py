"""cxsystem2 -- a cortex simulation software

Usage:
  cxsystem2 (-h | --help)
  cxsystem2 -a ANATOMY_FILE -p PHYSIOLOGY_FILE
  cxsystem2 (-v | --version)

A cortex simulation framework called `CxSystem`.

Arguments:
  PORT                                              port number on which the BUI server runs

Options:
  -h --help                                         Show this screen
  -v --version                                      Show current cxsystem version
  -a ANATOMY_FILE --anatomy=ANATOMY_FILE            Sets the anatomy file path
  -p PHYSIOLOGY_FILE --physiology=PHYSIOLOGY_FILE   Sets the physiology file path


Description:

  cxsystem2 -a ./anatomy.csv -p ./physiology.csv
    runs the cxsystem using the anatomy file called anatomy.csv and physiology file called physiology.csv

  cxsystem2 --anatomy ./anatomy.csv --physiology ./physiology.csv
    runs the cxsystem using the anatomy file called anatomy.csv and physiology file called physiology.csv

"""

import argparse
import sys
from pathlib import Path

# Local
import cxsystem2 as cxmodule
from cxsystem2.core.cxsystem import CxSystem


def main():
    parser = argparse.ArgumentParser(
        description="Run CxSystem with anatomy and physiology files.",
        usage=""" cxsystem2 (-h | --help)
        cxsystem2 -a ANATOMY_FILE -p PHYSIOLOGY_FILE
        cxsystem2 (-v | --version)
        """,
    )

    if len(sys.argv) == 1:
        parser.print_usage()
        sys.exit(1)

    parser.add_argument("-a", "--anatomy", type=Path, help="Path to the anatomy file")

    parser.add_argument(
        "-p", "--physiology", type=Path, help="Path to the physiology file"
    )

    parser.add_argument(
        "-v", "--version", action="store_true", help="Display the version of CxSystem2"
    )

    args = parser.parse_args()

    if args.version:
        print("CxSystem2 Version {}".format(cxmodule.__version__))
        return

    if args.anatomy and args.physiology:
        anatomy_path = args.anatomy
        if not anatomy_path.is_file():
            print("Anatomy file not found")
            return

        physio_path = args.physiology
        if not physio_path.is_file():
            print("Physiology file not found")
            return

        cx = CxSystem(anatomy_path.as_posix(), physio_path.as_posix())
        cx.run()


if __name__ == "__main__":
    if len(sys.argv) == 1:
        sys.argv.append("-h")
    main()
