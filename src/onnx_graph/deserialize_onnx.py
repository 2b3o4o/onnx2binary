import onnx
from .module import ir_graph
import logging

logging.basicConfig(level=logging.DEBUG)

def parse_constant(node, cpp_graph: ir_graph.IrGraph):
    # print(node)
    # print("---")
    # print(f"name: {node.name}")
    # print(f"output: {node.output[0]}")
    tensor = onnx.numpy_helper.to_array(node.attribute[0].t)
    print(f"values: {tensor}")
    assert tensor.dtype == "int64" # TODO: make template to support any type
    print(f"values type: {tensor.dtype}")
    cpp_graph.add_constant(name=node.name, output_name=node.output, val_arr=tensor)


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
                cpp_graph.add_reshape()
            case _:
                logging.debug(f"Encountered an ONNX node of an unsupported type: Node {i}: {node.op_type}\n  Inputs:{node.input}  Outputs:{node.output}")
    return cpp_graph

if __name__ == "__main__":
    deserialize("../simple_mnist.onnx")
