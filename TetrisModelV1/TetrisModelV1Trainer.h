#ifndef SIMPLIFIED_TETRIS_TETRISMODELV1TRAINER_H
#define SIMPLIFIED_TETRIS_TETRISMODELV1TRAINER_H
#include <random>
#include <torch/torch.h>
#include "../simplified-tetris/SimplifiedTetris.h"
#include "TetrisModelV1.h"

using std::vector;

class TetrisModelV1Trainer {
  private:
    std::mt19937_64 random;
    vector<TetrisModelV1> models;
    SimplifiedTetris::Game game;
    size_t population;
  public:
    typedef std::mt19937_64::result_type seed_type;
    explicit TetrisModelV1Trainer(size_t population, seed_type seed);
    void trainRound();
};

#endif //SIMPLIFIED_TETRIS_TETRISMODELV1TRAINER_H
