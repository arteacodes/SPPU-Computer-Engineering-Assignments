#include <iostream>
#include <cstdlib>
# include <map>
#include <algorithm>
using namespace std;

class Mnemonics
{
    map <string, int> AD;
    map <string, int> IS;
    map <string, int> DL;
    map <string, int> CC;
    map <string, int> REG;

    public:
    Mnemonics()
    {
        // assembler directives
        AD.insert(pair<string, int> ("START", 1));
        AD.insert(pair<string, int> ("END", 2));
        AD.insert(pair<string, int> ("ORIGIN", 3));
        AD.insert(pair<string, int> ("EQU", 4));
        AD.insert(pair<string, int> ("LTORG", 5));

        // imperative statements
        IS.insert(pair<string, int> ("STOP", 0));
        IS.insert(pair<string, int> ("ADD", 1));
        IS.insert(pair<string, int> ("SUB", 2));
        IS.insert(pair<string, int> ("MULT", 3));
        IS.insert(pair<string, int> ("MOVER", 4));
        IS.insert(pair<string, int> ("MOVEM", 5));
        IS.insert(pair<string, int> ("COMP", 6));
        IS.insert(pair<string, int> ("BC", 7));
        IS.insert(pair<string, int> ("DIV", 8));
        IS.insert(pair<string, int> ("READ", 9));
        IS.insert(pair<string, int> ("PRINT", 10));

        // declarative statements
        DL.insert(pair<string, int> ("DC", 1));
        DL.insert(pair<string, int> ("DS", 2));

        // conditional statements
        CC.insert(pair<string, int> ("LT", 1));
        CC.insert(pair<string, int> ("LE", 2));
        CC.insert(pair<string, int> ("EQ", 3));
        CC.insert(pair<string, int> ("GT", 4));
        CC.insert(pair<string, int> ("GE", 5));
        CC.insert(pair<string, int> ("ANY", 6));

        // registers
        REG.insert(pair<string, int> ("AREG", 1));
        REG.insert(pair<string, int> ("BREG", 2));
        REG.insert(pair<string, int> ("CREG", 3));
        REG.insert(pair<string, int> ("DREG", 4));
    }


    string getClassType(string str)
    {
        
    }
};