function setupTabs() {
    document.querySelectorAll(".tabs__button").forEach(button => {
        button.addEventListener("click", () => {
            const topBar = button.parentElement;
            const tabsContainer = topBar.nextElementSibling;
            const tabNumber = button.dataset.forTab;
            const tabToActivate = tabsContainer.querySelector(`.tabs__content[data-tab="${tabNumber}"]`);

            topBar.querySelectorAll('.tabs__button').forEach(button => {
                button.classList.remove("tabs__button--active");
            });

            tabsContainer.querySelectorAll('.tabs__content').forEach(tab => {
                tab.classList.remove("tabs__content--active");
            });

            tabToActivate.classList.add("tabs__content--active");
            button.classList.add("tabs__button--active");
        })
    })
}

function add_to_overview_tab(inp_data) {
    var overview = document.querySelector('.tabs__content[data-tab="1"]');
    overview.innerHTML = "<p>" + inp_data + "</p>" + overview.innerHTML;
}

document.addEventListener("DOMContentLoaded", () => {
    setupTabs();

    document.querySelectorAll(".tabs__topbar").forEach(tabsContainer => {
        tabsContainer.querySelector(".tabs__button").click();
    })
});

$('.tabs__button').click(function () {
    $(this).addClass("tabs__button--active");
});


function readSingleFile(e) {
    var file = e.target.files[0];
    if (!file) {
      return;
    }
    var reader = new FileReader();
    reader.onload = function(e) {
      var contents = e.target.result;
      displayContents(contents);
    };
    reader.readAsText(file);
  }
  document.getElementById('file-input').addEventListener('change', readSingleFile, false);

  $(document).ready(function(){
    $('#sign_up').click(function(){
        alert('Sign new href executed.');
    });
});

function downloadanatomy() {
    var editors_data = {
        "params": params_editor.getValue(),
        "neurongroups": neurons_editor.getValue(),
        "connections": connections_editor.getValue()
    };
    var data = "text/json;charset=utf-8," + encodeURIComponent(JSON.stringify(editors_data));
    var a = document.createElement('a');
    a.href = 'data:' + data;
    a.download = 'data.json';
    a.innerHTML = 'download JSON';
    a.style = "display: none";
    a.id = "data_downloader";

    var container = document.getElementById('container');
    container.appendChild(a);
    document.getElementById('data_downloader').click();
}


function downloadphysiology() {
    var editors_data = physio_editor.getValue();
    var data = "text/json;charset=utf-8," + encodeURIComponent(JSON.stringify(editors_data));
    var a = document.createElement('a');
    a.href = 'data:' + data;
    a.download = 'data.json';
    a.innerHTML = 'download JSON';
    a.style = "display: none";
    a.id = "physio_downloader";

    var container = document.getElementById('container');
    container.appendChild(a);
    document.getElementById('physio_downloader').click();
}

// This is the starting value for the editor
// We will use this to seed the initial editor 
// and to provide a "Restore to Default" button.
var starting_value = [
    {
        runtime: 1000,
        device: "C++",
        sys_mode: "Local",
        scale: 1,
        grid_radius: "1000*um",
        min_distance: "1*um",
        init_vms: true,
        output_filename: "./results/output.gz",
        export_simdata_filename: "/opt3/CX_Output/brian_data.gz",
        import_simdata_filename: "/opt3/CX_Output/sivanni/brian_data_20161028_142108.gz",
        load_positions_only: true,
        benchmark: false,
        save_generated_input_video: true,
        multidimension_array_run: false,
        number_of_process: 20,
        default_clock: 10,
        trials_per_config: 1
    }
];

// Initialize the editor
var params_editor = new JSONEditor(document.getElementById('params_holder'), {
    // Enable fetching schemas via ajax
    ajax: true,

    // The schema for the editor
    // schema: {
    // $ref: "person.json",
    // format: "grid"
    // },


    schema: runtime_params_schema,

    // Seed the form with a starting value
    startval: starting_value,

    // Disable additional properties
    no_additional_properties: true,

    // Require all properties by default
    required_by_default: true,
    disable_properties: true,
    disable_collapse: true
});



var starting_value2 = [
    {
        idx: 1,
        number_of_neurons: 300,
        neuron_type: "BC",
        layer_idx: 4,
        net_center: "5+0j",
        monitors: "[Sp] [St]vm[rec](10-299-20)",
        noise_sigma: "10*mV"
    }
];

var neurons_editor = new JSONEditor(document.getElementById('neurons_holder'), {
    // Enable fetching schemas via ajax
    ajax: true,

    // The schema for the editor
    // schema: {
    // $ref: "person.json",
    // format: "grid"
    // },


    schema: neurons_schema,

    // Seed the form with a starting value
    startval: starting_value2,

    // Disable additional properties
    no_additional_properties: true,

    // Require all properties by default
    required_by_default: true,
    disable_properties: true,
    disable_collapse: true
});


var starting_value3 = [
    {
        idx: 1,
        number_of_neurons: 300,
        neuron_type: "BC",
        layer_idx: 4,
        net_center: "5+0j",
        monitors: "[Sp] [St]vm[rec](10-299-20)",
        noise_sigma: "10*mV"
    }
];

var connections_editor = new JSONEditor(document.getElementById('connections_holder'), {
    // Enable fetching schemas via ajax
    ajax: true,

    // The schema for the editor
    // schema: {
    // $ref: "person.json",
    // format: "grid"
    // },


    schema: connections_schema,

    // Seed the form with a starting value
    startval: starting_value3,

    // Disable additional properties
    no_additional_properties: true,

    // Require all properties by default
    required_by_default: true,
    disable_properties: true,
    disable_collapse: true
});

var starting_value4 = [
    {"Variable":"calcium_concentration","Value":"1","Comment":""},
    {"Variable":"EE_weights_gain","Value":"0.5","Comment":""},
    {"Variable":"EI_weights_gain","Value":"0.5","Comment":""},
    {"Variable":"_weights","Key-Value":[{"key":"w_TC_E-E_connections","value":"(0.7 * EE_weights_gain) * nS","Comment":"#Cruikshank et al 2007, nature neuroscience"}]}
];

var physio_editor = new JSONEditor(document.getElementById('physio_holder'), {
    // Enable fetching schemas via ajax
    ajax: true,

    // The schema for the editor
    // schema: {
    // $ref: "person.json",
    // format: "grid"
    // },


    schema: physio_schema,

    // Seed the form with a starting value
    startval: starting_value4,

    // Disable additional properties
    no_additional_properties: true,

    // Require all properties by default
    required_by_default: true,
    disable_properties: true,
    disable_collapse: true
});



JSONEditor.defaults.custom_validators.push(function (schema, value, path) {
    var errors = [];
    if (schema.format === "text") {
        var path_ = path.split('.');
        var path_last_idx = path_.length - 1;
        var schema_variable = path_[path_last_idx];
        switch (schema_variable) {
            case "monitors":
                if (!/^(\[Sp\]\s)?(\[St\](vm|test)\[rec\]?\([0-9]+\-[0-9]+\-[0-9]+\))*$|^(\[St\](vm|test)\[rec\]?\([0-9]+\-[0-9]+\-[0-9]+\))*(\s\[Sp\])?$/.test(value)) {
                    errors.push({
                        path: path,
                        property: 'format',
                        message: 'Monitor format not correct'
                    });
                }
                break;
            case "post_syn_idx":
                if (!/^[0-9]{1,2}(\[C\]([1-6]|0(s|a|b|ab)))?$/.test(value)) {
                    errors.push({
                        path: path,
                        property: 'format',
                        message: 'post_syn_idx format not correct'
                    });
                }
                break;
            case "p":
                if (!/^(0?(\.[0-9]*)?|\.[0-9]+)$/.test(value)) { // regex for float number under 1 
                    errors.push({
                        path: path,
                        property: 'format',
                        message: 'p format not correct'
                    });
                }
                break;
            case "n":
                if (!/^([0-9]{1,2}|[0-9]\+[0-9])$/.test(value)) { // regex for float number under 1 
                    errors.push({
                        path: path,
                        property: 'format',
                        message: 'n format not correct'
                    });
                }
                break;
            case "load_connection":
                    if (!/^[1,0](<\-\-|\-\->)?$/.test(value)) { // regex for float number under 1 
                        errors.push({
                            path: path,
                            property: 'format',
                            message: 'load_connection format not correct'
                        });
                    }
                break;
            case "save_connection":
                    if (!/^[1,0](<\-\-|\-\->)?$/.test(value)) { // regex for float number under 1 
                        errors.push({
                            path: path,
                            property: 'format',
                            message: 'save_connection format not correct'
                        });
                    }
                break;
        }
    }
    return errors;
});


// // Hook up the submit button to log to the console
// document.getElementById('submit').addEventListener('click', function () {
//     // Get the value from the editor
//     console.log(editor.getValue());
// });

// // Hook up the Restore to Default button
// document.getElementById('restore').addEventListener('click', function () {
//     editor.setValue(starting_value);
// });

// Hook up the validation indicator to update its 
// status whenever the editor changes
params_editor.on('change', function () {
    // Get an array of errors from the validator
    var errors = params_editor.validate();

    var indicator = document.getElementById('valid_indicator');

    // Not valid
    if (errors.length) {
        indicator.className = 'label alert';
        indicator.textContent = 'not valid';
    }
    // Valid
    else {
        indicator.className = 'label success';
        indicator.textContent = 'valid';
    }
});

neurons_editor.on('change', function () {
    // Get an array of errors from the validator
    var errors = neurons_editor.validate();

    var indicator = document.getElementById('valid_indicator');

    // Not valid
    if (errors.length) {
        indicator.className = 'label alert';
        indicator.textContent = 'not valid';
    }
    // Valid
    else {
        indicator.className = 'label success';
        indicator.textContent = 'valid';
    }
});


connections_editor.on('change', function () {
    // Get an array of errors from the validator
    var errors = connections_editor.validate();

    var indicator = document.getElementById('valid_indicator');

    // Not valid
    if (errors.length) {
        indicator.className = 'label alert';
        indicator.textContent = 'not valid';
    }
    // Valid
    else {
        indicator.className = 'label success';
        indicator.textContent = 'valid';
    }
});


physio_editor.on('change', function () {
    // Get an array of errors from the validator
    var errors = physio_editor.validate();

    var indicator = document.getElementById('valid_indicator');

    // Not valid
    if (errors.length) {
        indicator.className = 'label alert';
        indicator.textContent = 'not valid';
    }
    // Valid
    else {
        indicator.className = 'label success';
        indicator.textContent = 'valid';
    }
});




