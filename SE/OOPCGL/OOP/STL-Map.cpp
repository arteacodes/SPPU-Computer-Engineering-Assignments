/*
Write a program in C++ to use map associative container. The keys will be the names of states
and the values will be the populations of the states. When the program runs, the user is
prompted to type the name of a state. The program then looks in the map, using the state
name as an index and returns the population of the state.
 */


// https://github.com/Parth1906/SPPU-2019-Pattern-SE-COMP-Object-Oriented-Programming-Practicals/blob/main/GroupC_Practical7.cpp


#include <iostream>
#include <map>
#include <string>
using namespace std;

class Population {
	typedef map<string, int> maptype;
	maptype popMap;
public:
	void create();
	void display();
	void search();
};

void Population::create() {
	popMap.insert(pair<string, int>("Uttar Pradesh", 233));
	popMap.insert(pair<string, int>("Maharashtra", 125));
	popMap.insert(pair<string, int>("Bihar", 104));
	popMap.insert(pair<string, int>("West Bengal", 91));
	popMap.insert(pair<string, int>("Madhya Pradesh", 73));
	popMap.insert(pair<string, int>("Tamil Nadu", 72));
	popMap.insert(pair<string, int>("Rajasthan", 68));
	popMap.insert(pair<string, int>("Karnataka", 61));
	popMap.insert(pair<string, int>("Gujarat", 60));
	popMap.insert(pair<string, int>("Andhra Pradesh", 49));
}


void Population::display() {
	maptype::iterator itr;
	cout<<"\nLIST OF STATES:\n";
	for (itr = popMap.begin(); itr!=popMap.end(); ++itr)
		cout<<(*itr).first<<endl;
}


void Population::search() {
	cout<<"HELLO\n";
	maptype::iterator itr;
	string state;
	cout<<"\nEnter state: ";
	cin>>state;
	cout<<endl;
	if (popMap.find(state)!=popMap.end())
		cout<<"Population of "<<state<<" is "<<popMap[state]<<" million\n";
	else
		cout<<"State not found!\n";
}



int main() {
	Population map;
	map.create();

	int ch;
	do {
		cout<<"\n 1.Search\n 2.Display\n 3.Exit\nEnter choice: ";
		cin>>ch;

		switch(ch) {
		case 1:
			map.search();
			break;
		case 2:
			map.display();
			break;
		case 3:
			exit(0);
			break;
		default:
			cout<<"Invalid choice!\n";
			break;
		}

	} while(ch!=3);
}
