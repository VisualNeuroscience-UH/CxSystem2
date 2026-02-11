"""cxvisualize -- cxsystem visualizer

Usage:
  cxvisualize (-h | --help)
  cxvisualize  [ -d | -c ] FILEPATH
  cxvisualize --rasterplot-pdf FOLDERPATH TIMESTAMP [--sampling-rate SAMPLINGRATE]

A tool for visualizing `CxSystem` spike data in ViSimpl.

Arguments:
  FILENAME                                          Path to results file
  FOLDERPATH                                        Path to folder containing array run files
  TIMESTAMP                                         Timestamp suffix of the arrayrun files
  SAMPLINGRATE                                      Sampling rate for the rasterplots

Options:
  -h --help                                         Show this screen
  --rasterplot-pdf                                  Generate a rasterplot pdf for arrayrun
  -c --convert                                      Convert results for use in ViSimpl
  -d --delete                                       Delete ViSimpl-related files after visualization
  -s SAMPLINGRATE --sampling-rate=SAMPLINGRATE      Sampling rate for raster plot (default is 1%)

Description:

  cxvisualize ./results.gz
    converts the results file into two CSVs and one JSON for ViSimpl, visualizes the result and does not remove the temp files
    (actual visualization: ./visimpl -csv results_structure.csv results_spikes.csv -se results_subsets.json)

  cxvisualize -d ./results.gz
    converts the results file into two CSVs and one JSON for ViSimpl, visualizes the result and remove the temp files

  cxvisualize -c ./results.gz
    converts the results file into two CSVs and one JSON for ViSimpl (no visualization)

  cxvisualize --rasterplot-pdf ./cobaeif 20191123_1353509
    Generates a pdf of rasterplots of all groups in the folder with 20191123_1353509 timestamp with default sampling rate of 1%

  cxvisualize --rasterplot-pdf ./cobaeif 20191123_1353509 --sampling-rate=4%
    Generates a pdf of rasterplots of all groups in the folder with timestamp 20191123_1353509 and sampling rate or 4%

"""

import argparse
import os
import sys
from pathlib import Path
from shutil import which

# Local
from cxsystem2.visualization.rasterplot_to_pdf import rasterplot_pdf_generator
from cxsystem2.visualization.spikedata_to_csvs import SpikeData

VISIMPL_BINARY = ""


def check_visimpl():
    global VISIMPL_BINARY
    if which("visimpl.AppImage") is None:
        VISIMPL_BINARY = "~/visimpl/visimpl.AppImage"
        if not Path(VISIMPL_BINARY).expanduser().is_file():
            raise FileNotFoundError("ViSimpl binary not found")
    else:
        VISIMPL_BINARY = "visimpl.AppImage"


def _convert(filepath):
    x = SpikeData(filepath)
    structure_csv, spikes_csv, subsets_json = x.save_for_visimpl()
    return structure_csv, spikes_csv, subsets_json


def _run_visimpl(structure_csv, spikes_csv, subsets_json):
    run_visimpl_cmd = (
        VISIMPL_BINARY
        + " -csv "
        + str(structure_csv)
        + " "
        + str(spikes_csv)
        + " -se "
        + str(subsets_json)
    )
    os.system(run_visimpl_cmd)


def main():
    parser = argparse.ArgumentParser(
        description="cxvisualize -- cxsystem visualizer\n\n"
        "A tool for visualizing `CxSystem` spike data in ViSimpl.",
        formatter_class=argparse.RawDescriptionHelpFormatter,
        epilog="""
        Examples:

        cxvisualize ./results.gz
            Converts the results file into two CSVs and one JSON for ViSimpl, 
            visualizes the result, and does not remove the temp files.

        cxvisualize -d ./results.gz
            Converts the results file into two CSVs and one JSON for ViSimpl, 
            visualizes the result, and removes the temp files.

        cxvisualize -c ./results.gz
            Converts the results file into two CSVs and one JSON for ViSimpl (no visualization).

        cxvisualize --rasterplot-pdf ./cobaeif 20191123_1353509
            Generates a PDF of rasterplots of all groups in the folder 
            with the timestamp 20191123_1353509 and a default sampling rate of 1%.

        cxvisualize --rasterplot-pdf ./cobaeif 20191123_1353509 --sampling-rate 4%
            Generates a PDF of rasterplots of all groups in the folder 
            with the timestamp 20191123_1353509 and a sampling rate of 4%.
        """,
    )

    # Define mutually exclusive group for rasterplot-pdf mode
    parser.add_argument(
        "--rasterplot-pdf",
        action="store_true",
        help="Generate a rasterplot PDF for arrayrun",
    )

    parser.add_argument(
        "FOLDERPATH",
        nargs="?",
        type=Path,
        help="Path to folder containing array run files",
    )

    parser.add_argument(
        "TIMESTAMP", nargs="?", type=str, help="Timestamp suffix of the arrayrun files"
    )

    parser.add_argument(
        "-s",
        "--sampling-rate",
        type=str,
        default="1%",
        help="Sampling rate for raster plot (default is 1%%)",
    )

    # Define mutually exclusive group for convert/delete mode
    parser.add_argument(
        "-c",
        "--convert",
        action="store_true",
        help="Convert results for use in ViSimpl",
    )

    parser.add_argument(
        "-d",
        "--delete",
        action="store_true",
        help="Delete ViSimpl-related files after visualization",
    )

    parser.add_argument("FILEPATH", nargs="?", type=Path, help="Path to results file")

    args = parser.parse_args()

    if len(sys.argv) == 1:
        parser.print_help(sys.stderr)
        sys.exit(1)

    if args.rasterplot_pdf:
        if args.FOLDERPATH is None or args.TIMESTAMP is None:
            print(
                "FOLDERPATH and TIMESTAMP are required for rasterplot PDF generation."
            )
            sys.exit(1)

        folder_path = args.FOLDERPATH
        if not folder_path.is_dir():
            print("Arrayrun folder not found. Make sure the path is correct.")
            sys.exit(1)

        timestamp = args.TIMESTAMP.strip("_")
        dir_file_list = folder_path.glob("**/*")
        files = [
            x
            for x in dir_file_list
            if x.is_file() and timestamp in x.as_posix() and "results" in x.as_posix()
        ]

        if len(files) == 0:
            print("Arrayrun folder does not contain files with that timestamp.")
            sys.exit(1)

        sampling_rate = args.sampling_rate
        try:
            if (
                sampling_rate.count("%") != 1
                or float(sampling_rate[:-1]) > 100
                or float(sampling_rate[:-1]) <= 0
            ):
                print(
                    "Sampling rate not valid. It should be a number greater than 0% and less than or equal to 100%."
                )
                sys.exit(1)
        except ValueError:
            print(
                "Sampling rate not valid. It should be a number greater than 0% and less than or equal to 100%."
            )
            sys.exit(1)

        rasterplot_pdf_generator(folder_path, timestamp, sampling_rate)

    else:
        if args.FILEPATH is None:
            print("FILEPATH is required for conversion.")
            sys.exit(1)

        check_visimpl()
        filepath = args.FILEPATH
        if not filepath.is_file():
            print(f"Error: file {filepath.as_posix()} not found")
            sys.exit(1)

        structure_csv, spikes_csv, subsets_json = _convert(filepath)
        if not args.convert:
            _run_visimpl(structure_csv, spikes_csv, subsets_json)

        if args.delete:
            os.remove(structure_csv)
            os.remove(spikes_csv)
            os.remove(subsets_json)


if __name__ == "__main__":
    main()
