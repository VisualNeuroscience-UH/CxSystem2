from importlib.metadata import version
from pathlib import Path

import tomllib

__version__ = version("cxsystem2")


def get_version_from_pyproject():
    pyproject_path = Path(__file__).parent.parent / "pyproject.toml"
    with open(pyproject_path, "rb") as f:
        data = tomllib.load(f)
    return data["tool"]["poetry"]["version"]

if __version__ != get_version_from_pyproject():
    raise ValueError(
        f"Version mismatch: __version__ is {__version__} but pyproject.toml version is {get_version_from_pyproject()}. Run poetry install at your repo root to update to the version in pyproject.toml."
    )