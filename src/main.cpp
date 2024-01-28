#include <memory>
#include <string>
#include <pybind11/pybind11.h>
#include <pybind11/embed.h>

#include "ir_graph/ir_graph.hpp"

namespace py = pybind11;

int main(int argc, char* argv[]) {
    // parse command line args
    std::string onnx_path = "../simple_mnist.onnx";

    // call into python code that parses serialized onnx
    // that python code calls into ir_graph.cpp, creating an IrGraph object and storing the graph in there
    py::scoped_interpreter guard{};
    py::module_ des_module = py::module_::import("onnx_graph.deserialize_onnx");
    py::object result = des_module.attr("deserialize")(onnx_path);
    auto ir_graph = result.cast<IrGraph*>();
    std::cout << "Calling print_nodes from main.cpp...\n";
    ir_graph->print_nodes();

    // interpret the IrGraph (or compile it, eventually)
    return 0;
}