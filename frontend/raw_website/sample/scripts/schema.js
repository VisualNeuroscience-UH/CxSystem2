main_schema = {
    "title": "Person",
    "type": "object",
    "id": "person",
    "properties": {
        "name": {
            "type": "string",
            "description": "First and Last name",
            "minLength": 4
        },
        "age": {
            "type": "integer",
            "default": 21,
            "minimum": 18,
            "maximum": 99
        },
        "gender": {
            "type": "string",
            "enum": [
                "male",
                "female"
            ]
        },
        "location": {
            "type": "object",
            "title": "Location",
            "properties": {
                "city": {
                    "type": "string"
                },
                "state": {
                    "type": "string"
                },
                "citystate": {
                    "type": "string",
                    "description": "This is generated automatically from the previous two fields",
                    "template": "{{city}}, {{state}}",
                    "watch": {
                        "city": "person.location.city",
                        "state": "person.location.state"
                    }
                }
            }
        },
        "pets": {
            "type": "array",
            "format": "table",
            "title": "Pets",
            "uniqueItems": true,
            "items": {
                "type": "object",
                "properties": {
                    "type": {
                        "type": "string",
                        "enum": [
                            "cat",
                            "dog",
                            "bird",
                            "reptile",
                            "other"
                        ],
                        "default": "dog"
                    },
                    "name": {
                        "type": "string"
                    },
                    "fixed": {
                        "type": "boolean",
                        "title": "spayed / neutered"
                    }
                }
            }
        }
    }
};

runtime_params_schema = {
    "title": "Params",
    "type": "object",
    "id": "params",
    "properties": {
        "runtime": {
            "type": "integer",
            "description": "Duration of simulation in miliseconds",
            "default": 1000,
            "minimum": 10,
            "maximum": 30000,
        },
        "device": {
            "type": "string",
            "description": "Brian simulation device type",
            "enum": ["C++", "Python", "GeNN"]
        },
        "sys_mode": {
            "type": "string",
            "description": "System mode: local means ... , expanded means ... ",
            "enum": ["Local", "Expanded"]
        },
        "scale": {
            "type": "integer",
            "description": "Defines how much the network is scaled",
            "default": 1,
            "minimum": 1,
            "maximum": 10,
        },
        "grid_radius": {
            "type": "integer",
            "description": "Defines grid radius in micrometer (um)",
            "default": 1000,
            "minimum": 10,
            "maximum": 10000,
        },
        "min_distance": {
            "type": "integer",
            "description": "Defines minimum distance between the neurons in micrometer (um)",
            "default": 1,
            "minimum": 1,
            "maximum": 100,
        },

        "output_filename": {
            "type": "string",
            "description": "relative path to the output filename",
            "default": "./results/output.gz"
        },
        "export_simdata_filename": {
            "type": "string",
            "description": "relative path of the filename to save the output connection information ",
            "default": "./simdata/data.gz"
        },
        "import_simdata_filename": {
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
            "type": "integer",
            "description": "Defines simulation clock in micro-seconds (us)",
            "default": 10,
            "minimum": 1,
            "maximum": 1000,
        },
        "trials_per_config": {
            "type": "integer",
            "description": "Defines how many times each simulation should be repeated",
            "default": 1,
            "minimum": 1,
            "maximum": 20,
        },
        "init_vms": {
            "type": "boolean",
            "description": "If checked, the initial membrane voltages will be randomized",
            "format": "checkbox"
        },
        "load_positions_only": {
            "type": "boolean",
            "description": "If checked, only the neuron positions will be loaded from the simulation data file (and connection info will not be loaded)",
            "format": "checkbox"
        },
        
        "benchmark": {
            "type": "boolean",
            "description": "If checked, the simulation will be benchamrked",
            "format": "checkbox"
        },
        "save_generated_input_video": {
            "type": "boolean",
            "description": "If checked, the generated video for input will be saved",
            "format": "checkbox"
        },
        "multidimension_array_run": {
            "type": "boolean",
            "description": "If checked, the array runs will be considered as a multi-dimentional simulations",
            "format": "checkbox"
        }
    }
};

