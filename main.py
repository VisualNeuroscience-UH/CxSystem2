from cxsystem2.core import cxsystem as cxs
from brian2  import *
import datetime


time_start = datetime.datetime.now()

### STEP ONE ###
# CM = cxs.CxSystem(anatomy_and_system_config = os.path.dirname(os.path.realpath(__file__)) + '/config_files/Rev2_Step1gamma_Anatomy_config_customweights_slurm.csv',
#                         physiology_config = os.path.dirname(os.path.realpath(__file__)) + '/config_files/Rev2_Step1gamma_Physiology_config.csv')

### STEP TWO ###
CM = cxs.CxSystem(anatomy_and_system_config = os.path.dirname(os.path.realpath(__file__)) + '/config_files/Rev2_Step2gamma_Anatomy_config_local.csv',
                        physiology_config = os.path.dirname(os.path.realpath(__file__)) + '/config_files/Rev2_Step2gamma_Physiology_config.csv')

time_before_run = datetime.datetime.now()
CM.run()
time_end = datetime.datetime.now()

duration_generation = int((time_before_run - time_start).total_seconds())
duration_simulation = int((time_end - time_before_run).total_seconds())
duration_total = int((time_end - time_start).total_seconds())

print('Duration of network generation: %d min %d s' % (duration_generation//60, duration_generation%60))
print('Duration of actual simulation: %d min %d s' % (duration_simulation//60, duration_simulation%60))
print('TOTAL %d min %d s' % (duration_total//60, duration_total%60)) #d