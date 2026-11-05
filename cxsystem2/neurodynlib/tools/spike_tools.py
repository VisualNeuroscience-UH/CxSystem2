"""
This the spike_tools submodule provides functions to analyse the
Brian2 SpikeMonitors and Brian2 StateMonitors. The code provided here is
not optimized for performance and there is no guarantee for correctness.

Relevant book chapters:
    - http://neuronaldynamics.epfl.ch/online/Ch19.S2.html#SS1.p6
"""

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
import numpy as np


def get_spike_time(
    voltage_monitor: b2.StateMonitor, spike_threshold: b2.units.Quantity
) -> np.ndarray:
    """
    Detect spike times in the voltage.

    A spike time is defined as the value in ``voltage_monitor.t`` for which
    ``voltage_monitor.v[idx]`` is above threshold AND ``voltage_monitor.v[idx-1]``
    is below threshold (crossing from below). Only the first column of the
    monitor is used; matrix-like monitors are not supported.

    Parameters
    ----------
    voltage_monitor : b2.StateMonitor
        A state monitor with at least the fields "v" and "t".
    spike_threshold : Quantity
        The spike threshold voltage, e.g. ``-50*b2.mV``.

    Returns
    -------
    np.ndarray
        The spike times.
    """
    assert isinstance(
        voltage_monitor, b2.StateMonitor
    ), "voltage_monitor is not of type StateMonitor"
    assert b2.units.fundamentalunits.have_same_dimensions(
        spike_threshold, b2.volt
    ), "spike_threshold must be a voltage. e.g. brian2.mV"

    v_above_th = np.asarray(voltage_monitor.v[0] > spike_threshold, dtype=int)
    diffs = np.diff(v_above_th)
    boolean_mask = diffs > 0  # cross from below.
    spike_times = (voltage_monitor.t[1:])[boolean_mask]
    return spike_times


def get_spike_stats(
    voltage_monitor: b2.StateMonitor, spike_threshold: b2.units.Quantity
) -> tuple[int, np.ndarray, np.ndarray, b2.units.Quantity, b2.units.Quantity, b2.units.Quantity]:
    """
    Detect spike times and compute ISI, mean ISI and firing frequency.

    Spike times are defined as in :func:`get_spike_time`. Mean ISI and firing
    frequency are set to NaN if fewer than two spikes are detected. Only the
    first column of the monitor is used.

    Parameters
    ----------
    voltage_monitor : b2.StateMonitor
        A state monitor with at least the fields "v" and "t".
    spike_threshold : Quantity
        The spike threshold voltage, e.g. ``-50*b2.mV``.

    Returns
    -------
    tuple
        (nr_of_spikes, spike_times, isi, mean_isi, spike_rate, var_isi).
    """
    spike_times = get_spike_time(voltage_monitor, spike_threshold)
    isi = np.diff(spike_times)
    nr_of_spikes = len(spike_times)
    # init with nan, compute values only if 2 or more spikes are detected
    mean_isi = np.nan * b2.ms
    var_isi = np.nan * (b2.ms**2)
    spike_rate = np.nan * b2.Hz
    if nr_of_spikes >= 2:
        mean_isi = np.mean(isi)
        var_isi = np.var(isi)
        spike_rate = 1.0 / mean_isi
    return nr_of_spikes, spike_times, isi, mean_isi, spike_rate, var_isi


def pretty_print_spike_train_stats(
    voltage_monitor: b2.StateMonitor, spike_threshold: b2.units.Quantity
) -> tuple[np.ndarray, np.ndarray, b2.units.Quantity, b2.units.Quantity, b2.units.Quantity]:
    """
    Compute and print the spike-train stats (same values as :func:`get_spike_stats`).

    Parameters
    ----------
    voltage_monitor : b2.StateMonitor
        A state monitor with at least the fields "v" and "t".
    spike_threshold : Quantity
        The spike threshold voltage.

    Returns
    -------
    tuple
        (spike_times, ISI, mean_isi, spike_freq, var_isi).
    """
    nr_of_spikes, spike_times, ISI, mean_isi, spike_freq, var_isi = get_spike_stats(
        voltage_monitor, spike_threshold
    )
    print(f"nr of spikes: {nr_of_spikes}")
    print(f"mean ISI: {mean_isi}")
    print(f"ISI variance: {var_isi}")
    print(f"spike freq: {spike_freq}")
    if nr_of_spikes > 20:
        print("spike times: too many values")
        print("ISI: too many values")
    else:
        print(f"spike times: {spike_times}")
        print(f"ISI: {ISI}")
    return spike_times, ISI, mean_isi, spike_freq, var_isi


class PopulationSpikeStats:
    """
    Not implemented! Wraps a few spike-train related properties.
    """

    def __init__(
        self,
        nr_neurons: int,
        nr_spikes: int,
        all_ISI: np.ndarray,
        filtered_spike_trains: dict,
    ) -> None:
        """
        Wrap a few spike-train related properties.

        Parameters
        ----------
        nr_neurons : int
            Number of neurons in the original population.
        nr_spikes : int
            Number of spikes.
        all_ISI : ndarray
            List of ISI values (can be used to plot a histogram).
        filtered_spike_trains : dict
            Time-window filtered copy of the original ``spike_monitor.spike_trains()``.
        """
        self._nr_neurons = nr_neurons
        self._nr_spikes = nr_spikes
        self._all_ISI = all_ISI
        self._filtered_spike_trains = filtered_spike_trains

    @property
    def nr_neurons(self) -> int:
        """
        Number of neurons in the original population
        """
        return self._nr_neurons

    @property
    def nr_spikes(self) -> int:
        """
        Nr of spikes
        """
        return self._nr_spikes

    @property
    def filtered_spike_trains(self) -> dict:
        """
        a time-window filtered copy of the original spike_monitor.all_spike_trains
        """
        return self._filtered_spike_trains

    @property
    def mean_isi(self) -> b2.units.Quantity:
        """
        Mean Inter Spike Interval
        """
        mean_isi = np.mean(self._all_ISI) * b2.second
        return mean_isi

    @property
    def std_isi(self) -> b2.units.Quantity:
        """
        Standard deviation of the ISI
        """
        std_isi = np.std(self._all_ISI) * b2.second
        return std_isi

    @property
    def all_ISI(self) -> np.ndarray:
        """
        all ISIs in no specific order
        """
        return self._all_ISI

    @property
    def CV(self) -> float:
        """
        Coefficient of Variation
        """
        cv = np.nan  # init with nan
        if self.mean_isi > 0.0:
            cv = self.std_isi / self.mean_isi
        return cv


def filter_spike_trains(
    spike_trains: dict,
    window_t_min: b2.units.Quantity = 0.0 * b2.ms,
    window_t_max: b2.units.Quantity | None = None,
    idx_subset: list | None = None,
) -> dict:
    """
    Create a new dict neuron_idx -> spike_times within a time window.

    Parameters
    ----------
    spike_trains : dict
        Dictionary of spike trains, typically from ``spike_monitor.spike_trains()``.
    window_t_min : Quantity, optional
        Lower bound of the time window: ``t >= window_t_min``. Default is 0 ms.
    window_t_max : Quantity, optional
        Upper bound of the time window: ``t < window_t_max``. Default is None
        (no upper bound).
    idx_subset : list, optional
        Neuron indices (dict keys) to include. If None, all neurons are included.

    Returns
    -------
    dict
        A filtered copy of ``spike_trains`` with all times in
        [window_t_min, window_t_max).
    """
    assert isinstance(spike_trains, dict), "spike_trains is not of type dict"

    if idx_subset is None:
        idx_subset = spike_trains.keys()

    spike_trains_subset = dict()
    for k in idx_subset:
        spike_trains_subset[k] = spike_trains[k].copy()

    # nr_neurons = len(idx_subset)
    filtered_spike_trains = dict()
    if (window_t_min == 0.0 * b2.ms) & (window_t_max is None):
        filtered_spike_trains = spike_trains_subset
    elif window_t_max is None:
        for i in idx_subset:
            idx = spike_trains_subset[i] >= window_t_min
            filtered_spike_trains[i] = spike_trains_subset[i][idx]
    else:
        for i in idx_subset:
            idx = (spike_trains_subset[i] >= window_t_min) & (
                spike_trains_subset[i] < window_t_max
            )
            filtered_spike_trains[i] = spike_trains_subset[i][idx]

    return filtered_spike_trains


def get_spike_train_stats(
    spike_monitor: b2.SpikeMonitor,
    window_t_min: b2.units.Quantity = 0.0 * b2.ms,
    window_t_max: b2.units.Quantity | None = None,
) -> PopulationSpikeStats:
    """
    Analyze a spike monitor and return a PopulationSpikeStats instance.

    Parameters
    ----------
    spike_monitor : b2.SpikeMonitor
        Brian2 spike monitor.
    window_t_min : Quantity, optional
        Lower bound of the time window: ``t >= window_t_min``. Default is 0 ms.
    window_t_max : Quantity, optional
        Upper bound of the time window: ``t < window_t_max``. Default is None
        (no upper bound).

    Returns
    -------
    PopulationSpikeStats
        The population spike statistics.
    """
    assert isinstance(
        spike_monitor, b2.SpikeMonitor
    ), "spike_monitor is not of type SpikeMonitor"
    filtered_spike_trains = filter_spike_trains(
        spike_monitor.spike_trains(), window_t_min, window_t_max
    )
    nr_neurons = len(filtered_spike_trains)
    all_ISI = []
    for i in range(nr_neurons):
        spike_times = filtered_spike_trains[i] / b2.ms
        nr_spikes = len(spike_times)
        if nr_spikes >= 2:
            isi = np.diff(spike_times)
            # maxISI = max(isi)
            # if maxISI > 400:
            #     print(maxISI)
            all_ISI = np.hstack([all_ISI, isi])
    all_ISI = all_ISI * b2.ms
    stats = PopulationSpikeStats(
        nr_neurons, spike_monitor.num_spikes, all_ISI, filtered_spike_trains
    )
    return stats


def _spike_train_2_binary_vector(
    spike_train: np.ndarray, vector_length: int, discretization_dt: b2.units.Quantity
) -> np.ndarray:
    """
    Convert the spike-time stamps into a binary vector of the given length.

    If more than one spike falls into the same time bin, only one is counted;
    surplus spikes are ignored.

    Parameters
    ----------
    spike_train : ndarray
        The spike times.
    vector_length : int
        Length of the output vector.
    discretization_dt : Quantity
        Width of one time bin.

    Returns
    -------
    np.ndarray
        The discretized, binary spike train.
    """
    vec = np.zeros(vector_length, int)
    idx = spike_train / discretization_dt
    idx = np.floor(idx).astype(int)
    vec[idx] = 1
    return vec


def _get_spike_train_power_spectrum(
    spike_train: np.ndarray, delta_t: b2.units.Quantity, subtract_mean: bool = False
) -> tuple[np.ndarray, np.ndarray]:
    st = spike_train / b2.ms
    if subtract_mean:
        data = st - np.mean(st)
    else:
        data = st
    N_signal = data.size
    ps = np.abs(np.fft.fft(data)) ** 2
    # normalize
    ps = ps * delta_t / N_signal  # TODO: verify: subtract 1 (N_signal-1)?
    freqs = np.fft.fftfreq(N_signal, delta_t)
    ps = ps[: (N_signal / 2)]
    freqs = freqs[: (N_signal / 2)]
    return ps, freqs


def get_averaged_single_neuron_power_spectrum(
    spike_monitor: b2.SpikeMonitor,
    sampling_frequency: b2.units.Quantity,
    window_t_min: b2.units.Quantity,
    window_t_max: b2.units.Quantity,
    nr_neurons_average: int = 100,
    subtract_mean: bool = False,
) -> tuple[np.ndarray, np.ndarray, dict, b2.units.Quantity, dict]:
    """
    Average the power spectrum of spike trains over a time window.

    The power spectrum of each single neuron's spike train is computed, then
    averaged across neurons. The number of neurons averaged over is limited to
    ``nr_neurons_average`` (default 100) to bound computation time.

    Parameters
    ----------
    spike_monitor : b2.SpikeMonitor
        Brian2 spike monitor.
    sampling_frequency : Quantity
        Sampling frequency used to discretize the spike trains.
    window_t_min : Quantity
        Lower bound of the time window: ``t >= window_t_min``. Spikes before it
        are ignored (use it to exclude an initial transient).
    window_t_max : Quantity
        Upper bound of the time window: ``t < window_t_max``.
    nr_neurons_average : int, optional
        Number of neurons over which the average is taken. Default is 100.
    subtract_mean : bool, optional
        If True, subtract the mean of the signal before the FFT. Default is False.

    Returns
    -------
    tuple
        (freq, mean_ps, all_ps_dict, mean_firing_rate, mean_firing_freqs_per_neuron).
    """

    assert isinstance(
        spike_monitor, b2.SpikeMonitor
    ), "spike_monitor is not of type SpikeMonitor"

    spiketrains = spike_monitor.spike_trains()
    nr_neurons = len(spiketrains)

    sample_neurons = []
    nr_samples = 0
    if nr_neurons <= nr_neurons_average:
        sample_neurons = range(nr_neurons)
        nr_samples = nr_neurons
    else:
        idxs = np.arange(nr_neurons)
        np.random.shuffle(idxs)
        sample_neurons = idxs[:(nr_neurons_average)]
        nr_samples = nr_neurons_average

    sptrs = filter_spike_trains(
        spike_monitor.spike_trains(), window_t_min, window_t_max, sample_neurons
    )
    time_window_size = window_t_max - window_t_min
    discretization_dt = 1.0 / sampling_frequency
    if window_t_max is None:
        window_t_max = max(spike_monitor.t)
    vector_length = 1 + int(
        math.ceil(time_window_size / discretization_dt)
    )  # +1: space for rounding issues
    freq = 0
    spike_count = 0
    all_ps = np.zeros([nr_samples, vector_length / 2], float)
    all_ps_dict = dict()
    mean_firing_freqs_per_neuron = dict()
    for i in range(nr_samples):
        idx = sample_neurons[i]
        vec = _spike_train_2_binary_vector(
            sptrs[idx] - window_t_min,
            vector_length,
            discretization_dt=discretization_dt,
        )
        ps, freq = _get_spike_train_power_spectrum(
            vec, discretization_dt, subtract_mean
        )
        all_ps[i, :] = ps
        all_ps_dict[idx] = ps
        nr_spikes = len(sptrs[idx])
        nu_avg = nr_spikes / time_window_size
        # print(nu_avg)
        mean_firing_freqs_per_neuron[idx] = nu_avg
        spike_count += nr_spikes  # count in the subsample which is filtered to [window_t_min, window_t_max]

    mean_ps = np.mean(all_ps, 0)
    mean_firing_rate = spike_count / nr_samples / time_window_size
    print(f"mean_firing_rate:{mean_firing_rate}")
    return freq, mean_ps, all_ps_dict, mean_firing_rate, mean_firing_freqs_per_neuron


def get_population_activity_power_spectrum(
    rate_monitor: b2.PopulationRateMonitor,
    delta_f: b2.units.Quantity,
    k_repetitions: int,
    T_init: b2.units.Quantity = 100 * b2.ms,
    subtract_mean_activity: bool = False,
) -> tuple[np.ndarray, np.ndarray, b2.units.Quantity]:
    """
    Compute the power spectrum of the population activity A(t) (``rate_monitor.rate``).

    Parameters
    ----------
    rate_monitor : b2.PopulationRateMonitor
        Brian2 rate monitor; its ``rate`` is the analyzed signal. The temporal
        resolution is read from ``rate_monitor.clock.dt``.
    delta_f : Quantity
        The desired frequency resolution.
    k_repetitions : int
        The data is split into ``k_repetitions`` segments which are FFT'd
        independently and then averaged in the frequency domain.
    T_init : Quantity, optional
        Rates in [0, T_init] are removed before the Fourier transform (use to
        ignore the initial transient). Default is 100 ms.
    subtract_mean_activity : bool, optional
        If True, subtract the mean of the signal. Default is False.

    Returns
    -------
    tuple
        (freqs, ps, average_population_rate).
    """
    data = rate_monitor.rate / b2.Hz
    delta_t = rate_monitor.clock.dt
    f_max = 1.0 / (2.0 * delta_t)
    N_signal = int(2 * f_max / delta_f)
    # T_signal = N_signal * delta_t
    N_init = int(T_init / delta_t)
    N_required = k_repetitions * N_signal + N_init
    N_data = len(data)

    # print("N_data={}, N_required={}".format(N_data,N_required))
    if N_data < N_required:
        err_msg = (
            f"Inconsistent parameters. k_repetitions require {N_required} samples."
            f" rate_monitor.rate contains {N_data} samples."
        )
        raise ValueError(err_msg)
    if N_data > N_required:
        # print("drop samples")
        data = data[:N_required]
    # print("length after dropping end:{}".format(len(data)))
    data = data[N_init:]
    # print("length after dropping init:{}".format(len(data)))
    average_population_rate = np.mean(data)
    if subtract_mean_activity:
        data = data - average_population_rate
    average_population_rate *= b2.Hz
    data = data.reshape(
        k_repetitions, N_signal
    )  # reshape into one row per repetition (k)
    k_ps = np.abs(np.fft.fft(data)) ** 2
    ps = np.mean(k_ps, 0)
    # normalize
    ps = ps * delta_t / N_signal  # TODO: verify: subtract 1 (N_signal-1)?
    freqs = np.fft.fftfreq(N_signal, delta_t)
    ps = ps[: (N_signal / 2)]
    freqs = freqs[: (N_signal / 2)]
    return freqs, ps, average_population_rate
