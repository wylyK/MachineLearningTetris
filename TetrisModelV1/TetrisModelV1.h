#ifndef SIMPLIFIED_TETRIS_TETRISMODELV1_H
#define SIMPLIFIED_TETRIS_TETRISMODELV1_H
#include <torch/torch.h>

class TetrisModelV1 {
  public:
    // TODO: change this back to 19 once the last 3 features are added
    // static size_t constexpr INPUT_FEATURES = 19;
    static size_t constexpr INPUT_FEATURES = 17;
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
        torch::Dtype const dtype;
        torch::nn::Linear fc1{nullptr};
        torch::nn::Linear fc2{nullptr};
        torch::nn::Linear fc3{nullptr};
        explicit Net(torch::Dtype);
        torch::Tensor forward(torch::Tensor);
    };

    torch::Dtype const dtype;
    torch::Tensor params;
  private:
    Net net;
  public:
    TetrisModelV1() : TetrisModelV1(torch::kFloat32) {}
    explicit TetrisModelV1(torch::Tensor const & params) : TetrisModelV1(params, torch::kFloat32) {}
    explicit TetrisModelV1(torch::Dtype);
    explicit TetrisModelV1(torch::Tensor const &, torch::Dtype);

    torch::Tensor evaluate(torch::Tensor const &);
    void setParams(torch::Tensor const & params);
};

#endif //SIMPLIFIED_TETRIS_TETRISMODELV1_H
