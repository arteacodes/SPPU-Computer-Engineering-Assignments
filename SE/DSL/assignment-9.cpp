/*
In any language program mostly syntax error occurs due to unbalancing delimiter such as (),{},[]. Write C++ program using stack to check whether given expression is well parenthesized or not.
*/


#include<iostream>
using namespace std;

#define size 30

class Stack {
	char s[size];
	int top;

public:
	Stack() {
		top = -1;
	}

	void push(char);
	char pop();
	bool isEmpty();
	bool isFull();
	bool checkExp(char[]);  // returns true if exp is well parenthesized
};



bool Stack::isEmpty() {
	if (top==-1)
		return true;
	else
		return false;
}


bool Stack::isFull() {
	if (top==size-1)
		return true;
	else
		return false;
}


void Stack::push(char ch) {
	if (!isFull()) {
		top++;
		s[top] = ch;
	}
}


char Stack::pop() {
	if (!isEmpty()) {
		char ch = s[top];
		top--;
		return ch;
	}
	else
		return '\0';
}


bool Stack::checkExp(char str[]) {

	int i = 0;
	char c;

	while(str[i]!='\0') {

		char x = str[i];
		switch (x) {
		case '(': push(x); break;
		case '{': push(x); break;
		case '[': push(x); break;
		case ')':
			c = pop();
			if (c!='(')
				return false;
			break;
		case '}':
			c = pop();
			if (c!='{')
				return false;
			break;
		case ']':
			c = pop();
			if (c!='[')
				return false;
			break;
		}
		i++;
	}
	// check stack empty i.e. all parenthesis matched
	return (isEmpty());
}


int main() {
	Stack s1;
	char exp[30];
	cout<<"Enter an expression: ";
	cin>>exp;

	if (s1.checkExp(exp))
		cout<<"Expression is well parenthesized.\n";
	else
		cout<<"Expression is not well parenthesized.\n";
}
