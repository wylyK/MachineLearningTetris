#ifndef SIMPLIFIED_TETRIS_TETRISMODELV2TRAINER_H
#define SIMPLIFIED_TETRIS_TETRISMODELV2TRAINER_H
#include <random>
#include <torch/torch.h>
#include "../simplified-tetris/SimplifiedTetris.h"
#include "TetrisModelV2.h"

using std::vector;

class TetrisModelV1Trainer {
  public:
    static constexpr float GENETIC_STDDEV = .5;
  private:
    std::mt19937_64 random;
    torch::Generator torchGen;
    vector<TetrisModelV1 *> models;
    SimplifiedTetris::Game game;
    size_t population;
  public:
    typedef std::mt19937_64::result_type seed_type;
    explicit TetrisModelV1Trainer(size_t population, seed_type seed);
    vector<std::tuple<int, int>> runPopulation();
    void trainRound();
};

#endif //SIMPLIFIED_TETRIS_TETRISMODELV2TRAINER_H
