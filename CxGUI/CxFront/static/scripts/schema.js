runtime_params_schema = {
    "title": "Params",
    "type": "object",
    "id": "params",
    "properties": {
        "runtime": {
            "type": "string",
            "description": "Duration of simulation in brian units, e.g. 0.2*seconds",
        },
        "device": {
            "type": "string",
            "description": "Brian simulation device type",
            "enum": ["Cpp", "Python", "GeNN"]
        },
        "sys_mode": {
            "type": "string",
            "description": "System mode: local means ... , expanded means ... ",
            "enum": ["local", "expanded"]
        },
        "scale": {
            "type": "integer",
            "description": "Defines how much the network is scaled",
            "default": 1,
            "minimum": 1,
            "maximum": 10,
        },
        "grid_radius": {
            "type": "string",
            "description": "Defines grid radius in micrometer (um)",
        },
        "min_distance": {
            "type": "string",
            "description": "Defines minimum distance between the neurons in micrometer (um)",
        },
        "output_path_and_filename": {
            "type": "string",
            "description": "relative path to the output filename",
            "default": "./results/output.gz"
        },
        "connections_saving_path_and_filename": {
            "type": "string",
            "description": "relative path of the filename to save the output connection information ",
            "default": "./simdata/data.gz"
        },
        "connections_loading_path_and_filename": {
            "type": "string",
            "description": "relative path of the filename to load the output connection information from",
            "default": "./simdata/data.gz"
        },
        "number_of_process": {
            "type": "integer",
            "description": "Defines number of processes for array run",
            "default": 1,
            "minimum": 1,
            "maximum": 32,
        },
        "default_clock": {
            "type": "string",
            "description": "Defines simulation clock in micro-seconds (us)",
        },
        "trials_per_config": {
            "type": "integer",
            "description": "Defines how many times each simulation should be repeated",
            "default": 1,
            "minimum": 1,
            "maximum": 20,
        },
        "do_init_vms": {
            "type": "boolean",
            "description": "If checked, the initial membrane voltages will be randomized",
            "format": "checkbox"
        },
        "load_positions_only": {
            "type": "boolean",
            "description": "If checked, only the neuron positions will be loaded from the simulation data file (and connection info will not be loaded)",
            "format": "checkbox"
        },

        "do_benchmark": {
            "type": "boolean",
            "description": "If checked, the simulation will be benchamrked",
            "format": "checkbox"
        },
        "save_generated_video_input_flag": {
            "type": "boolean",
            "description": "If checked, the generated video for input will be saved",
            "format": "checkbox"
        },
        "multidimension_array_run": {
            "type": "boolean",
            "description": "If checked, the array runs will be considered as a multi-dimentional simulations",
            "format": "checkbox"
        },
        "profiling": {
            "type": "boolean",
            "description": "If checked, the array runs will be considered as a multi-dimentional simulations",
            "format": "checkbox"
        }
    }
};

neurons_schema = {
    type: "array",
    title: "NeuronGroups",
    format: "tabs",
    items: {
        title: "NeuronGroup",
        headerTemplate: "Group{{i}} - {{self.neuron_type}}",
        properties: {
            "idx": {
                "type": "integer",
                "description": "index",
                // "default": "{{i}}",
            },
            "number_of_neurons": {
                "type": "integer",
                "description": "Defines number of neurons in neuron group ",
                "default": 100,
                "minimum": 1,
                "maximum": 10000,
            },
            "neuron_type": {
                "type": "string",
                "description": "Defines the neuron type",
                "enum": ["PC", "BC", "MC", "L1i","SS"]
            },
            'neuron_subtype':{
                  "type": "string",
                "description": "Defines the neuron subtype",
            },
            "layer_idx": {
                "type": "string",
                "description": "Defines ",
                "enum": ["1", "2", "3", "4", "5", "6", "[2->1]", "[3->1]", "[4->1]", "[5->1]", "[6->1]", "[3->2]", "[4->2]", "[5->2]", "[6->2]", "[4->3]", "[5->3]", "[6->3]", "[5->4]", "[6->4]", "[6->5]"]
            },
            "net_center": {
                "type": "string",
                "description": "net center ",
            },
            "noise_sigma": {
                "type": "string",
                "description": "defines noise",
            },
            "monitors": {
                "type": "string",
                "format": "text",
                "description": "defines noise",
            },
            'n_background_inputs':{
                "type": "integer",
                "description": "background input"
            },
            'n_background_inhibition':{
                "type": "integer",
                "description": "n_background_inhibition"
            },
            'gemean':{
                "type": "string",
                "description": ""
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
                "description": ""
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
        headerTemplate: "Group{{i}} - {{self.neuron_type}}",
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
                        // "default": "{{i}}",
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
        headerTemplate: "Synapse{{i}} - {{self.device}}",
        "properties": {
            "receptor": {
                "type": "string",
                "description": "Defines the receptor types",
                "enum": ["ge", "gi"]
            },
            "pre_syn_idx": {
                "type": "integer",
                "description": "Defines ...",
                "default": 0,
                "minimum": 0,
                "maximum": 100
            },
            "post_syn_idx": {
                "type": "string",
                "format": "text",
                "description": "Defines ...",
            },
            "syn_type": {
                "type": "string",
                "description": "Defines  ",
                "default": "Fixed",
                "enum": ["Fixed","Depressing"]
            },
            "p": {
                "type": "string",
                "description": "Defines ",
            },
            "n": {
                "type": "string",
                "description": "Defines "
            },
            "monitors": {
                "type": "string",
                "format": "text",
                "description": "defines noise",
            },
            "load_connection": {
                "type": "string",
                "format": "text",
                "description": "defines noise",
            },
            "save_connection": {
                "type": "string",
                "format": "text",
                "description": "defines noise",
            },
            "custom_weight": {
                "type": "string",
                "description": "defines "
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
        headerTemplate: "Physio{{i}} - {{self.device}}",
        options: {
            "keep_oneof_values": false
        },
        oneOf: [{
            "title": "Variable Value",
            "type": "object",
            "id": "vairablevalue",
            "properties": {
                "Variable": {
                    "type": "string",
                    "description": "defines "
                },
                "Value": {
                    "type": "string",
                    "description": "defines "
                },
                "Comment": {
                    "type": "string",
                    "description": "defines "
                }
            }
        },
            {
                "title": "Variable Key Value",
                "type": "object",
                "id": "vairablekeyvalue",
                "properties": {
                    "Variable": {
                        "type": "string",
                        "description": "defines "
                    },
                    "Key-Value": {
                        "type": "array",
                        "format": "table",
                        "items": {
                            "type": "object",
                            "properties": {
                                "Key": {
                                    "type": "string",
                                    "description": "defines "
                                },
                                "Value": {
                                    "type": "string",
                                    "description": "defines "
                                },
                                "Comment": {
                                    "type": "string",
                                    "description": "defines "
                                }
                            }
                        }
                    }
                }
            }
        ]
    }
}