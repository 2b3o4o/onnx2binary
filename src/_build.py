import subprocess

def build():
    compiler = "clang++"
    compiler_flags = [
        "-O0",
        "-v",
        "-fuse-ld=lld",
    ]
    subdirectories = [
        "onnx_graph",
    ]
    commands = [
    ]
    cpp_sources = [
        "main.cpp",
        "onnx_graph/onnx_graph.cpp",
    ]
    include_dirs = [
        "/opt/homebrew/opt/pybind11/include/",
        "/opt/homebrew/opt/python@3.11/Frameworks/Python.framework/Versions/3.11/include/python3.11/",
    ]
    linker_ops = [
        "-L/opt/homebrew/opt/python@3.11/Frameworks/Python.framework/Versions/3.11/lib",
        "-lpython3.11",
    ]
    binary = "main"
    for sd in subdirectories:
        commands.append(["python3", f"{sd}/_build.py"])
    commands.extend([
        [compiler] + compiler_flags + cpp_sources + ["-o", binary] + ["-I" + d for d in include_dirs] + linker_ops
    ])
    
    for command in commands:
        subprocess.run(command)

if __name__ == "__main__":
    build()
