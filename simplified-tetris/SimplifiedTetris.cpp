#include "SimplifiedTetris.h"

namespace SimplifiedTetris {

  Bag::Bag(Bag::seed_type const seed) :
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

  Game::Game(Game::seed_type seed) :
    bag(seed)
  {
      fallingPiece = bag.getNext();
      for (Tetromino & t : nextQueue) {
          t = bag.getNext();
      }
  }

  Tetromino Game::getNext() {
      Tetromino const nextTetromino = nextQueue[0];
      for (size_t i = 0; i < 5; ++i) {
          nextQueue[i] = nextQueue[i + 1];
      }
      nextQueue[5] = bag.getNext();
      return nextTetromino;
  }

  std::vector<std::size_t[2]> Game::getPlacements() {
      // TODO
  }

}
