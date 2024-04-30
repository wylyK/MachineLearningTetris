#include <iostream>

#include "featureExtractor.h"
#include "TetrisModelV1.h"

using std::vector;

int main() {
    SimplifiedTetris::Game game(5);
    std::vector<std::tuple<int, int, int>> placements = game.getPlacements();
    for (std::tuple<int, int, int> & placement : placements) {
        auto const newBoard = game.previewMove(std::get<0>(placement), std::get<1>(placement),std::get<2>(placement));
        std::cout << std::endl;
        vector<int> const colHeights = feats::columnHeights(*newBoard);
        std::cout << "unused:" << feats::getNumUnused(*newBoard) << std::endl;
        std::cout << "holes:" << feats::getNumHoles(*newBoard) << std::endl;
        std::cout << "wells:" << feats::getNumWells(*newBoard) << std::endl;
        std::cout << "col heights: ";
        for (int const colHeight : colHeights) {
            std::cout << colHeight << ", ";
        }
        std::cout << std::endl << std::endl;
    }

    std::cout << "Hello" << std::endl;

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
}
