#include <torch/torch.h>

class TetrisModelV1 {
  public:
    static size_t constexpr INPUT_FEATURES = 19;
    static size_t constexpr MIDDLE_LAYER_1_SIZE = 10;
    static size_t constexpr MIDDLE_LAYER_2_SIZE = 10;

    static size_t constexpr NUM_PARAMETERS = (
        INPUT_FEATURES * MIDDLE_LAYER_1_SIZE  // middle layer 1 weights
        + MIDDLE_LAYER_1_SIZE  // middle layer 1 biases
        + MIDDLE_LAYER_1_SIZE * MIDDLE_LAYER_2_SIZE  // middle layer 2 weights
        + MIDDLE_LAYER_2_SIZE  // middle layer 2 biases
        + MIDDLE_LAYER_2_SIZE  // output layer weights
        + 1 // output layer bias
    );

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
    torch::Tensor evaluate(torch::Tensor const &);
    void setParams(torch::Tensor const & params);
};
