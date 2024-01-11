/**
 * onnx2binary's internal representation for computation graphs. After being converted into this form, a graph can subsequently be either interpreted or compiled.
*/
#include <vector>

class IrNode {
public:
       
private:

}

class IrGraph {
private:
    std::vector<IrNode> nodes; // assuming a linear computation graph atp
}

class ConstTensor {

}

class Reshape {
public:

private:

}