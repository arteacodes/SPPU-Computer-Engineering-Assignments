// https://github.com/PradnyaSG/Macroprocessor_Two_Pass/blob/main/Main.java

import java.io.*;

class MNTAB
{
    String mName;
    int index;

    MNTAB(String n, int i)
    {
        mName = n;
        index = i;
    }
}


class KPDTAB
{
    String argName;
    String def;  // default value
    
    KPDTAB(String a, String d)
    {
        argName = a;
        def = d;
    }
}


class APTAB
{
    String arg;
    String actual;
    int key;

    APTAB(String a)
    {
        arg = a;
    }
}


public class Main {
    int mntp = 0;
    int mdtp = 0;
    int kpdtp = 0;
    int aptp = 0;
    int count_def = 0;

    MNTAB mnt[] = new MNTAB[30];
    KPDTAB kpdt[] = new KPDTAB[30];
    APTAB apt[] = new APTAB[30];
    String mdt[] = new String[30];


    int searchAPT(String s)
    {
        for (int i=0; i<aptp; i++)
        {
            if (apt[i].arg.equals(s))
            {
                return i;
            }
        }
        return -1;
    }

    int searchKeyPara(String s)
    {
        for (int i=0; i<aptp; i++)
        {
            String t = (apt[i].arg).substring(1);
            if (t.equals(s))
            {
                return i;
            }
        }
        return -1;
    }

    int searchMacro(String s)
    {
        for (int i=0; i<mntp; i++)
        {
            if (mnt[i].mName.equals(s))
            {
                return mnt[i].index;
            }
        }
        return -1;
    }


    void pass1() throws Exception
    {
        File inputFile = new File("input.txt");
        BufferedReader br = new BufferedReader(new FileReader(inputFile));
        FileWriter fw = new FileWriter("pass1_output.txt");

        String in = "";
        String out = "";

        while ((in = br.readLine()) != null)
        {
            String statement[] = in.trim().split(" ");

            if (statement[0].equals("MACRO"))
            {
                in = br.readLine();
                String tokens[] = in.trim().split(" ");
                String instruction = tokens[0];

                mnt[mntp] = new MNTAB(instruction, mntp);

                for (int i=1; i<tokens.length; i++)
                {
                    if (tokens[i].contains("="))
                    {
                        int indeq = tokens[i].indexOf("=");

                        if (indeq < (tokens[i].length() - 1))
                        {
                            String f = tokens[i].substring(0, indeq);
                            indeq += 1;
                            String g = tokens[i].substring(indeq);

                            kpdt[kpdtp] = new KPDTAB(f, g);
                            apt[aptp] = new APTAB(f);
                            apt[aptp].actual = tokens[i].substring(indeq);

                            instruction = instruction.concat(" #" + aptp);

                            aptp++;
                            kpdtp++;
                            count_def++;
                        }
                        else
                        {
                            String f = tokens[i].substring(0, indeq);
                            apt[aptp] = new APTAB(f);
                            instruction = instruction.concat(" #" + aptp);
                            aptp++;
                        }
                    }
                    else
                    {
                        apt[aptp] = new APTAB(tokens[i]);
                        instruction = instruction.concat(" #" + aptp);
                        aptp++;
                    }
                }
                mntp++;
                mdt[mdtp] = new String(instruction);
                mdtp++;

                while (!(out = br.readLine()).equals("MEND"))
                {
                    tokens = out.trim().split(" ");
                    instruction = "";

                    for (int j=0; j<tokens.length; j++)
                    {
                        if (tokens[j].charAt(0) == '&')
                        {
                            int p = searchAPT(tokens[j]);
                            
                            if (p == -1)
                            {
                                System.out.println("Error!");
                            }
                            instruction = instruction.concat("#" + p + " ");
                        }
                        else
                        {
                            instruction += tokens[j] + " ";
                        }
                    }
                    mdt[mdtp] = new String(instruction);
                    mdtp++;
                }  
                mdt[mdtp] = new String("MEND");
                mdtp++;            
            }
            else
            {
                fw.write(in + "\n");
            }
        }
        br.close();
        fw.close();
    }


    void printAll() throws Exception
    {
        System.out.println("***** MNT *****");
        System.out.println("Index | Name");
        for (int i=0; i<mntp; i++)
        {
            System.out.println(mnt[i].index + "   " + mnt[i].mName);
        }

        System.out.println("***** MDT *****");
        for (int i=0; i<mdtp; i++)
        {
            System.out.println(mdt[i]);
        }

        System.out.println("***** KPDTAB *****");
        System.out.println("Arg | Default Value");
        for (int i=0; i<kpdtp; i++)
        {
            System.out.println(kpdt[i].argName + "   " + kpdt[i].def);
        }

        System.out.println("***** APTAB *****");
        System.out.println("Formal | Actual");
        for (int i=0; i<aptp; i++)
        {
            System.out.println(apt[i].arg + "   " + apt[i].actual);
        }
    }


    void pass2() throws Exception
    {
        File inputFile = new File("pass1_output.txt.txt");
        BufferedReader br = new BufferedReader(new FileReader(inputFile));
        FileWriter fw = new FileWriter("pass2_output.txt");

        String in = "";
        String arr[];
        int k;

        while ((in = br.readLine()) != null)
        {
            String tokens[] = in.split(" ");
            int j = searchMacro(tokens[0]);

            if (j != -1)
            {
                arr = mdt[j].trim().split(" ");
                
                // if default arg not given, it is ok
                if (tokens.length < (arr.length - count_def))
                {
                    System.out.println("Error: Incorrect no. of parameters passed!");
                }

                for (int i=1; i<tokens.length; i++)
                {
                    k = Integer.parseInt(arr[i].substring(1));
                    
                    if (tokens[i].contains("="))
                    {
                        int indeq = tokens[i].indexOf("=");
                        String f = tokens[i].substring(0, indeq);
                        int h = searchKeyPara(f);
                        indeq += 1;

                        String g = tokens[i].substring(indeq);
                        apt[h].actual = g;
                    }
                    else
                    {
                        apt[k].actual = tokens[i];
                    }
                }
                while (true)
                {
                    j++;
                    arr = mdt[j].trim().split(" ");
                    String ans = "";

                    if (!arr[0].equals("MEND"))
                    {
                        for (int i=0; i<arr.length; i++)
                        {
                            if (arr[i].charAt(0) == '#')
                            {
                                k = Integer.parseInt(arr[i].substring(1));
                                ans += apt[k].actual;
                                ans += " ";
                            }
                            else
                            {
                                ans += arr[i];
                                ans += " ";
                            }
                        }
                        fw.write(ans + "\n");
                    }
                    else
                    {
                        break;
                    }
                }
            }
            else
            {
                fw.write(in + "\n");
            }
        }
        br.close();
        fw.close();
    }


    void print_APT_KPDT()
    {
        System.out.println("***** KPDTAB *****");
        System.out.println("Arg | Default Value");
        for (int i=0; i<kpdtp; i++)
        {
            System.out.println(kpdt[i].argName + "   " + kpdt[i].def);
        }

        System.out.println("***** APTAB *****");
        System.out.println("Formal | Actual");
        for (int i=0; i<aptp; i++)
        {
            System.out.println(apt[i].arg + "   " + apt[i].actual);
        }
    }


    public static void main(String[] args) throws Exception {
        Main obj = new Main();
        System.out.println("----------------------------");
        System.out.println(" MACRO PROCESSOR PASS - 1");
        System.out.println("----------------------------");
        obj.pass1();
        obj.printAll();

        System.out.println("----------------------------");
        System.out.println(" MACRO PROCESSOR PASS - 2");
        System.out.println("----------------------------");
        obj.pass2();
        obj.print_APT_KPDT();
    }
}
