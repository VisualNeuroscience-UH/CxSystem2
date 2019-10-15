from django.shortcuts import render
from django.http import HttpResponse,HttpResponseRedirect, JsonResponse
from django.template import loader
from django.views.decorators.csrf import csrf_exempt
import logging
import sys, os, json
from pathlib import Path
[sys.path.append(i) for i in ['.', '..', '../..']]
from CxSystem import CxSystem as Cx
import multiprocessing
from getpass import getpass
import json

logging.getLogger("requests").setLevel(logging.WARNING)

# Create your views here.
def index(request):
    # latest_question_list = Question.objects.order_by('-pub_date')[:5]
    template = loader.get_template('editor/index.html')
    return HttpResponse(template.render({}, request))
    # return HttpResponse("Hello, world. You're at the polls index.")


def CxSpawner(anatomy, physiology,root_path):
    '''
    The function that each spawned process runs and parallel instances of CxSystems are created here.

    :param idx: index of the requested parallel CxSystem.
    :param working: the index of the process that is being currently performed. This is to keep track of running processes to prevent spawning more than required processes.
    :param paths: The path for saving the output of the current instance of CxSystem.
    '''
    from time import sleep
    sleep(10)
    print(root_path)
    os.chdir(root_path)

    cm =  Cx(anatomy, physiology)
    cm.run()

def sanitize_data(received_data):
    received_data = received_data.replace('false', '0')
    received_data = received_data.replace('true', '1')
    received_data = received_data.replace(':null', ':"--"')
    return received_data


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

    received_data = list(request._get_post().keys())[0]
    sanitized_receive_data = eval(sanitize_data(received_data))

    anatomy = sanitized_receive_data['anatomy']
    physiology = { "physio_data": sanitized_receive_data['physiology']}

    # we can either save the data temporarily as json and use those for simulating, or pass the data itself and config_file_converter will take care of the save_to_file part
    # with open('.\\tmp_anatomy.json', 'w') as f:
    #     json.dump(anatomy, f)
    # with open('.\\tmp_physio.json', 'w') as f:
    #     json.dump(physiology, f)
    # CM = Cx.CxSystem('.\\tmp_anatomy.json', '.\\tmp_physio.json')

    if anatomy['params']['run_in_cluster'] == 1:
        anatomy['params']['password'] = getpass('Please enter your password for user {}: '.format(anatomy["params"]["username"]))
    p = multiprocessing.Process(target=CxSpawner, args=(anatomy, physiology,Path.cwd().parent.parent))
    p.name = "spawned_CxSystem"
    p.start()

    return HttpResponse("simulation started successfully")



@csrf_exempt
def load_example(request):
    example_name = list(request._get_post().keys())[0]
    config_type = list(request._get_post().values())[0]
    if config_type == 'anatomy':
        filename = example_name + '_anatomy_config.json'
    else:
        filename = example_name + '_physiology_config.json'
    current_dir = Path.cwd()
    examples_path = current_dir.joinpath('examples').joinpath(filename)
    if (examples_path.is_file()):
        with open(examples_path) as json_file :
            data = json.load(json_file)

    return HttpResponse(json.dumps(data), content_type="application/json")
