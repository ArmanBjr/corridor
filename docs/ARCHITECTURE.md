# Architecture

## Overview

Cooridor models the Quoridor board as a **grid graph**. Each playable cell is a node; open passages between cells are edges. Placing a wall removes one or two edges. Before a wall is accepted, **DFS** verifies that both players can still reach their respective goal rows.

## Data Structures

### `struct board`

| Field | Description |
|-------|-------------|
| `Map[n][m]` | Encoded cell state (walls + pawn occupancy) |
| `p1x, p1y` | Player 1 (O) position — starts bottom row |
| `p2x, p2y` | Player 2 (X) position — starts top row |
| `p1w, p2w` | Remaining walls per player |
| `vw[]` | Precomputed valid wall positions for AI |

Each `Map[i][j]` cell uses a 3-digit encoding:

```
[hundreds] [tens] [ones]
   left      up    pawn
```

- **Left wall** (hundreds): `1` = open, `2` = blocked
- **Up wall** (tens): `1` = open, `2` = blocked
- **Pawn** (ones): `0` = empty, `1` = player 1, `2` = player 2

### `struct Graph`

Adjacency list representation (`adjList[node][4]`) for up to 10,000 nodes. Used for DFS connectivity checks and Dijkstra distance calculations.

## AI Pipeline

```
┌─────────────┐     ┌──────────────┐     ┌─────────────────┐
│  findMoves  │────▶│   minimax    │────▶│  best move /    │
│  findWalls  │     │  + alpha-β   │     │  wall placement │
└─────────────┘     └──────┬───────┘     └─────────────────┘
                           │
                    ┌──────▼───────┐
                    │   utility()  │
                    │  (Dijkstra)  │
                    └──────────────┘
```

### Utility function

At leaf nodes (depth 0), the board is scored using:

- Shortest path distance of each player to their goal (via Dijkstra)
- Remaining wall count difference
- Row progress toward the goal

Positive scores favor the AI (player 2); negative scores favor the human (player 1).

### Difficulty levels 1–3

Random or heuristic-based moves without full tree search.

### Difficulty levels 4–5

Full **minimax** search with **alpha-beta pruning** at depth 2 (Legend) or depth 4 (Ultimate). The AI explores pawn moves and wall placements, evaluating leaf states with the utility function.

## Wall Validation Flow

```
Player requests wall at (x, y, H|V)
        │
        ▼
  Remove edges from graph
        │
        ▼
  DFS from Player 1 ──▶ can reach goal row?
        │
        ▼
  DFS from Player 2 ──▶ can reach goal row?
        │
   ┌────┴────┐
   │         │
  Yes       No ──▶ reject wall, restore edges
   │
   ▼
 Accept wall
```

## File Responsibilities

| File | Role |
|------|------|
| `cooridor.c` | Entry point, game loop, input handling, AI integration |
| `main.c` | Simpler two-player-only version (self-contained) |
| `dfs.h` | Graph construction, edge add/remove, DFS |
| `minimax.h` | Dijkstra, minimax, alpha-beta, move generation |
| `validV.h` | Wall validity checks, utility scoring |
| `screen.h` | Console rendering, colors, coordinate labels |
| `sp.h` | Random AI helpers, wall deletion utilities |
| `structures.h` | Shared type definitions |
