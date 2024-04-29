//
// Created by Rodrigo on 4/27/2024.
//

#include "featureExtractor.h"
#include "../simplified-tetris/SimplifiedTetris.h"
namespace feats {
  vector<int> columnHeights(SimplifiedTetris::Game::Board b) {
    vector<int> heights;
    for (int i = 0; i < SimplifiedTetris::Game::Board::WIDTH; i++){
        for(int j = SimplifiedTetris::Game::Board::HEIGHT; j > -1 ; j++){
            if (b.board[j][i] != SimplifiedTetris::null){
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
  }

}