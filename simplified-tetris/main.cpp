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
    std::vector<std::tuple<std::size_t, std::size_t, std::size_t>> placements = game.getPlacements();
    for (std::tuple<std::size_t, std::size_t, std::size_t> & placement : placements) {
        std::cout << std::get<0>(placement) << ", " << std::get<1>(placement) << ", " << std::get<2>(placement) << std::endl;
    }
}
