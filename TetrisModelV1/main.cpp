#include <iostream>

#include "TetrisModelV1Runner.h"

using namespace torch::indexing;

int main() {
    TetrisModelV1Runner runner(5);
    int const numMoves = runner.play();
    std::cout << "lasted " << numMoves << " moves" << std::endl;

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
