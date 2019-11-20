$(function () {
    $('#simulation_form').submit(function () {
        $.ajax({
            type: 'POST',
            url: 'simulate',
            headers: {
                'Authorization': 'Basic '+ session_token
            },
            data: JSON.stringify({
                'anatomy': {
                    "params": JSON.parse(JSON.stringify( params_editor.getValue())
                            .replace(/\+/g, encodeURIComponent('+'))
                            .replace(/&/g, encodeURIComponent('&'))
                            .replace(/#/g, encodeURIComponent('#'))),
                    "IN": JSON.parse(JSON.stringify( inputs_editor.getValue())
                            .replace(/\+/g, encodeURIComponent('+'))
                            .replace(/&/g, encodeURIComponent('&'))
                            .replace(/#/g, encodeURIComponent('#'))),
                    "G": JSON.parse(JSON.stringify( neurons_editor.getValue())
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
            success: function(response){
                var res = JSON.parse(response);
                console.log(res);
                if (res['authorized'] !== 'true'){
                    authenticate();
                }
                else{
                    Swal.fire(
                      res["response"],
                      '',
                      'success'
                    );
                }
            },
            error: function(response){
                var res = JSON.parse(response);
                if (res['authorized'] !== 'true'){
                    authenticate();
                }
                else{
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


