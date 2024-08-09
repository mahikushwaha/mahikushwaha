#include <iostream>
#include <vector>
#include <limits>

using namespace std;

const char PLAYER = 'X';
const char AI = 'O';

void printBoard(const vector<vector<char>>& board) {
    for (const auto& row : board) {
        for (const auto& cell : row) {
            cout << cell << " ";
        }
        cout << endl;
    }
    cout << endl;
}

bool isMovesLeft(const vector<vector<char>>& board) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] == '_') {
                return true;
            }
        }
    }
    return false;
}

int evaluate(const vector<vector<char>>& board) {
    // Check rows for victory
    for (int row = 0; row < 3; row++) {
        if (board[row][0] == board[row][1] && board[row][1] == board[row][2]) {
            if (board[row][0] == AI)
                return 10;
            else if (board[row][0] == PLAYER)
                return -10;
        }
    }

    // Check columns for victory
    for (int col = 0; col < 3; col++) {
        if (board[0][col] == board[1][col] && board[1][col] == board[2][col]) {
            if (board[0][col] == AI)
                return 10;
            else if (board[0][col] == PLAYER)
                return -10;
        }
    }

    // Check diagonals for victory
    if (board[0][0] == board[1][1] && board[1][1] == board[2][2]) {
        if (board[0][0] == AI)
            return 10;
        else if (board[0][0] == PLAYER)
            return -10;
    }

    if (board[0][2] == board[1][1] && board[1][1] == board[2][0]) {
        if (board[0][2] == AI)
            return 10;
        else if (board[0][2] == PLAYER)
            return -10;
    }

    return 0;
}

int minimax(vector<vector<char>>& board, int depth, bool isMax, int alpha, int beta) {
    int score = evaluate(board);

    if (score == 10)
        return score - depth;

    if (score == -10)
        return score + depth;

    if (!isMovesLeft(board))
        return 0;

    if (isMax) {
        int best = numeric_limits<int>::min();

        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (board[i][j] == '_') {
                    board[i][j] = AI;

                    best = max(best, minimax(board, depth + 1, !isMax, alpha, beta));
                    alpha = max(alpha, best);

                    board[i][j] = '_';

                    if (beta <= alpha)
                        break;
                }
            }
        }
        return best;
    } else {
        int best = numeric_limits<int>::max();

        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (board[i][j] == '_') {
                    board[i][j] = PLAYER;

                    best = min(best, minimax(board, depth + 1, !isMax, alpha, beta));
                    beta = min(beta, best);

                    board[i][j] = '_';

                    if (beta <= alpha)
                        break;
                }
            }
        }
        return best;
    }
}

pair<int, int> findBestMove(vector<vector<char>>& board) {
    int bestVal = numeric_limits<int>::min();
    pair<int, int> bestMove = {-1, -1};

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] == '_') {
                board[i][j] = AI;

                int moveVal = minimax(board, 0, false, numeric_limits<int>::min(), numeric_limits<int>::max());

                board[i][j] = '_';

                if (moveVal > bestVal) {
                    bestMove = {i, j};
                    bestVal = moveVal;
                }
            }
        }
    }

    return bestMove;
}

int main() {
    vector<vector<char>> board = {
        {'_', '_', '_'},
        {'_', '_', '_'},
        {'_', '_', '_'}
    };

    int x, y;
    while (isMovesLeft(board)) {
        cout << "Current board: " << endl;
        printBoard(board);

        cout << "Enter your move (row and column): ";
        cin >> x >> y;

        if (board[x][y] != '_') {
            cout << "Invalid move, try again!" << endl;
            continue;
        }

        board[x][y] = PLAYER;

        if (evaluate(board) == -10) {
            cout << "You won!" << endl;
            break;
        }

        if (!isMovesLeft(board)) {
            cout << "It's a draw!" << endl;
            break;
        }

        pair<int, int> bestMove = findBestMove(board);
        board[bestMove.first][bestMove.second] = AI;

        if (evaluate(board) == 10) {
            cout << "AI won!" << endl;
            break;
        }

        if (!isMovesLeft(board)) {
            cout << "It's a draw!" << endl;
            break;
        }
    }

    cout << "Final board: " << endl;
    printBoard(board);

    return 0;
}
