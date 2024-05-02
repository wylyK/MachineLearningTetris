#include <iostream>
#include "SimplifiedTetris.h"

int main() {
    SimplifiedTetris::Game game(5);
    game.printBoard();
    std::cout << std::endl;
    while (true) {
        auto placements = game.getPlacements();
        if (placements.empty()) {
            std::cout << "out of moves" << std::endl;
            break;
        }
        game.doMove(placements[0]);
        game.getBoard().print();
        std::cout << std::endl;
    }

}
