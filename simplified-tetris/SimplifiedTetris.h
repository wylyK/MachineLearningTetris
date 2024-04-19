#ifndef SIMPLIFIED_TETRIS_H
#define SIMPLIFIED_TETRIS_H

#include <cstddef>
#include <algorithm>
#include <array>
#include <random>
#include <type_traits>

namespace SimplifiedTetris {
  enum class Tetromino : std::underlying_type_t<std::byte> {
      null = 0,
      I = 1,
      J = 2,
      L = 3,
      O = 4,
      S = 5,
      Z = 6,
      T = 7
  };

  class Bag {
    private:
      static constexpr Tetromino tetrominos[] = {
          Tetromino::I,
          Tetromino::J,
          Tetromino::L,
          Tetromino::O,
          Tetromino::S,
          Tetromino::Z,
          Tetromino::T
      };
      Tetromino bag[7];
      size_t next = 0;
      std::mt19937_64 urbg;

      void refill();
    public:
      Bag(std::mt19937_64::result_type seed);
      Tetromino getNext();
  };

  class Game {
    private:
    public:
      Tetromino boardState[18][10];
      Tetromino holdPiece = Tetromino::null;
      Tetromino nextQueue[6];
      Tetromino bag[7];
    public:
  };
}

#endif //SIMPLIFIED_TETRIS_H