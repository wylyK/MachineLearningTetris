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
    if (!(x.ndimension() == 2 && x.size(1) == INPUT_FEATURES)) {
        std::cerr << "input to TetrisModelV1 must be of shape [n, " << INPUT_FEATURES << "], not " << x.sizes()
                  << std::endl;
        abort();
    }
    if (x.dtype() != torch::kFloat64) {
        x = x.to(torch::kFloat64);
    }
    std::cout << "x = " << x << std::endl;
    x = torch::relu(fc1->forward(x));
    x = torch::relu(fc2->forward(x));
    x = torch::sigmoid(fc3->forward(x));
    return x;
}

void TetrisModelV1::setParams(torch::Tensor const & params) {
    torch::NoGradGuard no_grad;
    size_t paramsIdx = 0;
    for (torch::Tensor & t : net.parameters()) {
        int64_t const tParams = t.numel();
        t.index_put_({torch::indexing::None},
                     params.index({torch::indexing::Slice(paramsIdx, paramsIdx + tParams)}).reshape_as(t));
        paramsIdx += tParams;
    }
}

torch::Tensor TetrisModelV1::evaluate(torch::Tensor const & features) {
    return net.forward(features);
}
