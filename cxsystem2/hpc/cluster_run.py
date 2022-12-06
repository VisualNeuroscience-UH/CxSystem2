#! /usr/bin/env python
# -*- coding: utf-8 -*-
__author__ = 'Andalibi, V., Hokkanen H., Vanni, S.'

'''
The preliminary version of this software has been developed at Aalto University 2012-2015, 
and the full version at the University of Helsinki 2013-2017. The software is distributed 
under the terms of the GNU General Public License. 
Copyright 2017 Vafa Andalibi, Henri Hokkanen and Simo Vanni.
'''

import getpass
import os
import pickle as pickle
import socket
import time
from builtins import input
from pathlib import Path, PurePosixPath
from sys import platform
from packaging import version

import paramiko
from ping3 import ping
from scp import SCPClient
from datetime import datetime

from cxsystem2.configuration import config_file_converter as fileconverter
from cxsystem2.core.exceptions import ParameterNotFoundError, ClusterNotReachableError, RelativePathError
from cxsystem2.core.tools import parameter_finder, change_anat_file_header_value


class ClusterRun:

    def __init__(self,
                 array_run_obj,
                 anat_file_path,
                 physio_file_path,
                 suffix=""):

        try:
            self.cluster_workspace = PurePosixPath(parameter_finder(array_run_obj.anatomy_df, 'cluster_workspace'))
        except NameError:
            raise ParameterNotFoundError("cluster_workspace is not defined for running CxSystem on cluster")
        assert self.cluster_workspace.is_absolute(), \
            "cluster_workspace {} must be an absolute path with explicit [remote] home directory path".format(self.cluster_workspace.as_posix())

        try:
            self.cluster_repospace = PurePosixPath(parameter_finder(array_run_obj.anatomy_df, 'remote_repo_path'))
            assert self.cluster_repospace.is_absolute(), \
                "remote_repo_path {} must be an absolute path with explicit [remote] home directory path".format(self.remote_repo_path.as_posix())
        except NameError:
            print(' -  Remote_repo_path not found, assuming remote_repo_path = [cluster_workspace]/CxSystem2') # inside method update_remote_cxsystem2
            self.cluster_repospace = None

        try:
            self.cluster_address = parameter_finder(array_run_obj.anatomy_df, 'cluster_address')
        except NameError:
            raise ParameterNotFoundError("cluster_address is not defined for running CxSystem on cluster")

        try:
            self.cluster_login_node = parameter_finder(array_run_obj.anatomy_df, 'cluster_login_node')
        except NameError:
            print(" -  No cluster login node found. Directly conencting to cluster address {}".format(self.cluster_address))
            self.cluster_login_node = '--'

        # # the following call will check if the cluster is available or not, but it needs root access
        # self.ping_cluster()

        try:
            self.cluster_username = parameter_finder(array_run_obj.anatomy_df, 'cluster_username')
            assert self.cluster_username != 'username', \
                "Cluster username must be changed in the configuration file, currently it is the default value 'username'"
            print(" -  Loggin in with user '%s'" % self.cluster_username)
        except NameError:
            self.cluster_username = input(' -  Enter cluster username: ')
        try:
            self.password = parameter_finder(array_run_obj.anatomy_df, 'password')
        except NameError:
            if 'CLUSTERPASS' in os.environ.keys():
                self.password = os.environ['CLUSTERPASS']
            else:
                self.password = getpass.getpass(' -  Enter password for user {}: '
                                                ''.format(self.cluster_username))

        self.suffix = suffix
        print(" -  temp file suffix is %s" % self.suffix)
        self.client = paramiko.SSHClient()
        self.client.load_system_host_keys()
        self.client.set_missing_host_key_policy(paramiko.AutoAddPolicy())
        if self.cluster_login_node != '--':
            print(" -  Connecting to login node {}".format(self.cluster_login_node))
            sock = paramiko.ProxyCommand("ssh {}@{} nc {} 22".format(self.cluster_username,
                                                                     self.cluster_login_node,
                                                                     self.cluster_address))
            sock.settimeout(30)
            self.client.connect(self.cluster_address,
                                port=22,
                                username=self.cluster_username,
                                password=self.password,
                                sock=sock)
        else:
            self.client.connect(self.cluster_address,
                                port=22,
                                username=self.cluster_username,
                                password=self.password)

        print(" -  Connected to %s" % self.cluster_address)
        print(f" -  Creating workspace folder ({self.cluster_workspace}) if not exists")
        self.ssh_commander('mkdir -p {}'.format(self.cluster_workspace.as_posix()))
        scp = SCPClient(self.client.get_transport())

        if 'json' in anat_file_path.suffix.lower():
            converter = fileconverter.ConfigConverter(anat_file_path.as_posix())
            anat_file_path = Path(converter.save_as_csv(overwrite=True))
        if 'json' in physio_file_path.suffix.lower():
            converter = fileconverter.ConfigConverter(physio_file_path.as_posix())
            physio_file_path = Path(converter.save_as_csv(overwrite=True))

        print(" -  Transferring configuration files ...")

        self.remote_anat_filename = '_tmp_anat_config{}.csv'.format(self.suffix)
        self.remote_phys_filename = '_tmp_physio_config{}.csv'.format(self.suffix)
        self.local_workspace_unexpanded = Path(parameter_finder(array_run_obj.anatomy_df, 'workspace_path'))
        self.local_workspace = Path(parameter_finder(array_run_obj.anatomy_df, 'workspace_path')).expanduser()
        self.local_cluster_folder = self.local_workspace.joinpath('cluster_run' + self.suffix)
        if not self.local_cluster_folder.is_dir():
            os.mkdir(self.local_cluster_folder.as_posix())
        try:
            imported_connections_file = Path(parameter_finder(array_run_obj.anatomy_df, 'import_connections_from'))
            if imported_connections_file.is_file():
                scp.put(imported_connections_file.as_posix(), self.cluster_workspace.as_posix())
                new_path = Path('./').joinpath(imported_connections_file.name).as_posix()
                change_anat_file_header_value(anat_file_path.as_posix(), self.local_cluster_folder.joinpath(anat_file_path.name),
                                               'import_connections_from', new_path)
                anat_file_path = self.local_cluster_folder.joinpath(anat_file_path.name)
        except TypeError:  # this is when the value is # or -- for instance
            pass
        scp.put(anat_file_path.as_posix(), self.cluster_workspace.joinpath(self.remote_anat_filename).as_posix())
        scp.put(physio_file_path.as_posix(), self.cluster_workspace.joinpath(self.remote_phys_filename).as_posix())

        # ask user to set the number of nodes, time and memory:
        print(" -  Please check the default csc_puhti.job file and set the time, memory and uncomment and enter email address if you wish."
              "\nNote that the number of nodes in default slurm file should always be set to 1."
              " Instead you should enter the number of nodes in the CxSystem network config file. "
              "\nAlso the default number of CPUs=16 does not need to be changed most of the times. ")

        self.slurm_file_path = Path(parameter_finder(array_run_obj.anatomy_df, 'cluster_job_file_path')).expanduser()
        if not self.slurm_file_path.is_file():
            if not self.slurm_file_path.is_absolute():
                raise RelativePathError("\nSlurm file {} not found in local workspace. Make sure the path to the file is "
                                        "absolute".format(self.slurm_file_path.as_posix()))
            else:
                raise FileNotFoundError("\nSlurm file {} not found".format(self.slurm_file_path.as_posix()))

        # updating remote cxsystem2. Comment to skip version check.
        self.update_remote_cxsystem2(self.slurm_file_path, self.cluster_workspace, self.cluster_repospace) 

        # building slurm files. This includes the cxsystem call for each job file at cluster. The cxsystem parameters, including idx to array, is defined here.
        for item_idx, item in enumerate(array_run_obj.clipping_indices):
            with open(self.slurm_file_path.as_posix(), 'r') as sl1:
                remote_slurm_filename = "_tmp_slurm{}_part{}.job".format(self.suffix, item_idx)
                with open(self.local_cluster_folder.joinpath(remote_slurm_filename).as_posix(), 'w') as sl2:  # wb -> w
                    for line in sl1:
                        sl2.write(line)
                    
                    # Append command to launch one of the jobs with correct item index (parameter).
                    try:
                        sl2.write("python -c "
                                  "\"from cxsystem2.core.cxsystem import CxSystem as cxs; "
                                  " cx = cxs('{anatomy}','{physio}', cluster_run_start_idx={cluster_start},cluster_run_step={cluster_step}); "
                                  "cx.run()\"".format(anatomy=self.remote_anat_filename,
                                                      physio=self.remote_phys_filename,
                                                      cluster_start=item,
                                                      cluster_step=array_run_obj.clipping_indices[item_idx + 1] - array_run_obj.clipping_indices[
                                                          item_idx]))
                    except IndexError:
                        sl2.write("python -c "
                                  "\"from cxsystem2.core.cxsystem import CxSystem as cxs; "
                                  " cx = cxs('{anatomy}','{physio}', cluster_run_start_idx={cluster_start},cluster_run_step={cluster_step}); "
                                  "cx.run()\"".format(anatomy=self.remote_anat_filename,
                                                      physio=self.remote_phys_filename,
                                                      cluster_start=item,
                                                      cluster_step=array_run_obj.total_configs - array_run_obj.clipping_indices[item_idx]))

            scp.put(self.local_cluster_folder.joinpath(remote_slurm_filename).as_posix(),
                    self.cluster_workspace.joinpath(remote_slurm_filename).as_posix())
        print(" -  Slurm file generated and copied to cluster")

        # Now the job files are launched at the remote cluster with sbatch slurm command
        self.channel = self.client.invoke_shell()
        for item_idx, item in enumerate(array_run_obj.clipping_indices):
            remote_slurm_filename = "_tmp_slurm{}_part{}.job".format(self.suffix, item_idx)
            if platform == 'win32':
                print(" -  Converting the file using dos2unix")
                self.channel.send('cd {} && dos2unix {}\n'.format(self.cluster_workspace.as_posix(), remote_slurm_filename))
                time.sleep(1)
            self.channel.send('cd {} && sbatch {}\n'.format(self.cluster_workspace.as_posix(), remote_slurm_filename))
            print(" -  Job file {} submitted".format(remote_slurm_filename))
            time.sleep(1)

        cluster_metadata = \
            {'cluster_address': self.cluster_address,
             'cluster_login_node': self.cluster_login_node,
             'cluster_username': self.cluster_username,
             'local_workspace_unexpanded': self.local_workspace_unexpanded.as_posix(),
             'local_workspace': self.local_workspace.as_posix(),
             'local_cluster_run_folder': self.local_cluster_folder.as_posix(),
             'local_cluster_run_download_folder': self.local_cluster_folder.joinpath('downloads').as_posix(),
             'cluster_workspace': self.cluster_workspace.as_posix(),
             'cluster_simulation_folder': self.cluster_workspace.joinpath(parameter_finder(array_run_obj.anatomy_df, 'simulation_title')).as_posix(),
             'suffix': self.suffix,
             'timestamp': datetime.now().strftime('%Y-%m-%d %H:%M:%S.%f')[:-7]}
        
        with open(self.local_cluster_folder.joinpath('cluster_metadata{}.pkl'.format(self.suffix)), 'wb') as ff:
            pickle.dump(cluster_metadata, ff)
        print(" -  Cluster metadata saved. To download the result and clean the environments after getting the email,"
              " run the following command in the terminal:\n")
        metadata_path = self.local_cluster_folder.joinpath('cluster_metadata{}.pkl'.format(self.suffix))
        print("cxcluster " + metadata_path.as_posix())

        # # TMP AUTOMATIC DOWNLOADING FROM HPC SIMO 211005
        # ClusterDownloader(metadata_path.as_posix(), clean_remote=True, retrieve=True)

    def ping_cluster(self):
        try:  # check if the cluster address is ip or hostname
            socket.inet_aton(self.cluster_address)
            cluster_ip = self.cluster_address
        except OSError:
            cluster_ip = socket.gethostbyname(self.cluster_address)
        p = ping(cluster_ip, timeout=3)
        if not p:
            raise ClusterNotReachableError("Cluster node is not reachable")

    def ssh_commander(self,
                      command,
                      print_flag=False):
        stdin, stdout, stderr = self.client.exec_command(command, get_pty=True)
        out = stdout.read(),
        if print_flag is True:
            print(out[0])
        return out[0]

    def update_remote_cxsystem2(self,
                                slurm_path,
                                remote_workspace,
                                remote_repospace=None):
        slurm_path = Path(slurm_path)
        remote_workspace = Path(remote_workspace)
        module_name, venv_activation = self.find_remote_python_module(slurm_path) # This examines slurm job file
        self.ssh_commander('mkdir -p {}'.format(self.cluster_workspace.as_posix()))

        # Query for valid cxsystem, install/update if necessary, report
        print(" -  Checking CxSystem2 on cluster")

        # Check installation in current environment. Remote environment should be set in .bashrc or in slurm job file on the cluster.
        # TODO Version check does not skip reinstallation, fix. Clear code, now somewhat spagetti
        first_cxsystem_version_for_virtual_env = '2.1.0.0'

        cxsystem_version_rawstring = self.ssh_commander(  f'source ~/.bashrc ; {venv_activation}; cxsystem2 -v')
        cxsystem_version_string = cxsystem_version_rawstring.decode("utf-8")
        cxsystem_version_string = cxsystem_version_string.strip('\r\n')
        # cxsystem_version = cxsystem_version_string.removeprefix('CxSystem2 Version ')
        cxsystem_version = cxsystem_version_string[18:]
        if version.parse(cxsystem_version) >= version.parse(first_cxsystem_version_for_virtual_env):
            git_repo_error_message = ''
            print(f" -  Found CxSystem2 version {cxsystem_version} installed")
            installed_repo_init_module = self.ssh_commander(  'source ~/.bashrc ; python -c "import cxsystem2; print(cxsystem2.__file__)"').decode('utf-8')
            if str(remote_repospace.as_posix()) not in installed_repo_init_module:
                print(f" -  NOTE {str(remote_repospace)} not in {installed_repo_init_module}, best to re-install")
                git_repo_error_message = 'not empty'
            
        else:
            remote_repospace = remote_workspace / 'CxSystem2'
            # Should be empty string for existing git repo
            git_repo_error_message = self.ssh_commander('source ~/.bash_profile ; '
                                    'source ~/.bashrc ; '
                                    'cd {repospace} ; '
                                    'git -C . rev-parse'.format(repospace=remote_repospace.as_posix())).decode('utf-8')
        if not git_repo_error_message:
            git_basename = self.ssh_commander(
                                    'cd {repospace} ; '
                                    'git rev-parse --show-toplevel'.format(repospace=remote_repospace.as_posix())).decode('utf-8')
            commit_HEAD_hash = self.ssh_commander('cd {repospace} ; '
                                    'git rev-parse --short HEAD'.format(repospace=remote_repospace.as_posix())).decode('utf-8')
            git_branch = self.ssh_commander('cd {repospace} ; '
                                    'git rev-parse --abbrev-ref HEAD'.format(repospace=remote_repospace.as_posix())).decode('utf-8')
            print(f" -  The git repo is {git_basename}    branch is {git_branch}    commit HEAD hash is {commit_HEAD_hash}")
            print(f" -  No need to download/install")
        else:
            print(" -  Updating CxSystem2 on cluster")
            print(self.ssh_commander('source ~/.bash_profile ; '
                                    'source ~/.bashrc ; '
                                    'cd {workspace} ; '
                                    'git clone https://github.com/VisualNeuroscience-UH/CxSystem2 ; '
                                    'cd CxSystem2 ; '
                                    'git pull ; '.format(workspace=remote_workspace.as_posix())).decode('utf-8'))
            if module_name:
                print(self.ssh_commander('bash -lc \''
                                        'source ~/.bash_profile ; '
                                        'source ~/.bashrc ; '
                                        'echo $PATH; '
                                        'module load {module} ;'
                                        'cd {cxfolder} ; '
                                        'python -m pip install -Ue . --user\''
                                        .format(module=module_name, cxfolder=remote_workspace.joinpath('CxSystem2').as_posix())).decode('utf-8'))
            elif venv_activation:
                print(self.ssh_commander('bash -lc \''
                                        'source ~/.bash_profile ; '
                                        'source ~/.bashrc ; '
                                        'echo $PATH; '
                                        '{venv} ;'
                                        'cd {cxfolder} ; '
                                        'python -m pip install -Ue . --user\''
                                        .format(venv=venv_activation, cxfolder=remote_workspace.joinpath('CxSystem2').as_posix())).decode('utf-8'))

    def find_remote_python_module(self,
                                  slurm_path):
        module_name = ''
        venv_activation = ''
        slurm_path = Path(slurm_path)
        with open(slurm_path.as_posix()) as f:
            for line in f:
                if 'module load' in line.lower() and 'python' in line.lower():
                    module_name = line.split(' ')[-1].strip('\n')
                elif 'conda activate' in line.lower() or ('source' in line.lower() and 'activate' in line.lower()):
                    venv_activation = line.strip('\n')

        if module_name and venv_activation:
            print('NOTE: You have both virtual environment activation and module load strings in your slurm job file, setting module priority')
            venv_activation = ''
        
        if module_name:
            print(" -  Remote module name is {}".format(module_name))
        if venv_activation:
            print(" -  Remote virtual environment is activated with command {}".format(venv_activation))
        return module_name, venv_activation


class ClusterDownloader:
    def __init__(self, metapath, clean_remote=False, retrieve=True):
        self.metadata_path = Path(metapath)
        if not self.metadata_path.is_file():
            raise FileNotFoundError("Cluster run metadata file not found: {}".format(self.metadata_path.as_posix()))
        self.metadata = self.load_metadata()
        submission_time = datetime.strptime(self.metadata['timestamp'], '%Y-%m-%d %H:%M:%S')
        time_diff = datetime.now() - submission_time
        # let's wait for at least 30 seconds after job submissions and then look for results
        while time_diff.seconds < 5:
            time.sleep(1)
            time_diff = datetime.now() - submission_time
        self.client = paramiko.SSHClient()
        self.client.load_system_host_keys()
        self.client.set_missing_host_key_policy(paramiko.AutoAddPolicy())
        if 'CLUSTERPASS' in os.environ.keys():
            self.password = os.environ['CLUSTERPASS']
        else:
            self.password = getpass.getpass('Enter password for user {}: '.format(self.metadata['cluster_username']))
        if self.metadata['cluster_login_node'] != '--':
            print(" -  Connecting to login node {}".format(self.metadata['cluster_login_node']))
            sock = paramiko.ProxyCommand("ssh {}@{} nc {} 22".format(self.metadata['cluster_username'],
                                                                     self.metadata['cluster_login_node'],
                                                                     self.metadata['cluster_address']))
            sock.settimeout(30)
            self.client.connect(self.metadata['cluster_address'],
                                port=22,
                                username=self.metadata['cluster_username'],
                                password=self.password,
                                sock=sock)
        else:
            self.client.connect(self.metadata['cluster_address'],
                                port=22,
                                username=self.metadata['cluster_username'],
                                password=self.password)

        self.scpclient = SCPClient(self.client.get_transport())
        time.sleep(1)
        if not Path(self.metadata['local_workspace']).is_dir():
            os.mkdir(self.metadata['local_workspace'])
        if retrieve:
            self.retrieve()
        if clean_remote:
            self.clean_remote()
        self.client.close()

    @staticmethod
    def ssh_commander(client,
                      command,
                      print_flag):
        stdin, stdout, stderr = client.exec_command(command)
        out = stdout.read(),
        if print_flag:
            print(out[0])
        return out[0]

    def load_metadata(self):
        with open(self.metadata_path.as_posix(), 'rb') as f:
            return pickle.load(f)

    def retrieve(self):
        waiting_flag = True
        print(" -  Waiting for the results ...")
        if type(self.metadata['local_cluster_run_download_folder']) is str:
            self.metadata['local_cluster_run_download_folder'] =Path(self.metadata['local_cluster_run_download_folder'])
        if not self.metadata['local_cluster_run_download_folder'].is_dir():
            os.mkdir(self.metadata['local_cluster_run_download_folder'].as_posix())
        while waiting_flag:
            # if not ssh_commander(client,'cd %s; ls -d */' % (remote_result_abs_path), 0) and \
            # 'metadata' in ssh_commander(client,'cd %s; ls' % (remote_result_abs_path), 0):
            # just a better check:
            time.sleep(2)
            check_remote = self.ssh_commander(self.client, 'squeue -l -u {}'.format(self.metadata['cluster_username']), 0).decode('utf-8')
            if not self.metadata['cluster_username'] in check_remote:
                # here it means there is no folder in result folder and therefore all simulations are done
                # so we copy back the result and remove the files on cluster

                # waiting another 10 seconds to make sure everything's copied back in the cluster
                # Note that this does not check for JOBID, if the same user has another process ongoing
                # waiting_flag will remain true
                time.sleep(10)

                print(" -  Downloading the results from cluster...")
                for item in self.ssh_commander(self.client, 'cd {}; ls'.format(self.metadata['cluster_simulation_folder']), 0).decode('utf-8').split(
                        '\n'):
                    if item != '' and self.metadata['suffix'] in item:
                        self.scpclient.get(Path(self.metadata['cluster_simulation_folder']).joinpath(item).as_posix(),
                                           Path(self.metadata['local_cluster_run_download_folder']).joinpath(item).as_posix())
                        print('\t', item)
                # cleaning
                # self.ssh_commander(self.client, 'rm -rf {}'.format(self.metadata['cluster_workspace']), 0)
                waiting_flag = False


        print(" -  Downloads are available in: {}".format(self.metadata['local_cluster_run_download_folder']))

    def clean_remote(self):
        self.ssh_commander(self.client,
                           'rm -rf {}'.format(self.metadata['cluster_workspace']), 0).decode('utf-8').split('\n')
        self.ssh_commander(self.client,
                           'rm -rf {}'.format(self.metadata['local_workspace_unexpanded']), 0).decode('utf-8').split('\n')
        print(" -  Results are downloaded and remote is cleaned.")


if __name__ == '__main__':
    cl = ClusterDownloader('/home/corriel/CxPytestWorkspace/cluster_run_20191127_1223593/cluster_metadata_20191127_1223593.pkl', retrieve=False)
    cl.clean_remote()
