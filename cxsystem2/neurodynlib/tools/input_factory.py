
# This file is part of the exercise code repository accompanying
# the book: Neuronal Dynamics (see http://neuronaldynamics.epfl.ch)
# located at http://github.com/EPFL-LCN/neuronaldynamics-exercises.

# This free software: you can redistribute it and/or modify it under
# the terms of the GNU General Public License 2.0 as published by the
# Free Software Foundation. You should have received a copy of the
# GNU General Public License along with the repository. If not,
# see http://www.gnu.org/licenses/.

# Should you reuse and publish the code for your own purposes,
# please cite the book or point to the webpage http://neuronaldynamics.epfl.ch.

# Wulfram Gerstner, Werner M. Kistler, Richard Naud, and Liam Paninski.
# Neuronal Dynamics: From Single Neurons to Networks and Models of Cognition.
# Cambridge University Press, 2014.

# Built-in
import math

# Third-party
import brian2 as b2
import matplotlib.pyplot as plt
import numpy
import numpy as np


###############
# Input Currents
###############
def get_step_current(
    t_start: int,
    t_end: int,
    unit_time: b2.units.Quantity,
    amplitude: b2.units.Quantity,
    append_zero: bool = True,
) -> b2.TimedArray:
    """
    Create a step current. If ``t_start == t_end``, a single entry in the
    values array is set to ``amplitude``.

    Parameters
    ----------
    t_start : int
        Start of the step.
    t_end : int
        End of the step.
    unit_time : Quantity
        Unit of t_start and t_end, e.g. ``0.1*brian2.ms``.
    amplitude : Quantity
        Amplitude of the step, e.g. ``3.5*brian2.uamp``.
    append_zero : bool, optional
        If True, 0 Amp is appended at ``t_end + 1``. Without that trailing 0,
        Brian reads out the last value (= amplitude) for all indices > t_end.

    Returns
    -------
    b2.TimedArray
    """

    assert isinstance(t_start, int), "t_start_ms must be of type int"
    assert isinstance(t_end, int), "t_end must be of type int"
    assert b2.units.fundamentalunits.have_same_dimensions(amplitude, b2.amp), \
        "amplitude must have the dimension of current e.g. brian2.uamp"
    tmp_size = 1 + t_end  # +1 for t=0
    if append_zero:
        tmp_size += 1
    tmp = np.zeros((tmp_size, 1)) * b2.amp
    tmp[t_start: t_end + 1, 0] = amplitude
    curr = b2.TimedArray(tmp, dt=1. * unit_time)
    return curr


def get_ramp_current(
    t_start: int,
    t_end: int,
    unit_time: b2.units.Quantity,
    amplitude_start: b2.units.Quantity,
    amplitude_end: b2.units.Quantity,
    append_zero: bool = True,
) -> b2.TimedArray:
    """
    Create a ramp current. If ``t_start == t_end``, all entries are 0.

    Parameters
    ----------
    t_start : int
        Start of the ramp.
    t_end : int
        End of the ramp.
    unit_time : Quantity
        Unit of t_start and t_end, e.g. ``0.1*ms``.
    amplitude_start : Quantity
        Amplitude of the ramp at t_start, e.g. ``3.5*uamp``.
    amplitude_end : Quantity
        Amplitude of the ramp at t_end, e.g. ``4.5*uamp``.
    append_zero : bool, optional
        If True, 0 Amp is appended at ``t_end + 1``. Without that trailing 0,
        Brian reads out the last value (= amplitude_end) for all indices > t_end.

    Returns
    -------
    b2.TimedArray
    """

    assert isinstance(t_start, int), "t_start_ms must be of type int"
    assert isinstance(t_end, int), "t_end must be of type int"
    assert b2.units.fundamentalunits.have_same_dimensions(amplitude_start, b2.amp), \
        "amplitude must have the dimension of current e.g. brian2.uamp"
    assert b2.units.fundamentalunits.have_same_dimensions(amplitude_end, b2.amp), \
        "amplitude must have the dimension of current e.g. brian2.uamp"
    tmp_size = 1 + t_end  # +1 for t=0
    if append_zero:
        tmp_size += 1
    tmp = np.zeros((tmp_size, 1)) * b2.amp
    if t_end > t_start:  # if deltaT is zero, we return a zero current
        slope = (amplitude_end - amplitude_start) / float((t_end - t_start))
        ramp = [amplitude_start + t * slope for t in range(0, (t_end - t_start) + 1)]
        tmp[t_start: t_end + 1, 0] = ramp

    curr = b2.TimedArray(tmp, dt=1. * unit_time)
    return curr


def get_sinusoidal_current(
    t_start: int,
    t_end: int,
    unit_time: b2.units.Quantity,
    amplitude: b2.units.Quantity,
    frequency: b2.units.Quantity,
    direct_current: b2.units.Quantity,
    phase_offset: float = 0.0,
    append_zero: bool = True,
) -> b2.TimedArray:
    """
    Create a sinusoidal current. If ``t_start == t_end``, all entries are 0.

    Parameters
    ----------
    t_start : int
        Start of the sine wave.
    t_end : int
        End of the sine wave.
    unit_time : Quantity
        Unit of t_start and t_end, e.g. ``0.1*ms``.
    amplitude : Quantity
        Maximum amplitude of the sine, e.g. ``3.0*uamp``.
    frequency : Quantity
        Frequency of the sine, e.g. ``0.5*kHz``.
    direct_current : Quantity
        DC component (offset) of the current, e.g. ``1.5*uamp``.
    phase_offset : float, optional
        Phase at t_start. Default is 0.
    append_zero : bool, optional
        If True, 0 Amp is appended at ``t_end + 1``. Without that trailing 0,
        Brian reads out the last value for all indices > t_end.

    Returns
    -------
    b2.TimedArray
    """

    assert isinstance(t_start, int), "t_start_ms must be of type int"
    assert isinstance(t_end, int), "t_end must be of type int"
    assert b2.units.fundamentalunits.have_same_dimensions(amplitude, b2.amp), \
        "amplitude must have the dimension of current. e.g. brian2.uamp"
    assert b2.units.fundamentalunits.have_same_dimensions(direct_current, b2.amp), \
        "direct_current must have the dimension of current. e.g. brian2.uamp"
    assert b2.units.fundamentalunits.have_same_dimensions(frequency, b2.Hz), \
        "frequency must have the dimension of 1/Time. e.g. brian2.Hz"

    tmp_size = 1 + t_end  # +1 for t=0
    if append_zero:
        tmp_size += 1
    tmp = np.zeros((tmp_size, 1)) * b2.amp
    if t_end > t_start:  # if deltaT is zero, we return a zero current
        phi = range(0, (t_end - t_start) + 1)
        phi = phi * unit_time * frequency
        phi = phi * 2. * math.pi + phase_offset
        c = numpy.sin(phi)
        c = (direct_current + c * amplitude)
        tmp[t_start: t_end + 1, 0] = c
    curr = b2.TimedArray(tmp, dt=1. * unit_time)
    return curr


def get_zero_current() -> b2.TimedArray:
    """
    Returns a TimedArray with one entry: 0 Amp

    Returns:
        TimedArray
    """
    amp = 0. * b2.amp
    return get_step_current(0, 0, b2.ms, amp, append_zero=False)


def get_spikes_current(
    t_spikes: list[int],
    unit_time: b2.units.Quantity,
    amplitude: b2.units.Quantity,
    append_zero: bool = True,
) -> b2.TimedArray:
    """
    Create a 2D TimedArray with one column per value in ``t_spikes``.

    All values in each column are 0 except one: the spike time given in
    ``t_spikes`` is set to ``amplitude``. Provided to easily insert pulse
    currents into a cable; for other spike input, see Brian2's SpikeGenerator.

    Parameters
    ----------
    t_spikes : list of int
        Spike times.
    unit_time : Quantity
        Unit of t_spikes, e.g. ``1*ms``.
    amplitude : Quantity
        Amplitude of the spikes (all spikes have the same amplitude).
    append_zero : bool, optional
        If True, 0 Amp is appended at ``t_end + 1``. Without that trailing 0,
        Brian reads out the last value for all indices > t_end.

    Returns
    -------
    b2.TimedArray
    """
    assert isinstance(t_spikes, list), "t_spikes must be of type list"
    assert b2.units.fundamentalunits.have_same_dimensions(amplitude, b2.amp), \
        "amplitude must have the dimension of current e.g. brian2.uamp"
    nr_spikes = len(t_spikes)
    t_max = max(t_spikes)
    tmp_size = 1 + t_max  # +1 for t=0
    if append_zero:
        tmp_size += 1
    tmp = np.zeros((tmp_size, nr_spikes)) * b2.amp
    for i in range(nr_spikes):
        tmp[t_spikes[i], i] = amplitude
    curr = b2.TimedArray(tmp, dt=1. * unit_time)
    return curr


def plot_step_current_example() -> None:
    """
    Example for get_step_current.
    """
    current = get_step_current(10, 30, b2.ms, amplitude=5. * b2.uA, append_zero=False)
    data = current.values[:, 0] / b2.uamp
    plt.plot(data, "ro", markersize=10, fillstyle="full")
    plt.title("get_step_current(10, 30, b2.ms, amplitude=5.*b2.uA, append_zero=False")
    plt.xlabel("index")
    plt.ylabel("value")


def plot_ramp_current_example() -> None:
    """
    Example for get_ramp_current
    """
    current = get_ramp_current(10, 25, b2.ms, 20 * b2.uamp, 50 * b2.uamp, append_zero=True)
    data = current.values[:, 0] / b2.uamp
    plt.plot(data, lw=3)
    plt.title("get_ramp_current(10, 25, b2.ms, 20*b2.uamp, 50*b2.uamp, append_zero=True)")
    plt.xlabel("index")
    plt.ylabel("value")


def plot_sinusoidal_current_example() -> None:
    """
    Example for get_sinusoidal_current
    """
    current = get_sinusoidal_current(
        100, 1100, b2.us,
        amplitude=2 * b2.uamp, frequency=1.5 * b2.kHz, direct_current=1.5 * b2.uamp, phase_offset=math.pi / 6,
        append_zero=False)
    data = current.values[:, 0] / b2.uamp
    plt.plot(data, lw=3)
    plt.title("get_sinusoidal_current(100, 1100, b2.us, amplitude=2*b2.uamp, frequency=1.5*b2.kHz, \n"
              "direct_current=1.5*b2.uamp, phase_offset=pi/6, append_zero=False)")
    plt.xlabel("index")
    plt.ylabel("value")


def getting_started() -> None:
    # plot examples
    plot_step_current_example()
    plt.show()
    plot_ramp_current_example()
    plt.show()
    plot_sinusoidal_current_example()
    plt.show()


if __name__ == "__main__":
    getting_started()
