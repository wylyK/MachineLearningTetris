#include "SimplifiedTetris.h"

namespace SimplifiedTetris {

  Bag::Bag(std::mt19937_64::result_type seed) :
      urbg(seed)
  {
      refill();
  }

  void Bag::refill() {
      std::copy(std::begin(tetrominos), std::end(tetrominos), std::begin(bag));
      std::shuffle(std::begin(bag), std::end(bag), urbg);
      next = 0;
  }

  Tetromino Bag::getNext() {
      if (next >= 7) {
          refill();
      }
      Tetromino const retVal = bag[next];
      ++next;
      return retVal;
  }

}
