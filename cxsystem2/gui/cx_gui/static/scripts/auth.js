let client = new jso.JSO({
	providerID: "HBP",
	client_id: "f34780ff-7842-499c-8440-5777c28e360d",
	redirect_uri: "https://127.0.0.1:4443", // The URL where you is redirected back, and where you perform run the callback() function.
	authorization: "https://services.humanbrainproject.eu/oidc/authorize",
})


function authenticate() {
  try {
    client.callback();
  } catch (e) {
    console.warn('Issue decoding the token');
  }

const USER_API = 'https://services.humanbrainproject.eu/idm/v1/api/user/me';
var authorization = client.getToken();

console.log(authorization);

authorization.then((session) => {
var header = {'headers' : {Authorization: 'Bearer ' + session.access_token}};
// document.getElementById("hbp-token").innerHTML = session.access_token;

console.log(header);

$.ajax({
    url: USER_API,
    headers: {
        'Authorization':'Bearer ' + session.access_token,
        'Content-Type':'application/json'
    },
    method: 'GET',
    success: function(data){
	    console.log(data.id);
        document.getElementById("hbp-user-data").innerHTML = JSON.stringify(data);
	    document.getElementById("hbp-user-id").innerHTML = data.id;
    }
});
});
	 return authorization;
}


