#include "TetrisModelV1Trainer.h"
#include <algorithm>
#include <array>
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

vector<int> TetrisModelV1Trainer::runPopulation() {
    vector<int> results;
    for (int i = 0; i < population; ++i) {

        // TODO: make this more efficient
        game = SimplifiedTetris::Game(random());

        results.push_back(playGame(models[i], game));
    }
    return results;
}

void TetrisModelV1Trainer::trainRound() {
    auto results = runPopulation();

    // create array if indexes 0..population
    int idxs[population];
    std::iota(&idxs[0], &idxs[population], 0);

    static int const k = 20;

    // sort largest to smallest
    std::partial_sort(&idxs[0], &idxs[k], &idxs[population], [&results](int const & i, int const & j) {
        return results[i] > results[j];
    });

    std::cout << "Results: " << results << std::endl;

    std::cout << "Top " << k << " results: ";
    for (int i = 0; i < k; ++i) {
        std::cout << results[idxs[i]] << ", ";
    }
    std::cout << std::endl;
}
