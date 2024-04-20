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

  void Game::printBoard() const {
      std::cout << "game state:" << std::endl;
      for (int i = 0; i < 20; ++i) {
          for (int j = 0; j < 10; ++j) {
              std::cout << (int)board.board[i][j] << " ";
          }
          std::cout << std::endl;
      }
  }

  std::vector<std::tuple<std::size_t, std::size_t, std::size_t>> Game::getPlacements() {
      std::vector<std::tuple<std::size_t, std::size_t, std::size_t>> validPlacements;
      for (int f = 0; f < 4; ++f) {
          for (int pieceX = -2; pieceX <= 8; ++pieceX) {
              for (int pieceY = 21; pieceY > 0; --pieceY) {
                  bool locationValid = true;
                  bool onFloor = false;
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
                          // x axis for piece: top=0
                          int const y = pieceY - subY;

                          if (x < 0 || x >= 10 || y < 0 || board.board[y][x] != Tetromino::null) {
                              locationValid = false;
                              break;
                          }
                          if (y == 0 || board.board[y - 1][x] != Tetromino::null) {
                              onFloor = true;
                          }
                      }
                      if (!locationValid) {
                          break;
                      }
                  }
                  if (locationValid && onFloor) {
                      validPlacements.emplace_back(f, pieceX, pieceY);
                  }
              }
          }
      }
      return validPlacements;
  }

}
