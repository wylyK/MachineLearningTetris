#include "TetrisModelV1.h"

TetrisModelV1::Net::Net(torch::Dtype const dtype) :
    dtype(dtype)
{
    fc1 = register_module("fc1", torch::nn::Linear(INPUT_FEATURES, MIDDLE_LAYER_1_SIZE));
    fc2 = register_module("fc2", torch::nn::Linear(MIDDLE_LAYER_1_SIZE, MIDDLE_LAYER_2_SIZE));
    fc3 = register_module("fc3", torch::nn::Linear(MIDDLE_LAYER_2_SIZE, 1));

    fc1->to(dtype);
    fc2->to(dtype);
    fc3->to(dtype);
}

torch::Tensor TetrisModelV1::Net::forward(torch::Tensor x) {
    if (!(x.ndimension() == 2 && x.size(1) == INPUT_FEATURES)) {
        std::cerr << "input to TetrisModelV1 must be of shape [n, " << INPUT_FEATURES << "], not " << x.sizes()
                  << std::endl;
        abort();
    }
    if (x.dtype() != dtype) {
        x = x.to(dtype);
    }
    // std::cout << "x = " << x << std::endl;
    x = torch::relu(fc1->forward(x));
    x = torch::relu(fc2->forward(x));
    x = torch::sigmoid(fc3->forward(x));
    return x;
}

TetrisModelV1::TetrisModelV1(torch::Dtype const dtype) :
    dtype(dtype),
    net(dtype)
{
    // mean 0, stddev .5
    setParams(torch::normal(0, .5, TetrisModelV1::NUM_PARAMETERS));
}

TetrisModelV1::TetrisModelV1(torch::Tensor const & params, torch::Dtype const dtype) :
    dtype(dtype),
    net(dtype)
{
    setParams(params);
}

void TetrisModelV1::setParams(torch::Tensor const & newParams) {
    params = newParams;
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
