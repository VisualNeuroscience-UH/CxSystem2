from cxsystem2.core.cxsystem import CxSystem
from pathlib import Path

an = Path('C:\\Users\\vafaa\\gitrepos\\CxSystem2\\tests\\config_files\\pytest_Anatomy_config.csv').as_posix()
ph = Path('C:\\Users\\vafaa\\gitrepos\\CxSystem2\\tests\\config_files\\pytest_Physiology_config.csv').as_posix()

cx = CxSystem(an,ph)
cx.run()