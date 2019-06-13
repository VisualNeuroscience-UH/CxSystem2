
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
	outfile__array_defaultclock_dt.open("results\\_array_defaultclock_dt_-7941466147850241514", ios::binary | ios::out);
	if(outfile__array_defaultclock_dt.is_open())
	{
		outfile__array_defaultclock_dt.write(reinterpret_cast<char*>(_array_defaultclock_dt), 1*sizeof(_array_defaultclock_dt[0]));
		outfile__array_defaultclock_dt.close();
	} else
	{
		std::cout << "Error writing output file for _array_defaultclock_dt." << endl;
	}
	ofstream outfile__array_defaultclock_t;
	outfile__array_defaultclock_t.open("results\\_array_defaultclock_t_6624538494730556918", ios::binary | ios::out);
	if(outfile__array_defaultclock_t.is_open())
	{
		outfile__array_defaultclock_t.write(reinterpret_cast<char*>(_array_defaultclock_t), 1*sizeof(_array_defaultclock_t[0]));
		outfile__array_defaultclock_t.close();
	} else
	{
		std::cout << "Error writing output file for _array_defaultclock_t." << endl;
	}
	ofstream outfile__array_defaultclock_timestep;
	outfile__array_defaultclock_timestep.open("results\\_array_defaultclock_timestep_1919425164303789151", ios::binary | ios::out);
	if(outfile__array_defaultclock_timestep.is_open())
	{
		outfile__array_defaultclock_timestep.write(reinterpret_cast<char*>(_array_defaultclock_timestep), 1*sizeof(_array_defaultclock_timestep[0]));
		outfile__array_defaultclock_timestep.close();
	} else
	{
		std::cout << "Error writing output file for _array_defaultclock_timestep." << endl;
	}
	ofstream outfile__array_neurongroup_1__spikespace;
	outfile__array_neurongroup_1__spikespace.open("results\\_array_neurongroup_1__spikespace_-4660677612965439397", ios::binary | ios::out);
	if(outfile__array_neurongroup_1__spikespace.is_open())
	{
		outfile__array_neurongroup_1__spikespace.write(reinterpret_cast<char*>(_array_neurongroup_1__spikespace), 268*sizeof(_array_neurongroup_1__spikespace[0]));
		outfile__array_neurongroup_1__spikespace.close();
	} else
	{
		std::cout << "Error writing output file for _array_neurongroup_1__spikespace." << endl;
	}
	ofstream outfile__array_neurongroup_1_ge_a0;
	outfile__array_neurongroup_1_ge_a0.open("results\\_array_neurongroup_1_ge_a0_-55534373274515944", ios::binary | ios::out);
	if(outfile__array_neurongroup_1_ge_a0.is_open())
	{
		outfile__array_neurongroup_1_ge_a0.write(reinterpret_cast<char*>(_array_neurongroup_1_ge_a0), 267*sizeof(_array_neurongroup_1_ge_a0[0]));
		outfile__array_neurongroup_1_ge_a0.close();
	} else
	{
		std::cout << "Error writing output file for _array_neurongroup_1_ge_a0." << endl;
	}
	ofstream outfile__array_neurongroup_1_ge_a1;
	outfile__array_neurongroup_1_ge_a1.open("results\\_array_neurongroup_1_ge_a1_6832167025789751233", ios::binary | ios::out);
	if(outfile__array_neurongroup_1_ge_a1.is_open())
	{
		outfile__array_neurongroup_1_ge_a1.write(reinterpret_cast<char*>(_array_neurongroup_1_ge_a1), 267*sizeof(_array_neurongroup_1_ge_a1[0]));
		outfile__array_neurongroup_1_ge_a1.close();
	} else
	{
		std::cout << "Error writing output file for _array_neurongroup_1_ge_a1." << endl;
	}
	ofstream outfile__array_neurongroup_1_ge_a2;
	outfile__array_neurongroup_1_ge_a2.open("results\\_array_neurongroup_1_ge_a2_-6801097645079849026", ios::binary | ios::out);
	if(outfile__array_neurongroup_1_ge_a2.is_open())
	{
		outfile__array_neurongroup_1_ge_a2.write(reinterpret_cast<char*>(_array_neurongroup_1_ge_a2), 267*sizeof(_array_neurongroup_1_ge_a2[0]));
		outfile__array_neurongroup_1_ge_a2.close();
	} else
	{
		std::cout << "Error writing output file for _array_neurongroup_1_ge_a2." << endl;
	}
	ofstream outfile__array_neurongroup_1_ge_basal;
	outfile__array_neurongroup_1_ge_basal.open("results\\_array_neurongroup_1_ge_basal_-11110298020463892", ios::binary | ios::out);
	if(outfile__array_neurongroup_1_ge_basal.is_open())
	{
		outfile__array_neurongroup_1_ge_basal.write(reinterpret_cast<char*>(_array_neurongroup_1_ge_basal), 267*sizeof(_array_neurongroup_1_ge_basal[0]));
		outfile__array_neurongroup_1_ge_basal.close();
	} else
	{
		std::cout << "Error writing output file for _array_neurongroup_1_ge_basal." << endl;
	}
	ofstream outfile__array_neurongroup_1_ge_soma;
	outfile__array_neurongroup_1_ge_soma.open("results\\_array_neurongroup_1_ge_soma_-981614789078082219", ios::binary | ios::out);
	if(outfile__array_neurongroup_1_ge_soma.is_open())
	{
		outfile__array_neurongroup_1_ge_soma.write(reinterpret_cast<char*>(_array_neurongroup_1_ge_soma), 267*sizeof(_array_neurongroup_1_ge_soma[0]));
		outfile__array_neurongroup_1_ge_soma.close();
	} else
	{
		std::cout << "Error writing output file for _array_neurongroup_1_ge_soma." << endl;
	}
	ofstream outfile__array_neurongroup_1_gealpha_a0;
	outfile__array_neurongroup_1_gealpha_a0.open("results\\_array_neurongroup_1_gealpha_a0_6717249558484986645", ios::binary | ios::out);
	if(outfile__array_neurongroup_1_gealpha_a0.is_open())
	{
		outfile__array_neurongroup_1_gealpha_a0.write(reinterpret_cast<char*>(_array_neurongroup_1_gealpha_a0), 267*sizeof(_array_neurongroup_1_gealpha_a0[0]));
		outfile__array_neurongroup_1_gealpha_a0.close();
	} else
	{
		std::cout << "Error writing output file for _array_neurongroup_1_gealpha_a0." << endl;
	}
	ofstream outfile__array_neurongroup_1_gealpha_a1;
	outfile__array_neurongroup_1_gealpha_a1.open("results\\_array_neurongroup_1_gealpha_a1_-2530787442239820816", ios::binary | ios::out);
	if(outfile__array_neurongroup_1_gealpha_a1.is_open())
	{
		outfile__array_neurongroup_1_gealpha_a1.write(reinterpret_cast<char*>(_array_neurongroup_1_gealpha_a1), 267*sizeof(_array_neurongroup_1_gealpha_a1[0]));
		outfile__array_neurongroup_1_gealpha_a1.close();
	} else
	{
		std::cout << "Error writing output file for _array_neurongroup_1_gealpha_a1." << endl;
	}
	ofstream outfile__array_neurongroup_1_gealpha_a2;
	outfile__array_neurongroup_1_gealpha_a2.open("results\\_array_neurongroup_1_gealpha_a2_-4357154842080452183", ios::binary | ios::out);
	if(outfile__array_neurongroup_1_gealpha_a2.is_open())
	{
		outfile__array_neurongroup_1_gealpha_a2.write(reinterpret_cast<char*>(_array_neurongroup_1_gealpha_a2), 267*sizeof(_array_neurongroup_1_gealpha_a2[0]));
		outfile__array_neurongroup_1_gealpha_a2.close();
	} else
	{
		std::cout << "Error writing output file for _array_neurongroup_1_gealpha_a2." << endl;
	}
	ofstream outfile__array_neurongroup_1_gealpha_basal;
	outfile__array_neurongroup_1_gealpha_basal.open("results\\_array_neurongroup_1_gealpha_basal_8265503964107589088", ios::binary | ios::out);
	if(outfile__array_neurongroup_1_gealpha_basal.is_open())
	{
		outfile__array_neurongroup_1_gealpha_basal.write(reinterpret_cast<char*>(_array_neurongroup_1_gealpha_basal), 267*sizeof(_array_neurongroup_1_gealpha_basal[0]));
		outfile__array_neurongroup_1_gealpha_basal.close();
	} else
	{
		std::cout << "Error writing output file for _array_neurongroup_1_gealpha_basal." << endl;
	}
	ofstream outfile__array_neurongroup_1_gealpha_soma;
	outfile__array_neurongroup_1_gealpha_soma.open("results\\_array_neurongroup_1_gealpha_soma_-3996660462325741708", ios::binary | ios::out);
	if(outfile__array_neurongroup_1_gealpha_soma.is_open())
	{
		outfile__array_neurongroup_1_gealpha_soma.write(reinterpret_cast<char*>(_array_neurongroup_1_gealpha_soma), 267*sizeof(_array_neurongroup_1_gealpha_soma[0]));
		outfile__array_neurongroup_1_gealpha_soma.close();
	} else
	{
		std::cout << "Error writing output file for _array_neurongroup_1_gealpha_soma." << endl;
	}
	ofstream outfile__array_neurongroup_1_gi_a0;
	outfile__array_neurongroup_1_gi_a0.open("results\\_array_neurongroup_1_gi_a0_-16459745037941720", ios::binary | ios::out);
	if(outfile__array_neurongroup_1_gi_a0.is_open())
	{
		outfile__array_neurongroup_1_gi_a0.write(reinterpret_cast<char*>(_array_neurongroup_1_gi_a0), 267*sizeof(_array_neurongroup_1_gi_a0[0]));
		outfile__array_neurongroup_1_gi_a0.close();
	} else
	{
		std::cout << "Error writing output file for _array_neurongroup_1_gi_a0." << endl;
	}
	ofstream outfile__array_neurongroup_1_gi_a1;
	outfile__array_neurongroup_1_gi_a1.open("results\\_array_neurongroup_1_gi_a1_1195433846768693357", ios::binary | ios::out);
	if(outfile__array_neurongroup_1_gi_a1.is_open())
	{
		outfile__array_neurongroup_1_gi_a1.write(reinterpret_cast<char*>(_array_neurongroup_1_gi_a1), 267*sizeof(_array_neurongroup_1_gi_a1[0]));
		outfile__array_neurongroup_1_gi_a1.close();
	} else
	{
		std::cout << "Error writing output file for _array_neurongroup_1_gi_a1." << endl;
	}
	ofstream outfile__array_neurongroup_1_gi_a2;
	outfile__array_neurongroup_1_gi_a2.open("results\\_array_neurongroup_1_gi_a2_2295742882065374575", ios::binary | ios::out);
	if(outfile__array_neurongroup_1_gi_a2.is_open())
	{
		outfile__array_neurongroup_1_gi_a2.write(reinterpret_cast<char*>(_array_neurongroup_1_gi_a2), 267*sizeof(_array_neurongroup_1_gi_a2[0]));
		outfile__array_neurongroup_1_gi_a2.close();
	} else
	{
		std::cout << "Error writing output file for _array_neurongroup_1_gi_a2." << endl;
	}
	ofstream outfile__array_neurongroup_1_gi_basal;
	outfile__array_neurongroup_1_gi_basal.open("results\\_array_neurongroup_1_gi_basal_7291089143049102458", ios::binary | ios::out);
	if(outfile__array_neurongroup_1_gi_basal.is_open())
	{
		outfile__array_neurongroup_1_gi_basal.write(reinterpret_cast<char*>(_array_neurongroup_1_gi_basal), 267*sizeof(_array_neurongroup_1_gi_basal[0]));
		outfile__array_neurongroup_1_gi_basal.close();
	} else
	{
		std::cout << "Error writing output file for _array_neurongroup_1_gi_basal." << endl;
	}
	ofstream outfile__array_neurongroup_1_gi_soma;
	outfile__array_neurongroup_1_gi_soma.open("results\\_array_neurongroup_1_gi_soma_-3377743334057803715", ios::binary | ios::out);
	if(outfile__array_neurongroup_1_gi_soma.is_open())
	{
		outfile__array_neurongroup_1_gi_soma.write(reinterpret_cast<char*>(_array_neurongroup_1_gi_soma), 267*sizeof(_array_neurongroup_1_gi_soma[0]));
		outfile__array_neurongroup_1_gi_soma.close();
	} else
	{
		std::cout << "Error writing output file for _array_neurongroup_1_gi_soma." << endl;
	}
	ofstream outfile__array_neurongroup_1_gialpha_a0;
	outfile__array_neurongroup_1_gialpha_a0.open("results\\_array_neurongroup_1_gialpha_a0_-7836305287212642642", ios::binary | ios::out);
	if(outfile__array_neurongroup_1_gialpha_a0.is_open())
	{
		outfile__array_neurongroup_1_gialpha_a0.write(reinterpret_cast<char*>(_array_neurongroup_1_gialpha_a0), 267*sizeof(_array_neurongroup_1_gialpha_a0[0]));
		outfile__array_neurongroup_1_gialpha_a0.close();
	} else
	{
		std::cout << "Error writing output file for _array_neurongroup_1_gialpha_a0." << endl;
	}
	ofstream outfile__array_neurongroup_1_gialpha_a1;
	outfile__array_neurongroup_1_gialpha_a1.open("results\\_array_neurongroup_1_gialpha_a1_3342049899127530888", ios::binary | ios::out);
	if(outfile__array_neurongroup_1_gialpha_a1.is_open())
	{
		outfile__array_neurongroup_1_gialpha_a1.write(reinterpret_cast<char*>(_array_neurongroup_1_gialpha_a1), 267*sizeof(_array_neurongroup_1_gialpha_a1[0]));
		outfile__array_neurongroup_1_gialpha_a1.close();
	} else
	{
		std::cout << "Error writing output file for _array_neurongroup_1_gialpha_a1." << endl;
	}
	ofstream outfile__array_neurongroup_1_gialpha_a2;
	outfile__array_neurongroup_1_gialpha_a2.open("results\\_array_neurongroup_1_gialpha_a2_7017021366184847638", ios::binary | ios::out);
	if(outfile__array_neurongroup_1_gialpha_a2.is_open())
	{
		outfile__array_neurongroup_1_gialpha_a2.write(reinterpret_cast<char*>(_array_neurongroup_1_gialpha_a2), 267*sizeof(_array_neurongroup_1_gialpha_a2[0]));
		outfile__array_neurongroup_1_gialpha_a2.close();
	} else
	{
		std::cout << "Error writing output file for _array_neurongroup_1_gialpha_a2." << endl;
	}
	ofstream outfile__array_neurongroup_1_gialpha_basal;
	outfile__array_neurongroup_1_gialpha_basal.open("results\\_array_neurongroup_1_gialpha_basal_-8544533485589988274", ios::binary | ios::out);
	if(outfile__array_neurongroup_1_gialpha_basal.is_open())
	{
		outfile__array_neurongroup_1_gialpha_basal.write(reinterpret_cast<char*>(_array_neurongroup_1_gialpha_basal), 267*sizeof(_array_neurongroup_1_gialpha_basal[0]));
		outfile__array_neurongroup_1_gialpha_basal.close();
	} else
	{
		std::cout << "Error writing output file for _array_neurongroup_1_gialpha_basal." << endl;
	}
	ofstream outfile__array_neurongroup_1_gialpha_soma;
	outfile__array_neurongroup_1_gialpha_soma.open("results\\_array_neurongroup_1_gialpha_soma_-5766710175460304964", ios::binary | ios::out);
	if(outfile__array_neurongroup_1_gialpha_soma.is_open())
	{
		outfile__array_neurongroup_1_gialpha_soma.write(reinterpret_cast<char*>(_array_neurongroup_1_gialpha_soma), 267*sizeof(_array_neurongroup_1_gialpha_soma[0]));
		outfile__array_neurongroup_1_gialpha_soma.close();
	} else
	{
		std::cout << "Error writing output file for _array_neurongroup_1_gialpha_soma." << endl;
	}
	ofstream outfile__array_neurongroup_1_i;
	outfile__array_neurongroup_1_i.open("results\\_array_neurongroup_1_i_-3150804520678245284", ios::binary | ios::out);
	if(outfile__array_neurongroup_1_i.is_open())
	{
		outfile__array_neurongroup_1_i.write(reinterpret_cast<char*>(_array_neurongroup_1_i), 267*sizeof(_array_neurongroup_1_i[0]));
		outfile__array_neurongroup_1_i.close();
	} else
	{
		std::cout << "Error writing output file for _array_neurongroup_1_i." << endl;
	}
	ofstream outfile__array_neurongroup_1_lastspike;
	outfile__array_neurongroup_1_lastspike.open("results\\_array_neurongroup_1_lastspike_4271100781605339109", ios::binary | ios::out);
	if(outfile__array_neurongroup_1_lastspike.is_open())
	{
		outfile__array_neurongroup_1_lastspike.write(reinterpret_cast<char*>(_array_neurongroup_1_lastspike), 267*sizeof(_array_neurongroup_1_lastspike[0]));
		outfile__array_neurongroup_1_lastspike.close();
	} else
	{
		std::cout << "Error writing output file for _array_neurongroup_1_lastspike." << endl;
	}
	ofstream outfile__array_neurongroup_1_not_refractory;
	outfile__array_neurongroup_1_not_refractory.open("results\\_array_neurongroup_1_not_refractory_6479783472185041722", ios::binary | ios::out);
	if(outfile__array_neurongroup_1_not_refractory.is_open())
	{
		outfile__array_neurongroup_1_not_refractory.write(reinterpret_cast<char*>(_array_neurongroup_1_not_refractory), 267*sizeof(_array_neurongroup_1_not_refractory[0]));
		outfile__array_neurongroup_1_not_refractory.close();
	} else
	{
		std::cout << "Error writing output file for _array_neurongroup_1_not_refractory." << endl;
	}
	ofstream outfile__array_neurongroup_1_vm;
	outfile__array_neurongroup_1_vm.open("results\\_array_neurongroup_1_vm_5093162417819806351", ios::binary | ios::out);
	if(outfile__array_neurongroup_1_vm.is_open())
	{
		outfile__array_neurongroup_1_vm.write(reinterpret_cast<char*>(_array_neurongroup_1_vm), 267*sizeof(_array_neurongroup_1_vm[0]));
		outfile__array_neurongroup_1_vm.close();
	} else
	{
		std::cout << "Error writing output file for _array_neurongroup_1_vm." << endl;
	}
	ofstream outfile__array_neurongroup_1_vm_a0;
	outfile__array_neurongroup_1_vm_a0.open("results\\_array_neurongroup_1_vm_a0_4772371007655864840", ios::binary | ios::out);
	if(outfile__array_neurongroup_1_vm_a0.is_open())
	{
		outfile__array_neurongroup_1_vm_a0.write(reinterpret_cast<char*>(_array_neurongroup_1_vm_a0), 267*sizeof(_array_neurongroup_1_vm_a0[0]));
		outfile__array_neurongroup_1_vm_a0.close();
	} else
	{
		std::cout << "Error writing output file for _array_neurongroup_1_vm_a0." << endl;
	}
	ofstream outfile__array_neurongroup_1_vm_a1;
	outfile__array_neurongroup_1_vm_a1.open("results\\_array_neurongroup_1_vm_a1_-3983252541283166627", ios::binary | ios::out);
	if(outfile__array_neurongroup_1_vm_a1.is_open())
	{
		outfile__array_neurongroup_1_vm_a1.write(reinterpret_cast<char*>(_array_neurongroup_1_vm_a1), 267*sizeof(_array_neurongroup_1_vm_a1[0]));
		outfile__array_neurongroup_1_vm_a1.close();
	} else
	{
		std::cout << "Error writing output file for _array_neurongroup_1_vm_a1." << endl;
	}
	ofstream outfile__array_neurongroup_1_vm_a2;
	outfile__array_neurongroup_1_vm_a2.open("results\\_array_neurongroup_1_vm_a2_-7933907824877055177", ios::binary | ios::out);
	if(outfile__array_neurongroup_1_vm_a2.is_open())
	{
		outfile__array_neurongroup_1_vm_a2.write(reinterpret_cast<char*>(_array_neurongroup_1_vm_a2), 267*sizeof(_array_neurongroup_1_vm_a2[0]));
		outfile__array_neurongroup_1_vm_a2.close();
	} else
	{
		std::cout << "Error writing output file for _array_neurongroup_1_vm_a2." << endl;
	}
	ofstream outfile__array_neurongroup_1_vm_basal;
	outfile__array_neurongroup_1_vm_basal.open("results\\_array_neurongroup_1_vm_basal_2397466875703415597", ios::binary | ios::out);
	if(outfile__array_neurongroup_1_vm_basal.is_open())
	{
		outfile__array_neurongroup_1_vm_basal.write(reinterpret_cast<char*>(_array_neurongroup_1_vm_basal), 267*sizeof(_array_neurongroup_1_vm_basal[0]));
		outfile__array_neurongroup_1_vm_basal.close();
	} else
	{
		std::cout << "Error writing output file for _array_neurongroup_1_vm_basal." << endl;
	}
	ofstream outfile__array_neurongroup_1_x;
	outfile__array_neurongroup_1_x.open("results\\_array_neurongroup_1_x_-5443473540141582830", ios::binary | ios::out);
	if(outfile__array_neurongroup_1_x.is_open())
	{
		outfile__array_neurongroup_1_x.write(reinterpret_cast<char*>(_array_neurongroup_1_x), 267*sizeof(_array_neurongroup_1_x[0]));
		outfile__array_neurongroup_1_x.close();
	} else
	{
		std::cout << "Error writing output file for _array_neurongroup_1_x." << endl;
	}
	ofstream outfile__array_neurongroup_1_y;
	outfile__array_neurongroup_1_y.open("results\\_array_neurongroup_1_y_-5828162271952574631", ios::binary | ios::out);
	if(outfile__array_neurongroup_1_y.is_open())
	{
		outfile__array_neurongroup_1_y.write(reinterpret_cast<char*>(_array_neurongroup_1_y), 267*sizeof(_array_neurongroup_1_y[0]));
		outfile__array_neurongroup_1_y.close();
	} else
	{
		std::cout << "Error writing output file for _array_neurongroup_1_y." << endl;
	}
	ofstream outfile__array_neurongroup_2__spikespace;
	outfile__array_neurongroup_2__spikespace.open("results\\_array_neurongroup_2__spikespace_-7875640825751932408", ios::binary | ios::out);
	if(outfile__array_neurongroup_2__spikespace.is_open())
	{
		outfile__array_neurongroup_2__spikespace.write(reinterpret_cast<char*>(_array_neurongroup_2__spikespace), 110*sizeof(_array_neurongroup_2__spikespace[0]));
		outfile__array_neurongroup_2__spikespace.close();
	} else
	{
		std::cout << "Error writing output file for _array_neurongroup_2__spikespace." << endl;
	}
	ofstream outfile__array_neurongroup_2_ge_a0;
	outfile__array_neurongroup_2_ge_a0.open("results\\_array_neurongroup_2_ge_a0_-3505918375887535992", ios::binary | ios::out);
	if(outfile__array_neurongroup_2_ge_a0.is_open())
	{
		outfile__array_neurongroup_2_ge_a0.write(reinterpret_cast<char*>(_array_neurongroup_2_ge_a0), 109*sizeof(_array_neurongroup_2_ge_a0[0]));
		outfile__array_neurongroup_2_ge_a0.close();
	} else
	{
		std::cout << "Error writing output file for _array_neurongroup_2_ge_a0." << endl;
	}
	ofstream outfile__array_neurongroup_2_ge_a1;
	outfile__array_neurongroup_2_ge_a1.open("results\\_array_neurongroup_2_ge_a1_1958009760452018376", ios::binary | ios::out);
	if(outfile__array_neurongroup_2_ge_a1.is_open())
	{
		outfile__array_neurongroup_2_ge_a1.write(reinterpret_cast<char*>(_array_neurongroup_2_ge_a1), 109*sizeof(_array_neurongroup_2_ge_a1[0]));
		outfile__array_neurongroup_2_ge_a1.close();
	} else
	{
		std::cout << "Error writing output file for _array_neurongroup_2_ge_a1." << endl;
	}
	ofstream outfile__array_neurongroup_2_ge_a2;
	outfile__array_neurongroup_2_ge_a2.open("results\\_array_neurongroup_2_ge_a2_-5439003161511856080", ios::binary | ios::out);
	if(outfile__array_neurongroup_2_ge_a2.is_open())
	{
		outfile__array_neurongroup_2_ge_a2.write(reinterpret_cast<char*>(_array_neurongroup_2_ge_a2), 109*sizeof(_array_neurongroup_2_ge_a2[0]));
		outfile__array_neurongroup_2_ge_a2.close();
	} else
	{
		std::cout << "Error writing output file for _array_neurongroup_2_ge_a2." << endl;
	}
	ofstream outfile__array_neurongroup_2_ge_basal;
	outfile__array_neurongroup_2_ge_basal.open("results\\_array_neurongroup_2_ge_basal_-4474101594565769041", ios::binary | ios::out);
	if(outfile__array_neurongroup_2_ge_basal.is_open())
	{
		outfile__array_neurongroup_2_ge_basal.write(reinterpret_cast<char*>(_array_neurongroup_2_ge_basal), 109*sizeof(_array_neurongroup_2_ge_basal[0]));
		outfile__array_neurongroup_2_ge_basal.close();
	} else
	{
		std::cout << "Error writing output file for _array_neurongroup_2_ge_basal." << endl;
	}
	ofstream outfile__array_neurongroup_2_ge_soma;
	outfile__array_neurongroup_2_ge_soma.open("results\\_array_neurongroup_2_ge_soma_8703539055164124431", ios::binary | ios::out);
	if(outfile__array_neurongroup_2_ge_soma.is_open())
	{
		outfile__array_neurongroup_2_ge_soma.write(reinterpret_cast<char*>(_array_neurongroup_2_ge_soma), 109*sizeof(_array_neurongroup_2_ge_soma[0]));
		outfile__array_neurongroup_2_ge_soma.close();
	} else
	{
		std::cout << "Error writing output file for _array_neurongroup_2_ge_soma." << endl;
	}
	ofstream outfile__array_neurongroup_2_gealpha_a0;
	outfile__array_neurongroup_2_gealpha_a0.open("results\\_array_neurongroup_2_gealpha_a0_328043695310375954", ios::binary | ios::out);
	if(outfile__array_neurongroup_2_gealpha_a0.is_open())
	{
		outfile__array_neurongroup_2_gealpha_a0.write(reinterpret_cast<char*>(_array_neurongroup_2_gealpha_a0), 109*sizeof(_array_neurongroup_2_gealpha_a0[0]));
		outfile__array_neurongroup_2_gealpha_a0.close();
	} else
	{
		std::cout << "Error writing output file for _array_neurongroup_2_gealpha_a0." << endl;
	}
	ofstream outfile__array_neurongroup_2_gealpha_a1;
	outfile__array_neurongroup_2_gealpha_a1.open("results\\_array_neurongroup_2_gealpha_a1_-1998655631967583970", ios::binary | ios::out);
	if(outfile__array_neurongroup_2_gealpha_a1.is_open())
	{
		outfile__array_neurongroup_2_gealpha_a1.write(reinterpret_cast<char*>(_array_neurongroup_2_gealpha_a1), 109*sizeof(_array_neurongroup_2_gealpha_a1[0]));
		outfile__array_neurongroup_2_gealpha_a1.close();
	} else
	{
		std::cout << "Error writing output file for _array_neurongroup_2_gealpha_a1." << endl;
	}
	ofstream outfile__array_neurongroup_2_gealpha_a2;
	outfile__array_neurongroup_2_gealpha_a2.open("results\\_array_neurongroup_2_gealpha_a2_1165870880797966903", ios::binary | ios::out);
	if(outfile__array_neurongroup_2_gealpha_a2.is_open())
	{
		outfile__array_neurongroup_2_gealpha_a2.write(reinterpret_cast<char*>(_array_neurongroup_2_gealpha_a2), 109*sizeof(_array_neurongroup_2_gealpha_a2[0]));
		outfile__array_neurongroup_2_gealpha_a2.close();
	} else
	{
		std::cout << "Error writing output file for _array_neurongroup_2_gealpha_a2." << endl;
	}
	ofstream outfile__array_neurongroup_2_gealpha_basal;
	outfile__array_neurongroup_2_gealpha_basal.open("results\\_array_neurongroup_2_gealpha_basal_-4742572174613555956", ios::binary | ios::out);
	if(outfile__array_neurongroup_2_gealpha_basal.is_open())
	{
		outfile__array_neurongroup_2_gealpha_basal.write(reinterpret_cast<char*>(_array_neurongroup_2_gealpha_basal), 109*sizeof(_array_neurongroup_2_gealpha_basal[0]));
		outfile__array_neurongroup_2_gealpha_basal.close();
	} else
	{
		std::cout << "Error writing output file for _array_neurongroup_2_gealpha_basal." << endl;
	}
	ofstream outfile__array_neurongroup_2_gealpha_soma;
	outfile__array_neurongroup_2_gealpha_soma.open("results\\_array_neurongroup_2_gealpha_soma_-1207549803633667448", ios::binary | ios::out);
	if(outfile__array_neurongroup_2_gealpha_soma.is_open())
	{
		outfile__array_neurongroup_2_gealpha_soma.write(reinterpret_cast<char*>(_array_neurongroup_2_gealpha_soma), 109*sizeof(_array_neurongroup_2_gealpha_soma[0]));
		outfile__array_neurongroup_2_gealpha_soma.close();
	} else
	{
		std::cout << "Error writing output file for _array_neurongroup_2_gealpha_soma." << endl;
	}
	ofstream outfile__array_neurongroup_2_gi_a0;
	outfile__array_neurongroup_2_gi_a0.open("results\\_array_neurongroup_2_gi_a0_-715018224315233578", ios::binary | ios::out);
	if(outfile__array_neurongroup_2_gi_a0.is_open())
	{
		outfile__array_neurongroup_2_gi_a0.write(reinterpret_cast<char*>(_array_neurongroup_2_gi_a0), 109*sizeof(_array_neurongroup_2_gi_a0[0]));
		outfile__array_neurongroup_2_gi_a0.close();
	} else
	{
		std::cout << "Error writing output file for _array_neurongroup_2_gi_a0." << endl;
	}
	ofstream outfile__array_neurongroup_2_gi_a1;
	outfile__array_neurongroup_2_gi_a1.open("results\\_array_neurongroup_2_gi_a1_-4572175882457116292", ios::binary | ios::out);
	if(outfile__array_neurongroup_2_gi_a1.is_open())
	{
		outfile__array_neurongroup_2_gi_a1.write(reinterpret_cast<char*>(_array_neurongroup_2_gi_a1), 109*sizeof(_array_neurongroup_2_gi_a1[0]));
		outfile__array_neurongroup_2_gi_a1.close();
	} else
	{
		std::cout << "Error writing output file for _array_neurongroup_2_gi_a1." << endl;
	}
	ofstream outfile__array_neurongroup_2_gi_a2;
	outfile__array_neurongroup_2_gi_a2.open("results\\_array_neurongroup_2_gi_a2_-8486126350515438326", ios::binary | ios::out);
	if(outfile__array_neurongroup_2_gi_a2.is_open())
	{
		outfile__array_neurongroup_2_gi_a2.write(reinterpret_cast<char*>(_array_neurongroup_2_gi_a2), 109*sizeof(_array_neurongroup_2_gi_a2[0]));
		outfile__array_neurongroup_2_gi_a2.close();
	} else
	{
		std::cout << "Error writing output file for _array_neurongroup_2_gi_a2." << endl;
	}
	ofstream outfile__array_neurongroup_2_gi_basal;
	outfile__array_neurongroup_2_gi_basal.open("results\\_array_neurongroup_2_gi_basal_1180390112127413573", ios::binary | ios::out);
	if(outfile__array_neurongroup_2_gi_basal.is_open())
	{
		outfile__array_neurongroup_2_gi_basal.write(reinterpret_cast<char*>(_array_neurongroup_2_gi_basal), 109*sizeof(_array_neurongroup_2_gi_basal[0]));
		outfile__array_neurongroup_2_gi_basal.close();
	} else
	{
		std::cout << "Error writing output file for _array_neurongroup_2_gi_basal." << endl;
	}
	ofstream outfile__array_neurongroup_2_gi_soma;
	outfile__array_neurongroup_2_gi_soma.open("results\\_array_neurongroup_2_gi_soma_-1273291018122015965", ios::binary | ios::out);
	if(outfile__array_neurongroup_2_gi_soma.is_open())
	{
		outfile__array_neurongroup_2_gi_soma.write(reinterpret_cast<char*>(_array_neurongroup_2_gi_soma), 109*sizeof(_array_neurongroup_2_gi_soma[0]));
		outfile__array_neurongroup_2_gi_soma.close();
	} else
	{
		std::cout << "Error writing output file for _array_neurongroup_2_gi_soma." << endl;
	}
	ofstream outfile__array_neurongroup_2_gialpha_a0;
	outfile__array_neurongroup_2_gialpha_a0.open("results\\_array_neurongroup_2_gialpha_a0_-79657171156846344", ios::binary | ios::out);
	if(outfile__array_neurongroup_2_gialpha_a0.is_open())
	{
		outfile__array_neurongroup_2_gialpha_a0.write(reinterpret_cast<char*>(_array_neurongroup_2_gialpha_a0), 109*sizeof(_array_neurongroup_2_gialpha_a0[0]));
		outfile__array_neurongroup_2_gialpha_a0.close();
	} else
	{
		std::cout << "Error writing output file for _array_neurongroup_2_gialpha_a0." << endl;
	}
	ofstream outfile__array_neurongroup_2_gialpha_a1;
	outfile__array_neurongroup_2_gialpha_a1.open("results\\_array_neurongroup_2_gialpha_a1_3105657685203496327", ios::binary | ios::out);
	if(outfile__array_neurongroup_2_gialpha_a1.is_open())
	{
		outfile__array_neurongroup_2_gialpha_a1.write(reinterpret_cast<char*>(_array_neurongroup_2_gialpha_a1), 109*sizeof(_array_neurongroup_2_gialpha_a1[0]));
		outfile__array_neurongroup_2_gialpha_a1.close();
	} else
	{
		std::cout << "Error writing output file for _array_neurongroup_2_gialpha_a1." << endl;
	}
	ofstream outfile__array_neurongroup_2_gialpha_a2;
	outfile__array_neurongroup_2_gialpha_a2.open("results\\_array_neurongroup_2_gialpha_a2_-449502838972081368", ios::binary | ios::out);
	if(outfile__array_neurongroup_2_gialpha_a2.is_open())
	{
		outfile__array_neurongroup_2_gialpha_a2.write(reinterpret_cast<char*>(_array_neurongroup_2_gialpha_a2), 109*sizeof(_array_neurongroup_2_gialpha_a2[0]));
		outfile__array_neurongroup_2_gialpha_a2.close();
	} else
	{
		std::cout << "Error writing output file for _array_neurongroup_2_gialpha_a2." << endl;
	}
	ofstream outfile__array_neurongroup_2_gialpha_basal;
	outfile__array_neurongroup_2_gialpha_basal.open("results\\_array_neurongroup_2_gialpha_basal_4345627443400782767", ios::binary | ios::out);
	if(outfile__array_neurongroup_2_gialpha_basal.is_open())
	{
		outfile__array_neurongroup_2_gialpha_basal.write(reinterpret_cast<char*>(_array_neurongroup_2_gialpha_basal), 109*sizeof(_array_neurongroup_2_gialpha_basal[0]));
		outfile__array_neurongroup_2_gialpha_basal.close();
	} else
	{
		std::cout << "Error writing output file for _array_neurongroup_2_gialpha_basal." << endl;
	}
	ofstream outfile__array_neurongroup_2_gialpha_soma;
	outfile__array_neurongroup_2_gialpha_soma.open("results\\_array_neurongroup_2_gialpha_soma_6137337754388750091", ios::binary | ios::out);
	if(outfile__array_neurongroup_2_gialpha_soma.is_open())
	{
		outfile__array_neurongroup_2_gialpha_soma.write(reinterpret_cast<char*>(_array_neurongroup_2_gialpha_soma), 109*sizeof(_array_neurongroup_2_gialpha_soma[0]));
		outfile__array_neurongroup_2_gialpha_soma.close();
	} else
	{
		std::cout << "Error writing output file for _array_neurongroup_2_gialpha_soma." << endl;
	}
	ofstream outfile__array_neurongroup_2_i;
	outfile__array_neurongroup_2_i.open("results\\_array_neurongroup_2_i_5856076903927948714", ios::binary | ios::out);
	if(outfile__array_neurongroup_2_i.is_open())
	{
		outfile__array_neurongroup_2_i.write(reinterpret_cast<char*>(_array_neurongroup_2_i), 109*sizeof(_array_neurongroup_2_i[0]));
		outfile__array_neurongroup_2_i.close();
	} else
	{
		std::cout << "Error writing output file for _array_neurongroup_2_i." << endl;
	}
	ofstream outfile__array_neurongroup_2_lastspike;
	outfile__array_neurongroup_2_lastspike.open("results\\_array_neurongroup_2_lastspike_-8558974055424946706", ios::binary | ios::out);
	if(outfile__array_neurongroup_2_lastspike.is_open())
	{
		outfile__array_neurongroup_2_lastspike.write(reinterpret_cast<char*>(_array_neurongroup_2_lastspike), 109*sizeof(_array_neurongroup_2_lastspike[0]));
		outfile__array_neurongroup_2_lastspike.close();
	} else
	{
		std::cout << "Error writing output file for _array_neurongroup_2_lastspike." << endl;
	}
	ofstream outfile__array_neurongroup_2_not_refractory;
	outfile__array_neurongroup_2_not_refractory.open("results\\_array_neurongroup_2_not_refractory_-3203329766200271659", ios::binary | ios::out);
	if(outfile__array_neurongroup_2_not_refractory.is_open())
	{
		outfile__array_neurongroup_2_not_refractory.write(reinterpret_cast<char*>(_array_neurongroup_2_not_refractory), 109*sizeof(_array_neurongroup_2_not_refractory[0]));
		outfile__array_neurongroup_2_not_refractory.close();
	} else
	{
		std::cout << "Error writing output file for _array_neurongroup_2_not_refractory." << endl;
	}
	ofstream outfile__array_neurongroup_2_vm;
	outfile__array_neurongroup_2_vm.open("results\\_array_neurongroup_2_vm_4913662739610181848", ios::binary | ios::out);
	if(outfile__array_neurongroup_2_vm.is_open())
	{
		outfile__array_neurongroup_2_vm.write(reinterpret_cast<char*>(_array_neurongroup_2_vm), 109*sizeof(_array_neurongroup_2_vm[0]));
		outfile__array_neurongroup_2_vm.close();
	} else
	{
		std::cout << "Error writing output file for _array_neurongroup_2_vm." << endl;
	}
	ofstream outfile__array_neurongroup_2_vm_a0;
	outfile__array_neurongroup_2_vm_a0.open("results\\_array_neurongroup_2_vm_a0_-5681525100987254403", ios::binary | ios::out);
	if(outfile__array_neurongroup_2_vm_a0.is_open())
	{
		outfile__array_neurongroup_2_vm_a0.write(reinterpret_cast<char*>(_array_neurongroup_2_vm_a0), 109*sizeof(_array_neurongroup_2_vm_a0[0]));
		outfile__array_neurongroup_2_vm_a0.close();
	} else
	{
		std::cout << "Error writing output file for _array_neurongroup_2_vm_a0." << endl;
	}
	ofstream outfile__array_neurongroup_2_vm_a1;
	outfile__array_neurongroup_2_vm_a1.open("results\\_array_neurongroup_2_vm_a1_-5362682639259806899", ios::binary | ios::out);
	if(outfile__array_neurongroup_2_vm_a1.is_open())
	{
		outfile__array_neurongroup_2_vm_a1.write(reinterpret_cast<char*>(_array_neurongroup_2_vm_a1), 109*sizeof(_array_neurongroup_2_vm_a1[0]));
		outfile__array_neurongroup_2_vm_a1.close();
	} else
	{
		std::cout << "Error writing output file for _array_neurongroup_2_vm_a1." << endl;
	}
	ofstream outfile__array_neurongroup_2_vm_a2;
	outfile__array_neurongroup_2_vm_a2.open("results\\_array_neurongroup_2_vm_a2_-5652153919999354127", ios::binary | ios::out);
	if(outfile__array_neurongroup_2_vm_a2.is_open())
	{
		outfile__array_neurongroup_2_vm_a2.write(reinterpret_cast<char*>(_array_neurongroup_2_vm_a2), 109*sizeof(_array_neurongroup_2_vm_a2[0]));
		outfile__array_neurongroup_2_vm_a2.close();
	} else
	{
		std::cout << "Error writing output file for _array_neurongroup_2_vm_a2." << endl;
	}
	ofstream outfile__array_neurongroup_2_vm_basal;
	outfile__array_neurongroup_2_vm_basal.open("results\\_array_neurongroup_2_vm_basal_-6049436016972707388", ios::binary | ios::out);
	if(outfile__array_neurongroup_2_vm_basal.is_open())
	{
		outfile__array_neurongroup_2_vm_basal.write(reinterpret_cast<char*>(_array_neurongroup_2_vm_basal), 109*sizeof(_array_neurongroup_2_vm_basal[0]));
		outfile__array_neurongroup_2_vm_basal.close();
	} else
	{
		std::cout << "Error writing output file for _array_neurongroup_2_vm_basal." << endl;
	}
	ofstream outfile__array_neurongroup_2_x;
	outfile__array_neurongroup_2_x.open("results\\_array_neurongroup_2_x_-7062293435095704044", ios::binary | ios::out);
	if(outfile__array_neurongroup_2_x.is_open())
	{
		outfile__array_neurongroup_2_x.write(reinterpret_cast<char*>(_array_neurongroup_2_x), 109*sizeof(_array_neurongroup_2_x[0]));
		outfile__array_neurongroup_2_x.close();
	} else
	{
		std::cout << "Error writing output file for _array_neurongroup_2_x." << endl;
	}
	ofstream outfile__array_neurongroup_2_y;
	outfile__array_neurongroup_2_y.open("results\\_array_neurongroup_2_y_2551159555877147581", ios::binary | ios::out);
	if(outfile__array_neurongroup_2_y.is_open())
	{
		outfile__array_neurongroup_2_y.write(reinterpret_cast<char*>(_array_neurongroup_2_y), 109*sizeof(_array_neurongroup_2_y[0]));
		outfile__array_neurongroup_2_y.close();
	} else
	{
		std::cout << "Error writing output file for _array_neurongroup_2_y." << endl;
	}
	ofstream outfile__array_neurongroup_3__spikespace;
	outfile__array_neurongroup_3__spikespace.open("results\\_array_neurongroup_3__spikespace_5540312381805051202", ios::binary | ios::out);
	if(outfile__array_neurongroup_3__spikespace.is_open())
	{
		outfile__array_neurongroup_3__spikespace.write(reinterpret_cast<char*>(_array_neurongroup_3__spikespace), 41*sizeof(_array_neurongroup_3__spikespace[0]));
		outfile__array_neurongroup_3__spikespace.close();
	} else
	{
		std::cout << "Error writing output file for _array_neurongroup_3__spikespace." << endl;
	}
	ofstream outfile__array_neurongroup_3_ge_soma;
	outfile__array_neurongroup_3_ge_soma.open("results\\_array_neurongroup_3_ge_soma_7972370838701972931", ios::binary | ios::out);
	if(outfile__array_neurongroup_3_ge_soma.is_open())
	{
		outfile__array_neurongroup_3_ge_soma.write(reinterpret_cast<char*>(_array_neurongroup_3_ge_soma), 40*sizeof(_array_neurongroup_3_ge_soma[0]));
		outfile__array_neurongroup_3_ge_soma.close();
	} else
	{
		std::cout << "Error writing output file for _array_neurongroup_3_ge_soma." << endl;
	}
	ofstream outfile__array_neurongroup_3_gi_soma;
	outfile__array_neurongroup_3_gi_soma.open("results\\_array_neurongroup_3_gi_soma_2272111926698772853", ios::binary | ios::out);
	if(outfile__array_neurongroup_3_gi_soma.is_open())
	{
		outfile__array_neurongroup_3_gi_soma.write(reinterpret_cast<char*>(_array_neurongroup_3_gi_soma), 40*sizeof(_array_neurongroup_3_gi_soma[0]));
		outfile__array_neurongroup_3_gi_soma.close();
	} else
	{
		std::cout << "Error writing output file for _array_neurongroup_3_gi_soma." << endl;
	}
	ofstream outfile__array_neurongroup_3_i;
	outfile__array_neurongroup_3_i.open("results\\_array_neurongroup_3_i_8667284331803718538", ios::binary | ios::out);
	if(outfile__array_neurongroup_3_i.is_open())
	{
		outfile__array_neurongroup_3_i.write(reinterpret_cast<char*>(_array_neurongroup_3_i), 40*sizeof(_array_neurongroup_3_i[0]));
		outfile__array_neurongroup_3_i.close();
	} else
	{
		std::cout << "Error writing output file for _array_neurongroup_3_i." << endl;
	}
	ofstream outfile__array_neurongroup_3_lastspike;
	outfile__array_neurongroup_3_lastspike.open("results\\_array_neurongroup_3_lastspike_7946387908332837982", ios::binary | ios::out);
	if(outfile__array_neurongroup_3_lastspike.is_open())
	{
		outfile__array_neurongroup_3_lastspike.write(reinterpret_cast<char*>(_array_neurongroup_3_lastspike), 40*sizeof(_array_neurongroup_3_lastspike[0]));
		outfile__array_neurongroup_3_lastspike.close();
	} else
	{
		std::cout << "Error writing output file for _array_neurongroup_3_lastspike." << endl;
	}
	ofstream outfile__array_neurongroup_3_not_refractory;
	outfile__array_neurongroup_3_not_refractory.open("results\\_array_neurongroup_3_not_refractory_-7358152163278777085", ios::binary | ios::out);
	if(outfile__array_neurongroup_3_not_refractory.is_open())
	{
		outfile__array_neurongroup_3_not_refractory.write(reinterpret_cast<char*>(_array_neurongroup_3_not_refractory), 40*sizeof(_array_neurongroup_3_not_refractory[0]));
		outfile__array_neurongroup_3_not_refractory.close();
	} else
	{
		std::cout << "Error writing output file for _array_neurongroup_3_not_refractory." << endl;
	}
	ofstream outfile__array_neurongroup_3_vm;
	outfile__array_neurongroup_3_vm.open("results\\_array_neurongroup_3_vm_6562429466414798672", ios::binary | ios::out);
	if(outfile__array_neurongroup_3_vm.is_open())
	{
		outfile__array_neurongroup_3_vm.write(reinterpret_cast<char*>(_array_neurongroup_3_vm), 40*sizeof(_array_neurongroup_3_vm[0]));
		outfile__array_neurongroup_3_vm.close();
	} else
	{
		std::cout << "Error writing output file for _array_neurongroup_3_vm." << endl;
	}
	ofstream outfile__array_neurongroup_3_x;
	outfile__array_neurongroup_3_x.open("results\\_array_neurongroup_3_x_3615456371974895877", ios::binary | ios::out);
	if(outfile__array_neurongroup_3_x.is_open())
	{
		outfile__array_neurongroup_3_x.write(reinterpret_cast<char*>(_array_neurongroup_3_x), 40*sizeof(_array_neurongroup_3_x[0]));
		outfile__array_neurongroup_3_x.close();
	} else
	{
		std::cout << "Error writing output file for _array_neurongroup_3_x." << endl;
	}
	ofstream outfile__array_neurongroup_3_y;
	outfile__array_neurongroup_3_y.open("results\\_array_neurongroup_3_y_-385510382756529355", ios::binary | ios::out);
	if(outfile__array_neurongroup_3_y.is_open())
	{
		outfile__array_neurongroup_3_y.write(reinterpret_cast<char*>(_array_neurongroup_3_y), 40*sizeof(_array_neurongroup_3_y[0]));
		outfile__array_neurongroup_3_y.close();
	} else
	{
		std::cout << "Error writing output file for _array_neurongroup_3_y." << endl;
	}
	ofstream outfile__array_neurongroup_4__spikespace;
	outfile__array_neurongroup_4__spikespace.open("results\\_array_neurongroup_4__spikespace_2260884869052135030", ios::binary | ios::out);
	if(outfile__array_neurongroup_4__spikespace.is_open())
	{
		outfile__array_neurongroup_4__spikespace.write(reinterpret_cast<char*>(_array_neurongroup_4__spikespace), 33*sizeof(_array_neurongroup_4__spikespace[0]));
		outfile__array_neurongroup_4__spikespace.close();
	} else
	{
		std::cout << "Error writing output file for _array_neurongroup_4__spikespace." << endl;
	}
	ofstream outfile__array_neurongroup_4_ge_soma;
	outfile__array_neurongroup_4_ge_soma.open("results\\_array_neurongroup_4_ge_soma_-1982654677727404171", ios::binary | ios::out);
	if(outfile__array_neurongroup_4_ge_soma.is_open())
	{
		outfile__array_neurongroup_4_ge_soma.write(reinterpret_cast<char*>(_array_neurongroup_4_ge_soma), 32*sizeof(_array_neurongroup_4_ge_soma[0]));
		outfile__array_neurongroup_4_ge_soma.close();
	} else
	{
		std::cout << "Error writing output file for _array_neurongroup_4_ge_soma." << endl;
	}
	ofstream outfile__array_neurongroup_4_gi_soma;
	outfile__array_neurongroup_4_gi_soma.open("results\\_array_neurongroup_4_gi_soma_8487108175424313334", ios::binary | ios::out);
	if(outfile__array_neurongroup_4_gi_soma.is_open())
	{
		outfile__array_neurongroup_4_gi_soma.write(reinterpret_cast<char*>(_array_neurongroup_4_gi_soma), 32*sizeof(_array_neurongroup_4_gi_soma[0]));
		outfile__array_neurongroup_4_gi_soma.close();
	} else
	{
		std::cout << "Error writing output file for _array_neurongroup_4_gi_soma." << endl;
	}
	ofstream outfile__array_neurongroup_4_i;
	outfile__array_neurongroup_4_i.open("results\\_array_neurongroup_4_i_-46183925562969860", ios::binary | ios::out);
	if(outfile__array_neurongroup_4_i.is_open())
	{
		outfile__array_neurongroup_4_i.write(reinterpret_cast<char*>(_array_neurongroup_4_i), 32*sizeof(_array_neurongroup_4_i[0]));
		outfile__array_neurongroup_4_i.close();
	} else
	{
		std::cout << "Error writing output file for _array_neurongroup_4_i." << endl;
	}
	ofstream outfile__array_neurongroup_4_lastspike;
	outfile__array_neurongroup_4_lastspike.open("results\\_array_neurongroup_4_lastspike_-6058800031581091383", ios::binary | ios::out);
	if(outfile__array_neurongroup_4_lastspike.is_open())
	{
		outfile__array_neurongroup_4_lastspike.write(reinterpret_cast<char*>(_array_neurongroup_4_lastspike), 32*sizeof(_array_neurongroup_4_lastspike[0]));
		outfile__array_neurongroup_4_lastspike.close();
	} else
	{
		std::cout << "Error writing output file for _array_neurongroup_4_lastspike." << endl;
	}
	ofstream outfile__array_neurongroup_4_not_refractory;
	outfile__array_neurongroup_4_not_refractory.open("results\\_array_neurongroup_4_not_refractory_926898101780303592", ios::binary | ios::out);
	if(outfile__array_neurongroup_4_not_refractory.is_open())
	{
		outfile__array_neurongroup_4_not_refractory.write(reinterpret_cast<char*>(_array_neurongroup_4_not_refractory), 32*sizeof(_array_neurongroup_4_not_refractory[0]));
		outfile__array_neurongroup_4_not_refractory.close();
	} else
	{
		std::cout << "Error writing output file for _array_neurongroup_4_not_refractory." << endl;
	}
	ofstream outfile__array_neurongroup_4_vm;
	outfile__array_neurongroup_4_vm.open("results\\_array_neurongroup_4_vm_2516885137899803453", ios::binary | ios::out);
	if(outfile__array_neurongroup_4_vm.is_open())
	{
		outfile__array_neurongroup_4_vm.write(reinterpret_cast<char*>(_array_neurongroup_4_vm), 32*sizeof(_array_neurongroup_4_vm[0]));
		outfile__array_neurongroup_4_vm.close();
	} else
	{
		std::cout << "Error writing output file for _array_neurongroup_4_vm." << endl;
	}
	ofstream outfile__array_neurongroup_4_x;
	outfile__array_neurongroup_4_x.open("results\\_array_neurongroup_4_x_1615184257645114436", ios::binary | ios::out);
	if(outfile__array_neurongroup_4_x.is_open())
	{
		outfile__array_neurongroup_4_x.write(reinterpret_cast<char*>(_array_neurongroup_4_x), 32*sizeof(_array_neurongroup_4_x[0]));
		outfile__array_neurongroup_4_x.close();
	} else
	{
		std::cout << "Error writing output file for _array_neurongroup_4_x." << endl;
	}
	ofstream outfile__array_neurongroup_4_y;
	outfile__array_neurongroup_4_y.open("results\\_array_neurongroup_4_y_-6723513169383686594", ios::binary | ios::out);
	if(outfile__array_neurongroup_4_y.is_open())
	{
		outfile__array_neurongroup_4_y.write(reinterpret_cast<char*>(_array_neurongroup_4_y), 32*sizeof(_array_neurongroup_4_y[0]));
		outfile__array_neurongroup_4_y.close();
	} else
	{
		std::cout << "Error writing output file for _array_neurongroup_4_y." << endl;
	}
	ofstream outfile__array_neurongroup_5__spikespace;
	outfile__array_neurongroup_5__spikespace.open("results\\_array_neurongroup_5__spikespace_2313911031615496480", ios::binary | ios::out);
	if(outfile__array_neurongroup_5__spikespace.is_open())
	{
		outfile__array_neurongroup_5__spikespace.write(reinterpret_cast<char*>(_array_neurongroup_5__spikespace), 14*sizeof(_array_neurongroup_5__spikespace[0]));
		outfile__array_neurongroup_5__spikespace.close();
	} else
	{
		std::cout << "Error writing output file for _array_neurongroup_5__spikespace." << endl;
	}
	ofstream outfile__array_neurongroup_5_ge_soma;
	outfile__array_neurongroup_5_ge_soma.open("results\\_array_neurongroup_5_ge_soma_-4668517227031951461", ios::binary | ios::out);
	if(outfile__array_neurongroup_5_ge_soma.is_open())
	{
		outfile__array_neurongroup_5_ge_soma.write(reinterpret_cast<char*>(_array_neurongroup_5_ge_soma), 13*sizeof(_array_neurongroup_5_ge_soma[0]));
		outfile__array_neurongroup_5_ge_soma.close();
	} else
	{
		std::cout << "Error writing output file for _array_neurongroup_5_ge_soma." << endl;
	}
	ofstream outfile__array_neurongroup_5_gi_soma;
	outfile__array_neurongroup_5_gi_soma.open("results\\_array_neurongroup_5_gi_soma_-6204821147759278701", ios::binary | ios::out);
	if(outfile__array_neurongroup_5_gi_soma.is_open())
	{
		outfile__array_neurongroup_5_gi_soma.write(reinterpret_cast<char*>(_array_neurongroup_5_gi_soma), 13*sizeof(_array_neurongroup_5_gi_soma[0]));
		outfile__array_neurongroup_5_gi_soma.close();
	} else
	{
		std::cout << "Error writing output file for _array_neurongroup_5_gi_soma." << endl;
	}
	ofstream outfile__array_neurongroup_5_i;
	outfile__array_neurongroup_5_i.open("results\\_array_neurongroup_5_i_2291693733791473416", ios::binary | ios::out);
	if(outfile__array_neurongroup_5_i.is_open())
	{
		outfile__array_neurongroup_5_i.write(reinterpret_cast<char*>(_array_neurongroup_5_i), 13*sizeof(_array_neurongroup_5_i[0]));
		outfile__array_neurongroup_5_i.close();
	} else
	{
		std::cout << "Error writing output file for _array_neurongroup_5_i." << endl;
	}
	ofstream outfile__array_neurongroup_5_lastspike;
	outfile__array_neurongroup_5_lastspike.open("results\\_array_neurongroup_5_lastspike_8885924614356848288", ios::binary | ios::out);
	if(outfile__array_neurongroup_5_lastspike.is_open())
	{
		outfile__array_neurongroup_5_lastspike.write(reinterpret_cast<char*>(_array_neurongroup_5_lastspike), 13*sizeof(_array_neurongroup_5_lastspike[0]));
		outfile__array_neurongroup_5_lastspike.close();
	} else
	{
		std::cout << "Error writing output file for _array_neurongroup_5_lastspike." << endl;
	}
	ofstream outfile__array_neurongroup_5_not_refractory;
	outfile__array_neurongroup_5_not_refractory.open("results\\_array_neurongroup_5_not_refractory_-1364242789759887481", ios::binary | ios::out);
	if(outfile__array_neurongroup_5_not_refractory.is_open())
	{
		outfile__array_neurongroup_5_not_refractory.write(reinterpret_cast<char*>(_array_neurongroup_5_not_refractory), 13*sizeof(_array_neurongroup_5_not_refractory[0]));
		outfile__array_neurongroup_5_not_refractory.close();
	} else
	{
		std::cout << "Error writing output file for _array_neurongroup_5_not_refractory." << endl;
	}
	ofstream outfile__array_neurongroup_5_vm;
	outfile__array_neurongroup_5_vm.open("results\\_array_neurongroup_5_vm_-4836840825498596124", ios::binary | ios::out);
	if(outfile__array_neurongroup_5_vm.is_open())
	{
		outfile__array_neurongroup_5_vm.write(reinterpret_cast<char*>(_array_neurongroup_5_vm), 13*sizeof(_array_neurongroup_5_vm[0]));
		outfile__array_neurongroup_5_vm.close();
	} else
	{
		std::cout << "Error writing output file for _array_neurongroup_5_vm." << endl;
	}
	ofstream outfile__array_neurongroup_5_x;
	outfile__array_neurongroup_5_x.open("results\\_array_neurongroup_5_x_2595258069356173793", ios::binary | ios::out);
	if(outfile__array_neurongroup_5_x.is_open())
	{
		outfile__array_neurongroup_5_x.write(reinterpret_cast<char*>(_array_neurongroup_5_x), 13*sizeof(_array_neurongroup_5_x[0]));
		outfile__array_neurongroup_5_x.close();
	} else
	{
		std::cout << "Error writing output file for _array_neurongroup_5_x." << endl;
	}
	ofstream outfile__array_neurongroup_5_y;
	outfile__array_neurongroup_5_y.open("results\\_array_neurongroup_5_y_-6613253192804692417", ios::binary | ios::out);
	if(outfile__array_neurongroup_5_y.is_open())
	{
		outfile__array_neurongroup_5_y.write(reinterpret_cast<char*>(_array_neurongroup_5_y), 13*sizeof(_array_neurongroup_5_y[0]));
		outfile__array_neurongroup_5_y.close();
	} else
	{
		std::cout << "Error writing output file for _array_neurongroup_5_y." << endl;
	}
	ofstream outfile__array_neurongroup__spikespace;
	outfile__array_neurongroup__spikespace.open("results\\_array_neurongroup__spikespace_8112398661543178723", ios::binary | ios::out);
	if(outfile__array_neurongroup__spikespace.is_open())
	{
		outfile__array_neurongroup__spikespace.write(reinterpret_cast<char*>(_array_neurongroup__spikespace), 61*sizeof(_array_neurongroup__spikespace[0]));
		outfile__array_neurongroup__spikespace.close();
	} else
	{
		std::cout << "Error writing output file for _array_neurongroup__spikespace." << endl;
	}
	ofstream outfile__array_neurongroup_emit_spike;
	outfile__array_neurongroup_emit_spike.open("results\\_array_neurongroup_emit_spike_1637800461724401315", ios::binary | ios::out);
	if(outfile__array_neurongroup_emit_spike.is_open())
	{
		outfile__array_neurongroup_emit_spike.write(reinterpret_cast<char*>(_array_neurongroup_emit_spike), 60*sizeof(_array_neurongroup_emit_spike[0]));
		outfile__array_neurongroup_emit_spike.close();
	} else
	{
		std::cout << "Error writing output file for _array_neurongroup_emit_spike." << endl;
	}
	ofstream outfile__array_neurongroup_i;
	outfile__array_neurongroup_i.open("results\\_array_neurongroup_i_-603929704045130371", ios::binary | ios::out);
	if(outfile__array_neurongroup_i.is_open())
	{
		outfile__array_neurongroup_i.write(reinterpret_cast<char*>(_array_neurongroup_i), 60*sizeof(_array_neurongroup_i[0]));
		outfile__array_neurongroup_i.close();
	} else
	{
		std::cout << "Error writing output file for _array_neurongroup_i." << endl;
	}
	ofstream outfile__array_neurongroup_x;
	outfile__array_neurongroup_x.open("results\\_array_neurongroup_x_5761950442718252570", ios::binary | ios::out);
	if(outfile__array_neurongroup_x.is_open())
	{
		outfile__array_neurongroup_x.write(reinterpret_cast<char*>(_array_neurongroup_x), 60*sizeof(_array_neurongroup_x[0]));
		outfile__array_neurongroup_x.close();
	} else
	{
		std::cout << "Error writing output file for _array_neurongroup_x." << endl;
	}
	ofstream outfile__array_neurongroup_y;
	outfile__array_neurongroup_y.open("results\\_array_neurongroup_y_4106848366501147634", ios::binary | ios::out);
	if(outfile__array_neurongroup_y.is_open())
	{
		outfile__array_neurongroup_y.write(reinterpret_cast<char*>(_array_neurongroup_y), 60*sizeof(_array_neurongroup_y[0]));
		outfile__array_neurongroup_y.close();
	} else
	{
		std::cout << "Error writing output file for _array_neurongroup_y." << endl;
	}
	ofstream outfile__array_spikegeneratorgroup__lastindex;
	outfile__array_spikegeneratorgroup__lastindex.open("results\\_array_spikegeneratorgroup__lastindex_5980250239470219954", ios::binary | ios::out);
	if(outfile__array_spikegeneratorgroup__lastindex.is_open())
	{
		outfile__array_spikegeneratorgroup__lastindex.write(reinterpret_cast<char*>(_array_spikegeneratorgroup__lastindex), 1*sizeof(_array_spikegeneratorgroup__lastindex[0]));
		outfile__array_spikegeneratorgroup__lastindex.close();
	} else
	{
		std::cout << "Error writing output file for _array_spikegeneratorgroup__lastindex." << endl;
	}
	ofstream outfile__array_spikegeneratorgroup__period_bins;
	outfile__array_spikegeneratorgroup__period_bins.open("results\\_array_spikegeneratorgroup__period_bins_-7520704935864198786", ios::binary | ios::out);
	if(outfile__array_spikegeneratorgroup__period_bins.is_open())
	{
		outfile__array_spikegeneratorgroup__period_bins.write(reinterpret_cast<char*>(_array_spikegeneratorgroup__period_bins), 1*sizeof(_array_spikegeneratorgroup__period_bins[0]));
		outfile__array_spikegeneratorgroup__period_bins.close();
	} else
	{
		std::cout << "Error writing output file for _array_spikegeneratorgroup__period_bins." << endl;
	}
	ofstream outfile__array_spikegeneratorgroup__spikespace;
	outfile__array_spikegeneratorgroup__spikespace.open("results\\_array_spikegeneratorgroup__spikespace_23133140151015299", ios::binary | ios::out);
	if(outfile__array_spikegeneratorgroup__spikespace.is_open())
	{
		outfile__array_spikegeneratorgroup__spikespace.write(reinterpret_cast<char*>(_array_spikegeneratorgroup__spikespace), 61*sizeof(_array_spikegeneratorgroup__spikespace[0]));
		outfile__array_spikegeneratorgroup__spikespace.close();
	} else
	{
		std::cout << "Error writing output file for _array_spikegeneratorgroup__spikespace." << endl;
	}
	ofstream outfile__array_spikegeneratorgroup_i;
	outfile__array_spikegeneratorgroup_i.open("results\\_array_spikegeneratorgroup_i_-1887123429412539116", ios::binary | ios::out);
	if(outfile__array_spikegeneratorgroup_i.is_open())
	{
		outfile__array_spikegeneratorgroup_i.write(reinterpret_cast<char*>(_array_spikegeneratorgroup_i), 60*sizeof(_array_spikegeneratorgroup_i[0]));
		outfile__array_spikegeneratorgroup_i.close();
	} else
	{
		std::cout << "Error writing output file for _array_spikegeneratorgroup_i." << endl;
	}
	ofstream outfile__array_spikegeneratorgroup_period;
	outfile__array_spikegeneratorgroup_period.open("results\\_array_spikegeneratorgroup_period_-2113254606927634525", ios::binary | ios::out);
	if(outfile__array_spikegeneratorgroup_period.is_open())
	{
		outfile__array_spikegeneratorgroup_period.write(reinterpret_cast<char*>(_array_spikegeneratorgroup_period), 1*sizeof(_array_spikegeneratorgroup_period[0]));
		outfile__array_spikegeneratorgroup_period.close();
	} else
	{
		std::cout << "Error writing output file for _array_spikegeneratorgroup_period." << endl;
	}
	ofstream outfile__array_spikemonitor_1__source_idx;
	outfile__array_spikemonitor_1__source_idx.open("results\\_array_spikemonitor_1__source_idx_-8628315099471667713", ios::binary | ios::out);
	if(outfile__array_spikemonitor_1__source_idx.is_open())
	{
		outfile__array_spikemonitor_1__source_idx.write(reinterpret_cast<char*>(_array_spikemonitor_1__source_idx), 267*sizeof(_array_spikemonitor_1__source_idx[0]));
		outfile__array_spikemonitor_1__source_idx.close();
	} else
	{
		std::cout << "Error writing output file for _array_spikemonitor_1__source_idx." << endl;
	}
	ofstream outfile__array_spikemonitor_1_count;
	outfile__array_spikemonitor_1_count.open("results\\_array_spikemonitor_1_count_3685574809863298859", ios::binary | ios::out);
	if(outfile__array_spikemonitor_1_count.is_open())
	{
		outfile__array_spikemonitor_1_count.write(reinterpret_cast<char*>(_array_spikemonitor_1_count), 267*sizeof(_array_spikemonitor_1_count[0]));
		outfile__array_spikemonitor_1_count.close();
	} else
	{
		std::cout << "Error writing output file for _array_spikemonitor_1_count." << endl;
	}
	ofstream outfile__array_spikemonitor_1_N;
	outfile__array_spikemonitor_1_N.open("results\\_array_spikemonitor_1_N_-6162079368954396671", ios::binary | ios::out);
	if(outfile__array_spikemonitor_1_N.is_open())
	{
		outfile__array_spikemonitor_1_N.write(reinterpret_cast<char*>(_array_spikemonitor_1_N), 1*sizeof(_array_spikemonitor_1_N[0]));
		outfile__array_spikemonitor_1_N.close();
	} else
	{
		std::cout << "Error writing output file for _array_spikemonitor_1_N." << endl;
	}
	ofstream outfile__array_spikemonitor_2__source_idx;
	outfile__array_spikemonitor_2__source_idx.open("results\\_array_spikemonitor_2__source_idx_4842352479638141825", ios::binary | ios::out);
	if(outfile__array_spikemonitor_2__source_idx.is_open())
	{
		outfile__array_spikemonitor_2__source_idx.write(reinterpret_cast<char*>(_array_spikemonitor_2__source_idx), 109*sizeof(_array_spikemonitor_2__source_idx[0]));
		outfile__array_spikemonitor_2__source_idx.close();
	} else
	{
		std::cout << "Error writing output file for _array_spikemonitor_2__source_idx." << endl;
	}
	ofstream outfile__array_spikemonitor_2_count;
	outfile__array_spikemonitor_2_count.open("results\\_array_spikemonitor_2_count_2617794024552164482", ios::binary | ios::out);
	if(outfile__array_spikemonitor_2_count.is_open())
	{
		outfile__array_spikemonitor_2_count.write(reinterpret_cast<char*>(_array_spikemonitor_2_count), 109*sizeof(_array_spikemonitor_2_count[0]));
		outfile__array_spikemonitor_2_count.close();
	} else
	{
		std::cout << "Error writing output file for _array_spikemonitor_2_count." << endl;
	}
	ofstream outfile__array_spikemonitor_2_N;
	outfile__array_spikemonitor_2_N.open("results\\_array_spikemonitor_2_N_-7835762837997192138", ios::binary | ios::out);
	if(outfile__array_spikemonitor_2_N.is_open())
	{
		outfile__array_spikemonitor_2_N.write(reinterpret_cast<char*>(_array_spikemonitor_2_N), 1*sizeof(_array_spikemonitor_2_N[0]));
		outfile__array_spikemonitor_2_N.close();
	} else
	{
		std::cout << "Error writing output file for _array_spikemonitor_2_N." << endl;
	}
	ofstream outfile__array_spikemonitor_3__source_idx;
	outfile__array_spikemonitor_3__source_idx.open("results\\_array_spikemonitor_3__source_idx_4381695219445360725", ios::binary | ios::out);
	if(outfile__array_spikemonitor_3__source_idx.is_open())
	{
		outfile__array_spikemonitor_3__source_idx.write(reinterpret_cast<char*>(_array_spikemonitor_3__source_idx), 40*sizeof(_array_spikemonitor_3__source_idx[0]));
		outfile__array_spikemonitor_3__source_idx.close();
	} else
	{
		std::cout << "Error writing output file for _array_spikemonitor_3__source_idx." << endl;
	}
	ofstream outfile__array_spikemonitor_3_count;
	outfile__array_spikemonitor_3_count.open("results\\_array_spikemonitor_3_count_853691453686606754", ios::binary | ios::out);
	if(outfile__array_spikemonitor_3_count.is_open())
	{
		outfile__array_spikemonitor_3_count.write(reinterpret_cast<char*>(_array_spikemonitor_3_count), 40*sizeof(_array_spikemonitor_3_count[0]));
		outfile__array_spikemonitor_3_count.close();
	} else
	{
		std::cout << "Error writing output file for _array_spikemonitor_3_count." << endl;
	}
	ofstream outfile__array_spikemonitor_3_N;
	outfile__array_spikemonitor_3_N.open("results\\_array_spikemonitor_3_N_-1637471382915355675", ios::binary | ios::out);
	if(outfile__array_spikemonitor_3_N.is_open())
	{
		outfile__array_spikemonitor_3_N.write(reinterpret_cast<char*>(_array_spikemonitor_3_N), 1*sizeof(_array_spikemonitor_3_N[0]));
		outfile__array_spikemonitor_3_N.close();
	} else
	{
		std::cout << "Error writing output file for _array_spikemonitor_3_N." << endl;
	}
	ofstream outfile__array_spikemonitor_4__source_idx;
	outfile__array_spikemonitor_4__source_idx.open("results\\_array_spikemonitor_4__source_idx_5803463390732673746", ios::binary | ios::out);
	if(outfile__array_spikemonitor_4__source_idx.is_open())
	{
		outfile__array_spikemonitor_4__source_idx.write(reinterpret_cast<char*>(_array_spikemonitor_4__source_idx), 32*sizeof(_array_spikemonitor_4__source_idx[0]));
		outfile__array_spikemonitor_4__source_idx.close();
	} else
	{
		std::cout << "Error writing output file for _array_spikemonitor_4__source_idx." << endl;
	}
	ofstream outfile__array_spikemonitor_4_count;
	outfile__array_spikemonitor_4_count.open("results\\_array_spikemonitor_4_count_6114280218094113869", ios::binary | ios::out);
	if(outfile__array_spikemonitor_4_count.is_open())
	{
		outfile__array_spikemonitor_4_count.write(reinterpret_cast<char*>(_array_spikemonitor_4_count), 32*sizeof(_array_spikemonitor_4_count[0]));
		outfile__array_spikemonitor_4_count.close();
	} else
	{
		std::cout << "Error writing output file for _array_spikemonitor_4_count." << endl;
	}
	ofstream outfile__array_spikemonitor_4_N;
	outfile__array_spikemonitor_4_N.open("results\\_array_spikemonitor_4_N_6890303945852457109", ios::binary | ios::out);
	if(outfile__array_spikemonitor_4_N.is_open())
	{
		outfile__array_spikemonitor_4_N.write(reinterpret_cast<char*>(_array_spikemonitor_4_N), 1*sizeof(_array_spikemonitor_4_N[0]));
		outfile__array_spikemonitor_4_N.close();
	} else
	{
		std::cout << "Error writing output file for _array_spikemonitor_4_N." << endl;
	}
	ofstream outfile__array_spikemonitor_5__source_idx;
	outfile__array_spikemonitor_5__source_idx.open("results\\_array_spikemonitor_5__source_idx_-4313025762039996030", ios::binary | ios::out);
	if(outfile__array_spikemonitor_5__source_idx.is_open())
	{
		outfile__array_spikemonitor_5__source_idx.write(reinterpret_cast<char*>(_array_spikemonitor_5__source_idx), 13*sizeof(_array_spikemonitor_5__source_idx[0]));
		outfile__array_spikemonitor_5__source_idx.close();
	} else
	{
		std::cout << "Error writing output file for _array_spikemonitor_5__source_idx." << endl;
	}
	ofstream outfile__array_spikemonitor_5_count;
	outfile__array_spikemonitor_5_count.open("results\\_array_spikemonitor_5_count_-3714558058255364664", ios::binary | ios::out);
	if(outfile__array_spikemonitor_5_count.is_open())
	{
		outfile__array_spikemonitor_5_count.write(reinterpret_cast<char*>(_array_spikemonitor_5_count), 13*sizeof(_array_spikemonitor_5_count[0]));
		outfile__array_spikemonitor_5_count.close();
	} else
	{
		std::cout << "Error writing output file for _array_spikemonitor_5_count." << endl;
	}
	ofstream outfile__array_spikemonitor_5_N;
	outfile__array_spikemonitor_5_N.open("results\\_array_spikemonitor_5_N_-8371328195457174538", ios::binary | ios::out);
	if(outfile__array_spikemonitor_5_N.is_open())
	{
		outfile__array_spikemonitor_5_N.write(reinterpret_cast<char*>(_array_spikemonitor_5_N), 1*sizeof(_array_spikemonitor_5_N[0]));
		outfile__array_spikemonitor_5_N.close();
	} else
	{
		std::cout << "Error writing output file for _array_spikemonitor_5_N." << endl;
	}
	ofstream outfile__array_spikemonitor__source_idx;
	outfile__array_spikemonitor__source_idx.open("results\\_array_spikemonitor__source_idx_294162745419648011", ios::binary | ios::out);
	if(outfile__array_spikemonitor__source_idx.is_open())
	{
		outfile__array_spikemonitor__source_idx.write(reinterpret_cast<char*>(_array_spikemonitor__source_idx), 60*sizeof(_array_spikemonitor__source_idx[0]));
		outfile__array_spikemonitor__source_idx.close();
	} else
	{
		std::cout << "Error writing output file for _array_spikemonitor__source_idx." << endl;
	}
	ofstream outfile__array_spikemonitor_count;
	outfile__array_spikemonitor_count.open("results\\_array_spikemonitor_count_-7060367653655850805", ios::binary | ios::out);
	if(outfile__array_spikemonitor_count.is_open())
	{
		outfile__array_spikemonitor_count.write(reinterpret_cast<char*>(_array_spikemonitor_count), 60*sizeof(_array_spikemonitor_count[0]));
		outfile__array_spikemonitor_count.close();
	} else
	{
		std::cout << "Error writing output file for _array_spikemonitor_count." << endl;
	}
	ofstream outfile__array_spikemonitor_N;
	outfile__array_spikemonitor_N.open("results\\_array_spikemonitor_N_-3759535840340425659", ios::binary | ios::out);
	if(outfile__array_spikemonitor_N.is_open())
	{
		outfile__array_spikemonitor_N.write(reinterpret_cast<char*>(_array_spikemonitor_N), 1*sizeof(_array_spikemonitor_N[0]));
		outfile__array_spikemonitor_N.close();
	} else
	{
		std::cout << "Error writing output file for _array_spikemonitor_N." << endl;
	}
	ofstream outfile__array_synapses_10_N;
	outfile__array_synapses_10_N.open("results\\_array_synapses_10_N_-213312102162196146", ios::binary | ios::out);
	if(outfile__array_synapses_10_N.is_open())
	{
		outfile__array_synapses_10_N.write(reinterpret_cast<char*>(_array_synapses_10_N), 1*sizeof(_array_synapses_10_N[0]));
		outfile__array_synapses_10_N.close();
	} else
	{
		std::cout << "Error writing output file for _array_synapses_10_N." << endl;
	}
	ofstream outfile__array_synapses_10_sources;
	outfile__array_synapses_10_sources.open("results\\_array_synapses_10_sources_5247669790054803907", ios::binary | ios::out);
	if(outfile__array_synapses_10_sources.is_open())
	{
		outfile__array_synapses_10_sources.write(reinterpret_cast<char*>(_array_synapses_10_sources), 990*sizeof(_array_synapses_10_sources[0]));
		outfile__array_synapses_10_sources.close();
	} else
	{
		std::cout << "Error writing output file for _array_synapses_10_sources." << endl;
	}
	ofstream outfile__array_synapses_10_targets;
	outfile__array_synapses_10_targets.open("results\\_array_synapses_10_targets_-6882442780660600942", ios::binary | ios::out);
	if(outfile__array_synapses_10_targets.is_open())
	{
		outfile__array_synapses_10_targets.write(reinterpret_cast<char*>(_array_synapses_10_targets), 990*sizeof(_array_synapses_10_targets[0]));
		outfile__array_synapses_10_targets.close();
	} else
	{
		std::cout << "Error writing output file for _array_synapses_10_targets." << endl;
	}
	ofstream outfile__array_synapses_11_N;
	outfile__array_synapses_11_N.open("results\\_array_synapses_11_N_6485960303079062902", ios::binary | ios::out);
	if(outfile__array_synapses_11_N.is_open())
	{
		outfile__array_synapses_11_N.write(reinterpret_cast<char*>(_array_synapses_11_N), 1*sizeof(_array_synapses_11_N[0]));
		outfile__array_synapses_11_N.close();
	} else
	{
		std::cout << "Error writing output file for _array_synapses_11_N." << endl;
	}
	ofstream outfile__array_synapses_11_sources;
	outfile__array_synapses_11_sources.open("results\\_array_synapses_11_sources_5875181874486520588", ios::binary | ios::out);
	if(outfile__array_synapses_11_sources.is_open())
	{
		outfile__array_synapses_11_sources.write(reinterpret_cast<char*>(_array_synapses_11_sources), 357*sizeof(_array_synapses_11_sources[0]));
		outfile__array_synapses_11_sources.close();
	} else
	{
		std::cout << "Error writing output file for _array_synapses_11_sources." << endl;
	}
	ofstream outfile__array_synapses_11_targets;
	outfile__array_synapses_11_targets.open("results\\_array_synapses_11_targets_8422609310177717170", ios::binary | ios::out);
	if(outfile__array_synapses_11_targets.is_open())
	{
		outfile__array_synapses_11_targets.write(reinterpret_cast<char*>(_array_synapses_11_targets), 357*sizeof(_array_synapses_11_targets[0]));
		outfile__array_synapses_11_targets.close();
	} else
	{
		std::cout << "Error writing output file for _array_synapses_11_targets." << endl;
	}
	ofstream outfile__array_synapses_12_N;
	outfile__array_synapses_12_N.open("results\\_array_synapses_12_N_6905118173845976941", ios::binary | ios::out);
	if(outfile__array_synapses_12_N.is_open())
	{
		outfile__array_synapses_12_N.write(reinterpret_cast<char*>(_array_synapses_12_N), 1*sizeof(_array_synapses_12_N[0]));
		outfile__array_synapses_12_N.close();
	} else
	{
		std::cout << "Error writing output file for _array_synapses_12_N." << endl;
	}
	ofstream outfile__array_synapses_12_sources;
	outfile__array_synapses_12_sources.open("results\\_array_synapses_12_sources_6904883836418434726", ios::binary | ios::out);
	if(outfile__array_synapses_12_sources.is_open())
	{
		outfile__array_synapses_12_sources.write(reinterpret_cast<char*>(_array_synapses_12_sources), 28*sizeof(_array_synapses_12_sources[0]));
		outfile__array_synapses_12_sources.close();
	} else
	{
		std::cout << "Error writing output file for _array_synapses_12_sources." << endl;
	}
	ofstream outfile__array_synapses_12_targets;
	outfile__array_synapses_12_targets.open("results\\_array_synapses_12_targets_4587486420051065387", ios::binary | ios::out);
	if(outfile__array_synapses_12_targets.is_open())
	{
		outfile__array_synapses_12_targets.write(reinterpret_cast<char*>(_array_synapses_12_targets), 28*sizeof(_array_synapses_12_targets[0]));
		outfile__array_synapses_12_targets.close();
	} else
	{
		std::cout << "Error writing output file for _array_synapses_12_targets." << endl;
	}
	ofstream outfile__array_synapses_13_N;
	outfile__array_synapses_13_N.open("results\\_array_synapses_13_N_1179600431090376853", ios::binary | ios::out);
	if(outfile__array_synapses_13_N.is_open())
	{
		outfile__array_synapses_13_N.write(reinterpret_cast<char*>(_array_synapses_13_N), 1*sizeof(_array_synapses_13_N[0]));
		outfile__array_synapses_13_N.close();
	} else
	{
		std::cout << "Error writing output file for _array_synapses_13_N." << endl;
	}
	ofstream outfile__array_synapses_13_sources;
	outfile__array_synapses_13_sources.open("results\\_array_synapses_13_sources_1355294832578995236", ios::binary | ios::out);
	if(outfile__array_synapses_13_sources.is_open())
	{
		outfile__array_synapses_13_sources.write(reinterpret_cast<char*>(_array_synapses_13_sources), 45*sizeof(_array_synapses_13_sources[0]));
		outfile__array_synapses_13_sources.close();
	} else
	{
		std::cout << "Error writing output file for _array_synapses_13_sources." << endl;
	}
	ofstream outfile__array_synapses_13_targets;
	outfile__array_synapses_13_targets.open("results\\_array_synapses_13_targets_-730531939457193272", ios::binary | ios::out);
	if(outfile__array_synapses_13_targets.is_open())
	{
		outfile__array_synapses_13_targets.write(reinterpret_cast<char*>(_array_synapses_13_targets), 45*sizeof(_array_synapses_13_targets[0]));
		outfile__array_synapses_13_targets.close();
	} else
	{
		std::cout << "Error writing output file for _array_synapses_13_targets." << endl;
	}
	ofstream outfile__array_synapses_14_N;
	outfile__array_synapses_14_N.open("results\\_array_synapses_14_N_-8582326864952496431", ios::binary | ios::out);
	if(outfile__array_synapses_14_N.is_open())
	{
		outfile__array_synapses_14_N.write(reinterpret_cast<char*>(_array_synapses_14_N), 1*sizeof(_array_synapses_14_N[0]));
		outfile__array_synapses_14_N.close();
	} else
	{
		std::cout << "Error writing output file for _array_synapses_14_N." << endl;
	}
	ofstream outfile__array_synapses_14_sources;
	outfile__array_synapses_14_sources.open("results\\_array_synapses_14_sources_8174083348892481013", ios::binary | ios::out);
	if(outfile__array_synapses_14_sources.is_open())
	{
		outfile__array_synapses_14_sources.write(reinterpret_cast<char*>(_array_synapses_14_sources), 492*sizeof(_array_synapses_14_sources[0]));
		outfile__array_synapses_14_sources.close();
	} else
	{
		std::cout << "Error writing output file for _array_synapses_14_sources." << endl;
	}
	ofstream outfile__array_synapses_14_targets;
	outfile__array_synapses_14_targets.open("results\\_array_synapses_14_targets_-7102720887649668836", ios::binary | ios::out);
	if(outfile__array_synapses_14_targets.is_open())
	{
		outfile__array_synapses_14_targets.write(reinterpret_cast<char*>(_array_synapses_14_targets), 492*sizeof(_array_synapses_14_targets[0]));
		outfile__array_synapses_14_targets.close();
	} else
	{
		std::cout << "Error writing output file for _array_synapses_14_targets." << endl;
	}
	ofstream outfile__array_synapses_15_N;
	outfile__array_synapses_15_N.open("results\\_array_synapses_15_N_8166023443774918893", ios::binary | ios::out);
	if(outfile__array_synapses_15_N.is_open())
	{
		outfile__array_synapses_15_N.write(reinterpret_cast<char*>(_array_synapses_15_N), 1*sizeof(_array_synapses_15_N[0]));
		outfile__array_synapses_15_N.close();
	} else
	{
		std::cout << "Error writing output file for _array_synapses_15_N." << endl;
	}
	ofstream outfile__array_synapses_15_sources;
	outfile__array_synapses_15_sources.open("results\\_array_synapses_15_sources_-555892077199456551", ios::binary | ios::out);
	if(outfile__array_synapses_15_sources.is_open())
	{
		outfile__array_synapses_15_sources.write(reinterpret_cast<char*>(_array_synapses_15_sources), 300*sizeof(_array_synapses_15_sources[0]));
		outfile__array_synapses_15_sources.close();
	} else
	{
		std::cout << "Error writing output file for _array_synapses_15_sources." << endl;
	}
	ofstream outfile__array_synapses_15_targets;
	outfile__array_synapses_15_targets.open("results\\_array_synapses_15_targets_8038226052643481190", ios::binary | ios::out);
	if(outfile__array_synapses_15_targets.is_open())
	{
		outfile__array_synapses_15_targets.write(reinterpret_cast<char*>(_array_synapses_15_targets), 300*sizeof(_array_synapses_15_targets[0]));
		outfile__array_synapses_15_targets.close();
	} else
	{
		std::cout << "Error writing output file for _array_synapses_15_targets." << endl;
	}
	ofstream outfile__array_synapses_16_N;
	outfile__array_synapses_16_N.open("results\\_array_synapses_16_N_1227831212638973219", ios::binary | ios::out);
	if(outfile__array_synapses_16_N.is_open())
	{
		outfile__array_synapses_16_N.write(reinterpret_cast<char*>(_array_synapses_16_N), 1*sizeof(_array_synapses_16_N[0]));
		outfile__array_synapses_16_N.close();
	} else
	{
		std::cout << "Error writing output file for _array_synapses_16_N." << endl;
	}
	ofstream outfile__array_synapses_16_sources;
	outfile__array_synapses_16_sources.open("results\\_array_synapses_16_sources_-8700662869014349905", ios::binary | ios::out);
	if(outfile__array_synapses_16_sources.is_open())
	{
		outfile__array_synapses_16_sources.write(reinterpret_cast<char*>(_array_synapses_16_sources), 154*sizeof(_array_synapses_16_sources[0]));
		outfile__array_synapses_16_sources.close();
	} else
	{
		std::cout << "Error writing output file for _array_synapses_16_sources." << endl;
	}
	ofstream outfile__array_synapses_16_targets;
	outfile__array_synapses_16_targets.open("results\\_array_synapses_16_targets_8226664709662137111", ios::binary | ios::out);
	if(outfile__array_synapses_16_targets.is_open())
	{
		outfile__array_synapses_16_targets.write(reinterpret_cast<char*>(_array_synapses_16_targets), 154*sizeof(_array_synapses_16_targets[0]));
		outfile__array_synapses_16_targets.close();
	} else
	{
		std::cout << "Error writing output file for _array_synapses_16_targets." << endl;
	}
	ofstream outfile__array_synapses_17_N;
	outfile__array_synapses_17_N.open("results\\_array_synapses_17_N_8738273717200242207", ios::binary | ios::out);
	if(outfile__array_synapses_17_N.is_open())
	{
		outfile__array_synapses_17_N.write(reinterpret_cast<char*>(_array_synapses_17_N), 1*sizeof(_array_synapses_17_N[0]));
		outfile__array_synapses_17_N.close();
	} else
	{
		std::cout << "Error writing output file for _array_synapses_17_N." << endl;
	}
	ofstream outfile__array_synapses_17_sources;
	outfile__array_synapses_17_sources.open("results\\_array_synapses_17_sources_-4401581000569211880", ios::binary | ios::out);
	if(outfile__array_synapses_17_sources.is_open())
	{
		outfile__array_synapses_17_sources.write(reinterpret_cast<char*>(_array_synapses_17_sources), 370*sizeof(_array_synapses_17_sources[0]));
		outfile__array_synapses_17_sources.close();
	} else
	{
		std::cout << "Error writing output file for _array_synapses_17_sources." << endl;
	}
	ofstream outfile__array_synapses_17_targets;
	outfile__array_synapses_17_targets.open("results\\_array_synapses_17_targets_-2959108807874849566", ios::binary | ios::out);
	if(outfile__array_synapses_17_targets.is_open())
	{
		outfile__array_synapses_17_targets.write(reinterpret_cast<char*>(_array_synapses_17_targets), 370*sizeof(_array_synapses_17_targets[0]));
		outfile__array_synapses_17_targets.close();
	} else
	{
		std::cout << "Error writing output file for _array_synapses_17_targets." << endl;
	}
	ofstream outfile__array_synapses_18_N;
	outfile__array_synapses_18_N.open("results\\_array_synapses_18_N_-1307485959945851440", ios::binary | ios::out);
	if(outfile__array_synapses_18_N.is_open())
	{
		outfile__array_synapses_18_N.write(reinterpret_cast<char*>(_array_synapses_18_N), 1*sizeof(_array_synapses_18_N[0]));
		outfile__array_synapses_18_N.close();
	} else
	{
		std::cout << "Error writing output file for _array_synapses_18_N." << endl;
	}
	ofstream outfile__array_synapses_18_sources;
	outfile__array_synapses_18_sources.open("results\\_array_synapses_18_sources_-8500602518669242996", ios::binary | ios::out);
	if(outfile__array_synapses_18_sources.is_open())
	{
		outfile__array_synapses_18_sources.write(reinterpret_cast<char*>(_array_synapses_18_sources), 252*sizeof(_array_synapses_18_sources[0]));
		outfile__array_synapses_18_sources.close();
	} else
	{
		std::cout << "Error writing output file for _array_synapses_18_sources." << endl;
	}
	ofstream outfile__array_synapses_18_targets;
	outfile__array_synapses_18_targets.open("results\\_array_synapses_18_targets_2324748256331257751", ios::binary | ios::out);
	if(outfile__array_synapses_18_targets.is_open())
	{
		outfile__array_synapses_18_targets.write(reinterpret_cast<char*>(_array_synapses_18_targets), 252*sizeof(_array_synapses_18_targets[0]));
		outfile__array_synapses_18_targets.close();
	} else
	{
		std::cout << "Error writing output file for _array_synapses_18_targets." << endl;
	}
	ofstream outfile__array_synapses_19_N;
	outfile__array_synapses_19_N.open("results\\_array_synapses_19_N_5513780667195714965", ios::binary | ios::out);
	if(outfile__array_synapses_19_N.is_open())
	{
		outfile__array_synapses_19_N.write(reinterpret_cast<char*>(_array_synapses_19_N), 1*sizeof(_array_synapses_19_N[0]));
		outfile__array_synapses_19_N.close();
	} else
	{
		std::cout << "Error writing output file for _array_synapses_19_N." << endl;
	}
	ofstream outfile__array_synapses_19_sources;
	outfile__array_synapses_19_sources.open("results\\_array_synapses_19_sources_7146905453200253619", ios::binary | ios::out);
	if(outfile__array_synapses_19_sources.is_open())
	{
		outfile__array_synapses_19_sources.write(reinterpret_cast<char*>(_array_synapses_19_sources), 2097*sizeof(_array_synapses_19_sources[0]));
		outfile__array_synapses_19_sources.close();
	} else
	{
		std::cout << "Error writing output file for _array_synapses_19_sources." << endl;
	}
	ofstream outfile__array_synapses_19_targets;
	outfile__array_synapses_19_targets.open("results\\_array_synapses_19_targets_-1077842239620982905", ios::binary | ios::out);
	if(outfile__array_synapses_19_targets.is_open())
	{
		outfile__array_synapses_19_targets.write(reinterpret_cast<char*>(_array_synapses_19_targets), 2097*sizeof(_array_synapses_19_targets[0]));
		outfile__array_synapses_19_targets.close();
	} else
	{
		std::cout << "Error writing output file for _array_synapses_19_targets." << endl;
	}
	ofstream outfile__array_synapses_1_N;
	outfile__array_synapses_1_N.open("results\\_array_synapses_1_N_400454719642151227", ios::binary | ios::out);
	if(outfile__array_synapses_1_N.is_open())
	{
		outfile__array_synapses_1_N.write(reinterpret_cast<char*>(_array_synapses_1_N), 1*sizeof(_array_synapses_1_N[0]));
		outfile__array_synapses_1_N.close();
	} else
	{
		std::cout << "Error writing output file for _array_synapses_1_N." << endl;
	}
	ofstream outfile__array_synapses_1_sources;
	outfile__array_synapses_1_sources.open("results\\_array_synapses_1_sources_6428046770457125413", ios::binary | ios::out);
	if(outfile__array_synapses_1_sources.is_open())
	{
		outfile__array_synapses_1_sources.write(reinterpret_cast<char*>(_array_synapses_1_sources), 4803*sizeof(_array_synapses_1_sources[0]));
		outfile__array_synapses_1_sources.close();
	} else
	{
		std::cout << "Error writing output file for _array_synapses_1_sources." << endl;
	}
	ofstream outfile__array_synapses_1_targets;
	outfile__array_synapses_1_targets.open("results\\_array_synapses_1_targets_8394679777133823084", ios::binary | ios::out);
	if(outfile__array_synapses_1_targets.is_open())
	{
		outfile__array_synapses_1_targets.write(reinterpret_cast<char*>(_array_synapses_1_targets), 4803*sizeof(_array_synapses_1_targets[0]));
		outfile__array_synapses_1_targets.close();
	} else
	{
		std::cout << "Error writing output file for _array_synapses_1_targets." << endl;
	}
	ofstream outfile__array_synapses_20_N;
	outfile__array_synapses_20_N.open("results\\_array_synapses_20_N_7091650118263346988", ios::binary | ios::out);
	if(outfile__array_synapses_20_N.is_open())
	{
		outfile__array_synapses_20_N.write(reinterpret_cast<char*>(_array_synapses_20_N), 1*sizeof(_array_synapses_20_N[0]));
		outfile__array_synapses_20_N.close();
	} else
	{
		std::cout << "Error writing output file for _array_synapses_20_N." << endl;
	}
	ofstream outfile__array_synapses_20_sources;
	outfile__array_synapses_20_sources.open("results\\_array_synapses_20_sources_6582110924103296621", ios::binary | ios::out);
	if(outfile__array_synapses_20_sources.is_open())
	{
		outfile__array_synapses_20_sources.write(reinterpret_cast<char*>(_array_synapses_20_sources), 2142*sizeof(_array_synapses_20_sources[0]));
		outfile__array_synapses_20_sources.close();
	} else
	{
		std::cout << "Error writing output file for _array_synapses_20_sources." << endl;
	}
	ofstream outfile__array_synapses_20_targets;
	outfile__array_synapses_20_targets.open("results\\_array_synapses_20_targets_8473542939756173007", ios::binary | ios::out);
	if(outfile__array_synapses_20_targets.is_open())
	{
		outfile__array_synapses_20_targets.write(reinterpret_cast<char*>(_array_synapses_20_targets), 2142*sizeof(_array_synapses_20_targets[0]));
		outfile__array_synapses_20_targets.close();
	} else
	{
		std::cout << "Error writing output file for _array_synapses_20_targets." << endl;
	}
	ofstream outfile__array_synapses_21_N;
	outfile__array_synapses_21_N.open("results\\_array_synapses_21_N_-5851977071886732797", ios::binary | ios::out);
	if(outfile__array_synapses_21_N.is_open())
	{
		outfile__array_synapses_21_N.write(reinterpret_cast<char*>(_array_synapses_21_N), 1*sizeof(_array_synapses_21_N[0]));
		outfile__array_synapses_21_N.close();
	} else
	{
		std::cout << "Error writing output file for _array_synapses_21_N." << endl;
	}
	ofstream outfile__array_synapses_21_sources;
	outfile__array_synapses_21_sources.open("results\\_array_synapses_21_sources_-4228963354351264326", ios::binary | ios::out);
	if(outfile__array_synapses_21_sources.is_open())
	{
		outfile__array_synapses_21_sources.write(reinterpret_cast<char*>(_array_synapses_21_sources), 762*sizeof(_array_synapses_21_sources[0]));
		outfile__array_synapses_21_sources.close();
	} else
	{
		std::cout << "Error writing output file for _array_synapses_21_sources." << endl;
	}
	ofstream outfile__array_synapses_21_targets;
	outfile__array_synapses_21_targets.open("results\\_array_synapses_21_targets_198094663961785989", ios::binary | ios::out);
	if(outfile__array_synapses_21_targets.is_open())
	{
		outfile__array_synapses_21_targets.write(reinterpret_cast<char*>(_array_synapses_21_targets), 762*sizeof(_array_synapses_21_targets[0]));
		outfile__array_synapses_21_targets.close();
	} else
	{
		std::cout << "Error writing output file for _array_synapses_21_targets." << endl;
	}
	ofstream outfile__array_synapses_22_N;
	outfile__array_synapses_22_N.open("results\\_array_synapses_22_N_1906281164527244460", ios::binary | ios::out);
	if(outfile__array_synapses_22_N.is_open())
	{
		outfile__array_synapses_22_N.write(reinterpret_cast<char*>(_array_synapses_22_N), 1*sizeof(_array_synapses_22_N[0]));
		outfile__array_synapses_22_N.close();
	} else
	{
		std::cout << "Error writing output file for _array_synapses_22_N." << endl;
	}
	ofstream outfile__array_synapses_22_sources;
	outfile__array_synapses_22_sources.open("results\\_array_synapses_22_sources_-7451318744479746563", ios::binary | ios::out);
	if(outfile__array_synapses_22_sources.is_open())
	{
		outfile__array_synapses_22_sources.write(reinterpret_cast<char*>(_array_synapses_22_sources), 747*sizeof(_array_synapses_22_sources[0]));
		outfile__array_synapses_22_sources.close();
	} else
	{
		std::cout << "Error writing output file for _array_synapses_22_sources." << endl;
	}
	ofstream outfile__array_synapses_22_targets;
	outfile__array_synapses_22_targets.open("results\\_array_synapses_22_targets_-4946890897148840776", ios::binary | ios::out);
	if(outfile__array_synapses_22_targets.is_open())
	{
		outfile__array_synapses_22_targets.write(reinterpret_cast<char*>(_array_synapses_22_targets), 747*sizeof(_array_synapses_22_targets[0]));
		outfile__array_synapses_22_targets.close();
	} else
	{
		std::cout << "Error writing output file for _array_synapses_22_targets." << endl;
	}
	ofstream outfile__array_synapses_23_N;
	outfile__array_synapses_23_N.open("results\\_array_synapses_23_N_193546582989690477", ios::binary | ios::out);
	if(outfile__array_synapses_23_N.is_open())
	{
		outfile__array_synapses_23_N.write(reinterpret_cast<char*>(_array_synapses_23_N), 1*sizeof(_array_synapses_23_N[0]));
		outfile__array_synapses_23_N.close();
	} else
	{
		std::cout << "Error writing output file for _array_synapses_23_N." << endl;
	}
	ofstream outfile__array_synapses_23_sources;
	outfile__array_synapses_23_sources.open("results\\_array_synapses_23_sources_-3663866175167817272", ios::binary | ios::out);
	if(outfile__array_synapses_23_sources.is_open())
	{
		outfile__array_synapses_23_sources.write(reinterpret_cast<char*>(_array_synapses_23_sources), 642*sizeof(_array_synapses_23_sources[0]));
		outfile__array_synapses_23_sources.close();
	} else
	{
		std::cout << "Error writing output file for _array_synapses_23_sources." << endl;
	}
	ofstream outfile__array_synapses_23_targets;
	outfile__array_synapses_23_targets.open("results\\_array_synapses_23_targets_2686882206566491259", ios::binary | ios::out);
	if(outfile__array_synapses_23_targets.is_open())
	{
		outfile__array_synapses_23_targets.write(reinterpret_cast<char*>(_array_synapses_23_targets), 642*sizeof(_array_synapses_23_targets[0]));
		outfile__array_synapses_23_targets.close();
	} else
	{
		std::cout << "Error writing output file for _array_synapses_23_targets." << endl;
	}
	ofstream outfile__array_synapses_24_N;
	outfile__array_synapses_24_N.open("results\\_array_synapses_24_N_354845389595590538", ios::binary | ios::out);
	if(outfile__array_synapses_24_N.is_open())
	{
		outfile__array_synapses_24_N.write(reinterpret_cast<char*>(_array_synapses_24_N), 1*sizeof(_array_synapses_24_N[0]));
		outfile__array_synapses_24_N.close();
	} else
	{
		std::cout << "Error writing output file for _array_synapses_24_N." << endl;
	}
	ofstream outfile__array_synapses_24_sources;
	outfile__array_synapses_24_sources.open("results\\_array_synapses_24_sources_-8478662677078124345", ios::binary | ios::out);
	if(outfile__array_synapses_24_sources.is_open())
	{
		outfile__array_synapses_24_sources.write(reinterpret_cast<char*>(_array_synapses_24_sources), 140*sizeof(_array_synapses_24_sources[0]));
		outfile__array_synapses_24_sources.close();
	} else
	{
		std::cout << "Error writing output file for _array_synapses_24_sources." << endl;
	}
	ofstream outfile__array_synapses_24_targets;
	outfile__array_synapses_24_targets.open("results\\_array_synapses_24_targets_6514677890203340854", ios::binary | ios::out);
	if(outfile__array_synapses_24_targets.is_open())
	{
		outfile__array_synapses_24_targets.write(reinterpret_cast<char*>(_array_synapses_24_targets), 140*sizeof(_array_synapses_24_targets[0]));
		outfile__array_synapses_24_targets.close();
	} else
	{
		std::cout << "Error writing output file for _array_synapses_24_targets." << endl;
	}
	ofstream outfile__array_synapses_25_N;
	outfile__array_synapses_25_N.open("results\\_array_synapses_25_N_6443394005084205420", ios::binary | ios::out);
	if(outfile__array_synapses_25_N.is_open())
	{
		outfile__array_synapses_25_N.write(reinterpret_cast<char*>(_array_synapses_25_N), 1*sizeof(_array_synapses_25_N[0]));
		outfile__array_synapses_25_N.close();
	} else
	{
		std::cout << "Error writing output file for _array_synapses_25_N." << endl;
	}
	ofstream outfile__array_synapses_25_sources;
	outfile__array_synapses_25_sources.open("results\\_array_synapses_25_sources_5379717544269151787", ios::binary | ios::out);
	if(outfile__array_synapses_25_sources.is_open())
	{
		outfile__array_synapses_25_sources.write(reinterpret_cast<char*>(_array_synapses_25_sources), 112*sizeof(_array_synapses_25_sources[0]));
		outfile__array_synapses_25_sources.close();
	} else
	{
		std::cout << "Error writing output file for _array_synapses_25_sources." << endl;
	}
	ofstream outfile__array_synapses_25_targets;
	outfile__array_synapses_25_targets.open("results\\_array_synapses_25_targets_3742156115974881261", ios::binary | ios::out);
	if(outfile__array_synapses_25_targets.is_open())
	{
		outfile__array_synapses_25_targets.write(reinterpret_cast<char*>(_array_synapses_25_targets), 112*sizeof(_array_synapses_25_targets[0]));
		outfile__array_synapses_25_targets.close();
	} else
	{
		std::cout << "Error writing output file for _array_synapses_25_targets." << endl;
	}
	ofstream outfile__array_synapses_26_N;
	outfile__array_synapses_26_N.open("results\\_array_synapses_26_N_-1994278141897885189", ios::binary | ios::out);
	if(outfile__array_synapses_26_N.is_open())
	{
		outfile__array_synapses_26_N.write(reinterpret_cast<char*>(_array_synapses_26_N), 1*sizeof(_array_synapses_26_N[0]));
		outfile__array_synapses_26_N.close();
	} else
	{
		std::cout << "Error writing output file for _array_synapses_26_N." << endl;
	}
	ofstream outfile__array_synapses_26_sources;
	outfile__array_synapses_26_sources.open("results\\_array_synapses_26_sources_-7146740845820432968", ios::binary | ios::out);
	if(outfile__array_synapses_26_sources.is_open())
	{
		outfile__array_synapses_26_sources.write(reinterpret_cast<char*>(_array_synapses_26_sources), 512*sizeof(_array_synapses_26_sources[0]));
		outfile__array_synapses_26_sources.close();
	} else
	{
		std::cout << "Error writing output file for _array_synapses_26_sources." << endl;
	}
	ofstream outfile__array_synapses_26_targets;
	outfile__array_synapses_26_targets.open("results\\_array_synapses_26_targets_3616139505268157054", ios::binary | ios::out);
	if(outfile__array_synapses_26_targets.is_open())
	{
		outfile__array_synapses_26_targets.write(reinterpret_cast<char*>(_array_synapses_26_targets), 512*sizeof(_array_synapses_26_targets[0]));
		outfile__array_synapses_26_targets.close();
	} else
	{
		std::cout << "Error writing output file for _array_synapses_26_targets." << endl;
	}
	ofstream outfile__array_synapses_27_N;
	outfile__array_synapses_27_N.open("results\\_array_synapses_27_N_-1142696334538811448", ios::binary | ios::out);
	if(outfile__array_synapses_27_N.is_open())
	{
		outfile__array_synapses_27_N.write(reinterpret_cast<char*>(_array_synapses_27_N), 1*sizeof(_array_synapses_27_N[0]));
		outfile__array_synapses_27_N.close();
	} else
	{
		std::cout << "Error writing output file for _array_synapses_27_N." << endl;
	}
	ofstream outfile__array_synapses_27_sources;
	outfile__array_synapses_27_sources.open("results\\_array_synapses_27_sources_-5899207117999466999", ios::binary | ios::out);
	if(outfile__array_synapses_27_sources.is_open())
	{
		outfile__array_synapses_27_sources.write(reinterpret_cast<char*>(_array_synapses_27_sources), 510*sizeof(_array_synapses_27_sources[0]));
		outfile__array_synapses_27_sources.close();
	} else
	{
		std::cout << "Error writing output file for _array_synapses_27_sources." << endl;
	}
	ofstream outfile__array_synapses_27_targets;
	outfile__array_synapses_27_targets.open("results\\_array_synapses_27_targets_1197058164494674178", ios::binary | ios::out);
	if(outfile__array_synapses_27_targets.is_open())
	{
		outfile__array_synapses_27_targets.write(reinterpret_cast<char*>(_array_synapses_27_targets), 510*sizeof(_array_synapses_27_targets[0]));
		outfile__array_synapses_27_targets.close();
	} else
	{
		std::cout << "Error writing output file for _array_synapses_27_targets." << endl;
	}
	ofstream outfile__array_synapses_28_N;
	outfile__array_synapses_28_N.open("results\\_array_synapses_28_N_-1073626896121451965", ios::binary | ios::out);
	if(outfile__array_synapses_28_N.is_open())
	{
		outfile__array_synapses_28_N.write(reinterpret_cast<char*>(_array_synapses_28_N), 1*sizeof(_array_synapses_28_N[0]));
		outfile__array_synapses_28_N.close();
	} else
	{
		std::cout << "Error writing output file for _array_synapses_28_N." << endl;
	}
	ofstream outfile__array_synapses_28_sources;
	outfile__array_synapses_28_sources.open("results\\_array_synapses_28_sources_-8559308106732579149", ios::binary | ios::out);
	if(outfile__array_synapses_28_sources.is_open())
	{
		outfile__array_synapses_28_sources.write(reinterpret_cast<char*>(_array_synapses_28_sources), 204*sizeof(_array_synapses_28_sources[0]));
		outfile__array_synapses_28_sources.close();
	} else
	{
		std::cout << "Error writing output file for _array_synapses_28_sources." << endl;
	}
	ofstream outfile__array_synapses_28_targets;
	outfile__array_synapses_28_targets.open("results\\_array_synapses_28_targets_-5057996566933985946", ios::binary | ios::out);
	if(outfile__array_synapses_28_targets.is_open())
	{
		outfile__array_synapses_28_targets.write(reinterpret_cast<char*>(_array_synapses_28_targets), 204*sizeof(_array_synapses_28_targets[0]));
		outfile__array_synapses_28_targets.close();
	} else
	{
		std::cout << "Error writing output file for _array_synapses_28_targets." << endl;
	}
	ofstream outfile__array_synapses_29_N;
	outfile__array_synapses_29_N.open("results\\_array_synapses_29_N_2079126256926663186", ios::binary | ios::out);
	if(outfile__array_synapses_29_N.is_open())
	{
		outfile__array_synapses_29_N.write(reinterpret_cast<char*>(_array_synapses_29_N), 1*sizeof(_array_synapses_29_N[0]));
		outfile__array_synapses_29_N.close();
	} else
	{
		std::cout << "Error writing output file for _array_synapses_29_N." << endl;
	}
	ofstream outfile__array_synapses_29_sources;
	outfile__array_synapses_29_sources.open("results\\_array_synapses_29_sources_6820139085837112721", ios::binary | ios::out);
	if(outfile__array_synapses_29_sources.is_open())
	{
		outfile__array_synapses_29_sources.write(reinterpret_cast<char*>(_array_synapses_29_sources), 234*sizeof(_array_synapses_29_sources[0]));
		outfile__array_synapses_29_sources.close();
	} else
	{
		std::cout << "Error writing output file for _array_synapses_29_sources." << endl;
	}
	ofstream outfile__array_synapses_29_targets;
	outfile__array_synapses_29_targets.open("results\\_array_synapses_29_targets_5525791234561109204", ios::binary | ios::out);
	if(outfile__array_synapses_29_targets.is_open())
	{
		outfile__array_synapses_29_targets.write(reinterpret_cast<char*>(_array_synapses_29_targets), 234*sizeof(_array_synapses_29_targets[0]));
		outfile__array_synapses_29_targets.close();
	} else
	{
		std::cout << "Error writing output file for _array_synapses_29_targets." << endl;
	}
	ofstream outfile__array_synapses_2_N;
	outfile__array_synapses_2_N.open("results\\_array_synapses_2_N_-3609917260023218731", ios::binary | ios::out);
	if(outfile__array_synapses_2_N.is_open())
	{
		outfile__array_synapses_2_N.write(reinterpret_cast<char*>(_array_synapses_2_N), 1*sizeof(_array_synapses_2_N[0]));
		outfile__array_synapses_2_N.close();
	} else
	{
		std::cout << "Error writing output file for _array_synapses_2_N." << endl;
	}
	ofstream outfile__array_synapses_2_sources;
	outfile__array_synapses_2_sources.open("results\\_array_synapses_2_sources_8459321261950244200", ios::binary | ios::out);
	if(outfile__array_synapses_2_sources.is_open())
	{
		outfile__array_synapses_2_sources.write(reinterpret_cast<char*>(_array_synapses_2_sources), 6336*sizeof(_array_synapses_2_sources[0]));
		outfile__array_synapses_2_sources.close();
	} else
	{
		std::cout << "Error writing output file for _array_synapses_2_sources." << endl;
	}
	ofstream outfile__array_synapses_2_targets;
	outfile__array_synapses_2_targets.open("results\\_array_synapses_2_targets_4314008392106518479", ios::binary | ios::out);
	if(outfile__array_synapses_2_targets.is_open())
	{
		outfile__array_synapses_2_targets.write(reinterpret_cast<char*>(_array_synapses_2_targets), 6336*sizeof(_array_synapses_2_targets[0]));
		outfile__array_synapses_2_targets.close();
	} else
	{
		std::cout << "Error writing output file for _array_synapses_2_targets." << endl;
	}
	ofstream outfile__array_synapses_30_N;
	outfile__array_synapses_30_N.open("results\\_array_synapses_30_N_6406756918509379101", ios::binary | ios::out);
	if(outfile__array_synapses_30_N.is_open())
	{
		outfile__array_synapses_30_N.write(reinterpret_cast<char*>(_array_synapses_30_N), 1*sizeof(_array_synapses_30_N[0]));
		outfile__array_synapses_30_N.close();
	} else
	{
		std::cout << "Error writing output file for _array_synapses_30_N." << endl;
	}
	ofstream outfile__array_synapses_30_sources;
	outfile__array_synapses_30_sources.open("results\\_array_synapses_30_sources_-8039566096768923519", ios::binary | ios::out);
	if(outfile__array_synapses_30_sources.is_open())
	{
		outfile__array_synapses_30_sources.write(reinterpret_cast<char*>(_array_synapses_30_sources), 168*sizeof(_array_synapses_30_sources[0]));
		outfile__array_synapses_30_sources.close();
	} else
	{
		std::cout << "Error writing output file for _array_synapses_30_sources." << endl;
	}
	ofstream outfile__array_synapses_30_targets;
	outfile__array_synapses_30_targets.open("results\\_array_synapses_30_targets_3368689966122854060", ios::binary | ios::out);
	if(outfile__array_synapses_30_targets.is_open())
	{
		outfile__array_synapses_30_targets.write(reinterpret_cast<char*>(_array_synapses_30_targets), 168*sizeof(_array_synapses_30_targets[0]));
		outfile__array_synapses_30_targets.close();
	} else
	{
		std::cout << "Error writing output file for _array_synapses_30_targets." << endl;
	}
	ofstream outfile__array_synapses_31_N;
	outfile__array_synapses_31_N.open("results\\_array_synapses_31_N_1967786755421625684", ios::binary | ios::out);
	if(outfile__array_synapses_31_N.is_open())
	{
		outfile__array_synapses_31_N.write(reinterpret_cast<char*>(_array_synapses_31_N), 1*sizeof(_array_synapses_31_N[0]));
		outfile__array_synapses_31_N.close();
	} else
	{
		std::cout << "Error writing output file for _array_synapses_31_N." << endl;
	}
	ofstream outfile__array_synapses_31_sources;
	outfile__array_synapses_31_sources.open("results\\_array_synapses_31_sources_-216618384967005441", ios::binary | ios::out);
	if(outfile__array_synapses_31_sources.is_open())
	{
		outfile__array_synapses_31_sources.write(reinterpret_cast<char*>(_array_synapses_31_sources), 21*sizeof(_array_synapses_31_sources[0]));
		outfile__array_synapses_31_sources.close();
	} else
	{
		std::cout << "Error writing output file for _array_synapses_31_sources." << endl;
	}
	ofstream outfile__array_synapses_31_targets;
	outfile__array_synapses_31_targets.open("results\\_array_synapses_31_targets_-336686106868744781", ios::binary | ios::out);
	if(outfile__array_synapses_31_targets.is_open())
	{
		outfile__array_synapses_31_targets.write(reinterpret_cast<char*>(_array_synapses_31_targets), 21*sizeof(_array_synapses_31_targets[0]));
		outfile__array_synapses_31_targets.close();
	} else
	{
		std::cout << "Error writing output file for _array_synapses_31_targets." << endl;
	}
	ofstream outfile__array_synapses_32_N;
	outfile__array_synapses_32_N.open("results\\_array_synapses_32_N_2099591638636351349", ios::binary | ios::out);
	if(outfile__array_synapses_32_N.is_open())
	{
		outfile__array_synapses_32_N.write(reinterpret_cast<char*>(_array_synapses_32_N), 1*sizeof(_array_synapses_32_N[0]));
		outfile__array_synapses_32_N.close();
	} else
	{
		std::cout << "Error writing output file for _array_synapses_32_N." << endl;
	}
	ofstream outfile__array_synapses_32_sources;
	outfile__array_synapses_32_sources.open("results\\_array_synapses_32_sources_1318632102269492285", ios::binary | ios::out);
	if(outfile__array_synapses_32_sources.is_open())
	{
		outfile__array_synapses_32_sources.write(reinterpret_cast<char*>(_array_synapses_32_sources), 27*sizeof(_array_synapses_32_sources[0]));
		outfile__array_synapses_32_sources.close();
	} else
	{
		std::cout << "Error writing output file for _array_synapses_32_sources." << endl;
	}
	ofstream outfile__array_synapses_32_targets;
	outfile__array_synapses_32_targets.open("results\\_array_synapses_32_targets_-3070933251298585993", ios::binary | ios::out);
	if(outfile__array_synapses_32_targets.is_open())
	{
		outfile__array_synapses_32_targets.write(reinterpret_cast<char*>(_array_synapses_32_targets), 27*sizeof(_array_synapses_32_targets[0]));
		outfile__array_synapses_32_targets.close();
	} else
	{
		std::cout << "Error writing output file for _array_synapses_32_targets." << endl;
	}
	ofstream outfile__array_synapses_33_N;
	outfile__array_synapses_33_N.open("results\\_array_synapses_33_N_852374131128585045", ios::binary | ios::out);
	if(outfile__array_synapses_33_N.is_open())
	{
		outfile__array_synapses_33_N.write(reinterpret_cast<char*>(_array_synapses_33_N), 1*sizeof(_array_synapses_33_N[0]));
		outfile__array_synapses_33_N.close();
	} else
	{
		std::cout << "Error writing output file for _array_synapses_33_N." << endl;
	}
	ofstream outfile__array_synapses_33_sources;
	outfile__array_synapses_33_sources.open("results\\_array_synapses_33_sources_-1065086385474481311", ios::binary | ios::out);
	if(outfile__array_synapses_33_sources.is_open())
	{
		outfile__array_synapses_33_sources.write(reinterpret_cast<char*>(_array_synapses_33_sources), 333*sizeof(_array_synapses_33_sources[0]));
		outfile__array_synapses_33_sources.close();
	} else
	{
		std::cout << "Error writing output file for _array_synapses_33_sources." << endl;
	}
	ofstream outfile__array_synapses_33_targets;
	outfile__array_synapses_33_targets.open("results\\_array_synapses_33_targets_-4643072678386117424", ios::binary | ios::out);
	if(outfile__array_synapses_33_targets.is_open())
	{
		outfile__array_synapses_33_targets.write(reinterpret_cast<char*>(_array_synapses_33_targets), 333*sizeof(_array_synapses_33_targets[0]));
		outfile__array_synapses_33_targets.close();
	} else
	{
		std::cout << "Error writing output file for _array_synapses_33_targets." << endl;
	}
	ofstream outfile__array_synapses_34_N;
	outfile__array_synapses_34_N.open("results\\_array_synapses_34_N_155062366419730206", ios::binary | ios::out);
	if(outfile__array_synapses_34_N.is_open())
	{
		outfile__array_synapses_34_N.write(reinterpret_cast<char*>(_array_synapses_34_N), 1*sizeof(_array_synapses_34_N[0]));
		outfile__array_synapses_34_N.close();
	} else
	{
		std::cout << "Error writing output file for _array_synapses_34_N." << endl;
	}
	ofstream outfile__array_synapses_34_sources;
	outfile__array_synapses_34_sources.open("results\\_array_synapses_34_sources_619343206516312331", ios::binary | ios::out);
	if(outfile__array_synapses_34_sources.is_open())
	{
		outfile__array_synapses_34_sources.write(reinterpret_cast<char*>(_array_synapses_34_sources), 333*sizeof(_array_synapses_34_sources[0]));
		outfile__array_synapses_34_sources.close();
	} else
	{
		std::cout << "Error writing output file for _array_synapses_34_sources." << endl;
	}
	ofstream outfile__array_synapses_34_targets;
	outfile__array_synapses_34_targets.open("results\\_array_synapses_34_targets_-752516836920811056", ios::binary | ios::out);
	if(outfile__array_synapses_34_targets.is_open())
	{
		outfile__array_synapses_34_targets.write(reinterpret_cast<char*>(_array_synapses_34_targets), 333*sizeof(_array_synapses_34_targets[0]));
		outfile__array_synapses_34_targets.close();
	} else
	{
		std::cout << "Error writing output file for _array_synapses_34_targets." << endl;
	}
	ofstream outfile__array_synapses_35_N;
	outfile__array_synapses_35_N.open("results\\_array_synapses_35_N_7883917955408006337", ios::binary | ios::out);
	if(outfile__array_synapses_35_N.is_open())
	{
		outfile__array_synapses_35_N.write(reinterpret_cast<char*>(_array_synapses_35_N), 1*sizeof(_array_synapses_35_N[0]));
		outfile__array_synapses_35_N.close();
	} else
	{
		std::cout << "Error writing output file for _array_synapses_35_N." << endl;
	}
	ofstream outfile__array_synapses_35_sources;
	outfile__array_synapses_35_sources.open("results\\_array_synapses_35_sources_-5396875033503998570", ios::binary | ios::out);
	if(outfile__array_synapses_35_sources.is_open())
	{
		outfile__array_synapses_35_sources.write(reinterpret_cast<char*>(_array_synapses_35_sources), 105*sizeof(_array_synapses_35_sources[0]));
		outfile__array_synapses_35_sources.close();
	} else
	{
		std::cout << "Error writing output file for _array_synapses_35_sources." << endl;
	}
	ofstream outfile__array_synapses_35_targets;
	outfile__array_synapses_35_targets.open("results\\_array_synapses_35_targets_475914081711324919", ios::binary | ios::out);
	if(outfile__array_synapses_35_targets.is_open())
	{
		outfile__array_synapses_35_targets.write(reinterpret_cast<char*>(_array_synapses_35_targets), 105*sizeof(_array_synapses_35_targets[0]));
		outfile__array_synapses_35_targets.close();
	} else
	{
		std::cout << "Error writing output file for _array_synapses_35_targets." << endl;
	}
	ofstream outfile__array_synapses_36_N;
	outfile__array_synapses_36_N.open("results\\_array_synapses_36_N_-544351885848671891", ios::binary | ios::out);
	if(outfile__array_synapses_36_N.is_open())
	{
		outfile__array_synapses_36_N.write(reinterpret_cast<char*>(_array_synapses_36_N), 1*sizeof(_array_synapses_36_N[0]));
		outfile__array_synapses_36_N.close();
	} else
	{
		std::cout << "Error writing output file for _array_synapses_36_N." << endl;
	}
	ofstream outfile__array_synapses_36_sources;
	outfile__array_synapses_36_sources.open("results\\_array_synapses_36_sources_4693837745935592555", ios::binary | ios::out);
	if(outfile__array_synapses_36_sources.is_open())
	{
		outfile__array_synapses_36_sources.write(reinterpret_cast<char*>(_array_synapses_36_sources), 78*sizeof(_array_synapses_36_sources[0]));
		outfile__array_synapses_36_sources.close();
	} else
	{
		std::cout << "Error writing output file for _array_synapses_36_sources." << endl;
	}
	ofstream outfile__array_synapses_36_targets;
	outfile__array_synapses_36_targets.open("results\\_array_synapses_36_targets_4351347371864507490", ios::binary | ios::out);
	if(outfile__array_synapses_36_targets.is_open())
	{
		outfile__array_synapses_36_targets.write(reinterpret_cast<char*>(_array_synapses_36_targets), 78*sizeof(_array_synapses_36_targets[0]));
		outfile__array_synapses_36_targets.close();
	} else
	{
		std::cout << "Error writing output file for _array_synapses_36_targets." << endl;
	}
	ofstream outfile__array_synapses_37_N;
	outfile__array_synapses_37_N.open("results\\_array_synapses_37_N_-6982327603799725433", ios::binary | ios::out);
	if(outfile__array_synapses_37_N.is_open())
	{
		outfile__array_synapses_37_N.write(reinterpret_cast<char*>(_array_synapses_37_N), 1*sizeof(_array_synapses_37_N[0]));
		outfile__array_synapses_37_N.close();
	} else
	{
		std::cout << "Error writing output file for _array_synapses_37_N." << endl;
	}
	ofstream outfile__array_synapses_37_sources;
	outfile__array_synapses_37_sources.open("results\\_array_synapses_37_sources_-3542004697642825556", ios::binary | ios::out);
	if(outfile__array_synapses_37_sources.is_open())
	{
		outfile__array_synapses_37_sources.write(reinterpret_cast<char*>(_array_synapses_37_sources), 66*sizeof(_array_synapses_37_sources[0]));
		outfile__array_synapses_37_sources.close();
	} else
	{
		std::cout << "Error writing output file for _array_synapses_37_sources." << endl;
	}
	ofstream outfile__array_synapses_37_targets;
	outfile__array_synapses_37_targets.open("results\\_array_synapses_37_targets_7422396906939395724", ios::binary | ios::out);
	if(outfile__array_synapses_37_targets.is_open())
	{
		outfile__array_synapses_37_targets.write(reinterpret_cast<char*>(_array_synapses_37_targets), 66*sizeof(_array_synapses_37_targets[0]));
		outfile__array_synapses_37_targets.close();
	} else
	{
		std::cout << "Error writing output file for _array_synapses_37_targets." << endl;
	}
	ofstream outfile__array_synapses_3_N;
	outfile__array_synapses_3_N.open("results\\_array_synapses_3_N_-7210235203420881544", ios::binary | ios::out);
	if(outfile__array_synapses_3_N.is_open())
	{
		outfile__array_synapses_3_N.write(reinterpret_cast<char*>(_array_synapses_3_N), 1*sizeof(_array_synapses_3_N[0]));
		outfile__array_synapses_3_N.close();
	} else
	{
		std::cout << "Error writing output file for _array_synapses_3_N." << endl;
	}
	ofstream outfile__array_synapses_3_sources;
	outfile__array_synapses_3_sources.open("results\\_array_synapses_3_sources_-148325138757069071", ios::binary | ios::out);
	if(outfile__array_synapses_3_sources.is_open())
	{
		outfile__array_synapses_3_sources.write(reinterpret_cast<char*>(_array_synapses_3_sources), 1938*sizeof(_array_synapses_3_sources[0]));
		outfile__array_synapses_3_sources.close();
	} else
	{
		std::cout << "Error writing output file for _array_synapses_3_sources." << endl;
	}
	ofstream outfile__array_synapses_3_targets;
	outfile__array_synapses_3_targets.open("results\\_array_synapses_3_targets_545653868026923405", ios::binary | ios::out);
	if(outfile__array_synapses_3_targets.is_open())
	{
		outfile__array_synapses_3_targets.write(reinterpret_cast<char*>(_array_synapses_3_targets), 1938*sizeof(_array_synapses_3_targets[0]));
		outfile__array_synapses_3_targets.close();
	} else
	{
		std::cout << "Error writing output file for _array_synapses_3_targets." << endl;
	}
	ofstream outfile__array_synapses_4_N;
	outfile__array_synapses_4_N.open("results\\_array_synapses_4_N_1274054717715557876", ios::binary | ios::out);
	if(outfile__array_synapses_4_N.is_open())
	{
		outfile__array_synapses_4_N.write(reinterpret_cast<char*>(_array_synapses_4_N), 1*sizeof(_array_synapses_4_N[0]));
		outfile__array_synapses_4_N.close();
	} else
	{
		std::cout << "Error writing output file for _array_synapses_4_N." << endl;
	}
	ofstream outfile__array_synapses_4_sources;
	outfile__array_synapses_4_sources.open("results\\_array_synapses_4_sources_-1227649039838751469", ios::binary | ios::out);
	if(outfile__array_synapses_4_sources.is_open())
	{
		outfile__array_synapses_4_sources.write(reinterpret_cast<char*>(_array_synapses_4_sources), 2588*sizeof(_array_synapses_4_sources[0]));
		outfile__array_synapses_4_sources.close();
	} else
	{
		std::cout << "Error writing output file for _array_synapses_4_sources." << endl;
	}
	ofstream outfile__array_synapses_4_targets;
	outfile__array_synapses_4_targets.open("results\\_array_synapses_4_targets_-8569529460637164272", ios::binary | ios::out);
	if(outfile__array_synapses_4_targets.is_open())
	{
		outfile__array_synapses_4_targets.write(reinterpret_cast<char*>(_array_synapses_4_targets), 2588*sizeof(_array_synapses_4_targets[0]));
		outfile__array_synapses_4_targets.close();
	} else
	{
		std::cout << "Error writing output file for _array_synapses_4_targets." << endl;
	}
	ofstream outfile__array_synapses_5_N;
	outfile__array_synapses_5_N.open("results\\_array_synapses_5_N_1941578055024493288", ios::binary | ios::out);
	if(outfile__array_synapses_5_N.is_open())
	{
		outfile__array_synapses_5_N.write(reinterpret_cast<char*>(_array_synapses_5_N), 1*sizeof(_array_synapses_5_N[0]));
		outfile__array_synapses_5_N.close();
	} else
	{
		std::cout << "Error writing output file for _array_synapses_5_N." << endl;
	}
	ofstream outfile__array_synapses_5_sources;
	outfile__array_synapses_5_sources.open("results\\_array_synapses_5_sources_4468457627316076817", ios::binary | ios::out);
	if(outfile__array_synapses_5_sources.is_open())
	{
		outfile__array_synapses_5_sources.write(reinterpret_cast<char*>(_array_synapses_5_sources), 11697*sizeof(_array_synapses_5_sources[0]));
		outfile__array_synapses_5_sources.close();
	} else
	{
		std::cout << "Error writing output file for _array_synapses_5_sources." << endl;
	}
	ofstream outfile__array_synapses_5_targets;
	outfile__array_synapses_5_targets.open("results\\_array_synapses_5_targets_-3520144189607568196", ios::binary | ios::out);
	if(outfile__array_synapses_5_targets.is_open())
	{
		outfile__array_synapses_5_targets.write(reinterpret_cast<char*>(_array_synapses_5_targets), 11697*sizeof(_array_synapses_5_targets[0]));
		outfile__array_synapses_5_targets.close();
	} else
	{
		std::cout << "Error writing output file for _array_synapses_5_targets." << endl;
	}
	ofstream outfile__array_synapses_6_N;
	outfile__array_synapses_6_N.open("results\\_array_synapses_6_N_-8598682625609288262", ios::binary | ios::out);
	if(outfile__array_synapses_6_N.is_open())
	{
		outfile__array_synapses_6_N.write(reinterpret_cast<char*>(_array_synapses_6_N), 1*sizeof(_array_synapses_6_N[0]));
		outfile__array_synapses_6_N.close();
	} else
	{
		std::cout << "Error writing output file for _array_synapses_6_N." << endl;
	}
	ofstream outfile__array_synapses_6_sources;
	outfile__array_synapses_6_sources.open("results\\_array_synapses_6_sources_-4231489486121087461", ios::binary | ios::out);
	if(outfile__array_synapses_6_sources.is_open())
	{
		outfile__array_synapses_6_sources.write(reinterpret_cast<char*>(_array_synapses_6_sources), 1384*sizeof(_array_synapses_6_sources[0]));
		outfile__array_synapses_6_sources.close();
	} else
	{
		std::cout << "Error writing output file for _array_synapses_6_sources." << endl;
	}
	ofstream outfile__array_synapses_6_targets;
	outfile__array_synapses_6_targets.open("results\\_array_synapses_6_targets_-1113288937549255176", ios::binary | ios::out);
	if(outfile__array_synapses_6_targets.is_open())
	{
		outfile__array_synapses_6_targets.write(reinterpret_cast<char*>(_array_synapses_6_targets), 1384*sizeof(_array_synapses_6_targets[0]));
		outfile__array_synapses_6_targets.close();
	} else
	{
		std::cout << "Error writing output file for _array_synapses_6_targets." << endl;
	}
	ofstream outfile__array_synapses_7_N;
	outfile__array_synapses_7_N.open("results\\_array_synapses_7_N_7005336055735785237", ios::binary | ios::out);
	if(outfile__array_synapses_7_N.is_open())
	{
		outfile__array_synapses_7_N.write(reinterpret_cast<char*>(_array_synapses_7_N), 1*sizeof(_array_synapses_7_N[0]));
		outfile__array_synapses_7_N.close();
	} else
	{
		std::cout << "Error writing output file for _array_synapses_7_N." << endl;
	}
	ofstream outfile__array_synapses_7_sources;
	outfile__array_synapses_7_sources.open("results\\_array_synapses_7_sources_4597278160900428671", ios::binary | ios::out);
	if(outfile__array_synapses_7_sources.is_open())
	{
		outfile__array_synapses_7_sources.write(reinterpret_cast<char*>(_array_synapses_7_sources), 224*sizeof(_array_synapses_7_sources[0]));
		outfile__array_synapses_7_sources.close();
	} else
	{
		std::cout << "Error writing output file for _array_synapses_7_sources." << endl;
	}
	ofstream outfile__array_synapses_7_targets;
	outfile__array_synapses_7_targets.open("results\\_array_synapses_7_targets_-5023188381905438124", ios::binary | ios::out);
	if(outfile__array_synapses_7_targets.is_open())
	{
		outfile__array_synapses_7_targets.write(reinterpret_cast<char*>(_array_synapses_7_targets), 224*sizeof(_array_synapses_7_targets[0]));
		outfile__array_synapses_7_targets.close();
	} else
	{
		std::cout << "Error writing output file for _array_synapses_7_targets." << endl;
	}
	ofstream outfile__array_synapses_8_N;
	outfile__array_synapses_8_N.open("results\\_array_synapses_8_N_-6872908603288752172", ios::binary | ios::out);
	if(outfile__array_synapses_8_N.is_open())
	{
		outfile__array_synapses_8_N.write(reinterpret_cast<char*>(_array_synapses_8_N), 1*sizeof(_array_synapses_8_N[0]));
		outfile__array_synapses_8_N.close();
	} else
	{
		std::cout << "Error writing output file for _array_synapses_8_N." << endl;
	}
	ofstream outfile__array_synapses_8_sources;
	outfile__array_synapses_8_sources.open("results\\_array_synapses_8_sources_6116964035258975489", ios::binary | ios::out);
	if(outfile__array_synapses_8_sources.is_open())
	{
		outfile__array_synapses_8_sources.write(reinterpret_cast<char*>(_array_synapses_8_sources), 108*sizeof(_array_synapses_8_sources[0]));
		outfile__array_synapses_8_sources.close();
	} else
	{
		std::cout << "Error writing output file for _array_synapses_8_sources." << endl;
	}
	ofstream outfile__array_synapses_8_targets;
	outfile__array_synapses_8_targets.open("results\\_array_synapses_8_targets_-4370500408284399837", ios::binary | ios::out);
	if(outfile__array_synapses_8_targets.is_open())
	{
		outfile__array_synapses_8_targets.write(reinterpret_cast<char*>(_array_synapses_8_targets), 108*sizeof(_array_synapses_8_targets[0]));
		outfile__array_synapses_8_targets.close();
	} else
	{
		std::cout << "Error writing output file for _array_synapses_8_targets." << endl;
	}
	ofstream outfile__array_synapses_9_N;
	outfile__array_synapses_9_N.open("results\\_array_synapses_9_N_1731608307477615942", ios::binary | ios::out);
	if(outfile__array_synapses_9_N.is_open())
	{
		outfile__array_synapses_9_N.write(reinterpret_cast<char*>(_array_synapses_9_N), 1*sizeof(_array_synapses_9_N[0]));
		outfile__array_synapses_9_N.close();
	} else
	{
		std::cout << "Error writing output file for _array_synapses_9_N." << endl;
	}
	ofstream outfile__array_synapses_9_sources;
	outfile__array_synapses_9_sources.open("results\\_array_synapses_9_sources_4843115749610560465", ios::binary | ios::out);
	if(outfile__array_synapses_9_sources.is_open())
	{
		outfile__array_synapses_9_sources.write(reinterpret_cast<char*>(_array_synapses_9_sources), 1854*sizeof(_array_synapses_9_sources[0]));
		outfile__array_synapses_9_sources.close();
	} else
	{
		std::cout << "Error writing output file for _array_synapses_9_sources." << endl;
	}
	ofstream outfile__array_synapses_9_targets;
	outfile__array_synapses_9_targets.open("results\\_array_synapses_9_targets_1630883067772258403", ios::binary | ios::out);
	if(outfile__array_synapses_9_targets.is_open())
	{
		outfile__array_synapses_9_targets.write(reinterpret_cast<char*>(_array_synapses_9_targets), 1854*sizeof(_array_synapses_9_targets[0]));
		outfile__array_synapses_9_targets.close();
	} else
	{
		std::cout << "Error writing output file for _array_synapses_9_targets." << endl;
	}
	ofstream outfile__array_synapses_N;
	outfile__array_synapses_N.open("results\\_array_synapses_N_1554142969677913142", ios::binary | ios::out);
	if(outfile__array_synapses_N.is_open())
	{
		outfile__array_synapses_N.write(reinterpret_cast<char*>(_array_synapses_N), 1*sizeof(_array_synapses_N[0]));
		outfile__array_synapses_N.close();
	} else
	{
		std::cout << "Error writing output file for _array_synapses_N." << endl;
	}

	ofstream outfile__dynamic_array_spikegeneratorgroup__timebins;
	outfile__dynamic_array_spikegeneratorgroup__timebins.open("results\\_dynamic_array_spikegeneratorgroup__timebins_5986820599884839937", ios::binary | ios::out);
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
	outfile__dynamic_array_spikegeneratorgroup_neuron_index.open("results\\_dynamic_array_spikegeneratorgroup_neuron_index_5475334512465896411", ios::binary | ios::out);
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
	outfile__dynamic_array_spikegeneratorgroup_spike_number.open("results\\_dynamic_array_spikegeneratorgroup_spike_number_-6240308399423484237", ios::binary | ios::out);
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
	outfile__dynamic_array_spikegeneratorgroup_spike_time.open("results\\_dynamic_array_spikegeneratorgroup_spike_time_-5215062427686759259", ios::binary | ios::out);
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
	outfile__dynamic_array_spikemonitor_1_i.open("results\\_dynamic_array_spikemonitor_1_i_7422260847782388794", ios::binary | ios::out);
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
	outfile__dynamic_array_spikemonitor_1_t.open("results\\_dynamic_array_spikemonitor_1_t_-7755008904881283", ios::binary | ios::out);
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
	outfile__dynamic_array_spikemonitor_2_i.open("results\\_dynamic_array_spikemonitor_2_i_6279233917514931584", ios::binary | ios::out);
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
	outfile__dynamic_array_spikemonitor_2_t.open("results\\_dynamic_array_spikemonitor_2_t_-289493325416729141", ios::binary | ios::out);
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
	outfile__dynamic_array_spikemonitor_3_i.open("results\\_dynamic_array_spikemonitor_3_i_570104954172684493", ios::binary | ios::out);
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
	outfile__dynamic_array_spikemonitor_3_t.open("results\\_dynamic_array_spikemonitor_3_t_4205007503056166261", ios::binary | ios::out);
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
	outfile__dynamic_array_spikemonitor_4_i.open("results\\_dynamic_array_spikemonitor_4_i_-7033109522332546995", ios::binary | ios::out);
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
	outfile__dynamic_array_spikemonitor_4_t.open("results\\_dynamic_array_spikemonitor_4_t_-5761539165959409282", ios::binary | ios::out);
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
	outfile__dynamic_array_spikemonitor_5_i.open("results\\_dynamic_array_spikemonitor_5_i_7687862844488785051", ios::binary | ios::out);
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
	outfile__dynamic_array_spikemonitor_5_t.open("results\\_dynamic_array_spikemonitor_5_t_3075311437501864986", ios::binary | ios::out);
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
	outfile__dynamic_array_spikemonitor_i.open("results\\_dynamic_array_spikemonitor_i_-8495226008394554715", ios::binary | ios::out);
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
	outfile__dynamic_array_spikemonitor_t.open("results\\_dynamic_array_spikemonitor_t_-2042059968629126923", ios::binary | ios::out);
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
	outfile__dynamic_array_synapses_10__synaptic_post.open("results\\_dynamic_array_synapses_10__synaptic_post_635142256561421633", ios::binary | ios::out);
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
	outfile__dynamic_array_synapses_10__synaptic_pre.open("results\\_dynamic_array_synapses_10__synaptic_pre_5447862875780037576", ios::binary | ios::out);
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
	outfile__dynamic_array_synapses_10_delay.open("results\\_dynamic_array_synapses_10_delay_-6886922494126110485", ios::binary | ios::out);
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
	outfile__dynamic_array_synapses_10_lastupdate.open("results\\_dynamic_array_synapses_10_lastupdate_-4726634885345814197", ios::binary | ios::out);
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
	outfile__dynamic_array_synapses_10_N_incoming.open("results\\_dynamic_array_synapses_10_N_incoming_4986803250159481030", ios::binary | ios::out);
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
	outfile__dynamic_array_synapses_10_N_outgoing.open("results\\_dynamic_array_synapses_10_N_outgoing_1401662601325506264", ios::binary | ios::out);
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
	outfile__dynamic_array_synapses_10_R.open("results\\_dynamic_array_synapses_10_R_-254151074005669151", ios::binary | ios::out);
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
	outfile__dynamic_array_synapses_10_wght.open("results\\_dynamic_array_synapses_10_wght_-3016103322046351868", ios::binary | ios::out);
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
	outfile__dynamic_array_synapses_11__synaptic_post.open("results\\_dynamic_array_synapses_11__synaptic_post_5516669230948146098", ios::binary | ios::out);
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
	outfile__dynamic_array_synapses_11__synaptic_pre.open("results\\_dynamic_array_synapses_11__synaptic_pre_-1118109356370928372", ios::binary | ios::out);
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
	outfile__dynamic_array_synapses_11_delay.open("results\\_dynamic_array_synapses_11_delay_-6098416947668949403", ios::binary | ios::out);
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
	outfile__dynamic_array_synapses_11_lastupdate.open("results\\_dynamic_array_synapses_11_lastupdate_8050418520367901372", ios::binary | ios::out);
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
	outfile__dynamic_array_synapses_11_N_incoming.open("results\\_dynamic_array_synapses_11_N_incoming_-5523947477043392693", ios::binary | ios::out);
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
	outfile__dynamic_array_synapses_11_N_outgoing.open("results\\_dynamic_array_synapses_11_N_outgoing_-7192781376194772562", ios::binary | ios::out);
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
	outfile__dynamic_array_synapses_11_R.open("results\\_dynamic_array_synapses_11_R_-8980206143659772867", ios::binary | ios::out);
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
	outfile__dynamic_array_synapses_11_wght.open("results\\_dynamic_array_synapses_11_wght_-190305513677505862", ios::binary | ios::out);
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
	outfile__dynamic_array_synapses_12__synaptic_post.open("results\\_dynamic_array_synapses_12__synaptic_post_-4534869052999394086", ios::binary | ios::out);
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
	outfile__dynamic_array_synapses_12__synaptic_pre.open("results\\_dynamic_array_synapses_12__synaptic_pre_-3941425226098177527", ios::binary | ios::out);
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
	outfile__dynamic_array_synapses_12_delay.open("results\\_dynamic_array_synapses_12_delay_-7808115927384139033", ios::binary | ios::out);
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
	outfile__dynamic_array_synapses_12_lastupdate.open("results\\_dynamic_array_synapses_12_lastupdate_-7252992263286998752", ios::binary | ios::out);
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
	outfile__dynamic_array_synapses_12_N_incoming.open("results\\_dynamic_array_synapses_12_N_incoming_338215787978169248", ios::binary | ios::out);
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
	outfile__dynamic_array_synapses_12_N_outgoing.open("results\\_dynamic_array_synapses_12_N_outgoing_-1174376947994576096", ios::binary | ios::out);
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
	outfile__dynamic_array_synapses_12_R.open("results\\_dynamic_array_synapses_12_R_5215541668849983530", ios::binary | ios::out);
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
	outfile__dynamic_array_synapses_12_wght.open("results\\_dynamic_array_synapses_12_wght_-5689504842007125315", ios::binary | ios::out);
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
	outfile__dynamic_array_synapses_13__synaptic_post.open("results\\_dynamic_array_synapses_13__synaptic_post_-1572040319407272379", ios::binary | ios::out);
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
	outfile__dynamic_array_synapses_13__synaptic_pre.open("results\\_dynamic_array_synapses_13__synaptic_pre_6682026262740488956", ios::binary | ios::out);
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
	outfile__dynamic_array_synapses_13_delay.open("results\\_dynamic_array_synapses_13_delay_3246368576452269069", ios::binary | ios::out);
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
	outfile__dynamic_array_synapses_13_lastupdate.open("results\\_dynamic_array_synapses_13_lastupdate_-2882251000732964599", ios::binary | ios::out);
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
	outfile__dynamic_array_synapses_13_N_incoming.open("results\\_dynamic_array_synapses_13_N_incoming_-603580418570397862", ios::binary | ios::out);
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
	outfile__dynamic_array_synapses_13_N_outgoing.open("results\\_dynamic_array_synapses_13_N_outgoing_-7724718389403676828", ios::binary | ios::out);
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
	outfile__dynamic_array_synapses_13_R.open("results\\_dynamic_array_synapses_13_R_4081624545817604200", ios::binary | ios::out);
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
	outfile__dynamic_array_synapses_13_wght.open("results\\_dynamic_array_synapses_13_wght_5588532360776040422", ios::binary | ios::out);
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
	outfile__dynamic_array_synapses_14__synaptic_post.open("results\\_dynamic_array_synapses_14__synaptic_post_8043553365220006263", ios::binary | ios::out);
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
	outfile__dynamic_array_synapses_14__synaptic_pre.open("results\\_dynamic_array_synapses_14__synaptic_pre_4262675601464827921", ios::binary | ios::out);
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
	outfile__dynamic_array_synapses_14_delay.open("results\\_dynamic_array_synapses_14_delay_-3570045343288999000", ios::binary | ios::out);
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
	outfile__dynamic_array_synapses_14_lastupdate.open("results\\_dynamic_array_synapses_14_lastupdate_4076924761804687406", ios::binary | ios::out);
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
	outfile__dynamic_array_synapses_14_N_incoming.open("results\\_dynamic_array_synapses_14_N_incoming_-7334618673924323432", ios::binary | ios::out);
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
	outfile__dynamic_array_synapses_14_N_outgoing.open("results\\_dynamic_array_synapses_14_N_outgoing_4291244843435096047", ios::binary | ios::out);
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
	outfile__dynamic_array_synapses_14_R.open("results\\_dynamic_array_synapses_14_R_8181986351814397609", ios::binary | ios::out);
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
	outfile__dynamic_array_synapses_14_wght.open("results\\_dynamic_array_synapses_14_wght_-2616531881216374676", ios::binary | ios::out);
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
	outfile__dynamic_array_synapses_15__synaptic_post.open("results\\_dynamic_array_synapses_15__synaptic_post_6108595386624902171", ios::binary | ios::out);
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
	outfile__dynamic_array_synapses_15__synaptic_pre.open("results\\_dynamic_array_synapses_15__synaptic_pre_7165739455882545582", ios::binary | ios::out);
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
	outfile__dynamic_array_synapses_15_delay.open("results\\_dynamic_array_synapses_15_delay_-9108413904859857726", ios::binary | ios::out);
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
	outfile__dynamic_array_synapses_15_lastupdate.open("results\\_dynamic_array_synapses_15_lastupdate_3589082456268161682", ios::binary | ios::out);
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
	outfile__dynamic_array_synapses_15_N_incoming.open("results\\_dynamic_array_synapses_15_N_incoming_-1121557576174356251", ios::binary | ios::out);
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
	outfile__dynamic_array_synapses_15_N_outgoing.open("results\\_dynamic_array_synapses_15_N_outgoing_-927492231544381600", ios::binary | ios::out);
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
	outfile__dynamic_array_synapses_15_R.open("results\\_dynamic_array_synapses_15_R_-714923865240444627", ios::binary | ios::out);
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
	outfile__dynamic_array_synapses_15_wght.open("results\\_dynamic_array_synapses_15_wght_4482536352330039759", ios::binary | ios::out);
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
	outfile__dynamic_array_synapses_16__synaptic_post.open("results\\_dynamic_array_synapses_16__synaptic_post_967040829823122016", ios::binary | ios::out);
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
	outfile__dynamic_array_synapses_16__synaptic_pre.open("results\\_dynamic_array_synapses_16__synaptic_pre_2729060702008006678", ios::binary | ios::out);
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
	outfile__dynamic_array_synapses_16_delay.open("results\\_dynamic_array_synapses_16_delay_74285386428362914", ios::binary | ios::out);
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
	outfile__dynamic_array_synapses_16_lastupdate.open("results\\_dynamic_array_synapses_16_lastupdate_-7134906959560425733", ios::binary | ios::out);
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
	outfile__dynamic_array_synapses_16_N_incoming.open("results\\_dynamic_array_synapses_16_N_incoming_5549504021911078281", ios::binary | ios::out);
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
	outfile__dynamic_array_synapses_16_N_outgoing.open("results\\_dynamic_array_synapses_16_N_outgoing_854151609432194803", ios::binary | ios::out);
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
	outfile__dynamic_array_synapses_16_R.open("results\\_dynamic_array_synapses_16_R_4713049284866064811", ios::binary | ios::out);
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
	outfile__dynamic_array_synapses_16_wght.open("results\\_dynamic_array_synapses_16_wght_-8465977985519943216", ios::binary | ios::out);
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
	outfile__dynamic_array_synapses_17__synaptic_post.open("results\\_dynamic_array_synapses_17__synaptic_post_7621637652842941670", ios::binary | ios::out);
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
	outfile__dynamic_array_synapses_17__synaptic_pre.open("results\\_dynamic_array_synapses_17__synaptic_pre_-7950647737542834636", ios::binary | ios::out);
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
	outfile__dynamic_array_synapses_17_delay.open("results\\_dynamic_array_synapses_17_delay_-9109310909018593336", ios::binary | ios::out);
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
	outfile__dynamic_array_synapses_17_lastupdate.open("results\\_dynamic_array_synapses_17_lastupdate_4770613615405824040", ios::binary | ios::out);
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
	outfile__dynamic_array_synapses_17_N_incoming.open("results\\_dynamic_array_synapses_17_N_incoming_4133878813659990156", ios::binary | ios::out);
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
	outfile__dynamic_array_synapses_17_N_outgoing.open("results\\_dynamic_array_synapses_17_N_outgoing_136264906552453843", ios::binary | ios::out);
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
	outfile__dynamic_array_synapses_17_R.open("results\\_dynamic_array_synapses_17_R_-5242369160811793979", ios::binary | ios::out);
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
	outfile__dynamic_array_synapses_17_wght.open("results\\_dynamic_array_synapses_17_wght_11788962234455408", ios::binary | ios::out);
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
	outfile__dynamic_array_synapses_18__synaptic_post.open("results\\_dynamic_array_synapses_18__synaptic_post_6207767054380087364", ios::binary | ios::out);
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
	outfile__dynamic_array_synapses_18__synaptic_pre.open("results\\_dynamic_array_synapses_18__synaptic_pre_-5419560907576357085", ios::binary | ios::out);
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
	outfile__dynamic_array_synapses_18_delay.open("results\\_dynamic_array_synapses_18_delay_489153203012296004", ios::binary | ios::out);
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
	outfile__dynamic_array_synapses_18_lastupdate.open("results\\_dynamic_array_synapses_18_lastupdate_-4514864374443250654", ios::binary | ios::out);
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
	outfile__dynamic_array_synapses_18_N_incoming.open("results\\_dynamic_array_synapses_18_N_incoming_-8955869865791534001", ios::binary | ios::out);
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
	outfile__dynamic_array_synapses_18_N_outgoing.open("results\\_dynamic_array_synapses_18_N_outgoing_3873908739066802595", ios::binary | ios::out);
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
	outfile__dynamic_array_synapses_18_R.open("results\\_dynamic_array_synapses_18_R_8793439286313676956", ios::binary | ios::out);
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
	outfile__dynamic_array_synapses_18_wght.open("results\\_dynamic_array_synapses_18_wght_3138658221205101140", ios::binary | ios::out);
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
	outfile__dynamic_array_synapses_19__synaptic_post.open("results\\_dynamic_array_synapses_19__synaptic_post_-1549129472473829482", ios::binary | ios::out);
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
	outfile__dynamic_array_synapses_19__synaptic_pre.open("results\\_dynamic_array_synapses_19__synaptic_pre_3078781494912627208", ios::binary | ios::out);
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
	outfile__dynamic_array_synapses_19_delay.open("results\\_dynamic_array_synapses_19_delay_-5160197598153807740", ios::binary | ios::out);
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
	outfile__dynamic_array_synapses_19_lastupdate.open("results\\_dynamic_array_synapses_19_lastupdate_6161842820048622045", ios::binary | ios::out);
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
	outfile__dynamic_array_synapses_19_N_incoming.open("results\\_dynamic_array_synapses_19_N_incoming_1824426552305122241", ios::binary | ios::out);
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
	outfile__dynamic_array_synapses_19_N_outgoing.open("results\\_dynamic_array_synapses_19_N_outgoing_-1317563990206811206", ios::binary | ios::out);
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
	outfile__dynamic_array_synapses_19_R.open("results\\_dynamic_array_synapses_19_R_-939977493597330447", ios::binary | ios::out);
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
	outfile__dynamic_array_synapses_19_wght.open("results\\_dynamic_array_synapses_19_wght_3042851850546334184", ios::binary | ios::out);
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
	outfile__dynamic_array_synapses_1__synaptic_post.open("results\\_dynamic_array_synapses_1__synaptic_post_-8902490448447502243", ios::binary | ios::out);
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
	outfile__dynamic_array_synapses_1__synaptic_pre.open("results\\_dynamic_array_synapses_1__synaptic_pre_4120312516366150252", ios::binary | ios::out);
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
	outfile__dynamic_array_synapses_1_delay.open("results\\_dynamic_array_synapses_1_delay_-6398132706229746034", ios::binary | ios::out);
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
	outfile__dynamic_array_synapses_1_lastupdate.open("results\\_dynamic_array_synapses_1_lastupdate_-8421494624776032447", ios::binary | ios::out);
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
	outfile__dynamic_array_synapses_1_N_incoming.open("results\\_dynamic_array_synapses_1_N_incoming_8935415995159910591", ios::binary | ios::out);
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
	outfile__dynamic_array_synapses_1_N_outgoing.open("results\\_dynamic_array_synapses_1_N_outgoing_4109173009481571405", ios::binary | ios::out);
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
	outfile__dynamic_array_synapses_1_R.open("results\\_dynamic_array_synapses_1_R_-62032696827071301", ios::binary | ios::out);
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
	outfile__dynamic_array_synapses_1_wght.open("results\\_dynamic_array_synapses_1_wght_-7953350037515313686", ios::binary | ios::out);
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
	outfile__dynamic_array_synapses_20__synaptic_post.open("results\\_dynamic_array_synapses_20__synaptic_post_-2358741167599363448", ios::binary | ios::out);
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
	outfile__dynamic_array_synapses_20__synaptic_pre.open("results\\_dynamic_array_synapses_20__synaptic_pre_-5753260120494607359", ios::binary | ios::out);
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
	outfile__dynamic_array_synapses_20_delay.open("results\\_dynamic_array_synapses_20_delay_-6765524623009551309", ios::binary | ios::out);
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
	outfile__dynamic_array_synapses_20_lastupdate.open("results\\_dynamic_array_synapses_20_lastupdate_8816375585034584191", ios::binary | ios::out);
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
	outfile__dynamic_array_synapses_20_N_incoming.open("results\\_dynamic_array_synapses_20_N_incoming_3636862113530121183", ios::binary | ios::out);
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
	outfile__dynamic_array_synapses_20_N_outgoing.open("results\\_dynamic_array_synapses_20_N_outgoing_-3695707381565561269", ios::binary | ios::out);
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
	outfile__dynamic_array_synapses_20_R.open("results\\_dynamic_array_synapses_20_R_-7199434789421340806", ios::binary | ios::out);
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
	outfile__dynamic_array_synapses_20_wght.open("results\\_dynamic_array_synapses_20_wght_6853214120680288353", ios::binary | ios::out);
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
	outfile__dynamic_array_synapses_21__synaptic_post.open("results\\_dynamic_array_synapses_21__synaptic_post_9106177377749759429", ios::binary | ios::out);
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
	outfile__dynamic_array_synapses_21__synaptic_pre.open("results\\_dynamic_array_synapses_21__synaptic_pre_453234748880414396", ios::binary | ios::out);
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
	outfile__dynamic_array_synapses_21_delay.open("results\\_dynamic_array_synapses_21_delay_-600025137917829723", ios::binary | ios::out);
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
	outfile__dynamic_array_synapses_21_lastupdate.open("results\\_dynamic_array_synapses_21_lastupdate_8054262370818855669", ios::binary | ios::out);
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
	outfile__dynamic_array_synapses_21_N_incoming.open("results\\_dynamic_array_synapses_21_N_incoming_6451393668904724406", ios::binary | ios::out);
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
	outfile__dynamic_array_synapses_21_N_outgoing.open("results\\_dynamic_array_synapses_21_N_outgoing_5653344137770806615", ios::binary | ios::out);
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
	outfile__dynamic_array_synapses_21_R.open("results\\_dynamic_array_synapses_21_R_3076690164978884562", ios::binary | ios::out);
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
	outfile__dynamic_array_synapses_21_wght.open("results\\_dynamic_array_synapses_21_wght_2118044851931419912", ios::binary | ios::out);
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
	outfile__dynamic_array_synapses_22__synaptic_post.open("results\\_dynamic_array_synapses_22__synaptic_post_-7487909031105282595", ios::binary | ios::out);
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
	outfile__dynamic_array_synapses_22__synaptic_pre.open("results\\_dynamic_array_synapses_22__synaptic_pre_1222226774358140367", ios::binary | ios::out);
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
	outfile__dynamic_array_synapses_22_delay.open("results\\_dynamic_array_synapses_22_delay_6669931861682692525", ios::binary | ios::out);
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
	outfile__dynamic_array_synapses_22_lastupdate.open("results\\_dynamic_array_synapses_22_lastupdate_2876351199656113741", ios::binary | ios::out);
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
	outfile__dynamic_array_synapses_22_N_incoming.open("results\\_dynamic_array_synapses_22_N_incoming_3214963832957742629", ios::binary | ios::out);
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
	outfile__dynamic_array_synapses_22_N_outgoing.open("results\\_dynamic_array_synapses_22_N_outgoing_-6992221640399427619", ios::binary | ios::out);
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
	outfile__dynamic_array_synapses_22_R.open("results\\_dynamic_array_synapses_22_R_6543183969117368452", ios::binary | ios::out);
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
	outfile__dynamic_array_synapses_22_wght.open("results\\_dynamic_array_synapses_22_wght_8320420455614128675", ios::binary | ios::out);
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
	outfile__dynamic_array_synapses_23__synaptic_post.open("results\\_dynamic_array_synapses_23__synaptic_post_6364560451154687093", ios::binary | ios::out);
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
	outfile__dynamic_array_synapses_23__synaptic_pre.open("results\\_dynamic_array_synapses_23__synaptic_pre_970113040799910793", ios::binary | ios::out);
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
	outfile__dynamic_array_synapses_23_delay.open("results\\_dynamic_array_synapses_23_delay_-949413800123291631", ios::binary | ios::out);
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
	outfile__dynamic_array_synapses_23_lastupdate.open("results\\_dynamic_array_synapses_23_lastupdate_-3646525085840258168", ios::binary | ios::out);
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
	outfile__dynamic_array_synapses_23_N_incoming.open("results\\_dynamic_array_synapses_23_N_incoming_5924941390610900630", ios::binary | ios::out);
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
	outfile__dynamic_array_synapses_23_N_outgoing.open("results\\_dynamic_array_synapses_23_N_outgoing_-6339053554212385351", ios::binary | ios::out);
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
	outfile__dynamic_array_synapses_23_R.open("results\\_dynamic_array_synapses_23_R_-601937267359045762", ios::binary | ios::out);
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
	outfile__dynamic_array_synapses_23_wght.open("results\\_dynamic_array_synapses_23_wght_-8032054167449118299", ios::binary | ios::out);
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
	outfile__dynamic_array_synapses_24__synaptic_post.open("results\\_dynamic_array_synapses_24__synaptic_post_8113912160323715503", ios::binary | ios::out);
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
	outfile__dynamic_array_synapses_24__synaptic_pre.open("results\\_dynamic_array_synapses_24__synaptic_pre_-9017579111844473127", ios::binary | ios::out);
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
	outfile__dynamic_array_synapses_24_delay.open("results\\_dynamic_array_synapses_24_delay_7610835321619616996", ios::binary | ios::out);
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
	outfile__dynamic_array_synapses_24_lastupdate.open("results\\_dynamic_array_synapses_24_lastupdate_3615430864562871150", ios::binary | ios::out);
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
	outfile__dynamic_array_synapses_24_N_incoming.open("results\\_dynamic_array_synapses_24_N_incoming_-9099720674398661210", ios::binary | ios::out);
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
	outfile__dynamic_array_synapses_24_N_outgoing.open("results\\_dynamic_array_synapses_24_N_outgoing_1163411303744778531", ios::binary | ios::out);
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
	outfile__dynamic_array_synapses_24_R.open("results\\_dynamic_array_synapses_24_R_-8710580062318377556", ios::binary | ios::out);
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
	outfile__dynamic_array_synapses_24_wght.open("results\\_dynamic_array_synapses_24_wght_4878776555105363711", ios::binary | ios::out);
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
	outfile__dynamic_array_synapses_25__synaptic_post.open("results\\_dynamic_array_synapses_25__synaptic_post_5893473879398005042", ios::binary | ios::out);
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
	outfile__dynamic_array_synapses_25__synaptic_pre.open("results\\_dynamic_array_synapses_25__synaptic_pre_1990884221640008108", ios::binary | ios::out);
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
	outfile__dynamic_array_synapses_25_delay.open("results\\_dynamic_array_synapses_25_delay_9201606559366798102", ios::binary | ios::out);
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
	outfile__dynamic_array_synapses_25_lastupdate.open("results\\_dynamic_array_synapses_25_lastupdate_-299180093247734602", ios::binary | ios::out);
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
	outfile__dynamic_array_synapses_25_N_incoming.open("results\\_dynamic_array_synapses_25_N_incoming_6154968322030438424", ios::binary | ios::out);
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
	outfile__dynamic_array_synapses_25_N_outgoing.open("results\\_dynamic_array_synapses_25_N_outgoing_-5021905681711363595", ios::binary | ios::out);
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
	outfile__dynamic_array_synapses_25_R.open("results\\_dynamic_array_synapses_25_R_7311302270896595632", ios::binary | ios::out);
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
	outfile__dynamic_array_synapses_25_wght.open("results\\_dynamic_array_synapses_25_wght_4014807177904894187", ios::binary | ios::out);
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
	outfile__dynamic_array_synapses_26__synaptic_post.open("results\\_dynamic_array_synapses_26__synaptic_post_-8343937354302452000", ios::binary | ios::out);
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
	outfile__dynamic_array_synapses_26__synaptic_pre.open("results\\_dynamic_array_synapses_26__synaptic_pre_-4225213297645832584", ios::binary | ios::out);
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
	outfile__dynamic_array_synapses_26_delay.open("results\\_dynamic_array_synapses_26_delay_-4230226613205410712", ios::binary | ios::out);
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
	outfile__dynamic_array_synapses_26_lastupdate.open("results\\_dynamic_array_synapses_26_lastupdate_1758056752794222689", ios::binary | ios::out);
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
	outfile__dynamic_array_synapses_26_N_incoming.open("results\\_dynamic_array_synapses_26_N_incoming_7604890201917592290", ios::binary | ios::out);
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
	outfile__dynamic_array_synapses_26_N_outgoing.open("results\\_dynamic_array_synapses_26_N_outgoing_2672812619454530589", ios::binary | ios::out);
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
	outfile__dynamic_array_synapses_26_R.open("results\\_dynamic_array_synapses_26_R_-3952604786796649775", ios::binary | ios::out);
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
	outfile__dynamic_array_synapses_26_wght.open("results\\_dynamic_array_synapses_26_wght_2238980378724837412", ios::binary | ios::out);
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
	outfile__dynamic_array_synapses_27__synaptic_post.open("results\\_dynamic_array_synapses_27__synaptic_post_-350521438655402860", ios::binary | ios::out);
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
	outfile__dynamic_array_synapses_27__synaptic_pre.open("results\\_dynamic_array_synapses_27__synaptic_pre_-110740667480478581", ios::binary | ios::out);
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
	outfile__dynamic_array_synapses_27_delay.open("results\\_dynamic_array_synapses_27_delay_98773609611337076", ios::binary | ios::out);
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
	outfile__dynamic_array_synapses_27_lastupdate.open("results\\_dynamic_array_synapses_27_lastupdate_-1289292041332696160", ios::binary | ios::out);
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
	outfile__dynamic_array_synapses_27_N_incoming.open("results\\_dynamic_array_synapses_27_N_incoming_5120956212294647577", ios::binary | ios::out);
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
	outfile__dynamic_array_synapses_27_N_outgoing.open("results\\_dynamic_array_synapses_27_N_outgoing_52173047870694330", ios::binary | ios::out);
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
	outfile__dynamic_array_synapses_27_R.open("results\\_dynamic_array_synapses_27_R_268950077995310707", ios::binary | ios::out);
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
	outfile__dynamic_array_synapses_27_wght.open("results\\_dynamic_array_synapses_27_wght_321506542200420935", ios::binary | ios::out);
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
	outfile__dynamic_array_synapses_28__synaptic_post.open("results\\_dynamic_array_synapses_28__synaptic_post_-2458285048568109656", ios::binary | ios::out);
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
	outfile__dynamic_array_synapses_28__synaptic_pre.open("results\\_dynamic_array_synapses_28__synaptic_pre_-1962747204997781902", ios::binary | ios::out);
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
	outfile__dynamic_array_synapses_28_delay.open("results\\_dynamic_array_synapses_28_delay_4284373621381531822", ios::binary | ios::out);
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
	outfile__dynamic_array_synapses_28_lastupdate.open("results\\_dynamic_array_synapses_28_lastupdate_-2015716164040484648", ios::binary | ios::out);
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
	outfile__dynamic_array_synapses_28_N_incoming.open("results\\_dynamic_array_synapses_28_N_incoming_4461138814119719610", ios::binary | ios::out);
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
	outfile__dynamic_array_synapses_28_N_outgoing.open("results\\_dynamic_array_synapses_28_N_outgoing_5071501431085634902", ios::binary | ios::out);
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
	outfile__dynamic_array_synapses_28_R.open("results\\_dynamic_array_synapses_28_R_237614353263561723", ios::binary | ios::out);
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
	outfile__dynamic_array_synapses_28_wght.open("results\\_dynamic_array_synapses_28_wght_-5510283354517901510", ios::binary | ios::out);
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
	outfile__dynamic_array_synapses_29__synaptic_post.open("results\\_dynamic_array_synapses_29__synaptic_post_4181079084303162857", ios::binary | ios::out);
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
	outfile__dynamic_array_synapses_29__synaptic_pre.open("results\\_dynamic_array_synapses_29__synaptic_pre_6750959268230156484", ios::binary | ios::out);
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
	outfile__dynamic_array_synapses_29_delay.open("results\\_dynamic_array_synapses_29_delay_-8895676169178677593", ios::binary | ios::out);
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
	outfile__dynamic_array_synapses_29_lastupdate.open("results\\_dynamic_array_synapses_29_lastupdate_7614416773165710009", ios::binary | ios::out);
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
	outfile__dynamic_array_synapses_29_N_incoming.open("results\\_dynamic_array_synapses_29_N_incoming_5962387800419132303", ios::binary | ios::out);
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
	outfile__dynamic_array_synapses_29_N_outgoing.open("results\\_dynamic_array_synapses_29_N_outgoing_-9167975029192567026", ios::binary | ios::out);
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
	outfile__dynamic_array_synapses_29_R.open("results\\_dynamic_array_synapses_29_R_-9172864415096904826", ios::binary | ios::out);
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
	outfile__dynamic_array_synapses_29_wght.open("results\\_dynamic_array_synapses_29_wght_-95942942311739766", ios::binary | ios::out);
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
	outfile__dynamic_array_synapses_2__synaptic_post.open("results\\_dynamic_array_synapses_2__synaptic_post_-6298236503699204567", ios::binary | ios::out);
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
	outfile__dynamic_array_synapses_2__synaptic_pre.open("results\\_dynamic_array_synapses_2__synaptic_pre_539174396856416432", ios::binary | ios::out);
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
	outfile__dynamic_array_synapses_2_delay.open("results\\_dynamic_array_synapses_2_delay_5235277766165499628", ios::binary | ios::out);
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
	outfile__dynamic_array_synapses_2_lastupdate.open("results\\_dynamic_array_synapses_2_lastupdate_2892674212610665867", ios::binary | ios::out);
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
	outfile__dynamic_array_synapses_2_N_incoming.open("results\\_dynamic_array_synapses_2_N_incoming_172006118191174017", ios::binary | ios::out);
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
	outfile__dynamic_array_synapses_2_N_outgoing.open("results\\_dynamic_array_synapses_2_N_outgoing_2789882076244406888", ios::binary | ios::out);
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
	outfile__dynamic_array_synapses_2_R.open("results\\_dynamic_array_synapses_2_R_3785780112074216966", ios::binary | ios::out);
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
	outfile__dynamic_array_synapses_2_wght.open("results\\_dynamic_array_synapses_2_wght_-2375625289654846959", ios::binary | ios::out);
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
	outfile__dynamic_array_synapses_30__synaptic_post.open("results\\_dynamic_array_synapses_30__synaptic_post_443383306993286509", ios::binary | ios::out);
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
	outfile__dynamic_array_synapses_30__synaptic_pre.open("results\\_dynamic_array_synapses_30__synaptic_pre_-7379775644986048795", ios::binary | ios::out);
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
	outfile__dynamic_array_synapses_30_delay.open("results\\_dynamic_array_synapses_30_delay_-5571716255274569572", ios::binary | ios::out);
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
	outfile__dynamic_array_synapses_30_lastupdate.open("results\\_dynamic_array_synapses_30_lastupdate_-7893525595833039540", ios::binary | ios::out);
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
	outfile__dynamic_array_synapses_30_N_incoming.open("results\\_dynamic_array_synapses_30_N_incoming_5143829975288173656", ios::binary | ios::out);
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
	outfile__dynamic_array_synapses_30_N_outgoing.open("results\\_dynamic_array_synapses_30_N_outgoing_-213505417154355749", ios::binary | ios::out);
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
	outfile__dynamic_array_synapses_30_R.open("results\\_dynamic_array_synapses_30_R_8791906598965489170", ios::binary | ios::out);
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
	outfile__dynamic_array_synapses_30_wght.open("results\\_dynamic_array_synapses_30_wght_3291911141565442654", ios::binary | ios::out);
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
	outfile__dynamic_array_synapses_31__synaptic_post.open("results\\_dynamic_array_synapses_31__synaptic_post_6777051788191389052", ios::binary | ios::out);
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
	outfile__dynamic_array_synapses_31__synaptic_pre.open("results\\_dynamic_array_synapses_31__synaptic_pre_7764402679088768358", ios::binary | ios::out);
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
	outfile__dynamic_array_synapses_31_delay.open("results\\_dynamic_array_synapses_31_delay_-7396014942864915440", ios::binary | ios::out);
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
	outfile__dynamic_array_synapses_31_lastupdate.open("results\\_dynamic_array_synapses_31_lastupdate_2649567524975336933", ios::binary | ios::out);
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
	outfile__dynamic_array_synapses_31_N_incoming.open("results\\_dynamic_array_synapses_31_N_incoming_-3472105293056079448", ios::binary | ios::out);
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
	outfile__dynamic_array_synapses_31_N_outgoing.open("results\\_dynamic_array_synapses_31_N_outgoing_-8256187731806381410", ios::binary | ios::out);
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
	outfile__dynamic_array_synapses_31_R.open("results\\_dynamic_array_synapses_31_R_4663782304945477992", ios::binary | ios::out);
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
	outfile__dynamic_array_synapses_31_wght.open("results\\_dynamic_array_synapses_31_wght_5500863268347125697", ios::binary | ios::out);
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
	outfile__dynamic_array_synapses_32__synaptic_post.open("results\\_dynamic_array_synapses_32__synaptic_post_-6569497471531199037", ios::binary | ios::out);
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
	outfile__dynamic_array_synapses_32__synaptic_pre.open("results\\_dynamic_array_synapses_32__synaptic_pre_-3266573142048004021", ios::binary | ios::out);
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
	outfile__dynamic_array_synapses_32_delay.open("results\\_dynamic_array_synapses_32_delay_1047162309059271296", ios::binary | ios::out);
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
	outfile__dynamic_array_synapses_32_lastupdate.open("results\\_dynamic_array_synapses_32_lastupdate_-6136861180122612111", ios::binary | ios::out);
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
	outfile__dynamic_array_synapses_32_N_incoming.open("results\\_dynamic_array_synapses_32_N_incoming_-4234493969057549156", ios::binary | ios::out);
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
	outfile__dynamic_array_synapses_32_N_outgoing.open("results\\_dynamic_array_synapses_32_N_outgoing_-3026844017652520037", ios::binary | ios::out);
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
	outfile__dynamic_array_synapses_32_R.open("results\\_dynamic_array_synapses_32_R_-7079502075060455414", ios::binary | ios::out);
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
	outfile__dynamic_array_synapses_32_wght.open("results\\_dynamic_array_synapses_32_wght_-5171508619901404189", ios::binary | ios::out);
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
	outfile__dynamic_array_synapses_33__synaptic_post.open("results\\_dynamic_array_synapses_33__synaptic_post_6936150014926567933", ios::binary | ios::out);
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
	outfile__dynamic_array_synapses_33__synaptic_pre.open("results\\_dynamic_array_synapses_33__synaptic_pre_1681437226021541206", ios::binary | ios::out);
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
	outfile__dynamic_array_synapses_33_delay.open("results\\_dynamic_array_synapses_33_delay_2304433687083237273", ios::binary | ios::out);
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
	outfile__dynamic_array_synapses_33_lastupdate.open("results\\_dynamic_array_synapses_33_lastupdate_295597907467199269", ios::binary | ios::out);
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
	outfile__dynamic_array_synapses_33_N_incoming.open("results\\_dynamic_array_synapses_33_N_incoming_808407919399929376", ios::binary | ios::out);
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
	outfile__dynamic_array_synapses_33_N_outgoing.open("results\\_dynamic_array_synapses_33_N_outgoing_61096420993320619", ios::binary | ios::out);
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
	outfile__dynamic_array_synapses_33_R.open("results\\_dynamic_array_synapses_33_R_-386084655151611852", ios::binary | ios::out);
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
	outfile__dynamic_array_synapses_33_wght.open("results\\_dynamic_array_synapses_33_wght_-1724395623668482303", ios::binary | ios::out);
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
	outfile__dynamic_array_synapses_34__synaptic_post.open("results\\_dynamic_array_synapses_34__synaptic_post_-5632017374392533824", ios::binary | ios::out);
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
	outfile__dynamic_array_synapses_34__synaptic_pre.open("results\\_dynamic_array_synapses_34__synaptic_pre_-6866516963546085315", ios::binary | ios::out);
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
	outfile__dynamic_array_synapses_34_delay.open("results\\_dynamic_array_synapses_34_delay_3808102319974580702", ios::binary | ios::out);
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
	outfile__dynamic_array_synapses_34_lastupdate.open("results\\_dynamic_array_synapses_34_lastupdate_-8263259941213305911", ios::binary | ios::out);
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
	outfile__dynamic_array_synapses_34_N_incoming.open("results\\_dynamic_array_synapses_34_N_incoming_8573523868220729266", ios::binary | ios::out);
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
	outfile__dynamic_array_synapses_34_N_outgoing.open("results\\_dynamic_array_synapses_34_N_outgoing_-5637007347492592388", ios::binary | ios::out);
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
	outfile__dynamic_array_synapses_34_R.open("results\\_dynamic_array_synapses_34_R_9171265434458295673", ios::binary | ios::out);
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
	outfile__dynamic_array_synapses_34_wght.open("results\\_dynamic_array_synapses_34_wght_8588009518360025477", ios::binary | ios::out);
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
	outfile__dynamic_array_synapses_35__synaptic_post.open("results\\_dynamic_array_synapses_35__synaptic_post_6558053307707972244", ios::binary | ios::out);
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
	outfile__dynamic_array_synapses_35__synaptic_pre.open("results\\_dynamic_array_synapses_35__synaptic_pre_-3358810283380213433", ios::binary | ios::out);
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
	outfile__dynamic_array_synapses_35_delay.open("results\\_dynamic_array_synapses_35_delay_7805474520136216221", ios::binary | ios::out);
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
	outfile__dynamic_array_synapses_35_lastupdate.open("results\\_dynamic_array_synapses_35_lastupdate_-8098419880582718351", ios::binary | ios::out);
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
	outfile__dynamic_array_synapses_35_N_incoming.open("results\\_dynamic_array_synapses_35_N_incoming_8267856540896906325", ios::binary | ios::out);
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
	outfile__dynamic_array_synapses_35_N_outgoing.open("results\\_dynamic_array_synapses_35_N_outgoing_8600283173310916023", ios::binary | ios::out);
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
	outfile__dynamic_array_synapses_35_R.open("results\\_dynamic_array_synapses_35_R_3430881201613466857", ios::binary | ios::out);
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
	outfile__dynamic_array_synapses_35_wght.open("results\\_dynamic_array_synapses_35_wght_-3369673095136950052", ios::binary | ios::out);
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
	outfile__dynamic_array_synapses_36__synaptic_post.open("results\\_dynamic_array_synapses_36__synaptic_post_-4887169234114903769", ios::binary | ios::out);
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
	outfile__dynamic_array_synapses_36__synaptic_pre.open("results\\_dynamic_array_synapses_36__synaptic_pre_3195919156899745742", ios::binary | ios::out);
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
	outfile__dynamic_array_synapses_36_delay.open("results\\_dynamic_array_synapses_36_delay_-8555781499541553297", ios::binary | ios::out);
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
	outfile__dynamic_array_synapses_36_lastupdate.open("results\\_dynamic_array_synapses_36_lastupdate_8612435511499651906", ios::binary | ios::out);
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
	outfile__dynamic_array_synapses_36_N_incoming.open("results\\_dynamic_array_synapses_36_N_incoming_-4964804874283452215", ios::binary | ios::out);
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
	outfile__dynamic_array_synapses_36_N_outgoing.open("results\\_dynamic_array_synapses_36_N_outgoing_1993263110889788823", ios::binary | ios::out);
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
	outfile__dynamic_array_synapses_36_R.open("results\\_dynamic_array_synapses_36_R_2987738444131229281", ios::binary | ios::out);
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
	outfile__dynamic_array_synapses_36_wght.open("results\\_dynamic_array_synapses_36_wght_3096527165921428605", ios::binary | ios::out);
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
	outfile__dynamic_array_synapses_37__synaptic_post.open("results\\_dynamic_array_synapses_37__synaptic_post_5388721571706219801", ios::binary | ios::out);
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
	outfile__dynamic_array_synapses_37__synaptic_pre.open("results\\_dynamic_array_synapses_37__synaptic_pre_-4399097048188570427", ios::binary | ios::out);
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
	outfile__dynamic_array_synapses_37_delay.open("results\\_dynamic_array_synapses_37_delay_-588565429524199647", ios::binary | ios::out);
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
	outfile__dynamic_array_synapses_37_lastupdate.open("results\\_dynamic_array_synapses_37_lastupdate_-1689854706207813254", ios::binary | ios::out);
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
	outfile__dynamic_array_synapses_37_N_incoming.open("results\\_dynamic_array_synapses_37_N_incoming_2132952301914010025", ios::binary | ios::out);
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
	outfile__dynamic_array_synapses_37_N_outgoing.open("results\\_dynamic_array_synapses_37_N_outgoing_-6537534250749211163", ios::binary | ios::out);
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
	outfile__dynamic_array_synapses_37_R.open("results\\_dynamic_array_synapses_37_R_-5283368274110474243", ios::binary | ios::out);
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
	outfile__dynamic_array_synapses_37_wght.open("results\\_dynamic_array_synapses_37_wght_-6043161739953326549", ios::binary | ios::out);
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
	outfile__dynamic_array_synapses_3__synaptic_post.open("results\\_dynamic_array_synapses_3__synaptic_post_-5304443676864083530", ios::binary | ios::out);
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
	outfile__dynamic_array_synapses_3__synaptic_pre.open("results\\_dynamic_array_synapses_3__synaptic_pre_-2290313623435032820", ios::binary | ios::out);
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
	outfile__dynamic_array_synapses_3_delay.open("results\\_dynamic_array_synapses_3_delay_4052387903921971925", ios::binary | ios::out);
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
	outfile__dynamic_array_synapses_3_lastupdate.open("results\\_dynamic_array_synapses_3_lastupdate_-2413605114685819544", ios::binary | ios::out);
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
	outfile__dynamic_array_synapses_3_N_incoming.open("results\\_dynamic_array_synapses_3_N_incoming_-8860290673197413256", ios::binary | ios::out);
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
	outfile__dynamic_array_synapses_3_N_outgoing.open("results\\_dynamic_array_synapses_3_N_outgoing_-6812250903342667283", ios::binary | ios::out);
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
	outfile__dynamic_array_synapses_3_R.open("results\\_dynamic_array_synapses_3_R_5681407234416764912", ios::binary | ios::out);
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
	outfile__dynamic_array_synapses_3_wght.open("results\\_dynamic_array_synapses_3_wght_7359133823739804074", ios::binary | ios::out);
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
	outfile__dynamic_array_synapses_4__synaptic_post.open("results\\_dynamic_array_synapses_4__synaptic_post_6502904115205269596", ios::binary | ios::out);
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
	outfile__dynamic_array_synapses_4__synaptic_pre.open("results\\_dynamic_array_synapses_4__synaptic_pre_-6074835899147993977", ios::binary | ios::out);
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
	outfile__dynamic_array_synapses_4_delay.open("results\\_dynamic_array_synapses_4_delay_4791624709598420324", ios::binary | ios::out);
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
	outfile__dynamic_array_synapses_4_lastupdate.open("results\\_dynamic_array_synapses_4_lastupdate_6914141399642689246", ios::binary | ios::out);
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
	outfile__dynamic_array_synapses_4_N_incoming.open("results\\_dynamic_array_synapses_4_N_incoming_7536835013407237338", ios::binary | ios::out);
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
	outfile__dynamic_array_synapses_4_N_outgoing.open("results\\_dynamic_array_synapses_4_N_outgoing_-8322952076495232570", ios::binary | ios::out);
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
	outfile__dynamic_array_synapses_4_R.open("results\\_dynamic_array_synapses_4_R_-1724035775163400030", ios::binary | ios::out);
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
	outfile__dynamic_array_synapses_4_wght.open("results\\_dynamic_array_synapses_4_wght_118283308545804625", ios::binary | ios::out);
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
	outfile__dynamic_array_synapses_5__synaptic_post.open("results\\_dynamic_array_synapses_5__synaptic_post_5660762151208094038", ios::binary | ios::out);
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
	outfile__dynamic_array_synapses_5__synaptic_pre.open("results\\_dynamic_array_synapses_5__synaptic_pre_-1438275478338361955", ios::binary | ios::out);
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
	outfile__dynamic_array_synapses_5_delay.open("results\\_dynamic_array_synapses_5_delay_5956664074284390937", ios::binary | ios::out);
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
	outfile__dynamic_array_synapses_5_lastupdate.open("results\\_dynamic_array_synapses_5_lastupdate_-8551061607363397962", ios::binary | ios::out);
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
	outfile__dynamic_array_synapses_5_N_incoming.open("results\\_dynamic_array_synapses_5_N_incoming_-610266439756641131", ios::binary | ios::out);
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
	outfile__dynamic_array_synapses_5_N_outgoing.open("results\\_dynamic_array_synapses_5_N_outgoing_-4582129905568079836", ios::binary | ios::out);
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
	outfile__dynamic_array_synapses_5_R.open("results\\_dynamic_array_synapses_5_R_-2017739363982113917", ios::binary | ios::out);
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
	outfile__dynamic_array_synapses_5_wght.open("results\\_dynamic_array_synapses_5_wght_1669108434635010797", ios::binary | ios::out);
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
	outfile__dynamic_array_synapses_6__synaptic_post.open("results\\_dynamic_array_synapses_6__synaptic_post_4745028105843256024", ios::binary | ios::out);
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
	outfile__dynamic_array_synapses_6__synaptic_pre.open("results\\_dynamic_array_synapses_6__synaptic_pre_-1217355358320884727", ios::binary | ios::out);
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
	outfile__dynamic_array_synapses_6_delay.open("results\\_dynamic_array_synapses_6_delay_8794425429537265309", ios::binary | ios::out);
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
	outfile__dynamic_array_synapses_6_lastupdate.open("results\\_dynamic_array_synapses_6_lastupdate_-7355709534695203444", ios::binary | ios::out);
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
	outfile__dynamic_array_synapses_6_N_incoming.open("results\\_dynamic_array_synapses_6_N_incoming_-4004273783161765889", ios::binary | ios::out);
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
	outfile__dynamic_array_synapses_6_N_outgoing.open("results\\_dynamic_array_synapses_6_N_outgoing_4168770422196356685", ios::binary | ios::out);
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
	outfile__dynamic_array_synapses_6_R.open("results\\_dynamic_array_synapses_6_R_-5055766996539059245", ios::binary | ios::out);
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
	outfile__dynamic_array_synapses_6_wght.open("results\\_dynamic_array_synapses_6_wght_-5093130196896152167", ios::binary | ios::out);
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
	outfile__dynamic_array_synapses_7__synaptic_post.open("results\\_dynamic_array_synapses_7__synaptic_post_-5307564230199644813", ios::binary | ios::out);
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
	outfile__dynamic_array_synapses_7__synaptic_pre.open("results\\_dynamic_array_synapses_7__synaptic_pre_483992996587745093", ios::binary | ios::out);
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
	outfile__dynamic_array_synapses_7_delay.open("results\\_dynamic_array_synapses_7_delay_5318483392809310852", ios::binary | ios::out);
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
	outfile__dynamic_array_synapses_7_lastupdate.open("results\\_dynamic_array_synapses_7_lastupdate_1312079637076249339", ios::binary | ios::out);
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
	outfile__dynamic_array_synapses_7_N_incoming.open("results\\_dynamic_array_synapses_7_N_incoming_6036093291978684075", ios::binary | ios::out);
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
	outfile__dynamic_array_synapses_7_N_outgoing.open("results\\_dynamic_array_synapses_7_N_outgoing_-6184397350799466005", ios::binary | ios::out);
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
	outfile__dynamic_array_synapses_7_R.open("results\\_dynamic_array_synapses_7_R_-7177511625738005436", ios::binary | ios::out);
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
	outfile__dynamic_array_synapses_7_wght.open("results\\_dynamic_array_synapses_7_wght_2621806234108601351", ios::binary | ios::out);
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
	outfile__dynamic_array_synapses_8__synaptic_post.open("results\\_dynamic_array_synapses_8__synaptic_post_7659652017538810841", ios::binary | ios::out);
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
	outfile__dynamic_array_synapses_8__synaptic_pre.open("results\\_dynamic_array_synapses_8__synaptic_pre_2965887361786840968", ios::binary | ios::out);
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
	outfile__dynamic_array_synapses_8_delay.open("results\\_dynamic_array_synapses_8_delay_4449174848002576296", ios::binary | ios::out);
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
	outfile__dynamic_array_synapses_8_lastupdate.open("results\\_dynamic_array_synapses_8_lastupdate_-5917720880398542450", ios::binary | ios::out);
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
	outfile__dynamic_array_synapses_8_N_incoming.open("results\\_dynamic_array_synapses_8_N_incoming_6782089295749547713", ios::binary | ios::out);
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
	outfile__dynamic_array_synapses_8_N_outgoing.open("results\\_dynamic_array_synapses_8_N_outgoing_-6920580249320511382", ios::binary | ios::out);
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
	outfile__dynamic_array_synapses_8_R.open("results\\_dynamic_array_synapses_8_R_-7176511906729963209", ios::binary | ios::out);
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
	outfile__dynamic_array_synapses_8_wght.open("results\\_dynamic_array_synapses_8_wght_2738882169639712769", ios::binary | ios::out);
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
	outfile__dynamic_array_synapses_9__synaptic_post.open("results\\_dynamic_array_synapses_9__synaptic_post_3573756045452286717", ios::binary | ios::out);
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
	outfile__dynamic_array_synapses_9__synaptic_pre.open("results\\_dynamic_array_synapses_9__synaptic_pre_1171405880313282599", ios::binary | ios::out);
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
	outfile__dynamic_array_synapses_9_delay.open("results\\_dynamic_array_synapses_9_delay_-8291819693853787461", ios::binary | ios::out);
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
	outfile__dynamic_array_synapses_9_lastupdate.open("results\\_dynamic_array_synapses_9_lastupdate_-8158165961834159693", ios::binary | ios::out);
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
	outfile__dynamic_array_synapses_9_N_incoming.open("results\\_dynamic_array_synapses_9_N_incoming_-4946526509521048413", ios::binary | ios::out);
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
	outfile__dynamic_array_synapses_9_N_outgoing.open("results\\_dynamic_array_synapses_9_N_outgoing_458390028926544986", ios::binary | ios::out);
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
	outfile__dynamic_array_synapses_9_R.open("results\\_dynamic_array_synapses_9_R_9046756874486778876", ios::binary | ios::out);
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
	outfile__dynamic_array_synapses_9_wght.open("results\\_dynamic_array_synapses_9_wght_5067722526642546245", ios::binary | ios::out);
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
	outfile__dynamic_array_synapses__synaptic_post.open("results\\_dynamic_array_synapses__synaptic_post_5109808899816100058", ios::binary | ios::out);
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
	outfile__dynamic_array_synapses__synaptic_pre.open("results\\_dynamic_array_synapses__synaptic_pre_-2602721193534432400", ios::binary | ios::out);
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
	outfile__dynamic_array_synapses_delay.open("results\\_dynamic_array_synapses_delay_8585861191010875245", ios::binary | ios::out);
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
	outfile__dynamic_array_synapses_N_incoming.open("results\\_dynamic_array_synapses_N_incoming_-3648686057675359758", ios::binary | ios::out);
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
	outfile__dynamic_array_synapses_N_outgoing.open("results\\_dynamic_array_synapses_N_outgoing_-2958078051116145934", ios::binary | ios::out);
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

