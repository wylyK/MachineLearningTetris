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
  Game::Game(Game::seed_type seed, SimplifiedTetris::Board b) :
      bag(seed)
  {
      fallingPiece = bag.getNext();
      for (Tetromino & t : nextQueue) {
          t = bag.getNext();
      }
      board = b;
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

  std::vector<std::tuple<int, int, int>> Game::getPlacements() {
      std::vector<std::tuple<int, int, int>> validPlacements;
      for (int f = 0; f < 4; ++f) {
          for (int pieceX = -2; pieceX <= Board::WIDTH - 2; ++pieceX) {
              for (int pieceY = Board::HEIGHT + 1; pieceY > 0; --pieceY) {
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
  std::vector<int> Game::clearedRows(){
      std::vector<int> rows;
      for (int j = 0; j < Board::HEIGHT; j++){
          bool cleared = true;
          for (int i = 0; i < Board::WIDTH; i++){
              cleared = cleared && board.board[j][i];
          }
          if (cleared){
              rows.push_back(j);
          }
      }
      return rows;
  }
  void Game::clearFull(){
      std::vector<int> full = clearedRows();
      auto const * boardCopy = new Board(board);
      int falls = 0;
      int nextCleared = 0;
      for (int j = 0; j < Board::HEIGHT; j++){
          if (j == full[nextCleared]) {
              for (int i = 0; i < Board::WIDTH; i++){
                  board.board[j][i] = null;
              }
              falls++;
              nextCleared < full.size() - 1 ? nextCleared++: 0;
          }
          else {
              for (int i = 0; i < Board::WIDTH; i++) {
                  if (falls > 0) {
                      board.board[j - falls][i] = board.board[j][i];
                      board.board[j][i] = null;
                  }
              }
          }
      }
  }
  Board * Game::previewMove(int const rotation, int const x, int const y) {
      auto * const boardCopy = new Board(board);
      Tetromino const piece = getFalling();
      int const size = PIECE_SIZE[piece];

      for (int i = 0; i < size; i++) {
          for (int j = 0; j < size; j++) {
              if (FACINGS[piece][rotation][i][j] == Tetromino::null)
                  continue;
              boardCopy->board[y - i][x + j] = piece;
          }
      }
      return boardCopy;
  }
}
