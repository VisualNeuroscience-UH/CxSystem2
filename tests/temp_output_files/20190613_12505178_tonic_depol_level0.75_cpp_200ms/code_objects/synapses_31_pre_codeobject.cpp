#include "objects.h"
#include "code_objects/synapses_31_pre_codeobject.h"
#include "brianlib/common_math.h"
#include "brianlib/stdint_compat.h"
#include<cmath>
#include<ctime>
#include<iostream>
#include<fstream>
#include<climits>
#include "brianlib/stdint_compat.h"
#include "synapses_classes.h"

////// SUPPORT CODE ///////
namespace {
 	
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



void _run_synapses_31_pre_codeobject()
{
	using namespace brian;

    const std::clock_t _start_time = std::clock();

	///// CONSTANTS ///////////
	int32_t* const _array_synapses_31__synaptic_pre = _dynamic_array_synapses_31__synaptic_pre.empty()? 0 : &_dynamic_array_synapses_31__synaptic_pre[0];
const int _num_synaptic_pre = _dynamic_array_synapses_31__synaptic_pre.size();
const int _numt = 1;
const int _numge_soma_post = 32;
double* const _array_synapses_31_wght = _dynamic_array_synapses_31_wght.empty()? 0 : &_dynamic_array_synapses_31_wght[0];
const int _numwght = _dynamic_array_synapses_31_wght.size();
double* const _array_synapses_31_lastupdate = _dynamic_array_synapses_31_lastupdate.empty()? 0 : &_dynamic_array_synapses_31_lastupdate[0];
const int _numlastupdate = _dynamic_array_synapses_31_lastupdate.size();
double* const _array_synapses_31_R = _dynamic_array_synapses_31_R.empty()? 0 : &_dynamic_array_synapses_31_R[0];
const int _numR = _dynamic_array_synapses_31_R.size();
int32_t* const _array_synapses_31__synaptic_post = _dynamic_array_synapses_31__synaptic_post.empty()? 0 : &_dynamic_array_synapses_31__synaptic_post[0];
const int _num_postsynaptic_idx = _dynamic_array_synapses_31__synaptic_post.size();
	///// POINTERS ////////////
 	
 int32_t* __restrict  _ptr_array_synapses_31__synaptic_pre = _array_synapses_31__synaptic_pre;
 double*   _ptr_array_defaultclock_t = _array_defaultclock_t;
 double* __restrict  _ptr_array_neurongroup_4_ge_soma = _array_neurongroup_4_ge_soma;
 double* __restrict  _ptr_array_synapses_31_wght = _array_synapses_31_wght;
 double* __restrict  _ptr_array_synapses_31_lastupdate = _array_synapses_31_lastupdate;
 double* __restrict  _ptr_array_synapses_31_R = _array_synapses_31_R;
 int32_t* __restrict  _ptr_array_synapses_31__synaptic_post = _array_synapses_31__synaptic_post;



	// This is only needed for the _debugmsg function below	
	

	// scalar code
	const int _vectorisation_idx = -1;
 	
 const double t = _ptr_array_defaultclock_t[0];
 const double _lio_1 = 1.0f*1.0/0.67;
 const double _lio_2 = 1.0 - 0.5;


	
	{
	std::vector<int> *_spiking_synapses = synapses_31_pre.peek();
	const unsigned int _num_spiking_synapses = _spiking_synapses->size();

	
	{
		for(unsigned int _spiking_synapse_idx=0;
			_spiking_synapse_idx<_num_spiking_synapses;
			_spiking_synapse_idx++)
		{
			const int _idx = (*_spiking_synapses)[_spiking_synapse_idx];
			const int _vectorisation_idx = _idx;
   			
   const int32_t _postsynaptic_idx = _ptr_array_synapses_31__synaptic_post[_idx];
   double ge_soma_post = _ptr_array_neurongroup_4_ge_soma[_postsynaptic_idx];
   const double wght = _ptr_array_synapses_31_wght[_idx];
   double lastupdate = _ptr_array_synapses_31_lastupdate[_idx];
   double R = _ptr_array_synapses_31_R[_idx];
   const double _R = (1.0 + (R * exp(_lio_1 * (- (t - lastupdate))))) - exp(_lio_1 * (- (t - lastupdate)));
   R = _R;
   ge_soma_post += 0.5 * (R * wght);
   R *= _lio_2;
   lastupdate = t;
   _ptr_array_neurongroup_4_ge_soma[_postsynaptic_idx] = ge_soma_post;
   _ptr_array_synapses_31_lastupdate[_idx] = lastupdate;
   _ptr_array_synapses_31_R[_idx] = R;

		}
	}
    }

    const double _run_time = (double)(std::clock() -_start_time)/CLOCKS_PER_SEC;
    synapses_31_pre_codeobject_profiling_info += _run_time;
}

void _debugmsg_synapses_31_pre_codeobject()
{
	using namespace brian;
	std::cout << "Number of synapses: " << _dynamic_array_synapses_31__synaptic_pre.size() << endl;
}

