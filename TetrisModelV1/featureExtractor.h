#ifndef SIMPLIFIED_TETRIS_FEATUREEXTRACTOR_H
#define SIMPLIFIED_TETRIS_FEATUREEXTRACTOR_H
#include <vector>
#include "../simplified-tetris/SimplifiedTetris.h"

using std::vector;

namespace feats {

  // analysis is done per column
  struct VerticalFeatures {
      int numOverHoles;
      int numColTrans;
  };

  // analysis is done per row
  struct HorizontalFeatures {
      int colHeights[SimplifiedTetris::Board::WIDTH];
      int maxColHeight;
      int numUnused;
      int numHoles;
      int numWells;
      // int rowsCleared;
      int numRowTrans;
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
