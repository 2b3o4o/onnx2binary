import onnx

# Path to your ONNX model
model_path = 'simple_mnist.onnx'

# Load the ONNX model
model = onnx.load(model_path)

# Check the model
print("Model is loaded")
print("Model type:", type(model))

# Inspect the model (optional)
# Print the model's graph
print(onnx.helper.printable_graph(model.graph))

# You can also access specific details
# For example, inputs, outputs, nodes, etc.
print("Inputs:", [input.name for input in model.graph.input])
print("Outputs:", [output.name for output in model.graph.output])
