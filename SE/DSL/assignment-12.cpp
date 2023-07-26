/*
Write program to implement a priority queue in C++ using an order list/array to store the items in the queue. Create a class that includes the data items (which should be template) and the priority (which should be int). The order list/array should contain these objects, with operator <= overloaded so that the items with highest priority appear at the beginning of the list/array (which will make it relatively easy to retrieve the highest item.)
*/



#include<iostream>
using namespace std;
#define MAX 10
//const int MAX=5;

class Item
{
	int id;
	int priority;  // greater integer value = higher priority
	friend class Queue;  //Queue can access private members of class Item
public:
	void getdata()
	{
		cout<<"\nEnter Item ID: ";
		cin>>id;
		cout<<"Enter Item Priority: ";
		cin>>priority;
	}

	void putdata()
	{  
		cout<<"\n"<<id;
		cout<<"\t\t"<<priority;
	}

	bool operator<=(Item it) {
		if (priority<=it.priority)
			return true;
		return false;
	}
	
};

class Queue
{
	int front,rear;
	Item queue[MAX]; 
public:
	Queue()
	{
		front=-1;
		rear=-1;
	}
	bool isEmpty();
	bool isFull();
	void enqueue();
	void dequeue();
	void display();

};

bool Queue::isEmpty()
{
	if(front==(rear+1)||rear==-1)
	//if (front == rear)
		return 1;
	else 
		return 0;
}

bool Queue::isFull()
{
	if(rear==MAX-1)
	{
		return 1;
	}
	else
		return 0;
}

void Queue::enqueue()
{
	Item it;

	if(isFull())
	{
		cout<<"\nQueue is Full.";
	}
	else
	{
		it.getdata();
		if(front==-1)  //empty
		{
			front++;
			rear++;
			queue[rear]=it;
		}
		else
		{

			int i=rear;
			while((i>=0) && (queue[i]<=it))  //overloaded operator used
			{
				queue[i+1]=queue[i];
				i--;
			}
			queue[i+1]=it;
			rear++;
		}
		cout<<"\nItem Added To Queue."<<endl;
	}
}

void Queue::dequeue()
{
	if(isEmpty())
	{
		cout<<"\nQueue is Empty.";
	}
	else
	{
		front++;
		cout<<"\nItem Processed From Queue."<<endl;
	}
}

void Queue::display()
{
	if(isEmpty())
	{
		cout<<"\nQueue is Empty.";
	}
	else
	{
		for(int i=front;i<=rear;i++)
		{
			queue[i].putdata();
		}
	}
}

int main()
{

	int ch;
	Queue q;

	do
	{

		cout<<"\nOPERATIONS\n";
		cout<<"1.Insert item\n";
		cout<<"2.Remove item\n";
		cout<<"3.Display\n";
		cout<<"4.Exit\n";

		cout<<"Enter choice: ";
		cin>>ch;

		switch(ch)
		{

			case 1: 
				q.enqueue();
				break;

			case 2: 
				q.dequeue();
				break;

			case 3:
				cout<<"Item ID ";
				cout<<"\t  Item Priority ";
				q.display();
				break;

			case 4:
				cout<<"Exiting Program...\n";
				break;

			default:
				cout<<"Invalid input!\n";
				break;
		}
	} while(ch!=4);

	return 0;
}
