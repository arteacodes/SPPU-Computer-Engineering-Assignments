/*
Queues are frequently used in computer programming, and a typical example is the creation of a job queue by an operating system. If the operating system does not use priorities, then the jobs are processed in the order they enter the system. Write C++ program for simulating job queue. Write
functions to add job, display job and delete job from queue.
*/


#include <iostream>
using namespace std;

#define MAX 20

struct queue {
	int jobs[MAX];
	int front;
	int rear;
};

class Queue
{
	struct queue q;

public:
	Queue(){
		q.front = -1;
    	q.rear = -1;
    }

    int isEmpty();
    int isFull();
    void enqueue(int);
    int dequeue();
    void display();
};


int Queue::isEmpty()
{
	return(q.front==-1)?1:0;
}

int Queue::isFull()
{
	return(q.rear==MAX-1)?1:0;
}

void Queue::enqueue(int x)
{
	if (q.front==-1)
		++q.front;
	if (!isFull()) {
		q.jobs[++q.rear]=x;
		cout<<"Job added: "<<x<<"\n";
	}
	else
		cout<<"Queue overflow!\n";
}

int Queue::dequeue()
{
	if (!isEmpty()) {
		int del = q.jobs[q.front]; 
		if (q.front==q.rear)
			q.front = q.rear = -1;
		else
			++q.front;
		cout<<"Job deleted: "<<del<<"\n";
		return del;
	}
	else {
		cout<<"Queue underflow!\n";
		return 0;
	}
}

void Queue::display()
{   int i;
    cout<<"SNo.\tJob\n";
    for(i=q.front; i<=q.rear; i++)
	     cout<<i+1<<"\t"<<q.jobs[i]<<"\n";
}

int main()
{
	Queue obj;
	int ch, x;

	do{
		cout<<"\nOPERATIONS\n 1.Insert Job\n 2.Delete Job\n 3.Display\n 4.Exit\nEnter your choice : ";
	    cin>>ch;
	    cout<<endl;

	    switch(ch)
	    {
	    case 1:
	    	cout<<"Enter job : ";
	    	cin>>x;
	    	obj.enqueue(x);
	    	cout<<endl;
	    	break;

	    case 2:
	    	obj.dequeue();
			if (!obj.isEmpty()) {
				cout<<"\nRemaining jobs: \n";
	    		obj.display();
			}
	        break;

	    case 3:
		    obj.display();
	        break;

	    case 4:
		    cout<<"\nExiting Program...";
		    break;

	    default:
	    	cout<<"Invalid choice!\n";
	    	break;
        }

	}while(ch!=4);
return 0;
}
