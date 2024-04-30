#include <torch/torch.h>

class TetrisModelV1 {
  public:
    struct Net : torch::nn::Module {
        torch::nn::Linear fc1{nullptr};
        torch::nn::Linear fc2{nullptr};
        torch::nn::Linear fc3{nullptr};
        Net();
        torch::Tensor forward(torch::Tensor);
    };
  private:
    Net net;
  public:
    torch::Tensor evaluate(torch::Tensor);
    void setParams(int);
};
