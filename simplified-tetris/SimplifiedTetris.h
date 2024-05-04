#ifndef SIMPLIFIED_TETRIS_H
#define SIMPLIFIED_TETRIS_H

#include <cstddef>
#include <algorithm>
#include <array>
#include <random>
#include <tuple>
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
  static constexpr int PIECE_SIZE[] = {
      0, // empty
      3, // O
      4, // I
      3, // T
      3, // L
      3, // J
      3, // S
      3 // Z
  };
  static constexpr Tetromino FACINGS[8][4][4][4] = {
      {}, //empty
      // O
      { // O
          // N
          {{Tetromino::null, Tetromino::O,    Tetromino::O},
           {Tetromino::null, Tetromino::O,    Tetromino::O},
           {Tetromino::null, Tetromino::null, Tetromino::null}},
          // E
          {{Tetromino::null, Tetromino::O,    Tetromino::O},
           {Tetromino::null, Tetromino::O,    Tetromino::O},
           {Tetromino::null, Tetromino::null, Tetromino::null}},
          // S
          {{Tetromino::null, Tetromino::O,    Tetromino::O},
           {Tetromino::null, Tetromino::O,    Tetromino::O},
           {Tetromino::null, Tetromino::null, Tetromino::null}},
          // W
          {{Tetromino::null, Tetromino::O,    Tetromino::O},
           {Tetromino::null, Tetromino::O,    Tetromino::O},
           {Tetromino::null, Tetromino::null, Tetromino::null}}
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
      },
      { // T
          // N
          {{Tetromino::null, Tetromino::T,    Tetromino::null},
           {Tetromino::T,    Tetromino::T,    Tetromino::T},
           {Tetromino::null, Tetromino::null, Tetromino::null}},
          // E
          {{Tetromino::null, Tetromino::T,    Tetromino::null},
           {Tetromino::null, Tetromino::T,    Tetromino::T},
           {Tetromino::null, Tetromino::T,    Tetromino::null}},
          // S
          {{Tetromino::null, Tetromino::null, Tetromino::null},
           {Tetromino::T,    Tetromino::T,    Tetromino::T},
           {Tetromino::null, Tetromino::T,    Tetromino::null}},
          // W
          {{Tetromino::null, Tetromino::T,    Tetromino::null},
           {Tetromino::T,    Tetromino::T,    Tetromino::null},
           {Tetromino::null, Tetromino::T,    Tetromino::null}},
      },
      { // L
          // N
          {{Tetromino::null, Tetromino::null, Tetromino::L},
           {Tetromino::L,    Tetromino::L,    Tetromino::L},
           {Tetromino::null, Tetromino::null, Tetromino::null}},
          // E
          {{Tetromino::null, Tetromino::L,    Tetromino::null},
           {Tetromino::null, Tetromino::L,    Tetromino::null},
           {Tetromino::null, Tetromino::L,    Tetromino::L}},
          // S
          {{Tetromino::null, Tetromino::null, Tetromino::null},
           {Tetromino::L,    Tetromino::L,    Tetromino::L},
           {Tetromino::L,    Tetromino::null, Tetromino::null}},
          // W
          {{Tetromino::L,    Tetromino::L,    Tetromino::null},
           {Tetromino::null, Tetromino::L,    Tetromino::null},
           {Tetromino::null, Tetromino::L,    Tetromino::null}},
      },
      { // J
          // N
          {{Tetromino::J,    Tetromino::null, Tetromino::null},
           {Tetromino::J,    Tetromino::J,    Tetromino::J},
           {Tetromino::null, Tetromino::null, Tetromino::null}},
          // E
          {{Tetromino::null, Tetromino::J,    Tetromino::J},
           {Tetromino::null, Tetromino::J,    Tetromino::null},
           {Tetromino::null, Tetromino::J,    Tetromino::null}},
          // S
          {{Tetromino::null, Tetromino::null, Tetromino::null},
           {Tetromino::J,    Tetromino::J,    Tetromino::J},
           {Tetromino::null, Tetromino::null, Tetromino::J}},
          // W
          {{Tetromino::null, Tetromino::J,    Tetromino::null},
           {Tetromino::null, Tetromino::J,    Tetromino::null},
           {Tetromino::J,    Tetromino::J,    Tetromino::null}},
      },
      { // S
          // N
          {{Tetromino::null, Tetromino::S,    Tetromino::S},
           {Tetromino::S,    Tetromino::S,    Tetromino::null},
           {Tetromino::null, Tetromino::null, Tetromino::null}},
          // E
          {{Tetromino::null, Tetromino::S,    Tetromino::null},
           {Tetromino::null, Tetromino::S,    Tetromino::S},
           {Tetromino::null, Tetromino::null, Tetromino::S}},
          // S
          {{Tetromino::null, Tetromino::null, Tetromino::null},
           {Tetromino::null, Tetromino::S,    Tetromino::S},
           {Tetromino::S,    Tetromino::S,    Tetromino::null}},
          // W
          {{Tetromino::S,    Tetromino::null, Tetromino::null},
           {Tetromino::S,    Tetromino::S,    Tetromino::null},
           {Tetromino::null, Tetromino::S,    Tetromino::null}},
      },
      { // Z
          // N
          {{Tetromino::Z,    Tetromino::Z,    Tetromino::null},
           {Tetromino::null, Tetromino::Z,    Tetromino::Z},
           {Tetromino::null, Tetromino::null, Tetromino::null}},
          // E
          {{Tetromino::null, Tetromino::null, Tetromino::Z},
           {Tetromino::null, Tetromino::Z,    Tetromino::Z},
           {Tetromino::null, Tetromino::Z,    Tetromino::null}},
          // S
          {{Tetromino::null, Tetromino::null, Tetromino::null},
           {Tetromino::Z,    Tetromino::Z,    Tetromino::null},
           {Tetromino::null, Tetromino::Z,    Tetromino::Z}},
          // W
          {{Tetromino::null, Tetromino::Z,    Tetromino::null},
           {Tetromino::Z,    Tetromino::Z,    Tetromino::null},
           {Tetromino::Z,    Tetromino::null, Tetromino::null}},
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

  struct Move {
      Tetromino piece;
      int rotation;
      int x;
      int y;
  };

  class Board {
    public:
      static constexpr int WIDTH = 10;
      static constexpr int HEIGHT = 20;
      static constexpr int NUM_CELLS = HEIGHT * WIDTH;
      Tetromino board[HEIGHT][WIDTH] = {};
      void print() const;
  };

  class Game {
    private:
      Board board;
      Tetromino fallingPiece{};
      Tetromino holdPiece = Tetromino::null;
      Tetromino nextQueue[6]{};
      Bag bag;

      void initializeNextQueue();
      Tetromino getNext();
      static void placePieceOnBoard(Board &, Move const &);
      static int clearRowsOnBoard(Board &);
    public:
      typedef Bag::seed_type seed_type;
      explicit Game(seed_type);
      explicit Game(seed_type, Board);
      Tetromino getFalling() const { return fallingPiece; };
      Board const & getBoard() const { return board; };
      void printBoard() const;
      void getPlacements(std::vector<Move> &);
      std::tuple<Board *, int> previewMove(Move const &) const;
      int doMove(Move const &);
  };
}

#endif //SIMPLIFIED_TETRIS_H