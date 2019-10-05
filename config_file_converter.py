import pandas as pd
from pathlib import Path
from pprint import pprint
import json
import csv
import pandas
import os
from io import StringIO
'''
This file converts the two types of configuration files, i.e. CSV and JSON to each other. 
'''

class filetype_converter():
    def __init__(self,input):
        if type(input) == dict:
            self.json_data = input
        else:
            self.original_path = Path(input)
            self.directory = self.original_path.parent.absolute()
            self.filename_without_extension = self.original_path.stem
        self.output = {}
        self.params = {}
        self.IN = []
        self.G = []
        self.S = []
        self.new_filepath = Path()
        self.suffix_to_method_mapping = {
            '.csv' : self.csv_to_json,
            '.json' : self.json_to_csv
        }
        # suffix_to_method_mapping[self.original_path.suffix.lower()]()


    def json_to_csv(self):
        if self.original_path.suffix == '.json':
            new_filename = self.filename_without_extension + '.csv'
            self.new_filepath = self.directory.joinpath(new_filename)
            counter = 1
            while self.new_filepath.is_file():
                new_filename = self.filename_without_extension + f'_{counter}' + '.csv'
                self.new_filepath = self.directory.joinpath(new_filename)
                counter+=1

            with open(self.original_path, 'r') as f:
                json_data = json.load(f)

            # let's find the total number of rows so that we can save the csv properly otherwise pandas will raise errors
            total_number_of_rows = 0
            for r_type in ['params','IN','G','S']:
                if r_type in json_data.keys():
                    if r_type == 'params':
                        tmp_row = json_data[r_type]
                    else :
                        tmp_row = json_data[r_type][0]
                    if len(tmp_row.keys()) > total_number_of_rows:
                        total_number_of_rows = len(tmp_row.keys())

            with open( self.new_filepath, 'w',newline='') as f:
                csvfile = csv.writer(f)
                if 'params' in json_data.keys():
                    column_num = len(json_data['params'].keys())
                    csvfile.writerow(['row_type'] + list(json_data['params'].keys()) + [''] * (total_number_of_rows-column_num) )
                    csvfile.writerow(['params'] + list(json_data['params'].values()) + [''] * (total_number_of_rows-column_num) )

                if 'IN' in json_data.keys():
                    column_num = len(json_data['IN'][0].keys())
                    csvfile.writerow(['row_type'] + list(json_data['IN'][0].keys())+ [''] * (total_number_of_rows-column_num))
                    for IN_data in json_data['IN']:
                        csvfile.writerow(['IN'] + list(IN_data.values()) +[''] * (total_number_of_rows-column_num))
                    csvfile.writerow([''] * (total_number_of_rows + 1))
                if 'G' in json_data.keys():
                    column_num = len(json_data['G'][0].keys())
                    csvfile.writerow(['row_type'] + list(json_data['G'][0].keys())+ [''] * (total_number_of_rows-column_num))
                    for G_data in json_data['G']:
                        csvfile.writerow(['G'] + list(G_data.values())+ [''] * (total_number_of_rows-column_num))
                    csvfile.writerow([''] * (total_number_of_rows + 1))
                if 'S' in json_data.keys():
                    column_num = len(json_data['S'][0].keys())
                    csvfile.writerow(['row_type'] + list(json_data['S'][0].keys()) + [''] * (total_number_of_rows-column_num))
                    for S_data in json_data['S']:
                        csvfile.writerow(['S'] + list(S_data.values())+ [''] * (total_number_of_rows-column_num))
                    csvfile.writerow([''] * (total_number_of_rows + 1))

                else:
                    csvfile.writerow(['Variable','Key', 'Value','Comment'])
                    for entry in json_data['physio_data']:
                        if 'Key-Value' in entry.keys(): # this means it's a key-value entry
                            for keyval_idx, keyvalue in enumerate(entry['Key-Value']):
                                if keyval_idx == 0 :
                                    row = [entry['Variable'],keyvalue['Key'], keyvalue['Value'], keyvalue['Comment']]
                                else:
                                    row = ["", keyvalue['Key'],keyvalue['Value'], keyvalue['Comment']]
                                csvfile.writerow(row)
                        else:
                            row = [entry['Variable'],"",entry['Value'],entry['Comment']]
                            csvfile.writerow(row)

    def json_data_to_csv(self):

        # let's find the total number of rows so that we can save the csv properly otherwise pandas will raise errors
        total_number_of_rows = 0
        for r_type in ['params', 'IN', 'G', 'S']:
            if r_type in self.json_data.keys():
                if r_type == 'params':
                    tmp_row = self.json_data[r_type]
                else:
                    tmp_row = self.json_data[r_type][0]
                if len(tmp_row.keys()) > total_number_of_rows:
                    total_number_of_rows = len(tmp_row.keys())

        csvstring = ''
        if 'params' in self.json_data.keys():
            column_num = len(self.json_data['params'].keys())
            tmp_keys_in_string_format = [str(x) for x in self.json_data['params'].keys()]
            csvstring += ','.join(['row_type'] + tmp_keys_in_string_format + [''] * (total_number_of_rows - column_num)) + '\n'
            tmp_values_in_string_format=  [str(x) for x in self.json_data['params'].values()]
            csvstring += ','.join(['params'] + tmp_values_in_string_format + [''] * (total_number_of_rows - column_num)) + '\n'

        if 'IN' in self.json_data.keys():
            column_num = len(self.json_data['IN'][0].keys())
            tmp_keys_in_string_format = [str(x) for x in self.json_data['IN'][0].keys()]
            csvstring += ','.join(['row_type'] + tmp_keys_in_string_format + [''] * (total_number_of_rows - column_num)) + '\n'
            for IN_data in self.json_data['IN']:
                tmp_values_in_string_format = [str(x) for x in IN_data.values()]
                csvstring += ','.join(['IN'] + tmp_values_in_string_format + [''] * (total_number_of_rows - column_num)) + '\n'
            csvstring += ','.join([''] * (total_number_of_rows + 1)) + '\n'
        if 'G' in self.json_data.keys():
            column_num = len(self.json_data['G'][0].keys())
            tmp_keys_in_string_format = [str(x) for x in self.json_data['G'][0].keys()]
            csvstring += ','.join(['row_type'] +tmp_keys_in_string_format + [''] * (total_number_of_rows - column_num)) + '\n'
            for G_data in self.json_data['G']:
                tmp_values_in_string_format = [str(x) for x in G_data.values()]
                csvstring += ','.join(['G'] + tmp_values_in_string_format + [''] * (total_number_of_rows - column_num)) + '\n'
            csvstring += ','.join([''] * (total_number_of_rows + 1)) + '\n'
        if 'S' in self.json_data.keys():
            column_num = len(self.json_data['S'][0].keys())
            tmp_keys_in_string_format = [str(x) for x in self.json_data['S'][0].keys()]
            csvstring += ','.join(['row_type'] + tmp_keys_in_string_format + [''] * (total_number_of_rows - column_num)) + '\n'
            for S_data in self.json_data['S']:
                tmp_values_in_string_format = [str(x) for x in S_data.values()]
                csvstring += ','.join(['S'] + tmp_values_in_string_format + [''] * (total_number_of_rows - column_num)) + '\n'
            csvstring += ','.join([''] * (total_number_of_rows + 1)) + '\n'

        else:
            csvstring += ','.join(['Variable', 'Key', 'Value', 'Comment']) + '\n'
            for entry in self.json_data['physio_data']:
                if 'Key-Value' in entry.keys():  # this means it's a key-value entry
                    for keyval_idx, keyvalue in enumerate(entry['Key-Value']):
                        if keyval_idx == 0:
                            row = [str(entry['Variable']), str(keyvalue['Key']).replace(',','{comma}'), str(keyvalue['Value']).replace(',','{comma}'), keyvalue['Comment'].replace(',','{comma}')]
                        else:
                            row = ["", str(keyvalue['Key']).replace(',','{comma}'), str(keyvalue['Value']).replace(',','{comma}'), keyvalue['Comment'].replace(',','{comma}')]
                        csvstring += ','.join(row) + '\n'
                else:
                    row = [str(entry['Variable']).replace(',','{comma}'), "", str(entry['Value']).replace(',','{comma}'), entry['Comment'].replace(',','{comma}')]
                    csvstring += ','.join(row) + '\n'
        return csvstring


    def csv_to_json(self):
        if self.original_path.suffix == '.csv':
            new_filename = self.filename_without_extension + '.json'
            self.new_filepath = self.directory.joinpath(new_filename)
            counter = 1
            while self.new_filepath.is_file():
                new_filename = self.filename_without_extension + f'_{counter}' + '.json'
                self.new_filepath = self.directory.joinpath(new_filename)
                counter+=1

            with open(self.original_path, 'r') as f:
                csv_data = pd.read_csv(f,header=None)

            row_type_rows = list(csv_data.loc[csv_data[0] == 'row_type'].index.values.astype(int))
            if len (row_type_rows) > 3 : # let's assuem a working anatomy config file has at least 3 instance of row_type for params, G and S
                for row_idx in row_type_rows:
                    next_non_comment_line_counter = 1
                    while '#' in csv_data.loc[row_idx+next_non_comment_line_counter][0]:
                        next_non_comment_line_counter+=1
                    if (csv_data.loc[row_idx+next_non_comment_line_counter][0] == 'params'):
                        for param_idx, param in enumerate(csv_data.loc[row_idx]):
                            if param != 'row_type' and not pd.isna(param):
                                try: # first we try to convert it to integer if possible , floats can stay in string format because jsoneditor validates float as string with regex
                                    self.params[param.strip()] = int(csv_data.loc[row_idx+1][param_idx].strip())
                                except ValueError:
                                    self.params[param.strip()] = csv_data.loc[row_idx + 1][param_idx].strip()
                    elif (csv_data.loc[row_idx + next_non_comment_line_counter][0] == 'IN'):
                        counter = 0
                        while csv_data.loc[row_idx + next_non_comment_line_counter + counter][0] == 'IN' or '#' in str(csv_data.loc[row_idx + next_non_comment_line_counter + counter][0]):
                            if ('#' not in csv_data.loc[row_idx + next_non_comment_line_counter + counter][0]):  # pass the commented row
                                # self.IN[str(counter)] = {}
                                tmp_IN = {}
                                for param_idx, param in enumerate(csv_data.loc[row_idx]):
                                    if param != 'row_type' and not pd.isna(param):
                                        try:
                                            tmp_IN[param.strip()] = int(csv_data.loc[row_idx + next_non_comment_line_counter + counter][param_idx].strip())
                                        except ValueError:
                                            tmp_IN[param.strip()] = \
                                            csv_data.loc[row_idx + next_non_comment_line_counter + counter][param_idx].strip()
                                self.IN.append(tmp_IN)
                            counter += 1
                            if row_idx +next_non_comment_line_counter+ counter > csv_data.index.to_list()[-1]:
                                break


                    elif (csv_data.loc[row_idx + next_non_comment_line_counter][0] == 'G'):
                        counter = 0
                        while csv_data.loc[row_idx + next_non_comment_line_counter+ counter][0] == 'G' or '#' in str(csv_data.loc[row_idx +next_non_comment_line_counter+ counter][0]):
                            if ('#' not in csv_data.loc[row_idx + next_non_comment_line_counter + counter][0]): # pass the commented row
                                # self.G[str(counter)] = {}
                                tmp_G = {}
                                for param_idx, param in enumerate(csv_data.loc[row_idx]):
                                    if param != 'row_type' and not pd.isna(param) :
                                        try:
                                            tmp_G[param.strip()] = int(csv_data.loc[row_idx+next_non_comment_line_counter+counter][param_idx].strip())
                                        except ValueError:
                                            tmp_G[param.strip()] = csv_data.loc[row_idx+next_non_comment_line_counter+counter][param_idx].strip()
                                self.G.append(tmp_G)
                            counter += 1
                            if row_idx +next_non_comment_line_counter+ counter > csv_data.index.to_list()[-1]:
                                break

                    elif (csv_data.loc[row_idx + next_non_comment_line_counter][0] == 'S'):
                        counter = 0
                        while csv_data.loc[row_idx + next_non_comment_line_counter+counter][0] == 'S' or '#' in str(csv_data.loc[row_idx +next_non_comment_line_counter+ counter][0]):
                            if ('#' not in csv_data.loc[row_idx +next_non_comment_line_counter+ counter][0]): # pass the commented row
                                # self.S[str(counter)] = {}
                                tmp_S = {}
                                for param_idx, param in enumerate(csv_data.loc[row_idx]):
                                    if param != 'row_type' and not pd.isna(param):
                                        try:
                                            tmp_S[param.strip()] = int(csv_data.loc[row_idx+next_non_comment_line_counter+counter][param_idx].strip())
                                        except ValueError:
                                            tmp_S[param.strip()] = csv_data.loc[row_idx + next_non_comment_line_counter + counter][param_idx].strip()
                                self.S.append(tmp_S)
                            counter += 1
                            if row_idx +next_non_comment_line_counter+ counter > csv_data.index.to_list()[-1]:
                                break
                self.output = {'params': self.params, 'IN': self.IN, 'G': self.G, 'S': self.S}
            else:
                self.output['physio_data'] = []
                json_idx_counter = 0
                for var_idx,var  in enumerate(csv_data[csv_data.columns[0]]):
                    if not pd.isna(var) and not var.startswith('#') and var != 'Variable':
                        key = csv_data[csv_data.columns[1]][var_idx]
                        value = csv_data[csv_data.columns[2]][var_idx] if not pd.isna(csv_data[csv_data.columns[2]][var_idx]) else ""
                        comment = csv_data[csv_data.columns[3]][var_idx] if not pd.isna(csv_data[csv_data.columns[3]][var_idx]) else ""
                        if pd.isna(key)  : # this checks if the key is nan, which means it's a key/value pair
                            # var_val = {str(json_idx_counter): {"Variable" : var, "Value":value, "Comment":comment } }
                            # self.output.update(var_val)
                            try:
                                self.output['physio_data'].append({"Variable" : str(var).strip(" "),
                                                               "Value":int(value),
                                                               "Comment":comment })
                            except ValueError:
                                self.output['physio_data'].append({"Variable": str(var).strip(" "),
                                                                   "Value": str(value).strip(" "),
                                                                   "Comment": comment})
                        else:
                            counter = 0
                            tmp_var = []
                            while pd.isna(csv_data[csv_data.columns[0]][var_idx+counter+1]):
                                key = csv_data[csv_data.columns[1]][var_idx+counter]
                                value = csv_data[csv_data.columns[2]][var_idx+counter]
                                comment = csv_data[csv_data.columns[3]][var_idx+counter] if not pd.isna(csv_data[csv_data.columns[3]][var_idx+counter]) else ""
                                if not (pd.isna(key) and pd.isna(value) and comment == ""):
                                    try:
                                        key_val = {"Key" : str(key).strip(" "),
                                               "Value" : str(value),
                                               "Comment" : comment}
                                    except ValueError:
                                        key_val = {"Key": str(key).strip(" "),
                                                   "Value": str(value).strip(" "),
                                                   "Comment": comment}
                                    tmp_var.append(key_val)
                                counter+=1
                                if var_idx+counter+1 > csv_data.index.to_list()[-1]:
                                    break
                            self.output['physio_data'].append({"Variable" : str(var).strip(" "), "Key-Value" : tmp_var})
                        json_idx_counter += 1

            with open(self.new_filepath, 'w') as f:
                json.dump(self.output,f)


    def get_path_of_converted_file(self):
        assert self.new_filepath != '', "No file has been converted yet"
        return self.new_filepath
    
    def get_csv(self, clean = True):
        self.json_to_csv()
        if self.new_filepath.suffix == '.csv':
            csv_data = pandas.read_csv(self.new_filepath, header=None)
        else:
            csv_data = pandas.read_csv(self.original_path, header=None)
        if clean:
            self.clean()
        return csv_data

    def get_csv_from_json_data(self):
        with open(Path.home().joinpath('tmp.json'), 'w') as f:
            json.dump(self.json_data, f)
        self.original_path = Path.home().joinpath('tmp.json')
        self.directory = self.original_path.parent.absolute()
        self.filename_without_extension = self.original_path.stem
        self.json_to_csv()
        if self.new_filepath.suffix == '.csv':
            csv_data = pandas.read_csv(self.new_filepath, header=None)
        else:
            csv_data = pandas.read_csv(self.original_path, header=None)
        self.clean()
        os.remove(Path.home().joinpath('tmp.json'))
        return csv_data

    def get_json(self, clean = True):
        self.csv_to_json()
        if self.new_filepath.suffix == '.json':
            with open(self.new_filepath, 'r') as f:
                json_data = json.load(f)

        else:
            with open(self.original_path, 'r') as f:
                json_data = json.load(f)
        if clean:
            self.clean()
        return json_data

    def clean(self):
        os.remove(self.new_filepath)

    def save_as_json(self):
        self.get_json(clean=False)

    def save_as_csv(self):
        self.get_csv(clean=False)

if __name__ == '__main__':
    from pprint import pprint
    # p = Path('./tests/config_files/pytest_Anatomy_config.csv')
    # p = Path('./tests/config_files/pytest_Physiology_config.csv')
    # p = Path('./tests/config_files/pytest_Anatomy_config.json')
    # p = Path('./tests/config_files/pytest_Physiology_config.json')
    # p = Path('.\config_files\SimplifiedMarkram\Markram_Step1_Anatomy_config.csv')
    p = Path('.\config_files\SimplifiedMarkram\Markram_Step1_Physiology_config.csv')
    converter = filetype_converter(p)
    pprint(converter.save_as_json())
    # converter.save_as_csv()
    # pprint(converter.output)
