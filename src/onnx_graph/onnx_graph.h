#ifndef ONNX_GRAPH_H
#define ONNX_GRAPH_H

#include <iostream>
#include <string>
#include <vector>
#include <pybind11/pybind11.h>

class OnnxGraph {
public:
    OnnxGraph() {};
    void add_constant();
    void add_reshape();
    void print_nodes();
    static auto* new_OnnxGraph();
    static void hello_from_header() { std::cout << "hello!\n"; };

private:
    std::vector<std::string> nodes;
};

namespace py = pybind11;

// PYBIND11_MODULE(onnx_graph, m);

#endif // ONNX_GRAPH_H