/*
Write C++ program for storing binary number using doubly linked lists. Write functions: a) To compute 1‘s and 2‘s complement b) Add two binary numbers.
 */

#include<iostream>
#include<string.h>
using namespace std;

struct Node {
	Node *next;
	int data;
	Node *prev;
};


class Binary {
private:
	Node *head;
	Node *tail;

public:
	Binary () {
		head = NULL;
		tail = NULL;
	}

	Binary operator+ (Binary);  //operator overloading for sum
	void insertNode(int);
	void create(int);
	void display();
	void ones();
	void twos();
};


//insert at the beginning
void Binary::insertNode(int data) {
	Node *p = new Node;
	p->data = data;

	p->next = head;
	p->prev = NULL;

	//make prev pointer of initial 1st element point to p
	if (head!=NULL)
		head->prev = p;

	head = p;
}


void Binary::create(int b) {
	string s = to_string(b);  //convert to string
	int len = s.length();

	for (int i=0; i<len; i++) {
		int digit = b%10;
		insertNode(digit);
		b/=10;
	}
}


void Binary::display() {
	Node *temp;
	temp = head;

	while (temp->next!=NULL) {
		cout<<temp->data<<"";
		temp = temp->next;
	}

	cout<<temp->data;  //print data in the last node
}


void Binary::ones() {
	Node *temp;
	temp = head;

	while (temp->next!=NULL) {
		if (temp->data == 0) {
			temp->data = 1;
		}
		else {
			temp->data = 0;
		}
		temp = temp->next;
	}

	//for last node
	if (temp->data == 0) {
		temp->data = 1;
	}
	else {
		temp->data = 0;
	}
	temp = temp->next;

	cout<<"One's complement: ";
	display();
	cout<<endl;
}


void Binary::twos() {
	ones();
	int carry = 1;

	Node *temp;
	temp = tail;

	while(temp!=NULL) {
		if (temp->data==0 && carry==1) {
			temp->data = 1;
			carry = 0;
		}
		else if (temp->data==1 && carry==1) {
			temp->data = 0;
			carry = 1;
		}
		
		if (carry==0) {
			break;
		}

		temp = temp->prev;
	}

	// for first node
	if (temp->data==0 && carry==1) {
		temp->data = 1;
		carry = 0;
	}
	else if (temp->data==1 && carry==1) {
		temp->data = 0;
		carry = 0;
	}

	cout<<"Two's complement: ";
	display();
}


int main() {
	Binary b1, b2;
	int bnum;

	cout<<"Enter binary number: ";
	cin>>bnum;
	b1.create(bnum);
	cout<<endl;
	b1.display();
	cout<<endl;
	b1.ones();
	cout<<endl;
	cout<<"Enter binary number: ";
	cin>>bnum;
	b1.create(bnum);
	cout<<endl;
	b1.display();
	cout<<endl;
	b1.twos();
}
