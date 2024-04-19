#include <iostream>
#include "SimplifiedTetris.h"

int main() {
    SimplifiedTetris::Bag bag(5);
    for (int i = 0; i < 30; ++i) {
        std::cout << (int)bag.getNext() << std::endl;
    }
}
