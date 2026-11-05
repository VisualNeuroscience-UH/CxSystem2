# Built-in
import os
import threading
from pathlib import Path
from typing import Any

# Third-party
from numpy.random import Generator, SeedSequence, default_rng

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


class RandomManager:
    """
    Singleton class for unified random number generation across all modules.

    The manager wraps a single shared ``Generator`` built on a master
    ``SeedSequence``. The first construction in the process fixes the seed
    for the entire run; every later construction returns the existing
    instance. The main module should therefore instantiate the manager once,
    at the call time of the constructor class, either with an integer seed
    for a deterministic and replicable run, or with ``None`` for
    system-entropy seeding.

    Notes
    -----
    Main internal variables:

    - ``_seed_sequence``: the master SeedSequence created from the requested
      seed. All spawned child streams derive from it.
    - ``_rng``: the shared Generator used by all modules that draw from
      ``rng``.

    Seeding behavior:

    - Integer seed: the whole run, including spawned subprocess streams, is
      deterministic and replicable.
    - ``None`` seed: the seed is drawn from the operating system entropy pool
      at construction time. The run is not reproducible, but the drawn seed
      is available through the ``seed`` property for post-hoc reconstruction.
    - ``SeedSequence``: adopted as the master sequence directly. This is the
      child path of the process recursion: the parent passes a spawned
      child seed sequence, and the child manager builds its own stream from
      it.

    Thread ownership:

    - The shared stream is owned by a single thread. The first thread that
      uses ``rng`` or ``spawn`` becomes the owner, and any other live thread
      touching them raises a ``RuntimeError``. This raises an error as soon
      as the shared stream would be used from several live threads, because
      the draw order would then depend on scheduling and the run would not
      be replicable.
    - Ownership transfers automatically once the previous owner thread has
      ended, which permits sequential use by successive threads.
    - ``claim_ownership`` is the explicit escape hatch for a deliberate
      sequential handoff while the previous owner is still alive.
    - Other threads should not draw from the manager at all: obtain
      independent generators with ``spawn(n)`` up front and pass one
      generator to each thread. Drawn independently, those streams remain
      deterministic even when the threads run concurrently.

    Process recursion:

    - To seed child processes deterministically, the parent obtains child
      seed sequences with ``seed_sequence.spawn(n)`` and passes one to each
      child process. In the child process, the same constructor path builds
      the manager: ``RandomManager(child_sequence)``.
    - The child's ``seed`` property reports the root seed of the tree, and
      its ``spawn_key`` property positions it in the tree, so the pair
      identifies and reconstructs the child stream. Child managers can
      spawn grandchildren, keeping the whole tree deterministic from the
      single root seed.
    - The recursion requires child processes that start as fresh
      interpreters, such as multiprocessing with the ``spawn`` start method
      or subprocess launches. With the ``fork`` start method, the child
      inherits the parent's singleton, so constructing the child manager
      raises a ``RuntimeError`` by design.
    """

    _instance: "RandomManager | None" = None
    _lock: threading.Lock = threading.Lock()
    _initialized: bool = False

    def __new__(cls: type["RandomManager"], seed: int | SeedSequence | None = None) -> "RandomManager":
        """
        Create the singleton instance on first construction and return it.

        On every subsequent construction, the existing instance is returned,
        and the requested seed must either match the fixed seed or be omitted.
        Seed sequences are compared by identity, since ``SeedSequence``
        defines no value equality.

        Parameters
        ----------
        seed : int, SeedSequence, or None
            The seed for the master seed sequence. Used only on the first
            construction in the process.

        Returns
        -------
        RandomManager
            The singleton instance.

        Raises
        ------
        RuntimeError
            If a seed is requested after the singleton has already been
            initialized with a different seed.
        """
        if cls._instance is None:
            with cls._lock:
                if cls._instance is None:
                    cls._instance = super().__new__(cls)
                    return cls._instance
        if seed is not None and not cls._seed_matches(seed):
            raise RuntimeError(
                f"RandomManager is already initialized with seed "
                f"{cls._describe_seed(getattr(cls._instance, '_requested_seed', None))}. "
                f"Cannot reinitialize with seed "
                f"{cls._describe_seed(seed)}. "
                f"The seed is fixed for the lifetime of the process."
            )
        return cls._instance

    @classmethod
    def _seed_matches(cls: type["RandomManager"], seed: int | SeedSequence) -> bool:
        """
        Check whether the requested seed matches the seed fixed by the
        singleton. Seed sequences are matched by identity, integers by value.
        """
        requested = getattr(cls._instance, "_requested_seed", None)
        if isinstance(seed, SeedSequence):
            return seed is requested
        if isinstance(requested, SeedSequence):
            return False
        return seed == requested

    @staticmethod
    def _describe_seed(seed: int | SeedSequence | None) -> str:
        """
        Build a compact, human-readable description of a seed for error
        messages and logs.
        """
        if isinstance(seed, SeedSequence):
            return (
                f"SeedSequence(entropy={seed.entropy}, "
                f"spawn_key={seed.spawn_key})"
            )
        return str(seed)

    def __init__(self, seed: int | SeedSequence | None = None) -> None:
        """
        Initialize the RandomManager instance.

        Parameters
        ----------
        seed : int, SeedSequence, or None
            The master seed. An integer produces a deterministic and
            replicable root manager; ``None`` draws the seed from the
            operating system entropy pool; a ``SeedSequence``, typically a
            spawned child sequence passed from the parent process, is
            adopted as the master sequence directly. Only the first
            construction in the process uses this parameter.
        """
        if self._initialized:
            return
        self._requested_seed: int | SeedSequence | None = seed
        if isinstance(seed, SeedSequence):
            self._seed_sequence: SeedSequence = seed
        else:
            self._seed_sequence = SeedSequence(seed)
        self._rng: Generator = default_rng(self._seed_sequence)
        self._owner_thread: threading.Thread | None = None
        self._initialized = True
        if self.spawn_key:
            print(
                f" -  RandomManager initialized with seed {self.seed} "
                f"and spawn key {self.spawn_key}"
            )
        else:
            print(f" -  RandomManager initialized with seed {self.seed}")

    def _ensure_thread_ownership(self) -> None:
        """
        Claim thread ownership of the manager, or raise if another live
        thread owns it.

        The first thread that uses ``rng`` or ``spawn`` becomes the owner.
        Ownership is transferred automatically when the previous owner thread
        has ended, which permits sequential use by successive threads while
        rejecting interleaved use from several live threads.
        """
        with self._lock:
            current = threading.current_thread()
            if self._owner_thread is None:
                self._owner_thread = current
                return
            if self._owner_thread is current:
                return
            if not self._owner_thread.is_alive():
                print(
                    f" -  RandomManager thread ownership transferred from "
                    f"{self._owner_thread.name} to {current.name}"
                )
                self._owner_thread = current
                return
            raise RuntimeError(
                f"RandomManager is owned by thread "
                f"'{self._owner_thread.name}', but was accessed from thread "
                f"'{current.name}'. The shared stream must not be used from "
                f"several live threads, because the draw order would depend "
                f"on scheduling and the run would not be replicable. Use "
                f"spawn(n) to obtain independent generators for other "
                f"threads, or call claim_ownership() for a deliberate "
                f"sequential handoff."
            )

    def claim_ownership(self) -> None:
        """
        Claim thread ownership of the manager for the calling thread.

        This is the explicit escape hatch for a deliberate, sequential
        handoff while the previous owner thread is still alive. The previous
        owner must not use the manager afterwards.
        """
        with self._lock:
            current = threading.current_thread()
            previous_name = (
                self._owner_thread.name
                if self._owner_thread is not None
                else "none"
            )
            self._owner_thread = current
            print(
                f" -  RandomManager thread ownership claimed by "
                f"{current.name} (previous owner: {previous_name})"
            )

    @classmethod
    def get_instance(cls: type["RandomManager"], seed: int | SeedSequence | None = None) -> "RandomManager":
        """
        Return the singleton instance, creating it on first call.

        The main module calls this method with the seed at the call time of
        the constructor class; all other modules call it without arguments.
        Calling ``RandomManager(seed)`` directly is equivalent.

        Parameters
        ----------
        seed : int, SeedSequence, or None
            The seed, used only if the singleton does not exist yet.

        Returns
        -------
        RandomManager
            The singleton instance.
        """
        return cls(seed)

    @property
    def seed(self) -> int:
        """
        The effective seed of this manager as an integer.

        When the manager was constructed with ``None``, this is the entropy
        value that was drawn from the operating system, so any run can be
        reconstructed post hoc by constructing a manager with this value as
        the seed. For managers constructed from a spawned child seed
        sequence, this is the root seed of the whole spawn tree; the
        ``spawn_key`` property completes the unique stream identity.

        Returns
        -------
        int
            The effective master seed.
        """
        return int(self._seed_sequence.entropy)

    @property
    def spawn_key(self) -> tuple[int, ...]:
        """
        The position of this manager in the spawn tree.

        The tuple is empty for root managers. For managers constructed from
        a spawned child seed sequence, it is the child's spawn key; together
        with the root ``seed`` it uniquely identifies and reconstructs the
        stream of this manager anywhere in the tree.

        Returns
        -------
        tuple of int
            The spawn key of the master seed sequence.
        """
        return tuple(self._seed_sequence.spawn_key)

    @property
    def seed_sequence(self) -> SeedSequence:
        """
        The master SeedSequence of this manager.

        This is the entry point for process recursion: the parent obtains
        child seed sequences with ``manager.seed_sequence.spawn(n)`` and
        passes one to each child process, where the same constructor path
        builds the child manager with ``RandomManager(child_sequence)``.
        Spawning through the returned sequence must follow the same
        owner-thread discipline as ``spawn``.

        Returns
        -------
        numpy.random.SeedSequence
            The master seed sequence.

        Raises
        ------
        RuntimeError
            If the manager is owned by another live thread.
        """
        self._ensure_thread_ownership()
        return self._seed_sequence

    @property
    def rng(self) -> Generator:
        """
        The shared random number generator with singleton status.

        All modules drawing from this generator consume one identical,
        ordered stream. The stream is owned by a single thread; see the
        class docstring for the thread ownership rules.

        Returns
        -------
        numpy.random.Generator
            The shared generator.

        Raises
        ------
        RuntimeError
            If the manager is owned by another live thread. Use ``spawn`` to
            obtain independent generators for other threads, or
            ``claim_ownership`` for a deliberate sequential handoff.
        """
        self._ensure_thread_ownership()
        return self._rng

    def spawn(self, n: int) -> list[Generator]:
        """
        Return n independent generators spawned from the master seed sequence.

        Each returned generator is seeded from a child seed sequence derived
        from the master sequence, which guarantees, with very high
        probability, statistically independent and non-overlapping streams.
        With an integer master seed, the spawned streams are deterministic:
        given the same master seed and the same sequence of ``spawn`` calls,
        the children are always identical. Each child generator can also
        spawn its own children, so a subprocess can split its stream further
        without coordination.

        For determinism, ``spawn`` must be called from the owner thread, so
        that the order of spawn calls, and therefore the child identities,
        do not depend on scheduling. Obtain the generators up front and pass
        one to each thread or worker; drawn independently, those streams are
        safe to use concurrently. For spawning child processes, use
        ``seed_sequence.spawn(n)`` instead and construct a ``RandomManager``
        from each child sequence inside the child process; see the class
        docstring for the process recursion rules.

        Parameters
        ----------
        n : int
            The number of independent generators to spawn.

        Returns
        -------
        list of numpy.random.Generator
            The spawned independent generators.

        Raises
        ------
        RuntimeError
            If the manager is owned by another live thread.
        """
        self._ensure_thread_ownership()
        with self._lock:
            children = self._seed_sequence.spawn(n)
        return [default_rng(child) for child in children]