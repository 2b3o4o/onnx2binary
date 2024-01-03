from setuptools import setup, Extension
from pybind11.setup_helpers import Pybind11Extension, build_ext

ext_modules = [
    Pybind11Extension(
        "onnx_graph",  # Name of the module
        ["onnx_graph.cpp"],  # Filename of the C++ source
    ),
]

setup(
    name="onnx_graph",
    version="1.0",
    author="Luke Weiler",
    description="Internal representation of ONNX graph in C++",
    ext_modules=ext_modules,
    cmdclass={"build_ext": build_ext},
)
