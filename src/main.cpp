#include <string>
#include <pybind11/pybind11.h>
#include <pybind11/embed.h>

namespace py = pybind11;

int main(int argc, char* argv[]) {
    // parse command line args
    std::string onnx_path = "../simple_mnist.onnx";


    // call into python code that parses onnx graph
    py::scoped_interpreter guard{};
    py::module_ des_module = py::module_::import("deserialize_onnx");
    py::object result = des_module.attr("deserialize")("onnx_file_string", onnx_path);
    assert(result.cast<bool>());    

    // that python code calls into onnx_graph.cpp, creating an OnnxGraph object and storing the graph in there
    // the onnxgraph gets lowered to my custom IR. probably a function in onnx_graph.cpp does this and produces an IrGraph object
    // interpret the IrGraph (or compile it, eventually)
    return 0;
}