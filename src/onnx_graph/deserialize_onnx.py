import onnx
from .module import ir_graph
import logging
import numpy as np

logging.basicConfig(level=logging.DEBUG)

def parse_constant(node, cpp_graph: ir_graph.IrGraph):
    tensor = onnx.numpy_helper.to_array(node.attribute[0].t)
    tensor = np.ascontiguousarray(tensor) # makes sure all elements are contiguous in memory

    dims = list(node.attribute[0].t.dims)

    match tensor.dtype:
        case "int64":
            add_constant = cpp_graph.add_constant__int64
        case _:
            assert False and "Tried to parse_constant with unsupported tensor type"

    add_constant(node.name, node.output[0], tensor, dims)

def parse_reshape(node, cpp_graph: ir_graph.IrGraph):
    inputs = node.input
    output = node.output[0]
    allowzero = False
    if node.attribute:
        assert node.attribute[0].name == "allowzero"
        if node.attribute[0].i == 1:
            allowzero = True
    
    cpp_graph.add_reshape(inputs, output, allowzero)

def deserialize(onnx_file_string: str) -> ir_graph.IrGraph:
    model_path = onnx_file_string
    model = onnx.load(model_path)
    logging.debug("Model is loaded")
    logging.debug("Model type: %s", type(model))
    
    graph = model.graph
    
    cpp_graph = ir_graph.IrGraph.new_IrGraph()
    
    for i, node in enumerate(graph.node):
        match node.op_type:
            case "Constant":
                parse_constant(node, cpp_graph)
            case "Reshape":
                parse_reshape(node, cpp_graph)
            case _:
                logging.debug(f"Encountered an ONNX node of an unsupported type: Node {i}: {node.op_type}\n  Inputs:{node.input}  Outputs:{node.output}")
    return cpp_graph

if __name__ == "__main__":
    deserialize("../simple_mnist.onnx")
