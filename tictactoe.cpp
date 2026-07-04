#include <iostream>
#include <vector>
#include <limits>
using namespace std;

class TicTacToe {
private:
    char board[3][3];
    char human;
    char ai;

public:
    TicTacToe(char humanSymbol = 'X', char aiSymbol = 'O') {
        human = humanSymbol;
        ai = aiSymbol;
        for (int i = 0; i < 3; i++)
            for (int j = 0; j < 3; j++)
                board[i][j] = ' ';
    }

    void printBoard() {
        cout << "\n";
        for (int i = 0; i < 3; i++) {
            cout << " " << board[i][0] << " | " << board[i][1] << " | " << board[i][2] << "\n";
            if (i < 2) cout << "---|---|---\n";
        }
        cout << "\n";
    }

    bool isMovesLeft() {
        for (int i = 0; i < 3; i++)
            for (int j = 0; j < 3; j++)
                if (board[i][j] == ' ')
                    return true;
        return false;
    }

    // Returns 'X', 'O', or ' ' (no winner yet / draw)
    char checkWinner() {
        // Rows and columns
        for (int i = 0; i < 3; i++) {
            if (board[i][0] != ' ' && board[i][0] == board[i][1] && board[i][1] == board[i][2])
                return board[i][0];
            if (board[0][i] != ' ' && board[0][i] == board[1][i] && board[1][i] == board[2][i])
                return board[0][i];
        }
        // Diagonals
        if (board[0][0] != ' ' && board[0][0] == board[1][1] && board[1][1] == board[2][2])
            return board[0][0];
        if (board[0][2] != ' ' && board[0][2] == board[1][1] && board[1][1] == board[2][0])
            return board[0][2];

        return ' ';
    }

    // Minimax: AI maximizes, human minimizes
    int minimax(int depth, bool isMaximizing) {
        char winner = checkWinner();
        if (winner == ai) return 10 - depth;
        if (winner == human) return depth - 10;
        if (!isMovesLeft()) return 0;

        if (isMaximizing) {
            int best = numeric_limits<int>::min();
            for (int i = 0; i < 3; i++) {
                for (int j = 0; j < 3; j++) {
                    if (board[i][j] == ' ') {
                        board[i][j] = ai;
                        best = max(best, minimax(depth + 1, false));
                        board[i][j] = ' ';
                    }
                }
            }
            return best;
        } else {
            int best = numeric_limits<int>::max();
            for (int i = 0; i < 3; i++) {
                for (int j = 0; j < 3; j++) {
                    if (board[i][j] == ' ') {
                        board[i][j] = human;
                        best = min(best, minimax(depth + 1, true));
                        board[i][j] = ' ';
                    }
                }
            }
            return best;
        }
    }

    void aiMove() {
        int bestVal = numeric_limits<int>::min();
        int bestRow = -1, bestCol = -1;

        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (board[i][j] == ' ') {
                    board[i][j] = ai;
                    int moveVal = minimax(0, false);
                    board[i][j] = ' ';

                    if (moveVal > bestVal) {
                        bestRow = i;
                        bestCol = j;
                        bestVal = moveVal;
                    }
                }
            }
        }

        board[bestRow][bestCol] = ai;
    }

    bool humanMove(int row, int col) {
        if (row < 0 || row > 2 || col < 0 || col > 2 || board[row][col] != ' ')
            return false;
        board[row][col] = human;
        return true;
    }

    void play() {
        cout << "=== TIC-TAC-TOE (You are '" << human << "', AI is '" << ai << "') ===\n";
        cout << "Enter row and column as: row col (0-indexed, e.g. '1 2')\n";
        printBoard();

        while (true) {
            // Human turn
            int row, col;
            bool validMove = false;
            while (!validMove) {
                cout << "Your move: ";
                if (!(cin >> row >> col)) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Invalid input. Try again.\n";
                    continue;
                }
                validMove = humanMove(row, col);
                if (!validMove) cout << "That cell is taken or invalid. Try again.\n";
            }

            printBoard();

            char winner = checkWinner();
            if (winner == human) {
                cout << "You win! (Well played, or I have a bug.)\n";
                break;
            }
            if (!isMovesLeft()) {
                cout << "It's a draw.\n";
                break;
            }

            // AI turn
            cout << "AI is thinking...\n";
            aiMove();
            printBoard();

            winner = checkWinner();
            if (winner == ai) {
                cout << "AI wins. Better luck next time.\n";
                break;
            }
            if (!isMovesLeft()) {
                cout << "It's a draw.\n";
                break;
            }
        }
    }
};

int main() {
    TicTacToe game;
    game.play();
    return 0;
}
