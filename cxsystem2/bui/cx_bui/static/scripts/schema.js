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
            "default": "1*um"
        },
        "workspace_path": {
            "type": "string",
            "description": "The main working directory of CxSystem; other paths are given relative to this path",
            "default": "~/CxWorkspace"
        },
        "simulation_title": {
            "type": "string",
            "description": "Title for the current batch of simulations",
            "default": "my_simulations"
        },
        "compression_method": {
            "type": "string",
            "description": "Data compression method",
            "enum": ["gzip", "bzip2", "pickle"]
        },
        "import_connections_from": {
            "type": "string",
            "description": "Path and filename from where connections with synaptic weights are imported (relative to workspace path)",
            "default": "--"
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
            "default": "0.1*ms"
        },
        "trials_per_config": {
            "type": "integer",
            "description": "Number of trials for each set of parameters",
            "default": 1,
            "minimum": 1,
            "maximum": 20,
        },
        "init_vms": {
            "type": "boolean",
            "description": "Randomize initial membrane voltages (between V_init_min and V_init_max)",
            "format": "checkbox"
        },
        "load_positions_only": {
            "type": "boolean",
            "description": "Import neuron positions from connectivity file but randomize connections",
            "format": "checkbox"
        },
        "benchmark": {
            "type": "boolean",
            "description": "Benchmark the simulation using CxSystem's own profiler",
            "format": "checkbox"
        },
        "save_input_video": {
            "type": "boolean",
            "description": "If checked, the generated video for input will be saved (?)",
            "format": "checkbox"
        },
        "multidimension_array_run": {
            "type": "boolean",
            "description": "Run all possible parameter combinations in an array run (instead of 1D sweeps)",
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
            "description": "Absolute path and filename of the Slurm batch file (csc_taito.job)",
            "default" : "--"
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
            "default" : "--"
        },
        "cluster_login_node": {
            "type": "string",
            "description": "Address of the login node in case there exists one",
            "default" : "--"
        },
        "cluster_username": {
            "type": "string",
            "description": "Username on the HPC server",
            "default" : "--"
        },
        "cluster_workspace": {
            "type": "string",
            "description": "Workspace path on the HPC server",
            "default" : "--"
        },
    }
};

neurons_schema = {
    type: "array",
    title: "NeuronGroups",
    format: "tabs",
    items: {
        title: "NeuronGroup",
        headerTemplate: "[G{{self.idx}}] {{self.neuron_type}} at L{{self.layer_idx}}",
        options: {
            "keep_oneof_values": false
        },
        oneOf: [{
            "title": "NeuronGroup",
            "type": "object",
            "id": "ng",
            properties: {
                "idx": {
                    "type": "integer",
                    "description": "Running index for the neuron group"
                },
                "number_of_neurons": {
                    "type": "integer",
                    "description": "Number of neurons in the neuron group ",
                    "default": 100,
                    "minimum": 1,
                    "maximum": 100000,
                },
                "neuron_type": {
                    "type": "string",
                    "description": "Neuron type",
                    "enum": ["PC", "BC", "MC", "L1i", "SS"]
                },
                'neuron_subtype': {
                    "type": "string",
                    "description": "Neuron subtype, i.e. reference to the concrete set of parameters in the physiology config",
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
                "monitors": {
                    "type": "string",
                    "format": "text",
                    "description": "Monitors for recording spikes and state variables",
                    "default" : "--"
                },
                'n_background_inputs': {
                    "type": "integer",
                    "description": "Number of excitatory background synapses"
                },
                'n_background_inhibition': {
                    "type": "integer",
                    "description": "Number of inhibitory background synapses"
                }
            }
        }]
    }
};

inputs_schema = {
    type: "array",
    title: "IN",
    format: "tabs",
    items: {
        title: "InputGroup",
        headerTemplate: "G{{self.idx}} - {{self.type}}",
        options: {
            "keep_oneof_values": false
        },
        oneOf: [
            // {
            //     "title": "Video Input",
            //     "type": "object",
            //     "id": "video",
            //     "properties": {
            //         "idx": {
            //             "type": "integer",
            //             "description": "index"
            //         },
            //         "path": {
            //             "type": "string",
            //             "description": "Defines path to input video",
            //         },
            //         "type": {
            //             "type": "string",
            //             "description": "Defines the input type",
            //             "enum": ["Video"]
            //         },
            //         "freq": {
            //             "type": "string",
            //             "format": "text",
            //             "description": "defines the frequency of "
            //         },
            //         "monitors": {
            //             "type": "string",
            //             "format": "text",
            //             "description": "defines noise",
            //         }
            //     }
            // },
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
                        "description": "Defines the input type",
                        "enum": ["VPM"]
                    },
                    "number_of_neurons": {
                        "type": "integer",
                        "description": "Defines the number of neurons in the input group",
                        "default": 100,
                        "minimum": 1,
                        "maximum": 10000,
                    },
                    "radius": {
                        "type": "string",
                        "description": "Radius of the disc inside which the thalamocortical axons are spread",
                    },
                    "spike_times": {
                        "type": "string",
                        "description": "Defines the times of synchronous spikes",
                    },
                    "net_center": {
                        "type": "string",
                        "description": "Center of the disc of thalamocortical connections",
                    },
                    "monitors": {
                        "type": "string",
                        "format": "text",
                        "default": "[Sp]",
                        "description": "Sets the monitors",
                    }
                }
            }
        ]
    }
};

connections_schema = {
    type: "array",
    title: "Synapses",
    format: "tabs",
    items: {
        title: "Synapse",
        headerTemplate: "[S{{i}}] {{self.pre_syn_idx}}  ➤ {{self.post_syn_idx}}",
        options: {
            "keep_oneof_values": false
        },
        oneOf: [{
            "title": "Synapse",
            "type": "object",
            "id": "syn",
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
                    "default": "1",
                    "description": "Number of synapses per connection"
                },
                "monitors": {
                    "type": "string",
                    "format": "text",
                    "default": "--",
                    "description": "Monitors for synaptic state variables",
                },
                "load_connection": {
                    "type": "string",
                    "format": "text",
                    "default": "1",
                    "description": "Load connection",
                },
                "save_connection": {
                    "type": "string",
                    "format": "text",
                    "default": "1",
                    "description": "Save connection",
                },
                "custom_weight": {
                    "type": "string",
                    "description": "Synaptic weight for this specific connection (overrides more general weight definitions)",
                    "default": "--"
                }
            }
        }]
    }
};


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
};
