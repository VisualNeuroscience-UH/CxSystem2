import os.path
with open("./VERSION",'r') as f :
    version = f.readline().strip()

__version__ = version