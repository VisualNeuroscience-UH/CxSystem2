
#include "objects.h"
#include "synapses_classes.h"
#include "brianlib/clocks.h"
#include "brianlib/dynamic_array.h"
#include "brianlib/stdint_compat.h"
#include "network.h"
#include "randomkit.h"
#include<vector>
#include<iostream>
#include<fstream>

namespace brian {

std::vector< rk_state* > _mersenne_twister_states;

//////////////// networks /////////////////
Network magicnetwork;

//////////////// arrays ///////////////////
double * _array_defaultclock_dt;
const int _num__array_defaultclock_dt = 1;
double * _array_defaultclock_t;
const int _num__array_defaultclock_t = 1;
int64_t * _array_defaultclock_timestep;
const int _num__array_defaultclock_timestep = 1;
int32_t * _array_neurongroup_1__spikespace;
const int _num__array_neurongroup_1__spikespace = 268;
double * _array_neurongroup_1_ge_a0;
const int _num__array_neurongroup_1_ge_a0 = 267;
double * _array_neurongroup_1_ge_a1;
const int _num__array_neurongroup_1_ge_a1 = 267;
double * _array_neurongroup_1_ge_a2;
const int _num__array_neurongroup_1_ge_a2 = 267;
double * _array_neurongroup_1_ge_basal;
const int _num__array_neurongroup_1_ge_basal = 267;
double * _array_neurongroup_1_ge_soma;
const int _num__array_neurongroup_1_ge_soma = 267;
double * _array_neurongroup_1_gealpha_a0;
const int _num__array_neurongroup_1_gealpha_a0 = 267;
double * _array_neurongroup_1_gealpha_a1;
const int _num__array_neurongroup_1_gealpha_a1 = 267;
double * _array_neurongroup_1_gealpha_a2;
const int _num__array_neurongroup_1_gealpha_a2 = 267;
double * _array_neurongroup_1_gealpha_basal;
const int _num__array_neurongroup_1_gealpha_basal = 267;
double * _array_neurongroup_1_gealpha_soma;
const int _num__array_neurongroup_1_gealpha_soma = 267;
double * _array_neurongroup_1_gi_a0;
const int _num__array_neurongroup_1_gi_a0 = 267;
double * _array_neurongroup_1_gi_a1;
const int _num__array_neurongroup_1_gi_a1 = 267;
double * _array_neurongroup_1_gi_a2;
const int _num__array_neurongroup_1_gi_a2 = 267;
double * _array_neurongroup_1_gi_basal;
const int _num__array_neurongroup_1_gi_basal = 267;
double * _array_neurongroup_1_gi_soma;
const int _num__array_neurongroup_1_gi_soma = 267;
double * _array_neurongroup_1_gialpha_a0;
const int _num__array_neurongroup_1_gialpha_a0 = 267;
double * _array_neurongroup_1_gialpha_a1;
const int _num__array_neurongroup_1_gialpha_a1 = 267;
double * _array_neurongroup_1_gialpha_a2;
const int _num__array_neurongroup_1_gialpha_a2 = 267;
double * _array_neurongroup_1_gialpha_basal;
const int _num__array_neurongroup_1_gialpha_basal = 267;
double * _array_neurongroup_1_gialpha_soma;
const int _num__array_neurongroup_1_gialpha_soma = 267;
int32_t * _array_neurongroup_1_i;
const int _num__array_neurongroup_1_i = 267;
double * _array_neurongroup_1_lastspike;
const int _num__array_neurongroup_1_lastspike = 267;
char * _array_neurongroup_1_not_refractory;
const int _num__array_neurongroup_1_not_refractory = 267;
double * _array_neurongroup_1_vm;
const int _num__array_neurongroup_1_vm = 267;
double * _array_neurongroup_1_vm_a0;
const int _num__array_neurongroup_1_vm_a0 = 267;
double * _array_neurongroup_1_vm_a1;
const int _num__array_neurongroup_1_vm_a1 = 267;
double * _array_neurongroup_1_vm_a2;
const int _num__array_neurongroup_1_vm_a2 = 267;
double * _array_neurongroup_1_vm_basal;
const int _num__array_neurongroup_1_vm_basal = 267;
double * _array_neurongroup_1_x;
const int _num__array_neurongroup_1_x = 267;
double * _array_neurongroup_1_y;
const int _num__array_neurongroup_1_y = 267;
int32_t * _array_neurongroup_2__spikespace;
const int _num__array_neurongroup_2__spikespace = 110;
double * _array_neurongroup_2_ge_a0;
const int _num__array_neurongroup_2_ge_a0 = 109;
double * _array_neurongroup_2_ge_a1;
const int _num__array_neurongroup_2_ge_a1 = 109;
double * _array_neurongroup_2_ge_a2;
const int _num__array_neurongroup_2_ge_a2 = 109;
double * _array_neurongroup_2_ge_basal;
const int _num__array_neurongroup_2_ge_basal = 109;
double * _array_neurongroup_2_ge_soma;
const int _num__array_neurongroup_2_ge_soma = 109;
double * _array_neurongroup_2_gealpha_a0;
const int _num__array_neurongroup_2_gealpha_a0 = 109;
double * _array_neurongroup_2_gealpha_a1;
const int _num__array_neurongroup_2_gealpha_a1 = 109;
double * _array_neurongroup_2_gealpha_a2;
const int _num__array_neurongroup_2_gealpha_a2 = 109;
double * _array_neurongroup_2_gealpha_basal;
const int _num__array_neurongroup_2_gealpha_basal = 109;
double * _array_neurongroup_2_gealpha_soma;
const int _num__array_neurongroup_2_gealpha_soma = 109;
double * _array_neurongroup_2_gi_a0;
const int _num__array_neurongroup_2_gi_a0 = 109;
double * _array_neurongroup_2_gi_a1;
const int _num__array_neurongroup_2_gi_a1 = 109;
double * _array_neurongroup_2_gi_a2;
const int _num__array_neurongroup_2_gi_a2 = 109;
double * _array_neurongroup_2_gi_basal;
const int _num__array_neurongroup_2_gi_basal = 109;
double * _array_neurongroup_2_gi_soma;
const int _num__array_neurongroup_2_gi_soma = 109;
double * _array_neurongroup_2_gialpha_a0;
const int _num__array_neurongroup_2_gialpha_a0 = 109;
double * _array_neurongroup_2_gialpha_a1;
const int _num__array_neurongroup_2_gialpha_a1 = 109;
double * _array_neurongroup_2_gialpha_a2;
const int _num__array_neurongroup_2_gialpha_a2 = 109;
double * _array_neurongroup_2_gialpha_basal;
const int _num__array_neurongroup_2_gialpha_basal = 109;
double * _array_neurongroup_2_gialpha_soma;
const int _num__array_neurongroup_2_gialpha_soma = 109;
int32_t * _array_neurongroup_2_i;
const int _num__array_neurongroup_2_i = 109;
double * _array_neurongroup_2_lastspike;
const int _num__array_neurongroup_2_lastspike = 109;
char * _array_neurongroup_2_not_refractory;
const int _num__array_neurongroup_2_not_refractory = 109;
double * _array_neurongroup_2_vm;
const int _num__array_neurongroup_2_vm = 109;
double * _array_neurongroup_2_vm_a0;
const int _num__array_neurongroup_2_vm_a0 = 109;
double * _array_neurongroup_2_vm_a1;
const int _num__array_neurongroup_2_vm_a1 = 109;
double * _array_neurongroup_2_vm_a2;
const int _num__array_neurongroup_2_vm_a2 = 109;
double * _array_neurongroup_2_vm_basal;
const int _num__array_neurongroup_2_vm_basal = 109;
double * _array_neurongroup_2_x;
const int _num__array_neurongroup_2_x = 109;
double * _array_neurongroup_2_y;
const int _num__array_neurongroup_2_y = 109;
int32_t * _array_neurongroup_3__spikespace;
const int _num__array_neurongroup_3__spikespace = 41;
double * _array_neurongroup_3_ge_soma;
const int _num__array_neurongroup_3_ge_soma = 40;
double * _array_neurongroup_3_gi_soma;
const int _num__array_neurongroup_3_gi_soma = 40;
int32_t * _array_neurongroup_3_i;
const int _num__array_neurongroup_3_i = 40;
double * _array_neurongroup_3_lastspike;
const int _num__array_neurongroup_3_lastspike = 40;
char * _array_neurongroup_3_not_refractory;
const int _num__array_neurongroup_3_not_refractory = 40;
double * _array_neurongroup_3_vm;
const int _num__array_neurongroup_3_vm = 40;
double * _array_neurongroup_3_x;
const int _num__array_neurongroup_3_x = 40;
double * _array_neurongroup_3_y;
const int _num__array_neurongroup_3_y = 40;
int32_t * _array_neurongroup_4__spikespace;
const int _num__array_neurongroup_4__spikespace = 33;
double * _array_neurongroup_4_ge_soma;
const int _num__array_neurongroup_4_ge_soma = 32;
double * _array_neurongroup_4_gi_soma;
const int _num__array_neurongroup_4_gi_soma = 32;
int32_t * _array_neurongroup_4_i;
const int _num__array_neurongroup_4_i = 32;
double * _array_neurongroup_4_lastspike;
const int _num__array_neurongroup_4_lastspike = 32;
char * _array_neurongroup_4_not_refractory;
const int _num__array_neurongroup_4_not_refractory = 32;
double * _array_neurongroup_4_vm;
const int _num__array_neurongroup_4_vm = 32;
double * _array_neurongroup_4_x;
const int _num__array_neurongroup_4_x = 32;
double * _array_neurongroup_4_y;
const int _num__array_neurongroup_4_y = 32;
int32_t * _array_neurongroup_5__spikespace;
const int _num__array_neurongroup_5__spikespace = 14;
double * _array_neurongroup_5_ge_soma;
const int _num__array_neurongroup_5_ge_soma = 13;
double * _array_neurongroup_5_gi_soma;
const int _num__array_neurongroup_5_gi_soma = 13;
int32_t * _array_neurongroup_5_i;
const int _num__array_neurongroup_5_i = 13;
double * _array_neurongroup_5_lastspike;
const int _num__array_neurongroup_5_lastspike = 13;
char * _array_neurongroup_5_not_refractory;
const int _num__array_neurongroup_5_not_refractory = 13;
double * _array_neurongroup_5_vm;
const int _num__array_neurongroup_5_vm = 13;
double * _array_neurongroup_5_x;
const int _num__array_neurongroup_5_x = 13;
double * _array_neurongroup_5_y;
const int _num__array_neurongroup_5_y = 13;
int32_t * _array_neurongroup__spikespace;
const int _num__array_neurongroup__spikespace = 61;
double * _array_neurongroup_emit_spike;
const int _num__array_neurongroup_emit_spike = 60;
int32_t * _array_neurongroup_i;
const int _num__array_neurongroup_i = 60;
double * _array_neurongroup_x;
const int _num__array_neurongroup_x = 60;
double * _array_neurongroup_y;
const int _num__array_neurongroup_y = 60;
int32_t * _array_spikegeneratorgroup__lastindex;
const int _num__array_spikegeneratorgroup__lastindex = 1;
int32_t * _array_spikegeneratorgroup__period_bins;
const int _num__array_spikegeneratorgroup__period_bins = 1;
int32_t * _array_spikegeneratorgroup__spikespace;
const int _num__array_spikegeneratorgroup__spikespace = 61;
int32_t * _array_spikegeneratorgroup_i;
const int _num__array_spikegeneratorgroup_i = 60;
double * _array_spikegeneratorgroup_period;
const int _num__array_spikegeneratorgroup_period = 1;
int32_t * _array_spikemonitor_1__source_idx;
const int _num__array_spikemonitor_1__source_idx = 267;
int32_t * _array_spikemonitor_1_count;
const int _num__array_spikemonitor_1_count = 267;
int32_t * _array_spikemonitor_1_N;
const int _num__array_spikemonitor_1_N = 1;
int32_t * _array_spikemonitor_2__source_idx;
const int _num__array_spikemonitor_2__source_idx = 109;
int32_t * _array_spikemonitor_2_count;
const int _num__array_spikemonitor_2_count = 109;
int32_t * _array_spikemonitor_2_N;
const int _num__array_spikemonitor_2_N = 1;
int32_t * _array_spikemonitor_3__source_idx;
const int _num__array_spikemonitor_3__source_idx = 40;
int32_t * _array_spikemonitor_3_count;
const int _num__array_spikemonitor_3_count = 40;
int32_t * _array_spikemonitor_3_N;
const int _num__array_spikemonitor_3_N = 1;
int32_t * _array_spikemonitor_4__source_idx;
const int _num__array_spikemonitor_4__source_idx = 32;
int32_t * _array_spikemonitor_4_count;
const int _num__array_spikemonitor_4_count = 32;
int32_t * _array_spikemonitor_4_N;
const int _num__array_spikemonitor_4_N = 1;
int32_t * _array_spikemonitor_5__source_idx;
const int _num__array_spikemonitor_5__source_idx = 13;
int32_t * _array_spikemonitor_5_count;
const int _num__array_spikemonitor_5_count = 13;
int32_t * _array_spikemonitor_5_N;
const int _num__array_spikemonitor_5_N = 1;
int32_t * _array_spikemonitor__source_idx;
const int _num__array_spikemonitor__source_idx = 60;
int32_t * _array_spikemonitor_count;
const int _num__array_spikemonitor_count = 60;
int32_t * _array_spikemonitor_N;
const int _num__array_spikemonitor_N = 1;
int32_t * _array_synapses_10_N;
const int _num__array_synapses_10_N = 1;
int32_t * _array_synapses_10_sources;
const int _num__array_synapses_10_sources = 990;
int32_t * _array_synapses_10_targets;
const int _num__array_synapses_10_targets = 990;
int32_t * _array_synapses_11_N;
const int _num__array_synapses_11_N = 1;
int32_t * _array_synapses_11_sources;
const int _num__array_synapses_11_sources = 357;
int32_t * _array_synapses_11_targets;
const int _num__array_synapses_11_targets = 357;
int32_t * _array_synapses_12_N;
const int _num__array_synapses_12_N = 1;
int32_t * _array_synapses_12_sources;
const int _num__array_synapses_12_sources = 28;
int32_t * _array_synapses_12_targets;
const int _num__array_synapses_12_targets = 28;
int32_t * _array_synapses_13_N;
const int _num__array_synapses_13_N = 1;
int32_t * _array_synapses_13_sources;
const int _num__array_synapses_13_sources = 45;
int32_t * _array_synapses_13_targets;
const int _num__array_synapses_13_targets = 45;
int32_t * _array_synapses_14_N;
const int _num__array_synapses_14_N = 1;
int32_t * _array_synapses_14_sources;
const int _num__array_synapses_14_sources = 492;
int32_t * _array_synapses_14_targets;
const int _num__array_synapses_14_targets = 492;
int32_t * _array_synapses_15_N;
const int _num__array_synapses_15_N = 1;
int32_t * _array_synapses_15_sources;
const int _num__array_synapses_15_sources = 300;
int32_t * _array_synapses_15_targets;
const int _num__array_synapses_15_targets = 300;
int32_t * _array_synapses_16_N;
const int _num__array_synapses_16_N = 1;
int32_t * _array_synapses_16_sources;
const int _num__array_synapses_16_sources = 154;
int32_t * _array_synapses_16_targets;
const int _num__array_synapses_16_targets = 154;
int32_t * _array_synapses_17_N;
const int _num__array_synapses_17_N = 1;
int32_t * _array_synapses_17_sources;
const int _num__array_synapses_17_sources = 370;
int32_t * _array_synapses_17_targets;
const int _num__array_synapses_17_targets = 370;
int32_t * _array_synapses_18_N;
const int _num__array_synapses_18_N = 1;
int32_t * _array_synapses_18_sources;
const int _num__array_synapses_18_sources = 252;
int32_t * _array_synapses_18_targets;
const int _num__array_synapses_18_targets = 252;
int32_t * _array_synapses_19_N;
const int _num__array_synapses_19_N = 1;
int32_t * _array_synapses_19_sources;
const int _num__array_synapses_19_sources = 2097;
int32_t * _array_synapses_19_targets;
const int _num__array_synapses_19_targets = 2097;
int32_t * _array_synapses_1_N;
const int _num__array_synapses_1_N = 1;
int32_t * _array_synapses_1_sources;
const int _num__array_synapses_1_sources = 4803;
int32_t * _array_synapses_1_targets;
const int _num__array_synapses_1_targets = 4803;
int32_t * _array_synapses_20_N;
const int _num__array_synapses_20_N = 1;
int32_t * _array_synapses_20_sources;
const int _num__array_synapses_20_sources = 2142;
int32_t * _array_synapses_20_targets;
const int _num__array_synapses_20_targets = 2142;
int32_t * _array_synapses_21_N;
const int _num__array_synapses_21_N = 1;
int32_t * _array_synapses_21_sources;
const int _num__array_synapses_21_sources = 762;
int32_t * _array_synapses_21_targets;
const int _num__array_synapses_21_targets = 762;
int32_t * _array_synapses_22_N;
const int _num__array_synapses_22_N = 1;
int32_t * _array_synapses_22_sources;
const int _num__array_synapses_22_sources = 747;
int32_t * _array_synapses_22_targets;
const int _num__array_synapses_22_targets = 747;
int32_t * _array_synapses_23_N;
const int _num__array_synapses_23_N = 1;
int32_t * _array_synapses_23_sources;
const int _num__array_synapses_23_sources = 642;
int32_t * _array_synapses_23_targets;
const int _num__array_synapses_23_targets = 642;
int32_t * _array_synapses_24_N;
const int _num__array_synapses_24_N = 1;
int32_t * _array_synapses_24_sources;
const int _num__array_synapses_24_sources = 140;
int32_t * _array_synapses_24_targets;
const int _num__array_synapses_24_targets = 140;
int32_t * _array_synapses_25_N;
const int _num__array_synapses_25_N = 1;
int32_t * _array_synapses_25_sources;
const int _num__array_synapses_25_sources = 112;
int32_t * _array_synapses_25_targets;
const int _num__array_synapses_25_targets = 112;
int32_t * _array_synapses_26_N;
const int _num__array_synapses_26_N = 1;
int32_t * _array_synapses_26_sources;
const int _num__array_synapses_26_sources = 512;
int32_t * _array_synapses_26_targets;
const int _num__array_synapses_26_targets = 512;
int32_t * _array_synapses_27_N;
const int _num__array_synapses_27_N = 1;
int32_t * _array_synapses_27_sources;
const int _num__array_synapses_27_sources = 510;
int32_t * _array_synapses_27_targets;
const int _num__array_synapses_27_targets = 510;
int32_t * _array_synapses_28_N;
const int _num__array_synapses_28_N = 1;
int32_t * _array_synapses_28_sources;
const int _num__array_synapses_28_sources = 204;
int32_t * _array_synapses_28_targets;
const int _num__array_synapses_28_targets = 204;
int32_t * _array_synapses_29_N;
const int _num__array_synapses_29_N = 1;
int32_t * _array_synapses_29_sources;
const int _num__array_synapses_29_sources = 234;
int32_t * _array_synapses_29_targets;
const int _num__array_synapses_29_targets = 234;
int32_t * _array_synapses_2_N;
const int _num__array_synapses_2_N = 1;
int32_t * _array_synapses_2_sources;
const int _num__array_synapses_2_sources = 6336;
int32_t * _array_synapses_2_targets;
const int _num__array_synapses_2_targets = 6336;
int32_t * _array_synapses_30_N;
const int _num__array_synapses_30_N = 1;
int32_t * _array_synapses_30_sources;
const int _num__array_synapses_30_sources = 168;
int32_t * _array_synapses_30_targets;
const int _num__array_synapses_30_targets = 168;
int32_t * _array_synapses_31_N;
const int _num__array_synapses_31_N = 1;
int32_t * _array_synapses_31_sources;
const int _num__array_synapses_31_sources = 21;
int32_t * _array_synapses_31_targets;
const int _num__array_synapses_31_targets = 21;
int32_t * _array_synapses_32_N;
const int _num__array_synapses_32_N = 1;
int32_t * _array_synapses_32_sources;
const int _num__array_synapses_32_sources = 27;
int32_t * _array_synapses_32_targets;
const int _num__array_synapses_32_targets = 27;
int32_t * _array_synapses_33_N;
const int _num__array_synapses_33_N = 1;
int32_t * _array_synapses_33_sources;
const int _num__array_synapses_33_sources = 333;
int32_t * _array_synapses_33_targets;
const int _num__array_synapses_33_targets = 333;
int32_t * _array_synapses_34_N;
const int _num__array_synapses_34_N = 1;
int32_t * _array_synapses_34_sources;
const int _num__array_synapses_34_sources = 333;
int32_t * _array_synapses_34_targets;
const int _num__array_synapses_34_targets = 333;
int32_t * _array_synapses_35_N;
const int _num__array_synapses_35_N = 1;
int32_t * _array_synapses_35_sources;
const int _num__array_synapses_35_sources = 105;
int32_t * _array_synapses_35_targets;
const int _num__array_synapses_35_targets = 105;
int32_t * _array_synapses_36_N;
const int _num__array_synapses_36_N = 1;
int32_t * _array_synapses_36_sources;
const int _num__array_synapses_36_sources = 78;
int32_t * _array_synapses_36_targets;
const int _num__array_synapses_36_targets = 78;
int32_t * _array_synapses_37_N;
const int _num__array_synapses_37_N = 1;
int32_t * _array_synapses_37_sources;
const int _num__array_synapses_37_sources = 66;
int32_t * _array_synapses_37_targets;
const int _num__array_synapses_37_targets = 66;
int32_t * _array_synapses_3_N;
const int _num__array_synapses_3_N = 1;
int32_t * _array_synapses_3_sources;
const int _num__array_synapses_3_sources = 1938;
int32_t * _array_synapses_3_targets;
const int _num__array_synapses_3_targets = 1938;
int32_t * _array_synapses_4_N;
const int _num__array_synapses_4_N = 1;
int32_t * _array_synapses_4_sources;
const int _num__array_synapses_4_sources = 2588;
int32_t * _array_synapses_4_targets;
const int _num__array_synapses_4_targets = 2588;
int32_t * _array_synapses_5_N;
const int _num__array_synapses_5_N = 1;
int32_t * _array_synapses_5_sources;
const int _num__array_synapses_5_sources = 11697;
int32_t * _array_synapses_5_targets;
const int _num__array_synapses_5_targets = 11697;
int32_t * _array_synapses_6_N;
const int _num__array_synapses_6_N = 1;
int32_t * _array_synapses_6_sources;
const int _num__array_synapses_6_sources = 1384;
int32_t * _array_synapses_6_targets;
const int _num__array_synapses_6_targets = 1384;
int32_t * _array_synapses_7_N;
const int _num__array_synapses_7_N = 1;
int32_t * _array_synapses_7_sources;
const int _num__array_synapses_7_sources = 224;
int32_t * _array_synapses_7_targets;
const int _num__array_synapses_7_targets = 224;
int32_t * _array_synapses_8_N;
const int _num__array_synapses_8_N = 1;
int32_t * _array_synapses_8_sources;
const int _num__array_synapses_8_sources = 108;
int32_t * _array_synapses_8_targets;
const int _num__array_synapses_8_targets = 108;
int32_t * _array_synapses_9_N;
const int _num__array_synapses_9_N = 1;
int32_t * _array_synapses_9_sources;
const int _num__array_synapses_9_sources = 1854;
int32_t * _array_synapses_9_targets;
const int _num__array_synapses_9_targets = 1854;
int32_t * _array_synapses_N;
const int _num__array_synapses_N = 1;

//////////////// dynamic arrays 1d /////////
std::vector<int32_t> _dynamic_array_spikegeneratorgroup__timebins;
std::vector<int32_t> _dynamic_array_spikegeneratorgroup_neuron_index;
std::vector<int32_t> _dynamic_array_spikegeneratorgroup_spike_number;
std::vector<double> _dynamic_array_spikegeneratorgroup_spike_time;
std::vector<int32_t> _dynamic_array_spikemonitor_1_i;
std::vector<double> _dynamic_array_spikemonitor_1_t;
std::vector<int32_t> _dynamic_array_spikemonitor_2_i;
std::vector<double> _dynamic_array_spikemonitor_2_t;
std::vector<int32_t> _dynamic_array_spikemonitor_3_i;
std::vector<double> _dynamic_array_spikemonitor_3_t;
std::vector<int32_t> _dynamic_array_spikemonitor_4_i;
std::vector<double> _dynamic_array_spikemonitor_4_t;
std::vector<int32_t> _dynamic_array_spikemonitor_5_i;
std::vector<double> _dynamic_array_spikemonitor_5_t;
std::vector<int32_t> _dynamic_array_spikemonitor_i;
std::vector<double> _dynamic_array_spikemonitor_t;
std::vector<int32_t> _dynamic_array_synapses_10__synaptic_post;
std::vector<int32_t> _dynamic_array_synapses_10__synaptic_pre;
std::vector<double> _dynamic_array_synapses_10_delay;
std::vector<double> _dynamic_array_synapses_10_lastupdate;
std::vector<int32_t> _dynamic_array_synapses_10_N_incoming;
std::vector<int32_t> _dynamic_array_synapses_10_N_outgoing;
std::vector<double> _dynamic_array_synapses_10_R;
std::vector<double> _dynamic_array_synapses_10_wght;
std::vector<int32_t> _dynamic_array_synapses_11__synaptic_post;
std::vector<int32_t> _dynamic_array_synapses_11__synaptic_pre;
std::vector<double> _dynamic_array_synapses_11_delay;
std::vector<double> _dynamic_array_synapses_11_lastupdate;
std::vector<int32_t> _dynamic_array_synapses_11_N_incoming;
std::vector<int32_t> _dynamic_array_synapses_11_N_outgoing;
std::vector<double> _dynamic_array_synapses_11_R;
std::vector<double> _dynamic_array_synapses_11_wght;
std::vector<int32_t> _dynamic_array_synapses_12__synaptic_post;
std::vector<int32_t> _dynamic_array_synapses_12__synaptic_pre;
std::vector<double> _dynamic_array_synapses_12_delay;
std::vector<double> _dynamic_array_synapses_12_lastupdate;
std::vector<int32_t> _dynamic_array_synapses_12_N_incoming;
std::vector<int32_t> _dynamic_array_synapses_12_N_outgoing;
std::vector<double> _dynamic_array_synapses_12_R;
std::vector<double> _dynamic_array_synapses_12_wght;
std::vector<int32_t> _dynamic_array_synapses_13__synaptic_post;
std::vector<int32_t> _dynamic_array_synapses_13__synaptic_pre;
std::vector<double> _dynamic_array_synapses_13_delay;
std::vector<double> _dynamic_array_synapses_13_lastupdate;
std::vector<int32_t> _dynamic_array_synapses_13_N_incoming;
std::vector<int32_t> _dynamic_array_synapses_13_N_outgoing;
std::vector<double> _dynamic_array_synapses_13_R;
std::vector<double> _dynamic_array_synapses_13_wght;
std::vector<int32_t> _dynamic_array_synapses_14__synaptic_post;
std::vector<int32_t> _dynamic_array_synapses_14__synaptic_pre;
std::vector<double> _dynamic_array_synapses_14_delay;
std::vector<double> _dynamic_array_synapses_14_lastupdate;
std::vector<int32_t> _dynamic_array_synapses_14_N_incoming;
std::vector<int32_t> _dynamic_array_synapses_14_N_outgoing;
std::vector<double> _dynamic_array_synapses_14_R;
std::vector<double> _dynamic_array_synapses_14_wght;
std::vector<int32_t> _dynamic_array_synapses_15__synaptic_post;
std::vector<int32_t> _dynamic_array_synapses_15__synaptic_pre;
std::vector<double> _dynamic_array_synapses_15_delay;
std::vector<double> _dynamic_array_synapses_15_lastupdate;
std::vector<int32_t> _dynamic_array_synapses_15_N_incoming;
std::vector<int32_t> _dynamic_array_synapses_15_N_outgoing;
std::vector<double> _dynamic_array_synapses_15_R;
std::vector<double> _dynamic_array_synapses_15_wght;
std::vector<int32_t> _dynamic_array_synapses_16__synaptic_post;
std::vector<int32_t> _dynamic_array_synapses_16__synaptic_pre;
std::vector<double> _dynamic_array_synapses_16_delay;
std::vector<double> _dynamic_array_synapses_16_lastupdate;
std::vector<int32_t> _dynamic_array_synapses_16_N_incoming;
std::vector<int32_t> _dynamic_array_synapses_16_N_outgoing;
std::vector<double> _dynamic_array_synapses_16_R;
std::vector<double> _dynamic_array_synapses_16_wght;
std::vector<int32_t> _dynamic_array_synapses_17__synaptic_post;
std::vector<int32_t> _dynamic_array_synapses_17__synaptic_pre;
std::vector<double> _dynamic_array_synapses_17_delay;
std::vector<double> _dynamic_array_synapses_17_lastupdate;
std::vector<int32_t> _dynamic_array_synapses_17_N_incoming;
std::vector<int32_t> _dynamic_array_synapses_17_N_outgoing;
std::vector<double> _dynamic_array_synapses_17_R;
std::vector<double> _dynamic_array_synapses_17_wght;
std::vector<int32_t> _dynamic_array_synapses_18__synaptic_post;
std::vector<int32_t> _dynamic_array_synapses_18__synaptic_pre;
std::vector<double> _dynamic_array_synapses_18_delay;
std::vector<double> _dynamic_array_synapses_18_lastupdate;
std::vector<int32_t> _dynamic_array_synapses_18_N_incoming;
std::vector<int32_t> _dynamic_array_synapses_18_N_outgoing;
std::vector<double> _dynamic_array_synapses_18_R;
std::vector<double> _dynamic_array_synapses_18_wght;
std::vector<int32_t> _dynamic_array_synapses_19__synaptic_post;
std::vector<int32_t> _dynamic_array_synapses_19__synaptic_pre;
std::vector<double> _dynamic_array_synapses_19_delay;
std::vector<double> _dynamic_array_synapses_19_lastupdate;
std::vector<int32_t> _dynamic_array_synapses_19_N_incoming;
std::vector<int32_t> _dynamic_array_synapses_19_N_outgoing;
std::vector<double> _dynamic_array_synapses_19_R;
std::vector<double> _dynamic_array_synapses_19_wght;
std::vector<int32_t> _dynamic_array_synapses_1__synaptic_post;
std::vector<int32_t> _dynamic_array_synapses_1__synaptic_pre;
std::vector<double> _dynamic_array_synapses_1_delay;
std::vector<double> _dynamic_array_synapses_1_lastupdate;
std::vector<int32_t> _dynamic_array_synapses_1_N_incoming;
std::vector<int32_t> _dynamic_array_synapses_1_N_outgoing;
std::vector<double> _dynamic_array_synapses_1_R;
std::vector<double> _dynamic_array_synapses_1_wght;
std::vector<int32_t> _dynamic_array_synapses_20__synaptic_post;
std::vector<int32_t> _dynamic_array_synapses_20__synaptic_pre;
std::vector<double> _dynamic_array_synapses_20_delay;
std::vector<double> _dynamic_array_synapses_20_lastupdate;
std::vector<int32_t> _dynamic_array_synapses_20_N_incoming;
std::vector<int32_t> _dynamic_array_synapses_20_N_outgoing;
std::vector<double> _dynamic_array_synapses_20_R;
std::vector<double> _dynamic_array_synapses_20_wght;
std::vector<int32_t> _dynamic_array_synapses_21__synaptic_post;
std::vector<int32_t> _dynamic_array_synapses_21__synaptic_pre;
std::vector<double> _dynamic_array_synapses_21_delay;
std::vector<double> _dynamic_array_synapses_21_lastupdate;
std::vector<int32_t> _dynamic_array_synapses_21_N_incoming;
std::vector<int32_t> _dynamic_array_synapses_21_N_outgoing;
std::vector<double> _dynamic_array_synapses_21_R;
std::vector<double> _dynamic_array_synapses_21_wght;
std::vector<int32_t> _dynamic_array_synapses_22__synaptic_post;
std::vector<int32_t> _dynamic_array_synapses_22__synaptic_pre;
std::vector<double> _dynamic_array_synapses_22_delay;
std::vector<double> _dynamic_array_synapses_22_lastupdate;
std::vector<int32_t> _dynamic_array_synapses_22_N_incoming;
std::vector<int32_t> _dynamic_array_synapses_22_N_outgoing;
std::vector<double> _dynamic_array_synapses_22_R;
std::vector<double> _dynamic_array_synapses_22_wght;
std::vector<int32_t> _dynamic_array_synapses_23__synaptic_post;
std::vector<int32_t> _dynamic_array_synapses_23__synaptic_pre;
std::vector<double> _dynamic_array_synapses_23_delay;
std::vector<double> _dynamic_array_synapses_23_lastupdate;
std::vector<int32_t> _dynamic_array_synapses_23_N_incoming;
std::vector<int32_t> _dynamic_array_synapses_23_N_outgoing;
std::vector<double> _dynamic_array_synapses_23_R;
std::vector<double> _dynamic_array_synapses_23_wght;
std::vector<int32_t> _dynamic_array_synapses_24__synaptic_post;
std::vector<int32_t> _dynamic_array_synapses_24__synaptic_pre;
std::vector<double> _dynamic_array_synapses_24_delay;
std::vector<double> _dynamic_array_synapses_24_lastupdate;
std::vector<int32_t> _dynamic_array_synapses_24_N_incoming;
std::vector<int32_t> _dynamic_array_synapses_24_N_outgoing;
std::vector<double> _dynamic_array_synapses_24_R;
std::vector<double> _dynamic_array_synapses_24_wght;
std::vector<int32_t> _dynamic_array_synapses_25__synaptic_post;
std::vector<int32_t> _dynamic_array_synapses_25__synaptic_pre;
std::vector<double> _dynamic_array_synapses_25_delay;
std::vector<double> _dynamic_array_synapses_25_lastupdate;
std::vector<int32_t> _dynamic_array_synapses_25_N_incoming;
std::vector<int32_t> _dynamic_array_synapses_25_N_outgoing;
std::vector<double> _dynamic_array_synapses_25_R;
std::vector<double> _dynamic_array_synapses_25_wght;
std::vector<int32_t> _dynamic_array_synapses_26__synaptic_post;
std::vector<int32_t> _dynamic_array_synapses_26__synaptic_pre;
std::vector<double> _dynamic_array_synapses_26_delay;
std::vector<double> _dynamic_array_synapses_26_lastupdate;
std::vector<int32_t> _dynamic_array_synapses_26_N_incoming;
std::vector<int32_t> _dynamic_array_synapses_26_N_outgoing;
std::vector<double> _dynamic_array_synapses_26_R;
std::vector<double> _dynamic_array_synapses_26_wght;
std::vector<int32_t> _dynamic_array_synapses_27__synaptic_post;
std::vector<int32_t> _dynamic_array_synapses_27__synaptic_pre;
std::vector<double> _dynamic_array_synapses_27_delay;
std::vector<double> _dynamic_array_synapses_27_lastupdate;
std::vector<int32_t> _dynamic_array_synapses_27_N_incoming;
std::vector<int32_t> _dynamic_array_synapses_27_N_outgoing;
std::vector<double> _dynamic_array_synapses_27_R;
std::vector<double> _dynamic_array_synapses_27_wght;
std::vector<int32_t> _dynamic_array_synapses_28__synaptic_post;
std::vector<int32_t> _dynamic_array_synapses_28__synaptic_pre;
std::vector<double> _dynamic_array_synapses_28_delay;
std::vector<double> _dynamic_array_synapses_28_lastupdate;
std::vector<int32_t> _dynamic_array_synapses_28_N_incoming;
std::vector<int32_t> _dynamic_array_synapses_28_N_outgoing;
std::vector<double> _dynamic_array_synapses_28_R;
std::vector<double> _dynamic_array_synapses_28_wght;
std::vector<int32_t> _dynamic_array_synapses_29__synaptic_post;
std::vector<int32_t> _dynamic_array_synapses_29__synaptic_pre;
std::vector<double> _dynamic_array_synapses_29_delay;
std::vector<double> _dynamic_array_synapses_29_lastupdate;
std::vector<int32_t> _dynamic_array_synapses_29_N_incoming;
std::vector<int32_t> _dynamic_array_synapses_29_N_outgoing;
std::vector<double> _dynamic_array_synapses_29_R;
std::vector<double> _dynamic_array_synapses_29_wght;
std::vector<int32_t> _dynamic_array_synapses_2__synaptic_post;
std::vector<int32_t> _dynamic_array_synapses_2__synaptic_pre;
std::vector<double> _dynamic_array_synapses_2_delay;
std::vector<double> _dynamic_array_synapses_2_lastupdate;
std::vector<int32_t> _dynamic_array_synapses_2_N_incoming;
std::vector<int32_t> _dynamic_array_synapses_2_N_outgoing;
std::vector<double> _dynamic_array_synapses_2_R;
std::vector<double> _dynamic_array_synapses_2_wght;
std::vector<int32_t> _dynamic_array_synapses_30__synaptic_post;
std::vector<int32_t> _dynamic_array_synapses_30__synaptic_pre;
std::vector<double> _dynamic_array_synapses_30_delay;
std::vector<double> _dynamic_array_synapses_30_lastupdate;
std::vector<int32_t> _dynamic_array_synapses_30_N_incoming;
std::vector<int32_t> _dynamic_array_synapses_30_N_outgoing;
std::vector<double> _dynamic_array_synapses_30_R;
std::vector<double> _dynamic_array_synapses_30_wght;
std::vector<int32_t> _dynamic_array_synapses_31__synaptic_post;
std::vector<int32_t> _dynamic_array_synapses_31__synaptic_pre;
std::vector<double> _dynamic_array_synapses_31_delay;
std::vector<double> _dynamic_array_synapses_31_lastupdate;
std::vector<int32_t> _dynamic_array_synapses_31_N_incoming;
std::vector<int32_t> _dynamic_array_synapses_31_N_outgoing;
std::vector<double> _dynamic_array_synapses_31_R;
std::vector<double> _dynamic_array_synapses_31_wght;
std::vector<int32_t> _dynamic_array_synapses_32__synaptic_post;
std::vector<int32_t> _dynamic_array_synapses_32__synaptic_pre;
std::vector<double> _dynamic_array_synapses_32_delay;
std::vector<double> _dynamic_array_synapses_32_lastupdate;
std::vector<int32_t> _dynamic_array_synapses_32_N_incoming;
std::vector<int32_t> _dynamic_array_synapses_32_N_outgoing;
std::vector<double> _dynamic_array_synapses_32_R;
std::vector<double> _dynamic_array_synapses_32_wght;
std::vector<int32_t> _dynamic_array_synapses_33__synaptic_post;
std::vector<int32_t> _dynamic_array_synapses_33__synaptic_pre;
std::vector<double> _dynamic_array_synapses_33_delay;
std::vector<double> _dynamic_array_synapses_33_lastupdate;
std::vector<int32_t> _dynamic_array_synapses_33_N_incoming;
std::vector<int32_t> _dynamic_array_synapses_33_N_outgoing;
std::vector<double> _dynamic_array_synapses_33_R;
std::vector<double> _dynamic_array_synapses_33_wght;
std::vector<int32_t> _dynamic_array_synapses_34__synaptic_post;
std::vector<int32_t> _dynamic_array_synapses_34__synaptic_pre;
std::vector<double> _dynamic_array_synapses_34_delay;
std::vector<double> _dynamic_array_synapses_34_lastupdate;
std::vector<int32_t> _dynamic_array_synapses_34_N_incoming;
std::vector<int32_t> _dynamic_array_synapses_34_N_outgoing;
std::vector<double> _dynamic_array_synapses_34_R;
std::vector<double> _dynamic_array_synapses_34_wght;
std::vector<int32_t> _dynamic_array_synapses_35__synaptic_post;
std::vector<int32_t> _dynamic_array_synapses_35__synaptic_pre;
std::vector<double> _dynamic_array_synapses_35_delay;
std::vector<double> _dynamic_array_synapses_35_lastupdate;
std::vector<int32_t> _dynamic_array_synapses_35_N_incoming;
std::vector<int32_t> _dynamic_array_synapses_35_N_outgoing;
std::vector<double> _dynamic_array_synapses_35_R;
std::vector<double> _dynamic_array_synapses_35_wght;
std::vector<int32_t> _dynamic_array_synapses_36__synaptic_post;
std::vector<int32_t> _dynamic_array_synapses_36__synaptic_pre;
std::vector<double> _dynamic_array_synapses_36_delay;
std::vector<double> _dynamic_array_synapses_36_lastupdate;
std::vector<int32_t> _dynamic_array_synapses_36_N_incoming;
std::vector<int32_t> _dynamic_array_synapses_36_N_outgoing;
std::vector<double> _dynamic_array_synapses_36_R;
std::vector<double> _dynamic_array_synapses_36_wght;
std::vector<int32_t> _dynamic_array_synapses_37__synaptic_post;
std::vector<int32_t> _dynamic_array_synapses_37__synaptic_pre;
std::vector<double> _dynamic_array_synapses_37_delay;
std::vector<double> _dynamic_array_synapses_37_lastupdate;
std::vector<int32_t> _dynamic_array_synapses_37_N_incoming;
std::vector<int32_t> _dynamic_array_synapses_37_N_outgoing;
std::vector<double> _dynamic_array_synapses_37_R;
std::vector<double> _dynamic_array_synapses_37_wght;
std::vector<int32_t> _dynamic_array_synapses_3__synaptic_post;
std::vector<int32_t> _dynamic_array_synapses_3__synaptic_pre;
std::vector<double> _dynamic_array_synapses_3_delay;
std::vector<double> _dynamic_array_synapses_3_lastupdate;
std::vector<int32_t> _dynamic_array_synapses_3_N_incoming;
std::vector<int32_t> _dynamic_array_synapses_3_N_outgoing;
std::vector<double> _dynamic_array_synapses_3_R;
std::vector<double> _dynamic_array_synapses_3_wght;
std::vector<int32_t> _dynamic_array_synapses_4__synaptic_post;
std::vector<int32_t> _dynamic_array_synapses_4__synaptic_pre;
std::vector<double> _dynamic_array_synapses_4_delay;
std::vector<double> _dynamic_array_synapses_4_lastupdate;
std::vector<int32_t> _dynamic_array_synapses_4_N_incoming;
std::vector<int32_t> _dynamic_array_synapses_4_N_outgoing;
std::vector<double> _dynamic_array_synapses_4_R;
std::vector<double> _dynamic_array_synapses_4_wght;
std::vector<int32_t> _dynamic_array_synapses_5__synaptic_post;
std::vector<int32_t> _dynamic_array_synapses_5__synaptic_pre;
std::vector<double> _dynamic_array_synapses_5_delay;
std::vector<double> _dynamic_array_synapses_5_lastupdate;
std::vector<int32_t> _dynamic_array_synapses_5_N_incoming;
std::vector<int32_t> _dynamic_array_synapses_5_N_outgoing;
std::vector<double> _dynamic_array_synapses_5_R;
std::vector<double> _dynamic_array_synapses_5_wght;
std::vector<int32_t> _dynamic_array_synapses_6__synaptic_post;
std::vector<int32_t> _dynamic_array_synapses_6__synaptic_pre;
std::vector<double> _dynamic_array_synapses_6_delay;
std::vector<double> _dynamic_array_synapses_6_lastupdate;
std::vector<int32_t> _dynamic_array_synapses_6_N_incoming;
std::vector<int32_t> _dynamic_array_synapses_6_N_outgoing;
std::vector<double> _dynamic_array_synapses_6_R;
std::vector<double> _dynamic_array_synapses_6_wght;
std::vector<int32_t> _dynamic_array_synapses_7__synaptic_post;
std::vector<int32_t> _dynamic_array_synapses_7__synaptic_pre;
std::vector<double> _dynamic_array_synapses_7_delay;
std::vector<double> _dynamic_array_synapses_7_lastupdate;
std::vector<int32_t> _dynamic_array_synapses_7_N_incoming;
std::vector<int32_t> _dynamic_array_synapses_7_N_outgoing;
std::vector<double> _dynamic_array_synapses_7_R;
std::vector<double> _dynamic_array_synapses_7_wght;
std::vector<int32_t> _dynamic_array_synapses_8__synaptic_post;
std::vector<int32_t> _dynamic_array_synapses_8__synaptic_pre;
std::vector<double> _dynamic_array_synapses_8_delay;
std::vector<double> _dynamic_array_synapses_8_lastupdate;
std::vector<int32_t> _dynamic_array_synapses_8_N_incoming;
std::vector<int32_t> _dynamic_array_synapses_8_N_outgoing;
std::vector<double> _dynamic_array_synapses_8_R;
std::vector<double> _dynamic_array_synapses_8_wght;
std::vector<int32_t> _dynamic_array_synapses_9__synaptic_post;
std::vector<int32_t> _dynamic_array_synapses_9__synaptic_pre;
std::vector<double> _dynamic_array_synapses_9_delay;
std::vector<double> _dynamic_array_synapses_9_lastupdate;
std::vector<int32_t> _dynamic_array_synapses_9_N_incoming;
std::vector<int32_t> _dynamic_array_synapses_9_N_outgoing;
std::vector<double> _dynamic_array_synapses_9_R;
std::vector<double> _dynamic_array_synapses_9_wght;
std::vector<int32_t> _dynamic_array_synapses__synaptic_post;
std::vector<int32_t> _dynamic_array_synapses__synaptic_pre;
std::vector<double> _dynamic_array_synapses_delay;
std::vector<int32_t> _dynamic_array_synapses_N_incoming;
std::vector<int32_t> _dynamic_array_synapses_N_outgoing;

//////////////// dynamic arrays 2d /////////

/////////////// static arrays /////////////
double * _static_array__array_neurongroup_1_x;
const int _num__static_array__array_neurongroup_1_x = 267;
double * _static_array__array_neurongroup_1_y;
const int _num__static_array__array_neurongroup_1_y = 267;
double * _static_array__array_neurongroup_2_x;
const int _num__static_array__array_neurongroup_2_x = 109;
double * _static_array__array_neurongroup_2_y;
const int _num__static_array__array_neurongroup_2_y = 109;
double * _static_array__array_neurongroup_3_x;
const int _num__static_array__array_neurongroup_3_x = 40;
double * _static_array__array_neurongroup_3_y;
const int _num__static_array__array_neurongroup_3_y = 40;
double * _static_array__array_neurongroup_4_x;
const int _num__static_array__array_neurongroup_4_x = 32;
double * _static_array__array_neurongroup_4_y;
const int _num__static_array__array_neurongroup_4_y = 32;
double * _static_array__array_neurongroup_5_x;
const int _num__static_array__array_neurongroup_5_x = 13;
double * _static_array__array_neurongroup_5_y;
const int _num__static_array__array_neurongroup_5_y = 13;
double * _static_array__array_neurongroup_x;
const int _num__static_array__array_neurongroup_x = 60;
double * _static_array__array_neurongroup_y;
const int _num__static_array__array_neurongroup_y = 60;
int32_t * _static_array__array_synapses_10_sources;
const int _num__static_array__array_synapses_10_sources = 990;
int32_t * _static_array__array_synapses_10_targets;
const int _num__static_array__array_synapses_10_targets = 990;
int32_t * _static_array__array_synapses_11_sources;
const int _num__static_array__array_synapses_11_sources = 357;
int32_t * _static_array__array_synapses_11_targets;
const int _num__static_array__array_synapses_11_targets = 357;
int32_t * _static_array__array_synapses_12_sources;
const int _num__static_array__array_synapses_12_sources = 28;
int32_t * _static_array__array_synapses_12_targets;
const int _num__static_array__array_synapses_12_targets = 28;
int32_t * _static_array__array_synapses_13_sources;
const int _num__static_array__array_synapses_13_sources = 45;
int32_t * _static_array__array_synapses_13_targets;
const int _num__static_array__array_synapses_13_targets = 45;
int32_t * _static_array__array_synapses_14_sources;
const int _num__static_array__array_synapses_14_sources = 492;
int32_t * _static_array__array_synapses_14_targets;
const int _num__static_array__array_synapses_14_targets = 492;
int32_t * _static_array__array_synapses_15_sources;
const int _num__static_array__array_synapses_15_sources = 300;
int32_t * _static_array__array_synapses_15_targets;
const int _num__static_array__array_synapses_15_targets = 300;
int32_t * _static_array__array_synapses_16_sources;
const int _num__static_array__array_synapses_16_sources = 154;
int32_t * _static_array__array_synapses_16_targets;
const int _num__static_array__array_synapses_16_targets = 154;
int32_t * _static_array__array_synapses_17_sources;
const int _num__static_array__array_synapses_17_sources = 370;
int32_t * _static_array__array_synapses_17_targets;
const int _num__static_array__array_synapses_17_targets = 370;
int32_t * _static_array__array_synapses_18_sources;
const int _num__static_array__array_synapses_18_sources = 252;
int32_t * _static_array__array_synapses_18_targets;
const int _num__static_array__array_synapses_18_targets = 252;
int32_t * _static_array__array_synapses_19_sources;
const int _num__static_array__array_synapses_19_sources = 2097;
int32_t * _static_array__array_synapses_19_targets;
const int _num__static_array__array_synapses_19_targets = 2097;
int32_t * _static_array__array_synapses_1_sources;
const int _num__static_array__array_synapses_1_sources = 4803;
int32_t * _static_array__array_synapses_1_targets;
const int _num__static_array__array_synapses_1_targets = 4803;
int32_t * _static_array__array_synapses_20_sources;
const int _num__static_array__array_synapses_20_sources = 2142;
int32_t * _static_array__array_synapses_20_targets;
const int _num__static_array__array_synapses_20_targets = 2142;
int32_t * _static_array__array_synapses_21_sources;
const int _num__static_array__array_synapses_21_sources = 762;
int32_t * _static_array__array_synapses_21_targets;
const int _num__static_array__array_synapses_21_targets = 762;
int32_t * _static_array__array_synapses_22_sources;
const int _num__static_array__array_synapses_22_sources = 747;
int32_t * _static_array__array_synapses_22_targets;
const int _num__static_array__array_synapses_22_targets = 747;
int32_t * _static_array__array_synapses_23_sources;
const int _num__static_array__array_synapses_23_sources = 642;
int32_t * _static_array__array_synapses_23_targets;
const int _num__static_array__array_synapses_23_targets = 642;
int32_t * _static_array__array_synapses_24_sources;
const int _num__static_array__array_synapses_24_sources = 140;
int32_t * _static_array__array_synapses_24_targets;
const int _num__static_array__array_synapses_24_targets = 140;
int32_t * _static_array__array_synapses_25_sources;
const int _num__static_array__array_synapses_25_sources = 112;
int32_t * _static_array__array_synapses_25_targets;
const int _num__static_array__array_synapses_25_targets = 112;
int32_t * _static_array__array_synapses_26_sources;
const int _num__static_array__array_synapses_26_sources = 512;
int32_t * _static_array__array_synapses_26_targets;
const int _num__static_array__array_synapses_26_targets = 512;
int32_t * _static_array__array_synapses_27_sources;
const int _num__static_array__array_synapses_27_sources = 510;
int32_t * _static_array__array_synapses_27_targets;
const int _num__static_array__array_synapses_27_targets = 510;
int32_t * _static_array__array_synapses_28_sources;
const int _num__static_array__array_synapses_28_sources = 204;
int32_t * _static_array__array_synapses_28_targets;
const int _num__static_array__array_synapses_28_targets = 204;
int32_t * _static_array__array_synapses_29_sources;
const int _num__static_array__array_synapses_29_sources = 234;
int32_t * _static_array__array_synapses_29_targets;
const int _num__static_array__array_synapses_29_targets = 234;
int32_t * _static_array__array_synapses_2_sources;
const int _num__static_array__array_synapses_2_sources = 6336;
int32_t * _static_array__array_synapses_2_targets;
const int _num__static_array__array_synapses_2_targets = 6336;
int32_t * _static_array__array_synapses_30_sources;
const int _num__static_array__array_synapses_30_sources = 168;
int32_t * _static_array__array_synapses_30_targets;
const int _num__static_array__array_synapses_30_targets = 168;
int32_t * _static_array__array_synapses_31_sources;
const int _num__static_array__array_synapses_31_sources = 21;
int32_t * _static_array__array_synapses_31_targets;
const int _num__static_array__array_synapses_31_targets = 21;
int32_t * _static_array__array_synapses_32_sources;
const int _num__static_array__array_synapses_32_sources = 27;
int32_t * _static_array__array_synapses_32_targets;
const int _num__static_array__array_synapses_32_targets = 27;
int32_t * _static_array__array_synapses_33_sources;
const int _num__static_array__array_synapses_33_sources = 333;
int32_t * _static_array__array_synapses_33_targets;
const int _num__static_array__array_synapses_33_targets = 333;
int32_t * _static_array__array_synapses_34_sources;
const int _num__static_array__array_synapses_34_sources = 333;
int32_t * _static_array__array_synapses_34_targets;
const int _num__static_array__array_synapses_34_targets = 333;
int32_t * _static_array__array_synapses_35_sources;
const int _num__static_array__array_synapses_35_sources = 105;
int32_t * _static_array__array_synapses_35_targets;
const int _num__static_array__array_synapses_35_targets = 105;
int32_t * _static_array__array_synapses_36_sources;
const int _num__static_array__array_synapses_36_sources = 78;
int32_t * _static_array__array_synapses_36_targets;
const int _num__static_array__array_synapses_36_targets = 78;
int32_t * _static_array__array_synapses_37_sources;
const int _num__static_array__array_synapses_37_sources = 66;
int32_t * _static_array__array_synapses_37_targets;
const int _num__static_array__array_synapses_37_targets = 66;
int32_t * _static_array__array_synapses_3_sources;
const int _num__static_array__array_synapses_3_sources = 1938;
int32_t * _static_array__array_synapses_3_targets;
const int _num__static_array__array_synapses_3_targets = 1938;
int32_t * _static_array__array_synapses_4_sources;
const int _num__static_array__array_synapses_4_sources = 2588;
int32_t * _static_array__array_synapses_4_targets;
const int _num__static_array__array_synapses_4_targets = 2588;
int32_t * _static_array__array_synapses_5_sources;
const int _num__static_array__array_synapses_5_sources = 11697;
int32_t * _static_array__array_synapses_5_targets;
const int _num__static_array__array_synapses_5_targets = 11697;
int32_t * _static_array__array_synapses_6_sources;
const int _num__static_array__array_synapses_6_sources = 1384;
int32_t * _static_array__array_synapses_6_targets;
const int _num__static_array__array_synapses_6_targets = 1384;
int32_t * _static_array__array_synapses_7_sources;
const int _num__static_array__array_synapses_7_sources = 224;
int32_t * _static_array__array_synapses_7_targets;
const int _num__static_array__array_synapses_7_targets = 224;
int32_t * _static_array__array_synapses_8_sources;
const int _num__static_array__array_synapses_8_sources = 108;
int32_t * _static_array__array_synapses_8_targets;
const int _num__static_array__array_synapses_8_targets = 108;
int32_t * _static_array__array_synapses_9_sources;
const int _num__static_array__array_synapses_9_sources = 1854;
int32_t * _static_array__array_synapses_9_targets;
const int _num__static_array__array_synapses_9_targets = 1854;
int32_t * _static_array__dynamic_array_spikegeneratorgroup__timebins;
const int _num__static_array__dynamic_array_spikegeneratorgroup__timebins = 60;
int32_t * _static_array__dynamic_array_spikegeneratorgroup_neuron_index;
const int _num__static_array__dynamic_array_spikegeneratorgroup_neuron_index = 60;
int32_t * _static_array__dynamic_array_spikegeneratorgroup_spike_number;
const int _num__static_array__dynamic_array_spikegeneratorgroup_spike_number = 60;
double * _static_array__dynamic_array_spikegeneratorgroup_spike_time;
const int _num__static_array__dynamic_array_spikegeneratorgroup_spike_time = 60;

//////////////// synapses /////////////////
// synapses
SynapticPathway synapses_pre(
		_dynamic_array_synapses__synaptic_pre,
		0, 60);
// synapses_1
SynapticPathway synapses_1_pre(
		_dynamic_array_synapses_1__synaptic_pre,
		0, 60);
// synapses_10
SynapticPathway synapses_10_pre(
		_dynamic_array_synapses_10__synaptic_pre,
		0, 32);
// synapses_11
SynapticPathway synapses_11_pre(
		_dynamic_array_synapses_11__synaptic_pre,
		0, 32);
// synapses_12
SynapticPathway synapses_12_pre(
		_dynamic_array_synapses_12__synaptic_pre,
		0, 13);
// synapses_13
SynapticPathway synapses_13_pre(
		_dynamic_array_synapses_13__synaptic_pre,
		0, 13);
// synapses_14
SynapticPathway synapses_14_pre(
		_dynamic_array_synapses_14__synaptic_pre,
		0, 13);
// synapses_15
SynapticPathway synapses_15_pre(
		_dynamic_array_synapses_15__synaptic_pre,
		0, 13);
// synapses_16
SynapticPathway synapses_16_pre(
		_dynamic_array_synapses_16__synaptic_pre,
		0, 13);
// synapses_17
SynapticPathway synapses_17_pre(
		_dynamic_array_synapses_17__synaptic_pre,
		0, 267);
// synapses_18
SynapticPathway synapses_18_pre(
		_dynamic_array_synapses_18__synaptic_pre,
		0, 267);
// synapses_19
SynapticPathway synapses_19_pre(
		_dynamic_array_synapses_19__synaptic_pre,
		0, 267);
// synapses_2
SynapticPathway synapses_2_pre(
		_dynamic_array_synapses_2__synaptic_pre,
		0, 60);
// synapses_20
SynapticPathway synapses_20_pre(
		_dynamic_array_synapses_20__synaptic_pre,
		0, 267);
// synapses_21
SynapticPathway synapses_21_pre(
		_dynamic_array_synapses_21__synaptic_pre,
		0, 267);
// synapses_22
SynapticPathway synapses_22_pre(
		_dynamic_array_synapses_22__synaptic_pre,
		0, 267);
// synapses_23
SynapticPathway synapses_23_pre(
		_dynamic_array_synapses_23__synaptic_pre,
		0, 267);
// synapses_24
SynapticPathway synapses_24_pre(
		_dynamic_array_synapses_24__synaptic_pre,
		0, 109);
// synapses_25
SynapticPathway synapses_25_pre(
		_dynamic_array_synapses_25__synaptic_pre,
		0, 109);
// synapses_26
SynapticPathway synapses_26_pre(
		_dynamic_array_synapses_26__synaptic_pre,
		0, 109);
// synapses_27
SynapticPathway synapses_27_pre(
		_dynamic_array_synapses_27__synaptic_pre,
		0, 109);
// synapses_28
SynapticPathway synapses_28_pre(
		_dynamic_array_synapses_28__synaptic_pre,
		0, 109);
// synapses_29
SynapticPathway synapses_29_pre(
		_dynamic_array_synapses_29__synaptic_pre,
		0, 109);
// synapses_3
SynapticPathway synapses_3_pre(
		_dynamic_array_synapses_3__synaptic_pre,
		0, 60);
// synapses_30
SynapticPathway synapses_30_pre(
		_dynamic_array_synapses_30__synaptic_pre,
		0, 109);
// synapses_31
SynapticPathway synapses_31_pre(
		_dynamic_array_synapses_31__synaptic_pre,
		0, 40);
// synapses_32
SynapticPathway synapses_32_pre(
		_dynamic_array_synapses_32__synaptic_pre,
		0, 40);
// synapses_33
SynapticPathway synapses_33_pre(
		_dynamic_array_synapses_33__synaptic_pre,
		0, 40);
// synapses_34
SynapticPathway synapses_34_pre(
		_dynamic_array_synapses_34__synaptic_pre,
		0, 40);
// synapses_35
SynapticPathway synapses_35_pre(
		_dynamic_array_synapses_35__synaptic_pre,
		0, 40);
// synapses_36
SynapticPathway synapses_36_pre(
		_dynamic_array_synapses_36__synaptic_pre,
		0, 40);
// synapses_37
SynapticPathway synapses_37_pre(
		_dynamic_array_synapses_37__synaptic_pre,
		0, 40);
// synapses_4
SynapticPathway synapses_4_pre(
		_dynamic_array_synapses_4__synaptic_pre,
		0, 60);
// synapses_5
SynapticPathway synapses_5_pre(
		_dynamic_array_synapses_5__synaptic_pre,
		0, 60);
// synapses_6
SynapticPathway synapses_6_pre(
		_dynamic_array_synapses_6__synaptic_pre,
		0, 60);
// synapses_7
SynapticPathway synapses_7_pre(
		_dynamic_array_synapses_7__synaptic_pre,
		0, 32);
// synapses_8
SynapticPathway synapses_8_pre(
		_dynamic_array_synapses_8__synaptic_pre,
		0, 32);
// synapses_9
SynapticPathway synapses_9_pre(
		_dynamic_array_synapses_9__synaptic_pre,
		0, 32);

//////////////// clocks ///////////////////
Clock defaultclock;  // attributes will be set in run.cpp

// Profiling information for each code object
double neurongroup_1_resetter_codeobject_profiling_info = 0.0;
double neurongroup_1_stateupdater_codeobject_profiling_info = 0.0;
double neurongroup_1_thresholder_codeobject_profiling_info = 0.0;
double neurongroup_2_resetter_codeobject_profiling_info = 0.0;
double neurongroup_2_stateupdater_codeobject_profiling_info = 0.0;
double neurongroup_2_thresholder_codeobject_profiling_info = 0.0;
double neurongroup_3_resetter_codeobject_profiling_info = 0.0;
double neurongroup_3_stateupdater_codeobject_profiling_info = 0.0;
double neurongroup_3_thresholder_codeobject_profiling_info = 0.0;
double neurongroup_4_resetter_codeobject_profiling_info = 0.0;
double neurongroup_4_stateupdater_codeobject_profiling_info = 0.0;
double neurongroup_4_thresholder_codeobject_profiling_info = 0.0;
double neurongroup_5_resetter_codeobject_profiling_info = 0.0;
double neurongroup_5_stateupdater_codeobject_profiling_info = 0.0;
double neurongroup_5_thresholder_codeobject_profiling_info = 0.0;
double neurongroup_resetter_codeobject_profiling_info = 0.0;
double neurongroup_thresholder_codeobject_profiling_info = 0.0;
double poissoninput_10_codeobject_profiling_info = 0.0;
double poissoninput_11_codeobject_profiling_info = 0.0;
double poissoninput_12_codeobject_profiling_info = 0.0;
double poissoninput_13_codeobject_profiling_info = 0.0;
double poissoninput_14_codeobject_profiling_info = 0.0;
double poissoninput_15_codeobject_profiling_info = 0.0;
double poissoninput_1_codeobject_profiling_info = 0.0;
double poissoninput_2_codeobject_profiling_info = 0.0;
double poissoninput_3_codeobject_profiling_info = 0.0;
double poissoninput_4_codeobject_profiling_info = 0.0;
double poissoninput_5_codeobject_profiling_info = 0.0;
double poissoninput_6_codeobject_profiling_info = 0.0;
double poissoninput_7_codeobject_profiling_info = 0.0;
double poissoninput_8_codeobject_profiling_info = 0.0;
double poissoninput_9_codeobject_profiling_info = 0.0;
double poissoninput_codeobject_profiling_info = 0.0;
double spikegeneratorgroup_codeobject_profiling_info = 0.0;
double spikemonitor_1_codeobject_profiling_info = 0.0;
double spikemonitor_2_codeobject_profiling_info = 0.0;
double spikemonitor_3_codeobject_profiling_info = 0.0;
double spikemonitor_4_codeobject_profiling_info = 0.0;
double spikemonitor_5_codeobject_profiling_info = 0.0;
double spikemonitor_codeobject_profiling_info = 0.0;
double synapses_10_pre_codeobject_profiling_info = 0.0;
double synapses_10_pre_initialise_queue_profiling_info = 0.0;
double synapses_10_pre_push_spikes_profiling_info = 0.0;
double synapses_11_pre_codeobject_profiling_info = 0.0;
double synapses_11_pre_initialise_queue_profiling_info = 0.0;
double synapses_11_pre_push_spikes_profiling_info = 0.0;
double synapses_12_pre_codeobject_profiling_info = 0.0;
double synapses_12_pre_initialise_queue_profiling_info = 0.0;
double synapses_12_pre_push_spikes_profiling_info = 0.0;
double synapses_13_pre_codeobject_profiling_info = 0.0;
double synapses_13_pre_initialise_queue_profiling_info = 0.0;
double synapses_13_pre_push_spikes_profiling_info = 0.0;
double synapses_14_pre_codeobject_profiling_info = 0.0;
double synapses_14_pre_initialise_queue_profiling_info = 0.0;
double synapses_14_pre_push_spikes_profiling_info = 0.0;
double synapses_15_pre_codeobject_profiling_info = 0.0;
double synapses_15_pre_initialise_queue_profiling_info = 0.0;
double synapses_15_pre_push_spikes_profiling_info = 0.0;
double synapses_16_pre_codeobject_profiling_info = 0.0;
double synapses_16_pre_initialise_queue_profiling_info = 0.0;
double synapses_16_pre_push_spikes_profiling_info = 0.0;
double synapses_17_pre_codeobject_profiling_info = 0.0;
double synapses_17_pre_initialise_queue_profiling_info = 0.0;
double synapses_17_pre_push_spikes_profiling_info = 0.0;
double synapses_18_pre_codeobject_profiling_info = 0.0;
double synapses_18_pre_initialise_queue_profiling_info = 0.0;
double synapses_18_pre_push_spikes_profiling_info = 0.0;
double synapses_19_pre_codeobject_profiling_info = 0.0;
double synapses_19_pre_initialise_queue_profiling_info = 0.0;
double synapses_19_pre_push_spikes_profiling_info = 0.0;
double synapses_1_pre_codeobject_profiling_info = 0.0;
double synapses_1_pre_initialise_queue_profiling_info = 0.0;
double synapses_1_pre_push_spikes_profiling_info = 0.0;
double synapses_20_pre_codeobject_profiling_info = 0.0;
double synapses_20_pre_initialise_queue_profiling_info = 0.0;
double synapses_20_pre_push_spikes_profiling_info = 0.0;
double synapses_21_pre_codeobject_profiling_info = 0.0;
double synapses_21_pre_initialise_queue_profiling_info = 0.0;
double synapses_21_pre_push_spikes_profiling_info = 0.0;
double synapses_22_pre_codeobject_profiling_info = 0.0;
double synapses_22_pre_initialise_queue_profiling_info = 0.0;
double synapses_22_pre_push_spikes_profiling_info = 0.0;
double synapses_23_pre_codeobject_profiling_info = 0.0;
double synapses_23_pre_initialise_queue_profiling_info = 0.0;
double synapses_23_pre_push_spikes_profiling_info = 0.0;
double synapses_24_pre_codeobject_profiling_info = 0.0;
double synapses_24_pre_initialise_queue_profiling_info = 0.0;
double synapses_24_pre_push_spikes_profiling_info = 0.0;
double synapses_25_pre_codeobject_profiling_info = 0.0;
double synapses_25_pre_initialise_queue_profiling_info = 0.0;
double synapses_25_pre_push_spikes_profiling_info = 0.0;
double synapses_26_pre_codeobject_profiling_info = 0.0;
double synapses_26_pre_initialise_queue_profiling_info = 0.0;
double synapses_26_pre_push_spikes_profiling_info = 0.0;
double synapses_27_pre_codeobject_profiling_info = 0.0;
double synapses_27_pre_initialise_queue_profiling_info = 0.0;
double synapses_27_pre_push_spikes_profiling_info = 0.0;
double synapses_28_pre_codeobject_profiling_info = 0.0;
double synapses_28_pre_initialise_queue_profiling_info = 0.0;
double synapses_28_pre_push_spikes_profiling_info = 0.0;
double synapses_29_pre_codeobject_profiling_info = 0.0;
double synapses_29_pre_initialise_queue_profiling_info = 0.0;
double synapses_29_pre_push_spikes_profiling_info = 0.0;
double synapses_2_pre_codeobject_profiling_info = 0.0;
double synapses_2_pre_initialise_queue_profiling_info = 0.0;
double synapses_2_pre_push_spikes_profiling_info = 0.0;
double synapses_30_pre_codeobject_profiling_info = 0.0;
double synapses_30_pre_initialise_queue_profiling_info = 0.0;
double synapses_30_pre_push_spikes_profiling_info = 0.0;
double synapses_31_pre_codeobject_profiling_info = 0.0;
double synapses_31_pre_initialise_queue_profiling_info = 0.0;
double synapses_31_pre_push_spikes_profiling_info = 0.0;
double synapses_32_pre_codeobject_profiling_info = 0.0;
double synapses_32_pre_initialise_queue_profiling_info = 0.0;
double synapses_32_pre_push_spikes_profiling_info = 0.0;
double synapses_33_pre_codeobject_profiling_info = 0.0;
double synapses_33_pre_initialise_queue_profiling_info = 0.0;
double synapses_33_pre_push_spikes_profiling_info = 0.0;
double synapses_34_pre_codeobject_profiling_info = 0.0;
double synapses_34_pre_initialise_queue_profiling_info = 0.0;
double synapses_34_pre_push_spikes_profiling_info = 0.0;
double synapses_35_pre_codeobject_profiling_info = 0.0;
double synapses_35_pre_initialise_queue_profiling_info = 0.0;
double synapses_35_pre_push_spikes_profiling_info = 0.0;
double synapses_36_pre_codeobject_profiling_info = 0.0;
double synapses_36_pre_initialise_queue_profiling_info = 0.0;
double synapses_36_pre_push_spikes_profiling_info = 0.0;
double synapses_37_pre_codeobject_profiling_info = 0.0;
double synapses_37_pre_initialise_queue_profiling_info = 0.0;
double synapses_37_pre_push_spikes_profiling_info = 0.0;
double synapses_3_pre_codeobject_profiling_info = 0.0;
double synapses_3_pre_initialise_queue_profiling_info = 0.0;
double synapses_3_pre_push_spikes_profiling_info = 0.0;
double synapses_4_pre_codeobject_profiling_info = 0.0;
double synapses_4_pre_initialise_queue_profiling_info = 0.0;
double synapses_4_pre_push_spikes_profiling_info = 0.0;
double synapses_5_pre_codeobject_profiling_info = 0.0;
double synapses_5_pre_initialise_queue_profiling_info = 0.0;
double synapses_5_pre_push_spikes_profiling_info = 0.0;
double synapses_6_pre_codeobject_profiling_info = 0.0;
double synapses_6_pre_initialise_queue_profiling_info = 0.0;
double synapses_6_pre_push_spikes_profiling_info = 0.0;
double synapses_7_pre_codeobject_profiling_info = 0.0;
double synapses_7_pre_initialise_queue_profiling_info = 0.0;
double synapses_7_pre_push_spikes_profiling_info = 0.0;
double synapses_8_pre_codeobject_profiling_info = 0.0;
double synapses_8_pre_initialise_queue_profiling_info = 0.0;
double synapses_8_pre_push_spikes_profiling_info = 0.0;
double synapses_9_pre_codeobject_profiling_info = 0.0;
double synapses_9_pre_initialise_queue_profiling_info = 0.0;
double synapses_9_pre_push_spikes_profiling_info = 0.0;
double synapses_pre_codeobject_profiling_info = 0.0;
double synapses_pre_initialise_queue_profiling_info = 0.0;
double synapses_pre_push_spikes_profiling_info = 0.0;
}

void _init_arrays()
{
	using namespace brian;

    // Arrays initialized to 0
	_array_defaultclock_dt = new double[1];
    
	for(int i=0; i<1; i++) _array_defaultclock_dt[i] = 0;

	_array_defaultclock_t = new double[1];
    
	for(int i=0; i<1; i++) _array_defaultclock_t[i] = 0;

	_array_defaultclock_timestep = new int64_t[1];
    
	for(int i=0; i<1; i++) _array_defaultclock_timestep[i] = 0;

	_array_neurongroup_1__spikespace = new int32_t[268];
    
	for(int i=0; i<268; i++) _array_neurongroup_1__spikespace[i] = 0;

	_array_neurongroup_1_ge_a0 = new double[267];
    
	for(int i=0; i<267; i++) _array_neurongroup_1_ge_a0[i] = 0;

	_array_neurongroup_1_ge_a1 = new double[267];
    
	for(int i=0; i<267; i++) _array_neurongroup_1_ge_a1[i] = 0;

	_array_neurongroup_1_ge_a2 = new double[267];
    
	for(int i=0; i<267; i++) _array_neurongroup_1_ge_a2[i] = 0;

	_array_neurongroup_1_ge_basal = new double[267];
    
	for(int i=0; i<267; i++) _array_neurongroup_1_ge_basal[i] = 0;

	_array_neurongroup_1_ge_soma = new double[267];
    
	for(int i=0; i<267; i++) _array_neurongroup_1_ge_soma[i] = 0;

	_array_neurongroup_1_gealpha_a0 = new double[267];
    
	for(int i=0; i<267; i++) _array_neurongroup_1_gealpha_a0[i] = 0;

	_array_neurongroup_1_gealpha_a1 = new double[267];
    
	for(int i=0; i<267; i++) _array_neurongroup_1_gealpha_a1[i] = 0;

	_array_neurongroup_1_gealpha_a2 = new double[267];
    
	for(int i=0; i<267; i++) _array_neurongroup_1_gealpha_a2[i] = 0;

	_array_neurongroup_1_gealpha_basal = new double[267];
    
	for(int i=0; i<267; i++) _array_neurongroup_1_gealpha_basal[i] = 0;

	_array_neurongroup_1_gealpha_soma = new double[267];
    
	for(int i=0; i<267; i++) _array_neurongroup_1_gealpha_soma[i] = 0;

	_array_neurongroup_1_gi_a0 = new double[267];
    
	for(int i=0; i<267; i++) _array_neurongroup_1_gi_a0[i] = 0;

	_array_neurongroup_1_gi_a1 = new double[267];
    
	for(int i=0; i<267; i++) _array_neurongroup_1_gi_a1[i] = 0;

	_array_neurongroup_1_gi_a2 = new double[267];
    
	for(int i=0; i<267; i++) _array_neurongroup_1_gi_a2[i] = 0;

	_array_neurongroup_1_gi_basal = new double[267];
    
	for(int i=0; i<267; i++) _array_neurongroup_1_gi_basal[i] = 0;

	_array_neurongroup_1_gi_soma = new double[267];
    
	for(int i=0; i<267; i++) _array_neurongroup_1_gi_soma[i] = 0;

	_array_neurongroup_1_gialpha_a0 = new double[267];
    
	for(int i=0; i<267; i++) _array_neurongroup_1_gialpha_a0[i] = 0;

	_array_neurongroup_1_gialpha_a1 = new double[267];
    
	for(int i=0; i<267; i++) _array_neurongroup_1_gialpha_a1[i] = 0;

	_array_neurongroup_1_gialpha_a2 = new double[267];
    
	for(int i=0; i<267; i++) _array_neurongroup_1_gialpha_a2[i] = 0;

	_array_neurongroup_1_gialpha_basal = new double[267];
    
	for(int i=0; i<267; i++) _array_neurongroup_1_gialpha_basal[i] = 0;

	_array_neurongroup_1_gialpha_soma = new double[267];
    
	for(int i=0; i<267; i++) _array_neurongroup_1_gialpha_soma[i] = 0;

	_array_neurongroup_1_i = new int32_t[267];
    
	for(int i=0; i<267; i++) _array_neurongroup_1_i[i] = 0;

	_array_neurongroup_1_lastspike = new double[267];
    
	for(int i=0; i<267; i++) _array_neurongroup_1_lastspike[i] = 0;

	_array_neurongroup_1_not_refractory = new char[267];
    
	for(int i=0; i<267; i++) _array_neurongroup_1_not_refractory[i] = 0;

	_array_neurongroup_1_vm = new double[267];
    
	for(int i=0; i<267; i++) _array_neurongroup_1_vm[i] = 0;

	_array_neurongroup_1_vm_a0 = new double[267];
    
	for(int i=0; i<267; i++) _array_neurongroup_1_vm_a0[i] = 0;

	_array_neurongroup_1_vm_a1 = new double[267];
    
	for(int i=0; i<267; i++) _array_neurongroup_1_vm_a1[i] = 0;

	_array_neurongroup_1_vm_a2 = new double[267];
    
	for(int i=0; i<267; i++) _array_neurongroup_1_vm_a2[i] = 0;

	_array_neurongroup_1_vm_basal = new double[267];
    
	for(int i=0; i<267; i++) _array_neurongroup_1_vm_basal[i] = 0;

	_array_neurongroup_1_x = new double[267];
    
	for(int i=0; i<267; i++) _array_neurongroup_1_x[i] = 0;

	_array_neurongroup_1_y = new double[267];
    
	for(int i=0; i<267; i++) _array_neurongroup_1_y[i] = 0;

	_array_neurongroup_2__spikespace = new int32_t[110];
    
	for(int i=0; i<110; i++) _array_neurongroup_2__spikespace[i] = 0;

	_array_neurongroup_2_ge_a0 = new double[109];
    
	for(int i=0; i<109; i++) _array_neurongroup_2_ge_a0[i] = 0;

	_array_neurongroup_2_ge_a1 = new double[109];
    
	for(int i=0; i<109; i++) _array_neurongroup_2_ge_a1[i] = 0;

	_array_neurongroup_2_ge_a2 = new double[109];
    
	for(int i=0; i<109; i++) _array_neurongroup_2_ge_a2[i] = 0;

	_array_neurongroup_2_ge_basal = new double[109];
    
	for(int i=0; i<109; i++) _array_neurongroup_2_ge_basal[i] = 0;

	_array_neurongroup_2_ge_soma = new double[109];
    
	for(int i=0; i<109; i++) _array_neurongroup_2_ge_soma[i] = 0;

	_array_neurongroup_2_gealpha_a0 = new double[109];
    
	for(int i=0; i<109; i++) _array_neurongroup_2_gealpha_a0[i] = 0;

	_array_neurongroup_2_gealpha_a1 = new double[109];
    
	for(int i=0; i<109; i++) _array_neurongroup_2_gealpha_a1[i] = 0;

	_array_neurongroup_2_gealpha_a2 = new double[109];
    
	for(int i=0; i<109; i++) _array_neurongroup_2_gealpha_a2[i] = 0;

	_array_neurongroup_2_gealpha_basal = new double[109];
    
	for(int i=0; i<109; i++) _array_neurongroup_2_gealpha_basal[i] = 0;

	_array_neurongroup_2_gealpha_soma = new double[109];
    
	for(int i=0; i<109; i++) _array_neurongroup_2_gealpha_soma[i] = 0;

	_array_neurongroup_2_gi_a0 = new double[109];
    
	for(int i=0; i<109; i++) _array_neurongroup_2_gi_a0[i] = 0;

	_array_neurongroup_2_gi_a1 = new double[109];
    
	for(int i=0; i<109; i++) _array_neurongroup_2_gi_a1[i] = 0;

	_array_neurongroup_2_gi_a2 = new double[109];
    
	for(int i=0; i<109; i++) _array_neurongroup_2_gi_a2[i] = 0;

	_array_neurongroup_2_gi_basal = new double[109];
    
	for(int i=0; i<109; i++) _array_neurongroup_2_gi_basal[i] = 0;

	_array_neurongroup_2_gi_soma = new double[109];
    
	for(int i=0; i<109; i++) _array_neurongroup_2_gi_soma[i] = 0;

	_array_neurongroup_2_gialpha_a0 = new double[109];
    
	for(int i=0; i<109; i++) _array_neurongroup_2_gialpha_a0[i] = 0;

	_array_neurongroup_2_gialpha_a1 = new double[109];
    
	for(int i=0; i<109; i++) _array_neurongroup_2_gialpha_a1[i] = 0;

	_array_neurongroup_2_gialpha_a2 = new double[109];
    
	for(int i=0; i<109; i++) _array_neurongroup_2_gialpha_a2[i] = 0;

	_array_neurongroup_2_gialpha_basal = new double[109];
    
	for(int i=0; i<109; i++) _array_neurongroup_2_gialpha_basal[i] = 0;

	_array_neurongroup_2_gialpha_soma = new double[109];
    
	for(int i=0; i<109; i++) _array_neurongroup_2_gialpha_soma[i] = 0;

	_array_neurongroup_2_i = new int32_t[109];
    
	for(int i=0; i<109; i++) _array_neurongroup_2_i[i] = 0;

	_array_neurongroup_2_lastspike = new double[109];
    
	for(int i=0; i<109; i++) _array_neurongroup_2_lastspike[i] = 0;

	_array_neurongroup_2_not_refractory = new char[109];
    
	for(int i=0; i<109; i++) _array_neurongroup_2_not_refractory[i] = 0;

	_array_neurongroup_2_vm = new double[109];
    
	for(int i=0; i<109; i++) _array_neurongroup_2_vm[i] = 0;

	_array_neurongroup_2_vm_a0 = new double[109];
    
	for(int i=0; i<109; i++) _array_neurongroup_2_vm_a0[i] = 0;

	_array_neurongroup_2_vm_a1 = new double[109];
    
	for(int i=0; i<109; i++) _array_neurongroup_2_vm_a1[i] = 0;

	_array_neurongroup_2_vm_a2 = new double[109];
    
	for(int i=0; i<109; i++) _array_neurongroup_2_vm_a2[i] = 0;

	_array_neurongroup_2_vm_basal = new double[109];
    
	for(int i=0; i<109; i++) _array_neurongroup_2_vm_basal[i] = 0;

	_array_neurongroup_2_x = new double[109];
    
	for(int i=0; i<109; i++) _array_neurongroup_2_x[i] = 0;

	_array_neurongroup_2_y = new double[109];
    
	for(int i=0; i<109; i++) _array_neurongroup_2_y[i] = 0;

	_array_neurongroup_3__spikespace = new int32_t[41];
    
	for(int i=0; i<41; i++) _array_neurongroup_3__spikespace[i] = 0;

	_array_neurongroup_3_ge_soma = new double[40];
    
	for(int i=0; i<40; i++) _array_neurongroup_3_ge_soma[i] = 0;

	_array_neurongroup_3_gi_soma = new double[40];
    
	for(int i=0; i<40; i++) _array_neurongroup_3_gi_soma[i] = 0;

	_array_neurongroup_3_i = new int32_t[40];
    
	for(int i=0; i<40; i++) _array_neurongroup_3_i[i] = 0;

	_array_neurongroup_3_lastspike = new double[40];
    
	for(int i=0; i<40; i++) _array_neurongroup_3_lastspike[i] = 0;

	_array_neurongroup_3_not_refractory = new char[40];
    
	for(int i=0; i<40; i++) _array_neurongroup_3_not_refractory[i] = 0;

	_array_neurongroup_3_vm = new double[40];
    
	for(int i=0; i<40; i++) _array_neurongroup_3_vm[i] = 0;

	_array_neurongroup_3_x = new double[40];
    
	for(int i=0; i<40; i++) _array_neurongroup_3_x[i] = 0;

	_array_neurongroup_3_y = new double[40];
    
	for(int i=0; i<40; i++) _array_neurongroup_3_y[i] = 0;

	_array_neurongroup_4__spikespace = new int32_t[33];
    
	for(int i=0; i<33; i++) _array_neurongroup_4__spikespace[i] = 0;

	_array_neurongroup_4_ge_soma = new double[32];
    
	for(int i=0; i<32; i++) _array_neurongroup_4_ge_soma[i] = 0;

	_array_neurongroup_4_gi_soma = new double[32];
    
	for(int i=0; i<32; i++) _array_neurongroup_4_gi_soma[i] = 0;

	_array_neurongroup_4_i = new int32_t[32];
    
	for(int i=0; i<32; i++) _array_neurongroup_4_i[i] = 0;

	_array_neurongroup_4_lastspike = new double[32];
    
	for(int i=0; i<32; i++) _array_neurongroup_4_lastspike[i] = 0;

	_array_neurongroup_4_not_refractory = new char[32];
    
	for(int i=0; i<32; i++) _array_neurongroup_4_not_refractory[i] = 0;

	_array_neurongroup_4_vm = new double[32];
    
	for(int i=0; i<32; i++) _array_neurongroup_4_vm[i] = 0;

	_array_neurongroup_4_x = new double[32];
    
	for(int i=0; i<32; i++) _array_neurongroup_4_x[i] = 0;

	_array_neurongroup_4_y = new double[32];
    
	for(int i=0; i<32; i++) _array_neurongroup_4_y[i] = 0;

	_array_neurongroup_5__spikespace = new int32_t[14];
    
	for(int i=0; i<14; i++) _array_neurongroup_5__spikespace[i] = 0;

	_array_neurongroup_5_ge_soma = new double[13];
    
	for(int i=0; i<13; i++) _array_neurongroup_5_ge_soma[i] = 0;

	_array_neurongroup_5_gi_soma = new double[13];
    
	for(int i=0; i<13; i++) _array_neurongroup_5_gi_soma[i] = 0;

	_array_neurongroup_5_i = new int32_t[13];
    
	for(int i=0; i<13; i++) _array_neurongroup_5_i[i] = 0;

	_array_neurongroup_5_lastspike = new double[13];
    
	for(int i=0; i<13; i++) _array_neurongroup_5_lastspike[i] = 0;

	_array_neurongroup_5_not_refractory = new char[13];
    
	for(int i=0; i<13; i++) _array_neurongroup_5_not_refractory[i] = 0;

	_array_neurongroup_5_vm = new double[13];
    
	for(int i=0; i<13; i++) _array_neurongroup_5_vm[i] = 0;

	_array_neurongroup_5_x = new double[13];
    
	for(int i=0; i<13; i++) _array_neurongroup_5_x[i] = 0;

	_array_neurongroup_5_y = new double[13];
    
	for(int i=0; i<13; i++) _array_neurongroup_5_y[i] = 0;

	_array_neurongroup__spikespace = new int32_t[61];
    
	for(int i=0; i<61; i++) _array_neurongroup__spikespace[i] = 0;

	_array_neurongroup_emit_spike = new double[60];
    
	for(int i=0; i<60; i++) _array_neurongroup_emit_spike[i] = 0;

	_array_neurongroup_i = new int32_t[60];
    
	for(int i=0; i<60; i++) _array_neurongroup_i[i] = 0;

	_array_neurongroup_x = new double[60];
    
	for(int i=0; i<60; i++) _array_neurongroup_x[i] = 0;

	_array_neurongroup_y = new double[60];
    
	for(int i=0; i<60; i++) _array_neurongroup_y[i] = 0;

	_array_spikegeneratorgroup__lastindex = new int32_t[1];
    
	for(int i=0; i<1; i++) _array_spikegeneratorgroup__lastindex[i] = 0;

	_array_spikegeneratorgroup__period_bins = new int32_t[1];
    
	for(int i=0; i<1; i++) _array_spikegeneratorgroup__period_bins[i] = 0;

	_array_spikegeneratorgroup__spikespace = new int32_t[61];
    
	for(int i=0; i<61; i++) _array_spikegeneratorgroup__spikespace[i] = 0;

	_array_spikegeneratorgroup_i = new int32_t[60];
    
	for(int i=0; i<60; i++) _array_spikegeneratorgroup_i[i] = 0;

	_array_spikegeneratorgroup_period = new double[1];
    
	for(int i=0; i<1; i++) _array_spikegeneratorgroup_period[i] = 0;

	_array_spikemonitor_1__source_idx = new int32_t[267];
    
	for(int i=0; i<267; i++) _array_spikemonitor_1__source_idx[i] = 0;

	_array_spikemonitor_1_count = new int32_t[267];
    
	for(int i=0; i<267; i++) _array_spikemonitor_1_count[i] = 0;

	_array_spikemonitor_1_N = new int32_t[1];
    
	for(int i=0; i<1; i++) _array_spikemonitor_1_N[i] = 0;

	_array_spikemonitor_2__source_idx = new int32_t[109];
    
	for(int i=0; i<109; i++) _array_spikemonitor_2__source_idx[i] = 0;

	_array_spikemonitor_2_count = new int32_t[109];
    
	for(int i=0; i<109; i++) _array_spikemonitor_2_count[i] = 0;

	_array_spikemonitor_2_N = new int32_t[1];
    
	for(int i=0; i<1; i++) _array_spikemonitor_2_N[i] = 0;

	_array_spikemonitor_3__source_idx = new int32_t[40];
    
	for(int i=0; i<40; i++) _array_spikemonitor_3__source_idx[i] = 0;

	_array_spikemonitor_3_count = new int32_t[40];
    
	for(int i=0; i<40; i++) _array_spikemonitor_3_count[i] = 0;

	_array_spikemonitor_3_N = new int32_t[1];
    
	for(int i=0; i<1; i++) _array_spikemonitor_3_N[i] = 0;

	_array_spikemonitor_4__source_idx = new int32_t[32];
    
	for(int i=0; i<32; i++) _array_spikemonitor_4__source_idx[i] = 0;

	_array_spikemonitor_4_count = new int32_t[32];
    
	for(int i=0; i<32; i++) _array_spikemonitor_4_count[i] = 0;

	_array_spikemonitor_4_N = new int32_t[1];
    
	for(int i=0; i<1; i++) _array_spikemonitor_4_N[i] = 0;

	_array_spikemonitor_5__source_idx = new int32_t[13];
    
	for(int i=0; i<13; i++) _array_spikemonitor_5__source_idx[i] = 0;

	_array_spikemonitor_5_count = new int32_t[13];
    
	for(int i=0; i<13; i++) _array_spikemonitor_5_count[i] = 0;

	_array_spikemonitor_5_N = new int32_t[1];
    
	for(int i=0; i<1; i++) _array_spikemonitor_5_N[i] = 0;

	_array_spikemonitor__source_idx = new int32_t[60];
    
	for(int i=0; i<60; i++) _array_spikemonitor__source_idx[i] = 0;

	_array_spikemonitor_count = new int32_t[60];
    
	for(int i=0; i<60; i++) _array_spikemonitor_count[i] = 0;

	_array_spikemonitor_N = new int32_t[1];
    
	for(int i=0; i<1; i++) _array_spikemonitor_N[i] = 0;

	_array_synapses_10_N = new int32_t[1];
    
	for(int i=0; i<1; i++) _array_synapses_10_N[i] = 0;

	_array_synapses_10_sources = new int32_t[990];
    
	for(int i=0; i<990; i++) _array_synapses_10_sources[i] = 0;

	_array_synapses_10_targets = new int32_t[990];
    
	for(int i=0; i<990; i++) _array_synapses_10_targets[i] = 0;

	_array_synapses_11_N = new int32_t[1];
    
	for(int i=0; i<1; i++) _array_synapses_11_N[i] = 0;

	_array_synapses_11_sources = new int32_t[357];
    
	for(int i=0; i<357; i++) _array_synapses_11_sources[i] = 0;

	_array_synapses_11_targets = new int32_t[357];
    
	for(int i=0; i<357; i++) _array_synapses_11_targets[i] = 0;

	_array_synapses_12_N = new int32_t[1];
    
	for(int i=0; i<1; i++) _array_synapses_12_N[i] = 0;

	_array_synapses_12_sources = new int32_t[28];
    
	for(int i=0; i<28; i++) _array_synapses_12_sources[i] = 0;

	_array_synapses_12_targets = new int32_t[28];
    
	for(int i=0; i<28; i++) _array_synapses_12_targets[i] = 0;

	_array_synapses_13_N = new int32_t[1];
    
	for(int i=0; i<1; i++) _array_synapses_13_N[i] = 0;

	_array_synapses_13_sources = new int32_t[45];
    
	for(int i=0; i<45; i++) _array_synapses_13_sources[i] = 0;

	_array_synapses_13_targets = new int32_t[45];
    
	for(int i=0; i<45; i++) _array_synapses_13_targets[i] = 0;

	_array_synapses_14_N = new int32_t[1];
    
	for(int i=0; i<1; i++) _array_synapses_14_N[i] = 0;

	_array_synapses_14_sources = new int32_t[492];
    
	for(int i=0; i<492; i++) _array_synapses_14_sources[i] = 0;

	_array_synapses_14_targets = new int32_t[492];
    
	for(int i=0; i<492; i++) _array_synapses_14_targets[i] = 0;

	_array_synapses_15_N = new int32_t[1];
    
	for(int i=0; i<1; i++) _array_synapses_15_N[i] = 0;

	_array_synapses_15_sources = new int32_t[300];
    
	for(int i=0; i<300; i++) _array_synapses_15_sources[i] = 0;

	_array_synapses_15_targets = new int32_t[300];
    
	for(int i=0; i<300; i++) _array_synapses_15_targets[i] = 0;

	_array_synapses_16_N = new int32_t[1];
    
	for(int i=0; i<1; i++) _array_synapses_16_N[i] = 0;

	_array_synapses_16_sources = new int32_t[154];
    
	for(int i=0; i<154; i++) _array_synapses_16_sources[i] = 0;

	_array_synapses_16_targets = new int32_t[154];
    
	for(int i=0; i<154; i++) _array_synapses_16_targets[i] = 0;

	_array_synapses_17_N = new int32_t[1];
    
	for(int i=0; i<1; i++) _array_synapses_17_N[i] = 0;

	_array_synapses_17_sources = new int32_t[370];
    
	for(int i=0; i<370; i++) _array_synapses_17_sources[i] = 0;

	_array_synapses_17_targets = new int32_t[370];
    
	for(int i=0; i<370; i++) _array_synapses_17_targets[i] = 0;

	_array_synapses_18_N = new int32_t[1];
    
	for(int i=0; i<1; i++) _array_synapses_18_N[i] = 0;

	_array_synapses_18_sources = new int32_t[252];
    
	for(int i=0; i<252; i++) _array_synapses_18_sources[i] = 0;

	_array_synapses_18_targets = new int32_t[252];
    
	for(int i=0; i<252; i++) _array_synapses_18_targets[i] = 0;

	_array_synapses_19_N = new int32_t[1];
    
	for(int i=0; i<1; i++) _array_synapses_19_N[i] = 0;

	_array_synapses_19_sources = new int32_t[2097];
    
	for(int i=0; i<2097; i++) _array_synapses_19_sources[i] = 0;

	_array_synapses_19_targets = new int32_t[2097];
    
	for(int i=0; i<2097; i++) _array_synapses_19_targets[i] = 0;

	_array_synapses_1_N = new int32_t[1];
    
	for(int i=0; i<1; i++) _array_synapses_1_N[i] = 0;

	_array_synapses_1_sources = new int32_t[4803];
    
	for(int i=0; i<4803; i++) _array_synapses_1_sources[i] = 0;

	_array_synapses_1_targets = new int32_t[4803];
    
	for(int i=0; i<4803; i++) _array_synapses_1_targets[i] = 0;

	_array_synapses_20_N = new int32_t[1];
    
	for(int i=0; i<1; i++) _array_synapses_20_N[i] = 0;

	_array_synapses_20_sources = new int32_t[2142];
    
	for(int i=0; i<2142; i++) _array_synapses_20_sources[i] = 0;

	_array_synapses_20_targets = new int32_t[2142];
    
	for(int i=0; i<2142; i++) _array_synapses_20_targets[i] = 0;

	_array_synapses_21_N = new int32_t[1];
    
	for(int i=0; i<1; i++) _array_synapses_21_N[i] = 0;

	_array_synapses_21_sources = new int32_t[762];
    
	for(int i=0; i<762; i++) _array_synapses_21_sources[i] = 0;

	_array_synapses_21_targets = new int32_t[762];
    
	for(int i=0; i<762; i++) _array_synapses_21_targets[i] = 0;

	_array_synapses_22_N = new int32_t[1];
    
	for(int i=0; i<1; i++) _array_synapses_22_N[i] = 0;

	_array_synapses_22_sources = new int32_t[747];
    
	for(int i=0; i<747; i++) _array_synapses_22_sources[i] = 0;

	_array_synapses_22_targets = new int32_t[747];
    
	for(int i=0; i<747; i++) _array_synapses_22_targets[i] = 0;

	_array_synapses_23_N = new int32_t[1];
    
	for(int i=0; i<1; i++) _array_synapses_23_N[i] = 0;

	_array_synapses_23_sources = new int32_t[642];
    
	for(int i=0; i<642; i++) _array_synapses_23_sources[i] = 0;

	_array_synapses_23_targets = new int32_t[642];
    
	for(int i=0; i<642; i++) _array_synapses_23_targets[i] = 0;

	_array_synapses_24_N = new int32_t[1];
    
	for(int i=0; i<1; i++) _array_synapses_24_N[i] = 0;

	_array_synapses_24_sources = new int32_t[140];
    
	for(int i=0; i<140; i++) _array_synapses_24_sources[i] = 0;

	_array_synapses_24_targets = new int32_t[140];
    
	for(int i=0; i<140; i++) _array_synapses_24_targets[i] = 0;

	_array_synapses_25_N = new int32_t[1];
    
	for(int i=0; i<1; i++) _array_synapses_25_N[i] = 0;

	_array_synapses_25_sources = new int32_t[112];
    
	for(int i=0; i<112; i++) _array_synapses_25_sources[i] = 0;

	_array_synapses_25_targets = new int32_t[112];
    
	for(int i=0; i<112; i++) _array_synapses_25_targets[i] = 0;

	_array_synapses_26_N = new int32_t[1];
    
	for(int i=0; i<1; i++) _array_synapses_26_N[i] = 0;

	_array_synapses_26_sources = new int32_t[512];
    
	for(int i=0; i<512; i++) _array_synapses_26_sources[i] = 0;

	_array_synapses_26_targets = new int32_t[512];
    
	for(int i=0; i<512; i++) _array_synapses_26_targets[i] = 0;

	_array_synapses_27_N = new int32_t[1];
    
	for(int i=0; i<1; i++) _array_synapses_27_N[i] = 0;

	_array_synapses_27_sources = new int32_t[510];
    
	for(int i=0; i<510; i++) _array_synapses_27_sources[i] = 0;

	_array_synapses_27_targets = new int32_t[510];
    
	for(int i=0; i<510; i++) _array_synapses_27_targets[i] = 0;

	_array_synapses_28_N = new int32_t[1];
    
	for(int i=0; i<1; i++) _array_synapses_28_N[i] = 0;

	_array_synapses_28_sources = new int32_t[204];
    
	for(int i=0; i<204; i++) _array_synapses_28_sources[i] = 0;

	_array_synapses_28_targets = new int32_t[204];
    
	for(int i=0; i<204; i++) _array_synapses_28_targets[i] = 0;

	_array_synapses_29_N = new int32_t[1];
    
	for(int i=0; i<1; i++) _array_synapses_29_N[i] = 0;

	_array_synapses_29_sources = new int32_t[234];
    
	for(int i=0; i<234; i++) _array_synapses_29_sources[i] = 0;

	_array_synapses_29_targets = new int32_t[234];
    
	for(int i=0; i<234; i++) _array_synapses_29_targets[i] = 0;

	_array_synapses_2_N = new int32_t[1];
    
	for(int i=0; i<1; i++) _array_synapses_2_N[i] = 0;

	_array_synapses_2_sources = new int32_t[6336];
    
	for(int i=0; i<6336; i++) _array_synapses_2_sources[i] = 0;

	_array_synapses_2_targets = new int32_t[6336];
    
	for(int i=0; i<6336; i++) _array_synapses_2_targets[i] = 0;

	_array_synapses_30_N = new int32_t[1];
    
	for(int i=0; i<1; i++) _array_synapses_30_N[i] = 0;

	_array_synapses_30_sources = new int32_t[168];
    
	for(int i=0; i<168; i++) _array_synapses_30_sources[i] = 0;

	_array_synapses_30_targets = new int32_t[168];
    
	for(int i=0; i<168; i++) _array_synapses_30_targets[i] = 0;

	_array_synapses_31_N = new int32_t[1];
    
	for(int i=0; i<1; i++) _array_synapses_31_N[i] = 0;

	_array_synapses_31_sources = new int32_t[21];
    
	for(int i=0; i<21; i++) _array_synapses_31_sources[i] = 0;

	_array_synapses_31_targets = new int32_t[21];
    
	for(int i=0; i<21; i++) _array_synapses_31_targets[i] = 0;

	_array_synapses_32_N = new int32_t[1];
    
	for(int i=0; i<1; i++) _array_synapses_32_N[i] = 0;

	_array_synapses_32_sources = new int32_t[27];
    
	for(int i=0; i<27; i++) _array_synapses_32_sources[i] = 0;

	_array_synapses_32_targets = new int32_t[27];
    
	for(int i=0; i<27; i++) _array_synapses_32_targets[i] = 0;

	_array_synapses_33_N = new int32_t[1];
    
	for(int i=0; i<1; i++) _array_synapses_33_N[i] = 0;

	_array_synapses_33_sources = new int32_t[333];
    
	for(int i=0; i<333; i++) _array_synapses_33_sources[i] = 0;

	_array_synapses_33_targets = new int32_t[333];
    
	for(int i=0; i<333; i++) _array_synapses_33_targets[i] = 0;

	_array_synapses_34_N = new int32_t[1];
    
	for(int i=0; i<1; i++) _array_synapses_34_N[i] = 0;

	_array_synapses_34_sources = new int32_t[333];
    
	for(int i=0; i<333; i++) _array_synapses_34_sources[i] = 0;

	_array_synapses_34_targets = new int32_t[333];
    
	for(int i=0; i<333; i++) _array_synapses_34_targets[i] = 0;

	_array_synapses_35_N = new int32_t[1];
    
	for(int i=0; i<1; i++) _array_synapses_35_N[i] = 0;

	_array_synapses_35_sources = new int32_t[105];
    
	for(int i=0; i<105; i++) _array_synapses_35_sources[i] = 0;

	_array_synapses_35_targets = new int32_t[105];
    
	for(int i=0; i<105; i++) _array_synapses_35_targets[i] = 0;

	_array_synapses_36_N = new int32_t[1];
    
	for(int i=0; i<1; i++) _array_synapses_36_N[i] = 0;

	_array_synapses_36_sources = new int32_t[78];
    
	for(int i=0; i<78; i++) _array_synapses_36_sources[i] = 0;

	_array_synapses_36_targets = new int32_t[78];
    
	for(int i=0; i<78; i++) _array_synapses_36_targets[i] = 0;

	_array_synapses_37_N = new int32_t[1];
    
	for(int i=0; i<1; i++) _array_synapses_37_N[i] = 0;

	_array_synapses_37_sources = new int32_t[66];
    
	for(int i=0; i<66; i++) _array_synapses_37_sources[i] = 0;

	_array_synapses_37_targets = new int32_t[66];
    
	for(int i=0; i<66; i++) _array_synapses_37_targets[i] = 0;

	_array_synapses_3_N = new int32_t[1];
    
	for(int i=0; i<1; i++) _array_synapses_3_N[i] = 0;

	_array_synapses_3_sources = new int32_t[1938];
    
	for(int i=0; i<1938; i++) _array_synapses_3_sources[i] = 0;

	_array_synapses_3_targets = new int32_t[1938];
    
	for(int i=0; i<1938; i++) _array_synapses_3_targets[i] = 0;

	_array_synapses_4_N = new int32_t[1];
    
	for(int i=0; i<1; i++) _array_synapses_4_N[i] = 0;

	_array_synapses_4_sources = new int32_t[2588];
    
	for(int i=0; i<2588; i++) _array_synapses_4_sources[i] = 0;

	_array_synapses_4_targets = new int32_t[2588];
    
	for(int i=0; i<2588; i++) _array_synapses_4_targets[i] = 0;

	_array_synapses_5_N = new int32_t[1];
    
	for(int i=0; i<1; i++) _array_synapses_5_N[i] = 0;

	_array_synapses_5_sources = new int32_t[11697];
    
	for(int i=0; i<11697; i++) _array_synapses_5_sources[i] = 0;

	_array_synapses_5_targets = new int32_t[11697];
    
	for(int i=0; i<11697; i++) _array_synapses_5_targets[i] = 0;

	_array_synapses_6_N = new int32_t[1];
    
	for(int i=0; i<1; i++) _array_synapses_6_N[i] = 0;

	_array_synapses_6_sources = new int32_t[1384];
    
	for(int i=0; i<1384; i++) _array_synapses_6_sources[i] = 0;

	_array_synapses_6_targets = new int32_t[1384];
    
	for(int i=0; i<1384; i++) _array_synapses_6_targets[i] = 0;

	_array_synapses_7_N = new int32_t[1];
    
	for(int i=0; i<1; i++) _array_synapses_7_N[i] = 0;

	_array_synapses_7_sources = new int32_t[224];
    
	for(int i=0; i<224; i++) _array_synapses_7_sources[i] = 0;

	_array_synapses_7_targets = new int32_t[224];
    
	for(int i=0; i<224; i++) _array_synapses_7_targets[i] = 0;

	_array_synapses_8_N = new int32_t[1];
    
	for(int i=0; i<1; i++) _array_synapses_8_N[i] = 0;

	_array_synapses_8_sources = new int32_t[108];
    
	for(int i=0; i<108; i++) _array_synapses_8_sources[i] = 0;

	_array_synapses_8_targets = new int32_t[108];
    
	for(int i=0; i<108; i++) _array_synapses_8_targets[i] = 0;

	_array_synapses_9_N = new int32_t[1];
    
	for(int i=0; i<1; i++) _array_synapses_9_N[i] = 0;

	_array_synapses_9_sources = new int32_t[1854];
    
	for(int i=0; i<1854; i++) _array_synapses_9_sources[i] = 0;

	_array_synapses_9_targets = new int32_t[1854];
    
	for(int i=0; i<1854; i++) _array_synapses_9_targets[i] = 0;

	_array_synapses_N = new int32_t[1];
    
	for(int i=0; i<1; i++) _array_synapses_N[i] = 0;

	_dynamic_array_spikegeneratorgroup__timebins.resize(60);
    
	for(int i=0; i<60; i++) _dynamic_array_spikegeneratorgroup__timebins[i] = 0;


	// Arrays initialized to an "arange"
	_array_neurongroup_1_i = new int32_t[267];
    
	for(int i=0; i<267; i++) _array_neurongroup_1_i[i] = 0 + i;

	_array_neurongroup_2_i = new int32_t[109];
    
	for(int i=0; i<109; i++) _array_neurongroup_2_i[i] = 0 + i;

	_array_neurongroup_3_i = new int32_t[40];
    
	for(int i=0; i<40; i++) _array_neurongroup_3_i[i] = 0 + i;

	_array_neurongroup_4_i = new int32_t[32];
    
	for(int i=0; i<32; i++) _array_neurongroup_4_i[i] = 0 + i;

	_array_neurongroup_5_i = new int32_t[13];
    
	for(int i=0; i<13; i++) _array_neurongroup_5_i[i] = 0 + i;

	_array_neurongroup_i = new int32_t[60];
    
	for(int i=0; i<60; i++) _array_neurongroup_i[i] = 0 + i;

	_array_spikegeneratorgroup_i = new int32_t[60];
    
	for(int i=0; i<60; i++) _array_spikegeneratorgroup_i[i] = 0 + i;

	_array_spikemonitor_1__source_idx = new int32_t[267];
    
	for(int i=0; i<267; i++) _array_spikemonitor_1__source_idx[i] = 0 + i;

	_array_spikemonitor_2__source_idx = new int32_t[109];
    
	for(int i=0; i<109; i++) _array_spikemonitor_2__source_idx[i] = 0 + i;

	_array_spikemonitor_3__source_idx = new int32_t[40];
    
	for(int i=0; i<40; i++) _array_spikemonitor_3__source_idx[i] = 0 + i;

	_array_spikemonitor_4__source_idx = new int32_t[32];
    
	for(int i=0; i<32; i++) _array_spikemonitor_4__source_idx[i] = 0 + i;

	_array_spikemonitor_5__source_idx = new int32_t[13];
    
	for(int i=0; i<13; i++) _array_spikemonitor_5__source_idx[i] = 0 + i;

	_array_spikemonitor__source_idx = new int32_t[60];
    
	for(int i=0; i<60; i++) _array_spikemonitor__source_idx[i] = 0 + i;


	// static arrays
	_static_array__array_neurongroup_1_x = new double[267];
	_static_array__array_neurongroup_1_y = new double[267];
	_static_array__array_neurongroup_2_x = new double[109];
	_static_array__array_neurongroup_2_y = new double[109];
	_static_array__array_neurongroup_3_x = new double[40];
	_static_array__array_neurongroup_3_y = new double[40];
	_static_array__array_neurongroup_4_x = new double[32];
	_static_array__array_neurongroup_4_y = new double[32];
	_static_array__array_neurongroup_5_x = new double[13];
	_static_array__array_neurongroup_5_y = new double[13];
	_static_array__array_neurongroup_x = new double[60];
	_static_array__array_neurongroup_y = new double[60];
	_static_array__array_synapses_10_sources = new int32_t[990];
	_static_array__array_synapses_10_targets = new int32_t[990];
	_static_array__array_synapses_11_sources = new int32_t[357];
	_static_array__array_synapses_11_targets = new int32_t[357];
	_static_array__array_synapses_12_sources = new int32_t[28];
	_static_array__array_synapses_12_targets = new int32_t[28];
	_static_array__array_synapses_13_sources = new int32_t[45];
	_static_array__array_synapses_13_targets = new int32_t[45];
	_static_array__array_synapses_14_sources = new int32_t[492];
	_static_array__array_synapses_14_targets = new int32_t[492];
	_static_array__array_synapses_15_sources = new int32_t[300];
	_static_array__array_synapses_15_targets = new int32_t[300];
	_static_array__array_synapses_16_sources = new int32_t[154];
	_static_array__array_synapses_16_targets = new int32_t[154];
	_static_array__array_synapses_17_sources = new int32_t[370];
	_static_array__array_synapses_17_targets = new int32_t[370];
	_static_array__array_synapses_18_sources = new int32_t[252];
	_static_array__array_synapses_18_targets = new int32_t[252];
	_static_array__array_synapses_19_sources = new int32_t[2097];
	_static_array__array_synapses_19_targets = new int32_t[2097];
	_static_array__array_synapses_1_sources = new int32_t[4803];
	_static_array__array_synapses_1_targets = new int32_t[4803];
	_static_array__array_synapses_20_sources = new int32_t[2142];
	_static_array__array_synapses_20_targets = new int32_t[2142];
	_static_array__array_synapses_21_sources = new int32_t[762];
	_static_array__array_synapses_21_targets = new int32_t[762];
	_static_array__array_synapses_22_sources = new int32_t[747];
	_static_array__array_synapses_22_targets = new int32_t[747];
	_static_array__array_synapses_23_sources = new int32_t[642];
	_static_array__array_synapses_23_targets = new int32_t[642];
	_static_array__array_synapses_24_sources = new int32_t[140];
	_static_array__array_synapses_24_targets = new int32_t[140];
	_static_array__array_synapses_25_sources = new int32_t[112];
	_static_array__array_synapses_25_targets = new int32_t[112];
	_static_array__array_synapses_26_sources = new int32_t[512];
	_static_array__array_synapses_26_targets = new int32_t[512];
	_static_array__array_synapses_27_sources = new int32_t[510];
	_static_array__array_synapses_27_targets = new int32_t[510];
	_static_array__array_synapses_28_sources = new int32_t[204];
	_static_array__array_synapses_28_targets = new int32_t[204];
	_static_array__array_synapses_29_sources = new int32_t[234];
	_static_array__array_synapses_29_targets = new int32_t[234];
	_static_array__array_synapses_2_sources = new int32_t[6336];
	_static_array__array_synapses_2_targets = new int32_t[6336];
	_static_array__array_synapses_30_sources = new int32_t[168];
	_static_array__array_synapses_30_targets = new int32_t[168];
	_static_array__array_synapses_31_sources = new int32_t[21];
	_static_array__array_synapses_31_targets = new int32_t[21];
	_static_array__array_synapses_32_sources = new int32_t[27];
	_static_array__array_synapses_32_targets = new int32_t[27];
	_static_array__array_synapses_33_sources = new int32_t[333];
	_static_array__array_synapses_33_targets = new int32_t[333];
	_static_array__array_synapses_34_sources = new int32_t[333];
	_static_array__array_synapses_34_targets = new int32_t[333];
	_static_array__array_synapses_35_sources = new int32_t[105];
	_static_array__array_synapses_35_targets = new int32_t[105];
	_static_array__array_synapses_36_sources = new int32_t[78];
	_static_array__array_synapses_36_targets = new int32_t[78];
	_static_array__array_synapses_37_sources = new int32_t[66];
	_static_array__array_synapses_37_targets = new int32_t[66];
	_static_array__array_synapses_3_sources = new int32_t[1938];
	_static_array__array_synapses_3_targets = new int32_t[1938];
	_static_array__array_synapses_4_sources = new int32_t[2588];
	_static_array__array_synapses_4_targets = new int32_t[2588];
	_static_array__array_synapses_5_sources = new int32_t[11697];
	_static_array__array_synapses_5_targets = new int32_t[11697];
	_static_array__array_synapses_6_sources = new int32_t[1384];
	_static_array__array_synapses_6_targets = new int32_t[1384];
	_static_array__array_synapses_7_sources = new int32_t[224];
	_static_array__array_synapses_7_targets = new int32_t[224];
	_static_array__array_synapses_8_sources = new int32_t[108];
	_static_array__array_synapses_8_targets = new int32_t[108];
	_static_array__array_synapses_9_sources = new int32_t[1854];
	_static_array__array_synapses_9_targets = new int32_t[1854];
	_static_array__dynamic_array_spikegeneratorgroup__timebins = new int32_t[60];
	_static_array__dynamic_array_spikegeneratorgroup_neuron_index = new int32_t[60];
	_static_array__dynamic_array_spikegeneratorgroup_spike_number = new int32_t[60];
	_static_array__dynamic_array_spikegeneratorgroup_spike_time = new double[60];

	// Random number generator states
	for (int i=0; i<1; i++)
	    _mersenne_twister_states.push_back(new rk_state());
}

void _load_arrays()
{
	using namespace brian;

	ifstream f_static_array__array_neurongroup_1_x;
	f_static_array__array_neurongroup_1_x.open("static_arrays/_static_array__array_neurongroup_1_x", ios::in | ios::binary);
	if(f_static_array__array_neurongroup_1_x.is_open())
	{
		f_static_array__array_neurongroup_1_x.read(reinterpret_cast<char*>(_static_array__array_neurongroup_1_x), 267*sizeof(double));
	} else
	{
		std::cout << "Error opening static array _static_array__array_neurongroup_1_x." << endl;
	}
	ifstream f_static_array__array_neurongroup_1_y;
	f_static_array__array_neurongroup_1_y.open("static_arrays/_static_array__array_neurongroup_1_y", ios::in | ios::binary);
	if(f_static_array__array_neurongroup_1_y.is_open())
	{
		f_static_array__array_neurongroup_1_y.read(reinterpret_cast<char*>(_static_array__array_neurongroup_1_y), 267*sizeof(double));
	} else
	{
		std::cout << "Error opening static array _static_array__array_neurongroup_1_y." << endl;
	}
	ifstream f_static_array__array_neurongroup_2_x;
	f_static_array__array_neurongroup_2_x.open("static_arrays/_static_array__array_neurongroup_2_x", ios::in | ios::binary);
	if(f_static_array__array_neurongroup_2_x.is_open())
	{
		f_static_array__array_neurongroup_2_x.read(reinterpret_cast<char*>(_static_array__array_neurongroup_2_x), 109*sizeof(double));
	} else
	{
		std::cout << "Error opening static array _static_array__array_neurongroup_2_x." << endl;
	}
	ifstream f_static_array__array_neurongroup_2_y;
	f_static_array__array_neurongroup_2_y.open("static_arrays/_static_array__array_neurongroup_2_y", ios::in | ios::binary);
	if(f_static_array__array_neurongroup_2_y.is_open())
	{
		f_static_array__array_neurongroup_2_y.read(reinterpret_cast<char*>(_static_array__array_neurongroup_2_y), 109*sizeof(double));
	} else
	{
		std::cout << "Error opening static array _static_array__array_neurongroup_2_y." << endl;
	}
	ifstream f_static_array__array_neurongroup_3_x;
	f_static_array__array_neurongroup_3_x.open("static_arrays/_static_array__array_neurongroup_3_x", ios::in | ios::binary);
	if(f_static_array__array_neurongroup_3_x.is_open())
	{
		f_static_array__array_neurongroup_3_x.read(reinterpret_cast<char*>(_static_array__array_neurongroup_3_x), 40*sizeof(double));
	} else
	{
		std::cout << "Error opening static array _static_array__array_neurongroup_3_x." << endl;
	}
	ifstream f_static_array__array_neurongroup_3_y;
	f_static_array__array_neurongroup_3_y.open("static_arrays/_static_array__array_neurongroup_3_y", ios::in | ios::binary);
	if(f_static_array__array_neurongroup_3_y.is_open())
	{
		f_static_array__array_neurongroup_3_y.read(reinterpret_cast<char*>(_static_array__array_neurongroup_3_y), 40*sizeof(double));
	} else
	{
		std::cout << "Error opening static array _static_array__array_neurongroup_3_y." << endl;
	}
	ifstream f_static_array__array_neurongroup_4_x;
	f_static_array__array_neurongroup_4_x.open("static_arrays/_static_array__array_neurongroup_4_x", ios::in | ios::binary);
	if(f_static_array__array_neurongroup_4_x.is_open())
	{
		f_static_array__array_neurongroup_4_x.read(reinterpret_cast<char*>(_static_array__array_neurongroup_4_x), 32*sizeof(double));
	} else
	{
		std::cout << "Error opening static array _static_array__array_neurongroup_4_x." << endl;
	}
	ifstream f_static_array__array_neurongroup_4_y;
	f_static_array__array_neurongroup_4_y.open("static_arrays/_static_array__array_neurongroup_4_y", ios::in | ios::binary);
	if(f_static_array__array_neurongroup_4_y.is_open())
	{
		f_static_array__array_neurongroup_4_y.read(reinterpret_cast<char*>(_static_array__array_neurongroup_4_y), 32*sizeof(double));
	} else
	{
		std::cout << "Error opening static array _static_array__array_neurongroup_4_y." << endl;
	}
	ifstream f_static_array__array_neurongroup_5_x;
	f_static_array__array_neurongroup_5_x.open("static_arrays/_static_array__array_neurongroup_5_x", ios::in | ios::binary);
	if(f_static_array__array_neurongroup_5_x.is_open())
	{
		f_static_array__array_neurongroup_5_x.read(reinterpret_cast<char*>(_static_array__array_neurongroup_5_x), 13*sizeof(double));
	} else
	{
		std::cout << "Error opening static array _static_array__array_neurongroup_5_x." << endl;
	}
	ifstream f_static_array__array_neurongroup_5_y;
	f_static_array__array_neurongroup_5_y.open("static_arrays/_static_array__array_neurongroup_5_y", ios::in | ios::binary);
	if(f_static_array__array_neurongroup_5_y.is_open())
	{
		f_static_array__array_neurongroup_5_y.read(reinterpret_cast<char*>(_static_array__array_neurongroup_5_y), 13*sizeof(double));
	} else
	{
		std::cout << "Error opening static array _static_array__array_neurongroup_5_y." << endl;
	}
	ifstream f_static_array__array_neurongroup_x;
	f_static_array__array_neurongroup_x.open("static_arrays/_static_array__array_neurongroup_x", ios::in | ios::binary);
	if(f_static_array__array_neurongroup_x.is_open())
	{
		f_static_array__array_neurongroup_x.read(reinterpret_cast<char*>(_static_array__array_neurongroup_x), 60*sizeof(double));
	} else
	{
		std::cout << "Error opening static array _static_array__array_neurongroup_x." << endl;
	}
	ifstream f_static_array__array_neurongroup_y;
	f_static_array__array_neurongroup_y.open("static_arrays/_static_array__array_neurongroup_y", ios::in | ios::binary);
	if(f_static_array__array_neurongroup_y.is_open())
	{
		f_static_array__array_neurongroup_y.read(reinterpret_cast<char*>(_static_array__array_neurongroup_y), 60*sizeof(double));
	} else
	{
		std::cout << "Error opening static array _static_array__array_neurongroup_y." << endl;
	}
	ifstream f_static_array__array_synapses_10_sources;
	f_static_array__array_synapses_10_sources.open("static_arrays/_static_array__array_synapses_10_sources", ios::in | ios::binary);
	if(f_static_array__array_synapses_10_sources.is_open())
	{
		f_static_array__array_synapses_10_sources.read(reinterpret_cast<char*>(_static_array__array_synapses_10_sources), 990*sizeof(int32_t));
	} else
	{
		std::cout << "Error opening static array _static_array__array_synapses_10_sources." << endl;
	}
	ifstream f_static_array__array_synapses_10_targets;
	f_static_array__array_synapses_10_targets.open("static_arrays/_static_array__array_synapses_10_targets", ios::in | ios::binary);
	if(f_static_array__array_synapses_10_targets.is_open())
	{
		f_static_array__array_synapses_10_targets.read(reinterpret_cast<char*>(_static_array__array_synapses_10_targets), 990*sizeof(int32_t));
	} else
	{
		std::cout << "Error opening static array _static_array__array_synapses_10_targets." << endl;
	}
	ifstream f_static_array__array_synapses_11_sources;
	f_static_array__array_synapses_11_sources.open("static_arrays/_static_array__array_synapses_11_sources", ios::in | ios::binary);
	if(f_static_array__array_synapses_11_sources.is_open())
	{
		f_static_array__array_synapses_11_sources.read(reinterpret_cast<char*>(_static_array__array_synapses_11_sources), 357*sizeof(int32_t));
	} else
	{
		std::cout << "Error opening static array _static_array__array_synapses_11_sources." << endl;
	}
	ifstream f_static_array__array_synapses_11_targets;
	f_static_array__array_synapses_11_targets.open("static_arrays/_static_array__array_synapses_11_targets", ios::in | ios::binary);
	if(f_static_array__array_synapses_11_targets.is_open())
	{
		f_static_array__array_synapses_11_targets.read(reinterpret_cast<char*>(_static_array__array_synapses_11_targets), 357*sizeof(int32_t));
	} else
	{
		std::cout << "Error opening static array _static_array__array_synapses_11_targets." << endl;
	}
	ifstream f_static_array__array_synapses_12_sources;
	f_static_array__array_synapses_12_sources.open("static_arrays/_static_array__array_synapses_12_sources", ios::in | ios::binary);
	if(f_static_array__array_synapses_12_sources.is_open())
	{
		f_static_array__array_synapses_12_sources.read(reinterpret_cast<char*>(_static_array__array_synapses_12_sources), 28*sizeof(int32_t));
	} else
	{
		std::cout << "Error opening static array _static_array__array_synapses_12_sources." << endl;
	}
	ifstream f_static_array__array_synapses_12_targets;
	f_static_array__array_synapses_12_targets.open("static_arrays/_static_array__array_synapses_12_targets", ios::in | ios::binary);
	if(f_static_array__array_synapses_12_targets.is_open())
	{
		f_static_array__array_synapses_12_targets.read(reinterpret_cast<char*>(_static_array__array_synapses_12_targets), 28*sizeof(int32_t));
	} else
	{
		std::cout << "Error opening static array _static_array__array_synapses_12_targets." << endl;
	}
	ifstream f_static_array__array_synapses_13_sources;
	f_static_array__array_synapses_13_sources.open("static_arrays/_static_array__array_synapses_13_sources", ios::in | ios::binary);
	if(f_static_array__array_synapses_13_sources.is_open())
	{
		f_static_array__array_synapses_13_sources.read(reinterpret_cast<char*>(_static_array__array_synapses_13_sources), 45*sizeof(int32_t));
	} else
	{
		std::cout << "Error opening static array _static_array__array_synapses_13_sources." << endl;
	}
	ifstream f_static_array__array_synapses_13_targets;
	f_static_array__array_synapses_13_targets.open("static_arrays/_static_array__array_synapses_13_targets", ios::in | ios::binary);
	if(f_static_array__array_synapses_13_targets.is_open())
	{
		f_static_array__array_synapses_13_targets.read(reinterpret_cast<char*>(_static_array__array_synapses_13_targets), 45*sizeof(int32_t));
	} else
	{
		std::cout << "Error opening static array _static_array__array_synapses_13_targets." << endl;
	}
	ifstream f_static_array__array_synapses_14_sources;
	f_static_array__array_synapses_14_sources.open("static_arrays/_static_array__array_synapses_14_sources", ios::in | ios::binary);
	if(f_static_array__array_synapses_14_sources.is_open())
	{
		f_static_array__array_synapses_14_sources.read(reinterpret_cast<char*>(_static_array__array_synapses_14_sources), 492*sizeof(int32_t));
	} else
	{
		std::cout << "Error opening static array _static_array__array_synapses_14_sources." << endl;
	}
	ifstream f_static_array__array_synapses_14_targets;
	f_static_array__array_synapses_14_targets.open("static_arrays/_static_array__array_synapses_14_targets", ios::in | ios::binary);
	if(f_static_array__array_synapses_14_targets.is_open())
	{
		f_static_array__array_synapses_14_targets.read(reinterpret_cast<char*>(_static_array__array_synapses_14_targets), 492*sizeof(int32_t));
	} else
	{
		std::cout << "Error opening static array _static_array__array_synapses_14_targets." << endl;
	}
	ifstream f_static_array__array_synapses_15_sources;
	f_static_array__array_synapses_15_sources.open("static_arrays/_static_array__array_synapses_15_sources", ios::in | ios::binary);
	if(f_static_array__array_synapses_15_sources.is_open())
	{
		f_static_array__array_synapses_15_sources.read(reinterpret_cast<char*>(_static_array__array_synapses_15_sources), 300*sizeof(int32_t));
	} else
	{
		std::cout << "Error opening static array _static_array__array_synapses_15_sources." << endl;
	}
	ifstream f_static_array__array_synapses_15_targets;
	f_static_array__array_synapses_15_targets.open("static_arrays/_static_array__array_synapses_15_targets", ios::in | ios::binary);
	if(f_static_array__array_synapses_15_targets.is_open())
	{
		f_static_array__array_synapses_15_targets.read(reinterpret_cast<char*>(_static_array__array_synapses_15_targets), 300*sizeof(int32_t));
	} else
	{
		std::cout << "Error opening static array _static_array__array_synapses_15_targets." << endl;
	}
	ifstream f_static_array__array_synapses_16_sources;
	f_static_array__array_synapses_16_sources.open("static_arrays/_static_array__array_synapses_16_sources", ios::in | ios::binary);
	if(f_static_array__array_synapses_16_sources.is_open())
	{
		f_static_array__array_synapses_16_sources.read(reinterpret_cast<char*>(_static_array__array_synapses_16_sources), 154*sizeof(int32_t));
	} else
	{
		std::cout << "Error opening static array _static_array__array_synapses_16_sources." << endl;
	}
	ifstream f_static_array__array_synapses_16_targets;
	f_static_array__array_synapses_16_targets.open("static_arrays/_static_array__array_synapses_16_targets", ios::in | ios::binary);
	if(f_static_array__array_synapses_16_targets.is_open())
	{
		f_static_array__array_synapses_16_targets.read(reinterpret_cast<char*>(_static_array__array_synapses_16_targets), 154*sizeof(int32_t));
	} else
	{
		std::cout << "Error opening static array _static_array__array_synapses_16_targets." << endl;
	}
	ifstream f_static_array__array_synapses_17_sources;
	f_static_array__array_synapses_17_sources.open("static_arrays/_static_array__array_synapses_17_sources", ios::in | ios::binary);
	if(f_static_array__array_synapses_17_sources.is_open())
	{
		f_static_array__array_synapses_17_sources.read(reinterpret_cast<char*>(_static_array__array_synapses_17_sources), 370*sizeof(int32_t));
	} else
	{
		std::cout << "Error opening static array _static_array__array_synapses_17_sources." << endl;
	}
	ifstream f_static_array__array_synapses_17_targets;
	f_static_array__array_synapses_17_targets.open("static_arrays/_static_array__array_synapses_17_targets", ios::in | ios::binary);
	if(f_static_array__array_synapses_17_targets.is_open())
	{
		f_static_array__array_synapses_17_targets.read(reinterpret_cast<char*>(_static_array__array_synapses_17_targets), 370*sizeof(int32_t));
	} else
	{
		std::cout << "Error opening static array _static_array__array_synapses_17_targets." << endl;
	}
	ifstream f_static_array__array_synapses_18_sources;
	f_static_array__array_synapses_18_sources.open("static_arrays/_static_array__array_synapses_18_sources", ios::in | ios::binary);
	if(f_static_array__array_synapses_18_sources.is_open())
	{
		f_static_array__array_synapses_18_sources.read(reinterpret_cast<char*>(_static_array__array_synapses_18_sources), 252*sizeof(int32_t));
	} else
	{
		std::cout << "Error opening static array _static_array__array_synapses_18_sources." << endl;
	}
	ifstream f_static_array__array_synapses_18_targets;
	f_static_array__array_synapses_18_targets.open("static_arrays/_static_array__array_synapses_18_targets", ios::in | ios::binary);
	if(f_static_array__array_synapses_18_targets.is_open())
	{
		f_static_array__array_synapses_18_targets.read(reinterpret_cast<char*>(_static_array__array_synapses_18_targets), 252*sizeof(int32_t));
	} else
	{
		std::cout << "Error opening static array _static_array__array_synapses_18_targets." << endl;
	}
	ifstream f_static_array__array_synapses_19_sources;
	f_static_array__array_synapses_19_sources.open("static_arrays/_static_array__array_synapses_19_sources", ios::in | ios::binary);
	if(f_static_array__array_synapses_19_sources.is_open())
	{
		f_static_array__array_synapses_19_sources.read(reinterpret_cast<char*>(_static_array__array_synapses_19_sources), 2097*sizeof(int32_t));
	} else
	{
		std::cout << "Error opening static array _static_array__array_synapses_19_sources." << endl;
	}
	ifstream f_static_array__array_synapses_19_targets;
	f_static_array__array_synapses_19_targets.open("static_arrays/_static_array__array_synapses_19_targets", ios::in | ios::binary);
	if(f_static_array__array_synapses_19_targets.is_open())
	{
		f_static_array__array_synapses_19_targets.read(reinterpret_cast<char*>(_static_array__array_synapses_19_targets), 2097*sizeof(int32_t));
	} else
	{
		std::cout << "Error opening static array _static_array__array_synapses_19_targets." << endl;
	}
	ifstream f_static_array__array_synapses_1_sources;
	f_static_array__array_synapses_1_sources.open("static_arrays/_static_array__array_synapses_1_sources", ios::in | ios::binary);
	if(f_static_array__array_synapses_1_sources.is_open())
	{
		f_static_array__array_synapses_1_sources.read(reinterpret_cast<char*>(_static_array__array_synapses_1_sources), 4803*sizeof(int32_t));
	} else
	{
		std::cout << "Error opening static array _static_array__array_synapses_1_sources." << endl;
	}
	ifstream f_static_array__array_synapses_1_targets;
	f_static_array__array_synapses_1_targets.open("static_arrays/_static_array__array_synapses_1_targets", ios::in | ios::binary);
	if(f_static_array__array_synapses_1_targets.is_open())
	{
		f_static_array__array_synapses_1_targets.read(reinterpret_cast<char*>(_static_array__array_synapses_1_targets), 4803*sizeof(int32_t));
	} else
	{
		std::cout << "Error opening static array _static_array__array_synapses_1_targets." << endl;
	}
	ifstream f_static_array__array_synapses_20_sources;
	f_static_array__array_synapses_20_sources.open("static_arrays/_static_array__array_synapses_20_sources", ios::in | ios::binary);
	if(f_static_array__array_synapses_20_sources.is_open())
	{
		f_static_array__array_synapses_20_sources.read(reinterpret_cast<char*>(_static_array__array_synapses_20_sources), 2142*sizeof(int32_t));
	} else
	{
		std::cout << "Error opening static array _static_array__array_synapses_20_sources." << endl;
	}
	ifstream f_static_array__array_synapses_20_targets;
	f_static_array__array_synapses_20_targets.open("static_arrays/_static_array__array_synapses_20_targets", ios::in | ios::binary);
	if(f_static_array__array_synapses_20_targets.is_open())
	{
		f_static_array__array_synapses_20_targets.read(reinterpret_cast<char*>(_static_array__array_synapses_20_targets), 2142*sizeof(int32_t));
	} else
	{
		std::cout << "Error opening static array _static_array__array_synapses_20_targets." << endl;
	}
	ifstream f_static_array__array_synapses_21_sources;
	f_static_array__array_synapses_21_sources.open("static_arrays/_static_array__array_synapses_21_sources", ios::in | ios::binary);
	if(f_static_array__array_synapses_21_sources.is_open())
	{
		f_static_array__array_synapses_21_sources.read(reinterpret_cast<char*>(_static_array__array_synapses_21_sources), 762*sizeof(int32_t));
	} else
	{
		std::cout << "Error opening static array _static_array__array_synapses_21_sources." << endl;
	}
	ifstream f_static_array__array_synapses_21_targets;
	f_static_array__array_synapses_21_targets.open("static_arrays/_static_array__array_synapses_21_targets", ios::in | ios::binary);
	if(f_static_array__array_synapses_21_targets.is_open())
	{
		f_static_array__array_synapses_21_targets.read(reinterpret_cast<char*>(_static_array__array_synapses_21_targets), 762*sizeof(int32_t));
	} else
	{
		std::cout << "Error opening static array _static_array__array_synapses_21_targets." << endl;
	}
	ifstream f_static_array__array_synapses_22_sources;
	f_static_array__array_synapses_22_sources.open("static_arrays/_static_array__array_synapses_22_sources", ios::in | ios::binary);
	if(f_static_array__array_synapses_22_sources.is_open())
	{
		f_static_array__array_synapses_22_sources.read(reinterpret_cast<char*>(_static_array__array_synapses_22_sources), 747*sizeof(int32_t));
	} else
	{
		std::cout << "Error opening static array _static_array__array_synapses_22_sources." << endl;
	}
	ifstream f_static_array__array_synapses_22_targets;
	f_static_array__array_synapses_22_targets.open("static_arrays/_static_array__array_synapses_22_targets", ios::in | ios::binary);
	if(f_static_array__array_synapses_22_targets.is_open())
	{
		f_static_array__array_synapses_22_targets.read(reinterpret_cast<char*>(_static_array__array_synapses_22_targets), 747*sizeof(int32_t));
	} else
	{
		std::cout << "Error opening static array _static_array__array_synapses_22_targets." << endl;
	}
	ifstream f_static_array__array_synapses_23_sources;
	f_static_array__array_synapses_23_sources.open("static_arrays/_static_array__array_synapses_23_sources", ios::in | ios::binary);
	if(f_static_array__array_synapses_23_sources.is_open())
	{
		f_static_array__array_synapses_23_sources.read(reinterpret_cast<char*>(_static_array__array_synapses_23_sources), 642*sizeof(int32_t));
	} else
	{
		std::cout << "Error opening static array _static_array__array_synapses_23_sources." << endl;
	}
	ifstream f_static_array__array_synapses_23_targets;
	f_static_array__array_synapses_23_targets.open("static_arrays/_static_array__array_synapses_23_targets", ios::in | ios::binary);
	if(f_static_array__array_synapses_23_targets.is_open())
	{
		f_static_array__array_synapses_23_targets.read(reinterpret_cast<char*>(_static_array__array_synapses_23_targets), 642*sizeof(int32_t));
	} else
	{
		std::cout << "Error opening static array _static_array__array_synapses_23_targets." << endl;
	}
	ifstream f_static_array__array_synapses_24_sources;
	f_static_array__array_synapses_24_sources.open("static_arrays/_static_array__array_synapses_24_sources", ios::in | ios::binary);
	if(f_static_array__array_synapses_24_sources.is_open())
	{
		f_static_array__array_synapses_24_sources.read(reinterpret_cast<char*>(_static_array__array_synapses_24_sources), 140*sizeof(int32_t));
	} else
	{
		std::cout << "Error opening static array _static_array__array_synapses_24_sources." << endl;
	}
	ifstream f_static_array__array_synapses_24_targets;
	f_static_array__array_synapses_24_targets.open("static_arrays/_static_array__array_synapses_24_targets", ios::in | ios::binary);
	if(f_static_array__array_synapses_24_targets.is_open())
	{
		f_static_array__array_synapses_24_targets.read(reinterpret_cast<char*>(_static_array__array_synapses_24_targets), 140*sizeof(int32_t));
	} else
	{
		std::cout << "Error opening static array _static_array__array_synapses_24_targets." << endl;
	}
	ifstream f_static_array__array_synapses_25_sources;
	f_static_array__array_synapses_25_sources.open("static_arrays/_static_array__array_synapses_25_sources", ios::in | ios::binary);
	if(f_static_array__array_synapses_25_sources.is_open())
	{
		f_static_array__array_synapses_25_sources.read(reinterpret_cast<char*>(_static_array__array_synapses_25_sources), 112*sizeof(int32_t));
	} else
	{
		std::cout << "Error opening static array _static_array__array_synapses_25_sources." << endl;
	}
	ifstream f_static_array__array_synapses_25_targets;
	f_static_array__array_synapses_25_targets.open("static_arrays/_static_array__array_synapses_25_targets", ios::in | ios::binary);
	if(f_static_array__array_synapses_25_targets.is_open())
	{
		f_static_array__array_synapses_25_targets.read(reinterpret_cast<char*>(_static_array__array_synapses_25_targets), 112*sizeof(int32_t));
	} else
	{
		std::cout << "Error opening static array _static_array__array_synapses_25_targets." << endl;
	}
	ifstream f_static_array__array_synapses_26_sources;
	f_static_array__array_synapses_26_sources.open("static_arrays/_static_array__array_synapses_26_sources", ios::in | ios::binary);
	if(f_static_array__array_synapses_26_sources.is_open())
	{
		f_static_array__array_synapses_26_sources.read(reinterpret_cast<char*>(_static_array__array_synapses_26_sources), 512*sizeof(int32_t));
	} else
	{
		std::cout << "Error opening static array _static_array__array_synapses_26_sources." << endl;
	}
	ifstream f_static_array__array_synapses_26_targets;
	f_static_array__array_synapses_26_targets.open("static_arrays/_static_array__array_synapses_26_targets", ios::in | ios::binary);
	if(f_static_array__array_synapses_26_targets.is_open())
	{
		f_static_array__array_synapses_26_targets.read(reinterpret_cast<char*>(_static_array__array_synapses_26_targets), 512*sizeof(int32_t));
	} else
	{
		std::cout << "Error opening static array _static_array__array_synapses_26_targets." << endl;
	}
	ifstream f_static_array__array_synapses_27_sources;
	f_static_array__array_synapses_27_sources.open("static_arrays/_static_array__array_synapses_27_sources", ios::in | ios::binary);
	if(f_static_array__array_synapses_27_sources.is_open())
	{
		f_static_array__array_synapses_27_sources.read(reinterpret_cast<char*>(_static_array__array_synapses_27_sources), 510*sizeof(int32_t));
	} else
	{
		std::cout << "Error opening static array _static_array__array_synapses_27_sources." << endl;
	}
	ifstream f_static_array__array_synapses_27_targets;
	f_static_array__array_synapses_27_targets.open("static_arrays/_static_array__array_synapses_27_targets", ios::in | ios::binary);
	if(f_static_array__array_synapses_27_targets.is_open())
	{
		f_static_array__array_synapses_27_targets.read(reinterpret_cast<char*>(_static_array__array_synapses_27_targets), 510*sizeof(int32_t));
	} else
	{
		std::cout << "Error opening static array _static_array__array_synapses_27_targets." << endl;
	}
	ifstream f_static_array__array_synapses_28_sources;
	f_static_array__array_synapses_28_sources.open("static_arrays/_static_array__array_synapses_28_sources", ios::in | ios::binary);
	if(f_static_array__array_synapses_28_sources.is_open())
	{
		f_static_array__array_synapses_28_sources.read(reinterpret_cast<char*>(_static_array__array_synapses_28_sources), 204*sizeof(int32_t));
	} else
	{
		std::cout << "Error opening static array _static_array__array_synapses_28_sources." << endl;
	}
	ifstream f_static_array__array_synapses_28_targets;
	f_static_array__array_synapses_28_targets.open("static_arrays/_static_array__array_synapses_28_targets", ios::in | ios::binary);
	if(f_static_array__array_synapses_28_targets.is_open())
	{
		f_static_array__array_synapses_28_targets.read(reinterpret_cast<char*>(_static_array__array_synapses_28_targets), 204*sizeof(int32_t));
	} else
	{
		std::cout << "Error opening static array _static_array__array_synapses_28_targets." << endl;
	}
	ifstream f_static_array__array_synapses_29_sources;
	f_static_array__array_synapses_29_sources.open("static_arrays/_static_array__array_synapses_29_sources", ios::in | ios::binary);
	if(f_static_array__array_synapses_29_sources.is_open())
	{
		f_static_array__array_synapses_29_sources.read(reinterpret_cast<char*>(_static_array__array_synapses_29_sources), 234*sizeof(int32_t));
	} else
	{
		std::cout << "Error opening static array _static_array__array_synapses_29_sources." << endl;
	}
	ifstream f_static_array__array_synapses_29_targets;
	f_static_array__array_synapses_29_targets.open("static_arrays/_static_array__array_synapses_29_targets", ios::in | ios::binary);
	if(f_static_array__array_synapses_29_targets.is_open())
	{
		f_static_array__array_synapses_29_targets.read(reinterpret_cast<char*>(_static_array__array_synapses_29_targets), 234*sizeof(int32_t));
	} else
	{
		std::cout << "Error opening static array _static_array__array_synapses_29_targets." << endl;
	}
	ifstream f_static_array__array_synapses_2_sources;
	f_static_array__array_synapses_2_sources.open("static_arrays/_static_array__array_synapses_2_sources", ios::in | ios::binary);
	if(f_static_array__array_synapses_2_sources.is_open())
	{
		f_static_array__array_synapses_2_sources.read(reinterpret_cast<char*>(_static_array__array_synapses_2_sources), 6336*sizeof(int32_t));
	} else
	{
		std::cout << "Error opening static array _static_array__array_synapses_2_sources." << endl;
	}
	ifstream f_static_array__array_synapses_2_targets;
	f_static_array__array_synapses_2_targets.open("static_arrays/_static_array__array_synapses_2_targets", ios::in | ios::binary);
	if(f_static_array__array_synapses_2_targets.is_open())
	{
		f_static_array__array_synapses_2_targets.read(reinterpret_cast<char*>(_static_array__array_synapses_2_targets), 6336*sizeof(int32_t));
	} else
	{
		std::cout << "Error opening static array _static_array__array_synapses_2_targets." << endl;
	}
	ifstream f_static_array__array_synapses_30_sources;
	f_static_array__array_synapses_30_sources.open("static_arrays/_static_array__array_synapses_30_sources", ios::in | ios::binary);
	if(f_static_array__array_synapses_30_sources.is_open())
	{
		f_static_array__array_synapses_30_sources.read(reinterpret_cast<char*>(_static_array__array_synapses_30_sources), 168*sizeof(int32_t));
	} else
	{
		std::cout << "Error opening static array _static_array__array_synapses_30_sources." << endl;
	}
	ifstream f_static_array__array_synapses_30_targets;
	f_static_array__array_synapses_30_targets.open("static_arrays/_static_array__array_synapses_30_targets", ios::in | ios::binary);
	if(f_static_array__array_synapses_30_targets.is_open())
	{
		f_static_array__array_synapses_30_targets.read(reinterpret_cast<char*>(_static_array__array_synapses_30_targets), 168*sizeof(int32_t));
	} else
	{
		std::cout << "Error opening static array _static_array__array_synapses_30_targets." << endl;
	}
	ifstream f_static_array__array_synapses_31_sources;
	f_static_array__array_synapses_31_sources.open("static_arrays/_static_array__array_synapses_31_sources", ios::in | ios::binary);
	if(f_static_array__array_synapses_31_sources.is_open())
	{
		f_static_array__array_synapses_31_sources.read(reinterpret_cast<char*>(_static_array__array_synapses_31_sources), 21*sizeof(int32_t));
	} else
	{
		std::cout << "Error opening static array _static_array__array_synapses_31_sources." << endl;
	}
	ifstream f_static_array__array_synapses_31_targets;
	f_static_array__array_synapses_31_targets.open("static_arrays/_static_array__array_synapses_31_targets", ios::in | ios::binary);
	if(f_static_array__array_synapses_31_targets.is_open())
	{
		f_static_array__array_synapses_31_targets.read(reinterpret_cast<char*>(_static_array__array_synapses_31_targets), 21*sizeof(int32_t));
	} else
	{
		std::cout << "Error opening static array _static_array__array_synapses_31_targets." << endl;
	}
	ifstream f_static_array__array_synapses_32_sources;
	f_static_array__array_synapses_32_sources.open("static_arrays/_static_array__array_synapses_32_sources", ios::in | ios::binary);
	if(f_static_array__array_synapses_32_sources.is_open())
	{
		f_static_array__array_synapses_32_sources.read(reinterpret_cast<char*>(_static_array__array_synapses_32_sources), 27*sizeof(int32_t));
	} else
	{
		std::cout << "Error opening static array _static_array__array_synapses_32_sources." << endl;
	}
	ifstream f_static_array__array_synapses_32_targets;
	f_static_array__array_synapses_32_targets.open("static_arrays/_static_array__array_synapses_32_targets", ios::in | ios::binary);
	if(f_static_array__array_synapses_32_targets.is_open())
	{
		f_static_array__array_synapses_32_targets.read(reinterpret_cast<char*>(_static_array__array_synapses_32_targets), 27*sizeof(int32_t));
	} else
	{
		std::cout << "Error opening static array _static_array__array_synapses_32_targets." << endl;
	}
	ifstream f_static_array__array_synapses_33_sources;
	f_static_array__array_synapses_33_sources.open("static_arrays/_static_array__array_synapses_33_sources", ios::in | ios::binary);
	if(f_static_array__array_synapses_33_sources.is_open())
	{
		f_static_array__array_synapses_33_sources.read(reinterpret_cast<char*>(_static_array__array_synapses_33_sources), 333*sizeof(int32_t));
	} else
	{
		std::cout << "Error opening static array _static_array__array_synapses_33_sources." << endl;
	}
	ifstream f_static_array__array_synapses_33_targets;
	f_static_array__array_synapses_33_targets.open("static_arrays/_static_array__array_synapses_33_targets", ios::in | ios::binary);
	if(f_static_array__array_synapses_33_targets.is_open())
	{
		f_static_array__array_synapses_33_targets.read(reinterpret_cast<char*>(_static_array__array_synapses_33_targets), 333*sizeof(int32_t));
	} else
	{
		std::cout << "Error opening static array _static_array__array_synapses_33_targets." << endl;
	}
	ifstream f_static_array__array_synapses_34_sources;
	f_static_array__array_synapses_34_sources.open("static_arrays/_static_array__array_synapses_34_sources", ios::in | ios::binary);
	if(f_static_array__array_synapses_34_sources.is_open())
	{
		f_static_array__array_synapses_34_sources.read(reinterpret_cast<char*>(_static_array__array_synapses_34_sources), 333*sizeof(int32_t));
	} else
	{
		std::cout << "Error opening static array _static_array__array_synapses_34_sources." << endl;
	}
	ifstream f_static_array__array_synapses_34_targets;
	f_static_array__array_synapses_34_targets.open("static_arrays/_static_array__array_synapses_34_targets", ios::in | ios::binary);
	if(f_static_array__array_synapses_34_targets.is_open())
	{
		f_static_array__array_synapses_34_targets.read(reinterpret_cast<char*>(_static_array__array_synapses_34_targets), 333*sizeof(int32_t));
	} else
	{
		std::cout << "Error opening static array _static_array__array_synapses_34_targets." << endl;
	}
	ifstream f_static_array__array_synapses_35_sources;
	f_static_array__array_synapses_35_sources.open("static_arrays/_static_array__array_synapses_35_sources", ios::in | ios::binary);
	if(f_static_array__array_synapses_35_sources.is_open())
	{
		f_static_array__array_synapses_35_sources.read(reinterpret_cast<char*>(_static_array__array_synapses_35_sources), 105*sizeof(int32_t));
	} else
	{
		std::cout << "Error opening static array _static_array__array_synapses_35_sources." << endl;
	}
	ifstream f_static_array__array_synapses_35_targets;
	f_static_array__array_synapses_35_targets.open("static_arrays/_static_array__array_synapses_35_targets", ios::in | ios::binary);
	if(f_static_array__array_synapses_35_targets.is_open())
	{
		f_static_array__array_synapses_35_targets.read(reinterpret_cast<char*>(_static_array__array_synapses_35_targets), 105*sizeof(int32_t));
	} else
	{
		std::cout << "Error opening static array _static_array__array_synapses_35_targets." << endl;
	}
	ifstream f_static_array__array_synapses_36_sources;
	f_static_array__array_synapses_36_sources.open("static_arrays/_static_array__array_synapses_36_sources", ios::in | ios::binary);
	if(f_static_array__array_synapses_36_sources.is_open())
	{
		f_static_array__array_synapses_36_sources.read(reinterpret_cast<char*>(_static_array__array_synapses_36_sources), 78*sizeof(int32_t));
	} else
	{
		std::cout << "Error opening static array _static_array__array_synapses_36_sources." << endl;
	}
	ifstream f_static_array__array_synapses_36_targets;
	f_static_array__array_synapses_36_targets.open("static_arrays/_static_array__array_synapses_36_targets", ios::in | ios::binary);
	if(f_static_array__array_synapses_36_targets.is_open())
	{
		f_static_array__array_synapses_36_targets.read(reinterpret_cast<char*>(_static_array__array_synapses_36_targets), 78*sizeof(int32_t));
	} else
	{
		std::cout << "Error opening static array _static_array__array_synapses_36_targets." << endl;
	}
	ifstream f_static_array__array_synapses_37_sources;
	f_static_array__array_synapses_37_sources.open("static_arrays/_static_array__array_synapses_37_sources", ios::in | ios::binary);
	if(f_static_array__array_synapses_37_sources.is_open())
	{
		f_static_array__array_synapses_37_sources.read(reinterpret_cast<char*>(_static_array__array_synapses_37_sources), 66*sizeof(int32_t));
	} else
	{
		std::cout << "Error opening static array _static_array__array_synapses_37_sources." << endl;
	}
	ifstream f_static_array__array_synapses_37_targets;
	f_static_array__array_synapses_37_targets.open("static_arrays/_static_array__array_synapses_37_targets", ios::in | ios::binary);
	if(f_static_array__array_synapses_37_targets.is_open())
	{
		f_static_array__array_synapses_37_targets.read(reinterpret_cast<char*>(_static_array__array_synapses_37_targets), 66*sizeof(int32_t));
	} else
	{
		std::cout << "Error opening static array _static_array__array_synapses_37_targets." << endl;
	}
	ifstream f_static_array__array_synapses_3_sources;
	f_static_array__array_synapses_3_sources.open("static_arrays/_static_array__array_synapses_3_sources", ios::in | ios::binary);
	if(f_static_array__array_synapses_3_sources.is_open())
	{
		f_static_array__array_synapses_3_sources.read(reinterpret_cast<char*>(_static_array__array_synapses_3_sources), 1938*sizeof(int32_t));
	} else
	{
		std::cout << "Error opening static array _static_array__array_synapses_3_sources." << endl;
	}
	ifstream f_static_array__array_synapses_3_targets;
	f_static_array__array_synapses_3_targets.open("static_arrays/_static_array__array_synapses_3_targets", ios::in | ios::binary);
	if(f_static_array__array_synapses_3_targets.is_open())
	{
		f_static_array__array_synapses_3_targets.read(reinterpret_cast<char*>(_static_array__array_synapses_3_targets), 1938*sizeof(int32_t));
	} else
	{
		std::cout << "Error opening static array _static_array__array_synapses_3_targets." << endl;
	}
	ifstream f_static_array__array_synapses_4_sources;
	f_static_array__array_synapses_4_sources.open("static_arrays/_static_array__array_synapses_4_sources", ios::in | ios::binary);
	if(f_static_array__array_synapses_4_sources.is_open())
	{
		f_static_array__array_synapses_4_sources.read(reinterpret_cast<char*>(_static_array__array_synapses_4_sources), 2588*sizeof(int32_t));
	} else
	{
		std::cout << "Error opening static array _static_array__array_synapses_4_sources." << endl;
	}
	ifstream f_static_array__array_synapses_4_targets;
	f_static_array__array_synapses_4_targets.open("static_arrays/_static_array__array_synapses_4_targets", ios::in | ios::binary);
	if(f_static_array__array_synapses_4_targets.is_open())
	{
		f_static_array__array_synapses_4_targets.read(reinterpret_cast<char*>(_static_array__array_synapses_4_targets), 2588*sizeof(int32_t));
	} else
	{
		std::cout << "Error opening static array _static_array__array_synapses_4_targets." << endl;
	}
	ifstream f_static_array__array_synapses_5_sources;
	f_static_array__array_synapses_5_sources.open("static_arrays/_static_array__array_synapses_5_sources", ios::in | ios::binary);
	if(f_static_array__array_synapses_5_sources.is_open())
	{
		f_static_array__array_synapses_5_sources.read(reinterpret_cast<char*>(_static_array__array_synapses_5_sources), 11697*sizeof(int32_t));
	} else
	{
		std::cout << "Error opening static array _static_array__array_synapses_5_sources." << endl;
	}
	ifstream f_static_array__array_synapses_5_targets;
	f_static_array__array_synapses_5_targets.open("static_arrays/_static_array__array_synapses_5_targets", ios::in | ios::binary);
	if(f_static_array__array_synapses_5_targets.is_open())
	{
		f_static_array__array_synapses_5_targets.read(reinterpret_cast<char*>(_static_array__array_synapses_5_targets), 11697*sizeof(int32_t));
	} else
	{
		std::cout << "Error opening static array _static_array__array_synapses_5_targets." << endl;
	}
	ifstream f_static_array__array_synapses_6_sources;
	f_static_array__array_synapses_6_sources.open("static_arrays/_static_array__array_synapses_6_sources", ios::in | ios::binary);
	if(f_static_array__array_synapses_6_sources.is_open())
	{
		f_static_array__array_synapses_6_sources.read(reinterpret_cast<char*>(_static_array__array_synapses_6_sources), 1384*sizeof(int32_t));
	} else
	{
		std::cout << "Error opening static array _static_array__array_synapses_6_sources." << endl;
	}
	ifstream f_static_array__array_synapses_6_targets;
	f_static_array__array_synapses_6_targets.open("static_arrays/_static_array__array_synapses_6_targets", ios::in | ios::binary);
	if(f_static_array__array_synapses_6_targets.is_open())
	{
		f_static_array__array_synapses_6_targets.read(reinterpret_cast<char*>(_static_array__array_synapses_6_targets), 1384*sizeof(int32_t));
	} else
	{
		std::cout << "Error opening static array _static_array__array_synapses_6_targets." << endl;
	}
	ifstream f_static_array__array_synapses_7_sources;
	f_static_array__array_synapses_7_sources.open("static_arrays/_static_array__array_synapses_7_sources", ios::in | ios::binary);
	if(f_static_array__array_synapses_7_sources.is_open())
	{
		f_static_array__array_synapses_7_sources.read(reinterpret_cast<char*>(_static_array__array_synapses_7_sources), 224*sizeof(int32_t));
	} else
	{
		std::cout << "Error opening static array _static_array__array_synapses_7_sources." << endl;
	}
	ifstream f_static_array__array_synapses_7_targets;
	f_static_array__array_synapses_7_targets.open("static_arrays/_static_array__array_synapses_7_targets", ios::in | ios::binary);
	if(f_static_array__array_synapses_7_targets.is_open())
	{
		f_static_array__array_synapses_7_targets.read(reinterpret_cast<char*>(_static_array__array_synapses_7_targets), 224*sizeof(int32_t));
	} else
	{
		std::cout << "Error opening static array _static_array__array_synapses_7_targets." << endl;
	}
	ifstream f_static_array__array_synapses_8_sources;
	f_static_array__array_synapses_8_sources.open("static_arrays/_static_array__array_synapses_8_sources", ios::in | ios::binary);
	if(f_static_array__array_synapses_8_sources.is_open())
	{
		f_static_array__array_synapses_8_sources.read(reinterpret_cast<char*>(_static_array__array_synapses_8_sources), 108*sizeof(int32_t));
	} else
	{
		std::cout << "Error opening static array _static_array__array_synapses_8_sources." << endl;
	}
	ifstream f_static_array__array_synapses_8_targets;
	f_static_array__array_synapses_8_targets.open("static_arrays/_static_array__array_synapses_8_targets", ios::in | ios::binary);
	if(f_static_array__array_synapses_8_targets.is_open())
	{
		f_static_array__array_synapses_8_targets.read(reinterpret_cast<char*>(_static_array__array_synapses_8_targets), 108*sizeof(int32_t));
	} else
	{
		std::cout << "Error opening static array _static_array__array_synapses_8_targets." << endl;
	}
	ifstream f_static_array__array_synapses_9_sources;
	f_static_array__array_synapses_9_sources.open("static_arrays/_static_array__array_synapses_9_sources", ios::in | ios::binary);
	if(f_static_array__array_synapses_9_sources.is_open())
	{
		f_static_array__array_synapses_9_sources.read(reinterpret_cast<char*>(_static_array__array_synapses_9_sources), 1854*sizeof(int32_t));
	} else
	{
		std::cout << "Error opening static array _static_array__array_synapses_9_sources." << endl;
	}
	ifstream f_static_array__array_synapses_9_targets;
	f_static_array__array_synapses_9_targets.open("static_arrays/_static_array__array_synapses_9_targets", ios::in | ios::binary);
	if(f_static_array__array_synapses_9_targets.is_open())
	{
		f_static_array__array_synapses_9_targets.read(reinterpret_cast<char*>(_static_array__array_synapses_9_targets), 1854*sizeof(int32_t));
	} else
	{
		std::cout << "Error opening static array _static_array__array_synapses_9_targets." << endl;
	}
	ifstream f_static_array__dynamic_array_spikegeneratorgroup__timebins;
	f_static_array__dynamic_array_spikegeneratorgroup__timebins.open("static_arrays/_static_array__dynamic_array_spikegeneratorgroup__timebins", ios::in | ios::binary);
	if(f_static_array__dynamic_array_spikegeneratorgroup__timebins.is_open())
	{
		f_static_array__dynamic_array_spikegeneratorgroup__timebins.read(reinterpret_cast<char*>(_static_array__dynamic_array_spikegeneratorgroup__timebins), 60*sizeof(int32_t));
	} else
	{
		std::cout << "Error opening static array _static_array__dynamic_array_spikegeneratorgroup__timebins." << endl;
	}
	ifstream f_static_array__dynamic_array_spikegeneratorgroup_neuron_index;
	f_static_array__dynamic_array_spikegeneratorgroup_neuron_index.open("static_arrays/_static_array__dynamic_array_spikegeneratorgroup_neuron_index", ios::in | ios::binary);
	if(f_static_array__dynamic_array_spikegeneratorgroup_neuron_index.is_open())
	{
		f_static_array__dynamic_array_spikegeneratorgroup_neuron_index.read(reinterpret_cast<char*>(_static_array__dynamic_array_spikegeneratorgroup_neuron_index), 60*sizeof(int32_t));
	} else
	{
		std::cout << "Error opening static array _static_array__dynamic_array_spikegeneratorgroup_neuron_index." << endl;
	}
	ifstream f_static_array__dynamic_array_spikegeneratorgroup_spike_number;
	f_static_array__dynamic_array_spikegeneratorgroup_spike_number.open("static_arrays/_static_array__dynamic_array_spikegeneratorgroup_spike_number", ios::in | ios::binary);
	if(f_static_array__dynamic_array_spikegeneratorgroup_spike_number.is_open())
	{
		f_static_array__dynamic_array_spikegeneratorgroup_spike_number.read(reinterpret_cast<char*>(_static_array__dynamic_array_spikegeneratorgroup_spike_number), 60*sizeof(int32_t));
	} else
	{
		std::cout << "Error opening static array _static_array__dynamic_array_spikegeneratorgroup_spike_number." << endl;
	}
	ifstream f_static_array__dynamic_array_spikegeneratorgroup_spike_time;
	f_static_array__dynamic_array_spikegeneratorgroup_spike_time.open("static_arrays/_static_array__dynamic_array_spikegeneratorgroup_spike_time", ios::in | ios::binary);
	if(f_static_array__dynamic_array_spikegeneratorgroup_spike_time.is_open())
	{
		f_static_array__dynamic_array_spikegeneratorgroup_spike_time.read(reinterpret_cast<char*>(_static_array__dynamic_array_spikegeneratorgroup_spike_time), 60*sizeof(double));
	} else
	{
		std::cout << "Error opening static array _static_array__dynamic_array_spikegeneratorgroup_spike_time." << endl;
	}
}

void _write_arrays()
{
	using namespace brian;

	ofstream outfile__array_defaultclock_dt;
	outfile__array_defaultclock_dt.open("results\\_array_defaultclock_dt_-8953586961601847179", ios::binary | ios::out);
	if(outfile__array_defaultclock_dt.is_open())
	{
		outfile__array_defaultclock_dt.write(reinterpret_cast<char*>(_array_defaultclock_dt), 1*sizeof(_array_defaultclock_dt[0]));
		outfile__array_defaultclock_dt.close();
	} else
	{
		std::cout << "Error writing output file for _array_defaultclock_dt." << endl;
	}
	ofstream outfile__array_defaultclock_t;
	outfile__array_defaultclock_t.open("results\\_array_defaultclock_t_-1768137214433379808", ios::binary | ios::out);
	if(outfile__array_defaultclock_t.is_open())
	{
		outfile__array_defaultclock_t.write(reinterpret_cast<char*>(_array_defaultclock_t), 1*sizeof(_array_defaultclock_t[0]));
		outfile__array_defaultclock_t.close();
	} else
	{
		std::cout << "Error writing output file for _array_defaultclock_t." << endl;
	}
	ofstream outfile__array_defaultclock_timestep;
	outfile__array_defaultclock_timestep.open("results\\_array_defaultclock_timestep_-2501002956882764845", ios::binary | ios::out);
	if(outfile__array_defaultclock_timestep.is_open())
	{
		outfile__array_defaultclock_timestep.write(reinterpret_cast<char*>(_array_defaultclock_timestep), 1*sizeof(_array_defaultclock_timestep[0]));
		outfile__array_defaultclock_timestep.close();
	} else
	{
		std::cout << "Error writing output file for _array_defaultclock_timestep." << endl;
	}
	ofstream outfile__array_neurongroup_1__spikespace;
	outfile__array_neurongroup_1__spikespace.open("results\\_array_neurongroup_1__spikespace_4524678804069838786", ios::binary | ios::out);
	if(outfile__array_neurongroup_1__spikespace.is_open())
	{
		outfile__array_neurongroup_1__spikespace.write(reinterpret_cast<char*>(_array_neurongroup_1__spikespace), 268*sizeof(_array_neurongroup_1__spikespace[0]));
		outfile__array_neurongroup_1__spikespace.close();
	} else
	{
		std::cout << "Error writing output file for _array_neurongroup_1__spikespace." << endl;
	}
	ofstream outfile__array_neurongroup_1_ge_a0;
	outfile__array_neurongroup_1_ge_a0.open("results\\_array_neurongroup_1_ge_a0_-4838561815964892489", ios::binary | ios::out);
	if(outfile__array_neurongroup_1_ge_a0.is_open())
	{
		outfile__array_neurongroup_1_ge_a0.write(reinterpret_cast<char*>(_array_neurongroup_1_ge_a0), 267*sizeof(_array_neurongroup_1_ge_a0[0]));
		outfile__array_neurongroup_1_ge_a0.close();
	} else
	{
		std::cout << "Error writing output file for _array_neurongroup_1_ge_a0." << endl;
	}
	ofstream outfile__array_neurongroup_1_ge_a1;
	outfile__array_neurongroup_1_ge_a1.open("results\\_array_neurongroup_1_ge_a1_-6389538931109807503", ios::binary | ios::out);
	if(outfile__array_neurongroup_1_ge_a1.is_open())
	{
		outfile__array_neurongroup_1_ge_a1.write(reinterpret_cast<char*>(_array_neurongroup_1_ge_a1), 267*sizeof(_array_neurongroup_1_ge_a1[0]));
		outfile__array_neurongroup_1_ge_a1.close();
	} else
	{
		std::cout << "Error writing output file for _array_neurongroup_1_ge_a1." << endl;
	}
	ofstream outfile__array_neurongroup_1_ge_a2;
	outfile__array_neurongroup_1_ge_a2.open("results\\_array_neurongroup_1_ge_a2_83712609345242005", ios::binary | ios::out);
	if(outfile__array_neurongroup_1_ge_a2.is_open())
	{
		outfile__array_neurongroup_1_ge_a2.write(reinterpret_cast<char*>(_array_neurongroup_1_ge_a2), 267*sizeof(_array_neurongroup_1_ge_a2[0]));
		outfile__array_neurongroup_1_ge_a2.close();
	} else
	{
		std::cout << "Error writing output file for _array_neurongroup_1_ge_a2." << endl;
	}
	ofstream outfile__array_neurongroup_1_ge_basal;
	outfile__array_neurongroup_1_ge_basal.open("results\\_array_neurongroup_1_ge_basal_4894803224279188048", ios::binary | ios::out);
	if(outfile__array_neurongroup_1_ge_basal.is_open())
	{
		outfile__array_neurongroup_1_ge_basal.write(reinterpret_cast<char*>(_array_neurongroup_1_ge_basal), 267*sizeof(_array_neurongroup_1_ge_basal[0]));
		outfile__array_neurongroup_1_ge_basal.close();
	} else
	{
		std::cout << "Error writing output file for _array_neurongroup_1_ge_basal." << endl;
	}
	ofstream outfile__array_neurongroup_1_ge_soma;
	outfile__array_neurongroup_1_ge_soma.open("results\\_array_neurongroup_1_ge_soma_6178004825859227947", ios::binary | ios::out);
	if(outfile__array_neurongroup_1_ge_soma.is_open())
	{
		outfile__array_neurongroup_1_ge_soma.write(reinterpret_cast<char*>(_array_neurongroup_1_ge_soma), 267*sizeof(_array_neurongroup_1_ge_soma[0]));
		outfile__array_neurongroup_1_ge_soma.close();
	} else
	{
		std::cout << "Error writing output file for _array_neurongroup_1_ge_soma." << endl;
	}
	ofstream outfile__array_neurongroup_1_gealpha_a0;
	outfile__array_neurongroup_1_gealpha_a0.open("results\\_array_neurongroup_1_gealpha_a0_-4019200337298414207", ios::binary | ios::out);
	if(outfile__array_neurongroup_1_gealpha_a0.is_open())
	{
		outfile__array_neurongroup_1_gealpha_a0.write(reinterpret_cast<char*>(_array_neurongroup_1_gealpha_a0), 267*sizeof(_array_neurongroup_1_gealpha_a0[0]));
		outfile__array_neurongroup_1_gealpha_a0.close();
	} else
	{
		std::cout << "Error writing output file for _array_neurongroup_1_gealpha_a0." << endl;
	}
	ofstream outfile__array_neurongroup_1_gealpha_a1;
	outfile__array_neurongroup_1_gealpha_a1.open("results\\_array_neurongroup_1_gealpha_a1_487133597475503738", ios::binary | ios::out);
	if(outfile__array_neurongroup_1_gealpha_a1.is_open())
	{
		outfile__array_neurongroup_1_gealpha_a1.write(reinterpret_cast<char*>(_array_neurongroup_1_gealpha_a1), 267*sizeof(_array_neurongroup_1_gealpha_a1[0]));
		outfile__array_neurongroup_1_gealpha_a1.close();
	} else
	{
		std::cout << "Error writing output file for _array_neurongroup_1_gealpha_a1." << endl;
	}
	ofstream outfile__array_neurongroup_1_gealpha_a2;
	outfile__array_neurongroup_1_gealpha_a2.open("results\\_array_neurongroup_1_gealpha_a2_9038007855696702356", ios::binary | ios::out);
	if(outfile__array_neurongroup_1_gealpha_a2.is_open())
	{
		outfile__array_neurongroup_1_gealpha_a2.write(reinterpret_cast<char*>(_array_neurongroup_1_gealpha_a2), 267*sizeof(_array_neurongroup_1_gealpha_a2[0]));
		outfile__array_neurongroup_1_gealpha_a2.close();
	} else
	{
		std::cout << "Error writing output file for _array_neurongroup_1_gealpha_a2." << endl;
	}
	ofstream outfile__array_neurongroup_1_gealpha_basal;
	outfile__array_neurongroup_1_gealpha_basal.open("results\\_array_neurongroup_1_gealpha_basal_-453613938547970360", ios::binary | ios::out);
	if(outfile__array_neurongroup_1_gealpha_basal.is_open())
	{
		outfile__array_neurongroup_1_gealpha_basal.write(reinterpret_cast<char*>(_array_neurongroup_1_gealpha_basal), 267*sizeof(_array_neurongroup_1_gealpha_basal[0]));
		outfile__array_neurongroup_1_gealpha_basal.close();
	} else
	{
		std::cout << "Error writing output file for _array_neurongroup_1_gealpha_basal." << endl;
	}
	ofstream outfile__array_neurongroup_1_gealpha_soma;
	outfile__array_neurongroup_1_gealpha_soma.open("results\\_array_neurongroup_1_gealpha_soma_-1071771522252478919", ios::binary | ios::out);
	if(outfile__array_neurongroup_1_gealpha_soma.is_open())
	{
		outfile__array_neurongroup_1_gealpha_soma.write(reinterpret_cast<char*>(_array_neurongroup_1_gealpha_soma), 267*sizeof(_array_neurongroup_1_gealpha_soma[0]));
		outfile__array_neurongroup_1_gealpha_soma.close();
	} else
	{
		std::cout << "Error writing output file for _array_neurongroup_1_gealpha_soma." << endl;
	}
	ofstream outfile__array_neurongroup_1_gi_a0;
	outfile__array_neurongroup_1_gi_a0.open("results\\_array_neurongroup_1_gi_a0_477660732799816209", ios::binary | ios::out);
	if(outfile__array_neurongroup_1_gi_a0.is_open())
	{
		outfile__array_neurongroup_1_gi_a0.write(reinterpret_cast<char*>(_array_neurongroup_1_gi_a0), 267*sizeof(_array_neurongroup_1_gi_a0[0]));
		outfile__array_neurongroup_1_gi_a0.close();
	} else
	{
		std::cout << "Error writing output file for _array_neurongroup_1_gi_a0." << endl;
	}
	ofstream outfile__array_neurongroup_1_gi_a1;
	outfile__array_neurongroup_1_gi_a1.open("results\\_array_neurongroup_1_gi_a1_-6507340280138794091", ios::binary | ios::out);
	if(outfile__array_neurongroup_1_gi_a1.is_open())
	{
		outfile__array_neurongroup_1_gi_a1.write(reinterpret_cast<char*>(_array_neurongroup_1_gi_a1), 267*sizeof(_array_neurongroup_1_gi_a1[0]));
		outfile__array_neurongroup_1_gi_a1.close();
	} else
	{
		std::cout << "Error writing output file for _array_neurongroup_1_gi_a1." << endl;
	}
	ofstream outfile__array_neurongroup_1_gi_a2;
	outfile__array_neurongroup_1_gi_a2.open("results\\_array_neurongroup_1_gi_a2_4443083955032112473", ios::binary | ios::out);
	if(outfile__array_neurongroup_1_gi_a2.is_open())
	{
		outfile__array_neurongroup_1_gi_a2.write(reinterpret_cast<char*>(_array_neurongroup_1_gi_a2), 267*sizeof(_array_neurongroup_1_gi_a2[0]));
		outfile__array_neurongroup_1_gi_a2.close();
	} else
	{
		std::cout << "Error writing output file for _array_neurongroup_1_gi_a2." << endl;
	}
	ofstream outfile__array_neurongroup_1_gi_basal;
	outfile__array_neurongroup_1_gi_basal.open("results\\_array_neurongroup_1_gi_basal_-55901924745120848", ios::binary | ios::out);
	if(outfile__array_neurongroup_1_gi_basal.is_open())
	{
		outfile__array_neurongroup_1_gi_basal.write(reinterpret_cast<char*>(_array_neurongroup_1_gi_basal), 267*sizeof(_array_neurongroup_1_gi_basal[0]));
		outfile__array_neurongroup_1_gi_basal.close();
	} else
	{
		std::cout << "Error writing output file for _array_neurongroup_1_gi_basal." << endl;
	}
	ofstream outfile__array_neurongroup_1_gi_soma;
	outfile__array_neurongroup_1_gi_soma.open("results\\_array_neurongroup_1_gi_soma_-3209573405802102420", ios::binary | ios::out);
	if(outfile__array_neurongroup_1_gi_soma.is_open())
	{
		outfile__array_neurongroup_1_gi_soma.write(reinterpret_cast<char*>(_array_neurongroup_1_gi_soma), 267*sizeof(_array_neurongroup_1_gi_soma[0]));
		outfile__array_neurongroup_1_gi_soma.close();
	} else
	{
		std::cout << "Error writing output file for _array_neurongroup_1_gi_soma." << endl;
	}
	ofstream outfile__array_neurongroup_1_gialpha_a0;
	outfile__array_neurongroup_1_gialpha_a0.open("results\\_array_neurongroup_1_gialpha_a0_-8565933846834554889", ios::binary | ios::out);
	if(outfile__array_neurongroup_1_gialpha_a0.is_open())
	{
		outfile__array_neurongroup_1_gialpha_a0.write(reinterpret_cast<char*>(_array_neurongroup_1_gialpha_a0), 267*sizeof(_array_neurongroup_1_gialpha_a0[0]));
		outfile__array_neurongroup_1_gialpha_a0.close();
	} else
	{
		std::cout << "Error writing output file for _array_neurongroup_1_gialpha_a0." << endl;
	}
	ofstream outfile__array_neurongroup_1_gialpha_a1;
	outfile__array_neurongroup_1_gialpha_a1.open("results\\_array_neurongroup_1_gialpha_a1_-5168365174569931012", ios::binary | ios::out);
	if(outfile__array_neurongroup_1_gialpha_a1.is_open())
	{
		outfile__array_neurongroup_1_gialpha_a1.write(reinterpret_cast<char*>(_array_neurongroup_1_gialpha_a1), 267*sizeof(_array_neurongroup_1_gialpha_a1[0]));
		outfile__array_neurongroup_1_gialpha_a1.close();
	} else
	{
		std::cout << "Error writing output file for _array_neurongroup_1_gialpha_a1." << endl;
	}
	ofstream outfile__array_neurongroup_1_gialpha_a2;
	outfile__array_neurongroup_1_gialpha_a2.open("results\\_array_neurongroup_1_gialpha_a2_7595555979726408867", ios::binary | ios::out);
	if(outfile__array_neurongroup_1_gialpha_a2.is_open())
	{
		outfile__array_neurongroup_1_gialpha_a2.write(reinterpret_cast<char*>(_array_neurongroup_1_gialpha_a2), 267*sizeof(_array_neurongroup_1_gialpha_a2[0]));
		outfile__array_neurongroup_1_gialpha_a2.close();
	} else
	{
		std::cout << "Error writing output file for _array_neurongroup_1_gialpha_a2." << endl;
	}
	ofstream outfile__array_neurongroup_1_gialpha_basal;
	outfile__array_neurongroup_1_gialpha_basal.open("results\\_array_neurongroup_1_gialpha_basal_4804531197255235699", ios::binary | ios::out);
	if(outfile__array_neurongroup_1_gialpha_basal.is_open())
	{
		outfile__array_neurongroup_1_gialpha_basal.write(reinterpret_cast<char*>(_array_neurongroup_1_gialpha_basal), 267*sizeof(_array_neurongroup_1_gialpha_basal[0]));
		outfile__array_neurongroup_1_gialpha_basal.close();
	} else
	{
		std::cout << "Error writing output file for _array_neurongroup_1_gialpha_basal." << endl;
	}
	ofstream outfile__array_neurongroup_1_gialpha_soma;
	outfile__array_neurongroup_1_gialpha_soma.open("results\\_array_neurongroup_1_gialpha_soma_3684599978872892188", ios::binary | ios::out);
	if(outfile__array_neurongroup_1_gialpha_soma.is_open())
	{
		outfile__array_neurongroup_1_gialpha_soma.write(reinterpret_cast<char*>(_array_neurongroup_1_gialpha_soma), 267*sizeof(_array_neurongroup_1_gialpha_soma[0]));
		outfile__array_neurongroup_1_gialpha_soma.close();
	} else
	{
		std::cout << "Error writing output file for _array_neurongroup_1_gialpha_soma." << endl;
	}
	ofstream outfile__array_neurongroup_1_i;
	outfile__array_neurongroup_1_i.open("results\\_array_neurongroup_1_i_-7759459328357737744", ios::binary | ios::out);
	if(outfile__array_neurongroup_1_i.is_open())
	{
		outfile__array_neurongroup_1_i.write(reinterpret_cast<char*>(_array_neurongroup_1_i), 267*sizeof(_array_neurongroup_1_i[0]));
		outfile__array_neurongroup_1_i.close();
	} else
	{
		std::cout << "Error writing output file for _array_neurongroup_1_i." << endl;
	}
	ofstream outfile__array_neurongroup_1_lastspike;
	outfile__array_neurongroup_1_lastspike.open("results\\_array_neurongroup_1_lastspike_6965506225800120864", ios::binary | ios::out);
	if(outfile__array_neurongroup_1_lastspike.is_open())
	{
		outfile__array_neurongroup_1_lastspike.write(reinterpret_cast<char*>(_array_neurongroup_1_lastspike), 267*sizeof(_array_neurongroup_1_lastspike[0]));
		outfile__array_neurongroup_1_lastspike.close();
	} else
	{
		std::cout << "Error writing output file for _array_neurongroup_1_lastspike." << endl;
	}
	ofstream outfile__array_neurongroup_1_not_refractory;
	outfile__array_neurongroup_1_not_refractory.open("results\\_array_neurongroup_1_not_refractory_-3638147582966966579", ios::binary | ios::out);
	if(outfile__array_neurongroup_1_not_refractory.is_open())
	{
		outfile__array_neurongroup_1_not_refractory.write(reinterpret_cast<char*>(_array_neurongroup_1_not_refractory), 267*sizeof(_array_neurongroup_1_not_refractory[0]));
		outfile__array_neurongroup_1_not_refractory.close();
	} else
	{
		std::cout << "Error writing output file for _array_neurongroup_1_not_refractory." << endl;
	}
	ofstream outfile__array_neurongroup_1_vm;
	outfile__array_neurongroup_1_vm.open("results\\_array_neurongroup_1_vm_-4523195985634577060", ios::binary | ios::out);
	if(outfile__array_neurongroup_1_vm.is_open())
	{
		outfile__array_neurongroup_1_vm.write(reinterpret_cast<char*>(_array_neurongroup_1_vm), 267*sizeof(_array_neurongroup_1_vm[0]));
		outfile__array_neurongroup_1_vm.close();
	} else
	{
		std::cout << "Error writing output file for _array_neurongroup_1_vm." << endl;
	}
	ofstream outfile__array_neurongroup_1_vm_a0;
	outfile__array_neurongroup_1_vm_a0.open("results\\_array_neurongroup_1_vm_a0_-3324608343207027967", ios::binary | ios::out);
	if(outfile__array_neurongroup_1_vm_a0.is_open())
	{
		outfile__array_neurongroup_1_vm_a0.write(reinterpret_cast<char*>(_array_neurongroup_1_vm_a0), 267*sizeof(_array_neurongroup_1_vm_a0[0]));
		outfile__array_neurongroup_1_vm_a0.close();
	} else
	{
		std::cout << "Error writing output file for _array_neurongroup_1_vm_a0." << endl;
	}
	ofstream outfile__array_neurongroup_1_vm_a1;
	outfile__array_neurongroup_1_vm_a1.open("results\\_array_neurongroup_1_vm_a1_7901805569076986989", ios::binary | ios::out);
	if(outfile__array_neurongroup_1_vm_a1.is_open())
	{
		outfile__array_neurongroup_1_vm_a1.write(reinterpret_cast<char*>(_array_neurongroup_1_vm_a1), 267*sizeof(_array_neurongroup_1_vm_a1[0]));
		outfile__array_neurongroup_1_vm_a1.close();
	} else
	{
		std::cout << "Error writing output file for _array_neurongroup_1_vm_a1." << endl;
	}
	ofstream outfile__array_neurongroup_1_vm_a2;
	outfile__array_neurongroup_1_vm_a2.open("results\\_array_neurongroup_1_vm_a2_5629892126892092015", ios::binary | ios::out);
	if(outfile__array_neurongroup_1_vm_a2.is_open())
	{
		outfile__array_neurongroup_1_vm_a2.write(reinterpret_cast<char*>(_array_neurongroup_1_vm_a2), 267*sizeof(_array_neurongroup_1_vm_a2[0]));
		outfile__array_neurongroup_1_vm_a2.close();
	} else
	{
		std::cout << "Error writing output file for _array_neurongroup_1_vm_a2." << endl;
	}
	ofstream outfile__array_neurongroup_1_vm_basal;
	outfile__array_neurongroup_1_vm_basal.open("results\\_array_neurongroup_1_vm_basal_5828768994929220448", ios::binary | ios::out);
	if(outfile__array_neurongroup_1_vm_basal.is_open())
	{
		outfile__array_neurongroup_1_vm_basal.write(reinterpret_cast<char*>(_array_neurongroup_1_vm_basal), 267*sizeof(_array_neurongroup_1_vm_basal[0]));
		outfile__array_neurongroup_1_vm_basal.close();
	} else
	{
		std::cout << "Error writing output file for _array_neurongroup_1_vm_basal." << endl;
	}
	ofstream outfile__array_neurongroup_1_x;
	outfile__array_neurongroup_1_x.open("results\\_array_neurongroup_1_x_-8027086588419875401", ios::binary | ios::out);
	if(outfile__array_neurongroup_1_x.is_open())
	{
		outfile__array_neurongroup_1_x.write(reinterpret_cast<char*>(_array_neurongroup_1_x), 267*sizeof(_array_neurongroup_1_x[0]));
		outfile__array_neurongroup_1_x.close();
	} else
	{
		std::cout << "Error writing output file for _array_neurongroup_1_x." << endl;
	}
	ofstream outfile__array_neurongroup_1_y;
	outfile__array_neurongroup_1_y.open("results\\_array_neurongroup_1_y_490070502020046410", ios::binary | ios::out);
	if(outfile__array_neurongroup_1_y.is_open())
	{
		outfile__array_neurongroup_1_y.write(reinterpret_cast<char*>(_array_neurongroup_1_y), 267*sizeof(_array_neurongroup_1_y[0]));
		outfile__array_neurongroup_1_y.close();
	} else
	{
		std::cout << "Error writing output file for _array_neurongroup_1_y." << endl;
	}
	ofstream outfile__array_neurongroup_2__spikespace;
	outfile__array_neurongroup_2__spikespace.open("results\\_array_neurongroup_2__spikespace_8358275026275430938", ios::binary | ios::out);
	if(outfile__array_neurongroup_2__spikespace.is_open())
	{
		outfile__array_neurongroup_2__spikespace.write(reinterpret_cast<char*>(_array_neurongroup_2__spikespace), 110*sizeof(_array_neurongroup_2__spikespace[0]));
		outfile__array_neurongroup_2__spikespace.close();
	} else
	{
		std::cout << "Error writing output file for _array_neurongroup_2__spikespace." << endl;
	}
	ofstream outfile__array_neurongroup_2_ge_a0;
	outfile__array_neurongroup_2_ge_a0.open("results\\_array_neurongroup_2_ge_a0_-1230499469878989151", ios::binary | ios::out);
	if(outfile__array_neurongroup_2_ge_a0.is_open())
	{
		outfile__array_neurongroup_2_ge_a0.write(reinterpret_cast<char*>(_array_neurongroup_2_ge_a0), 109*sizeof(_array_neurongroup_2_ge_a0[0]));
		outfile__array_neurongroup_2_ge_a0.close();
	} else
	{
		std::cout << "Error writing output file for _array_neurongroup_2_ge_a0." << endl;
	}
	ofstream outfile__array_neurongroup_2_ge_a1;
	outfile__array_neurongroup_2_ge_a1.open("results\\_array_neurongroup_2_ge_a1_-6817411806266080227", ios::binary | ios::out);
	if(outfile__array_neurongroup_2_ge_a1.is_open())
	{
		outfile__array_neurongroup_2_ge_a1.write(reinterpret_cast<char*>(_array_neurongroup_2_ge_a1), 109*sizeof(_array_neurongroup_2_ge_a1[0]));
		outfile__array_neurongroup_2_ge_a1.close();
	} else
	{
		std::cout << "Error writing output file for _array_neurongroup_2_ge_a1." << endl;
	}
	ofstream outfile__array_neurongroup_2_ge_a2;
	outfile__array_neurongroup_2_ge_a2.open("results\\_array_neurongroup_2_ge_a2_-4737280522866209966", ios::binary | ios::out);
	if(outfile__array_neurongroup_2_ge_a2.is_open())
	{
		outfile__array_neurongroup_2_ge_a2.write(reinterpret_cast<char*>(_array_neurongroup_2_ge_a2), 109*sizeof(_array_neurongroup_2_ge_a2[0]));
		outfile__array_neurongroup_2_ge_a2.close();
	} else
	{
		std::cout << "Error writing output file for _array_neurongroup_2_ge_a2." << endl;
	}
	ofstream outfile__array_neurongroup_2_ge_basal;
	outfile__array_neurongroup_2_ge_basal.open("results\\_array_neurongroup_2_ge_basal_4782892635213541302", ios::binary | ios::out);
	if(outfile__array_neurongroup_2_ge_basal.is_open())
	{
		outfile__array_neurongroup_2_ge_basal.write(reinterpret_cast<char*>(_array_neurongroup_2_ge_basal), 109*sizeof(_array_neurongroup_2_ge_basal[0]));
		outfile__array_neurongroup_2_ge_basal.close();
	} else
	{
		std::cout << "Error writing output file for _array_neurongroup_2_ge_basal." << endl;
	}
	ofstream outfile__array_neurongroup_2_ge_soma;
	outfile__array_neurongroup_2_ge_soma.open("results\\_array_neurongroup_2_ge_soma_-229724910354929081", ios::binary | ios::out);
	if(outfile__array_neurongroup_2_ge_soma.is_open())
	{
		outfile__array_neurongroup_2_ge_soma.write(reinterpret_cast<char*>(_array_neurongroup_2_ge_soma), 109*sizeof(_array_neurongroup_2_ge_soma[0]));
		outfile__array_neurongroup_2_ge_soma.close();
	} else
	{
		std::cout << "Error writing output file for _array_neurongroup_2_ge_soma." << endl;
	}
	ofstream outfile__array_neurongroup_2_gealpha_a0;
	outfile__array_neurongroup_2_gealpha_a0.open("results\\_array_neurongroup_2_gealpha_a0_7951960894561847106", ios::binary | ios::out);
	if(outfile__array_neurongroup_2_gealpha_a0.is_open())
	{
		outfile__array_neurongroup_2_gealpha_a0.write(reinterpret_cast<char*>(_array_neurongroup_2_gealpha_a0), 109*sizeof(_array_neurongroup_2_gealpha_a0[0]));
		outfile__array_neurongroup_2_gealpha_a0.close();
	} else
	{
		std::cout << "Error writing output file for _array_neurongroup_2_gealpha_a0." << endl;
	}
	ofstream outfile__array_neurongroup_2_gealpha_a1;
	outfile__array_neurongroup_2_gealpha_a1.open("results\\_array_neurongroup_2_gealpha_a1_-2947879468421442291", ios::binary | ios::out);
	if(outfile__array_neurongroup_2_gealpha_a1.is_open())
	{
		outfile__array_neurongroup_2_gealpha_a1.write(reinterpret_cast<char*>(_array_neurongroup_2_gealpha_a1), 109*sizeof(_array_neurongroup_2_gealpha_a1[0]));
		outfile__array_neurongroup_2_gealpha_a1.close();
	} else
	{
		std::cout << "Error writing output file for _array_neurongroup_2_gealpha_a1." << endl;
	}
	ofstream outfile__array_neurongroup_2_gealpha_a2;
	outfile__array_neurongroup_2_gealpha_a2.open("results\\_array_neurongroup_2_gealpha_a2_-5510422594159967293", ios::binary | ios::out);
	if(outfile__array_neurongroup_2_gealpha_a2.is_open())
	{
		outfile__array_neurongroup_2_gealpha_a2.write(reinterpret_cast<char*>(_array_neurongroup_2_gealpha_a2), 109*sizeof(_array_neurongroup_2_gealpha_a2[0]));
		outfile__array_neurongroup_2_gealpha_a2.close();
	} else
	{
		std::cout << "Error writing output file for _array_neurongroup_2_gealpha_a2." << endl;
	}
	ofstream outfile__array_neurongroup_2_gealpha_basal;
	outfile__array_neurongroup_2_gealpha_basal.open("results\\_array_neurongroup_2_gealpha_basal_-1207330903917725742", ios::binary | ios::out);
	if(outfile__array_neurongroup_2_gealpha_basal.is_open())
	{
		outfile__array_neurongroup_2_gealpha_basal.write(reinterpret_cast<char*>(_array_neurongroup_2_gealpha_basal), 109*sizeof(_array_neurongroup_2_gealpha_basal[0]));
		outfile__array_neurongroup_2_gealpha_basal.close();
	} else
	{
		std::cout << "Error writing output file for _array_neurongroup_2_gealpha_basal." << endl;
	}
	ofstream outfile__array_neurongroup_2_gealpha_soma;
	outfile__array_neurongroup_2_gealpha_soma.open("results\\_array_neurongroup_2_gealpha_soma_-2779996106924288609", ios::binary | ios::out);
	if(outfile__array_neurongroup_2_gealpha_soma.is_open())
	{
		outfile__array_neurongroup_2_gealpha_soma.write(reinterpret_cast<char*>(_array_neurongroup_2_gealpha_soma), 109*sizeof(_array_neurongroup_2_gealpha_soma[0]));
		outfile__array_neurongroup_2_gealpha_soma.close();
	} else
	{
		std::cout << "Error writing output file for _array_neurongroup_2_gealpha_soma." << endl;
	}
	ofstream outfile__array_neurongroup_2_gi_a0;
	outfile__array_neurongroup_2_gi_a0.open("results\\_array_neurongroup_2_gi_a0_-4737059550465621280", ios::binary | ios::out);
	if(outfile__array_neurongroup_2_gi_a0.is_open())
	{
		outfile__array_neurongroup_2_gi_a0.write(reinterpret_cast<char*>(_array_neurongroup_2_gi_a0), 109*sizeof(_array_neurongroup_2_gi_a0[0]));
		outfile__array_neurongroup_2_gi_a0.close();
	} else
	{
		std::cout << "Error writing output file for _array_neurongroup_2_gi_a0." << endl;
	}
	ofstream outfile__array_neurongroup_2_gi_a1;
	outfile__array_neurongroup_2_gi_a1.open("results\\_array_neurongroup_2_gi_a1_7193043074208227448", ios::binary | ios::out);
	if(outfile__array_neurongroup_2_gi_a1.is_open())
	{
		outfile__array_neurongroup_2_gi_a1.write(reinterpret_cast<char*>(_array_neurongroup_2_gi_a1), 109*sizeof(_array_neurongroup_2_gi_a1[0]));
		outfile__array_neurongroup_2_gi_a1.close();
	} else
	{
		std::cout << "Error writing output file for _array_neurongroup_2_gi_a1." << endl;
	}
	ofstream outfile__array_neurongroup_2_gi_a2;
	outfile__array_neurongroup_2_gi_a2.open("results\\_array_neurongroup_2_gi_a2_3487780519656499816", ios::binary | ios::out);
	if(outfile__array_neurongroup_2_gi_a2.is_open())
	{
		outfile__array_neurongroup_2_gi_a2.write(reinterpret_cast<char*>(_array_neurongroup_2_gi_a2), 109*sizeof(_array_neurongroup_2_gi_a2[0]));
		outfile__array_neurongroup_2_gi_a2.close();
	} else
	{
		std::cout << "Error writing output file for _array_neurongroup_2_gi_a2." << endl;
	}
	ofstream outfile__array_neurongroup_2_gi_basal;
	outfile__array_neurongroup_2_gi_basal.open("results\\_array_neurongroup_2_gi_basal_5142467606852698620", ios::binary | ios::out);
	if(outfile__array_neurongroup_2_gi_basal.is_open())
	{
		outfile__array_neurongroup_2_gi_basal.write(reinterpret_cast<char*>(_array_neurongroup_2_gi_basal), 109*sizeof(_array_neurongroup_2_gi_basal[0]));
		outfile__array_neurongroup_2_gi_basal.close();
	} else
	{
		std::cout << "Error writing output file for _array_neurongroup_2_gi_basal." << endl;
	}
	ofstream outfile__array_neurongroup_2_gi_soma;
	outfile__array_neurongroup_2_gi_soma.open("results\\_array_neurongroup_2_gi_soma_7815538421956194027", ios::binary | ios::out);
	if(outfile__array_neurongroup_2_gi_soma.is_open())
	{
		outfile__array_neurongroup_2_gi_soma.write(reinterpret_cast<char*>(_array_neurongroup_2_gi_soma), 109*sizeof(_array_neurongroup_2_gi_soma[0]));
		outfile__array_neurongroup_2_gi_soma.close();
	} else
	{
		std::cout << "Error writing output file for _array_neurongroup_2_gi_soma." << endl;
	}
	ofstream outfile__array_neurongroup_2_gialpha_a0;
	outfile__array_neurongroup_2_gialpha_a0.open("results\\_array_neurongroup_2_gialpha_a0_1146825612951050898", ios::binary | ios::out);
	if(outfile__array_neurongroup_2_gialpha_a0.is_open())
	{
		outfile__array_neurongroup_2_gialpha_a0.write(reinterpret_cast<char*>(_array_neurongroup_2_gialpha_a0), 109*sizeof(_array_neurongroup_2_gialpha_a0[0]));
		outfile__array_neurongroup_2_gialpha_a0.close();
	} else
	{
		std::cout << "Error writing output file for _array_neurongroup_2_gialpha_a0." << endl;
	}
	ofstream outfile__array_neurongroup_2_gialpha_a1;
	outfile__array_neurongroup_2_gialpha_a1.open("results\\_array_neurongroup_2_gialpha_a1_-443608993864152559", ios::binary | ios::out);
	if(outfile__array_neurongroup_2_gialpha_a1.is_open())
	{
		outfile__array_neurongroup_2_gialpha_a1.write(reinterpret_cast<char*>(_array_neurongroup_2_gialpha_a1), 109*sizeof(_array_neurongroup_2_gialpha_a1[0]));
		outfile__array_neurongroup_2_gialpha_a1.close();
	} else
	{
		std::cout << "Error writing output file for _array_neurongroup_2_gialpha_a1." << endl;
	}
	ofstream outfile__array_neurongroup_2_gialpha_a2;
	outfile__array_neurongroup_2_gialpha_a2.open("results\\_array_neurongroup_2_gialpha_a2_-3482639614407330293", ios::binary | ios::out);
	if(outfile__array_neurongroup_2_gialpha_a2.is_open())
	{
		outfile__array_neurongroup_2_gialpha_a2.write(reinterpret_cast<char*>(_array_neurongroup_2_gialpha_a2), 109*sizeof(_array_neurongroup_2_gialpha_a2[0]));
		outfile__array_neurongroup_2_gialpha_a2.close();
	} else
	{
		std::cout << "Error writing output file for _array_neurongroup_2_gialpha_a2." << endl;
	}
	ofstream outfile__array_neurongroup_2_gialpha_basal;
	outfile__array_neurongroup_2_gialpha_basal.open("results\\_array_neurongroup_2_gialpha_basal_4173419968226709990", ios::binary | ios::out);
	if(outfile__array_neurongroup_2_gialpha_basal.is_open())
	{
		outfile__array_neurongroup_2_gialpha_basal.write(reinterpret_cast<char*>(_array_neurongroup_2_gialpha_basal), 109*sizeof(_array_neurongroup_2_gialpha_basal[0]));
		outfile__array_neurongroup_2_gialpha_basal.close();
	} else
	{
		std::cout << "Error writing output file for _array_neurongroup_2_gialpha_basal." << endl;
	}
	ofstream outfile__array_neurongroup_2_gialpha_soma;
	outfile__array_neurongroup_2_gialpha_soma.open("results\\_array_neurongroup_2_gialpha_soma_7244806031912408720", ios::binary | ios::out);
	if(outfile__array_neurongroup_2_gialpha_soma.is_open())
	{
		outfile__array_neurongroup_2_gialpha_soma.write(reinterpret_cast<char*>(_array_neurongroup_2_gialpha_soma), 109*sizeof(_array_neurongroup_2_gialpha_soma[0]));
		outfile__array_neurongroup_2_gialpha_soma.close();
	} else
	{
		std::cout << "Error writing output file for _array_neurongroup_2_gialpha_soma." << endl;
	}
	ofstream outfile__array_neurongroup_2_i;
	outfile__array_neurongroup_2_i.open("results\\_array_neurongroup_2_i_8478582440569619327", ios::binary | ios::out);
	if(outfile__array_neurongroup_2_i.is_open())
	{
		outfile__array_neurongroup_2_i.write(reinterpret_cast<char*>(_array_neurongroup_2_i), 109*sizeof(_array_neurongroup_2_i[0]));
		outfile__array_neurongroup_2_i.close();
	} else
	{
		std::cout << "Error writing output file for _array_neurongroup_2_i." << endl;
	}
	ofstream outfile__array_neurongroup_2_lastspike;
	outfile__array_neurongroup_2_lastspike.open("results\\_array_neurongroup_2_lastspike_-1548786906493206515", ios::binary | ios::out);
	if(outfile__array_neurongroup_2_lastspike.is_open())
	{
		outfile__array_neurongroup_2_lastspike.write(reinterpret_cast<char*>(_array_neurongroup_2_lastspike), 109*sizeof(_array_neurongroup_2_lastspike[0]));
		outfile__array_neurongroup_2_lastspike.close();
	} else
	{
		std::cout << "Error writing output file for _array_neurongroup_2_lastspike." << endl;
	}
	ofstream outfile__array_neurongroup_2_not_refractory;
	outfile__array_neurongroup_2_not_refractory.open("results\\_array_neurongroup_2_not_refractory_-4397089012682701968", ios::binary | ios::out);
	if(outfile__array_neurongroup_2_not_refractory.is_open())
	{
		outfile__array_neurongroup_2_not_refractory.write(reinterpret_cast<char*>(_array_neurongroup_2_not_refractory), 109*sizeof(_array_neurongroup_2_not_refractory[0]));
		outfile__array_neurongroup_2_not_refractory.close();
	} else
	{
		std::cout << "Error writing output file for _array_neurongroup_2_not_refractory." << endl;
	}
	ofstream outfile__array_neurongroup_2_vm;
	outfile__array_neurongroup_2_vm.open("results\\_array_neurongroup_2_vm_6756730272439515399", ios::binary | ios::out);
	if(outfile__array_neurongroup_2_vm.is_open())
	{
		outfile__array_neurongroup_2_vm.write(reinterpret_cast<char*>(_array_neurongroup_2_vm), 109*sizeof(_array_neurongroup_2_vm[0]));
		outfile__array_neurongroup_2_vm.close();
	} else
	{
		std::cout << "Error writing output file for _array_neurongroup_2_vm." << endl;
	}
	ofstream outfile__array_neurongroup_2_vm_a0;
	outfile__array_neurongroup_2_vm_a0.open("results\\_array_neurongroup_2_vm_a0_-8876097029043257991", ios::binary | ios::out);
	if(outfile__array_neurongroup_2_vm_a0.is_open())
	{
		outfile__array_neurongroup_2_vm_a0.write(reinterpret_cast<char*>(_array_neurongroup_2_vm_a0), 109*sizeof(_array_neurongroup_2_vm_a0[0]));
		outfile__array_neurongroup_2_vm_a0.close();
	} else
	{
		std::cout << "Error writing output file for _array_neurongroup_2_vm_a0." << endl;
	}
	ofstream outfile__array_neurongroup_2_vm_a1;
	outfile__array_neurongroup_2_vm_a1.open("results\\_array_neurongroup_2_vm_a1_-2369620818127222594", ios::binary | ios::out);
	if(outfile__array_neurongroup_2_vm_a1.is_open())
	{
		outfile__array_neurongroup_2_vm_a1.write(reinterpret_cast<char*>(_array_neurongroup_2_vm_a1), 109*sizeof(_array_neurongroup_2_vm_a1[0]));
		outfile__array_neurongroup_2_vm_a1.close();
	} else
	{
		std::cout << "Error writing output file for _array_neurongroup_2_vm_a1." << endl;
	}
	ofstream outfile__array_neurongroup_2_vm_a2;
	outfile__array_neurongroup_2_vm_a2.open("results\\_array_neurongroup_2_vm_a2_3964307727054609900", ios::binary | ios::out);
	if(outfile__array_neurongroup_2_vm_a2.is_open())
	{
		outfile__array_neurongroup_2_vm_a2.write(reinterpret_cast<char*>(_array_neurongroup_2_vm_a2), 109*sizeof(_array_neurongroup_2_vm_a2[0]));
		outfile__array_neurongroup_2_vm_a2.close();
	} else
	{
		std::cout << "Error writing output file for _array_neurongroup_2_vm_a2." << endl;
	}
	ofstream outfile__array_neurongroup_2_vm_basal;
	outfile__array_neurongroup_2_vm_basal.open("results\\_array_neurongroup_2_vm_basal_3246167377535256014", ios::binary | ios::out);
	if(outfile__array_neurongroup_2_vm_basal.is_open())
	{
		outfile__array_neurongroup_2_vm_basal.write(reinterpret_cast<char*>(_array_neurongroup_2_vm_basal), 109*sizeof(_array_neurongroup_2_vm_basal[0]));
		outfile__array_neurongroup_2_vm_basal.close();
	} else
	{
		std::cout << "Error writing output file for _array_neurongroup_2_vm_basal." << endl;
	}
	ofstream outfile__array_neurongroup_2_x;
	outfile__array_neurongroup_2_x.open("results\\_array_neurongroup_2_x_-6222789293406877882", ios::binary | ios::out);
	if(outfile__array_neurongroup_2_x.is_open())
	{
		outfile__array_neurongroup_2_x.write(reinterpret_cast<char*>(_array_neurongroup_2_x), 109*sizeof(_array_neurongroup_2_x[0]));
		outfile__array_neurongroup_2_x.close();
	} else
	{
		std::cout << "Error writing output file for _array_neurongroup_2_x." << endl;
	}
	ofstream outfile__array_neurongroup_2_y;
	outfile__array_neurongroup_2_y.open("results\\_array_neurongroup_2_y_-1777504077900867358", ios::binary | ios::out);
	if(outfile__array_neurongroup_2_y.is_open())
	{
		outfile__array_neurongroup_2_y.write(reinterpret_cast<char*>(_array_neurongroup_2_y), 109*sizeof(_array_neurongroup_2_y[0]));
		outfile__array_neurongroup_2_y.close();
	} else
	{
		std::cout << "Error writing output file for _array_neurongroup_2_y." << endl;
	}
	ofstream outfile__array_neurongroup_3__spikespace;
	outfile__array_neurongroup_3__spikespace.open("results\\_array_neurongroup_3__spikespace_2333756082837416995", ios::binary | ios::out);
	if(outfile__array_neurongroup_3__spikespace.is_open())
	{
		outfile__array_neurongroup_3__spikespace.write(reinterpret_cast<char*>(_array_neurongroup_3__spikespace), 41*sizeof(_array_neurongroup_3__spikespace[0]));
		outfile__array_neurongroup_3__spikespace.close();
	} else
	{
		std::cout << "Error writing output file for _array_neurongroup_3__spikespace." << endl;
	}
	ofstream outfile__array_neurongroup_3_ge_soma;
	outfile__array_neurongroup_3_ge_soma.open("results\\_array_neurongroup_3_ge_soma_-460269630824058952", ios::binary | ios::out);
	if(outfile__array_neurongroup_3_ge_soma.is_open())
	{
		outfile__array_neurongroup_3_ge_soma.write(reinterpret_cast<char*>(_array_neurongroup_3_ge_soma), 40*sizeof(_array_neurongroup_3_ge_soma[0]));
		outfile__array_neurongroup_3_ge_soma.close();
	} else
	{
		std::cout << "Error writing output file for _array_neurongroup_3_ge_soma." << endl;
	}
	ofstream outfile__array_neurongroup_3_gi_soma;
	outfile__array_neurongroup_3_gi_soma.open("results\\_array_neurongroup_3_gi_soma_7952049431296405874", ios::binary | ios::out);
	if(outfile__array_neurongroup_3_gi_soma.is_open())
	{
		outfile__array_neurongroup_3_gi_soma.write(reinterpret_cast<char*>(_array_neurongroup_3_gi_soma), 40*sizeof(_array_neurongroup_3_gi_soma[0]));
		outfile__array_neurongroup_3_gi_soma.close();
	} else
	{
		std::cout << "Error writing output file for _array_neurongroup_3_gi_soma." << endl;
	}
	ofstream outfile__array_neurongroup_3_i;
	outfile__array_neurongroup_3_i.open("results\\_array_neurongroup_3_i_-3323581507541901766", ios::binary | ios::out);
	if(outfile__array_neurongroup_3_i.is_open())
	{
		outfile__array_neurongroup_3_i.write(reinterpret_cast<char*>(_array_neurongroup_3_i), 40*sizeof(_array_neurongroup_3_i[0]));
		outfile__array_neurongroup_3_i.close();
	} else
	{
		std::cout << "Error writing output file for _array_neurongroup_3_i." << endl;
	}
	ofstream outfile__array_neurongroup_3_lastspike;
	outfile__array_neurongroup_3_lastspike.open("results\\_array_neurongroup_3_lastspike_-4468790755256783597", ios::binary | ios::out);
	if(outfile__array_neurongroup_3_lastspike.is_open())
	{
		outfile__array_neurongroup_3_lastspike.write(reinterpret_cast<char*>(_array_neurongroup_3_lastspike), 40*sizeof(_array_neurongroup_3_lastspike[0]));
		outfile__array_neurongroup_3_lastspike.close();
	} else
	{
		std::cout << "Error writing output file for _array_neurongroup_3_lastspike." << endl;
	}
	ofstream outfile__array_neurongroup_3_not_refractory;
	outfile__array_neurongroup_3_not_refractory.open("results\\_array_neurongroup_3_not_refractory_5784905520108590072", ios::binary | ios::out);
	if(outfile__array_neurongroup_3_not_refractory.is_open())
	{
		outfile__array_neurongroup_3_not_refractory.write(reinterpret_cast<char*>(_array_neurongroup_3_not_refractory), 40*sizeof(_array_neurongroup_3_not_refractory[0]));
		outfile__array_neurongroup_3_not_refractory.close();
	} else
	{
		std::cout << "Error writing output file for _array_neurongroup_3_not_refractory." << endl;
	}
	ofstream outfile__array_neurongroup_3_vm;
	outfile__array_neurongroup_3_vm.open("results\\_array_neurongroup_3_vm_928617712007475184", ios::binary | ios::out);
	if(outfile__array_neurongroup_3_vm.is_open())
	{
		outfile__array_neurongroup_3_vm.write(reinterpret_cast<char*>(_array_neurongroup_3_vm), 40*sizeof(_array_neurongroup_3_vm[0]));
		outfile__array_neurongroup_3_vm.close();
	} else
	{
		std::cout << "Error writing output file for _array_neurongroup_3_vm." << endl;
	}
	ofstream outfile__array_neurongroup_3_x;
	outfile__array_neurongroup_3_x.open("results\\_array_neurongroup_3_x_-7927672638932793739", ios::binary | ios::out);
	if(outfile__array_neurongroup_3_x.is_open())
	{
		outfile__array_neurongroup_3_x.write(reinterpret_cast<char*>(_array_neurongroup_3_x), 40*sizeof(_array_neurongroup_3_x[0]));
		outfile__array_neurongroup_3_x.close();
	} else
	{
		std::cout << "Error writing output file for _array_neurongroup_3_x." << endl;
	}
	ofstream outfile__array_neurongroup_3_y;
	outfile__array_neurongroup_3_y.open("results\\_array_neurongroup_3_y_-4362469678534335947", ios::binary | ios::out);
	if(outfile__array_neurongroup_3_y.is_open())
	{
		outfile__array_neurongroup_3_y.write(reinterpret_cast<char*>(_array_neurongroup_3_y), 40*sizeof(_array_neurongroup_3_y[0]));
		outfile__array_neurongroup_3_y.close();
	} else
	{
		std::cout << "Error writing output file for _array_neurongroup_3_y." << endl;
	}
	ofstream outfile__array_neurongroup_4__spikespace;
	outfile__array_neurongroup_4__spikespace.open("results\\_array_neurongroup_4__spikespace_75850709626131747", ios::binary | ios::out);
	if(outfile__array_neurongroup_4__spikespace.is_open())
	{
		outfile__array_neurongroup_4__spikespace.write(reinterpret_cast<char*>(_array_neurongroup_4__spikespace), 33*sizeof(_array_neurongroup_4__spikespace[0]));
		outfile__array_neurongroup_4__spikespace.close();
	} else
	{
		std::cout << "Error writing output file for _array_neurongroup_4__spikespace." << endl;
	}
	ofstream outfile__array_neurongroup_4_ge_soma;
	outfile__array_neurongroup_4_ge_soma.open("results\\_array_neurongroup_4_ge_soma_-3891579814041513260", ios::binary | ios::out);
	if(outfile__array_neurongroup_4_ge_soma.is_open())
	{
		outfile__array_neurongroup_4_ge_soma.write(reinterpret_cast<char*>(_array_neurongroup_4_ge_soma), 32*sizeof(_array_neurongroup_4_ge_soma[0]));
		outfile__array_neurongroup_4_ge_soma.close();
	} else
	{
		std::cout << "Error writing output file for _array_neurongroup_4_ge_soma." << endl;
	}
	ofstream outfile__array_neurongroup_4_gi_soma;
	outfile__array_neurongroup_4_gi_soma.open("results\\_array_neurongroup_4_gi_soma_7904364754583756197", ios::binary | ios::out);
	if(outfile__array_neurongroup_4_gi_soma.is_open())
	{
		outfile__array_neurongroup_4_gi_soma.write(reinterpret_cast<char*>(_array_neurongroup_4_gi_soma), 32*sizeof(_array_neurongroup_4_gi_soma[0]));
		outfile__array_neurongroup_4_gi_soma.close();
	} else
	{
		std::cout << "Error writing output file for _array_neurongroup_4_gi_soma." << endl;
	}
	ofstream outfile__array_neurongroup_4_i;
	outfile__array_neurongroup_4_i.open("results\\_array_neurongroup_4_i_-2647176943468620875", ios::binary | ios::out);
	if(outfile__array_neurongroup_4_i.is_open())
	{
		outfile__array_neurongroup_4_i.write(reinterpret_cast<char*>(_array_neurongroup_4_i), 32*sizeof(_array_neurongroup_4_i[0]));
		outfile__array_neurongroup_4_i.close();
	} else
	{
		std::cout << "Error writing output file for _array_neurongroup_4_i." << endl;
	}
	ofstream outfile__array_neurongroup_4_lastspike;
	outfile__array_neurongroup_4_lastspike.open("results\\_array_neurongroup_4_lastspike_-3922743056926992174", ios::binary | ios::out);
	if(outfile__array_neurongroup_4_lastspike.is_open())
	{
		outfile__array_neurongroup_4_lastspike.write(reinterpret_cast<char*>(_array_neurongroup_4_lastspike), 32*sizeof(_array_neurongroup_4_lastspike[0]));
		outfile__array_neurongroup_4_lastspike.close();
	} else
	{
		std::cout << "Error writing output file for _array_neurongroup_4_lastspike." << endl;
	}
	ofstream outfile__array_neurongroup_4_not_refractory;
	outfile__array_neurongroup_4_not_refractory.open("results\\_array_neurongroup_4_not_refractory_-1310297816773682507", ios::binary | ios::out);
	if(outfile__array_neurongroup_4_not_refractory.is_open())
	{
		outfile__array_neurongroup_4_not_refractory.write(reinterpret_cast<char*>(_array_neurongroup_4_not_refractory), 32*sizeof(_array_neurongroup_4_not_refractory[0]));
		outfile__array_neurongroup_4_not_refractory.close();
	} else
	{
		std::cout << "Error writing output file for _array_neurongroup_4_not_refractory." << endl;
	}
	ofstream outfile__array_neurongroup_4_vm;
	outfile__array_neurongroup_4_vm.open("results\\_array_neurongroup_4_vm_-1760418928366236949", ios::binary | ios::out);
	if(outfile__array_neurongroup_4_vm.is_open())
	{
		outfile__array_neurongroup_4_vm.write(reinterpret_cast<char*>(_array_neurongroup_4_vm), 32*sizeof(_array_neurongroup_4_vm[0]));
		outfile__array_neurongroup_4_vm.close();
	} else
	{
		std::cout << "Error writing output file for _array_neurongroup_4_vm." << endl;
	}
	ofstream outfile__array_neurongroup_4_x;
	outfile__array_neurongroup_4_x.open("results\\_array_neurongroup_4_x_-4705747379041897310", ios::binary | ios::out);
	if(outfile__array_neurongroup_4_x.is_open())
	{
		outfile__array_neurongroup_4_x.write(reinterpret_cast<char*>(_array_neurongroup_4_x), 32*sizeof(_array_neurongroup_4_x[0]));
		outfile__array_neurongroup_4_x.close();
	} else
	{
		std::cout << "Error writing output file for _array_neurongroup_4_x." << endl;
	}
	ofstream outfile__array_neurongroup_4_y;
	outfile__array_neurongroup_4_y.open("results\\_array_neurongroup_4_y_1870386463338211984", ios::binary | ios::out);
	if(outfile__array_neurongroup_4_y.is_open())
	{
		outfile__array_neurongroup_4_y.write(reinterpret_cast<char*>(_array_neurongroup_4_y), 32*sizeof(_array_neurongroup_4_y[0]));
		outfile__array_neurongroup_4_y.close();
	} else
	{
		std::cout << "Error writing output file for _array_neurongroup_4_y." << endl;
	}
	ofstream outfile__array_neurongroup_5__spikespace;
	outfile__array_neurongroup_5__spikespace.open("results\\_array_neurongroup_5__spikespace_-5237732135961454294", ios::binary | ios::out);
	if(outfile__array_neurongroup_5__spikespace.is_open())
	{
		outfile__array_neurongroup_5__spikespace.write(reinterpret_cast<char*>(_array_neurongroup_5__spikespace), 14*sizeof(_array_neurongroup_5__spikespace[0]));
		outfile__array_neurongroup_5__spikespace.close();
	} else
	{
		std::cout << "Error writing output file for _array_neurongroup_5__spikespace." << endl;
	}
	ofstream outfile__array_neurongroup_5_ge_soma;
	outfile__array_neurongroup_5_ge_soma.open("results\\_array_neurongroup_5_ge_soma_-4222041300425398686", ios::binary | ios::out);
	if(outfile__array_neurongroup_5_ge_soma.is_open())
	{
		outfile__array_neurongroup_5_ge_soma.write(reinterpret_cast<char*>(_array_neurongroup_5_ge_soma), 13*sizeof(_array_neurongroup_5_ge_soma[0]));
		outfile__array_neurongroup_5_ge_soma.close();
	} else
	{
		std::cout << "Error writing output file for _array_neurongroup_5_ge_soma." << endl;
	}
	ofstream outfile__array_neurongroup_5_gi_soma;
	outfile__array_neurongroup_5_gi_soma.open("results\\_array_neurongroup_5_gi_soma_-6573390215539688431", ios::binary | ios::out);
	if(outfile__array_neurongroup_5_gi_soma.is_open())
	{
		outfile__array_neurongroup_5_gi_soma.write(reinterpret_cast<char*>(_array_neurongroup_5_gi_soma), 13*sizeof(_array_neurongroup_5_gi_soma[0]));
		outfile__array_neurongroup_5_gi_soma.close();
	} else
	{
		std::cout << "Error writing output file for _array_neurongroup_5_gi_soma." << endl;
	}
	ofstream outfile__array_neurongroup_5_i;
	outfile__array_neurongroup_5_i.open("results\\_array_neurongroup_5_i_-1170009839770144768", ios::binary | ios::out);
	if(outfile__array_neurongroup_5_i.is_open())
	{
		outfile__array_neurongroup_5_i.write(reinterpret_cast<char*>(_array_neurongroup_5_i), 13*sizeof(_array_neurongroup_5_i[0]));
		outfile__array_neurongroup_5_i.close();
	} else
	{
		std::cout << "Error writing output file for _array_neurongroup_5_i." << endl;
	}
	ofstream outfile__array_neurongroup_5_lastspike;
	outfile__array_neurongroup_5_lastspike.open("results\\_array_neurongroup_5_lastspike_-890156880031410422", ios::binary | ios::out);
	if(outfile__array_neurongroup_5_lastspike.is_open())
	{
		outfile__array_neurongroup_5_lastspike.write(reinterpret_cast<char*>(_array_neurongroup_5_lastspike), 13*sizeof(_array_neurongroup_5_lastspike[0]));
		outfile__array_neurongroup_5_lastspike.close();
	} else
	{
		std::cout << "Error writing output file for _array_neurongroup_5_lastspike." << endl;
	}
	ofstream outfile__array_neurongroup_5_not_refractory;
	outfile__array_neurongroup_5_not_refractory.open("results\\_array_neurongroup_5_not_refractory_5155384943948151282", ios::binary | ios::out);
	if(outfile__array_neurongroup_5_not_refractory.is_open())
	{
		outfile__array_neurongroup_5_not_refractory.write(reinterpret_cast<char*>(_array_neurongroup_5_not_refractory), 13*sizeof(_array_neurongroup_5_not_refractory[0]));
		outfile__array_neurongroup_5_not_refractory.close();
	} else
	{
		std::cout << "Error writing output file for _array_neurongroup_5_not_refractory." << endl;
	}
	ofstream outfile__array_neurongroup_5_vm;
	outfile__array_neurongroup_5_vm.open("results\\_array_neurongroup_5_vm_-4709939029324874066", ios::binary | ios::out);
	if(outfile__array_neurongroup_5_vm.is_open())
	{
		outfile__array_neurongroup_5_vm.write(reinterpret_cast<char*>(_array_neurongroup_5_vm), 13*sizeof(_array_neurongroup_5_vm[0]));
		outfile__array_neurongroup_5_vm.close();
	} else
	{
		std::cout << "Error writing output file for _array_neurongroup_5_vm." << endl;
	}
	ofstream outfile__array_neurongroup_5_x;
	outfile__array_neurongroup_5_x.open("results\\_array_neurongroup_5_x_-8780593944062406671", ios::binary | ios::out);
	if(outfile__array_neurongroup_5_x.is_open())
	{
		outfile__array_neurongroup_5_x.write(reinterpret_cast<char*>(_array_neurongroup_5_x), 13*sizeof(_array_neurongroup_5_x[0]));
		outfile__array_neurongroup_5_x.close();
	} else
	{
		std::cout << "Error writing output file for _array_neurongroup_5_x." << endl;
	}
	ofstream outfile__array_neurongroup_5_y;
	outfile__array_neurongroup_5_y.open("results\\_array_neurongroup_5_y_-8766890858410809859", ios::binary | ios::out);
	if(outfile__array_neurongroup_5_y.is_open())
	{
		outfile__array_neurongroup_5_y.write(reinterpret_cast<char*>(_array_neurongroup_5_y), 13*sizeof(_array_neurongroup_5_y[0]));
		outfile__array_neurongroup_5_y.close();
	} else
	{
		std::cout << "Error writing output file for _array_neurongroup_5_y." << endl;
	}
	ofstream outfile__array_neurongroup__spikespace;
	outfile__array_neurongroup__spikespace.open("results\\_array_neurongroup__spikespace_-7985567967029060029", ios::binary | ios::out);
	if(outfile__array_neurongroup__spikespace.is_open())
	{
		outfile__array_neurongroup__spikespace.write(reinterpret_cast<char*>(_array_neurongroup__spikespace), 61*sizeof(_array_neurongroup__spikespace[0]));
		outfile__array_neurongroup__spikespace.close();
	} else
	{
		std::cout << "Error writing output file for _array_neurongroup__spikespace." << endl;
	}
	ofstream outfile__array_neurongroup_emit_spike;
	outfile__array_neurongroup_emit_spike.open("results\\_array_neurongroup_emit_spike_1992101945329156208", ios::binary | ios::out);
	if(outfile__array_neurongroup_emit_spike.is_open())
	{
		outfile__array_neurongroup_emit_spike.write(reinterpret_cast<char*>(_array_neurongroup_emit_spike), 60*sizeof(_array_neurongroup_emit_spike[0]));
		outfile__array_neurongroup_emit_spike.close();
	} else
	{
		std::cout << "Error writing output file for _array_neurongroup_emit_spike." << endl;
	}
	ofstream outfile__array_neurongroup_i;
	outfile__array_neurongroup_i.open("results\\_array_neurongroup_i_8510146991507224961", ios::binary | ios::out);
	if(outfile__array_neurongroup_i.is_open())
	{
		outfile__array_neurongroup_i.write(reinterpret_cast<char*>(_array_neurongroup_i), 60*sizeof(_array_neurongroup_i[0]));
		outfile__array_neurongroup_i.close();
	} else
	{
		std::cout << "Error writing output file for _array_neurongroup_i." << endl;
	}
	ofstream outfile__array_neurongroup_x;
	outfile__array_neurongroup_x.open("results\\_array_neurongroup_x_3704152947998157525", ios::binary | ios::out);
	if(outfile__array_neurongroup_x.is_open())
	{
		outfile__array_neurongroup_x.write(reinterpret_cast<char*>(_array_neurongroup_x), 60*sizeof(_array_neurongroup_x[0]));
		outfile__array_neurongroup_x.close();
	} else
	{
		std::cout << "Error writing output file for _array_neurongroup_x." << endl;
	}
	ofstream outfile__array_neurongroup_y;
	outfile__array_neurongroup_y.open("results\\_array_neurongroup_y_1294601131724742687", ios::binary | ios::out);
	if(outfile__array_neurongroup_y.is_open())
	{
		outfile__array_neurongroup_y.write(reinterpret_cast<char*>(_array_neurongroup_y), 60*sizeof(_array_neurongroup_y[0]));
		outfile__array_neurongroup_y.close();
	} else
	{
		std::cout << "Error writing output file for _array_neurongroup_y." << endl;
	}
	ofstream outfile__array_spikegeneratorgroup__lastindex;
	outfile__array_spikegeneratorgroup__lastindex.open("results\\_array_spikegeneratorgroup__lastindex_-7151917947645849296", ios::binary | ios::out);
	if(outfile__array_spikegeneratorgroup__lastindex.is_open())
	{
		outfile__array_spikegeneratorgroup__lastindex.write(reinterpret_cast<char*>(_array_spikegeneratorgroup__lastindex), 1*sizeof(_array_spikegeneratorgroup__lastindex[0]));
		outfile__array_spikegeneratorgroup__lastindex.close();
	} else
	{
		std::cout << "Error writing output file for _array_spikegeneratorgroup__lastindex." << endl;
	}
	ofstream outfile__array_spikegeneratorgroup__period_bins;
	outfile__array_spikegeneratorgroup__period_bins.open("results\\_array_spikegeneratorgroup__period_bins_-6998934688322105576", ios::binary | ios::out);
	if(outfile__array_spikegeneratorgroup__period_bins.is_open())
	{
		outfile__array_spikegeneratorgroup__period_bins.write(reinterpret_cast<char*>(_array_spikegeneratorgroup__period_bins), 1*sizeof(_array_spikegeneratorgroup__period_bins[0]));
		outfile__array_spikegeneratorgroup__period_bins.close();
	} else
	{
		std::cout << "Error writing output file for _array_spikegeneratorgroup__period_bins." << endl;
	}
	ofstream outfile__array_spikegeneratorgroup__spikespace;
	outfile__array_spikegeneratorgroup__spikespace.open("results\\_array_spikegeneratorgroup__spikespace_-7684492526146061142", ios::binary | ios::out);
	if(outfile__array_spikegeneratorgroup__spikespace.is_open())
	{
		outfile__array_spikegeneratorgroup__spikespace.write(reinterpret_cast<char*>(_array_spikegeneratorgroup__spikespace), 61*sizeof(_array_spikegeneratorgroup__spikespace[0]));
		outfile__array_spikegeneratorgroup__spikespace.close();
	} else
	{
		std::cout << "Error writing output file for _array_spikegeneratorgroup__spikespace." << endl;
	}
	ofstream outfile__array_spikegeneratorgroup_i;
	outfile__array_spikegeneratorgroup_i.open("results\\_array_spikegeneratorgroup_i_5029652107432470427", ios::binary | ios::out);
	if(outfile__array_spikegeneratorgroup_i.is_open())
	{
		outfile__array_spikegeneratorgroup_i.write(reinterpret_cast<char*>(_array_spikegeneratorgroup_i), 60*sizeof(_array_spikegeneratorgroup_i[0]));
		outfile__array_spikegeneratorgroup_i.close();
	} else
	{
		std::cout << "Error writing output file for _array_spikegeneratorgroup_i." << endl;
	}
	ofstream outfile__array_spikegeneratorgroup_period;
	outfile__array_spikegeneratorgroup_period.open("results\\_array_spikegeneratorgroup_period_-5607261807773511589", ios::binary | ios::out);
	if(outfile__array_spikegeneratorgroup_period.is_open())
	{
		outfile__array_spikegeneratorgroup_period.write(reinterpret_cast<char*>(_array_spikegeneratorgroup_period), 1*sizeof(_array_spikegeneratorgroup_period[0]));
		outfile__array_spikegeneratorgroup_period.close();
	} else
	{
		std::cout << "Error writing output file for _array_spikegeneratorgroup_period." << endl;
	}
	ofstream outfile__array_spikemonitor_1__source_idx;
	outfile__array_spikemonitor_1__source_idx.open("results\\_array_spikemonitor_1__source_idx_6385773202534406217", ios::binary | ios::out);
	if(outfile__array_spikemonitor_1__source_idx.is_open())
	{
		outfile__array_spikemonitor_1__source_idx.write(reinterpret_cast<char*>(_array_spikemonitor_1__source_idx), 267*sizeof(_array_spikemonitor_1__source_idx[0]));
		outfile__array_spikemonitor_1__source_idx.close();
	} else
	{
		std::cout << "Error writing output file for _array_spikemonitor_1__source_idx." << endl;
	}
	ofstream outfile__array_spikemonitor_1_count;
	outfile__array_spikemonitor_1_count.open("results\\_array_spikemonitor_1_count_-5619752821046873161", ios::binary | ios::out);
	if(outfile__array_spikemonitor_1_count.is_open())
	{
		outfile__array_spikemonitor_1_count.write(reinterpret_cast<char*>(_array_spikemonitor_1_count), 267*sizeof(_array_spikemonitor_1_count[0]));
		outfile__array_spikemonitor_1_count.close();
	} else
	{
		std::cout << "Error writing output file for _array_spikemonitor_1_count." << endl;
	}
	ofstream outfile__array_spikemonitor_1_N;
	outfile__array_spikemonitor_1_N.open("results\\_array_spikemonitor_1_N_7809277910378706485", ios::binary | ios::out);
	if(outfile__array_spikemonitor_1_N.is_open())
	{
		outfile__array_spikemonitor_1_N.write(reinterpret_cast<char*>(_array_spikemonitor_1_N), 1*sizeof(_array_spikemonitor_1_N[0]));
		outfile__array_spikemonitor_1_N.close();
	} else
	{
		std::cout << "Error writing output file for _array_spikemonitor_1_N." << endl;
	}
	ofstream outfile__array_spikemonitor_2__source_idx;
	outfile__array_spikemonitor_2__source_idx.open("results\\_array_spikemonitor_2__source_idx_6320991018704751508", ios::binary | ios::out);
	if(outfile__array_spikemonitor_2__source_idx.is_open())
	{
		outfile__array_spikemonitor_2__source_idx.write(reinterpret_cast<char*>(_array_spikemonitor_2__source_idx), 109*sizeof(_array_spikemonitor_2__source_idx[0]));
		outfile__array_spikemonitor_2__source_idx.close();
	} else
	{
		std::cout << "Error writing output file for _array_spikemonitor_2__source_idx." << endl;
	}
	ofstream outfile__array_spikemonitor_2_count;
	outfile__array_spikemonitor_2_count.open("results\\_array_spikemonitor_2_count_-4604702824022812179", ios::binary | ios::out);
	if(outfile__array_spikemonitor_2_count.is_open())
	{
		outfile__array_spikemonitor_2_count.write(reinterpret_cast<char*>(_array_spikemonitor_2_count), 109*sizeof(_array_spikemonitor_2_count[0]));
		outfile__array_spikemonitor_2_count.close();
	} else
	{
		std::cout << "Error writing output file for _array_spikemonitor_2_count." << endl;
	}
	ofstream outfile__array_spikemonitor_2_N;
	outfile__array_spikemonitor_2_N.open("results\\_array_spikemonitor_2_N_-2815320330084250244", ios::binary | ios::out);
	if(outfile__array_spikemonitor_2_N.is_open())
	{
		outfile__array_spikemonitor_2_N.write(reinterpret_cast<char*>(_array_spikemonitor_2_N), 1*sizeof(_array_spikemonitor_2_N[0]));
		outfile__array_spikemonitor_2_N.close();
	} else
	{
		std::cout << "Error writing output file for _array_spikemonitor_2_N." << endl;
	}
	ofstream outfile__array_spikemonitor_3__source_idx;
	outfile__array_spikemonitor_3__source_idx.open("results\\_array_spikemonitor_3__source_idx_1559171939768179153", ios::binary | ios::out);
	if(outfile__array_spikemonitor_3__source_idx.is_open())
	{
		outfile__array_spikemonitor_3__source_idx.write(reinterpret_cast<char*>(_array_spikemonitor_3__source_idx), 40*sizeof(_array_spikemonitor_3__source_idx[0]));
		outfile__array_spikemonitor_3__source_idx.close();
	} else
	{
		std::cout << "Error writing output file for _array_spikemonitor_3__source_idx." << endl;
	}
	ofstream outfile__array_spikemonitor_3_count;
	outfile__array_spikemonitor_3_count.open("results\\_array_spikemonitor_3_count_-1006075607088432255", ios::binary | ios::out);
	if(outfile__array_spikemonitor_3_count.is_open())
	{
		outfile__array_spikemonitor_3_count.write(reinterpret_cast<char*>(_array_spikemonitor_3_count), 40*sizeof(_array_spikemonitor_3_count[0]));
		outfile__array_spikemonitor_3_count.close();
	} else
	{
		std::cout << "Error writing output file for _array_spikemonitor_3_count." << endl;
	}
	ofstream outfile__array_spikemonitor_3_N;
	outfile__array_spikemonitor_3_N.open("results\\_array_spikemonitor_3_N_-7656065102646607941", ios::binary | ios::out);
	if(outfile__array_spikemonitor_3_N.is_open())
	{
		outfile__array_spikemonitor_3_N.write(reinterpret_cast<char*>(_array_spikemonitor_3_N), 1*sizeof(_array_spikemonitor_3_N[0]));
		outfile__array_spikemonitor_3_N.close();
	} else
	{
		std::cout << "Error writing output file for _array_spikemonitor_3_N." << endl;
	}
	ofstream outfile__array_spikemonitor_4__source_idx;
	outfile__array_spikemonitor_4__source_idx.open("results\\_array_spikemonitor_4__source_idx_7465051260450829985", ios::binary | ios::out);
	if(outfile__array_spikemonitor_4__source_idx.is_open())
	{
		outfile__array_spikemonitor_4__source_idx.write(reinterpret_cast<char*>(_array_spikemonitor_4__source_idx), 32*sizeof(_array_spikemonitor_4__source_idx[0]));
		outfile__array_spikemonitor_4__source_idx.close();
	} else
	{
		std::cout << "Error writing output file for _array_spikemonitor_4__source_idx." << endl;
	}
	ofstream outfile__array_spikemonitor_4_count;
	outfile__array_spikemonitor_4_count.open("results\\_array_spikemonitor_4_count_-4790451547490478057", ios::binary | ios::out);
	if(outfile__array_spikemonitor_4_count.is_open())
	{
		outfile__array_spikemonitor_4_count.write(reinterpret_cast<char*>(_array_spikemonitor_4_count), 32*sizeof(_array_spikemonitor_4_count[0]));
		outfile__array_spikemonitor_4_count.close();
	} else
	{
		std::cout << "Error writing output file for _array_spikemonitor_4_count." << endl;
	}
	ofstream outfile__array_spikemonitor_4_N;
	outfile__array_spikemonitor_4_N.open("results\\_array_spikemonitor_4_N_-2281573846266654190", ios::binary | ios::out);
	if(outfile__array_spikemonitor_4_N.is_open())
	{
		outfile__array_spikemonitor_4_N.write(reinterpret_cast<char*>(_array_spikemonitor_4_N), 1*sizeof(_array_spikemonitor_4_N[0]));
		outfile__array_spikemonitor_4_N.close();
	} else
	{
		std::cout << "Error writing output file for _array_spikemonitor_4_N." << endl;
	}
	ofstream outfile__array_spikemonitor_5__source_idx;
	outfile__array_spikemonitor_5__source_idx.open("results\\_array_spikemonitor_5__source_idx_-4702842491357721440", ios::binary | ios::out);
	if(outfile__array_spikemonitor_5__source_idx.is_open())
	{
		outfile__array_spikemonitor_5__source_idx.write(reinterpret_cast<char*>(_array_spikemonitor_5__source_idx), 13*sizeof(_array_spikemonitor_5__source_idx[0]));
		outfile__array_spikemonitor_5__source_idx.close();
	} else
	{
		std::cout << "Error writing output file for _array_spikemonitor_5__source_idx." << endl;
	}
	ofstream outfile__array_spikemonitor_5_count;
	outfile__array_spikemonitor_5_count.open("results\\_array_spikemonitor_5_count_6684368429843708065", ios::binary | ios::out);
	if(outfile__array_spikemonitor_5_count.is_open())
	{
		outfile__array_spikemonitor_5_count.write(reinterpret_cast<char*>(_array_spikemonitor_5_count), 13*sizeof(_array_spikemonitor_5_count[0]));
		outfile__array_spikemonitor_5_count.close();
	} else
	{
		std::cout << "Error writing output file for _array_spikemonitor_5_count." << endl;
	}
	ofstream outfile__array_spikemonitor_5_N;
	outfile__array_spikemonitor_5_N.open("results\\_array_spikemonitor_5_N_8015654462372744336", ios::binary | ios::out);
	if(outfile__array_spikemonitor_5_N.is_open())
	{
		outfile__array_spikemonitor_5_N.write(reinterpret_cast<char*>(_array_spikemonitor_5_N), 1*sizeof(_array_spikemonitor_5_N[0]));
		outfile__array_spikemonitor_5_N.close();
	} else
	{
		std::cout << "Error writing output file for _array_spikemonitor_5_N." << endl;
	}
	ofstream outfile__array_spikemonitor__source_idx;
	outfile__array_spikemonitor__source_idx.open("results\\_array_spikemonitor__source_idx_-9131071501907561888", ios::binary | ios::out);
	if(outfile__array_spikemonitor__source_idx.is_open())
	{
		outfile__array_spikemonitor__source_idx.write(reinterpret_cast<char*>(_array_spikemonitor__source_idx), 60*sizeof(_array_spikemonitor__source_idx[0]));
		outfile__array_spikemonitor__source_idx.close();
	} else
	{
		std::cout << "Error writing output file for _array_spikemonitor__source_idx." << endl;
	}
	ofstream outfile__array_spikemonitor_count;
	outfile__array_spikemonitor_count.open("results\\_array_spikemonitor_count_5336304115422974898", ios::binary | ios::out);
	if(outfile__array_spikemonitor_count.is_open())
	{
		outfile__array_spikemonitor_count.write(reinterpret_cast<char*>(_array_spikemonitor_count), 60*sizeof(_array_spikemonitor_count[0]));
		outfile__array_spikemonitor_count.close();
	} else
	{
		std::cout << "Error writing output file for _array_spikemonitor_count." << endl;
	}
	ofstream outfile__array_spikemonitor_N;
	outfile__array_spikemonitor_N.open("results\\_array_spikemonitor_N_-4209999139093117962", ios::binary | ios::out);
	if(outfile__array_spikemonitor_N.is_open())
	{
		outfile__array_spikemonitor_N.write(reinterpret_cast<char*>(_array_spikemonitor_N), 1*sizeof(_array_spikemonitor_N[0]));
		outfile__array_spikemonitor_N.close();
	} else
	{
		std::cout << "Error writing output file for _array_spikemonitor_N." << endl;
	}
	ofstream outfile__array_synapses_10_N;
	outfile__array_synapses_10_N.open("results\\_array_synapses_10_N_-5896465797994953638", ios::binary | ios::out);
	if(outfile__array_synapses_10_N.is_open())
	{
		outfile__array_synapses_10_N.write(reinterpret_cast<char*>(_array_synapses_10_N), 1*sizeof(_array_synapses_10_N[0]));
		outfile__array_synapses_10_N.close();
	} else
	{
		std::cout << "Error writing output file for _array_synapses_10_N." << endl;
	}
	ofstream outfile__array_synapses_10_sources;
	outfile__array_synapses_10_sources.open("results\\_array_synapses_10_sources_-1758986204624103638", ios::binary | ios::out);
	if(outfile__array_synapses_10_sources.is_open())
	{
		outfile__array_synapses_10_sources.write(reinterpret_cast<char*>(_array_synapses_10_sources), 990*sizeof(_array_synapses_10_sources[0]));
		outfile__array_synapses_10_sources.close();
	} else
	{
		std::cout << "Error writing output file for _array_synapses_10_sources." << endl;
	}
	ofstream outfile__array_synapses_10_targets;
	outfile__array_synapses_10_targets.open("results\\_array_synapses_10_targets_729351282929028687", ios::binary | ios::out);
	if(outfile__array_synapses_10_targets.is_open())
	{
		outfile__array_synapses_10_targets.write(reinterpret_cast<char*>(_array_synapses_10_targets), 990*sizeof(_array_synapses_10_targets[0]));
		outfile__array_synapses_10_targets.close();
	} else
	{
		std::cout << "Error writing output file for _array_synapses_10_targets." << endl;
	}
	ofstream outfile__array_synapses_11_N;
	outfile__array_synapses_11_N.open("results\\_array_synapses_11_N_4796254809534137987", ios::binary | ios::out);
	if(outfile__array_synapses_11_N.is_open())
	{
		outfile__array_synapses_11_N.write(reinterpret_cast<char*>(_array_synapses_11_N), 1*sizeof(_array_synapses_11_N[0]));
		outfile__array_synapses_11_N.close();
	} else
	{
		std::cout << "Error writing output file for _array_synapses_11_N." << endl;
	}
	ofstream outfile__array_synapses_11_sources;
	outfile__array_synapses_11_sources.open("results\\_array_synapses_11_sources_-1854453750665734163", ios::binary | ios::out);
	if(outfile__array_synapses_11_sources.is_open())
	{
		outfile__array_synapses_11_sources.write(reinterpret_cast<char*>(_array_synapses_11_sources), 357*sizeof(_array_synapses_11_sources[0]));
		outfile__array_synapses_11_sources.close();
	} else
	{
		std::cout << "Error writing output file for _array_synapses_11_sources." << endl;
	}
	ofstream outfile__array_synapses_11_targets;
	outfile__array_synapses_11_targets.open("results\\_array_synapses_11_targets_-2127579854497547403", ios::binary | ios::out);
	if(outfile__array_synapses_11_targets.is_open())
	{
		outfile__array_synapses_11_targets.write(reinterpret_cast<char*>(_array_synapses_11_targets), 357*sizeof(_array_synapses_11_targets[0]));
		outfile__array_synapses_11_targets.close();
	} else
	{
		std::cout << "Error writing output file for _array_synapses_11_targets." << endl;
	}
	ofstream outfile__array_synapses_12_N;
	outfile__array_synapses_12_N.open("results\\_array_synapses_12_N_-2404467604695753778", ios::binary | ios::out);
	if(outfile__array_synapses_12_N.is_open())
	{
		outfile__array_synapses_12_N.write(reinterpret_cast<char*>(_array_synapses_12_N), 1*sizeof(_array_synapses_12_N[0]));
		outfile__array_synapses_12_N.close();
	} else
	{
		std::cout << "Error writing output file for _array_synapses_12_N." << endl;
	}
	ofstream outfile__array_synapses_12_sources;
	outfile__array_synapses_12_sources.open("results\\_array_synapses_12_sources_4488166564474064357", ios::binary | ios::out);
	if(outfile__array_synapses_12_sources.is_open())
	{
		outfile__array_synapses_12_sources.write(reinterpret_cast<char*>(_array_synapses_12_sources), 28*sizeof(_array_synapses_12_sources[0]));
		outfile__array_synapses_12_sources.close();
	} else
	{
		std::cout << "Error writing output file for _array_synapses_12_sources." << endl;
	}
	ofstream outfile__array_synapses_12_targets;
	outfile__array_synapses_12_targets.open("results\\_array_synapses_12_targets_-4406911051528152710", ios::binary | ios::out);
	if(outfile__array_synapses_12_targets.is_open())
	{
		outfile__array_synapses_12_targets.write(reinterpret_cast<char*>(_array_synapses_12_targets), 28*sizeof(_array_synapses_12_targets[0]));
		outfile__array_synapses_12_targets.close();
	} else
	{
		std::cout << "Error writing output file for _array_synapses_12_targets." << endl;
	}
	ofstream outfile__array_synapses_13_N;
	outfile__array_synapses_13_N.open("results\\_array_synapses_13_N_-165398585046270573", ios::binary | ios::out);
	if(outfile__array_synapses_13_N.is_open())
	{
		outfile__array_synapses_13_N.write(reinterpret_cast<char*>(_array_synapses_13_N), 1*sizeof(_array_synapses_13_N[0]));
		outfile__array_synapses_13_N.close();
	} else
	{
		std::cout << "Error writing output file for _array_synapses_13_N." << endl;
	}
	ofstream outfile__array_synapses_13_sources;
	outfile__array_synapses_13_sources.open("results\\_array_synapses_13_sources_8643494607536500026", ios::binary | ios::out);
	if(outfile__array_synapses_13_sources.is_open())
	{
		outfile__array_synapses_13_sources.write(reinterpret_cast<char*>(_array_synapses_13_sources), 45*sizeof(_array_synapses_13_sources[0]));
		outfile__array_synapses_13_sources.close();
	} else
	{
		std::cout << "Error writing output file for _array_synapses_13_sources." << endl;
	}
	ofstream outfile__array_synapses_13_targets;
	outfile__array_synapses_13_targets.open("results\\_array_synapses_13_targets_-1285824999002785015", ios::binary | ios::out);
	if(outfile__array_synapses_13_targets.is_open())
	{
		outfile__array_synapses_13_targets.write(reinterpret_cast<char*>(_array_synapses_13_targets), 45*sizeof(_array_synapses_13_targets[0]));
		outfile__array_synapses_13_targets.close();
	} else
	{
		std::cout << "Error writing output file for _array_synapses_13_targets." << endl;
	}
	ofstream outfile__array_synapses_14_N;
	outfile__array_synapses_14_N.open("results\\_array_synapses_14_N_2405391560037491507", ios::binary | ios::out);
	if(outfile__array_synapses_14_N.is_open())
	{
		outfile__array_synapses_14_N.write(reinterpret_cast<char*>(_array_synapses_14_N), 1*sizeof(_array_synapses_14_N[0]));
		outfile__array_synapses_14_N.close();
	} else
	{
		std::cout << "Error writing output file for _array_synapses_14_N." << endl;
	}
	ofstream outfile__array_synapses_14_sources;
	outfile__array_synapses_14_sources.open("results\\_array_synapses_14_sources_8389132913381864607", ios::binary | ios::out);
	if(outfile__array_synapses_14_sources.is_open())
	{
		outfile__array_synapses_14_sources.write(reinterpret_cast<char*>(_array_synapses_14_sources), 492*sizeof(_array_synapses_14_sources[0]));
		outfile__array_synapses_14_sources.close();
	} else
	{
		std::cout << "Error writing output file for _array_synapses_14_sources." << endl;
	}
	ofstream outfile__array_synapses_14_targets;
	outfile__array_synapses_14_targets.open("results\\_array_synapses_14_targets_-4225136969391658003", ios::binary | ios::out);
	if(outfile__array_synapses_14_targets.is_open())
	{
		outfile__array_synapses_14_targets.write(reinterpret_cast<char*>(_array_synapses_14_targets), 492*sizeof(_array_synapses_14_targets[0]));
		outfile__array_synapses_14_targets.close();
	} else
	{
		std::cout << "Error writing output file for _array_synapses_14_targets." << endl;
	}
	ofstream outfile__array_synapses_15_N;
	outfile__array_synapses_15_N.open("results\\_array_synapses_15_N_-5682071268804064449", ios::binary | ios::out);
	if(outfile__array_synapses_15_N.is_open())
	{
		outfile__array_synapses_15_N.write(reinterpret_cast<char*>(_array_synapses_15_N), 1*sizeof(_array_synapses_15_N[0]));
		outfile__array_synapses_15_N.close();
	} else
	{
		std::cout << "Error writing output file for _array_synapses_15_N." << endl;
	}
	ofstream outfile__array_synapses_15_sources;
	outfile__array_synapses_15_sources.open("results\\_array_synapses_15_sources_-2991184938766648840", ios::binary | ios::out);
	if(outfile__array_synapses_15_sources.is_open())
	{
		outfile__array_synapses_15_sources.write(reinterpret_cast<char*>(_array_synapses_15_sources), 300*sizeof(_array_synapses_15_sources[0]));
		outfile__array_synapses_15_sources.close();
	} else
	{
		std::cout << "Error writing output file for _array_synapses_15_sources." << endl;
	}
	ofstream outfile__array_synapses_15_targets;
	outfile__array_synapses_15_targets.open("results\\_array_synapses_15_targets_4543371310841047790", ios::binary | ios::out);
	if(outfile__array_synapses_15_targets.is_open())
	{
		outfile__array_synapses_15_targets.write(reinterpret_cast<char*>(_array_synapses_15_targets), 300*sizeof(_array_synapses_15_targets[0]));
		outfile__array_synapses_15_targets.close();
	} else
	{
		std::cout << "Error writing output file for _array_synapses_15_targets." << endl;
	}
	ofstream outfile__array_synapses_16_N;
	outfile__array_synapses_16_N.open("results\\_array_synapses_16_N_5383130040915980788", ios::binary | ios::out);
	if(outfile__array_synapses_16_N.is_open())
	{
		outfile__array_synapses_16_N.write(reinterpret_cast<char*>(_array_synapses_16_N), 1*sizeof(_array_synapses_16_N[0]));
		outfile__array_synapses_16_N.close();
	} else
	{
		std::cout << "Error writing output file for _array_synapses_16_N." << endl;
	}
	ofstream outfile__array_synapses_16_sources;
	outfile__array_synapses_16_sources.open("results\\_array_synapses_16_sources_-8756909459241990369", ios::binary | ios::out);
	if(outfile__array_synapses_16_sources.is_open())
	{
		outfile__array_synapses_16_sources.write(reinterpret_cast<char*>(_array_synapses_16_sources), 154*sizeof(_array_synapses_16_sources[0]));
		outfile__array_synapses_16_sources.close();
	} else
	{
		std::cout << "Error writing output file for _array_synapses_16_sources." << endl;
	}
	ofstream outfile__array_synapses_16_targets;
	outfile__array_synapses_16_targets.open("results\\_array_synapses_16_targets_-6959724548773856891", ios::binary | ios::out);
	if(outfile__array_synapses_16_targets.is_open())
	{
		outfile__array_synapses_16_targets.write(reinterpret_cast<char*>(_array_synapses_16_targets), 154*sizeof(_array_synapses_16_targets[0]));
		outfile__array_synapses_16_targets.close();
	} else
	{
		std::cout << "Error writing output file for _array_synapses_16_targets." << endl;
	}
	ofstream outfile__array_synapses_17_N;
	outfile__array_synapses_17_N.open("results\\_array_synapses_17_N_7164143314270752505", ios::binary | ios::out);
	if(outfile__array_synapses_17_N.is_open())
	{
		outfile__array_synapses_17_N.write(reinterpret_cast<char*>(_array_synapses_17_N), 1*sizeof(_array_synapses_17_N[0]));
		outfile__array_synapses_17_N.close();
	} else
	{
		std::cout << "Error writing output file for _array_synapses_17_N." << endl;
	}
	ofstream outfile__array_synapses_17_sources;
	outfile__array_synapses_17_sources.open("results\\_array_synapses_17_sources_-7695664694276744352", ios::binary | ios::out);
	if(outfile__array_synapses_17_sources.is_open())
	{
		outfile__array_synapses_17_sources.write(reinterpret_cast<char*>(_array_synapses_17_sources), 370*sizeof(_array_synapses_17_sources[0]));
		outfile__array_synapses_17_sources.close();
	} else
	{
		std::cout << "Error writing output file for _array_synapses_17_sources." << endl;
	}
	ofstream outfile__array_synapses_17_targets;
	outfile__array_synapses_17_targets.open("results\\_array_synapses_17_targets_-7746991235514011061", ios::binary | ios::out);
	if(outfile__array_synapses_17_targets.is_open())
	{
		outfile__array_synapses_17_targets.write(reinterpret_cast<char*>(_array_synapses_17_targets), 370*sizeof(_array_synapses_17_targets[0]));
		outfile__array_synapses_17_targets.close();
	} else
	{
		std::cout << "Error writing output file for _array_synapses_17_targets." << endl;
	}
	ofstream outfile__array_synapses_18_N;
	outfile__array_synapses_18_N.open("results\\_array_synapses_18_N_-5914551209553228780", ios::binary | ios::out);
	if(outfile__array_synapses_18_N.is_open())
	{
		outfile__array_synapses_18_N.write(reinterpret_cast<char*>(_array_synapses_18_N), 1*sizeof(_array_synapses_18_N[0]));
		outfile__array_synapses_18_N.close();
	} else
	{
		std::cout << "Error writing output file for _array_synapses_18_N." << endl;
	}
	ofstream outfile__array_synapses_18_sources;
	outfile__array_synapses_18_sources.open("results\\_array_synapses_18_sources_8628552468694578947", ios::binary | ios::out);
	if(outfile__array_synapses_18_sources.is_open())
	{
		outfile__array_synapses_18_sources.write(reinterpret_cast<char*>(_array_synapses_18_sources), 252*sizeof(_array_synapses_18_sources[0]));
		outfile__array_synapses_18_sources.close();
	} else
	{
		std::cout << "Error writing output file for _array_synapses_18_sources." << endl;
	}
	ofstream outfile__array_synapses_18_targets;
	outfile__array_synapses_18_targets.open("results\\_array_synapses_18_targets_2511984775173847212", ios::binary | ios::out);
	if(outfile__array_synapses_18_targets.is_open())
	{
		outfile__array_synapses_18_targets.write(reinterpret_cast<char*>(_array_synapses_18_targets), 252*sizeof(_array_synapses_18_targets[0]));
		outfile__array_synapses_18_targets.close();
	} else
	{
		std::cout << "Error writing output file for _array_synapses_18_targets." << endl;
	}
	ofstream outfile__array_synapses_19_N;
	outfile__array_synapses_19_N.open("results\\_array_synapses_19_N_-6066691566152130917", ios::binary | ios::out);
	if(outfile__array_synapses_19_N.is_open())
	{
		outfile__array_synapses_19_N.write(reinterpret_cast<char*>(_array_synapses_19_N), 1*sizeof(_array_synapses_19_N[0]));
		outfile__array_synapses_19_N.close();
	} else
	{
		std::cout << "Error writing output file for _array_synapses_19_N." << endl;
	}
	ofstream outfile__array_synapses_19_sources;
	outfile__array_synapses_19_sources.open("results\\_array_synapses_19_sources_-1469382558872900225", ios::binary | ios::out);
	if(outfile__array_synapses_19_sources.is_open())
	{
		outfile__array_synapses_19_sources.write(reinterpret_cast<char*>(_array_synapses_19_sources), 2097*sizeof(_array_synapses_19_sources[0]));
		outfile__array_synapses_19_sources.close();
	} else
	{
		std::cout << "Error writing output file for _array_synapses_19_sources." << endl;
	}
	ofstream outfile__array_synapses_19_targets;
	outfile__array_synapses_19_targets.open("results\\_array_synapses_19_targets_4681662440298937090", ios::binary | ios::out);
	if(outfile__array_synapses_19_targets.is_open())
	{
		outfile__array_synapses_19_targets.write(reinterpret_cast<char*>(_array_synapses_19_targets), 2097*sizeof(_array_synapses_19_targets[0]));
		outfile__array_synapses_19_targets.close();
	} else
	{
		std::cout << "Error writing output file for _array_synapses_19_targets." << endl;
	}
	ofstream outfile__array_synapses_1_N;
	outfile__array_synapses_1_N.open("results\\_array_synapses_1_N_-3147268526515707421", ios::binary | ios::out);
	if(outfile__array_synapses_1_N.is_open())
	{
		outfile__array_synapses_1_N.write(reinterpret_cast<char*>(_array_synapses_1_N), 1*sizeof(_array_synapses_1_N[0]));
		outfile__array_synapses_1_N.close();
	} else
	{
		std::cout << "Error writing output file for _array_synapses_1_N." << endl;
	}
	ofstream outfile__array_synapses_1_sources;
	outfile__array_synapses_1_sources.open("results\\_array_synapses_1_sources_819128652198857027", ios::binary | ios::out);
	if(outfile__array_synapses_1_sources.is_open())
	{
		outfile__array_synapses_1_sources.write(reinterpret_cast<char*>(_array_synapses_1_sources), 4803*sizeof(_array_synapses_1_sources[0]));
		outfile__array_synapses_1_sources.close();
	} else
	{
		std::cout << "Error writing output file for _array_synapses_1_sources." << endl;
	}
	ofstream outfile__array_synapses_1_targets;
	outfile__array_synapses_1_targets.open("results\\_array_synapses_1_targets_-3075877575842688014", ios::binary | ios::out);
	if(outfile__array_synapses_1_targets.is_open())
	{
		outfile__array_synapses_1_targets.write(reinterpret_cast<char*>(_array_synapses_1_targets), 4803*sizeof(_array_synapses_1_targets[0]));
		outfile__array_synapses_1_targets.close();
	} else
	{
		std::cout << "Error writing output file for _array_synapses_1_targets." << endl;
	}
	ofstream outfile__array_synapses_20_N;
	outfile__array_synapses_20_N.open("results\\_array_synapses_20_N_-7113860317856165254", ios::binary | ios::out);
	if(outfile__array_synapses_20_N.is_open())
	{
		outfile__array_synapses_20_N.write(reinterpret_cast<char*>(_array_synapses_20_N), 1*sizeof(_array_synapses_20_N[0]));
		outfile__array_synapses_20_N.close();
	} else
	{
		std::cout << "Error writing output file for _array_synapses_20_N." << endl;
	}
	ofstream outfile__array_synapses_20_sources;
	outfile__array_synapses_20_sources.open("results\\_array_synapses_20_sources_5548018889346107272", ios::binary | ios::out);
	if(outfile__array_synapses_20_sources.is_open())
	{
		outfile__array_synapses_20_sources.write(reinterpret_cast<char*>(_array_synapses_20_sources), 2142*sizeof(_array_synapses_20_sources[0]));
		outfile__array_synapses_20_sources.close();
	} else
	{
		std::cout << "Error writing output file for _array_synapses_20_sources." << endl;
	}
	ofstream outfile__array_synapses_20_targets;
	outfile__array_synapses_20_targets.open("results\\_array_synapses_20_targets_4526667741848829578", ios::binary | ios::out);
	if(outfile__array_synapses_20_targets.is_open())
	{
		outfile__array_synapses_20_targets.write(reinterpret_cast<char*>(_array_synapses_20_targets), 2142*sizeof(_array_synapses_20_targets[0]));
		outfile__array_synapses_20_targets.close();
	} else
	{
		std::cout << "Error writing output file for _array_synapses_20_targets." << endl;
	}
	ofstream outfile__array_synapses_21_N;
	outfile__array_synapses_21_N.open("results\\_array_synapses_21_N_1496952278624038399", ios::binary | ios::out);
	if(outfile__array_synapses_21_N.is_open())
	{
		outfile__array_synapses_21_N.write(reinterpret_cast<char*>(_array_synapses_21_N), 1*sizeof(_array_synapses_21_N[0]));
		outfile__array_synapses_21_N.close();
	} else
	{
		std::cout << "Error writing output file for _array_synapses_21_N." << endl;
	}
	ofstream outfile__array_synapses_21_sources;
	outfile__array_synapses_21_sources.open("results\\_array_synapses_21_sources_-728119937010401663", ios::binary | ios::out);
	if(outfile__array_synapses_21_sources.is_open())
	{
		outfile__array_synapses_21_sources.write(reinterpret_cast<char*>(_array_synapses_21_sources), 762*sizeof(_array_synapses_21_sources[0]));
		outfile__array_synapses_21_sources.close();
	} else
	{
		std::cout << "Error writing output file for _array_synapses_21_sources." << endl;
	}
	ofstream outfile__array_synapses_21_targets;
	outfile__array_synapses_21_targets.open("results\\_array_synapses_21_targets_8270699996259028599", ios::binary | ios::out);
	if(outfile__array_synapses_21_targets.is_open())
	{
		outfile__array_synapses_21_targets.write(reinterpret_cast<char*>(_array_synapses_21_targets), 762*sizeof(_array_synapses_21_targets[0]));
		outfile__array_synapses_21_targets.close();
	} else
	{
		std::cout << "Error writing output file for _array_synapses_21_targets." << endl;
	}
	ofstream outfile__array_synapses_22_N;
	outfile__array_synapses_22_N.open("results\\_array_synapses_22_N_-1082511668686276091", ios::binary | ios::out);
	if(outfile__array_synapses_22_N.is_open())
	{
		outfile__array_synapses_22_N.write(reinterpret_cast<char*>(_array_synapses_22_N), 1*sizeof(_array_synapses_22_N[0]));
		outfile__array_synapses_22_N.close();
	} else
	{
		std::cout << "Error writing output file for _array_synapses_22_N." << endl;
	}
	ofstream outfile__array_synapses_22_sources;
	outfile__array_synapses_22_sources.open("results\\_array_synapses_22_sources_-5795067300323600449", ios::binary | ios::out);
	if(outfile__array_synapses_22_sources.is_open())
	{
		outfile__array_synapses_22_sources.write(reinterpret_cast<char*>(_array_synapses_22_sources), 747*sizeof(_array_synapses_22_sources[0]));
		outfile__array_synapses_22_sources.close();
	} else
	{
		std::cout << "Error writing output file for _array_synapses_22_sources." << endl;
	}
	ofstream outfile__array_synapses_22_targets;
	outfile__array_synapses_22_targets.open("results\\_array_synapses_22_targets_-5740835684419147511", ios::binary | ios::out);
	if(outfile__array_synapses_22_targets.is_open())
	{
		outfile__array_synapses_22_targets.write(reinterpret_cast<char*>(_array_synapses_22_targets), 747*sizeof(_array_synapses_22_targets[0]));
		outfile__array_synapses_22_targets.close();
	} else
	{
		std::cout << "Error writing output file for _array_synapses_22_targets." << endl;
	}
	ofstream outfile__array_synapses_23_N;
	outfile__array_synapses_23_N.open("results\\_array_synapses_23_N_-2670367145784927011", ios::binary | ios::out);
	if(outfile__array_synapses_23_N.is_open())
	{
		outfile__array_synapses_23_N.write(reinterpret_cast<char*>(_array_synapses_23_N), 1*sizeof(_array_synapses_23_N[0]));
		outfile__array_synapses_23_N.close();
	} else
	{
		std::cout << "Error writing output file for _array_synapses_23_N." << endl;
	}
	ofstream outfile__array_synapses_23_sources;
	outfile__array_synapses_23_sources.open("results\\_array_synapses_23_sources_-2913791568720093254", ios::binary | ios::out);
	if(outfile__array_synapses_23_sources.is_open())
	{
		outfile__array_synapses_23_sources.write(reinterpret_cast<char*>(_array_synapses_23_sources), 642*sizeof(_array_synapses_23_sources[0]));
		outfile__array_synapses_23_sources.close();
	} else
	{
		std::cout << "Error writing output file for _array_synapses_23_sources." << endl;
	}
	ofstream outfile__array_synapses_23_targets;
	outfile__array_synapses_23_targets.open("results\\_array_synapses_23_targets_-1991421556518436090", ios::binary | ios::out);
	if(outfile__array_synapses_23_targets.is_open())
	{
		outfile__array_synapses_23_targets.write(reinterpret_cast<char*>(_array_synapses_23_targets), 642*sizeof(_array_synapses_23_targets[0]));
		outfile__array_synapses_23_targets.close();
	} else
	{
		std::cout << "Error writing output file for _array_synapses_23_targets." << endl;
	}
	ofstream outfile__array_synapses_24_N;
	outfile__array_synapses_24_N.open("results\\_array_synapses_24_N_2303888934416924765", ios::binary | ios::out);
	if(outfile__array_synapses_24_N.is_open())
	{
		outfile__array_synapses_24_N.write(reinterpret_cast<char*>(_array_synapses_24_N), 1*sizeof(_array_synapses_24_N[0]));
		outfile__array_synapses_24_N.close();
	} else
	{
		std::cout << "Error writing output file for _array_synapses_24_N." << endl;
	}
	ofstream outfile__array_synapses_24_sources;
	outfile__array_synapses_24_sources.open("results\\_array_synapses_24_sources_-4456211416895316206", ios::binary | ios::out);
	if(outfile__array_synapses_24_sources.is_open())
	{
		outfile__array_synapses_24_sources.write(reinterpret_cast<char*>(_array_synapses_24_sources), 140*sizeof(_array_synapses_24_sources[0]));
		outfile__array_synapses_24_sources.close();
	} else
	{
		std::cout << "Error writing output file for _array_synapses_24_sources." << endl;
	}
	ofstream outfile__array_synapses_24_targets;
	outfile__array_synapses_24_targets.open("results\\_array_synapses_24_targets_2146161712910937014", ios::binary | ios::out);
	if(outfile__array_synapses_24_targets.is_open())
	{
		outfile__array_synapses_24_targets.write(reinterpret_cast<char*>(_array_synapses_24_targets), 140*sizeof(_array_synapses_24_targets[0]));
		outfile__array_synapses_24_targets.close();
	} else
	{
		std::cout << "Error writing output file for _array_synapses_24_targets." << endl;
	}
	ofstream outfile__array_synapses_25_N;
	outfile__array_synapses_25_N.open("results\\_array_synapses_25_N_1665308530864531133", ios::binary | ios::out);
	if(outfile__array_synapses_25_N.is_open())
	{
		outfile__array_synapses_25_N.write(reinterpret_cast<char*>(_array_synapses_25_N), 1*sizeof(_array_synapses_25_N[0]));
		outfile__array_synapses_25_N.close();
	} else
	{
		std::cout << "Error writing output file for _array_synapses_25_N." << endl;
	}
	ofstream outfile__array_synapses_25_sources;
	outfile__array_synapses_25_sources.open("results\\_array_synapses_25_sources_2231256877311606917", ios::binary | ios::out);
	if(outfile__array_synapses_25_sources.is_open())
	{
		outfile__array_synapses_25_sources.write(reinterpret_cast<char*>(_array_synapses_25_sources), 112*sizeof(_array_synapses_25_sources[0]));
		outfile__array_synapses_25_sources.close();
	} else
	{
		std::cout << "Error writing output file for _array_synapses_25_sources." << endl;
	}
	ofstream outfile__array_synapses_25_targets;
	outfile__array_synapses_25_targets.open("results\\_array_synapses_25_targets_1162155259221956765", ios::binary | ios::out);
	if(outfile__array_synapses_25_targets.is_open())
	{
		outfile__array_synapses_25_targets.write(reinterpret_cast<char*>(_array_synapses_25_targets), 112*sizeof(_array_synapses_25_targets[0]));
		outfile__array_synapses_25_targets.close();
	} else
	{
		std::cout << "Error writing output file for _array_synapses_25_targets." << endl;
	}
	ofstream outfile__array_synapses_26_N;
	outfile__array_synapses_26_N.open("results\\_array_synapses_26_N_2180578204010239030", ios::binary | ios::out);
	if(outfile__array_synapses_26_N.is_open())
	{
		outfile__array_synapses_26_N.write(reinterpret_cast<char*>(_array_synapses_26_N), 1*sizeof(_array_synapses_26_N[0]));
		outfile__array_synapses_26_N.close();
	} else
	{
		std::cout << "Error writing output file for _array_synapses_26_N." << endl;
	}
	ofstream outfile__array_synapses_26_sources;
	outfile__array_synapses_26_sources.open("results\\_array_synapses_26_sources_7352592773549251506", ios::binary | ios::out);
	if(outfile__array_synapses_26_sources.is_open())
	{
		outfile__array_synapses_26_sources.write(reinterpret_cast<char*>(_array_synapses_26_sources), 512*sizeof(_array_synapses_26_sources[0]));
		outfile__array_synapses_26_sources.close();
	} else
	{
		std::cout << "Error writing output file for _array_synapses_26_sources." << endl;
	}
	ofstream outfile__array_synapses_26_targets;
	outfile__array_synapses_26_targets.open("results\\_array_synapses_26_targets_7161609866012754161", ios::binary | ios::out);
	if(outfile__array_synapses_26_targets.is_open())
	{
		outfile__array_synapses_26_targets.write(reinterpret_cast<char*>(_array_synapses_26_targets), 512*sizeof(_array_synapses_26_targets[0]));
		outfile__array_synapses_26_targets.close();
	} else
	{
		std::cout << "Error writing output file for _array_synapses_26_targets." << endl;
	}
	ofstream outfile__array_synapses_27_N;
	outfile__array_synapses_27_N.open("results\\_array_synapses_27_N_-2542178334098386184", ios::binary | ios::out);
	if(outfile__array_synapses_27_N.is_open())
	{
		outfile__array_synapses_27_N.write(reinterpret_cast<char*>(_array_synapses_27_N), 1*sizeof(_array_synapses_27_N[0]));
		outfile__array_synapses_27_N.close();
	} else
	{
		std::cout << "Error writing output file for _array_synapses_27_N." << endl;
	}
	ofstream outfile__array_synapses_27_sources;
	outfile__array_synapses_27_sources.open("results\\_array_synapses_27_sources_7087713065232077702", ios::binary | ios::out);
	if(outfile__array_synapses_27_sources.is_open())
	{
		outfile__array_synapses_27_sources.write(reinterpret_cast<char*>(_array_synapses_27_sources), 510*sizeof(_array_synapses_27_sources[0]));
		outfile__array_synapses_27_sources.close();
	} else
	{
		std::cout << "Error writing output file for _array_synapses_27_sources." << endl;
	}
	ofstream outfile__array_synapses_27_targets;
	outfile__array_synapses_27_targets.open("results\\_array_synapses_27_targets_-7351318667252019909", ios::binary | ios::out);
	if(outfile__array_synapses_27_targets.is_open())
	{
		outfile__array_synapses_27_targets.write(reinterpret_cast<char*>(_array_synapses_27_targets), 510*sizeof(_array_synapses_27_targets[0]));
		outfile__array_synapses_27_targets.close();
	} else
	{
		std::cout << "Error writing output file for _array_synapses_27_targets." << endl;
	}
	ofstream outfile__array_synapses_28_N;
	outfile__array_synapses_28_N.open("results\\_array_synapses_28_N_6020155267426306205", ios::binary | ios::out);
	if(outfile__array_synapses_28_N.is_open())
	{
		outfile__array_synapses_28_N.write(reinterpret_cast<char*>(_array_synapses_28_N), 1*sizeof(_array_synapses_28_N[0]));
		outfile__array_synapses_28_N.close();
	} else
	{
		std::cout << "Error writing output file for _array_synapses_28_N." << endl;
	}
	ofstream outfile__array_synapses_28_sources;
	outfile__array_synapses_28_sources.open("results\\_array_synapses_28_sources_368196751036695836", ios::binary | ios::out);
	if(outfile__array_synapses_28_sources.is_open())
	{
		outfile__array_synapses_28_sources.write(reinterpret_cast<char*>(_array_synapses_28_sources), 204*sizeof(_array_synapses_28_sources[0]));
		outfile__array_synapses_28_sources.close();
	} else
	{
		std::cout << "Error writing output file for _array_synapses_28_sources." << endl;
	}
	ofstream outfile__array_synapses_28_targets;
	outfile__array_synapses_28_targets.open("results\\_array_synapses_28_targets_-9076445067812543262", ios::binary | ios::out);
	if(outfile__array_synapses_28_targets.is_open())
	{
		outfile__array_synapses_28_targets.write(reinterpret_cast<char*>(_array_synapses_28_targets), 204*sizeof(_array_synapses_28_targets[0]));
		outfile__array_synapses_28_targets.close();
	} else
	{
		std::cout << "Error writing output file for _array_synapses_28_targets." << endl;
	}
	ofstream outfile__array_synapses_29_N;
	outfile__array_synapses_29_N.open("results\\_array_synapses_29_N_1115964852724555007", ios::binary | ios::out);
	if(outfile__array_synapses_29_N.is_open())
	{
		outfile__array_synapses_29_N.write(reinterpret_cast<char*>(_array_synapses_29_N), 1*sizeof(_array_synapses_29_N[0]));
		outfile__array_synapses_29_N.close();
	} else
	{
		std::cout << "Error writing output file for _array_synapses_29_N." << endl;
	}
	ofstream outfile__array_synapses_29_sources;
	outfile__array_synapses_29_sources.open("results\\_array_synapses_29_sources_3311603343831081913", ios::binary | ios::out);
	if(outfile__array_synapses_29_sources.is_open())
	{
		outfile__array_synapses_29_sources.write(reinterpret_cast<char*>(_array_synapses_29_sources), 234*sizeof(_array_synapses_29_sources[0]));
		outfile__array_synapses_29_sources.close();
	} else
	{
		std::cout << "Error writing output file for _array_synapses_29_sources." << endl;
	}
	ofstream outfile__array_synapses_29_targets;
	outfile__array_synapses_29_targets.open("results\\_array_synapses_29_targets_939795385803222289", ios::binary | ios::out);
	if(outfile__array_synapses_29_targets.is_open())
	{
		outfile__array_synapses_29_targets.write(reinterpret_cast<char*>(_array_synapses_29_targets), 234*sizeof(_array_synapses_29_targets[0]));
		outfile__array_synapses_29_targets.close();
	} else
	{
		std::cout << "Error writing output file for _array_synapses_29_targets." << endl;
	}
	ofstream outfile__array_synapses_2_N;
	outfile__array_synapses_2_N.open("results\\_array_synapses_2_N_-5801585769958696185", ios::binary | ios::out);
	if(outfile__array_synapses_2_N.is_open())
	{
		outfile__array_synapses_2_N.write(reinterpret_cast<char*>(_array_synapses_2_N), 1*sizeof(_array_synapses_2_N[0]));
		outfile__array_synapses_2_N.close();
	} else
	{
		std::cout << "Error writing output file for _array_synapses_2_N." << endl;
	}
	ofstream outfile__array_synapses_2_sources;
	outfile__array_synapses_2_sources.open("results\\_array_synapses_2_sources_-8131076693625527956", ios::binary | ios::out);
	if(outfile__array_synapses_2_sources.is_open())
	{
		outfile__array_synapses_2_sources.write(reinterpret_cast<char*>(_array_synapses_2_sources), 6336*sizeof(_array_synapses_2_sources[0]));
		outfile__array_synapses_2_sources.close();
	} else
	{
		std::cout << "Error writing output file for _array_synapses_2_sources." << endl;
	}
	ofstream outfile__array_synapses_2_targets;
	outfile__array_synapses_2_targets.open("results\\_array_synapses_2_targets_-3290246805936012494", ios::binary | ios::out);
	if(outfile__array_synapses_2_targets.is_open())
	{
		outfile__array_synapses_2_targets.write(reinterpret_cast<char*>(_array_synapses_2_targets), 6336*sizeof(_array_synapses_2_targets[0]));
		outfile__array_synapses_2_targets.close();
	} else
	{
		std::cout << "Error writing output file for _array_synapses_2_targets." << endl;
	}
	ofstream outfile__array_synapses_30_N;
	outfile__array_synapses_30_N.open("results\\_array_synapses_30_N_2464114009405864063", ios::binary | ios::out);
	if(outfile__array_synapses_30_N.is_open())
	{
		outfile__array_synapses_30_N.write(reinterpret_cast<char*>(_array_synapses_30_N), 1*sizeof(_array_synapses_30_N[0]));
		outfile__array_synapses_30_N.close();
	} else
	{
		std::cout << "Error writing output file for _array_synapses_30_N." << endl;
	}
	ofstream outfile__array_synapses_30_sources;
	outfile__array_synapses_30_sources.open("results\\_array_synapses_30_sources_5147096373783599237", ios::binary | ios::out);
	if(outfile__array_synapses_30_sources.is_open())
	{
		outfile__array_synapses_30_sources.write(reinterpret_cast<char*>(_array_synapses_30_sources), 168*sizeof(_array_synapses_30_sources[0]));
		outfile__array_synapses_30_sources.close();
	} else
	{
		std::cout << "Error writing output file for _array_synapses_30_sources." << endl;
	}
	ofstream outfile__array_synapses_30_targets;
	outfile__array_synapses_30_targets.open("results\\_array_synapses_30_targets_-6665552157931124555", ios::binary | ios::out);
	if(outfile__array_synapses_30_targets.is_open())
	{
		outfile__array_synapses_30_targets.write(reinterpret_cast<char*>(_array_synapses_30_targets), 168*sizeof(_array_synapses_30_targets[0]));
		outfile__array_synapses_30_targets.close();
	} else
	{
		std::cout << "Error writing output file for _array_synapses_30_targets." << endl;
	}
	ofstream outfile__array_synapses_31_N;
	outfile__array_synapses_31_N.open("results\\_array_synapses_31_N_-3176435880115991993", ios::binary | ios::out);
	if(outfile__array_synapses_31_N.is_open())
	{
		outfile__array_synapses_31_N.write(reinterpret_cast<char*>(_array_synapses_31_N), 1*sizeof(_array_synapses_31_N[0]));
		outfile__array_synapses_31_N.close();
	} else
	{
		std::cout << "Error writing output file for _array_synapses_31_N." << endl;
	}
	ofstream outfile__array_synapses_31_sources;
	outfile__array_synapses_31_sources.open("results\\_array_synapses_31_sources_500183182729544255", ios::binary | ios::out);
	if(outfile__array_synapses_31_sources.is_open())
	{
		outfile__array_synapses_31_sources.write(reinterpret_cast<char*>(_array_synapses_31_sources), 21*sizeof(_array_synapses_31_sources[0]));
		outfile__array_synapses_31_sources.close();
	} else
	{
		std::cout << "Error writing output file for _array_synapses_31_sources." << endl;
	}
	ofstream outfile__array_synapses_31_targets;
	outfile__array_synapses_31_targets.open("results\\_array_synapses_31_targets_2399107284523840922", ios::binary | ios::out);
	if(outfile__array_synapses_31_targets.is_open())
	{
		outfile__array_synapses_31_targets.write(reinterpret_cast<char*>(_array_synapses_31_targets), 21*sizeof(_array_synapses_31_targets[0]));
		outfile__array_synapses_31_targets.close();
	} else
	{
		std::cout << "Error writing output file for _array_synapses_31_targets." << endl;
	}
	ofstream outfile__array_synapses_32_N;
	outfile__array_synapses_32_N.open("results\\_array_synapses_32_N_-5836407360785788524", ios::binary | ios::out);
	if(outfile__array_synapses_32_N.is_open())
	{
		outfile__array_synapses_32_N.write(reinterpret_cast<char*>(_array_synapses_32_N), 1*sizeof(_array_synapses_32_N[0]));
		outfile__array_synapses_32_N.close();
	} else
	{
		std::cout << "Error writing output file for _array_synapses_32_N." << endl;
	}
	ofstream outfile__array_synapses_32_sources;
	outfile__array_synapses_32_sources.open("results\\_array_synapses_32_sources_-5490435833454102027", ios::binary | ios::out);
	if(outfile__array_synapses_32_sources.is_open())
	{
		outfile__array_synapses_32_sources.write(reinterpret_cast<char*>(_array_synapses_32_sources), 27*sizeof(_array_synapses_32_sources[0]));
		outfile__array_synapses_32_sources.close();
	} else
	{
		std::cout << "Error writing output file for _array_synapses_32_sources." << endl;
	}
	ofstream outfile__array_synapses_32_targets;
	outfile__array_synapses_32_targets.open("results\\_array_synapses_32_targets_-5182740534368024506", ios::binary | ios::out);
	if(outfile__array_synapses_32_targets.is_open())
	{
		outfile__array_synapses_32_targets.write(reinterpret_cast<char*>(_array_synapses_32_targets), 27*sizeof(_array_synapses_32_targets[0]));
		outfile__array_synapses_32_targets.close();
	} else
	{
		std::cout << "Error writing output file for _array_synapses_32_targets." << endl;
	}
	ofstream outfile__array_synapses_33_N;
	outfile__array_synapses_33_N.open("results\\_array_synapses_33_N_-7584715493997113380", ios::binary | ios::out);
	if(outfile__array_synapses_33_N.is_open())
	{
		outfile__array_synapses_33_N.write(reinterpret_cast<char*>(_array_synapses_33_N), 1*sizeof(_array_synapses_33_N[0]));
		outfile__array_synapses_33_N.close();
	} else
	{
		std::cout << "Error writing output file for _array_synapses_33_N." << endl;
	}
	ofstream outfile__array_synapses_33_sources;
	outfile__array_synapses_33_sources.open("results\\_array_synapses_33_sources_-5916410711436780341", ios::binary | ios::out);
	if(outfile__array_synapses_33_sources.is_open())
	{
		outfile__array_synapses_33_sources.write(reinterpret_cast<char*>(_array_synapses_33_sources), 333*sizeof(_array_synapses_33_sources[0]));
		outfile__array_synapses_33_sources.close();
	} else
	{
		std::cout << "Error writing output file for _array_synapses_33_sources." << endl;
	}
	ofstream outfile__array_synapses_33_targets;
	outfile__array_synapses_33_targets.open("results\\_array_synapses_33_targets_-170539931505759453", ios::binary | ios::out);
	if(outfile__array_synapses_33_targets.is_open())
	{
		outfile__array_synapses_33_targets.write(reinterpret_cast<char*>(_array_synapses_33_targets), 333*sizeof(_array_synapses_33_targets[0]));
		outfile__array_synapses_33_targets.close();
	} else
	{
		std::cout << "Error writing output file for _array_synapses_33_targets." << endl;
	}
	ofstream outfile__array_synapses_34_N;
	outfile__array_synapses_34_N.open("results\\_array_synapses_34_N_6701338072347495088", ios::binary | ios::out);
	if(outfile__array_synapses_34_N.is_open())
	{
		outfile__array_synapses_34_N.write(reinterpret_cast<char*>(_array_synapses_34_N), 1*sizeof(_array_synapses_34_N[0]));
		outfile__array_synapses_34_N.close();
	} else
	{
		std::cout << "Error writing output file for _array_synapses_34_N." << endl;
	}
	ofstream outfile__array_synapses_34_sources;
	outfile__array_synapses_34_sources.open("results\\_array_synapses_34_sources_6094785009019231683", ios::binary | ios::out);
	if(outfile__array_synapses_34_sources.is_open())
	{
		outfile__array_synapses_34_sources.write(reinterpret_cast<char*>(_array_synapses_34_sources), 333*sizeof(_array_synapses_34_sources[0]));
		outfile__array_synapses_34_sources.close();
	} else
	{
		std::cout << "Error writing output file for _array_synapses_34_sources." << endl;
	}
	ofstream outfile__array_synapses_34_targets;
	outfile__array_synapses_34_targets.open("results\\_array_synapses_34_targets_-6669217407416039614", ios::binary | ios::out);
	if(outfile__array_synapses_34_targets.is_open())
	{
		outfile__array_synapses_34_targets.write(reinterpret_cast<char*>(_array_synapses_34_targets), 333*sizeof(_array_synapses_34_targets[0]));
		outfile__array_synapses_34_targets.close();
	} else
	{
		std::cout << "Error writing output file for _array_synapses_34_targets." << endl;
	}
	ofstream outfile__array_synapses_35_N;
	outfile__array_synapses_35_N.open("results\\_array_synapses_35_N_-7495462055041768506", ios::binary | ios::out);
	if(outfile__array_synapses_35_N.is_open())
	{
		outfile__array_synapses_35_N.write(reinterpret_cast<char*>(_array_synapses_35_N), 1*sizeof(_array_synapses_35_N[0]));
		outfile__array_synapses_35_N.close();
	} else
	{
		std::cout << "Error writing output file for _array_synapses_35_N." << endl;
	}
	ofstream outfile__array_synapses_35_sources;
	outfile__array_synapses_35_sources.open("results\\_array_synapses_35_sources_-2757262493644877823", ios::binary | ios::out);
	if(outfile__array_synapses_35_sources.is_open())
	{
		outfile__array_synapses_35_sources.write(reinterpret_cast<char*>(_array_synapses_35_sources), 105*sizeof(_array_synapses_35_sources[0]));
		outfile__array_synapses_35_sources.close();
	} else
	{
		std::cout << "Error writing output file for _array_synapses_35_sources." << endl;
	}
	ofstream outfile__array_synapses_35_targets;
	outfile__array_synapses_35_targets.open("results\\_array_synapses_35_targets_-2445919908070514435", ios::binary | ios::out);
	if(outfile__array_synapses_35_targets.is_open())
	{
		outfile__array_synapses_35_targets.write(reinterpret_cast<char*>(_array_synapses_35_targets), 105*sizeof(_array_synapses_35_targets[0]));
		outfile__array_synapses_35_targets.close();
	} else
	{
		std::cout << "Error writing output file for _array_synapses_35_targets." << endl;
	}
	ofstream outfile__array_synapses_36_N;
	outfile__array_synapses_36_N.open("results\\_array_synapses_36_N_-2524495114630796368", ios::binary | ios::out);
	if(outfile__array_synapses_36_N.is_open())
	{
		outfile__array_synapses_36_N.write(reinterpret_cast<char*>(_array_synapses_36_N), 1*sizeof(_array_synapses_36_N[0]));
		outfile__array_synapses_36_N.close();
	} else
	{
		std::cout << "Error writing output file for _array_synapses_36_N." << endl;
	}
	ofstream outfile__array_synapses_36_sources;
	outfile__array_synapses_36_sources.open("results\\_array_synapses_36_sources_-1057532190727715683", ios::binary | ios::out);
	if(outfile__array_synapses_36_sources.is_open())
	{
		outfile__array_synapses_36_sources.write(reinterpret_cast<char*>(_array_synapses_36_sources), 78*sizeof(_array_synapses_36_sources[0]));
		outfile__array_synapses_36_sources.close();
	} else
	{
		std::cout << "Error writing output file for _array_synapses_36_sources." << endl;
	}
	ofstream outfile__array_synapses_36_targets;
	outfile__array_synapses_36_targets.open("results\\_array_synapses_36_targets_8107680672447228540", ios::binary | ios::out);
	if(outfile__array_synapses_36_targets.is_open())
	{
		outfile__array_synapses_36_targets.write(reinterpret_cast<char*>(_array_synapses_36_targets), 78*sizeof(_array_synapses_36_targets[0]));
		outfile__array_synapses_36_targets.close();
	} else
	{
		std::cout << "Error writing output file for _array_synapses_36_targets." << endl;
	}
	ofstream outfile__array_synapses_37_N;
	outfile__array_synapses_37_N.open("results\\_array_synapses_37_N_2794010466334413347", ios::binary | ios::out);
	if(outfile__array_synapses_37_N.is_open())
	{
		outfile__array_synapses_37_N.write(reinterpret_cast<char*>(_array_synapses_37_N), 1*sizeof(_array_synapses_37_N[0]));
		outfile__array_synapses_37_N.close();
	} else
	{
		std::cout << "Error writing output file for _array_synapses_37_N." << endl;
	}
	ofstream outfile__array_synapses_37_sources;
	outfile__array_synapses_37_sources.open("results\\_array_synapses_37_sources_497972854529771280", ios::binary | ios::out);
	if(outfile__array_synapses_37_sources.is_open())
	{
		outfile__array_synapses_37_sources.write(reinterpret_cast<char*>(_array_synapses_37_sources), 66*sizeof(_array_synapses_37_sources[0]));
		outfile__array_synapses_37_sources.close();
	} else
	{
		std::cout << "Error writing output file for _array_synapses_37_sources." << endl;
	}
	ofstream outfile__array_synapses_37_targets;
	outfile__array_synapses_37_targets.open("results\\_array_synapses_37_targets_2227733870489613394", ios::binary | ios::out);
	if(outfile__array_synapses_37_targets.is_open())
	{
		outfile__array_synapses_37_targets.write(reinterpret_cast<char*>(_array_synapses_37_targets), 66*sizeof(_array_synapses_37_targets[0]));
		outfile__array_synapses_37_targets.close();
	} else
	{
		std::cout << "Error writing output file for _array_synapses_37_targets." << endl;
	}
	ofstream outfile__array_synapses_3_N;
	outfile__array_synapses_3_N.open("results\\_array_synapses_3_N_7537057014040712833", ios::binary | ios::out);
	if(outfile__array_synapses_3_N.is_open())
	{
		outfile__array_synapses_3_N.write(reinterpret_cast<char*>(_array_synapses_3_N), 1*sizeof(_array_synapses_3_N[0]));
		outfile__array_synapses_3_N.close();
	} else
	{
		std::cout << "Error writing output file for _array_synapses_3_N." << endl;
	}
	ofstream outfile__array_synapses_3_sources;
	outfile__array_synapses_3_sources.open("results\\_array_synapses_3_sources_-580913234045781027", ios::binary | ios::out);
	if(outfile__array_synapses_3_sources.is_open())
	{
		outfile__array_synapses_3_sources.write(reinterpret_cast<char*>(_array_synapses_3_sources), 1938*sizeof(_array_synapses_3_sources[0]));
		outfile__array_synapses_3_sources.close();
	} else
	{
		std::cout << "Error writing output file for _array_synapses_3_sources." << endl;
	}
	ofstream outfile__array_synapses_3_targets;
	outfile__array_synapses_3_targets.open("results\\_array_synapses_3_targets_985323634680089100", ios::binary | ios::out);
	if(outfile__array_synapses_3_targets.is_open())
	{
		outfile__array_synapses_3_targets.write(reinterpret_cast<char*>(_array_synapses_3_targets), 1938*sizeof(_array_synapses_3_targets[0]));
		outfile__array_synapses_3_targets.close();
	} else
	{
		std::cout << "Error writing output file for _array_synapses_3_targets." << endl;
	}
	ofstream outfile__array_synapses_4_N;
	outfile__array_synapses_4_N.open("results\\_array_synapses_4_N_-5480815264466009956", ios::binary | ios::out);
	if(outfile__array_synapses_4_N.is_open())
	{
		outfile__array_synapses_4_N.write(reinterpret_cast<char*>(_array_synapses_4_N), 1*sizeof(_array_synapses_4_N[0]));
		outfile__array_synapses_4_N.close();
	} else
	{
		std::cout << "Error writing output file for _array_synapses_4_N." << endl;
	}
	ofstream outfile__array_synapses_4_sources;
	outfile__array_synapses_4_sources.open("results\\_array_synapses_4_sources_-6630528490612914037", ios::binary | ios::out);
	if(outfile__array_synapses_4_sources.is_open())
	{
		outfile__array_synapses_4_sources.write(reinterpret_cast<char*>(_array_synapses_4_sources), 2588*sizeof(_array_synapses_4_sources[0]));
		outfile__array_synapses_4_sources.close();
	} else
	{
		std::cout << "Error writing output file for _array_synapses_4_sources." << endl;
	}
	ofstream outfile__array_synapses_4_targets;
	outfile__array_synapses_4_targets.open("results\\_array_synapses_4_targets_-6978808513214546696", ios::binary | ios::out);
	if(outfile__array_synapses_4_targets.is_open())
	{
		outfile__array_synapses_4_targets.write(reinterpret_cast<char*>(_array_synapses_4_targets), 2588*sizeof(_array_synapses_4_targets[0]));
		outfile__array_synapses_4_targets.close();
	} else
	{
		std::cout << "Error writing output file for _array_synapses_4_targets." << endl;
	}
	ofstream outfile__array_synapses_5_N;
	outfile__array_synapses_5_N.open("results\\_array_synapses_5_N_-638366387178456983", ios::binary | ios::out);
	if(outfile__array_synapses_5_N.is_open())
	{
		outfile__array_synapses_5_N.write(reinterpret_cast<char*>(_array_synapses_5_N), 1*sizeof(_array_synapses_5_N[0]));
		outfile__array_synapses_5_N.close();
	} else
	{
		std::cout << "Error writing output file for _array_synapses_5_N." << endl;
	}
	ofstream outfile__array_synapses_5_sources;
	outfile__array_synapses_5_sources.open("results\\_array_synapses_5_sources_-608693291864218849", ios::binary | ios::out);
	if(outfile__array_synapses_5_sources.is_open())
	{
		outfile__array_synapses_5_sources.write(reinterpret_cast<char*>(_array_synapses_5_sources), 11697*sizeof(_array_synapses_5_sources[0]));
		outfile__array_synapses_5_sources.close();
	} else
	{
		std::cout << "Error writing output file for _array_synapses_5_sources." << endl;
	}
	ofstream outfile__array_synapses_5_targets;
	outfile__array_synapses_5_targets.open("results\\_array_synapses_5_targets_8244734464437624703", ios::binary | ios::out);
	if(outfile__array_synapses_5_targets.is_open())
	{
		outfile__array_synapses_5_targets.write(reinterpret_cast<char*>(_array_synapses_5_targets), 11697*sizeof(_array_synapses_5_targets[0]));
		outfile__array_synapses_5_targets.close();
	} else
	{
		std::cout << "Error writing output file for _array_synapses_5_targets." << endl;
	}
	ofstream outfile__array_synapses_6_N;
	outfile__array_synapses_6_N.open("results\\_array_synapses_6_N_-6149505238710165527", ios::binary | ios::out);
	if(outfile__array_synapses_6_N.is_open())
	{
		outfile__array_synapses_6_N.write(reinterpret_cast<char*>(_array_synapses_6_N), 1*sizeof(_array_synapses_6_N[0]));
		outfile__array_synapses_6_N.close();
	} else
	{
		std::cout << "Error writing output file for _array_synapses_6_N." << endl;
	}
	ofstream outfile__array_synapses_6_sources;
	outfile__array_synapses_6_sources.open("results\\_array_synapses_6_sources_-8142194176834051751", ios::binary | ios::out);
	if(outfile__array_synapses_6_sources.is_open())
	{
		outfile__array_synapses_6_sources.write(reinterpret_cast<char*>(_array_synapses_6_sources), 1384*sizeof(_array_synapses_6_sources[0]));
		outfile__array_synapses_6_sources.close();
	} else
	{
		std::cout << "Error writing output file for _array_synapses_6_sources." << endl;
	}
	ofstream outfile__array_synapses_6_targets;
	outfile__array_synapses_6_targets.open("results\\_array_synapses_6_targets_5886585891567695365", ios::binary | ios::out);
	if(outfile__array_synapses_6_targets.is_open())
	{
		outfile__array_synapses_6_targets.write(reinterpret_cast<char*>(_array_synapses_6_targets), 1384*sizeof(_array_synapses_6_targets[0]));
		outfile__array_synapses_6_targets.close();
	} else
	{
		std::cout << "Error writing output file for _array_synapses_6_targets." << endl;
	}
	ofstream outfile__array_synapses_7_N;
	outfile__array_synapses_7_N.open("results\\_array_synapses_7_N_-214957734040705962", ios::binary | ios::out);
	if(outfile__array_synapses_7_N.is_open())
	{
		outfile__array_synapses_7_N.write(reinterpret_cast<char*>(_array_synapses_7_N), 1*sizeof(_array_synapses_7_N[0]));
		outfile__array_synapses_7_N.close();
	} else
	{
		std::cout << "Error writing output file for _array_synapses_7_N." << endl;
	}
	ofstream outfile__array_synapses_7_sources;
	outfile__array_synapses_7_sources.open("results\\_array_synapses_7_sources_3094034737869353596", ios::binary | ios::out);
	if(outfile__array_synapses_7_sources.is_open())
	{
		outfile__array_synapses_7_sources.write(reinterpret_cast<char*>(_array_synapses_7_sources), 224*sizeof(_array_synapses_7_sources[0]));
		outfile__array_synapses_7_sources.close();
	} else
	{
		std::cout << "Error writing output file for _array_synapses_7_sources." << endl;
	}
	ofstream outfile__array_synapses_7_targets;
	outfile__array_synapses_7_targets.open("results\\_array_synapses_7_targets_3901028533942047983", ios::binary | ios::out);
	if(outfile__array_synapses_7_targets.is_open())
	{
		outfile__array_synapses_7_targets.write(reinterpret_cast<char*>(_array_synapses_7_targets), 224*sizeof(_array_synapses_7_targets[0]));
		outfile__array_synapses_7_targets.close();
	} else
	{
		std::cout << "Error writing output file for _array_synapses_7_targets." << endl;
	}
	ofstream outfile__array_synapses_8_N;
	outfile__array_synapses_8_N.open("results\\_array_synapses_8_N_-7197540552793422349", ios::binary | ios::out);
	if(outfile__array_synapses_8_N.is_open())
	{
		outfile__array_synapses_8_N.write(reinterpret_cast<char*>(_array_synapses_8_N), 1*sizeof(_array_synapses_8_N[0]));
		outfile__array_synapses_8_N.close();
	} else
	{
		std::cout << "Error writing output file for _array_synapses_8_N." << endl;
	}
	ofstream outfile__array_synapses_8_sources;
	outfile__array_synapses_8_sources.open("results\\_array_synapses_8_sources_-6046983043803338656", ios::binary | ios::out);
	if(outfile__array_synapses_8_sources.is_open())
	{
		outfile__array_synapses_8_sources.write(reinterpret_cast<char*>(_array_synapses_8_sources), 108*sizeof(_array_synapses_8_sources[0]));
		outfile__array_synapses_8_sources.close();
	} else
	{
		std::cout << "Error writing output file for _array_synapses_8_sources." << endl;
	}
	ofstream outfile__array_synapses_8_targets;
	outfile__array_synapses_8_targets.open("results\\_array_synapses_8_targets_7891182235419693137", ios::binary | ios::out);
	if(outfile__array_synapses_8_targets.is_open())
	{
		outfile__array_synapses_8_targets.write(reinterpret_cast<char*>(_array_synapses_8_targets), 108*sizeof(_array_synapses_8_targets[0]));
		outfile__array_synapses_8_targets.close();
	} else
	{
		std::cout << "Error writing output file for _array_synapses_8_targets." << endl;
	}
	ofstream outfile__array_synapses_9_N;
	outfile__array_synapses_9_N.open("results\\_array_synapses_9_N_-7844481015502587347", ios::binary | ios::out);
	if(outfile__array_synapses_9_N.is_open())
	{
		outfile__array_synapses_9_N.write(reinterpret_cast<char*>(_array_synapses_9_N), 1*sizeof(_array_synapses_9_N[0]));
		outfile__array_synapses_9_N.close();
	} else
	{
		std::cout << "Error writing output file for _array_synapses_9_N." << endl;
	}
	ofstream outfile__array_synapses_9_sources;
	outfile__array_synapses_9_sources.open("results\\_array_synapses_9_sources_-6682619826831360042", ios::binary | ios::out);
	if(outfile__array_synapses_9_sources.is_open())
	{
		outfile__array_synapses_9_sources.write(reinterpret_cast<char*>(_array_synapses_9_sources), 1854*sizeof(_array_synapses_9_sources[0]));
		outfile__array_synapses_9_sources.close();
	} else
	{
		std::cout << "Error writing output file for _array_synapses_9_sources." << endl;
	}
	ofstream outfile__array_synapses_9_targets;
	outfile__array_synapses_9_targets.open("results\\_array_synapses_9_targets_6246614140402686527", ios::binary | ios::out);
	if(outfile__array_synapses_9_targets.is_open())
	{
		outfile__array_synapses_9_targets.write(reinterpret_cast<char*>(_array_synapses_9_targets), 1854*sizeof(_array_synapses_9_targets[0]));
		outfile__array_synapses_9_targets.close();
	} else
	{
		std::cout << "Error writing output file for _array_synapses_9_targets." << endl;
	}
	ofstream outfile__array_synapses_N;
	outfile__array_synapses_N.open("results\\_array_synapses_N_2691246406457229068", ios::binary | ios::out);
	if(outfile__array_synapses_N.is_open())
	{
		outfile__array_synapses_N.write(reinterpret_cast<char*>(_array_synapses_N), 1*sizeof(_array_synapses_N[0]));
		outfile__array_synapses_N.close();
	} else
	{
		std::cout << "Error writing output file for _array_synapses_N." << endl;
	}

	ofstream outfile__dynamic_array_spikegeneratorgroup__timebins;
	outfile__dynamic_array_spikegeneratorgroup__timebins.open("results\\_dynamic_array_spikegeneratorgroup__timebins_1501960342395132284", ios::binary | ios::out);
	if(outfile__dynamic_array_spikegeneratorgroup__timebins.is_open())
	{
        if (! _dynamic_array_spikegeneratorgroup__timebins.empty() )
        {
			outfile__dynamic_array_spikegeneratorgroup__timebins.write(reinterpret_cast<char*>(&_dynamic_array_spikegeneratorgroup__timebins[0]), _dynamic_array_spikegeneratorgroup__timebins.size()*sizeof(_dynamic_array_spikegeneratorgroup__timebins[0]));
		    outfile__dynamic_array_spikegeneratorgroup__timebins.close();
		}
	} else
	{
		std::cout << "Error writing output file for _dynamic_array_spikegeneratorgroup__timebins." << endl;
	}
	ofstream outfile__dynamic_array_spikegeneratorgroup_neuron_index;
	outfile__dynamic_array_spikegeneratorgroup_neuron_index.open("results\\_dynamic_array_spikegeneratorgroup_neuron_index_-4545024460851383872", ios::binary | ios::out);
	if(outfile__dynamic_array_spikegeneratorgroup_neuron_index.is_open())
	{
        if (! _dynamic_array_spikegeneratorgroup_neuron_index.empty() )
        {
			outfile__dynamic_array_spikegeneratorgroup_neuron_index.write(reinterpret_cast<char*>(&_dynamic_array_spikegeneratorgroup_neuron_index[0]), _dynamic_array_spikegeneratorgroup_neuron_index.size()*sizeof(_dynamic_array_spikegeneratorgroup_neuron_index[0]));
		    outfile__dynamic_array_spikegeneratorgroup_neuron_index.close();
		}
	} else
	{
		std::cout << "Error writing output file for _dynamic_array_spikegeneratorgroup_neuron_index." << endl;
	}
	ofstream outfile__dynamic_array_spikegeneratorgroup_spike_number;
	outfile__dynamic_array_spikegeneratorgroup_spike_number.open("results\\_dynamic_array_spikegeneratorgroup_spike_number_8567763864887485701", ios::binary | ios::out);
	if(outfile__dynamic_array_spikegeneratorgroup_spike_number.is_open())
	{
        if (! _dynamic_array_spikegeneratorgroup_spike_number.empty() )
        {
			outfile__dynamic_array_spikegeneratorgroup_spike_number.write(reinterpret_cast<char*>(&_dynamic_array_spikegeneratorgroup_spike_number[0]), _dynamic_array_spikegeneratorgroup_spike_number.size()*sizeof(_dynamic_array_spikegeneratorgroup_spike_number[0]));
		    outfile__dynamic_array_spikegeneratorgroup_spike_number.close();
		}
	} else
	{
		std::cout << "Error writing output file for _dynamic_array_spikegeneratorgroup_spike_number." << endl;
	}
	ofstream outfile__dynamic_array_spikegeneratorgroup_spike_time;
	outfile__dynamic_array_spikegeneratorgroup_spike_time.open("results\\_dynamic_array_spikegeneratorgroup_spike_time_3711776644331728881", ios::binary | ios::out);
	if(outfile__dynamic_array_spikegeneratorgroup_spike_time.is_open())
	{
        if (! _dynamic_array_spikegeneratorgroup_spike_time.empty() )
        {
			outfile__dynamic_array_spikegeneratorgroup_spike_time.write(reinterpret_cast<char*>(&_dynamic_array_spikegeneratorgroup_spike_time[0]), _dynamic_array_spikegeneratorgroup_spike_time.size()*sizeof(_dynamic_array_spikegeneratorgroup_spike_time[0]));
		    outfile__dynamic_array_spikegeneratorgroup_spike_time.close();
		}
	} else
	{
		std::cout << "Error writing output file for _dynamic_array_spikegeneratorgroup_spike_time." << endl;
	}
	ofstream outfile__dynamic_array_spikemonitor_1_i;
	outfile__dynamic_array_spikemonitor_1_i.open("results\\_dynamic_array_spikemonitor_1_i_-6534457563460356049", ios::binary | ios::out);
	if(outfile__dynamic_array_spikemonitor_1_i.is_open())
	{
        if (! _dynamic_array_spikemonitor_1_i.empty() )
        {
			outfile__dynamic_array_spikemonitor_1_i.write(reinterpret_cast<char*>(&_dynamic_array_spikemonitor_1_i[0]), _dynamic_array_spikemonitor_1_i.size()*sizeof(_dynamic_array_spikemonitor_1_i[0]));
		    outfile__dynamic_array_spikemonitor_1_i.close();
		}
	} else
	{
		std::cout << "Error writing output file for _dynamic_array_spikemonitor_1_i." << endl;
	}
	ofstream outfile__dynamic_array_spikemonitor_1_t;
	outfile__dynamic_array_spikemonitor_1_t.open("results\\_dynamic_array_spikemonitor_1_t_2321393239292896693", ios::binary | ios::out);
	if(outfile__dynamic_array_spikemonitor_1_t.is_open())
	{
        if (! _dynamic_array_spikemonitor_1_t.empty() )
        {
			outfile__dynamic_array_spikemonitor_1_t.write(reinterpret_cast<char*>(&_dynamic_array_spikemonitor_1_t[0]), _dynamic_array_spikemonitor_1_t.size()*sizeof(_dynamic_array_spikemonitor_1_t[0]));
		    outfile__dynamic_array_spikemonitor_1_t.close();
		}
	} else
	{
		std::cout << "Error writing output file for _dynamic_array_spikemonitor_1_t." << endl;
	}
	ofstream outfile__dynamic_array_spikemonitor_2_i;
	outfile__dynamic_array_spikemonitor_2_i.open("results\\_dynamic_array_spikemonitor_2_i_-5400512530865618377", ios::binary | ios::out);
	if(outfile__dynamic_array_spikemonitor_2_i.is_open())
	{
        if (! _dynamic_array_spikemonitor_2_i.empty() )
        {
			outfile__dynamic_array_spikemonitor_2_i.write(reinterpret_cast<char*>(&_dynamic_array_spikemonitor_2_i[0]), _dynamic_array_spikemonitor_2_i.size()*sizeof(_dynamic_array_spikemonitor_2_i[0]));
		    outfile__dynamic_array_spikemonitor_2_i.close();
		}
	} else
	{
		std::cout << "Error writing output file for _dynamic_array_spikemonitor_2_i." << endl;
	}
	ofstream outfile__dynamic_array_spikemonitor_2_t;
	outfile__dynamic_array_spikemonitor_2_t.open("results\\_dynamic_array_spikemonitor_2_t_-1668249005553631135", ios::binary | ios::out);
	if(outfile__dynamic_array_spikemonitor_2_t.is_open())
	{
        if (! _dynamic_array_spikemonitor_2_t.empty() )
        {
			outfile__dynamic_array_spikemonitor_2_t.write(reinterpret_cast<char*>(&_dynamic_array_spikemonitor_2_t[0]), _dynamic_array_spikemonitor_2_t.size()*sizeof(_dynamic_array_spikemonitor_2_t[0]));
		    outfile__dynamic_array_spikemonitor_2_t.close();
		}
	} else
	{
		std::cout << "Error writing output file for _dynamic_array_spikemonitor_2_t." << endl;
	}
	ofstream outfile__dynamic_array_spikemonitor_3_i;
	outfile__dynamic_array_spikemonitor_3_i.open("results\\_dynamic_array_spikemonitor_3_i_-2150968741265460532", ios::binary | ios::out);
	if(outfile__dynamic_array_spikemonitor_3_i.is_open())
	{
        if (! _dynamic_array_spikemonitor_3_i.empty() )
        {
			outfile__dynamic_array_spikemonitor_3_i.write(reinterpret_cast<char*>(&_dynamic_array_spikemonitor_3_i[0]), _dynamic_array_spikemonitor_3_i.size()*sizeof(_dynamic_array_spikemonitor_3_i[0]));
		    outfile__dynamic_array_spikemonitor_3_i.close();
		}
	} else
	{
		std::cout << "Error writing output file for _dynamic_array_spikemonitor_3_i." << endl;
	}
	ofstream outfile__dynamic_array_spikemonitor_3_t;
	outfile__dynamic_array_spikemonitor_3_t.open("results\\_dynamic_array_spikemonitor_3_t_8928869046461769462", ios::binary | ios::out);
	if(outfile__dynamic_array_spikemonitor_3_t.is_open())
	{
        if (! _dynamic_array_spikemonitor_3_t.empty() )
        {
			outfile__dynamic_array_spikemonitor_3_t.write(reinterpret_cast<char*>(&_dynamic_array_spikemonitor_3_t[0]), _dynamic_array_spikemonitor_3_t.size()*sizeof(_dynamic_array_spikemonitor_3_t[0]));
		    outfile__dynamic_array_spikemonitor_3_t.close();
		}
	} else
	{
		std::cout << "Error writing output file for _dynamic_array_spikemonitor_3_t." << endl;
	}
	ofstream outfile__dynamic_array_spikemonitor_4_i;
	outfile__dynamic_array_spikemonitor_4_i.open("results\\_dynamic_array_spikemonitor_4_i_1581049992954188705", ios::binary | ios::out);
	if(outfile__dynamic_array_spikemonitor_4_i.is_open())
	{
        if (! _dynamic_array_spikemonitor_4_i.empty() )
        {
			outfile__dynamic_array_spikemonitor_4_i.write(reinterpret_cast<char*>(&_dynamic_array_spikemonitor_4_i[0]), _dynamic_array_spikemonitor_4_i.size()*sizeof(_dynamic_array_spikemonitor_4_i[0]));
		    outfile__dynamic_array_spikemonitor_4_i.close();
		}
	} else
	{
		std::cout << "Error writing output file for _dynamic_array_spikemonitor_4_i." << endl;
	}
	ofstream outfile__dynamic_array_spikemonitor_4_t;
	outfile__dynamic_array_spikemonitor_4_t.open("results\\_dynamic_array_spikemonitor_4_t_-6392744250958527655", ios::binary | ios::out);
	if(outfile__dynamic_array_spikemonitor_4_t.is_open())
	{
        if (! _dynamic_array_spikemonitor_4_t.empty() )
        {
			outfile__dynamic_array_spikemonitor_4_t.write(reinterpret_cast<char*>(&_dynamic_array_spikemonitor_4_t[0]), _dynamic_array_spikemonitor_4_t.size()*sizeof(_dynamic_array_spikemonitor_4_t[0]));
		    outfile__dynamic_array_spikemonitor_4_t.close();
		}
	} else
	{
		std::cout << "Error writing output file for _dynamic_array_spikemonitor_4_t." << endl;
	}
	ofstream outfile__dynamic_array_spikemonitor_5_i;
	outfile__dynamic_array_spikemonitor_5_i.open("results\\_dynamic_array_spikemonitor_5_i_4158123727329561805", ios::binary | ios::out);
	if(outfile__dynamic_array_spikemonitor_5_i.is_open())
	{
        if (! _dynamic_array_spikemonitor_5_i.empty() )
        {
			outfile__dynamic_array_spikemonitor_5_i.write(reinterpret_cast<char*>(&_dynamic_array_spikemonitor_5_i[0]), _dynamic_array_spikemonitor_5_i.size()*sizeof(_dynamic_array_spikemonitor_5_i[0]));
		    outfile__dynamic_array_spikemonitor_5_i.close();
		}
	} else
	{
		std::cout << "Error writing output file for _dynamic_array_spikemonitor_5_i." << endl;
	}
	ofstream outfile__dynamic_array_spikemonitor_5_t;
	outfile__dynamic_array_spikemonitor_5_t.open("results\\_dynamic_array_spikemonitor_5_t_5463830881931553732", ios::binary | ios::out);
	if(outfile__dynamic_array_spikemonitor_5_t.is_open())
	{
        if (! _dynamic_array_spikemonitor_5_t.empty() )
        {
			outfile__dynamic_array_spikemonitor_5_t.write(reinterpret_cast<char*>(&_dynamic_array_spikemonitor_5_t[0]), _dynamic_array_spikemonitor_5_t.size()*sizeof(_dynamic_array_spikemonitor_5_t[0]));
		    outfile__dynamic_array_spikemonitor_5_t.close();
		}
	} else
	{
		std::cout << "Error writing output file for _dynamic_array_spikemonitor_5_t." << endl;
	}
	ofstream outfile__dynamic_array_spikemonitor_i;
	outfile__dynamic_array_spikemonitor_i.open("results\\_dynamic_array_spikemonitor_i_-6032029339981493381", ios::binary | ios::out);
	if(outfile__dynamic_array_spikemonitor_i.is_open())
	{
        if (! _dynamic_array_spikemonitor_i.empty() )
        {
			outfile__dynamic_array_spikemonitor_i.write(reinterpret_cast<char*>(&_dynamic_array_spikemonitor_i[0]), _dynamic_array_spikemonitor_i.size()*sizeof(_dynamic_array_spikemonitor_i[0]));
		    outfile__dynamic_array_spikemonitor_i.close();
		}
	} else
	{
		std::cout << "Error writing output file for _dynamic_array_spikemonitor_i." << endl;
	}
	ofstream outfile__dynamic_array_spikemonitor_t;
	outfile__dynamic_array_spikemonitor_t.open("results\\_dynamic_array_spikemonitor_t_2538261576755621935", ios::binary | ios::out);
	if(outfile__dynamic_array_spikemonitor_t.is_open())
	{
        if (! _dynamic_array_spikemonitor_t.empty() )
        {
			outfile__dynamic_array_spikemonitor_t.write(reinterpret_cast<char*>(&_dynamic_array_spikemonitor_t[0]), _dynamic_array_spikemonitor_t.size()*sizeof(_dynamic_array_spikemonitor_t[0]));
		    outfile__dynamic_array_spikemonitor_t.close();
		}
	} else
	{
		std::cout << "Error writing output file for _dynamic_array_spikemonitor_t." << endl;
	}
	ofstream outfile__dynamic_array_synapses_10__synaptic_post;
	outfile__dynamic_array_synapses_10__synaptic_post.open("results\\_dynamic_array_synapses_10__synaptic_post_802227545676064072", ios::binary | ios::out);
	if(outfile__dynamic_array_synapses_10__synaptic_post.is_open())
	{
        if (! _dynamic_array_synapses_10__synaptic_post.empty() )
        {
			outfile__dynamic_array_synapses_10__synaptic_post.write(reinterpret_cast<char*>(&_dynamic_array_synapses_10__synaptic_post[0]), _dynamic_array_synapses_10__synaptic_post.size()*sizeof(_dynamic_array_synapses_10__synaptic_post[0]));
		    outfile__dynamic_array_synapses_10__synaptic_post.close();
		}
	} else
	{
		std::cout << "Error writing output file for _dynamic_array_synapses_10__synaptic_post." << endl;
	}
	ofstream outfile__dynamic_array_synapses_10__synaptic_pre;
	outfile__dynamic_array_synapses_10__synaptic_pre.open("results\\_dynamic_array_synapses_10__synaptic_pre_-2526696860082787490", ios::binary | ios::out);
	if(outfile__dynamic_array_synapses_10__synaptic_pre.is_open())
	{
        if (! _dynamic_array_synapses_10__synaptic_pre.empty() )
        {
			outfile__dynamic_array_synapses_10__synaptic_pre.write(reinterpret_cast<char*>(&_dynamic_array_synapses_10__synaptic_pre[0]), _dynamic_array_synapses_10__synaptic_pre.size()*sizeof(_dynamic_array_synapses_10__synaptic_pre[0]));
		    outfile__dynamic_array_synapses_10__synaptic_pre.close();
		}
	} else
	{
		std::cout << "Error writing output file for _dynamic_array_synapses_10__synaptic_pre." << endl;
	}
	ofstream outfile__dynamic_array_synapses_10_delay;
	outfile__dynamic_array_synapses_10_delay.open("results\\_dynamic_array_synapses_10_delay_-7150920952294536524", ios::binary | ios::out);
	if(outfile__dynamic_array_synapses_10_delay.is_open())
	{
        if (! _dynamic_array_synapses_10_delay.empty() )
        {
			outfile__dynamic_array_synapses_10_delay.write(reinterpret_cast<char*>(&_dynamic_array_synapses_10_delay[0]), _dynamic_array_synapses_10_delay.size()*sizeof(_dynamic_array_synapses_10_delay[0]));
		    outfile__dynamic_array_synapses_10_delay.close();
		}
	} else
	{
		std::cout << "Error writing output file for _dynamic_array_synapses_10_delay." << endl;
	}
	ofstream outfile__dynamic_array_synapses_10_lastupdate;
	outfile__dynamic_array_synapses_10_lastupdate.open("results\\_dynamic_array_synapses_10_lastupdate_4538882017161966740", ios::binary | ios::out);
	if(outfile__dynamic_array_synapses_10_lastupdate.is_open())
	{
        if (! _dynamic_array_synapses_10_lastupdate.empty() )
        {
			outfile__dynamic_array_synapses_10_lastupdate.write(reinterpret_cast<char*>(&_dynamic_array_synapses_10_lastupdate[0]), _dynamic_array_synapses_10_lastupdate.size()*sizeof(_dynamic_array_synapses_10_lastupdate[0]));
		    outfile__dynamic_array_synapses_10_lastupdate.close();
		}
	} else
	{
		std::cout << "Error writing output file for _dynamic_array_synapses_10_lastupdate." << endl;
	}
	ofstream outfile__dynamic_array_synapses_10_N_incoming;
	outfile__dynamic_array_synapses_10_N_incoming.open("results\\_dynamic_array_synapses_10_N_incoming_-5139579930307814339", ios::binary | ios::out);
	if(outfile__dynamic_array_synapses_10_N_incoming.is_open())
	{
        if (! _dynamic_array_synapses_10_N_incoming.empty() )
        {
			outfile__dynamic_array_synapses_10_N_incoming.write(reinterpret_cast<char*>(&_dynamic_array_synapses_10_N_incoming[0]), _dynamic_array_synapses_10_N_incoming.size()*sizeof(_dynamic_array_synapses_10_N_incoming[0]));
		    outfile__dynamic_array_synapses_10_N_incoming.close();
		}
	} else
	{
		std::cout << "Error writing output file for _dynamic_array_synapses_10_N_incoming." << endl;
	}
	ofstream outfile__dynamic_array_synapses_10_N_outgoing;
	outfile__dynamic_array_synapses_10_N_outgoing.open("results\\_dynamic_array_synapses_10_N_outgoing_-144706102521907790", ios::binary | ios::out);
	if(outfile__dynamic_array_synapses_10_N_outgoing.is_open())
	{
        if (! _dynamic_array_synapses_10_N_outgoing.empty() )
        {
			outfile__dynamic_array_synapses_10_N_outgoing.write(reinterpret_cast<char*>(&_dynamic_array_synapses_10_N_outgoing[0]), _dynamic_array_synapses_10_N_outgoing.size()*sizeof(_dynamic_array_synapses_10_N_outgoing[0]));
		    outfile__dynamic_array_synapses_10_N_outgoing.close();
		}
	} else
	{
		std::cout << "Error writing output file for _dynamic_array_synapses_10_N_outgoing." << endl;
	}
	ofstream outfile__dynamic_array_synapses_10_R;
	outfile__dynamic_array_synapses_10_R.open("results\\_dynamic_array_synapses_10_R_-4528039577914813034", ios::binary | ios::out);
	if(outfile__dynamic_array_synapses_10_R.is_open())
	{
        if (! _dynamic_array_synapses_10_R.empty() )
        {
			outfile__dynamic_array_synapses_10_R.write(reinterpret_cast<char*>(&_dynamic_array_synapses_10_R[0]), _dynamic_array_synapses_10_R.size()*sizeof(_dynamic_array_synapses_10_R[0]));
		    outfile__dynamic_array_synapses_10_R.close();
		}
	} else
	{
		std::cout << "Error writing output file for _dynamic_array_synapses_10_R." << endl;
	}
	ofstream outfile__dynamic_array_synapses_10_wght;
	outfile__dynamic_array_synapses_10_wght.open("results\\_dynamic_array_synapses_10_wght_-9156786890932634821", ios::binary | ios::out);
	if(outfile__dynamic_array_synapses_10_wght.is_open())
	{
        if (! _dynamic_array_synapses_10_wght.empty() )
        {
			outfile__dynamic_array_synapses_10_wght.write(reinterpret_cast<char*>(&_dynamic_array_synapses_10_wght[0]), _dynamic_array_synapses_10_wght.size()*sizeof(_dynamic_array_synapses_10_wght[0]));
		    outfile__dynamic_array_synapses_10_wght.close();
		}
	} else
	{
		std::cout << "Error writing output file for _dynamic_array_synapses_10_wght." << endl;
	}
	ofstream outfile__dynamic_array_synapses_11__synaptic_post;
	outfile__dynamic_array_synapses_11__synaptic_post.open("results\\_dynamic_array_synapses_11__synaptic_post_7928586431355325639", ios::binary | ios::out);
	if(outfile__dynamic_array_synapses_11__synaptic_post.is_open())
	{
        if (! _dynamic_array_synapses_11__synaptic_post.empty() )
        {
			outfile__dynamic_array_synapses_11__synaptic_post.write(reinterpret_cast<char*>(&_dynamic_array_synapses_11__synaptic_post[0]), _dynamic_array_synapses_11__synaptic_post.size()*sizeof(_dynamic_array_synapses_11__synaptic_post[0]));
		    outfile__dynamic_array_synapses_11__synaptic_post.close();
		}
	} else
	{
		std::cout << "Error writing output file for _dynamic_array_synapses_11__synaptic_post." << endl;
	}
	ofstream outfile__dynamic_array_synapses_11__synaptic_pre;
	outfile__dynamic_array_synapses_11__synaptic_pre.open("results\\_dynamic_array_synapses_11__synaptic_pre_-5723772326616286294", ios::binary | ios::out);
	if(outfile__dynamic_array_synapses_11__synaptic_pre.is_open())
	{
        if (! _dynamic_array_synapses_11__synaptic_pre.empty() )
        {
			outfile__dynamic_array_synapses_11__synaptic_pre.write(reinterpret_cast<char*>(&_dynamic_array_synapses_11__synaptic_pre[0]), _dynamic_array_synapses_11__synaptic_pre.size()*sizeof(_dynamic_array_synapses_11__synaptic_pre[0]));
		    outfile__dynamic_array_synapses_11__synaptic_pre.close();
		}
	} else
	{
		std::cout << "Error writing output file for _dynamic_array_synapses_11__synaptic_pre." << endl;
	}
	ofstream outfile__dynamic_array_synapses_11_delay;
	outfile__dynamic_array_synapses_11_delay.open("results\\_dynamic_array_synapses_11_delay_5298856117412384298", ios::binary | ios::out);
	if(outfile__dynamic_array_synapses_11_delay.is_open())
	{
        if (! _dynamic_array_synapses_11_delay.empty() )
        {
			outfile__dynamic_array_synapses_11_delay.write(reinterpret_cast<char*>(&_dynamic_array_synapses_11_delay[0]), _dynamic_array_synapses_11_delay.size()*sizeof(_dynamic_array_synapses_11_delay[0]));
		    outfile__dynamic_array_synapses_11_delay.close();
		}
	} else
	{
		std::cout << "Error writing output file for _dynamic_array_synapses_11_delay." << endl;
	}
	ofstream outfile__dynamic_array_synapses_11_lastupdate;
	outfile__dynamic_array_synapses_11_lastupdate.open("results\\_dynamic_array_synapses_11_lastupdate_-2375702365052693937", ios::binary | ios::out);
	if(outfile__dynamic_array_synapses_11_lastupdate.is_open())
	{
        if (! _dynamic_array_synapses_11_lastupdate.empty() )
        {
			outfile__dynamic_array_synapses_11_lastupdate.write(reinterpret_cast<char*>(&_dynamic_array_synapses_11_lastupdate[0]), _dynamic_array_synapses_11_lastupdate.size()*sizeof(_dynamic_array_synapses_11_lastupdate[0]));
		    outfile__dynamic_array_synapses_11_lastupdate.close();
		}
	} else
	{
		std::cout << "Error writing output file for _dynamic_array_synapses_11_lastupdate." << endl;
	}
	ofstream outfile__dynamic_array_synapses_11_N_incoming;
	outfile__dynamic_array_synapses_11_N_incoming.open("results\\_dynamic_array_synapses_11_N_incoming_-6666575083129369023", ios::binary | ios::out);
	if(outfile__dynamic_array_synapses_11_N_incoming.is_open())
	{
        if (! _dynamic_array_synapses_11_N_incoming.empty() )
        {
			outfile__dynamic_array_synapses_11_N_incoming.write(reinterpret_cast<char*>(&_dynamic_array_synapses_11_N_incoming[0]), _dynamic_array_synapses_11_N_incoming.size()*sizeof(_dynamic_array_synapses_11_N_incoming[0]));
		    outfile__dynamic_array_synapses_11_N_incoming.close();
		}
	} else
	{
		std::cout << "Error writing output file for _dynamic_array_synapses_11_N_incoming." << endl;
	}
	ofstream outfile__dynamic_array_synapses_11_N_outgoing;
	outfile__dynamic_array_synapses_11_N_outgoing.open("results\\_dynamic_array_synapses_11_N_outgoing_-5459586044511010860", ios::binary | ios::out);
	if(outfile__dynamic_array_synapses_11_N_outgoing.is_open())
	{
        if (! _dynamic_array_synapses_11_N_outgoing.empty() )
        {
			outfile__dynamic_array_synapses_11_N_outgoing.write(reinterpret_cast<char*>(&_dynamic_array_synapses_11_N_outgoing[0]), _dynamic_array_synapses_11_N_outgoing.size()*sizeof(_dynamic_array_synapses_11_N_outgoing[0]));
		    outfile__dynamic_array_synapses_11_N_outgoing.close();
		}
	} else
	{
		std::cout << "Error writing output file for _dynamic_array_synapses_11_N_outgoing." << endl;
	}
	ofstream outfile__dynamic_array_synapses_11_R;
	outfile__dynamic_array_synapses_11_R.open("results\\_dynamic_array_synapses_11_R_6007239813210604235", ios::binary | ios::out);
	if(outfile__dynamic_array_synapses_11_R.is_open())
	{
        if (! _dynamic_array_synapses_11_R.empty() )
        {
			outfile__dynamic_array_synapses_11_R.write(reinterpret_cast<char*>(&_dynamic_array_synapses_11_R[0]), _dynamic_array_synapses_11_R.size()*sizeof(_dynamic_array_synapses_11_R[0]));
		    outfile__dynamic_array_synapses_11_R.close();
		}
	} else
	{
		std::cout << "Error writing output file for _dynamic_array_synapses_11_R." << endl;
	}
	ofstream outfile__dynamic_array_synapses_11_wght;
	outfile__dynamic_array_synapses_11_wght.open("results\\_dynamic_array_synapses_11_wght_7717151907414917321", ios::binary | ios::out);
	if(outfile__dynamic_array_synapses_11_wght.is_open())
	{
        if (! _dynamic_array_synapses_11_wght.empty() )
        {
			outfile__dynamic_array_synapses_11_wght.write(reinterpret_cast<char*>(&_dynamic_array_synapses_11_wght[0]), _dynamic_array_synapses_11_wght.size()*sizeof(_dynamic_array_synapses_11_wght[0]));
		    outfile__dynamic_array_synapses_11_wght.close();
		}
	} else
	{
		std::cout << "Error writing output file for _dynamic_array_synapses_11_wght." << endl;
	}
	ofstream outfile__dynamic_array_synapses_12__synaptic_post;
	outfile__dynamic_array_synapses_12__synaptic_post.open("results\\_dynamic_array_synapses_12__synaptic_post_165561995328044122", ios::binary | ios::out);
	if(outfile__dynamic_array_synapses_12__synaptic_post.is_open())
	{
        if (! _dynamic_array_synapses_12__synaptic_post.empty() )
        {
			outfile__dynamic_array_synapses_12__synaptic_post.write(reinterpret_cast<char*>(&_dynamic_array_synapses_12__synaptic_post[0]), _dynamic_array_synapses_12__synaptic_post.size()*sizeof(_dynamic_array_synapses_12__synaptic_post[0]));
		    outfile__dynamic_array_synapses_12__synaptic_post.close();
		}
	} else
	{
		std::cout << "Error writing output file for _dynamic_array_synapses_12__synaptic_post." << endl;
	}
	ofstream outfile__dynamic_array_synapses_12__synaptic_pre;
	outfile__dynamic_array_synapses_12__synaptic_pre.open("results\\_dynamic_array_synapses_12__synaptic_pre_1686117218780673707", ios::binary | ios::out);
	if(outfile__dynamic_array_synapses_12__synaptic_pre.is_open())
	{
        if (! _dynamic_array_synapses_12__synaptic_pre.empty() )
        {
			outfile__dynamic_array_synapses_12__synaptic_pre.write(reinterpret_cast<char*>(&_dynamic_array_synapses_12__synaptic_pre[0]), _dynamic_array_synapses_12__synaptic_pre.size()*sizeof(_dynamic_array_synapses_12__synaptic_pre[0]));
		    outfile__dynamic_array_synapses_12__synaptic_pre.close();
		}
	} else
	{
		std::cout << "Error writing output file for _dynamic_array_synapses_12__synaptic_pre." << endl;
	}
	ofstream outfile__dynamic_array_synapses_12_delay;
	outfile__dynamic_array_synapses_12_delay.open("results\\_dynamic_array_synapses_12_delay_3784941052352061244", ios::binary | ios::out);
	if(outfile__dynamic_array_synapses_12_delay.is_open())
	{
        if (! _dynamic_array_synapses_12_delay.empty() )
        {
			outfile__dynamic_array_synapses_12_delay.write(reinterpret_cast<char*>(&_dynamic_array_synapses_12_delay[0]), _dynamic_array_synapses_12_delay.size()*sizeof(_dynamic_array_synapses_12_delay[0]));
		    outfile__dynamic_array_synapses_12_delay.close();
		}
	} else
	{
		std::cout << "Error writing output file for _dynamic_array_synapses_12_delay." << endl;
	}
	ofstream outfile__dynamic_array_synapses_12_lastupdate;
	outfile__dynamic_array_synapses_12_lastupdate.open("results\\_dynamic_array_synapses_12_lastupdate_1065401354477149088", ios::binary | ios::out);
	if(outfile__dynamic_array_synapses_12_lastupdate.is_open())
	{
        if (! _dynamic_array_synapses_12_lastupdate.empty() )
        {
			outfile__dynamic_array_synapses_12_lastupdate.write(reinterpret_cast<char*>(&_dynamic_array_synapses_12_lastupdate[0]), _dynamic_array_synapses_12_lastupdate.size()*sizeof(_dynamic_array_synapses_12_lastupdate[0]));
		    outfile__dynamic_array_synapses_12_lastupdate.close();
		}
	} else
	{
		std::cout << "Error writing output file for _dynamic_array_synapses_12_lastupdate." << endl;
	}
	ofstream outfile__dynamic_array_synapses_12_N_incoming;
	outfile__dynamic_array_synapses_12_N_incoming.open("results\\_dynamic_array_synapses_12_N_incoming_24143762351526726", ios::binary | ios::out);
	if(outfile__dynamic_array_synapses_12_N_incoming.is_open())
	{
        if (! _dynamic_array_synapses_12_N_incoming.empty() )
        {
			outfile__dynamic_array_synapses_12_N_incoming.write(reinterpret_cast<char*>(&_dynamic_array_synapses_12_N_incoming[0]), _dynamic_array_synapses_12_N_incoming.size()*sizeof(_dynamic_array_synapses_12_N_incoming[0]));
		    outfile__dynamic_array_synapses_12_N_incoming.close();
		}
	} else
	{
		std::cout << "Error writing output file for _dynamic_array_synapses_12_N_incoming." << endl;
	}
	ofstream outfile__dynamic_array_synapses_12_N_outgoing;
	outfile__dynamic_array_synapses_12_N_outgoing.open("results\\_dynamic_array_synapses_12_N_outgoing_5352938101570616722", ios::binary | ios::out);
	if(outfile__dynamic_array_synapses_12_N_outgoing.is_open())
	{
        if (! _dynamic_array_synapses_12_N_outgoing.empty() )
        {
			outfile__dynamic_array_synapses_12_N_outgoing.write(reinterpret_cast<char*>(&_dynamic_array_synapses_12_N_outgoing[0]), _dynamic_array_synapses_12_N_outgoing.size()*sizeof(_dynamic_array_synapses_12_N_outgoing[0]));
		    outfile__dynamic_array_synapses_12_N_outgoing.close();
		}
	} else
	{
		std::cout << "Error writing output file for _dynamic_array_synapses_12_N_outgoing." << endl;
	}
	ofstream outfile__dynamic_array_synapses_12_R;
	outfile__dynamic_array_synapses_12_R.open("results\\_dynamic_array_synapses_12_R_3337808348004869407", ios::binary | ios::out);
	if(outfile__dynamic_array_synapses_12_R.is_open())
	{
        if (! _dynamic_array_synapses_12_R.empty() )
        {
			outfile__dynamic_array_synapses_12_R.write(reinterpret_cast<char*>(&_dynamic_array_synapses_12_R[0]), _dynamic_array_synapses_12_R.size()*sizeof(_dynamic_array_synapses_12_R[0]));
		    outfile__dynamic_array_synapses_12_R.close();
		}
	} else
	{
		std::cout << "Error writing output file for _dynamic_array_synapses_12_R." << endl;
	}
	ofstream outfile__dynamic_array_synapses_12_wght;
	outfile__dynamic_array_synapses_12_wght.open("results\\_dynamic_array_synapses_12_wght_-414140224739202208", ios::binary | ios::out);
	if(outfile__dynamic_array_synapses_12_wght.is_open())
	{
        if (! _dynamic_array_synapses_12_wght.empty() )
        {
			outfile__dynamic_array_synapses_12_wght.write(reinterpret_cast<char*>(&_dynamic_array_synapses_12_wght[0]), _dynamic_array_synapses_12_wght.size()*sizeof(_dynamic_array_synapses_12_wght[0]));
		    outfile__dynamic_array_synapses_12_wght.close();
		}
	} else
	{
		std::cout << "Error writing output file for _dynamic_array_synapses_12_wght." << endl;
	}
	ofstream outfile__dynamic_array_synapses_13__synaptic_post;
	outfile__dynamic_array_synapses_13__synaptic_post.open("results\\_dynamic_array_synapses_13__synaptic_post_-3375192811726000140", ios::binary | ios::out);
	if(outfile__dynamic_array_synapses_13__synaptic_post.is_open())
	{
        if (! _dynamic_array_synapses_13__synaptic_post.empty() )
        {
			outfile__dynamic_array_synapses_13__synaptic_post.write(reinterpret_cast<char*>(&_dynamic_array_synapses_13__synaptic_post[0]), _dynamic_array_synapses_13__synaptic_post.size()*sizeof(_dynamic_array_synapses_13__synaptic_post[0]));
		    outfile__dynamic_array_synapses_13__synaptic_post.close();
		}
	} else
	{
		std::cout << "Error writing output file for _dynamic_array_synapses_13__synaptic_post." << endl;
	}
	ofstream outfile__dynamic_array_synapses_13__synaptic_pre;
	outfile__dynamic_array_synapses_13__synaptic_pre.open("results\\_dynamic_array_synapses_13__synaptic_pre_1802055287347015861", ios::binary | ios::out);
	if(outfile__dynamic_array_synapses_13__synaptic_pre.is_open())
	{
        if (! _dynamic_array_synapses_13__synaptic_pre.empty() )
        {
			outfile__dynamic_array_synapses_13__synaptic_pre.write(reinterpret_cast<char*>(&_dynamic_array_synapses_13__synaptic_pre[0]), _dynamic_array_synapses_13__synaptic_pre.size()*sizeof(_dynamic_array_synapses_13__synaptic_pre[0]));
		    outfile__dynamic_array_synapses_13__synaptic_pre.close();
		}
	} else
	{
		std::cout << "Error writing output file for _dynamic_array_synapses_13__synaptic_pre." << endl;
	}
	ofstream outfile__dynamic_array_synapses_13_delay;
	outfile__dynamic_array_synapses_13_delay.open("results\\_dynamic_array_synapses_13_delay_-4122399447187697628", ios::binary | ios::out);
	if(outfile__dynamic_array_synapses_13_delay.is_open())
	{
        if (! _dynamic_array_synapses_13_delay.empty() )
        {
			outfile__dynamic_array_synapses_13_delay.write(reinterpret_cast<char*>(&_dynamic_array_synapses_13_delay[0]), _dynamic_array_synapses_13_delay.size()*sizeof(_dynamic_array_synapses_13_delay[0]));
		    outfile__dynamic_array_synapses_13_delay.close();
		}
	} else
	{
		std::cout << "Error writing output file for _dynamic_array_synapses_13_delay." << endl;
	}
	ofstream outfile__dynamic_array_synapses_13_lastupdate;
	outfile__dynamic_array_synapses_13_lastupdate.open("results\\_dynamic_array_synapses_13_lastupdate_7816718318937911938", ios::binary | ios::out);
	if(outfile__dynamic_array_synapses_13_lastupdate.is_open())
	{
        if (! _dynamic_array_synapses_13_lastupdate.empty() )
        {
			outfile__dynamic_array_synapses_13_lastupdate.write(reinterpret_cast<char*>(&_dynamic_array_synapses_13_lastupdate[0]), _dynamic_array_synapses_13_lastupdate.size()*sizeof(_dynamic_array_synapses_13_lastupdate[0]));
		    outfile__dynamic_array_synapses_13_lastupdate.close();
		}
	} else
	{
		std::cout << "Error writing output file for _dynamic_array_synapses_13_lastupdate." << endl;
	}
	ofstream outfile__dynamic_array_synapses_13_N_incoming;
	outfile__dynamic_array_synapses_13_N_incoming.open("results\\_dynamic_array_synapses_13_N_incoming_-1428153494518071530", ios::binary | ios::out);
	if(outfile__dynamic_array_synapses_13_N_incoming.is_open())
	{
        if (! _dynamic_array_synapses_13_N_incoming.empty() )
        {
			outfile__dynamic_array_synapses_13_N_incoming.write(reinterpret_cast<char*>(&_dynamic_array_synapses_13_N_incoming[0]), _dynamic_array_synapses_13_N_incoming.size()*sizeof(_dynamic_array_synapses_13_N_incoming[0]));
		    outfile__dynamic_array_synapses_13_N_incoming.close();
		}
	} else
	{
		std::cout << "Error writing output file for _dynamic_array_synapses_13_N_incoming." << endl;
	}
	ofstream outfile__dynamic_array_synapses_13_N_outgoing;
	outfile__dynamic_array_synapses_13_N_outgoing.open("results\\_dynamic_array_synapses_13_N_outgoing_-2497625236874204604", ios::binary | ios::out);
	if(outfile__dynamic_array_synapses_13_N_outgoing.is_open())
	{
        if (! _dynamic_array_synapses_13_N_outgoing.empty() )
        {
			outfile__dynamic_array_synapses_13_N_outgoing.write(reinterpret_cast<char*>(&_dynamic_array_synapses_13_N_outgoing[0]), _dynamic_array_synapses_13_N_outgoing.size()*sizeof(_dynamic_array_synapses_13_N_outgoing[0]));
		    outfile__dynamic_array_synapses_13_N_outgoing.close();
		}
	} else
	{
		std::cout << "Error writing output file for _dynamic_array_synapses_13_N_outgoing." << endl;
	}
	ofstream outfile__dynamic_array_synapses_13_R;
	outfile__dynamic_array_synapses_13_R.open("results\\_dynamic_array_synapses_13_R_-2672266605580122823", ios::binary | ios::out);
	if(outfile__dynamic_array_synapses_13_R.is_open())
	{
        if (! _dynamic_array_synapses_13_R.empty() )
        {
			outfile__dynamic_array_synapses_13_R.write(reinterpret_cast<char*>(&_dynamic_array_synapses_13_R[0]), _dynamic_array_synapses_13_R.size()*sizeof(_dynamic_array_synapses_13_R[0]));
		    outfile__dynamic_array_synapses_13_R.close();
		}
	} else
	{
		std::cout << "Error writing output file for _dynamic_array_synapses_13_R." << endl;
	}
	ofstream outfile__dynamic_array_synapses_13_wght;
	outfile__dynamic_array_synapses_13_wght.open("results\\_dynamic_array_synapses_13_wght_2615485500061079917", ios::binary | ios::out);
	if(outfile__dynamic_array_synapses_13_wght.is_open())
	{
        if (! _dynamic_array_synapses_13_wght.empty() )
        {
			outfile__dynamic_array_synapses_13_wght.write(reinterpret_cast<char*>(&_dynamic_array_synapses_13_wght[0]), _dynamic_array_synapses_13_wght.size()*sizeof(_dynamic_array_synapses_13_wght[0]));
		    outfile__dynamic_array_synapses_13_wght.close();
		}
	} else
	{
		std::cout << "Error writing output file for _dynamic_array_synapses_13_wght." << endl;
	}
	ofstream outfile__dynamic_array_synapses_14__synaptic_post;
	outfile__dynamic_array_synapses_14__synaptic_post.open("results\\_dynamic_array_synapses_14__synaptic_post_-6782524525025463383", ios::binary | ios::out);
	if(outfile__dynamic_array_synapses_14__synaptic_post.is_open())
	{
        if (! _dynamic_array_synapses_14__synaptic_post.empty() )
        {
			outfile__dynamic_array_synapses_14__synaptic_post.write(reinterpret_cast<char*>(&_dynamic_array_synapses_14__synaptic_post[0]), _dynamic_array_synapses_14__synaptic_post.size()*sizeof(_dynamic_array_synapses_14__synaptic_post[0]));
		    outfile__dynamic_array_synapses_14__synaptic_post.close();
		}
	} else
	{
		std::cout << "Error writing output file for _dynamic_array_synapses_14__synaptic_post." << endl;
	}
	ofstream outfile__dynamic_array_synapses_14__synaptic_pre;
	outfile__dynamic_array_synapses_14__synaptic_pre.open("results\\_dynamic_array_synapses_14__synaptic_pre_-7321740874353605338", ios::binary | ios::out);
	if(outfile__dynamic_array_synapses_14__synaptic_pre.is_open())
	{
        if (! _dynamic_array_synapses_14__synaptic_pre.empty() )
        {
			outfile__dynamic_array_synapses_14__synaptic_pre.write(reinterpret_cast<char*>(&_dynamic_array_synapses_14__synaptic_pre[0]), _dynamic_array_synapses_14__synaptic_pre.size()*sizeof(_dynamic_array_synapses_14__synaptic_pre[0]));
		    outfile__dynamic_array_synapses_14__synaptic_pre.close();
		}
	} else
	{
		std::cout << "Error writing output file for _dynamic_array_synapses_14__synaptic_pre." << endl;
	}
	ofstream outfile__dynamic_array_synapses_14_delay;
	outfile__dynamic_array_synapses_14_delay.open("results\\_dynamic_array_synapses_14_delay_-3978336466182051663", ios::binary | ios::out);
	if(outfile__dynamic_array_synapses_14_delay.is_open())
	{
        if (! _dynamic_array_synapses_14_delay.empty() )
        {
			outfile__dynamic_array_synapses_14_delay.write(reinterpret_cast<char*>(&_dynamic_array_synapses_14_delay[0]), _dynamic_array_synapses_14_delay.size()*sizeof(_dynamic_array_synapses_14_delay[0]));
		    outfile__dynamic_array_synapses_14_delay.close();
		}
	} else
	{
		std::cout << "Error writing output file for _dynamic_array_synapses_14_delay." << endl;
	}
	ofstream outfile__dynamic_array_synapses_14_lastupdate;
	outfile__dynamic_array_synapses_14_lastupdate.open("results\\_dynamic_array_synapses_14_lastupdate_-8432645628507029193", ios::binary | ios::out);
	if(outfile__dynamic_array_synapses_14_lastupdate.is_open())
	{
        if (! _dynamic_array_synapses_14_lastupdate.empty() )
        {
			outfile__dynamic_array_synapses_14_lastupdate.write(reinterpret_cast<char*>(&_dynamic_array_synapses_14_lastupdate[0]), _dynamic_array_synapses_14_lastupdate.size()*sizeof(_dynamic_array_synapses_14_lastupdate[0]));
		    outfile__dynamic_array_synapses_14_lastupdate.close();
		}
	} else
	{
		std::cout << "Error writing output file for _dynamic_array_synapses_14_lastupdate." << endl;
	}
	ofstream outfile__dynamic_array_synapses_14_N_incoming;
	outfile__dynamic_array_synapses_14_N_incoming.open("results\\_dynamic_array_synapses_14_N_incoming_-928223471225002855", ios::binary | ios::out);
	if(outfile__dynamic_array_synapses_14_N_incoming.is_open())
	{
        if (! _dynamic_array_synapses_14_N_incoming.empty() )
        {
			outfile__dynamic_array_synapses_14_N_incoming.write(reinterpret_cast<char*>(&_dynamic_array_synapses_14_N_incoming[0]), _dynamic_array_synapses_14_N_incoming.size()*sizeof(_dynamic_array_synapses_14_N_incoming[0]));
		    outfile__dynamic_array_synapses_14_N_incoming.close();
		}
	} else
	{
		std::cout << "Error writing output file for _dynamic_array_synapses_14_N_incoming." << endl;
	}
	ofstream outfile__dynamic_array_synapses_14_N_outgoing;
	outfile__dynamic_array_synapses_14_N_outgoing.open("results\\_dynamic_array_synapses_14_N_outgoing_6945355630988234684", ios::binary | ios::out);
	if(outfile__dynamic_array_synapses_14_N_outgoing.is_open())
	{
        if (! _dynamic_array_synapses_14_N_outgoing.empty() )
        {
			outfile__dynamic_array_synapses_14_N_outgoing.write(reinterpret_cast<char*>(&_dynamic_array_synapses_14_N_outgoing[0]), _dynamic_array_synapses_14_N_outgoing.size()*sizeof(_dynamic_array_synapses_14_N_outgoing[0]));
		    outfile__dynamic_array_synapses_14_N_outgoing.close();
		}
	} else
	{
		std::cout << "Error writing output file for _dynamic_array_synapses_14_N_outgoing." << endl;
	}
	ofstream outfile__dynamic_array_synapses_14_R;
	outfile__dynamic_array_synapses_14_R.open("results\\_dynamic_array_synapses_14_R_5256543848346570654", ios::binary | ios::out);
	if(outfile__dynamic_array_synapses_14_R.is_open())
	{
        if (! _dynamic_array_synapses_14_R.empty() )
        {
			outfile__dynamic_array_synapses_14_R.write(reinterpret_cast<char*>(&_dynamic_array_synapses_14_R[0]), _dynamic_array_synapses_14_R.size()*sizeof(_dynamic_array_synapses_14_R[0]));
		    outfile__dynamic_array_synapses_14_R.close();
		}
	} else
	{
		std::cout << "Error writing output file for _dynamic_array_synapses_14_R." << endl;
	}
	ofstream outfile__dynamic_array_synapses_14_wght;
	outfile__dynamic_array_synapses_14_wght.open("results\\_dynamic_array_synapses_14_wght_3063166055217273216", ios::binary | ios::out);
	if(outfile__dynamic_array_synapses_14_wght.is_open())
	{
        if (! _dynamic_array_synapses_14_wght.empty() )
        {
			outfile__dynamic_array_synapses_14_wght.write(reinterpret_cast<char*>(&_dynamic_array_synapses_14_wght[0]), _dynamic_array_synapses_14_wght.size()*sizeof(_dynamic_array_synapses_14_wght[0]));
		    outfile__dynamic_array_synapses_14_wght.close();
		}
	} else
	{
		std::cout << "Error writing output file for _dynamic_array_synapses_14_wght." << endl;
	}
	ofstream outfile__dynamic_array_synapses_15__synaptic_post;
	outfile__dynamic_array_synapses_15__synaptic_post.open("results\\_dynamic_array_synapses_15__synaptic_post_8485025085083106294", ios::binary | ios::out);
	if(outfile__dynamic_array_synapses_15__synaptic_post.is_open())
	{
        if (! _dynamic_array_synapses_15__synaptic_post.empty() )
        {
			outfile__dynamic_array_synapses_15__synaptic_post.write(reinterpret_cast<char*>(&_dynamic_array_synapses_15__synaptic_post[0]), _dynamic_array_synapses_15__synaptic_post.size()*sizeof(_dynamic_array_synapses_15__synaptic_post[0]));
		    outfile__dynamic_array_synapses_15__synaptic_post.close();
		}
	} else
	{
		std::cout << "Error writing output file for _dynamic_array_synapses_15__synaptic_post." << endl;
	}
	ofstream outfile__dynamic_array_synapses_15__synaptic_pre;
	outfile__dynamic_array_synapses_15__synaptic_pre.open("results\\_dynamic_array_synapses_15__synaptic_pre_7819705559062114464", ios::binary | ios::out);
	if(outfile__dynamic_array_synapses_15__synaptic_pre.is_open())
	{
        if (! _dynamic_array_synapses_15__synaptic_pre.empty() )
        {
			outfile__dynamic_array_synapses_15__synaptic_pre.write(reinterpret_cast<char*>(&_dynamic_array_synapses_15__synaptic_pre[0]), _dynamic_array_synapses_15__synaptic_pre.size()*sizeof(_dynamic_array_synapses_15__synaptic_pre[0]));
		    outfile__dynamic_array_synapses_15__synaptic_pre.close();
		}
	} else
	{
		std::cout << "Error writing output file for _dynamic_array_synapses_15__synaptic_pre." << endl;
	}
	ofstream outfile__dynamic_array_synapses_15_delay;
	outfile__dynamic_array_synapses_15_delay.open("results\\_dynamic_array_synapses_15_delay_-5940366401966571516", ios::binary | ios::out);
	if(outfile__dynamic_array_synapses_15_delay.is_open())
	{
        if (! _dynamic_array_synapses_15_delay.empty() )
        {
			outfile__dynamic_array_synapses_15_delay.write(reinterpret_cast<char*>(&_dynamic_array_synapses_15_delay[0]), _dynamic_array_synapses_15_delay.size()*sizeof(_dynamic_array_synapses_15_delay[0]));
		    outfile__dynamic_array_synapses_15_delay.close();
		}
	} else
	{
		std::cout << "Error writing output file for _dynamic_array_synapses_15_delay." << endl;
	}
	ofstream outfile__dynamic_array_synapses_15_lastupdate;
	outfile__dynamic_array_synapses_15_lastupdate.open("results\\_dynamic_array_synapses_15_lastupdate_-2581603289615955587", ios::binary | ios::out);
	if(outfile__dynamic_array_synapses_15_lastupdate.is_open())
	{
        if (! _dynamic_array_synapses_15_lastupdate.empty() )
        {
			outfile__dynamic_array_synapses_15_lastupdate.write(reinterpret_cast<char*>(&_dynamic_array_synapses_15_lastupdate[0]), _dynamic_array_synapses_15_lastupdate.size()*sizeof(_dynamic_array_synapses_15_lastupdate[0]));
		    outfile__dynamic_array_synapses_15_lastupdate.close();
		}
	} else
	{
		std::cout << "Error writing output file for _dynamic_array_synapses_15_lastupdate." << endl;
	}
	ofstream outfile__dynamic_array_synapses_15_N_incoming;
	outfile__dynamic_array_synapses_15_N_incoming.open("results\\_dynamic_array_synapses_15_N_incoming_4132398844833285974", ios::binary | ios::out);
	if(outfile__dynamic_array_synapses_15_N_incoming.is_open())
	{
        if (! _dynamic_array_synapses_15_N_incoming.empty() )
        {
			outfile__dynamic_array_synapses_15_N_incoming.write(reinterpret_cast<char*>(&_dynamic_array_synapses_15_N_incoming[0]), _dynamic_array_synapses_15_N_incoming.size()*sizeof(_dynamic_array_synapses_15_N_incoming[0]));
		    outfile__dynamic_array_synapses_15_N_incoming.close();
		}
	} else
	{
		std::cout << "Error writing output file for _dynamic_array_synapses_15_N_incoming." << endl;
	}
	ofstream outfile__dynamic_array_synapses_15_N_outgoing;
	outfile__dynamic_array_synapses_15_N_outgoing.open("results\\_dynamic_array_synapses_15_N_outgoing_8583663874874560366", ios::binary | ios::out);
	if(outfile__dynamic_array_synapses_15_N_outgoing.is_open())
	{
        if (! _dynamic_array_synapses_15_N_outgoing.empty() )
        {
			outfile__dynamic_array_synapses_15_N_outgoing.write(reinterpret_cast<char*>(&_dynamic_array_synapses_15_N_outgoing[0]), _dynamic_array_synapses_15_N_outgoing.size()*sizeof(_dynamic_array_synapses_15_N_outgoing[0]));
		    outfile__dynamic_array_synapses_15_N_outgoing.close();
		}
	} else
	{
		std::cout << "Error writing output file for _dynamic_array_synapses_15_N_outgoing." << endl;
	}
	ofstream outfile__dynamic_array_synapses_15_R;
	outfile__dynamic_array_synapses_15_R.open("results\\_dynamic_array_synapses_15_R_-6374689729046023052", ios::binary | ios::out);
	if(outfile__dynamic_array_synapses_15_R.is_open())
	{
        if (! _dynamic_array_synapses_15_R.empty() )
        {
			outfile__dynamic_array_synapses_15_R.write(reinterpret_cast<char*>(&_dynamic_array_synapses_15_R[0]), _dynamic_array_synapses_15_R.size()*sizeof(_dynamic_array_synapses_15_R[0]));
		    outfile__dynamic_array_synapses_15_R.close();
		}
	} else
	{
		std::cout << "Error writing output file for _dynamic_array_synapses_15_R." << endl;
	}
	ofstream outfile__dynamic_array_synapses_15_wght;
	outfile__dynamic_array_synapses_15_wght.open("results\\_dynamic_array_synapses_15_wght_6462024058271835001", ios::binary | ios::out);
	if(outfile__dynamic_array_synapses_15_wght.is_open())
	{
        if (! _dynamic_array_synapses_15_wght.empty() )
        {
			outfile__dynamic_array_synapses_15_wght.write(reinterpret_cast<char*>(&_dynamic_array_synapses_15_wght[0]), _dynamic_array_synapses_15_wght.size()*sizeof(_dynamic_array_synapses_15_wght[0]));
		    outfile__dynamic_array_synapses_15_wght.close();
		}
	} else
	{
		std::cout << "Error writing output file for _dynamic_array_synapses_15_wght." << endl;
	}
	ofstream outfile__dynamic_array_synapses_16__synaptic_post;
	outfile__dynamic_array_synapses_16__synaptic_post.open("results\\_dynamic_array_synapses_16__synaptic_post_-6399651174575304594", ios::binary | ios::out);
	if(outfile__dynamic_array_synapses_16__synaptic_post.is_open())
	{
        if (! _dynamic_array_synapses_16__synaptic_post.empty() )
        {
			outfile__dynamic_array_synapses_16__synaptic_post.write(reinterpret_cast<char*>(&_dynamic_array_synapses_16__synaptic_post[0]), _dynamic_array_synapses_16__synaptic_post.size()*sizeof(_dynamic_array_synapses_16__synaptic_post[0]));
		    outfile__dynamic_array_synapses_16__synaptic_post.close();
		}
	} else
	{
		std::cout << "Error writing output file for _dynamic_array_synapses_16__synaptic_post." << endl;
	}
	ofstream outfile__dynamic_array_synapses_16__synaptic_pre;
	outfile__dynamic_array_synapses_16__synaptic_pre.open("results\\_dynamic_array_synapses_16__synaptic_pre_-1979768826665012661", ios::binary | ios::out);
	if(outfile__dynamic_array_synapses_16__synaptic_pre.is_open())
	{
        if (! _dynamic_array_synapses_16__synaptic_pre.empty() )
        {
			outfile__dynamic_array_synapses_16__synaptic_pre.write(reinterpret_cast<char*>(&_dynamic_array_synapses_16__synaptic_pre[0]), _dynamic_array_synapses_16__synaptic_pre.size()*sizeof(_dynamic_array_synapses_16__synaptic_pre[0]));
		    outfile__dynamic_array_synapses_16__synaptic_pre.close();
		}
	} else
	{
		std::cout << "Error writing output file for _dynamic_array_synapses_16__synaptic_pre." << endl;
	}
	ofstream outfile__dynamic_array_synapses_16_delay;
	outfile__dynamic_array_synapses_16_delay.open("results\\_dynamic_array_synapses_16_delay_-8460385085080836509", ios::binary | ios::out);
	if(outfile__dynamic_array_synapses_16_delay.is_open())
	{
        if (! _dynamic_array_synapses_16_delay.empty() )
        {
			outfile__dynamic_array_synapses_16_delay.write(reinterpret_cast<char*>(&_dynamic_array_synapses_16_delay[0]), _dynamic_array_synapses_16_delay.size()*sizeof(_dynamic_array_synapses_16_delay[0]));
		    outfile__dynamic_array_synapses_16_delay.close();
		}
	} else
	{
		std::cout << "Error writing output file for _dynamic_array_synapses_16_delay." << endl;
	}
	ofstream outfile__dynamic_array_synapses_16_lastupdate;
	outfile__dynamic_array_synapses_16_lastupdate.open("results\\_dynamic_array_synapses_16_lastupdate_2525491572460582903", ios::binary | ios::out);
	if(outfile__dynamic_array_synapses_16_lastupdate.is_open())
	{
        if (! _dynamic_array_synapses_16_lastupdate.empty() )
        {
			outfile__dynamic_array_synapses_16_lastupdate.write(reinterpret_cast<char*>(&_dynamic_array_synapses_16_lastupdate[0]), _dynamic_array_synapses_16_lastupdate.size()*sizeof(_dynamic_array_synapses_16_lastupdate[0]));
		    outfile__dynamic_array_synapses_16_lastupdate.close();
		}
	} else
	{
		std::cout << "Error writing output file for _dynamic_array_synapses_16_lastupdate." << endl;
	}
	ofstream outfile__dynamic_array_synapses_16_N_incoming;
	outfile__dynamic_array_synapses_16_N_incoming.open("results\\_dynamic_array_synapses_16_N_incoming_-1149756027277703879", ios::binary | ios::out);
	if(outfile__dynamic_array_synapses_16_N_incoming.is_open())
	{
        if (! _dynamic_array_synapses_16_N_incoming.empty() )
        {
			outfile__dynamic_array_synapses_16_N_incoming.write(reinterpret_cast<char*>(&_dynamic_array_synapses_16_N_incoming[0]), _dynamic_array_synapses_16_N_incoming.size()*sizeof(_dynamic_array_synapses_16_N_incoming[0]));
		    outfile__dynamic_array_synapses_16_N_incoming.close();
		}
	} else
	{
		std::cout << "Error writing output file for _dynamic_array_synapses_16_N_incoming." << endl;
	}
	ofstream outfile__dynamic_array_synapses_16_N_outgoing;
	outfile__dynamic_array_synapses_16_N_outgoing.open("results\\_dynamic_array_synapses_16_N_outgoing_-4151246040542306136", ios::binary | ios::out);
	if(outfile__dynamic_array_synapses_16_N_outgoing.is_open())
	{
        if (! _dynamic_array_synapses_16_N_outgoing.empty() )
        {
			outfile__dynamic_array_synapses_16_N_outgoing.write(reinterpret_cast<char*>(&_dynamic_array_synapses_16_N_outgoing[0]), _dynamic_array_synapses_16_N_outgoing.size()*sizeof(_dynamic_array_synapses_16_N_outgoing[0]));
		    outfile__dynamic_array_synapses_16_N_outgoing.close();
		}
	} else
	{
		std::cout << "Error writing output file for _dynamic_array_synapses_16_N_outgoing." << endl;
	}
	ofstream outfile__dynamic_array_synapses_16_R;
	outfile__dynamic_array_synapses_16_R.open("results\\_dynamic_array_synapses_16_R_-9079777076509741982", ios::binary | ios::out);
	if(outfile__dynamic_array_synapses_16_R.is_open())
	{
        if (! _dynamic_array_synapses_16_R.empty() )
        {
			outfile__dynamic_array_synapses_16_R.write(reinterpret_cast<char*>(&_dynamic_array_synapses_16_R[0]), _dynamic_array_synapses_16_R.size()*sizeof(_dynamic_array_synapses_16_R[0]));
		    outfile__dynamic_array_synapses_16_R.close();
		}
	} else
	{
		std::cout << "Error writing output file for _dynamic_array_synapses_16_R." << endl;
	}
	ofstream outfile__dynamic_array_synapses_16_wght;
	outfile__dynamic_array_synapses_16_wght.open("results\\_dynamic_array_synapses_16_wght_1972927278077621848", ios::binary | ios::out);
	if(outfile__dynamic_array_synapses_16_wght.is_open())
	{
        if (! _dynamic_array_synapses_16_wght.empty() )
        {
			outfile__dynamic_array_synapses_16_wght.write(reinterpret_cast<char*>(&_dynamic_array_synapses_16_wght[0]), _dynamic_array_synapses_16_wght.size()*sizeof(_dynamic_array_synapses_16_wght[0]));
		    outfile__dynamic_array_synapses_16_wght.close();
		}
	} else
	{
		std::cout << "Error writing output file for _dynamic_array_synapses_16_wght." << endl;
	}
	ofstream outfile__dynamic_array_synapses_17__synaptic_post;
	outfile__dynamic_array_synapses_17__synaptic_post.open("results\\_dynamic_array_synapses_17__synaptic_post_-5390724365369969621", ios::binary | ios::out);
	if(outfile__dynamic_array_synapses_17__synaptic_post.is_open())
	{
        if (! _dynamic_array_synapses_17__synaptic_post.empty() )
        {
			outfile__dynamic_array_synapses_17__synaptic_post.write(reinterpret_cast<char*>(&_dynamic_array_synapses_17__synaptic_post[0]), _dynamic_array_synapses_17__synaptic_post.size()*sizeof(_dynamic_array_synapses_17__synaptic_post[0]));
		    outfile__dynamic_array_synapses_17__synaptic_post.close();
		}
	} else
	{
		std::cout << "Error writing output file for _dynamic_array_synapses_17__synaptic_post." << endl;
	}
	ofstream outfile__dynamic_array_synapses_17__synaptic_pre;
	outfile__dynamic_array_synapses_17__synaptic_pre.open("results\\_dynamic_array_synapses_17__synaptic_pre_5500128543064380467", ios::binary | ios::out);
	if(outfile__dynamic_array_synapses_17__synaptic_pre.is_open())
	{
        if (! _dynamic_array_synapses_17__synaptic_pre.empty() )
        {
			outfile__dynamic_array_synapses_17__synaptic_pre.write(reinterpret_cast<char*>(&_dynamic_array_synapses_17__synaptic_pre[0]), _dynamic_array_synapses_17__synaptic_pre.size()*sizeof(_dynamic_array_synapses_17__synaptic_pre[0]));
		    outfile__dynamic_array_synapses_17__synaptic_pre.close();
		}
	} else
	{
		std::cout << "Error writing output file for _dynamic_array_synapses_17__synaptic_pre." << endl;
	}
	ofstream outfile__dynamic_array_synapses_17_delay;
	outfile__dynamic_array_synapses_17_delay.open("results\\_dynamic_array_synapses_17_delay_-8238115337950147135", ios::binary | ios::out);
	if(outfile__dynamic_array_synapses_17_delay.is_open())
	{
        if (! _dynamic_array_synapses_17_delay.empty() )
        {
			outfile__dynamic_array_synapses_17_delay.write(reinterpret_cast<char*>(&_dynamic_array_synapses_17_delay[0]), _dynamic_array_synapses_17_delay.size()*sizeof(_dynamic_array_synapses_17_delay[0]));
		    outfile__dynamic_array_synapses_17_delay.close();
		}
	} else
	{
		std::cout << "Error writing output file for _dynamic_array_synapses_17_delay." << endl;
	}
	ofstream outfile__dynamic_array_synapses_17_lastupdate;
	outfile__dynamic_array_synapses_17_lastupdate.open("results\\_dynamic_array_synapses_17_lastupdate_4785151334131928918", ios::binary | ios::out);
	if(outfile__dynamic_array_synapses_17_lastupdate.is_open())
	{
        if (! _dynamic_array_synapses_17_lastupdate.empty() )
        {
			outfile__dynamic_array_synapses_17_lastupdate.write(reinterpret_cast<char*>(&_dynamic_array_synapses_17_lastupdate[0]), _dynamic_array_synapses_17_lastupdate.size()*sizeof(_dynamic_array_synapses_17_lastupdate[0]));
		    outfile__dynamic_array_synapses_17_lastupdate.close();
		}
	} else
	{
		std::cout << "Error writing output file for _dynamic_array_synapses_17_lastupdate." << endl;
	}
	ofstream outfile__dynamic_array_synapses_17_N_incoming;
	outfile__dynamic_array_synapses_17_N_incoming.open("results\\_dynamic_array_synapses_17_N_incoming_-8318644590053041283", ios::binary | ios::out);
	if(outfile__dynamic_array_synapses_17_N_incoming.is_open())
	{
        if (! _dynamic_array_synapses_17_N_incoming.empty() )
        {
			outfile__dynamic_array_synapses_17_N_incoming.write(reinterpret_cast<char*>(&_dynamic_array_synapses_17_N_incoming[0]), _dynamic_array_synapses_17_N_incoming.size()*sizeof(_dynamic_array_synapses_17_N_incoming[0]));
		    outfile__dynamic_array_synapses_17_N_incoming.close();
		}
	} else
	{
		std::cout << "Error writing output file for _dynamic_array_synapses_17_N_incoming." << endl;
	}
	ofstream outfile__dynamic_array_synapses_17_N_outgoing;
	outfile__dynamic_array_synapses_17_N_outgoing.open("results\\_dynamic_array_synapses_17_N_outgoing_7243775914732188878", ios::binary | ios::out);
	if(outfile__dynamic_array_synapses_17_N_outgoing.is_open())
	{
        if (! _dynamic_array_synapses_17_N_outgoing.empty() )
        {
			outfile__dynamic_array_synapses_17_N_outgoing.write(reinterpret_cast<char*>(&_dynamic_array_synapses_17_N_outgoing[0]), _dynamic_array_synapses_17_N_outgoing.size()*sizeof(_dynamic_array_synapses_17_N_outgoing[0]));
		    outfile__dynamic_array_synapses_17_N_outgoing.close();
		}
	} else
	{
		std::cout << "Error writing output file for _dynamic_array_synapses_17_N_outgoing." << endl;
	}
	ofstream outfile__dynamic_array_synapses_17_R;
	outfile__dynamic_array_synapses_17_R.open("results\\_dynamic_array_synapses_17_R_-1733346414859967379", ios::binary | ios::out);
	if(outfile__dynamic_array_synapses_17_R.is_open())
	{
        if (! _dynamic_array_synapses_17_R.empty() )
        {
			outfile__dynamic_array_synapses_17_R.write(reinterpret_cast<char*>(&_dynamic_array_synapses_17_R[0]), _dynamic_array_synapses_17_R.size()*sizeof(_dynamic_array_synapses_17_R[0]));
		    outfile__dynamic_array_synapses_17_R.close();
		}
	} else
	{
		std::cout << "Error writing output file for _dynamic_array_synapses_17_R." << endl;
	}
	ofstream outfile__dynamic_array_synapses_17_wght;
	outfile__dynamic_array_synapses_17_wght.open("results\\_dynamic_array_synapses_17_wght_4675611744587837397", ios::binary | ios::out);
	if(outfile__dynamic_array_synapses_17_wght.is_open())
	{
        if (! _dynamic_array_synapses_17_wght.empty() )
        {
			outfile__dynamic_array_synapses_17_wght.write(reinterpret_cast<char*>(&_dynamic_array_synapses_17_wght[0]), _dynamic_array_synapses_17_wght.size()*sizeof(_dynamic_array_synapses_17_wght[0]));
		    outfile__dynamic_array_synapses_17_wght.close();
		}
	} else
	{
		std::cout << "Error writing output file for _dynamic_array_synapses_17_wght." << endl;
	}
	ofstream outfile__dynamic_array_synapses_18__synaptic_post;
	outfile__dynamic_array_synapses_18__synaptic_post.open("results\\_dynamic_array_synapses_18__synaptic_post_-7870522004763955172", ios::binary | ios::out);
	if(outfile__dynamic_array_synapses_18__synaptic_post.is_open())
	{
        if (! _dynamic_array_synapses_18__synaptic_post.empty() )
        {
			outfile__dynamic_array_synapses_18__synaptic_post.write(reinterpret_cast<char*>(&_dynamic_array_synapses_18__synaptic_post[0]), _dynamic_array_synapses_18__synaptic_post.size()*sizeof(_dynamic_array_synapses_18__synaptic_post[0]));
		    outfile__dynamic_array_synapses_18__synaptic_post.close();
		}
	} else
	{
		std::cout << "Error writing output file for _dynamic_array_synapses_18__synaptic_post." << endl;
	}
	ofstream outfile__dynamic_array_synapses_18__synaptic_pre;
	outfile__dynamic_array_synapses_18__synaptic_pre.open("results\\_dynamic_array_synapses_18__synaptic_pre_-4075546359354307127", ios::binary | ios::out);
	if(outfile__dynamic_array_synapses_18__synaptic_pre.is_open())
	{
        if (! _dynamic_array_synapses_18__synaptic_pre.empty() )
        {
			outfile__dynamic_array_synapses_18__synaptic_pre.write(reinterpret_cast<char*>(&_dynamic_array_synapses_18__synaptic_pre[0]), _dynamic_array_synapses_18__synaptic_pre.size()*sizeof(_dynamic_array_synapses_18__synaptic_pre[0]));
		    outfile__dynamic_array_synapses_18__synaptic_pre.close();
		}
	} else
	{
		std::cout << "Error writing output file for _dynamic_array_synapses_18__synaptic_pre." << endl;
	}
	ofstream outfile__dynamic_array_synapses_18_delay;
	outfile__dynamic_array_synapses_18_delay.open("results\\_dynamic_array_synapses_18_delay_-8932599050570140169", ios::binary | ios::out);
	if(outfile__dynamic_array_synapses_18_delay.is_open())
	{
        if (! _dynamic_array_synapses_18_delay.empty() )
        {
			outfile__dynamic_array_synapses_18_delay.write(reinterpret_cast<char*>(&_dynamic_array_synapses_18_delay[0]), _dynamic_array_synapses_18_delay.size()*sizeof(_dynamic_array_synapses_18_delay[0]));
		    outfile__dynamic_array_synapses_18_delay.close();
		}
	} else
	{
		std::cout << "Error writing output file for _dynamic_array_synapses_18_delay." << endl;
	}
	ofstream outfile__dynamic_array_synapses_18_lastupdate;
	outfile__dynamic_array_synapses_18_lastupdate.open("results\\_dynamic_array_synapses_18_lastupdate_129858149661517971", ios::binary | ios::out);
	if(outfile__dynamic_array_synapses_18_lastupdate.is_open())
	{
        if (! _dynamic_array_synapses_18_lastupdate.empty() )
        {
			outfile__dynamic_array_synapses_18_lastupdate.write(reinterpret_cast<char*>(&_dynamic_array_synapses_18_lastupdate[0]), _dynamic_array_synapses_18_lastupdate.size()*sizeof(_dynamic_array_synapses_18_lastupdate[0]));
		    outfile__dynamic_array_synapses_18_lastupdate.close();
		}
	} else
	{
		std::cout << "Error writing output file for _dynamic_array_synapses_18_lastupdate." << endl;
	}
	ofstream outfile__dynamic_array_synapses_18_N_incoming;
	outfile__dynamic_array_synapses_18_N_incoming.open("results\\_dynamic_array_synapses_18_N_incoming_-6668525467517842092", ios::binary | ios::out);
	if(outfile__dynamic_array_synapses_18_N_incoming.is_open())
	{
        if (! _dynamic_array_synapses_18_N_incoming.empty() )
        {
			outfile__dynamic_array_synapses_18_N_incoming.write(reinterpret_cast<char*>(&_dynamic_array_synapses_18_N_incoming[0]), _dynamic_array_synapses_18_N_incoming.size()*sizeof(_dynamic_array_synapses_18_N_incoming[0]));
		    outfile__dynamic_array_synapses_18_N_incoming.close();
		}
	} else
	{
		std::cout << "Error writing output file for _dynamic_array_synapses_18_N_incoming." << endl;
	}
	ofstream outfile__dynamic_array_synapses_18_N_outgoing;
	outfile__dynamic_array_synapses_18_N_outgoing.open("results\\_dynamic_array_synapses_18_N_outgoing_5869521251448403679", ios::binary | ios::out);
	if(outfile__dynamic_array_synapses_18_N_outgoing.is_open())
	{
        if (! _dynamic_array_synapses_18_N_outgoing.empty() )
        {
			outfile__dynamic_array_synapses_18_N_outgoing.write(reinterpret_cast<char*>(&_dynamic_array_synapses_18_N_outgoing[0]), _dynamic_array_synapses_18_N_outgoing.size()*sizeof(_dynamic_array_synapses_18_N_outgoing[0]));
		    outfile__dynamic_array_synapses_18_N_outgoing.close();
		}
	} else
	{
		std::cout << "Error writing output file for _dynamic_array_synapses_18_N_outgoing." << endl;
	}
	ofstream outfile__dynamic_array_synapses_18_R;
	outfile__dynamic_array_synapses_18_R.open("results\\_dynamic_array_synapses_18_R_882743798720610094", ios::binary | ios::out);
	if(outfile__dynamic_array_synapses_18_R.is_open())
	{
        if (! _dynamic_array_synapses_18_R.empty() )
        {
			outfile__dynamic_array_synapses_18_R.write(reinterpret_cast<char*>(&_dynamic_array_synapses_18_R[0]), _dynamic_array_synapses_18_R.size()*sizeof(_dynamic_array_synapses_18_R[0]));
		    outfile__dynamic_array_synapses_18_R.close();
		}
	} else
	{
		std::cout << "Error writing output file for _dynamic_array_synapses_18_R." << endl;
	}
	ofstream outfile__dynamic_array_synapses_18_wght;
	outfile__dynamic_array_synapses_18_wght.open("results\\_dynamic_array_synapses_18_wght_571015598705084369", ios::binary | ios::out);
	if(outfile__dynamic_array_synapses_18_wght.is_open())
	{
        if (! _dynamic_array_synapses_18_wght.empty() )
        {
			outfile__dynamic_array_synapses_18_wght.write(reinterpret_cast<char*>(&_dynamic_array_synapses_18_wght[0]), _dynamic_array_synapses_18_wght.size()*sizeof(_dynamic_array_synapses_18_wght[0]));
		    outfile__dynamic_array_synapses_18_wght.close();
		}
	} else
	{
		std::cout << "Error writing output file for _dynamic_array_synapses_18_wght." << endl;
	}
	ofstream outfile__dynamic_array_synapses_19__synaptic_post;
	outfile__dynamic_array_synapses_19__synaptic_post.open("results\\_dynamic_array_synapses_19__synaptic_post_6698795439009033253", ios::binary | ios::out);
	if(outfile__dynamic_array_synapses_19__synaptic_post.is_open())
	{
        if (! _dynamic_array_synapses_19__synaptic_post.empty() )
        {
			outfile__dynamic_array_synapses_19__synaptic_post.write(reinterpret_cast<char*>(&_dynamic_array_synapses_19__synaptic_post[0]), _dynamic_array_synapses_19__synaptic_post.size()*sizeof(_dynamic_array_synapses_19__synaptic_post[0]));
		    outfile__dynamic_array_synapses_19__synaptic_post.close();
		}
	} else
	{
		std::cout << "Error writing output file for _dynamic_array_synapses_19__synaptic_post." << endl;
	}
	ofstream outfile__dynamic_array_synapses_19__synaptic_pre;
	outfile__dynamic_array_synapses_19__synaptic_pre.open("results\\_dynamic_array_synapses_19__synaptic_pre_-3639350892762106673", ios::binary | ios::out);
	if(outfile__dynamic_array_synapses_19__synaptic_pre.is_open())
	{
        if (! _dynamic_array_synapses_19__synaptic_pre.empty() )
        {
			outfile__dynamic_array_synapses_19__synaptic_pre.write(reinterpret_cast<char*>(&_dynamic_array_synapses_19__synaptic_pre[0]), _dynamic_array_synapses_19__synaptic_pre.size()*sizeof(_dynamic_array_synapses_19__synaptic_pre[0]));
		    outfile__dynamic_array_synapses_19__synaptic_pre.close();
		}
	} else
	{
		std::cout << "Error writing output file for _dynamic_array_synapses_19__synaptic_pre." << endl;
	}
	ofstream outfile__dynamic_array_synapses_19_delay;
	outfile__dynamic_array_synapses_19_delay.open("results\\_dynamic_array_synapses_19_delay_2673826646021654322", ios::binary | ios::out);
	if(outfile__dynamic_array_synapses_19_delay.is_open())
	{
        if (! _dynamic_array_synapses_19_delay.empty() )
        {
			outfile__dynamic_array_synapses_19_delay.write(reinterpret_cast<char*>(&_dynamic_array_synapses_19_delay[0]), _dynamic_array_synapses_19_delay.size()*sizeof(_dynamic_array_synapses_19_delay[0]));
		    outfile__dynamic_array_synapses_19_delay.close();
		}
	} else
	{
		std::cout << "Error writing output file for _dynamic_array_synapses_19_delay." << endl;
	}
	ofstream outfile__dynamic_array_synapses_19_lastupdate;
	outfile__dynamic_array_synapses_19_lastupdate.open("results\\_dynamic_array_synapses_19_lastupdate_3745128238511292011", ios::binary | ios::out);
	if(outfile__dynamic_array_synapses_19_lastupdate.is_open())
	{
        if (! _dynamic_array_synapses_19_lastupdate.empty() )
        {
			outfile__dynamic_array_synapses_19_lastupdate.write(reinterpret_cast<char*>(&_dynamic_array_synapses_19_lastupdate[0]), _dynamic_array_synapses_19_lastupdate.size()*sizeof(_dynamic_array_synapses_19_lastupdate[0]));
		    outfile__dynamic_array_synapses_19_lastupdate.close();
		}
	} else
	{
		std::cout << "Error writing output file for _dynamic_array_synapses_19_lastupdate." << endl;
	}
	ofstream outfile__dynamic_array_synapses_19_N_incoming;
	outfile__dynamic_array_synapses_19_N_incoming.open("results\\_dynamic_array_synapses_19_N_incoming_7066894924703060158", ios::binary | ios::out);
	if(outfile__dynamic_array_synapses_19_N_incoming.is_open())
	{
        if (! _dynamic_array_synapses_19_N_incoming.empty() )
        {
			outfile__dynamic_array_synapses_19_N_incoming.write(reinterpret_cast<char*>(&_dynamic_array_synapses_19_N_incoming[0]), _dynamic_array_synapses_19_N_incoming.size()*sizeof(_dynamic_array_synapses_19_N_incoming[0]));
		    outfile__dynamic_array_synapses_19_N_incoming.close();
		}
	} else
	{
		std::cout << "Error writing output file for _dynamic_array_synapses_19_N_incoming." << endl;
	}
	ofstream outfile__dynamic_array_synapses_19_N_outgoing;
	outfile__dynamic_array_synapses_19_N_outgoing.open("results\\_dynamic_array_synapses_19_N_outgoing_-5789417699591632633", ios::binary | ios::out);
	if(outfile__dynamic_array_synapses_19_N_outgoing.is_open())
	{
        if (! _dynamic_array_synapses_19_N_outgoing.empty() )
        {
			outfile__dynamic_array_synapses_19_N_outgoing.write(reinterpret_cast<char*>(&_dynamic_array_synapses_19_N_outgoing[0]), _dynamic_array_synapses_19_N_outgoing.size()*sizeof(_dynamic_array_synapses_19_N_outgoing[0]));
		    outfile__dynamic_array_synapses_19_N_outgoing.close();
		}
	} else
	{
		std::cout << "Error writing output file for _dynamic_array_synapses_19_N_outgoing." << endl;
	}
	ofstream outfile__dynamic_array_synapses_19_R;
	outfile__dynamic_array_synapses_19_R.open("results\\_dynamic_array_synapses_19_R_9124212147252363874", ios::binary | ios::out);
	if(outfile__dynamic_array_synapses_19_R.is_open())
	{
        if (! _dynamic_array_synapses_19_R.empty() )
        {
			outfile__dynamic_array_synapses_19_R.write(reinterpret_cast<char*>(&_dynamic_array_synapses_19_R[0]), _dynamic_array_synapses_19_R.size()*sizeof(_dynamic_array_synapses_19_R[0]));
		    outfile__dynamic_array_synapses_19_R.close();
		}
	} else
	{
		std::cout << "Error writing output file for _dynamic_array_synapses_19_R." << endl;
	}
	ofstream outfile__dynamic_array_synapses_19_wght;
	outfile__dynamic_array_synapses_19_wght.open("results\\_dynamic_array_synapses_19_wght_-4884422880289707417", ios::binary | ios::out);
	if(outfile__dynamic_array_synapses_19_wght.is_open())
	{
        if (! _dynamic_array_synapses_19_wght.empty() )
        {
			outfile__dynamic_array_synapses_19_wght.write(reinterpret_cast<char*>(&_dynamic_array_synapses_19_wght[0]), _dynamic_array_synapses_19_wght.size()*sizeof(_dynamic_array_synapses_19_wght[0]));
		    outfile__dynamic_array_synapses_19_wght.close();
		}
	} else
	{
		std::cout << "Error writing output file for _dynamic_array_synapses_19_wght." << endl;
	}
	ofstream outfile__dynamic_array_synapses_1__synaptic_post;
	outfile__dynamic_array_synapses_1__synaptic_post.open("results\\_dynamic_array_synapses_1__synaptic_post_-4328994833034138356", ios::binary | ios::out);
	if(outfile__dynamic_array_synapses_1__synaptic_post.is_open())
	{
        if (! _dynamic_array_synapses_1__synaptic_post.empty() )
        {
			outfile__dynamic_array_synapses_1__synaptic_post.write(reinterpret_cast<char*>(&_dynamic_array_synapses_1__synaptic_post[0]), _dynamic_array_synapses_1__synaptic_post.size()*sizeof(_dynamic_array_synapses_1__synaptic_post[0]));
		    outfile__dynamic_array_synapses_1__synaptic_post.close();
		}
	} else
	{
		std::cout << "Error writing output file for _dynamic_array_synapses_1__synaptic_post." << endl;
	}
	ofstream outfile__dynamic_array_synapses_1__synaptic_pre;
	outfile__dynamic_array_synapses_1__synaptic_pre.open("results\\_dynamic_array_synapses_1__synaptic_pre_-5268798294217322665", ios::binary | ios::out);
	if(outfile__dynamic_array_synapses_1__synaptic_pre.is_open())
	{
        if (! _dynamic_array_synapses_1__synaptic_pre.empty() )
        {
			outfile__dynamic_array_synapses_1__synaptic_pre.write(reinterpret_cast<char*>(&_dynamic_array_synapses_1__synaptic_pre[0]), _dynamic_array_synapses_1__synaptic_pre.size()*sizeof(_dynamic_array_synapses_1__synaptic_pre[0]));
		    outfile__dynamic_array_synapses_1__synaptic_pre.close();
		}
	} else
	{
		std::cout << "Error writing output file for _dynamic_array_synapses_1__synaptic_pre." << endl;
	}
	ofstream outfile__dynamic_array_synapses_1_delay;
	outfile__dynamic_array_synapses_1_delay.open("results\\_dynamic_array_synapses_1_delay_-9217074031402482190", ios::binary | ios::out);
	if(outfile__dynamic_array_synapses_1_delay.is_open())
	{
        if (! _dynamic_array_synapses_1_delay.empty() )
        {
			outfile__dynamic_array_synapses_1_delay.write(reinterpret_cast<char*>(&_dynamic_array_synapses_1_delay[0]), _dynamic_array_synapses_1_delay.size()*sizeof(_dynamic_array_synapses_1_delay[0]));
		    outfile__dynamic_array_synapses_1_delay.close();
		}
	} else
	{
		std::cout << "Error writing output file for _dynamic_array_synapses_1_delay." << endl;
	}
	ofstream outfile__dynamic_array_synapses_1_lastupdate;
	outfile__dynamic_array_synapses_1_lastupdate.open("results\\_dynamic_array_synapses_1_lastupdate_1808345919649038444", ios::binary | ios::out);
	if(outfile__dynamic_array_synapses_1_lastupdate.is_open())
	{
        if (! _dynamic_array_synapses_1_lastupdate.empty() )
        {
			outfile__dynamic_array_synapses_1_lastupdate.write(reinterpret_cast<char*>(&_dynamic_array_synapses_1_lastupdate[0]), _dynamic_array_synapses_1_lastupdate.size()*sizeof(_dynamic_array_synapses_1_lastupdate[0]));
		    outfile__dynamic_array_synapses_1_lastupdate.close();
		}
	} else
	{
		std::cout << "Error writing output file for _dynamic_array_synapses_1_lastupdate." << endl;
	}
	ofstream outfile__dynamic_array_synapses_1_N_incoming;
	outfile__dynamic_array_synapses_1_N_incoming.open("results\\_dynamic_array_synapses_1_N_incoming_-6598903573148709615", ios::binary | ios::out);
	if(outfile__dynamic_array_synapses_1_N_incoming.is_open())
	{
        if (! _dynamic_array_synapses_1_N_incoming.empty() )
        {
			outfile__dynamic_array_synapses_1_N_incoming.write(reinterpret_cast<char*>(&_dynamic_array_synapses_1_N_incoming[0]), _dynamic_array_synapses_1_N_incoming.size()*sizeof(_dynamic_array_synapses_1_N_incoming[0]));
		    outfile__dynamic_array_synapses_1_N_incoming.close();
		}
	} else
	{
		std::cout << "Error writing output file for _dynamic_array_synapses_1_N_incoming." << endl;
	}
	ofstream outfile__dynamic_array_synapses_1_N_outgoing;
	outfile__dynamic_array_synapses_1_N_outgoing.open("results\\_dynamic_array_synapses_1_N_outgoing_-6901531541381477809", ios::binary | ios::out);
	if(outfile__dynamic_array_synapses_1_N_outgoing.is_open())
	{
        if (! _dynamic_array_synapses_1_N_outgoing.empty() )
        {
			outfile__dynamic_array_synapses_1_N_outgoing.write(reinterpret_cast<char*>(&_dynamic_array_synapses_1_N_outgoing[0]), _dynamic_array_synapses_1_N_outgoing.size()*sizeof(_dynamic_array_synapses_1_N_outgoing[0]));
		    outfile__dynamic_array_synapses_1_N_outgoing.close();
		}
	} else
	{
		std::cout << "Error writing output file for _dynamic_array_synapses_1_N_outgoing." << endl;
	}
	ofstream outfile__dynamic_array_synapses_1_R;
	outfile__dynamic_array_synapses_1_R.open("results\\_dynamic_array_synapses_1_R_3946271599657743805", ios::binary | ios::out);
	if(outfile__dynamic_array_synapses_1_R.is_open())
	{
        if (! _dynamic_array_synapses_1_R.empty() )
        {
			outfile__dynamic_array_synapses_1_R.write(reinterpret_cast<char*>(&_dynamic_array_synapses_1_R[0]), _dynamic_array_synapses_1_R.size()*sizeof(_dynamic_array_synapses_1_R[0]));
		    outfile__dynamic_array_synapses_1_R.close();
		}
	} else
	{
		std::cout << "Error writing output file for _dynamic_array_synapses_1_R." << endl;
	}
	ofstream outfile__dynamic_array_synapses_1_wght;
	outfile__dynamic_array_synapses_1_wght.open("results\\_dynamic_array_synapses_1_wght_-3083580538810141533", ios::binary | ios::out);
	if(outfile__dynamic_array_synapses_1_wght.is_open())
	{
        if (! _dynamic_array_synapses_1_wght.empty() )
        {
			outfile__dynamic_array_synapses_1_wght.write(reinterpret_cast<char*>(&_dynamic_array_synapses_1_wght[0]), _dynamic_array_synapses_1_wght.size()*sizeof(_dynamic_array_synapses_1_wght[0]));
		    outfile__dynamic_array_synapses_1_wght.close();
		}
	} else
	{
		std::cout << "Error writing output file for _dynamic_array_synapses_1_wght." << endl;
	}
	ofstream outfile__dynamic_array_synapses_20__synaptic_post;
	outfile__dynamic_array_synapses_20__synaptic_post.open("results\\_dynamic_array_synapses_20__synaptic_post_8380812780287294568", ios::binary | ios::out);
	if(outfile__dynamic_array_synapses_20__synaptic_post.is_open())
	{
        if (! _dynamic_array_synapses_20__synaptic_post.empty() )
        {
			outfile__dynamic_array_synapses_20__synaptic_post.write(reinterpret_cast<char*>(&_dynamic_array_synapses_20__synaptic_post[0]), _dynamic_array_synapses_20__synaptic_post.size()*sizeof(_dynamic_array_synapses_20__synaptic_post[0]));
		    outfile__dynamic_array_synapses_20__synaptic_post.close();
		}
	} else
	{
		std::cout << "Error writing output file for _dynamic_array_synapses_20__synaptic_post." << endl;
	}
	ofstream outfile__dynamic_array_synapses_20__synaptic_pre;
	outfile__dynamic_array_synapses_20__synaptic_pre.open("results\\_dynamic_array_synapses_20__synaptic_pre_4082738027716725517", ios::binary | ios::out);
	if(outfile__dynamic_array_synapses_20__synaptic_pre.is_open())
	{
        if (! _dynamic_array_synapses_20__synaptic_pre.empty() )
        {
			outfile__dynamic_array_synapses_20__synaptic_pre.write(reinterpret_cast<char*>(&_dynamic_array_synapses_20__synaptic_pre[0]), _dynamic_array_synapses_20__synaptic_pre.size()*sizeof(_dynamic_array_synapses_20__synaptic_pre[0]));
		    outfile__dynamic_array_synapses_20__synaptic_pre.close();
		}
	} else
	{
		std::cout << "Error writing output file for _dynamic_array_synapses_20__synaptic_pre." << endl;
	}
	ofstream outfile__dynamic_array_synapses_20_delay;
	outfile__dynamic_array_synapses_20_delay.open("results\\_dynamic_array_synapses_20_delay_-3632461793374085295", ios::binary | ios::out);
	if(outfile__dynamic_array_synapses_20_delay.is_open())
	{
        if (! _dynamic_array_synapses_20_delay.empty() )
        {
			outfile__dynamic_array_synapses_20_delay.write(reinterpret_cast<char*>(&_dynamic_array_synapses_20_delay[0]), _dynamic_array_synapses_20_delay.size()*sizeof(_dynamic_array_synapses_20_delay[0]));
		    outfile__dynamic_array_synapses_20_delay.close();
		}
	} else
	{
		std::cout << "Error writing output file for _dynamic_array_synapses_20_delay." << endl;
	}
	ofstream outfile__dynamic_array_synapses_20_lastupdate;
	outfile__dynamic_array_synapses_20_lastupdate.open("results\\_dynamic_array_synapses_20_lastupdate_8480413214458074901", ios::binary | ios::out);
	if(outfile__dynamic_array_synapses_20_lastupdate.is_open())
	{
        if (! _dynamic_array_synapses_20_lastupdate.empty() )
        {
			outfile__dynamic_array_synapses_20_lastupdate.write(reinterpret_cast<char*>(&_dynamic_array_synapses_20_lastupdate[0]), _dynamic_array_synapses_20_lastupdate.size()*sizeof(_dynamic_array_synapses_20_lastupdate[0]));
		    outfile__dynamic_array_synapses_20_lastupdate.close();
		}
	} else
	{
		std::cout << "Error writing output file for _dynamic_array_synapses_20_lastupdate." << endl;
	}
	ofstream outfile__dynamic_array_synapses_20_N_incoming;
	outfile__dynamic_array_synapses_20_N_incoming.open("results\\_dynamic_array_synapses_20_N_incoming_-622531726432766923", ios::binary | ios::out);
	if(outfile__dynamic_array_synapses_20_N_incoming.is_open())
	{
        if (! _dynamic_array_synapses_20_N_incoming.empty() )
        {
			outfile__dynamic_array_synapses_20_N_incoming.write(reinterpret_cast<char*>(&_dynamic_array_synapses_20_N_incoming[0]), _dynamic_array_synapses_20_N_incoming.size()*sizeof(_dynamic_array_synapses_20_N_incoming[0]));
		    outfile__dynamic_array_synapses_20_N_incoming.close();
		}
	} else
	{
		std::cout << "Error writing output file for _dynamic_array_synapses_20_N_incoming." << endl;
	}
	ofstream outfile__dynamic_array_synapses_20_N_outgoing;
	outfile__dynamic_array_synapses_20_N_outgoing.open("results\\_dynamic_array_synapses_20_N_outgoing_-5143265631346154058", ios::binary | ios::out);
	if(outfile__dynamic_array_synapses_20_N_outgoing.is_open())
	{
        if (! _dynamic_array_synapses_20_N_outgoing.empty() )
        {
			outfile__dynamic_array_synapses_20_N_outgoing.write(reinterpret_cast<char*>(&_dynamic_array_synapses_20_N_outgoing[0]), _dynamic_array_synapses_20_N_outgoing.size()*sizeof(_dynamic_array_synapses_20_N_outgoing[0]));
		    outfile__dynamic_array_synapses_20_N_outgoing.close();
		}
	} else
	{
		std::cout << "Error writing output file for _dynamic_array_synapses_20_N_outgoing." << endl;
	}
	ofstream outfile__dynamic_array_synapses_20_R;
	outfile__dynamic_array_synapses_20_R.open("results\\_dynamic_array_synapses_20_R_-2044036879699610418", ios::binary | ios::out);
	if(outfile__dynamic_array_synapses_20_R.is_open())
	{
        if (! _dynamic_array_synapses_20_R.empty() )
        {
			outfile__dynamic_array_synapses_20_R.write(reinterpret_cast<char*>(&_dynamic_array_synapses_20_R[0]), _dynamic_array_synapses_20_R.size()*sizeof(_dynamic_array_synapses_20_R[0]));
		    outfile__dynamic_array_synapses_20_R.close();
		}
	} else
	{
		std::cout << "Error writing output file for _dynamic_array_synapses_20_R." << endl;
	}
	ofstream outfile__dynamic_array_synapses_20_wght;
	outfile__dynamic_array_synapses_20_wght.open("results\\_dynamic_array_synapses_20_wght_-6882763546927370823", ios::binary | ios::out);
	if(outfile__dynamic_array_synapses_20_wght.is_open())
	{
        if (! _dynamic_array_synapses_20_wght.empty() )
        {
			outfile__dynamic_array_synapses_20_wght.write(reinterpret_cast<char*>(&_dynamic_array_synapses_20_wght[0]), _dynamic_array_synapses_20_wght.size()*sizeof(_dynamic_array_synapses_20_wght[0]));
		    outfile__dynamic_array_synapses_20_wght.close();
		}
	} else
	{
		std::cout << "Error writing output file for _dynamic_array_synapses_20_wght." << endl;
	}
	ofstream outfile__dynamic_array_synapses_21__synaptic_post;
	outfile__dynamic_array_synapses_21__synaptic_post.open("results\\_dynamic_array_synapses_21__synaptic_post_3430531953109100335", ios::binary | ios::out);
	if(outfile__dynamic_array_synapses_21__synaptic_post.is_open())
	{
        if (! _dynamic_array_synapses_21__synaptic_post.empty() )
        {
			outfile__dynamic_array_synapses_21__synaptic_post.write(reinterpret_cast<char*>(&_dynamic_array_synapses_21__synaptic_post[0]), _dynamic_array_synapses_21__synaptic_post.size()*sizeof(_dynamic_array_synapses_21__synaptic_post[0]));
		    outfile__dynamic_array_synapses_21__synaptic_post.close();
		}
	} else
	{
		std::cout << "Error writing output file for _dynamic_array_synapses_21__synaptic_post." << endl;
	}
	ofstream outfile__dynamic_array_synapses_21__synaptic_pre;
	outfile__dynamic_array_synapses_21__synaptic_pre.open("results\\_dynamic_array_synapses_21__synaptic_pre_5554135877981805776", ios::binary | ios::out);
	if(outfile__dynamic_array_synapses_21__synaptic_pre.is_open())
	{
        if (! _dynamic_array_synapses_21__synaptic_pre.empty() )
        {
			outfile__dynamic_array_synapses_21__synaptic_pre.write(reinterpret_cast<char*>(&_dynamic_array_synapses_21__synaptic_pre[0]), _dynamic_array_synapses_21__synaptic_pre.size()*sizeof(_dynamic_array_synapses_21__synaptic_pre[0]));
		    outfile__dynamic_array_synapses_21__synaptic_pre.close();
		}
	} else
	{
		std::cout << "Error writing output file for _dynamic_array_synapses_21__synaptic_pre." << endl;
	}
	ofstream outfile__dynamic_array_synapses_21_delay;
	outfile__dynamic_array_synapses_21_delay.open("results\\_dynamic_array_synapses_21_delay_-2617207447202652942", ios::binary | ios::out);
	if(outfile__dynamic_array_synapses_21_delay.is_open())
	{
        if (! _dynamic_array_synapses_21_delay.empty() )
        {
			outfile__dynamic_array_synapses_21_delay.write(reinterpret_cast<char*>(&_dynamic_array_synapses_21_delay[0]), _dynamic_array_synapses_21_delay.size()*sizeof(_dynamic_array_synapses_21_delay[0]));
		    outfile__dynamic_array_synapses_21_delay.close();
		}
	} else
	{
		std::cout << "Error writing output file for _dynamic_array_synapses_21_delay." << endl;
	}
	ofstream outfile__dynamic_array_synapses_21_lastupdate;
	outfile__dynamic_array_synapses_21_lastupdate.open("results\\_dynamic_array_synapses_21_lastupdate_7588937162380615164", ios::binary | ios::out);
	if(outfile__dynamic_array_synapses_21_lastupdate.is_open())
	{
        if (! _dynamic_array_synapses_21_lastupdate.empty() )
        {
			outfile__dynamic_array_synapses_21_lastupdate.write(reinterpret_cast<char*>(&_dynamic_array_synapses_21_lastupdate[0]), _dynamic_array_synapses_21_lastupdate.size()*sizeof(_dynamic_array_synapses_21_lastupdate[0]));
		    outfile__dynamic_array_synapses_21_lastupdate.close();
		}
	} else
	{
		std::cout << "Error writing output file for _dynamic_array_synapses_21_lastupdate." << endl;
	}
	ofstream outfile__dynamic_array_synapses_21_N_incoming;
	outfile__dynamic_array_synapses_21_N_incoming.open("results\\_dynamic_array_synapses_21_N_incoming_-736319395172984229", ios::binary | ios::out);
	if(outfile__dynamic_array_synapses_21_N_incoming.is_open())
	{
        if (! _dynamic_array_synapses_21_N_incoming.empty() )
        {
			outfile__dynamic_array_synapses_21_N_incoming.write(reinterpret_cast<char*>(&_dynamic_array_synapses_21_N_incoming[0]), _dynamic_array_synapses_21_N_incoming.size()*sizeof(_dynamic_array_synapses_21_N_incoming[0]));
		    outfile__dynamic_array_synapses_21_N_incoming.close();
		}
	} else
	{
		std::cout << "Error writing output file for _dynamic_array_synapses_21_N_incoming." << endl;
	}
	ofstream outfile__dynamic_array_synapses_21_N_outgoing;
	outfile__dynamic_array_synapses_21_N_outgoing.open("results\\_dynamic_array_synapses_21_N_outgoing_-78850260009287415", ios::binary | ios::out);
	if(outfile__dynamic_array_synapses_21_N_outgoing.is_open())
	{
        if (! _dynamic_array_synapses_21_N_outgoing.empty() )
        {
			outfile__dynamic_array_synapses_21_N_outgoing.write(reinterpret_cast<char*>(&_dynamic_array_synapses_21_N_outgoing[0]), _dynamic_array_synapses_21_N_outgoing.size()*sizeof(_dynamic_array_synapses_21_N_outgoing[0]));
		    outfile__dynamic_array_synapses_21_N_outgoing.close();
		}
	} else
	{
		std::cout << "Error writing output file for _dynamic_array_synapses_21_N_outgoing." << endl;
	}
	ofstream outfile__dynamic_array_synapses_21_R;
	outfile__dynamic_array_synapses_21_R.open("results\\_dynamic_array_synapses_21_R_-1597558454955318268", ios::binary | ios::out);
	if(outfile__dynamic_array_synapses_21_R.is_open())
	{
        if (! _dynamic_array_synapses_21_R.empty() )
        {
			outfile__dynamic_array_synapses_21_R.write(reinterpret_cast<char*>(&_dynamic_array_synapses_21_R[0]), _dynamic_array_synapses_21_R.size()*sizeof(_dynamic_array_synapses_21_R[0]));
		    outfile__dynamic_array_synapses_21_R.close();
		}
	} else
	{
		std::cout << "Error writing output file for _dynamic_array_synapses_21_R." << endl;
	}
	ofstream outfile__dynamic_array_synapses_21_wght;
	outfile__dynamic_array_synapses_21_wght.open("results\\_dynamic_array_synapses_21_wght_510719741942044154", ios::binary | ios::out);
	if(outfile__dynamic_array_synapses_21_wght.is_open())
	{
        if (! _dynamic_array_synapses_21_wght.empty() )
        {
			outfile__dynamic_array_synapses_21_wght.write(reinterpret_cast<char*>(&_dynamic_array_synapses_21_wght[0]), _dynamic_array_synapses_21_wght.size()*sizeof(_dynamic_array_synapses_21_wght[0]));
		    outfile__dynamic_array_synapses_21_wght.close();
		}
	} else
	{
		std::cout << "Error writing output file for _dynamic_array_synapses_21_wght." << endl;
	}
	ofstream outfile__dynamic_array_synapses_22__synaptic_post;
	outfile__dynamic_array_synapses_22__synaptic_post.open("results\\_dynamic_array_synapses_22__synaptic_post_-5292398919031583481", ios::binary | ios::out);
	if(outfile__dynamic_array_synapses_22__synaptic_post.is_open())
	{
        if (! _dynamic_array_synapses_22__synaptic_post.empty() )
        {
			outfile__dynamic_array_synapses_22__synaptic_post.write(reinterpret_cast<char*>(&_dynamic_array_synapses_22__synaptic_post[0]), _dynamic_array_synapses_22__synaptic_post.size()*sizeof(_dynamic_array_synapses_22__synaptic_post[0]));
		    outfile__dynamic_array_synapses_22__synaptic_post.close();
		}
	} else
	{
		std::cout << "Error writing output file for _dynamic_array_synapses_22__synaptic_post." << endl;
	}
	ofstream outfile__dynamic_array_synapses_22__synaptic_pre;
	outfile__dynamic_array_synapses_22__synaptic_pre.open("results\\_dynamic_array_synapses_22__synaptic_pre_5844308290132469283", ios::binary | ios::out);
	if(outfile__dynamic_array_synapses_22__synaptic_pre.is_open())
	{
        if (! _dynamic_array_synapses_22__synaptic_pre.empty() )
        {
			outfile__dynamic_array_synapses_22__synaptic_pre.write(reinterpret_cast<char*>(&_dynamic_array_synapses_22__synaptic_pre[0]), _dynamic_array_synapses_22__synaptic_pre.size()*sizeof(_dynamic_array_synapses_22__synaptic_pre[0]));
		    outfile__dynamic_array_synapses_22__synaptic_pre.close();
		}
	} else
	{
		std::cout << "Error writing output file for _dynamic_array_synapses_22__synaptic_pre." << endl;
	}
	ofstream outfile__dynamic_array_synapses_22_delay;
	outfile__dynamic_array_synapses_22_delay.open("results\\_dynamic_array_synapses_22_delay_6067609940011655009", ios::binary | ios::out);
	if(outfile__dynamic_array_synapses_22_delay.is_open())
	{
        if (! _dynamic_array_synapses_22_delay.empty() )
        {
			outfile__dynamic_array_synapses_22_delay.write(reinterpret_cast<char*>(&_dynamic_array_synapses_22_delay[0]), _dynamic_array_synapses_22_delay.size()*sizeof(_dynamic_array_synapses_22_delay[0]));
		    outfile__dynamic_array_synapses_22_delay.close();
		}
	} else
	{
		std::cout << "Error writing output file for _dynamic_array_synapses_22_delay." << endl;
	}
	ofstream outfile__dynamic_array_synapses_22_lastupdate;
	outfile__dynamic_array_synapses_22_lastupdate.open("results\\_dynamic_array_synapses_22_lastupdate_-2094609428572956241", ios::binary | ios::out);
	if(outfile__dynamic_array_synapses_22_lastupdate.is_open())
	{
        if (! _dynamic_array_synapses_22_lastupdate.empty() )
        {
			outfile__dynamic_array_synapses_22_lastupdate.write(reinterpret_cast<char*>(&_dynamic_array_synapses_22_lastupdate[0]), _dynamic_array_synapses_22_lastupdate.size()*sizeof(_dynamic_array_synapses_22_lastupdate[0]));
		    outfile__dynamic_array_synapses_22_lastupdate.close();
		}
	} else
	{
		std::cout << "Error writing output file for _dynamic_array_synapses_22_lastupdate." << endl;
	}
	ofstream outfile__dynamic_array_synapses_22_N_incoming;
	outfile__dynamic_array_synapses_22_N_incoming.open("results\\_dynamic_array_synapses_22_N_incoming_5905867618539196899", ios::binary | ios::out);
	if(outfile__dynamic_array_synapses_22_N_incoming.is_open())
	{
        if (! _dynamic_array_synapses_22_N_incoming.empty() )
        {
			outfile__dynamic_array_synapses_22_N_incoming.write(reinterpret_cast<char*>(&_dynamic_array_synapses_22_N_incoming[0]), _dynamic_array_synapses_22_N_incoming.size()*sizeof(_dynamic_array_synapses_22_N_incoming[0]));
		    outfile__dynamic_array_synapses_22_N_incoming.close();
		}
	} else
	{
		std::cout << "Error writing output file for _dynamic_array_synapses_22_N_incoming." << endl;
	}
	ofstream outfile__dynamic_array_synapses_22_N_outgoing;
	outfile__dynamic_array_synapses_22_N_outgoing.open("results\\_dynamic_array_synapses_22_N_outgoing_9121558550112735491", ios::binary | ios::out);
	if(outfile__dynamic_array_synapses_22_N_outgoing.is_open())
	{
        if (! _dynamic_array_synapses_22_N_outgoing.empty() )
        {
			outfile__dynamic_array_synapses_22_N_outgoing.write(reinterpret_cast<char*>(&_dynamic_array_synapses_22_N_outgoing[0]), _dynamic_array_synapses_22_N_outgoing.size()*sizeof(_dynamic_array_synapses_22_N_outgoing[0]));
		    outfile__dynamic_array_synapses_22_N_outgoing.close();
		}
	} else
	{
		std::cout << "Error writing output file for _dynamic_array_synapses_22_N_outgoing." << endl;
	}
	ofstream outfile__dynamic_array_synapses_22_R;
	outfile__dynamic_array_synapses_22_R.open("results\\_dynamic_array_synapses_22_R_-4073481493659015424", ios::binary | ios::out);
	if(outfile__dynamic_array_synapses_22_R.is_open())
	{
        if (! _dynamic_array_synapses_22_R.empty() )
        {
			outfile__dynamic_array_synapses_22_R.write(reinterpret_cast<char*>(&_dynamic_array_synapses_22_R[0]), _dynamic_array_synapses_22_R.size()*sizeof(_dynamic_array_synapses_22_R[0]));
		    outfile__dynamic_array_synapses_22_R.close();
		}
	} else
	{
		std::cout << "Error writing output file for _dynamic_array_synapses_22_R." << endl;
	}
	ofstream outfile__dynamic_array_synapses_22_wght;
	outfile__dynamic_array_synapses_22_wght.open("results\\_dynamic_array_synapses_22_wght_-5797457005278961793", ios::binary | ios::out);
	if(outfile__dynamic_array_synapses_22_wght.is_open())
	{
        if (! _dynamic_array_synapses_22_wght.empty() )
        {
			outfile__dynamic_array_synapses_22_wght.write(reinterpret_cast<char*>(&_dynamic_array_synapses_22_wght[0]), _dynamic_array_synapses_22_wght.size()*sizeof(_dynamic_array_synapses_22_wght[0]));
		    outfile__dynamic_array_synapses_22_wght.close();
		}
	} else
	{
		std::cout << "Error writing output file for _dynamic_array_synapses_22_wght." << endl;
	}
	ofstream outfile__dynamic_array_synapses_23__synaptic_post;
	outfile__dynamic_array_synapses_23__synaptic_post.open("results\\_dynamic_array_synapses_23__synaptic_post_767282795163826549", ios::binary | ios::out);
	if(outfile__dynamic_array_synapses_23__synaptic_post.is_open())
	{
        if (! _dynamic_array_synapses_23__synaptic_post.empty() )
        {
			outfile__dynamic_array_synapses_23__synaptic_post.write(reinterpret_cast<char*>(&_dynamic_array_synapses_23__synaptic_post[0]), _dynamic_array_synapses_23__synaptic_post.size()*sizeof(_dynamic_array_synapses_23__synaptic_post[0]));
		    outfile__dynamic_array_synapses_23__synaptic_post.close();
		}
	} else
	{
		std::cout << "Error writing output file for _dynamic_array_synapses_23__synaptic_post." << endl;
	}
	ofstream outfile__dynamic_array_synapses_23__synaptic_pre;
	outfile__dynamic_array_synapses_23__synaptic_pre.open("results\\_dynamic_array_synapses_23__synaptic_pre_8270039311533031155", ios::binary | ios::out);
	if(outfile__dynamic_array_synapses_23__synaptic_pre.is_open())
	{
        if (! _dynamic_array_synapses_23__synaptic_pre.empty() )
        {
			outfile__dynamic_array_synapses_23__synaptic_pre.write(reinterpret_cast<char*>(&_dynamic_array_synapses_23__synaptic_pre[0]), _dynamic_array_synapses_23__synaptic_pre.size()*sizeof(_dynamic_array_synapses_23__synaptic_pre[0]));
		    outfile__dynamic_array_synapses_23__synaptic_pre.close();
		}
	} else
	{
		std::cout << "Error writing output file for _dynamic_array_synapses_23__synaptic_pre." << endl;
	}
	ofstream outfile__dynamic_array_synapses_23_delay;
	outfile__dynamic_array_synapses_23_delay.open("results\\_dynamic_array_synapses_23_delay_-2188905030936151337", ios::binary | ios::out);
	if(outfile__dynamic_array_synapses_23_delay.is_open())
	{
        if (! _dynamic_array_synapses_23_delay.empty() )
        {
			outfile__dynamic_array_synapses_23_delay.write(reinterpret_cast<char*>(&_dynamic_array_synapses_23_delay[0]), _dynamic_array_synapses_23_delay.size()*sizeof(_dynamic_array_synapses_23_delay[0]));
		    outfile__dynamic_array_synapses_23_delay.close();
		}
	} else
	{
		std::cout << "Error writing output file for _dynamic_array_synapses_23_delay." << endl;
	}
	ofstream outfile__dynamic_array_synapses_23_lastupdate;
	outfile__dynamic_array_synapses_23_lastupdate.open("results\\_dynamic_array_synapses_23_lastupdate_-7922782247615458997", ios::binary | ios::out);
	if(outfile__dynamic_array_synapses_23_lastupdate.is_open())
	{
        if (! _dynamic_array_synapses_23_lastupdate.empty() )
        {
			outfile__dynamic_array_synapses_23_lastupdate.write(reinterpret_cast<char*>(&_dynamic_array_synapses_23_lastupdate[0]), _dynamic_array_synapses_23_lastupdate.size()*sizeof(_dynamic_array_synapses_23_lastupdate[0]));
		    outfile__dynamic_array_synapses_23_lastupdate.close();
		}
	} else
	{
		std::cout << "Error writing output file for _dynamic_array_synapses_23_lastupdate." << endl;
	}
	ofstream outfile__dynamic_array_synapses_23_N_incoming;
	outfile__dynamic_array_synapses_23_N_incoming.open("results\\_dynamic_array_synapses_23_N_incoming_8222057182831588775", ios::binary | ios::out);
	if(outfile__dynamic_array_synapses_23_N_incoming.is_open())
	{
        if (! _dynamic_array_synapses_23_N_incoming.empty() )
        {
			outfile__dynamic_array_synapses_23_N_incoming.write(reinterpret_cast<char*>(&_dynamic_array_synapses_23_N_incoming[0]), _dynamic_array_synapses_23_N_incoming.size()*sizeof(_dynamic_array_synapses_23_N_incoming[0]));
		    outfile__dynamic_array_synapses_23_N_incoming.close();
		}
	} else
	{
		std::cout << "Error writing output file for _dynamic_array_synapses_23_N_incoming." << endl;
	}
	ofstream outfile__dynamic_array_synapses_23_N_outgoing;
	outfile__dynamic_array_synapses_23_N_outgoing.open("results\\_dynamic_array_synapses_23_N_outgoing_-3192476626257328768", ios::binary | ios::out);
	if(outfile__dynamic_array_synapses_23_N_outgoing.is_open())
	{
        if (! _dynamic_array_synapses_23_N_outgoing.empty() )
        {
			outfile__dynamic_array_synapses_23_N_outgoing.write(reinterpret_cast<char*>(&_dynamic_array_synapses_23_N_outgoing[0]), _dynamic_array_synapses_23_N_outgoing.size()*sizeof(_dynamic_array_synapses_23_N_outgoing[0]));
		    outfile__dynamic_array_synapses_23_N_outgoing.close();
		}
	} else
	{
		std::cout << "Error writing output file for _dynamic_array_synapses_23_N_outgoing." << endl;
	}
	ofstream outfile__dynamic_array_synapses_23_R;
	outfile__dynamic_array_synapses_23_R.open("results\\_dynamic_array_synapses_23_R_-9104384278395482768", ios::binary | ios::out);
	if(outfile__dynamic_array_synapses_23_R.is_open())
	{
        if (! _dynamic_array_synapses_23_R.empty() )
        {
			outfile__dynamic_array_synapses_23_R.write(reinterpret_cast<char*>(&_dynamic_array_synapses_23_R[0]), _dynamic_array_synapses_23_R.size()*sizeof(_dynamic_array_synapses_23_R[0]));
		    outfile__dynamic_array_synapses_23_R.close();
		}
	} else
	{
		std::cout << "Error writing output file for _dynamic_array_synapses_23_R." << endl;
	}
	ofstream outfile__dynamic_array_synapses_23_wght;
	outfile__dynamic_array_synapses_23_wght.open("results\\_dynamic_array_synapses_23_wght_-3927153111063474786", ios::binary | ios::out);
	if(outfile__dynamic_array_synapses_23_wght.is_open())
	{
        if (! _dynamic_array_synapses_23_wght.empty() )
        {
			outfile__dynamic_array_synapses_23_wght.write(reinterpret_cast<char*>(&_dynamic_array_synapses_23_wght[0]), _dynamic_array_synapses_23_wght.size()*sizeof(_dynamic_array_synapses_23_wght[0]));
		    outfile__dynamic_array_synapses_23_wght.close();
		}
	} else
	{
		std::cout << "Error writing output file for _dynamic_array_synapses_23_wght." << endl;
	}
	ofstream outfile__dynamic_array_synapses_24__synaptic_post;
	outfile__dynamic_array_synapses_24__synaptic_post.open("results\\_dynamic_array_synapses_24__synaptic_post_4126900000679179656", ios::binary | ios::out);
	if(outfile__dynamic_array_synapses_24__synaptic_post.is_open())
	{
        if (! _dynamic_array_synapses_24__synaptic_post.empty() )
        {
			outfile__dynamic_array_synapses_24__synaptic_post.write(reinterpret_cast<char*>(&_dynamic_array_synapses_24__synaptic_post[0]), _dynamic_array_synapses_24__synaptic_post.size()*sizeof(_dynamic_array_synapses_24__synaptic_post[0]));
		    outfile__dynamic_array_synapses_24__synaptic_post.close();
		}
	} else
	{
		std::cout << "Error writing output file for _dynamic_array_synapses_24__synaptic_post." << endl;
	}
	ofstream outfile__dynamic_array_synapses_24__synaptic_pre;
	outfile__dynamic_array_synapses_24__synaptic_pre.open("results\\_dynamic_array_synapses_24__synaptic_pre_5708257385003294776", ios::binary | ios::out);
	if(outfile__dynamic_array_synapses_24__synaptic_pre.is_open())
	{
        if (! _dynamic_array_synapses_24__synaptic_pre.empty() )
        {
			outfile__dynamic_array_synapses_24__synaptic_pre.write(reinterpret_cast<char*>(&_dynamic_array_synapses_24__synaptic_pre[0]), _dynamic_array_synapses_24__synaptic_pre.size()*sizeof(_dynamic_array_synapses_24__synaptic_pre[0]));
		    outfile__dynamic_array_synapses_24__synaptic_pre.close();
		}
	} else
	{
		std::cout << "Error writing output file for _dynamic_array_synapses_24__synaptic_pre." << endl;
	}
	ofstream outfile__dynamic_array_synapses_24_delay;
	outfile__dynamic_array_synapses_24_delay.open("results\\_dynamic_array_synapses_24_delay_-8788117187544191548", ios::binary | ios::out);
	if(outfile__dynamic_array_synapses_24_delay.is_open())
	{
        if (! _dynamic_array_synapses_24_delay.empty() )
        {
			outfile__dynamic_array_synapses_24_delay.write(reinterpret_cast<char*>(&_dynamic_array_synapses_24_delay[0]), _dynamic_array_synapses_24_delay.size()*sizeof(_dynamic_array_synapses_24_delay[0]));
		    outfile__dynamic_array_synapses_24_delay.close();
		}
	} else
	{
		std::cout << "Error writing output file for _dynamic_array_synapses_24_delay." << endl;
	}
	ofstream outfile__dynamic_array_synapses_24_lastupdate;
	outfile__dynamic_array_synapses_24_lastupdate.open("results\\_dynamic_array_synapses_24_lastupdate_-4092549459851089692", ios::binary | ios::out);
	if(outfile__dynamic_array_synapses_24_lastupdate.is_open())
	{
        if (! _dynamic_array_synapses_24_lastupdate.empty() )
        {
			outfile__dynamic_array_synapses_24_lastupdate.write(reinterpret_cast<char*>(&_dynamic_array_synapses_24_lastupdate[0]), _dynamic_array_synapses_24_lastupdate.size()*sizeof(_dynamic_array_synapses_24_lastupdate[0]));
		    outfile__dynamic_array_synapses_24_lastupdate.close();
		}
	} else
	{
		std::cout << "Error writing output file for _dynamic_array_synapses_24_lastupdate." << endl;
	}
	ofstream outfile__dynamic_array_synapses_24_N_incoming;
	outfile__dynamic_array_synapses_24_N_incoming.open("results\\_dynamic_array_synapses_24_N_incoming_-4514447723043174848", ios::binary | ios::out);
	if(outfile__dynamic_array_synapses_24_N_incoming.is_open())
	{
        if (! _dynamic_array_synapses_24_N_incoming.empty() )
        {
			outfile__dynamic_array_synapses_24_N_incoming.write(reinterpret_cast<char*>(&_dynamic_array_synapses_24_N_incoming[0]), _dynamic_array_synapses_24_N_incoming.size()*sizeof(_dynamic_array_synapses_24_N_incoming[0]));
		    outfile__dynamic_array_synapses_24_N_incoming.close();
		}
	} else
	{
		std::cout << "Error writing output file for _dynamic_array_synapses_24_N_incoming." << endl;
	}
	ofstream outfile__dynamic_array_synapses_24_N_outgoing;
	outfile__dynamic_array_synapses_24_N_outgoing.open("results\\_dynamic_array_synapses_24_N_outgoing_6186112606882700579", ios::binary | ios::out);
	if(outfile__dynamic_array_synapses_24_N_outgoing.is_open())
	{
        if (! _dynamic_array_synapses_24_N_outgoing.empty() )
        {
			outfile__dynamic_array_synapses_24_N_outgoing.write(reinterpret_cast<char*>(&_dynamic_array_synapses_24_N_outgoing[0]), _dynamic_array_synapses_24_N_outgoing.size()*sizeof(_dynamic_array_synapses_24_N_outgoing[0]));
		    outfile__dynamic_array_synapses_24_N_outgoing.close();
		}
	} else
	{
		std::cout << "Error writing output file for _dynamic_array_synapses_24_N_outgoing." << endl;
	}
	ofstream outfile__dynamic_array_synapses_24_R;
	outfile__dynamic_array_synapses_24_R.open("results\\_dynamic_array_synapses_24_R_-8710211140426794824", ios::binary | ios::out);
	if(outfile__dynamic_array_synapses_24_R.is_open())
	{
        if (! _dynamic_array_synapses_24_R.empty() )
        {
			outfile__dynamic_array_synapses_24_R.write(reinterpret_cast<char*>(&_dynamic_array_synapses_24_R[0]), _dynamic_array_synapses_24_R.size()*sizeof(_dynamic_array_synapses_24_R[0]));
		    outfile__dynamic_array_synapses_24_R.close();
		}
	} else
	{
		std::cout << "Error writing output file for _dynamic_array_synapses_24_R." << endl;
	}
	ofstream outfile__dynamic_array_synapses_24_wght;
	outfile__dynamic_array_synapses_24_wght.open("results\\_dynamic_array_synapses_24_wght_8717390868832532803", ios::binary | ios::out);
	if(outfile__dynamic_array_synapses_24_wght.is_open())
	{
        if (! _dynamic_array_synapses_24_wght.empty() )
        {
			outfile__dynamic_array_synapses_24_wght.write(reinterpret_cast<char*>(&_dynamic_array_synapses_24_wght[0]), _dynamic_array_synapses_24_wght.size()*sizeof(_dynamic_array_synapses_24_wght[0]));
		    outfile__dynamic_array_synapses_24_wght.close();
		}
	} else
	{
		std::cout << "Error writing output file for _dynamic_array_synapses_24_wght." << endl;
	}
	ofstream outfile__dynamic_array_synapses_25__synaptic_post;
	outfile__dynamic_array_synapses_25__synaptic_post.open("results\\_dynamic_array_synapses_25__synaptic_post_6106858358908035570", ios::binary | ios::out);
	if(outfile__dynamic_array_synapses_25__synaptic_post.is_open())
	{
        if (! _dynamic_array_synapses_25__synaptic_post.empty() )
        {
			outfile__dynamic_array_synapses_25__synaptic_post.write(reinterpret_cast<char*>(&_dynamic_array_synapses_25__synaptic_post[0]), _dynamic_array_synapses_25__synaptic_post.size()*sizeof(_dynamic_array_synapses_25__synaptic_post[0]));
		    outfile__dynamic_array_synapses_25__synaptic_post.close();
		}
	} else
	{
		std::cout << "Error writing output file for _dynamic_array_synapses_25__synaptic_post." << endl;
	}
	ofstream outfile__dynamic_array_synapses_25__synaptic_pre;
	outfile__dynamic_array_synapses_25__synaptic_pre.open("results\\_dynamic_array_synapses_25__synaptic_pre_8422361281456786321", ios::binary | ios::out);
	if(outfile__dynamic_array_synapses_25__synaptic_pre.is_open())
	{
        if (! _dynamic_array_synapses_25__synaptic_pre.empty() )
        {
			outfile__dynamic_array_synapses_25__synaptic_pre.write(reinterpret_cast<char*>(&_dynamic_array_synapses_25__synaptic_pre[0]), _dynamic_array_synapses_25__synaptic_pre.size()*sizeof(_dynamic_array_synapses_25__synaptic_pre[0]));
		    outfile__dynamic_array_synapses_25__synaptic_pre.close();
		}
	} else
	{
		std::cout << "Error writing output file for _dynamic_array_synapses_25__synaptic_pre." << endl;
	}
	ofstream outfile__dynamic_array_synapses_25_delay;
	outfile__dynamic_array_synapses_25_delay.open("results\\_dynamic_array_synapses_25_delay_6744726725256661745", ios::binary | ios::out);
	if(outfile__dynamic_array_synapses_25_delay.is_open())
	{
        if (! _dynamic_array_synapses_25_delay.empty() )
        {
			outfile__dynamic_array_synapses_25_delay.write(reinterpret_cast<char*>(&_dynamic_array_synapses_25_delay[0]), _dynamic_array_synapses_25_delay.size()*sizeof(_dynamic_array_synapses_25_delay[0]));
		    outfile__dynamic_array_synapses_25_delay.close();
		}
	} else
	{
		std::cout << "Error writing output file for _dynamic_array_synapses_25_delay." << endl;
	}
	ofstream outfile__dynamic_array_synapses_25_lastupdate;
	outfile__dynamic_array_synapses_25_lastupdate.open("results\\_dynamic_array_synapses_25_lastupdate_-2758387586833776208", ios::binary | ios::out);
	if(outfile__dynamic_array_synapses_25_lastupdate.is_open())
	{
        if (! _dynamic_array_synapses_25_lastupdate.empty() )
        {
			outfile__dynamic_array_synapses_25_lastupdate.write(reinterpret_cast<char*>(&_dynamic_array_synapses_25_lastupdate[0]), _dynamic_array_synapses_25_lastupdate.size()*sizeof(_dynamic_array_synapses_25_lastupdate[0]));
		    outfile__dynamic_array_synapses_25_lastupdate.close();
		}
	} else
	{
		std::cout << "Error writing output file for _dynamic_array_synapses_25_lastupdate." << endl;
	}
	ofstream outfile__dynamic_array_synapses_25_N_incoming;
	outfile__dynamic_array_synapses_25_N_incoming.open("results\\_dynamic_array_synapses_25_N_incoming_-6536592221831155467", ios::binary | ios::out);
	if(outfile__dynamic_array_synapses_25_N_incoming.is_open())
	{
        if (! _dynamic_array_synapses_25_N_incoming.empty() )
        {
			outfile__dynamic_array_synapses_25_N_incoming.write(reinterpret_cast<char*>(&_dynamic_array_synapses_25_N_incoming[0]), _dynamic_array_synapses_25_N_incoming.size()*sizeof(_dynamic_array_synapses_25_N_incoming[0]));
		    outfile__dynamic_array_synapses_25_N_incoming.close();
		}
	} else
	{
		std::cout << "Error writing output file for _dynamic_array_synapses_25_N_incoming." << endl;
	}
	ofstream outfile__dynamic_array_synapses_25_N_outgoing;
	outfile__dynamic_array_synapses_25_N_outgoing.open("results\\_dynamic_array_synapses_25_N_outgoing_5064937373362195040", ios::binary | ios::out);
	if(outfile__dynamic_array_synapses_25_N_outgoing.is_open())
	{
        if (! _dynamic_array_synapses_25_N_outgoing.empty() )
        {
			outfile__dynamic_array_synapses_25_N_outgoing.write(reinterpret_cast<char*>(&_dynamic_array_synapses_25_N_outgoing[0]), _dynamic_array_synapses_25_N_outgoing.size()*sizeof(_dynamic_array_synapses_25_N_outgoing[0]));
		    outfile__dynamic_array_synapses_25_N_outgoing.close();
		}
	} else
	{
		std::cout << "Error writing output file for _dynamic_array_synapses_25_N_outgoing." << endl;
	}
	ofstream outfile__dynamic_array_synapses_25_R;
	outfile__dynamic_array_synapses_25_R.open("results\\_dynamic_array_synapses_25_R_8309277875040757415", ios::binary | ios::out);
	if(outfile__dynamic_array_synapses_25_R.is_open())
	{
        if (! _dynamic_array_synapses_25_R.empty() )
        {
			outfile__dynamic_array_synapses_25_R.write(reinterpret_cast<char*>(&_dynamic_array_synapses_25_R[0]), _dynamic_array_synapses_25_R.size()*sizeof(_dynamic_array_synapses_25_R[0]));
		    outfile__dynamic_array_synapses_25_R.close();
		}
	} else
	{
		std::cout << "Error writing output file for _dynamic_array_synapses_25_R." << endl;
	}
	ofstream outfile__dynamic_array_synapses_25_wght;
	outfile__dynamic_array_synapses_25_wght.open("results\\_dynamic_array_synapses_25_wght_3239532310691569382", ios::binary | ios::out);
	if(outfile__dynamic_array_synapses_25_wght.is_open())
	{
        if (! _dynamic_array_synapses_25_wght.empty() )
        {
			outfile__dynamic_array_synapses_25_wght.write(reinterpret_cast<char*>(&_dynamic_array_synapses_25_wght[0]), _dynamic_array_synapses_25_wght.size()*sizeof(_dynamic_array_synapses_25_wght[0]));
		    outfile__dynamic_array_synapses_25_wght.close();
		}
	} else
	{
		std::cout << "Error writing output file for _dynamic_array_synapses_25_wght." << endl;
	}
	ofstream outfile__dynamic_array_synapses_26__synaptic_post;
	outfile__dynamic_array_synapses_26__synaptic_post.open("results\\_dynamic_array_synapses_26__synaptic_post_1148804894016761931", ios::binary | ios::out);
	if(outfile__dynamic_array_synapses_26__synaptic_post.is_open())
	{
        if (! _dynamic_array_synapses_26__synaptic_post.empty() )
        {
			outfile__dynamic_array_synapses_26__synaptic_post.write(reinterpret_cast<char*>(&_dynamic_array_synapses_26__synaptic_post[0]), _dynamic_array_synapses_26__synaptic_post.size()*sizeof(_dynamic_array_synapses_26__synaptic_post[0]));
		    outfile__dynamic_array_synapses_26__synaptic_post.close();
		}
	} else
	{
		std::cout << "Error writing output file for _dynamic_array_synapses_26__synaptic_post." << endl;
	}
	ofstream outfile__dynamic_array_synapses_26__synaptic_pre;
	outfile__dynamic_array_synapses_26__synaptic_pre.open("results\\_dynamic_array_synapses_26__synaptic_pre_6649370418529741425", ios::binary | ios::out);
	if(outfile__dynamic_array_synapses_26__synaptic_pre.is_open())
	{
        if (! _dynamic_array_synapses_26__synaptic_pre.empty() )
        {
			outfile__dynamic_array_synapses_26__synaptic_pre.write(reinterpret_cast<char*>(&_dynamic_array_synapses_26__synaptic_pre[0]), _dynamic_array_synapses_26__synaptic_pre.size()*sizeof(_dynamic_array_synapses_26__synaptic_pre[0]));
		    outfile__dynamic_array_synapses_26__synaptic_pre.close();
		}
	} else
	{
		std::cout << "Error writing output file for _dynamic_array_synapses_26__synaptic_pre." << endl;
	}
	ofstream outfile__dynamic_array_synapses_26_delay;
	outfile__dynamic_array_synapses_26_delay.open("results\\_dynamic_array_synapses_26_delay_7015959368872905290", ios::binary | ios::out);
	if(outfile__dynamic_array_synapses_26_delay.is_open())
	{
        if (! _dynamic_array_synapses_26_delay.empty() )
        {
			outfile__dynamic_array_synapses_26_delay.write(reinterpret_cast<char*>(&_dynamic_array_synapses_26_delay[0]), _dynamic_array_synapses_26_delay.size()*sizeof(_dynamic_array_synapses_26_delay[0]));
		    outfile__dynamic_array_synapses_26_delay.close();
		}
	} else
	{
		std::cout << "Error writing output file for _dynamic_array_synapses_26_delay." << endl;
	}
	ofstream outfile__dynamic_array_synapses_26_lastupdate;
	outfile__dynamic_array_synapses_26_lastupdate.open("results\\_dynamic_array_synapses_26_lastupdate_-8108307161361384601", ios::binary | ios::out);
	if(outfile__dynamic_array_synapses_26_lastupdate.is_open())
	{
        if (! _dynamic_array_synapses_26_lastupdate.empty() )
        {
			outfile__dynamic_array_synapses_26_lastupdate.write(reinterpret_cast<char*>(&_dynamic_array_synapses_26_lastupdate[0]), _dynamic_array_synapses_26_lastupdate.size()*sizeof(_dynamic_array_synapses_26_lastupdate[0]));
		    outfile__dynamic_array_synapses_26_lastupdate.close();
		}
	} else
	{
		std::cout << "Error writing output file for _dynamic_array_synapses_26_lastupdate." << endl;
	}
	ofstream outfile__dynamic_array_synapses_26_N_incoming;
	outfile__dynamic_array_synapses_26_N_incoming.open("results\\_dynamic_array_synapses_26_N_incoming_-8402146113435984664", ios::binary | ios::out);
	if(outfile__dynamic_array_synapses_26_N_incoming.is_open())
	{
        if (! _dynamic_array_synapses_26_N_incoming.empty() )
        {
			outfile__dynamic_array_synapses_26_N_incoming.write(reinterpret_cast<char*>(&_dynamic_array_synapses_26_N_incoming[0]), _dynamic_array_synapses_26_N_incoming.size()*sizeof(_dynamic_array_synapses_26_N_incoming[0]));
		    outfile__dynamic_array_synapses_26_N_incoming.close();
		}
	} else
	{
		std::cout << "Error writing output file for _dynamic_array_synapses_26_N_incoming." << endl;
	}
	ofstream outfile__dynamic_array_synapses_26_N_outgoing;
	outfile__dynamic_array_synapses_26_N_outgoing.open("results\\_dynamic_array_synapses_26_N_outgoing_-5229621858222547140", ios::binary | ios::out);
	if(outfile__dynamic_array_synapses_26_N_outgoing.is_open())
	{
        if (! _dynamic_array_synapses_26_N_outgoing.empty() )
        {
			outfile__dynamic_array_synapses_26_N_outgoing.write(reinterpret_cast<char*>(&_dynamic_array_synapses_26_N_outgoing[0]), _dynamic_array_synapses_26_N_outgoing.size()*sizeof(_dynamic_array_synapses_26_N_outgoing[0]));
		    outfile__dynamic_array_synapses_26_N_outgoing.close();
		}
	} else
	{
		std::cout << "Error writing output file for _dynamic_array_synapses_26_N_outgoing." << endl;
	}
	ofstream outfile__dynamic_array_synapses_26_R;
	outfile__dynamic_array_synapses_26_R.open("results\\_dynamic_array_synapses_26_R_3460322888969073257", ios::binary | ios::out);
	if(outfile__dynamic_array_synapses_26_R.is_open())
	{
        if (! _dynamic_array_synapses_26_R.empty() )
        {
			outfile__dynamic_array_synapses_26_R.write(reinterpret_cast<char*>(&_dynamic_array_synapses_26_R[0]), _dynamic_array_synapses_26_R.size()*sizeof(_dynamic_array_synapses_26_R[0]));
		    outfile__dynamic_array_synapses_26_R.close();
		}
	} else
	{
		std::cout << "Error writing output file for _dynamic_array_synapses_26_R." << endl;
	}
	ofstream outfile__dynamic_array_synapses_26_wght;
	outfile__dynamic_array_synapses_26_wght.open("results\\_dynamic_array_synapses_26_wght_631576469138646832", ios::binary | ios::out);
	if(outfile__dynamic_array_synapses_26_wght.is_open())
	{
        if (! _dynamic_array_synapses_26_wght.empty() )
        {
			outfile__dynamic_array_synapses_26_wght.write(reinterpret_cast<char*>(&_dynamic_array_synapses_26_wght[0]), _dynamic_array_synapses_26_wght.size()*sizeof(_dynamic_array_synapses_26_wght[0]));
		    outfile__dynamic_array_synapses_26_wght.close();
		}
	} else
	{
		std::cout << "Error writing output file for _dynamic_array_synapses_26_wght." << endl;
	}
	ofstream outfile__dynamic_array_synapses_27__synaptic_post;
	outfile__dynamic_array_synapses_27__synaptic_post.open("results\\_dynamic_array_synapses_27__synaptic_post_-3643556230237043232", ios::binary | ios::out);
	if(outfile__dynamic_array_synapses_27__synaptic_post.is_open())
	{
        if (! _dynamic_array_synapses_27__synaptic_post.empty() )
        {
			outfile__dynamic_array_synapses_27__synaptic_post.write(reinterpret_cast<char*>(&_dynamic_array_synapses_27__synaptic_post[0]), _dynamic_array_synapses_27__synaptic_post.size()*sizeof(_dynamic_array_synapses_27__synaptic_post[0]));
		    outfile__dynamic_array_synapses_27__synaptic_post.close();
		}
	} else
	{
		std::cout << "Error writing output file for _dynamic_array_synapses_27__synaptic_post." << endl;
	}
	ofstream outfile__dynamic_array_synapses_27__synaptic_pre;
	outfile__dynamic_array_synapses_27__synaptic_pre.open("results\\_dynamic_array_synapses_27__synaptic_pre_-3503263024111511101", ios::binary | ios::out);
	if(outfile__dynamic_array_synapses_27__synaptic_pre.is_open())
	{
        if (! _dynamic_array_synapses_27__synaptic_pre.empty() )
        {
			outfile__dynamic_array_synapses_27__synaptic_pre.write(reinterpret_cast<char*>(&_dynamic_array_synapses_27__synaptic_pre[0]), _dynamic_array_synapses_27__synaptic_pre.size()*sizeof(_dynamic_array_synapses_27__synaptic_pre[0]));
		    outfile__dynamic_array_synapses_27__synaptic_pre.close();
		}
	} else
	{
		std::cout << "Error writing output file for _dynamic_array_synapses_27__synaptic_pre." << endl;
	}
	ofstream outfile__dynamic_array_synapses_27_delay;
	outfile__dynamic_array_synapses_27_delay.open("results\\_dynamic_array_synapses_27_delay_-9135496093610057834", ios::binary | ios::out);
	if(outfile__dynamic_array_synapses_27_delay.is_open())
	{
        if (! _dynamic_array_synapses_27_delay.empty() )
        {
			outfile__dynamic_array_synapses_27_delay.write(reinterpret_cast<char*>(&_dynamic_array_synapses_27_delay[0]), _dynamic_array_synapses_27_delay.size()*sizeof(_dynamic_array_synapses_27_delay[0]));
		    outfile__dynamic_array_synapses_27_delay.close();
		}
	} else
	{
		std::cout << "Error writing output file for _dynamic_array_synapses_27_delay." << endl;
	}
	ofstream outfile__dynamic_array_synapses_27_lastupdate;
	outfile__dynamic_array_synapses_27_lastupdate.open("results\\_dynamic_array_synapses_27_lastupdate_5309177777017141110", ios::binary | ios::out);
	if(outfile__dynamic_array_synapses_27_lastupdate.is_open())
	{
        if (! _dynamic_array_synapses_27_lastupdate.empty() )
        {
			outfile__dynamic_array_synapses_27_lastupdate.write(reinterpret_cast<char*>(&_dynamic_array_synapses_27_lastupdate[0]), _dynamic_array_synapses_27_lastupdate.size()*sizeof(_dynamic_array_synapses_27_lastupdate[0]));
		    outfile__dynamic_array_synapses_27_lastupdate.close();
		}
	} else
	{
		std::cout << "Error writing output file for _dynamic_array_synapses_27_lastupdate." << endl;
	}
	ofstream outfile__dynamic_array_synapses_27_N_incoming;
	outfile__dynamic_array_synapses_27_N_incoming.open("results\\_dynamic_array_synapses_27_N_incoming_-9177640147098054136", ios::binary | ios::out);
	if(outfile__dynamic_array_synapses_27_N_incoming.is_open())
	{
        if (! _dynamic_array_synapses_27_N_incoming.empty() )
        {
			outfile__dynamic_array_synapses_27_N_incoming.write(reinterpret_cast<char*>(&_dynamic_array_synapses_27_N_incoming[0]), _dynamic_array_synapses_27_N_incoming.size()*sizeof(_dynamic_array_synapses_27_N_incoming[0]));
		    outfile__dynamic_array_synapses_27_N_incoming.close();
		}
	} else
	{
		std::cout << "Error writing output file for _dynamic_array_synapses_27_N_incoming." << endl;
	}
	ofstream outfile__dynamic_array_synapses_27_N_outgoing;
	outfile__dynamic_array_synapses_27_N_outgoing.open("results\\_dynamic_array_synapses_27_N_outgoing_3479806102570573080", ios::binary | ios::out);
	if(outfile__dynamic_array_synapses_27_N_outgoing.is_open())
	{
        if (! _dynamic_array_synapses_27_N_outgoing.empty() )
        {
			outfile__dynamic_array_synapses_27_N_outgoing.write(reinterpret_cast<char*>(&_dynamic_array_synapses_27_N_outgoing[0]), _dynamic_array_synapses_27_N_outgoing.size()*sizeof(_dynamic_array_synapses_27_N_outgoing[0]));
		    outfile__dynamic_array_synapses_27_N_outgoing.close();
		}
	} else
	{
		std::cout << "Error writing output file for _dynamic_array_synapses_27_N_outgoing." << endl;
	}
	ofstream outfile__dynamic_array_synapses_27_R;
	outfile__dynamic_array_synapses_27_R.open("results\\_dynamic_array_synapses_27_R_-7645253012749115094", ios::binary | ios::out);
	if(outfile__dynamic_array_synapses_27_R.is_open())
	{
        if (! _dynamic_array_synapses_27_R.empty() )
        {
			outfile__dynamic_array_synapses_27_R.write(reinterpret_cast<char*>(&_dynamic_array_synapses_27_R[0]), _dynamic_array_synapses_27_R.size()*sizeof(_dynamic_array_synapses_27_R[0]));
		    outfile__dynamic_array_synapses_27_R.close();
		}
	} else
	{
		std::cout << "Error writing output file for _dynamic_array_synapses_27_R." << endl;
	}
	ofstream outfile__dynamic_array_synapses_27_wght;
	outfile__dynamic_array_synapses_27_wght.open("results\\_dynamic_array_synapses_27_wght_8419737671954825740", ios::binary | ios::out);
	if(outfile__dynamic_array_synapses_27_wght.is_open())
	{
        if (! _dynamic_array_synapses_27_wght.empty() )
        {
			outfile__dynamic_array_synapses_27_wght.write(reinterpret_cast<char*>(&_dynamic_array_synapses_27_wght[0]), _dynamic_array_synapses_27_wght.size()*sizeof(_dynamic_array_synapses_27_wght[0]));
		    outfile__dynamic_array_synapses_27_wght.close();
		}
	} else
	{
		std::cout << "Error writing output file for _dynamic_array_synapses_27_wght." << endl;
	}
	ofstream outfile__dynamic_array_synapses_28__synaptic_post;
	outfile__dynamic_array_synapses_28__synaptic_post.open("results\\_dynamic_array_synapses_28__synaptic_post_8372989375229962273", ios::binary | ios::out);
	if(outfile__dynamic_array_synapses_28__synaptic_post.is_open())
	{
        if (! _dynamic_array_synapses_28__synaptic_post.empty() )
        {
			outfile__dynamic_array_synapses_28__synaptic_post.write(reinterpret_cast<char*>(&_dynamic_array_synapses_28__synaptic_post[0]), _dynamic_array_synapses_28__synaptic_post.size()*sizeof(_dynamic_array_synapses_28__synaptic_post[0]));
		    outfile__dynamic_array_synapses_28__synaptic_post.close();
		}
	} else
	{
		std::cout << "Error writing output file for _dynamic_array_synapses_28__synaptic_post." << endl;
	}
	ofstream outfile__dynamic_array_synapses_28__synaptic_pre;
	outfile__dynamic_array_synapses_28__synaptic_pre.open("results\\_dynamic_array_synapses_28__synaptic_pre_-5955506215811082131", ios::binary | ios::out);
	if(outfile__dynamic_array_synapses_28__synaptic_pre.is_open())
	{
        if (! _dynamic_array_synapses_28__synaptic_pre.empty() )
        {
			outfile__dynamic_array_synapses_28__synaptic_pre.write(reinterpret_cast<char*>(&_dynamic_array_synapses_28__synaptic_pre[0]), _dynamic_array_synapses_28__synaptic_pre.size()*sizeof(_dynamic_array_synapses_28__synaptic_pre[0]));
		    outfile__dynamic_array_synapses_28__synaptic_pre.close();
		}
	} else
	{
		std::cout << "Error writing output file for _dynamic_array_synapses_28__synaptic_pre." << endl;
	}
	ofstream outfile__dynamic_array_synapses_28_delay;
	outfile__dynamic_array_synapses_28_delay.open("results\\_dynamic_array_synapses_28_delay_3417426809925371656", ios::binary | ios::out);
	if(outfile__dynamic_array_synapses_28_delay.is_open())
	{
        if (! _dynamic_array_synapses_28_delay.empty() )
        {
			outfile__dynamic_array_synapses_28_delay.write(reinterpret_cast<char*>(&_dynamic_array_synapses_28_delay[0]), _dynamic_array_synapses_28_delay.size()*sizeof(_dynamic_array_synapses_28_delay[0]));
		    outfile__dynamic_array_synapses_28_delay.close();
		}
	} else
	{
		std::cout << "Error writing output file for _dynamic_array_synapses_28_delay." << endl;
	}
	ofstream outfile__dynamic_array_synapses_28_lastupdate;
	outfile__dynamic_array_synapses_28_lastupdate.open("results\\_dynamic_array_synapses_28_lastupdate_5988074395273161473", ios::binary | ios::out);
	if(outfile__dynamic_array_synapses_28_lastupdate.is_open())
	{
        if (! _dynamic_array_synapses_28_lastupdate.empty() )
        {
			outfile__dynamic_array_synapses_28_lastupdate.write(reinterpret_cast<char*>(&_dynamic_array_synapses_28_lastupdate[0]), _dynamic_array_synapses_28_lastupdate.size()*sizeof(_dynamic_array_synapses_28_lastupdate[0]));
		    outfile__dynamic_array_synapses_28_lastupdate.close();
		}
	} else
	{
		std::cout << "Error writing output file for _dynamic_array_synapses_28_lastupdate." << endl;
	}
	ofstream outfile__dynamic_array_synapses_28_N_incoming;
	outfile__dynamic_array_synapses_28_N_incoming.open("results\\_dynamic_array_synapses_28_N_incoming_-77115600220532685", ios::binary | ios::out);
	if(outfile__dynamic_array_synapses_28_N_incoming.is_open())
	{
        if (! _dynamic_array_synapses_28_N_incoming.empty() )
        {
			outfile__dynamic_array_synapses_28_N_incoming.write(reinterpret_cast<char*>(&_dynamic_array_synapses_28_N_incoming[0]), _dynamic_array_synapses_28_N_incoming.size()*sizeof(_dynamic_array_synapses_28_N_incoming[0]));
		    outfile__dynamic_array_synapses_28_N_incoming.close();
		}
	} else
	{
		std::cout << "Error writing output file for _dynamic_array_synapses_28_N_incoming." << endl;
	}
	ofstream outfile__dynamic_array_synapses_28_N_outgoing;
	outfile__dynamic_array_synapses_28_N_outgoing.open("results\\_dynamic_array_synapses_28_N_outgoing_-1922154029447679168", ios::binary | ios::out);
	if(outfile__dynamic_array_synapses_28_N_outgoing.is_open())
	{
        if (! _dynamic_array_synapses_28_N_outgoing.empty() )
        {
			outfile__dynamic_array_synapses_28_N_outgoing.write(reinterpret_cast<char*>(&_dynamic_array_synapses_28_N_outgoing[0]), _dynamic_array_synapses_28_N_outgoing.size()*sizeof(_dynamic_array_synapses_28_N_outgoing[0]));
		    outfile__dynamic_array_synapses_28_N_outgoing.close();
		}
	} else
	{
		std::cout << "Error writing output file for _dynamic_array_synapses_28_N_outgoing." << endl;
	}
	ofstream outfile__dynamic_array_synapses_28_R;
	outfile__dynamic_array_synapses_28_R.open("results\\_dynamic_array_synapses_28_R_-7900604301832094587", ios::binary | ios::out);
	if(outfile__dynamic_array_synapses_28_R.is_open())
	{
        if (! _dynamic_array_synapses_28_R.empty() )
        {
			outfile__dynamic_array_synapses_28_R.write(reinterpret_cast<char*>(&_dynamic_array_synapses_28_R[0]), _dynamic_array_synapses_28_R.size()*sizeof(_dynamic_array_synapses_28_R[0]));
		    outfile__dynamic_array_synapses_28_R.close();
		}
	} else
	{
		std::cout << "Error writing output file for _dynamic_array_synapses_28_R." << endl;
	}
	ofstream outfile__dynamic_array_synapses_28_wght;
	outfile__dynamic_array_synapses_28_wght.open("results\\_dynamic_array_synapses_28_wght_3954280364819115100", ios::binary | ios::out);
	if(outfile__dynamic_array_synapses_28_wght.is_open())
	{
        if (! _dynamic_array_synapses_28_wght.empty() )
        {
			outfile__dynamic_array_synapses_28_wght.write(reinterpret_cast<char*>(&_dynamic_array_synapses_28_wght[0]), _dynamic_array_synapses_28_wght.size()*sizeof(_dynamic_array_synapses_28_wght[0]));
		    outfile__dynamic_array_synapses_28_wght.close();
		}
	} else
	{
		std::cout << "Error writing output file for _dynamic_array_synapses_28_wght." << endl;
	}
	ofstream outfile__dynamic_array_synapses_29__synaptic_post;
	outfile__dynamic_array_synapses_29__synaptic_post.open("results\\_dynamic_array_synapses_29__synaptic_post_3990589093100808273", ios::binary | ios::out);
	if(outfile__dynamic_array_synapses_29__synaptic_post.is_open())
	{
        if (! _dynamic_array_synapses_29__synaptic_post.empty() )
        {
			outfile__dynamic_array_synapses_29__synaptic_post.write(reinterpret_cast<char*>(&_dynamic_array_synapses_29__synaptic_post[0]), _dynamic_array_synapses_29__synaptic_post.size()*sizeof(_dynamic_array_synapses_29__synaptic_post[0]));
		    outfile__dynamic_array_synapses_29__synaptic_post.close();
		}
	} else
	{
		std::cout << "Error writing output file for _dynamic_array_synapses_29__synaptic_post." << endl;
	}
	ofstream outfile__dynamic_array_synapses_29__synaptic_pre;
	outfile__dynamic_array_synapses_29__synaptic_pre.open("results\\_dynamic_array_synapses_29__synaptic_pre_6939237623063264327", ios::binary | ios::out);
	if(outfile__dynamic_array_synapses_29__synaptic_pre.is_open())
	{
        if (! _dynamic_array_synapses_29__synaptic_pre.empty() )
        {
			outfile__dynamic_array_synapses_29__synaptic_pre.write(reinterpret_cast<char*>(&_dynamic_array_synapses_29__synaptic_pre[0]), _dynamic_array_synapses_29__synaptic_pre.size()*sizeof(_dynamic_array_synapses_29__synaptic_pre[0]));
		    outfile__dynamic_array_synapses_29__synaptic_pre.close();
		}
	} else
	{
		std::cout << "Error writing output file for _dynamic_array_synapses_29__synaptic_pre." << endl;
	}
	ofstream outfile__dynamic_array_synapses_29_delay;
	outfile__dynamic_array_synapses_29_delay.open("results\\_dynamic_array_synapses_29_delay_-2672034248518216491", ios::binary | ios::out);
	if(outfile__dynamic_array_synapses_29_delay.is_open())
	{
        if (! _dynamic_array_synapses_29_delay.empty() )
        {
			outfile__dynamic_array_synapses_29_delay.write(reinterpret_cast<char*>(&_dynamic_array_synapses_29_delay[0]), _dynamic_array_synapses_29_delay.size()*sizeof(_dynamic_array_synapses_29_delay[0]));
		    outfile__dynamic_array_synapses_29_delay.close();
		}
	} else
	{
		std::cout << "Error writing output file for _dynamic_array_synapses_29_delay." << endl;
	}
	ofstream outfile__dynamic_array_synapses_29_lastupdate;
	outfile__dynamic_array_synapses_29_lastupdate.open("results\\_dynamic_array_synapses_29_lastupdate_1462824086278830039", ios::binary | ios::out);
	if(outfile__dynamic_array_synapses_29_lastupdate.is_open())
	{
        if (! _dynamic_array_synapses_29_lastupdate.empty() )
        {
			outfile__dynamic_array_synapses_29_lastupdate.write(reinterpret_cast<char*>(&_dynamic_array_synapses_29_lastupdate[0]), _dynamic_array_synapses_29_lastupdate.size()*sizeof(_dynamic_array_synapses_29_lastupdate[0]));
		    outfile__dynamic_array_synapses_29_lastupdate.close();
		}
	} else
	{
		std::cout << "Error writing output file for _dynamic_array_synapses_29_lastupdate." << endl;
	}
	ofstream outfile__dynamic_array_synapses_29_N_incoming;
	outfile__dynamic_array_synapses_29_N_incoming.open("results\\_dynamic_array_synapses_29_N_incoming_-1699437575967843489", ios::binary | ios::out);
	if(outfile__dynamic_array_synapses_29_N_incoming.is_open())
	{
        if (! _dynamic_array_synapses_29_N_incoming.empty() )
        {
			outfile__dynamic_array_synapses_29_N_incoming.write(reinterpret_cast<char*>(&_dynamic_array_synapses_29_N_incoming[0]), _dynamic_array_synapses_29_N_incoming.size()*sizeof(_dynamic_array_synapses_29_N_incoming[0]));
		    outfile__dynamic_array_synapses_29_N_incoming.close();
		}
	} else
	{
		std::cout << "Error writing output file for _dynamic_array_synapses_29_N_incoming." << endl;
	}
	ofstream outfile__dynamic_array_synapses_29_N_outgoing;
	outfile__dynamic_array_synapses_29_N_outgoing.open("results\\_dynamic_array_synapses_29_N_outgoing_7840822620991395216", ios::binary | ios::out);
	if(outfile__dynamic_array_synapses_29_N_outgoing.is_open())
	{
        if (! _dynamic_array_synapses_29_N_outgoing.empty() )
        {
			outfile__dynamic_array_synapses_29_N_outgoing.write(reinterpret_cast<char*>(&_dynamic_array_synapses_29_N_outgoing[0]), _dynamic_array_synapses_29_N_outgoing.size()*sizeof(_dynamic_array_synapses_29_N_outgoing[0]));
		    outfile__dynamic_array_synapses_29_N_outgoing.close();
		}
	} else
	{
		std::cout << "Error writing output file for _dynamic_array_synapses_29_N_outgoing." << endl;
	}
	ofstream outfile__dynamic_array_synapses_29_R;
	outfile__dynamic_array_synapses_29_R.open("results\\_dynamic_array_synapses_29_R_8989893923711158542", ios::binary | ios::out);
	if(outfile__dynamic_array_synapses_29_R.is_open())
	{
        if (! _dynamic_array_synapses_29_R.empty() )
        {
			outfile__dynamic_array_synapses_29_R.write(reinterpret_cast<char*>(&_dynamic_array_synapses_29_R[0]), _dynamic_array_synapses_29_R.size()*sizeof(_dynamic_array_synapses_29_R[0]));
		    outfile__dynamic_array_synapses_29_R.close();
		}
	} else
	{
		std::cout << "Error writing output file for _dynamic_array_synapses_29_R." << endl;
	}
	ofstream outfile__dynamic_array_synapses_29_wght;
	outfile__dynamic_array_synapses_29_wght.open("results\\_dynamic_array_synapses_29_wght_375032910109263046", ios::binary | ios::out);
	if(outfile__dynamic_array_synapses_29_wght.is_open())
	{
        if (! _dynamic_array_synapses_29_wght.empty() )
        {
			outfile__dynamic_array_synapses_29_wght.write(reinterpret_cast<char*>(&_dynamic_array_synapses_29_wght[0]), _dynamic_array_synapses_29_wght.size()*sizeof(_dynamic_array_synapses_29_wght[0]));
		    outfile__dynamic_array_synapses_29_wght.close();
		}
	} else
	{
		std::cout << "Error writing output file for _dynamic_array_synapses_29_wght." << endl;
	}
	ofstream outfile__dynamic_array_synapses_2__synaptic_post;
	outfile__dynamic_array_synapses_2__synaptic_post.open("results\\_dynamic_array_synapses_2__synaptic_post_-3396510052947751748", ios::binary | ios::out);
	if(outfile__dynamic_array_synapses_2__synaptic_post.is_open())
	{
        if (! _dynamic_array_synapses_2__synaptic_post.empty() )
        {
			outfile__dynamic_array_synapses_2__synaptic_post.write(reinterpret_cast<char*>(&_dynamic_array_synapses_2__synaptic_post[0]), _dynamic_array_synapses_2__synaptic_post.size()*sizeof(_dynamic_array_synapses_2__synaptic_post[0]));
		    outfile__dynamic_array_synapses_2__synaptic_post.close();
		}
	} else
	{
		std::cout << "Error writing output file for _dynamic_array_synapses_2__synaptic_post." << endl;
	}
	ofstream outfile__dynamic_array_synapses_2__synaptic_pre;
	outfile__dynamic_array_synapses_2__synaptic_pre.open("results\\_dynamic_array_synapses_2__synaptic_pre_8812155270186647118", ios::binary | ios::out);
	if(outfile__dynamic_array_synapses_2__synaptic_pre.is_open())
	{
        if (! _dynamic_array_synapses_2__synaptic_pre.empty() )
        {
			outfile__dynamic_array_synapses_2__synaptic_pre.write(reinterpret_cast<char*>(&_dynamic_array_synapses_2__synaptic_pre[0]), _dynamic_array_synapses_2__synaptic_pre.size()*sizeof(_dynamic_array_synapses_2__synaptic_pre[0]));
		    outfile__dynamic_array_synapses_2__synaptic_pre.close();
		}
	} else
	{
		std::cout << "Error writing output file for _dynamic_array_synapses_2__synaptic_pre." << endl;
	}
	ofstream outfile__dynamic_array_synapses_2_delay;
	outfile__dynamic_array_synapses_2_delay.open("results\\_dynamic_array_synapses_2_delay_-1180979534500669471", ios::binary | ios::out);
	if(outfile__dynamic_array_synapses_2_delay.is_open())
	{
        if (! _dynamic_array_synapses_2_delay.empty() )
        {
			outfile__dynamic_array_synapses_2_delay.write(reinterpret_cast<char*>(&_dynamic_array_synapses_2_delay[0]), _dynamic_array_synapses_2_delay.size()*sizeof(_dynamic_array_synapses_2_delay[0]));
		    outfile__dynamic_array_synapses_2_delay.close();
		}
	} else
	{
		std::cout << "Error writing output file for _dynamic_array_synapses_2_delay." << endl;
	}
	ofstream outfile__dynamic_array_synapses_2_lastupdate;
	outfile__dynamic_array_synapses_2_lastupdate.open("results\\_dynamic_array_synapses_2_lastupdate_5620170231718027756", ios::binary | ios::out);
	if(outfile__dynamic_array_synapses_2_lastupdate.is_open())
	{
        if (! _dynamic_array_synapses_2_lastupdate.empty() )
        {
			outfile__dynamic_array_synapses_2_lastupdate.write(reinterpret_cast<char*>(&_dynamic_array_synapses_2_lastupdate[0]), _dynamic_array_synapses_2_lastupdate.size()*sizeof(_dynamic_array_synapses_2_lastupdate[0]));
		    outfile__dynamic_array_synapses_2_lastupdate.close();
		}
	} else
	{
		std::cout << "Error writing output file for _dynamic_array_synapses_2_lastupdate." << endl;
	}
	ofstream outfile__dynamic_array_synapses_2_N_incoming;
	outfile__dynamic_array_synapses_2_N_incoming.open("results\\_dynamic_array_synapses_2_N_incoming_-5362191990781075919", ios::binary | ios::out);
	if(outfile__dynamic_array_synapses_2_N_incoming.is_open())
	{
        if (! _dynamic_array_synapses_2_N_incoming.empty() )
        {
			outfile__dynamic_array_synapses_2_N_incoming.write(reinterpret_cast<char*>(&_dynamic_array_synapses_2_N_incoming[0]), _dynamic_array_synapses_2_N_incoming.size()*sizeof(_dynamic_array_synapses_2_N_incoming[0]));
		    outfile__dynamic_array_synapses_2_N_incoming.close();
		}
	} else
	{
		std::cout << "Error writing output file for _dynamic_array_synapses_2_N_incoming." << endl;
	}
	ofstream outfile__dynamic_array_synapses_2_N_outgoing;
	outfile__dynamic_array_synapses_2_N_outgoing.open("results\\_dynamic_array_synapses_2_N_outgoing_-5354855443801619000", ios::binary | ios::out);
	if(outfile__dynamic_array_synapses_2_N_outgoing.is_open())
	{
        if (! _dynamic_array_synapses_2_N_outgoing.empty() )
        {
			outfile__dynamic_array_synapses_2_N_outgoing.write(reinterpret_cast<char*>(&_dynamic_array_synapses_2_N_outgoing[0]), _dynamic_array_synapses_2_N_outgoing.size()*sizeof(_dynamic_array_synapses_2_N_outgoing[0]));
		    outfile__dynamic_array_synapses_2_N_outgoing.close();
		}
	} else
	{
		std::cout << "Error writing output file for _dynamic_array_synapses_2_N_outgoing." << endl;
	}
	ofstream outfile__dynamic_array_synapses_2_R;
	outfile__dynamic_array_synapses_2_R.open("results\\_dynamic_array_synapses_2_R_1417469693573880838", ios::binary | ios::out);
	if(outfile__dynamic_array_synapses_2_R.is_open())
	{
        if (! _dynamic_array_synapses_2_R.empty() )
        {
			outfile__dynamic_array_synapses_2_R.write(reinterpret_cast<char*>(&_dynamic_array_synapses_2_R[0]), _dynamic_array_synapses_2_R.size()*sizeof(_dynamic_array_synapses_2_R[0]));
		    outfile__dynamic_array_synapses_2_R.close();
		}
	} else
	{
		std::cout << "Error writing output file for _dynamic_array_synapses_2_R." << endl;
	}
	ofstream outfile__dynamic_array_synapses_2_wght;
	outfile__dynamic_array_synapses_2_wght.open("results\\_dynamic_array_synapses_2_wght_257591862585291696", ios::binary | ios::out);
	if(outfile__dynamic_array_synapses_2_wght.is_open())
	{
        if (! _dynamic_array_synapses_2_wght.empty() )
        {
			outfile__dynamic_array_synapses_2_wght.write(reinterpret_cast<char*>(&_dynamic_array_synapses_2_wght[0]), _dynamic_array_synapses_2_wght.size()*sizeof(_dynamic_array_synapses_2_wght[0]));
		    outfile__dynamic_array_synapses_2_wght.close();
		}
	} else
	{
		std::cout << "Error writing output file for _dynamic_array_synapses_2_wght." << endl;
	}
	ofstream outfile__dynamic_array_synapses_30__synaptic_post;
	outfile__dynamic_array_synapses_30__synaptic_post.open("results\\_dynamic_array_synapses_30__synaptic_post_-487596586497936924", ios::binary | ios::out);
	if(outfile__dynamic_array_synapses_30__synaptic_post.is_open())
	{
        if (! _dynamic_array_synapses_30__synaptic_post.empty() )
        {
			outfile__dynamic_array_synapses_30__synaptic_post.write(reinterpret_cast<char*>(&_dynamic_array_synapses_30__synaptic_post[0]), _dynamic_array_synapses_30__synaptic_post.size()*sizeof(_dynamic_array_synapses_30__synaptic_post[0]));
		    outfile__dynamic_array_synapses_30__synaptic_post.close();
		}
	} else
	{
		std::cout << "Error writing output file for _dynamic_array_synapses_30__synaptic_post." << endl;
	}
	ofstream outfile__dynamic_array_synapses_30__synaptic_pre;
	outfile__dynamic_array_synapses_30__synaptic_pre.open("results\\_dynamic_array_synapses_30__synaptic_pre_-2021967835028906436", ios::binary | ios::out);
	if(outfile__dynamic_array_synapses_30__synaptic_pre.is_open())
	{
        if (! _dynamic_array_synapses_30__synaptic_pre.empty() )
        {
			outfile__dynamic_array_synapses_30__synaptic_pre.write(reinterpret_cast<char*>(&_dynamic_array_synapses_30__synaptic_pre[0]), _dynamic_array_synapses_30__synaptic_pre.size()*sizeof(_dynamic_array_synapses_30__synaptic_pre[0]));
		    outfile__dynamic_array_synapses_30__synaptic_pre.close();
		}
	} else
	{
		std::cout << "Error writing output file for _dynamic_array_synapses_30__synaptic_pre." << endl;
	}
	ofstream outfile__dynamic_array_synapses_30_delay;
	outfile__dynamic_array_synapses_30_delay.open("results\\_dynamic_array_synapses_30_delay_5521487716644573723", ios::binary | ios::out);
	if(outfile__dynamic_array_synapses_30_delay.is_open())
	{
        if (! _dynamic_array_synapses_30_delay.empty() )
        {
			outfile__dynamic_array_synapses_30_delay.write(reinterpret_cast<char*>(&_dynamic_array_synapses_30_delay[0]), _dynamic_array_synapses_30_delay.size()*sizeof(_dynamic_array_synapses_30_delay[0]));
		    outfile__dynamic_array_synapses_30_delay.close();
		}
	} else
	{
		std::cout << "Error writing output file for _dynamic_array_synapses_30_delay." << endl;
	}
	ofstream outfile__dynamic_array_synapses_30_lastupdate;
	outfile__dynamic_array_synapses_30_lastupdate.open("results\\_dynamic_array_synapses_30_lastupdate_7049961195669389337", ios::binary | ios::out);
	if(outfile__dynamic_array_synapses_30_lastupdate.is_open())
	{
        if (! _dynamic_array_synapses_30_lastupdate.empty() )
        {
			outfile__dynamic_array_synapses_30_lastupdate.write(reinterpret_cast<char*>(&_dynamic_array_synapses_30_lastupdate[0]), _dynamic_array_synapses_30_lastupdate.size()*sizeof(_dynamic_array_synapses_30_lastupdate[0]));
		    outfile__dynamic_array_synapses_30_lastupdate.close();
		}
	} else
	{
		std::cout << "Error writing output file for _dynamic_array_synapses_30_lastupdate." << endl;
	}
	ofstream outfile__dynamic_array_synapses_30_N_incoming;
	outfile__dynamic_array_synapses_30_N_incoming.open("results\\_dynamic_array_synapses_30_N_incoming_4897687899581130173", ios::binary | ios::out);
	if(outfile__dynamic_array_synapses_30_N_incoming.is_open())
	{
        if (! _dynamic_array_synapses_30_N_incoming.empty() )
        {
			outfile__dynamic_array_synapses_30_N_incoming.write(reinterpret_cast<char*>(&_dynamic_array_synapses_30_N_incoming[0]), _dynamic_array_synapses_30_N_incoming.size()*sizeof(_dynamic_array_synapses_30_N_incoming[0]));
		    outfile__dynamic_array_synapses_30_N_incoming.close();
		}
	} else
	{
		std::cout << "Error writing output file for _dynamic_array_synapses_30_N_incoming." << endl;
	}
	ofstream outfile__dynamic_array_synapses_30_N_outgoing;
	outfile__dynamic_array_synapses_30_N_outgoing.open("results\\_dynamic_array_synapses_30_N_outgoing_-7307190200689920559", ios::binary | ios::out);
	if(outfile__dynamic_array_synapses_30_N_outgoing.is_open())
	{
        if (! _dynamic_array_synapses_30_N_outgoing.empty() )
        {
			outfile__dynamic_array_synapses_30_N_outgoing.write(reinterpret_cast<char*>(&_dynamic_array_synapses_30_N_outgoing[0]), _dynamic_array_synapses_30_N_outgoing.size()*sizeof(_dynamic_array_synapses_30_N_outgoing[0]));
		    outfile__dynamic_array_synapses_30_N_outgoing.close();
		}
	} else
	{
		std::cout << "Error writing output file for _dynamic_array_synapses_30_N_outgoing." << endl;
	}
	ofstream outfile__dynamic_array_synapses_30_R;
	outfile__dynamic_array_synapses_30_R.open("results\\_dynamic_array_synapses_30_R_-4147472290540009019", ios::binary | ios::out);
	if(outfile__dynamic_array_synapses_30_R.is_open())
	{
        if (! _dynamic_array_synapses_30_R.empty() )
        {
			outfile__dynamic_array_synapses_30_R.write(reinterpret_cast<char*>(&_dynamic_array_synapses_30_R[0]), _dynamic_array_synapses_30_R.size()*sizeof(_dynamic_array_synapses_30_R[0]));
		    outfile__dynamic_array_synapses_30_R.close();
		}
	} else
	{
		std::cout << "Error writing output file for _dynamic_array_synapses_30_R." << endl;
	}
	ofstream outfile__dynamic_array_synapses_30_wght;
	outfile__dynamic_array_synapses_30_wght.open("results\\_dynamic_array_synapses_30_wght_-8119810068090359121", ios::binary | ios::out);
	if(outfile__dynamic_array_synapses_30_wght.is_open())
	{
        if (! _dynamic_array_synapses_30_wght.empty() )
        {
			outfile__dynamic_array_synapses_30_wght.write(reinterpret_cast<char*>(&_dynamic_array_synapses_30_wght[0]), _dynamic_array_synapses_30_wght.size()*sizeof(_dynamic_array_synapses_30_wght[0]));
		    outfile__dynamic_array_synapses_30_wght.close();
		}
	} else
	{
		std::cout << "Error writing output file for _dynamic_array_synapses_30_wght." << endl;
	}
	ofstream outfile__dynamic_array_synapses_31__synaptic_post;
	outfile__dynamic_array_synapses_31__synaptic_post.open("results\\_dynamic_array_synapses_31__synaptic_post_-9110398429546928584", ios::binary | ios::out);
	if(outfile__dynamic_array_synapses_31__synaptic_post.is_open())
	{
        if (! _dynamic_array_synapses_31__synaptic_post.empty() )
        {
			outfile__dynamic_array_synapses_31__synaptic_post.write(reinterpret_cast<char*>(&_dynamic_array_synapses_31__synaptic_post[0]), _dynamic_array_synapses_31__synaptic_post.size()*sizeof(_dynamic_array_synapses_31__synaptic_post[0]));
		    outfile__dynamic_array_synapses_31__synaptic_post.close();
		}
	} else
	{
		std::cout << "Error writing output file for _dynamic_array_synapses_31__synaptic_post." << endl;
	}
	ofstream outfile__dynamic_array_synapses_31__synaptic_pre;
	outfile__dynamic_array_synapses_31__synaptic_pre.open("results\\_dynamic_array_synapses_31__synaptic_pre_4939526405510142241", ios::binary | ios::out);
	if(outfile__dynamic_array_synapses_31__synaptic_pre.is_open())
	{
        if (! _dynamic_array_synapses_31__synaptic_pre.empty() )
        {
			outfile__dynamic_array_synapses_31__synaptic_pre.write(reinterpret_cast<char*>(&_dynamic_array_synapses_31__synaptic_pre[0]), _dynamic_array_synapses_31__synaptic_pre.size()*sizeof(_dynamic_array_synapses_31__synaptic_pre[0]));
		    outfile__dynamic_array_synapses_31__synaptic_pre.close();
		}
	} else
	{
		std::cout << "Error writing output file for _dynamic_array_synapses_31__synaptic_pre." << endl;
	}
	ofstream outfile__dynamic_array_synapses_31_delay;
	outfile__dynamic_array_synapses_31_delay.open("results\\_dynamic_array_synapses_31_delay_-6920540618878851367", ios::binary | ios::out);
	if(outfile__dynamic_array_synapses_31_delay.is_open())
	{
        if (! _dynamic_array_synapses_31_delay.empty() )
        {
			outfile__dynamic_array_synapses_31_delay.write(reinterpret_cast<char*>(&_dynamic_array_synapses_31_delay[0]), _dynamic_array_synapses_31_delay.size()*sizeof(_dynamic_array_synapses_31_delay[0]));
		    outfile__dynamic_array_synapses_31_delay.close();
		}
	} else
	{
		std::cout << "Error writing output file for _dynamic_array_synapses_31_delay." << endl;
	}
	ofstream outfile__dynamic_array_synapses_31_lastupdate;
	outfile__dynamic_array_synapses_31_lastupdate.open("results\\_dynamic_array_synapses_31_lastupdate_-6714176678221229449", ios::binary | ios::out);
	if(outfile__dynamic_array_synapses_31_lastupdate.is_open())
	{
        if (! _dynamic_array_synapses_31_lastupdate.empty() )
        {
			outfile__dynamic_array_synapses_31_lastupdate.write(reinterpret_cast<char*>(&_dynamic_array_synapses_31_lastupdate[0]), _dynamic_array_synapses_31_lastupdate.size()*sizeof(_dynamic_array_synapses_31_lastupdate[0]));
		    outfile__dynamic_array_synapses_31_lastupdate.close();
		}
	} else
	{
		std::cout << "Error writing output file for _dynamic_array_synapses_31_lastupdate." << endl;
	}
	ofstream outfile__dynamic_array_synapses_31_N_incoming;
	outfile__dynamic_array_synapses_31_N_incoming.open("results\\_dynamic_array_synapses_31_N_incoming_-6808283219678156276", ios::binary | ios::out);
	if(outfile__dynamic_array_synapses_31_N_incoming.is_open())
	{
        if (! _dynamic_array_synapses_31_N_incoming.empty() )
        {
			outfile__dynamic_array_synapses_31_N_incoming.write(reinterpret_cast<char*>(&_dynamic_array_synapses_31_N_incoming[0]), _dynamic_array_synapses_31_N_incoming.size()*sizeof(_dynamic_array_synapses_31_N_incoming[0]));
		    outfile__dynamic_array_synapses_31_N_incoming.close();
		}
	} else
	{
		std::cout << "Error writing output file for _dynamic_array_synapses_31_N_incoming." << endl;
	}
	ofstream outfile__dynamic_array_synapses_31_N_outgoing;
	outfile__dynamic_array_synapses_31_N_outgoing.open("results\\_dynamic_array_synapses_31_N_outgoing_-7373834467813931787", ios::binary | ios::out);
	if(outfile__dynamic_array_synapses_31_N_outgoing.is_open())
	{
        if (! _dynamic_array_synapses_31_N_outgoing.empty() )
        {
			outfile__dynamic_array_synapses_31_N_outgoing.write(reinterpret_cast<char*>(&_dynamic_array_synapses_31_N_outgoing[0]), _dynamic_array_synapses_31_N_outgoing.size()*sizeof(_dynamic_array_synapses_31_N_outgoing[0]));
		    outfile__dynamic_array_synapses_31_N_outgoing.close();
		}
	} else
	{
		std::cout << "Error writing output file for _dynamic_array_synapses_31_N_outgoing." << endl;
	}
	ofstream outfile__dynamic_array_synapses_31_R;
	outfile__dynamic_array_synapses_31_R.open("results\\_dynamic_array_synapses_31_R_2777802280974733497", ios::binary | ios::out);
	if(outfile__dynamic_array_synapses_31_R.is_open())
	{
        if (! _dynamic_array_synapses_31_R.empty() )
        {
			outfile__dynamic_array_synapses_31_R.write(reinterpret_cast<char*>(&_dynamic_array_synapses_31_R[0]), _dynamic_array_synapses_31_R.size()*sizeof(_dynamic_array_synapses_31_R[0]));
		    outfile__dynamic_array_synapses_31_R.close();
		}
	} else
	{
		std::cout << "Error writing output file for _dynamic_array_synapses_31_R." << endl;
	}
	ofstream outfile__dynamic_array_synapses_31_wght;
	outfile__dynamic_array_synapses_31_wght.open("results\\_dynamic_array_synapses_31_wght_-7208317495081804938", ios::binary | ios::out);
	if(outfile__dynamic_array_synapses_31_wght.is_open())
	{
        if (! _dynamic_array_synapses_31_wght.empty() )
        {
			outfile__dynamic_array_synapses_31_wght.write(reinterpret_cast<char*>(&_dynamic_array_synapses_31_wght[0]), _dynamic_array_synapses_31_wght.size()*sizeof(_dynamic_array_synapses_31_wght[0]));
		    outfile__dynamic_array_synapses_31_wght.close();
		}
	} else
	{
		std::cout << "Error writing output file for _dynamic_array_synapses_31_wght." << endl;
	}
	ofstream outfile__dynamic_array_synapses_32__synaptic_post;
	outfile__dynamic_array_synapses_32__synaptic_post.open("results\\_dynamic_array_synapses_32__synaptic_post_3902149829404861744", ios::binary | ios::out);
	if(outfile__dynamic_array_synapses_32__synaptic_post.is_open())
	{
        if (! _dynamic_array_synapses_32__synaptic_post.empty() )
        {
			outfile__dynamic_array_synapses_32__synaptic_post.write(reinterpret_cast<char*>(&_dynamic_array_synapses_32__synaptic_post[0]), _dynamic_array_synapses_32__synaptic_post.size()*sizeof(_dynamic_array_synapses_32__synaptic_post[0]));
		    outfile__dynamic_array_synapses_32__synaptic_post.close();
		}
	} else
	{
		std::cout << "Error writing output file for _dynamic_array_synapses_32__synaptic_post." << endl;
	}
	ofstream outfile__dynamic_array_synapses_32__synaptic_pre;
	outfile__dynamic_array_synapses_32__synaptic_pre.open("results\\_dynamic_array_synapses_32__synaptic_pre_-1279243365558726243", ios::binary | ios::out);
	if(outfile__dynamic_array_synapses_32__synaptic_pre.is_open())
	{
        if (! _dynamic_array_synapses_32__synaptic_pre.empty() )
        {
			outfile__dynamic_array_synapses_32__synaptic_pre.write(reinterpret_cast<char*>(&_dynamic_array_synapses_32__synaptic_pre[0]), _dynamic_array_synapses_32__synaptic_pre.size()*sizeof(_dynamic_array_synapses_32__synaptic_pre[0]));
		    outfile__dynamic_array_synapses_32__synaptic_pre.close();
		}
	} else
	{
		std::cout << "Error writing output file for _dynamic_array_synapses_32__synaptic_pre." << endl;
	}
	ofstream outfile__dynamic_array_synapses_32_delay;
	outfile__dynamic_array_synapses_32_delay.open("results\\_dynamic_array_synapses_32_delay_462966556356367131", ios::binary | ios::out);
	if(outfile__dynamic_array_synapses_32_delay.is_open())
	{
        if (! _dynamic_array_synapses_32_delay.empty() )
        {
			outfile__dynamic_array_synapses_32_delay.write(reinterpret_cast<char*>(&_dynamic_array_synapses_32_delay[0]), _dynamic_array_synapses_32_delay.size()*sizeof(_dynamic_array_synapses_32_delay[0]));
		    outfile__dynamic_array_synapses_32_delay.close();
		}
	} else
	{
		std::cout << "Error writing output file for _dynamic_array_synapses_32_delay." << endl;
	}
	ofstream outfile__dynamic_array_synapses_32_lastupdate;
	outfile__dynamic_array_synapses_32_lastupdate.open("results\\_dynamic_array_synapses_32_lastupdate_-8534362344074486848", ios::binary | ios::out);
	if(outfile__dynamic_array_synapses_32_lastupdate.is_open())
	{
        if (! _dynamic_array_synapses_32_lastupdate.empty() )
        {
			outfile__dynamic_array_synapses_32_lastupdate.write(reinterpret_cast<char*>(&_dynamic_array_synapses_32_lastupdate[0]), _dynamic_array_synapses_32_lastupdate.size()*sizeof(_dynamic_array_synapses_32_lastupdate[0]));
		    outfile__dynamic_array_synapses_32_lastupdate.close();
		}
	} else
	{
		std::cout << "Error writing output file for _dynamic_array_synapses_32_lastupdate." << endl;
	}
	ofstream outfile__dynamic_array_synapses_32_N_incoming;
	outfile__dynamic_array_synapses_32_N_incoming.open("results\\_dynamic_array_synapses_32_N_incoming_6960682863985115952", ios::binary | ios::out);
	if(outfile__dynamic_array_synapses_32_N_incoming.is_open())
	{
        if (! _dynamic_array_synapses_32_N_incoming.empty() )
        {
			outfile__dynamic_array_synapses_32_N_incoming.write(reinterpret_cast<char*>(&_dynamic_array_synapses_32_N_incoming[0]), _dynamic_array_synapses_32_N_incoming.size()*sizeof(_dynamic_array_synapses_32_N_incoming[0]));
		    outfile__dynamic_array_synapses_32_N_incoming.close();
		}
	} else
	{
		std::cout << "Error writing output file for _dynamic_array_synapses_32_N_incoming." << endl;
	}
	ofstream outfile__dynamic_array_synapses_32_N_outgoing;
	outfile__dynamic_array_synapses_32_N_outgoing.open("results\\_dynamic_array_synapses_32_N_outgoing_-6549669275483807726", ios::binary | ios::out);
	if(outfile__dynamic_array_synapses_32_N_outgoing.is_open())
	{
        if (! _dynamic_array_synapses_32_N_outgoing.empty() )
        {
			outfile__dynamic_array_synapses_32_N_outgoing.write(reinterpret_cast<char*>(&_dynamic_array_synapses_32_N_outgoing[0]), _dynamic_array_synapses_32_N_outgoing.size()*sizeof(_dynamic_array_synapses_32_N_outgoing[0]));
		    outfile__dynamic_array_synapses_32_N_outgoing.close();
		}
	} else
	{
		std::cout << "Error writing output file for _dynamic_array_synapses_32_N_outgoing." << endl;
	}
	ofstream outfile__dynamic_array_synapses_32_R;
	outfile__dynamic_array_synapses_32_R.open("results\\_dynamic_array_synapses_32_R_-2893583197581770851", ios::binary | ios::out);
	if(outfile__dynamic_array_synapses_32_R.is_open())
	{
        if (! _dynamic_array_synapses_32_R.empty() )
        {
			outfile__dynamic_array_synapses_32_R.write(reinterpret_cast<char*>(&_dynamic_array_synapses_32_R[0]), _dynamic_array_synapses_32_R.size()*sizeof(_dynamic_array_synapses_32_R[0]));
		    outfile__dynamic_array_synapses_32_R.close();
		}
	} else
	{
		std::cout << "Error writing output file for _dynamic_array_synapses_32_R." << endl;
	}
	ofstream outfile__dynamic_array_synapses_32_wght;
	outfile__dynamic_array_synapses_32_wght.open("results\\_dynamic_array_synapses_32_wght_3687640199012313104", ios::binary | ios::out);
	if(outfile__dynamic_array_synapses_32_wght.is_open())
	{
        if (! _dynamic_array_synapses_32_wght.empty() )
        {
			outfile__dynamic_array_synapses_32_wght.write(reinterpret_cast<char*>(&_dynamic_array_synapses_32_wght[0]), _dynamic_array_synapses_32_wght.size()*sizeof(_dynamic_array_synapses_32_wght[0]));
		    outfile__dynamic_array_synapses_32_wght.close();
		}
	} else
	{
		std::cout << "Error writing output file for _dynamic_array_synapses_32_wght." << endl;
	}
	ofstream outfile__dynamic_array_synapses_33__synaptic_post;
	outfile__dynamic_array_synapses_33__synaptic_post.open("results\\_dynamic_array_synapses_33__synaptic_post_7855701861746181125", ios::binary | ios::out);
	if(outfile__dynamic_array_synapses_33__synaptic_post.is_open())
	{
        if (! _dynamic_array_synapses_33__synaptic_post.empty() )
        {
			outfile__dynamic_array_synapses_33__synaptic_post.write(reinterpret_cast<char*>(&_dynamic_array_synapses_33__synaptic_post[0]), _dynamic_array_synapses_33__synaptic_post.size()*sizeof(_dynamic_array_synapses_33__synaptic_post[0]));
		    outfile__dynamic_array_synapses_33__synaptic_post.close();
		}
	} else
	{
		std::cout << "Error writing output file for _dynamic_array_synapses_33__synaptic_post." << endl;
	}
	ofstream outfile__dynamic_array_synapses_33__synaptic_pre;
	outfile__dynamic_array_synapses_33__synaptic_pre.open("results\\_dynamic_array_synapses_33__synaptic_pre_-2800762775726496508", ios::binary | ios::out);
	if(outfile__dynamic_array_synapses_33__synaptic_pre.is_open())
	{
        if (! _dynamic_array_synapses_33__synaptic_pre.empty() )
        {
			outfile__dynamic_array_synapses_33__synaptic_pre.write(reinterpret_cast<char*>(&_dynamic_array_synapses_33__synaptic_pre[0]), _dynamic_array_synapses_33__synaptic_pre.size()*sizeof(_dynamic_array_synapses_33__synaptic_pre[0]));
		    outfile__dynamic_array_synapses_33__synaptic_pre.close();
		}
	} else
	{
		std::cout << "Error writing output file for _dynamic_array_synapses_33__synaptic_pre." << endl;
	}
	ofstream outfile__dynamic_array_synapses_33_delay;
	outfile__dynamic_array_synapses_33_delay.open("results\\_dynamic_array_synapses_33_delay_186710161929056795", ios::binary | ios::out);
	if(outfile__dynamic_array_synapses_33_delay.is_open())
	{
        if (! _dynamic_array_synapses_33_delay.empty() )
        {
			outfile__dynamic_array_synapses_33_delay.write(reinterpret_cast<char*>(&_dynamic_array_synapses_33_delay[0]), _dynamic_array_synapses_33_delay.size()*sizeof(_dynamic_array_synapses_33_delay[0]));
		    outfile__dynamic_array_synapses_33_delay.close();
		}
	} else
	{
		std::cout << "Error writing output file for _dynamic_array_synapses_33_delay." << endl;
	}
	ofstream outfile__dynamic_array_synapses_33_lastupdate;
	outfile__dynamic_array_synapses_33_lastupdate.open("results\\_dynamic_array_synapses_33_lastupdate_-5366239604464899330", ios::binary | ios::out);
	if(outfile__dynamic_array_synapses_33_lastupdate.is_open())
	{
        if (! _dynamic_array_synapses_33_lastupdate.empty() )
        {
			outfile__dynamic_array_synapses_33_lastupdate.write(reinterpret_cast<char*>(&_dynamic_array_synapses_33_lastupdate[0]), _dynamic_array_synapses_33_lastupdate.size()*sizeof(_dynamic_array_synapses_33_lastupdate[0]));
		    outfile__dynamic_array_synapses_33_lastupdate.close();
		}
	} else
	{
		std::cout << "Error writing output file for _dynamic_array_synapses_33_lastupdate." << endl;
	}
	ofstream outfile__dynamic_array_synapses_33_N_incoming;
	outfile__dynamic_array_synapses_33_N_incoming.open("results\\_dynamic_array_synapses_33_N_incoming_4605706003237739443", ios::binary | ios::out);
	if(outfile__dynamic_array_synapses_33_N_incoming.is_open())
	{
        if (! _dynamic_array_synapses_33_N_incoming.empty() )
        {
			outfile__dynamic_array_synapses_33_N_incoming.write(reinterpret_cast<char*>(&_dynamic_array_synapses_33_N_incoming[0]), _dynamic_array_synapses_33_N_incoming.size()*sizeof(_dynamic_array_synapses_33_N_incoming[0]));
		    outfile__dynamic_array_synapses_33_N_incoming.close();
		}
	} else
	{
		std::cout << "Error writing output file for _dynamic_array_synapses_33_N_incoming." << endl;
	}
	ofstream outfile__dynamic_array_synapses_33_N_outgoing;
	outfile__dynamic_array_synapses_33_N_outgoing.open("results\\_dynamic_array_synapses_33_N_outgoing_-3052437870725917449", ios::binary | ios::out);
	if(outfile__dynamic_array_synapses_33_N_outgoing.is_open())
	{
        if (! _dynamic_array_synapses_33_N_outgoing.empty() )
        {
			outfile__dynamic_array_synapses_33_N_outgoing.write(reinterpret_cast<char*>(&_dynamic_array_synapses_33_N_outgoing[0]), _dynamic_array_synapses_33_N_outgoing.size()*sizeof(_dynamic_array_synapses_33_N_outgoing[0]));
		    outfile__dynamic_array_synapses_33_N_outgoing.close();
		}
	} else
	{
		std::cout << "Error writing output file for _dynamic_array_synapses_33_N_outgoing." << endl;
	}
	ofstream outfile__dynamic_array_synapses_33_R;
	outfile__dynamic_array_synapses_33_R.open("results\\_dynamic_array_synapses_33_R_4145854288281535277", ios::binary | ios::out);
	if(outfile__dynamic_array_synapses_33_R.is_open())
	{
        if (! _dynamic_array_synapses_33_R.empty() )
        {
			outfile__dynamic_array_synapses_33_R.write(reinterpret_cast<char*>(&_dynamic_array_synapses_33_R[0]), _dynamic_array_synapses_33_R.size()*sizeof(_dynamic_array_synapses_33_R[0]));
		    outfile__dynamic_array_synapses_33_R.close();
		}
	} else
	{
		std::cout << "Error writing output file for _dynamic_array_synapses_33_R." << endl;
	}
	ofstream outfile__dynamic_array_synapses_33_wght;
	outfile__dynamic_array_synapses_33_wght.open("results\\_dynamic_array_synapses_33_wght_-325887328750963825", ios::binary | ios::out);
	if(outfile__dynamic_array_synapses_33_wght.is_open())
	{
        if (! _dynamic_array_synapses_33_wght.empty() )
        {
			outfile__dynamic_array_synapses_33_wght.write(reinterpret_cast<char*>(&_dynamic_array_synapses_33_wght[0]), _dynamic_array_synapses_33_wght.size()*sizeof(_dynamic_array_synapses_33_wght[0]));
		    outfile__dynamic_array_synapses_33_wght.close();
		}
	} else
	{
		std::cout << "Error writing output file for _dynamic_array_synapses_33_wght." << endl;
	}
	ofstream outfile__dynamic_array_synapses_34__synaptic_post;
	outfile__dynamic_array_synapses_34__synaptic_post.open("results\\_dynamic_array_synapses_34__synaptic_post_5425014911715896788", ios::binary | ios::out);
	if(outfile__dynamic_array_synapses_34__synaptic_post.is_open())
	{
        if (! _dynamic_array_synapses_34__synaptic_post.empty() )
        {
			outfile__dynamic_array_synapses_34__synaptic_post.write(reinterpret_cast<char*>(&_dynamic_array_synapses_34__synaptic_post[0]), _dynamic_array_synapses_34__synaptic_post.size()*sizeof(_dynamic_array_synapses_34__synaptic_post[0]));
		    outfile__dynamic_array_synapses_34__synaptic_post.close();
		}
	} else
	{
		std::cout << "Error writing output file for _dynamic_array_synapses_34__synaptic_post." << endl;
	}
	ofstream outfile__dynamic_array_synapses_34__synaptic_pre;
	outfile__dynamic_array_synapses_34__synaptic_pre.open("results\\_dynamic_array_synapses_34__synaptic_pre_8971166156200179821", ios::binary | ios::out);
	if(outfile__dynamic_array_synapses_34__synaptic_pre.is_open())
	{
        if (! _dynamic_array_synapses_34__synaptic_pre.empty() )
        {
			outfile__dynamic_array_synapses_34__synaptic_pre.write(reinterpret_cast<char*>(&_dynamic_array_synapses_34__synaptic_pre[0]), _dynamic_array_synapses_34__synaptic_pre.size()*sizeof(_dynamic_array_synapses_34__synaptic_pre[0]));
		    outfile__dynamic_array_synapses_34__synaptic_pre.close();
		}
	} else
	{
		std::cout << "Error writing output file for _dynamic_array_synapses_34__synaptic_pre." << endl;
	}
	ofstream outfile__dynamic_array_synapses_34_delay;
	outfile__dynamic_array_synapses_34_delay.open("results\\_dynamic_array_synapses_34_delay_-2018748199593016842", ios::binary | ios::out);
	if(outfile__dynamic_array_synapses_34_delay.is_open())
	{
        if (! _dynamic_array_synapses_34_delay.empty() )
        {
			outfile__dynamic_array_synapses_34_delay.write(reinterpret_cast<char*>(&_dynamic_array_synapses_34_delay[0]), _dynamic_array_synapses_34_delay.size()*sizeof(_dynamic_array_synapses_34_delay[0]));
		    outfile__dynamic_array_synapses_34_delay.close();
		}
	} else
	{
		std::cout << "Error writing output file for _dynamic_array_synapses_34_delay." << endl;
	}
	ofstream outfile__dynamic_array_synapses_34_lastupdate;
	outfile__dynamic_array_synapses_34_lastupdate.open("results\\_dynamic_array_synapses_34_lastupdate_6804232585042897228", ios::binary | ios::out);
	if(outfile__dynamic_array_synapses_34_lastupdate.is_open())
	{
        if (! _dynamic_array_synapses_34_lastupdate.empty() )
        {
			outfile__dynamic_array_synapses_34_lastupdate.write(reinterpret_cast<char*>(&_dynamic_array_synapses_34_lastupdate[0]), _dynamic_array_synapses_34_lastupdate.size()*sizeof(_dynamic_array_synapses_34_lastupdate[0]));
		    outfile__dynamic_array_synapses_34_lastupdate.close();
		}
	} else
	{
		std::cout << "Error writing output file for _dynamic_array_synapses_34_lastupdate." << endl;
	}
	ofstream outfile__dynamic_array_synapses_34_N_incoming;
	outfile__dynamic_array_synapses_34_N_incoming.open("results\\_dynamic_array_synapses_34_N_incoming_4219102716220230452", ios::binary | ios::out);
	if(outfile__dynamic_array_synapses_34_N_incoming.is_open())
	{
        if (! _dynamic_array_synapses_34_N_incoming.empty() )
        {
			outfile__dynamic_array_synapses_34_N_incoming.write(reinterpret_cast<char*>(&_dynamic_array_synapses_34_N_incoming[0]), _dynamic_array_synapses_34_N_incoming.size()*sizeof(_dynamic_array_synapses_34_N_incoming[0]));
		    outfile__dynamic_array_synapses_34_N_incoming.close();
		}
	} else
	{
		std::cout << "Error writing output file for _dynamic_array_synapses_34_N_incoming." << endl;
	}
	ofstream outfile__dynamic_array_synapses_34_N_outgoing;
	outfile__dynamic_array_synapses_34_N_outgoing.open("results\\_dynamic_array_synapses_34_N_outgoing_-3607771433822881226", ios::binary | ios::out);
	if(outfile__dynamic_array_synapses_34_N_outgoing.is_open())
	{
        if (! _dynamic_array_synapses_34_N_outgoing.empty() )
        {
			outfile__dynamic_array_synapses_34_N_outgoing.write(reinterpret_cast<char*>(&_dynamic_array_synapses_34_N_outgoing[0]), _dynamic_array_synapses_34_N_outgoing.size()*sizeof(_dynamic_array_synapses_34_N_outgoing[0]));
		    outfile__dynamic_array_synapses_34_N_outgoing.close();
		}
	} else
	{
		std::cout << "Error writing output file for _dynamic_array_synapses_34_N_outgoing." << endl;
	}
	ofstream outfile__dynamic_array_synapses_34_R;
	outfile__dynamic_array_synapses_34_R.open("results\\_dynamic_array_synapses_34_R_772948904492943174", ios::binary | ios::out);
	if(outfile__dynamic_array_synapses_34_R.is_open())
	{
        if (! _dynamic_array_synapses_34_R.empty() )
        {
			outfile__dynamic_array_synapses_34_R.write(reinterpret_cast<char*>(&_dynamic_array_synapses_34_R[0]), _dynamic_array_synapses_34_R.size()*sizeof(_dynamic_array_synapses_34_R[0]));
		    outfile__dynamic_array_synapses_34_R.close();
		}
	} else
	{
		std::cout << "Error writing output file for _dynamic_array_synapses_34_R." << endl;
	}
	ofstream outfile__dynamic_array_synapses_34_wght;
	outfile__dynamic_array_synapses_34_wght.open("results\\_dynamic_array_synapses_34_wght_-157609744103413602", ios::binary | ios::out);
	if(outfile__dynamic_array_synapses_34_wght.is_open())
	{
        if (! _dynamic_array_synapses_34_wght.empty() )
        {
			outfile__dynamic_array_synapses_34_wght.write(reinterpret_cast<char*>(&_dynamic_array_synapses_34_wght[0]), _dynamic_array_synapses_34_wght.size()*sizeof(_dynamic_array_synapses_34_wght[0]));
		    outfile__dynamic_array_synapses_34_wght.close();
		}
	} else
	{
		std::cout << "Error writing output file for _dynamic_array_synapses_34_wght." << endl;
	}
	ofstream outfile__dynamic_array_synapses_35__synaptic_post;
	outfile__dynamic_array_synapses_35__synaptic_post.open("results\\_dynamic_array_synapses_35__synaptic_post_8065806107896119522", ios::binary | ios::out);
	if(outfile__dynamic_array_synapses_35__synaptic_post.is_open())
	{
        if (! _dynamic_array_synapses_35__synaptic_post.empty() )
        {
			outfile__dynamic_array_synapses_35__synaptic_post.write(reinterpret_cast<char*>(&_dynamic_array_synapses_35__synaptic_post[0]), _dynamic_array_synapses_35__synaptic_post.size()*sizeof(_dynamic_array_synapses_35__synaptic_post[0]));
		    outfile__dynamic_array_synapses_35__synaptic_post.close();
		}
	} else
	{
		std::cout << "Error writing output file for _dynamic_array_synapses_35__synaptic_post." << endl;
	}
	ofstream outfile__dynamic_array_synapses_35__synaptic_pre;
	outfile__dynamic_array_synapses_35__synaptic_pre.open("results\\_dynamic_array_synapses_35__synaptic_pre_-6454957083318169872", ios::binary | ios::out);
	if(outfile__dynamic_array_synapses_35__synaptic_pre.is_open())
	{
        if (! _dynamic_array_synapses_35__synaptic_pre.empty() )
        {
			outfile__dynamic_array_synapses_35__synaptic_pre.write(reinterpret_cast<char*>(&_dynamic_array_synapses_35__synaptic_pre[0]), _dynamic_array_synapses_35__synaptic_pre.size()*sizeof(_dynamic_array_synapses_35__synaptic_pre[0]));
		    outfile__dynamic_array_synapses_35__synaptic_pre.close();
		}
	} else
	{
		std::cout << "Error writing output file for _dynamic_array_synapses_35__synaptic_pre." << endl;
	}
	ofstream outfile__dynamic_array_synapses_35_delay;
	outfile__dynamic_array_synapses_35_delay.open("results\\_dynamic_array_synapses_35_delay_3657250101399361193", ios::binary | ios::out);
	if(outfile__dynamic_array_synapses_35_delay.is_open())
	{
        if (! _dynamic_array_synapses_35_delay.empty() )
        {
			outfile__dynamic_array_synapses_35_delay.write(reinterpret_cast<char*>(&_dynamic_array_synapses_35_delay[0]), _dynamic_array_synapses_35_delay.size()*sizeof(_dynamic_array_synapses_35_delay[0]));
		    outfile__dynamic_array_synapses_35_delay.close();
		}
	} else
	{
		std::cout << "Error writing output file for _dynamic_array_synapses_35_delay." << endl;
	}
	ofstream outfile__dynamic_array_synapses_35_lastupdate;
	outfile__dynamic_array_synapses_35_lastupdate.open("results\\_dynamic_array_synapses_35_lastupdate_-3374678321326610019", ios::binary | ios::out);
	if(outfile__dynamic_array_synapses_35_lastupdate.is_open())
	{
        if (! _dynamic_array_synapses_35_lastupdate.empty() )
        {
			outfile__dynamic_array_synapses_35_lastupdate.write(reinterpret_cast<char*>(&_dynamic_array_synapses_35_lastupdate[0]), _dynamic_array_synapses_35_lastupdate.size()*sizeof(_dynamic_array_synapses_35_lastupdate[0]));
		    outfile__dynamic_array_synapses_35_lastupdate.close();
		}
	} else
	{
		std::cout << "Error writing output file for _dynamic_array_synapses_35_lastupdate." << endl;
	}
	ofstream outfile__dynamic_array_synapses_35_N_incoming;
	outfile__dynamic_array_synapses_35_N_incoming.open("results\\_dynamic_array_synapses_35_N_incoming_8314118979259561932", ios::binary | ios::out);
	if(outfile__dynamic_array_synapses_35_N_incoming.is_open())
	{
        if (! _dynamic_array_synapses_35_N_incoming.empty() )
        {
			outfile__dynamic_array_synapses_35_N_incoming.write(reinterpret_cast<char*>(&_dynamic_array_synapses_35_N_incoming[0]), _dynamic_array_synapses_35_N_incoming.size()*sizeof(_dynamic_array_synapses_35_N_incoming[0]));
		    outfile__dynamic_array_synapses_35_N_incoming.close();
		}
	} else
	{
		std::cout << "Error writing output file for _dynamic_array_synapses_35_N_incoming." << endl;
	}
	ofstream outfile__dynamic_array_synapses_35_N_outgoing;
	outfile__dynamic_array_synapses_35_N_outgoing.open("results\\_dynamic_array_synapses_35_N_outgoing_6916554267797326048", ios::binary | ios::out);
	if(outfile__dynamic_array_synapses_35_N_outgoing.is_open())
	{
        if (! _dynamic_array_synapses_35_N_outgoing.empty() )
        {
			outfile__dynamic_array_synapses_35_N_outgoing.write(reinterpret_cast<char*>(&_dynamic_array_synapses_35_N_outgoing[0]), _dynamic_array_synapses_35_N_outgoing.size()*sizeof(_dynamic_array_synapses_35_N_outgoing[0]));
		    outfile__dynamic_array_synapses_35_N_outgoing.close();
		}
	} else
	{
		std::cout << "Error writing output file for _dynamic_array_synapses_35_N_outgoing." << endl;
	}
	ofstream outfile__dynamic_array_synapses_35_R;
	outfile__dynamic_array_synapses_35_R.open("results\\_dynamic_array_synapses_35_R_-8811759951008302690", ios::binary | ios::out);
	if(outfile__dynamic_array_synapses_35_R.is_open())
	{
        if (! _dynamic_array_synapses_35_R.empty() )
        {
			outfile__dynamic_array_synapses_35_R.write(reinterpret_cast<char*>(&_dynamic_array_synapses_35_R[0]), _dynamic_array_synapses_35_R.size()*sizeof(_dynamic_array_synapses_35_R[0]));
		    outfile__dynamic_array_synapses_35_R.close();
		}
	} else
	{
		std::cout << "Error writing output file for _dynamic_array_synapses_35_R." << endl;
	}
	ofstream outfile__dynamic_array_synapses_35_wght;
	outfile__dynamic_array_synapses_35_wght.open("results\\_dynamic_array_synapses_35_wght_-5339064234430991390", ios::binary | ios::out);
	if(outfile__dynamic_array_synapses_35_wght.is_open())
	{
        if (! _dynamic_array_synapses_35_wght.empty() )
        {
			outfile__dynamic_array_synapses_35_wght.write(reinterpret_cast<char*>(&_dynamic_array_synapses_35_wght[0]), _dynamic_array_synapses_35_wght.size()*sizeof(_dynamic_array_synapses_35_wght[0]));
		    outfile__dynamic_array_synapses_35_wght.close();
		}
	} else
	{
		std::cout << "Error writing output file for _dynamic_array_synapses_35_wght." << endl;
	}
	ofstream outfile__dynamic_array_synapses_36__synaptic_post;
	outfile__dynamic_array_synapses_36__synaptic_post.open("results\\_dynamic_array_synapses_36__synaptic_post_-3525612892904260561", ios::binary | ios::out);
	if(outfile__dynamic_array_synapses_36__synaptic_post.is_open())
	{
        if (! _dynamic_array_synapses_36__synaptic_post.empty() )
        {
			outfile__dynamic_array_synapses_36__synaptic_post.write(reinterpret_cast<char*>(&_dynamic_array_synapses_36__synaptic_post[0]), _dynamic_array_synapses_36__synaptic_post.size()*sizeof(_dynamic_array_synapses_36__synaptic_post[0]));
		    outfile__dynamic_array_synapses_36__synaptic_post.close();
		}
	} else
	{
		std::cout << "Error writing output file for _dynamic_array_synapses_36__synaptic_post." << endl;
	}
	ofstream outfile__dynamic_array_synapses_36__synaptic_pre;
	outfile__dynamic_array_synapses_36__synaptic_pre.open("results\\_dynamic_array_synapses_36__synaptic_pre_4965635487283866322", ios::binary | ios::out);
	if(outfile__dynamic_array_synapses_36__synaptic_pre.is_open())
	{
        if (! _dynamic_array_synapses_36__synaptic_pre.empty() )
        {
			outfile__dynamic_array_synapses_36__synaptic_pre.write(reinterpret_cast<char*>(&_dynamic_array_synapses_36__synaptic_pre[0]), _dynamic_array_synapses_36__synaptic_pre.size()*sizeof(_dynamic_array_synapses_36__synaptic_pre[0]));
		    outfile__dynamic_array_synapses_36__synaptic_pre.close();
		}
	} else
	{
		std::cout << "Error writing output file for _dynamic_array_synapses_36__synaptic_pre." << endl;
	}
	ofstream outfile__dynamic_array_synapses_36_delay;
	outfile__dynamic_array_synapses_36_delay.open("results\\_dynamic_array_synapses_36_delay_-1032892613025171552", ios::binary | ios::out);
	if(outfile__dynamic_array_synapses_36_delay.is_open())
	{
        if (! _dynamic_array_synapses_36_delay.empty() )
        {
			outfile__dynamic_array_synapses_36_delay.write(reinterpret_cast<char*>(&_dynamic_array_synapses_36_delay[0]), _dynamic_array_synapses_36_delay.size()*sizeof(_dynamic_array_synapses_36_delay[0]));
		    outfile__dynamic_array_synapses_36_delay.close();
		}
	} else
	{
		std::cout << "Error writing output file for _dynamic_array_synapses_36_delay." << endl;
	}
	ofstream outfile__dynamic_array_synapses_36_lastupdate;
	outfile__dynamic_array_synapses_36_lastupdate.open("results\\_dynamic_array_synapses_36_lastupdate_-5584254651102790321", ios::binary | ios::out);
	if(outfile__dynamic_array_synapses_36_lastupdate.is_open())
	{
        if (! _dynamic_array_synapses_36_lastupdate.empty() )
        {
			outfile__dynamic_array_synapses_36_lastupdate.write(reinterpret_cast<char*>(&_dynamic_array_synapses_36_lastupdate[0]), _dynamic_array_synapses_36_lastupdate.size()*sizeof(_dynamic_array_synapses_36_lastupdate[0]));
		    outfile__dynamic_array_synapses_36_lastupdate.close();
		}
	} else
	{
		std::cout << "Error writing output file for _dynamic_array_synapses_36_lastupdate." << endl;
	}
	ofstream outfile__dynamic_array_synapses_36_N_incoming;
	outfile__dynamic_array_synapses_36_N_incoming.open("results\\_dynamic_array_synapses_36_N_incoming_145217418630095481", ios::binary | ios::out);
	if(outfile__dynamic_array_synapses_36_N_incoming.is_open())
	{
        if (! _dynamic_array_synapses_36_N_incoming.empty() )
        {
			outfile__dynamic_array_synapses_36_N_incoming.write(reinterpret_cast<char*>(&_dynamic_array_synapses_36_N_incoming[0]), _dynamic_array_synapses_36_N_incoming.size()*sizeof(_dynamic_array_synapses_36_N_incoming[0]));
		    outfile__dynamic_array_synapses_36_N_incoming.close();
		}
	} else
	{
		std::cout << "Error writing output file for _dynamic_array_synapses_36_N_incoming." << endl;
	}
	ofstream outfile__dynamic_array_synapses_36_N_outgoing;
	outfile__dynamic_array_synapses_36_N_outgoing.open("results\\_dynamic_array_synapses_36_N_outgoing_-2739836278026092145", ios::binary | ios::out);
	if(outfile__dynamic_array_synapses_36_N_outgoing.is_open())
	{
        if (! _dynamic_array_synapses_36_N_outgoing.empty() )
        {
			outfile__dynamic_array_synapses_36_N_outgoing.write(reinterpret_cast<char*>(&_dynamic_array_synapses_36_N_outgoing[0]), _dynamic_array_synapses_36_N_outgoing.size()*sizeof(_dynamic_array_synapses_36_N_outgoing[0]));
		    outfile__dynamic_array_synapses_36_N_outgoing.close();
		}
	} else
	{
		std::cout << "Error writing output file for _dynamic_array_synapses_36_N_outgoing." << endl;
	}
	ofstream outfile__dynamic_array_synapses_36_R;
	outfile__dynamic_array_synapses_36_R.open("results\\_dynamic_array_synapses_36_R_-7696597323482934376", ios::binary | ios::out);
	if(outfile__dynamic_array_synapses_36_R.is_open())
	{
        if (! _dynamic_array_synapses_36_R.empty() )
        {
			outfile__dynamic_array_synapses_36_R.write(reinterpret_cast<char*>(&_dynamic_array_synapses_36_R[0]), _dynamic_array_synapses_36_R.size()*sizeof(_dynamic_array_synapses_36_R[0]));
		    outfile__dynamic_array_synapses_36_R.close();
		}
	} else
	{
		std::cout << "Error writing output file for _dynamic_array_synapses_36_R." << endl;
	}
	ofstream outfile__dynamic_array_synapses_36_wght;
	outfile__dynamic_array_synapses_36_wght.open("results\\_dynamic_array_synapses_36_wght_4175571747662778362", ios::binary | ios::out);
	if(outfile__dynamic_array_synapses_36_wght.is_open())
	{
        if (! _dynamic_array_synapses_36_wght.empty() )
        {
			outfile__dynamic_array_synapses_36_wght.write(reinterpret_cast<char*>(&_dynamic_array_synapses_36_wght[0]), _dynamic_array_synapses_36_wght.size()*sizeof(_dynamic_array_synapses_36_wght[0]));
		    outfile__dynamic_array_synapses_36_wght.close();
		}
	} else
	{
		std::cout << "Error writing output file for _dynamic_array_synapses_36_wght." << endl;
	}
	ofstream outfile__dynamic_array_synapses_37__synaptic_post;
	outfile__dynamic_array_synapses_37__synaptic_post.open("results\\_dynamic_array_synapses_37__synaptic_post_-8501942835727226075", ios::binary | ios::out);
	if(outfile__dynamic_array_synapses_37__synaptic_post.is_open())
	{
        if (! _dynamic_array_synapses_37__synaptic_post.empty() )
        {
			outfile__dynamic_array_synapses_37__synaptic_post.write(reinterpret_cast<char*>(&_dynamic_array_synapses_37__synaptic_post[0]), _dynamic_array_synapses_37__synaptic_post.size()*sizeof(_dynamic_array_synapses_37__synaptic_post[0]));
		    outfile__dynamic_array_synapses_37__synaptic_post.close();
		}
	} else
	{
		std::cout << "Error writing output file for _dynamic_array_synapses_37__synaptic_post." << endl;
	}
	ofstream outfile__dynamic_array_synapses_37__synaptic_pre;
	outfile__dynamic_array_synapses_37__synaptic_pre.open("results\\_dynamic_array_synapses_37__synaptic_pre_-6035492922968653525", ios::binary | ios::out);
	if(outfile__dynamic_array_synapses_37__synaptic_pre.is_open())
	{
        if (! _dynamic_array_synapses_37__synaptic_pre.empty() )
        {
			outfile__dynamic_array_synapses_37__synaptic_pre.write(reinterpret_cast<char*>(&_dynamic_array_synapses_37__synaptic_pre[0]), _dynamic_array_synapses_37__synaptic_pre.size()*sizeof(_dynamic_array_synapses_37__synaptic_pre[0]));
		    outfile__dynamic_array_synapses_37__synaptic_pre.close();
		}
	} else
	{
		std::cout << "Error writing output file for _dynamic_array_synapses_37__synaptic_pre." << endl;
	}
	ofstream outfile__dynamic_array_synapses_37_delay;
	outfile__dynamic_array_synapses_37_delay.open("results\\_dynamic_array_synapses_37_delay_-7405299129688735866", ios::binary | ios::out);
	if(outfile__dynamic_array_synapses_37_delay.is_open())
	{
        if (! _dynamic_array_synapses_37_delay.empty() )
        {
			outfile__dynamic_array_synapses_37_delay.write(reinterpret_cast<char*>(&_dynamic_array_synapses_37_delay[0]), _dynamic_array_synapses_37_delay.size()*sizeof(_dynamic_array_synapses_37_delay[0]));
		    outfile__dynamic_array_synapses_37_delay.close();
		}
	} else
	{
		std::cout << "Error writing output file for _dynamic_array_synapses_37_delay." << endl;
	}
	ofstream outfile__dynamic_array_synapses_37_lastupdate;
	outfile__dynamic_array_synapses_37_lastupdate.open("results\\_dynamic_array_synapses_37_lastupdate_-6983258797854373912", ios::binary | ios::out);
	if(outfile__dynamic_array_synapses_37_lastupdate.is_open())
	{
        if (! _dynamic_array_synapses_37_lastupdate.empty() )
        {
			outfile__dynamic_array_synapses_37_lastupdate.write(reinterpret_cast<char*>(&_dynamic_array_synapses_37_lastupdate[0]), _dynamic_array_synapses_37_lastupdate.size()*sizeof(_dynamic_array_synapses_37_lastupdate[0]));
		    outfile__dynamic_array_synapses_37_lastupdate.close();
		}
	} else
	{
		std::cout << "Error writing output file for _dynamic_array_synapses_37_lastupdate." << endl;
	}
	ofstream outfile__dynamic_array_synapses_37_N_incoming;
	outfile__dynamic_array_synapses_37_N_incoming.open("results\\_dynamic_array_synapses_37_N_incoming_-2222906403924279150", ios::binary | ios::out);
	if(outfile__dynamic_array_synapses_37_N_incoming.is_open())
	{
        if (! _dynamic_array_synapses_37_N_incoming.empty() )
        {
			outfile__dynamic_array_synapses_37_N_incoming.write(reinterpret_cast<char*>(&_dynamic_array_synapses_37_N_incoming[0]), _dynamic_array_synapses_37_N_incoming.size()*sizeof(_dynamic_array_synapses_37_N_incoming[0]));
		    outfile__dynamic_array_synapses_37_N_incoming.close();
		}
	} else
	{
		std::cout << "Error writing output file for _dynamic_array_synapses_37_N_incoming." << endl;
	}
	ofstream outfile__dynamic_array_synapses_37_N_outgoing;
	outfile__dynamic_array_synapses_37_N_outgoing.open("results\\_dynamic_array_synapses_37_N_outgoing_6907754194064286567", ios::binary | ios::out);
	if(outfile__dynamic_array_synapses_37_N_outgoing.is_open())
	{
        if (! _dynamic_array_synapses_37_N_outgoing.empty() )
        {
			outfile__dynamic_array_synapses_37_N_outgoing.write(reinterpret_cast<char*>(&_dynamic_array_synapses_37_N_outgoing[0]), _dynamic_array_synapses_37_N_outgoing.size()*sizeof(_dynamic_array_synapses_37_N_outgoing[0]));
		    outfile__dynamic_array_synapses_37_N_outgoing.close();
		}
	} else
	{
		std::cout << "Error writing output file for _dynamic_array_synapses_37_N_outgoing." << endl;
	}
	ofstream outfile__dynamic_array_synapses_37_R;
	outfile__dynamic_array_synapses_37_R.open("results\\_dynamic_array_synapses_37_R_-7385338672183227354", ios::binary | ios::out);
	if(outfile__dynamic_array_synapses_37_R.is_open())
	{
        if (! _dynamic_array_synapses_37_R.empty() )
        {
			outfile__dynamic_array_synapses_37_R.write(reinterpret_cast<char*>(&_dynamic_array_synapses_37_R[0]), _dynamic_array_synapses_37_R.size()*sizeof(_dynamic_array_synapses_37_R[0]));
		    outfile__dynamic_array_synapses_37_R.close();
		}
	} else
	{
		std::cout << "Error writing output file for _dynamic_array_synapses_37_R." << endl;
	}
	ofstream outfile__dynamic_array_synapses_37_wght;
	outfile__dynamic_array_synapses_37_wght.open("results\\_dynamic_array_synapses_37_wght_2786872461890505939", ios::binary | ios::out);
	if(outfile__dynamic_array_synapses_37_wght.is_open())
	{
        if (! _dynamic_array_synapses_37_wght.empty() )
        {
			outfile__dynamic_array_synapses_37_wght.write(reinterpret_cast<char*>(&_dynamic_array_synapses_37_wght[0]), _dynamic_array_synapses_37_wght.size()*sizeof(_dynamic_array_synapses_37_wght[0]));
		    outfile__dynamic_array_synapses_37_wght.close();
		}
	} else
	{
		std::cout << "Error writing output file for _dynamic_array_synapses_37_wght." << endl;
	}
	ofstream outfile__dynamic_array_synapses_3__synaptic_post;
	outfile__dynamic_array_synapses_3__synaptic_post.open("results\\_dynamic_array_synapses_3__synaptic_post_7366624155637653317", ios::binary | ios::out);
	if(outfile__dynamic_array_synapses_3__synaptic_post.is_open())
	{
        if (! _dynamic_array_synapses_3__synaptic_post.empty() )
        {
			outfile__dynamic_array_synapses_3__synaptic_post.write(reinterpret_cast<char*>(&_dynamic_array_synapses_3__synaptic_post[0]), _dynamic_array_synapses_3__synaptic_post.size()*sizeof(_dynamic_array_synapses_3__synaptic_post[0]));
		    outfile__dynamic_array_synapses_3__synaptic_post.close();
		}
	} else
	{
		std::cout << "Error writing output file for _dynamic_array_synapses_3__synaptic_post." << endl;
	}
	ofstream outfile__dynamic_array_synapses_3__synaptic_pre;
	outfile__dynamic_array_synapses_3__synaptic_pre.open("results\\_dynamic_array_synapses_3__synaptic_pre_-3353109611933328107", ios::binary | ios::out);
	if(outfile__dynamic_array_synapses_3__synaptic_pre.is_open())
	{
        if (! _dynamic_array_synapses_3__synaptic_pre.empty() )
        {
			outfile__dynamic_array_synapses_3__synaptic_pre.write(reinterpret_cast<char*>(&_dynamic_array_synapses_3__synaptic_pre[0]), _dynamic_array_synapses_3__synaptic_pre.size()*sizeof(_dynamic_array_synapses_3__synaptic_pre[0]));
		    outfile__dynamic_array_synapses_3__synaptic_pre.close();
		}
	} else
	{
		std::cout << "Error writing output file for _dynamic_array_synapses_3__synaptic_pre." << endl;
	}
	ofstream outfile__dynamic_array_synapses_3_delay;
	outfile__dynamic_array_synapses_3_delay.open("results\\_dynamic_array_synapses_3_delay_-7915148265008644029", ios::binary | ios::out);
	if(outfile__dynamic_array_synapses_3_delay.is_open())
	{
        if (! _dynamic_array_synapses_3_delay.empty() )
        {
			outfile__dynamic_array_synapses_3_delay.write(reinterpret_cast<char*>(&_dynamic_array_synapses_3_delay[0]), _dynamic_array_synapses_3_delay.size()*sizeof(_dynamic_array_synapses_3_delay[0]));
		    outfile__dynamic_array_synapses_3_delay.close();
		}
	} else
	{
		std::cout << "Error writing output file for _dynamic_array_synapses_3_delay." << endl;
	}
	ofstream outfile__dynamic_array_synapses_3_lastupdate;
	outfile__dynamic_array_synapses_3_lastupdate.open("results\\_dynamic_array_synapses_3_lastupdate_8007704870257513987", ios::binary | ios::out);
	if(outfile__dynamic_array_synapses_3_lastupdate.is_open())
	{
        if (! _dynamic_array_synapses_3_lastupdate.empty() )
        {
			outfile__dynamic_array_synapses_3_lastupdate.write(reinterpret_cast<char*>(&_dynamic_array_synapses_3_lastupdate[0]), _dynamic_array_synapses_3_lastupdate.size()*sizeof(_dynamic_array_synapses_3_lastupdate[0]));
		    outfile__dynamic_array_synapses_3_lastupdate.close();
		}
	} else
	{
		std::cout << "Error writing output file for _dynamic_array_synapses_3_lastupdate." << endl;
	}
	ofstream outfile__dynamic_array_synapses_3_N_incoming;
	outfile__dynamic_array_synapses_3_N_incoming.open("results\\_dynamic_array_synapses_3_N_incoming_5659509645839609901", ios::binary | ios::out);
	if(outfile__dynamic_array_synapses_3_N_incoming.is_open())
	{
        if (! _dynamic_array_synapses_3_N_incoming.empty() )
        {
			outfile__dynamic_array_synapses_3_N_incoming.write(reinterpret_cast<char*>(&_dynamic_array_synapses_3_N_incoming[0]), _dynamic_array_synapses_3_N_incoming.size()*sizeof(_dynamic_array_synapses_3_N_incoming[0]));
		    outfile__dynamic_array_synapses_3_N_incoming.close();
		}
	} else
	{
		std::cout << "Error writing output file for _dynamic_array_synapses_3_N_incoming." << endl;
	}
	ofstream outfile__dynamic_array_synapses_3_N_outgoing;
	outfile__dynamic_array_synapses_3_N_outgoing.open("results\\_dynamic_array_synapses_3_N_outgoing_-8860710565355080903", ios::binary | ios::out);
	if(outfile__dynamic_array_synapses_3_N_outgoing.is_open())
	{
        if (! _dynamic_array_synapses_3_N_outgoing.empty() )
        {
			outfile__dynamic_array_synapses_3_N_outgoing.write(reinterpret_cast<char*>(&_dynamic_array_synapses_3_N_outgoing[0]), _dynamic_array_synapses_3_N_outgoing.size()*sizeof(_dynamic_array_synapses_3_N_outgoing[0]));
		    outfile__dynamic_array_synapses_3_N_outgoing.close();
		}
	} else
	{
		std::cout << "Error writing output file for _dynamic_array_synapses_3_N_outgoing." << endl;
	}
	ofstream outfile__dynamic_array_synapses_3_R;
	outfile__dynamic_array_synapses_3_R.open("results\\_dynamic_array_synapses_3_R_5627764015442035411", ios::binary | ios::out);
	if(outfile__dynamic_array_synapses_3_R.is_open())
	{
        if (! _dynamic_array_synapses_3_R.empty() )
        {
			outfile__dynamic_array_synapses_3_R.write(reinterpret_cast<char*>(&_dynamic_array_synapses_3_R[0]), _dynamic_array_synapses_3_R.size()*sizeof(_dynamic_array_synapses_3_R[0]));
		    outfile__dynamic_array_synapses_3_R.close();
		}
	} else
	{
		std::cout << "Error writing output file for _dynamic_array_synapses_3_R." << endl;
	}
	ofstream outfile__dynamic_array_synapses_3_wght;
	outfile__dynamic_array_synapses_3_wght.open("results\\_dynamic_array_synapses_3_wght_-7251802942134289934", ios::binary | ios::out);
	if(outfile__dynamic_array_synapses_3_wght.is_open())
	{
        if (! _dynamic_array_synapses_3_wght.empty() )
        {
			outfile__dynamic_array_synapses_3_wght.write(reinterpret_cast<char*>(&_dynamic_array_synapses_3_wght[0]), _dynamic_array_synapses_3_wght.size()*sizeof(_dynamic_array_synapses_3_wght[0]));
		    outfile__dynamic_array_synapses_3_wght.close();
		}
	} else
	{
		std::cout << "Error writing output file for _dynamic_array_synapses_3_wght." << endl;
	}
	ofstream outfile__dynamic_array_synapses_4__synaptic_post;
	outfile__dynamic_array_synapses_4__synaptic_post.open("results\\_dynamic_array_synapses_4__synaptic_post_6291845469352317596", ios::binary | ios::out);
	if(outfile__dynamic_array_synapses_4__synaptic_post.is_open())
	{
        if (! _dynamic_array_synapses_4__synaptic_post.empty() )
        {
			outfile__dynamic_array_synapses_4__synaptic_post.write(reinterpret_cast<char*>(&_dynamic_array_synapses_4__synaptic_post[0]), _dynamic_array_synapses_4__synaptic_post.size()*sizeof(_dynamic_array_synapses_4__synaptic_post[0]));
		    outfile__dynamic_array_synapses_4__synaptic_post.close();
		}
	} else
	{
		std::cout << "Error writing output file for _dynamic_array_synapses_4__synaptic_post." << endl;
	}
	ofstream outfile__dynamic_array_synapses_4__synaptic_pre;
	outfile__dynamic_array_synapses_4__synaptic_pre.open("results\\_dynamic_array_synapses_4__synaptic_pre_-8370485863281648202", ios::binary | ios::out);
	if(outfile__dynamic_array_synapses_4__synaptic_pre.is_open())
	{
        if (! _dynamic_array_synapses_4__synaptic_pre.empty() )
        {
			outfile__dynamic_array_synapses_4__synaptic_pre.write(reinterpret_cast<char*>(&_dynamic_array_synapses_4__synaptic_pre[0]), _dynamic_array_synapses_4__synaptic_pre.size()*sizeof(_dynamic_array_synapses_4__synaptic_pre[0]));
		    outfile__dynamic_array_synapses_4__synaptic_pre.close();
		}
	} else
	{
		std::cout << "Error writing output file for _dynamic_array_synapses_4__synaptic_pre." << endl;
	}
	ofstream outfile__dynamic_array_synapses_4_delay;
	outfile__dynamic_array_synapses_4_delay.open("results\\_dynamic_array_synapses_4_delay_5012490760453085249", ios::binary | ios::out);
	if(outfile__dynamic_array_synapses_4_delay.is_open())
	{
        if (! _dynamic_array_synapses_4_delay.empty() )
        {
			outfile__dynamic_array_synapses_4_delay.write(reinterpret_cast<char*>(&_dynamic_array_synapses_4_delay[0]), _dynamic_array_synapses_4_delay.size()*sizeof(_dynamic_array_synapses_4_delay[0]));
		    outfile__dynamic_array_synapses_4_delay.close();
		}
	} else
	{
		std::cout << "Error writing output file for _dynamic_array_synapses_4_delay." << endl;
	}
	ofstream outfile__dynamic_array_synapses_4_lastupdate;
	outfile__dynamic_array_synapses_4_lastupdate.open("results\\_dynamic_array_synapses_4_lastupdate_-1555678062695447690", ios::binary | ios::out);
	if(outfile__dynamic_array_synapses_4_lastupdate.is_open())
	{
        if (! _dynamic_array_synapses_4_lastupdate.empty() )
        {
			outfile__dynamic_array_synapses_4_lastupdate.write(reinterpret_cast<char*>(&_dynamic_array_synapses_4_lastupdate[0]), _dynamic_array_synapses_4_lastupdate.size()*sizeof(_dynamic_array_synapses_4_lastupdate[0]));
		    outfile__dynamic_array_synapses_4_lastupdate.close();
		}
	} else
	{
		std::cout << "Error writing output file for _dynamic_array_synapses_4_lastupdate." << endl;
	}
	ofstream outfile__dynamic_array_synapses_4_N_incoming;
	outfile__dynamic_array_synapses_4_N_incoming.open("results\\_dynamic_array_synapses_4_N_incoming_-8961007114318297916", ios::binary | ios::out);
	if(outfile__dynamic_array_synapses_4_N_incoming.is_open())
	{
        if (! _dynamic_array_synapses_4_N_incoming.empty() )
        {
			outfile__dynamic_array_synapses_4_N_incoming.write(reinterpret_cast<char*>(&_dynamic_array_synapses_4_N_incoming[0]), _dynamic_array_synapses_4_N_incoming.size()*sizeof(_dynamic_array_synapses_4_N_incoming[0]));
		    outfile__dynamic_array_synapses_4_N_incoming.close();
		}
	} else
	{
		std::cout << "Error writing output file for _dynamic_array_synapses_4_N_incoming." << endl;
	}
	ofstream outfile__dynamic_array_synapses_4_N_outgoing;
	outfile__dynamic_array_synapses_4_N_outgoing.open("results\\_dynamic_array_synapses_4_N_outgoing_820888196233136333", ios::binary | ios::out);
	if(outfile__dynamic_array_synapses_4_N_outgoing.is_open())
	{
        if (! _dynamic_array_synapses_4_N_outgoing.empty() )
        {
			outfile__dynamic_array_synapses_4_N_outgoing.write(reinterpret_cast<char*>(&_dynamic_array_synapses_4_N_outgoing[0]), _dynamic_array_synapses_4_N_outgoing.size()*sizeof(_dynamic_array_synapses_4_N_outgoing[0]));
		    outfile__dynamic_array_synapses_4_N_outgoing.close();
		}
	} else
	{
		std::cout << "Error writing output file for _dynamic_array_synapses_4_N_outgoing." << endl;
	}
	ofstream outfile__dynamic_array_synapses_4_R;
	outfile__dynamic_array_synapses_4_R.open("results\\_dynamic_array_synapses_4_R_9046411436822126879", ios::binary | ios::out);
	if(outfile__dynamic_array_synapses_4_R.is_open())
	{
        if (! _dynamic_array_synapses_4_R.empty() )
        {
			outfile__dynamic_array_synapses_4_R.write(reinterpret_cast<char*>(&_dynamic_array_synapses_4_R[0]), _dynamic_array_synapses_4_R.size()*sizeof(_dynamic_array_synapses_4_R[0]));
		    outfile__dynamic_array_synapses_4_R.close();
		}
	} else
	{
		std::cout << "Error writing output file for _dynamic_array_synapses_4_R." << endl;
	}
	ofstream outfile__dynamic_array_synapses_4_wght;
	outfile__dynamic_array_synapses_4_wght.open("results\\_dynamic_array_synapses_4_wght_4762348733285266801", ios::binary | ios::out);
	if(outfile__dynamic_array_synapses_4_wght.is_open())
	{
        if (! _dynamic_array_synapses_4_wght.empty() )
        {
			outfile__dynamic_array_synapses_4_wght.write(reinterpret_cast<char*>(&_dynamic_array_synapses_4_wght[0]), _dynamic_array_synapses_4_wght.size()*sizeof(_dynamic_array_synapses_4_wght[0]));
		    outfile__dynamic_array_synapses_4_wght.close();
		}
	} else
	{
		std::cout << "Error writing output file for _dynamic_array_synapses_4_wght." << endl;
	}
	ofstream outfile__dynamic_array_synapses_5__synaptic_post;
	outfile__dynamic_array_synapses_5__synaptic_post.open("results\\_dynamic_array_synapses_5__synaptic_post_7105180021343123026", ios::binary | ios::out);
	if(outfile__dynamic_array_synapses_5__synaptic_post.is_open())
	{
        if (! _dynamic_array_synapses_5__synaptic_post.empty() )
        {
			outfile__dynamic_array_synapses_5__synaptic_post.write(reinterpret_cast<char*>(&_dynamic_array_synapses_5__synaptic_post[0]), _dynamic_array_synapses_5__synaptic_post.size()*sizeof(_dynamic_array_synapses_5__synaptic_post[0]));
		    outfile__dynamic_array_synapses_5__synaptic_post.close();
		}
	} else
	{
		std::cout << "Error writing output file for _dynamic_array_synapses_5__synaptic_post." << endl;
	}
	ofstream outfile__dynamic_array_synapses_5__synaptic_pre;
	outfile__dynamic_array_synapses_5__synaptic_pre.open("results\\_dynamic_array_synapses_5__synaptic_pre_-7667837423575168633", ios::binary | ios::out);
	if(outfile__dynamic_array_synapses_5__synaptic_pre.is_open())
	{
        if (! _dynamic_array_synapses_5__synaptic_pre.empty() )
        {
			outfile__dynamic_array_synapses_5__synaptic_pre.write(reinterpret_cast<char*>(&_dynamic_array_synapses_5__synaptic_pre[0]), _dynamic_array_synapses_5__synaptic_pre.size()*sizeof(_dynamic_array_synapses_5__synaptic_pre[0]));
		    outfile__dynamic_array_synapses_5__synaptic_pre.close();
		}
	} else
	{
		std::cout << "Error writing output file for _dynamic_array_synapses_5__synaptic_pre." << endl;
	}
	ofstream outfile__dynamic_array_synapses_5_delay;
	outfile__dynamic_array_synapses_5_delay.open("results\\_dynamic_array_synapses_5_delay_-6806923730392320829", ios::binary | ios::out);
	if(outfile__dynamic_array_synapses_5_delay.is_open())
	{
        if (! _dynamic_array_synapses_5_delay.empty() )
        {
			outfile__dynamic_array_synapses_5_delay.write(reinterpret_cast<char*>(&_dynamic_array_synapses_5_delay[0]), _dynamic_array_synapses_5_delay.size()*sizeof(_dynamic_array_synapses_5_delay[0]));
		    outfile__dynamic_array_synapses_5_delay.close();
		}
	} else
	{
		std::cout << "Error writing output file for _dynamic_array_synapses_5_delay." << endl;
	}
	ofstream outfile__dynamic_array_synapses_5_lastupdate;
	outfile__dynamic_array_synapses_5_lastupdate.open("results\\_dynamic_array_synapses_5_lastupdate_2105032228763926897", ios::binary | ios::out);
	if(outfile__dynamic_array_synapses_5_lastupdate.is_open())
	{
        if (! _dynamic_array_synapses_5_lastupdate.empty() )
        {
			outfile__dynamic_array_synapses_5_lastupdate.write(reinterpret_cast<char*>(&_dynamic_array_synapses_5_lastupdate[0]), _dynamic_array_synapses_5_lastupdate.size()*sizeof(_dynamic_array_synapses_5_lastupdate[0]));
		    outfile__dynamic_array_synapses_5_lastupdate.close();
		}
	} else
	{
		std::cout << "Error writing output file for _dynamic_array_synapses_5_lastupdate." << endl;
	}
	ofstream outfile__dynamic_array_synapses_5_N_incoming;
	outfile__dynamic_array_synapses_5_N_incoming.open("results\\_dynamic_array_synapses_5_N_incoming_-376979778177868820", ios::binary | ios::out);
	if(outfile__dynamic_array_synapses_5_N_incoming.is_open())
	{
        if (! _dynamic_array_synapses_5_N_incoming.empty() )
        {
			outfile__dynamic_array_synapses_5_N_incoming.write(reinterpret_cast<char*>(&_dynamic_array_synapses_5_N_incoming[0]), _dynamic_array_synapses_5_N_incoming.size()*sizeof(_dynamic_array_synapses_5_N_incoming[0]));
		    outfile__dynamic_array_synapses_5_N_incoming.close();
		}
	} else
	{
		std::cout << "Error writing output file for _dynamic_array_synapses_5_N_incoming." << endl;
	}
	ofstream outfile__dynamic_array_synapses_5_N_outgoing;
	outfile__dynamic_array_synapses_5_N_outgoing.open("results\\_dynamic_array_synapses_5_N_outgoing_-6058796157348490703", ios::binary | ios::out);
	if(outfile__dynamic_array_synapses_5_N_outgoing.is_open())
	{
        if (! _dynamic_array_synapses_5_N_outgoing.empty() )
        {
			outfile__dynamic_array_synapses_5_N_outgoing.write(reinterpret_cast<char*>(&_dynamic_array_synapses_5_N_outgoing[0]), _dynamic_array_synapses_5_N_outgoing.size()*sizeof(_dynamic_array_synapses_5_N_outgoing[0]));
		    outfile__dynamic_array_synapses_5_N_outgoing.close();
		}
	} else
	{
		std::cout << "Error writing output file for _dynamic_array_synapses_5_N_outgoing." << endl;
	}
	ofstream outfile__dynamic_array_synapses_5_R;
	outfile__dynamic_array_synapses_5_R.open("results\\_dynamic_array_synapses_5_R_8936343628024490712", ios::binary | ios::out);
	if(outfile__dynamic_array_synapses_5_R.is_open())
	{
        if (! _dynamic_array_synapses_5_R.empty() )
        {
			outfile__dynamic_array_synapses_5_R.write(reinterpret_cast<char*>(&_dynamic_array_synapses_5_R[0]), _dynamic_array_synapses_5_R.size()*sizeof(_dynamic_array_synapses_5_R[0]));
		    outfile__dynamic_array_synapses_5_R.close();
		}
	} else
	{
		std::cout << "Error writing output file for _dynamic_array_synapses_5_R." << endl;
	}
	ofstream outfile__dynamic_array_synapses_5_wght;
	outfile__dynamic_array_synapses_5_wght.open("results\\_dynamic_array_synapses_5_wght_-7692356664922115542", ios::binary | ios::out);
	if(outfile__dynamic_array_synapses_5_wght.is_open())
	{
        if (! _dynamic_array_synapses_5_wght.empty() )
        {
			outfile__dynamic_array_synapses_5_wght.write(reinterpret_cast<char*>(&_dynamic_array_synapses_5_wght[0]), _dynamic_array_synapses_5_wght.size()*sizeof(_dynamic_array_synapses_5_wght[0]));
		    outfile__dynamic_array_synapses_5_wght.close();
		}
	} else
	{
		std::cout << "Error writing output file for _dynamic_array_synapses_5_wght." << endl;
	}
	ofstream outfile__dynamic_array_synapses_6__synaptic_post;
	outfile__dynamic_array_synapses_6__synaptic_post.open("results\\_dynamic_array_synapses_6__synaptic_post_-8828046771515519868", ios::binary | ios::out);
	if(outfile__dynamic_array_synapses_6__synaptic_post.is_open())
	{
        if (! _dynamic_array_synapses_6__synaptic_post.empty() )
        {
			outfile__dynamic_array_synapses_6__synaptic_post.write(reinterpret_cast<char*>(&_dynamic_array_synapses_6__synaptic_post[0]), _dynamic_array_synapses_6__synaptic_post.size()*sizeof(_dynamic_array_synapses_6__synaptic_post[0]));
		    outfile__dynamic_array_synapses_6__synaptic_post.close();
		}
	} else
	{
		std::cout << "Error writing output file for _dynamic_array_synapses_6__synaptic_post." << endl;
	}
	ofstream outfile__dynamic_array_synapses_6__synaptic_pre;
	outfile__dynamic_array_synapses_6__synaptic_pre.open("results\\_dynamic_array_synapses_6__synaptic_pre_-1878323221830201051", ios::binary | ios::out);
	if(outfile__dynamic_array_synapses_6__synaptic_pre.is_open())
	{
        if (! _dynamic_array_synapses_6__synaptic_pre.empty() )
        {
			outfile__dynamic_array_synapses_6__synaptic_pre.write(reinterpret_cast<char*>(&_dynamic_array_synapses_6__synaptic_pre[0]), _dynamic_array_synapses_6__synaptic_pre.size()*sizeof(_dynamic_array_synapses_6__synaptic_pre[0]));
		    outfile__dynamic_array_synapses_6__synaptic_pre.close();
		}
	} else
	{
		std::cout << "Error writing output file for _dynamic_array_synapses_6__synaptic_pre." << endl;
	}
	ofstream outfile__dynamic_array_synapses_6_delay;
	outfile__dynamic_array_synapses_6_delay.open("results\\_dynamic_array_synapses_6_delay_6903763495160126201", ios::binary | ios::out);
	if(outfile__dynamic_array_synapses_6_delay.is_open())
	{
        if (! _dynamic_array_synapses_6_delay.empty() )
        {
			outfile__dynamic_array_synapses_6_delay.write(reinterpret_cast<char*>(&_dynamic_array_synapses_6_delay[0]), _dynamic_array_synapses_6_delay.size()*sizeof(_dynamic_array_synapses_6_delay[0]));
		    outfile__dynamic_array_synapses_6_delay.close();
		}
	} else
	{
		std::cout << "Error writing output file for _dynamic_array_synapses_6_delay." << endl;
	}
	ofstream outfile__dynamic_array_synapses_6_lastupdate;
	outfile__dynamic_array_synapses_6_lastupdate.open("results\\_dynamic_array_synapses_6_lastupdate_-8042230469687190204", ios::binary | ios::out);
	if(outfile__dynamic_array_synapses_6_lastupdate.is_open())
	{
        if (! _dynamic_array_synapses_6_lastupdate.empty() )
        {
			outfile__dynamic_array_synapses_6_lastupdate.write(reinterpret_cast<char*>(&_dynamic_array_synapses_6_lastupdate[0]), _dynamic_array_synapses_6_lastupdate.size()*sizeof(_dynamic_array_synapses_6_lastupdate[0]));
		    outfile__dynamic_array_synapses_6_lastupdate.close();
		}
	} else
	{
		std::cout << "Error writing output file for _dynamic_array_synapses_6_lastupdate." << endl;
	}
	ofstream outfile__dynamic_array_synapses_6_N_incoming;
	outfile__dynamic_array_synapses_6_N_incoming.open("results\\_dynamic_array_synapses_6_N_incoming_-1007656985274105250", ios::binary | ios::out);
	if(outfile__dynamic_array_synapses_6_N_incoming.is_open())
	{
        if (! _dynamic_array_synapses_6_N_incoming.empty() )
        {
			outfile__dynamic_array_synapses_6_N_incoming.write(reinterpret_cast<char*>(&_dynamic_array_synapses_6_N_incoming[0]), _dynamic_array_synapses_6_N_incoming.size()*sizeof(_dynamic_array_synapses_6_N_incoming[0]));
		    outfile__dynamic_array_synapses_6_N_incoming.close();
		}
	} else
	{
		std::cout << "Error writing output file for _dynamic_array_synapses_6_N_incoming." << endl;
	}
	ofstream outfile__dynamic_array_synapses_6_N_outgoing;
	outfile__dynamic_array_synapses_6_N_outgoing.open("results\\_dynamic_array_synapses_6_N_outgoing_2184285357932284871", ios::binary | ios::out);
	if(outfile__dynamic_array_synapses_6_N_outgoing.is_open())
	{
        if (! _dynamic_array_synapses_6_N_outgoing.empty() )
        {
			outfile__dynamic_array_synapses_6_N_outgoing.write(reinterpret_cast<char*>(&_dynamic_array_synapses_6_N_outgoing[0]), _dynamic_array_synapses_6_N_outgoing.size()*sizeof(_dynamic_array_synapses_6_N_outgoing[0]));
		    outfile__dynamic_array_synapses_6_N_outgoing.close();
		}
	} else
	{
		std::cout << "Error writing output file for _dynamic_array_synapses_6_N_outgoing." << endl;
	}
	ofstream outfile__dynamic_array_synapses_6_R;
	outfile__dynamic_array_synapses_6_R.open("results\\_dynamic_array_synapses_6_R_-5941457494161460429", ios::binary | ios::out);
	if(outfile__dynamic_array_synapses_6_R.is_open())
	{
        if (! _dynamic_array_synapses_6_R.empty() )
        {
			outfile__dynamic_array_synapses_6_R.write(reinterpret_cast<char*>(&_dynamic_array_synapses_6_R[0]), _dynamic_array_synapses_6_R.size()*sizeof(_dynamic_array_synapses_6_R[0]));
		    outfile__dynamic_array_synapses_6_R.close();
		}
	} else
	{
		std::cout << "Error writing output file for _dynamic_array_synapses_6_R." << endl;
	}
	ofstream outfile__dynamic_array_synapses_6_wght;
	outfile__dynamic_array_synapses_6_wght.open("results\\_dynamic_array_synapses_6_wght_-8642806566958461329", ios::binary | ios::out);
	if(outfile__dynamic_array_synapses_6_wght.is_open())
	{
        if (! _dynamic_array_synapses_6_wght.empty() )
        {
			outfile__dynamic_array_synapses_6_wght.write(reinterpret_cast<char*>(&_dynamic_array_synapses_6_wght[0]), _dynamic_array_synapses_6_wght.size()*sizeof(_dynamic_array_synapses_6_wght[0]));
		    outfile__dynamic_array_synapses_6_wght.close();
		}
	} else
	{
		std::cout << "Error writing output file for _dynamic_array_synapses_6_wght." << endl;
	}
	ofstream outfile__dynamic_array_synapses_7__synaptic_post;
	outfile__dynamic_array_synapses_7__synaptic_post.open("results\\_dynamic_array_synapses_7__synaptic_post_3793648736495667734", ios::binary | ios::out);
	if(outfile__dynamic_array_synapses_7__synaptic_post.is_open())
	{
        if (! _dynamic_array_synapses_7__synaptic_post.empty() )
        {
			outfile__dynamic_array_synapses_7__synaptic_post.write(reinterpret_cast<char*>(&_dynamic_array_synapses_7__synaptic_post[0]), _dynamic_array_synapses_7__synaptic_post.size()*sizeof(_dynamic_array_synapses_7__synaptic_post[0]));
		    outfile__dynamic_array_synapses_7__synaptic_post.close();
		}
	} else
	{
		std::cout << "Error writing output file for _dynamic_array_synapses_7__synaptic_post." << endl;
	}
	ofstream outfile__dynamic_array_synapses_7__synaptic_pre;
	outfile__dynamic_array_synapses_7__synaptic_pre.open("results\\_dynamic_array_synapses_7__synaptic_pre_9043450373294522870", ios::binary | ios::out);
	if(outfile__dynamic_array_synapses_7__synaptic_pre.is_open())
	{
        if (! _dynamic_array_synapses_7__synaptic_pre.empty() )
        {
			outfile__dynamic_array_synapses_7__synaptic_pre.write(reinterpret_cast<char*>(&_dynamic_array_synapses_7__synaptic_pre[0]), _dynamic_array_synapses_7__synaptic_pre.size()*sizeof(_dynamic_array_synapses_7__synaptic_pre[0]));
		    outfile__dynamic_array_synapses_7__synaptic_pre.close();
		}
	} else
	{
		std::cout << "Error writing output file for _dynamic_array_synapses_7__synaptic_pre." << endl;
	}
	ofstream outfile__dynamic_array_synapses_7_delay;
	outfile__dynamic_array_synapses_7_delay.open("results\\_dynamic_array_synapses_7_delay_1860435128544759980", ios::binary | ios::out);
	if(outfile__dynamic_array_synapses_7_delay.is_open())
	{
        if (! _dynamic_array_synapses_7_delay.empty() )
        {
			outfile__dynamic_array_synapses_7_delay.write(reinterpret_cast<char*>(&_dynamic_array_synapses_7_delay[0]), _dynamic_array_synapses_7_delay.size()*sizeof(_dynamic_array_synapses_7_delay[0]));
		    outfile__dynamic_array_synapses_7_delay.close();
		}
	} else
	{
		std::cout << "Error writing output file for _dynamic_array_synapses_7_delay." << endl;
	}
	ofstream outfile__dynamic_array_synapses_7_lastupdate;
	outfile__dynamic_array_synapses_7_lastupdate.open("results\\_dynamic_array_synapses_7_lastupdate_3819530111537870317", ios::binary | ios::out);
	if(outfile__dynamic_array_synapses_7_lastupdate.is_open())
	{
        if (! _dynamic_array_synapses_7_lastupdate.empty() )
        {
			outfile__dynamic_array_synapses_7_lastupdate.write(reinterpret_cast<char*>(&_dynamic_array_synapses_7_lastupdate[0]), _dynamic_array_synapses_7_lastupdate.size()*sizeof(_dynamic_array_synapses_7_lastupdate[0]));
		    outfile__dynamic_array_synapses_7_lastupdate.close();
		}
	} else
	{
		std::cout << "Error writing output file for _dynamic_array_synapses_7_lastupdate." << endl;
	}
	ofstream outfile__dynamic_array_synapses_7_N_incoming;
	outfile__dynamic_array_synapses_7_N_incoming.open("results\\_dynamic_array_synapses_7_N_incoming_-4272173237895068688", ios::binary | ios::out);
	if(outfile__dynamic_array_synapses_7_N_incoming.is_open())
	{
        if (! _dynamic_array_synapses_7_N_incoming.empty() )
        {
			outfile__dynamic_array_synapses_7_N_incoming.write(reinterpret_cast<char*>(&_dynamic_array_synapses_7_N_incoming[0]), _dynamic_array_synapses_7_N_incoming.size()*sizeof(_dynamic_array_synapses_7_N_incoming[0]));
		    outfile__dynamic_array_synapses_7_N_incoming.close();
		}
	} else
	{
		std::cout << "Error writing output file for _dynamic_array_synapses_7_N_incoming." << endl;
	}
	ofstream outfile__dynamic_array_synapses_7_N_outgoing;
	outfile__dynamic_array_synapses_7_N_outgoing.open("results\\_dynamic_array_synapses_7_N_outgoing_-9166221343852518570", ios::binary | ios::out);
	if(outfile__dynamic_array_synapses_7_N_outgoing.is_open())
	{
        if (! _dynamic_array_synapses_7_N_outgoing.empty() )
        {
			outfile__dynamic_array_synapses_7_N_outgoing.write(reinterpret_cast<char*>(&_dynamic_array_synapses_7_N_outgoing[0]), _dynamic_array_synapses_7_N_outgoing.size()*sizeof(_dynamic_array_synapses_7_N_outgoing[0]));
		    outfile__dynamic_array_synapses_7_N_outgoing.close();
		}
	} else
	{
		std::cout << "Error writing output file for _dynamic_array_synapses_7_N_outgoing." << endl;
	}
	ofstream outfile__dynamic_array_synapses_7_R;
	outfile__dynamic_array_synapses_7_R.open("results\\_dynamic_array_synapses_7_R_3908110134774216785", ios::binary | ios::out);
	if(outfile__dynamic_array_synapses_7_R.is_open())
	{
        if (! _dynamic_array_synapses_7_R.empty() )
        {
			outfile__dynamic_array_synapses_7_R.write(reinterpret_cast<char*>(&_dynamic_array_synapses_7_R[0]), _dynamic_array_synapses_7_R.size()*sizeof(_dynamic_array_synapses_7_R[0]));
		    outfile__dynamic_array_synapses_7_R.close();
		}
	} else
	{
		std::cout << "Error writing output file for _dynamic_array_synapses_7_R." << endl;
	}
	ofstream outfile__dynamic_array_synapses_7_wght;
	outfile__dynamic_array_synapses_7_wght.open("results\\_dynamic_array_synapses_7_wght_4179179846765495109", ios::binary | ios::out);
	if(outfile__dynamic_array_synapses_7_wght.is_open())
	{
        if (! _dynamic_array_synapses_7_wght.empty() )
        {
			outfile__dynamic_array_synapses_7_wght.write(reinterpret_cast<char*>(&_dynamic_array_synapses_7_wght[0]), _dynamic_array_synapses_7_wght.size()*sizeof(_dynamic_array_synapses_7_wght[0]));
		    outfile__dynamic_array_synapses_7_wght.close();
		}
	} else
	{
		std::cout << "Error writing output file for _dynamic_array_synapses_7_wght." << endl;
	}
	ofstream outfile__dynamic_array_synapses_8__synaptic_post;
	outfile__dynamic_array_synapses_8__synaptic_post.open("results\\_dynamic_array_synapses_8__synaptic_post_5644101835761275293", ios::binary | ios::out);
	if(outfile__dynamic_array_synapses_8__synaptic_post.is_open())
	{
        if (! _dynamic_array_synapses_8__synaptic_post.empty() )
        {
			outfile__dynamic_array_synapses_8__synaptic_post.write(reinterpret_cast<char*>(&_dynamic_array_synapses_8__synaptic_post[0]), _dynamic_array_synapses_8__synaptic_post.size()*sizeof(_dynamic_array_synapses_8__synaptic_post[0]));
		    outfile__dynamic_array_synapses_8__synaptic_post.close();
		}
	} else
	{
		std::cout << "Error writing output file for _dynamic_array_synapses_8__synaptic_post." << endl;
	}
	ofstream outfile__dynamic_array_synapses_8__synaptic_pre;
	outfile__dynamic_array_synapses_8__synaptic_pre.open("results\\_dynamic_array_synapses_8__synaptic_pre_7822807556416212042", ios::binary | ios::out);
	if(outfile__dynamic_array_synapses_8__synaptic_pre.is_open())
	{
        if (! _dynamic_array_synapses_8__synaptic_pre.empty() )
        {
			outfile__dynamic_array_synapses_8__synaptic_pre.write(reinterpret_cast<char*>(&_dynamic_array_synapses_8__synaptic_pre[0]), _dynamic_array_synapses_8__synaptic_pre.size()*sizeof(_dynamic_array_synapses_8__synaptic_pre[0]));
		    outfile__dynamic_array_synapses_8__synaptic_pre.close();
		}
	} else
	{
		std::cout << "Error writing output file for _dynamic_array_synapses_8__synaptic_pre." << endl;
	}
	ofstream outfile__dynamic_array_synapses_8_delay;
	outfile__dynamic_array_synapses_8_delay.open("results\\_dynamic_array_synapses_8_delay_-2346182455350253204", ios::binary | ios::out);
	if(outfile__dynamic_array_synapses_8_delay.is_open())
	{
        if (! _dynamic_array_synapses_8_delay.empty() )
        {
			outfile__dynamic_array_synapses_8_delay.write(reinterpret_cast<char*>(&_dynamic_array_synapses_8_delay[0]), _dynamic_array_synapses_8_delay.size()*sizeof(_dynamic_array_synapses_8_delay[0]));
		    outfile__dynamic_array_synapses_8_delay.close();
		}
	} else
	{
		std::cout << "Error writing output file for _dynamic_array_synapses_8_delay." << endl;
	}
	ofstream outfile__dynamic_array_synapses_8_lastupdate;
	outfile__dynamic_array_synapses_8_lastupdate.open("results\\_dynamic_array_synapses_8_lastupdate_-6024841201519696886", ios::binary | ios::out);
	if(outfile__dynamic_array_synapses_8_lastupdate.is_open())
	{
        if (! _dynamic_array_synapses_8_lastupdate.empty() )
        {
			outfile__dynamic_array_synapses_8_lastupdate.write(reinterpret_cast<char*>(&_dynamic_array_synapses_8_lastupdate[0]), _dynamic_array_synapses_8_lastupdate.size()*sizeof(_dynamic_array_synapses_8_lastupdate[0]));
		    outfile__dynamic_array_synapses_8_lastupdate.close();
		}
	} else
	{
		std::cout << "Error writing output file for _dynamic_array_synapses_8_lastupdate." << endl;
	}
	ofstream outfile__dynamic_array_synapses_8_N_incoming;
	outfile__dynamic_array_synapses_8_N_incoming.open("results\\_dynamic_array_synapses_8_N_incoming_-2360775045222179477", ios::binary | ios::out);
	if(outfile__dynamic_array_synapses_8_N_incoming.is_open())
	{
        if (! _dynamic_array_synapses_8_N_incoming.empty() )
        {
			outfile__dynamic_array_synapses_8_N_incoming.write(reinterpret_cast<char*>(&_dynamic_array_synapses_8_N_incoming[0]), _dynamic_array_synapses_8_N_incoming.size()*sizeof(_dynamic_array_synapses_8_N_incoming[0]));
		    outfile__dynamic_array_synapses_8_N_incoming.close();
		}
	} else
	{
		std::cout << "Error writing output file for _dynamic_array_synapses_8_N_incoming." << endl;
	}
	ofstream outfile__dynamic_array_synapses_8_N_outgoing;
	outfile__dynamic_array_synapses_8_N_outgoing.open("results\\_dynamic_array_synapses_8_N_outgoing_-8133134852357540960", ios::binary | ios::out);
	if(outfile__dynamic_array_synapses_8_N_outgoing.is_open())
	{
        if (! _dynamic_array_synapses_8_N_outgoing.empty() )
        {
			outfile__dynamic_array_synapses_8_N_outgoing.write(reinterpret_cast<char*>(&_dynamic_array_synapses_8_N_outgoing[0]), _dynamic_array_synapses_8_N_outgoing.size()*sizeof(_dynamic_array_synapses_8_N_outgoing[0]));
		    outfile__dynamic_array_synapses_8_N_outgoing.close();
		}
	} else
	{
		std::cout << "Error writing output file for _dynamic_array_synapses_8_N_outgoing." << endl;
	}
	ofstream outfile__dynamic_array_synapses_8_R;
	outfile__dynamic_array_synapses_8_R.open("results\\_dynamic_array_synapses_8_R_5620245805137889761", ios::binary | ios::out);
	if(outfile__dynamic_array_synapses_8_R.is_open())
	{
        if (! _dynamic_array_synapses_8_R.empty() )
        {
			outfile__dynamic_array_synapses_8_R.write(reinterpret_cast<char*>(&_dynamic_array_synapses_8_R[0]), _dynamic_array_synapses_8_R.size()*sizeof(_dynamic_array_synapses_8_R[0]));
		    outfile__dynamic_array_synapses_8_R.close();
		}
	} else
	{
		std::cout << "Error writing output file for _dynamic_array_synapses_8_R." << endl;
	}
	ofstream outfile__dynamic_array_synapses_8_wght;
	outfile__dynamic_array_synapses_8_wght.open("results\\_dynamic_array_synapses_8_wght_4432541842523263278", ios::binary | ios::out);
	if(outfile__dynamic_array_synapses_8_wght.is_open())
	{
        if (! _dynamic_array_synapses_8_wght.empty() )
        {
			outfile__dynamic_array_synapses_8_wght.write(reinterpret_cast<char*>(&_dynamic_array_synapses_8_wght[0]), _dynamic_array_synapses_8_wght.size()*sizeof(_dynamic_array_synapses_8_wght[0]));
		    outfile__dynamic_array_synapses_8_wght.close();
		}
	} else
	{
		std::cout << "Error writing output file for _dynamic_array_synapses_8_wght." << endl;
	}
	ofstream outfile__dynamic_array_synapses_9__synaptic_post;
	outfile__dynamic_array_synapses_9__synaptic_post.open("results\\_dynamic_array_synapses_9__synaptic_post_7566120877425309824", ios::binary | ios::out);
	if(outfile__dynamic_array_synapses_9__synaptic_post.is_open())
	{
        if (! _dynamic_array_synapses_9__synaptic_post.empty() )
        {
			outfile__dynamic_array_synapses_9__synaptic_post.write(reinterpret_cast<char*>(&_dynamic_array_synapses_9__synaptic_post[0]), _dynamic_array_synapses_9__synaptic_post.size()*sizeof(_dynamic_array_synapses_9__synaptic_post[0]));
		    outfile__dynamic_array_synapses_9__synaptic_post.close();
		}
	} else
	{
		std::cout << "Error writing output file for _dynamic_array_synapses_9__synaptic_post." << endl;
	}
	ofstream outfile__dynamic_array_synapses_9__synaptic_pre;
	outfile__dynamic_array_synapses_9__synaptic_pre.open("results\\_dynamic_array_synapses_9__synaptic_pre_-6239594450507728939", ios::binary | ios::out);
	if(outfile__dynamic_array_synapses_9__synaptic_pre.is_open())
	{
        if (! _dynamic_array_synapses_9__synaptic_pre.empty() )
        {
			outfile__dynamic_array_synapses_9__synaptic_pre.write(reinterpret_cast<char*>(&_dynamic_array_synapses_9__synaptic_pre[0]), _dynamic_array_synapses_9__synaptic_pre.size()*sizeof(_dynamic_array_synapses_9__synaptic_pre[0]));
		    outfile__dynamic_array_synapses_9__synaptic_pre.close();
		}
	} else
	{
		std::cout << "Error writing output file for _dynamic_array_synapses_9__synaptic_pre." << endl;
	}
	ofstream outfile__dynamic_array_synapses_9_delay;
	outfile__dynamic_array_synapses_9_delay.open("results\\_dynamic_array_synapses_9_delay_8771265377939477977", ios::binary | ios::out);
	if(outfile__dynamic_array_synapses_9_delay.is_open())
	{
        if (! _dynamic_array_synapses_9_delay.empty() )
        {
			outfile__dynamic_array_synapses_9_delay.write(reinterpret_cast<char*>(&_dynamic_array_synapses_9_delay[0]), _dynamic_array_synapses_9_delay.size()*sizeof(_dynamic_array_synapses_9_delay[0]));
		    outfile__dynamic_array_synapses_9_delay.close();
		}
	} else
	{
		std::cout << "Error writing output file for _dynamic_array_synapses_9_delay." << endl;
	}
	ofstream outfile__dynamic_array_synapses_9_lastupdate;
	outfile__dynamic_array_synapses_9_lastupdate.open("results\\_dynamic_array_synapses_9_lastupdate_-5585496283630213764", ios::binary | ios::out);
	if(outfile__dynamic_array_synapses_9_lastupdate.is_open())
	{
        if (! _dynamic_array_synapses_9_lastupdate.empty() )
        {
			outfile__dynamic_array_synapses_9_lastupdate.write(reinterpret_cast<char*>(&_dynamic_array_synapses_9_lastupdate[0]), _dynamic_array_synapses_9_lastupdate.size()*sizeof(_dynamic_array_synapses_9_lastupdate[0]));
		    outfile__dynamic_array_synapses_9_lastupdate.close();
		}
	} else
	{
		std::cout << "Error writing output file for _dynamic_array_synapses_9_lastupdate." << endl;
	}
	ofstream outfile__dynamic_array_synapses_9_N_incoming;
	outfile__dynamic_array_synapses_9_N_incoming.open("results\\_dynamic_array_synapses_9_N_incoming_-532634285670516088", ios::binary | ios::out);
	if(outfile__dynamic_array_synapses_9_N_incoming.is_open())
	{
        if (! _dynamic_array_synapses_9_N_incoming.empty() )
        {
			outfile__dynamic_array_synapses_9_N_incoming.write(reinterpret_cast<char*>(&_dynamic_array_synapses_9_N_incoming[0]), _dynamic_array_synapses_9_N_incoming.size()*sizeof(_dynamic_array_synapses_9_N_incoming[0]));
		    outfile__dynamic_array_synapses_9_N_incoming.close();
		}
	} else
	{
		std::cout << "Error writing output file for _dynamic_array_synapses_9_N_incoming." << endl;
	}
	ofstream outfile__dynamic_array_synapses_9_N_outgoing;
	outfile__dynamic_array_synapses_9_N_outgoing.open("results\\_dynamic_array_synapses_9_N_outgoing_-5403873616426450280", ios::binary | ios::out);
	if(outfile__dynamic_array_synapses_9_N_outgoing.is_open())
	{
        if (! _dynamic_array_synapses_9_N_outgoing.empty() )
        {
			outfile__dynamic_array_synapses_9_N_outgoing.write(reinterpret_cast<char*>(&_dynamic_array_synapses_9_N_outgoing[0]), _dynamic_array_synapses_9_N_outgoing.size()*sizeof(_dynamic_array_synapses_9_N_outgoing[0]));
		    outfile__dynamic_array_synapses_9_N_outgoing.close();
		}
	} else
	{
		std::cout << "Error writing output file for _dynamic_array_synapses_9_N_outgoing." << endl;
	}
	ofstream outfile__dynamic_array_synapses_9_R;
	outfile__dynamic_array_synapses_9_R.open("results\\_dynamic_array_synapses_9_R_-2511293249675702099", ios::binary | ios::out);
	if(outfile__dynamic_array_synapses_9_R.is_open())
	{
        if (! _dynamic_array_synapses_9_R.empty() )
        {
			outfile__dynamic_array_synapses_9_R.write(reinterpret_cast<char*>(&_dynamic_array_synapses_9_R[0]), _dynamic_array_synapses_9_R.size()*sizeof(_dynamic_array_synapses_9_R[0]));
		    outfile__dynamic_array_synapses_9_R.close();
		}
	} else
	{
		std::cout << "Error writing output file for _dynamic_array_synapses_9_R." << endl;
	}
	ofstream outfile__dynamic_array_synapses_9_wght;
	outfile__dynamic_array_synapses_9_wght.open("results\\_dynamic_array_synapses_9_wght_-1886064199523380671", ios::binary | ios::out);
	if(outfile__dynamic_array_synapses_9_wght.is_open())
	{
        if (! _dynamic_array_synapses_9_wght.empty() )
        {
			outfile__dynamic_array_synapses_9_wght.write(reinterpret_cast<char*>(&_dynamic_array_synapses_9_wght[0]), _dynamic_array_synapses_9_wght.size()*sizeof(_dynamic_array_synapses_9_wght[0]));
		    outfile__dynamic_array_synapses_9_wght.close();
		}
	} else
	{
		std::cout << "Error writing output file for _dynamic_array_synapses_9_wght." << endl;
	}
	ofstream outfile__dynamic_array_synapses__synaptic_post;
	outfile__dynamic_array_synapses__synaptic_post.open("results\\_dynamic_array_synapses__synaptic_post_-1493737320517669780", ios::binary | ios::out);
	if(outfile__dynamic_array_synapses__synaptic_post.is_open())
	{
        if (! _dynamic_array_synapses__synaptic_post.empty() )
        {
			outfile__dynamic_array_synapses__synaptic_post.write(reinterpret_cast<char*>(&_dynamic_array_synapses__synaptic_post[0]), _dynamic_array_synapses__synaptic_post.size()*sizeof(_dynamic_array_synapses__synaptic_post[0]));
		    outfile__dynamic_array_synapses__synaptic_post.close();
		}
	} else
	{
		std::cout << "Error writing output file for _dynamic_array_synapses__synaptic_post." << endl;
	}
	ofstream outfile__dynamic_array_synapses__synaptic_pre;
	outfile__dynamic_array_synapses__synaptic_pre.open("results\\_dynamic_array_synapses__synaptic_pre_-813164193253639097", ios::binary | ios::out);
	if(outfile__dynamic_array_synapses__synaptic_pre.is_open())
	{
        if (! _dynamic_array_synapses__synaptic_pre.empty() )
        {
			outfile__dynamic_array_synapses__synaptic_pre.write(reinterpret_cast<char*>(&_dynamic_array_synapses__synaptic_pre[0]), _dynamic_array_synapses__synaptic_pre.size()*sizeof(_dynamic_array_synapses__synaptic_pre[0]));
		    outfile__dynamic_array_synapses__synaptic_pre.close();
		}
	} else
	{
		std::cout << "Error writing output file for _dynamic_array_synapses__synaptic_pre." << endl;
	}
	ofstream outfile__dynamic_array_synapses_delay;
	outfile__dynamic_array_synapses_delay.open("results\\_dynamic_array_synapses_delay_-6584010427613785939", ios::binary | ios::out);
	if(outfile__dynamic_array_synapses_delay.is_open())
	{
        if (! _dynamic_array_synapses_delay.empty() )
        {
			outfile__dynamic_array_synapses_delay.write(reinterpret_cast<char*>(&_dynamic_array_synapses_delay[0]), _dynamic_array_synapses_delay.size()*sizeof(_dynamic_array_synapses_delay[0]));
		    outfile__dynamic_array_synapses_delay.close();
		}
	} else
	{
		std::cout << "Error writing output file for _dynamic_array_synapses_delay." << endl;
	}
	ofstream outfile__dynamic_array_synapses_N_incoming;
	outfile__dynamic_array_synapses_N_incoming.open("results\\_dynamic_array_synapses_N_incoming_-3927568910411626391", ios::binary | ios::out);
	if(outfile__dynamic_array_synapses_N_incoming.is_open())
	{
        if (! _dynamic_array_synapses_N_incoming.empty() )
        {
			outfile__dynamic_array_synapses_N_incoming.write(reinterpret_cast<char*>(&_dynamic_array_synapses_N_incoming[0]), _dynamic_array_synapses_N_incoming.size()*sizeof(_dynamic_array_synapses_N_incoming[0]));
		    outfile__dynamic_array_synapses_N_incoming.close();
		}
	} else
	{
		std::cout << "Error writing output file for _dynamic_array_synapses_N_incoming." << endl;
	}
	ofstream outfile__dynamic_array_synapses_N_outgoing;
	outfile__dynamic_array_synapses_N_outgoing.open("results\\_dynamic_array_synapses_N_outgoing_-7235594971023667180", ios::binary | ios::out);
	if(outfile__dynamic_array_synapses_N_outgoing.is_open())
	{
        if (! _dynamic_array_synapses_N_outgoing.empty() )
        {
			outfile__dynamic_array_synapses_N_outgoing.write(reinterpret_cast<char*>(&_dynamic_array_synapses_N_outgoing[0]), _dynamic_array_synapses_N_outgoing.size()*sizeof(_dynamic_array_synapses_N_outgoing[0]));
		    outfile__dynamic_array_synapses_N_outgoing.close();
		}
	} else
	{
		std::cout << "Error writing output file for _dynamic_array_synapses_N_outgoing." << endl;
	}

	// Write profiling info to disk
	ofstream outfile_profiling_info;
	outfile_profiling_info.open("results/profiling_info.txt", ios::out);
	if(outfile_profiling_info.is_open())
	{
	outfile_profiling_info << "neurongroup_1_resetter_codeobject\t" << neurongroup_1_resetter_codeobject_profiling_info << std::endl;
	outfile_profiling_info << "neurongroup_1_stateupdater_codeobject\t" << neurongroup_1_stateupdater_codeobject_profiling_info << std::endl;
	outfile_profiling_info << "neurongroup_1_thresholder_codeobject\t" << neurongroup_1_thresholder_codeobject_profiling_info << std::endl;
	outfile_profiling_info << "neurongroup_2_resetter_codeobject\t" << neurongroup_2_resetter_codeobject_profiling_info << std::endl;
	outfile_profiling_info << "neurongroup_2_stateupdater_codeobject\t" << neurongroup_2_stateupdater_codeobject_profiling_info << std::endl;
	outfile_profiling_info << "neurongroup_2_thresholder_codeobject\t" << neurongroup_2_thresholder_codeobject_profiling_info << std::endl;
	outfile_profiling_info << "neurongroup_3_resetter_codeobject\t" << neurongroup_3_resetter_codeobject_profiling_info << std::endl;
	outfile_profiling_info << "neurongroup_3_stateupdater_codeobject\t" << neurongroup_3_stateupdater_codeobject_profiling_info << std::endl;
	outfile_profiling_info << "neurongroup_3_thresholder_codeobject\t" << neurongroup_3_thresholder_codeobject_profiling_info << std::endl;
	outfile_profiling_info << "neurongroup_4_resetter_codeobject\t" << neurongroup_4_resetter_codeobject_profiling_info << std::endl;
	outfile_profiling_info << "neurongroup_4_stateupdater_codeobject\t" << neurongroup_4_stateupdater_codeobject_profiling_info << std::endl;
	outfile_profiling_info << "neurongroup_4_thresholder_codeobject\t" << neurongroup_4_thresholder_codeobject_profiling_info << std::endl;
	outfile_profiling_info << "neurongroup_5_resetter_codeobject\t" << neurongroup_5_resetter_codeobject_profiling_info << std::endl;
	outfile_profiling_info << "neurongroup_5_stateupdater_codeobject\t" << neurongroup_5_stateupdater_codeobject_profiling_info << std::endl;
	outfile_profiling_info << "neurongroup_5_thresholder_codeobject\t" << neurongroup_5_thresholder_codeobject_profiling_info << std::endl;
	outfile_profiling_info << "neurongroup_resetter_codeobject\t" << neurongroup_resetter_codeobject_profiling_info << std::endl;
	outfile_profiling_info << "neurongroup_thresholder_codeobject\t" << neurongroup_thresholder_codeobject_profiling_info << std::endl;
	outfile_profiling_info << "poissoninput_10_codeobject\t" << poissoninput_10_codeobject_profiling_info << std::endl;
	outfile_profiling_info << "poissoninput_11_codeobject\t" << poissoninput_11_codeobject_profiling_info << std::endl;
	outfile_profiling_info << "poissoninput_12_codeobject\t" << poissoninput_12_codeobject_profiling_info << std::endl;
	outfile_profiling_info << "poissoninput_13_codeobject\t" << poissoninput_13_codeobject_profiling_info << std::endl;
	outfile_profiling_info << "poissoninput_14_codeobject\t" << poissoninput_14_codeobject_profiling_info << std::endl;
	outfile_profiling_info << "poissoninput_15_codeobject\t" << poissoninput_15_codeobject_profiling_info << std::endl;
	outfile_profiling_info << "poissoninput_1_codeobject\t" << poissoninput_1_codeobject_profiling_info << std::endl;
	outfile_profiling_info << "poissoninput_2_codeobject\t" << poissoninput_2_codeobject_profiling_info << std::endl;
	outfile_profiling_info << "poissoninput_3_codeobject\t" << poissoninput_3_codeobject_profiling_info << std::endl;
	outfile_profiling_info << "poissoninput_4_codeobject\t" << poissoninput_4_codeobject_profiling_info << std::endl;
	outfile_profiling_info << "poissoninput_5_codeobject\t" << poissoninput_5_codeobject_profiling_info << std::endl;
	outfile_profiling_info << "poissoninput_6_codeobject\t" << poissoninput_6_codeobject_profiling_info << std::endl;
	outfile_profiling_info << "poissoninput_7_codeobject\t" << poissoninput_7_codeobject_profiling_info << std::endl;
	outfile_profiling_info << "poissoninput_8_codeobject\t" << poissoninput_8_codeobject_profiling_info << std::endl;
	outfile_profiling_info << "poissoninput_9_codeobject\t" << poissoninput_9_codeobject_profiling_info << std::endl;
	outfile_profiling_info << "poissoninput_codeobject\t" << poissoninput_codeobject_profiling_info << std::endl;
	outfile_profiling_info << "spikegeneratorgroup_codeobject\t" << spikegeneratorgroup_codeobject_profiling_info << std::endl;
	outfile_profiling_info << "spikemonitor_1_codeobject\t" << spikemonitor_1_codeobject_profiling_info << std::endl;
	outfile_profiling_info << "spikemonitor_2_codeobject\t" << spikemonitor_2_codeobject_profiling_info << std::endl;
	outfile_profiling_info << "spikemonitor_3_codeobject\t" << spikemonitor_3_codeobject_profiling_info << std::endl;
	outfile_profiling_info << "spikemonitor_4_codeobject\t" << spikemonitor_4_codeobject_profiling_info << std::endl;
	outfile_profiling_info << "spikemonitor_5_codeobject\t" << spikemonitor_5_codeobject_profiling_info << std::endl;
	outfile_profiling_info << "spikemonitor_codeobject\t" << spikemonitor_codeobject_profiling_info << std::endl;
	outfile_profiling_info << "synapses_10_pre_codeobject\t" << synapses_10_pre_codeobject_profiling_info << std::endl;
	outfile_profiling_info << "synapses_10_pre_initialise_queue\t" << synapses_10_pre_initialise_queue_profiling_info << std::endl;
	outfile_profiling_info << "synapses_10_pre_push_spikes\t" << synapses_10_pre_push_spikes_profiling_info << std::endl;
	outfile_profiling_info << "synapses_11_pre_codeobject\t" << synapses_11_pre_codeobject_profiling_info << std::endl;
	outfile_profiling_info << "synapses_11_pre_initialise_queue\t" << synapses_11_pre_initialise_queue_profiling_info << std::endl;
	outfile_profiling_info << "synapses_11_pre_push_spikes\t" << synapses_11_pre_push_spikes_profiling_info << std::endl;
	outfile_profiling_info << "synapses_12_pre_codeobject\t" << synapses_12_pre_codeobject_profiling_info << std::endl;
	outfile_profiling_info << "synapses_12_pre_initialise_queue\t" << synapses_12_pre_initialise_queue_profiling_info << std::endl;
	outfile_profiling_info << "synapses_12_pre_push_spikes\t" << synapses_12_pre_push_spikes_profiling_info << std::endl;
	outfile_profiling_info << "synapses_13_pre_codeobject\t" << synapses_13_pre_codeobject_profiling_info << std::endl;
	outfile_profiling_info << "synapses_13_pre_initialise_queue\t" << synapses_13_pre_initialise_queue_profiling_info << std::endl;
	outfile_profiling_info << "synapses_13_pre_push_spikes\t" << synapses_13_pre_push_spikes_profiling_info << std::endl;
	outfile_profiling_info << "synapses_14_pre_codeobject\t" << synapses_14_pre_codeobject_profiling_info << std::endl;
	outfile_profiling_info << "synapses_14_pre_initialise_queue\t" << synapses_14_pre_initialise_queue_profiling_info << std::endl;
	outfile_profiling_info << "synapses_14_pre_push_spikes\t" << synapses_14_pre_push_spikes_profiling_info << std::endl;
	outfile_profiling_info << "synapses_15_pre_codeobject\t" << synapses_15_pre_codeobject_profiling_info << std::endl;
	outfile_profiling_info << "synapses_15_pre_initialise_queue\t" << synapses_15_pre_initialise_queue_profiling_info << std::endl;
	outfile_profiling_info << "synapses_15_pre_push_spikes\t" << synapses_15_pre_push_spikes_profiling_info << std::endl;
	outfile_profiling_info << "synapses_16_pre_codeobject\t" << synapses_16_pre_codeobject_profiling_info << std::endl;
	outfile_profiling_info << "synapses_16_pre_initialise_queue\t" << synapses_16_pre_initialise_queue_profiling_info << std::endl;
	outfile_profiling_info << "synapses_16_pre_push_spikes\t" << synapses_16_pre_push_spikes_profiling_info << std::endl;
	outfile_profiling_info << "synapses_17_pre_codeobject\t" << synapses_17_pre_codeobject_profiling_info << std::endl;
	outfile_profiling_info << "synapses_17_pre_initialise_queue\t" << synapses_17_pre_initialise_queue_profiling_info << std::endl;
	outfile_profiling_info << "synapses_17_pre_push_spikes\t" << synapses_17_pre_push_spikes_profiling_info << std::endl;
	outfile_profiling_info << "synapses_18_pre_codeobject\t" << synapses_18_pre_codeobject_profiling_info << std::endl;
	outfile_profiling_info << "synapses_18_pre_initialise_queue\t" << synapses_18_pre_initialise_queue_profiling_info << std::endl;
	outfile_profiling_info << "synapses_18_pre_push_spikes\t" << synapses_18_pre_push_spikes_profiling_info << std::endl;
	outfile_profiling_info << "synapses_19_pre_codeobject\t" << synapses_19_pre_codeobject_profiling_info << std::endl;
	outfile_profiling_info << "synapses_19_pre_initialise_queue\t" << synapses_19_pre_initialise_queue_profiling_info << std::endl;
	outfile_profiling_info << "synapses_19_pre_push_spikes\t" << synapses_19_pre_push_spikes_profiling_info << std::endl;
	outfile_profiling_info << "synapses_1_pre_codeobject\t" << synapses_1_pre_codeobject_profiling_info << std::endl;
	outfile_profiling_info << "synapses_1_pre_initialise_queue\t" << synapses_1_pre_initialise_queue_profiling_info << std::endl;
	outfile_profiling_info << "synapses_1_pre_push_spikes\t" << synapses_1_pre_push_spikes_profiling_info << std::endl;
	outfile_profiling_info << "synapses_20_pre_codeobject\t" << synapses_20_pre_codeobject_profiling_info << std::endl;
	outfile_profiling_info << "synapses_20_pre_initialise_queue\t" << synapses_20_pre_initialise_queue_profiling_info << std::endl;
	outfile_profiling_info << "synapses_20_pre_push_spikes\t" << synapses_20_pre_push_spikes_profiling_info << std::endl;
	outfile_profiling_info << "synapses_21_pre_codeobject\t" << synapses_21_pre_codeobject_profiling_info << std::endl;
	outfile_profiling_info << "synapses_21_pre_initialise_queue\t" << synapses_21_pre_initialise_queue_profiling_info << std::endl;
	outfile_profiling_info << "synapses_21_pre_push_spikes\t" << synapses_21_pre_push_spikes_profiling_info << std::endl;
	outfile_profiling_info << "synapses_22_pre_codeobject\t" << synapses_22_pre_codeobject_profiling_info << std::endl;
	outfile_profiling_info << "synapses_22_pre_initialise_queue\t" << synapses_22_pre_initialise_queue_profiling_info << std::endl;
	outfile_profiling_info << "synapses_22_pre_push_spikes\t" << synapses_22_pre_push_spikes_profiling_info << std::endl;
	outfile_profiling_info << "synapses_23_pre_codeobject\t" << synapses_23_pre_codeobject_profiling_info << std::endl;
	outfile_profiling_info << "synapses_23_pre_initialise_queue\t" << synapses_23_pre_initialise_queue_profiling_info << std::endl;
	outfile_profiling_info << "synapses_23_pre_push_spikes\t" << synapses_23_pre_push_spikes_profiling_info << std::endl;
	outfile_profiling_info << "synapses_24_pre_codeobject\t" << synapses_24_pre_codeobject_profiling_info << std::endl;
	outfile_profiling_info << "synapses_24_pre_initialise_queue\t" << synapses_24_pre_initialise_queue_profiling_info << std::endl;
	outfile_profiling_info << "synapses_24_pre_push_spikes\t" << synapses_24_pre_push_spikes_profiling_info << std::endl;
	outfile_profiling_info << "synapses_25_pre_codeobject\t" << synapses_25_pre_codeobject_profiling_info << std::endl;
	outfile_profiling_info << "synapses_25_pre_initialise_queue\t" << synapses_25_pre_initialise_queue_profiling_info << std::endl;
	outfile_profiling_info << "synapses_25_pre_push_spikes\t" << synapses_25_pre_push_spikes_profiling_info << std::endl;
	outfile_profiling_info << "synapses_26_pre_codeobject\t" << synapses_26_pre_codeobject_profiling_info << std::endl;
	outfile_profiling_info << "synapses_26_pre_initialise_queue\t" << synapses_26_pre_initialise_queue_profiling_info << std::endl;
	outfile_profiling_info << "synapses_26_pre_push_spikes\t" << synapses_26_pre_push_spikes_profiling_info << std::endl;
	outfile_profiling_info << "synapses_27_pre_codeobject\t" << synapses_27_pre_codeobject_profiling_info << std::endl;
	outfile_profiling_info << "synapses_27_pre_initialise_queue\t" << synapses_27_pre_initialise_queue_profiling_info << std::endl;
	outfile_profiling_info << "synapses_27_pre_push_spikes\t" << synapses_27_pre_push_spikes_profiling_info << std::endl;
	outfile_profiling_info << "synapses_28_pre_codeobject\t" << synapses_28_pre_codeobject_profiling_info << std::endl;
	outfile_profiling_info << "synapses_28_pre_initialise_queue\t" << synapses_28_pre_initialise_queue_profiling_info << std::endl;
	outfile_profiling_info << "synapses_28_pre_push_spikes\t" << synapses_28_pre_push_spikes_profiling_info << std::endl;
	outfile_profiling_info << "synapses_29_pre_codeobject\t" << synapses_29_pre_codeobject_profiling_info << std::endl;
	outfile_profiling_info << "synapses_29_pre_initialise_queue\t" << synapses_29_pre_initialise_queue_profiling_info << std::endl;
	outfile_profiling_info << "synapses_29_pre_push_spikes\t" << synapses_29_pre_push_spikes_profiling_info << std::endl;
	outfile_profiling_info << "synapses_2_pre_codeobject\t" << synapses_2_pre_codeobject_profiling_info << std::endl;
	outfile_profiling_info << "synapses_2_pre_initialise_queue\t" << synapses_2_pre_initialise_queue_profiling_info << std::endl;
	outfile_profiling_info << "synapses_2_pre_push_spikes\t" << synapses_2_pre_push_spikes_profiling_info << std::endl;
	outfile_profiling_info << "synapses_30_pre_codeobject\t" << synapses_30_pre_codeobject_profiling_info << std::endl;
	outfile_profiling_info << "synapses_30_pre_initialise_queue\t" << synapses_30_pre_initialise_queue_profiling_info << std::endl;
	outfile_profiling_info << "synapses_30_pre_push_spikes\t" << synapses_30_pre_push_spikes_profiling_info << std::endl;
	outfile_profiling_info << "synapses_31_pre_codeobject\t" << synapses_31_pre_codeobject_profiling_info << std::endl;
	outfile_profiling_info << "synapses_31_pre_initialise_queue\t" << synapses_31_pre_initialise_queue_profiling_info << std::endl;
	outfile_profiling_info << "synapses_31_pre_push_spikes\t" << synapses_31_pre_push_spikes_profiling_info << std::endl;
	outfile_profiling_info << "synapses_32_pre_codeobject\t" << synapses_32_pre_codeobject_profiling_info << std::endl;
	outfile_profiling_info << "synapses_32_pre_initialise_queue\t" << synapses_32_pre_initialise_queue_profiling_info << std::endl;
	outfile_profiling_info << "synapses_32_pre_push_spikes\t" << synapses_32_pre_push_spikes_profiling_info << std::endl;
	outfile_profiling_info << "synapses_33_pre_codeobject\t" << synapses_33_pre_codeobject_profiling_info << std::endl;
	outfile_profiling_info << "synapses_33_pre_initialise_queue\t" << synapses_33_pre_initialise_queue_profiling_info << std::endl;
	outfile_profiling_info << "synapses_33_pre_push_spikes\t" << synapses_33_pre_push_spikes_profiling_info << std::endl;
	outfile_profiling_info << "synapses_34_pre_codeobject\t" << synapses_34_pre_codeobject_profiling_info << std::endl;
	outfile_profiling_info << "synapses_34_pre_initialise_queue\t" << synapses_34_pre_initialise_queue_profiling_info << std::endl;
	outfile_profiling_info << "synapses_34_pre_push_spikes\t" << synapses_34_pre_push_spikes_profiling_info << std::endl;
	outfile_profiling_info << "synapses_35_pre_codeobject\t" << synapses_35_pre_codeobject_profiling_info << std::endl;
	outfile_profiling_info << "synapses_35_pre_initialise_queue\t" << synapses_35_pre_initialise_queue_profiling_info << std::endl;
	outfile_profiling_info << "synapses_35_pre_push_spikes\t" << synapses_35_pre_push_spikes_profiling_info << std::endl;
	outfile_profiling_info << "synapses_36_pre_codeobject\t" << synapses_36_pre_codeobject_profiling_info << std::endl;
	outfile_profiling_info << "synapses_36_pre_initialise_queue\t" << synapses_36_pre_initialise_queue_profiling_info << std::endl;
	outfile_profiling_info << "synapses_36_pre_push_spikes\t" << synapses_36_pre_push_spikes_profiling_info << std::endl;
	outfile_profiling_info << "synapses_37_pre_codeobject\t" << synapses_37_pre_codeobject_profiling_info << std::endl;
	outfile_profiling_info << "synapses_37_pre_initialise_queue\t" << synapses_37_pre_initialise_queue_profiling_info << std::endl;
	outfile_profiling_info << "synapses_37_pre_push_spikes\t" << synapses_37_pre_push_spikes_profiling_info << std::endl;
	outfile_profiling_info << "synapses_3_pre_codeobject\t" << synapses_3_pre_codeobject_profiling_info << std::endl;
	outfile_profiling_info << "synapses_3_pre_initialise_queue\t" << synapses_3_pre_initialise_queue_profiling_info << std::endl;
	outfile_profiling_info << "synapses_3_pre_push_spikes\t" << synapses_3_pre_push_spikes_profiling_info << std::endl;
	outfile_profiling_info << "synapses_4_pre_codeobject\t" << synapses_4_pre_codeobject_profiling_info << std::endl;
	outfile_profiling_info << "synapses_4_pre_initialise_queue\t" << synapses_4_pre_initialise_queue_profiling_info << std::endl;
	outfile_profiling_info << "synapses_4_pre_push_spikes\t" << synapses_4_pre_push_spikes_profiling_info << std::endl;
	outfile_profiling_info << "synapses_5_pre_codeobject\t" << synapses_5_pre_codeobject_profiling_info << std::endl;
	outfile_profiling_info << "synapses_5_pre_initialise_queue\t" << synapses_5_pre_initialise_queue_profiling_info << std::endl;
	outfile_profiling_info << "synapses_5_pre_push_spikes\t" << synapses_5_pre_push_spikes_profiling_info << std::endl;
	outfile_profiling_info << "synapses_6_pre_codeobject\t" << synapses_6_pre_codeobject_profiling_info << std::endl;
	outfile_profiling_info << "synapses_6_pre_initialise_queue\t" << synapses_6_pre_initialise_queue_profiling_info << std::endl;
	outfile_profiling_info << "synapses_6_pre_push_spikes\t" << synapses_6_pre_push_spikes_profiling_info << std::endl;
	outfile_profiling_info << "synapses_7_pre_codeobject\t" << synapses_7_pre_codeobject_profiling_info << std::endl;
	outfile_profiling_info << "synapses_7_pre_initialise_queue\t" << synapses_7_pre_initialise_queue_profiling_info << std::endl;
	outfile_profiling_info << "synapses_7_pre_push_spikes\t" << synapses_7_pre_push_spikes_profiling_info << std::endl;
	outfile_profiling_info << "synapses_8_pre_codeobject\t" << synapses_8_pre_codeobject_profiling_info << std::endl;
	outfile_profiling_info << "synapses_8_pre_initialise_queue\t" << synapses_8_pre_initialise_queue_profiling_info << std::endl;
	outfile_profiling_info << "synapses_8_pre_push_spikes\t" << synapses_8_pre_push_spikes_profiling_info << std::endl;
	outfile_profiling_info << "synapses_9_pre_codeobject\t" << synapses_9_pre_codeobject_profiling_info << std::endl;
	outfile_profiling_info << "synapses_9_pre_initialise_queue\t" << synapses_9_pre_initialise_queue_profiling_info << std::endl;
	outfile_profiling_info << "synapses_9_pre_push_spikes\t" << synapses_9_pre_push_spikes_profiling_info << std::endl;
	outfile_profiling_info << "synapses_pre_codeobject\t" << synapses_pre_codeobject_profiling_info << std::endl;
	outfile_profiling_info << "synapses_pre_initialise_queue\t" << synapses_pre_initialise_queue_profiling_info << std::endl;
	outfile_profiling_info << "synapses_pre_push_spikes\t" << synapses_pre_push_spikes_profiling_info << std::endl;
	outfile_profiling_info.close();
	} else
	{
	    std::cout << "Error writing profiling info to file." << std::endl;
	}
	// Write last run info to disk
	ofstream outfile_last_run_info;
	outfile_last_run_info.open("results/last_run_info.txt", ios::out);
	if(outfile_last_run_info.is_open())
	{
		outfile_last_run_info << (Network::_last_run_time) << " " << (Network::_last_run_completed_fraction) << std::endl;
		outfile_last_run_info.close();
	} else
	{
	    std::cout << "Error writing last run info to file." << std::endl;
	}
}

void _dealloc_arrays()
{
	using namespace brian;


	// static arrays
	if(_static_array__array_neurongroup_1_x!=0)
	{
		delete [] _static_array__array_neurongroup_1_x;
		_static_array__array_neurongroup_1_x = 0;
	}
	if(_static_array__array_neurongroup_1_y!=0)
	{
		delete [] _static_array__array_neurongroup_1_y;
		_static_array__array_neurongroup_1_y = 0;
	}
	if(_static_array__array_neurongroup_2_x!=0)
	{
		delete [] _static_array__array_neurongroup_2_x;
		_static_array__array_neurongroup_2_x = 0;
	}
	if(_static_array__array_neurongroup_2_y!=0)
	{
		delete [] _static_array__array_neurongroup_2_y;
		_static_array__array_neurongroup_2_y = 0;
	}
	if(_static_array__array_neurongroup_3_x!=0)
	{
		delete [] _static_array__array_neurongroup_3_x;
		_static_array__array_neurongroup_3_x = 0;
	}
	if(_static_array__array_neurongroup_3_y!=0)
	{
		delete [] _static_array__array_neurongroup_3_y;
		_static_array__array_neurongroup_3_y = 0;
	}
	if(_static_array__array_neurongroup_4_x!=0)
	{
		delete [] _static_array__array_neurongroup_4_x;
		_static_array__array_neurongroup_4_x = 0;
	}
	if(_static_array__array_neurongroup_4_y!=0)
	{
		delete [] _static_array__array_neurongroup_4_y;
		_static_array__array_neurongroup_4_y = 0;
	}
	if(_static_array__array_neurongroup_5_x!=0)
	{
		delete [] _static_array__array_neurongroup_5_x;
		_static_array__array_neurongroup_5_x = 0;
	}
	if(_static_array__array_neurongroup_5_y!=0)
	{
		delete [] _static_array__array_neurongroup_5_y;
		_static_array__array_neurongroup_5_y = 0;
	}
	if(_static_array__array_neurongroup_x!=0)
	{
		delete [] _static_array__array_neurongroup_x;
		_static_array__array_neurongroup_x = 0;
	}
	if(_static_array__array_neurongroup_y!=0)
	{
		delete [] _static_array__array_neurongroup_y;
		_static_array__array_neurongroup_y = 0;
	}
	if(_static_array__array_synapses_10_sources!=0)
	{
		delete [] _static_array__array_synapses_10_sources;
		_static_array__array_synapses_10_sources = 0;
	}
	if(_static_array__array_synapses_10_targets!=0)
	{
		delete [] _static_array__array_synapses_10_targets;
		_static_array__array_synapses_10_targets = 0;
	}
	if(_static_array__array_synapses_11_sources!=0)
	{
		delete [] _static_array__array_synapses_11_sources;
		_static_array__array_synapses_11_sources = 0;
	}
	if(_static_array__array_synapses_11_targets!=0)
	{
		delete [] _static_array__array_synapses_11_targets;
		_static_array__array_synapses_11_targets = 0;
	}
	if(_static_array__array_synapses_12_sources!=0)
	{
		delete [] _static_array__array_synapses_12_sources;
		_static_array__array_synapses_12_sources = 0;
	}
	if(_static_array__array_synapses_12_targets!=0)
	{
		delete [] _static_array__array_synapses_12_targets;
		_static_array__array_synapses_12_targets = 0;
	}
	if(_static_array__array_synapses_13_sources!=0)
	{
		delete [] _static_array__array_synapses_13_sources;
		_static_array__array_synapses_13_sources = 0;
	}
	if(_static_array__array_synapses_13_targets!=0)
	{
		delete [] _static_array__array_synapses_13_targets;
		_static_array__array_synapses_13_targets = 0;
	}
	if(_static_array__array_synapses_14_sources!=0)
	{
		delete [] _static_array__array_synapses_14_sources;
		_static_array__array_synapses_14_sources = 0;
	}
	if(_static_array__array_synapses_14_targets!=0)
	{
		delete [] _static_array__array_synapses_14_targets;
		_static_array__array_synapses_14_targets = 0;
	}
	if(_static_array__array_synapses_15_sources!=0)
	{
		delete [] _static_array__array_synapses_15_sources;
		_static_array__array_synapses_15_sources = 0;
	}
	if(_static_array__array_synapses_15_targets!=0)
	{
		delete [] _static_array__array_synapses_15_targets;
		_static_array__array_synapses_15_targets = 0;
	}
	if(_static_array__array_synapses_16_sources!=0)
	{
		delete [] _static_array__array_synapses_16_sources;
		_static_array__array_synapses_16_sources = 0;
	}
	if(_static_array__array_synapses_16_targets!=0)
	{
		delete [] _static_array__array_synapses_16_targets;
		_static_array__array_synapses_16_targets = 0;
	}
	if(_static_array__array_synapses_17_sources!=0)
	{
		delete [] _static_array__array_synapses_17_sources;
		_static_array__array_synapses_17_sources = 0;
	}
	if(_static_array__array_synapses_17_targets!=0)
	{
		delete [] _static_array__array_synapses_17_targets;
		_static_array__array_synapses_17_targets = 0;
	}
	if(_static_array__array_synapses_18_sources!=0)
	{
		delete [] _static_array__array_synapses_18_sources;
		_static_array__array_synapses_18_sources = 0;
	}
	if(_static_array__array_synapses_18_targets!=0)
	{
		delete [] _static_array__array_synapses_18_targets;
		_static_array__array_synapses_18_targets = 0;
	}
	if(_static_array__array_synapses_19_sources!=0)
	{
		delete [] _static_array__array_synapses_19_sources;
		_static_array__array_synapses_19_sources = 0;
	}
	if(_static_array__array_synapses_19_targets!=0)
	{
		delete [] _static_array__array_synapses_19_targets;
		_static_array__array_synapses_19_targets = 0;
	}
	if(_static_array__array_synapses_1_sources!=0)
	{
		delete [] _static_array__array_synapses_1_sources;
		_static_array__array_synapses_1_sources = 0;
	}
	if(_static_array__array_synapses_1_targets!=0)
	{
		delete [] _static_array__array_synapses_1_targets;
		_static_array__array_synapses_1_targets = 0;
	}
	if(_static_array__array_synapses_20_sources!=0)
	{
		delete [] _static_array__array_synapses_20_sources;
		_static_array__array_synapses_20_sources = 0;
	}
	if(_static_array__array_synapses_20_targets!=0)
	{
		delete [] _static_array__array_synapses_20_targets;
		_static_array__array_synapses_20_targets = 0;
	}
	if(_static_array__array_synapses_21_sources!=0)
	{
		delete [] _static_array__array_synapses_21_sources;
		_static_array__array_synapses_21_sources = 0;
	}
	if(_static_array__array_synapses_21_targets!=0)
	{
		delete [] _static_array__array_synapses_21_targets;
		_static_array__array_synapses_21_targets = 0;
	}
	if(_static_array__array_synapses_22_sources!=0)
	{
		delete [] _static_array__array_synapses_22_sources;
		_static_array__array_synapses_22_sources = 0;
	}
	if(_static_array__array_synapses_22_targets!=0)
	{
		delete [] _static_array__array_synapses_22_targets;
		_static_array__array_synapses_22_targets = 0;
	}
	if(_static_array__array_synapses_23_sources!=0)
	{
		delete [] _static_array__array_synapses_23_sources;
		_static_array__array_synapses_23_sources = 0;
	}
	if(_static_array__array_synapses_23_targets!=0)
	{
		delete [] _static_array__array_synapses_23_targets;
		_static_array__array_synapses_23_targets = 0;
	}
	if(_static_array__array_synapses_24_sources!=0)
	{
		delete [] _static_array__array_synapses_24_sources;
		_static_array__array_synapses_24_sources = 0;
	}
	if(_static_array__array_synapses_24_targets!=0)
	{
		delete [] _static_array__array_synapses_24_targets;
		_static_array__array_synapses_24_targets = 0;
	}
	if(_static_array__array_synapses_25_sources!=0)
	{
		delete [] _static_array__array_synapses_25_sources;
		_static_array__array_synapses_25_sources = 0;
	}
	if(_static_array__array_synapses_25_targets!=0)
	{
		delete [] _static_array__array_synapses_25_targets;
		_static_array__array_synapses_25_targets = 0;
	}
	if(_static_array__array_synapses_26_sources!=0)
	{
		delete [] _static_array__array_synapses_26_sources;
		_static_array__array_synapses_26_sources = 0;
	}
	if(_static_array__array_synapses_26_targets!=0)
	{
		delete [] _static_array__array_synapses_26_targets;
		_static_array__array_synapses_26_targets = 0;
	}
	if(_static_array__array_synapses_27_sources!=0)
	{
		delete [] _static_array__array_synapses_27_sources;
		_static_array__array_synapses_27_sources = 0;
	}
	if(_static_array__array_synapses_27_targets!=0)
	{
		delete [] _static_array__array_synapses_27_targets;
		_static_array__array_synapses_27_targets = 0;
	}
	if(_static_array__array_synapses_28_sources!=0)
	{
		delete [] _static_array__array_synapses_28_sources;
		_static_array__array_synapses_28_sources = 0;
	}
	if(_static_array__array_synapses_28_targets!=0)
	{
		delete [] _static_array__array_synapses_28_targets;
		_static_array__array_synapses_28_targets = 0;
	}
	if(_static_array__array_synapses_29_sources!=0)
	{
		delete [] _static_array__array_synapses_29_sources;
		_static_array__array_synapses_29_sources = 0;
	}
	if(_static_array__array_synapses_29_targets!=0)
	{
		delete [] _static_array__array_synapses_29_targets;
		_static_array__array_synapses_29_targets = 0;
	}
	if(_static_array__array_synapses_2_sources!=0)
	{
		delete [] _static_array__array_synapses_2_sources;
		_static_array__array_synapses_2_sources = 0;
	}
	if(_static_array__array_synapses_2_targets!=0)
	{
		delete [] _static_array__array_synapses_2_targets;
		_static_array__array_synapses_2_targets = 0;
	}
	if(_static_array__array_synapses_30_sources!=0)
	{
		delete [] _static_array__array_synapses_30_sources;
		_static_array__array_synapses_30_sources = 0;
	}
	if(_static_array__array_synapses_30_targets!=0)
	{
		delete [] _static_array__array_synapses_30_targets;
		_static_array__array_synapses_30_targets = 0;
	}
	if(_static_array__array_synapses_31_sources!=0)
	{
		delete [] _static_array__array_synapses_31_sources;
		_static_array__array_synapses_31_sources = 0;
	}
	if(_static_array__array_synapses_31_targets!=0)
	{
		delete [] _static_array__array_synapses_31_targets;
		_static_array__array_synapses_31_targets = 0;
	}
	if(_static_array__array_synapses_32_sources!=0)
	{
		delete [] _static_array__array_synapses_32_sources;
		_static_array__array_synapses_32_sources = 0;
	}
	if(_static_array__array_synapses_32_targets!=0)
	{
		delete [] _static_array__array_synapses_32_targets;
		_static_array__array_synapses_32_targets = 0;
	}
	if(_static_array__array_synapses_33_sources!=0)
	{
		delete [] _static_array__array_synapses_33_sources;
		_static_array__array_synapses_33_sources = 0;
	}
	if(_static_array__array_synapses_33_targets!=0)
	{
		delete [] _static_array__array_synapses_33_targets;
		_static_array__array_synapses_33_targets = 0;
	}
	if(_static_array__array_synapses_34_sources!=0)
	{
		delete [] _static_array__array_synapses_34_sources;
		_static_array__array_synapses_34_sources = 0;
	}
	if(_static_array__array_synapses_34_targets!=0)
	{
		delete [] _static_array__array_synapses_34_targets;
		_static_array__array_synapses_34_targets = 0;
	}
	if(_static_array__array_synapses_35_sources!=0)
	{
		delete [] _static_array__array_synapses_35_sources;
		_static_array__array_synapses_35_sources = 0;
	}
	if(_static_array__array_synapses_35_targets!=0)
	{
		delete [] _static_array__array_synapses_35_targets;
		_static_array__array_synapses_35_targets = 0;
	}
	if(_static_array__array_synapses_36_sources!=0)
	{
		delete [] _static_array__array_synapses_36_sources;
		_static_array__array_synapses_36_sources = 0;
	}
	if(_static_array__array_synapses_36_targets!=0)
	{
		delete [] _static_array__array_synapses_36_targets;
		_static_array__array_synapses_36_targets = 0;
	}
	if(_static_array__array_synapses_37_sources!=0)
	{
		delete [] _static_array__array_synapses_37_sources;
		_static_array__array_synapses_37_sources = 0;
	}
	if(_static_array__array_synapses_37_targets!=0)
	{
		delete [] _static_array__array_synapses_37_targets;
		_static_array__array_synapses_37_targets = 0;
	}
	if(_static_array__array_synapses_3_sources!=0)
	{
		delete [] _static_array__array_synapses_3_sources;
		_static_array__array_synapses_3_sources = 0;
	}
	if(_static_array__array_synapses_3_targets!=0)
	{
		delete [] _static_array__array_synapses_3_targets;
		_static_array__array_synapses_3_targets = 0;
	}
	if(_static_array__array_synapses_4_sources!=0)
	{
		delete [] _static_array__array_synapses_4_sources;
		_static_array__array_synapses_4_sources = 0;
	}
	if(_static_array__array_synapses_4_targets!=0)
	{
		delete [] _static_array__array_synapses_4_targets;
		_static_array__array_synapses_4_targets = 0;
	}
	if(_static_array__array_synapses_5_sources!=0)
	{
		delete [] _static_array__array_synapses_5_sources;
		_static_array__array_synapses_5_sources = 0;
	}
	if(_static_array__array_synapses_5_targets!=0)
	{
		delete [] _static_array__array_synapses_5_targets;
		_static_array__array_synapses_5_targets = 0;
	}
	if(_static_array__array_synapses_6_sources!=0)
	{
		delete [] _static_array__array_synapses_6_sources;
		_static_array__array_synapses_6_sources = 0;
	}
	if(_static_array__array_synapses_6_targets!=0)
	{
		delete [] _static_array__array_synapses_6_targets;
		_static_array__array_synapses_6_targets = 0;
	}
	if(_static_array__array_synapses_7_sources!=0)
	{
		delete [] _static_array__array_synapses_7_sources;
		_static_array__array_synapses_7_sources = 0;
	}
	if(_static_array__array_synapses_7_targets!=0)
	{
		delete [] _static_array__array_synapses_7_targets;
		_static_array__array_synapses_7_targets = 0;
	}
	if(_static_array__array_synapses_8_sources!=0)
	{
		delete [] _static_array__array_synapses_8_sources;
		_static_array__array_synapses_8_sources = 0;
	}
	if(_static_array__array_synapses_8_targets!=0)
	{
		delete [] _static_array__array_synapses_8_targets;
		_static_array__array_synapses_8_targets = 0;
	}
	if(_static_array__array_synapses_9_sources!=0)
	{
		delete [] _static_array__array_synapses_9_sources;
		_static_array__array_synapses_9_sources = 0;
	}
	if(_static_array__array_synapses_9_targets!=0)
	{
		delete [] _static_array__array_synapses_9_targets;
		_static_array__array_synapses_9_targets = 0;
	}
	if(_static_array__dynamic_array_spikegeneratorgroup__timebins!=0)
	{
		delete [] _static_array__dynamic_array_spikegeneratorgroup__timebins;
		_static_array__dynamic_array_spikegeneratorgroup__timebins = 0;
	}
	if(_static_array__dynamic_array_spikegeneratorgroup_neuron_index!=0)
	{
		delete [] _static_array__dynamic_array_spikegeneratorgroup_neuron_index;
		_static_array__dynamic_array_spikegeneratorgroup_neuron_index = 0;
	}
	if(_static_array__dynamic_array_spikegeneratorgroup_spike_number!=0)
	{
		delete [] _static_array__dynamic_array_spikegeneratorgroup_spike_number;
		_static_array__dynamic_array_spikegeneratorgroup_spike_number = 0;
	}
	if(_static_array__dynamic_array_spikegeneratorgroup_spike_time!=0)
	{
		delete [] _static_array__dynamic_array_spikegeneratorgroup_spike_time;
		_static_array__dynamic_array_spikegeneratorgroup_spike_time = 0;
	}
}

