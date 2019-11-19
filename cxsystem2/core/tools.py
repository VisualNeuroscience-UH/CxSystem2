import bz2
import pickle as pickle
import zlib

import numpy as np
import pandas as pd
import pathlib as pl

from cxsystem2.core.exceptions import ParameterNotFoundError
from cxsystem2.configuration import config_file_converter as file_converter

def write_to_file(save_path,
                  data):
    if type(save_path) != pl.PosixPath:
        save_path = pl.Path(save_path)
    if save_path.suffix == '.gz':
        with open(save_path.as_posix(), 'wb') as fb:
            fb.write(zlib.compress(pickle.dumps(data, pickle.HIGHEST_PROTOCOL), 9))
    elif save_path.suffix == '.bz2':
        with bz2.BZ2File(save_path.as_posix(), 'wb') as fb:
            pickle.dump(data, fb, pickle.HIGHEST_PROTOCOL)
    elif save_path.suffix == '.pickle':
        with open(save_path.as_posix(), 'wb') as fb:
            pickle.dump(data, fb, pickle.HIGHEST_PROTOCOL)


def load_from_file(load_path):
    if type(load_path) != pl.PosixPath:
        load_path = pl.Path(load_path)
    if load_path.suffix == '.gz':
        with open(load_path.as_posix(), 'rb') as fb:
            data = zlib.decompress(fb.read())
            loaded_data = pickle.loads(data)
    elif load_path.suffix == '.bz2':
        with bz2.BZ2File(load_path.as_posix(), 'rb') as fb:
            loaded_data = pickle.load(fb)
    elif load_path.suffix == '.pickle':
        with open(load_path.as_posix(), 'rb') as fb:
            loaded_data = pickle.load(fb)
    return loaded_data

def parameter_finder(df,
                     keyword):
    location = np.where(df.values == keyword)
    value = ''
    if location[0].size:
        counter = int(location[0]) + 1
        while counter < df.shape[0]:
            if '#' not in str(df.loc[counter][int(location[1])]):
                value = df.loc[counter][int(location[1])]
                break
            else:
                counter += 1
        return value
    else:
        raise NameError('Variable %s not found in the configuration file.' % keyword)



def change_parameter_value_in_file(filepath,
                                   save_path,
                                   parameter,
                                   new_value):
    df = pd.read_csv(filepath, header=None)
    location = np.where(df.values == parameter)
    if location[0].size == 1:
        df.at[int(location[0] + 1), int(location[1])] = new_value
        df.to_csv(save_path, header=False, index=False)
    elif location[0].size == 1:
        raise ParameterNotFoundError('Parameter {} not found in the configuration file.'.format(parameter))
    else:
        raise ParameterNotFoundError('More than one instance of parameter {} found, cannot chagne the value'.format(parameter))


def read_config_file(conf,
                     header=False):
    """
    This function reads the file and convert it to csv from json if necessary.
    It only works by loading the csv without headers. (header=none)
    If you need the first row as header, do it manually
    :param header:
    :param conf:
    :return:
    """
    if type(conf) == str:
        if '.json' in conf.lower():
            converter = file_converter.ConfigConverter(conf)
            data = converter.get_csv()
        else:
            data = pd.read_csv(conf, header=None)
    else:
        if type(conf) == dict:  # it means we've received json data
            converter = file_converter.ConfigConverter(conf)
            data = converter.get_csv_from_json_data()
        else:
            data = conf
    if header is True and (type(conf) == dict or type(conf) == str):
        new_header = data.iloc[0]  # grab the first row for the header
        data = data[1:]  # take the data less the header row
        data.columns = new_header  # set the header row as the df header
    return data
