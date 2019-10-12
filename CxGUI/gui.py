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
        if platform == 'win32':
            disable_file_system_redirection().__enter__()
        os.system('cd ' + server_folder.as_posix()  + ' && python manage.py runserver_plus --cert server_cert')
