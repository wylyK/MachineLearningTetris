#ifndef SIMPLIFIED_TETRIS_PIECES_H
#define SIMPLIFIED_TETRIS_PIECES_H
#include <type_traits>

namespace SimplifiedTetris {
  enum Tetromino : std::underlying_type_t<std::byte> {
      null = 0,
      O = 1,
      I = 2,
      T = 3,
      L = 4,
      J = 5,
      S = 6,
      Z = 7
  };
  static constexpr int PIECE_SIZE[] = {
      0, // Tetromino::null
      3, // O
      4, // I
      3, // T
      3, // L
      3, // J
      3, // S
      3  // Z
  };
  static constexpr Tetromino FACINGS[8][4][4][4] = {
      {}, // Tetromino::null
      { // O
          // N
          {{Tetromino::null, Tetromino::O,    Tetromino::O},
           {Tetromino::null, Tetromino::O,    Tetromino::O},
           {Tetromino::null, Tetromino::null, Tetromino::null}},
          // E
          {{Tetromino::null, Tetromino::O,    Tetromino::O},
           {Tetromino::null, Tetromino::O,    Tetromino::O},
           {Tetromino::null, Tetromino::null, Tetromino::null}},
          // S
          {{Tetromino::null, Tetromino::O,    Tetromino::O},
           {Tetromino::null, Tetromino::O,    Tetromino::O},
           {Tetromino::null, Tetromino::null, Tetromino::null}},
          // W
          {{Tetromino::null, Tetromino::O,    Tetromino::O},
           {Tetromino::null, Tetromino::O,    Tetromino::O},
           {Tetromino::null, Tetromino::null, Tetromino::null}}
      },
      { // I
          // N
          {{Tetromino::null, Tetromino::null, Tetromino::null, Tetromino::null},
           {Tetromino::I,    Tetromino::I,    Tetromino::I,    Tetromino::I},
           {Tetromino::null, Tetromino::null, Tetromino::null, Tetromino::null},
           {Tetromino::null, Tetromino::null, Tetromino::null, Tetromino::null}},
          // E
          {{Tetromino::null, Tetromino::null, Tetromino::I,    Tetromino::null},
           {Tetromino::null, Tetromino::null, Tetromino::I,    Tetromino::null},
           {Tetromino::null, Tetromino::null, Tetromino::I,    Tetromino::null},
           {Tetromino::null, Tetromino::null, Tetromino::I,    Tetromino::null}},
          // S
          {{Tetromino::null, Tetromino::null, Tetromino::null, Tetromino::null},
           {Tetromino::null, Tetromino::null, Tetromino::null, Tetromino::null},
           {Tetromino::I,    Tetromino::I,    Tetromino::I,    Tetromino::I},
           {Tetromino::null, Tetromino::null, Tetromino::null, Tetromino::null}},
          // W
          {{Tetromino::null, Tetromino::I,    Tetromino::null, Tetromino::null},
           {Tetromino::null, Tetromino::I,    Tetromino::null, Tetromino::null},
           {Tetromino::null, Tetromino::I,    Tetromino::null, Tetromino::null},
           {Tetromino::null, Tetromino::I,    Tetromino::null, Tetromino::null}},
      },
      { // T
          // N
          {{Tetromino::null, Tetromino::T,    Tetromino::null},
           {Tetromino::T,    Tetromino::T,    Tetromino::T},
           {Tetromino::null, Tetromino::null, Tetromino::null}},
          // E
          {{Tetromino::null, Tetromino::T,    Tetromino::null},
           {Tetromino::null, Tetromino::T,    Tetromino::T},
           {Tetromino::null, Tetromino::T,    Tetromino::null}},
          // S
          {{Tetromino::null, Tetromino::null, Tetromino::null},
           {Tetromino::T,    Tetromino::T,    Tetromino::T},
           {Tetromino::null, Tetromino::T,    Tetromino::null}},
          // W
          {{Tetromino::null, Tetromino::T,    Tetromino::null},
           {Tetromino::T,    Tetromino::T,    Tetromino::null},
           {Tetromino::null, Tetromino::T,    Tetromino::null}},
      },
      { // L
          // N
          {{Tetromino::null, Tetromino::null, Tetromino::L},
           {Tetromino::L,    Tetromino::L,    Tetromino::L},
           {Tetromino::null, Tetromino::null, Tetromino::null}},
          // E
          {{Tetromino::null, Tetromino::L,    Tetromino::null},
           {Tetromino::null, Tetromino::L,    Tetromino::null},
           {Tetromino::null, Tetromino::L,    Tetromino::L}},
          // S
          {{Tetromino::null, Tetromino::null, Tetromino::null},
           {Tetromino::L,    Tetromino::L,    Tetromino::L},
           {Tetromino::L,    Tetromino::null, Tetromino::null}},
          // W
          {{Tetromino::L,    Tetromino::L,    Tetromino::null},
           {Tetromino::null, Tetromino::L,    Tetromino::null},
           {Tetromino::null, Tetromino::L,    Tetromino::null}},
      },
      { // J
          // N
          {{Tetromino::J,    Tetromino::null, Tetromino::null},
           {Tetromino::J,    Tetromino::J,    Tetromino::J},
           {Tetromino::null, Tetromino::null, Tetromino::null}},
          // E
          {{Tetromino::null, Tetromino::J,    Tetromino::J},
           {Tetromino::null, Tetromino::J,    Tetromino::null},
           {Tetromino::null, Tetromino::J,    Tetromino::null}},
          // S
          {{Tetromino::null, Tetromino::null, Tetromino::null},
           {Tetromino::J,    Tetromino::J,    Tetromino::J},
           {Tetromino::null, Tetromino::null, Tetromino::J}},
          // W
          {{Tetromino::null, Tetromino::J,    Tetromino::null},
           {Tetromino::null, Tetromino::J,    Tetromino::null},
           {Tetromino::J,    Tetromino::J,    Tetromino::null}},
      },
      { // S
          // N
          {{Tetromino::null, Tetromino::S,    Tetromino::S},
           {Tetromino::S,    Tetromino::S,    Tetromino::null},
           {Tetromino::null, Tetromino::null, Tetromino::null}},
          // E
          {{Tetromino::null, Tetromino::S,    Tetromino::null},
           {Tetromino::null, Tetromino::S,    Tetromino::S},
           {Tetromino::null, Tetromino::null, Tetromino::S}},
          // S
          {{Tetromino::null, Tetromino::null, Tetromino::null},
           {Tetromino::null, Tetromino::S,    Tetromino::S},
           {Tetromino::S,    Tetromino::S,    Tetromino::null}},
          // W
          {{Tetromino::S,    Tetromino::null, Tetromino::null},
           {Tetromino::S,    Tetromino::S,    Tetromino::null},
           {Tetromino::null, Tetromino::S,    Tetromino::null}},
      },
      { // Z
          // N
          {{Tetromino::Z,    Tetromino::Z,    Tetromino::null},
           {Tetromino::null, Tetromino::Z,    Tetromino::Z},
           {Tetromino::null, Tetromino::null, Tetromino::null}},
          // E
          {{Tetromino::null, Tetromino::null, Tetromino::Z},
           {Tetromino::null, Tetromino::Z,    Tetromino::Z},
           {Tetromino::null, Tetromino::Z,    Tetromino::null}},
          // S
          {{Tetromino::null, Tetromino::null, Tetromino::null},
           {Tetromino::Z,    Tetromino::Z,    Tetromino::null},
           {Tetromino::null, Tetromino::Z,    Tetromino::Z}},
          // W
          {{Tetromino::null, Tetromino::Z,    Tetromino::null},
           {Tetromino::Z,    Tetromino::Z,    Tetromino::null},
           {Tetromino::Z,    Tetromino::null, Tetromino::null}},
      }
  };

  static constexpr int PIECE_IDXS[8][4][4][2] = {
      {}, // Tetromino::null
      { // O
          {{0, 1}, {0, 2}, {1, 1}, {1, 2}}, // N
          {{0, 1}, {0, 2}, {1, 1}, {1, 2}}, // E
          {{0, 1}, {0, 2}, {1, 1}, {1, 2}}, // S
          {{0, 1}, {0, 2}, {1, 1}, {1, 2}}  // W
      },
      { // I
          {{1, 0}, {1, 1}, {1, 2}, {1, 3}}, // N
          {{0, 2}, {1, 2}, {2, 2}, {3, 2}}, // E
          {{2, 0}, {2, 1}, {2, 2}, {2, 3}}, // S
          {{0, 1}, {1, 1}, {2, 1}, {3, 1}}  // W
      },
      { // T
          {{0, 1}, {1, 0}, {1, 1}, {1, 2}}, // N
          {{0, 1}, {1, 1}, {1, 2}, {2, 1}}, // E
          {{1, 0}, {1, 1}, {1, 2}, {2, 1}}, // S
          {{0, 1}, {1, 0}, {1, 1}, {2, 1}}  // W
      },
      { // L
          {{0, 2}, {1, 0}, {1, 1}, {1, 2}}, // N
          {{0, 1}, {1, 1}, {2, 1}, {2, 2}}, // E
          {{1, 0}, {1, 1}, {1, 2}, {2, 0}}, // S
          {{0, 0}, {0, 1}, {1, 1}, {2, 1}}  // W
      },
      { // J
          {{0, 0}, {1, 0}, {1, 1}, {1, 2}}, // N
          {{0, 1}, {0, 2}, {1, 1}, {2, 1}}, // E
          {{1, 0}, {1, 1}, {1, 2}, {2, 2}}, // S
          {{0, 1}, {1, 1}, {2, 0}, {2, 1}}  // W
      },
      { // S
          {{0, 1}, {0, 2}, {1, 0}, {1, 1}}, // N
          {{0, 1}, {1, 1}, {1, 2}, {2, 2}}, // E
          {{1, 1}, {1, 2}, {2, 0}, {2, 1}}, // S
          {{0, 0}, {1, 0}, {1, 1}, {2, 1}}  // W
      },
      { // Z
          {{0, 0}, {0, 1}, {1, 1}, {1, 2}}, // N
          {{0, 2}, {1, 1}, {1, 2}, {2, 1}}, // E
          {{1, 0}, {1, 1}, {2, 1}, {2, 2}}, // S
          {{0, 1}, {1, 0}, {1, 1}, {2, 0}}  // W
      }
  };

  const std::unordered_map<Tetromino, std::string_view> COLOR_STRINGS = {
      {Tetromino::null, "·"},
      {Tetromino::O, "⬛"},
      {Tetromino::I, "\u001b[36m⬛\u001b[0m"},
      {Tetromino::T, "\u001b[35m⬛\u001b[0m"},
      {Tetromino::L, "\u001b[33m⬛\u001b[0m"},
      {Tetromino::J, "\u001b[34m⬛\u001b[0m"},
      {Tetromino::S, "\u001b[32m⬛\u001b[0m"},
      {Tetromino::Z, "\u001b[31m⬛\u001b[0m"}
  };

}

#endif //SIMPLIFIED_TETRIS_PIECES_H
