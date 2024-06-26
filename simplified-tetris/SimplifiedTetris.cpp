#include "SimplifiedTetris.h"
#include <iostream>

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
      initializeNextQueue();
  }

  Game::Game(Game::seed_type const seed, SimplifiedTetris::Board b) :
      bag(seed),
      board(b)
  {
      initializeNextQueue();
  }

  void Game::initializeNextQueue() {
      fallingPiece = bag.getNext();
      for (Tetromino & t : nextQueue) {
          t = bag.getNext();
      }
  }

  void Game::placePieceOnBoard(Board & board, Move const & move) {
      for (auto const & blockCoord : PIECE_IDXS[move.piece][move.rotation]) {
          board.board[move.y - blockCoord[0]][move.x + blockCoord[1]] = move.piece;
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

  void Board::print() const {
      for (int i = Board::HEIGHT - 1; i >= 0; --i) {
          for (int j = 0; j < Board::WIDTH; ++j) {
              std::cout << COLOR_STRINGS.at(board[i][j]) << " ";
          }
          std::cout << std::endl;
      }
  }

  void Game::printBoard() const {
      std::cout << "game state:" << std::endl;
      board.print();
  }

  void Game::getPlacements(std::vector<Move> & placementsList) {
      for (int f = 0; f < 4; ++f) {
          for (int pieceX = -2; pieceX <= Board::WIDTH - 2; ++pieceX) {
              for (int pieceY = Board::HEIGHT + 1; pieceY > 0; --pieceY) {
                  bool locationValid = true;
                  bool onFloor = false;
                  bool overlap = false;
                  for (auto const & blockCoord : PIECE_IDXS[fallingPiece][f]) {
                      // x axis for board: left=0
                      // x axis for piece: left=0
                      int const x = pieceX + blockCoord[1];
                      // y axis for board: bottom=0
                      // y axis for piece: top=0
                      int const y = pieceY - blockCoord[0];

                      if (x < 0 || x >= 10 || y < 0 || y >= Board::HEIGHT) {
                          // piece is out of bounds
                          locationValid = false;
                          break;
                      }
                      if (board.board[y][x] != Tetromino::null) {
                          // piece overlaps with a piece already on the board
                          overlap = true;
                          locationValid = false;
                          break;
                      }
                      if (y == 0 || board.board[y - 1][x] != Tetromino::null) {
                          onFloor = true;
                      }
                  }
                  if (onFloor) {
                      if (locationValid) {
                          placementsList.push_back({fallingPiece, f, pieceX, pieceY});
                      }

                      // we have been moving the tetromino down a column and it has hit the floor,
                      // so
                      break;
                  } else if (overlap) {
                      // most cases the onFloor check above should handle this, but if even the top of the column is
                      // obstructed, then we don't want to waste time checking the entire column.
                      break;
                  }
              } // end for pieceY
          } // end for pieceX
      } // end for f
  }

  int Game::clearRowsOnBoard(SimplifiedTetris::Board & board) {
      // std::cout << "before:" << std::endl;
      // board.print();

      int rowsCleared = 0;
      for (int row = 0; row < Board::HEIGHT; ++row) {

          bool full = true;
          for (int x = 0; x < Board::WIDTH; ++x) {
              if (board.board[row][x] == Tetromino::null) {
                  full = false;
                  break;
              }
          }

          if (full) {
              ++rowsCleared;
          } else if (rowsCleared > 0) {
              for (int x = 0; x < Board::WIDTH; ++x) {
                  board.board[row - rowsCleared][x] = board.board[row][x];
              }
          }
      }

      // make the new rows at the top empty
      for (int row = Board::HEIGHT - rowsCleared; row < Board::HEIGHT; ++row) {
          for (int x = 0; x < Board::WIDTH; ++x) {
              board.board[row][x] = Tetromino::null;
          }
      }

      // std::cout << "after:" << std::endl;
      // board.print();
      // if (rowsCleared) {
      //     abort();
      // }

      return rowsCleared;
  }

  int Game::previewMove(Move const & move, Board & boardOut) const {
      boardOut = board;
      placePieceOnBoard(boardOut, move);
      int rowsCleared = clearRowsOnBoard(boardOut);
      return rowsCleared;
  }

  int Game::doMove(Move const & move) {
      placePieceOnBoard(board, move);
      int const rowsCleared = clearRowsOnBoard(board);
      fallingPiece = getNext();
      return rowsCleared;
  }

}
