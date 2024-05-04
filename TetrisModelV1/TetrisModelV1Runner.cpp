#include "TetrisModelV1Runner.h"
#include "featureExtractor.h"

using std::vector;

TetrisModelV1Runner::TetrisModelV1Runner(TetrisModelV1Runner::seed_type const seed) :
    game(seed)
{
    // mean 0, stddev .5
    weights = torch::normal(0, .5, TetrisModelV1::NUM_PARAMETERS);
    model.setParams(weights);
}

int TetrisModelV1Runner::play() {
    return playGame(model, game);
}

int playGame(TetrisModelV1 & model, SimplifiedTetris::Game & game) {
    int numMoves = 0;
    while (true) {
        auto const placements = game.getPlacements();
        if (placements.empty()) {
            // std::cout << "Out of moves. Lasted " << numMoves << " moves." << std::endl;
            return numMoves;
        }

        torch::Tensor modelInput = torch::empty({static_cast<int64_t>(placements.size()),
                                                 TetrisModelV1::INPUT_FEATURES});
        auto modelInputAccessor = modelInput.accessor<float, 2>();
        for (int n = 0; n < placements.size(); ++n) {
            auto const boardState = game.previewMove(placements[n]);
            auto const newBoard = get<0>(boardState);
            (boardState)int64_t modelInputIdx = 0;

            vector<int> const colHeights = feats::columnHeights(*newBoard);
            for (int const & colHeight : colHeights) {
                modelInputAccessor[n][modelInputIdx] = static_cast<float>(colHeight);

                ++modelInputIdx;
            }

            // divide by board size to normalize between 0 and 1
            modelInputAccessor[n][modelInputIdx] = static_cast<float>(feats::getNumUnused(*newBoard)) / SimplifiedTetris::Board::NUM_CELLS;
            ++modelInputIdx;

            modelInputAccessor[n][modelInputIdx] = static_cast<float>(feats::getNumHoles(*newBoard));
            ++modelInputIdx;

            modelInputAccessor[n][modelInputIdx] = static_cast<float>(feats::getNumWells(*newBoard));
            ++modelInputIdx;

            modelInputAccessor[n][modelInputIdx] = static_cast<float>(feats::getNumOverHoles(*newBoard));
            ++modelInputIdx;

            modelInputAccessor[n][modelInputIdx] = static_cast<float>(feats::getNumRowTrans(*newBoard));
            ++modelInputIdx;

            modelInputAccessor[n][modelInputIdx] = static_cast<float>(feats::getNumColTrans(*newBoard));
            ++modelInputIdx;

            if (modelInputIdx != TetrisModelV1::INPUT_FEATURES) {
                std::cerr << "defined number of inputs to TetrisModelV1 does not match amount passed in TetrisModelV1Runner" << std::endl;
                abort();
            }
        }
        auto const scores = model.evaluate(modelInput);
        // std::cout << "scores = " << scores << std::endl;
        int const bestPlacement = torch::argmax(scores).item<int>();
        game.doMove(placements[bestPlacement]);
        // game.getBoard().print();
        ++numMoves;
        // std::cout << std::endl;
    }
}

void TetrisModelV1Runner::reset(seed_type seed) {
    game = SimplifiedTetris::Game(seed);
}
