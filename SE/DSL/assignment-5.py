"""
Write a python program to store second year percentage of students in array.
Write function for sorting array of floating point numbers in ascending order using
a) Insertion sort
b) Shell Sort and display top five scores
"""

class SE_Student:

    def __init__(self):
        self.p = []


    def getData(self):
        print("Enter % of SE students:", end=" ")
        self.p = list(map(float, input().split()))


    def insertionSort(self):
        n = len(self.p)
        for i in range(1, n):
            temp = self.p[i]
            j = i-1
            while j>=0 and temp<self.p[j]:
                self.p[j + 1] = self.p[j]
                j-=1
            self.p[j + 1] = temp

        print("Sorted array: ", self.p)


    def shellSort(self):
        n = len(self.p)

        interval = n//2
        while interval>0:
            for i in range(interval, n):
                temp = self.p[i]
                j = i
                while j>=interval and temp<=self.p[j - interval]:
                    self.p[j]=self.p[j - interval]
                    j-=interval
                self.p[j] = temp
            interval//=2  # dividing into further sub-arrays

        print("Sorted array: ", self.p)


    def display(self):
        print("Top 5 scores:", end=" ")
        rev = self.p[::-1]
        for i in range(5):
            print(rev[i], end=" ")


s1 = SE_Student()
s1.getData()

print()
ch = int(input("1. Insertion Sort\n2. Shell Sort\nEnter choice: "))
if ch==1:
    s1.insertionSort()
elif ch==2:
    s1.shellSort()

print()
s1.display()