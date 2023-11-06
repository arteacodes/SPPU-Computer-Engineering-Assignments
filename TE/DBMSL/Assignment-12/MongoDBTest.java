package demo2;

import java.util.*;

import org.bson.*;

import com.mongodb.*;

import com.mongodb.client.MongoDatabase;
import com.mongodb.client.MongoCollection;

import com.mongodb.client.model.Filters;
import com.mongodb.client.model.Updates;

public class MongoDBTest
{
	public static int choice()
	{
		int c;
		Scanner sc = new Scanner(System.in);
		System.out.println("Operations:");
		System.out.println("1. Insert");
		System.out.println("2. Read");
		System.out.println("3. Update");
		System.out.println("4. Delete");
		System.out.println("Press 0 to EXIT");
		System.out.println("Enter choice: ");
		
		c = sc.nextInt();
		return c;
	}
	
	public static void main(String args[])
	{
		// make mongo client
		MongoClient client = new MongoClient("127.0.0.1", 27017);
		
		// connect to db
		MongoDatabase db = client.getDatabase("jdbcmongo");
		System.out.println("Connected!");
		
		// connect to collection
		MongoCollection <Document> collection = db.getCollection("mycol");
		
		Scanner sc = new Scanner (System.in);
		int id, age;
		String name;
		
		int ch = -1;
		
		do
		{
			// get operation choice
			ch = choice();
			
			if (ch == 1)
			{
				System.out.println("Enter ID: ");
				id = sc.nextInt();
				System.out.println("Enter Name: ");
				name = sc.next();
				System.out.println("Enter Age: ");
				age = sc.nextInt();
				
				BasicDBObject d1 = new BasicDBObject("id", id).append("name", name).append("age",  age);
				
				Document doc = new Document(d1);
				collection.insertOne(doc);
				
				System.out.println("Inserted!");
			}
			else if (ch == 2)
			{
				for (Document doc: collection.find())
				{
					System.out.println(doc.toJson());
				}
			}
			else if (ch == 3)
			{
				System.out.println("Enter ID: ");
				id = sc.nextInt();
				System.out.println("Enter Name: ");
				name = sc.next();
				System.out.println("Enter Age: ");
				age = sc.nextInt();
				
				collection.updateOne(Filters.eq("id", id), Updates.set("name",  name));
				collection.updateOne(Filters.eq("id", id), Updates.set("age",  age));
				System.out.println("Updated!");
			}
			else if (ch == 4)
			{
				System.out.println("Enter ID: ");
				id = sc.nextInt();
				
				collection.deleteOne(Filters.eq("id", id));
				System.out.println("Deleted!");
			}
			else
			{
				System.out.println("Invalid input.");
			}
		} while (ch != 0);
		client.close();
	}
}
