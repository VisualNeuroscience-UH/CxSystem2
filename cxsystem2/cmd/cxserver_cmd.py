"""cxserver -- web server for cxsystem2

Usage:
  cxserver (-h | --help)
  cxserver [--port=PORT] [--no-browser]
  cxserver --https [-p PROVIDERID -c CLIENTID -r REDIRECTURI -a AUTHORIZATION] [--port=PORT] [--no-browser]
  cxserver --overwrite -p PROVIDERID -c CLIENTID -r REDIRECTURI -a AUTHORIZATION

Web server for running the BUI for `cxsystem2`

Arguments:
  PORT                                              port number on which the BUI server runs
  PROVIDERID                                        provider id for OAuth2 client for authentication
  CLIENTID                                          client id for OAuth2 client for authentication
  REDIRECTURI                                       redirect url for OAuth2 client for authentication
  AUTHORIZATION                                     authorization url for OAuth2 client for authentication

Options:
  -h --help                                         Show this screen
  -v --version                                      Show current cxsystem version
  --https                                           Run server with ssl certificate
  --port=PORT                                       Runs the server on port PORT
  --overwrite                                       Rewrite the oauth config file with the new parameters
  --no-browser                                      Do not open browser after running the server
  -p PROVIDERID --provider-id=PROVIDERID            Sets the provider id
  -c CLIENTID --client-id=CLIENTID                  Sets the client id
  -r REDIRECTURI --redirect-uri=REDIRECTURI         Sets the redirect url
  -a AUTHORIZATION --authorization=AUTHORIZATION    Sets the authorization url


Description:

  cxserver
    runs the cxsystem2 server without SSL certificate on a random port

  cxserver --port=PORT
    runs the server on a specific port number PORT

  cxserver --https -p HBP -c f34780ff-7842-499c-8440-5777c28e360d -r https://127.0.0.1:4443 -a https://services.humanbrainproject.eu/oidc/authorize
    runs the cxsystem using the ssl certificate and the corresponding authentication parameters

  cxserver --overwrite -p HBP -c f34780ff-7842-499c-8440-5777c28e360d -r https://127.0.0.1:4443 -a https://services.humanbrainproject.eu/oidc/authorize
    overwrite the configuration yaml file with the new oauth parameters
"""

import sys
from pathlib import Path
import yaml

from docopt import docopt

from cxsystem2.core.cxsystem import CxSystem


def main():
    arguments = docopt(__doc__)
    # print(arguments)
    yaml_path = Path().home().joinpath('.cxconfig.yaml')

    if arguments['--https']:
        cx = CxSystem()
        if not yaml_path.is_file() and \
            (not arguments['--provider-id'] or
            not arguments['--client-id'] or
            not arguments['--redirect-uri'] or
            not arguments['--authorization']):
            print ("Cxserver needs OAuth configuration to run in https mode. These parameters should either be set as parameters (see usage)"
                   " or they should be put in ~/.cxconfig.yaml in yaml formart.")
        elif yaml_path.is_file() and \
                arguments['--provider-id'] and \
                arguments['--client-id'] and \
                arguments['--redirect-uri'] and \
                arguments['--authorization']:
            print("OAuth configuration file already exists. If you want to overwrite the configuration, use the --rewrite (read usage)"
                  " or alternatively run the server `cxserver --https` without additional parameters to run the server with current configurations.")

        elif not yaml_path.is_file() and \
                arguments['--provider-id'] and \
                arguments['--client-id'] and \
                arguments['--redirect-uri'] and \
                arguments['--authorization']:
            print ("OAuth configuration not found, creating configuration file with the new parameters.")
            oauth_config = [{'oauth2':{
                                        'provider-id': arguments['--provider-id'],
                                        'client-id': arguments['--client-id'],
                                        'redirect-uri': arguments['--redirect-uri'],
                                        'authorization': arguments['--authorization']}}]
            with open(yaml_path.as_posix(), 'w') as file:
                yaml.dump(oauth_config, file)
            print("Configuration yaml file updated successfully.")
            cx.run_bui(ssl=True,
                       port=arguments['--port'],
                       nobrowser=arguments['--no-browser'])
        elif yaml_path.is_file():
            cx.run_bui(ssl=True,
                       port=arguments['--port'],
                       nobrowser=arguments['--no-browser'])

    elif arguments['--overwrite']:
        oauth_config = [{'oauth2':{
                                    'provider-id': arguments['--provider-id'],
                                    'client-id': arguments['--client-id'],
                                    'redirect-uri': arguments['--redirect-uri'],
                                    'authorization': arguments['--authorization']}}]
        with open(yaml_path.as_posix(), 'w') as file:
            yaml.dump(oauth_config, file)
        print("Configuration yaml file updated successfully.")
    else:
        cx = CxSystem()
        cx.run_bui(ssl=False,
                   port=arguments['--port'],
                   nobrowser=arguments['--no-browser'])


if __name__ == '__main__':
    if len(sys.argv) == 1:
        sys.argv.append('-h')
    main()
