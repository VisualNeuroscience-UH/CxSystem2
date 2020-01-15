var req_simulate = function () {
    $.ajax({
        type: 'POST',
        url: 'simulate',
        headers: {
            'Authorization': 'Basic ' + session_token
        },
        data: JSON.stringify({
            'anatomy': {
                "params": JSON.parse(JSON.stringify(params_editor.getValue())
                    .replace(/\+/g, encodeURIComponent('+'))
                    .replace(/&/g, encodeURIComponent('&'))
                    .replace(/#/g, encodeURIComponent('#'))),
                "IN": JSON.parse(JSON.stringify(inputs_editor.getValue())
                    .replace(/\+/g, encodeURIComponent('+'))
                    .replace(/&/g, encodeURIComponent('&'))
                    .replace(/#/g, encodeURIComponent('#'))),
                "G": JSON.parse(JSON.stringify(neurons_editor.getValue())
                    .replace(/\+/g, encodeURIComponent('+'))
                    .replace(/&/g, encodeURIComponent('&'))
                    .replace(/#/g, encodeURIComponent('#'))),
                "S": JSON.parse(JSON.stringify(connections_editor.getValue())
                    .replace(/\+/g, encodeURIComponent('+'))
                    .replace(/&/g, encodeURIComponent('&'))
                    .replace(/#/g, encodeURIComponent('#'))),
            },
            'physiology': JSON.parse(JSON.stringify(physio_editor.getValue())
                .replace(/\+/g, encodeURIComponent('+'))
                .replace(/&/g, encodeURIComponent('&'))
                .replace(/#/g, encodeURIComponent('#'))),
        }),
        beforeSend: function() {
            let params_tmp =  params_editor.getValue()

            $('#simulation_status_texts').append(" [Sent] Request submitted for simulation \"" +params_tmp.simulation_title + "\" <br>");
            var status_text_div = document.getElementById("simulation_status");
            status_text_div.scrollTop = status_text_div.scrollHeight;
                // Swal.fire(
                //        'Simulation Request Submitted',
                //         '',
                //         'success'
                //     )
        },
        success: function (response) {
            if (response['authorized'] != null && response['authorized'] !== 'true') {
                authenticate(req_simulate);
            } else {
                Swal.fire(
                    {
                        title: JSON.parse(response)["response"],
                    })
            }
        }
    });
    return false;
};

var req_download_workspace = function () {
    $.ajax({
        type: 'POST',
        url: 'download_workspace',
        headers: {
            'Authorization': 'Basic ' + session_token
        },
        beforeSend: function () {
            Swal.fire(
                {
                    title: 'Compressing and downloading the workspace, this might take a few minutes ...',
                    showConfirmButton: false,
                    timer: 1500
                }
            );
        },
        success: function (response) {
            if (response['authorized'] != null && response['authorized'] !== 'true') {
                authenticate(req_download_workspace);
            } else {
                var r = response.substring(2, response.length - 1);
                var typedArray = new Uint8Array(r.match(/[\da-f]{2}/gi).map(function (h) {
                    return parseInt(h, 16)
                }));
                download(typedArray, 'workspace.tar.gz', 'application/gzip');
            }
        }
    });
    return false;
};

var req_download_files = function () {
    Swal.fire({
        title: 'Enter list of the files (separated by comma)',
        input: 'text',
        inputAttributes: {
            autocapitalize: 'off'
        },
        showCancelButton: true,
        confirmButtonText: 'Look up',
        showLoaderOnConfirm: true,
        preConfirm: (login) => {
            $.ajax({
                type: 'POST',
                url: 'download_files',
                headers: {
                    'Authorization': 'Basic ' + session_token
                },
                data: {
                    'files': login
                },
                success: function (response) {
                    if (response['authorized'] != null && response['authorized'] !== 'true') {
                        authenticate(req_download_files);
                    } else {
                        try {
                            Swal.fire(
                                {
                                    title: JSON.parse(response)["response"],
                                })
                        } catch (err) {
                            var r = response.substring(2, response.length - 1);
                            var typedArray = new Uint8Array(r.match(/[\da-f]{2}/gi).map(function (h) {
                                return parseInt(h, 16)
                            }));
                            download(typedArray, 'collected_files.tar.gz', 'application/gzip');
                        }
                    }
                }
            });

        },
        allowOutsideClick: false
    })
};

var req_lsworkspace = function () {
    $.ajax({
        type: 'POST',
        url: 'ls_workspace',
        headers: {
            'Authorization': 'Basic ' + session_token
        },
        success: function (response) {
            if (response['authorized'] != null && response['authorized'] !== 'true') {
                authenticate(req_lsworkspace);
            } else {
                // alert(response);
                Swal.fire(
                    {
                        title: "Tree Remote Folder Structure",
                        html: '<pre style="text-align: left !important;">' + response + '<pre>',
                        width: '80%'
                    })
            }
        }
    });
    return false;
};

var simulation_results = [];
var req_simstatus = function () {
    $.ajax({
        type: 'POST',
        url: 'simstatus',
        headers: {
            'Authorization': 'Basic ' + session_token
        },
        success: function (response) {
            if (response['authorized'] != null && response['authorized'] !== 'true') {
                authenticate(req_simoutput);
            } else {
                let splitted = response.split('&');
                splitted.forEach(
                    function(element){
                      if (!simulation_results.includes(element)) {
                            simulation_results.push(element);
                            $('#simulation_status_texts').append(element, "<br> ");
                            var status_text_div = document.getElementById("simulation_status");
                            status_text_div.scrollTop = status_text_div.scrollHeight;
                      }
                    });
            }
        }
    });
    return false;
};

window.setInterval(function(){
    req_simstatus();
}, 10000);

$(document).ready( function(){
        $('#simulation_status_texts').append("<br>");  // add two blank lines for visibility
        req_simstatus();
    }
);

var req_simoutput = function () {
    $.ajax({
        type: 'POST',
        url: 'simoutput',
        headers: {
            'Authorization': 'Basic ' + session_token
        },
        success: function (response) {
            if (response['authorized'] != null && response['authorized'] !== 'true') {
                authenticate(req_simoutput);
            } else {
                // alert(response);
                Swal.fire(
                    {
                        title: "Output of the Simulation (last 30 lines)",
                        html: '<pre style="text-align: left;">' + response + '<pre>',
                        width: '80%'
                    })
            }
        }
    });
    return false;
};


var req_delete = function () {
    $.ajax({
        type: 'POST',
        url: 'delete',
        headers: {
            'Authorization': 'Basic ' + session_token
        },
        success: function (response) {
            if (response['authorized'] != null && response['authorized'] !== 'true') {
                authenticate(req_delete);
            } else {
                Swal.fire(
                    {
                        title: JSON.parse(response)["response"],
                    })
            }
        }
    });
    return false;
};


var req_visualize = function () {
    $.ajax({
        type: 'POST',
        url: 'visualize',
        data: JSON.stringify(
            {
                "folder": $("input[name=simulation_name").val(),
                "timestamp": $("input[name=timestamp_suffix").val(),
                "sampling": $("input[name=sampling_rate").val()
            }
        ),
        headers: {
            'Authorization': 'Basic ' + session_token
        },
        beforeSend: function () {
            Swal.fire(
                {
                    title: 'Generating and downloading the pdf, please wait ...',
                    showConfirmButton: false,
                    timer: 3000
                }
            );
        },
        success: function (response) {
            if (response['authorized'] != null && response['authorized'] !== 'true') {
                authenticate(req_visualize);
            } else {
                try {
                    Swal.fire(
                        {
                            title: JSON.parse(response)["response"],
                        })
                } catch (err) {
                    var r = response.substring(2, response.length - 1);
                    var typedArray = new Uint8Array(r.match(/[\da-f]{2}/gi).map(function (h) {
                        return parseInt(h, 16)
                    }));
                    var blob = new Blob([typedArray], {
                        type: 'application/pdf'
                    });
                    var file = window.URL.createObjectURL(blob);
                    document.querySelector("iframe").src = file;
                    $("iframe").show();
                    // download(typedArray, 'output.pdf', 'application/pdf');

                }
            }
        }
    });
    return false;
};


function download(content, filename, contentType) {
    if (!contentType) contentType = 'application/octet-stream';
    var a = document.createElement('a');
    var blob = new Blob([content], {'type': contentType});
    a.href = window.URL.createObjectURL(blob);
    a.download = filename;
    a.click();
}

function double_check_delete() {
    Swal.fire({
        title: 'Are you sure?',
        text: "You won't be able to revert this!",
        icon: 'warning',
        showCancelButton: true,
        confirmButtonColor: '#3085d6',
        cancelButtonColor: '#d33',
        confirmButtonText: 'Yes, delete everything!'
    }).then((result) => {
        if (result.value) {
            req_delete();
        }
    })
}

$(function () {
    $('#visualize_form').submit(req_visualize);
});
