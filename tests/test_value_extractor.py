import pandas as pd
import pytest
from brian2.units import *  # noqa: F403

from cxsystem2.core.exceptions import ParameterNotFoundError
from cxsystem2.core.tools import value_extractor


# Sample dataframe for testing
def create_test_df():
    data = {
        "Variable": ["k", "J", "k_I", "J_I", "_weights", "some_other_variable"],
        "Key": [
            "w_TC_E-I_connections",
            "w_TC_E-E_connections",
            "w_All_other_E-E_connections",
            "w_All_other_E-I_connections",
            None,
            None,
        ],
        "Value": ["0.7*nS", "0.4*nS", "1.8", "0.4*nS", "J_I", "2.0"],
        "Comment": [
            "E to E weight",
            "E to I weight",
            "IE/EE -ratio",
            "IE/EE -ratio",
            None,
            None,
        ],
    }
    df = pd.DataFrame(data)
    # Add a test case where the value is a reference to another key
    df.loc[len(df)] = [None, "ref_value", "w_TC_E-I_connections", None]
    # Add a test case where the value is a multiplication
    df.loc[len(df)] = [None, "mult_value", "k_I*J_I", None]
    # Add a test case where the value is a dictionary notation
    df.loc[len(df)] = [None, "dict_value", "_weights['w_TC_E-I_connections']", None]
    # Add a test case where the value is a direct numerical value
    df.loc[len(df)] = [None, "direct_value", "0.1", None]
    # Add a test case where the value is a division
    df.loc[len(df)] = [None, "div_value", "k_I/J_I", None]
    return df


# Test top-level variable name
def test_top_level_variable():
    df = create_test_df()
    assert value_extractor(df, "k") == 0.7 * nS  # noqa: F405


# Test second-level key name
def test_second_level_key():
    df = create_test_df()
    assert value_extractor(df, "w_TC_E-I_connections") == 0.7 * nS  # noqa: F405


# Test multiplication of two terms
def test_multiplication():
    df = create_test_df()
    result = value_extractor(df, "mult_value")
    assert result == eval("(1.8) * (0.4*nS)")


# Test dictionary notation for second-level keys
def test_dictionary_notation():
    df = create_test_df()
    assert value_extractor(df, "dict_value") == 0.7 * nS  # noqa: F405  # noqa: F405


# Test direct numerical or string value
def test_direct_value():
    df = create_test_df()
    assert value_extractor(df, "direct_value") == 0.1


# Test reference to another top-level variable
def test_reference_top_level():
    df = create_test_df()
    assert value_extractor(df, "k") == 0.7 * nS  # noqa: F405


# Test reference to another second-level key
def test_reference_second_level():
    df = create_test_df()
    assert value_extractor(df, "ref_value") == 0.7 * nS  # noqa: F405


# Test multiplication or division of two terms in the value
def test_multiplication_in_value():
    df = create_test_df()
    result = value_extractor(df, "mult_value")
    assert result == eval("(1.8) * (0.4*nS)")


# Test division of two terms
def test_division():
    df = create_test_df()
    result = value_extractor(df, "div_value")
    assert result == eval("(1.8) / (0.4*nS)")


# Test that ParameterNotFoundError is raised for non-existent keys
def test_parameter_not_found():
    df = create_test_df()
    with pytest.raises(ParameterNotFoundError):
        value_extractor(df, "non_existent_key")
