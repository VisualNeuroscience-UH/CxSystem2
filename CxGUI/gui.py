import os
from pathlib import Path
import ctypes
from sys import platform, exit
import webbrowser


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
    def __init__(self, port = 8000):
        try:
            python_cmd_version = os.popen('python --version').read().strip().split(' ')[1]
            if int(python_cmd_version[0]) < 3 :
                print("CxGUI is only supported on python 3")
                exit(1)
        except Exception as e:
            print ("something went wrong getting python version ... ")
            print (e)

        server_folder= Path(os.path.dirname(__file__)).joinpath('CxFront')
        if platform == 'win32':
            disable_file_system_redirection().__enter__()
            os.system("cd {} && start chrome http://127.0.0.1:{port}/ && python manage.py runserver {port}".format(server_folder.as_posix(), port = port))
        else:
            os.system('cd {}; python manage.py runserver'.format(server_folder))
        chrome = webbrowser.get('chrome')
        chrome.open_new('http://127.0.0.1:{}/'.format(port))
