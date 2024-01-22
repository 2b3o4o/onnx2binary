import subprocess
import os
import shutil

def build():
    wd = os.path.dirname(os.path.realpath(__file__))
    module_dir = os.path.join(wd, "module")

    # Copy ../ir_graph/module to ./module
    src_module_dir = os.path.join(wd, "..", "ir_graph", "module")
    if os.path.exists(module_dir):
        shutil.rmtree(module_dir)
    shutil.copytree(src_module_dir, module_dir)

    # commands = [
        # ["python3", "setup.py", "build_ext", "--build-lib", "module"],
    # ]
    # for command in commands:
        # subprocess.run(command, cwd=wd)

if __name__ == "__main__":
    build()
