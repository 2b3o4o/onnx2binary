#include <string>
#include <vector>
#include <iostream>
#include <pybind11/pybind11.h>

#include "onnx_graph.hpp"

void OnnxGraph::add_constant(std::string name, std::string output_name, py::array_t<long> val_arr) {
    nodes.push_back(name);
    std::cout << "add_constant called\n";
}

void OnnxGraph::add_reshape() {
    nodes.push_back("reshape!");
    std::cout << "add_reshape called\n";
}

void OnnxGraph::print_nodes() {
    for (size_t i = 0; i < nodes.size(); i++) {
        std::cout << "Node " << i << ":\n" << nodes[i] << "\n";
    }
}

auto* OnnxGraph::new_OnnxGraph() {
    return new OnnxGraph();
}

namespace py = pybind11;

PYBIND11_MODULE(onnx_graph, m) {
    py::class_<OnnxGraph>(m, "OnnxGraph")
        .def(py::init<>())
        .def("add_constant", &OnnxGraph::add_constant)
        .def("add_reshape", &OnnxGraph::add_reshape)
        .def("print_nodes", &OnnxGraph::print_nodes)
        .def("new_OnnxGraph", &OnnxGraph::new_OnnxGraph);
}