#include "objects.h"
#include "code_objects/synapses_19_pre_push_spikes.h"
#include "brianlib/common_math.h"
#include "brianlib/stdint_compat.h"
#include<cmath>
#include<ctime>

void _run_synapses_19_pre_push_spikes()
{
    using namespace brian;

    const std::clock_t _start_time = std::clock();

    ///// CONSTANTS ///////////
    const int _num_spikespace = 268;
    ///// POINTERS ////////////
        
    int32_t* __restrict  _ptr_array_neurongroup_1__spikespace = _array_neurongroup_1__spikespace;


    //// MAIN CODE ////////////
    // we do advance at the beginning rather than at the end because it saves us making
    // a copy of the current spiking synapses
    
    {
        synapses_19_pre.advance();
        synapses_19_pre.push(_ptr_array_neurongroup_1__spikespace, _ptr_array_neurongroup_1__spikespace[_num_spikespace-1]);
    }

    // Profiling
    const double _run_time = (double)(std::clock() -_start_time)/CLOCKS_PER_SEC;
    synapses_19_pre_push_spikes_profiling_info += _run_time;
}
