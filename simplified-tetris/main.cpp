#include <iostream>
#include "SimplifiedTetris.h"

int main() {
    SimplifiedTetris::Game game(5);
    std::cout << (int)game.getFalling() << std::endl;
    game.printBoard();
    std::cout << std::endl << (int)game.getFalling() << std::endl << std::endl;
    std::vector<SimplifiedTetris::Move> placements = game.getPlacements();
//    for (std::tuple<int, int, int> & placement : placements) {
//        std::cout << std::get<0>(placement) << ", " << std::get<1>(placement) << ", " << std::get<2>(placement) << std::endl;
//    }

    game.doMove(placements[0]);
    game.getBoard().print();

    placements = game.getPlacements();
    game.doMove(placements[0]);
    game.getBoard().print();


}
