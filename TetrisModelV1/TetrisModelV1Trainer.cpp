#include "TetrisModelV1Trainer.h"
#include <algorithm>
#include <array>
#include <torch/torch.h>
#include "TetrisModelV1Runner.h"

TetrisModelV1Trainer::TetrisModelV1Trainer(size_t population, seed_type seed) :
    population(population),
    random(seed),
    game(random())
{
    for (size_t i = 0; i < population; ++i) {
        // TODO: implement destructor
        models.push_back(new TetrisModelV1());
    }
}

vector<int> TetrisModelV1Trainer::runPopulation() {
    vector<int> results;
    for (int i = 0; i < population; ++i) {

        // TODO: make this more efficient
        game = SimplifiedTetris::Game(random());

        results.push_back(playGame(*models[i], game));
    }
    return results;
}

void TetrisModelV1Trainer::trainRound() {
    auto results = runPopulation();
    // std::cout << "Results: " << results << std::endl;

    // create array if indexes 0..population
    int idxs[population];
    std::iota(&idxs[0], &idxs[population], 0);

    static int const k = 20;

    // sort largest to smallest
    std::partial_sort(&idxs[0], &idxs[k], &idxs[population], [&results](int const & i, int const & j) {
        return results[i] > results[j];
    });

    // move the 20 best performing models to the start front of the array
    for (int i = 0; i < k; ++i) {
        std::swap(models[i], models[idxs[i]]);
    }

    int topKSum = 0;
    // std::cout << "Top " << k << " results: ";
    for (int i = 0; i < k; ++i) {
        // std::cout << results[idxs[i]] << ", ";
        topKSum += results[idxs[i]];
    }
    // std::cout << std::endl;
    std::cout << "Mean of top " << k << ": " << static_cast<float>(topKSum) / k << std::endl;

    std::uniform_int_distribution<size_t> randomSampler(0, k);
    for (int i = k; i < population; ++i) {
        torch::Tensor const & sourceParams = models[randomSampler(random)]->params;
        // models[i]->setParams(torch::normal(sourceParams, torch::full(TetrisModelV1::NUM_PARAMETERS, GENETIC_STDDEV),
        //                                    TetrisModelV1::NUM_PARAMETERS));
        models[i]->setParams(at::normal(sourceParams, TetrisModelV1::NUM_PARAMETERS));
    }
}
