#include "TetrisModelV1Trainer.h"

TetrisModelV1Trainer::TetrisModelV1Trainer(size_t population) {
    for (size_t i = 0; i < population; ++i) {
        models.push_back(TetrisModelV1());
    }
}
