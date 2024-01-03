import onnx
import onnx_graph

# Path to your ONNX model
model_path = '../simple_mnist.onnx'

# Load the ONNX model
model = onnx.load(model_path)

# Check the model
print("Model is loaded")
print("Model type:", type(model))

graph = model.graph

cpp_graph = onnx_graph.OnnxGraph()


for i, node in enumerate(graph.node):
    cpp_graph.add_node(f"Node {i}: {node.op_type}\n  Inputs:{node.input}  Outputs:{node.output}")

cpp_graph.print_nodes()