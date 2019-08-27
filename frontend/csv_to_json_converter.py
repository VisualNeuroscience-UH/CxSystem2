import pandas as pd
from pathlib import Path
from pprint import pprint
import math

# p = Path('../tests/config_files/pytest_Anatomy_config.csv')
p = Path('../tests/config_files/pytest_Physiology_config.csv')
output = {}
params = {}
IN = {}
G = {}
S = {}
with open(p, 'r') as f:
    csv_file = pd.read_csv(f,header=None)

    row_type_rows = list(csv_file.loc[csv_file[0] == 'row_type'].index.values.astype(int))
    if len (row_type_rows) > 3 : # let's assuem a working anatomy config file has at least 3 instance of row_type for params, G and S
        for row_idx in row_type_rows:
            next_non_comment_line_counter = 1
            while '#' in csv_file.loc[row_idx+next_non_comment_line_counter][0]:
                next_non_comment_line_counter+=1
            if (csv_file.loc[row_idx+next_non_comment_line_counter][0] == 'params'):
                for param_idx, param in enumerate(csv_file.loc[row_idx]):
                    if param != 'row_type' and not pd.isna(param):
                        params[param] = csv_file.loc[row_idx+1][param_idx]
            elif (csv_file.loc[row_idx + next_non_comment_line_counter][0] == 'IN'):
                for param_idx, param in enumerate(csv_file.loc[row_idx]):
                    if param != 'row_type' and not pd.isna(param):
                        IN[param] = csv_file.loc[row_idx+1][param_idx]
            elif (csv_file.loc[row_idx + next_non_comment_line_counter][0] == 'G'):
                counter = 1
                while csv_file.loc[row_idx + next_non_comment_line_counter+ counter][0] == 'G' or '#' in str(csv_file.loc[row_idx +next_non_comment_line_counter+ counter][0]):
                    if (csv_file.loc[row_idx + next_non_comment_line_counter + counter][0]): # pass the commented row
                        G[str(counter)] = {}
                        for param_idx, param in enumerate(csv_file.loc[row_idx]):
                            if param != 'row_type' and not math.isnan(param) :
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
                            if param != 'row_type' and not pd.isna(param):
                                S[str(counter)][param] = csv_file.loc[row_idx+next_non_comment_line_counter+counter][param_idx]
                    counter += 1
                    if row_idx +next_non_comment_line_counter+ counter > csv_file.index.to_list()[-1]:
                        break
        output = {'params': params, 'IN': IN, 'G': G, 'S': S}
    else:
        json_idx_counter = 0
        for var_idx,var  in enumerate(csv_file[csv_file.columns[0]]):
            if not pd.isna(var) and not var.startswith('#') and var != 'Variable':
                key = csv_file[csv_file.columns[1]][var_idx]
                value = csv_file[csv_file.columns[2]][var_idx]
                comment = csv_file[csv_file.columns[3]][var_idx] if not pd.isna(csv_file[csv_file.columns[3]][var_idx]) else ""
                if pd.isna(key)  : # this checks if the key is nan, which means it's a key/value pair
                    var_val = {str(json_idx_counter): {"Variable" : var, "Value":value, "Comment":comment } }
                    output.update(var_val)
                else:
                    counter = 0
                    tmp_var = []
                    while pd.isna(csv_file[csv_file.columns[0]][var_idx+counter+1]):
                        key = csv_file[csv_file.columns[1]][var_idx+counter]
                        value = csv_file[csv_file.columns[2]][var_idx+counter]
                        comment = csv_file[csv_file.columns[3]][var_idx+counter] if not pd.isna(csv_file[csv_file.columns[3]][var_idx]) else ""
                        if not (pd.isna(key) and pd.isna(value) and comment == ""):
                            key_val = {"Key" : key, "Value" : value, "Comment" : comment}
                            tmp_var.append(key_val)
                        counter+=1
                        if var_idx+counter+1 > csv_file.index.to_list()[-1]:
                            break
                    output.update({str(json_idx_counter):{"Variable" : var, "Key-Value" : tmp_var}})
                json_idx_counter += 1

pprint(output)