"""
a) Write a Python program to store roll numbers of student in array who attended training program in random order. Write function for searching whether particular student attended training program  or not, using Linear search and Sentinel search.
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

    def linearSearch(self, k):
        found = False
        for i in range(self.num):
            if self.roll[i]==k:
                found = True
                break
        if found:
            print(k, " found at index = ", i)
        else:
            print("Not found")
        print()

    def sentinelSearch(self, k):
        last = self.roll[self.num-1]  # assign as last element of array
        self.roll[self.num-1] = k  # place key at last index
        i = 0
        while self.roll[i]!=k:
            i+=1

        self.roll[self.num-1] = last  # put last element back
        if i<self.num-1:
            print(k, " found at index = ", i)
        else:
            print("Not found")
        print()


s1 = Student()
s1.getData()
proceed = True
while proceed:
    key = int(input("Enter roll no. to be searched: "))
    print("1. Linear Search\n2. Sentinel Search")
    ch = int(input("Enter choice: "))

    if ch==1:
        s1.linearSearch(key)
    elif ch==2:
        s1.sentinelSearch(key)
    else:
        print("Invalid input")
        print()

    ans = input("Continue? (y/n):")
    if ans == "y":
        continue
    else:
        proceed = False