#ifndef SIMPLIFIED_TETRIS_FEATUREEXTRACTOR_H
#define SIMPLIFIED_TETRIS_FEATUREEXTRACTOR_H
#include <vector>
#include "../simplified-tetris/SimplifiedTetris.h"

namespace feats {
  using std::vector;

  vector<int> columnHeights(SimplifiedTetris::Board b);
  int max(vector<int> heights);

  int getNumHoles(SimplifiedTetris::Board const &);

  int getNumWells(SimplifiedTetris::Board const &);

  int getNumUnused(SimplifiedTetris::Board const &);
}


#endif //SIMPLIFIED_TETRIS_FEATUREEXTRACTOR_H
