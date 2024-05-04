#include "TetrisModelV1Runner.h"
#include "featureExtractor.h"

using std::vector;

std::tuple<int, int> playGame(TetrisModelV1 & model, SimplifiedTetris::Game & game) {
    int numMoves = 0;
    int totalRowsCleared = 0;
    while (true) {
        auto const placements = game.getPlacements();
        if (placements.empty()) {
            // std::cout << "Out of moves. Lasted " << numMoves << " moves." << std::endl;
            return {numMoves, totalRowsCleared};
        }

        torch::Tensor modelInput = torch::empty({static_cast<int64_t>(placements.size()),
                                                 TetrisModelV1::INPUT_FEATURES});
        auto modelInputAccessor = modelInput.accessor<float, 2>();
        for (int n = 0; n < placements.size(); ++n) {
            auto const preview_result = game.previewMove(placements[n]);
            auto const newBoard = std::get<0>(preview_result);
            auto const rowsCleared = std::get<1>(preview_result);
            int64_t modelInputIdx = 0;

            feats::HorizontalFeatures const horizontalFeatures = feats::getHorizontalFeatures(*newBoard);
            feats::VerticalFeatures const verticalFeatures = feats::getVerticalFeatures(*newBoard);

            for (int const & colHeight : verticalFeatures.colHeights) {
                modelInputAccessor[n][modelInputIdx] = static_cast<float>(colHeight);
                ++modelInputIdx;
            }

            // divide by board size to normalize between 0 and 1
            modelInputAccessor[n][modelInputIdx] = static_cast<float>(horizontalFeatures.numUnused) / SimplifiedTetris::Board::NUM_CELLS;
            ++modelInputIdx;

            modelInputAccessor[n][modelInputIdx] = static_cast<float>(horizontalFeatures.numHoles);
            ++modelInputIdx;

            modelInputAccessor[n][modelInputIdx] = static_cast<float>(feats::getNumWells(*newBoard));
            ++modelInputIdx;

            modelInputAccessor[n][modelInputIdx] = static_cast<float>(verticalFeatures.numOverHoles);
            ++modelInputIdx;

            modelInputAccessor[n][modelInputIdx] = static_cast<float>(verticalFeatures.numColTrans);
            ++modelInputIdx;

            modelInputAccessor[n][modelInputIdx] = static_cast<float>(horizontalFeatures.numRowTrans);
            ++modelInputIdx;

            // std::cout << std::endl;
            // newBoard->print();
            // std::cout << "num col trans: " << verticalFeatures.numColTrans << std::endl;
            // std::cout << "num row trans: " << horizontalFeatures.numRowTrans << std::endl;

            modelInputAccessor[n][modelInputIdx] = static_cast<float>(rowsCleared);
            ++modelInputIdx;

            if (modelInputIdx != TetrisModelV1::INPUT_FEATURES) {
                std::cerr << "defined number of inputs to TetrisModelV1 does not match amount passed in TetrisModelV1Runner" << std::endl;
                abort();
            }

            delete newBoard;
        }
        auto const scores = model.evaluate(modelInput);
        // std::cout << "scores = " << scores << std::endl;
        int const bestPlacement = torch::argmax(scores).item<int>();
        int const rowsCleared = game.doMove(placements[bestPlacement]);
        // game.getBoard().print();
        ++numMoves;
        totalRowsCleared += rowsCleared;
        // std::cout << std::endl;
    }
}
