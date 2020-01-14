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


var imported_data;


function load_example(example_name) {
    request_data = {};
    request_data[example_name] = 'anatomy';
    $.ajax({
        type: 'POST',
        url: 'load_example',
        headers: {
            'Authorization': 'Basic ' + session_token
        },
        dataType: "json",
        data: request_data,
        success: function (anatomy) {
            // console.log(anatomy);
            if (anatomy['authorized'] !== 'true') {
                authenticate();
                return;
            }
            for (var key in anatomy) {
                switch (key) {
                    case "params":
                        data = anatomy['params'];
                        params_editor.setValue(data);
                        break;
                    case "IN":
                        data = anatomy.IN;
                        inputs_editor.setValue(data);
                        break;
                    case "G":
                        data = anatomy.G;
                        neurons_editor.setValue(data);
                        break;
                    case "S":
                        data = anatomy['S'];
                        connections_editor.setValue(data);
                        break;
                }
            }
        }
    });

    request_data = {};
    request_data[example_name] = 'physiology'
    $.ajax({
        type: 'POST',
        url: 'load_example',
        headers: {
            'Authorization': 'Basic ' + session_token,
        },
        data: request_data,
        dataType: "json",
        success: function (physio) {
            // console.log('phys',physio);
            if (physio['authorized'] !== 'true') {
                authenticate();
                return;
            }
            physio_editor.setValue(physio['physio_data']);
            Swal.fire(
                'Example Loaded',
                '',
                'success'
            );
        }
    });
    $("button[data-for-tab='1']").click();
}


function readSingleFile(e) {
    var file = e.target.files[0];
    if (!file) {
        return;
    }
    var reader = new FileReader();
    reader.onload = function (e) {
        imported_data = JSON.parse(e.target.result);
        if (Object.keys(imported_data).includes('physio_data')) { // this means it's a physio file
            data = imported_data['physio_data'];
            physio_editor.setValue(data);
            Swal.fire(
                'Physiology Configuration Loaded',
                '',
                'success'
            );
        } else { // this means it's a anatomy file
            for (var key in imported_data) {
                let data;
                switch (key) {
                    case "params":
                        data = imported_data['params'];
                        params_editor.setValue(data);
                        break;
                    case "IN":
                        data = imported_data.IN;
                        inputs_editor.setValue(data);
                        break;
                    case "G":
                        data = imported_data.G;
                        neurons_editor.setValue(data);
                        break;
                    case "S":
                        data = imported_data['S'];
                        connections_editor.setValue(data);
                        break;
                }
            }
            Swal.fire(
                'Anatomy/System Configuration Loaded',
                '',
                'success'
            );
        }

    };
    reader.readAsText(file);
}

document.getElementById('file-input').addEventListener('change', readSingleFile, false);

$(document).ready(function () {
    $('#sign_up').click(function () {
        alert('Sign new href executed.');
    });
});

function downloadanatomy() {
    var editors_data = {
        "params": params_editor.getValue(),
        "IN": inputs_editor.getValue(),
        "G": neurons_editor.getValue(),
        "S": connections_editor.getValue()
    };
    var data = "text/json;charset=utf-8," + encodeURIComponent(JSON.stringify(editors_data));
    var a = document.createElement('a');
    a.href = 'data:' + data;
    a.download = 'exported_anatomy.json';
    a.innerHTML = 'download JSON';
    a.style = "display: none";
    a.id = "data_downloader";

    var container = document.getElementById('export_config_container');
    container.appendChild(a);
    document.getElementById('data_downloader').click();
    document.getElementById('data_downloader').remove();
}


function downloadphysiology() {
    var editors_data = {'physio_data': physio_editor.getValue()};
    var data = "text/json;charset=utf-8," + encodeURIComponent(JSON.stringify(editors_data));
    var a = document.createElement('a');
    a.href = 'data:' + data;
    a.download = 'exported_physiology.json';
    a.innerHTML = 'download JSON';
    a.style = "display: none";
    a.id = "physio_downloader";

    var container = document.getElementById('export_config_container');
    container.appendChild(a);
    document.getElementById('physio_downloader').click();
}

// This is the starting value for the editor
// We will use this to seed the initial editor
// and to provide a "Restore to Default" button.
var starting_value = [
    {
        runtime: 1000,
        device: "Cpp",
        sys_mode: "Local",
        scale: 1,
        grid_radius: "1000*um",
        min_distance: "1*um",
        init_vms: true,
        import_connections_from: "/opt3/CX_Output/sivanni/brian_data_20161028_142108.gz",
        load_positions_only: true,
        benchmark: false,
        save_input_video: true,
        multidimension_array_run: false,
        number_of_process: 20,
        default_clock: 10,
        trials_per_config: 1,
        profiling: false
    }
];

// Initialize the editor
var params_editor = new JSONEditor(document.getElementById('params_holder'), {
    // Enable fetching schemas via ajax
    ajax: true,
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


var starting_value_inputs = [
    {
        idx: 1,
        type: "VPM",
        number_of_neurons: 60,
        radius: "92*um",
        spike_times: "[0.5]*second",
        net_center: "--",
        monitors: "[Sp]",
    }
];

var inputs_editor = new JSONEditor(document.getElementById('inputs_holder'), {
    // Enable fetching schemas via ajax
    ajax: true,
    schema: inputs_schema,
    // Seed the form with a starting value
    startval: starting_value_inputs,
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
    schema: connections_schema,
    // Seed the form with a starting value
    startval: starting_value3,
    // Disable additional properties
    no_additional_properties: true,
    // Require all properties by default
    required_by_default: true,
    disable_properties: true,
    disable_collapse: true,

});

var starting_value4 = [
    {"Variable": "calcium_concentration", "Value": "1", "Comment": ""},
    {"Variable": "EE_weights_gain", "Value": "0.5", "Comment": ""},
    {"Variable": "EI_weights_gain", "Value": "0.5", "Comment": ""},
    {
        "Variable": "_weights",
        "Key-Value": [{
            "Key": "w_TC_E-E_connections",
            "Value": "(0.7 * EE_weights_gain) * nS",
            "Comment": "#Cruikshank et al 2007, nature neuroscience"
        }]
    }
];

var physio_editor = new JSONEditor(document.getElementById('physio_holder'), {
    // Enable fetching schemas via ajax
    ajax: true,
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
                if (!/^(\[Sp\])?(\s)?(\[St\](vm|test)\[rec\]?\([0-9]+\-[0-9]+\-[0-9]+\))*$|^(\[St\](vm|test)\[rec\]?\([0-9]+\-[0-9]+\-[0-9]+\))*(\s\[Sp\])?$/.test(value)) {
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
        // if (schema_variable == 'monitors'){

        // }
        // else if ()

    }
    return errors;
});


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


inputs_editor.on('change', function () {
    // Get an array of errors from the validator
    var errors = inputs_editor.validate();

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


function clearBox(elementID) {
    document.getElementById(elementID).innerHTML = "";
}




dragElement(document.getElementById("simulation_status"));

function dragElement(elmnt) {
  var pos1 = 0, pos2 = 0, pos3 = 0, pos4 = 0;
  if (document.getElementById(elmnt.id + "header")) {
    /* if present, the header is where you move the DIV from:*/
    document.getElementById(elmnt.id + "header").onmousedown = dragMouseDown;
  } else {
    /* otherwise, move the DIV from anywhere inside the DIV:*/
    elmnt.onmousedown = dragMouseDown;
  }

  function dragMouseDown(e) {
    e = e || window.event;
    e.preventDefault();
    // get the mouse cursor position at startup:
    pos3 = e.clientX;
    pos4 = e.clientY;
    document.onmouseup = closeDragElement;
    // call a function whenever the cursor moves:
    document.onmousemove = elementDrag;
  }

  function elementDrag(e) {
    e = e || window.event;
    e.preventDefault();
    // calculate the new cursor position:
    pos1 = pos3 - e.clientX;
    pos2 = pos4 - e.clientY;
    pos3 = e.clientX;
    pos4 = e.clientY;
    // set the element's new position:
    elmnt.style.top = (elmnt.offsetTop - pos2) + "px";
    elmnt.style.left = (elmnt.offsetLeft - pos1) + "px";
  }

  function closeDragElement() {
    /* stop moving when mouse button is released:*/
    document.onmouseup = null;
    document.onmousemove = null;
  }
}
