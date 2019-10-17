runtime_params_schema = {
    "title": "SimulationConfig",  // Params->simulation_config (let's try to avoid ambiguity) -HH
    "type": "object",
    "id": "params",
    "properties": {
        "runtime": {
            "type": "integer",
            "description": "Duration of simulation in milliseconds (ms)",
            "default": 1000,
            "minimum": 10,
            "maximum": 30000,
        },
        "device": {
            "type": "string",
            "description": "Sets the device for Brian2 code generation",
            "enum": ["C++", "Python", "GeNN"]
        },
        // Leave this out for now as we don't use or test it actively -HH
        //"sys_mode": {
        //    "type": "string",
        //    "description": "System mode: local means ... , expanded means ... ",
        //    "enum": ["Local", "Expanded"]
        //},
        // Leave this out for now as we don't use or test it actively -HH
        // "scale": {
        //    "type": "integer",
        //    "description": "Defines how much the network is scaled",
        //    "default": 1,
        //    "minimum": 1,
        //    "maximum": 10,
        //},
        "grid_radius": {
            "type": "integer",
            "description": "Sets the half-width of the 2D square grid where neurons are placed (in micrometers, µm)",
            "default": 1000,
            "minimum": 10,
            "maximum": 10000,
        },
        "min_distance": {
            "type": "integer",
            "description": "Sets the minimum distance between neurons in micrometers (µm)",
            "default": 1,
            "minimum": 1,
            "maximum": 100,
        },

        "output_filename": {
            "type": "string",
            "description": "Sets the relative path to where results are stored",
            "default": "./results/output.gz"
        },
        "export_simdata_filename": {  // TODO: "simdata" is ambiguous -HH
            "type": "string",
            "description": "Sets the relative path to where the network configuration with synaptic weights are stored (export)",
            "default": "./net_configs/connections.gz"
        },
        "import_simdata_filename": {
            "type": "string",
            "description": "Sets the relative path from where the network configuration with synaptic weights are retrieved (import)",
            "default": "./net_configs/connections.gz"
        },
        "number_of_process": {  // TYPO: process -> processes -HH
            "type": "integer",
            "description": "Sets the number of CPU cores to use in parallel",
            "default": 1,
            "minimum": 1,
            "maximum": 32,
        },
        "default_clock": {
            "type": "integer",
            "description": "Sets the simulation timestep in microseconds (µs)",
            "default": 10,
            "minimum": 1,
            "maximum": 1000,
        },
        "trials_per_config": {
            "type": "integer",
            "description": "Sets the number of trials for each set of parameters",
            "default": 1,
            "minimum": 1,
            "maximum": 20,
        },
        "init_vms": {
            "type": "boolean",
            "description": "Randomize initial membrane voltages (between leak reversal and threshold potential)",
            "format": "checkbox"
        },
        "load_positions_only": {
            "type": "boolean",
            "description": "Import neuron positions but randomize connections",
            "format": "checkbox"
        },

        "benchmark": {
            "type": "boolean",
            "description": "Benchmark the simulation using Brian2's profiling tool",
            "format": "checkbox"
        },
        // Leave this out for now as we don't use or test it actively -HH
        //"save_generated_input_video": {
        //    "type": "boolean",
        //    "description": "If checked, the generated video for input will be saved",
        //    "format": "checkbox"
        //},
        "multidimension_array_run": { // TODO - check what this means
            "type": "boolean",
            "description": "Sets whether to run all possible parameter combinations in array run",
            "format": "checkbox"
        }
    }
};

// "IN": {
//     "idx": 0,
//     "path": "./video_input_files/V1_input_layer_.mat",
//     "type": "video",
//     "freq": "190*Hz",
//     "monitors": "[Sp]"
//   },

// The referee for Hokkanen_2019_NeCo insisted that we not use "neuron groups" and 
// we switched to "cell types" in the paper. However, we haven't really discussed how we should call the different levels of
// descriptions we have, so I'm sticking here with the good old "neuron group". -HH
neurons_schema = {
    type: "array",
    title: "NeuronGroups",
    format: "tabs",
    items: {
        title: "NeuronGroup",
        headerTemplate: "Group{{i}} - {{self.neuron_type}}",
        oneOf: [
            {
            "title": "NG",
            "type": "object",
            "id": "ng",
            "properties": {
                "idx": {
                    "type": "integer",
                    "description": "Running index for the neuron group",
                    "default": "{{i}}",
                },
                "number_of_neurons": {
                    "type": "integer",
                    "description": "Sets the number of neurons in the neuron group",
                    "default": 100,
                    "minimum": 1,
                    "maximum": 10000,
                },
                // neuron_type refers to hardcoded types in the CxSystem code.
                // In NeCo setup, only PC and 1 pointlike class is needed. -HH
                "neuron_type": {
                    "type": "string",
                    "description": "Sets the cell class",
                    "enum": ["PC", "BC", "MC", "L1i"]  
                },
                "neuron_subtype": {
                    "type": "string",
                    "description": "Sets the cell type",
                    "enum": ["XXX", "YYY", "ZZZ"]
                },
                "layer_idx": {
                    "type": "string",
                    "description": "Sets the layer where the neuron population is located (L2/3 = 2)",
                    "enum": ["1", "2", "4", "5", "6", 
                    "[2->1]", "[4->1]", "[5->1]", "[6->1]", 
                    "[4->2]", "[5->2]", "[6->2]", 
                    "[5->4]", "[6->4]", 
                    "[6->5]"]
                },
                "net_center": {
                    "type": "string",
                    "description": "Center point of the network in 2D",
                    "default": "0+0j"
                },
                "spike_monitor": {
                    "type": "boolean",
                    "description": "Add a spike monitor",
                    "format": "checkbox"
                },
                "state_monitors": {
                    "type": "string",
                    "format": "text",
                    "description": "Sets the state monitors",
                },                
                "noise_sigma": {
                    "type": "string",
                    "description": "Sets the internal membrane noise (mV)",
                    "default": "0*mV"
                },
                "n_background_inputs": {
                    "type": "integer",
                    "description": "Sets the number of excitatory background inputs",
                    "default": 0
                },
                "n_background_inhibition": {
                    "type": "integer",
                    "description": "Sets the number of inhibitory background inputs",
                    "default": 0
                },                


            }
        },
        {
            "title": "IN",
            "type": "object",
            "id": "ng",
            "properties": {
                "idx": {
                    "type": "integer",
                    "description": "Running index for the input group",
                    "default": "{{i}}",
                },
                // Leave this out for now as we don't use or test it actively -HH
                //"path": { 
                //    "type": "string",
                //    "description": "Defines path to input video",
                //},
                "type": {
                    "type": "string",
                    "description": "Sets the type of input",
                    "enum": ["VPM"]
                },
                "number_of_neurons": {
                    "type": "integer",
                    "description": "Sets the number of neurons in the input group",
                    "default": 100,
                    "minimum": 1,
                    "maximum": 10000,
                },
                "radius": {
                    "type": "string",
                    "description": "Sets the radius of the circle to be stimulated",
                },
                "spike_times": {
                    "type": "string",
                    "description": "Sets the spike times",
                },
                "monitors": {
                    "type": "string",
                    "format": "text",
                    "description": "Sets the monitors of the input group",
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
                "description": "Sets whether the connection is excitatory or inhibitory",
                "enum": ["ge", "gi"]
            },
            "pre_syn_idx": {
                "type": "integer",
                "description": "Sets the presynaptic neuron group index",
                "default": 0,
                "minimum": 0,
                "maximum": 100
            },
            "post_syn_idx": {
                "type": "string",
                "format": "text",
                "description": "Sets the postsynaptic neuron group index",
            },
            "syn_type": {
                "type": "string",
                "description": "Sets whether the synapse has short-term plasticity or not",
                "default": "Fixed",
                "enum": ["Fixed", "Depressing", "Facilitating"]
            },
            "p": {
                "type": "string",
                "description": "Sets the connection probability",
                "format": "text",
            },
            "n": {
                "type": "integer",
                "description": "Sets the number of synapses per connection",
                "format": "text",
            },
            "monitors": {
                "type": "string",
                "format": "text",
                "description": "Sets the monitors",
            },
            "load_connection": {
                "type": "boolean",
                "format": "checkbox",
                "description": "Sets whether the connection will be loaded",
            },
            "save_connection": {
                "type": "boolean",
                "format": "checkbox",
                "description": "Sets whether the connection will be saved",
            },
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
                            "key": {
                                "type": "string",
                                "description": "defines "
                            },
                            "value": {
                                "type": "string",
                                "description": "defines "
                            },
                            "Comment": {
                                "type": "string",
                                "description": "defines "
                            }
                        }
                    }
                },

            }
        }

        ]
    }
}
