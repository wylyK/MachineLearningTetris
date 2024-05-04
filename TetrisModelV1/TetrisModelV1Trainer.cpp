#include "TetrisModelV1Trainer.h"
#include <algorithm>
#include <array>
#include <torch/torch.h>
#include "TetrisModelV1Runner.h"

TetrisModelV1Trainer::TetrisModelV1Trainer(size_t population, seed_type seed) :
    population(population),
    random(seed),
    game(random()),
    torchGen(at::detail::createCPUGenerator(random()))
{
    for (size_t i = 0; i < population; ++i) {
        // TODO: implement destructor
        models.push_back(new TetrisModelV1(random()));
    }
}

vector<std::tuple<int, int>> TetrisModelV1Trainer::runPopulation() {
    vector<std::tuple<int, int>> results;
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
        return std::get<0>(results[i]) > std::get<1>(results[j]);
    });

    // move the 20 best performing models to the start front of the array
    for (int i = 0; i < k; ++i) {
        std::swap(models[i], models[idxs[i]]);
    }

    int topKSumPieces = 0;
    int topKSumRows = 0;
    // std::cout << "Top " << k << " results: ";
    for (int i = 0; i < k; ++i) {
        // std::cout << results[idxs[i]] << ", ";
        topKSumPieces += std::get<0>(results[idxs[i]]);
        topKSumRows += std::get<1>(results[idxs[i]]);
    }
    // std::cout << std::endl;
    std::cout << "Mean pieces of top " << k << ": " << static_cast<float>(topKSumPieces) / k << std::endl;
    std::cout << "Mean rows of top " << k << ": " << static_cast<float>(topKSumRows) / k << std::endl;

    std::uniform_int_distribution<size_t> randomSampler(0, k);
    for (int i = k; i < population; ++i) {
        torch::Tensor const & sourceParams = models[randomSampler(random)]->params;
        models[i]->setParams(at::normal(sourceParams, TetrisModelV1::NUM_PARAMETERS, torchGen));
    }
}
