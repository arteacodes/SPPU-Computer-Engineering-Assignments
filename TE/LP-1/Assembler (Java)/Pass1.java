import java.io.*;
import java.util.*;

class Mnemonics {
    private Map<String, Integer> AD = new HashMap<>();
    private Map<String, Integer> IS = new HashMap<>();
    private Map<String, Integer> DL = new HashMap<>();
    private Map<String, Integer> REG = new HashMap<>();
    private Map<String, Integer> CC = new HashMap<>();

    public Mnemonics() {
        AD.put("START", 1);
        AD.put("END", 2);
        AD.put("ORIGIN", 3);
        AD.put("EQU", 4);
        AD.put("LTORG", 5);

        IS.put("STOP", 0);
        IS.put("ADD", 1);
        IS.put("SUB", 2);
        // ... Add other IS codes here ...

        DL.put("DC", 1);
        DL.put("DS", 2);

        REG.put("AREG", 1);
        REG.put("BREG", 2);
        // ... Add other register codes here ...

        CC.put("LT", 1);
        CC.put("LE", 2);
        // ... Add other condition codes here ...
    }

    public String getClassType(String string) {
        if (AD.containsKey(string)) {
            return "AD";
        } else if (IS.containsKey(string)) {
            return "IS";
        } else if (DL.containsKey(string)) {
            return "DL";
        } else if (REG.containsKey(string)) {
            return "RG";
        } else if (CC.containsKey(string)) {
            return "CC";
        } else {
            return "";
        }
    }

    public int getCode(String string) {
        if (AD.containsKey(string)) {
            return AD.get(string);
        } else if (IS.containsKey(string)) {
            return IS.get(string);
        } else if (DL.containsKey(string)) {
            return DL.get(string);
        } else if (REG.containsKey(string)) {
            return REG.get(string);
        } else if (CC.containsKey(string)) {
            return CC.get(string);
        } else {
            return -1;
        }
    }
}

public class Pass1 {
    private Mnemonics opTab = new Mnemonics();
    private Map<String, Integer> symTab = new HashMap<>();
    private List<int[]> litTab = new ArrayList<>();
    private List<Integer> poolTab = new ArrayList<>(Collections.singletonList(0));
    private int litIndex = 0;
    private int litPtr = 0;
    private int LC = 0;
    private List<List<String>> IC = new ArrayList<>();

    private BufferedReader ICFile;
    private BufferedReader symTabFile;
    private BufferedReader litTabFile;
    private BufferedWriter inputFile;

    public Pass1() throws IOException {
        ICFile = new BufferedReader(new FileReader("intermediateCode.txt"));
        symTabFile = new BufferedReader(new FileReader("symbolTable.txt"));
        litTabFile = new BufferedReader(new FileReader("literalTable.txt"));
        inputFile = new BufferedWriter(new FileWriter("test-case-1.txt"));
    }

    public int location(String string) {
        if (string.contains("+")) {
            String[] parts = string.split("\\+");
            return symTab.get(parts[0]) + Integer.parseInt(parts[1]);
        } else if (string.contains("-")) {
            String[] parts = string.split("-");
            return symTab.get(parts[0]) - Integer.parseInt(parts[1]);
        } else {
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
            String operand1 = (parts.length >= 3) ? parts[2] : "";
            String operand2 = (parts.length >= 4) ? parts[3] : "";
    
            // Process the opcode logic here
            // ...
    
            // For example, you can handle START opcode like this:
            if (opcode.equals("START")) {
                LC = Integer.parseInt(operand1);
                IC.get(IC.size() - 1).add(new String[]{"AD", "1"});
                IC.get(IC.size() - 1).add(new String[]{"C", String.valueOf(LC)});
            }
    
        }
    }
    
    }

    public void printST() {

    }

    public void printLT() {
 
    }

    public void printPT() {

    }

    public void printIC() {

    }

    public static void main(String[] args) throws IOException {
        Pass1 obj = new Pass1();
        obj.compute();
    }
}
