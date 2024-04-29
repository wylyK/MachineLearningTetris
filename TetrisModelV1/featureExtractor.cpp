#include "featureExtractor.h"

namespace feats {

  vector<int> columnHeights(SimplifiedTetris::Board const & b) {
      vector<int> heights;
      for (int i = 0; i < SimplifiedTetris::Board::WIDTH; i++) {
          for (int j = SimplifiedTetris::Board::HEIGHT; j > -1; j++) {
              if (b.board[j][i] != SimplifiedTetris::null) {
                  heights[i] = j + 1;
                  break;
              }
              heights[i] = -1;
          }
      }
      return heights;
  }

 int rowsCleared(SimplifiedTetris::Game::Board b){
  int cleared = 0;
  for (auto & j : b.board){
      bool isCleared = true;
      for (int i = 0; i < SimplifiedTetris::Game::Board::WIDTH; i++){
          isCleared  = isCleared && j[i];
      }
      cleared += isCleared;
  }
  return cleared;


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
                      && (col == SimplifiedTetris::Board::WIDTH - 1
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