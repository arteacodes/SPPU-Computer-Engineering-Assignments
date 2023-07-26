/*
Write C++ program using STL for sorting and searching with user-defined
records such as Person Record (Name, birth date, telephone no)
 */

//https://se-sppu.blogspot.com/2018/10/write-c-program-using-stl-for-sorting.html

#include <iostream>
#include <vector>
#include <algorithm>  // generic STL algorithms
#include <string>
using namespace std;

class Person {
public:
	string name;
	string dob;
	long long phone;

	bool operator<(const Person &p) {
		if (name < p.name)
			return true;
		return false;
	}

	bool operator==(const Person &p) {
		for (char i = name[0]; i!='\0'; i++) {
			for (char j = p.name[0]; j!='\0'; j++) {
				if (i!=j)
					return false;
			}
		}
		return true;
	}

	void accept();
	friend bool compare(Person, Person);

};

bool compare(Person p1, Person p2) {  // comparator function to be passed as 3rd parameter in sort()
	return (p1.name < p2.name);  // returns boolean value and helps sort lexicographically
}


void Person::accept() {
	cout<<"Enter name: ";
	cin>>name;
	cout<<"Enter date of birth (dd/mm/yy): ";
	cin>>dob;
	cout<<"Enter phone number: ";
	cin>>phone;
	cout<<endl;
}


vector<Person>v1;
// function declarations
void show(Person &p);
void insert(vector<Person> &v);
void display(vector<Person> &v);
void search(vector<Person> &v);


void insert(vector<Person> &v) {  // add object as vector element
	Person p1;
	p1.accept();
	v.push_back(p1);
}

void show(Person &p) {
	cout<<"Name:"<<p.name<<"\t";
	cout<<"DOB:"<<p.dob<<"    ";
	cout<<"Phone No.:"<<p.phone<<endl;
}

void display(vector<Person> &v) {
	int i = 1;
	for (auto itr = v.begin(); itr!=v.end(); ++itr) {
		cout<<i<<") ";
		show(*itr);
		i++;
	}
}

void search(vector<Person> &v) {

	Person p1;
	cout<<"Enter name of person to search record: ";
	cin>>p1.name;

	auto p = find(v.begin(), v.end(), p1);
	if (p==v.end())
		cout<<"Record not found"<<endl;
	else {
		int index = p - v.begin();
		cout<<"Found at "<<index<<endl;
	}

}

int main() {
	int ch;

	do {
		cout<<"***Operations Menu***\n";
		cout<<"1.Insert\n2.Search\n3.Sort\n4.Display\n5.Exit\nEnter choice: ";
		cin>>ch;

		switch(ch) {
		case 1:
			insert(v1);
			break;
		case 2:
			search(v1);
			break;
		case 3:
			sort(v1.begin(), v1.end(), compare);
			cout<<"Sorted by name: "<<endl;
			display(v1);
			break;
		case 4:
			display(v1);
			break;
		case 5:
			exit(0);
			break;
		default:
			cout<<"Invalid input!"<<endl;
		}
	} while (ch>0 && ch<6);


}
