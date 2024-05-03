#ifndef SIMPLIFIED_TETRIS_FEATUREEXTRACTOR_H
#define SIMPLIFIED_TETRIS_FEATUREEXTRACTOR_H
#include <vector>
#include "../simplified-tetris/SimplifiedTetris.h"

using std::vector;

namespace feats {
  vector<int> columnHeights(SimplifiedTetris::Board const &);
  // int max(vector<int> heights);
  int rowsCleared(SimplifiedTetris::Board const &);
  // int holeDepth(SimplifiedTetris::Board const &);
  int getNumHoles(SimplifiedTetris::Board const &);
  int getNumWells(SimplifiedTetris::Board const &);
  int getNumUnused(SimplifiedTetris::Board const &);
  int getNumOverHoles(SimplifiedTetris::Board const &);
  int getNumRowTrans(SimplifiedTetris::Board const &);
  int getNumColTrans(SimplifiedTetris::Board const &);
  std::pair<int, int>getNumTrans(SimplifiedTetris::Board const &);
}

#endif //SIMPLIFIED_TETRIS_FEATUREEXTRACTOR_H
