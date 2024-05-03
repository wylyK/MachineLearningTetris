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

void TetrisModelV1Runner::play() {
    int numMoves = 0;
    while (true) {
        auto placements = game.getPlacements();
        if (placements.empty()) {
            std::cout << "Out of moves. Lasted " << numMoves << " moves." << std::endl;
            break;
        }

        torch::Tensor modelInput = torch::empty({static_cast<int64_t>(placements.size()),
                                                 TetrisModelV1::INPUT_FEATURES});
        for (int n = 0; n < placements.size(); ++n) {
            auto const newBoard = game.previewMove(placements[n]);
            int64_t modelInputIdx = 0;

            vector<int> const colHeights = feats::columnHeights(*newBoard);
            for (int const & colHeight : colHeights) {
                modelInput[n][modelInputIdx] = colHeight;
                ++modelInputIdx;
            }

            modelInput[n][modelInputIdx] = feats::getNumUnused(*newBoard);
            ++modelInputIdx;

            modelInput[n][modelInputIdx] = feats::getNumHoles(*newBoard);
            ++modelInputIdx;

            modelInput[n][modelInputIdx] = feats::getNumWells(*newBoard);
            ++modelInputIdx;

            modelInput[n][modelInputIdx] = feats::getNumOverHoles(*newBoard);
            ++modelInputIdx;

            modelInput[n][modelInputIdx] = feats::getNumRowTrans(*newBoard);
            ++modelInputIdx;

            modelInput[n][modelInputIdx] = feats::getNumColTrans(*newBoard);
            ++modelInputIdx;

            if (modelInputIdx != TetrisModelV1::INPUT_FEATURES) {
                std::cerr << "defined number of inputs to TetrisModelV1 does not match amount passed in TetrisModelV1Runner" << std::endl;
                abort();
            }
        }
        auto const scores = model.evaluate(modelInput);
        std::cout << "scores = " << scores << std::endl;
        break;

        game.doMove(placements[0]);
        game.getBoard().print();
        std::cout << std::endl;
    }
}
