#include "objects.h"
#include "code_objects/neurongroup_3_stateupdater_codeobject.h"
#include "brianlib/common_math.h"
#include "brianlib/stdint_compat.h"
#include<cmath>
#include<ctime>
#include<iostream>
#include<fstream>
#include<climits>

////// SUPPORT CODE ///////
namespace {
 	
 static inline int64_t _timestep(double t, double dt)
 {
     return (int64_t)((t + 1e-3*dt)/dt); 
 }
 double _randn(const int _vectorisation_idx) {
     return rk_gauss(brian::_mersenne_twister_states[0]);
 }
 template < typename T1, typename T2 > struct _higher_type;
 template < > struct _higher_type<int,int> { typedef int type; };
 template < > struct _higher_type<int,long> { typedef long type; };
 template < > struct _higher_type<int,long long> { typedef long long type; };
 template < > struct _higher_type<int,float> { typedef float type; };
 template < > struct _higher_type<int,double> { typedef double type; };
 template < > struct _higher_type<int,long double> { typedef long double type; };
 template < > struct _higher_type<long,int> { typedef long type; };
 template < > struct _higher_type<long,long> { typedef long type; };
 template < > struct _higher_type<long,long long> { typedef long long type; };
 template < > struct _higher_type<long,float> { typedef float type; };
 template < > struct _higher_type<long,double> { typedef double type; };
 template < > struct _higher_type<long,long double> { typedef long double type; };
 template < > struct _higher_type<long long,int> { typedef long long type; };
 template < > struct _higher_type<long long,long> { typedef long long type; };
 template < > struct _higher_type<long long,long long> { typedef long long type; };
 template < > struct _higher_type<long long,float> { typedef float type; };
 template < > struct _higher_type<long long,double> { typedef double type; };
 template < > struct _higher_type<long long,long double> { typedef long double type; };
 template < > struct _higher_type<float,int> { typedef float type; };
 template < > struct _higher_type<float,long> { typedef float type; };
 template < > struct _higher_type<float,long long> { typedef float type; };
 template < > struct _higher_type<float,float> { typedef float type; };
 template < > struct _higher_type<float,double> { typedef double type; };
 template < > struct _higher_type<float,long double> { typedef long double type; };
 template < > struct _higher_type<double,int> { typedef double type; };
 template < > struct _higher_type<double,long> { typedef double type; };
 template < > struct _higher_type<double,long long> { typedef double type; };
 template < > struct _higher_type<double,float> { typedef double type; };
 template < > struct _higher_type<double,double> { typedef double type; };
 template < > struct _higher_type<double,long double> { typedef long double type; };
 template < > struct _higher_type<long double,int> { typedef long double type; };
 template < > struct _higher_type<long double,long> { typedef long double type; };
 template < > struct _higher_type<long double,long long> { typedef long double type; };
 template < > struct _higher_type<long double,float> { typedef long double type; };
 template < > struct _higher_type<long double,double> { typedef long double type; };
 template < > struct _higher_type<long double,long double> { typedef long double type; };
 template < typename T1, typename T2 >
 static inline typename _higher_type<T1,T2>::type
 _brian_mod(T1 x, T2 y)
 {{
     return x-y*floor(1.0*x/y);
 }}
 template < typename T1, typename T2 >
 static inline typename _higher_type<T1,T2>::type
 _brian_floordiv(T1 x, T2 y)
 {{
     return floor(1.0*x/y);
 }}
 #ifdef _MSC_VER
 #define _brian_pow(x, y) (pow((double)(x), (y)))
 #else
 #define _brian_pow(x, y) (pow((x), (y)))
 #endif

}

////// HASH DEFINES ///////



void _run_neurongroup_3_stateupdater_codeobject()
{
	using namespace brian;

    const std::clock_t _start_time = std::clock();

	///// CONSTANTS ///////////
	const int _numnot_refractory = 40;
const int _numt = 1;
const int _numlastspike = 40;
const int _numgi_soma = 40;
const int _numge_soma = 40;
const int _numvm = 40;
const int _numdt = 1;
	///// POINTERS ////////////
 	
 char* __restrict  _ptr_array_neurongroup_3_not_refractory = _array_neurongroup_3_not_refractory;
 double*   _ptr_array_defaultclock_t = _array_defaultclock_t;
 double* __restrict  _ptr_array_neurongroup_3_lastspike = _array_neurongroup_3_lastspike;
 double* __restrict  _ptr_array_neurongroup_3_gi_soma = _array_neurongroup_3_gi_soma;
 double* __restrict  _ptr_array_neurongroup_3_ge_soma = _array_neurongroup_3_ge_soma;
 double* __restrict  _ptr_array_neurongroup_3_vm = _array_neurongroup_3_vm;
 double*   _ptr_array_defaultclock_dt = _array_defaultclock_dt;


	//// MAIN CODE ////////////
	// scalar code
	const int _vectorisation_idx = -1;
 	
 const double dt = _ptr_array_defaultclock_dt[0];
 const double t = _ptr_array_defaultclock_t[0];
 const int32_t _lio_1 = _timestep(4.0 * 0.001, dt);
 const double _lio_2 = _brian_pow(dt, 0.5);
 const double _lio_3 = 1.0f*((0.002 * 4.768068577800001e-09) * exp(1.0f*(- (- 0.0556988618021))/0.002))/1.7524133390299998e-10;
 const double _lio_4 = 1.0f*1.0/0.002;
 const double _lio_5 = 1.0f*((- 0.07366282) * 4.768068577800001e-09)/1.7524133390299998e-10;
 const double _lio_6 = 1.0f*0.0/1.7524133390299998e-10;
 const double _lio_7 = 1.0f*(- 0.075)/1.7524133390299998e-10;
 const double _lio_8 = 1.0f*5.7374999999999996e-11/1.7524133390299998e-10;
 const double _lio_9 = 1.0f*4.768068577800001e-09/1.7524133390299998e-10;
 const double _lio_10 = 1.0f*1.0/1.7524133390299998e-10;
 const double _lio_11 = 1.0f*(5.7374999999999996e-11 * exp(1.0f*((- 0.02) * t)/0.001))/1.7524133390299998e-10;
 const double _lio_12 = 0.0 * (_brian_pow(0.03675310684894906, - 0.5));
 const double _lio_13 = (_lio_5 + _lio_8) - _lio_11;
 const double _lio_14 = 1.0f*(- dt)/0.003;
 const double _lio_15 = 1.0f*(- dt)/0.0083;


	const int _N = 40;
	
	for(int _idx=0; _idx<_N; _idx++)
	{
	    // vector code
		const int _vectorisation_idx = _idx;
                
        const double lastspike = _ptr_array_neurongroup_3_lastspike[_idx];
        double gi_soma = _ptr_array_neurongroup_3_gi_soma[_idx];
        double ge_soma = _ptr_array_neurongroup_3_ge_soma[_idx];
        double vm = _ptr_array_neurongroup_3_vm[_idx];
        char not_refractory = _ptr_array_neurongroup_3_not_refractory[_idx];
        not_refractory = _timestep(t - lastspike, dt) >= _lio_1;
        const double xi = _lio_2 * _randn(_vectorisation_idx);
        double _vm;
        if(!not_refractory)
            _vm = vm;
        else 
            _vm = ((dt * ((_lio_13 + (((_lio_3 * exp(_lio_4 * vm)) + (_lio_6 * ge_soma)) + (_lio_7 * gi_soma))) - (((_lio_9 * vm) + (_lio_10 * (ge_soma * vm))) + (_lio_10 * (gi_soma * vm))))) + (_lio_12 * xi)) + vm;
        const double _ge_soma = (_lio_14 * ge_soma) + ge_soma;
        const double _gi_soma = (_lio_15 * gi_soma) + gi_soma;
        if(not_refractory)
            vm = _vm;
        ge_soma = _ge_soma;
        gi_soma = _gi_soma;
        _ptr_array_neurongroup_3_gi_soma[_idx] = gi_soma;
        _ptr_array_neurongroup_3_ge_soma[_idx] = ge_soma;
        _ptr_array_neurongroup_3_vm[_idx] = vm;
        _ptr_array_neurongroup_3_not_refractory[_idx] = not_refractory;

	}

    const double _run_time = (double)(std::clock() -_start_time)/CLOCKS_PER_SEC;
    neurongroup_3_stateupdater_codeobject_profiling_info += _run_time;
}


