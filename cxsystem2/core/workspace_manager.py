# Built-in
import os
from pathlib import Path
from typing import Any

# Local
from cxsystem2.core.tools import load_from_file, write_to_file

__author__ = "Andalibi, V., Hokkanen H., Vanni, S."

"""
The preliminary version of this software has been developed at Aalto University 2012-2015, 
and the full version at the University of Helsinki 2013-2017. The software is distributed 
under the terms of the GNU General Public License. 
Copyright 2017 Vafa Andalibi, Henri Hokkanen and Simo Vanni.
"""


class Workspace:
    """
    As the name implies, this module is used for gathering the data and saving the result.
    """

    def __init__(self, workspace_path: str | Path, suffix: str) -> None:
        """
        Initialize the Workspace object.

        Parameters
        ----------
        workspace_path : str or Path
            The path for saving the data.
        suffix : str
            The string containing date and time that is supposed to be unique
            for each simulation and is used as a suffix for file names.

        Notes
        -----
        Main internal variables:

        - ``results``: the main variable to be saved. It contains all the data
          about the positions of the NeuronGroup()s as well as the monitor results.
        - ``syntax_bank``: Since the monitors are explicitly defined in the Globals(),
          extracting the data from them requires addressing their name explicitly.
          To automatize this process, the syntaxes for extracting the data from
          the target monitors are generated and saved in this variable, so that
          they can be run at the end of the simulation.
        """
        self.workspace_path = Path(workspace_path).expanduser()
        assert self.workspace_path.is_absolute(), "workspace path must be absolute."
        if not self.workspace_path.is_dir():
            os.makedirs(self.workspace_path.as_posix())
        self.suffix = suffix
        self.output_extension = ".gz"
        self.compression_to_extension: dict[str, str] = {
            "gzip": ".gz",
            "bzip2": "bz2",
            "pickle": ".pickle",
        }
        self.results: dict[str, Any] = {}
        self.connections: dict[str, Any] = {}
        self.syntax_bank: list[Any] = []
        self.simulation_name = ""
        self.simulation_folder = Path()
        self.results_export_path = Path()
        self.connections_export_path = Path()
        self.imported_connections_path = Path()

    def set_compression_method(self, compression_method: str) -> None:
        """
        Set the output file extension based on the chosen compression method.

        Parameters
        ----------
        compression_method : str
            The compression method to use. Must be one of the keys in
            ``compression_to_extension`` (e.g. ``"gzip"``, ``"bzip2"``, ``"pickle"``).
        """
        self.output_extension = self.compression_to_extension[compression_method]

    def create_simulation(self, sim_name: str | None) -> None:
        """
        Create the simulation folder and set the export paths for results and connections.

        Parameters
        ----------
        sim_name : str or None
            The name of the simulation. If ``"."``, ``""``, ``"--"``, or ``None``,
            the workspace folder itself is used as the simulation folder and its
            name becomes the simulation name.
        """
        match sim_name:
            case "." | "" | "--" | None:
                self.simulation_name = self.workspace_path.name
                self.simulation_folder = self.workspace_path
            case _:
                self.simulation_name = sim_name
                self.simulation_folder = self.workspace_path.joinpath(
                    self.simulation_name
                )

        print(f" -  simulation folder {self.simulation_folder}")

        self.simulation_folder.mkdir(parents=True, exist_ok=True)
        self.results_export_path = self.simulation_folder.joinpath(
            self.simulation_name + "_results" + self.suffix
        ).with_suffix(self.output_extension)
        self.connections_export_path = self.simulation_folder.joinpath(
            self.simulation_name + "_connections" + self.suffix
        ).with_suffix(self.output_extension)

    def get_workspace_folder(self) -> Path:
        return self.workspace_path

    def get_workspace_as_posix(self) -> str:
        return self.workspace_path.as_posix()

    def get_simulation_folder(self) -> Path:
        return self.simulation_folder

    def get_simulation_folder_as_posix(self) -> str:
        return self.simulation_folder.as_posix()

    def get_output_extension(self) -> str:
        return self.output_extension

    def get_imported_connection_path(self) -> str:
        return self.imported_connections_path.as_posix()

    def get_results_export_path(self) -> str:
        return self.results_export_path.as_posix()

    def set_imported_connection_path(self, path: str | Path) -> None:
        self.imported_connections_path = Path(path).expanduser()

    def import_connections(self) -> Any:
        """
        Load and return the connections data from the configured import path.

        The import path can be a file, a directory (in which case the most recent
        ``*connections*`` file matching the output extension is used), or a path
        relative to the workspace or simulation folder.

        Returns
        -------
        Any
            The deserialized connections data loaded from the file.

        Raises
        ------
        FileNotFoundError
            If no matching connections file is found at the configured path.
        """

        def _find_most_recent_pattern(path: str | Path, pattern: str) -> Path:
            files = list(Path(path).glob(pattern))

            if not files:
                raise FileNotFoundError(f"\nNo {pattern} found in {path}")
            else:
                # Take most recent matching file
                print(
                    f"\n -  Multiple {pattern} found in {path}. Taking the most recent one:"
                )
                return max(files, key=os.path.getmtime)

        if self.imported_connections_path.is_file():
            connections_fullpath_filename = self.imported_connections_path
        elif self.imported_connections_path.is_dir():
            # Find most recent *connections*.gz file in the specified folder
            connections_fullpath_filename = _find_most_recent_pattern(
                self.imported_connections_path,
                f"*connections*{self.output_extension}",
            )
        elif self.workspace_path.joinpath(self.imported_connections_path).is_file():
            # Assume the path is relative to workspace
            connections_fullpath_filename = self.workspace_path.joinpath(
                self.imported_connections_path
            )

        elif (
            self.workspace_path.joinpath(self.simulation_name)
            .joinpath(self.imported_connections_path)
            .is_file()
        ):
            # Assume the path is relative to workspace
            connections_fullpath_filename = self.workspace_path.joinpath(
                self.simulation_name
            ).joinpath(self.imported_connections_path)

        elif self.workspace_path.joinpath(self.imported_connections_path).is_dir():
            # Find most recent *connections*.gz file in the specified folder relative to workspace
            connections_fullpath_filename = _find_most_recent_pattern(
                self.workspace_path.joinpath(self.imported_connections_path),
                f"*connections*{self.output_extension}",
            )

        else:
            raise FileNotFoundError(
                f" -  Connection file not found: {self.imported_connections_path.as_posix()}"
            )

        self.imported_connections_path = connections_fullpath_filename
        return load_from_file(connections_fullpath_filename.as_posix())

    def create_results_key(self, key: str) -> None:
        if key not in self.results:
            self.results[key] = {}

    def create_connections_key(self, key: str) -> None:
        if key not in self.connections:
            self.connections[key] = {}

    def save_results_to_file(self) -> dict[str, Any]:
        """
        Save the results dictionary to the results export file.

        If the target file already exists, a numeric suffix is appended to the
        filename to avoid overwriting.

        Returns
        -------
        dict[str, Any]
            The results dictionary that was saved, including the ``"Full_path"`` key
            pointing to the actual file location.
        """

        print(" -  Saving results to file ...")
        self.results["Full_path"] = self.results_export_path.as_posix()
        while self.results_export_path.is_file():
            idx = 1
            self.results_export_path = self.results_export_path.parent.joinpath(
                f"{self.results_export_path.stem}_{idx}{self.results_export_path.suffix}"
            )
            idx += 1
        write_to_file(self.results_export_path.as_posix(), self.results)
        print(
            f" -  The output of the simulation is saved at: {self.results_export_path}"
        )

        return self.results

    def save_connections_to_file(self) -> None:
        """
        Save the connections dictionary to the connections export file.

        If the target file already exists, a numeric suffix is appended to the
        filename to avoid overwriting.
        """

        print(" -  Saving connections to file ...")
        self.connections["Full_path"] = self.connections_export_path.as_posix()
        while self.connections_export_path.is_file():
            idx = 1
            self.connections_export_path = self.connections_export_path.parent.joinpath(
                f"{self.connections_export_path.stem}_{idx}{self.connections_export_path.suffix}"
            )
            idx += 1
        write_to_file(self.connections_export_path.as_posix(), self.connections)
