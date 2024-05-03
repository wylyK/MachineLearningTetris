#ifndef SIMPLIFIED_TETRIS_TETRISMODELV1TRAINER_H
#define SIMPLIFIED_TETRIS_TETRISMODELV1TRAINER_H
#include <torch/torch.h>
#include "TetrisModelV1.h"

using std::vector;

class TetrisModelV1Trainer {
  private:
    vector<TetrisModelV1> models;
    vector<torch::Tensor> weights;
  public:
    TetrisModelV1Trainer();
};

#endif //SIMPLIFIED_TETRIS_TETRISMODELV1TRAINER_H
