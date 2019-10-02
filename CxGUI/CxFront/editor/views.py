from django.shortcuts import render
from django.http import HttpResponse,HttpResponseRedirect
from django.template import loader
from django.views.decorators.csrf import csrf_exempt
import logging
import sys, os, json
from pathlib import Path
[sys.path.append(i) for i in ['.', '..', '../..']]
from CxSystem import CxSystem as Cx
import multiprocessing

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
    print(root_path)
    os.chdir(root_path)

    cm =  Cx(anatomy, physiology)
    cm.run()

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
    received_data = eval(list(request._get_post().keys())[0].replace('false','0').replace('true','1'))

    anatomy = received_data['anatomy']
    physiology = { "physio_data": received_data['physiology']}

    # let's store the current folder because we have to change the folder and we need to change back after simulation


    # we can either save the data temporarily as json and use those for simulating, or pass the data itself and config_file_converter will take care of the save_to_file part
    # with open('.\\tmp_anatomy.json', 'w') as f:
    #     json.dump(anatomy, f)
    # with open('.\\tmp_physio.json', 'w') as f:
    #     json.dump(physiology, f)
    # CM = Cx.CxSystem('.\\tmp_anatomy.json', '.\\tmp_physio.json')


    p = multiprocessing.Process(target=CxSpawner, args=(anatomy, physiology,Path.cwd().parent.parent))
    p.start()


    # # this is the old way of running CxSystem in the same process of django
    # cwd = Path.cwd()
    #
    # # go to the CxSystem root because of the relative paths
    # os.chdir(Path.cwd().parent.parent)
    # CM = Cx(anatomy, physiology)
    # CM.run()
    #
    # # change folder to where we were before
    # os.chdir(cwd)


    return HttpResponse("simulation started successfully")