#ifndef SIMPLIFIED_TETRIS_H
#define SIMPLIFIED_TETRIS_H

#include <cstddef>
#include <algorithm>
#include <array>
#include <random>
#include <type_traits>

namespace SimplifiedTetris {
  enum Tetromino : std::underlying_type_t<std::byte> {
      null = 0,
      O = 1,
      I = 2,
      T = 3,
      L = 4,
      J = 5,
      S = 6,
      Z = 7
  };
  static Tetromino const pieces[7][4][4][4] = {
      // O
      { // O
          // N
          {{Tetromino::null, Tetromino::null, Tetromino::O, Tetromino::O},
           {Tetromino::null, Tetromino::null, Tetromino::O, Tetromino::O},
           {Tetromino::null, Tetromino::null, Tetromino::null, Tetromino::null},
           {Tetromino::null, Tetromino::null, Tetromino::null, Tetromino::null}},
          // E
          {{Tetromino::null, Tetromino::null, Tetromino::O, Tetromino::O},
           {Tetromino::null, Tetromino::null, Tetromino::O, Tetromino::O},
           {Tetromino::null, Tetromino::null, Tetromino::null, Tetromino::null},
           {Tetromino::null, Tetromino::null, Tetromino::null, Tetromino::null}},
          // S
          {{Tetromino::null, Tetromino::null, Tetromino::O, Tetromino::O},
           {Tetromino::null, Tetromino::null, Tetromino::O, Tetromino::O},
           {Tetromino::null, Tetromino::null, Tetromino::null, Tetromino::null},
           {Tetromino::null, Tetromino::null, Tetromino::null, Tetromino::null}},
          // W
          {{Tetromino::null, Tetromino::null, Tetromino::O, Tetromino::O},
           {Tetromino::null, Tetromino::null, Tetromino::O, Tetromino::O},
           {Tetromino::null, Tetromino::null, Tetromino::null, Tetromino::null},
           {Tetromino::null, Tetromino::null, Tetromino::null, Tetromino::null}},
      },
      // I
      {
          // N
          {{Tetromino::null, Tetromino::null, Tetromino::null, Tetromino::null},
           {Tetromino::I,    Tetromino::I,    Tetromino::I,    Tetromino::I},
           {Tetromino::null, Tetromino::null, Tetromino::null, Tetromino::null},
           {Tetromino::null, Tetromino::null, Tetromino::null, Tetromino::null}},
          // E
          {{Tetromino::null, Tetromino::null, Tetromino::I,    Tetromino::null},
           {Tetromino::null, Tetromino::null, Tetromino::I,    Tetromino::null},
           {Tetromino::null, Tetromino::null, Tetromino::I,    Tetromino::null},
           {Tetromino::null, Tetromino::null, Tetromino::I,    Tetromino::null}},
          // S
          {{Tetromino::null, Tetromino::null, Tetromino::null, Tetromino::null},
           {Tetromino::null, Tetromino::null, Tetromino::null, Tetromino::null},
           {Tetromino::I,    Tetromino::I,    Tetromino::I,    Tetromino::I},
           {Tetromino::null, Tetromino::null, Tetromino::null, Tetromino::null}},
          // W
          {{Tetromino::null, Tetromino::I,    Tetromino::null, Tetromino::null},
           {Tetromino::null, Tetromino::I,    Tetromino::null, Tetromino::null},
           {Tetromino::null, Tetromino::I,    Tetromino::null, Tetromino::null},
           {Tetromino::null, Tetromino::I,    Tetromino::null, Tetromino::null}},
      }
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
      typedef std::mt19937_64::result_type seed_type;
      Bag(seed_type);
      Tetromino getNext();
  };

  class Game {
    private:
    public:
      Tetromino boardState[20][10] = {};
      Tetromino holdPiece = Tetromino::null;
      Tetromino nextQueue[6];
      Bag bag;
    public:
      typedef Bag::seed_type seed_type;
      Game(seed_type);
      Tetromino getNext();
  };
}

#endif //SIMPLIFIED_TETRIS_H