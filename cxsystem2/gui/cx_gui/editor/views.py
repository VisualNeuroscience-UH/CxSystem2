import json
import logging
import multiprocessing
import os
from getpass import getpass
from pathlib import Path
import requests
import tarfile
import binascii

from django.http import HttpResponse
from django.template import loader
from django.views.decorators.csrf import csrf_exempt

from cxsystem2.core.cxsystem import CxSystem as Cx

logging.getLogger("requests").setLevel(logging.WARNING)


def is_authorized(request):
    session_token = ''
    if "Authorization" in request.headers.keys():
        session_token = request.headers['Authorization'].split(' ')[1]
    user_api = "https://services.humanbrainproject.eu/idm/v1/api/user/me"
    headers = {"Authorization": 'Bearer ' + session_token}
    reply = requests.get(user_api, headers=headers)
    return reply


def index(request):
    # only authenticate if it's running in https

    template = loader.get_template('editor/index.html')
    context = {
        'is_secure' : request.is_secure(),
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
        userid = ''
        if request.is_secure():
            auth_response = is_authorized(request)
            if auth_response.ok:
                userid = auth_response.json()['id']
            else:
                return HttpResponse(json.dumps({'authorized': 'false'}), content_type="application/json")
        received_data = list(request._get_post().keys())[0]
        sanitized_receive_data = eval(sanitize_data(received_data))

        anatomy = sanitized_receive_data['anatomy']
        if request.is_secure() and userid != '':
            user_workspace_path =  Path().home().joinpath('CxServerWorkspace').joinpath(userid)
            anatomy['params']['workspace_path'] = user_workspace_path.as_posix()
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
    if request.is_secure() and not is_authorized(request).ok:
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

@csrf_exempt
def download_workspace(request):
    if request.is_secure():
        userid = ''
        auth_response = is_authorized(request)
        if auth_response.ok:
            userid = auth_response.json()['id']
        else:
            return HttpResponse(json.dumps({'authorized': 'false'}), content_type="application/json")

        user_workspace_path = Path().home().joinpath('CxServerWorkspace').joinpath(userid)
        tar_path =  Path().home().joinpath('CxServerWorkspace').joinpath(userid + ".gz")
        tar = tarfile.open(tar_path.as_posix(), "w:gz")
        tar.add(user_workspace_path.as_posix(), arcname=userid)
        tar.close()

        try:
            with open(tar_path.as_posix(), 'rb') as f:
                file_data = binascii.hexlify(f.read())
            response = HttpResponse(str(file_data), content_type='application/gzip')
            response['Content-Disposition'] = 'attachment; filename="%s"' % userid

        except IOError:
            response = HttpResponse('File not exist')

        return response

def list_files(startpath):
    output = ''
    for root, dirs, files in os.walk(startpath):
        level = root.replace(startpath, '').count(os.sep)
        indent = ' ' * 4 * (level)
        # print('{}{}/'.format(indent, os.path.basename(root)))
        output += '{}{}/\n'.format(indent, os.path.basename(root))
        subindent = ' ' * 4 * (level + 1)
        for f in files:
            output += '{}{}\n'.format(subindent, f)
            # print('{}{}'.format(subindent, f))
    return output

@csrf_exempt
def ls_workspace(request):
    if request.is_secure():
        userid = ''
        auth_response = is_authorized(request)
        if auth_response.ok:
            userid = auth_response.json()['id']
        else:
            return HttpResponse(json.dumps({'authorized': 'false'}), content_type="application/json")

        user_workspace_path = Path().home().joinpath('CxServerWorkspace').joinpath(userid)
        dir_list = list_files(user_workspace_path.as_posix())
        dir_list = dir_list[6:]

        return HttpResponse(dir_list, content_type='text/plain')