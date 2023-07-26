/*
Implement C++ program for expression conversion as infix to postfix and its evaluation using stack based on given conditions:
1. Operands and operator, both must be single character.
2. Input postfix expression must be in a desired format.
3. Only '+', '-', '*' and '/ ' operators are expected.
*/


#include<iostream>
#include <bits/stdc++.h>
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
	void convert(char[]);
	int precedence(char);
	void evaluate(char[]);
	int result(int, int, char);
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


int Stack::precedence(char ch) {
	if ((ch=='*') || (ch=='/'))
		return 2;
	else if ((ch=='+') || (ch=='-'))
		return 1;
	else
		return 0;
}


void Stack::convert(char infix[]) {
	int i = 0;

	string postfix;

	while (infix[i]!='\0') {
		char x = infix[i];

		if (x=='+' || x=='-' || x=='*' || x=='/') {  // case - operator
			while (!isEmpty() && s[top]!='(' && precedence(x)<=precedence(s[top])) {
				postfix += pop();
			}
			push(x);  // save new operator to the stack
		}
		else if (x=='(') {
			push(x);
		}
		else if (x==')') {
			while (s[top]!='(') {  // pop until '(' is encountered
				postfix += s[top];
				pop();
			}
			pop();  // pop the '('
		}
		else {  // case - operand
			postfix += x;
		}
		i++;
	}
	// append remaining operators at the end of postfix exp
	while (!isEmpty()) {
		postfix += s[top];
		pop();
	}
	// print postfix expression
	cout<<"Postfix expression: "<<postfix<<"\n";
	char pf[postfix.length()+1];
	strcpy(pf, postfix.c_str());
	evaluate(pf);
}


int Stack::result(int a, int b, char op) {
	switch (op) {
	// reverse operations to maintain associativity
	case '+': return b+a;
	case '-': return b-a;
	case '*': return b*a;
	case '/': return b/a;
	default: return 0;
	}
}


void Stack::evaluate(char pf[]) {
	int i = 0;
	int val;

	while (pf[i]!='\0') {
		char x = pf[i];
		if (isdigit(x)) {  // case - operand
			push(x-'0');  // subtracting char value of '0' to get desired integers
		}
		else {
			int a = s[top];
			pop();
			int b = s[top];
			pop();
			val = result(a, b, x);

			push(val);
		}
		i++;
	}

	cout<<"Evaluation result = "<<val<<"\n";
}

int main() {
	Stack s1;
	char exp[30];

	cout<<"Enter infix expression: ";
	cin>>exp;

	s1.convert(exp);
}
