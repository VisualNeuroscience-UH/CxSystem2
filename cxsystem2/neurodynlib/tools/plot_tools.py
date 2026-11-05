
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



# Third-party
import brian2 as b2
import matplotlib.pyplot as plt
import numpy

# Local
from cxsystem2.neurodynlib.tools import spike_tools


def plot_voltage_and_current_traces(
    voltage_monitor: b2.StateMonitor,
    current: b2.TimedArray,
    title: str | None = None,
    firing_threshold: b2.units.Quantity | None = None,
    legend_location: int = 0,
    save_name: str | None = None,
) -> tuple[plt.Axes, plt.Axes]:
    """
    Plot voltage and current traces.

    Parameters
    ----------
    voltage_monitor : b2.StateMonitor
        Recorded voltage.
    current : b2.TimedArray
        Injected current.
    title : str, optional
        Title of the figure.
    firing_threshold : Quantity, optional
        If set, the firing threshold is plotted.
    legend_location : int, optional
        Legend location. Default is 0 ("best").
    save_name : str, optional
        If set, the figure is saved to this file name.

    Returns
    -------
    tuple of Axes
        The current (top) and voltage (bottom) axes.
    """

    assert isinstance(voltage_monitor, b2.StateMonitor), "voltage_monitor is not of type StateMonitor"
    assert isinstance(current, b2.TimedArray), "current is not of type TimedArray"

    time_values_ms = voltage_monitor.t / b2.ms

    # current
    axis_c = plt.subplot(211)
    c = current(voltage_monitor.t, 0)
    max_current = max(current(voltage_monitor.t, 0))
    min_current = min(current(voltage_monitor.t, 0))
    margin = 1.05 * (max_current - min_current)
    # plot the input current time-aligned with the voltage monitor
    plt.plot(voltage_monitor.t / b2.ms, c, "r", lw=2)
    if margin > 0.:
        plt.ylim((min_current - margin) / b2.amp, (max_current + margin) / b2.amp)

    plt.ylabel(f"Input current [A] \n min: {min_current} \nmax: {max_current}")
    plt.grid()
    axis_v = plt.subplot(212)
    plt.plot(time_values_ms, voltage_monitor[0].vm / b2.mV, lw=2)

    if firing_threshold is not None:
        plt.plot(
            (voltage_monitor.t / b2.ms)[[0, -1]],
            [firing_threshold / b2.mV, firing_threshold / b2.mV],
            "r--", lw=2
        )
    max_val = max(voltage_monitor[0].vm)
    if firing_threshold is not None:
        max_val = max(max_val, firing_threshold)
    min_val = min(voltage_monitor[0].vm)
    margin = 0.05 * (max_val - min_val)
    plt.ylim((min_val - margin) / b2.mV, (max_val + margin) / b2.mV)
    plt.xlabel("t [ms]")
    plt.ylabel(f"membrane voltage [mV]\n min: {min_val}\n max: {max_val}")
    plt.grid()

    if firing_threshold is not None:
        plt.legend(["vm", "firing threshold"], fontsize=12, loc=legend_location)

    if title is not None:
        plt.suptitle(title)

    if save_name is not None:
        if save_name[-4:] != '.png' and save_name[-4:] != '.eps':
            save_name += '.png'
        plt.savefig(save_name)

    return axis_c, axis_v


def plot_network_activity(
    rate_monitor: b2.PopulationRateMonitor,
    spike_monitor: b2.SpikeMonitor,
    voltage_monitor: b2.StateMonitor | None = None,
    spike_train_idx_list: list | None = None,
    t_min: b2.units.Quantity | None = None,
    t_max: b2.units.Quantity | None = None,
    N_highlighted_spiketrains: int = 3,
    avg_window_width: b2.units.Quantity | None = None,
    sup_title: str | None = None,
    figure_size: tuple = (10, 4),
) -> tuple[plt.Figure, plt.Axes, plt.Axes, plt.Axes | None]:
    """
    Visualize the results of a network simulation: spike train, population
    activity and voltage traces.

    Parameters
    ----------
    rate_monitor : b2.PopulationRateMonitor
        Rate of the population.
    spike_monitor : b2.SpikeMonitor
        Spike trains of individual neurons.
    voltage_monitor : b2.StateMonitor, optional
        Voltage traces of some neurons (same as in ``spike_train_idx_list``).
    spike_train_idx_list : list, optional
        Neuron indices whose spike train is plotted. If None, all (up to 5000)
        spike trains are plotted, or ``voltage_monitor.record`` if a voltage
        monitor is given.
    t_min : Quantity, optional
        Lower bound of the plotted time interval. If None, set to the larger of
        [0 ms, t_max - 100 ms].
    t_max : Quantity, optional
        Upper bound of the plotted time interval. If None, set to the timestamp
        of the last spike.
    N_highlighted_spiketrains : int, optional
        Number of spike trains visually highlighted. Default is 3. If 0 and a
        voltage monitor is given, all its voltage traces are plotted.
    avg_window_width : Quantity, optional
        Width of the smoothing window applied to the population rate before
        plotting. Default is 1.0 ms.
    sup_title : str, optional
        Figure suptitle.
    figure_size : tuple, optional
        (width, height) passed to pyplot's ``figsize``.

    Returns
    -------
    tuple
        (figure, raster axes, rate axes, voltage axes or None).
    """
    if avg_window_width is None:
        avg_window_width = 1.0 * b2.ms

    assert isinstance(rate_monitor, b2.PopulationRateMonitor), \
        "rate_monitor  is not of type PopulationRateMonitor"
    assert isinstance(spike_monitor, b2.SpikeMonitor), \
        "spike_monitor is not of type SpikeMonitor"
    assert (voltage_monitor is None) or (isinstance(voltage_monitor, b2.StateMonitor)), \
        "voltage_monitor is not of type StateMonitor"
    assert (spike_train_idx_list is None) or (isinstance(spike_train_idx_list, list)), \
        "spike_train_idx_list is not of type list"

    all_spike_trains = spike_monitor.spike_trains()
    if spike_train_idx_list is None:
        if voltage_monitor is not None:
            # if no index list is provided use the one from the voltage monitor
            spike_train_idx_list = numpy.sort(voltage_monitor.record)
        else:
            # no index list AND no voltage monitor: plot all spike trains
            spike_train_idx_list = numpy.sort(all_spike_trains.keys())
        if len(spike_train_idx_list) > 5000:
            # avoid slow plotting of a large set
            print("Warning: raster plot with more than 5000 neurons truncated!")
            spike_train_idx_list = spike_train_idx_list[:5000]

    # get a reasonable default interval
    if t_max is None:
        t_max = max(rate_monitor.t / b2.ms)
    else:
        t_max = t_max / b2.ms
    if t_min is None:
        t_min = max(0., t_max - 100.)  # if none, plot at most the last 100ms
    else:
        t_min = t_min / b2.ms

    fig = None
    ax_raster = None
    ax_rate = None
    ax_voltage = None
    if voltage_monitor is None:
        fig, (ax_raster, ax_rate) = plt.subplots(2, 1, sharex=True, figsize=figure_size)
    else:
        fig, (ax_raster, ax_rate, ax_voltage) = plt.subplots(3, 1, sharex=True, figsize=figure_size)

    # nested helpers to plot the parts, note that they use parameters defined outside.
    def get_spike_train_ts_indices(
        spike_train: b2.units.Quantity,
    ) -> tuple[numpy.ndarray, numpy.ndarray]:
        """
        Helper. Extracts the spikes within the time window from the spike train
        """
        ts = spike_train/b2.ms
        # spike_within_time_window = (ts >= t_min) & (ts <= t_max)
        # idx_spikes = numpy.where(spike_within_time_window)
        idx_spikes = (ts >= t_min) & (ts <= t_max)
        ts_spikes = ts[idx_spikes]
        return idx_spikes, ts_spikes

    def plot_raster() -> None:
        """
        Helper. Plots the spike trains of the spikes in spike_train_idx_list
        """
        neuron_counter = 0
        for neuron_index in spike_train_idx_list:
            idx_spikes, ts_spikes = get_spike_train_ts_indices(all_spike_trains[neuron_index])
            ax_raster.scatter(ts_spikes, neuron_counter * numpy.ones(ts_spikes.shape),
                              marker=".", c="k", s=15, lw=0)
            neuron_counter += 1
        ax_raster.set_ylim([0, neuron_counter])

    def highlight_raster(neuron_idxs: list) -> None:
        """
        Helper. Highlights three spike trains
        """
        for i in range(len(neuron_idxs)):
            color = "r" if i == 0 else "k"
            raster_plot_index = neuron_idxs[i]
            population_index = spike_train_idx_list[raster_plot_index]
            idx_spikes, ts_spikes = get_spike_train_ts_indices(all_spike_trains[population_index])
            ax_raster.axhline(y=raster_plot_index, linewidth=.5, linestyle="-", color=[.9, .9, .9])
            ax_raster.scatter(
                ts_spikes, raster_plot_index * numpy.ones(ts_spikes.shape),
                marker=".", c=color, s=144, lw=0)
        ax_raster.set_ylabel("neuron #")
        ax_raster.set_title("Raster Plot", fontsize=10)

    def plot_population_activity(window_width: b2.units.Quantity = 0.5 * b2.ms) -> None:
        """
        Helper. Plots the population rate and a mean
        """
        ts = rate_monitor.t / b2.ms
        idx_rate = (ts >= t_min) & (ts <= t_max)
        # ax_rate.plot(ts[idx_rate],rate_monitor.rate[idx_rate]/b2.Hz, ".k", markersize=2)
        smoothed_rates = rate_monitor.smooth_rate(window="flat", width=window_width)/b2.Hz
        ax_rate.plot(ts[idx_rate], smoothed_rates[idx_rate])
        ax_rate.set_ylabel("A(t) [Hz]")
        ax_rate.set_title("Population Activity", fontsize=10)

    def plot_voltage_traces(voltage_traces_i: list[int] | range) -> None:
        """
        Helper. Plots three voltage traces
        """
        ts = voltage_monitor.t/b2.ms
        idx_voltage = (ts >= t_min) & (ts <= t_max)
        for i in range(len(voltage_traces_i)):
            color = "r" if i == 0 else ".7"
            raster_plot_index = voltage_traces_i[i]
            population_index = spike_train_idx_list[raster_plot_index]
            ax_voltage.plot(
                ts[idx_voltage], voltage_monitor[population_index].v[idx_voltage]/b2.mV,
                c=color, lw=1.)
            ax_voltage.set_ylabel("V(t) [mV]")
            ax_voltage.set_title("Voltage Traces", fontsize=10)

    plot_raster()
    plot_population_activity(avg_window_width)
    nr_neurons = len(spike_train_idx_list)
    highlighted_neurons_i = []  # default to an empty list.
    if N_highlighted_spiketrains > 0:
        fract = numpy.linspace(0, 1, N_highlighted_spiketrains + 2)[1:-1]
        highlighted_neurons_i = [int(nr_neurons * v) for v in fract]
        highlight_raster(highlighted_neurons_i)

    if voltage_monitor is not None:
        if N_highlighted_spiketrains == 0:
            traces_i = range(nr_neurons)
        else:
            traces_i = highlighted_neurons_i
        plot_voltage_traces(traces_i)

    plt.xlabel("t [ms]")

    if sup_title is not None:
        plt.suptitle(sup_title)

    return fig, ax_raster, ax_rate, ax_voltage


def plot_ISI_distribution(
    spike_stats: spike_tools.PopulationSpikeStats,
    hist_nr_bins: int = 50,
    xlim_max_ISI: b2.units.Quantity | None = None,
) -> plt.Figure:
    """
    Compute and display the ISI distribution of a population as a histogram.

    Parameters
    ----------
    spike_stats : spike_tools.PopulationSpikeStats
        Statistics of a population activity.
    hist_nr_bins : int, optional
        Number of histogram bins. Default is 50.
    xlim_max_ISI : Quantity, optional
        If set, the upper xlim of the plot is set to this value. The CV does
        not change if this bound is set.

    Returns
    -------
    plt.Figure
        The figure.
    """
    assert isinstance(spike_stats, spike_tools.PopulationSpikeStats), \
        "spike_stats is not of type spike_tools.PopulationSpikeStats"
    isi_ms = spike_stats.all_ISI/b2.ms

    if xlim_max_ISI is not None:
        lim = xlim_max_ISI/b2.ms
        idx = isi_ms < lim
        isi_ms = isi_ms[idx]

    f = plt.figure()
    plt.hist(isi_ms, bins=hist_nr_bins)
    if xlim_max_ISI is not None:
        xmax = xlim_max_ISI / b2.ms
        plt.xlim([0, xmax])
    plt.title(f"ISI histogram, CV={round(spike_stats.CV, 3)}")
    plt.xlabel("ISI [ms]")
    return f


def plot_spike_train_power_spectrum(
    freq: numpy.ndarray,
    mean_ps: numpy.ndarray,
    all_ps: dict,
    max_freq: b2.units.Quantity,
    nr_highlighted_neurons: int = 2,
    mean_firing_freqs_per_neuron: dict | None = None,
    plot_f0: bool = False,
) -> tuple[plt.Figure, list]:
    """
    Visualize the power spectrum of spike trains.

    Parameters
    ----------
    freq : ndarray
        Frequencies (x axis).
    mean_ps : ndarray
        Average power over all neurons.
    all_ps : dict
        Power spectra for each single neuron.
    max_freq : Quantity
        The x-lim of the plot is [-0.05*max_freq, max_freq].
    nr_highlighted_neurons : int, optional
        Number of single-neuron spectra highlighted. Default is 2.
    mean_firing_freqs_per_neuron : dict, optional
        Mean firing rate per neuron. If None, not shown in the legend.
    plot_f0 : bool, optional
        If True, the power at frequency 0 is plotted. Default is False.

    Returns
    -------
    tuple
        The figure and the list of highlighted neuron indices.
    """
    nr_neurons = len(all_ps)
    f = plt.figure()
    color = "r"
    msize = 10
    legend_text = []
    random_neuron_index = []

    first_idx_to_plot = 0 if plot_f0 else 1
    for i in range(nr_highlighted_neurons):
        rand_idx = numpy.random.randint(nr_neurons)
        rand_key = all_ps.keys()[rand_idx]
        rand_neuron_ps = all_ps[rand_key]
        plt.plot(freq[first_idx_to_plot:], rand_neuron_ps[first_idx_to_plot:],
                 marker=".", linestyle=" ", markersize=msize, c=color)
        color = [.75, .75, .75]  # print the first neuron in red and all others in gray
        msize = 8
        random_neuron_index.append(rand_key)
        if mean_firing_freqs_per_neuron is None:
            legend_text.append(f"PS Neuron #{rand_key}")
        else:
            legend_text.append(
                f"PS Neuron #{rand_key}, avg rate={round(mean_firing_freqs_per_neuron[rand_key], 1)}"
            )

    plt.plot(freq[first_idx_to_plot:], mean_ps[first_idx_to_plot:], ".b")

    if mean_firing_freqs_per_neuron is None:
        legend_text.append("averaged PS")
    else:
        avg_rate = numpy.mean(mean_firing_freqs_per_neuron.values())
        legend_text.append(f"averaged PS, avg rate={round(avg_rate, 1)}")

    plt.legend(legend_text)
    plt.xlim([-0.05*max_freq/b2.Hz, max_freq/b2.Hz])
    plt.axvline(x=0., lw=1, color="k")
    plt.grid()
    plt.xlabel("Frequency [Hz]")
    plt.ylabel("Power")
    plt.title("Single neuron power spectrum and average")
    return f, random_neuron_index


def plot_population_activity_power_spectrum(
    freq: numpy.ndarray,
    ps: numpy.ndarray,
    max_freq: b2.units.Quantity,
    average_At: b2.units.Quantity | None = None,
    plot_f0: bool = False,
) -> plt.Figure:
    """
    Plot the power spectrum of the population activity A(t).

    Parameters
    ----------
    freq : ndarray
        Frequencies (x axis).
    ps : ndarray
        Power spectrum of the population activity.
    max_freq : Quantity
        Data is plotted in the interval [-0.05*max_freq, max_freq].
    average_At : Quantity, optional
        Average population rate, shown in the title if given.
    plot_f0 : bool, optional
        If True, the power at frequency 0 is plotted. Default is False.

    Returns
    -------
    plt.Figure
        The figure.
    """
    first_idx_to_plot = 0 if plot_f0 else 1
    f = plt.figure()
    plt.plot(freq[first_idx_to_plot:], ps[first_idx_to_plot:], ".b")
    plt.axvline(x=0., lw=1, color="k")
    plt.xlim([-.05*max_freq/b2.Hz, max_freq/b2.Hz])
    plt.grid()
    plt.xlabel("Frequency [Hz]")
    plt.ylabel("Power")
    if average_At is None:
        plt.title("Power Spectrum of population activity A(t).")
    else:
        plt.title(f"Power Spectrum of population activity A(t). Avg. rate = {round(average_At, 1)}")
    return f
