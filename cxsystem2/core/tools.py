import bz2
import pickle as pickle
import zlib

import numpy as np
import pandas as pd

from cxsystem2.core.exceptions import ParameterNotFoundError


def save_to_file(save_path, data):
    if '.gz' in save_path:
        with open(save_path, 'wb') as fb:
            fb.write(zlib.compress(pickle.dumps(data, pickle.HIGHEST_PROTOCOL), 9))
    elif '.bz2' in save_path:
        with bz2.BZ2File(save_path, 'wb') as fb:
            pickle.dump(data, fb, pickle.HIGHEST_PROTOCOL)
    elif '.pickle' in save_path:
        with open(save_path, 'wb') as fb:
            pickle.dump(data, fb, pickle.HIGHEST_PROTOCOL)

def parameter_finder(df,keyword):
    location = np.where(df.values == keyword)
    if location[0].size:
        counter = int(location[0])+1
        while counter < df.shape[0] :
            if '#' not in str(df.loc[counter][int(location[1])]):
                value = df.loc[counter][int(location[1])]
                break
            else:
                counter+=1
        return value
    else:
        raise NameError('Variable %s not found in the configuration file.'%keyword)

def change_parameter_value_in_file(filepath, save_path, parameter,new_value):
    df = pd.read_csv(filepath, header=None)
    location = np.where(df.values == parameter)
    if location[0].size == 1:
        df.at[int(location[0] + 1), int(location[1])] = new_value
        df.to_csv(save_path,header=False,index=False)
    elif location[0].size == 1:
        raise ParameterNotFoundError('Parameter {} not found in the configuration file.'.format(parameter))
    else:
        raise ParameterNotFoundError('More than one instance of parameter {} found, cannot chagne the value'.format(parameter))
