$(function () {
    $('form').submit(function () {
        Swal.fire(
          'Simulation Started',
          '',
          'success'
        );
        console.log(JSON.stringify( params_editor.getValue())
                            .replace(/\+/g, encodeURIComponent('+'))
                            .replace(/&/g, encodeURIComponent('&')));
        $.ajax({
            type: 'POST',
            url: 'simulate',
            data: JSON.stringify({
                'anatomy': {
                    "params": JSON.parse(JSON.stringify( params_editor.getValue())
                            .replace(/\+/g, encodeURIComponent('+'))
                            .replace(/&/g, encodeURIComponent('&'))),
                    "IN": JSON.parse(JSON.stringify( inputs_editor.getValue())
                            .replace(/\+/g, encodeURIComponent('+'))
                            .replace(/&/g, encodeURIComponent('&'))),
                    "G": JSON.parse(JSON.stringify( neurons_editor.getValue())
                            .replace(/\+/g, encodeURIComponent('+'))
                            .replace(/&/g, encodeURIComponent('&'))),
                    "S": JSON.parse(JSON.stringify(connections_editor.getValue())
                            .replace(/\+/g, encodeURIComponent('+'))
                            .replace(/&/g, encodeURIComponent('&')))
                },
                'physiology': physio_editor.getValue()
            })
        });
        return false;
    });
})