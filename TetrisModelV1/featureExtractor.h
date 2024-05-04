#ifndef SIMPLIFIED_TETRIS_FEATUREEXTRACTOR_H
#define SIMPLIFIED_TETRIS_FEATUREEXTRACTOR_H
#include <vector>
#include "../simplified-tetris/SimplifiedTetris.h"

using std::vector;

namespace feats {
  struct verticalFeatures {
      vector<int> heights;
      int numOverHoles;
      int numColTrans;
      int maxHeight;

  };
  struct horizontalFeatures {
      int numRowTrans;
      int numUnused;
      int numWells;
      int numHoles;
      int rowsCleared;
  };
  vector<int> columnHeights(SimplifiedTetris::Board const &);
  int maxHeight(vector<int> const & heights);
  int rowsCleared(SimplifiedTetris::Board const &);
  // int holeDepth(SimplifiedTetris::Board const &);
  int getNumHoles(SimplifiedTetris::Board const &);
  int getNumWells(SimplifiedTetris::Board const &);
  int getNumUnused(SimplifiedTetris::Board const &);
  int getNumOverHoles(SimplifiedTetris::Board const &);
  int getNumRowTrans(SimplifiedTetris::Board const &);
  int getNumColTrans(SimplifiedTetris::Board const &);
  std::pair<int, int>getNumTrans(SimplifiedTetris::Board const &);
  std::tuple<int, int> horizontalFeatures(SimplifiedTetris::Board const & board);
  std::tuple<vector<int>, int, int> verticalFeatures(SimplifiedTetris::Board const & board);
}

#endif //SIMPLIFIED_TETRIS_FEATUREEXTRACTOR_H
