/*
 * filehandling.cpp
 *
 *  Created on: Nov 4, 2022
 *      Author: se
 */


#include<iostream>
#include<fstream>
using namespace std;

class Student {
private:
    string name;
    int rollNo;

public:
    void accept() {
        cout<<"Enter name: "; cin>>name;
        cout<<"Enter roll no.: "; cin>>rollNo;
        fstream file;  // file object created
        file.open("student_data.txt", ios::out | ios::app);  // open file in write mode
        file<<"Name: ";
        file<<name;
        file<<" | Roll No.: ";
        file<<rollNo<<"\n";
        file.close();
    }


    static void display() {
        fstream file;
        string line;
        file.open("student_data.txt", ios::in);
        while (!file.eof()) {
            getline(file, line);
            cout<<line;
            cout<<endl;
        }
        file.close();
    }
};

int main() {
    int n;
    cout<<"Enter no. of records: ";
    cin>>n;

    Student s[n];

    for (int i=0; i<n; i++) {
        s[i].accept();
    }

    cout<<"********************"<<endl;
    cout<<"Records in File:"<<endl;
    Student::display();
}
