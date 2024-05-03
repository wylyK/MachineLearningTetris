#ifndef SIMPLIFIED_TETRIS_TETRISMODELV1TRAINER_H
#define SIMPLIFIED_TETRIS_TETRISMODELV1TRAINER_H
#include <torch/torch.h>
#include "TetrisModelV1.h"

using std::vector;

class TetrisModelV1Trainer {
  private:
    vector<TetrisModelV1> models;
  public:
    explicit TetrisModelV1Trainer(size_t population);
};

#endif //SIMPLIFIED_TETRIS_TETRISMODELV1TRAINER_H
