#include "TetrisModelV2Runner.h"
#include "featureExtractor.h"

using std::vector;

std::tuple<int, int> playGame(TetrisModelV1 & model, SimplifiedTetris::Game & game) {
    int numMoves = 0;
    int totalRowsCleared = 0;
    SimplifiedTetris::Board tmpBoard;
    while (true) {
        vector<SimplifiedTetris::Move> placements;
        game.getPlacements(placements);
        if (placements.empty()) {
            // std::cout << "Out of moves. Lasted " << numMoves << " moves." << std::endl;
            return {numMoves, totalRowsCleared};
        }

        torch::Tensor modelInput = torch::empty({static_cast<int64_t>(placements.size()),
                                                 TetrisModelV1::INPUT_FEATURES});
        auto modelInputAccessor = modelInput.accessor<float, 2>();
        for (int n = 0; n < placements.size(); ++n) {
            int const rowsCleared = game.previewMove(placements[n], tmpBoard);
            int64_t modelInputIdx = 0;

            feats::HorizontalFeatures const horizontalFeatures = feats::getHorizontalFeatures(tmpBoard);
            feats::VerticalFeatures const verticalFeatures = feats::getVerticalFeatures(tmpBoard);

            for (int const & colHeight : horizontalFeatures.colHeights) {
                modelInputAccessor[n][modelInputIdx] = static_cast<float>(colHeight);
                ++modelInputIdx;
            }

            // divide by board size to normalize between 0 and 1
            modelInputAccessor[n][modelInputIdx] = static_cast<float>(horizontalFeatures.numUnused) / SimplifiedTetris::Board::NUM_CELLS;
            ++modelInputIdx;

            modelInputAccessor[n][modelInputIdx] = static_cast<float>(horizontalFeatures.numHoles);
            ++modelInputIdx;

            modelInputAccessor[n][modelInputIdx] = static_cast<float>(horizontalFeatures.numWells);
            ++modelInputIdx;

            modelInputAccessor[n][modelInputIdx] = static_cast<float>(verticalFeatures.numOverHoles);
            ++modelInputIdx;

            modelInputAccessor[n][modelInputIdx] = static_cast<float>(verticalFeatures.numColTrans);
            ++modelInputIdx;

            modelInputAccessor[n][modelInputIdx] = static_cast<float>(horizontalFeatures.numRowTrans);
            ++modelInputIdx;

            // std::cout << std::endl;
            // tmpBoard.print();
            // std::cout << "num col trans: " << verticalFeatures.numColTrans << std::endl;
            // std::cout << "num row trans: " << horizontalFeatures.numRowTrans << std::endl;

            modelInputAccessor[n][modelInputIdx] = static_cast<float>(rowsCleared);
            ++modelInputIdx;

            if (modelInputIdx != TetrisModelV1::INPUT_FEATURES) {
                std::cerr << "defined number of inputs to TetrisModelV1 does not match amount passed in TetrisModelV1Runner" << std::endl;
                abort();
            }
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
