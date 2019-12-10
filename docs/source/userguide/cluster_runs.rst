Running on cluster
==================

In Cluster Run mode, CxSystem connects to a connection node of a cluster via SSH and runs instances of array run 
on pre-defined number of nodes in the cluster. Currently Cluster Run is tested on `Taito supercluster
<https://research.csc.fi/taito-supercluster>`_ at Finnish IT Center for Science that employs Slurm workload manager.  
However, with a slight modification to the Slurm template file, one can use the cluster run on other types of workload 
manager systems, e.g. Torque.

Setting up the environment
...........................

We assume that you are familiar with and have access to and available resources for a computing cluster, and that your 
cluster accepts ssh connections.
Before submitting the batch jobs to the cluster with CxSystem, the cluster environment should be properly set up. 
This includes finding/copying/assigning the python environment in the Slurm file. In case you are using 
a custom branch you should as well clone and checkout to that branch otherwise CxSystem will clone itself and try to 
spawn the processes using the master branch. The parameters that are used for cluster run are as follows:


 .. csv-table::

   run_in_cluster
   1

which triggers the cluster run.

 .. csv-table::

   cluster_job_file_path
   ./csc_taito.job

This parameter defines the address of the template workload management system file. In this case the a template 
for Slurm system is made available in the Github page which can be used for any cluster that utilizes the Slurm. 
In case the cluster of choice uses another workload management system, the template file should be specified accordingly.


 .. csv-table::

   cluster_number_of_nodes
   10

Defines how many nodes will be requested from the cluster to CxSystem.

**Important Note: the number of nodes in the cluster workload management system file should be set to 1 
and instead the number of nodes should be defined here. The reason for this is that CxSystem submits 
separate jobs to each node in the cluster. This has some advantages, including less waiting time, and some disadvantages, complexity.**

 .. csv-table::

   cluster_address
   taito.csc.fi

Defines the URL of the cluster.

 .. csv-table::

   cluster_username
   johnsmith

Defines the username for the SSH connection.

 .. csv-table::

   remote_repo_path
   ~/CxSystem

Defines the path of the CxSystem in the connection node of the cluster. In this example :code:`~/CxSystem` indicates that the CxSystem 
clone exists in the home folder, i.e. :code:`~/`, in the connection node. If the repository clone does not exist there, then the latest 
version will be cloned and used. As mentioned earlier, in case the user is using a specific branch, CxSystem should be cloned and checked 
out manually. Otherwise the user can rely on CxSystem cloning itself in the connection node.

  .. csv-table::

   cluster_workspace
   /Users/cxuser/results

Defines the folder in which the results will be copied. In this example, a new folder :code:`results` will be created in 
the :code:`/Users/cxuser/` folder and the results will be saved there. Note that :code:`cluster_workspace` must be an absolute 
path and in case the results reside under the home folder, it's path must as well be explicitly defined.

Transferring the Results
.........................

Usually clusters have an option to send users an email when the job is finished and users can transfer the results to their local machine. 
CxSystem can do this automatically: When a batch job is submitted, besides generating several Slurm files, CxSystem creates a :code:`_tmp_checker_data` 
file. This file, which contains information about the current cluster batch job, will be used to check the status of the results in the cluster. 
If the results are ready, they will be copied to the local result folder defined using :code:`output_path_and_filename` attribute in the 
network and model configuration file. This task can be done by directly running :code:`cluster_run.py`.
