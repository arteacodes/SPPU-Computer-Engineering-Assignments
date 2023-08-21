# using https://github.com/Prago2001/LP-1/blob/main/SPOS/A1/pass_1.py

from os import sep, write

tab = "\t"
newline = "\n"

class Mnemonics:

    # constructor with all the opcodes
    def __init__(self):
        self.AD = {"START": 1,
                    "END": 2,
                    "ORIGIN": 3,
                    "EQU": 4,
                    "LTORG": 5}

        self.IS = {"STOP": 0,
                    "ADD": 1,
                    "SUB": 2,
                    "MULT": 3,
                    "MOVER": 4,
                    "MOVEM": 5,
                    "COMP": 6,
                    "BC": 7,
                    "DIV": 8,
                    "READ": 9,
                    "PRINT": 10}

        self.DL = {"DC": 1,
                   "DS": 2}

        self.REG = {"AREG": 1,
                    "BREG": 2,
                    "CREG": 3,
                    "DREG": 4}

        self.CC = {"LT": 1,
                    "LE": 2,
                    "EQ": 3,
                    "GT": 4,
                    "GE": 5,
                    "ANY": 6}


    def getClassType(self, string):
        if string in self.AD:
            return "AD"
        elif string in self.IS:
            return "IS"
        elif string in self.DL:
            return "DL"
        elif string in self.REG:
            return "RG"
        elif string in self.CC:
            return "CC"
        else:
            return ""


    def getCode(self, string):
        if string in self.AD:
            return self.AD[string]
        elif string in self.IS:
            return self.IS[string]
        elif string in self.DL:
            return self.DL[string]
        elif string in self.REG:
            return self.REG[string]
        elif string in self.CC:
            return self.CC[string]
        else:
            return -1



class Pass1:
    def __init__(self):
        self.opTab = Mnemonics()  # object of Mnemonics class for lookup
        self.symTab = {}
        self.litTab = {}
        self.poolTab = [0]  # default entry for 1st literal pool
        self.litIndex = 0  # literal table index (for appending)
        self.litPtr = 0  # literal table pointer
        self.LC = 0  # location counter
        self.IC = []

        # files
        self.inputFile = open("test-case-1.txt", "r")
        self.litTabFile = open("literalTable.txt","w")
        self.symTabFile = open("symbolTable.txt","w")
        self.poolTabFile = open("poolTable.txt","w")
        self.ICFile = open("intermediateCode.txt","w")


    # calculates and returns location for ORIGIN 
    def location(self, string):
        if "+" in string:
            string = string.split("+")
            return self.symTab[string[0]] + int(string[1])
        elif "-" in string:
            string = string.split("-")
            return self.symTab[string[0]] - int(string[1])
        else:
            return self.symTab[string]

    
    def compute(self):
        for line in self.inputFile.readlines():

            self.IC.append([])

            line = line.strip("\n")
            line = line.split("\t")

            label = line[0]
            opcode = line[1]
            if len(line) >= 3:
                operand1 = line[2]
            if len(line) >= 4:
                operand2 = line[3]


            # for labels
            if label != "":
                self.symTab[label] = self.LC  # set label, location


            # for opcodes that need specific handling
            if opcode == "START":
                self.LC = int(operand1)
                self.IC[-1].append(('AD', 1))
                self.IC[-1].append(('C', int(operand1)))
            
            elif opcode == "LTORG":
                for i in range(self.poolTab[-1], len(self.litTab)):
                    self.litTab[i][1] = self.LC  # set the location for literal 
                    self.IC[-1].append(('DL', 1))
                    self.IC[-1].append(('C', self.litTab[i][0]))
                    self.IC[-1].append(self.LC)
                    self.LC += 1
                    self.litPtr += 1

                    if i < (len(self.litTab) - 1):
                        self.IC.append([])
                
                self.poolTab.append(self.litPtr)

            elif opcode == "ORIGIN":
                self.LC = self.location(operand1)
                self.IC[-1].append(('AD', 3))
                self.IC[-1].append(('C', self.LC))
            
            elif opcode == "EQU":
                newLocation = self.location(operand1)
                self.symTab[label] = newLocation
                self.IC[-1].append(('AD', 4))
                self.IC[-1].append(('C', newLocation))

            elif opcode == "DC":
                self.IC[-1].append(('DL', 1))
                self.IC[-1].append(('C', int(operand1)))
                self.IC[-1].append(self.LC)
                self.LC += 1

            elif opcode == "DS":
                self.IC[-1].append(('DL', 2))
                self.IC[-1].append(('C', int(operand1)))
                self.IC[-1].append(self.LC)
                self.LC += int(operand1)

            elif opcode == "STOP":
                self.IC[-1].append(('IS', 0))
                self.IC[-1].append(self.LC)
                self.LC += 1

            elif opcode == "END":
                self.IC[-1].append(('AD', 2))
                # process remaining literals if any
                if self.litPtr != len(self.litTab):
                    for i in range(self.poolTab[-1], len(self.litTab)):
                        self.IC.append([])
                        self.litTab[i][1] = self.LC
                        self.IC[-1].append(('DL', 1))
                        self.IC[-1].append(('C', self.litTab[i][0]))
                        self.IC[-1].append(self.LC)
                        self.LC += 1
                        self.litPtr += 1
                    self.poolTab.append(self.litPtr)

            elif opcode == "BC":
                self.IC[-1].append(('IS', 7))
                # get class and code for 1st operand
                classType = self.opTab.getClassType(operand1)
                machineCode = self.opTab.getCode(operand1)
                self.IC[-1].append((classType, machineCode))
                # compute 2nd operand if exists
                if operand2 not in self.symTab:
                    self.symTab[operand2] = None
                symTabKeys = list(self.symTab.keys())
                self.IC[-1].append(("S",symTabKeys.index(operand2)))
                self.IC[-1].append(self.LC)
                self.LC += 1
                
            elif opcode == "READ":
                self.IC[-1].append(('IS', 9))
                self.symTab[operand1] = None
                symTabKeys = list(self.symTab.keys())
                self.IC[-1].append(("S",symTabKeys.index(operand1)))
                self.IC[-1].append(self.LC)
                self.LC += 1
            
            elif opcode == "PRINT":
                self.IC[-1].append(('IS', 10))
                symTabKeys = list(self.symTab.keys())
                self.IC[-1].append(('S', symTabKeys.index(operand1)))
                self.IC[-1].append(self.LC)
                self.LC += 1
            
            else:
                # for opcodes
                classType = self.opTab.getClassType(opcode)
                machineCode = self.opTab.getCode(opcode)
                self.IC[-1].append((classType, machineCode))

                # for operand1
                classType = self.opTab.getClassType(operand1)
                machineCode = self.opTab.getCode(operand1)
                self.IC[-1].append((classType, machineCode))

                # for operand2
                if "=" in operand2:  # if it is a literal
                    constant = operand2.strip("=")
                    constant = int(constant.strip("'"))
                    self.litTab[self.litIndex] = [constant, None]
                    self.IC[-1].append(('L', self.litIndex))
                    self.IC[-1].append(self.LC)
                    self.litIndex += 1
                else:
                    if operand2 in self.symTab:
                        symTabKeys = list(self.symTab.keys())
                        self.IC[-1].append(('S', symTabKeys.index(operand2)))
                        self.IC[-1].append(self.LC)
                    else:
                        self.symTab[operand2] = None
                        symTabKeys = list(self.symTab.keys())
                        self.IC[-1].append(('S', symTabKeys.index(operand2)))
                        self.IC[-1].append(self.LC)
                
                self.LC += 1
        
        # print all tables
        self.printST()
        self.printLT()
        self.printPT()
        self.printIC()

    def printST(self):
        print("\n--------------------")
        print("SYMBOL TABLE")
        print("--------------------")
        for index, item in enumerate(self.symTab):
            line = str(index) + tab + str(item) + tab + str(self.symTab[item]) + newline
            print(line, end="")
            self.symTabFile.write(line)
        self.symTabFile.close()
        print()


    def printLT(self):
        print("\n--------------------")
        print("LITERAL TABLE")
        print("--------------------")
        for item in range(len(self.litTab)):
            line = str(item) + tab + str(self.litTab[item][0]) + tab + str(self.litTab[item][1]) + newline
            print(line, end="")
            self.litTabFile.write(line)
        self.litTabFile.close()
        print()


    def printPT(self):
        print("\n--------------------")
        print("POOL TABLE")
        print("--------------------")
        for item in range(len(self.poolTab)):
            print(self.poolTab[item])
            self.poolTabFile.write(str(self.poolTab[item]) + newline)
        self.poolTabFile.close()
        print()


    def printIC(self):
        print("\n----------------------------------------------------")
        print("INTERMEDIATE CODE")
        print("----------------------------------------------------")
        for item in self.IC:
            line = ""
            for i in range(len(item)):
                line += str(item[i])
                if i!= len(item):
                    line += tab
            line += newline
            print(line, end="")
            self.ICFile.write(line)
        self.ICFile.close()       


obj = Pass1()
obj.compute()
