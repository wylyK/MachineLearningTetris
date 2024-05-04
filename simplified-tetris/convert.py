pieces = [
      [], # "null"
      [ # O
          # N
          [["null", "O",    "O"],
           ["null", "O",    "O"],
           ["null", "null", "null"]],
          # E
          [["null", "O",    "O"],
           ["null", "O",    "O"],
           ["null", "null", "null"]],
          # S
          [["null", "O",    "O"],
           ["null", "O",    "O"],
           ["null", "null", "null"]],
          # W
          [["null", "O",    "O"],
           ["null", "O",    "O"],
           ["null", "null", "null"]]
      ],
      [ # I
          # N
          [["null", "null", "null", "null"],
           ["I",    "I",    "I",    "I"],
           ["null", "null", "null", "null"],
           ["null", "null", "null", "null"]],
          # E
          [["null", "null", "I",    "null"],
           ["null", "null", "I",    "null"],
           ["null", "null", "I",    "null"],
           ["null", "null", "I",    "null"]],
          # S
          [["null", "null", "null", "null"],
           ["null", "null", "null", "null"],
           ["I",    "I",    "I",    "I"],
           ["null", "null", "null", "null"]],
          # W
          [["null", "I",    "null", "null"],
           ["null", "I",    "null", "null"],
           ["null", "I",    "null", "null"],
           ["null", "I",    "null", "null"]],
      ],
      [ # T
          # N
          [["null", "T",    "null"],
           ["T",    "T",    "T"],
           ["null", "null", "null"]],
          # E
          [["null", "T",    "null"],
           ["null", "T",    "T"],
           ["null", "T",    "null"]],
          # S
          [["null", "null", "null"],
           ["T",    "T",    "T"],
           ["null", "T",    "null"]],
          # W
          [["null", "T",    "null"],
           ["T",    "T",    "null"],
           ["null", "T",    "null"]],
      ],
      [ # L
          # N
          [["null", "null", "L"],
           ["L",    "L",    "L"],
           ["null", "null", "null"]],
          # E
          [["null", "L",    "null"],
           ["null", "L",    "null"],
           ["null", "L",    "L"]],
          # S
          [["null", "null", "null"],
           ["L",    "L",    "L"],
           ["L",    "null", "null"]],
          # W
          [["L",    "L",    "null"],
           ["null", "L",    "null"],
           ["null", "L",    "null"]],
      ],
      [ # J
          # N
          [["J",    "null", "null"],
           ["J",    "J",    "J"],
           ["null", "null", "null"]],
          # E
          [["null", "J",    "J"],
           ["null", "J",    "null"],
           ["null", "J",    "null"]],
          # S
          [["null", "null", "null"],
           ["J",    "J",    "J"],
           ["null", "null", "J"]],
          # W
          [["null", "J",    "null"],
           ["null", "J",    "null"],
           ["J",    "J",    "null"]],
      ],
      [ # S
          # N
          [["null", "S",    "S"],
           ["S",    "S",    "null"],
           ["null", "null", "null"]],
          # E
          [["null", "S",    "null"],
           ["null", "S",    "S"],
           ["null", "null", "S"]],
          # S
          [["null", "null", "null"],
           ["null", "S",    "S"],
           ["S",    "S",    "null"]],
          # W
          [["S",    "null", "null"],
           ["S",    "S",    "null"],
           ["null", "S",    "null"]],
      ],
      [ # Z
          # N
          [["Z",    "Z",    "null"],
           ["null", "Z",    "Z"],
           ["null", "null", "null"]],
          # E
          [["null", "null", "Z"],
           ["null", "Z",    "Z"],
           ["null", "Z",    "null"]],
          # S
          [["null", "null", "null"],
           ["Z",    "Z",    "null"],
           ["null", "Z",    "Z"]],
          # W
          [["null", "Z",    "null"],
           ["Z",    "Z",    "null"],
           ["Z",    "null", "null"]],
      ]
  ]

reverse_sets = []
for piece_type in pieces:
    reverse_sets.append([])
    for rotation in piece_type:
        reverse = []
        for i, row in enumerate(rotation):
            for j, cell in enumerate(row):
                if cell != "null":
                    reverse.append([i, j])
        reverse_sets[-1].append(reverse)
print(str(reverse_sets).replace('[', '{').replace(']', '}'))
