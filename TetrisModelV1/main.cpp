#include <iostream>

#include <torch/torch.h>

#include "TetrisModelV1.h"

using namespace torch::indexing;

int main() {

//    SimplifiedTetris::Game game(5);
////    for (int i = 0; i < 50; ++i) {
////        std::cout << (int)game.getNext() << std::endl;
////    }
//    std::cout << (int)game.getFalling() << std::endl;
//    game.printBoard();
//    std::cout << std::endl << (int)game.getFalling() << std::endl << std::endl;
//    std::vector<std::tuple<int, int, int>> placements = game.getPlacements();
//    for (std::tuple<int, int, int> & placement : placements) {
//        std::cout << std::get<0>(placement) << ", " << std::get<1>(placement) << ", " << std::get<2>(placement) << std::endl;
//    }

    // Create a new Net.
//    auto net = std::make_shared<TetrisModelV1::Net>();
    TetrisModelV1 model{};

    torch::Tensor inputData = torch::zeros({1, 19});

    model.setParams(5);

//    torch::Tensor prediction = net->forward(inputData);
    torch::Tensor prediction = model.evaluate(inputData);

    std::cout << "prediction: " << prediction << std::endl;
    std::cout << "prediction: " << prediction.index({0, 0}) << std::endl;

}
