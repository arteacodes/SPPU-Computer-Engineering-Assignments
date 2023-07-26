/*
 Develop a program in C++ to create a database of student’s information system containing the following information:
 Name, Roll number, Class, Division, Date of Birth, Blood group, Contact
address, Telephone number, Driving license no. and other.
Construct the database with suitable member functions. Make use of constructor, default constructor, copy constructor, destructor, static member functions, friend class, this pointer, inline code and dynamic memory allocation operators-new and delete as well as exception handling.
 */

#include<iostream>
#include<string.h>
using namespace std;

class Person {

	string addr;
	string phone;
	friend class Student;  // friend class declared

public:
	Person() {  // default constructor
		addr = "";
	}

	void getPerson() {
		cout<<"Enter phone number: ";
		cin.get();
		getline(cin, phone);
		cout<<"Enter address: ";
		cin.get();
		getline(cin, addr);
		cout<<endl;
	}

	void showPerson() {
		cout<<"Phone No.: "<<phone<<endl;
		cout<<"Address: "<<addr<<endl;
	}
};



class Student {  // friend class defined
private:
	string name;
	int roll;
	string cls;
	char* div;
	string dob;
	char* bgroup;

public:
	static int count;

	Student() {		// default constructor
		name = "";
		roll = 0;
		cls = "";
		div = new char;
		dob = "dd/mm/yy";
		bgroup = new char[3];
	}

	Student(Student &obj2) {  // copy constructor  (class_name, &object_name)
		name = obj2.name;
		roll = obj2.roll;
		cls = obj2.cls;
		div = obj2.div;
		dob = obj2.dob;
		bgroup = obj2.bgroup;
	}

	~Student() {  // destructor
		delete div;
		delete bgroup;
	}

	void getData(Person*);
	void showData(Person*);

	static int getCount() {
		return count;
	}
};

int Student::count;  // define static member


inline void Student::getData(Person* p) {
	cout<<"Enter student name: "; cin>>name;
	cout<<"Enter student roll no.: "; cin>>roll;
	cout<<"Enter student class: "; cin.get(); getline(cin, cls);
	cout<<"Enter student division: "; cin>>div;
	cout<<"Enter student date of birth: "; cin>>dob;
	cout<<"Enter student blood group: "; cin>>bgroup;
	p->getPerson();  // calling member function of Person class
	count++;
}


inline void Student::showData(Person* p) {
	cout<<"Name: "<<name<<endl;
	cout<<"Roll No.: "<<roll<<endl;
	cout<<"Class: "<<cls<<endl;
	cout<<"Division: "<<div<<endl;
	cout<<"Date of Birth: "<<dob<<endl;
	cout<<"Blood Group: "<<bgroup<<endl;
	p->showPerson();  // calling member function of Person class	
}


int main() {
	Student* s1[10];
	Person* p1[10];
	
	int n = 0;
	char ch;

	cout<<"-----------------\nSTUDENT DATABASE\n-----------------"<<endl;

	do {
		s1[n] = new Student;
		p1[n] = new Person;

		s1[n]->getData(p1[n]);
		n++;

		cout<<"Continue adding records? (y/n): ";
		cin>>ch;
		cin.get();
		cout<<endl;

	} while (n<10 && ch=='y');

	cout<<"Student Details:"<<endl;
	for (int i=0; i<n; i++) {
		s1[i]->showData(p1[i]);
		cout<<"--------------------"<<endl;
	}
}
