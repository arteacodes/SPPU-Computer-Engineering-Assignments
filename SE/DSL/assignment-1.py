"""
In  second  year  computer engineering class, group A students play cricket, group B students play badminton and group C students play football. Write a Python program using functions to compute following:
a)List of students who play both cricket and badminton
b)List of students who play either cricket or badminton but not both
c)Number of students who play neither cricket nor badminton
d)Number of students who play cricket and football but not badminton.
(Note - While  realizing  the  group,  duplicate  entries  should  be  avoided. Do not use  SET built-in functions)
"""

  

cricket = []
badminton = []
football = []


c = int(input("Enter number of students playing cricket: "))
for i in range(c):
    player = input("Enter name of cricket player: ")
    cricket.append(player)
print("Cricket List: ", cricket)
print()


b = int(input("Enter number of students playing badminton: "))
for i in range(b):
    player = input("Enter name of badminton player: ")
    badminton.append(player)
print("Badminton List: ", badminton)
print()


f = int(input("Enter number of students playing football: "))
for i in range(f):
    player = input("Enter name of football player: ")
    football.append(player)
print("Football List: ", football)
print()



def both(l1, l2):
    '''returns list of common elements of 2 lists'''
    result = []

    for i in l1:
        if i in l2:
            result.append(i)
    
    return(result)



def notBoth(l1, l2):
    '''returns list of elements in either l1 or l2 but not in both'''
    result = []

    for i in l1:
        if i not in l2:
            result.append(i)
    for j in l2:
        if j not in l1:
            result.append(j)
    
    return(result)



def neither(l1, l2, l3):
    '''returns number of elements neither in l1 nor in l2'''
    result = []

    for i in l3:
        if i not in l2:
            if i not in l1:
                result.append(i)

    return(len(result))



def notSecond(l1, l2):
    '''returns number of elements in l1 but not in l2'''
    result= []

    for i in l1:
        if i not in l2:
            result.append(i)
    
    return(len(result))


print()
print("List of students who play both cricket and badminton:", end=" ")
print(both(cricket, badminton))  #cricket and badminton
print()
print("List of students who play either cricket or badminton but not both:", end=" ")
print(notBoth(cricket, badminton))  #either cricket or badminton but not both
print()
print("Number of students who play neither cricket nor badminton:", end=" ")
print(neither(cricket, badminton, football))  #neither cricket not badminton
print()
print("Number of students who play cricket and football but not badminton:", end=" ")
print(notSecond(both(cricket, football), badminton))  #cricket and football but not badminton