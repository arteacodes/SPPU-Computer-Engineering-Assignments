"""
Write a Python program to compute following computation on matrix:
a) Addition of two matrices
b) Subtraction of two matrices
c) Multiplication of two matrices
d) Transpose of a matrix
"""


class Matrix:

    def __init__(self):
        self.m = []
        self.rows = 0
        self.cols = 0

    def getMatrix(self):
        self.rows = int(input("Enter no. of rows: "))
        self.cols = int(input("Enter no. of cols: "))

        for i in range(self.rows):
            row = []
            for j in range(self.cols):
                print("Enter element at ", i, j, ":", end=" ")
                element = int(input())
                row.append(element)  # appending element to nested list
            self.m.append(row)  # appending nested list to main list

        for x in range(self.rows):
            for y in range(self.cols):
                print(self.m[x][y], end=" ")
            print()


    def add(self, obj):
        if (self.rows != obj.rows) or (self.cols != obj.cols):
            print("Addition not possible.")
        else:
            mAdd = []   # empty matrix to store result

            for i in range(self.rows):
                row = []
                for j in range(self.cols):
                    addition = self.m[i][j] + obj.m[i][j]
                    row.append(addition)
                mAdd.append(row)

            # printing result
            print("Addition Result:")
            for x in range(self.rows):
                for y in range(self.cols):
                    print(mAdd[x][y], end=" ")
                print()


    def subtract(self, obj):
        if (self.rows != obj.rows) or (self.cols != obj.cols):
            print("Subtraction not possible.")
        else:
            mSub = []   # empty matrix to store result

            for i in range(self.rows):
                row = []
                for j in range(self.cols):
                    subtraction = self.m[i][j] - obj.m[i][j]
                    row.append(subtraction)
                mSub.append(row)

            # printing result
            print("Subtraction Result:")
            for x in range(self.rows):
                for y in range(self.cols):
                    print(mSub[x][y], end=" ")
                print()


    def multiply(self, obj):
        if self.cols != obj.rows:  # matrices should be of form axb and bxc
            print("Multiplication not possible.")
        else:
            mMpy = Matrix()
            mMpy.rows = self.rows
            mMpy.cols = obj.cols
            for i in range(self.rows):  # iterating rows of A
                row = []
                for j in range(obj.cols):  # iterating columns of B
                    mpy = 0
                    for k in range(obj.rows):
                        mpy += self.m[i][k] * obj.m[k][j]
                    row.append(mpy)
                mMpy.m.append(row)

            # printing result
            print("Multiplication Result:")
            for x in range(mMpy.rows):
                for y in range(mMpy.cols):
                    print(mMpy.m[x][y], end=" ")
                print()

    def transpose(self):
        mTp = Matrix()
        mTp.rows = self.cols
        mTp.cols = self.rows
        for i in range(self.cols):
            row = []
            for j in range(self.rows):
                row.append(self.m[j][i])
            mTp.m.append(row)

        # printing result
        print("Transpose:")
        for x in range(mTp.rows):
            for y in range(mTp.cols):
                print(mTp.m[x][y], end=" ")
            print()


# matrix object creation
print("Matrix 1:")
m1 = Matrix()
m1.getMatrix()
print()
print("Matrix 2:")
m2 = Matrix()
m2.getMatrix()
print()

m1.add(m2)
print()
m1.subtract(m2)
print()
m1.multiply(m2)
print()
print("Matrix 1\t")
m1.transpose()
print()
print("Matrix 2\t")
m2.transpose()
