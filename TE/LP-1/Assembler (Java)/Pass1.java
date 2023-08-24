import java.io.*;
import java.util.*;

class Mnemonics
{
    private Map<String, Integer> AD = new HashMap<>();
    private Map<String, Integer> IS = new HashMap<>();
    private Map<String, Integer> DL = new HashMap<>();
    private Map<String, Integer> RG = new HashMap<>();
    private Map<String, Integer> CC = new HashMap<>();

    // add all mnemonics in constructor
    public Mnemonics() {
        AD.put("START", 1);
        AD.put("END", 2);
        AD.put("ORIGIN", 3);
        AD.put("EQU", 4);
        AD.put("LTORG", 5);

        IS.put("STOP", 0);
        IS.put("ADD", 1);
        IS.put("SUB", 2);
        IS.put("MULT", 3);
        IS.put("MOVER", 4);
        IS.put("MOVEM", 5);
        IS.put("COMP", 6);
        IS.put("BC", 7);
        IS.put("DIV", 8);
        IS.put("READ", 9);
        IS.put("PRINT", 10);

        DL.put("DC", 1);
        DL.put("DS", 2);

        RG.put("AREG", 1);
        RG.put("BREG", 2);
        RG.put("CREG", 2);
        RG.put("DREG", 2);

        CC.put("LT", 1);
        CC.put("LE", 2);
        CC.put("EQ", 3);
        CC.put("GT", 4);
        CC.put("GE", 5);
        CC.put("ANY", 6);
    }

    public String getClassType(String string)
    {
        if (AD.containsKey(string)) {
            return "AD";
        }
        else if (IS.containsKey(string)) {
            return "IS";
        }
        else if (DL.containsKey(string)) {
            return "DL";
        }
        else if (RG.containsKey(string)) {
            return "RG";
        }
        else if (CC.containsKey(string)) {
            return "CC";
        }
        else {
            return "";
        }
    }

    public int getMachineCode(String string)
    {
        if (AD.containsKey(string)) {
            return AD.get(string);
        }
        else if (IS.containsKey(string)) {
            return IS.get(string);
        }
        else if (DL.containsKey(string)) {
            return DL.get(string);
        }
        else if (RG.containsKey(string)) {
            return RG.get(string);
        }
        else if (CC.containsKey(string)) {
            return CC.get(string);
        }
        else {
            return -1;
        }
    }
}


class IntermediateCodeEntry {
    String type;
    Object value;

    IntermediateCodeEntry(String type, Object value) {
        this.type = type;
        this.value = value;
    }
}



public class Pass1
{
    private Mnemonics opTab = new Mnemonics();
    private Map<String, Integer> symTab = new HashMap<>();
    private List<int[]> litTab = new ArrayList<>();
    private List<Integer> poolTab = new ArrayList<>(Collections.singletonList(0));
    private int litIndex = 0;
    private int litPtr = 0;
    private int LC = 0;
    private List<List<IntermediateCodeEntry>> IC;

    private FileWriter ICFile;  
    private FileWriter symTabFile;
    private FileWriter litTabFile;
    private FileWriter poolTabFile;
    private BufferedReader inputFile;

    // open all files in constructor
    public Pass1() throws IOException {
        ICFile = new FileWriter("intermediateCode.txt");
        symTabFile = new FileWriter("symbolTable.txt");
        litTabFile = new FileWriter("literalTable.txt");
        poolTabFile = new FileWriter("poolTable.txt");
        inputFile = new BufferedReader (new FileReader("test-case-1.txt"));
        IC = new ArrayList<>();
    }


    public int location(String string) {
        if (string.contains("+")) {
            String[] parts = string.split("\\+");
            return symTab.get(parts[0]) + Integer.parseInt(parts[1]);
        }
        else if (string.contains("-")) {
            String[] parts = string.split("-");
            return symTab.get(parts[0]) - Integer.parseInt(parts[1]);
        }
        else {
            return symTab.get(string);
        }
    }


    public void compute() throws IOException {
        String line;
        while ((line = inputFile.readLine()) != null) {
            IC.add(new ArrayList<>());
    
            line = line.trim();
            String[] parts = line.split("\t");
    
            String label = parts[0];
            String opcode = parts[1];
            String operand1 = parts.length >= 3 ? parts[2] : null;
            String operand2 = parts.length >= 4 ? parts[3] : null;
            

            // for labels
            if (!label.isEmpty()) {
                symTab.put(label, LC);
            }


            // for opcodes that need to be handled separately
            if (opcode.equals("START")) {
                LC = Integer.parseInt(operand1);
                IC.get(IC.size() - 1).add(new IntermediateCodeEntry("AD", 1));
                IC.get(IC.size() - 1).add(new IntermediateCodeEntry("C", LC));
            }
            else if (opcode.equals("LTORG")) {
                for (int i = poolTab.get(poolTab.size() - 1); i < litTab.size(); i++) {
                    litTab.get(i)[1] = LC;
                    IC.get(IC.size() - 1).add(new IntermediateCodeEntry("DL", 1));
                    IC.get(IC.size() - 1).add(new IntermediateCodeEntry("C", litTab.get(i)[0]));
                    IC.get(IC.size() - 1).add(new IntermediateCodeEntry("LC", LC));
                    LC++;
                    litPtr++;
                    if (i < litTab.size() - 1) {
                        IC.add(new ArrayList<>());
                    }
                }
                poolTab.add(litPtr);
            }
            else if (opcode.equals("ORIGIN")) {
                LC = location(operand1);
                IC.get(IC.size() - 1).add(new IntermediateCodeEntry("AD", 3));
                IC.get(IC.size() - 1).add(new IntermediateCodeEntry("C", LC));
            }
            else if (opcode.equals("EQU")) {
                int newLocation = location(operand1);
                symTab.put(label, newLocation);
                IC.get(IC.size() - 1).add(new IntermediateCodeEntry("AD", 4));
                IC.get(IC.size() - 1).add(new IntermediateCodeEntry("C", newLocation));
            }
            else if (opcode.equals("DC")) {
                IC.get(IC.size() - 1).add(new IntermediateCodeEntry("DL", 1));
                IC.get(IC.size() - 1).add(new IntermediateCodeEntry("C", Integer.parseInt(operand1)));
                IC.get(IC.size() - 1).add(new IntermediateCodeEntry("LC", LC));
                LC++;
            }
            else if (opcode.equals("DS")) {
                IC.get(IC.size() - 1).add(new IntermediateCodeEntry("DL", 2));
                IC.get(IC.size() - 1).add(new IntermediateCodeEntry("C", Integer.parseInt(operand1)));
                IC.get(IC.size() - 1).add(new IntermediateCodeEntry("LC", LC));
                LC += Integer.parseInt(operand1);
            }
            else if (opcode.equals("STOP")) {
                IC.get(IC.size() - 1).add(new IntermediateCodeEntry("IS", 0));
                IC.get(IC.size() - 1).add(new IntermediateCodeEntry("LC", LC));
                LC++;
            }
            else if (opcode.equals("END")) {
                IC.get(IC.size() - 1).add(new IntermediateCodeEntry("AD", 2));
                if (litPtr != litTab.size()) {
                    for (int i = poolTab.get(poolTab.size() - 1); i < litTab.size(); i++) {
                        IC.add(new ArrayList<>());
                        litTab.get(i)[1] = LC;
                        IC.get(IC.size() - 1).add(new IntermediateCodeEntry("DL", 1));
                        IC.get(IC.size() - 1).add(new IntermediateCodeEntry("C", litTab.get(i)[0]));
                        IC.get(IC.size() - 1).add(new IntermediateCodeEntry("LC", LC));
                        LC++;
                        litPtr++;
                    }
                    poolTab.add(litPtr);
                }
            }
            else if (opcode.equals("BC")) {
                IC.get(IC.size() - 1).add(new IntermediateCodeEntry("IS", 7));
                String classType = opTab.getClassType(operand1);
                int machineCode = opTab.getMachineCode(operand1);
                IC.get(IC.size() - 1).add(new IntermediateCodeEntry(classType, machineCode));
                if (!symTab.containsKey(operand2)) {
                    symTab.put(operand2, null);
                }
                List<String> symTabKeys = new ArrayList<>(symTab.keySet());
                IC.get(IC.size() - 1).add(new IntermediateCodeEntry("S", symTabKeys.indexOf(operand2)));
                IC.get(IC.size() - 1).add(new IntermediateCodeEntry("LC", LC));
                LC++;
            }
            else if (opcode.equals("READ")) {
                IC.get(IC.size() - 1).add(new IntermediateCodeEntry("IS", 9));
                symTab.put(operand1, null);
                List<String> symTabKeys = new ArrayList<>(symTab.keySet());
                IC.get(IC.size() - 1).add(new IntermediateCodeEntry("S", symTabKeys.indexOf(operand1)));
                IC.get(IC.size() - 1).add(new IntermediateCodeEntry("LC", LC));
                LC++;
            }
            else if (opcode.equals("PRINT")) {
                IC.get(IC.size() - 1).add(new IntermediateCodeEntry("IS", 10));
                List<String> symTabKeys = new ArrayList<>(symTab.keySet());
                IC.get(IC.size() - 1).add(new IntermediateCodeEntry("S", symTabKeys.indexOf(operand1)));
                IC.get(IC.size() - 1).add(new IntermediateCodeEntry("LC", LC));
                LC++;
            }
            else {
                String classType = opTab.getClassType(opcode);
                int machineCode = opTab.getMachineCode(opcode);
                IC.get(IC.size() - 1).add(new IntermediateCodeEntry(classType, machineCode));

                classType = opTab.getClassType(operand1);
                machineCode = opTab.getMachineCode(operand1);
                IC.get(IC.size() - 1).add(new IntermediateCodeEntry(classType, machineCode));
                
                try {
                    if (operand2.contains("=")){
                        int constant = Integer.parseInt(operand2.replace("=", "").replace("'", ""));
                        litTab.get(litIndex)[0] = constant;
                        IC.get(IC.size() - 1).add(new IntermediateCodeEntry("L", litIndex));
                        IC.get(IC.size() - 1).add(new IntermediateCodeEntry("LC", LC));
                        litIndex++;
                    }
                    else {
                        if (!symTab.containsKey(operand2)) {
                            symTab.put(operand2, null);
                        }
                        List<String> symTabKeys = new ArrayList<>(symTab.keySet());
                        IC.get(IC.size() - 1).add(new IntermediateCodeEntry("S", symTabKeys.indexOf(operand2)));
                        IC.get(IC.size() - 1).add(new IntermediateCodeEntry("LC", LC));
                    }
                }
                catch (NullPointerException n) {
                    n.getStackTrace();
                }
                
                LC++;
            }
        }

        // print all tables
        printST();
        printLT();
        printPT();
        printIC();
    }


    public void printST() {
        System.out.println("\n--------------------");
        System.out.println("SYMBOL TABLE");
        System.out.println("--------------------");

        try {
            for (Map.Entry<String, Integer> entry: symTab.entrySet()) {
                String line = entry.getKey() + "\t" + entry.getValue() + "\n";
                System.out.print(line);
                symTabFile.write(line);
            }
            symTabFile.close();
        }
        catch (IOException e) {
            e.printStackTrace();
        }
        System.out.println();
    }


    public void printLT() {
        System.out.println("\n--------------------");
        System.out.println("LITERAL TABLE");
        System.out.println("--------------------");

        try {
            for (int item = 0; item < litTab.size(); item++) {
                String line = item + "\t" + litTab.get(item) + "\n";
                System.out.print(line);
                litTabFile.write(line);
            }
            litTabFile.close();
        }
        catch (IOException e) {
            e.printStackTrace();
        }
        System.out.println();
    }


    public void printPT() {
        System.out.println("\n--------------------");
        System.out.println("POOL TABLE");
        System.out.println("--------------------");

        try {
            for (int item = 0; item < poolTab.size(); item++) {
                System.out.print(poolTab.get(item));
                poolTabFile.write(poolTab.get(item) + "\n");
            }
            poolTabFile.close();
        }
        catch (IOException e) {
            e.printStackTrace();
        }
        System.out.println();
    }


    public void printIC() {
        System.out.println("\n----------------------------------------------------");
        System.out.println("INTERMEDIATE CODE");
        System.out.println("----------------------------------------------------");
        try {
            for (List<IntermediateCodeEntry> item : IC) {
                StringBuilder line = new StringBuilder();
                for (int i = 0; i < item.size(); i++) {
                    line.append(item.get(i).type).append(item.get(i).value);
                    if (i != item.size() - 1) {
                        line.append("\t");
                    }
                }
                line.append("\n");
                System.out.print(line);
                ICFile.write(line.toString());
            }
            ICFile.close();
        }
        catch (IOException e) {
            e.printStackTrace();
        }
    }

    public static void main(String[] args) throws IOException {
        Pass1 obj = new Pass1();
        obj.compute();
    }
}
