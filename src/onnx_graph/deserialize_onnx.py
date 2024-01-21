import onnx
# import onnx_graph
from .module import onnx_graph
import logging

logging.basicConfig(level=logging.DEBUG)

def deserialize(onnx_file_string: str) -> onnx_graph.OnnxGraph:
    model_path = onnx_file_string
    model = onnx.load(model_path)
    logging.debug("Model is loaded")
    logging.debug("Model type: %s", type(model))
    
    graph = model.graph
    
    cpp_graph = onnx_graph.OnnxGraph.new_OnnxGraph()
    
    for i, node in enumerate(graph.node):
        match node.op_type:
            case "Constant":
                cpp_graph.add_constant()
            case "Reshape":
                cpp_graph.add_reshape()
            case _:
                logging.debug(f"Encountered an ONNX node of an unsupported type: Node {i}: {node.op_type}\n  Inputs:{node.input}  Outputs:{node.output}")
    return cpp_graph

if __name__ == "__main__":
    deserialize("../simple_mnist.onnx")
