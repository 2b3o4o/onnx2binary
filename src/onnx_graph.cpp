#include <string>
#include <vector>
#include <iostream>
#include <pybind11/pybind11.h>

class OnnxGraph {
public:
    OnnxGraph() {};
    void print_nodes() {
        std::cout << "Print nodes from C++ code...\n";
        for (size_t i = 0; i < nodes.size(); i++) {
            std::cout << "Node " << i << ":\n" << nodes[i] << "\n";
        }
    }

    void add_node(std::string& node) {
        nodes.push_back(node);
    }

private:
    std::vector<std::string> nodes = {};
};


namespace py = pybind11;

PYBIND11_MODULE(onnx_graph, m) {
    py::class_<OnnxGraph>(m, "OnnxGraph")
        .def(py::init<>())
        .def("add_node", &OnnxGraph::add_node)
        .def("print_nodes", &OnnxGraph::print_nodes);
}