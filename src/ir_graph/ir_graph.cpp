#include <cstring>

#include "ir_graph.hpp"

template <typename T>
void IrGraph::add_constant(std::string name, std::string output_name, py::array_t<T>& val_arr, std::vector<int> arr_dims) {
    std::unique_ptr<IrGraphNode> tensor = std::make_unique<Tensor<T>>(name, std::make_unique<std::vector<int>>(arr_dims), val_arr);
    nodes.push_back(std::move(tensor));
    std::cout << "add_constant called\n";
}

void IrGraph::add_reshape(std::vector<std::string>& inputs, std::string& output, bool allowzero) {
    std::unique_ptr<IrGraphNode> tensor = std::make_unique<Reshape>(inputs, output, allowzero);
    nodes.push_back(std::move(tensor));
    std::cout << "add_reshape called\n";
}

void IrGraph::print_nodes() {
    for (size_t i = 0; i < nodes.size(); i++) {
        std::cout << "Node " << i << ":\n" << "Type: " << nodes[i]->type() << "\n";
    }
}

auto IrGraph::new_IrGraph() {
    return std::make_unique<IrGraph>();
}

template <typename T>
std::vector<int> Tensor<T>::arr_pos_to_tensor_pos(int arr_pos) {
    auto output = std::vector<int>(dims->size());
    for (int dimIndex = dims->size(); dimIndex > 0; dimIndex--) {
        int remainder = arr_pos % (*dims)[dimIndex];
        output[dimIndex] = remainder;
        arr_pos -= remainder;
    }
    return output;
}

template <typename T>
int Tensor<T>::tensor_pos_to_arr_pos(std::vector<int>& tensor_pos) {
    assert(tensor_pos.size() == dims->size());
    int pos = 0;
    int prevDimSize = 1;
    for (int dimIndex = dims->size(); dimIndex >= 0; dimIndex--) {
        pos += tensor_pos[dimIndex] * prevDimSize;
        prevDimSize *= (*dims)[dimIndex];
    }
    return pos;
}

template <typename T>
Tensor<T>::Tensor(std::string name, std::unique_ptr<std::vector<int>> dims, py::array_t<T>& np_array)
    : dims(std::move(dims)), array_size(1), m_name(name) {
    assert(dims->size() > 0); // TODO: actually 0 elem dims is valid, I just don't support it yet. see ONNX docs
    // assert(np_array.check()); // check for contiguity of elements, which is assumed by the copy mechanism below
    for (int dim : *(this->dims)) {
        if (dim == -1) { // this also is valid and indicates a dynamic dimension (ex. used for batching) but that's a later problem
            dim = 1;
        }
        array_size *= dim;
    }

    values = new T[array_size];
    auto buff = np_array.request();
    assert(buff.shape.size() == this->dims->size());
    memcpy(values, buff.ptr, sizeof(T) * array_size);
}

template <typename T>
Tensor<T>::Tensor(const Tensor<T>& other) : dims(other.dims), array_size(other.array_size), values(new T[other.array_size]), m_name(other.name()) {
    std::copy(other.values, other.values + array_size, values);
}


namespace py = pybind11;

PYBIND11_MODULE(ir_graph, m) {
    py::class_<IrGraph>(m, "IrGraph")
        .def(py::init<>())
        .def("add_constant__int64", &IrGraph::add_constant<int64_t>)
        .def("add_reshape", &IrGraph::add_reshape)
        .def("print_nodes", &IrGraph::print_nodes)
        .def("new_IrGraph", &IrGraph::new_IrGraph);
}