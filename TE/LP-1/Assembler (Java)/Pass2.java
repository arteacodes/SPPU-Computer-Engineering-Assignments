import java.io.*;
import java.util.HashMap;
import java.util.Map;
import java.util.regex.*;

public class Pass2 {
    private Map<Integer, Integer> symTab = new HashMap<>();
    private Map<Integer, Integer> litTab = new HashMap<>();

    private BufferedReader ICFile;
    private BufferedReader symTabFile;
    private BufferedReader litTabFile;
    private BufferedWriter outputFile;

    private Pattern pattern = Pattern.compile("\\('\\([A-Z]{,2}\\)',\\s(\\d+)\\)");

    private static String tab = "\t";
    private static String newline = "\n";

    public Pass2() throws IOException {
        ICFile = new BufferedReader(new FileReader("intermediateCode.txt"));
        symTabFile = new BufferedReader(new FileReader("symbolTable.txt"));
        litTabFile = new BufferedReader(new FileReader("literalTable.txt"));
        outputFile = new BufferedWriter(new FileWriter("machineCode.txt"));
    }

    private String convert(int number) {
        String string = Integer.toString(number);
        if (string.length() == 1) {
            return "00" + string;
        } else if (string.length() == 2) {
            return "0" + string;
        } else {
            return string;
        }
    }

    private void readST() throws IOException {
        System.out.println("\n--------------------");
        System.out.println("SYMBOL TABLE");
        System.out.println("--------------------");
        String line;
        while ((line = symTabFile.readLine()) != null) {
            String[] parts = line.split("\t");
            int index = Integer.parseInt(parts[0]);
            int location = Integer.parseInt(parts[2]);
            symTab.put(index, location);
            System.out.println(index + tab + location);
        }
        System.out.println();
    }

    private void readLT() throws IOException {
        System.out.println("\n--------------------");
        System.out.println("LITERAL TABLE");
        System.out.println("--------------------");
        String line;
        while ((line = litTabFile.readLine()) != null) {
            String[] parts = line.split("\t");
            int index = Integer.parseInt(parts[0]);
            int location = Integer.parseInt(parts[2]);
            litTab.put(index, location);
            System.out.println(index + tab + location);
        }
        System.out.println();
    }

    private void generate() throws IOException {
        readST();
        readLT();
        System.out.println("\n----------------------------------------------------");
        System.out.println("MACHINE CODE");
        System.out.println("----------------------------------------------------");
        System.out.println("LC\tOPCODE\tOPERAND-1\tOPERAND-2");

        String line;
        while ((line = ICFile.readLine()) != null) {
            line = line.trim();
            String[] parts = line.split("\t");

            Matcher matcher = pattern.matcher(parts[0]);
            if (matcher.matches()) {
                String group1 = matcher.group(1);
                String group2 = matcher.group(2);

                String machineCode = "";
                String location = parts[parts.length - 2];
                machineCode += location + tab;

                if ("IS".equals(group1) || "DL".equals(group1)) {
                    machineCode += convert(Integer.parseInt(group2)) + tab;

                    if ("IS".equals(group1) && ("10".equals(group2) || "9".equals(group2))) {
                        matcher = pattern.matcher(parts[1]);
                        if (matcher.matches()) {
                            int key = Integer.parseInt(matcher.group(2));
                            machineCode += "000" + tab + convert(symTab.get(key)) + newline;
                        }
                    } else if ("0".equals(group2)) {
                        machineCode += "000" + tab + "000" + newline;
                    } else {
                        matcher = pattern.matcher(parts[1]);
                        if (matcher.matches()) {
                            machineCode += convert(Integer.parseInt(matcher.group(2))) + tab;

                            matcher = pattern.matcher(parts[2]);
                            if (matcher.matches()) {
                                if ("S".equals(matcher.group(1))) {
                                    int key = Integer.parseInt(matcher.group(2));
                                    machineCode += convert(symTab.get(key)) + newline;
                                } else if ("L".equals(matcher.group(1))) {
                                    int key = Integer.parseInt(matcher.group(2));
                                    machineCode += convert(litTab.get(key)) + newline;
                                }
                            }
                        }
                    }
                } else {
                    if ("1".equals(group2)) {
                        machineCode += "000" + tab + "000" + tab;

                        matcher = pattern.matcher(parts[1]);
                        if (matcher.matches()) {
                            machineCode += convert(Integer.parseInt(matcher.group(2))) + newline;
                        }
                    } else {
                        machineCode += "000" + tab + "000" + tab + "000" + newline;
                    }
                }

                System.out.print(machineCode);
                outputFile.write(machineCode);
            }
        }

        outputFile.close();
        symTabFile.close();
        litTabFile.close();
    }

    public static void main(String[] args) throws IOException {
        Pass2 obj = new Pass2();
        obj.generate();
    }
}
