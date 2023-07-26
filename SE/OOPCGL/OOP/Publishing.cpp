/*
Create  a  class  publication that  stores the  title  (a string)  and price  (type  float) of  publications.
From  this  class  derive  two  classes:  book  which  adds  a  page  count  (type  int)  and  tape  which adds
a playing time in minutes (type float). Write  a  program  that  instantiates  the  book  and  tape  class,
allows  user  to  enter  data  and displays the data members. If an exception is caught,
replace all the data member values with zero values.
 */


#include<iostream>
using namespace std;

class Publication {
public:
	string title;
	float price;

	void read() {
		cout<<"Enter Title: ";
		cin>>title;
		cout<<"Enter Price: ";
		cin>>price;
	}

	void display() {
		cout<<"Title: "<<title;
		cout<<"  |  Price: Rs. "<<price;
	}
};


class Book : public Publication {
public:
	int pageCount;

    void getBook() {
        Publication::read();
		try {
			cout<<"Enter Page Count: ";
			cin>>pageCount;
            cout<<endl;
			if ((pageCount<=0) || (isalpha(pageCount)==true))
				throw pageCount;
		}
		catch(...) {    // (...) catches all kinds of exceptions
			cout<<"\nInvalid Input"<<endl;
			pageCount = 0;
		}
    }

	void show() {
		Publication::display();
		cout<<"  |  Page Count: "<<pageCount<<endl;
	}
};


class Tape : public Publication {
public:
	float playTime;

    void getTape() {
        Publication::read();
		try {
			cout<<"Enter Playing Time (minutes): ";
			cin>>playTime;
            cout<<endl;
			if ((playTime<=0) || (isalpha(playTime)==true))
				throw playTime;
		}
		catch(...) {    // (...) catches all kinds of exceptions
			cout<<"\nInvalid Input"<<endl;
			playTime = 0;
		}
    }

	void show() {
		Publication::display();
		cout<<"  |  Playing Time: "<<playTime<<" mins"<<endl;
	}
};



int main() {

	int bnum, tnum;

	cout<<"Enter number of books: ";
	cin>>bnum;

	//array of objects of book class
	Book b1[bnum];

    for (int x=0; x<bnum; x++) {
		cout<<"Book "<<x+1<<": \n";
        b1[x].getBook();
    }

	for (int x=0; x<bnum; x++) {   
		cout<<"Book "<<x+1<<": \n";
		b1[x].show();
	}


	cout<<"\nEnter number of tapes: ";
	cin>>tnum;

	//array of objects of tape class
	Tape t1[tnum];

     for (int y=0; y<tnum; y++) {
        cout<<"Tape "<<y+1<<": \n";
        t1[y].getTape();
    }

	for (int y=0; y<tnum; y++) {
		cout<<"Tape "<<y+1<<": \n";
		t1[y].show();
	}
}