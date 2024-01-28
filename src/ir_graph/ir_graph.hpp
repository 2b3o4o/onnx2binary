#ifndef IR_GRAPH_H
#define IR_GRAPH_H

#include <iostream>
#include <string>
#include <vector>
#include <cassert>
#include <pybind11/pybind11.h>
#include <pybind11/numpy.h>
#include <pybind11/stl.h>

namespace py = pybind11;

class IrGraphNode {
public:
    IrGraphNode() {};
    IrGraphNode(const IrGraphNode& other) {};
    virtual ~IrGraphNode() {};
    virtual std::string type() const = 0;
};

template <typename T>
class Tensor : public IrGraphNode {
public:
    Tensor(std::string name, std::unique_ptr<std::vector<int>> dims, py::array_t<T>& np_array);
    Tensor(const Tensor<T>& other);
    ~Tensor() { delete[] values; };
    std::vector<int> arr_pos_to_tensor_pos(int arr_pos);
    int tensor_pos_to_arr_pos(std::vector<int>& tensor_pos);
    std::string type() const { return "Tensor"; };
    std::string name() const { return m_name; };

private:
    std::unique_ptr<std::vector<int>> dims;
    int array_size;
    T* values;
    std::string m_name;
};

class Reshape : public IrGraphNode {
public:
    Reshape(std::vector<std::string>& inputs, std::string& output, bool allowzero) : inputs(inputs), output(output), allowzero(allowzero) {};
    // Reshape(const Reshape& other);
    // ~Reshape() {};
    std::string type() const { return "Reshape"; };
    void _silencewarning() { (void)allowzero; };

private:
    const std::vector<std::string> inputs;
    const std::string output;
    const bool allowzero;
};


class IrGraph {
public:
    IrGraph() { nodes = std::vector<std::unique_ptr<IrGraphNode>>(); };
    template <typename T>
    void add_constant(std::string name, std::string output_name, py::array_t<T>& val_arr, std::vector<int> arr_dims);
    void add_reshape(std::vector<std::string>& inputs, std::string& output, bool allowzero);
    void print_nodes();
    static auto new_IrGraph();
    static void hello_from_header() { std::cout << "hello!\n"; };


private:
    std::vector<std::unique_ptr<IrGraphNode>> nodes;
};



#endif // IR_GRAPH_H