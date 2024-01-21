#include <string>
#include <vector>
#include <iostream>
#include <pybind11/pybind11.h>

#include "ir_graph.hpp"

void IrGraph::add_constant(std::string name, std::string output_name, py::array_t<long> val_arr) {
    nodes.push_back(name);
    std::cout << "add_constant called\n";
}

void IrGraph::add_reshape() {
    nodes.push_back("reshape!");
    std::cout << "add_reshape called\n";
}

void IrGraph::print_nodes() {
    for (size_t i = 0; i < nodes.size(); i++) {
        std::cout << "Node " << i << ":\n" << nodes[i] << "\n";
    }
}

auto* IrGraph::new_IrGraph() {
    return new IrGraph();
}

namespace py = pybind11;

PYBIND11_MODULE(onnx_graph, m) {
    py::class_<IrGraph>(m, "IrGraph")
        .def(py::init<>())
        .def("add_constant", &IrGraph::add_constant)
        .def("add_reshape", &IrGraph::add_reshape)
        .def("print_nodes", &IrGraph::print_nodes)
        .def("new_IrGraph", &IrGraph::new_IrGraph);
}