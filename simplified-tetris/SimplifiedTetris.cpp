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
      int const size = PIECE_SIZE[move.piece];
      for (int i = 0; i < size; i++) {
          for (int j = 0; j < size; j++) {
              if (FACINGS[move.piece][move.rotation][i][j] == Tetromino::null)
                  continue;
              board.board[move.y - i][move.x + j] = move.piece;
          }
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
              std::cout << (int)board[i][j] << " ";
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
                  for (int subX = 0; subX < PIECE_SIZE[fallingPiece]; ++subX) {
                      for (int subY = 0; subY < PIECE_SIZE[fallingPiece]; ++subY) {
                          if (FACINGS[fallingPiece][f][subY][subX] == Tetromino::null) {
                              // this block in the tetromino is empty, so we don't need to check it
                              continue;
                          }

                          // x axis for board: left=0
                          // x axis for piece: left=0
                          int const x = pieceX + subX;
                          // y axis for board: bottom=0
                          // y axis for piece: top=0
                          int const y = pieceY - subY;

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
                      if (!locationValid) {
                          break;
                      } // end for subY
                  } // end for subX
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
      int rowsCleared = 0;
      for (int j = 0; j < Board::HEIGHT; j++) {

          bool full = true;
          for (int i = 0; i < Board::WIDTH; i++) {
              if (board.board[j][i] == Tetromino::null) {
                  full = false;
              }
          }

          if (full) {
              // null the row (required for edge case at the top of the board)
              for (int i = 0; i < Board::WIDTH; i++) {
                  board.board[j][i] = null;
              }
              ++rowsCleared;
          } else if (rowsCleared > 0) {
              for (int i = 0; i < Board::WIDTH; i++) {
                  board.board[j - rowsCleared][i] = board.board[j][i];
                  board.board[j][i] = null;
              }
          }
      }
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
