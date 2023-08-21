from re import compile

tab = "\t"
newline = "\n"

pattern = compile(r'\(\'([A-Z]{,2})\',\s(\d+)\)')
# captures upto 2 consecutive uppercase alphabets and one or more digits sep by a comma within () eg: (AD,01)
# pattern is now compiled into an object that can be used to search for the above regex

class Pass2:
    def __init__(self):
        self.symTab = {}
        self.litTab = {}

        # files
        self.ICFile = open("intermediateCode.txt","r")
        self.symTabFile = open("symbolTable.txt","r")
        self.litTabFile = open("literalTable.txt","r")
        self.outputFile = open("machineCode.txt", "w")


    def convert(self, string):
        string = str(string)
        if len(string)==1:
            return "00" + string
        elif len(string)==2:
            return "0" + string
        elif len(string)==3:
            return string
        

    def readST(self):
        print("\n--------------------")
        print("SYMBOL TABLE")
        print("--------------------")
        for line in self.symTabFile.readlines():
            line = line.split("\t")
            index = int(line[0])
            location = int(line[2])
            self.symTab[index] = location
            print(index, location, sep=tab)
        print()

    
    def readLT(self):
        print("\n--------------------")
        print("LITERAL TABLE")
        print("--------------------")
        for line in self.litTabFile.readlines():
            line = line.split("\t")
            index = int(line[0])
            location = int(line[2])
            self.litTab[index] = location
            print(index, location, sep="\t")
        print()

    
    def generate(self):
        self.readST()
        self.readLT()
        print("\n-----------------------------")
        print("MACHINE CODE")
        print("-----------------------------")
        print("| LC | OPCODE | OP-1 | OP-2 |")
        print("-----------------------------")
        
        for line in self.ICFile.readlines():
            line = line.strip("\n")
            line = line.split("\t")

            find = pattern.search(line[0])  # if found, 'find' will hold the matched object, else None

            # group(1) will access captured group ([A-Z]{,2}) and group(2) will access (d+)
            if find.group(1)=="IS" or find.group(1)=="DL":
                machineCode = ""
                location = line[-2]
                machineCode += location + tab

                if find.group(1)=="IS":
                    machineCode += self.convert(find.group(2)) + tab

                    if find.group(2)=="10" or find.group(2)=="9":
                        find = pattern.search(line[1])
                        key = int(find.group(2))
                        machineCode += "000" + tab + self.convert(self.symTab[key]) + newline
                    elif find.group(2)=="0":
                        machineCode += "000" + tab + "000" + newline
                    else:
                        find = pattern.search(line[1])
                        machineCode += self.convert(find.group(2)) + tab
                        find = pattern.search(line[2])
                        if find.group(1)=="S":  
                            key = int(find.group(2))
                            machineCode += self.convert(self.symTab[key]) + newline
                        elif find.group(1)=="L":
                            key = int(find.group(2))
                            machineCode += self.convert(self.litTab[key]) + newline
                else:
                    if find.group(2)=="1":
                        machineCode += "000" + tab + "000" + tab
                        find = pattern.search(line[1])
                        machineCode += self.convert(find.group(2)) + newline
                    else:
                        machineCode += "000" + tab + "000" + tab + "000" + newline
            
            else:
                continue
            print(machineCode, end="")
            self.outputFile.write(machineCode)

        self.outputFile.close()
        self.symTabFile.close()
        self.litTabFile.close()


obj = Pass2()
obj.generate()
