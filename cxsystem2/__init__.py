import os.path
with open(os.path.dirname(__file__) + "/../VERSION",'r') as f :
    version = f.readline().strip()

__version__ = version