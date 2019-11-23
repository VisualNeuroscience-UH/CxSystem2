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
        success: function (response) {
            if (response['authorized'] != null && response['authorized'] !== 'true') {
                authenticate(req_download_workspace);
            } else {
                Swal.fire(
                    'Simulation request sent ...',
                    '',
                    'success'
                );
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
                    title: 'Downloading the workspace, please wait ...',
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
                        width: '80%',
                        content: 'span',
                    })
            }
        }
    });
    return false;
};

var req_simstatus = function () {
    $.ajax({
        type: 'POST',
        url: 'simstatus',
        headers: {
            'Authorization': 'Basic ' + session_token
        },
        success: function (response) {
            if (response['authorized'] != null && response['authorized'] !== 'true') {
                authenticate(req_simstatus);
            } else {
                // alert(response);
                Swal.fire(
                    {
                        title: "Output of the Simulation (last 30 lines)",
                        html: '<pre style="text-align: left;">' + response + '<pre>',
                        width: '80%',
                        content: 'span',
                    })
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

// form submission events:

$(function () {
    $('#lsworkspace_form').submit(req_lsworkspace);
});


$(function () {
    $('#downloader_form').submit(req_download_workspace);
});


$(function () {
    $('#simulation_form').submit(req_simulate);
});

$(function () {
    $('#simstatus_form').submit(req_simstatus);
});

