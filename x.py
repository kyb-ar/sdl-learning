#!/usr/bin/python3
import fire
import os
import subprocess
import shutil
import shlex
import platform


def get_os():
    if os.name == "nt":
        return "Windows"
    elif os.name == "posix":
        if platform.system() == "Darwin":
            return "macOS"
        else:
            return "Linux or other Unix-like"
    else:
        return "Unknown"


class Build:
    """Simple build commands for the project"""

    def run(self):
        subprocess.run(["premake5", "gmake"])
        build = "linux_release"
        if get_os == "macOS":
            build = "mac_release"
        s = shlex.shlex(f"make config={build}")
        subprocess.run(list(s), shell=True)
        to_run = os.path.join("./bin/sdl_learning")
        subprocess.run(to_run)

    def clean(self):
        dirs = [
            "obj",
            "bin",
        ]
        files = ["Makefile", "sdl_learning.make"]

        for d in dirs:
            if os.path.exists(d):
                shutil.rmtree(d)
        for f in files:
            if os.path.exists(f):
                os.remove(f)


if __name__ == "__main__":
    fire.Fire(Build)
