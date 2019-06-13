#include "objects.h"
#include "code_objects/neurongroup_1_stateupdater_codeobject.h"
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



void _run_neurongroup_1_stateupdater_codeobject()
{
	using namespace brian;

    const std::clock_t _start_time = std::clock();

	///// CONSTANTS ///////////
	const int _numgi_basal = 267;
const int _numvm_a1 = 267;
const int _numge_a0 = 267;
const int _numvm_a0 = 267;
const int _numgi_a1 = 267;
const int _numnot_refractory = 267;
const int _numgealpha_a0 = 267;
const int _numgialpha_basal = 267;
const int _numdt = 1;
const int _numge_soma = 267;
const int _numvm_a2 = 267;
const int _numgi_a0 = 267;
const int _numgealpha_a1 = 267;
const int _numgi_soma = 267;
const int _numgealpha_soma = 267;
const int _numgialpha_a1 = 267;
const int _numvm = 267;
const int _numge_a2 = 267;
const int _numgealpha_basal = 267;
const int _numvm_basal = 267;
const int _numlastspike = 267;
const int _numge_basal = 267;
const int _numgi_a2 = 267;
const int _numgialpha_a2 = 267;
const int _numge_a1 = 267;
const int _numt = 1;
const int _numgialpha_soma = 267;
const int _numgialpha_a0 = 267;
const int _numgealpha_a2 = 267;
	///// POINTERS ////////////
 	
 double* __restrict  _ptr_array_neurongroup_1_gi_basal = _array_neurongroup_1_gi_basal;
 double* __restrict  _ptr_array_neurongroup_1_vm_a1 = _array_neurongroup_1_vm_a1;
 double* __restrict  _ptr_array_neurongroup_1_ge_a0 = _array_neurongroup_1_ge_a0;
 double* __restrict  _ptr_array_neurongroup_1_vm_a0 = _array_neurongroup_1_vm_a0;
 double* __restrict  _ptr_array_neurongroup_1_gi_a1 = _array_neurongroup_1_gi_a1;
 char* __restrict  _ptr_array_neurongroup_1_not_refractory = _array_neurongroup_1_not_refractory;
 double* __restrict  _ptr_array_neurongroup_1_gealpha_a0 = _array_neurongroup_1_gealpha_a0;
 double* __restrict  _ptr_array_neurongroup_1_gialpha_basal = _array_neurongroup_1_gialpha_basal;
 double*   _ptr_array_defaultclock_dt = _array_defaultclock_dt;
 double* __restrict  _ptr_array_neurongroup_1_ge_soma = _array_neurongroup_1_ge_soma;
 double* __restrict  _ptr_array_neurongroup_1_vm_a2 = _array_neurongroup_1_vm_a2;
 double* __restrict  _ptr_array_neurongroup_1_gi_a0 = _array_neurongroup_1_gi_a0;
 double* __restrict  _ptr_array_neurongroup_1_gealpha_a1 = _array_neurongroup_1_gealpha_a1;
 double* __restrict  _ptr_array_neurongroup_1_gi_soma = _array_neurongroup_1_gi_soma;
 double* __restrict  _ptr_array_neurongroup_1_gealpha_soma = _array_neurongroup_1_gealpha_soma;
 double* __restrict  _ptr_array_neurongroup_1_gialpha_a1 = _array_neurongroup_1_gialpha_a1;
 double* __restrict  _ptr_array_neurongroup_1_vm = _array_neurongroup_1_vm;
 double* __restrict  _ptr_array_neurongroup_1_ge_a2 = _array_neurongroup_1_ge_a2;
 double* __restrict  _ptr_array_neurongroup_1_gealpha_basal = _array_neurongroup_1_gealpha_basal;
 double* __restrict  _ptr_array_neurongroup_1_vm_basal = _array_neurongroup_1_vm_basal;
 double* __restrict  _ptr_array_neurongroup_1_lastspike = _array_neurongroup_1_lastspike;
 double* __restrict  _ptr_array_neurongroup_1_ge_basal = _array_neurongroup_1_ge_basal;
 double* __restrict  _ptr_array_neurongroup_1_gi_a2 = _array_neurongroup_1_gi_a2;
 double* __restrict  _ptr_array_neurongroup_1_gialpha_a2 = _array_neurongroup_1_gialpha_a2;
 double* __restrict  _ptr_array_neurongroup_1_ge_a1 = _array_neurongroup_1_ge_a1;
 double*   _ptr_array_defaultclock_t = _array_defaultclock_t;
 double* __restrict  _ptr_array_neurongroup_1_gialpha_soma = _array_neurongroup_1_gialpha_soma;
 double* __restrict  _ptr_array_neurongroup_1_gialpha_a0 = _array_neurongroup_1_gialpha_a0;
 double* __restrict  _ptr_array_neurongroup_1_gealpha_a2 = _array_neurongroup_1_gealpha_a2;


	//// MAIN CODE ////////////
	// scalar code
	const int _vectorisation_idx = -1;
 	
 const double dt = _ptr_array_defaultclock_dt[0];
 const double t = _ptr_array_defaultclock_t[0];
 const int32_t _lio_1 = _timestep(4.0 * 0.001, dt);
 const double _lio_2 = _brian_pow(dt, 0.5);
 const double _lio_3 = 1.0f*dt/1e-12;
 const double _lio_4 = 0.021000000005255 * 1e-09;
 const double _lio_5 = 0.0547401180968913 * 1e-09;
 const double _lio_6 = 1.0f*(- dt)/0.003;
 const double _lio_7 = 1.0f*dt/0.003;
 const double _lio_8 = 1.0f*(- dt)/0.0083;
 const double _lio_9 = 1.0f*dt/0.0083;
 const double _lio_10 = 1.0f*(0.0210000001003783 * ((0.002 * 1e-09) * exp(1.0f*(- (- 0.0557511171965))/0.002)))/1e-12;
 const double _lio_11 = 1.0f*1.0/0.002;
 const double _lio_12 = 1.0f*(0.0210000001003783 * ((- 0.07265804000000001) * 1e-09))/1e-12;
 const double _lio_13 = 1.0f*(0.0601067963251688 * 0.0)/1e-12;
 const double _lio_14 = 1.0f*(0.0601067963251688 * (- 0.075))/1e-12;
 const double _lio_15 = 1.0f*(0.601067963251688 * 1e-09)/1e-12;
 const double _lio_16 = 1.0f*(0.0601067963251688 * 1.01625e-10)/1e-12;
 const double _lio_17 = 1.0f*0.0601067963251688/1e-12;
 const double _lio_18 = 1.0f*(1.22313592660375 * 1e-09)/1e-12;
 const double _lio_19 = 1.0f*(0.0601067963251688 * (1.01625e-10 * exp(1.0f*((- 0.02) * t)/0.001)))/1e-12;
 const double _lio_20 = 0.144913767460445 * ((_brian_pow(0.001, - 0.5)) * 0.0);
 const double _lio_21 = (_lio_12 + _lio_16) - _lio_19;
 const double _lio_22 = 0.0364934120828409 * 1e-09;
 const double _lio_23 = 0.0210000001003783 * 1e-09;
 const double _lio_24 = 0.601067963251688 * 1e-09;
 const double _lio_25 = 0.020999999986476 * 1e-09;
 const double _lio_26 = 0.120213592746573 * 1e-09;


	const int _N = 267;
	
	for(int _idx=0; _idx<_N; _idx++)
	{
	    // vector code
		const int _vectorisation_idx = _idx;
                
        double gi_basal = _ptr_array_neurongroup_1_gi_basal[_idx];
        double vm_a1 = _ptr_array_neurongroup_1_vm_a1[_idx];
        double ge_a0 = _ptr_array_neurongroup_1_ge_a0[_idx];
        double vm_a0 = _ptr_array_neurongroup_1_vm_a0[_idx];
        double gi_a1 = _ptr_array_neurongroup_1_gi_a1[_idx];
        char not_refractory = _ptr_array_neurongroup_1_not_refractory[_idx];
        double gealpha_a0 = _ptr_array_neurongroup_1_gealpha_a0[_idx];
        double gialpha_basal = _ptr_array_neurongroup_1_gialpha_basal[_idx];
        double ge_soma = _ptr_array_neurongroup_1_ge_soma[_idx];
        double vm_a2 = _ptr_array_neurongroup_1_vm_a2[_idx];
        double gi_a0 = _ptr_array_neurongroup_1_gi_a0[_idx];
        double gealpha_a1 = _ptr_array_neurongroup_1_gealpha_a1[_idx];
        double gi_soma = _ptr_array_neurongroup_1_gi_soma[_idx];
        double gealpha_soma = _ptr_array_neurongroup_1_gealpha_soma[_idx];
        double gialpha_a1 = _ptr_array_neurongroup_1_gialpha_a1[_idx];
        double vm = _ptr_array_neurongroup_1_vm[_idx];
        double ge_a2 = _ptr_array_neurongroup_1_ge_a2[_idx];
        double gealpha_basal = _ptr_array_neurongroup_1_gealpha_basal[_idx];
        double vm_basal = _ptr_array_neurongroup_1_vm_basal[_idx];
        const double lastspike = _ptr_array_neurongroup_1_lastspike[_idx];
        double ge_basal = _ptr_array_neurongroup_1_ge_basal[_idx];
        double gi_a2 = _ptr_array_neurongroup_1_gi_a2[_idx];
        double gialpha_a2 = _ptr_array_neurongroup_1_gialpha_a2[_idx];
        double ge_a1 = _ptr_array_neurongroup_1_ge_a1[_idx];
        double gialpha_soma = _ptr_array_neurongroup_1_gialpha_soma[_idx];
        double gialpha_a0 = _ptr_array_neurongroup_1_gialpha_a0[_idx];
        double gealpha_a2 = _ptr_array_neurongroup_1_gealpha_a2[_idx];
        not_refractory = _timestep(t - lastspike, dt) >= _lio_1;
        const double xi = _lio_2 * _randn(_vectorisation_idx);
        const double _vm_basal = (_lio_3 * ((((0.00547401180968913 * (gealpha_basal * (0.0 - vm_basal))) + (0.00547401180968913 * (gialpha_basal * ((- 0.075) - vm_basal)))) + (_lio_4 * ((- 0.07265804000000001) - vm_basal))) + (_lio_5 * (vm - vm_basal)))) + vm_basal;
        const double _ge_basal = (_lio_6 * ge_basal) + ge_basal;
        const double _gealpha_basal = (_lio_7 * (ge_basal - gealpha_basal)) + gealpha_basal;
        const double _gi_basal = (_lio_8 * gi_basal) + gi_basal;
        const double _gialpha_basal = (_lio_9 * (gi_basal - gialpha_basal)) + gialpha_basal;
        double _vm;
        if(!not_refractory)
            _vm = vm;
        else 
            _vm = ((dt * ((_lio_21 + (((((_lio_10 * exp(_lio_11 * vm)) + (_lio_13 * gealpha_soma)) + (_lio_14 * gialpha_soma)) + (_lio_15 * vm_a0)) + (_lio_15 * vm_basal))) - (((_lio_17 * (gealpha_soma * vm)) + (_lio_17 * (gialpha_soma * vm))) + (_lio_18 * vm)))) + (_lio_20 * xi)) + vm;
        const double _ge_soma = (_lio_6 * ge_soma) + ge_soma;
        const double _gealpha_soma = (_lio_7 * (ge_soma - gealpha_soma)) + gealpha_soma;
        const double _gi_soma = (_lio_8 * gi_soma) + gi_soma;
        const double _gialpha_soma = (_lio_9 * (gi_soma - gialpha_soma)) + gialpha_soma;
        const double _vm_a0 = (_lio_3 * (((((0.00547401180968913 * (gealpha_a0 * (0.0 - vm_a0))) + (0.00547401180968913 * (gialpha_a0 * ((- 0.075) - vm_a0)))) + (_lio_4 * ((- 0.07265804000000001) - vm_a0))) + (_lio_5 * (vm - vm_a0))) + (_lio_22 * ((- vm_a0) + vm_a1)))) + vm_a0;
        const double _ge_a0 = (_lio_6 * ge_a0) + ge_a0;
        const double _gealpha_a0 = (_lio_7 * (ge_a0 - gealpha_a0)) + gealpha_a0;
        const double _gi_a0 = (_lio_8 * gi_a0) + gi_a0;
        const double _gialpha_a0 = (_lio_9 * (gi_a0 - gialpha_a0)) + gialpha_a0;
        const double _vm_a1 = (_lio_3 * (((((0.0601067963251688 * (gealpha_a1 * (0.0 - vm_a1))) + (0.0601067963251688 * (gialpha_a1 * ((- 0.075) - vm_a1)))) + (_lio_23 * ((- 0.07265804000000001) - vm_a1))) + (_lio_24 * (vm_a0 - vm_a1))) + (_lio_24 * ((- vm_a1) + vm_a2)))) + vm_a1;
        const double _ge_a1 = (_lio_6 * ge_a1) + ge_a1;
        const double _gealpha_a1 = (_lio_7 * (ge_a1 - gealpha_a1)) + gealpha_a1;
        const double _gi_a1 = (_lio_8 * gi_a1) + gi_a1;
        const double _gialpha_a1 = (_lio_9 * (gi_a1 - gialpha_a1)) + gialpha_a1;
        const double _vm_a2 = (_lio_3 * ((((0.0180320389029699 * (gealpha_a2 * (0.0 - vm_a2))) + (0.0180320389029699 * (gialpha_a2 * ((- 0.075) - vm_a2)))) + (_lio_25 * ((- 0.07265804000000001) - vm_a2))) + (_lio_26 * (vm_a1 - vm_a2)))) + vm_a2;
        const double _ge_a2 = (_lio_6 * ge_a2) + ge_a2;
        const double _gealpha_a2 = (_lio_7 * (ge_a2 - gealpha_a2)) + gealpha_a2;
        const double _gi_a2 = (_lio_8 * gi_a2) + gi_a2;
        const double _gialpha_a2 = (_lio_9 * (gi_a2 - gialpha_a2)) + gialpha_a2;
        vm_basal = _vm_basal;
        ge_basal = _ge_basal;
        gealpha_basal = _gealpha_basal;
        gi_basal = _gi_basal;
        gialpha_basal = _gialpha_basal;
        if(not_refractory)
            vm = _vm;
        ge_soma = _ge_soma;
        gealpha_soma = _gealpha_soma;
        gi_soma = _gi_soma;
        gialpha_soma = _gialpha_soma;
        vm_a0 = _vm_a0;
        ge_a0 = _ge_a0;
        gealpha_a0 = _gealpha_a0;
        gi_a0 = _gi_a0;
        gialpha_a0 = _gialpha_a0;
        vm_a1 = _vm_a1;
        ge_a1 = _ge_a1;
        gealpha_a1 = _gealpha_a1;
        gi_a1 = _gi_a1;
        gialpha_a1 = _gialpha_a1;
        vm_a2 = _vm_a2;
        ge_a2 = _ge_a2;
        gealpha_a2 = _gealpha_a2;
        gi_a2 = _gi_a2;
        gialpha_a2 = _gialpha_a2;
        _ptr_array_neurongroup_1_gi_basal[_idx] = gi_basal;
        _ptr_array_neurongroup_1_vm_a1[_idx] = vm_a1;
        _ptr_array_neurongroup_1_ge_a0[_idx] = ge_a0;
        _ptr_array_neurongroup_1_vm_a0[_idx] = vm_a0;
        _ptr_array_neurongroup_1_gi_a1[_idx] = gi_a1;
        _ptr_array_neurongroup_1_not_refractory[_idx] = not_refractory;
        _ptr_array_neurongroup_1_gealpha_a0[_idx] = gealpha_a0;
        _ptr_array_neurongroup_1_gialpha_basal[_idx] = gialpha_basal;
        _ptr_array_neurongroup_1_ge_soma[_idx] = ge_soma;
        _ptr_array_neurongroup_1_vm_a2[_idx] = vm_a2;
        _ptr_array_neurongroup_1_gi_a0[_idx] = gi_a0;
        _ptr_array_neurongroup_1_gealpha_a1[_idx] = gealpha_a1;
        _ptr_array_neurongroup_1_gi_soma[_idx] = gi_soma;
        _ptr_array_neurongroup_1_gealpha_soma[_idx] = gealpha_soma;
        _ptr_array_neurongroup_1_gialpha_a1[_idx] = gialpha_a1;
        _ptr_array_neurongroup_1_vm[_idx] = vm;
        _ptr_array_neurongroup_1_ge_a2[_idx] = ge_a2;
        _ptr_array_neurongroup_1_gealpha_basal[_idx] = gealpha_basal;
        _ptr_array_neurongroup_1_vm_basal[_idx] = vm_basal;
        _ptr_array_neurongroup_1_ge_basal[_idx] = ge_basal;
        _ptr_array_neurongroup_1_gi_a2[_idx] = gi_a2;
        _ptr_array_neurongroup_1_gialpha_a2[_idx] = gialpha_a2;
        _ptr_array_neurongroup_1_ge_a1[_idx] = ge_a1;
        _ptr_array_neurongroup_1_gialpha_soma[_idx] = gialpha_soma;
        _ptr_array_neurongroup_1_gialpha_a0[_idx] = gialpha_a0;
        _ptr_array_neurongroup_1_gealpha_a2[_idx] = gealpha_a2;

	}

    const double _run_time = (double)(std::clock() -_start_time)/CLOCKS_PER_SEC;
    neurongroup_1_stateupdater_codeobject_profiling_info += _run_time;
}


