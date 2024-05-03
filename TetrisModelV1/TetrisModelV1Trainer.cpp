#include "TetrisModelV1Trainer.h"
#include "TetrisModelV1Runner.h"

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
    vector<int> results;
    for (int i = 0; i < population; ++i) {

        // TODO: make this more efficient
        game = SimplifiedTetris::Game(random());

        results.push_back(playGame(models[i], game));
    }
    std::cout << "Results: " << results << std::endl;
}
