#include "objects.h"
#include "code_objects/synapses_28_pre_initialise_queue.h"
void _run_synapses_28_pre_initialise_queue() {
	using namespace brian;
        
    double*   _ptr_array_defaultclock_dt = _array_defaultclock_dt;

    std::vector<double> &real_delays = _dynamic_array_synapses_28_delay;
    double* real_delays_data = real_delays.empty() ? 0 : &(real_delays[0]);
    int32_t* sources = synapses_28_pre.sources.empty() ? 0 : &(synapses_28_pre.sources[0]);
    const unsigned int n_delays = real_delays.size();
    const unsigned int n_synapses = synapses_28_pre.sources.size();
    synapses_28_pre.prepare(109,
                        109,
                        real_delays_data, n_delays, sources,
                        n_synapses,
                        _ptr_array_defaultclock_dt[0]);
}
