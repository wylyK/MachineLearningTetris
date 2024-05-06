#include "TetrisModelV1Trainer.h"
#include <algorithm>
#include <array>
#include <torch/torch.h>
#include "TetrisModelV1Runner.h"

TetrisModelV1Trainer::TetrisModelV1Trainer(size_t population, seed_type seed) :
    population(population),
    random(seed),
    game(random()),
    torchGen(at::detail::createCPUGenerator(random()))  // TODO: use bracket initialization?
{
    for (size_t i = 0; i < population; ++i) {
        // TODO: implement destructor
        models.push_back(new TetrisModelV1(random()));
    }
}

void TetrisModelV1Trainer::runPopulation(torch::Tensor & resultsOut) {
    auto resultsAccessor = resultsOut.accessor<int, 2>();
    // vector<std::tuple<int, int>> results;
    for (int i = 0; i < population; ++i) {

        // TODO: make this more efficient
        game = SimplifiedTetris::Game(random());

        auto const gameResults = playGame(*models[i], game);

        resultsAccessor[i][0] += static_cast<float>(std::get<0>(gameResults));
        resultsAccessor[i][1] += static_cast<float>(std::get<1>(gameResults));
    }
}

void TetrisModelV1Trainer::trainRound() {
    torch::Tensor results = torch::zeros({static_cast<int64_t>(population), 2}, torch::kInt32);
    for (int gameIdx = 0; gameIdx < GAMES_PER_ROUND; ++gameIdx) {
        runPopulation(results);
    }
    auto resultsAccessor = results.accessor<int, 2>();
    // std::cout << "Results: " << results << std::endl;

    // create array if indexes 0..population
    int idxs[population];
    std::iota(&idxs[0], &idxs[population], 0);

    // sort largest to smallest
    std::partial_sort(&idxs[0], &idxs[K_SAVED], &idxs[population], [&resultsAccessor](int const & i, int const & j) {
        return resultsAccessor[i][0]> resultsAccessor[j][0];
    });

    // move the 20 best performing models to the start front of the array
    for (int i = 0; i < K_SAVED; ++i) {
        std::swap(models[i], models[idxs[i]]);
    }

    int topKSumPieces = 0;
    int topKSumRows = 0;
    // std::cout << "Top " << k << " results: ";
    for (int i = 0; i < K_SAVED; ++i) {
        // std::cout << results[idxs[i]] << ", ";
        topKSumPieces += resultsAccessor[idxs[i]][0];
        topKSumRows += resultsAccessor[idxs[i]][1];
    }
    // std::cout << std::endl;
    std::cout << "Mean pieces of top " << K_SAVED << ": "
              << static_cast<float>(topKSumPieces) / (K_SAVED * GAMES_PER_ROUND) << std::endl;
    std::cout << "Mean rows of top " << K_SAVED << ": "
              << static_cast<float>(topKSumRows) / (K_SAVED * GAMES_PER_ROUND) << std::endl;

    std::uniform_int_distribution<size_t> randomSampler(0, K_SAVED);
    for (int i = K_SAVED; i < population; ++i) {
        torch::Tensor const & sourceParams = models[randomSampler(random)]->params;
        models[i]->setParams(at::normal(sourceParams, TetrisModelV1::NUM_PARAMETERS, torchGen));
    }
}
