package assignment8;

import java.util.*;
import java.sql.*;

public class Main
{
    public static void main(String[] args)
    {
        String url = "jdbc:mysql://10.10.15.233/te31301db";
        String username = "te31301";
        String password = "te31301";

        try
        {
            Class.forName("com.mysql.cj.jdbc.Driver");
            Connection con = DriverManager.getConnection(url, username, password);
            Statement st = con.createStatement();
            
            if (con != null && !con.isClosed())
            {
                System.out.println("Database connected!");
            }   
            else
            {
                System.out.println("Not connected.");
            }
            
            String query = "select bookid, bname from library;";
        
            ResultSet rs = st.executeQuery(query);
            
            while (rs.next()) {
            	// indexing starts from 1
            	String output = rs.getInt(1) + " " + rs.getString(2);
                System.out.println(output);
            }
            
            st.close();
            con.close();
            System.out.println("Connection closed.");
        }
        catch(Exception e) {}
    }
}
