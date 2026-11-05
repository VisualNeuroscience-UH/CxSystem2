# Built-in
import bz2
import pathlib as pl
import pickle as pickle
import zlib
from typing import Any

# Third-party
import numpy as np
import pandas as pd
from brian2.input.timedarray import TimedArray
from brian2.units import *  # noqa: F403

# Local
from cxsystem2.configuration import config_file_converter as file_converter
from cxsystem2.core.exceptions import ParameterNotFoundError

array = np.array  # necessary to have as top-level variable for the brian2.


def _remove_timed_arrays(obj: Any) -> Any:
    """
    Recursively remove TimedArray objects from dictionaries.

    TimedArrays contain expressions that cannot be pickled, so they are deleted
    in place before saving.

    Parameters
    ----------
    obj : Any
        The object to clean; dictionaries are traversed recursively.

    Returns
    -------
    Any
        The object with all TimedArray entries removed.
    """
    # Timed arrays of brian contain some expressions which cannot be saved by pickle,
    # thus we need to remove them.
    if not isinstance(obj, dict):
        return obj
    keys = list(obj.keys())
    for key in keys:
        if isinstance(obj[key], TimedArray):
            del obj[key]
        elif isinstance(obj[key], dict):
            obj[key] = _remove_timed_arrays(obj[key])
    return obj


def write_to_file(save_path: pl.Path | str, data: Any) -> None:
    """
    Write data to a file, pickled and compressed based on the file suffix.

    Parameters
    ----------
    save_path : str or Path
        Target file path; the suffix selects the format: ``.gz`` (gzip),
        ``.bz2`` (bzip2), ``.pickle``/``.pkl`` (plain pickle).
    data : Any
        The object to serialize. TimedArray objects are removed first when
        writing ``.gz``.
    """
    if not isinstance(save_path, pl.PosixPath):
        save_path = pl.Path(save_path)
    if save_path.suffix == ".gz":
        # Check data dictionary for TimedArray objects and remove them
        data = _remove_timed_arrays(data)
        with open(save_path.as_posix(), "wb") as fb:
            fb.write(zlib.compress(pickle.dumps(data, pickle.HIGHEST_PROTOCOL), 1))
    elif save_path.suffix == ".bz2":
        with bz2.BZ2File(save_path.as_posix(), "wb") as fb:
            pickle.dump(data, fb, pickle.HIGHEST_PROTOCOL)
    elif save_path.suffix == ".pickle" or save_path.suffix == ".pkl":
        with open(save_path.as_posix(), "wb") as fb:
            pickle.dump(data, fb, pickle.HIGHEST_PROTOCOL)


def load_from_file(load_path: pl.Path | str) -> Any:
    """
    Load pickled data from a file, decompressed based on the file suffix.

    Parameters
    ----------
    load_path : str or Path
        Source file path; the suffix selects the format: ``.gz``, ``.bz2``,
        ``.pickle``/``.pkl``.

    Returns
    -------
    Any
        The deserialized object.
    """
    if not isinstance(load_path, pl.PosixPath):
        load_path = pl.Path(load_path)
    if load_path.suffix == ".gz":
        with open(load_path.as_posix(), "rb") as fb:
            data = zlib.decompress(fb.read())
            loaded_data = pickle.loads(data)
    elif load_path.suffix == ".bz2":
        with bz2.BZ2File(load_path.as_posix(), "rb") as fb:
            loaded_data = pickle.load(fb)
    elif load_path.suffix == ".pickle" or load_path.suffix == ".pkl":
        with open(load_path.as_posix(), "rb") as fb:
            loaded_data = pickle.load(fb)
    return loaded_data


def parameter_finder(df: pd.DataFrame, keyword: str) -> Any:
    """
    Find the value of a parameter in a configuration dataframe.

    Parameters
    ----------
    df : DataFrame
        The configuration dataframe.
    keyword : str
        The parameter name to search for.

    Returns
    -------
    Any
        The first non-commented value below the parameter's row.

    Raises
    ------
    NameError
        If the keyword is not found in the dataframe.
    """
    location = np.where(df.values == keyword)
    value = ""
    if location[0].size:
        counter = int(location[0][0]) + 1
        while counter < df.shape[0]:
            if "#" not in str(df.loc[counter][int(location[1][0])]):
                value = df.loc[counter][int(location[1][0])]
                break
            else:
                counter += 1
        return value
    else:
        raise NameError(f"Variable {keyword} not found in the configuration file.")


def change_anat_file_header_value(
    filepath: pl.Path | str,
    save_path: pl.Path | str,
    parameters_to_change: dict[str, Any],
) -> None:
    """
    Change parameter values in an anatomy configuration file and save it.

    Parameters
    ----------
    filepath : Path or str
        Path to the input csv configuration file (no header).
    save_path : Path or str
        Path where the modified csv is written.
    parameters_to_change : dict
        Mapping of parameter names to their new values.

    Raises
    ------
    ValueError
        If ``parameters_to_change`` is not a dict.
    ParameterNotFoundError
        If a parameter is not found or found more than once.
    """
    df = pd.read_csv(filepath, header=None)

    if not isinstance(parameters_to_change, dict):
        raise ValueError(
            "parameters_to_change must be a dictionary of parameter names and values"
        )

    for parameter, new_value in parameters_to_change.items():
        location = np.where(df.values == parameter)
        if location[0].size == 1:
            row_index = int(location[0][0]) + 1
            col_index = int(location[1][0])
            df.at[row_index, col_index] = new_value
        elif location[0].size == 0:
            raise ParameterNotFoundError(
                f"Parameter {parameter} not found in the configuration file."
            )
        else:
            raise ParameterNotFoundError(
                f"More than one instance of parameter {parameter} found, cannot change the value"
            )
        df.to_csv(save_path, header=False, index=False)


def read_config_file(
    conf: str | dict | pd.DataFrame, header: bool = False
) -> pd.DataFrame:
    """
    Read a configuration file and return it as a dataframe.

    Accepts csv or json file paths, json data as a dict, or an existing
    dataframe. Json input is converted to csv format first.

    Parameters
    ----------
    conf : str, dict, or DataFrame
        Path to a csv/json file, json data as a dict, or a dataframe.
    header : bool, optional
        If True and ``conf`` is a path or dict, use the first row as the
        dataframe header. Default is False.

    Returns
    -------
    DataFrame
        The configuration dataframe.
    """
    if isinstance(conf, str):
        if ".json" in conf.lower():
            converter = file_converter.ConfigConverter(conf)
            data = converter.get_csv()
        else:
            data = pd.read_csv(conf, header=None)
    else:
        if isinstance(conf, dict):  # it means we've received json data
            converter = file_converter.ConfigConverter(conf)
            data = converter.get_csv_from_json_data()
        elif isinstance(conf, pd.DataFrame):
            data = conf
        else:
            raise TypeError(
                "Configuration file must be a path to csv or json file, a dictionary or a dataframe"
            )
    if header is True and (type(conf) == dict or type(conf) == str):  # noqa: E721
        new_header = data.iloc[0]  # grab the first row for the header
        data = data[1:]  # take the data less the header row
        data.columns = new_header  # set the header row as the df header
    return data
