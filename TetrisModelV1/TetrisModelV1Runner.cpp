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

        vector<double> scores;
        for (SimplifiedTetris::Move & placement : placements) {
            torch::Tensor modelInput = torch::empty(TetrisModelV1::NUM_PARAMETERS);
            auto const newBoard = game.previewMove(placement);
            int64_t modelInputIdx = 0;

            vector<int> const colHeights = feats::columnHeights(*newBoard);
            for (int const & colHeight : colHeights) {
                modelInput[modelInputIdx] = colHeight;
                ++modelInputIdx;
            }

            modelInput[modelInputIdx] = feats::getNumUnused(*newBoard);
            ++modelInputIdx;

            modelInput[modelInputIdx] = feats::getNumHoles(*newBoard);
            ++modelInputIdx;

            modelInput[modelInputIdx] = feats::getNumWells(*newBoard);
            ++modelInputIdx;

            modelInput[modelInputIdx] = feats::getNumOverHoles(*newBoard);
            ++modelInputIdx;

            modelInput[modelInputIdx] = feats::getNumRowTrans(*newBoard);
            ++modelInputIdx;

            modelInput[modelInputIdx] = feats::getNumColTrans(*newBoard);
            ++modelInputIdx;

            if (modelInputIdx != TetrisModelV1::INPUT_FEATURES) {
                std::cerr << "defined number of inputs to TetrisModelV1 does not match amount passed in TetrisModelV1Runner" << std::endl;
                abort();
            }

            scores.push_back(model.evaluate(modelInput).item<double>());
        }
        std::cout << "scores = " << scores << std::endl;
        break;

        game.doMove(placements[0]);
        game.getBoard().print();
        std::cout << std::endl;
    }
}
