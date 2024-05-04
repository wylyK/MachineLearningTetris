#include <iostream>
#include "SimplifiedTetris.h"

int main() {
    SimplifiedTetris::Game game(5);
    game.printBoard();
    std::cout << std::endl;
    int moves[] = {0, 3, 8, 6, 8, 5};
    for (int const & i : moves) {
        auto placements = game.getPlacements();
        if (placements.empty()) {
            std::cout << "out of moves" << std::endl;
            break;
        }
        game.doMove(placements[i]);
        game.getBoard().print();
        std::cout << std::endl;
    }

}
