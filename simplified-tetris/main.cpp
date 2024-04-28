#include <iostream>
#include "SimplifiedTetris.h"

int main() {
    SimplifiedTetris::Game game(5);
//    for (int i = 0; i < 50; ++i) {
//        std::cout << (int)game.getNext() << std::endl;
//    }
    std::cout << (int)game.getFalling() << std::endl;
    game.printBoard();
    std::cout << std::endl << (int)game.getFalling() << std::endl << std::endl;
    std::vector<std::tuple<int, int, int>> placements = game.getPlacements();
//    for (std::tuple<int, int, int> & placement : placements) {
//        std::cout << std::get<0>(placement) << ", " << std::get<1>(placement) << ", " << std::get<2>(placement) << std::endl;
//    }

    auto const newBoard = game.previewMove(std::get<0>(placements[0]), std::get<1>(placements[0]),std::get<2>(placements[0]));
    newBoard->print();


}
