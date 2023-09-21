import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.io.IOException;
import java.io.PrintStream;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.Scanner;


public class Server implements Runnable
{
    int id;
    Socket csocket;
    
    Server(Socket csocket, int id) {
        this.id = id;
        this.csocket = csocket;
    }

    public void run() {
        System.out.println("Client with Id= " + id + " connected");
        DataInputStream input=null;
        
        try {
            input = new DataInputStream(csocket.getInputStream());
        }
        catch (IOException e) {
            System.out.println(e);
        }
     
        DataOutputStream output=null;
        
        try {
            output = new DataOutputStream(csocket.getOutputStream());
        }
        catch (IOException e) {
            System.out.println(e);
        }
     
        while(true) {
            try {
                output.writeUTF(input.readUTF());
            }
            catch (IOException e) {
                System.out.println("Client with Id= " + id + " exited");
            return;    
            }
        }
    }

    public static void main(String[] args) {
        int id = 1;
        Scanner sc = new Scanner(System.in);
        int pno;
    
        System.out.println("This is the Server Program");
        System.out.println("Enter the port number");
        pno=sc.nextInt();
  
        System.out.println("Attempting to create the server socket");
        ServerSocket MyService=null;
    
        try {
            MyService = new ServerSocket(pno);
            System.out.println("Server Socket Created Successfully");
        }
        catch (IOException e) {
            System.out.println(e);
        }
    
        System.out.println("Waiting for client");
  
        while (true) {
            Socket sock=null;
        
            try {
                sock = MyService.accept();
            }
            catch (IOException e) {
                e.printStackTrace();
            }
            
            System.out.println("Connected to a new Client");
            new Thread(new Server(sock,id++)).start();
        }    
    }
}