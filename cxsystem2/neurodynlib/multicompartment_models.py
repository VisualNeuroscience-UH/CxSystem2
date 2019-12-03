import brian2 as b2
from brian2.units import *

import cxsystem2.neurodynlib.neuron_models as nd


class LeakyCompartment(nd.PointNeuron):
    """
    Not implemented!
    A leaky capacitor to be used as a template for pyramidal cell compartments.
    """

    default_neuron_parameters = {
            'E_leak': -70 * mV,
            'V_reset': -65 * mV,
            'V_threshold': -50 * mV,
            'g_leak': 10 * nS,
            'C': 100 * pF,
            'refractory_period': 2.0 * ms
    }

    neuron_model_defns = {
        'I_NEURON_MODEL': 'g_leak*(E_leak-vm)',
        'BRIAN2_FLAGS': ''

    }

    def __init__(self):
        super().__init__()
        # self.compartment_vars_and_consts = ['vm', 'g_leak', 'C']

class MulticompartmentNeuron:
    """
    Not implemented!
    A base class for multicompartmental neuron models.
    """
    def __init__(self):
        super().__init__()


class LegacyPyramidalCell(MulticompartmentNeuron):
    """
    Not implemented!
    The kind of pyramidal cell used in Heikkinen et al. 2015 J Neurosci, Andalibi et al. 2019 Neural Computation,
    and Hokkanen et al. 2019 Neural Computation. See cxsystem2.core.equation_templates for the current implementation.
    """

    default_neuron_parameters = {
        'C': [10,20,30,40,50,60]*pF,
        'g_leak': [1,2,3,4,5,6]*nS,
        'Ra': [1,1/2,1/3,1/4,1/5,1/6]*ohm
    }

    def __init__(self, n_apical=3):
        super().__init__()

        assert n_apical > 0, "PC must have at least one apical compartment"
        self.n_apical = n_apical
        self.neuron_parameters = self.default_neuron_parameters

        # Make isopotential compartments
        self.soma_compartment = nd.EifNeuron()
        self.basal_compartment = LeakyCompartment()
        self.apical_compartments = [LeakyCompartment() for i in range(n_apical)]

        # Some custom settings
        self.soma_compartment.compartment_vars_and_consts = ['vm']
        self.basal_compartment.compartment_vars_and_consts = ['vm']
        self.basal_compartment.full_model_defns['BRIAN2_FLAGS'] = ''
        for i in range(n_apical):
            self.apical_compartments[i].compartment_vars_and_consts = ['vm']
            self.apical_compartments[i].full_model_defns['BRIAN2_FLAGS'] = ''

        # Variable for final eqs
        self.final_eqs = None

    def set_neuron_parameters(self, **kwargs):
        self.default_neuron_parameters.update(**kwargs)

    def add_tonic_current(self, tonic_current=50 * pA, tau_rampup=None):  # Used by CxSystem

        assert 'tonic_current' not in self.neuron_parameters.keys(), \
            "Tonic current is already set, please modify neuron parameters instead of using this method"

        self.soma_compartment.set_neuron_parameters(I_tonic=tonic_current, tau_tonic_rampup=tau_rampup)

        if tau_rampup is None:
            ext_currents_string = '+ tonic_current $EXT_CURRENTS'
        else:
            ext_currents_string = '+ tonic_current*(1-exp(-t/(tau_tonic_rampup))) $EXT_CURRENTS'

        self.soma_compartment.add_model_definition('EXT_CURRENTS', ext_currents_string)

    def add_vm_noise(self, sigma_noise=2 * mV):  # Used by CxSystem
        self.soma_compartment.set_model_definition('VM_NOISE', '+ sigma_noise*xi*taum_soma**-0.5')
        C = self.neuron_parameters['C'][1]  # Not sure if this is the right way
        g_leak = self.neuron_parameters['g_leak'][1]  # Not sure if this is the right way
        self.soma_compartment.set_neuron_parameters(sigma_noise=sigma_noise, taum_soma=C / g_leak)

    def set_excitatory_receptors(self, receptor_name):

        self.soma_compartment.set_excitatory_receptors(receptor_name)
        self.basal_compartment.set_excitatory_receptors(receptor_name)
        for i in range(self.n_apical):
            self.apical_compartments[i].set_excitatory_receptors(receptor_name)

    def set_inhibitory_receptors(self, receptor_name):

        self.soma_compartment.set_inhibitory_receptors(receptor_name)
        self.basal_compartment.set_inhibitory_receptors(receptor_name)
        for i in range(self.n_apical):
            self.apical_compartments[i].set_inhibitory_receptors(receptor_name)

    def get_threshold_condition(self):
        return self.soma_compartment.get_threshold_condition()

    def get_reset_statements(self):
        return self.soma_compartment.get_reset_statements()

    def get_refractory_period(self):
        return self.soma_compartment.get_refractory_period()

    def make_neuron_equations(self):
        # Topology here is: (POST) basal -> soma -> a0 -> a1 -> ... (PRE)
        # Multiple different indexes:
        #  - C, g_leak are indexed 0...N from basal...last apical
        #  - Apical dendrite compartments are indexed 0...(N-2)
        #  - Ra is indexed 0...(N-1) from basal...last apical
        # In legacy code, vm of soma is vm, not vm_soma. To keep things separate & clear, however,
        # we will replace vm_soma->vm only in the very end

        # For convenience
        R_axial = self.neuron_parameters['Ra']
        C = self.neuron_parameters['C']
        g_leak = self.neuron_parameters['g_leak']

        # Dendritic current templates
        I_dendr_basal = 'I_dendr = gapre*(vmpre-vmself) : amp'
        I_dendr_2way = 'I_dendr = gapre*(vmpre-vmself) + gapost*(vmpost-vmself) : amp'
        I_dendr_last_apical = 'I_dendr = gapost*(vmpost-vmself) : amp'

        # Basal compartment
        temp_eq = b2.Equations(I_dendr_basal,
                               I_dendr='I_dendr_basal', vmself='vm_basal', vmpre='vm_soma',
                               gapre=1 / (R_axial[0]))
        self.basal_compartment.add_external_current('I_dendr_basal', str(temp_eq))
        eq_basal = self.basal_compartment.get_compartment_equations('basal')
        eq_basal = b2.Equations(str(eq_basal), C=C[0], g_leak=g_leak[0])

        # The soma
        temp_eq = b2.Equations(I_dendr_2way,
                               I_dendr='I_dendr_soma', vmself='vm_soma',
                               vmpre='vm_a0', vmpost='vm_basal',
                               gapre=1 / (R_axial[1]), gapost=1 / (R_axial[0]))
        self.soma_compartment.add_external_current('I_dendr_soma', str(temp_eq))
        eq_soma = self.soma_compartment.get_compartment_equations('soma')

        eq_soma = b2.Equations(str(eq_soma), C=C[1], g_leak=g_leak[1])

        # Finally, go through all apical compartments but not the last one
        n_apical = self.n_apical
        eq_apicals = []
        post_compartment = 'soma'
        for i in range(n_apical-1):
            temp_eq = b2.Equations(I_dendr_2way,
                                   I_dendr='I_dendr_a%d'%i, vmself='vm_a%d'%i,
                                   vmpre='vm_a%d'%(i+1), vmpost='vm_'+post_compartment,
                                   gapre=1 / (R_axial[i+2]), gapost=1 / (R_axial[i+1]))
            self.apical_compartments[i].add_external_current('I_dendr_a%d'%i, str(temp_eq))
            eq_apical = self.apical_compartments[i].get_compartment_equations('a%d'%i)
            eq_apical = b2.Equations(str(eq_apical),
                                   C=C[i+2], g_leak=g_leak[i+2])
            eq_apicals.append(eq_apical)
            post_compartment = 'a%d'%i


        # The last apical compartment
        last_ix = n_apical - 1
        if n_apical == 1:
            post_compartment = 'soma'
        else:
            post_compartment = 'a%d' % (last_ix - 1)

        vm_post = 'vm_'+post_compartment

        temp_eq = b2.Equations(I_dendr_last_apical,
                               I_dendr='I_dendr_a%d'%last_ix, vmself='vm_a%d' % last_ix,
                               vmpost=vm_post, gapost=1 / (R_axial[-1]))
        # R_axial[-1] can be wrong but we keep it in this legacy version

        self.apical_compartments[last_ix].add_external_current('I_dendr_a%d' % last_ix, str(temp_eq))
        eq_apical = self.apical_compartments[last_ix].get_compartment_equations('a%d' % last_ix)
        eq_apical = b2.Equations(str(eq_apical),
                                 C=C[last_ix + 2], g_leak=g_leak[last_ix + 2])
        eq_apicals.append(eq_apical)

        # Combine all the equations into one & replace vm_soma -> vm

        final_eq = eq_basal+eq_soma
        for i in range(n_apical):
            final_eq += eq_apicals[i]

        self.final_eqs = b2.Equations(str(final_eq), vm_soma='vm')

    def get_neuron_equations(self):
        if self.final_eqs is None:
            self.make_neuron_equations()

        return self.final_eqs
