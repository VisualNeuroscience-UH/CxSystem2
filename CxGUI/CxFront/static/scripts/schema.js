runtime_params_schema = {
    "title": "Params",
    "type": "object",
    "id": "params",
    "properties": {
        "runtime": {
            "type": "string",
            "description": "Duration of simulation (e.g. 1500*ms or 1.5*second)",
        },
        "device": {
            "type": "string",
            "description": "Device for Brian2 code generation",
            "enum": ["Python", "Cython", "Cpp", "GeNN"]
        },
        "sys_mode": {
            "type": "string",
            "description": "System mode: local means ... , expanded means ... (?)",
            "enum": ["local", "expanded"]
        },
        "scale": {
            "type": "string",
            "description": "Defines how much the network is scaled (?)",
        },
        "grid_radius": {
            "type": "string",
            "description": "Radius of the 2D circle inside which the neurons are randomly placed (e.g. 200*um)",
        },
        "min_distance": {
            "type": "string",
            "description": "Minimum distance between neurons (e.g. 1*um)",
        },
        "output_path_and_filename": {
            "type": "string",
            "description": "Relative path and filename to where results are stored (e.g. ./results/output.gz)",
            "default": "./results/output.gz"
        },
        "connections_saving_path_and_filename": {
            "type": "string",
            "description": "Relative path and filename to where the network configuration with synaptic weights are stored (export)",
            "default": "./simdata/data.gz"
        },
        "connections_loading_path_and_filename": {
            "type": "string",
            "description": "Relative path and filename from where the network configuration with synaptic weights are retrieved (import)",
            "default": "./simdata/data.gz"
        },
        "number_of_process": {
            "type": "integer",
            "description": "Number of CPU cores to use in parallel (for parameter searches; a single simulation cannot be run in parallel)",
            "default": 1,
            "minimum": 1,
            "maximum": 32,
        },
        "default_clock": {
            "type": "string",
            "description": "Simulation time step (e.g. 0.1*ms)",
        },
        "trials_per_config": {
            "type": "integer",
            "description": "Number of trials for each set of parameters",
            "default": 1,
            "minimum": 1,
            "maximum": 20,
        },
        "do_init_vms": {
            "type": "boolean",
            "description": "Randomize initial membrane voltages (between leak reversal and threshold potential)",
            "format": "checkbox"
        },
        "load_positions_only": {
            "type": "boolean",
            "description": "Import neuron positions from connectivity file but randomize connections",
            "format": "checkbox"
        },

        "do_benchmark": {
            "type": "boolean",
            "description": "Do a benchmark (?)",
            "format": "checkbox"
        },
        "save_generated_video_input_flag": {
            "type": "boolean",
            "description": "If checked, the generated video for input will be saved (?)",
            "format": "checkbox"
        },
        "multidimension_array_run": {
            "type": "boolean",
            "description": "Run all possible parameter combinations in array run (instead of 1D sweeps)",
            "format": "checkbox"
        },
        "profiling": {
            "type": "boolean",
            "description": "Benchmark the simulation using Brian2's profiling tool",
            "format": "checkbox"
        },
        "run_in_cluster": {
            "type": "boolean",
            "description": "Run the simulation on a cluster",
            "format": "checkbox"
        },
        "cluster_job_file_path": {
            "type": "string",
            "description": "Relative path and filename of the Slurm batch file",
        },
        "cluster_number_of_nodes": {
            "type": "integer",
            "description": "Number of nodes to be employed on the HPC server",
            "default": 1,
            "minimum": 1,
            "maximum": 32,
        },
        "cluster_address": {
            "type": "string",
            "description": "Address of the HPC server (e.g. taito.csc.fi)",
        },
        "username": {
            "type": "string",
            "description": "Username on the HPC server",
        },
        "remote_repo_path": {
            "type": "string",
            "description": "Absolute path to CxSystem2 on the HPC server",
        },
        "remote_output_folder": {
            "type": "string",
            "description": "Absolute path for storing results on the HPC server",
        },
        "remote_branch": {
            "type": "string",
            "description": "GitHub branch of CxSystem2 to use for HPC simulations",
        },
    }
};

neurons_schema = {
    type: "array",
    title: "NeuronGroups",
    format: "tabs",
    items: {
        title: "NeuronGroup",
        headerTemplate: "[G{{i}}] {{self.neuron_type}} at L{{self.layer_idx}}",
        properties: {
            "idx": {
                "type": "integer",
                "description": "Running index for the neuron group",
                // "default": "{{i}}",
            },
            "number_of_neurons": {
                "type": "integer",
                "description": "Number of neurons in the neuron group ",
                "default": 100,
                "minimum": 1,
                "maximum": 10000,
            },
            "neuron_type": {
                "type": "string",
                "description": "Neuron type",
                "enum": ["PC", "BC", "MC", "L1i","SS"]
            },
            'neuron_subtype':{
                  "type": "string",
                "description": "Neuron subtype, i.e. reference to the concrete set of parameters",
            },
            "layer_idx": {
                "type": "string",
                "description": "Layer where the neuron population is located (2 = layer 2/3)",
                "enum": ["1", "2", "4", "5", "6",
                    "[2->1]", "[4->1]", "[5->1]", "[6->1]",
                    "[2->2]", "[4->2]", "[5->2]", "[6->2]",
                    "[4->4]", "[5->4]", "[6->4]",
                    "[5->5]", "[6->5]", "[6->6]"]
            },
            "net_center": {
                "type": "string",
                "description": "Center point of the neuron population (e.g. 0+0j)",
            },
            "noise_sigma": {
                "type": "string",
                "description": "Membrane noise (e.g. 2*mV)",
            },
            "monitors": {
                "type": "string",
                "format": "text",
                "description": "Monitors for recording spikes and state variables",
            },
            'n_background_inputs':{
                "type": "integer",
                "description": "Number of excitatory background synapses"
            },
            'n_background_inhibition':{
                "type": "integer",
                "description": "Number of inhibitory background synapses"
            },
            'gemean':{
                "type": "string",
                "description": "gemean"
            },
            'gestd':{
                "type": "string",
                "description": "gestd"
            },
            'gimean':{
                "type": "string",
                "description": "gimean"
            },
            'gistd':{
                "type": "string",
                "description": "gistd"
            }
        }
    }
};

inputs_schema = {
    type: "array",
    title: "IN",
    format: "tabs",
    items: {
        title: "InputGroup",
        headerTemplate: "Group{{i}} - {{self.type}}",
        options: {
            "keep_oneof_values": false
        },
        oneOf: [
            {
                "title": "Video Input",
                "type": "object",
                "id": "video",
                "properties": {
                    "idx": {
                        "type": "integer",
                        "description": "index"
                    },
                    "path": {
                        "type": "string",
                        "description": "Defines path to input video",
                    },
                    "type": {
                        "type": "string",
                        "description": "Defines path to input video",
                        "enum": ["Video"]
                    },
                    "freq": {
                        "type": "string",
                        "format": "text",
                        "description": "defines the frequency of "
                    },
                    "monitors": {
                        "type": "string",
                        "format": "text",
                        "description": "defines noise",
                    }
                }
            },
            {
                "title": "VPM",
                "type": "object",
                "id": "vpm",
                "properties": {
                    "idx": {
                        "type": "integer",
                        "description": "index",
                        // "default": "{{i}}",
                    },
                    "type": {
                        "type": "string",
                        "description": "Defines path to input video",
                        "enum": ["VPM"]
                    },
                    "number_of_neurons": {
                        "type": "integer",
                        "description": "Defines number of neurons in neuron group ",
                        "default": 100,
                        "minimum": 1,
                        "maximum": 10000,
                    },
                    "radius": {
                        "type": "string",
                        "description": "defines",
                    },
                    "spike_times": {
                        "type": "string",
                        "description": "Defines the spike times ",
                    },
                    "net_center": {
                        "type": "string",
                        "description": "net center ",
                    },
                    "monitors": {
                        "type": "string",
                        "format": "text",
                        "description": "defines noise",
                    }
                }
            }
        ]
    }
}

connections_schema = {
    type: "array",
    title: "Synapses",
    format: "tabs",
    items: {
        title: "Synapse",
        headerTemplate: "[S{{i}}] {{self.pre_syn_idx}}  ➤ {{self.post_syn_idx}}",
        "properties": {
            "receptor": {
                "type": "string",
                "description": "Sets whether the connection is excitatory or inhibitory",
                "enum": ["ge", "gi"]
            },
            "pre_syn_idx": {
                "type": "integer",
                "description": "Presynaptic neuron group index",
                "default": 0,
                "minimum": 0,
                "maximum": 100
            },
            "post_syn_idx": {
                "type": "string",
                "format": "text",
                "description": "Postsynaptic neuron group index",
            },
            "syn_type": {
                "type": "string",
                "description": "Synapse model",
                "default": "Fixed",
                "enum": ["Fixed", "Depressing", "Facilitating"]
            },
            "p": {
                "type": "string",
                "description": "Connection probability",
            },
            "n": {
                "type": "string",
                "description": "Number of synapses per connection"
            },
            "monitors": {
                "type": "string",
                "format": "text",
                "description": "Monitors for synaptic state variables",
            },
            "load_connection": {
                "type": "string",
                "format": "text",
                "description": "Load connection",
            },
            "save_connection": {
                "type": "string",
                "format": "text",
                "description": "Save connection",
            },
            "custom_weight": {
                "type": "string",
                "description": "Synaptic weight for this specific connection (overrides more general weight definitions)"
            }
        }
    }
}


physio_schema = {
    type: "array",
    title: "Physiology",
    format: "tabs",
    items: {
        title: "Physio",
        headerTemplate: "{{self.Variable}}",
        options: {
            "keep_oneof_values": false
        },
        oneOf: [{
            "title": "Variable Value",
            "type": "object",
            "id": "vairablevalue",
            "properties": {
                "Variable": {
                    "type": "string"
                },
                "Value": {
                    "type": "string",
                },
                "Comment": {
                    "type": "string"
                }
            }
        },
            {
                "title": "Variable Key Value",
                "type": "object",
                "id": "vairablekeyvalue",
                "properties": {
                    "Variable": {
                        "type": "string"
                    },
                    "Key-Value": {
                        "type": "array",
                        "format": "table",
                        "items": {
                            "type": "object",
                            "properties": {
                                "Key": {
                                    "type": "string"
                                },
                                "Value": {
                                    "type": "string"
                                },
                                "Comment": {
                                    "type": "string"
                                }
                            }
                        }
                    }
                }
            }
        ]
    }
}