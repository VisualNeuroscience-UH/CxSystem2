#include <stdlib.h>
#include "objects.h"
#include <ctime>
#include <time.h>

#include "run.h"
#include "brianlib/common_math.h"
#include "randomkit.h"

#include "code_objects/neurongroup_1_resetter_codeobject.h"
#include "code_objects/neurongroup_1_stateupdater_codeobject.h"
#include "code_objects/neurongroup_1_thresholder_codeobject.h"
#include "code_objects/neurongroup_2_resetter_codeobject.h"
#include "code_objects/neurongroup_2_stateupdater_codeobject.h"
#include "code_objects/neurongroup_2_thresholder_codeobject.h"
#include "code_objects/neurongroup_3_resetter_codeobject.h"
#include "code_objects/neurongroup_3_stateupdater_codeobject.h"
#include "code_objects/neurongroup_3_thresholder_codeobject.h"
#include "code_objects/neurongroup_4_resetter_codeobject.h"
#include "code_objects/neurongroup_4_stateupdater_codeobject.h"
#include "code_objects/neurongroup_4_thresholder_codeobject.h"
#include "code_objects/neurongroup_5_resetter_codeobject.h"
#include "code_objects/neurongroup_5_stateupdater_codeobject.h"
#include "code_objects/neurongroup_5_thresholder_codeobject.h"
#include "code_objects/neurongroup_resetter_codeobject.h"
#include "code_objects/neurongroup_thresholder_codeobject.h"
#include "code_objects/poissoninput_10_codeobject.h"
#include "code_objects/poissoninput_11_codeobject.h"
#include "code_objects/poissoninput_12_codeobject.h"
#include "code_objects/poissoninput_13_codeobject.h"
#include "code_objects/poissoninput_14_codeobject.h"
#include "code_objects/poissoninput_15_codeobject.h"
#include "code_objects/poissoninput_1_codeobject.h"
#include "code_objects/poissoninput_2_codeobject.h"
#include "code_objects/poissoninput_3_codeobject.h"
#include "code_objects/poissoninput_4_codeobject.h"
#include "code_objects/poissoninput_5_codeobject.h"
#include "code_objects/poissoninput_6_codeobject.h"
#include "code_objects/poissoninput_7_codeobject.h"
#include "code_objects/poissoninput_8_codeobject.h"
#include "code_objects/poissoninput_9_codeobject.h"
#include "code_objects/poissoninput_codeobject.h"
#include "code_objects/spikegeneratorgroup_codeobject.h"
#include "code_objects/spikemonitor_1_codeobject.h"
#include "code_objects/spikemonitor_2_codeobject.h"
#include "code_objects/spikemonitor_3_codeobject.h"
#include "code_objects/spikemonitor_4_codeobject.h"
#include "code_objects/spikemonitor_5_codeobject.h"
#include "code_objects/spikemonitor_codeobject.h"
#include "code_objects/synapses_10_group_variable_set_conditional_codeobject.h"
#include "code_objects/synapses_10_pre_codeobject.h"
#include "code_objects/synapses_10_pre_group_variable_set_conditional_codeobject.h"
#include "code_objects/synapses_10_pre_initialise_queue.h"
#include "code_objects/synapses_10_pre_push_spikes.h"
#include "code_objects/synapses_10_synapses_create_array_codeobject.h"
#include "code_objects/synapses_11_group_variable_set_conditional_codeobject.h"
#include "code_objects/synapses_11_pre_codeobject.h"
#include "code_objects/synapses_11_pre_group_variable_set_conditional_codeobject.h"
#include "code_objects/synapses_11_pre_initialise_queue.h"
#include "code_objects/synapses_11_pre_push_spikes.h"
#include "code_objects/synapses_11_synapses_create_array_codeobject.h"
#include "code_objects/synapses_12_group_variable_set_conditional_codeobject.h"
#include "code_objects/synapses_12_pre_codeobject.h"
#include "code_objects/synapses_12_pre_group_variable_set_conditional_codeobject.h"
#include "code_objects/synapses_12_pre_initialise_queue.h"
#include "code_objects/synapses_12_pre_push_spikes.h"
#include "code_objects/synapses_12_synapses_create_array_codeobject.h"
#include "code_objects/synapses_13_group_variable_set_conditional_codeobject.h"
#include "code_objects/synapses_13_pre_codeobject.h"
#include "code_objects/synapses_13_pre_group_variable_set_conditional_codeobject.h"
#include "code_objects/synapses_13_pre_initialise_queue.h"
#include "code_objects/synapses_13_pre_push_spikes.h"
#include "code_objects/synapses_13_synapses_create_array_codeobject.h"
#include "code_objects/synapses_14_group_variable_set_conditional_codeobject.h"
#include "code_objects/synapses_14_pre_codeobject.h"
#include "code_objects/synapses_14_pre_group_variable_set_conditional_codeobject.h"
#include "code_objects/synapses_14_pre_initialise_queue.h"
#include "code_objects/synapses_14_pre_push_spikes.h"
#include "code_objects/synapses_14_synapses_create_array_codeobject.h"
#include "code_objects/synapses_15_group_variable_set_conditional_codeobject.h"
#include "code_objects/synapses_15_pre_codeobject.h"
#include "code_objects/synapses_15_pre_group_variable_set_conditional_codeobject.h"
#include "code_objects/synapses_15_pre_initialise_queue.h"
#include "code_objects/synapses_15_pre_push_spikes.h"
#include "code_objects/synapses_15_synapses_create_array_codeobject.h"
#include "code_objects/synapses_16_group_variable_set_conditional_codeobject.h"
#include "code_objects/synapses_16_pre_codeobject.h"
#include "code_objects/synapses_16_pre_group_variable_set_conditional_codeobject.h"
#include "code_objects/synapses_16_pre_initialise_queue.h"
#include "code_objects/synapses_16_pre_push_spikes.h"
#include "code_objects/synapses_16_synapses_create_array_codeobject.h"
#include "code_objects/synapses_17_group_variable_set_conditional_codeobject.h"
#include "code_objects/synapses_17_pre_codeobject.h"
#include "code_objects/synapses_17_pre_group_variable_set_conditional_codeobject.h"
#include "code_objects/synapses_17_pre_initialise_queue.h"
#include "code_objects/synapses_17_pre_push_spikes.h"
#include "code_objects/synapses_17_synapses_create_array_codeobject.h"
#include "code_objects/synapses_18_group_variable_set_conditional_codeobject.h"
#include "code_objects/synapses_18_pre_codeobject.h"
#include "code_objects/synapses_18_pre_group_variable_set_conditional_codeobject.h"
#include "code_objects/synapses_18_pre_initialise_queue.h"
#include "code_objects/synapses_18_pre_push_spikes.h"
#include "code_objects/synapses_18_synapses_create_array_codeobject.h"
#include "code_objects/synapses_19_group_variable_set_conditional_codeobject.h"
#include "code_objects/synapses_19_pre_codeobject.h"
#include "code_objects/synapses_19_pre_group_variable_set_conditional_codeobject.h"
#include "code_objects/synapses_19_pre_initialise_queue.h"
#include "code_objects/synapses_19_pre_push_spikes.h"
#include "code_objects/synapses_19_synapses_create_array_codeobject.h"
#include "code_objects/synapses_1_group_variable_set_conditional_codeobject.h"
#include "code_objects/synapses_1_pre_codeobject.h"
#include "code_objects/synapses_1_pre_group_variable_set_conditional_codeobject.h"
#include "code_objects/synapses_1_pre_initialise_queue.h"
#include "code_objects/synapses_1_pre_push_spikes.h"
#include "code_objects/synapses_1_synapses_create_array_codeobject.h"
#include "code_objects/synapses_20_group_variable_set_conditional_codeobject.h"
#include "code_objects/synapses_20_pre_codeobject.h"
#include "code_objects/synapses_20_pre_group_variable_set_conditional_codeobject.h"
#include "code_objects/synapses_20_pre_initialise_queue.h"
#include "code_objects/synapses_20_pre_push_spikes.h"
#include "code_objects/synapses_20_synapses_create_array_codeobject.h"
#include "code_objects/synapses_21_group_variable_set_conditional_codeobject.h"
#include "code_objects/synapses_21_pre_codeobject.h"
#include "code_objects/synapses_21_pre_group_variable_set_conditional_codeobject.h"
#include "code_objects/synapses_21_pre_initialise_queue.h"
#include "code_objects/synapses_21_pre_push_spikes.h"
#include "code_objects/synapses_21_synapses_create_array_codeobject.h"
#include "code_objects/synapses_22_group_variable_set_conditional_codeobject.h"
#include "code_objects/synapses_22_pre_codeobject.h"
#include "code_objects/synapses_22_pre_group_variable_set_conditional_codeobject.h"
#include "code_objects/synapses_22_pre_initialise_queue.h"
#include "code_objects/synapses_22_pre_push_spikes.h"
#include "code_objects/synapses_22_synapses_create_array_codeobject.h"
#include "code_objects/synapses_23_group_variable_set_conditional_codeobject.h"
#include "code_objects/synapses_23_pre_codeobject.h"
#include "code_objects/synapses_23_pre_group_variable_set_conditional_codeobject.h"
#include "code_objects/synapses_23_pre_initialise_queue.h"
#include "code_objects/synapses_23_pre_push_spikes.h"
#include "code_objects/synapses_23_synapses_create_array_codeobject.h"
#include "code_objects/synapses_24_group_variable_set_conditional_codeobject.h"
#include "code_objects/synapses_24_pre_codeobject.h"
#include "code_objects/synapses_24_pre_group_variable_set_conditional_codeobject.h"
#include "code_objects/synapses_24_pre_initialise_queue.h"
#include "code_objects/synapses_24_pre_push_spikes.h"
#include "code_objects/synapses_24_synapses_create_array_codeobject.h"
#include "code_objects/synapses_25_group_variable_set_conditional_codeobject.h"
#include "code_objects/synapses_25_pre_codeobject.h"
#include "code_objects/synapses_25_pre_group_variable_set_conditional_codeobject.h"
#include "code_objects/synapses_25_pre_initialise_queue.h"
#include "code_objects/synapses_25_pre_push_spikes.h"
#include "code_objects/synapses_25_synapses_create_array_codeobject.h"
#include "code_objects/synapses_26_group_variable_set_conditional_codeobject.h"
#include "code_objects/synapses_26_pre_codeobject.h"
#include "code_objects/synapses_26_pre_group_variable_set_conditional_codeobject.h"
#include "code_objects/synapses_26_pre_initialise_queue.h"
#include "code_objects/synapses_26_pre_push_spikes.h"
#include "code_objects/synapses_26_synapses_create_array_codeobject.h"
#include "code_objects/synapses_27_group_variable_set_conditional_codeobject.h"
#include "code_objects/synapses_27_pre_codeobject.h"
#include "code_objects/synapses_27_pre_group_variable_set_conditional_codeobject.h"
#include "code_objects/synapses_27_pre_initialise_queue.h"
#include "code_objects/synapses_27_pre_push_spikes.h"
#include "code_objects/synapses_27_synapses_create_array_codeobject.h"
#include "code_objects/synapses_28_group_variable_set_conditional_codeobject.h"
#include "code_objects/synapses_28_pre_codeobject.h"
#include "code_objects/synapses_28_pre_group_variable_set_conditional_codeobject.h"
#include "code_objects/synapses_28_pre_initialise_queue.h"
#include "code_objects/synapses_28_pre_push_spikes.h"
#include "code_objects/synapses_28_synapses_create_array_codeobject.h"
#include "code_objects/synapses_29_group_variable_set_conditional_codeobject.h"
#include "code_objects/synapses_29_pre_codeobject.h"
#include "code_objects/synapses_29_pre_group_variable_set_conditional_codeobject.h"
#include "code_objects/synapses_29_pre_initialise_queue.h"
#include "code_objects/synapses_29_pre_push_spikes.h"
#include "code_objects/synapses_29_synapses_create_array_codeobject.h"
#include "code_objects/synapses_2_group_variable_set_conditional_codeobject.h"
#include "code_objects/synapses_2_pre_codeobject.h"
#include "code_objects/synapses_2_pre_group_variable_set_conditional_codeobject.h"
#include "code_objects/synapses_2_pre_initialise_queue.h"
#include "code_objects/synapses_2_pre_push_spikes.h"
#include "code_objects/synapses_2_synapses_create_array_codeobject.h"
#include "code_objects/synapses_30_group_variable_set_conditional_codeobject.h"
#include "code_objects/synapses_30_pre_codeobject.h"
#include "code_objects/synapses_30_pre_group_variable_set_conditional_codeobject.h"
#include "code_objects/synapses_30_pre_initialise_queue.h"
#include "code_objects/synapses_30_pre_push_spikes.h"
#include "code_objects/synapses_30_synapses_create_array_codeobject.h"
#include "code_objects/synapses_31_group_variable_set_conditional_codeobject.h"
#include "code_objects/synapses_31_pre_codeobject.h"
#include "code_objects/synapses_31_pre_group_variable_set_conditional_codeobject.h"
#include "code_objects/synapses_31_pre_initialise_queue.h"
#include "code_objects/synapses_31_pre_push_spikes.h"
#include "code_objects/synapses_31_synapses_create_array_codeobject.h"
#include "code_objects/synapses_32_group_variable_set_conditional_codeobject.h"
#include "code_objects/synapses_32_pre_codeobject.h"
#include "code_objects/synapses_32_pre_group_variable_set_conditional_codeobject.h"
#include "code_objects/synapses_32_pre_initialise_queue.h"
#include "code_objects/synapses_32_pre_push_spikes.h"
#include "code_objects/synapses_32_synapses_create_array_codeobject.h"
#include "code_objects/synapses_33_group_variable_set_conditional_codeobject.h"
#include "code_objects/synapses_33_pre_codeobject.h"
#include "code_objects/synapses_33_pre_group_variable_set_conditional_codeobject.h"
#include "code_objects/synapses_33_pre_initialise_queue.h"
#include "code_objects/synapses_33_pre_push_spikes.h"
#include "code_objects/synapses_33_synapses_create_array_codeobject.h"
#include "code_objects/synapses_34_group_variable_set_conditional_codeobject.h"
#include "code_objects/synapses_34_pre_codeobject.h"
#include "code_objects/synapses_34_pre_group_variable_set_conditional_codeobject.h"
#include "code_objects/synapses_34_pre_initialise_queue.h"
#include "code_objects/synapses_34_pre_push_spikes.h"
#include "code_objects/synapses_34_synapses_create_array_codeobject.h"
#include "code_objects/synapses_35_group_variable_set_conditional_codeobject.h"
#include "code_objects/synapses_35_pre_codeobject.h"
#include "code_objects/synapses_35_pre_group_variable_set_conditional_codeobject.h"
#include "code_objects/synapses_35_pre_initialise_queue.h"
#include "code_objects/synapses_35_pre_push_spikes.h"
#include "code_objects/synapses_35_synapses_create_array_codeobject.h"
#include "code_objects/synapses_36_group_variable_set_conditional_codeobject.h"
#include "code_objects/synapses_36_pre_codeobject.h"
#include "code_objects/synapses_36_pre_group_variable_set_conditional_codeobject.h"
#include "code_objects/synapses_36_pre_initialise_queue.h"
#include "code_objects/synapses_36_pre_push_spikes.h"
#include "code_objects/synapses_36_synapses_create_array_codeobject.h"
#include "code_objects/synapses_37_group_variable_set_conditional_codeobject.h"
#include "code_objects/synapses_37_pre_codeobject.h"
#include "code_objects/synapses_37_pre_group_variable_set_conditional_codeobject.h"
#include "code_objects/synapses_37_pre_initialise_queue.h"
#include "code_objects/synapses_37_pre_push_spikes.h"
#include "code_objects/synapses_37_synapses_create_array_codeobject.h"
#include "code_objects/synapses_3_group_variable_set_conditional_codeobject.h"
#include "code_objects/synapses_3_pre_codeobject.h"
#include "code_objects/synapses_3_pre_group_variable_set_conditional_codeobject.h"
#include "code_objects/synapses_3_pre_initialise_queue.h"
#include "code_objects/synapses_3_pre_push_spikes.h"
#include "code_objects/synapses_3_synapses_create_array_codeobject.h"
#include "code_objects/synapses_4_group_variable_set_conditional_codeobject.h"
#include "code_objects/synapses_4_pre_codeobject.h"
#include "code_objects/synapses_4_pre_group_variable_set_conditional_codeobject.h"
#include "code_objects/synapses_4_pre_initialise_queue.h"
#include "code_objects/synapses_4_pre_push_spikes.h"
#include "code_objects/synapses_4_synapses_create_array_codeobject.h"
#include "code_objects/synapses_5_group_variable_set_conditional_codeobject.h"
#include "code_objects/synapses_5_pre_codeobject.h"
#include "code_objects/synapses_5_pre_group_variable_set_conditional_codeobject.h"
#include "code_objects/synapses_5_pre_initialise_queue.h"
#include "code_objects/synapses_5_pre_push_spikes.h"
#include "code_objects/synapses_5_synapses_create_array_codeobject.h"
#include "code_objects/synapses_6_group_variable_set_conditional_codeobject.h"
#include "code_objects/synapses_6_pre_codeobject.h"
#include "code_objects/synapses_6_pre_group_variable_set_conditional_codeobject.h"
#include "code_objects/synapses_6_pre_initialise_queue.h"
#include "code_objects/synapses_6_pre_push_spikes.h"
#include "code_objects/synapses_6_synapses_create_array_codeobject.h"
#include "code_objects/synapses_7_group_variable_set_conditional_codeobject.h"
#include "code_objects/synapses_7_pre_codeobject.h"
#include "code_objects/synapses_7_pre_group_variable_set_conditional_codeobject.h"
#include "code_objects/synapses_7_pre_initialise_queue.h"
#include "code_objects/synapses_7_pre_push_spikes.h"
#include "code_objects/synapses_7_synapses_create_array_codeobject.h"
#include "code_objects/synapses_8_group_variable_set_conditional_codeobject.h"
#include "code_objects/synapses_8_pre_codeobject.h"
#include "code_objects/synapses_8_pre_group_variable_set_conditional_codeobject.h"
#include "code_objects/synapses_8_pre_initialise_queue.h"
#include "code_objects/synapses_8_pre_push_spikes.h"
#include "code_objects/synapses_8_synapses_create_array_codeobject.h"
#include "code_objects/synapses_9_group_variable_set_conditional_codeobject.h"
#include "code_objects/synapses_9_pre_codeobject.h"
#include "code_objects/synapses_9_pre_group_variable_set_conditional_codeobject.h"
#include "code_objects/synapses_9_pre_initialise_queue.h"
#include "code_objects/synapses_9_pre_push_spikes.h"
#include "code_objects/synapses_9_synapses_create_array_codeobject.h"
#include "code_objects/synapses_pre_codeobject.h"
#include "code_objects/synapses_pre_initialise_queue.h"
#include "code_objects/synapses_pre_push_spikes.h"
#include "code_objects/synapses_synapses_create_generator_codeobject.h"


#include <iostream>
#include <fstream>


        void report_progress(const double elapsed, const double completed, const double start, const double duration)
        {
            if (completed == 0.0)
            {
                std::cout << "Starting simulation at t=" << start << " s for duration " << duration << " s";
            } else
            {
                std::cout << completed*duration << " s (" << (int)(completed*100.) << "%) simulated in " << elapsed << " s";
                if (completed < 1.0)
                {
                    const int remaining = (int)((1-completed)/completed*elapsed+0.5);
                    std::cout << ", estimated " << remaining << " s remaining.";
                }
            }

            std::cout << std::endl << std::flush;
        }
        


int main(int argc, char **argv)
{
        

	brian_start();
        

	{
		using namespace brian;

		
                
        _array_defaultclock_dt[0] = 0.0001;
        _array_defaultclock_dt[0] = 0.0001;
        _array_defaultclock_dt[0] = 0.0001;
        _dynamic_array_spikegeneratorgroup_spike_number.resize(60);
        
                        
                        for(int i=0; i<_dynamic_array_spikegeneratorgroup_spike_number.size(); i++)
                        {
                            _dynamic_array_spikegeneratorgroup_spike_number[i] = _static_array__dynamic_array_spikegeneratorgroup_spike_number[i];
                        }
                        
        _dynamic_array_spikegeneratorgroup_neuron_index.resize(60);
        
                        
                        for(int i=0; i<_dynamic_array_spikegeneratorgroup_neuron_index.size(); i++)
                        {
                            _dynamic_array_spikegeneratorgroup_neuron_index[i] = _static_array__dynamic_array_spikegeneratorgroup_neuron_index[i];
                        }
                        
        _dynamic_array_spikegeneratorgroup_spike_time.resize(60);
        
                        
                        for(int i=0; i<_dynamic_array_spikegeneratorgroup_spike_time.size(); i++)
                        {
                            _dynamic_array_spikegeneratorgroup_spike_time[i] = _static_array__dynamic_array_spikegeneratorgroup_spike_time[i];
                        }
                        
        _dynamic_array_spikegeneratorgroup__timebins.resize(60);
        _array_spikegeneratorgroup__lastindex[0] = 0;
        _array_spikegeneratorgroup_period[0] = 0.0;
        
                        
                        for(int i=0; i<_num__array_neurongroup_x; i++)
                        {
                            _array_neurongroup_x[i] = _static_array__array_neurongroup_x[i];
                        }
                        
        
                        
                        for(int i=0; i<_num__array_neurongroup_y; i++)
                        {
                            _array_neurongroup_y[i] = _static_array__array_neurongroup_y[i];
                        }
                        
        _run_synapses_synapses_create_generator_codeobject();
        
                        
                        for(int i=0; i<_num__array_neurongroup_1_lastspike; i++)
                        {
                            _array_neurongroup_1_lastspike[i] = - 10000.0;
                        }
                        
        
                        
                        for(int i=0; i<_num__array_neurongroup_1_not_refractory; i++)
                        {
                            _array_neurongroup_1_not_refractory[i] = true;
                        }
                        
        
                        
                        for(int i=0; i<_num__array_neurongroup_1_x; i++)
                        {
                            _array_neurongroup_1_x[i] = _static_array__array_neurongroup_1_x[i];
                        }
                        
        
                        
                        for(int i=0; i<_num__array_neurongroup_1_y; i++)
                        {
                            _array_neurongroup_1_y[i] = _static_array__array_neurongroup_1_y[i];
                        }
                        
        
                        
                        for(int i=0; i<_num__array_neurongroup_1_vm_basal; i++)
                        {
                            _array_neurongroup_1_vm_basal[i] = - 0.07265804000000001;
                        }
                        
        
                        
                        for(int i=0; i<_num__array_neurongroup_1_vm; i++)
                        {
                            _array_neurongroup_1_vm[i] = - 0.07265804000000001;
                        }
                        
        
                        
                        for(int i=0; i<_num__array_neurongroup_1_vm_a0; i++)
                        {
                            _array_neurongroup_1_vm_a0[i] = - 0.07265804000000001;
                        }
                        
        
                        
                        for(int i=0; i<_num__array_neurongroup_1_vm_a1; i++)
                        {
                            _array_neurongroup_1_vm_a1[i] = - 0.07265804000000001;
                        }
                        
        
                        
                        for(int i=0; i<_num__array_neurongroup_1_vm_a2; i++)
                        {
                            _array_neurongroup_1_vm_a2[i] = - 0.07265804000000001;
                        }
                        
        
                        
                        for(int i=0; i<_num__array_neurongroup_2_lastspike; i++)
                        {
                            _array_neurongroup_2_lastspike[i] = - 10000.0;
                        }
                        
        
                        
                        for(int i=0; i<_num__array_neurongroup_2_not_refractory; i++)
                        {
                            _array_neurongroup_2_not_refractory[i] = true;
                        }
                        
        
                        
                        for(int i=0; i<_num__array_neurongroup_2_x; i++)
                        {
                            _array_neurongroup_2_x[i] = _static_array__array_neurongroup_2_x[i];
                        }
                        
        
                        
                        for(int i=0; i<_num__array_neurongroup_2_y; i++)
                        {
                            _array_neurongroup_2_y[i] = _static_array__array_neurongroup_2_y[i];
                        }
                        
        
                        
                        for(int i=0; i<_num__array_neurongroup_2_vm_basal; i++)
                        {
                            _array_neurongroup_2_vm_basal[i] = - 0.07302760000000001;
                        }
                        
        
                        
                        for(int i=0; i<_num__array_neurongroup_2_vm; i++)
                        {
                            _array_neurongroup_2_vm[i] = - 0.07302760000000001;
                        }
                        
        
                        
                        for(int i=0; i<_num__array_neurongroup_2_vm_a0; i++)
                        {
                            _array_neurongroup_2_vm_a0[i] = - 0.07302760000000001;
                        }
                        
        
                        
                        for(int i=0; i<_num__array_neurongroup_2_vm_a1; i++)
                        {
                            _array_neurongroup_2_vm_a1[i] = - 0.07302760000000001;
                        }
                        
        
                        
                        for(int i=0; i<_num__array_neurongroup_2_vm_a2; i++)
                        {
                            _array_neurongroup_2_vm_a2[i] = - 0.07302760000000001;
                        }
                        
        
                        
                        for(int i=0; i<_num__array_neurongroup_3_lastspike; i++)
                        {
                            _array_neurongroup_3_lastspike[i] = - 10000.0;
                        }
                        
        
                        
                        for(int i=0; i<_num__array_neurongroup_3_not_refractory; i++)
                        {
                            _array_neurongroup_3_not_refractory[i] = true;
                        }
                        
        
                        
                        for(int i=0; i<_num__array_neurongroup_3_x; i++)
                        {
                            _array_neurongroup_3_x[i] = _static_array__array_neurongroup_3_x[i];
                        }
                        
        
                        
                        for(int i=0; i<_num__array_neurongroup_3_y; i++)
                        {
                            _array_neurongroup_3_y[i] = _static_array__array_neurongroup_3_y[i];
                        }
                        
        
                        
                        for(int i=0; i<_num__array_neurongroup_3_vm; i++)
                        {
                            _array_neurongroup_3_vm[i] = - 0.07366282;
                        }
                        
        
                        
                        for(int i=0; i<_num__array_neurongroup_4_lastspike; i++)
                        {
                            _array_neurongroup_4_lastspike[i] = - 10000.0;
                        }
                        
        
                        
                        for(int i=0; i<_num__array_neurongroup_4_not_refractory; i++)
                        {
                            _array_neurongroup_4_not_refractory[i] = true;
                        }
                        
        
                        
                        for(int i=0; i<_num__array_neurongroup_4_x; i++)
                        {
                            _array_neurongroup_4_x[i] = _static_array__array_neurongroup_4_x[i];
                        }
                        
        
                        
                        for(int i=0; i<_num__array_neurongroup_4_y; i++)
                        {
                            _array_neurongroup_4_y[i] = _static_array__array_neurongroup_4_y[i];
                        }
                        
        
                        
                        for(int i=0; i<_num__array_neurongroup_4_vm; i++)
                        {
                            _array_neurongroup_4_vm[i] = - 0.0724306544604;
                        }
                        
        
                        
                        for(int i=0; i<_num__array_neurongroup_5_lastspike; i++)
                        {
                            _array_neurongroup_5_lastspike[i] = - 10000.0;
                        }
                        
        
                        
                        for(int i=0; i<_num__array_neurongroup_5_not_refractory; i++)
                        {
                            _array_neurongroup_5_not_refractory[i] = true;
                        }
                        
        
                        
                        for(int i=0; i<_num__array_neurongroup_5_x; i++)
                        {
                            _array_neurongroup_5_x[i] = _static_array__array_neurongroup_5_x[i];
                        }
                        
        
                        
                        for(int i=0; i<_num__array_neurongroup_5_y; i++)
                        {
                            _array_neurongroup_5_y[i] = _static_array__array_neurongroup_5_y[i];
                        }
                        
        
                        
                        for(int i=0; i<_num__array_neurongroup_5_vm; i++)
                        {
                            _array_neurongroup_5_vm[i] = - 0.0708507355932;
                        }
                        
        
                        
                        for(int i=0; i<_num__array_synapses_1_sources; i++)
                        {
                            _array_synapses_1_sources[i] = _static_array__array_synapses_1_sources[i];
                        }
                        
        
                        
                        for(int i=0; i<_num__array_synapses_1_targets; i++)
                        {
                            _array_synapses_1_targets[i] = _static_array__array_synapses_1_targets[i];
                        }
                        
        _run_synapses_1_synapses_create_array_codeobject();
        _run_synapses_1_group_variable_set_conditional_codeobject();
        _run_synapses_1_pre_group_variable_set_conditional_codeobject();
        
                        
                        for(int i=0; i<_num__array_synapses_2_sources; i++)
                        {
                            _array_synapses_2_sources[i] = _static_array__array_synapses_2_sources[i];
                        }
                        
        
                        
                        for(int i=0; i<_num__array_synapses_2_targets; i++)
                        {
                            _array_synapses_2_targets[i] = _static_array__array_synapses_2_targets[i];
                        }
                        
        _run_synapses_2_synapses_create_array_codeobject();
        _run_synapses_2_group_variable_set_conditional_codeobject();
        _run_synapses_2_pre_group_variable_set_conditional_codeobject();
        
                        
                        for(int i=0; i<_num__array_synapses_3_sources; i++)
                        {
                            _array_synapses_3_sources[i] = _static_array__array_synapses_3_sources[i];
                        }
                        
        
                        
                        for(int i=0; i<_num__array_synapses_3_targets; i++)
                        {
                            _array_synapses_3_targets[i] = _static_array__array_synapses_3_targets[i];
                        }
                        
        _run_synapses_3_synapses_create_array_codeobject();
        _run_synapses_3_group_variable_set_conditional_codeobject();
        _run_synapses_3_pre_group_variable_set_conditional_codeobject();
        
                        
                        for(int i=0; i<_num__array_synapses_4_sources; i++)
                        {
                            _array_synapses_4_sources[i] = _static_array__array_synapses_4_sources[i];
                        }
                        
        
                        
                        for(int i=0; i<_num__array_synapses_4_targets; i++)
                        {
                            _array_synapses_4_targets[i] = _static_array__array_synapses_4_targets[i];
                        }
                        
        _run_synapses_4_synapses_create_array_codeobject();
        _run_synapses_4_group_variable_set_conditional_codeobject();
        _run_synapses_4_pre_group_variable_set_conditional_codeobject();
        
                        
                        for(int i=0; i<_num__array_synapses_5_sources; i++)
                        {
                            _array_synapses_5_sources[i] = _static_array__array_synapses_5_sources[i];
                        }
                        
        
                        
                        for(int i=0; i<_num__array_synapses_5_targets; i++)
                        {
                            _array_synapses_5_targets[i] = _static_array__array_synapses_5_targets[i];
                        }
                        
        _run_synapses_5_synapses_create_array_codeobject();
        _run_synapses_5_group_variable_set_conditional_codeobject();
        _run_synapses_5_pre_group_variable_set_conditional_codeobject();
        
                        
                        for(int i=0; i<_num__array_synapses_6_sources; i++)
                        {
                            _array_synapses_6_sources[i] = _static_array__array_synapses_6_sources[i];
                        }
                        
        
                        
                        for(int i=0; i<_num__array_synapses_6_targets; i++)
                        {
                            _array_synapses_6_targets[i] = _static_array__array_synapses_6_targets[i];
                        }
                        
        _run_synapses_6_synapses_create_array_codeobject();
        _run_synapses_6_group_variable_set_conditional_codeobject();
        _run_synapses_6_pre_group_variable_set_conditional_codeobject();
        
                        
                        for(int i=0; i<_num__array_synapses_7_sources; i++)
                        {
                            _array_synapses_7_sources[i] = _static_array__array_synapses_7_sources[i];
                        }
                        
        
                        
                        for(int i=0; i<_num__array_synapses_7_targets; i++)
                        {
                            _array_synapses_7_targets[i] = _static_array__array_synapses_7_targets[i];
                        }
                        
        _run_synapses_7_synapses_create_array_codeobject();
        _run_synapses_7_group_variable_set_conditional_codeobject();
        _run_synapses_7_pre_group_variable_set_conditional_codeobject();
        
                        
                        for(int i=0; i<_num__array_synapses_8_sources; i++)
                        {
                            _array_synapses_8_sources[i] = _static_array__array_synapses_8_sources[i];
                        }
                        
        
                        
                        for(int i=0; i<_num__array_synapses_8_targets; i++)
                        {
                            _array_synapses_8_targets[i] = _static_array__array_synapses_8_targets[i];
                        }
                        
        _run_synapses_8_synapses_create_array_codeobject();
        _run_synapses_8_group_variable_set_conditional_codeobject();
        _run_synapses_8_pre_group_variable_set_conditional_codeobject();
        
                        
                        for(int i=0; i<_num__array_synapses_9_sources; i++)
                        {
                            _array_synapses_9_sources[i] = _static_array__array_synapses_9_sources[i];
                        }
                        
        
                        
                        for(int i=0; i<_num__array_synapses_9_targets; i++)
                        {
                            _array_synapses_9_targets[i] = _static_array__array_synapses_9_targets[i];
                        }
                        
        _run_synapses_9_synapses_create_array_codeobject();
        _run_synapses_9_group_variable_set_conditional_codeobject();
        _run_synapses_9_pre_group_variable_set_conditional_codeobject();
        
                        
                        for(int i=0; i<_num__array_synapses_10_sources; i++)
                        {
                            _array_synapses_10_sources[i] = _static_array__array_synapses_10_sources[i];
                        }
                        
        
                        
                        for(int i=0; i<_num__array_synapses_10_targets; i++)
                        {
                            _array_synapses_10_targets[i] = _static_array__array_synapses_10_targets[i];
                        }
                        
        _run_synapses_10_synapses_create_array_codeobject();
        _run_synapses_10_group_variable_set_conditional_codeobject();
        _run_synapses_10_pre_group_variable_set_conditional_codeobject();
        
                        
                        for(int i=0; i<_num__array_synapses_11_sources; i++)
                        {
                            _array_synapses_11_sources[i] = _static_array__array_synapses_11_sources[i];
                        }
                        
        
                        
                        for(int i=0; i<_num__array_synapses_11_targets; i++)
                        {
                            _array_synapses_11_targets[i] = _static_array__array_synapses_11_targets[i];
                        }
                        
        _run_synapses_11_synapses_create_array_codeobject();
        _run_synapses_11_group_variable_set_conditional_codeobject();
        _run_synapses_11_pre_group_variable_set_conditional_codeobject();
        
                        
                        for(int i=0; i<_num__array_synapses_12_sources; i++)
                        {
                            _array_synapses_12_sources[i] = _static_array__array_synapses_12_sources[i];
                        }
                        
        
                        
                        for(int i=0; i<_num__array_synapses_12_targets; i++)
                        {
                            _array_synapses_12_targets[i] = _static_array__array_synapses_12_targets[i];
                        }
                        
        _run_synapses_12_synapses_create_array_codeobject();
        _run_synapses_12_group_variable_set_conditional_codeobject();
        _run_synapses_12_pre_group_variable_set_conditional_codeobject();
        
                        
                        for(int i=0; i<_num__array_synapses_13_sources; i++)
                        {
                            _array_synapses_13_sources[i] = _static_array__array_synapses_13_sources[i];
                        }
                        
        
                        
                        for(int i=0; i<_num__array_synapses_13_targets; i++)
                        {
                            _array_synapses_13_targets[i] = _static_array__array_synapses_13_targets[i];
                        }
                        
        _run_synapses_13_synapses_create_array_codeobject();
        _run_synapses_13_group_variable_set_conditional_codeobject();
        _run_synapses_13_pre_group_variable_set_conditional_codeobject();
        
                        
                        for(int i=0; i<_num__array_synapses_14_sources; i++)
                        {
                            _array_synapses_14_sources[i] = _static_array__array_synapses_14_sources[i];
                        }
                        
        
                        
                        for(int i=0; i<_num__array_synapses_14_targets; i++)
                        {
                            _array_synapses_14_targets[i] = _static_array__array_synapses_14_targets[i];
                        }
                        
        _run_synapses_14_synapses_create_array_codeobject();
        _run_synapses_14_group_variable_set_conditional_codeobject();
        _run_synapses_14_pre_group_variable_set_conditional_codeobject();
        
                        
                        for(int i=0; i<_num__array_synapses_15_sources; i++)
                        {
                            _array_synapses_15_sources[i] = _static_array__array_synapses_15_sources[i];
                        }
                        
        
                        
                        for(int i=0; i<_num__array_synapses_15_targets; i++)
                        {
                            _array_synapses_15_targets[i] = _static_array__array_synapses_15_targets[i];
                        }
                        
        _run_synapses_15_synapses_create_array_codeobject();
        _run_synapses_15_group_variable_set_conditional_codeobject();
        _run_synapses_15_pre_group_variable_set_conditional_codeobject();
        
                        
                        for(int i=0; i<_num__array_synapses_16_sources; i++)
                        {
                            _array_synapses_16_sources[i] = _static_array__array_synapses_16_sources[i];
                        }
                        
        
                        
                        for(int i=0; i<_num__array_synapses_16_targets; i++)
                        {
                            _array_synapses_16_targets[i] = _static_array__array_synapses_16_targets[i];
                        }
                        
        _run_synapses_16_synapses_create_array_codeobject();
        _run_synapses_16_group_variable_set_conditional_codeobject();
        _run_synapses_16_pre_group_variable_set_conditional_codeobject();
        
                        
                        for(int i=0; i<_num__array_synapses_17_sources; i++)
                        {
                            _array_synapses_17_sources[i] = _static_array__array_synapses_17_sources[i];
                        }
                        
        
                        
                        for(int i=0; i<_num__array_synapses_17_targets; i++)
                        {
                            _array_synapses_17_targets[i] = _static_array__array_synapses_17_targets[i];
                        }
                        
        _run_synapses_17_synapses_create_array_codeobject();
        _run_synapses_17_group_variable_set_conditional_codeobject();
        _run_synapses_17_pre_group_variable_set_conditional_codeobject();
        
                        
                        for(int i=0; i<_num__array_synapses_18_sources; i++)
                        {
                            _array_synapses_18_sources[i] = _static_array__array_synapses_18_sources[i];
                        }
                        
        
                        
                        for(int i=0; i<_num__array_synapses_18_targets; i++)
                        {
                            _array_synapses_18_targets[i] = _static_array__array_synapses_18_targets[i];
                        }
                        
        _run_synapses_18_synapses_create_array_codeobject();
        _run_synapses_18_group_variable_set_conditional_codeobject();
        _run_synapses_18_pre_group_variable_set_conditional_codeobject();
        
                        
                        for(int i=0; i<_num__array_synapses_19_sources; i++)
                        {
                            _array_synapses_19_sources[i] = _static_array__array_synapses_19_sources[i];
                        }
                        
        
                        
                        for(int i=0; i<_num__array_synapses_19_targets; i++)
                        {
                            _array_synapses_19_targets[i] = _static_array__array_synapses_19_targets[i];
                        }
                        
        _run_synapses_19_synapses_create_array_codeobject();
        _run_synapses_19_group_variable_set_conditional_codeobject();
        _run_synapses_19_pre_group_variable_set_conditional_codeobject();
        
                        
                        for(int i=0; i<_num__array_synapses_20_sources; i++)
                        {
                            _array_synapses_20_sources[i] = _static_array__array_synapses_20_sources[i];
                        }
                        
        
                        
                        for(int i=0; i<_num__array_synapses_20_targets; i++)
                        {
                            _array_synapses_20_targets[i] = _static_array__array_synapses_20_targets[i];
                        }
                        
        _run_synapses_20_synapses_create_array_codeobject();
        _run_synapses_20_group_variable_set_conditional_codeobject();
        _run_synapses_20_pre_group_variable_set_conditional_codeobject();
        
                        
                        for(int i=0; i<_num__array_synapses_21_sources; i++)
                        {
                            _array_synapses_21_sources[i] = _static_array__array_synapses_21_sources[i];
                        }
                        
        
                        
                        for(int i=0; i<_num__array_synapses_21_targets; i++)
                        {
                            _array_synapses_21_targets[i] = _static_array__array_synapses_21_targets[i];
                        }
                        
        _run_synapses_21_synapses_create_array_codeobject();
        _run_synapses_21_group_variable_set_conditional_codeobject();
        _run_synapses_21_pre_group_variable_set_conditional_codeobject();
        
                        
                        for(int i=0; i<_num__array_synapses_22_sources; i++)
                        {
                            _array_synapses_22_sources[i] = _static_array__array_synapses_22_sources[i];
                        }
                        
        
                        
                        for(int i=0; i<_num__array_synapses_22_targets; i++)
                        {
                            _array_synapses_22_targets[i] = _static_array__array_synapses_22_targets[i];
                        }
                        
        _run_synapses_22_synapses_create_array_codeobject();
        _run_synapses_22_group_variable_set_conditional_codeobject();
        _run_synapses_22_pre_group_variable_set_conditional_codeobject();
        
                        
                        for(int i=0; i<_num__array_synapses_23_sources; i++)
                        {
                            _array_synapses_23_sources[i] = _static_array__array_synapses_23_sources[i];
                        }
                        
        
                        
                        for(int i=0; i<_num__array_synapses_23_targets; i++)
                        {
                            _array_synapses_23_targets[i] = _static_array__array_synapses_23_targets[i];
                        }
                        
        _run_synapses_23_synapses_create_array_codeobject();
        _run_synapses_23_group_variable_set_conditional_codeobject();
        _run_synapses_23_pre_group_variable_set_conditional_codeobject();
        
                        
                        for(int i=0; i<_num__array_synapses_24_sources; i++)
                        {
                            _array_synapses_24_sources[i] = _static_array__array_synapses_24_sources[i];
                        }
                        
        
                        
                        for(int i=0; i<_num__array_synapses_24_targets; i++)
                        {
                            _array_synapses_24_targets[i] = _static_array__array_synapses_24_targets[i];
                        }
                        
        _run_synapses_24_synapses_create_array_codeobject();
        _run_synapses_24_group_variable_set_conditional_codeobject();
        _run_synapses_24_pre_group_variable_set_conditional_codeobject();
        
                        
                        for(int i=0; i<_num__array_synapses_25_sources; i++)
                        {
                            _array_synapses_25_sources[i] = _static_array__array_synapses_25_sources[i];
                        }
                        
        
                        
                        for(int i=0; i<_num__array_synapses_25_targets; i++)
                        {
                            _array_synapses_25_targets[i] = _static_array__array_synapses_25_targets[i];
                        }
                        
        _run_synapses_25_synapses_create_array_codeobject();
        _run_synapses_25_group_variable_set_conditional_codeobject();
        _run_synapses_25_pre_group_variable_set_conditional_codeobject();
        
                        
                        for(int i=0; i<_num__array_synapses_26_sources; i++)
                        {
                            _array_synapses_26_sources[i] = _static_array__array_synapses_26_sources[i];
                        }
                        
        
                        
                        for(int i=0; i<_num__array_synapses_26_targets; i++)
                        {
                            _array_synapses_26_targets[i] = _static_array__array_synapses_26_targets[i];
                        }
                        
        _run_synapses_26_synapses_create_array_codeobject();
        _run_synapses_26_group_variable_set_conditional_codeobject();
        _run_synapses_26_pre_group_variable_set_conditional_codeobject();
        
                        
                        for(int i=0; i<_num__array_synapses_27_sources; i++)
                        {
                            _array_synapses_27_sources[i] = _static_array__array_synapses_27_sources[i];
                        }
                        
        
                        
                        for(int i=0; i<_num__array_synapses_27_targets; i++)
                        {
                            _array_synapses_27_targets[i] = _static_array__array_synapses_27_targets[i];
                        }
                        
        _run_synapses_27_synapses_create_array_codeobject();
        _run_synapses_27_group_variable_set_conditional_codeobject();
        _run_synapses_27_pre_group_variable_set_conditional_codeobject();
        
                        
                        for(int i=0; i<_num__array_synapses_28_sources; i++)
                        {
                            _array_synapses_28_sources[i] = _static_array__array_synapses_28_sources[i];
                        }
                        
        
                        
                        for(int i=0; i<_num__array_synapses_28_targets; i++)
                        {
                            _array_synapses_28_targets[i] = _static_array__array_synapses_28_targets[i];
                        }
                        
        _run_synapses_28_synapses_create_array_codeobject();
        _run_synapses_28_group_variable_set_conditional_codeobject();
        _run_synapses_28_pre_group_variable_set_conditional_codeobject();
        
                        
                        for(int i=0; i<_num__array_synapses_29_sources; i++)
                        {
                            _array_synapses_29_sources[i] = _static_array__array_synapses_29_sources[i];
                        }
                        
        
                        
                        for(int i=0; i<_num__array_synapses_29_targets; i++)
                        {
                            _array_synapses_29_targets[i] = _static_array__array_synapses_29_targets[i];
                        }
                        
        _run_synapses_29_synapses_create_array_codeobject();
        _run_synapses_29_group_variable_set_conditional_codeobject();
        _run_synapses_29_pre_group_variable_set_conditional_codeobject();
        
                        
                        for(int i=0; i<_num__array_synapses_30_sources; i++)
                        {
                            _array_synapses_30_sources[i] = _static_array__array_synapses_30_sources[i];
                        }
                        
        
                        
                        for(int i=0; i<_num__array_synapses_30_targets; i++)
                        {
                            _array_synapses_30_targets[i] = _static_array__array_synapses_30_targets[i];
                        }
                        
        _run_synapses_30_synapses_create_array_codeobject();
        _run_synapses_30_group_variable_set_conditional_codeobject();
        _run_synapses_30_pre_group_variable_set_conditional_codeobject();
        
                        
                        for(int i=0; i<_num__array_synapses_31_sources; i++)
                        {
                            _array_synapses_31_sources[i] = _static_array__array_synapses_31_sources[i];
                        }
                        
        
                        
                        for(int i=0; i<_num__array_synapses_31_targets; i++)
                        {
                            _array_synapses_31_targets[i] = _static_array__array_synapses_31_targets[i];
                        }
                        
        _run_synapses_31_synapses_create_array_codeobject();
        _run_synapses_31_group_variable_set_conditional_codeobject();
        _run_synapses_31_pre_group_variable_set_conditional_codeobject();
        
                        
                        for(int i=0; i<_num__array_synapses_32_sources; i++)
                        {
                            _array_synapses_32_sources[i] = _static_array__array_synapses_32_sources[i];
                        }
                        
        
                        
                        for(int i=0; i<_num__array_synapses_32_targets; i++)
                        {
                            _array_synapses_32_targets[i] = _static_array__array_synapses_32_targets[i];
                        }
                        
        _run_synapses_32_synapses_create_array_codeobject();
        _run_synapses_32_group_variable_set_conditional_codeobject();
        _run_synapses_32_pre_group_variable_set_conditional_codeobject();
        
                        
                        for(int i=0; i<_num__array_synapses_33_sources; i++)
                        {
                            _array_synapses_33_sources[i] = _static_array__array_synapses_33_sources[i];
                        }
                        
        
                        
                        for(int i=0; i<_num__array_synapses_33_targets; i++)
                        {
                            _array_synapses_33_targets[i] = _static_array__array_synapses_33_targets[i];
                        }
                        
        _run_synapses_33_synapses_create_array_codeobject();
        _run_synapses_33_group_variable_set_conditional_codeobject();
        _run_synapses_33_pre_group_variable_set_conditional_codeobject();
        
                        
                        for(int i=0; i<_num__array_synapses_34_sources; i++)
                        {
                            _array_synapses_34_sources[i] = _static_array__array_synapses_34_sources[i];
                        }
                        
        
                        
                        for(int i=0; i<_num__array_synapses_34_targets; i++)
                        {
                            _array_synapses_34_targets[i] = _static_array__array_synapses_34_targets[i];
                        }
                        
        _run_synapses_34_synapses_create_array_codeobject();
        _run_synapses_34_group_variable_set_conditional_codeobject();
        _run_synapses_34_pre_group_variable_set_conditional_codeobject();
        
                        
                        for(int i=0; i<_num__array_synapses_35_sources; i++)
                        {
                            _array_synapses_35_sources[i] = _static_array__array_synapses_35_sources[i];
                        }
                        
        
                        
                        for(int i=0; i<_num__array_synapses_35_targets; i++)
                        {
                            _array_synapses_35_targets[i] = _static_array__array_synapses_35_targets[i];
                        }
                        
        _run_synapses_35_synapses_create_array_codeobject();
        _run_synapses_35_group_variable_set_conditional_codeobject();
        _run_synapses_35_pre_group_variable_set_conditional_codeobject();
        
                        
                        for(int i=0; i<_num__array_synapses_36_sources; i++)
                        {
                            _array_synapses_36_sources[i] = _static_array__array_synapses_36_sources[i];
                        }
                        
        
                        
                        for(int i=0; i<_num__array_synapses_36_targets; i++)
                        {
                            _array_synapses_36_targets[i] = _static_array__array_synapses_36_targets[i];
                        }
                        
        _run_synapses_36_synapses_create_array_codeobject();
        _run_synapses_36_group_variable_set_conditional_codeobject();
        _run_synapses_36_pre_group_variable_set_conditional_codeobject();
        
                        
                        for(int i=0; i<_num__array_synapses_37_sources; i++)
                        {
                            _array_synapses_37_sources[i] = _static_array__array_synapses_37_sources[i];
                        }
                        
        
                        
                        for(int i=0; i<_num__array_synapses_37_targets; i++)
                        {
                            _array_synapses_37_targets[i] = _static_array__array_synapses_37_targets[i];
                        }
                        
        _run_synapses_37_synapses_create_array_codeobject();
        _run_synapses_37_group_variable_set_conditional_codeobject();
        _run_synapses_37_pre_group_variable_set_conditional_codeobject();
        _array_defaultclock_timestep[0] = 0;
        _array_defaultclock_t[0] = 0.0;
        _array_spikegeneratorgroup__lastindex[0] = 0;
        
                        
                        for(int i=0; i<_dynamic_array_spikegeneratorgroup__timebins.size(); i++)
                        {
                            _dynamic_array_spikegeneratorgroup__timebins[i] = _static_array__dynamic_array_spikegeneratorgroup__timebins[i];
                        }
                        
        _array_spikegeneratorgroup__period_bins[0] = 0.0;
        _run_synapses_10_pre_initialise_queue();
        _run_synapses_11_pre_initialise_queue();
        _run_synapses_12_pre_initialise_queue();
        _run_synapses_13_pre_initialise_queue();
        _run_synapses_14_pre_initialise_queue();
        _run_synapses_15_pre_initialise_queue();
        _run_synapses_16_pre_initialise_queue();
        _run_synapses_17_pre_initialise_queue();
        _run_synapses_18_pre_initialise_queue();
        _run_synapses_19_pre_initialise_queue();
        _run_synapses_1_pre_initialise_queue();
        _run_synapses_20_pre_initialise_queue();
        _run_synapses_21_pre_initialise_queue();
        _run_synapses_22_pre_initialise_queue();
        _run_synapses_23_pre_initialise_queue();
        _run_synapses_24_pre_initialise_queue();
        _run_synapses_25_pre_initialise_queue();
        _run_synapses_26_pre_initialise_queue();
        _run_synapses_27_pre_initialise_queue();
        _run_synapses_28_pre_initialise_queue();
        _run_synapses_29_pre_initialise_queue();
        _run_synapses_2_pre_initialise_queue();
        _run_synapses_30_pre_initialise_queue();
        _run_synapses_31_pre_initialise_queue();
        _run_synapses_32_pre_initialise_queue();
        _run_synapses_33_pre_initialise_queue();
        _run_synapses_34_pre_initialise_queue();
        _run_synapses_35_pre_initialise_queue();
        _run_synapses_36_pre_initialise_queue();
        _run_synapses_37_pre_initialise_queue();
        _run_synapses_3_pre_initialise_queue();
        _run_synapses_4_pre_initialise_queue();
        _run_synapses_5_pre_initialise_queue();
        _run_synapses_6_pre_initialise_queue();
        _run_synapses_7_pre_initialise_queue();
        _run_synapses_8_pre_initialise_queue();
        _run_synapses_9_pre_initialise_queue();
        _run_synapses_pre_initialise_queue();
        magicnetwork.clear();
        magicnetwork.add(&defaultclock, _run_neurongroup_1_stateupdater_codeobject);
        magicnetwork.add(&defaultclock, _run_neurongroup_2_stateupdater_codeobject);
        magicnetwork.add(&defaultclock, _run_neurongroup_3_stateupdater_codeobject);
        magicnetwork.add(&defaultclock, _run_neurongroup_4_stateupdater_codeobject);
        magicnetwork.add(&defaultclock, _run_neurongroup_5_stateupdater_codeobject);
        magicnetwork.add(&defaultclock, _run_neurongroup_1_thresholder_codeobject);
        magicnetwork.add(&defaultclock, _run_neurongroup_2_thresholder_codeobject);
        magicnetwork.add(&defaultclock, _run_neurongroup_3_thresholder_codeobject);
        magicnetwork.add(&defaultclock, _run_neurongroup_4_thresholder_codeobject);
        magicnetwork.add(&defaultclock, _run_neurongroup_5_thresholder_codeobject);
        magicnetwork.add(&defaultclock, _run_neurongroup_thresholder_codeobject);
        magicnetwork.add(&defaultclock, _run_spikegeneratorgroup_codeobject);
        magicnetwork.add(&defaultclock, _run_spikemonitor_codeobject);
        magicnetwork.add(&defaultclock, _run_spikemonitor_1_codeobject);
        magicnetwork.add(&defaultclock, _run_spikemonitor_2_codeobject);
        magicnetwork.add(&defaultclock, _run_spikemonitor_3_codeobject);
        magicnetwork.add(&defaultclock, _run_spikemonitor_4_codeobject);
        magicnetwork.add(&defaultclock, _run_spikemonitor_5_codeobject);
        magicnetwork.add(&defaultclock, _run_synapses_10_pre_push_spikes);
        magicnetwork.add(&defaultclock, _run_synapses_10_pre_codeobject);
        magicnetwork.add(&defaultclock, _run_synapses_11_pre_push_spikes);
        magicnetwork.add(&defaultclock, _run_synapses_11_pre_codeobject);
        magicnetwork.add(&defaultclock, _run_synapses_12_pre_push_spikes);
        magicnetwork.add(&defaultclock, _run_synapses_12_pre_codeobject);
        magicnetwork.add(&defaultclock, _run_synapses_13_pre_push_spikes);
        magicnetwork.add(&defaultclock, _run_synapses_13_pre_codeobject);
        magicnetwork.add(&defaultclock, _run_synapses_14_pre_push_spikes);
        magicnetwork.add(&defaultclock, _run_synapses_14_pre_codeobject);
        magicnetwork.add(&defaultclock, _run_synapses_15_pre_push_spikes);
        magicnetwork.add(&defaultclock, _run_synapses_15_pre_codeobject);
        magicnetwork.add(&defaultclock, _run_synapses_16_pre_push_spikes);
        magicnetwork.add(&defaultclock, _run_synapses_16_pre_codeobject);
        magicnetwork.add(&defaultclock, _run_synapses_17_pre_push_spikes);
        magicnetwork.add(&defaultclock, _run_synapses_17_pre_codeobject);
        magicnetwork.add(&defaultclock, _run_synapses_18_pre_push_spikes);
        magicnetwork.add(&defaultclock, _run_synapses_18_pre_codeobject);
        magicnetwork.add(&defaultclock, _run_synapses_19_pre_push_spikes);
        magicnetwork.add(&defaultclock, _run_synapses_19_pre_codeobject);
        magicnetwork.add(&defaultclock, _run_synapses_1_pre_push_spikes);
        magicnetwork.add(&defaultclock, _run_synapses_1_pre_codeobject);
        magicnetwork.add(&defaultclock, _run_synapses_20_pre_push_spikes);
        magicnetwork.add(&defaultclock, _run_synapses_20_pre_codeobject);
        magicnetwork.add(&defaultclock, _run_synapses_21_pre_push_spikes);
        magicnetwork.add(&defaultclock, _run_synapses_21_pre_codeobject);
        magicnetwork.add(&defaultclock, _run_synapses_22_pre_push_spikes);
        magicnetwork.add(&defaultclock, _run_synapses_22_pre_codeobject);
        magicnetwork.add(&defaultclock, _run_synapses_23_pre_push_spikes);
        magicnetwork.add(&defaultclock, _run_synapses_23_pre_codeobject);
        magicnetwork.add(&defaultclock, _run_synapses_24_pre_push_spikes);
        magicnetwork.add(&defaultclock, _run_synapses_24_pre_codeobject);
        magicnetwork.add(&defaultclock, _run_synapses_25_pre_push_spikes);
        magicnetwork.add(&defaultclock, _run_synapses_25_pre_codeobject);
        magicnetwork.add(&defaultclock, _run_synapses_26_pre_push_spikes);
        magicnetwork.add(&defaultclock, _run_synapses_26_pre_codeobject);
        magicnetwork.add(&defaultclock, _run_synapses_27_pre_push_spikes);
        magicnetwork.add(&defaultclock, _run_synapses_27_pre_codeobject);
        magicnetwork.add(&defaultclock, _run_synapses_28_pre_push_spikes);
        magicnetwork.add(&defaultclock, _run_synapses_28_pre_codeobject);
        magicnetwork.add(&defaultclock, _run_synapses_29_pre_push_spikes);
        magicnetwork.add(&defaultclock, _run_synapses_29_pre_codeobject);
        magicnetwork.add(&defaultclock, _run_synapses_2_pre_push_spikes);
        magicnetwork.add(&defaultclock, _run_synapses_2_pre_codeobject);
        magicnetwork.add(&defaultclock, _run_synapses_30_pre_push_spikes);
        magicnetwork.add(&defaultclock, _run_synapses_30_pre_codeobject);
        magicnetwork.add(&defaultclock, _run_synapses_31_pre_push_spikes);
        magicnetwork.add(&defaultclock, _run_synapses_31_pre_codeobject);
        magicnetwork.add(&defaultclock, _run_synapses_32_pre_push_spikes);
        magicnetwork.add(&defaultclock, _run_synapses_32_pre_codeobject);
        magicnetwork.add(&defaultclock, _run_synapses_33_pre_push_spikes);
        magicnetwork.add(&defaultclock, _run_synapses_33_pre_codeobject);
        magicnetwork.add(&defaultclock, _run_synapses_34_pre_push_spikes);
        magicnetwork.add(&defaultclock, _run_synapses_34_pre_codeobject);
        magicnetwork.add(&defaultclock, _run_synapses_35_pre_push_spikes);
        magicnetwork.add(&defaultclock, _run_synapses_35_pre_codeobject);
        magicnetwork.add(&defaultclock, _run_synapses_36_pre_push_spikes);
        magicnetwork.add(&defaultclock, _run_synapses_36_pre_codeobject);
        magicnetwork.add(&defaultclock, _run_synapses_37_pre_push_spikes);
        magicnetwork.add(&defaultclock, _run_synapses_37_pre_codeobject);
        magicnetwork.add(&defaultclock, _run_synapses_3_pre_push_spikes);
        magicnetwork.add(&defaultclock, _run_synapses_3_pre_codeobject);
        magicnetwork.add(&defaultclock, _run_synapses_4_pre_push_spikes);
        magicnetwork.add(&defaultclock, _run_synapses_4_pre_codeobject);
        magicnetwork.add(&defaultclock, _run_synapses_5_pre_push_spikes);
        magicnetwork.add(&defaultclock, _run_synapses_5_pre_codeobject);
        magicnetwork.add(&defaultclock, _run_synapses_6_pre_push_spikes);
        magicnetwork.add(&defaultclock, _run_synapses_6_pre_codeobject);
        magicnetwork.add(&defaultclock, _run_synapses_7_pre_push_spikes);
        magicnetwork.add(&defaultclock, _run_synapses_7_pre_codeobject);
        magicnetwork.add(&defaultclock, _run_synapses_8_pre_push_spikes);
        magicnetwork.add(&defaultclock, _run_synapses_8_pre_codeobject);
        magicnetwork.add(&defaultclock, _run_synapses_9_pre_push_spikes);
        magicnetwork.add(&defaultclock, _run_synapses_9_pre_codeobject);
        magicnetwork.add(&defaultclock, _run_synapses_pre_push_spikes);
        magicnetwork.add(&defaultclock, _run_synapses_pre_codeobject);
        magicnetwork.add(&defaultclock, _run_poissoninput_codeobject);
        magicnetwork.add(&defaultclock, _run_poissoninput_1_codeobject);
        magicnetwork.add(&defaultclock, _run_poissoninput_10_codeobject);
        magicnetwork.add(&defaultclock, _run_poissoninput_11_codeobject);
        magicnetwork.add(&defaultclock, _run_poissoninput_12_codeobject);
        magicnetwork.add(&defaultclock, _run_poissoninput_13_codeobject);
        magicnetwork.add(&defaultclock, _run_poissoninput_14_codeobject);
        magicnetwork.add(&defaultclock, _run_poissoninput_15_codeobject);
        magicnetwork.add(&defaultclock, _run_poissoninput_2_codeobject);
        magicnetwork.add(&defaultclock, _run_poissoninput_3_codeobject);
        magicnetwork.add(&defaultclock, _run_poissoninput_4_codeobject);
        magicnetwork.add(&defaultclock, _run_poissoninput_5_codeobject);
        magicnetwork.add(&defaultclock, _run_poissoninput_6_codeobject);
        magicnetwork.add(&defaultclock, _run_poissoninput_7_codeobject);
        magicnetwork.add(&defaultclock, _run_poissoninput_8_codeobject);
        magicnetwork.add(&defaultclock, _run_poissoninput_9_codeobject);
        magicnetwork.add(&defaultclock, _run_neurongroup_1_resetter_codeobject);
        magicnetwork.add(&defaultclock, _run_neurongroup_2_resetter_codeobject);
        magicnetwork.add(&defaultclock, _run_neurongroup_3_resetter_codeobject);
        magicnetwork.add(&defaultclock, _run_neurongroup_4_resetter_codeobject);
        magicnetwork.add(&defaultclock, _run_neurongroup_5_resetter_codeobject);
        magicnetwork.add(&defaultclock, _run_neurongroup_resetter_codeobject);
        magicnetwork.run(0.2, report_progress, 10.0);
        #ifdef DEBUG
        _debugmsg_spikemonitor_codeobject();
        #endif
        
        #ifdef DEBUG
        _debugmsg_spikemonitor_1_codeobject();
        #endif
        
        #ifdef DEBUG
        _debugmsg_spikemonitor_2_codeobject();
        #endif
        
        #ifdef DEBUG
        _debugmsg_spikemonitor_3_codeobject();
        #endif
        
        #ifdef DEBUG
        _debugmsg_spikemonitor_4_codeobject();
        #endif
        
        #ifdef DEBUG
        _debugmsg_spikemonitor_5_codeobject();
        #endif
        
        #ifdef DEBUG
        _debugmsg_synapses_10_pre_codeobject();
        #endif
        
        #ifdef DEBUG
        _debugmsg_synapses_11_pre_codeobject();
        #endif
        
        #ifdef DEBUG
        _debugmsg_synapses_12_pre_codeobject();
        #endif
        
        #ifdef DEBUG
        _debugmsg_synapses_13_pre_codeobject();
        #endif
        
        #ifdef DEBUG
        _debugmsg_synapses_14_pre_codeobject();
        #endif
        
        #ifdef DEBUG
        _debugmsg_synapses_15_pre_codeobject();
        #endif
        
        #ifdef DEBUG
        _debugmsg_synapses_16_pre_codeobject();
        #endif
        
        #ifdef DEBUG
        _debugmsg_synapses_17_pre_codeobject();
        #endif
        
        #ifdef DEBUG
        _debugmsg_synapses_18_pre_codeobject();
        #endif
        
        #ifdef DEBUG
        _debugmsg_synapses_19_pre_codeobject();
        #endif
        
        #ifdef DEBUG
        _debugmsg_synapses_1_pre_codeobject();
        #endif
        
        #ifdef DEBUG
        _debugmsg_synapses_20_pre_codeobject();
        #endif
        
        #ifdef DEBUG
        _debugmsg_synapses_21_pre_codeobject();
        #endif
        
        #ifdef DEBUG
        _debugmsg_synapses_22_pre_codeobject();
        #endif
        
        #ifdef DEBUG
        _debugmsg_synapses_23_pre_codeobject();
        #endif
        
        #ifdef DEBUG
        _debugmsg_synapses_24_pre_codeobject();
        #endif
        
        #ifdef DEBUG
        _debugmsg_synapses_25_pre_codeobject();
        #endif
        
        #ifdef DEBUG
        _debugmsg_synapses_26_pre_codeobject();
        #endif
        
        #ifdef DEBUG
        _debugmsg_synapses_27_pre_codeobject();
        #endif
        
        #ifdef DEBUG
        _debugmsg_synapses_28_pre_codeobject();
        #endif
        
        #ifdef DEBUG
        _debugmsg_synapses_29_pre_codeobject();
        #endif
        
        #ifdef DEBUG
        _debugmsg_synapses_2_pre_codeobject();
        #endif
        
        #ifdef DEBUG
        _debugmsg_synapses_30_pre_codeobject();
        #endif
        
        #ifdef DEBUG
        _debugmsg_synapses_31_pre_codeobject();
        #endif
        
        #ifdef DEBUG
        _debugmsg_synapses_32_pre_codeobject();
        #endif
        
        #ifdef DEBUG
        _debugmsg_synapses_33_pre_codeobject();
        #endif
        
        #ifdef DEBUG
        _debugmsg_synapses_34_pre_codeobject();
        #endif
        
        #ifdef DEBUG
        _debugmsg_synapses_35_pre_codeobject();
        #endif
        
        #ifdef DEBUG
        _debugmsg_synapses_36_pre_codeobject();
        #endif
        
        #ifdef DEBUG
        _debugmsg_synapses_37_pre_codeobject();
        #endif
        
        #ifdef DEBUG
        _debugmsg_synapses_3_pre_codeobject();
        #endif
        
        #ifdef DEBUG
        _debugmsg_synapses_4_pre_codeobject();
        #endif
        
        #ifdef DEBUG
        _debugmsg_synapses_5_pre_codeobject();
        #endif
        
        #ifdef DEBUG
        _debugmsg_synapses_6_pre_codeobject();
        #endif
        
        #ifdef DEBUG
        _debugmsg_synapses_7_pre_codeobject();
        #endif
        
        #ifdef DEBUG
        _debugmsg_synapses_8_pre_codeobject();
        #endif
        
        #ifdef DEBUG
        _debugmsg_synapses_9_pre_codeobject();
        #endif
        
        #ifdef DEBUG
        _debugmsg_synapses_pre_codeobject();
        #endif

	}
        

	brian_end();
        

	return 0;
}