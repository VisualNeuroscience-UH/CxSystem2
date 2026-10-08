# Third-party
import brian2 as b2

# Local
from cxsystem2.neurodynlib.neuron_models import PointNeuron

# ruff: noqa: RUF012
# These test are generated with Mistral AI.  

class TestablePointNeuron(PointNeuron):
    """Concrete subclass for testing PointNeuron with custom __init__ parameters."""

    neuron_model_defns = {"I_NEURON_MODEL": "gL*(EL-vm)"}
    default_neuron_parameters = {
        "EL": -70 * b2.mV,
        "V_res": -65 * b2.mV,
        "VT": -50 * b2.mV,
        "gL": 100 * b2.nS,
        "C": 800 * b2.pF,
        "refractory_period": 2.0 * b2.ms,
    }


class TestPointNeuronInit:
    """Tests for PointNeuron.__init__ method."""

    def test_default_compartment_is_soma(self):
        """Test that default compartment is 'soma'."""
        neuron = TestablePointNeuron()
        assert neuron.compartment == "soma"
        assert neuron.compartment_type == "soma"

    def test_custom_compartment_is_dendrite(self):
        """Test that non-soma compartments are classified as dendrites."""
        neuron = TestablePointNeuron(compartment="a2")
        assert neuron.compartment == "a2"
        assert neuron.compartment_type == "dendrite"

    def test_is_pyramidal_false(self):
        """Test initialization with is_pyramidal=False."""
        neuron = TestablePointNeuron(is_pyramidal=False)
        assert neuron.is_pyramidal is False

    def test_is_pyramidal_true_soma(self):
        """Test initialization with is_pyramidal=True and soma compartment."""
        neuron = TestablePointNeuron(is_pyramidal=True, compartment="soma")
        assert neuron.is_pyramidal is True
        assert neuron.compartment_type == "soma"

    def test_default_threshold_condition(self):
        """Test that default threshold condition is set."""
        neuron = TestablePointNeuron()
        assert neuron.threshold_condition == "vm > VT"

    def test_default_reset_statements(self):
        """Test that default reset statements are set."""
        neuron = TestablePointNeuron()
        assert neuron.reset_statements == "vm = V_res"

    def test_default_integration_method(self):
        """Test that default integration method is 'euler'."""
        neuron = TestablePointNeuron()
        assert neuron.integration_method == "euler"

    def test_default_initial_values(self):
        """Test that default initial values are set."""
        neuron = TestablePointNeuron()
        assert neuron.initial_values == {"vm": "EL"}

    def test_default_states_to_monitor(self):
        """Test that default states to monitor are set."""
        neuron = TestablePointNeuron()
        assert neuron.states_to_monitor == ["vm"]


class TestPointNeuronMembraneEquation:
    """Tests for PointNeuron.get_membrane_equation method."""

    def test_returns_string_by_default(self):
        """Test that method returns a string by default."""
        neuron = TestablePointNeuron()
        result = neuron.get_membrane_equation()
        assert isinstance(result, str)

    def test_returns_equations_object(self):
        """Test that method returns b2.Equations when return_string=False."""
        neuron = TestablePointNeuron()
        result = neuron.get_membrane_equation(return_string=False)
        assert isinstance(result, b2.Equations)

    def test_contains_vm_derivative(self):
        """Test that membrane equation contains dvm/dt."""
        neuron = TestablePointNeuron()
        result = neuron.get_membrane_equation()
        assert "dvm/dt" in result

    def test_contains_neuron_model_current(self):
        """Test that membrane equation contains the neuron model current."""
        neuron = TestablePointNeuron()
        result = neuron.get_membrane_equation()
        assert "gL*(EL-vm)" in result

    def test_substitute_ad_hoc_overrides(self):
        """Test that ad-hoc substitutions override model definitions."""
        neuron = TestablePointNeuron()
        ad_hoc = {"I_NEURON_MODEL": "custom_current"}
        result = neuron.get_membrane_equation(substitute_ad_hoc=ad_hoc)
        assert "custom_current" in result


class TestPointNeuronParameterMethods:
    """Tests for parameter-related methods."""

    def test_get_parameter_names_returns_keys(self):
        """Test that get_parameter_names returns dictionary keys."""
        neuron = TestablePointNeuron()
        names = neuron.get_parameter_names()
        assert isinstance(names, type(neuron.default_neuron_parameters.keys()))

    def test_get_neuron_parameters_returns_dict(self):
        """Test that get_neuron_parameters returns a dict."""
        neuron = TestablePointNeuron()
        params = neuron.get_neuron_parameters()
        assert isinstance(params, dict)

    def test_set_neuron_parameters_updates(self):
        """Test that set_neuron_parameters updates the parameters dict."""
        neuron = TestablePointNeuron()
        neuron.set_neuron_parameters(EL=-60 * b2.mV)
        assert neuron.neuron_parameters["EL"] == -60 * b2.mV


class TestPointNeuronGetterMethods:
    """Tests for getter methods."""

    def test_get_reset_statements(self):
        """Test get_reset_statements returns a string."""
        neuron = TestablePointNeuron()
        result = neuron.get_reset_statements()
        assert isinstance(result, str)

    def test_get_threshold_condition(self):
        """Test get_threshold_condition returns a string."""
        neuron = TestablePointNeuron()
        result = neuron.get_threshold_condition()
        assert isinstance(result, str)

    def test_get_states_to_monitor(self):
        """Test get_states_to_monitor returns a list."""
        neuron = TestablePointNeuron()
        result = neuron.get_states_to_monitor()
        assert isinstance(result, list)


class TestPointNeuronModelDefinitionMethods:
    """Tests for model definition methods."""

    def test_set_model_definition(self):
        """Test set_model_definition sets a placeholder value."""
        neuron = TestablePointNeuron()
        neuron.set_model_definition("I_NEURON_MODEL", "gL*(EL-vm)")
        assert neuron.full_model_defns["I_NEURON_MODEL"] == "gL*(EL-vm)"

    def test_add_model_definition_new_key(self):
        """Test add_model_definition adds to an empty placeholder."""
        neuron = TestablePointNeuron()
        neuron.add_model_definition("CUSTOM_PLACEHOLDER", "+ test")
        assert neuron.full_model_defns["CUSTOM_PLACEHOLDER"] == "+ test"

