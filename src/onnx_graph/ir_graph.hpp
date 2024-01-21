#ifndef IR_GRAPH_H
#define IR_GRAPH_H

#include <iostream>
#include <string>
#include <vector>
#include <pybind11/pybind11.h>

namespace py = pybind11;

class IrGraph {
public:
    IrGraph() {};
    void add_constant(std::string name, std::string output_name, py::array_t<long> val_arr);
    void add_reshape();
    void print_nodes();
    static auto* new_IrGraph();
    static void hello_from_header() { std::cout << "hello!\n"; };

private:
    std::vector<std::string> nodes;
};


#endif // IR_GRAPH_H