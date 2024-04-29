#ifndef SIMPLIFIED_TETRIS_FEATUREEXTRACTOR_H
#define SIMPLIFIED_TETRIS_FEATUREEXTRACTOR_H
#include <vector>
#include "../simplified-tetris/SimplifiedTetris.h"

namespace feats {
  using std::vector;
<<<<<<< HEAD
  vector<int> columnHeights(Game::board b);
  int rowsCleared(Game::board b);
  int holeDepth(Game)
=======

  vector<int> columnHeights(SimplifiedTetris::Board b);
  int max(vector<int> heights);

  int getNumHoles(SimplifiedTetris::Board const &);
>>>>>>> features

  int getNumWells(SimplifiedTetris::Board const &);
}

#endif //SIMPLIFIED_TETRIS_FEATUREEXTRACTOR_H
