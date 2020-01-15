import binascii
import json
import logging
import multiprocessing
import os
import shutil
import sys
import tarfile
from getpass import getpass
from pathlib import Path
from datetime import datetime

import requests
import yaml
from django.http import HttpResponse
from django.template import loader
from django.views.decorators.csrf import csrf_exempt

from cxsystem2.core.cxsystem import CxSystem as Cx
from cxsystem2.visualization.rasterplot_to_pdf import rasterplot_pdf_generator

logging.getLogger("requests").setLevel(logging.WARNING)
infologger = logging.getLogger('info_logger')

def get_workspace_path():
    cx_folder = Path(os.path.dirname(os.path.abspath(__file__))).parent.parent.parent
    yaml_path = cx_folder.joinpath('.cxconfig.yaml')
    with open(yaml_path.as_posix(), 'r') as file:
        httpsconfig = yaml.load(file, Loader=yaml.FullLoader)
    return Path(httpsconfig['workspace']['path'])


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
    if request.is_secure():
        cx_folder = Path(os.path.dirname(os.path.abspath(__file__))).parent.parent.parent
        yaml_path = cx_folder.joinpath('.cxconfig.yaml')
        with open(yaml_path.as_posix(), 'r') as file:
            oauth_config = yaml.load(file, Loader=yaml.FullLoader)
        context = {
            'provider_id': oauth_config['oauth2']['provider-id'],
            'client_id' : oauth_config['oauth2']['client-id'],
            'redirect_uri': oauth_config['oauth2']['redirect-uri'],
            'authorization': oauth_config['oauth2']['authorization'],
            'is_secure' : request.is_secure(),
        }
    else:
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
    print(root_path.as_posix())
    os.chdir(root_path.as_posix())

    cm = Cx(anatomy, physiology)
    cm.run()

def cxspawner_secure(anatomy,
              physiology,
              root_path,
              user_workspace_path,
              userid,
              sim_title):
    """
    The function that each spawned process runs and parallel instances of CxSystems are created here.
    :param anatomy:
    :param root_path:
    :param physiology:
    """
    sys.stdout = open(Path(user_workspace_path).joinpath("cxoutput.out"), "a+")
    print("Process {} started for user {} ".format(os.getpid(), userid))
    start_time = datetime.now()
    print("[Started] Simulation \"{}\", timestamp: {}".format(sim_title, datetime.now()))
    print(root_path)
    os.chdir(root_path)

    cm = Cx(anatomy, physiology,array_run_stdout_file=Path(user_workspace_path).joinpath("cxoutput.out"))
    cm.run()
    print("Process {} finished for user {} ".format(os.getpid(),userid))
    print("[Done] Simulation \"{}\" started at [{}]".format(sim_title, start_time))


def sanitize_data(received_data):
    received_data = received_data.replace('false', '0')
    received_data = received_data.replace('true', '1')
    received_data = received_data.replace(':null', ':"--"')
    return received_data


# noinspection PyProtectedMember
@csrf_exempt
def simulate(request):
    # There request that we receive here is the following from django_requests.js :
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
            infologger.info("User {} started simulation".format(userid))

        received_data = list(request._get_post().keys())[0]
        sanitized_receive_data = eval(sanitize_data(received_data))

        anatomy = sanitized_receive_data['anatomy']
        if request.is_secure() and userid != '':
            cx_workspace_path = get_workspace_path()
            user_workspace_path =  cx_workspace_path.joinpath(userid)
            user_workspace_path.mkdir(parents=True, exist_ok=True)
            if workspace_is_full(user_workspace_path):
                return HttpResponse(json.dumps({"authorized": "true", "response": "Workspace is full. Try downloading your workspace, delete the content, then retry."}))

            anatomy['params']['workspace_path'] = user_workspace_path.as_posix()
        physiology = {"physio_data": sanitized_receive_data['physiology']}
        sim_title = anatomy['params']['simulation_title']
        # # we can either save the data temporarily as json and use those for simulating,
        # # or pass the data itself and config_file_converter will take care of the save_to_file part
        # with open('.\\tmp_anatomy.json', 'w') as f:
        #     json.dump(anatomy, f)
        # with open('.\\tmp_physio.json', 'w') as f:
        #     json.dump(physiology, f)
        # CM = Cx.CxSystem('.\\tmp_anatomy.json', '.\\tmp_physio.json')

        if anatomy['params']['run_in_cluster'] == 1:
            anatomy['params']['password'] = getpass('Please enter your password for user {}: '.format(anatomy["params"]["cluster_username"]))
        if request.is_secure() and userid != '':
            p = multiprocessing.Process(target=cxspawner_secure,
                                        args=(anatomy,
                                              physiology,
                                              Path.cwd().parent.parent,
                                              user_workspace_path.as_posix(),
                                              userid,
                                              sim_title))
        else:
            p = multiprocessing.Process(target=cxspawner,
                                        args=(anatomy,
                                              physiology,
                                              Path.cwd().parent.parent))
        p.name = "spawned_CxSystem"
        p.start()
        return HttpResponse(json.dumps({"authorized":"true", "response": "Simulation Started"}))
    except Exception as e:
        print(e)
        return HttpResponse(json.dumps({"authorized":"true", "response": "Something went wrong before simulation"}))

@csrf_exempt
def load_example(request):
    if request.is_secure():
        auth_response = is_authorized(request)
        if not auth_response.ok:
            return HttpResponse(json.dumps({'authorized':'false'}), content_type="application/json")
        userid = auth_response.json()['id']
        infologger.info("User {} loaded example file {}".format(userid,request.body.decode('utf-8')))

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

        cx_workspace_path = get_workspace_path()
        user_workspace_path = cx_workspace_path.joinpath(userid)
        user_workspace_path.mkdir(parents=True, exist_ok=True)
        tar_path =  cx_workspace_path.joinpath(userid + ".gz")
        tar = tarfile.open(tar_path.as_posix(), "w:gz")
        tar.add(user_workspace_path.as_posix(), arcname=userid)
        tar.close()
        infologger.info("User {} downloaded workspace, size: {} Bytes".format(userid, os.path.getsize(tar_path.as_posix())))
        try:
            with open(tar_path.as_posix(), 'rb') as f:
                file_data = binascii.hexlify(f.read())
            response = HttpResponse(str(file_data), content_type='application/gzip')
            response['Content-Disposition'] = 'attachment; filename="%s"' % userid
            os.remove(tar_path.as_posix())
        except IOError:
            response = HttpResponse('File not exist')

        return response

@csrf_exempt
def download_files(request):
    if request.is_secure():
        auth_response = is_authorized(request)
        if auth_response.ok:
            userid = auth_response.json()['id']
        else:
            return HttpResponse(json.dumps({'authorized': 'false'}), content_type="application/json")
        cx_workspace_path = get_workspace_path()
        user_workspace_path = cx_workspace_path.joinpath(userid)
        user_workspace_path.mkdir(parents=True, exist_ok=True)

        print(request.body.decode('utf-8'))
        files = request.body.decode('utf-8').split('=')[1].replace('+','')
        files = files.split('%2C')

        ls = [x.name for x in user_workspace_path.glob('**/*')]
        for file in files:
            if file not in ls:
                return HttpResponse(json.dumps({"authorized": "true", "response": "File {} not found".format(file)}))
        command = 'cd {path} && find . '.format(path=user_workspace_path)
        for file in files:
            command += "-name {name} -or ".format(name=file)
        command = command [:-5] # remove last or
        command += " | xargs tar cfvz ./collected_files.tar.gz"
        os.system(command)

        compressed_file_path = user_workspace_path.joinpath('collected_files.tar.gz')
        infologger.info("User {} downloaded a selection of files {}, size: {} Bytes"
                        .format(userid, files, os.path.getsize(compressed_file_path.as_posix())))

        with open(compressed_file_path.as_posix(), 'rb') as f:
            file_data = binascii.hexlify(f.read())
        response = HttpResponse(str(file_data), content_type='application/gzip')
        response['Content-Disposition'] = 'attachment; filename="collected_files.tar.gz"'
        os.remove(compressed_file_path.as_posix())

        return response


def list_files(startpath):
    output = ''
    for root, dirs, files in os.walk(startpath):
        level = root.replace(startpath, '').count(os.sep)
        indent = ' ' * 4 * (level)
        # print('{}{}/'.format(indent, os.path.basename(root)))
        output += '{}{}/<br>'.format(indent, os.path.basename(root))
        subindent = ' ' * 4 * (level + 1)
        for f in files:
            output += '{}{}<br>'.format(subindent, f)
            # print('{}{}'.format(subindent, f))
    return output

def workspace_is_full(p):
    allowance = 2 # allowed space in GB
    path = Path(p)
    directory_size_bytes = sum(f.stat().st_size for f in path.glob('**/*') if f.is_file())
    directory_size_gb = directory_size_bytes/1024/1024/1024
    if directory_size_gb >= 2:
        return True
    return False

@csrf_exempt
def ls_workspace(request):
    if request.is_secure():
        auth_response = is_authorized(request)
        if auth_response.ok:
            userid = auth_response.json()['id']
        else:
            return HttpResponse(json.dumps({'authorized': 'false'}), content_type="application/json")
        infologger.info("User {} listed workspace files".format(userid))
        cx_workspace_path = get_workspace_path()
        user_workspace_path = cx_workspace_path.joinpath(userid)
        user_workspace_path.mkdir(parents=True, exist_ok=True)
        dir_list = list_files(user_workspace_path.as_posix())
        dir_list = dir_list[6:]

        return HttpResponse(dir_list, content_type='text/plain')


@csrf_exempt
def sim_status(request):
    if request.is_secure():
        auth_response = is_authorized(request)
        if auth_response.ok:
            userid = auth_response.json()['id']
        else:
            return HttpResponse(json.dumps({'authorized': 'false'}), content_type="application/json")
        infologger.info("User {} checked simulation status".format(userid))
        cx_workspace_path = get_workspace_path()
        user_workspace_path = cx_workspace_path.joinpath(userid)
        user_workspace_path.mkdir(parents=True, exist_ok=True)
        outputfile_path = user_workspace_path.joinpath('cxoutput.out')
        sim_finish_lines = []
        output = ''
        if outputfile_path.is_file():
            with open(outputfile_path.as_posix(),'r') as f:
                for line in f:
                    if '[Started]' in line or '[Done]' in line:
                        sim_finish_lines.append(line)
            output = '&'.join(sim_finish_lines) # just send the last 30 lines
        return HttpResponse(output, content_type='text/plain')


@csrf_exempt
def sim_output(request):
    if request.is_secure():
        auth_response = is_authorized(request)
        if auth_response.ok:
            userid = auth_response.json()['id']
        else:
            return HttpResponse(json.dumps({'authorized': 'false'}), content_type="application/json")
        infologger.info("User {} checked simulation status".format(userid))
        cx_workspace_path = get_workspace_path()
        user_workspace_path = cx_workspace_path.joinpath(userid)
        user_workspace_path.mkdir(parents=True, exist_ok=True)
        outputfile_path = user_workspace_path.joinpath('cxoutput.out')
        all_lines = []
        output = ''
        if outputfile_path.is_file():
            with open(outputfile_path.as_posix(),'r') as f:
                for line in f:
                    all_lines.append(line)
            output = ''.join(all_lines[-30:]) # just send the last 30 lines

        return HttpResponse(output, content_type='text/plain')

@csrf_exempt
def delete_all(request):
    if request.is_secure():
        auth_response = is_authorized(request)
        if auth_response.ok:
            userid = auth_response.json()['id']
        else:
            return HttpResponse(json.dumps({'authorized': 'false'}), content_type="application/json")
        infologger.info("User {} cleaned workspace".format(userid))
        cx_workspace_path = get_workspace_path()
        user_workspace_path = cx_workspace_path.joinpath(userid)
        shutil.rmtree(user_workspace_path.as_posix())
        os.mkdir(user_workspace_path.as_posix())

        return HttpResponse(json.dumps({"authorized":"true", "response": "Workspace folder cleaned successfully"}))

@csrf_exempt
def visualize(request):
    if request.is_secure():
        auth_response = is_authorized(request)
        if auth_response.ok:
            userid = auth_response.json()['id']
        else:
            return HttpResponse(json.dumps({'authorized': 'false'}), content_type="application/json")
        cx_workspace_path = get_workspace_path()
        user_workspace_path = cx_workspace_path.joinpath(userid)
        user_workspace_path.mkdir(parents=True, exist_ok=True)
        if workspace_is_full(user_workspace_path):
            return HttpResponse(json.dumps({"authorized": "true", "response":
                "Workspace is full. Try downloading your workspace, delete the content, then retry."}))

        req_data = eval(request.body.decode('utf-8'))
        folder = req_data['folder']
        timestamp = req_data['timestamp'].strip('_')
        sampling_rate = req_data['sampling']
        simulation_folder = user_workspace_path.joinpath(folder)
        if not simulation_folder.is_dir():
            return HttpResponse(json.dumps({"authorized": "true", "response": "Folder not found. Make sure you are typing the correct folder name."}))

        dir_file_list = simulation_folder.glob('**/*')
        files = [x for x in dir_file_list if x.is_file() and timestamp in x.as_posix() and 'results' in x.as_posix()]
        print(files)
        if len(files) == 0 or len(timestamp) != 16:
            return HttpResponse(json.dumps({"authorized": "true", "response": "No file with that timestamp was found."}))

        try:
            if sampling_rate.count('%') != 1 or \
                    float(sampling_rate[:-1]) > 100 or \
                    float(sampling_rate[:-1]) <= 0 :
                return HttpResponse(json.dumps({"authorized": "true", "response": "Sampling rate is not valid"}))
        except ValueError:
            return HttpResponse(json.dumps({"authorized": "true", "response": "Sampling rate is not valid"}))

        rplot = rasterplot_pdf_generator(simulation_folder.as_posix(),timestamp,sampling_rate)
        output_pdf_path = Path(rplot.get_output_file_path())
        infologger.info("User {} visualized rasterplot, pdf size: {} Bytes".format(userid,os.path.getsize(output_pdf_path.as_posix())))
        with open(output_pdf_path.as_posix(), 'rb') as f:
            pdf_file = binascii.hexlify(f.read())
        response = HttpResponse(str(pdf_file), content_type='application/pdf')
        response['Content-Disposition'] = 'attachment; filename="%s"' % output_pdf_path.name

        return response
