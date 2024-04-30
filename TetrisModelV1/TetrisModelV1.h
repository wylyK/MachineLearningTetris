#include <torch/torch.h>

struct TetrisModelV1 : torch::nn::Module {
    torch::nn::Linear fc1{nullptr};
    torch::nn::Linear fc2{nullptr};
    torch::nn::Linear fc3{nullptr};
    TetrisModelV1();
    torch::Tensor forward(torch::Tensor);
};
