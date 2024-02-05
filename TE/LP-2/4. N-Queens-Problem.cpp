#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

class NQueens
{
    int n;
    vector<vector<int>> board;
    vector<bool> rowLook;
    vector<bool> slashDiagonalLook;
    vector<bool> backSlashDiagonalLook;
     
    public:
    NQueens ()
    {}

    NQueens(int n)
    {
        this->n = n;
        board.resize(n, vector<int>(n, 0));
        rowLook.resize(n, false);
        slashDiagonalLook.resize(2*n - 1, false);
        backSlashDiagonalLook.resize(2*n - 1, false);      
    }

    void print();

    // methods for backtracking
    bool isSafe(int, int);
    bool solveBT(int);
    bool backtracking();

    // methods for branch and bound
    bool isPossible(int, int);  
    bool solveBB(int);    
    bool branchAndBound();
};


// print a Q if queen is placed and . if it is empty
void NQueens::print()
{
    cout<<endl;
    for (int i=0; i<n; i++)
    {
        for (int j=0; j<n; j++)
        {
            cout<< (board[i][j] == 1 ? 'Q' : '.') << " ";
        }
        cout<<endl;
    }
    cout<<endl;
}


// to check if queen can be placed at (row, col) - backtracking
bool NQueens::isSafe(int row, int col)
{
    // check for queen in same row
    for (int i=0; i<col; i++)
    {
        if (board[row][i] == 1)
            return false;
    }

    // check for queen in upper diagonal
    for (int i=row, j=col; i>=0 && j>=0; i--, j--)
    {
        if (board[i][j] == 1)
            return false;
    }

    // check for queen in lower diagonal
    for (int i=row, j=col; i<n && j>=0; i++, j--)
    {
        if (board[i][j] == 1)
            return false;
    }

    return true;
}


// to check if queen can be placed at (row, col) - branch & bound
bool NQueens::isPossible(int row, int col)
{
    return !rowLook[row] && !slashDiagonalLook[row + col] && !backSlashDiagonalLook[row - col + n - 1];
}


// recursive backtracking
bool NQueens::solveBT(int col)
{
    if (col >= n)
    {
        return true;
    }

    for (int i=0; i<n; i++)
    {
        if (isSafe(i, col))
        {
            board[i][col] = 1;

            if (solveBT(col+1))
            {
                return true;
            }

            board[i][col] = 0;  // backtrack
        }
    }
    return false;
}


// recursive branch & bound
bool NQueens::solveBB(int col)
{
    if (col >= n)
    {
        return true;
    }

    for (int i=0; i<n; i++)
    {
        if (isPossible(i, col))
        {
            board[i][col] = 1;
            rowLook[i] = true;
            slashDiagonalLook[i+col] = true;
            backSlashDiagonalLook[i-col+n-1] = true;

            if (solveBB(col+1))
                return true;

            board[i][col] = 0;
            rowLook[i] = false;
            slashDiagonalLook[i+col] = false;
            backSlashDiagonalLook[i-col+n-1] = false;
        }
    }
    return false;
}


bool NQueens::backtracking()
{
    if (solveBT(0) == false)
    {
        cout<<"\nNo solution!";  // for cases like 2x2 & 3x3 board
        return false;
    }

    print();
    return true;
}


bool NQueens::branchAndBound()
{
    if (solveBB(0) == false) 
    {
        cout<<"\nNo solution!";
        cout<<endl;
        return false;
    }

    print();
    return true;
}

int main()
{
    int N, choice;

    cout<<"Enter the size of the board (N): ";
    cin>>N;

    if (N<0 || N>8)
    {
        cout<<"\nInvalid board size. N should be between 0 & 8.";
        return 1;
    }

    NQueens q(N);

    cout<<"\n1. Backtracking\n2. Branch & Bound\nEnter choice: ";
    cin>>choice;

    switch (choice)
    {
        case 1:
        q.backtracking();
        break;

        case 2:
        q.branchAndBound();
        break;

        default:
        cout<<"\nInvalid choice!";
        break;
    }

    return 0;
}