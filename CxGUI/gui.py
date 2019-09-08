import os
from pathlib import Path
import ctypes
from sys import platform
import webbrowser

class disable_file_system_redirection:
    _disable = ctypes.windll.kernel32.Wow64DisableWow64FsRedirection
    _revert = ctypes.windll.kernel32.Wow64RevertWow64FsRedirection
    def __enter__(self):
        self.old_value = ctypes.c_long()
        self.success = self._disable(ctypes.byref(self.old_value))
    def __exit__(self, type, value, traceback):
        if self.success:
            self._revert(self.old_value)

class runserver:
    def __init__(self):
        server_folder= Path(os.path.dirname(__file__)).joinpath('CxFront')
        if platform == 'win32':
            disable_file_system_redirection().__enter__()
            os.system(f'cd {server_folder.as_posix()} && start chrome http://127.0.0.1:8000/ && python manage.py runserver')
        else:
            os.system(f'cd {server_folder}; python manage.py runserver')
        webbrowser.get('chrome').open_new('http://127.0.0.1:8000/')
