#include "TetrisModelV1.h"

TetrisModelV1::Net::Net() {
    fc1 = register_module("fc1", torch::nn::Linear(19, 10));
    fc2 = register_module("fc2", torch::nn::Linear(10, 10));
    fc3 = register_module("fc3", torch::nn::Linear(10, 1));
}

torch::Tensor TetrisModelV1::Net::forward(torch::Tensor x) {
    x = torch::relu(fc1->forward(x.reshape({x.size(0), 19})));
    x = torch::relu(fc2->forward(x));
    x = torch::sigmoid(fc3->forward(x));
    return x;
}

void TetrisModelV1::setParams(int const param) {
    int i = 0;
    for (torch::Tensor & t : net.parameters()) {
        std::cout << "params " << i << ": " << t << std::endl;
    }
}

torch::Tensor TetrisModelV1::evaluate(torch::Tensor features) {
    return net.forward(features);
}
