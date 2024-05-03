#include "TetrisModelV1Runner.h"

TetrisModelV1Runner::TetrisModelV1Runner(TetrisModelV1Runner::seed_type const seed) :
    game(seed)
{
    // mean 0, stddev .5
    weights = torch::normal(0, .5, TetrisModelV1::NUM_PARAMETERS);
    model.setParams(weights);
}
