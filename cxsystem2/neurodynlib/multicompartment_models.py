import numpy as np
import matplotlib.pyplot as plt
import random
import brian2 as b2
from brian2.units import *
import cxsystem2.neurodynlib as nd


class LeakyCompartment(nd.PointNeuron):

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

class MulticompartmentNeuron(object):
    def __init__(self):
        super().__init__()


class EifPyramidalCell(MulticompartmentNeuron):

    default_neuron_parameters = {
        'C': [10,20,30,40,50,60]*pF,
        'g_leak': [1,2,3,4,5,6]*nS,
        'fract_areas': 1,
        'total_pyram_area': 1,
        'Ra': [1,2,3,4,5,6]*ohm
    }

    def __init__(self, n_apical=3):
        super().__init__()

        # Construct equations of all the compartments with compartment-specific variable names
        self.soma_compartment = nd.EifNeuron()  # but note that in legacy code soma's vm is vm, not vm_soma
        self.basal_compartment = LeakyCompartment()
        self.apical_compartments = [LeakyCompartment() for i in range(n_apical)]
        self.n_apical = n_apical

        self.neuron_parameters = self.default_neuron_parameters
        self.compartment_vars_and_consts = ['vm']

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


    def get_neuron_equations(self):

        # For convenience
        R_axial = self.neuron_parameters['Ra']
        C = self.neuron_parameters['C']
        g_leak = self.neuron_parameters['g_leak']

        # Dendritic current templates
        I_dendr_1way = 'I_dendr = gapre*(vmpre-vmself) : amp'
        I_dendr_2way = 'I_dendr = gapre*(vmpre-vmself) + gapost*(vmpost-vmself) : amp'

        # First create the vm equations for each compartment
        ## Basal compartment
        temp_eq = b2.Equations(I_dendr_1way,
                               I_dendr='I_dendr_basal', vmself='vm_basal', vmpre='vm',
                               gapre=1 / (R_axial[0]))
        self.basal_compartment.add_external_current('I_dendr_basal', str(temp_eq))
        eq_basal = self.basal_compartment.get_compartment_equations('basal')
        eq_basal = b2.Equations(str(eq_basal),
                                C=C[0], g_leak=g_leak[0])

        ## The soma
        temp_eq = b2.Equations(I_dendr_2way,
                               I_dendr='I_dendr_soma', vmself='vm',
                               vmpre='vm_a0', vmpost='vm_basal',
                               gapre=1 / (R_axial[1]), gapost=1 / (R_axial[0]))
        self.soma_compartment.add_external_current('I_dendr_soma', str(temp_eq))
        eq_soma = self.soma_compartment.get_compartment_equations('soma')

        eq_soma = b2.Equations(str(eq_soma), vm_soma='vm')  # exception!
        eq_soma = b2.Equations(str(eq_soma),
                                C=C[1], g_leak=g_leak[1])

        # ## Finally, go through all apical compartments but not the last one
        n_apical = self.n_apical
        eq_apicals = []
        pre_compartment = 'soma'
        for i in range(n_apical-1):
            temp_eq = b2.Equations(I_dendr_2way,
                                   I_dendr='I_dendr_a%d'%i, vmself='vm_a%d'%i,
                                   vmpre='vm_'+pre_compartment, vmpost='vm_a%d'%(i+1),
                                   gapre=1 / (R_axial[i+1]), gapost=1 / (R_axial[i+2]))
            self.apical_compartments[i].add_external_current('I_dendr_a%d'%i, str(temp_eq))
            eq_apical = self.apical_compartments[i].get_compartment_equations('a%d'%i)
            eq_apical = b2.Equations(str(eq_apical),
                                   C=C[i+2], g_leak=g_leak[i+2])
            eq_apicals.append(eq_apical)
            pre_compartment = 'a%d'%i

        # TODO - Fix this!!
        ## The last apical compartment

        last_ix = n_apical - 1
        if n_apical == 1:
            pre_compartment = 'soma'
            vm_pre = 'vm'
        else:
            pre_compartment = 'a%d' % (last_ix - 1)
            vm_pre = 'vm_'+pre_compartment

        temp_eq = b2.Equations(I_dendr_1way,
                               I_dendr='I_dendr_a%d'%last_ix, vmself='vm_a%d' % last_ix,
                               vmpre=vm_pre,
                               gapre=1 / (R_axial[last_ix + 1]))
        self.apical_compartments[i].add_external_current('I_dendr_a%d' % last_ix, str(temp_eq))
        eq_apical = self.apical_compartments[i].get_compartment_equations('a%d' % last_ix)
        eq_apical = b2.Equations(str(eq_apical),
                                 C=C[last_ix + 2], g_leak=g_leak[last_ix + 2])
        eq_apicals.append(eq_apical)

        # Combine all the equations into one
        # . Get the first line of every compartments equ
        # . Combine these
        # . Get the remaining lines
        # . Then combine these
        # (I wonder if the order even matters?)

        final_eq = eq_basal+eq_soma
        for i in range(n_apical):
            final_eq += eq_apicals[i]

        return final_eq