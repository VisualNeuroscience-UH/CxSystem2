# Built-in
import bz2
import pathlib as pl
import pickle as pickle
import zlib

# Third-party
import numpy as np
import pandas as pd
from brian2.input.timedarray import TimedArray
from brian2.units import *  # noqa: F403

# Local
from cxsystem2.configuration import config_file_converter as file_converter
from cxsystem2.core.exceptions import ParameterNotFoundError

array = np.array  # necessary to have as top-level variable for the brian2.


def _remove_timed_arrays(obj):
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


def write_to_file(save_path, data):
    if not isinstance(save_path, pl.PosixPath):
        save_path = pl.Path(save_path)
    if save_path.suffix == ".gz":
        # Check data dictionary for TimedArray objects and remove them
        data = _remove_timed_arrays(data)
        with open(save_path.as_posix(), "wb") as fb:
            fb.write(zlib.compress(pickle.dumps(data, pickle.HIGHEST_PROTOCOL), 9))
    elif save_path.suffix == ".bz2":
        with bz2.BZ2File(save_path.as_posix(), "wb") as fb:
            pickle.dump(data, fb, pickle.HIGHEST_PROTOCOL)
    elif save_path.suffix == ".pickle" or save_path.suffix == ".pkl":
        with open(save_path.as_posix(), "wb") as fb:
            pickle.dump(data, fb, pickle.HIGHEST_PROTOCOL)


def load_from_file(load_path):
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


def parameter_finder(df, keyword):
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
        raise NameError("Variable %s not found in the configuration file." % keyword)


def change_anat_file_header_value(
    filepath: pl.Path | str,
    save_path: pl.Path | str,
    parameters_to_change: dict,
) -> None:
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
                "Parameter {} not found in the configuration file.".format(parameter)
            )
        else:
            raise ParameterNotFoundError(
                "More than one instance of parameter {} found, cannot change the value".format(
                    parameter
                )
            )
        df.to_csv(save_path, header=False, index=False)


def read_config_file(conf, header=False):
    """
    This function reads the file and convert it to csv from json if necessary.
    It only works by loading the csv without headers. (header=none)
    If you need the first row as header, do it manually
    :param header:
    :param conf:
    :return:
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
