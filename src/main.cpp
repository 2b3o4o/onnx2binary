#include <string>
#include <pybind11/pybind11.h>
#include <pybind11/embed.h>

#include "onnx_graph/onnx_graph.h"

namespace py = pybind11;

int main(int argc, char* argv[]) {
    // parse command line args
    std::string onnx_path = "../simple_mnist.onnx";

    // call into python code that parses onnx graph
    py::scoped_interpreter guard{};
    py::module_ des_module = py::module_::import("onnx_graph.deserialize_onnx");
    py::object result = des_module.attr("deserialize")(onnx_path);
    OnnxGraph* onnx_graph = result.cast<OnnxGraph*>();
    std::cout << "Calling print_nodes from main.cpp...\n";
    onnx_graph->print_nodes();
    OnnxGraph::hello_from_header();

    // that python code calls into onnx_graph.cpp, creating an OnnxGraph object and storing the graph in there
    // the onnxgraph gets lowered to my custom IR. probably a function in onnx_graph.cpp does this and produces an IrGraph object
    // interpret the IrGraph (or compile it, eventually)
    return 0;
}