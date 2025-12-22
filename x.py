#!/usr/bin/python3
import os
import subprocess
import shutil
import sys


class Build:
    """Simple build commands for the project"""

    def build(self):
        result = subprocess.run(["premake5", "gmake"])
        if result.returncode:
            return result.returncode
        result = subprocess.run(["make", "config", "=", "linux_release"], shell=True)
        if result.returncode:
            return result.returncode
        return 0


    def run(self):
        build_result = self.build()
        if build_result:
            return build_result
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


def no_func():
    print("Command not found!")


if __name__ == "__main__":
    command = "run"
    if len(sys.argv) > 1:
        command = sys.argv[1]
    build = Build()
    sys.exit(getattr(build, command, no_func)())
