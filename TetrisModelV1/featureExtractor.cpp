#include "featureExtractor.h"

namespace feats {

 // int rowsCleared(SimplifiedTetris::Board const & b) {
 //     int cleared = 0;
 //     for (int j = 0; j < SimplifiedTetris::Board::HEIGHT;j++) {
 //
 //         bool isCleared = true;
 //         for (int i = 0; i < SimplifiedTetris::Board::WIDTH; i++) {
 //             isCleared = isCleared && b.board[j][i];
 //         }
 //         cleared += isCleared ? 1 : 0;
 //     }
 //     return cleared;
 // }

  // int rowsCleared(SimplifiedTetris::Game const & g) {
  //     return g.clearedRows().size();
  // }

  // analysis is done per row
  HorizontalFeatures getHorizontalFeatures(SimplifiedTetris::Board const & board) {
      HorizontalFeatures outFeats{
          .colHeights={},  // initialize to all zeros
          .maxColHeight=0,
          .numUnused=0,
          .numHoles=0,
          .numWells=0,
          .numRowTrans=0
      };
      bool filled[SimplifiedTetris::Board::WIDTH] = {};
      for (int row = SimplifiedTetris::Board::HEIGHT - 1; row >= 0; --row) {
          bool prevEmpty = board.board[row][0] == SimplifiedTetris::Tetromino::null;
          for (int x = 0; x < SimplifiedTetris::Board::WIDTH; ++x) {
              bool const curEmpty = board.board[row][x] == SimplifiedTetris::Tetromino::null;
              if (curEmpty) {
                  ++outFeats.numUnused;
                  if (filled[x]) {
                      ++outFeats.numHoles;
                  } else if ((x == 0 || board.board[row][x - 1] != SimplifiedTetris::Tetromino::null)
                             && (x == SimplifiedTetris::Board::WIDTH - 1
                                 || board.board[row][x + 1] != SimplifiedTetris::Tetromino::null)) {
                      ++outFeats.numWells;
                  }
              } else if (!filled[x]) {
                  filled[x] = true;
                  int const height = row + 1;
                  outFeats.colHeights[x] = height;
                  if (height > outFeats.maxColHeight) {
                      outFeats.maxColHeight = height;
                  }
              }
              if (curEmpty != prevEmpty) {
                  outFeats.numRowTrans++;
              }
              prevEmpty = curEmpty;
          }
      }
      return outFeats;
  }

  // analysis is done per column
  VerticalFeatures getVerticalFeatures(SimplifiedTetris::Board const & board) {
      int numColTrans = 0;
      int numOverHoles = 0;
      vector<int> heights(SimplifiedTetris::Board::WIDTH);
      int maxColHeight = 0;
      for (int col = 0; col < SimplifiedTetris::Board::WIDTH; ++col) {
          bool reachedHole = false;
          bool prevEmpty = board.board[0][col] == SimplifiedTetris::Tetromino::null;
          for (int y = 0; y < SimplifiedTetris::Board::HEIGHT; ++y) {
              bool const curEmpty = board.board[y][col] == SimplifiedTetris::Tetromino::null;
              if (curEmpty) {
                  reachedHole = true;
              } else if (reachedHole) {
                  ++numOverHoles;
              }
              if (curEmpty != prevEmpty) {
                  ++numColTrans;
              }
              prevEmpty = curEmpty;
          }
      }
      // for (int col = 0; col < SimplifiedTetris::Board::WIDTH; ++col) {
      //     heights[col] = 0;
      //     for (int y = SimplifiedTetris::Board::HEIGHT - 1; y >= 0; --y) {
      //         if (board.board[y][col] != SimplifiedTetris::null) {
      //             int const height = y + 1;
      //             heights[col] = height;
      //             if (height > maxColHeight) {
      //                 maxColHeight = height;
      //             }
      //             break;
      //         }
      //     }
      // }
      return {
          // .colHeights=heights, // TODO: avoid copy
          .numOverHoles=numOverHoles,
          .numColTrans=numColTrans,
          // .maxColHeight=maxColHeight
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

  // std::pair<int, int> getNumTrans(SimplifiedTetris::Board const & board) {
  //     std::pair<int, int> numTrans;
  //
  //     // row and col transitions respectively
  //     numTrans.first = 0;
  //     numTrans.second = 0;
  //     int const HEIGHT = SimplifiedTetris::Board::HEIGHT;
  //     int const WIDTH = SimplifiedTetris::Board::WIDTH;
  //     for (int row = HEIGHT - 1; row >= 0; --row) {
  //         for (int col = 0; col < WIDTH; ++col) {
  //
  //             if (row < HEIGHT - 1) {
  //                 bool is_prev_row_filled = board.board[row + 1][col] != SimplifiedTetris::Tetromino::null;
  //                 bool is_curr_row_filled = board.board[row][col] != SimplifiedTetris::Tetromino::null;
  //
  //                 // check if row transition
  //                 if (is_prev_row_filled != is_curr_row_filled) {
  //                     numTrans.first++;
  //                 }
  //             }
  //
  //             if (col != 0) {
  //                 bool is_prev_col_filled = board.board[row][col - 1] != SimplifiedTetris::Tetromino::null;
  //                 bool is_curr_col_filled = board.board[row][col] != SimplifiedTetris::Tetromino::null;
  //
  //                 // check if col transition
  //                 if (is_prev_col_filled != is_curr_col_filled) {
  //                     numTrans.second++;
  //                 }
  //             }
  //         }
  //     }
  //     return numTrans;
  // }

}