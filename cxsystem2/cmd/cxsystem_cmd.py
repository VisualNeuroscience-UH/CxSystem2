"""cxsystem2 -- a cortex simulation software

Usage:
  cxsystem2 (-h | --help)
  cxsystem2 --runserver [--https] [--port=PORT]


A cortex simulation framework called `CxSystem`.

Arguments:
  PORT    port number on which the GUI server runs

Options:
  -h --help     Show this screen
  --runserver   runs http[s] server for GUI
  --https       run server with ssl certificate
  --port=PORT   runs the server on port PORT


Description:

  cxsystem2 --runserver --https

    spawns a secure web server to run the GUI on

  cxsystem2 --runserver --port=PORT

    runs the server on a specific port number PORT, otherwise random port would be used 
"""

from docopt import docopt
from cxsystem2.core.cxsystem import CxSystem
import sys

def main():
    arguments = docopt(__doc__)
    # print(arguments)

    if arguments['--runserver']:
        if arguments['--https']:
            cx = CxSystem()
            cx.runGUI(ssl=True, port=arguments['--port'])
        else:
            cx = CxSystem()
            cx.runGUI(ssl=False, port=arguments['--port'])


if __name__=='__main__':
    if len(sys.argv) == 1:
        sys.argv.append('-h')
    main()
