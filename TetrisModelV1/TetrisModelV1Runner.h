#ifndef SIMPLIFIED_TETRIS_TETRISMODELV1RUNNER_H
#define SIMPLIFIED_TETRIS_TETRISMODELV1RUNNER_H
#include <torch/torch.h>

#include "TetrisModelV1.h"
#include "../simplified-tetris/SimplifiedTetris.h"

std::tuple<int, int> playGame(TetrisModelV1 &, SimplifiedTetris::Game &);

#endif //SIMPLIFIED_TETRIS_TETRISMODELV1RUNNER_H
