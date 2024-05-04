#ifndef SIMPLIFIED_TETRIS_FEATUREEXTRACTOR_H
#define SIMPLIFIED_TETRIS_FEATUREEXTRACTOR_H
#include <vector>
#include "../simplified-tetris/SimplifiedTetris.h"

using std::vector;

namespace feats {

  // analysis is done per column
  struct VerticalFeatures {
      vector<int> colHeights;
      int numOverHoles;
      int numColTrans;
      int maxColHeight;
  };

  // analysis is done per row
  struct HorizontalFeatures {
      int numRowTrans;
      int numUnused;
      int numHoles;
      int numWells;
      // int rowsCleared;
  };

  HorizontalFeatures getHorizontalFeatures(SimplifiedTetris::Board const &);
  VerticalFeatures getVerticalFeatures(SimplifiedTetris::Board const &);

  // int rowsCleared(SimplifiedTetris::Board const &);
  // int holeDepth(SimplifiedTetris::Board const &);
  // std::pair<int, int>getNumTrans(SimplifiedTetris::Board const &);
  // std::tuple<int, int> horizontalFeatures(SimplifiedTetris::Board const & board);
  // std::tuple<vector<int>, int, int> verticalFeatures(SimplifiedTetris::Board const & board);
}

#endif //SIMPLIFIED_TETRIS_FEATUREEXTRACTOR_H
