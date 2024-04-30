#ifndef SIMPLIFIED_TETRIS_FEATUREEXTRACTOR_H
#define SIMPLIFIED_TETRIS_FEATUREEXTRACTOR_H
#include <vector>
#include "../simplified-tetris/SimplifiedTetris.h"

namespace feats {
  using std::vector;


  vector<int> columnHeights(SimplifiedTetris::Board  const &);
 // int max(vector<int> heights);
  int rowsCleared(SimplifiedTetris::Board const &);
  int holeDepth(SimplifiedTetris::Board const &);
  int getNumHoles(SimplifiedTetris::Board const &);
  int getNumWells(SimplifiedTetris::Board const &);
}

#endif //SIMPLIFIED_TETRIS_FEATUREEXTRACTOR_H
