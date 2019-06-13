#include "objects.h"
#include "code_objects/poissoninput_9_codeobject.h"
#include "brianlib/common_math.h"
#include "brianlib/stdint_compat.h"
#include<cmath>
#include<ctime>
#include<iostream>
#include<fstream>
#include<climits>

////// SUPPORT CODE ///////
namespace {
 	
 double _rand(const int _vectorisation_idx) {
     return rk_double(brian::_mersenne_twister_states[0]);
 }
 long poissoninput_binomial_9(const int vectorisation_idx)
 {
     long X = 0;
     double px = 1.000000000000000;
     double U = _rand(vectorisation_idx);
     while (U > px)
     {
         X++;
         if (X > 10.000000000000000)
         {
             X = 0;
             px = 1.000000000000000;
             U = _rand(vectorisation_idx);
         } else
         {
             U -= px;
             px = ((290-X+1) * 0.000000000000000 * px)/(X*1.000000000000000);
         }
     }
     return X;
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



void _run_poissoninput_9_codeobject()
{
	using namespace brian;

    const std::clock_t _start_time = std::clock();

	///// CONSTANTS ///////////
	const int _numgi_soma = 109;
	///// POINTERS ////////////
 	
 double* __restrict  _ptr_array_neurongroup_2_gi_soma = _array_neurongroup_2_gi_soma;


	//// MAIN CODE ////////////
	// scalar code
	const int _vectorisation_idx = -1;
 	
 const double _lio_1 = 1.296 * 1e-09;


	const int _N = 109;
	
	for(int _idx=0; _idx<_N; _idx++)
	{
	    // vector code
		const int _vectorisation_idx = _idx;
                
        double gi_soma = _ptr_array_neurongroup_2_gi_soma[_idx];
        gi_soma += _lio_1 * poissoninput_binomial_9(_vectorisation_idx);
        _ptr_array_neurongroup_2_gi_soma[_idx] = gi_soma;

	}

    const double _run_time = (double)(std::clock() -_start_time)/CLOCKS_PER_SEC;
    poissoninput_9_codeobject_profiling_info += _run_time;
}


