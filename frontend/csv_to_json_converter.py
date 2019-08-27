import pandas as pd
from pathlib import Path
import numpy as np
from pprint import pprint

p = Path('../tests/config_files/pytest_Anatomy_config.csv')

params = {}
IN = {}
G = {}
S = {}
with open(p, 'r') as f:
    csv_file = pd.read_csv(f,header=None)

    row_type_rows = list(csv_file.loc[csv_file[0] == 'row_type'].index.values.astype(int))
    for row_idx in row_type_rows:
        next_non_comment_line_counter = 1
        while '#' in csv_file.loc[row_idx+next_non_comment_line_counter][0]:
            next_non_comment_line_counter+=1
        if (csv_file.loc[row_idx+next_non_comment_line_counter][0] == 'params'):
            for param_idx, param in enumerate(csv_file.loc[row_idx]):
                if param not in  ['row_type' , np.nan]:
                    params[param] = csv_file.loc[row_idx+1][param_idx]
        elif (csv_file.loc[row_idx + next_non_comment_line_counter][0] == 'IN'):
            for param_idx, param in enumerate(csv_file.loc[row_idx]):
                if param not in  ['row_type' , np.nan]:
                    IN[param] = csv_file.loc[row_idx+1][param_idx]
        elif (csv_file.loc[row_idx + next_non_comment_line_counter][0] == 'G'):
            counter = 1
            while csv_file.loc[row_idx + next_non_comment_line_counter+ counter][0] == 'G' or '#' in str(csv_file.loc[row_idx +next_non_comment_line_counter+ counter][0]):
                if (csv_file.loc[row_idx + next_non_comment_line_counter + counter][0]): # pass the commented row
                    G[str(counter)] = {}
                    for param_idx, param in enumerate(csv_file.loc[row_idx]):
                        if param not in  ['row_type' , np.nan]:
                            G[str(counter)][param] = csv_file.loc[row_idx+next_non_comment_line_counter+counter][param_idx]
                counter += 1
                if row_idx +next_non_comment_line_counter+ counter > csv_file.index.to_list()[-1]:
                    break

        elif (csv_file.loc[row_idx + next_non_comment_line_counter][0] == 'S'):
            counter = 1
            while csv_file.loc[row_idx + next_non_comment_line_counter+counter][0] == 'S' or '#' in str(csv_file.loc[row_idx +next_non_comment_line_counter+ counter][0]):
                if (csv_file.loc[row_idx +next_non_comment_line_counter+ counter][0]): # pass the commented row
                    S[str(counter)] = {}
                    for param_idx, param in enumerate(csv_file.loc[row_idx]):
                        if param not in  ['row_type' , np.nan]:
                            S[str(counter)][param] = csv_file.loc[row_idx+next_non_comment_line_counter+counter][param_idx]
                counter += 1
                if row_idx +next_non_comment_line_counter+ counter > csv_file.index.to_list()[-1]:
                    break
output = {'params': params, 'IN': IN, 'G': G, 'S': S}

pprint(output)