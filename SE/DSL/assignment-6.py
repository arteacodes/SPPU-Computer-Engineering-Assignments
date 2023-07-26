"""
Write a python program to store first year percentage of students in array. Write function for sorting array of floating point numbers in ascending order using quick sort and display top five scores.
"""

class FE_Student:

    def __init__(self):
        self.arr = []


    def getData(self, n):
        print("Enter", n, "percentage values:", end=" ")
        for i in range(n):
            val = float(input())
            self.arr.append(val)


    def partition(self, low, high):
        pivot = self.arr[high]
        i = low-1
        for j in range(low, high):
            if self.arr[j]<=pivot:  #compare each element with pivot
                i+=1  # increase i if jth element is smaller than pivot
                self.arr[i], self.arr[j] = self.arr[j], self.arr[i]  # swap ith and jth element

        # place pivot element at correct position
        self.arr[i+1], self.arr[high] = self.arr[high], self.arr[i+1]
        return i+1  # return index of pivot


    def quickSort(self, low, high):
        if low<high:
            pi = self.partition(low, high)  # pivot index

            self.quickSort(low, pi-1)  # sort lower sub array
            self.quickSort(pi+1, high)  # sort upper sub array



    def display(self):
        print("\nSorted array:", end=" ")
        print(self.arr)
        print("\nTop 5 scores:", end=" ")
        rev = self.arr[::-1]
        for i in range(5):
            print(rev[i], end=" ")


f = FE_Student()
num = int(input("Enter number of FE students: "))
f.getData(num)
f.quickSort(0, num-1)
f.display()