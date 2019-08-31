import pandas as pd
from pathlib import Path
from pprint import pprint
import json
import csv
import pandas
import os
'''
This file converts the two types of configuration files, i.e. CSV and JSON to each other. 
'''

class filetype_converter():
    def __init__(self,path):
        self.original_path = Path(path)
        self.directory = self.original_path.parent.absolute()
        self.filename_without_extension = self.original_path.stem
        self.output = {}
        self.params = {}
        self.IN = {}
        self.G = {}
        self.S = {}
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

            with open(self.original_path, 'r') as f:
                json_data = json.load(f)

            with open( self.new_filepath, 'w',newline='') as f:
                csvfile = csv.writer(f)
                if 'params' in json_data.keys():
                    csvfile.writerow(['row_type'] + list(json_data['params'].keys()))
                    csvfile.writerow(['params'] + list(json_data['params'].values()))

                    if 'IN' in json_data.keys():
                        csvfile.writerow(['row_type'] + list(json_data['IN']["0"].keys()))
                        for _, IN_data in json_data['IN'].items():
                            csvfile.writerow(['IN'] + list(IN_data.values()))
                        csvfile.writerow([])
                    if 'G' in json_data.keys():
                        csvfile.writerow(['row_type'] + list(json_data['G']["0"].keys()))
                        for _, G_data in json_data['G'].items():
                            csvfile.writerow(['G'] + list(G_data.values()))
                        csvfile.writerow([])
                    if 'S' in json_data.keys():
                        csvfile.writerow(['row_type'] + list(json_data['S']["0"].keys()))
                        for _, S_data in json_data['S'].items():
                            csvfile.writerow(['S'] + list(S_data.values()))
                        csvfile.writerow([])

                else:
                    csvfile.writerow(['Variable','Key', 'Value','Comment'])
                    for key, entry in json_data.items():
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

    def csv_to_json(self):
        if self.original_path.suffix == '.csv':
            new_filename = self.filename_without_extension + '.json'
            self.new_filepath = self.directory.joinpath(new_filename)
            counter = 1
            while self.new_filepath.is_file():
                new_filename = self.filename_without_extension + f'_{counter}' + '.json'
                self.new_filepath = self.directory.joinpath(new_filename)

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
                                self.params[param] = csv_data.loc[row_idx+1][param_idx]
                    elif (csv_data.loc[row_idx + next_non_comment_line_counter][0] == 'IN'):
                        counter = 0
                        while csv_data.loc[row_idx + next_non_comment_line_counter + counter][0] == 'IN' or '#' in str(csv_data.loc[row_idx + next_non_comment_line_counter + counter][0]):
                            if ('#' not in csv_data.loc[row_idx + next_non_comment_line_counter + counter][0]):  # pass the commented row
                                self.IN[str(counter)] = {}
                                for param_idx, param in enumerate(csv_data.loc[row_idx]):
                                    if param != 'row_type' and not pd.isna(param):
                                        self.IN[str(counter)][param] = csv_data.loc[row_idx + next_non_comment_line_counter + counter][param_idx]
                            counter += 1
                            if row_idx +next_non_comment_line_counter+ counter > csv_data.index.to_list()[-1]:
                                break


                    elif (csv_data.loc[row_idx + next_non_comment_line_counter][0] == 'G'):
                        counter = 0
                        while csv_data.loc[row_idx + next_non_comment_line_counter+ counter][0] == 'G' or '#' in str(csv_data.loc[row_idx +next_non_comment_line_counter+ counter][0]):
                            if ('#' not in csv_data.loc[row_idx + next_non_comment_line_counter + counter][0]): # pass the commented row
                                self.G[str(counter)] = {}
                                for param_idx, param in enumerate(csv_data.loc[row_idx]):
                                    if param != 'row_type' and not pd.isna(param) :
                                        self.G[str(counter)][param] = csv_data.loc[row_idx+next_non_comment_line_counter+counter][param_idx]
                            counter += 1
                            if row_idx +next_non_comment_line_counter+ counter > csv_data.index.to_list()[-1]:
                                break

                    elif (csv_data.loc[row_idx + next_non_comment_line_counter][0] == 'S'):
                        counter = 0
                        while csv_data.loc[row_idx + next_non_comment_line_counter+counter][0] == 'S' or '#' in str(csv_data.loc[row_idx +next_non_comment_line_counter+ counter][0]):
                            if ('#' not in csv_data.loc[row_idx +next_non_comment_line_counter+ counter][0]): # pass the commented row
                                self.S[str(counter)] = {}
                                for param_idx, param in enumerate(csv_data.loc[row_idx]):
                                    if param != 'row_type' and not pd.isna(param):
                                        self.S[str(counter)][param] = csv_data.loc[row_idx+next_non_comment_line_counter+counter][param_idx]
                            counter += 1
                            if row_idx +next_non_comment_line_counter+ counter > csv_data.index.to_list()[-1]:
                                break
                self.output = {'params': self.params, 'IN': self.IN, 'G': self.G, 'S': self.S}
            else:
                json_idx_counter = 0
                for var_idx,var  in enumerate(csv_data[csv_data.columns[0]]):
                    if not pd.isna(var) and not var.startswith('#') and var != 'Variable':
                        key = csv_data[csv_data.columns[1]][var_idx]
                        value = csv_data[csv_data.columns[2]][var_idx] if not pd.isna(csv_data[csv_data.columns[2]][var_idx]) else ""
                        comment = csv_data[csv_data.columns[3]][var_idx] if not pd.isna(csv_data[csv_data.columns[3]][var_idx]) else ""
                        if pd.isna(key)  : # this checks if the key is nan, which means it's a key/value pair
                            var_val = {str(json_idx_counter): {"Variable" : var, "Value":value, "Comment":comment } }
                            self.output.update(var_val)
                        else:
                            counter = 0
                            tmp_var = []
                            while pd.isna(csv_data[csv_data.columns[0]][var_idx+counter+1]):
                                key = csv_data[csv_data.columns[1]][var_idx+counter]
                                value = csv_data[csv_data.columns[2]][var_idx+counter]
                                comment = csv_data[csv_data.columns[3]][var_idx+counter] if not pd.isna(csv_data[csv_data.columns[3]][var_idx+counter]) else ""
                                if not (pd.isna(key) and pd.isna(value) and comment == ""):
                                    key_val = {"Key" : key, "Value" : value, "Comment" : comment}
                                    tmp_var.append(key_val)
                                counter+=1
                                if var_idx+counter+1 > csv_data.index.to_list()[-1]:
                                    break
                            self.output.update({str(json_idx_counter):{"Variable" : var, "Key-Value" : tmp_var}})
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
    # p = Path('./tests/config_files/pytest_Anatomy_config.csv')
    p = Path('./tests/config_files/pytest_Anatomy_config.json')
    # p = Path('./tests/config_files/pytest_Physiology_config.csv')
    # p = Path('./tests/config_files/pytest_Physiology_config.json')
    converter = filetype_converter(p)
    # converter.save_as_json()
    converter.save_as_csv()
    # pprint(converter.output)
