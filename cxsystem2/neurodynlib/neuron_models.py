# This code is based on the exercise code repository accompanying
# the book: Neuronal Dynamics (see http://neuronaldynamics.epfl.ch)
# located at http://github.com/EPFL-LCN/neuronaldynamics-exercises.
#
# The book is also published in print:
# Wulfram Gerstner, Werner M. Kistler, Richard Naud, and Liam Paninski.
# Neuronal Dynamics: From Single Neurons to Networks and Models of Cognition.
# Cambridge University Press, 2014.
#
# Neuron models that were used from the exercise code repository are:
# AdEx, passive_cable, exp_IF, HH, LIF, NeuronAbstract, NeuronTypeOne, NeuronTypeTwo, fitzhugh_nagumo

import json
from datetime import datetime
from string import Template
import brian2 as b2
import matplotlib.pyplot as plt
import numpy as np
from brian2.units import *
import copy

from cxsystem2.neurodynlib.receptor_models import ReceptorModel
from cxsystem2.neurodynlib.tools import plot_tools, input_factory


class PointNeuron:
    """
    Base class for point neurons

    """

    # General equation for neuron models
    membrane_eq_template = '''
    dvm/dt = (($I_NEURON_MODEL $I_SYNAPTIC_EXC $I_SYNAPTIC_INH $EXT_CURRENTS)/C) $VM_NOISE : $VM_UNIT $BRIAN2_FLAGS
    $NEURON_MODEL_EQS
    $SYNAPTIC_EXC_EQS
    $SYNAPTIC_INH_EQS
    $EXT_CURRENTS_EQS
    '''
    all_template_placeholders = ['I_NEURON_MODEL', 'I_SYNAPTIC_EXC', 'I_SYNAPTIC_INH', 'EXT_CURRENTS',
                                 'VM_NOISE', 'VM_UNIT', 'BRIAN2_FLAGS',
                                 'NEURON_MODEL_EQS',
                                 'SYNAPTIC_EXC_EQS', 'SYNAPTIC_INH_EQS',
                                 'EXT_CURRENTS_EQS']

    # Default components
    default_soma_defns = {
        # 'I_NEURON_MODEL': '',
        # 'NEURON_MODEL_EQ': '',
        # 'EXT_CURRENTS': '+ I_stim(t,i)',  # + tonic_current*(1-exp(-t/(50*msecond)))
        # 'EXT_CURRENTS_EQS': 'I_ext : amp',
        # 'VM_NOISE': '',  # + noise_sigma*xi*taum_soma**-0.5
        'VM_UNIT': 'volt',
        'BRIAN2_FLAGS': '(unless refractory)'
    }

    default_dendrite_defns = {
        # 'EXT_CURRENTS': '',
        # 'EXT_CURRENTS_EQS': '',
        # 'VM_NOISE': '',
        'VM_UNIT': 'volt',
        'BRIAN2_FLAGS': ''  # Be careful! "Unless refractory" in dendrites will not cause an error, but behavior is WRONG
    }

    default_neuron_parameters = {}
    model_info_url = 'http://neuronaldynamics.epfl.ch/online/'

    def __init__(self, is_pyramidal=False, compartment='soma'):
        """
        Initializes the point neuron object

        :param bool is_pyramidal: whether the point neuron model is part of a pyramidal/multicompartmental cell
        :param string compartment: name of the compartment (eg. soma, basal, a3)
        """

        self.is_pyramidal = is_pyramidal
        self.compartment = compartment
        #self.custom_strings = custom_strings

        # If compartment is other than 'soma' ('a2' for example), we assume it to be a dendritic compartment
        if compartment == 'soma':
            self.compartment_type = 'soma'
        else:
            self.compartment_type = 'dendrite'

        if is_pyramidal is True:
            if self.compartment_type == 'soma':
                self.full_model_defns = dict(PointNeuron.default_soma_defns)
            else:
                self.full_model_defns = dict(PointNeuron.default_dendrite_defns)

            self.full_model_defns.update(self.neuron_model_defns)  # Model-specific definitions

        # Then, if we are dealing with a point neuron:
        else:
            self.full_model_defns = dict(PointNeuron.default_soma_defns)
            self.full_model_defns.update(self.neuron_model_defns)  # Model-specific definitions


        # Get a clean string with empty placeholders removed
        self.neuron_eqs = self.get_membrane_equation()

        # Set default parameters
        self.neuron_parameters = self.default_neuron_parameters

        # Add default threshold condition, reset statements and integration method
        self.threshold_condition = 'vm > VT'
        self.reset_statements = 'vm = V_res'
        self.integration_method = 'euler'

        # Add other defaults
        self.initial_values = {'vm': 'EL'}  # was vm : None, but this was not tolerated by added set_state() method in cxsystem.py
        self.states_to_monitor = ['vm']
        self.neuron_name = self.__class__.__name__ + '_' + datetime.now().strftime('%Y%m%d%H%M%S%f')

        self.parameter_units = {
            'EL': mV, 'V_res': mV, 'VT': mV,
            'gL': nS, 'C': pF, 'refractory_period': ms
        }

        self.link_to_book = self.model_info_url

        # Will be useful for multicompartmental neurons using these same classes
        # NB! C and gL not set compartment-specific by default due to the way
        # multicompartmental neurons are set, see module multicompartment_models.py
        self.compartment_vars_and_consts = []

    def get_membrane_equation(self, substitute_ad_hoc=None, return_string=True):
        """
        Compiles the membrane equation from the template for use in Brian2.
        This should be the only function where the template equation is used.

        :param dict substitute_ad_hoc: dictionary of temporary values to use in the equation template
        :param bool return_string: If True, returns equations as a string. Otherwise, returns a b2.Equations object.
        :return: string (or b2.Equations object)
        """

        # Get the generic template
        neuron_eqs_template = Template(self.membrane_eq_template)

        # Do ad hoc substitutions, overriding any definitions in full_model_defns
        if substitute_ad_hoc is not None:
            neuron_eqs_template2 = Template(neuron_eqs_template.safe_substitute(substitute_ad_hoc))
        else:
            neuron_eqs_template2 = neuron_eqs_template

        # Make substitutions in full_model_defns
        neuron_eqs_template2 = Template(neuron_eqs_template2.safe_substitute(self.full_model_defns))

        # Deal with extra placeholders in the eq template
        nullify_placeholders_dict = {k: '' for k in PointNeuron.all_template_placeholders}
        neuron_eqs_template_wo_placeholders = neuron_eqs_template2.substitute(nullify_placeholders_dict)

        # Stringify the equations
        neuron_eqs_string = str(neuron_eqs_template_wo_placeholders)
        eq_lines = neuron_eqs_string.splitlines()
        eq_lines = [line.strip()+'\n' for line in eq_lines if len(line.strip()) > 0]
        model_membrane_equation = ''.join(eq_lines)

        if return_string is True:
            return model_membrane_equation
        else:
            return b2.Equations(model_membrane_equation)

    def get_compartment_equations(self, compartment_name):
        """
        Compiles the membrane equation and adds compartment name to all compartment-specific variables

        :param string compartment_name: name of the compartment
        :return: string
        """
        membrane_eq = self.get_membrane_equation(return_string=True)

        substitutables = {key: key + '_' + compartment_name for key in self.compartment_vars_and_consts}
        compartment_eq = b2.Equations(membrane_eq, **substitutables)

        return compartment_eq

    def what_is_this(self):
        """
        Method to query for the URL describing the neuron model

        :return: url
        """

        return self.link_to_book

    def get_neuron_equations(self):
        """
        Returns the membrane equations in a form that prints out nicely in Jupyter Notebook

        :return: b2.Equations object
        """

        s = self.get_membrane_equation(return_string=True)
        return b2.Equations(s)

    def get_parameter_names(self):
        """
        Shows all the parameter names that can/must be defined

        :return: list
        """
        return self.default_neuron_parameters.keys()

    def get_neuron_parameters(self):
        """
        Shows all the current parameter names and values

        :return: dict
        """
        return self.neuron_parameters

    def set_neuron_parameters(self, **kwargs):
        """
        Set neuron parameters.
        If you don't know the correct units, use get_neuron_parameters() first to get the default parameters with
        correct units.

        :param kwargs: new parameter values are given as arguments
        """
        self.neuron_parameters.update(kwargs)

    def get_reset_statements(self):
        """
        Get the statements that will be executed once the neuron hits the threshold.

        :return: string
        """
        return self.reset_statements

    def get_threshold_condition(self):
        """
        Get the spike threshold condition.

        :return: string
        """
        return self.threshold_condition

    def get_refractory_period(self):
        """
        Get the refractory period (after a spike).

        :return: duration (typically in ms)
        """

        return self.neuron_parameters['refractory_period']

    def get_initial_values(self):  # Model-specific
        """
        Get initial values. If the initial value of vm is None, will replace it with EL (reversal potential of leak).

        :return:
        """
        init_vals = dict(self.initial_values)
        if init_vals['vm'] is None:
            vm_dict = {'vm': self.neuron_parameters['EL']}
            init_vals.update(vm_dict)

        return init_vals

    def get_states_to_monitor(self):
        """
        Get state variables to monitor (for method plot_states())

        :return: list
        """
        return self.states_to_monitor

    def set_model_definition(self, key, string_to_set):
        """
        Set the value of a template placeholder.

        :param string key: placeholder name
        :param string string_to_set: placeholder value

        """
        self.full_model_defns[key] = string_to_set

    def add_model_definition(self, key, string_to_add):
        """
        Append a string to a template placeholder.

        :param string key: placeholder name
        :param string_to_add: string to append to the placeholder

        """
        try:
            self.full_model_defns[key] += string_to_add
        except KeyError:  # ie if nothing has been defined
            self.full_model_defns[key] = string_to_add

    def simulate_neuron(self, I_stim=input_factory.get_zero_current(), simulation_time=1000*ms, **kwargs):
        """
        Simulate/stimulate the neuron

        :param I_stim: input stimulus (use the input_factory to create the stimulus)
        :param simulation_time: duration (usually in milliseconds, eg. 3000*ms)
        :param kwargs: custom neuron parameters can be given as arguments
        :return: b2.StateMonitor, b2.SpikeMonitor
        """

        neuron_parameters = dict(self.neuron_parameters)  # Make a copy of parameters; otherwise will change object params
        neuron_parameters.update(kwargs)
        refractory_period = neuron_parameters['refractory_period']

        stim_string = '+ I_stim(t,i)'
        old_model_defns = dict(self.full_model_defns)
        self.add_model_definition('EXT_CURRENTS', stim_string)
        eqs = self.get_membrane_equation()
        self.full_model_defns = old_model_defns

        # Create a neuron group
        neuron = b2.NeuronGroup(1,
                                model=eqs, namespace=neuron_parameters,
                                reset=self.reset_statements, threshold=self.threshold_condition,
                                refractory=refractory_period, method=self.integration_method)

        # Set initial values
        initial_values = self.get_initial_values()
        neuron.set_states(initial_values)

        # Set what to monitor
        state_monitor = b2.StateMonitor(neuron, self.get_states_to_monitor(), record=True)
        spike_monitor = b2.SpikeMonitor(neuron)

        # Run the simulation
        net = b2.Network(neuron, state_monitor, spike_monitor)
        net.run(simulation_time)

        return state_monitor, spike_monitor

    def getting_started(self, step_amplitude=1.2*nA, sine_amplitude=2.5*nA, sine_freq=150*Hz, sine_dc=2*nA):
        """
        Simple example that stimulates the neuron with a step and a sinusoidal current.

        :param step_amplitude: step current amplitude (in amps)
        :param sine_amplitude: sine current amplitude (in amps)
        :param sine_freq: sine current frequency (in Hz)
        :param sine_dc: constant current to inject during the sine stimulation (in amps)
        :return:
        """
        # specify step current
        step_current = input_factory.get_step_current(t_start=100, t_end=200, unit_time=ms, amplitude=step_amplitude)

        # run
        state_monitor, spike_monitor = self.simulate_neuron(I_stim=step_current, simulation_time=300 * ms)

        # plot the membrane voltage
        try:
            firing_threshold = self.neuron_parameters['VT']
        except KeyError:
            firing_threshold = None

        plot_tools.plot_voltage_and_current_traces(state_monitor, step_current,
                                                   title="Step current", firing_threshold=firing_threshold)
        print("nr of spikes: {}".format(len(spike_monitor.t)))
        plt.show()

        # second example: sinusoidal current. note the higher resolution 0.1 * ms
        sinusoidal_current = input_factory.get_sinusoidal_current(
            1000, 2000, unit_time=0.1 * ms,
            amplitude=sine_amplitude, frequency=sine_freq, direct_current=sine_dc)
        # run
        state_monitor, spike_monitor = self.simulate_neuron(
            I_stim=sinusoidal_current, simulation_time=300 * ms)
        # plot the membrane voltage
        plot_tools.plot_voltage_and_current_traces(
            state_monitor, sinusoidal_current, title="Sinusoidal input current",
            firing_threshold=firing_threshold)
        print("nr of spikes: {}".format(spike_monitor.count[0]))
        plt.show()

    def plot_fi_curve(self, min_current=0*pA, max_current=1*nA, step_size=10*pA, plot=True, max_rate=None, save_name=None):
        """
        Plot the frequency-current (f-I) curve.

        :param min_current: minimum current (in amps)
        :param max_current: maximum current (in amps)
        :param step_size: current step (in amps)
        :param bool plot: whether to plot the results or not
        :param max_rate: maximum frequency to show in the plot
        :return: steps, counts (if plot is False)
        """
        # Compute current steps
        steps = np.arange(min_current, max_current, step_size) * amp
        N_steps = len(steps)

        # Prepare params and eqs
        neuron_parameters = self.neuron_parameters
        refractory_period = neuron_parameters['refractory_period']
        eqs = self.get_membrane_equation(substitute_ad_hoc={'EXT_CURRENTS': '+ I_ext',
                                                            'EXT_CURRENTS_EQS': 'I_ext : amp'})

        # Create a neuron group
        neurons = b2.NeuronGroup(N_steps,
                                model=eqs, namespace=neuron_parameters,
                                reset=self.reset_statements, threshold=self.threshold_condition,
                                refractory=refractory_period, method=self.integration_method)

        # Set initial values
        initial_values = self.get_initial_values()
        neurons.set_states(initial_values)
        neurons.I_ext = 0*pA

        # Set what to monitor
        #state_monitor = b2.StateMonitor(neurons, self.get_states_to_monitor(), record=True)
        spike_monitor = b2.SpikeMonitor(neurons)

        # Run the simulation
        net = b2.Network(neurons, spike_monitor)
        net.run(500*ms)

        # Add step current
        neurons.I_ext = steps
        net.run(1000 * ms)

        counts = spike_monitor.count
        print(f'N_steps = {N_steps}')
        # print(f'dir(spike_monitor) = {dir(spike_monitor)}')
        # print(f"spike_monitor.get_states(['t', 'i']) = {spike_monitor.get_states(['t', 'i'])}")
        # print(f'len(spike_monitor.it) = {len(spike_monitor.it)}')
        # print(f'type(spike_monitor.it[0]) = {type(spike_monitor.it[0])}')
        
        # Plot/return the f-I curve
        if plot is True:
            plt.plot(steps/pA, counts)
            plt.title('f-I curve')
            plt.ylabel('Firing rate [Hz]')
            plt.xlabel('Current [pA]')
            if max_rate is not None:
                plt.ylim([0, max_rate])
            
            if save_name is not None:
                if save_name[-4:] != '.png' and save_name[-4:] != '.eps':
                    save_name += '.png'
                plt.savefig(save_name)
            
            plt.show()
        else:
            return steps, counts

    def plot_vm(self, state_monitor):
        """
        Plots the vm from a state monitor

        :param state_monitor: b2.StateMonitor with vm recording

        """

        plt.figure(figsize=(12, 4))
        plt.plot(state_monitor.t / ms, state_monitor.vm[0] / mV, lw=1)
        plt.title('Membrane voltage')
        plt.xlabel("time [ms]")
        plt.ylabel("vm [mV]")
        plt.show()

    def plot_states(self, state_monitor, parameters=None):
        """
        Plots pre-defined state variables from a state monitor

        :param state_monitor: b2.StateMonitor
        :param parameters: list of parameters
        """
        if parameters is None:
            print("No parameters specified. Plotting membrane voltage.")
            self.plot_vm(state_monitor)
        else:
            n_parameters = len(parameters)
            fig, axs = plt.subplots(n_parameters, figsize=(12, 4 * n_parameters))
            for i, parameter in enumerate(parameters):
                this_unit = self.parameter_units[parameter]
                axs[i].plot(state_monitor.t / ms, state_monitor[parameter][0] / this_unit, lw=1)
                axs[i].set_title(parameter)
                axs[i].set_xlabel("time [ms]")
                axs[i].set_ylabel(f"{parameter} [{this_unit}]")

    def get_json(self, include_neuron_name=True):
        """
        Creates a JSON string of parameter names and values (units are discarded).

        :param bool include_neuron_name: whether to include the neuron name
        :return: string
        """
        neuron_parameters_wo_units = dict()
        neuron_parameters_wo_units[self.neuron_name] = dict()
        for key, value in self.neuron_parameters.items():
            neuron_parameters_wo_units[self.neuron_name][key] = value / self.parameter_units[key]

        if include_neuron_name is True:
            return json.dumps(neuron_parameters_wo_units)
        else:
            return json.dumps(neuron_parameters_wo_units[self.neuron_name])

    def save_json(self, filename=None):
        """
        Saves the neuron parameters in a JSON file.

        :param string filename: Path to file. If None, will save as neuron_name.json

        """

        if filename is None:
            filename = self.neuron_name + '.json'

        with open(filename, 'w') as fi:
            fi.write(self.get_json())
            fi.close()

    def read_json(self, filename, neuron_name=None):
        """
        Read and load parameters from a JSON file.

        :param string filename: Path to file
        :param string neuron_name: the name of the neuron to read from the file

        """

        with open(filename, 'r') as fi:
            params_dict = json.load(fi)

        # If no neuron_name is provided, we take the first (and hopefully only) one
        if neuron_name is None:
            neuron_name = list(params_dict.keys())[0]

        self.neuron_name = neuron_name

        imported_params = dict()
        for key, value in params_dict[neuron_name].items():
            imported_params[key] = np.float(value) * self.parameter_units[key]

        self.neuron_parameters = imported_params

    def list_neurons_in_json(self, filename):
        """
        List neuron types (sets of parameters) in a JSON file

        :param string filename: Path to file
        :return: list
        """

        with open(filename, 'r') as fi:
            params_dict = json.load(fi)

        return list(params_dict.keys())

    def add_tonic_current(self, tonic_current=50 * pA, tau_rampup=None):
        """
        Adds tonic current injection to the neuron

        :param tonic_current: amplitude of current injection (in amps)
        :param tau_rampup: time constant for current ramp-up (in milliseconds)

        """

        assert 'tonic_current' not in self.neuron_parameters.keys(), \
            "Tonic current is already set, please modify neuron parameters instead of using this method"

        self.set_neuron_parameters(tonic_current=tonic_current, tau_tonic_rampup=tau_rampup)

        if tau_rampup is None:
            ext_currents_string = '+ tonic_current $EXT_CURRENTS'
        else:
            ext_currents_string = '+ tonic_current*(1-exp(-t/(tau_tonic_rampup))) $EXT_CURRENTS'

        self.add_model_definition('EXT_CURRENTS', ext_currents_string)

    def add_external_current(self, current_name='I_ext', current_eqs=None):
        """
        Adds an external current to the neuron

        :param string current_name: name of the current
        :param string current_eqs: equations describing the external current
        :return:
        """
        self.add_model_definition('EXT_CURRENTS', '+ '+current_name)
        if current_eqs is None:
            self.add_model_definition('EXT_CURRENTS_EQS', '\n' + current_name + ': amp')
        elif current_eqs == 'timedarray':
            # TimedArray with units do not need (nor tolerate) eqs definition
            pass
        else:
            self.add_model_definition('EXT_CURRENTS_EQS', '\n' + current_eqs)

    def add_vm_noise(self, noise_sigma=2*mV):
        """
        Adds a stochastic component to the membrane equation as explained in
        `Brian2 documentation <https://brian2.readthedocs.io/en/stable/user/models.html#noise>`_

        :param noise_sigma:
        :return:
        """
        self.set_model_definition('VM_NOISE', '+ noise_sigma*xi*taum_soma**-0.5')
        C = self.neuron_parameters['C']
        gL = self.neuron_parameters['gL']
        self.set_neuron_parameters(noise_sigma=noise_sigma, taum_soma=C / gL)

    def set_excitatory_receptors(self, receptor_name):
        """
        Sets the excitatory receptors.

        :param string receptor_name: name of receptor model (see neurodynlib.receptor_models)

        """
        assert receptor_name in ReceptorModel.ExcModelNames, \
            "Undefined excitation model!"

        receptor_model = ReceptorModel(receptor_name)
        synaptic_exc_model = receptor_model.get_receptor_equations()
        self.full_model_defns.update(synaptic_exc_model)

        # Add compartment-specific variable names to the common list
        self.compartment_vars_and_consts.extend(receptor_model.get_compartment_specific_variables())

    def set_inhibitory_receptors(self, receptor_name):
        """
        Sets the inhibitory receptors.

        :param string receptor_name: name of receptor model (see neurodynlib.receptor_models)

        """
        assert receptor_name in ReceptorModel.InhModelNames, \
            "Undefined inhibition model!"

        receptor_model = ReceptorModel(receptor_name)
        synaptic_inh_model = receptor_model.get_receptor_equations()
        self.full_model_defns.update(synaptic_inh_model)

        # Add compartment-specific variable names to the common list
        self.compartment_vars_and_consts.extend(receptor_model.get_compartment_specific_variables())

    def make_neuron_group(self, n):
        """
        Makes a Brian2 NeuronGroup

        :param int n: number of neurons
        :return: b2.NeuronGroup object
        """

        neuron_pop = b2.NeuronGroup(n, model=self.get_neuron_equations(),
                                       namespace=self.get_neuron_parameters(),
                                       reset=self.get_reset_statements(),
                                       threshold=self.get_threshold_condition(),
                                       refractory=self.get_refractory_period())
        return neuron_pop

class LifNeuron(PointNeuron):
    """
    Leaky Intergrate-and-Fire (LIF) model.
    See Neuronal Dynamics, `Chapter 1 Section 3 <http://neuronaldynamics.epfl.ch/online/Ch1.S3.html>`_.

    Requires setting the following parameters: EL, gL, C, V_res, VT.
    """

    # __OBFUSCATION_FACTORS = [543, 622, 9307, 584, 2029, 211]

    # The large gL and capacitance are from the original code
    default_neuron_parameters = {
            'EL': -70 * mV,
            'V_res': -65 * mV,
            'VT': -50 * mV,
            'gL': 100 * nS,
            'C': 800 * pF,
            'refractory_period': 2.0 * ms
    }

    neuron_model_defns = {'I_NEURON_MODEL': 'gL*(EL-vm)'}
    model_info_url = 'http://neuronaldynamics.epfl.ch/online/Ch1.S3.html'

    def __init__(self):
        super().__init__()

class ClopathAdexNeuron(PointNeuron):
    """
    Adaptive Exponential Integrate-and-Fire (ADEX) model including CLopath_2010_NatNeurosci extra variables.
    See Clopath et al. Nature Neuroscience 13 (2010) 344-352 <http://dx.doi.org/10.1038/nn.2479>`_.

    Requires setting the following parameters: EL, gL, C, V_res, VT, DeltaT, Vcut, a, b, tau_w,
    Isp, tau_z, tau_VT, VTmax, tau_lowpass1, tau_lowpass2, tau_homeo, x_reset, taux.
    """

    # The large gL and capacitance are from the original code
    default_neuron_parameters = {
            'EL': -70.0 * mV,
            'V_res': -51.0 * mV,
            'VTrest': -50.0 * mV,
            'gL': 2 * nS,
            'C': 10 * pF,
            'DeltaT': 2 * mV,
            'a': 0.5 * nS,
            'b': 7.0 * pA,
            'Isp': 40. * pA,
            'tau_w': 100.0 * ms,
            'tau_z': 40.0 * ms, 
            'refractory_period': 2.0 * ms,
            'Vcut': -30.0 * mV,
            'tau_VT': 50 * ms, 
            'VTmax': 30 * mV,
            'tau_lowpass1' : 40 * ms,    # timeconstant for low-pass filtered voltage
            'tau_lowpass2' : 30 * ms,    # timeconstant for low-pass filtered voltage
            'tau_homeo' : 1000 * ms,     # homeostatic timeconstant
            'x_reset' : 1.,            # spike trace reset value
            'taux' : 15. * ms           # spike trace time constant
    }

    neuron_model_defns = {'I_NEURON_MODEL': 'gL*(EL-vm) - w + z + gL * DeltaT * exp((vm-VT) / DeltaT)',
                          'NEURON_MODEL_EQS': 
            '''
            dw/dt = (a*(vm-EL) - w) / tau_w : amp
            dz/dt = -z / tau_z : amp                                        
            dVT/dt = (VTrest-VT) / tau_VT : volt
            dv_lowpass1 / dt = (vm - v_lowpass1) / tau_lowpass1 : volt      # low-pass filter of the voltage
            dv_lowpass2 / dt = (vm - v_lowpass2) / tau_lowpass2 : volt      # low-pass filter of the voltage
            dv_homeo / dt = (vm - EL - v_homeo) / tau_homeo : volt          # low-pass filter of the voltage
            dx_trace / dt = -x_trace / taux :1                              # spike trace
            '''
    }
    model_info_url = 'https://brian2.readthedocs.io/en/stable/examples/frompapers.Clopath_et_al_2010_homeostasis.html'

    def __init__(self):
        super().__init__()
        self.threshold_condition = 'vm > VT'
        self.reset_statements = 'vm = V_res; w += b; x_trace += x_reset / (taux / ms); z = Isp; VT = VTmax'
        self.initial_values = { 'vm': 'EL', 'w': 0.*pA, 'z': 0.*pA, 'x_trace': 0., 'v_lowpass1': -70.*mvolt, 
                                'v_lowpass2': -70.*mvolt, 'v_homeo': 0., 'VT': -50. * mvolt}
        # self.states_to_monitor = ['vm', 'w']
        new_parameter_units = {'DeltaT': mV, 'Vcut': mV, 'a': nS, 'b': pA, 'tau_w': ms, 'tau_z': ms}
        self.parameter_units.update(new_parameter_units)

class EifNeuron(PointNeuron):
    """
    Exponential Integrate-and-Fire (EIF) model.
    See Neuronal Dynamics, `Chapter 5 Section 2 <http://neuronaldynamics.epfl.ch/online/Ch5.S2.html>`_.

    Requires setting the following parameters: EL, gL, C, V_res, VT, DeltaT, Vcut.
    """

    # The large gL and capacitance come from the original code
    default_neuron_parameters = {
            'EL': -65.0 * mV,
            'V_res': -60.0 * mV,
            'VT': -55.0 * mV,  # soft threshold
            'gL': 50 * nS,
            'C': 600 * pF,
            'DeltaT': 2 * mV,  # spike sharpness
            'refractory_period': 2.0 * ms,
            'Vcut': -30.0 * mV  # technical threshold to tell the algorithm when to reset vm to v_reset
    }

    neuron_model_defns = {'I_NEURON_MODEL': 'gL*(EL-vm) + gL * DeltaT * exp((vm-VT) / DeltaT)'}
    model_info_url = 'http://neuronaldynamics.epfl.ch/online/Ch5.S2.html'

    def __init__(self):
        super().__init__()
        self.threshold_condition = 'vm > Vcut'
        new_parameter_units = {'DeltaT': mV, 'Vcut': mV}
        self.parameter_units.update(new_parameter_units)

    def getting_started(self, step_amplitude=0.8*nA, sine_amplitude=1.6*nA, sine_freq=150*Hz, sine_dc=1.3*nA):
        super().getting_started(step_amplitude, sine_amplitude, sine_freq, sine_dc)

class AdexNeuron(PointNeuron):
    """
    Adaptive Exponential Integrate-and-Fire (ADEX) model.
    See Neuronal Dynamics, `Chapter 6 Section 1 <http://neuronaldynamics.epfl.ch/online/Ch6.S1.html>`_.

    Requires setting the following parameters: EL, gL, C, V_res, VT, DeltaT, Vcut, a, b, tau_w.
    """

    # Default values (see Table 6.1, Initial Burst)
    # http://neuronaldynamics.epfl.ch/online/Ch6.S2.html#Ch6.F3
    default_neuron_parameters = {
            'EL': -70.0 * mV,
            'V_res': -51.0 * mV,
            'VT': -50.0 * mV,
            'gL': 2 * nS,
            'C': 10 * pF,
            'DeltaT': 2 * mV,
            'a': 0.5 * nS,
            'b': 7.0 * pA,
            'tau_w': 100.0 * ms,
            'refractory_period': 2.0 * ms,
            'Vcut': -30.0 * mV
    }

    neuron_model_defns = {'I_NEURON_MODEL': 'gL*(EL-vm) - w + gL * DeltaT * exp((vm-VT) / DeltaT)',
                          'NEURON_MODEL_EQS': 'dw/dt = (a*(vm-EL) - w) / tau_w : amp'}
    model_info_url = 'http://neuronaldynamics.epfl.ch/online/Ch6.S1.html'

    def __init__(self):

        super().__init__()
        self.threshold_condition = 'vm > Vcut'
        self.reset_statements = 'vm = V_res; w += b'
        self.initial_values = {'vm': 'EL', 'w': 0*pA}
        self.states_to_monitor = ['vm', 'w']
        new_parameter_units = {'DeltaT': mV, 'Vcut': mV, 'a': nS, 'b': pA, 'tau_w': ms}
        self.parameter_units.update(new_parameter_units)

    # This function implement Adaptive Exponential Leaky Integrate-And-Fire neuron model

    def getting_started(self, step_amplitude=65*pA, sine_amplitude=125*pA, sine_freq=150*Hz, sine_dc=100*pA):
        super().getting_started(step_amplitude, sine_amplitude, sine_freq, sine_dc)

    def plot_states(self, state_monitor, spike_monitor=None, save_name=None):
        """
        Visualizes the state variables: w-t, vm-t and phase-plane w-vm

        :param state_monitor: b2.StateMonitor

        """
        parameters = self.get_neuron_parameters()
        if save_name is None:
            n_hor_panels =2
        else:
            n_hor_panels = 3
        plt.subplot(2, n_hor_panels, 1)
        plt.plot(state_monitor.t / ms, state_monitor.vm[0] / mV, lw=2)
        plt.xlabel("t [ms]")
        plt.ylabel("u [mV]")
        plt.axhline(parameters['EL'] / mV, ls='-', color='k')
        plt.title("Membrane potential")
        plt.subplot(2, n_hor_panels, 2)
        plt.plot(state_monitor.vm[0] / mV, state_monitor.w[0] / pA, lw=2)
        plt.xlabel("u [mV]")
        plt.ylabel("w [pA]")
        plt.title("Phase plane representation")
        plt.subplot(2, n_hor_panels, n_hor_panels + 1)
        plt.plot(state_monitor.t / ms, state_monitor.w[0] / pA, lw=2)
        plt.xlabel("t [ms]")
        plt.ylabel("w [pA]")
        plt.plot([state_monitor.t[0] / ms, state_monitor.t[-1] / ms], [0, 0], '-', color='black', lw=1)
        plt.title("Adaptation current")

        # Plot spikes as vertical dashed lines to Membrane potential and Adaptation current plots
        if spike_monitor is not None:
            for t in spike_monitor.t:
                plt.subplot(2, n_hor_panels, 1)
                plt.axvline(t / ms, ls='--', c='k')
                plt.subplot(2, n_hor_panels, n_hor_panels + 1)
                plt.axvline(t / ms, ls='--', c='k')

        plt.tight_layout(w_pad=0.5, h_pad=1.5)

        # Check save_name for suffix png or eps. If no suffix is provided, use .png
        if save_name is not None:
            # write parameters to the plot
            plt.subplot(2, n_hor_panels, 3)

            plt.axis('off')
            plt.text(0.1, 0.9, 'EL = %.2f mV' % (parameters['EL'] / mV), fontsize=10)
            plt.text(0.1, 0.8, 'V_res = %.2f mV' % (parameters['V_res'] / mV), fontsize=10)
            plt.text(0.1, 0.7, 'VT = %.2f mV' % (parameters['VT'] / mV), fontsize=10)
            plt.text(0.1, 0.6, 'gL = %.2f nS' % (parameters['gL'] / nS), fontsize=10)
            plt.text(0.1, 0.5, 'C = %.2f pF' % (parameters['C'] / pF), fontsize=10)
            plt.text(0.1, 0.4, 'DeltaT = %.2f mV' % (parameters['DeltaT'] / mV), fontsize=10)
            plt.text(0.1, 0.3, 'a = %.2f nS' % (parameters['a'] / nS), fontsize=10)
            plt.text(0.1, 0.2, 'b = %.2f pA' % (parameters['b'] / pA), fontsize=10)
            plt.text(0.1, 0.1, 'tau_w = %.2f ms' % (parameters['tau_w'] / ms), fontsize=10)

            if save_name[-4:] != '.png' and save_name[-4:] != '.eps':
                save_name += '.png'
            plt.savefig(save_name)

        plt.show()

class HodgkinHuxleyNeuron(PointNeuron):
    """
    Implementation of a Hodgkin-Huxley neuron with Na, K and leak channels (SIMPLE_HH).
    See Neuronal Dynamics, `Chapter 2 Section 2 <http://neuronaldynamics.epfl.ch/online/Ch2.S2.html>`_

    Requires setting the following parameters: EL, gL, C, EK, ENa, gK, gNa, V_spike.
    """

    default_neuron_parameters = {
            'EL': 10.6 * mV,
            'gL': 0.3 * msiemens,
            'C': 1 * ufarad,
            'EK': -12 * mV,
            'ENa': 115 * mV,
            'gK': 36 * msiemens,
            'gNa': 120 * msiemens,
            'refractory_period': 2.0 * ms,
            'V_spike': 60 * mV
    }

    neuron_model_defns = {
        'I_NEURON_MODEL': 'gL*(EL-vm) + gNa*m**3*h*(ENa-vm) + gK*n**4*(EK-vm)',
        'NEURON_MODEL_EQS':
        '''
        alphah = .07*exp(-.05*vm/mV)/ms : Hz
        alpham = .1*(25*mV-vm)/(exp(2.5-.1*vm/mV)-1)/mV/ms : Hz
        alphan = .01*(10*mV-vm)/(exp(1-.1*vm/mV)-1)/mV/ms : Hz
        betah = 1./(1+exp(3.-.1*vm/mV))/ms : Hz
        betam = 4*exp(-.0556*vm/mV)/ms : Hz
        betan = .125*exp(-.0125*vm/mV)/ms : Hz
        dh/dt = alphah*(1-h)-betah*h : 1
        dm/dt = alpham*(1-m)-betam*m : 1
        dn/dt = alphan*(1-n)-betan*n : 1
        '''
    }
    model_info_url = 'http://neuronaldynamics.epfl.ch/online/Ch2.S2.html'

    def __init__(self):

        super().__init__()
        self.threshold_condition = 'vm > V_spike'
        self.reset_statements = ''
        self.integration_method = 'exponential_euler'
        self.initial_values = {'m': 0.05, 'h': 0.60, 'n': 0.32, 'vm': 0*mV}
        self.states_to_monitor = ['vm', 'm', 'n', 'h']
        new_parameter_units = {'EK': mV, 'ENa': mV, 'gK': nS, 'gNa': nS, 'V_spike': mV}
        self.parameter_units.update(new_parameter_units)

    def plot_states(self, state_monitor):
        """
        Plots the state variables vm, m, n, h vs. time.

        :param state_monitor: b2.StateMonitor

        """
        plt.subplots(3, 1, sharex=True)

        plt.subplot(311)
        plt.plot(state_monitor.t / ms, state_monitor.vm[0] / mV, lw=2)
        plt.title('Membrane voltage')
        #plt.xlabel("t [ms]")
        plt.ylabel("v [mV]")
        plt.grid()

        plt.subplot(312)
        plt.title('gNa activation (m) and inactivation (h)')
        plt.plot(state_monitor.t / ms, state_monitor.m[0] / b2.volt, "black", lw=2, label='m')
        plt.plot(state_monitor.t / ms, state_monitor.h[0] / b2.volt, "red", lw=2, label='h')
        #plt.xlabel("t (ms)")
        plt.ylabel("act./inact. [a.u.]")
        plt.legend()
        plt.ylim((0, 1))
        plt.grid()

        plt.subplot(313)
        plt.title('gK activation (n)')
        plt.plot(state_monitor.t / ms, state_monitor.n[0] / b2.volt, "blue", lw=2)
        plt.xlabel("t (ms)")
        plt.ylabel("act. [a.u.]")
        plt.ylim((0, 1))
        plt.grid()

        # plt.plot(state_monitor.t / ms, state_monitor.I_e[0] / b2.uamp, lw=2)
        # plt.axis((
        #     0,
        #     np.max(state_monitor.t / ms),
        #     min(state_monitor.I_e[0] / b2.uamp) * 1.1,
        #     max(state_monitor.I_e[0] / b2.uamp) * 1.1
        # ))
        #
        # plt.xlabel("t [ms]")
        # plt.ylabel("I [micro A]")
        plt.grid()

        plt.tight_layout(w_pad=0.5, h_pad=1.5)

        plt.show()

    def getting_started(self, step_amplitude=7.2*uA, sine_amplitude=3.6*uA, sine_freq=150*Hz, sine_dc=2.9*nA):
        super().getting_started(step_amplitude, sine_amplitude, sine_freq, sine_dc)

class IzhikevichNeuron(PointNeuron):
    """
    Izhikevich model (IZHIKEVICH).
    See Neuronal Dynamics, `Chapter 6 Section 1 <http://neuronaldynamics.epfl.ch/online/Ch6.S1.html>`_

    Here, we use the formulation and parameters presented in
    `Izhikevich & Edelman 2008 PNAS <https://www.pnas.org/content/105/9/3593>`_.

    Requires setting the following parameters: EL, C, V_res, VT, k, a, b, d, Vcut.
    """

    # Default parameters give a chattering (CH) neuron
    default_neuron_parameters = {
            'EL': -60.0*mV,            # equivalent to v_r in PNAS 2008
            'V_res': -40.0*mV,         # c
            'VT': -40.0*mV,            # v_t
            'C': 50*pF,
            'k': 1.5*nS/mV,
            'a': 0.03/ms,              # inverse of recovery time constant
            'b': 5*nS,
            'd': 150* pA,
            'refractory_period': 2.0 * ms,
            'Vcut': 35.0*mV            # v_peak
    }


    neuron_model_defns = {'I_NEURON_MODEL': 'k * (vm-EL) * (vm-VT) - u',
                          'NEURON_MODEL_EQS': 'du/dt = a*(b*(vm-EL) - u) : amp'}
    model_info_url = 'http://neuronaldynamics.epfl.ch/online/Ch6.S1.html'

    def __init__(self):
        super().__init__()
        self.threshold_condition = 'vm > Vcut'
        self.reset_statements = 'vm = V_res; u += d'
        self.initial_values = {'vm': None, 'u': 0}
        self.states_to_monitor = ['vm', 'u']
        new_parameter_units = {'Vcut': mV, 'k': nS/mV, 'a': (1/ms), 'b': nS, 'd': pA, 'tau_w': ms}
        self.parameter_units.update(new_parameter_units)

    def plot_states(self, state_monitor):
        """
        Visualizes the state variables: u-t, vm-t and phase-plane u-vm

        :param state_monitor: b2.StateMonitor

        """

        plt.subplot(2, 2, 1)
        plt.plot(state_monitor.t / ms, state_monitor.vm[0] / mV, lw=2)
        plt.xlabel("t [ms]")
        plt.ylabel("u [mV]")
        plt.title("Membrane potential")
        plt.subplot(2, 2, 2)
        plt.plot(state_monitor.vm[0] / mV, state_monitor.u[0] / pA, lw=2)
        plt.xlabel("u [mV]")
        plt.ylabel("w [pA]")
        plt.title("Phase plane representation")
        plt.subplot(2, 2, 3)
        plt.plot(state_monitor.t / ms, state_monitor.u[0] / pA, lw=2)
        plt.xlabel("t [ms]")
        plt.ylabel("w [pA]")
        plt.title("Adaptation current")

        plt.tight_layout(w_pad=0.5, h_pad=1.5)
        plt.show()

class LifAscNeuron(PointNeuron):  # TODO - Figure out why output different from plots in cell type atlas
    """
    Leaky Integrate-and-Fire with After-spike Currents (LIFASC).
    One of the generalized LIF (GLIF_3) models used in the Allen Brain Institute.

    For more information, see http://celltypes.brain-map.org/ ,
    http://help.brain-map.org/display/celltypes/Documentation?_ga=2.31556414.1221863260.1571652272-1994599725.1571652272 ,
    or Teeter et al. 2018 Nature Comm. https://www.nature.com/articles/s41467-017-02717-4.

    Requires setting the following parameters: EL, gL, C, V_res, VT, A_asc1, A_asc2, tau_asc1, tau_asc2.
    """

    # The default parameters correspond to neuronal_model_id = 637925685 available at
    # https://celltypes.brain-map.org/experiment/electrophysiology/623893177
    default_neuron_parameters = {
        'EL': -77.01623281 * mvolt,
        'C': 233.02310736 * pfarad,
        'gL': 8.10525954 * nsiemens,
        'A_asc1': -56.75679504 * pamp,
        'tau_asc1': 100. * msecond,
        'A_asc2': -0.60597377 * namp,
        'tau_asc2': 10. * msecond,
        'V_res': -77. * mvolt,
        'VT': -49.31118264 * mvolt,
        'refractory_period': 2. * msecond
    }

    neuron_model_defns = {'I_NEURON_MODEL': 'gL*(EL - vm) + I_asc1 + I_asc2',
                          'NEURON_MODEL_EQS': '''
                          dI_asc1/dt = -I_asc1/tau_asc1 : amp
                          dI_asc2/dt = -I_asc2/tau_asc2 : amp
                          '''}
    model_info_url = 'https://www.nature.com/articles/s41467-017-02717-4'

    def __init__(self):
        super().__init__()
        self.threshold_condition = 'vm > VT'
        self.reset_statements = 'vm = V_res; I_asc1 += A_asc1; I_asc2 += A_asc2'
        self.initial_values = {'vm': None, 'I_asc1': 0.0, 'I_asc2': 0.0}
        self.states_to_monitor = ['vm', 'I_asc1', 'I_asc2']
        new_parameter_units = {'A_asc1': pA, 'A_asc2': pA, 'tau_asc1': ms, 'tau_asc2': ms}
        self.parameter_units.update(new_parameter_units)


    def read_abi_neuron_config(self, neuron_config):
        """
        Method for importing parameters from the Allen Brain Institute's cell type atlas.
        Parameters can be obtained by downloading the json from their website.

        You can also use the AllenSDK::

           from allensdk.api.queries.glif_api import GlifApi
           neuron_config = GlifApi().get_neuron_configs([neuronal_model_id])[neuronal_model_id]

        :param neuron_config:
        :return:
        """

        if len(neuron_config['asc_amp_array']) > 2:
            print('Warning! Model has more than 2 afterspike currents. Will take only the first two.')

        abi_parameters = {
            'EL': neuron_config['El_reference'] * volt,
            'C': neuron_config['C'] * farad,
            'gL': (1 / neuron_config['R_input']) * siemens,
            'VT': (neuron_config['El_reference'] + neuron_config['th_inf']) * volt,
            'A_asc1': neuron_config['asc_amp_array'][0] * amp,
            'A_asc2': neuron_config['asc_amp_array'][1] * amp,
            'tau_asc1': neuron_config['asc_tau_array'][0] * second,
            'tau_asc2': neuron_config['asc_tau_array'][1] * second
        }

        self.initial_values['I_asc1'] = neuron_config['init_AScurrents'][0] * amp
        self.initial_values['I_asc2'] = neuron_config['init_AScurrents'][1] * amp

        self.set_neuron_parameters(**abi_parameters)

class neuron_factory:
    def __init__(self):
        self.name_to_class = {'LIF': LifNeuron, 'LifNeuron': LifNeuron,
                            'CADEX': ClopathAdexNeuron, 'ClopathAdexNeuron': ClopathAdexNeuron,
                            'EIF': EifNeuron, 'EifNeuron': EifNeuron,
                            'ADEX': AdexNeuron, 'AdexNeuron': AdexNeuron,
                            'SIMPLE_HH': HodgkinHuxleyNeuron, 'HodgkinHuxleyNeuron': HodgkinHuxleyNeuron,
                            'IZHIKEVICH': IzhikevichNeuron, 'IzhikevichNeuron': IzhikevichNeuron,
                            'LIFASC': LifAscNeuron, 'LifAscNeuron': LifAscNeuron}

    def get_class(self, neuron_model_name):
        return copy.deepcopy(self.name_to_class[neuron_model_name]())



if __name__ == '__main__':
    pass
