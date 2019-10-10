import os
from pathlib import Path
import ctypes
from sys import platform
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
    def __init__(self):
        crr_file_folder= Path(os.path.dirname(__file__))
        server_folder= crr_file_folder.joinpath('CxFront')
        crt_path = os.path.join(crr_file_folder, "../certificates/server.crt")
        key_path = os.path.join(crr_file_folder, "../certificates/server.key")
        if platform == 'win32':
            disable_file_system_redirection().__enter__()
            if os.path.exists(crt_path) and os.path.exists(key_path):
                os.system(f'cd {server_folder.as_posix()} && start chrome https://127.0.0.1:8000/ && python manage.py runsslserver --certificate ' + crt_path + ' --key ' + key_path)
                webbrowser.get('chrome').open_new('https://127.0.0.1:8000/')
            else:
                os.system(f'cd {server_folder.as_posix()} && start chrome http://127.0.0.1:8000/ && python manage.py runserver')
                webbrowser.get('chrome').open_new('http://127.0.0.1:8000/')
        else:
            if os.path.exists(crt_path) and os.path.exists(key_path):
                os.system(f'cd {server_folder}; python manage.py runsslserver --certificate ' + crt_path + ' --key ' + key_path)
                webbrowser.get('chrome').open_new('https://127.0.0.1:8000/')
            else:
                os.system(f'cd {server_folder}; python manage.py runserver')
                webbrowser.get('chrome').open_new('http://127.0.0.1:8000/')

