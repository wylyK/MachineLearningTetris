#include "featureExtractor.h"

namespace feats {

  vector<int> columnHeights(SimplifiedTetris::Game::Board b) {
      vector<int> heights;
      for (int i = 0; i < SimplifiedTetris::Game::Board::WIDTH; i++) {
          for (int j = SimplifiedTetris::Game::Board::HEIGHT; j > -1; j++) {
              if (b.board[j][i] != SimplifiedTetris::null) {
                  heights[i] = j + 1;
                  break;
              }
              heights[i] = -1;
          }
      }
      return heights;
  }

  int getNumHoles(SimplifiedTetris::Game::Board const & board) {
      bool filled[SimplifiedTetris::Game::Board::WIDTH] = {};
      int holes = 0;
      for (int row = SimplifiedTetris::Game::Board::HEIGHT - 1; row >= 0; --row) {
          for (int col = 0; col < SimplifiedTetris::Game::Board::WIDTH; ++col) {
              if (board.board[row][col] == SimplifiedTetris::Tetromino::null) {
                  if (filled[col]) {
                      ++holes;
                  }
              } else {
                  filled[col] = true;
              }
          }
      }
      return holes;
  }

  int getNumWells(SimplifiedTetris::Game::Board const & board) {
      bool filled[SimplifiedTetris::Game::Board::WIDTH] = {};
      int wells = 0;
      for (int row = SimplifiedTetris::Game::Board::HEIGHT - 1; row >= 0; --row) {
          for (int col = 0; col < SimplifiedTetris::Game::Board::WIDTH; ++col) {
              if (board.board[row][col] == SimplifiedTetris::Tetromino::null) {
                  if (!filled[col]
                      && (col == 0 || board.board[row][col - 1] != SimplifiedTetris::Tetromino::null)
                      && (   col == SimplifiedTetris::Game::Board::WIDTH - 1
                             || board.board[row][col + 1] != SimplifiedTetris::Tetromino::null)) {
                      ++wells;
                  }
              } else {
                  filled[col] = true;
              }
          }
      }
      return wells;
  }

  int getNumUnused(SimplifiedTetris::Game::Board const & board) {
      int numUnused = 0;
    for (int row = SimplifiedTetris::Game::Board::HEIGHT - 1; row >= 0; --row) {
        for (int col = 0; col < SimplifiedTetris::Game::Board::WIDTH; ++col) {
            if (board.board[row][col] == SimplifiedTetris::Tetromino::null) {
                numUnused++;
            }
        }
    }
    return numUnused;
  }



}