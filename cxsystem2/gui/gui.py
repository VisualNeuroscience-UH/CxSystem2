import ctypes
import os
import socket
import webbrowser
from pathlib import Path
from sys import platform, exit


class disable_file_system_redirection:
    if platform == 'win32':
        _disable = ctypes.windll.kernel32.Wow64DisableWow64FsRedirection
        _revert = ctypes.windll.kernel32.Wow64RevertWow64FsRedirection
    def __enter__(self):
        if platform == 'win32':
            self.old_value = ctypes.c_long()
            self.success = self._disable(ctypes.byref(self.old_value))
    def __exit__(self, type, value, traceback):
        if platform == 'win32' and self.success:
            self._revert(self.old_value)

class runserver:
    def __init__(self, ssl=False, port = None ):
        try:
            python_cmd_version = os.popen('python --version').read().strip().split(' ')[1]
            if int(python_cmd_version[0]) < 3 :
                print("CxGUI is only supported on python 3")
                exit(1)
        except Exception as e:
            print ("something went wrong getting python version ... ")
            print (e)
            exit(1)

        crr_file_folder= Path(os.path.dirname(__file__))
        server_folder= crr_file_folder.joinpath('cx_gui')

        # server_folder= Path(os.path.dirname(__file__)).joinpath('cx_gui')
        os.chdir(server_folder)

        if port is None:
            port = self.find_free_port()
        if ssl:
            a_website = "https://127.0.0.1:{}/".format(port)
            webbrowser.open_new_tab(a_website)
            if platform == 'win32':
                disable_file_system_redirection().__enter__()
            os.system("python manage.py runserver_plus {port} --cert server_cert".format(port=port))
        else:
            a_website = "http://127.0.0.1:{}/".format(port)
            webbrowser.open_new_tab(a_website)
            if platform == 'win32':
                disable_file_system_redirection().__enter__()
            os.system("python manage.py runserver {port}".format(port=port))

    def find_free_port(self):
        s = socket.socket()
        s.bind(('', 0))  # Bind to a free port provided by the host.
        return s.getsockname()[1]  # Return the port number assigned.