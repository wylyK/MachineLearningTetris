#include "TetrisModelV1.h"

TetrisModelV1::Net::Net() {
    fc1 = register_module("fc1", torch::nn::Linear(INPUT_FEATURES, MIDDLE_LAYER_1_SIZE));
    fc2 = register_module("fc2", torch::nn::Linear(MIDDLE_LAYER_1_SIZE, MIDDLE_LAYER_2_SIZE));
    fc3 = register_module("fc3", torch::nn::Linear(MIDDLE_LAYER_2_SIZE, 1));

    fc1->to(torch::kFloat64);
    fc2->to(torch::kFloat64);
    fc3->to(torch::kFloat64);
}

torch::Tensor TetrisModelV1::Net::forward(torch::Tensor x) {
    if (x.dtype() != torch::kFloat64) {
        x = x.to(torch::kFloat64);
    }
    std::cout << "x = " << x << std::endl;
    x = torch::relu(fc1->forward(x.reshape({x.size(0), 19})));
    x = torch::relu(fc2->forward(x));
    x = torch::sigmoid(fc3->forward(x));
    return x;
}

//void TetrisModelV1::setParams(torch::Tensor const & params) {
void TetrisModelV1::setParams(int) {
    size_t paramsIdx = 0;
    for (torch::Tensor & t : net.parameters()) {
        for (int i = 0; i < t.numel(); ++i) {

            ;
        }
//        std::cout << "params " << i << ": " << t << std::endl;
//        totalParams += t.numel();
//        ++i;
    }
//    std::cout << totalParams << " total parameters counted" << std::endl;
    std::cout << NUM_PARAMETERS << " total parameters calculated" << std::endl;
}

torch::Tensor TetrisModelV1::evaluate(torch::Tensor const & features) {
    return net.forward(features);
}
