#include <torch/torch.h>

class TetrisModelV1 : torch::nn::Module {
  private:
    torch::nn::Linear fc1{nullptr};
    torch::nn::Linear fc2{nullptr};
    torch::nn::Linear fc3{nullptr};
  public:
    TetrisModelV1();
    torch::Tensor forward(torch::Tensor);
};
