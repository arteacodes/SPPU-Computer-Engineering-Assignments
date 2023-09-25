import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.io.IOException;
import java.net.Socket;
import java.util.*;


public class Client
{
    public static void main(String[] args)
    {
        Scanner sc = new Scanner(System.in);
        String sip;
        int pno;
    
        System.out.println("This is the Client Program.");
        System.out.println("Enter the Server IP: ");
        sip = sc.nextLine();
    
        System.out.println("Enter the Port Number to use: ");
        pno = sc.nextInt();
        System.out.println("\nAttempting to create the Socket...");
    
        Socket MyClient = null;
    
        try {
            MyClient = new Socket(sip, pno);
            System.out.println("Socket created successfully!");
        }
        catch (IOException e) {
            System.out.println(e);
        }
        
        System.out.println("\nAttempting to create Input Stream...");
        DataInputStream input = null;
        
        try {
            input = new DataInputStream(MyClient.getInputStream());
            System.out.println("Input Stream created successfully!");
        }
        catch (IOException e) {
            System.out.println(e);
        }
     
        System.out.println("\nAttempting to create Ouput Stream...");
        DataOutputStream output = null;
        
        try {
            output = new DataOutputStream(MyClient.getOutputStream());
        }
        catch (IOException e1) {
            e1.printStackTrace();
        }
        
        System.out.println("Output Stream created successfully!");
        System.out.println("\nConnected to Echo Server.");
        System.out.println("Enter message to be echoed back (type 'quit' to exit): ");
        
        while(true) {
            String strIn = sc.nextLine();
            String copy = new String(strIn);
            
            if (copy.trim().equals("quit")) { 
                System.out.println("Detected quit.\nTerminating program.");
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
        sc.close();
     
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