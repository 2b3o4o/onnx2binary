import onnx
import numpy as np
import tvm
from tvm import relay
from tvm.contrib import graph_executor

# Path to your ONNX model
model_path = "simple_mnist.onnx"

# Load the ONNX model
onnx_model = onnx.load(model_path)

# Set the target to LLVM
target = "llvm"

# Convert the ONNX model to Relay IR
shape_dict = {"onnx::Reshape_0": (1, 1, 28, 28)}  # Adjust as per your model's input
mod, params = relay.frontend.from_onnx(onnx_model, shape_dict)

# Compile the model
with tvm.transform.PassContext(opt_level=0):
    lib = relay.build(mod, target=target, params=params)

# Save the compiled module
output_lib_path = "compiled_model.so"
lib.export_library(output_lib_path)

# Load the compiled module
loaded_lib = tvm.runtime.load_module(output_lib_path)

# Create the runtime module (graph executor)
ctx = tvm.cpu(0)
module = graph_executor.GraphModule(loaded_lib["default"](ctx))

# Prepare and set the input
input_data = np.random.rand(1, 1, 28, 28).astype("float32")
module.set_input("onnx::Reshape_0", tvm.nd.array(input_data))

# Run the model
module.run()

# Get the output
output = module.get_output(0).asnumpy()
print("Model output:", output)
