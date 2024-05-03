#ifndef SIMPLIFIED_TETRIS_TETRISMODELV1RUNNER_H
#define SIMPLIFIED_TETRIS_TETRISMODELV1RUNNER_H
#include <torch/torch.h>

#include "TetrisModelV1.h"
#include "../simplified-tetris/SimplifiedTetris.h"

class TetrisModelV1Runner {
  private:
    TetrisModelV1 model;
    SimplifiedTetris::Game game;
    torch::Tensor weights;
  public:
    typedef SimplifiedTetris::Game::seed_type seed_type;
    explicit TetrisModelV1Runner(seed_type);
    void play();
};

#endif //SIMPLIFIED_TETRIS_TETRISMODELV1RUNNER_H
