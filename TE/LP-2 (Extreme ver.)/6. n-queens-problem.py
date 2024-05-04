"""
This code implements both backtracking and branch and bound techniques for the N-Queens Problem.
"""

class NQueens:
    
    def __init__(self, n):
        self.n = n
        self.board = [[0] * n for _ in range(n)]  # initialize the chess board
        self.rowLook = [False] * n  # list to keep track of occupied rows
        self.slashDiagonalLook = [False] * (2 * n - 1)  # list to keep track of occupied slash diagonals
        self.backSlashDiagonalLook = [False] * (2 * n - 1)  # list to keep track of occupied backslash diagonals


    def print_board(self):  # print the chess board
        print()
        for row in self.board:
            print(' '.join('Q' if cell == 1 else '.' for cell in row))
        print()


    def is_safe(self, row, col):  # check if placing a queen at a specific position is safe
        for i in range(col):
            if self.board[row][i] == 1:
                return False

        for i, j in zip(range(row, -1, -1), range(col, -1, -1)):
            if self.board[i][j] == 1:
                return False

        for i, j in zip(range(row, self.n), range(col, -1, -1)):
            if self.board[i][j] == 1:
                return False

        return True


    def is_possible(self, row, col):  # check if placing a queen at a specific position is possible
        return not self.rowLook[row] and not self.slashDiagonalLook[row + col] and not self.backSlashDiagonalLook[row - col + self.n - 1]


    def solve_backtracking(self, col): 
        if col >= self.n:
            return True

        for i in range(self.n):
            if self.is_safe(i, col):
                self.board[i][col] = 1

                if self.solve_backtracking(col + 1):
                    return True

                self.board[i][col] = 0

        return False


    def solve_branch_and_bound(self, col):  
        if col >= self.n:
            return True

        for i in range(self.n):
            if self.is_possible(i, col):
                self.board[i][col] = 1
                self.rowLook[i] = True
                self.slashDiagonalLook[i + col] = True
                self.backSlashDiagonalLook[i - col + self.n - 1] = True

                if self.solve_branch_and_bound(col + 1):
                    return True

                self.board[i][col] = 0
                self.rowLook[i] = False
                self.slashDiagonalLook[i + col] = False
                self.backSlashDiagonalLook[i - col + self.n - 1] = False

        return False


    def backtracking(self): 
        if not self.solve_backtracking(0):
            print("\nno solution!")
            return False

        self.print_board()
        return True


    def branch_and_bound(self):
        if not self.solve_branch_and_bound(0):
            print("\nno solution!")
            return False

        self.print_board()
        return True


N = int(input("\nEnter the size of the chessboard (N): "))

if N < 0 or N > 8:
    print("\nInvalid board size. N should be between 0 and 8.")
else:
    q = NQueens(N)

    choice = int(input("\n1. Backtracking\n2. Branch & Bound\nEnter choice: "))

    if choice == 1:
        q.backtracking()
    elif choice == 2:
        q.branch_and_bound()
    else:
        print("\nInvalid choice!")
