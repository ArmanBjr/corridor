# Cooridor

A console implementation of [**Quoridor**](https://en.wikipedia.org/wiki/Quoridor) — the two-player strategy board game where you race your pawn to the opposite side while placing walls to block your opponent.

Built in **C** as the final project for **Fundamentals of Programming (FUM)**, Ferdowsi University of Mashhad (2024).

## Features

- **Human vs Human** — full rules with wall placement and jump mechanics
- **Human vs Computer** — five AI difficulty levels:
  | Level | Name | Strategy |
  |-------|------|----------|
  | 1 | Beginner | Random moves |
  | 2 | Semi-pro | Random with basic heuristics |
  | 3 | Pro | Improved heuristic wall placement |
  | 4 | Legend | Minimax (depth 2) |
  | 5 | Ultimate | Minimax with alpha-beta pruning (depth 4) |
- **Wall validation** — DFS ensures both players always have a path to their goal
- **Colored terminal UI** — ASCII board with coordinate labels (Windows console)

## Screenshots

```
player one has 8 wall(s) left and player 2(or computer) has 7 walls left
This is the Map(O stands for player 1 and X stands for player 2):
      0   1   2   3   4
 0  ....|....|....|....|.... .
    :   :   :   :   :   :
 1  ....|....|....|....|.... .
    :   : O :   :   :   :
 2  ....|....|....|....|.... .
    :   :   :   :   :   :
 3  ....|....|....|....|.... .
    :   :   :   : X :   :
 4  ....|....|....|....|.... .
```

## Requirements

- **Windows** (uses `windows.h` / `conio.h` for console colors and arrow-key input)
- **GCC** (MinGW-w64 recommended)

## Build & Run

```bash
git clone https://github.com/ArmanBjr/cooridor.git
cd cooridor
make
./cooridor
```

Or without Make:

```bash
gcc -std=c99 cooridor.c -o cooridor -lm
./cooridor
```

### Classic two-player mode

An earlier milestone without AI is also available:

```bash
make classic
./classic
```

## Controls

| Input | Action |
|-------|--------|
| Arrow keys | Move your pawn |
| `W` | Place a wall (then enter coordinates and `H`/`V`) |
| `0` | Quit the game |

When placing a wall, enter: `row col H` (horizontal) or `row col V` (vertical).

## Project Structure

```
cooridor/
├── cooridor.c      # Main game loop (PvP + AI)
├── main.c          # Classic two-player version
├── structures.h    # Board, graph, and wall data types
├── dfs.h           # Graph adjacency list + DFS path checking
├── minimax.h       # Dijkstra utility + minimax / alpha-beta AI
├── validV.h        # Wall validation + board evaluation
├── screen.h        # Terminal rendering and colors
├── sp.h            # AI helper functions (random moves, wall logic)
├── archive/        # Course milestone snapshots (phases 1–5)
├── Makefile
└── LICENSE
```

See [docs/ARCHITECTURE.md](docs/ARCHITECTURE.md) for algorithm details.

## Algorithms

| Component | Algorithm | Purpose |
|-----------|-----------|---------|
| Wall validity | **DFS** on adjacency graph | Ensure both players retain a path after placing a wall |
| AI evaluation | **Dijkstra** shortest path | Score board positions by distance to goal |
| AI decision | **Minimax + alpha-beta** | Choose optimal move at higher difficulty levels |

The board is modeled as a graph where each cell is a node and walls remove edges. This makes connectivity checks and shortest-path calculations straightforward.

## Course Context

This project was developed incrementally across five phases during the FUM Fundamentals of Programming course:

1. Board representation and rendering
2. Pawn movement with jump rules
3. Wall placement with validity checks
4. Two-player game loop
5. Computer opponent with minimax AI

Phase snapshots are preserved in [`archive/`](archive/).

## License

MIT — see [LICENSE](LICENSE).

## Authors

- **Arman Bijari** — [GitHub](https://github.com/ArmanBjr)
- **Ali Houshyar** — [GitHub](https://github.com/AliHoushyar)
