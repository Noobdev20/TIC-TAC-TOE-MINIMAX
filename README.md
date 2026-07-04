**TicTacToe (C++)**

- **What:** Minimal command-line Tic-Tac-Toe implemented in a single C++ source file. Human vs AI using the Minimax algorithm.
- **Language:** C++ (C++17)
- **Source:** [tictactoe.cpp](tictactoe.cpp)

**Requirements:**
- **Compiler:** A C++ compiler that supports C++17 (example: `g++`, `clang++`).

**Files:**
- **Source:** [tictactoe.cpp](tictactoe.cpp) — contains the `TicTacToe` class and `main()`.
- **Environment:** `.env` — convenience variables for building and running.

**Build & Run (quick):**
Load environment variables then build:

```bash
source .env
eval "$BUILD_CMD"
./$EXECUTABLE $RUN_ARGS
```

Or compile directly:

```bash
g++ -std=c++17 -O2 tictactoe.cpp -o tictactoe
./tictactoe
```

**Gameplay:**
- The program runs in the terminal. You'll be prompted to enter your move as two integers: `row col` (0-indexed). Example: `1 2` places your symbol in row 1, column 2.
- By default the human plays `'X'` and the AI plays `'O'`.

**How it works (brief):**
- The game is implemented as a `TicTacToe` class with a 3x3 `board` of `char`.
- Winner detection: `checkWinner()` checks rows, columns, and diagonals and returns `'X'`, `'O'`, or `' '`.
- AI: `aiMove()` uses the `minimax()` algorithm to evaluate all possible moves. The AI maximizes a score (favors quicker wins); the human is treated as the minimizing player.
- Scoring: win = +/-10 adjusted by depth to prefer faster wins / slower losses; draw = 0.

**Key functions (in `tictactoe.cpp`):**
- `printBoard()` — prints current board state.
- `isMovesLeft()` — checks for empty cells.
- `humanMove(row, col)` — validate and apply human move.
- `aiMove()` — compute and apply AI move via `minimax()`.
- `play()` — main game loop managing turns and input.

**Notes, limitations & possible improvements:**
- Current AI uses full Minimax with no pruning; performance is fine for 3x3, but pruning (alpha-beta) would be an easy improvement for larger boards.
- No configurable AI difficulty — you can add a depth limit or randomized move choice to simulate weaker opponents.
- Input is 0-indexed; consider accepting 1-indexed input or adding a simple UI mapping for user convenience.
- To change player symbols or start with AI first, modify `main()` or expose constructor arguments for `TicTacToe(char humanSymbol, char aiSymbol)`.

**Example changes:**
- Make AI `X` and human `O` by changing `main()` to `TicTacToe game('O','X');` or reverse arguments as needed.

**License:**
- No license file included. Add one if you plan to publish.
