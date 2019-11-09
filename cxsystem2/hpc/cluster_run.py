#! /usr/bin/env python
# -*- coding: utf-8 -*-
__author__ = 'Andalibi, V., Hokkanen H., Vanni, S.'

'''
The preliminary version of this software has been developed at Aalto University 2012-2015, 
and the full version at the University of Helsinki 2013-2017. The software is distributed 
under the terms of the GNU General Public License. 
Copyright 2017 Vafa Andalibi, Henri Hokkanen and Simo Vanni.
'''

#import pip
from brian2 import *
import time
import shutil
import datetime
import os
import pickle as pickle
import getpass
import paramiko
from scp import SCPClient
from builtins import input
from sys import platform
from pathlib import Path
from cxsystem2.configuration import config_file_converter as fileconverter
from cxsystem2.core.exceptions import ParameterNotFoundError, ClusterNotReachableError, RelativePathError
import socket
from ping3 import ping
import pandas as pd

class cluster_run(object):

    def __init__(self, array_run_obj, anat_file_path, physio_file_path, suffix = ""):

        try:
            self.cluster_workspace = Path(self.parameter_finder(array_run_obj.anatomy_df, 'cluster_workspace'))
        except NameError:
            raise ParameterNotFoundError("cluster_workspace is not defined for running CxSystem on cluster")
        assert not self.cluster_workspace.is_absolute() , "cluster_workspace must be an absolute path with explicit [remote] home directory path"

        try:
            self.cluster_address = self.parameter_finder(array_run_obj.anatomy_df, 'cluster_address')
        except NameError:
            raise ParameterNotFoundError("cluster_address is not defined for running CxSystem on cluster")

        self.ping_cluster()

        try:
            self.cluster_username = self.parameter_finder(array_run_obj.anatomy_df, 'cluster_username')
            print ("Loggin in with user %s"%self.cluster_username)
        except NameError:
            self.cluster_username = input('cluster_username: ')
        try:
            self.password = self.parameter_finder(array_run_obj.anatomy_df, 'password')
        except NameError:
            self.password = getpass.getpass('password: ')


        # self.suffix =  '_' + str(datetime.datetime.now()).replace('-', '').replace(' ', '_').replace(':', '')[0:str(datetime.datetime.now()).replace('-', '').replace(' ', '_').replace(':', '').index('.')+3].replace('.','')
        self.suffix = suffix
        print (" -  temp file suffix is %s" %self.suffix)
        self.client = paramiko.SSHClient()
        self.client.load_system_host_keys()
        self.client.set_missing_host_key_policy(paramiko.WarningPolicy)
        self.client.connect(self.cluster_address, port=22, username=self.cluster_username, password=self.password)
        print(" -  Connected to %s"%self.cluster_address)

        print(" -  Creating workspace folder if not exists")
        self.ssh_commander('mkdir -p {}'.format(self.cluster_workspace.as_posix()))
        scp = SCPClient(self.client.get_transport())

        if 'json' in anat_file_path.suffix.lower():
            converter = fileconverter.filetype_converter(anat_file_path.as_posix())
            anat_file_path = Path(converter.save_as_csv(overwrite=True))
        if 'json' in physio_file_path.suffix.lower():
            converter = fileconverter.filetype_converter(physio_file_path.as_posix())
            physio_file_path = Path(converter.save_as_csv(overwrite=True))

        print(" -  Transferring configuration files ...")

        self.remote_anat_filename = '_tmp_anat_config{}.csv'.format(self.suffix)
        self.remote_phys_filename = '_tmp_physio_config{}.csv'.format(self.suffix)
        self.local_workspace = Path(self.parameter_finder(array_run_obj.anatomy_df, 'workspace_path')).expanduser()
        self.local_cluster_folder = self.local_workspace.joinpath('cluster_run' + self.suffix)
        if not self.local_cluster_folder.is_dir():
            os.mkdir(self.local_cluster_folder.as_posix())

        imported_connections_file = Path(self.parameter_finder(array_run_obj.anatomy_df, 'import_connections_from'))
        if imported_connections_file.is_file():
            scp.put(imported_connections_file.as_posix(), self.cluster_workspace.as_posix())
            new_path = Path('./').joinpath(imported_connections_file.name).as_posix()
            self.change_parameter_value_in_file(anat_file_path.as_posix(), self.local_cluster_folder.joinpath(anat_file_path.name), 'import_connections_from', new_path)
            anat_file_path = self.local_cluster_folder.joinpath(anat_file_path.name)
        scp.put(anat_file_path.as_posix(), self.cluster_workspace.joinpath(self.remote_anat_filename).as_posix())
        scp.put(physio_file_path.as_posix(), self.cluster_workspace.joinpath(self.remote_phys_filename).as_posix())

        # ask user to set the number of nodes, time and memory:
        print(" -  Please check the default slurm.job file and set the time, memory and uncomment and enter email address if you wish."
                  "\nNote that the number of nodes in default slurm file should always be set to 1. Instead you should enter the number of nodes in the CxSystem network config file. "
                  "\nAlso the default number of CPUs=16 does not need to be changed most of the times. ")




        self.slurm_file_path = Path(self.parameter_finder(array_run_obj.anatomy_df, 'cluster_job_file_path')).expanduser()
        if not self.slurm_file_path.is_file():
            if not self.slurm_file_path.is_absolute():
                raise RelativePathError("Slurm file path is not absolute")
            else:
                raise FileNotFoundError("Slurm file not found")
        # building slurm :
        for item_idx, item in enumerate(array_run_obj.clipping_indices):
            with open(self.slurm_file_path.as_posix(),'r') as sl1:
                remote_slurm_filename =  "_tmp_slurm{}_part{}.job".format(self.suffix , item_idx)
                with open (self.local_cluster_folder.joinpath(remote_slurm_filename).as_posix(), 'w') as sl2:  # wb -> w
                    for line in sl1:
                        sl2.write(line)
                    # for item_idx,item in enumerate(array_run_obj.clipping_indices):
                    try:
                        # sl2.write('python CxSystem.py _tmp_anat_config%s.csv _tmp_physio_config%s.csv %d %d\n'%(
                        #     self.suffix,self.suffix,item,array_run_obj.clipping_indices[item_idx+1]-array_run_obj.clipping_indices[item_idx]))
                        sl2.write("python -c "
                                  "\"from cxsystem2.core.cxsystem import CxSystem as cxs; "
                                  " cx = cxs('{anatomy}','{physio}', cluster_run_start_idx={cluster_start},cluster_run_step={cluster_step}); "
                                  "cx.run()\"".format(anatomy=self.remote_anat_filename,
                                                     physio=self.remote_phys_filename,
                                                     cluster_start=item,
                                                     cluster_step=array_run_obj.clipping_indices[item_idx+1]-array_run_obj.clipping_indices[item_idx]))
                    except IndexError:
                        # sl2.write('python CxSystem.py _tmp_anat_config%s.csv _tmp_physio_config%s.csv %d %d\n' % (
                        # self.suffix,self.suffix,item, array_run_obj.total_configs - array_run_obj.clipping_indices[item_idx]))
                        sl2.write("python -c "
                                  "\"from cxsystem2.core.cxsystem import CxSystem as cxs; "
                                  " cx = cxs('{anatomy}','{physio}', cluster_run_start_idx={cluster_start},cluster_run_step={cluster_step}); "
                                  "cx.run()\"".format(anatomy=self.remote_anat_filename,
                                                     physio=self.remote_phys_filename,
                                                     cluster_start=item,
                                                     cluster_step=array_run_obj.total_configs - array_run_obj.clipping_indices[item_idx]))

                    # sl2.write('wait\n')
            scp.put(self.local_cluster_folder.joinpath(remote_slurm_filename).as_posix(), self.cluster_workspace.joinpath(remote_slurm_filename).as_posix())
        print(" -  Slurm file generated and copied to cluster")
        self.channel = self.client.invoke_shell()
        self.channel.send('cd %s\n' % self.cluster_workspace.as_posix())
        for item_idx, item in enumerate(array_run_obj.clipping_indices):
            remote_slurm_filename = "_tmp_slurm{}_part{}.job".format(self.suffix, item_idx)
            if platform == 'win32':
                print(" -  Converting the file using dos2unix")
                self.channel.send('dos2unix {}\n'.format(remote_slurm_filename))
                time.sleep(1)
            self.channel.send('sbatch {}\n'.format(remote_slurm_filename))
            time.sleep(1)
        print(" -  Slurm job successfully submitted")
        cluster_metadata = {}
        cluster_metadata['cluster_address'] = self.cluster_address
        cluster_metadata['cluster_username'] = self.cluster_username
        cluster_metadata['local_workspace'] = self.local_workspace.as_posix()
        cluster_metadata['local_cluster_run_folder'] = self.local_cluster_folder.as_posix()
        cluster_metadata['local_cluster_run_download_folder'] = self.local_cluster_folder.joinpath('downloads')
        cluster_metadata['cluster_workspace'] = self.cluster_workspace.as_posix()
        cluster_metadata['cluster_simulation_folder'] = self.cluster_workspace.joinpath(self.parameter_finder(array_run_obj.anatomy_df, 'simulation_title')).as_posix()
        cluster_metadata['suffix'] = self.suffix
        with open (self.local_cluster_folder.joinpath('cluster_metadata{}.pkl'.format(self.suffix)), 'wb') as ff:
            pickle.dump(cluster_metadata,ff)
        print(" -  Cluster metadata saved. To download the result and clean the environments after getting the email, run 'python cluster_run.py'\n" \
              "Alternatively you can run it in another terminal and it will "
               "do its job when the results are ready.")

    def ping_cluster(self):
        try: # check if the cluster address is ip or hostname
            socket.inet_aton(self.cluster_address)
            self.cluster_ip = self.cluster_address
        except OSError:
            self.cluster_ip = socket.gethostbyname(self.cluster_address)
        p = ping(self.cluster_ip, timeout=3)
        if not p:
            raise ClusterNotReachableError("Cluster node is not reachable")

    def ssh_commander(self,command,print_flag=False):
        stdin, stdout, stderr = self.client.exec_command(command,get_pty=True)
        out= stdout.read(),
        if print_flag is True:
            print(out[0])
        return out[0]

    def parameter_finder(self,df,keyword):
        location = where(df.values == keyword)
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

    def change_parameter_value_in_file(self,filepath, save_path, parameter,new_value):
        df = pd.read_csv(filepath, header=None)
        location = where(df.values == parameter)
        if location[0].size == 1:
            df.at[int(location[0] + 1), int(location[1])] = new_value
            df.to_csv(save_path,header=False,index=False)
        elif location[0].size == 1:
            raise ParameterNotFoundError('Parameter {} not found in the configuration file.'.format(parameter))
        else:
            raise ParameterNotFoundError('More than one instance of parameter {} found, cannot chagne the value'.format(parameter))


class cluster_downlaod(object):
    def __init__(self, metapath):
        self.metadata_path = Path(metapath)
        if not self.metadata_path.is_file():
            raise FileNotFoundError("Cluster run metadata file not found: {}".format(self.metadata_path.as_posix()))
        self.metadata = self.load_metadata()
        self.connect_ssh_client()

        time.sleep(1)
        if not Path(self.metadata['local_workspace']).is_dir():
            os.mkdir(self.metadata['local_workspace'])
        self.retrieve()

    def ssh_commander(self, client, command, print_flag):
        stdin, stdout, stderr = client.exec_command(command)
        out = stdout.read(),
        if print_flag:
            print(out[0])
        return out[0]

    def load_metadata(self):
        with open(self.metadata_path.as_posix(), 'rb') as f:
            return pickle.load(f)

    def connect_ssh_client(self):
        self.client = paramiko.SSHClient()
        self.client.load_system_host_keys()
        self.client.set_missing_host_key_policy(paramiko.WarningPolicy)
        self.password = getpass.getpass('password: ')
        self.client.connect(self.metadata['cluster_address'], port=22, username=self.metadata['cluster_username'],
                       password=self.password)
        self.scpclient = SCPClient(self.client.get_transport())

    def retrieve(self):
        waiting_flag = True
        print(" -  Waiting for the results ...")
        if not self.metadata['local_cluster_run_download_folder'].is_dir():
            os.mkdir(self.metadata['local_cluster_run_download_folder'].as_posix())
        while waiting_flag:
            # if not ssh_commander(client,'cd %s; ls -d */' % (remote_result_abs_path), 0) and 'metadata' in ssh_commander(client,'cd %s; ls' % (remote_result_abs_path), 0):
            # just a better check:
            if not self.metadata['cluster_username'] in self.ssh_commander(self.client, 'squeue -l -u {}'.format(self.metadata['cluster_username']), 0).decode('utf-8'):
                # here it means there is no folder in result folder and therefore all simulations are done
                # so we copy back the result and remove the files on cluster
                print(" -  Copying the results from cluster...")
                for item in self.ssh_commander(self.client, 'cd {}; ls'.format(self.metadata['cluster_simulation_folder']), 0).decode('utf-8').split('\n'):
                    if item != '' and self.metadata['suffix'] in item:
                        self.scpclient.get(Path(self.metadata['cluster_simulation_folder']).joinpath(item).as_posix(), Path(self.metadata['local_cluster_run_download_folder']).joinpath(item).as_posix())
                # cleaning
                # self.ssh_commander(self.client, 'rm -rf {}'.format(self.metadata['cluster_workspace']), 0)
                waiting_flag = False
            time.sleep(1)
        self.client.close()
        # print(" -  Results are downloaded and remote is cleaned.")
        # print(" -  Local environment cleaned.")
        print(" -  Downloads are available in: {}".format(self.metadata['local_cluster_run_download_folder']))

if __name__ == '__main__':
    d = cluster_downlaod("C:\\Users\\vafaa\\CxPytestWorkspace\\cluster_run_20191108_21451786\\cluster_metadata_20191108_21451786.pkl")
