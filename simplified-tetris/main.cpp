#include <iostream>
#include "SimplifiedTetris.h"

int main() {
    SimplifiedTetris::Game game(5);
    for (int i = 0; i < 50; ++i) {
        std::cout << (int)game.getNext() << std::endl;
    }
}
