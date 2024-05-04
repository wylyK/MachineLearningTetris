#ifndef SIMPLIFIED_TETRIS_H
#define SIMPLIFIED_TETRIS_H
#include <cstddef>
#include <algorithm>
#include <array>
#include <random>
#include <tuple>
#include "pieces.h"

namespace SimplifiedTetris {
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
      int previewMove(Move const &, Board &) const;
      int doMove(Move const &);
  };
}

#endif //SIMPLIFIED_TETRIS_H