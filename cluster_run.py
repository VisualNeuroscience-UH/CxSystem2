#! /usr/bin/env python
# -*- coding: utf-8 -*-
__author__ = 'Andalibi, V., Hokkanen H., Vanni, S.'

'''
The preliminary version of this software has been developed at Aalto University 2012-2015, 
and the full version at the University of Helsinki 2013-2017. The software is distributed 
under the terms of the GNU General Public License. 
Copyright 2017 Vafa Andalibi, Henri Hokkanen and Simo Vanni.
'''

import pip
import sys
import CxSystem as CX
from brian2 import *
import multiprocessing
import time
import shutil
import datetime
import os
import pandas as pd
import zlib
import bz2
import pickle as pickle
import sys
import itertools
import getpass
import paramiko
from scp import SCPClient
from builtins import input

class cluster_run(object):

    def __init__(self,array_run_obj, anat_file_address,physio_file_address):

        self.output_path_and_filename = self.parameter_finder(array_run_obj.anatomy_df, 'output_path_and_filename')
        try:
            self.remote_output_folder = self.parameter_finder(array_run_obj.anatomy_df, 'remote_output_folder')
        except NameError:
            # print(" -    remote_output_folder is not defined in the
            # configuration file, the default path is ./results [in cluster]")
            raise Exception("remote_output_folder is not defined for running CxSystem on cluster")
            # self.remote_output_folder = "./results"
        assert not str.startswith(self.remote_output_folder,'.') and not str.startswith(self.remote_output_folder,'~'),"remote_output_folder must be an absolute path with explicit home directory path"
        try:
            self.remote_repo_path = self.parameter_finder(array_run_obj.anatomy_df, 'remote_repo_path')
        except NameError:
            # print(" -    remote_repo_path is not defined in the
            # configuration file, the default value is home directory ~")
            # self.remote_repo_path = "."
            raise Exception("remote_repo_path is not defined for running CxSystem on cluster")
        assert not str.startswith(self.remote_repo_path,'.'),"remote_repo_path must be an apsolute path"
        try:
            self.cluster_address = self.parameter_finder(array_run_obj.anatomy_df, 'cluster_address')
        except NameError:
            raise Exception("cluster_address is not defined for running CxSystem on cluster")
        try:
            self.remote_branch = self.parameter_finder(array_run_obj.anatomy_df, 'remote_branch')
        except NameError:
            print (" -    remote_branch is not defined in the configuration file, the default value is master")
            self.remote_branch = "master"
        try:
            self.username = self.parameter_finder(array_run_obj.anatomy_df, 'username')
            print ("Loggin in with user %s"%self.username)
        except NameError:
            self.username = input('username: ')
        self.password = getpass.getpass('password: ')
        self.suffix =  '_' + str(datetime.datetime.now()).replace('-', '').replace(' ', '_').replace(':', '')[0:str(datetime.datetime.now()).replace('-', '').replace(' ', '_').replace(':', '').index('.')+3].replace('.','')
        print (" -  temp file suffix is %s" %self.suffix)
        self.client = paramiko.SSHClient()
        self.client.load_system_host_keys()
        self.client.set_missing_host_key_policy(paramiko.WarningPolicy)
        self.client.connect(self.cluster_address, port=22, username=self.username, password=self.password)
        print(" -  Connected to %s"%self.cluster_address)
        scp = SCPClient(self.client.get_transport())
        ls_result = str(self.ssh_commander('cd %s;ls'%self.remote_repo_path,0))
        if 'CxSystem.py' in ls_result: # path is to CxSystem folder
            pass
        elif 'CxSystem' in ls_result and "No such file or directory" not in ls_result: # path is to CxSystem root folder
            self.remote_repo_path = os.path.join(self.remote_repo_path, 'CxSystem')
        else: # no CxSystem ==> cloning the repo
            if self.remote_repo_path.endswith('CxSystem'):
                self.remote_repo_path = self.remote_repo_path.rstrip('/CxSystem')
            self.ssh_commander('mkdir %s;cd %s;git clone https://github.com/VisualNeuroscience-UH/CxSystem;cd CxSystem; git checkout %s' % (self.remote_repo_path,self.remote_repo_path,self.remote_branch),0)
            self.remote_repo_path = self.remote_repo_path +  '/CxSystem'
            print(" -  CxSystem cloned in cluster.")
        scp.put(anat_file_address, self.remote_repo_path+ '/_tmp_anat_config%s.csv' % self.suffix)
        scp.put(physio_file_address, self.remote_repo_path + '/_tmp_physio_config%s.csv' % self.suffix)
        print(" -  config files transfered to cluster")
        # ask user to set the number of nodes, time and memory:
        input(" -  Please check the default slurm.job file and set the time, memory and uncomment and enter email address if you wish."
                  "\nNote that the number of nodes in default slurm file should always be set to 1. Instead you should enter the number of nodes in the CxSystem network config file. "
                  "\nAlso the default number of CPUs=16 does not need to be changed most of the times. "
                  "\nPress a key to continue ...")
        if not os.path.exists('./_cluster_tmp'.replace('/',os.sep)):
            os.mkdir('./_cluster_tmp'.replace('/',os.sep))
            print(" -  _cluster_tmp folder created locally to keep the "
                   "necessary information for retrieving the results in the "
                   "future.")
        # building slurm :
        for item_idx, item in enumerate(array_run_obj.clipping_indices):
            with open("./slurm.job".replace('/',os.sep),'r') as sl1:
                with open ("./_cluster_tmp/_tmp_slurm_%d.job".replace('/',os.sep)%item_idx,'w') as sl2:  # wb -> w
                    for line in sl1:
                        sl2.write(line)
                    # for item_idx,item in enumerate(array_run_obj.clipping_indices):
                    try:
                        sl2.write('python CxSystem.py _tmp_anat_config%s.csv _tmp_physio_config%s.csv %d %d\n'%(
                            self.suffix,self.suffix,item,array_run_obj.clipping_indices[item_idx+1]-array_run_obj.clipping_indices[item_idx]))
                    except IndexError:
                        sl2.write('python CxSystem.py _tmp_anat_config%s.csv _tmp_physio_config%s.csv %d %d\n' % (
                        self.suffix,self.suffix,item, array_run_obj.total_configs - array_run_obj.clipping_indices[item_idx]))
                    # sl2.write('wait\n')
            scp.put('./_cluster_tmp/_tmp_slurm_%d.job'.replace('/',os.sep)%item_idx, self.remote_repo_path + '/_tmp_slurm_%d.job'%item_idx)
        print(" -  Slurm file generated and copied to cluster")
        self.chan = self.client.invoke_shell()
        self.chan.send('cd %s\n'%self.remote_repo_path)
        for item_idx, item in enumerate(array_run_obj.clipping_indices):
            self.chan.send('sbatch _tmp_slurm_%d.job\n' %item_idx)
            time.sleep(1)
        print(" -  Slurm job successfully submitted")
        checker_data = {}
        checker_data['cluster_address'] = self.cluster_address
        checker_data['username'] = self.username
        checker_data['local_folder'] = os.path.dirname(self.output_path_and_filename)
        checker_data['remote_repo_path'] = self.remote_repo_path
        checker_data['remote_output_folder'] = self.remote_output_folder
        checker_data['remote_repo_path'] = self.remote_repo_path
        with open ('./_cluster_tmp/_tmp_checker_data.pkl'.replace('/',os.sep),'wb') as ff:
            pickle.dump(checker_data,ff)
        print(" -  _tmp_checker_data saved. To download the result and clean the environments after getting the email, run 'python cluster_run.py'\n" \
              "Alternatively you can run it in another terminal and it will "
               "do its job when the results are ready.")


    def ssh_commander(self,command,print_flag):
        stdin, stdout, stderr = self.client.exec_command(command,get_pty=True)
        out= stdout.read(),
        if print_flag:
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


if __name__ == '__main__':
    def ssh_commander(client, command, print_flag):
        stdin, stdout, stderr = client.exec_command(command)
        out = stdout.read(),
        if print_flag:
            print(out[0])
        return out[0]
    with open('./_cluster_tmp/_tmp_checker_data.pkl'.replace('/',os.sep),'rb') as ff:
        checker_data = pickle.load(ff)
    client = paramiko.SSHClient()
    client.load_system_host_keys()
    client.set_missing_host_key_policy(paramiko.WarningPolicy)
    password = getpass.getpass('password: ')
    client.connect(checker_data['cluster_address'], port=22, username=checker_data['username'], password=password)
    scp = SCPClient(client.get_transport())
    # print(" -  Checker_downloader_cleaner Connected to
    # %s"%self.cluster_address)
    time.sleep(1)
    if not os.path.isdir(checker_data['local_folder']):
        os.mkdir(checker_data['local_folder'])
   # remote_result_abs_path = ssh_commander(client,'cd %s;cd %s; pwd' % (checker_data['remote_repo_path'],checker_data['remote_output_folder']), 0).rstrip('\r\n')
    remote_result_abs_path = checker_data['remote_output_folder']

    waiting_flag = True
    print(" -  Waiting for the results ...")
    while waiting_flag:
        # if not ssh_commander(client,'cd %s; ls -d */' % (remote_result_abs_path), 0) and 'metadata' in ssh_commander(client,'cd %s; ls' % (remote_result_abs_path), 0):
        # just a better check:
        if not checker_data['username'] in ssh_commander(client, 'squeue -l -u %s' % checker_data['username'], 0):
            # here it means there is no folder in result folder and therefore all simulations are done
            # so we copy back the result and remove the files on cluster
            print(" -  Copying the results from cluster...")
            for item in ssh_commander(client, 'cd %s; ls' % (remote_result_abs_path), 0).split('\n'):
                if item != '':
                    scp.get( remote_result_abs_path + '/' + item, os.path.join(checker_data['local_folder'], item))
            # cleaning
            ssh_commander(client, 'cd %s; rm auto_cluster_job*;rm _tmp_*;rm -rf %s' % (
            checker_data['remote_repo_path'], remote_result_abs_path), 0)
            waiting_flag = False
        time.sleep(1)
    client.close()
    print(" -  Results are downloaded and remote is cleaned.")
    shutil.rmtree('./_cluster_tmp'.replace('/',os.sep))
    print(" -  Local environment cleaned.")
    print(" -  Results available in: %s" % checker_data['local_folder'])
