# versioning format from Software_Versionin in wiki:
# The followings can be used in the third position:
#
# 0 for alpha (status)
# 1 for beta (status)
# 2 for release candidate
# 3 for (final) release
# For instance:
#
# 1.2.0.1 instead of 1.2-a1
# 1.2.1.2 instead of 1.2-b2 (beta with some bug fixes)
# 1.2.2.3 instead of 1.2-rc3 (release candidate)
# 1.2.3.0 instead of 1.2-r (commercial distribution)
# 1.2.3.5 instead of 1.2-r5 (commercial distribution with many bug fixes)
#
# for instance the new format starts with 0.1.1.1 which means version 0.1 beta with several patches. At final release
# we will move to version 1.0 instead of 0.1
# __version__ = "2.1.1.52"
from pathlib import Path


this_file_path = Path(__file__).resolve()
full_path = this_file_path.parent.parent / "pyproject.toml"


def get_version():
    version_key = "version ="
    with open(full_path, "r", encoding="utf-8") as file:
        for line in file:
            if line.strip().startswith(version_key):
                # Extract the version number, stripping quotes and whitespace
                return line.split("=")[1].strip().strip('"').strip("'")


__version__ = get_version()
