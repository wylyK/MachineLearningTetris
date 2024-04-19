#include <iostream>
#include "SimplifiedTetris.h"

int main() {
    SimplifiedTetris::Game game(5);
    for (int i = 0; i < 50; ++i) {
        std::cout << (int)game.getNext() << std::endl;
    }
    std::cout << "game state:" << std::endl;
    for (int i = 0; i < 20; ++i) {
        for (int j = 0; j < 10; ++j) {
            std::cout << (int)game.boardState[i][j] << " ";
        }
        std::cout << std::endl;
    }
}
