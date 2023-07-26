"""
b) Write a Python program to store roll numbers of student array who attended training program in sorted order. Write function for searching whether particular student attended training program or not, using Binary search and Fibonacci search.
"""

class Student:

    def __init__(self):
        self.roll = []
        self.num = 0

    def getData(self):
        print("Enter roll numbers of students who attended:", end=" ")
        self.roll = list(map(int, input().split()))
        self.num = len(self.roll)
        print("List of roll no.s: ", self.roll)

    def binarySearch(self, k):  # iterative
        low = 0
        high = len(self.roll)

        while low<=high:
            mid = (low + high) // 2     # floor div for integer value
            if self.roll[mid] == k:
                print(k, " found at index = ", mid)
                break
            elif k < self.roll[mid]:
                high = mid-1    # to sort in lower half
            else:
                low = mid+1    # to sort in upper half

        if low>high:
            print("Not found")


    def fibonacciSearch(self, k):
        found = False
        fib2 = 0
        fib1 = 1
        fib = fib1 + fib2
        n = len(self.roll)
        offset = -1

        while fib<n:  # find fibonacci no. >= length of array
            fib2 = fib1
            fib1 = fib
            fib = fib2 + fib1

        while fib>1:
            index = min(offset+fib2, n-1)  # check if fib2 is a valid location
            if self.roll[index]<k:
                # go down 1 no. in fibonacci series
                # remove subarray from offset to index
                fib = fib1
                fib1 = fib2
                fib2 = fib - fib1
                offset = index
            elif self.roll[index]>k:
                # go down 2 no.s in fibonacci series
                # remove subarray after index+1
                fib = fib2
                fib1 = fib1 - fib2
                fib2 = fib - fib1
            else:
                found = True
                break

        if found:  # compare last element with key
            print(k, " found at index = ", index)
        else:
            print("Not found")



s1 = Student()
s1.getData()
proceed = True
while proceed:
    key = int(input("Enter roll no. to be searched: "))
    print("1. Binary Search\n2. Fibonacci Search")
    ch = int(input("Enter choice: "))

    if ch==1:
        s1.binarySearch(key)
    elif ch==2:
        s1.fibonacciSearch(key)
    else:
        print("Invalid input")
        print()

    ans = input("Continue? (y/n):")
    if ans == "y":
        continue
    else:
        proceed = False

