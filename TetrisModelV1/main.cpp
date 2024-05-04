#include <chrono>
#include <iostream>

#include "TetrisModelV1Trainer.h"

using namespace torch::indexing;

int main() {
    TetrisModelV1Trainer trainer(100, 5);

    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
    for (int generation = 0; generation < 100; ++generation) {
        std::cout << "Generation " << generation << std::endl;
        trainer.trainRound();
        std::cout << std::endl;
    }
    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    std::cout << "Time taken = " << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << " ms" << std::endl;

    auto results = trainer.runPopulation();
    std::cout << "Results: ";
    for (auto const & result : results) {
        std::cout << std::get<0>(result) << " ";
    }
    std::cout << std::endl;

//    SimplifiedTetris::Game game(4);
//    std::vector<SimplifiedTetris::Move> placements = game.getPlacements();
//    for (SimplifiedTetris::Move & placement : placements) {
//        auto const newBoard = game.previewMove(placement);
//        newBoard->print();
//        std::cout << std::endl;
//        vector<int> const colHeights = feats::columnHeights(*newBoard);
//        std::cout << "unused: " << feats::getNumUnused(*newBoard) << std::endl;
//        std::cout << "holes: " << feats::getNumHoles(*newBoard) << std::endl;
//        std::cout << "wells: " << feats::getNumWells(*newBoard) << std::endl;
//        std::cout << "pieces over holes: " << feats::getNumOverHoles(*newBoard) << std::endl;
//        std::cout << "row transitions: " << feats::getNumRowTrans(*newBoard) << std::endl;
//        std::cout << "col transitions: " << feats::getNumColTrans(*newBoard) << std::endl << std::endl;
//        std::cout << "col heights: ";
//        for (int const colHeight : colHeights) {
//            std::cout << colHeight << " , ";
//        }
//        std::cout << std::endl << std::endl;
//    }

//    TetrisModelV1 model{};
//    torch::Tensor inputData = torch::zeros({1, TetrisModelV1::INPUT_FEATURES});
//    model.setParams(torch::full(TetrisModelV1::NUM_PARAMETERS, .1));
//    torch::Tensor prediction = model.evaluate(inputData);
//    std::cout << "prediction: " << prediction.item<double>() << std::endl;

}
