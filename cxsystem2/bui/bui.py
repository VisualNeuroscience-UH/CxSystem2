import ctypes
import os
import socket
import webbrowser
import requests
import threading
from time import sleep
from pathlib import Path
from sys import platform, exit
from requests.exceptions import ConnectionError, SSLError

class disable_file_system_redirection:
    if platform == 'win32':
        _disable = ctypes.windll.kernel32.Wow64DisableWow64FsRedirection
        _revert = ctypes.windll.kernel32.Wow64RevertWow64FsRedirection

    def __enter__(self):
        if platform == 'win32':
            self.old_value = ctypes.c_long()
            self.success = self._disable(ctypes.byref(self.old_value))

    def __exit__(self, type_, value, traceback):
        if platform == 'win32' and self.success:
            self._revert(self.old_value)


def find_free_port():
    s = socket.socket()
    s.bind(('', 0))  # Bind to a free port provided by the host.
    return s.getsockname()[1]  # Return the port number assigned.


class RunServer:
    def __init__(self,
                 ssl=False,
                 port=None,
                 nobrowser=False):
        try:
            python_cmd_version = os.popen('python --version').read().strip().split(' ')[1]
            if int(python_cmd_version[0]) < 3:
                print("CxBUI is only supported on python 3")
                exit(1)
        except Exception as e:
            print("something went wrong getting python version ... ")
            print(e)
            exit(1)

        crr_file_folder = Path(os.path.dirname(__file__))
        server_folder = crr_file_folder.joinpath('cx_bui')

        os.chdir(server_folder.as_posix())
        if port is None:
            port = find_free_port()
        self.url = "https://127.0.0.1:{}/".format(port) if ssl else "http://127.0.0.1:{}/".format(port)
        if not nobrowser:
            t = threading.Thread(target=self.run_browser_when_ready, args=())
            t.start()
        if platform == 'win32':
            disable_file_system_redirection().__enter__()
        if ssl:
            os.system("python manage.py runserver_plus {port} --cert server_cert".format(port=port))
        else:
            os.system("python manage.py runserver {port}".format(port=port))

    def run_browser_when_ready(self):
        ready = False
        while not ready:
            try:
                r = requests.get(self.url)
                if r.status_code == 200:
                    ready = True
            except SSLError:
                ready = True
            except ConnectionError:
                pass
            sleep(1)
        webbrowser.open_new_tab(self.url)
