#include "FeatureExtractor.h"

int getNumHoles(SimplifiedTetris::Game::Board const & board) {
    bool filled[SimplifiedTetris::Game::Board::WIDTH];
    int holes = 0;
    for (int row = SimplifiedTetris::Game::Board::HEIGHT - 1; row >= 0; --row) {
        for (int col = 0; col < SimplifiedTetris::Game::Board::WIDTH; ++col) {
            if (board.board[row][col] == SimplifiedTetris::Tetromino::null) {
                if (filled[col]) {
                    ++holes;
                }
            } else {
                filled[col] = true;
            }
        }
    }
    return holes;
}
