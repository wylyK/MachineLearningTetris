#include "featureExtractor.h"

namespace feats {

  vector<int> columnHeights(SimplifiedTetris::Board const & b) {
      vector<int> heights(10);

      for (int i = 0; i < SimplifiedTetris::Board::WIDTH; i++) {
          heights[i] = 0;
          for (int j = SimplifiedTetris::Board::HEIGHT - 1; j > -1; j--) {
              if (b.board[j][i] != SimplifiedTetris::null) {
                  heights[i]  = j + 1;
                  break;
              }

          }
      }
      return heights;
  }

  int getNumHoles(SimplifiedTetris::Board const & board) {
      bool filled[SimplifiedTetris::Board::WIDTH] = {};
      int holes = 0;
      for (int row = SimplifiedTetris::Board::HEIGHT - 1; row >= 0; --row) {
          for (int col = 0; col < SimplifiedTetris::Board::WIDTH; ++col) {
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

  int getNumWells(SimplifiedTetris::Board const & board) {
      bool filled[SimplifiedTetris::Board::WIDTH] = {};
      int wells = 0;
      for (int row = SimplifiedTetris::Board::HEIGHT - 1; row >= 0; --row) {
          for (int col = 0; col < SimplifiedTetris::Board::WIDTH; ++col) {
              if (board.board[row][col] == SimplifiedTetris::Tetromino::null) {
                  if (!filled[col]
                      && (col == 0 || board.board[row][col - 1] != SimplifiedTetris::Tetromino::null)
                      && (   col == SimplifiedTetris::Board::WIDTH - 1
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

}