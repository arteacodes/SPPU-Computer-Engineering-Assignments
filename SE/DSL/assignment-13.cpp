/*
A double-ended queue (deque) is a linear list in which additions and deletions may be made at either end. Obtain a data representation mapping a deque into a one-dimensional array. Write C++ program to simulate deque with functions to add and delete elements from either end of the deque.
*/

#include<iostream>
using namespace std;
#define SIZE 5

class Dequeue
{
	int a[10];
    int front;
    int rear;
    int count;

public:
    Dequeue();
	void add_front(int);
	void add_rear(int);
	void delete_front();
	void delete_rear();
	void display();
};

 Dequeue::Dequeue()
{
	front=-1;
	rear=-1;
	count=0;
}


void Dequeue::add_front(int item)
{
	int  i;


	if(rear>=SIZE-1)
	{
		cout<<"\nQueue overflow!";
	}
	else
	{
        if(front==-1)
	    {
		    front++;
		    rear++;
		    a[rear]=item;
		    count++;
	    }
        else 
        {
            for(i=count;i>0;i--) {
			    a[i]=a[i-1];
		    }
		    a[i]=item;
		    count++;
		    rear++;
        }
		
	}
}



void Dequeue::add_rear(int item)
{

	if(front==-1)
	{
		front++;
		rear++;
		a[rear]=item;
		count++;
	}
	else if(rear>=SIZE-1)
	{
		cout<<"\nQueue overflow!";
		return;
	}
	else
	{
		a[++rear]=item;
	}


}



void Dequeue::display()
{

	for(int i=front;i<=rear;i++)
	{
		cout<<a[i]<<" ";	}
}


void Dequeue::delete_front()
{
	if(front==-1)
	{
		cout<<"Queue underflow!";
		return;
	}
	else
	{
		if(front==rear)
		{
			front=rear=-1;
			return;
		}
		cout<<"The deleted element is "<<a[front];
		++front;
	}


}

void Dequeue::delete_rear()
{
	if(front==-1)
	{
		cout<<"Queue underflow!";
		return;
	}
	else
	{
		if(front==rear)
		{
			front=rear=-1;
		}
		cout<<"The deleted element is "<<a[rear];
		--rear;
	}


}



int main()
{
	int c,item;
 Dequeue d1;

	do
	{
		cout<<"\n\nOPERATIONS\n";
		cout<<"\n1.Insert at start";
		cout<<"\n2.Insert at end";
		cout<<"\n3.Delete from start";
		cout<<"\n4.Delete from end";
		cout<<"\n5.Display";
		cout<<"\n6.Exit";
		cout<<"\nEnter your choice: ";
		cin>>c;

		switch(c)
		{
		case 1:
			cout<<"Enter the element to be inserted: ";
			cin>>item;
			d1.add_front(item);
			break;

		case 2:
			cout<<"Enter the element to be inserted: ";
			cin>>item;
			d1.add_rear(item);
			break;

		case 3:
			d1.delete_front();
			break;

		case 4:
			d1.delete_rear();
			break;

		case 5:
			d1.display();
			break;

		case 6:
			exit(1);
			break;

		default:
			cout<<"Invalid choice\n";
			break;
		}

	}while(c!=7);
	return 0;

}
