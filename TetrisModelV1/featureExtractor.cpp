#include "featureExtractor.h"

namespace feats {

  vector<int> columnHeights(SimplifiedTetris::Board const & b) {
      vector<int> heights(SimplifiedTetris::Board::WIDTH);
      for (int i = 0; i < SimplifiedTetris::Board::WIDTH; i++) {
          heights[i] = 0;
          for (int j = SimplifiedTetris::Board::HEIGHT - 1; j > -1; j--) {
              if (b.board[j][i] != SimplifiedTetris::null) {
                  heights[i] = j + 1;
                  break;
              }

          }
      }
      return heights;
  }

 int rowsCleared(SimplifiedTetris::Board const & b) {
     int cleared = 0;
     for (int j = 0; j < SimplifiedTetris::Board::HEIGHT;j++) {

         bool isCleared = true;
         for (int i = 0; i < SimplifiedTetris::Board::WIDTH; i++) {
             isCleared = isCleared && b.board[j][i];
         }
         cleared += isCleared ? 1 : 0;
     }
     return cleared;
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

  int getNumUnused(SimplifiedTetris::Board const & board) {
      int numUnused = 0;
      for (int row = SimplifiedTetris::Board::HEIGHT - 1; row >= 0; --row) {
          for (int col = 0; col < SimplifiedTetris::Board::WIDTH; ++col) {
              if (board.board[row][col] == SimplifiedTetris::Tetromino::null) {
                  numUnused++;
              }
          }
      }
      return numUnused;
  }
  
  int getNumOverHoles(SimplifiedTetris::Board const & board) {
      int numOverHoles = 0;
      for (int col = 0; col < SimplifiedTetris::Board::WIDTH; ++col) {
          bool reachedHole = false;
          for (int row = 0; row < SimplifiedTetris::Board::HEIGHT; ++row) {
              if (board.board[row][col] == SimplifiedTetris::Tetromino::null) {
                  reachedHole = true;
              }
              if(board.board[row][col] != SimplifiedTetris::Tetromino::null && reachedHole) {
                  numOverHoles++;
              }
          }
      }
      return numOverHoles;
  }

  // int rowsCleared(SimplifiedTetris::Game const & g) {
  //     return g.clearedRows().size();
  // }

  int maxHeight(vector<int> const & heights) {
      int max = 0;
      for (int const height : heights) {
          max = std::max(max, height);
      }
      return max;
  }

  // analysis is done per row
  HorizontalFeatures getHorizontalFeatures(SimplifiedTetris::Board const & board) {
      int numRowTrans = 0;
      for (int row = SimplifiedTetris::Board::HEIGHT - 1; row >= 0; --row) {
          bool is_prev_used = board.board[row][0] != SimplifiedTetris::Tetromino::null;
          for (int col = 1; col < SimplifiedTetris::Board::WIDTH; ++col) {
              bool is_curr_used = board.board[row][col] != SimplifiedTetris::Tetromino::null;
              if (is_prev_used != is_curr_used) {
                  numRowTrans++;
              }
              is_prev_used = is_curr_used;
          }
      }
      return {
          .numRowTrans=numRowTrans
      };
  }

  // analysis is done per column
  VerticalFeatures getVerticalFeatures(SimplifiedTetris::Board const & board) {
      int numColTrans = 0;
      for (int col = 0; col < SimplifiedTetris::Board::WIDTH; ++col) {
          bool prevEmpty = board.board[0][col] == SimplifiedTetris::Tetromino::null;
          for (int y = 0; y < SimplifiedTetris::Board::HEIGHT; ++y) {
              bool const curEmpty = board.board[y][col] == SimplifiedTetris::Tetromino::null;
              if (prevEmpty != curEmpty) {
                  ++numColTrans;
              }
              prevEmpty = curEmpty;
          }
      }
      return {
          .numColTrans=numColTrans
      };
  }

  // //analysis is done per column
  // //iterate over columns: columnHeights, numHoles, row transitions
  // std::tuple<vector<int>, int, int> verticalFeatures(SimplifiedTetris::Board const & board) {
  //     int numOverHoles = 0;
  //     vector<int> heights(10);
  //     int numColTrans = 0;
  //
  //     for (int row = 0; row < SimplifiedTetris::Board::WIDTH; row++) {
  //         bool reachedHole = false;
  //         bool is_prev_used = board.board[row][0] != SimplifiedTetris::Tetromino::null;
  //         for (int col = SimplifiedTetris::Board::HEIGHT - 1; col > -1; col--) {
  //             if (board.board[row][col] == SimplifiedTetris::Tetromino::null) {
  //                 reachedHole = true;
  //             }
  //             if(board.board[row][col] != SimplifiedTetris::Tetromino::null && reachedHole) {
  //                 numOverHoles++;
  //             }
  //
  //         }
  //     }
  // }

  std::pair<int, int> getNumTrans(SimplifiedTetris::Board const & board) {
      std::pair<int, int> numTrans;

      // row and col transitions respectively
      numTrans.first = 0;
      numTrans.second = 0;
      int const HEIGHT = SimplifiedTetris::Board::HEIGHT;
      int const WIDTH = SimplifiedTetris::Board::WIDTH;
      for (int row = HEIGHT - 1; row >= 0; --row) {
          for (int col = 0; col < WIDTH; ++col) {

              if (row < HEIGHT - 1) {
                  bool is_prev_row_filled = board.board[row + 1][col] != SimplifiedTetris::Tetromino::null;
                  bool is_curr_row_filled = board.board[row][col] != SimplifiedTetris::Tetromino::null;

                  // check if row transition
                  if (is_prev_row_filled != is_curr_row_filled) {
                      numTrans.first++;
                  }
              }

              if (col != 0) {
                  bool is_prev_col_filled = board.board[row][col - 1] != SimplifiedTetris::Tetromino::null;
                  bool is_curr_col_filled = board.board[row][col] != SimplifiedTetris::Tetromino::null;

                  // check if col transition
                  if (is_prev_col_filled != is_curr_col_filled) {
                      numTrans.second++;
                  }
              }
          }
      }
      return numTrans;
  }

}