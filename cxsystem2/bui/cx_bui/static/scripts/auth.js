var hbp_auth_response;
var session_token = '';

function authenticate(callback) {

    try {
        client.callback();
    } catch (e) {
        console.warn('Issue decoding the token');
    }

    const USER_API = 'https://services.humanbrainproject.eu/idm/v1/api/user/me';
    var authorization = client.getToken();

    authorization.then((session) => {
        var header = {'headers': {Authorization: 'Bearer ' + session.access_token}};

        session_token = session.access_token;

        $.ajax({
            url: USER_API,
            headers: {
                'Authorization': 'Bearer ' + session.access_token,
                'Content-Type': 'application/json'
            },
            method: 'GET',
            success: function (data) {
                hbp_auth_response = data;
                document.getElementById('welcome').innerHTML = "Welcome " + data.givenName + "  <img id=\"imagebox\" width=\"30\" height=\"30\" style='margin-left:5px;'/>";
                document.getElementById('imagebox').src = data.picture;

                // console.log(data);

            }
        });
    });
    if (callback != null){
        callback();
    }
    return authorization;
}


