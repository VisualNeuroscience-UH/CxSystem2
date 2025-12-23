# Built-in
import os
from pathlib import Path

# Third-party
import pandas as pd
import pytest

# Local
from cxsystem2.core.exceptions import ParameterNotFoundError
from cxsystem2.core.tools import change_anat_file_header_value


@pytest.fixture
def setup_and_teardown():
    # Create a dummy CSV file
    dummy_data = [
        ["Parameter1", "Parameter2", "Parameter3"],
        ["Value1", "Value2", "Value3"],
    ]

    dummy_file = Path("dummy.csv")
    save_file = Path("dummy_modified.csv")
    pd.DataFrame(dummy_data).to_csv(dummy_file, header=False, index=False)

    yield dummy_file, save_file

    # Remove the dummy CSV files
    if dummy_file.exists():
        os.remove(dummy_file)
    if save_file.exists():
        os.remove(save_file)


def test_change_single_parameter(setup_and_teardown):
    dummy_file, save_file = setup_and_teardown
    # Test changing a single parameter
    change_anat_file_header_value(dummy_file, save_file, {"Parameter1": "NewValue1"})
    df_modified = pd.read_csv(save_file, header=None)
    assert df_modified.iloc[1, 0] == "NewValue1"


def test_change_multiple_parameters(setup_and_teardown):
    dummy_file, save_file = setup_and_teardown
    # Test changing multiple parameters
    change_anat_file_header_value(
        dummy_file, save_file, {"Parameter1": "NewValue1", "Parameter2": "NewValue2"}
    )
    df_modified = pd.read_csv(save_file, header=None)
    assert df_modified.iloc[1, 0] == "NewValue1"
    assert df_modified.iloc[1, 1] == "NewValue2"


def test_parameter_not_found(setup_and_teardown):
    dummy_file, save_file = setup_and_teardown
    # Test when parameter is not found
    with pytest.raises(ParameterNotFoundError):
        change_anat_file_header_value(
            dummy_file, save_file, {"NonExistentParameter": "NewValue"}
        )


def test_multiple_instances_of_parameter(setup_and_teardown):
    dummy_file, save_file = setup_and_teardown
    # Test when there are multiple instances of the same parameter
    dummy_data_multiple = [
        ["Parameter1", "Parameter1", "Parameter3"],
        ["Value1", "Value2", "Value3"],
    ]
    pd.DataFrame(dummy_data_multiple).to_csv(dummy_file, header=False, index=False)
    with pytest.raises(ParameterNotFoundError):
        change_anat_file_header_value(dummy_file, save_file, {"Parameter1": "NewValue"})
