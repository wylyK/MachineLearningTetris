#include "TetrisModelV1Trainer.h"

TetrisModelV1Trainer::TetrisModelV1Trainer(size_t population, seed_type seed) :
    population(population),
    random(seed),
    game(random())
{
    for (size_t i = 0; i < population; ++i) {
        models.emplace_back();
    }
}

void TetrisModelV1Trainer::trainRound() {
    for (int i = 0; i < population; ++i) {
        ;
    }
}
