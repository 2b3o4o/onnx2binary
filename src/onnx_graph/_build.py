import subprocess
import os

def build():
    try:
        wd = os.path.dirname(os.path.realpath(__file__))
        module_dir = os.path.join(wd, "module")
        os.makedirs(module_dir, exist_ok=True)
        open(os.path.join(module_dir, "__init__.py"), 'a').close()

        commands = [
            ["python3", "setup.py", "build_ext", "--build-lib", "module"],
        ]
        for command in commands:
            subprocess.run(command, cwd=wd)

    except subprocess.CalledProcessError:
        print("Compilation failed.")

if __name__ == "__main__":
    build()
