# Game AI Engine (C++)

A modular C++ framework for building and experimenting with AI-driven, turn-based games using classic game theory algorithms such as Minimax and Alpha-Beta Pruning.

Currently, it includes a working Tic-Tac-Toe implementation as a demo, but the engine is designed to support multiple games through a simple and reusable interface.

## Quick Start
```bash
# 1) Configure
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release

# 2) Build
cmake --build build -j

# 3) Run (human vs AI)
./build/t3_cli
```

## How it works (simple idea)
1) Read current board
2) Generate legal moves
3) For each move:
   - Apply move → new board
   - Evaluate opponent response (Minimax)
   - Use Alpha-Beta pruning to skip bad branches
4) Pick the move with the best score

Where to look:
- `src/engine/GameConcept.hpp` — tiny interface the engine expects
- `src/engine/Minimax.hpp` — header-only Minimax + Alpha-Beta
- `src/games/tictactoe/TicTacToe.hpp/.cpp` — Tic-Tac-Toe rules and evaluation
- `src/main.cpp` — console app

## Requirements
- CMake ≥ 3.16
- C++17 compiler

## License
MIT
