
class ReceptorModel:
    # <editor-fold desc="SYNAPTIC EXC/INH MODEL COMPONENTS">
    default_synaptic_excinh_strings = {}

    ExcModelNames = ['SIMPLE_E', 'E_ALPHA', 'E_ALPHA_NONSCALED', 'AMPA_NMDA', 'AMPA_NMDA_BIEXP', 'SIMPLE_E_NMDA', 'E_ALPHA_NMDA']
    InhModelNames = ['SIMPLE_I', 'I_ALPHA', 'I_ALPHA_NONSCALED', 'GABAA_GABAB', 'GABAA_GABAB_BIEXP', 'SIMPLE_I_GABAB', 'I_ALPHA_GABAB']

    SynapticExcInhModels = dict()

    # <editor-fold desc="...NeCo excitation/inhibition models">

    # Simple synaptic current models
    SynapticExcInhModels['SIMPLE_E'] = {'I_SYNAPTIC_EXC': '+ ge * (Ee - vm)',
                                        'SYNAPTIC_EXC_EQS': 'dge/dt = -ge/tau_e : siemens'}
    SynapticExcInhModels['SIMPLE_I'] = {'I_SYNAPTIC_INH': '+ gi * (Ei - vm)',
                                        'SYNAPTIC_INH_EQS': 'dgi/dt = -gi/tau_i : siemens'}

    # Alpha synapses
    # Non-scaled versions provided for backwards compatibility (were used in VCX model);
    # reach only 1/e = 37% of given peak conductance
    SynapticExcInhModels['E_ALPHA'] = {'I_SYNAPTIC_EXC': '+ gealpha * (Ee - vm)',
                                       'SYNAPTIC_EXC_EQS':
                                           '''dge/dt = -ge/tau_e_alpha : siemens
                                              dgealpha1/dt = (ge-gealpha1)/tau_e_alpha : siemens
                                              gealpha = scaling_alpha*exp(1)*gealpha1 : siemens
                                              '''}

    SynapticExcInhModels['I_ALPHA'] = {'I_SYNAPTIC_INH': '+ gialpha * (Ei - vm)',
                                       'SYNAPTIC_INH_EQS':
                                           '''dgi/dt = -gi/tau_i_alpha : siemens
                                              dgialpha1/dt = (gi-gialpha1)/tau_i_alpha : siemens
                                              gialpha = scaling_alpha*exp(1)*gialpha1 : siemens
                                              '''}

    SynapticExcInhModels['E_ALPHA_NONSCALED'] = {'I_SYNAPTIC_EXC': '+ gealpha * (Ee - vm)',
                                                 'SYNAPTIC_EXC_EQS':
                                                     '''dge/dt = -ge/tau_e_alpha : siemens
                                                        dgealpha/dt = (ge-gealpha)/tau_e_alpha : siemens
                                                 '''}

    SynapticExcInhModels['I_ALPHA_NONSCALED'] = {'I_SYNAPTIC_INH': '+ gialpha * (Ei - vm)',
                                                 'SYNAPTIC_INH_EQS':
                                                     '''dgi/dt = -gi/tau_i_alpha : siemens
                                                        dgialpha/dt = (gi-gialpha)/tau_i_alpha : siemens
                                                 '''}

    # Alpha synapse + NMDA (CXSYSTEM SPECIFIC VERSIONS)
    SynapticExcInhModels['E_ALPHA_NMDA'] = {'I_SYNAPTIC_EXC': '+ gealpha * (Ee - vm) + g_nmda_alpha*(E_nmda - vm)',
                                            'SYNAPTIC_EXC_EQS':
                                                 '''dge/dt = -ge/tau_e_alpha : siemens
                                                    dgealpha1/dt = (ge-gealpha1)/tau_e_alpha : siemens
                                                    gealpha = scaling_alpha*exp(1)*gealpha1 : siemens
                                                    dg_nmda/dt = -g_nmda/tau_decay_nmda : siemens
                                                    dg_nmda_alpha1/dt = (g_nmda - g_nmda_alpha1)/tau_rise_nmda : siemens
                                                    g_nmda_alpha = scaling_nmda * (tau_decay_nmda/tau_rise_nmda)**(tau_rise_nmda/(tau_decay_nmda-tau_rise_nmda)) * B * g_nmda_alpha1 : siemens
                                                    B = (1/(1+exp(-62*(vm/volt))*(1/3.57))) : 1
                                                 '''}

    SynapticExcInhModels['I_ALPHA_GABAB'] = {'I_SYNAPTIC_INH': '+ gialpha * (Ei - vm) + g_gabab_alpha*(E_gabab - vm)',
                                             'SYNAPTIC_INH_EQS':
                                                 '''dgi/dt = -gi/tau_i_alpha : siemens
                                                    dgialpha1/dt = (gi-gialpha1)/tau_i_alpha : siemens
                                                    gialpha = scaling_alpha*exp(1)*gialpha1 : siemens
                                                    dg_gabab/dt = -g_gabab/tau_decay_gabab : siemens
                                                    dg_gabab_alpha1/dt = (g_gabab - g_gabab_alpha1)/tau_rise_gabab : siemens
                                                    g_gabab_alpha = scaling_gabab * (tau_decay_gabab/tau_rise_gabab)**(tau_rise_gabab/(tau_decay_gabab-tau_rise_gabab)) * g_gabab_alpha1 : siemens
                                                    '''}

    SynapticExcInhModels['SIMPLE_E_NMDA'] = {'I_SYNAPTIC_EXC': '+ ge * (Ee - vm) + scaling_nmda*g_nmda*B*(E_nmda - vm)',
                                             'SYNAPTIC_EXC_EQS':
                                                 '''dge/dt = -ge/tau_e : siemens
                                                    dg_nmda/dt = -g_nmda/tau_decay_nmda : siemens
                                                    B = (1/(1+exp(-62*(vm/volt))*(1/3.57))) : 1
                                                 '''}
    SynapticExcInhModels['SIMPLE_I_GABAB'] = {'I_SYNAPTIC_INH': '+ gi * (Ei - vm) + scaling_gabab*g_gabab*(E_gabab - vm)',
                                              'SYNAPTIC_INH_EQS':
                                                  '''dgi/dt = -gi/tau_i : siemens
                                                     dg_gabab/dt = -g_gabab/tau_decay_gabab : siemens
                                                  '''}
    # </editor-fold>

    # <editor-fold desc="...Other excitation/inhibition models">

    # Single-exponential AMPA+NMDA and GABA-A+GABA-B
    SynapticExcInhModels['AMPA_NMDA'] = {'I_SYNAPTIC_EXC': '+ g_ampa*(E_ampa - vm) + scaling_nmda*g_nmda*B*(E_nmda - vm)',
                                         'SYNAPTIC_EXC_EQS':
                                             '''dg_ampa/dt = -g_ampa/tau_decay_ampa : siemens
                                                dg_nmda/dt = -g_nmda/tau_decay_nmda : siemens
                                                B = (1/(1+exp(-62*(vm/volt))*(1/3.57))) : 1
                                                '''}

    SynapticExcInhModels['GABAA_GABAB'] = {'I_SYNAPTIC_INH': '+ g_gabaa*(E_gabaa - vm) + scaling_gabab*g_gabab*(E_gabab - vm)',
                                           'SYNAPTIC_INH_EQS':
                                           '''dg_gabaa/dt = -g_gabaa/tau_decay_gabaa : siemens
                                              dg_gabab/dt = -g_gabab/tau_decay_gabab : siemens
                                              '''}

    # Bi-exponential  AMPA+NMDA and GABA-A+GABA-B
    # Conductances scaled by (tau_e_decay/tau_e_rise)**(tau_e_rise/(tau_e_decay-tau_e_rise)) to normalize
    SynapticExcInhModels['AMPA_NMDA_BIEXP'] = {'I_SYNAPTIC_EXC': '+ g_ampa_alpha*(E_ampa - vm) + g_nmda_alpha*(E_nmda - vm)',
                                                 'SYNAPTIC_EXC_EQS':
                                                     '''dg_ampa/dt = -g_ampa/tau_decay_ampa : siemens
                                                        dg_nmda/dt = -g_nmda/tau_decay_nmda : siemens
                                                        dg_ampa_alpha1/dt = (g_ampa - g_ampa_alpha1)/tau_rise_ampa : siemens
                                                        dg_nmda_alpha1/dt = (g_nmda - g_nmda_alpha1)/tau_rise_nmda : siemens
                                                        g_ampa_alpha = scaling_ampa * (tau_decay_ampa/tau_rise_ampa)**(tau_rise_ampa/(tau_decay_ampa-tau_rise_ampa)) * g_ampa_alpha1 : siemens
                                                        g_nmda_alpha = scaling_nmda * (tau_decay_nmda/tau_rise_nmda)**(tau_rise_nmda/(tau_decay_nmda-tau_rise_nmda)) * B * g_nmda_alpha1 : siemens
                                                        B = (1/(1+exp(-62*(vm/volt))*(1/3.57))) : 1
                                                        '''}

    SynapticExcInhModels['GABAA_GABAB_BIEXP'] = {'I_SYNAPTIC_INH': '+ g_gabaa_alpha*(E_gabaa - vm) + g_gabab_alpha*(E_gabab - vm)',
                                                   'SYNAPTIC_INH_EQS':
                                                       '''dg_gabaa/dt = -g_gabaa/tau_decay_gabaa : siemens
                                                          dg_gabab/dt = -g_gabab/tau_decay_gabab : siemens
                                                          dg_gabaa_alpha1/dt = (g_gabaa - g_gabaa_alpha1)/tau_rise_gabaa : siemens
                                                          dg_gabab_alpha1/dt = (g_gabab - g_gabab_alpha1)/tau_rise_gabab : siemens
                                                          g_gabaa_alpha = (tau_decay_gabaa/tau_rise_gabaa)**(tau_rise_gabaa/(tau_decay_gabaa-tau_rise_gabaa)) * g_gabaa_alpha1 : siemens
                                                          g_gabab_alpha = (tau_decay_gabab/tau_rise_gabab)**(tau_rise_gabab/(tau_decay_gabab-tau_rise_gabab)) * g_gabab_alpha1 : siemens
                                                          '''}
    #</editor-fold>

    # Variables that are compartment-specific; will have compartment name attached to them
    CompSpecificVariables = {'SIMPLE_E': ['ge'],
                             'SIMPLE_I': ['gi'],
                             'E_ALPHA': ['ge', 'gealpha', 'gealpha1'],
                             'I_ALPHA': ['gi', 'gialpha', 'gialpha1'],
                             'E_ALPHA_NONSCALED': ['ge', 'gealpha'],
                             'I_ALPHA_NONSCALED': ['gi', 'gialpha'],
                             'AMPA_NMDA': ['g_ampa', 'g_nmda', 'B'],
                             'GABAA_GABAB': ['g_gabaa', 'g_gabab'],
                             'AMPA_NMDA_BIEXP': ['g_ampa', 'g_nmda', 'g_ampa_alpha', 'g_nmda_alpha','g_ampa_alpha1', 'g_nmda_alpha1', 'B'],
                             'GABAA_GABAB_BIEXP': ['g_gabaa', 'g_gabab', 'g_gabaa_alpha', 'g_gabab_alpha', 'g_gabaa_alpha1', 'g_gabab_alpha1'],
                             'SIMPLE_E_NMDA': ['ge', 'g_nmda'],
                             'SIMPLE_I_GABAB': ['gi', 'g_gabab'],
                             'E_ALPHA_NMDA': ['ge', 'gealpha', 'gealpha1', 'g_nmda', 'g_nmda_alpha', 'g_nmda_alpha1', 'B'],
                             'I_ALPHA_GABAB': ['gi', 'gialpha', 'gialpha1', 'g_gabab', 'g_gabab_alpha', 'g_gabab_alpha1']}

    # Receptors that need to be incremented in response to presynaptic spikes
    Receptors = {'SIMPLE_E': ['ge'],
                 'SIMPLE_I': ['gi'],
                 'E_ALPHA': ['ge'],
                 'I_ALPHA': ['gi'],
                 'E_ALPHA_NONSCALED': ['ge'],
                 'I_ALPHA_NONSCALED': ['gi'],
                 'AMPA_NMDA': ['g_ampa', 'g_nmda'],
                 'GABAA_GABAB': ['g_gabaa', 'g_gabab'],
                 'AMPA_NMDA_BIEXP': ['g_ampa', 'g_nmda'],
                 'GABAA_GABAB_BIEXP': ['g_gabaa', 'g_gabab'],
                 'SIMPLE_E_NMDA': ['ge', 'g_nmda'],
                 'SIMPLE_I_GABAB': ['gi', 'g_gabab'],
                 'E_ALPHA_NMDA': ['ge', 'g_nmda'],
                 'I_ALPHA_GABAB': ['gi', 'g_gabab']
                 }

    BackgroundReceptors = {'SIMPLE_E': ['ge'],
                 'SIMPLE_I': ['gi'],
                 'E_ALPHA': ['ge'],
                 'I_ALPHA': ['gi'],
                 'E_ALPHA_NONSCALED': ['ge'],
                 'I_ALPHA_NONSCALED': ['gi'],
                 'AMPA_NMDA': ['g_ampa', 'g_nmda'],
                 'GABAA_GABAB': ['g_gabaa', 'g_gabab'],
                 'AMPA_NMDA_BIEXP': ['g_ampa', 'g_nmda'],
                 'GABAA_GABAB_BIEXP': ['g_gabaa', 'g_gabab'],
                 'SIMPLE_E_NMDA': ['ge'],
                 'SIMPLE_I_GABAB': ['gi'],
                 'E_ALPHA_NMDA': ['ge'],
                 'I_ALPHA_GABAB': ['gi']
                 }

    # </editor-fold>

    def __init__(self, receptor_model):
        self.receptor_model = receptor_model
        self.receptor_model_eqs = self.SynapticExcInhModels[receptor_model]

    def get_receptor_equations(self):
        return self.receptor_model_eqs

    def get_compartment_specific_variables(self):
        return self.CompSpecificVariables[self.receptor_model]

    def get_receptor_names(self):
        return self.Receptors[self.receptor_model]

if __name__ == '__main__':
    print(ReceptorModel('SIMPLE_E').get_receptor_equations())