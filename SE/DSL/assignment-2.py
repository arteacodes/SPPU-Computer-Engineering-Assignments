"""
Write a Python program to compute following operations on String:
a) To display word with the longest length
b) To determines the frequency of occurrence of particular character in the string
c) To check whether given string is palindrome or not
d) To display index of first appearance of the substring
e) To count the occurrences of each word in a given string
"""


class StringOp:

    def __init__(self):
        self.st = input("Enter a string: ")

        # separating string into list of words
        self.words = []
        word = ""   # local variable
        for i in self.st:
            if i not in [" ", "\t", "\n"]:
                word += i
            else:
                self.words.append(word)
                word = ""
        if word:
            self.words.append(word)  # appending the last word


    # prints the longest word in string
    def longest(self):
        longestWord = ""
        for i in self.words:
            if len(i) >= len(longestWord):
                longestWord = i

        print("Longest word: ", longestWord)


    # prints frequency of input character in string
    def frequency(self):
        ch = input("Enter a character: ")
        count = 0
        for i in self.st:
            if i == ch:
                count += 1

        print("Frequency of character: ", count)


    # prints whether string is palindrome or not
    def palindrome(self):
        if self.st == self.st[::-1]:
            print("String is palindrome.")
        else:
            print("String is not palindrome.")


    # prints the index of first appearance of substring
        def showIndex(self):
            substr = input("Enter a substring: ")
            flag = False
            if substr in self.st:
                for i in range(len(self.st)):
                    for j in range(len(self.st)):
                        if self.st[i:j]==substr:
                            index = i
                            flag = True
                            print("Index at which substring first appears: ", index)
                            break
                    if flag==True:
                        break
            else:
                print("Substring not found")


    # prints list of words with no. of occurrences
    def wordCount(self):
        countDict = {}
        for i in self.words:
            if i not in countDict.keys():
                countDict[i] = self.words.count(i)

        print("No. of occurrences of each word:")
        for j in countDict.keys():
            print(j, "=", countDict[j])


s1 = StringOp()

print()
s1.longest()
print()
s1.frequency()
print()
s1.palindrome()
print()
s1.showIndex()
print()
s1.wordCount()