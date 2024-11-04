#include <iostream>
#include <vector>
using namespace std;

bool isSafe(int N, int row, int col, const vector<vector<int>>& board) {

    // check current column
    for (int i=0; i<row; i++) {
        if (board[i][col] == 1)
            return false;
    }

    // check upper-left diagonal
    for (int i=row, j=col; i>=0 && j>=0; i--, j--) {
        if (board[i][j] == 1)
            return false;
    }

    // check upper-right diagonal
    for (int i=row, j=col; i>=0 && j<N; i--, j++) {
        if (board[i][j] == 1)
            return false;
    }
    
    return true;
}


bool solve(int N, int row, vector<vector<int>>& board) {
    
    if (row >= N) {
        return true;  // all queens placed
    }

    for (int col=0; col<N; col++) {
        
        if (isSafe(N, row, col, board)) {
            board[row][col] = 1;  // place queen

            if (solve(N, row+1, board)) {
                return true;
            }

            board[row][col] = 0;  // backtrack
        }
    }
    return false;  // no solution found
}


void printBoard(const vector<vector<int>>& board, int N) {
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            cout << (board[i][j] ? "Q " : ". ");
        }
        cout << endl;
    }
}


int main() {
    int N = 8;
    vector<vector<int>> board(N, vector<int>(N, 0));

    bool solutionFound = false;

    for (int col=0; col<N; col++) {
        
        board[0][col] = 1;  // place 1st queen

        if (solve(N, 1, board)) {
            solutionFound = true;
            break;
        }
        board[0][col] = 0;  // backtrack
    }

    if (solutionFound) {
        cout << "Solution:\n";
        printBoard(board, N);
    } 
    else {
        cout << "No solution exists.\n";
    }
    
    return 0;
}
