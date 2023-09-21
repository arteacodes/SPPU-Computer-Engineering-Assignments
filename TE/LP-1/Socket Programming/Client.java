import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.io.IOException;
import java.io.PrintStream;
import java.net.Socket;
import java.util.*;


public class Client
{
    public static void main(String[] args)
    {
        Scanner sc = new Scanner(System.in);
        String sip;
        int pno;
    
        System.out.println("This is the Client Program");
        System.out.println("Enter the Server ip");
        sip = sc.nextLine();
    
        System.out.println("Enter the Port Number to Use");
        pno = sc.nextInt();
        System.out.println("Attempting to create the Socket");
    
        Socket MyClient = null;
    
        try {
            MyClient = new Socket(sip, pno);
            System.out.println("Socket Created Successfully");
        }
        catch (IOException e) {
            System.out.println(e);
        }
        
        System.out.println("Attempting to create input Stream");
        DataInputStream input=null;
        
        try {
            input = new DataInputStream(MyClient.getInputStream());
            System.out.println("Input Stream Created Successfully");
        }
        catch (IOException e) {
            System.out.println(e);
        }
     
        System.out.println("Attempting to create Ouput Stream");
        DataOutputStream output=null;
        
        try {
            output = new DataOutputStream(MyClient.getOutputStream());
        }
        catch (IOException e1) {
            e1.printStackTrace();
        }
        
        System.out.println("Output Stream created successfully");
        System.out.println("Connected to Echo Server");
        System.out.println("Enter the text which you want to be echoed back");
        System.out.println("Type quit to exit");
        
        while(true) {
            String strIn=sc.nextLine();
            String copy=new String(strIn);
            
            if (copy.trim().equals("quit")) { 
                System.out.println("Detected quit.\nTerminating Program");
                break;
            }
            
            try {
                output.writeUTF(strIn);
            }
            catch (IOException e) {
                e.printStackTrace();
            }
            
            try {
                System.out.println(input.readUTF());
            }
            catch (IOException e) {
                e.printStackTrace();
            }
        }
     
        try {
            output.close();
            input.close();
            MyClient.close();
        } 
        catch (IOException e) {
            System.out.println(e);
        }
    }
}