#include <string>
#include <vector>
#include <iostream>
#include <pybind11/pybind11.h>

class OnnxGraph {
public:
    OnnxGraph() {};
    // void print_nodes() {
        // std::cout << "Print nodes from C++ code...\n";
        // for (size_t i = 0; i < nodes.size(); i++) {
            // std::cout << "Node " << i << ":\n" << nodes[i] << "\n";
        // }
    // }

    void add_constant() {
        std::cout << "add_constant called\n";
    }

    void add_reshape() {
        std::cout << "add_reshape called\n";
    }

private:
    std::vector<std::string> nodes = {};
};


namespace py = pybind11;

PYBIND11_MODULE(onnx_graph, m) {
    py::class_<OnnxGraph>(m, "OnnxGraph")
        .def(py::init<>())
        .def("add_constant", &OnnxGraph::add_constant)
        .def("add_reshape", &OnnxGraph::add_reshape);
        // .def("print_nodes", &OnnxGraph::print_nodes);
}