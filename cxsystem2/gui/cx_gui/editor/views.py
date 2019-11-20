import json
import logging
import multiprocessing
import os
from getpass import getpass
from pathlib import Path
import requests

from django.http import HttpResponse
from django.template import loader
from django.views.decorators.csrf import csrf_exempt

from cxsystem2.core.cxsystem import CxSystem as Cx

logging.getLogger("requests").setLevel(logging.WARNING)


def is_authorized(request):
    if "Authorization" in request.headers.keys():
        session_token = request.headers['Authorization'].split(' ')[1]
        user_api = "https://services.humanbrainproject.eu/idm/v1/api/user/me"
        headers = {"Authorization": 'Bearer ' + session_token}
        reply = requests.get(user_api, headers=headers)
        if reply.ok:
            return True
    print("User is not authorized")
    return False

def index(request):
    is_https = False
    if request.is_secure():
        is_https = True
    # only authenticate if it's running in https
    template = loader.get_template('editor/index.html')
    context = {
        'is_https' : is_https,
    }
    return HttpResponse(template.render(context, request))


def cxspawner(anatomy,
              physiology,
              root_path):
    """
    The function that each spawned process runs and parallel instances of CxSystems are created here.
    :param anatomy:
    :param root_path:
    :param physiology:
    """
    from time import sleep
    sleep(10)
    print(root_path)
    os.chdir(root_path)

    cm = Cx(anatomy, physiology)
    cm.run()


def sanitize_data(received_data):
    received_data = received_data.replace('false', '0')
    received_data = received_data.replace('true', '1')
    received_data = received_data.replace(':null', ':"--"')
    return received_data


# noinspection PyProtectedMember
@csrf_exempt
def simulate(request):
    # There request that we receive here is the following from django_simulation_request.js :
    # data: JSON.stringify({
    #     'anatomy': {
    #         "params": params_editor.getValue(),
    #         "IN": inputs_editor.getValue(),
    #         "G": neurons_editor.getValue(),
    #         "S": connections_editor.getValue()
    #     },
    #     'physio_data': physio_editor.getValue()
    # })
    #
    # However, in the plain text format, so it needs some processing to be formed in a dictionary format usable for cxsystem:
    # our data is sent in the "key" of the request so request._get_post().keys() returns the data in plain text.
    # We wil need to get its first key using list(request._get_post().keys())[0]
    # then the "false" statements that are from Javascript should be changed to False in python so that parsing using eval
    # does not raise error
    try:
        if not is_authorized(request):
            return HttpResponse(json.dumps({'authorized': 'false'}), content_type="application/json")
        received_data = list(request._get_post().keys())[0]
        sanitized_receive_data = eval(sanitize_data(received_data))

        anatomy = sanitized_receive_data['anatomy']
        physiology = {"physio_data": sanitized_receive_data['physiology']}

        # # we can either save the data temporarily as json and use those for simulating,
        # # or pass the data itself and config_file_converter will take care of the save_to_file part
        # with open('.\\tmp_anatomy.json', 'w') as f:
        #     json.dump(anatomy, f)
        # with open('.\\tmp_physio.json', 'w') as f:
        #     json.dump(physiology, f)
        # CM = Cx.CxSystem('.\\tmp_anatomy.json', '.\\tmp_physio.json')

        if anatomy['params']['run_in_cluster'] == 1:
            anatomy['params']['password'] = getpass('Please enter your password for user {}: '.format(anatomy["params"]["cluster_username"]))
        p = multiprocessing.Process(target=cxspawner, args=(anatomy, physiology, Path.cwd().parent.parent))
        p.name = "spawned_CxSystem"
        p.start()
        return HttpResponse(json.dumps({"authorized":"true", "response": "simulation started successfully"}))
    except Exception as e:
        print(e)
        return HttpResponse(json.dumps({"authorized":"true", "response": "Something went wrong on server"}))





@csrf_exempt
def load_example(request):
    if not is_authorized(request):
        return HttpResponse(json.dumps({'authorized':'false'}), content_type="application/json")
    data = {'authorized':'true'}
    example_name = request.body.decode('utf-8').split('=')[0]
    config_type = request.body.decode('utf-8').split('=')[1]

    if config_type == 'anatomy':
        filename = example_name + '_anatomy_config.json'
    else:
        filename = example_name + '_physiology_config.json'
    current_dir = Path.cwd()
    examples_path = current_dir.joinpath('examples').joinpath(filename)
    if examples_path.is_file():
        with open(examples_path.as_posix()) as json_file:
            data.update(json.load(json_file))
    return HttpResponse(json.dumps(data), content_type="application/json")
