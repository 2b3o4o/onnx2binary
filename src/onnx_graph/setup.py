from setuptools import setup, Extension
from pybind11.setup_helpers import Pybind11Extension, build_ext

ext_modules = [
    Pybind11Extension(
        "ir_graph",  # Name of the module
        ["ir_graph.cpp"],  # Filename of the C++ source
        include_dirs=["ir_graph.hpp"],  # Include directory for the header file
    ),
]

setup(
    name="ir_graph",
    version="1.0",
    author="Luke Weiler",
    description="Assembles an intermediate graph representation, which can be interpreted directly or further lowered.",
    ext_modules=ext_modules,
    cmdclass={"build_ext": build_ext},
)
