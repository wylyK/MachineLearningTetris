
#ifndef SIMPLIFIED_TETRIS_FEATUREEXTRACTOR_H
#define SIMPLIFIED_TETRIS_FEATUREEXTRACTOR_H
#include <vector>
namespace feats{
  using std::vector;
  vector<int> columnHeights(Game::board b);
  int max(vector<int> heights);



}

#endif //SIMPLIFIED_TETRIS_FEATUREEXTRACTOR_H
