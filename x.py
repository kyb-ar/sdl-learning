#!/usr/bin/python3
import fire
import os
import subprocess
import shutil


class Build:
    """Simple build commands for the project"""

    def run(self):
        subprocess.run(["premake5", "gmake"])
        subprocess.run(["make", "config", "=", "linux_release"], shell=True)
        to_run = os.path.join("./bin/sdl_learning")
        subprocess.run(to_run)

    def clean(self):
        dirs = [
            "obj",
            "bin",
        ]
        files = [
            "Makefile",
            "sdl_learning.make"
        ]

        for d in dirs:
            if os.path.exists(d):
                shutil.rmtree(d)
        for f in files:
            if os.path.exists(f):
                os.remove(f)


if __name__ == "__main__":
    fire.Fire(Build)
