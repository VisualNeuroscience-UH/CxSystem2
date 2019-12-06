"""cxserver -- web server for cxsystem2

Usage:
  cxserver (-h | --help)
  cxserver [--port=PORT] [--no-browser]
  cxserver --https [-p PROVIDERID -c CLIENTID -r REDIRECTURI -a AUTHORIZATION] [--port=PORT] [--no-browser]
  cxserver --config -p PROVIDERID -c CLIENTID -r REDIRECTURI -a AUTHORIZATION
  cxserver --config -w WORKSPACEPATH
  cxserver --config -l LOGPATH

Web server for running the BUI for `cxsystem2`

Arguments:
  PORT                                              port number on which the BUI server runs
  PROVIDERID                                        provider id for OAuth2 client for authentication
  CLIENTID                                          client id for OAuth2 client for authentication
  REDIRECTURI                                       redirect url for OAuth2 client for authentication
  AUTHORIZATION                                     authorization url for OAuth2 client for authentication
  WORKSPACEPATH                                     path to the main workspace folder
  LOGPATH                                           path to the log folder

Options:
  -h --help                                         Show this screen
  -v --version                                      Show current cxsystem version
  --https                                           Run server with ssl certificate
  --port=PORT                                       Runs the server on port PORT
  --config                                       Rewrite the oauth config file with the new parameters
  --no-browser                                      Do not open browser after running the server
  -p PROVIDERID --provider-id=PROVIDERID            Sets the provider id
  -c CLIENTID --client-id=CLIENTID                  Sets the client id
  -r REDIRECTURI --redirect-uri=REDIRECTURI         Sets the redirect url
  -a AUTHORIZATION --authorization=AUTHORIZATION    Sets the authorization url
  -w WORKSPACE --workspace-path=WORKSPACE           Sets the workspace path
  -l LOGPATH --log-path=LOGPATH                     Sets the log path

Description:

  cxserver
    runs the cxsystem2 server without SSL certificate on a random port

  cxserver --port=PORT
    runs the server on a specific port number PORT

  cxserver --https
    runs the cxsystem using the ssl certificate and other parameters previously saved in the configuraiton file using --config

  cxserver --config -p HBP -c f34780ff-7842-499c-8440-5777c28e360d -r https://127.0.0.1:4443 -a https://services.humanbrainproject.eu/oidc/authorize
    config the configuration yaml file with the new oauth parameters

  cxserver --config -w /cxworkspace
    config the configuration yaml file with the new workspace path

  cxserver --config -l /var/log/
    config the configuration yaml file with the new log path

"""

import sys
from pathlib import Path
import yaml
import os

from docopt import docopt

from cxsystem2.core.cxsystem import CxSystem

def all_params_exist(httpsconf):
    missing_parameter = ''
    if 'oauth2' in httpsconf.keys():
        if 'provider-id' not in httpsconf['oauth2'].keys():
            missing_parameter = 'provider-id'
        elif 'client-id' not in httpsconf['oauth2'].keys():
            missing_parameter = 'client-id'
        elif 'redirect-uri' not in httpsconf['oauth2'].keys():
            missing_parameter = 'redirect-uri'
        elif 'authorization' not in httpsconf['oauth2'].keys():
            missing_parameter = 'authorization'
    else:
        missing_parameter = 'oauth2'
    if 'workspace' not in httpsconf.keys():
        missing_parameter = 'workspace path'
    if 'log' not in httpsconf.keys():
        missing_parameter = 'log path'
    if missing_parameter == '':
        return True
    return missing_parameter


def main():
    arguments = docopt(__doc__)
    # print(arguments)
    cx_folder = Path(os.path.dirname(os.path.abspath(__file__))).parent
    yaml_path = cx_folder.joinpath('.cxconfig.yaml')

    httpsconfig = {}
    if yaml_path.is_file() and not arguments['--config']:
        with open(yaml_path.as_posix(), 'r') as file:
            httpsconfig = yaml.load(file, Loader=yaml.FullLoader)
        if all_params_exist(httpsconfig) is not True:
            missing_parameter = all_params_exist(httpsconfig)
            print("Parameter {} missing. Set it using --config (see usage)".format(missing_parameter))
            return

    if arguments['--config']:
        if yaml_path.is_file():
            with open(yaml_path.as_posix(), 'r') as file:
                httpsconfig = yaml.load(file, Loader=yaml.FullLoader)
        if arguments['--provider-id'] and arguments['--client-id'] and arguments['--redirect-uri'] and arguments['--authorization']:
            httpsconfig['oauth2'] = {
                'provider-id': arguments['--provider-id'],
                'client-id': arguments['--client-id'],
                'redirect-uri': arguments['--redirect-uri'],
                'authorization': arguments['--authorization']}
        elif arguments['--workspace-path']:
            workspace_path = Path(arguments['--workspace-path'])
            if workspace_path.suffix != '':
                print("Workspace path should be folder, removing the file name")
                workspace_path = workspace_path.parent
            workspace_path.mkdir(parents=True, exist_ok=True)
            httpsconfig['workspace'] = {'path': workspace_path.as_posix()}
        elif arguments['--log-path']:
            log_path = Path(arguments['--log-path'])
            if log_path.suffix != '':
                print("Log path should be folder, removing the file name")
                log_path = log_path.parent
            log_path.mkdir(parents=True, exist_ok=True)
            httpsconfig['log'] = {'path': log_path.as_posix()}

        with open(yaml_path.as_posix(), 'w') as file:
            yaml.dump(httpsconfig, file)
        print ("Parameter(s) set successfully")
        return

    if arguments['--https']:
        cx = CxSystem()
        if not yaml_path.is_file():
            print ("Cxserver needs path to workspace and log, as well as OAuth configuration to run in https mode. These parameters should "
                   "be set using --config as parameters (see usage).")
            return


        cx.run_bui(ssl=True,
                   port=arguments['--port'],
                   nobrowser=arguments['--no-browser'])

    else:
        cx = CxSystem()
        cx.run_bui(ssl=False,
                   port=arguments['--port'],
                   nobrowser=arguments['--no-browser'])


if __name__ == '__main__':
    if len(sys.argv) == 1:
        sys.argv.append('-h')
    main()
