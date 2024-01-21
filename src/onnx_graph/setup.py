from setuptools import setup, Extension
from pybind11.setup_helpers import Pybind11Extension, build_ext

ext_modules = [
    Pybind11Extension(
        "onnx_graph",  # Name of the module
        ["onnx_graph.cpp"],  # Filename of the C++ source
        include_dirs=["onnx_graph.hpp"],  # Include directory for the header file
    ),
]

setup(
    name="onnx_graph",
    version="1.0",
    author="Luke Weiler",
    description="Assembles and represents an ONNX graph in a way which is compatible with the project's internal graph representation, and can be cleanly lowered to it.",
    ext_modules=ext_modules,
    cmdclass={"build_ext": build_ext},
)
