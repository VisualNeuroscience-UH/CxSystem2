$(function () {
    $('#simulation_form').submit(function () {
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
                var res = JSON.parse(response);
                console.log(res);
                if (res['authorized'] !== 'true') {
                    authenticate();
                } else {
                    Swal.fire(
                        res["response"],
                        '',
                        'success'
                    );
                }
            },
            error: function (response) {
                var res = JSON.parse(response);
                if (res['authorized'] !== 'true') {
                    authenticate();
                } else {
                    Swal.fire(
                        res["response"],
                        '',
                        'error'
                    );
                }
            }
        });
        return false;
    });
});


$(function () {
    $('#downloader_form').submit(function () {
        $.ajax({
            type: 'POST',
            url: 'download_workspace',
            headers: {
                'Authorization': 'Basic ' + session_token
            },
            success: function (response) {
                var r = response.substring(2, response.length - 1);
                var typedArray = new Uint8Array(r.match(/[\da-f]{2}/gi).map(function (h) {
                    return parseInt(h, 16)
                }));
                download(typedArray, filename, 'application/gzip');
            },
            error: function (response) {
                var res = JSON.parse(response);
                if (res['authorized'] !== 'true') {
                    authenticate();
                } else {
                    Swal.fire(
                        res["response"],
                        '',
                        'error'
                    );
                }
            }
        });
        return false;
    });
});


function download(content, filename, contentType) {
    if (!contentType) contentType = 'application/octet-stream';
    var a = document.createElement('a');
    var blob = new Blob([content], {'type': contentType});
    a.href = window.URL.createObjectURL(blob);
    a.download = filename;
    a.click();
}


