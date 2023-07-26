/*
Department maintains a Student information. The file contains roll number, name, division and address. Allow user to add, delete information of Student. Display information of particular Student. If record of Student does not exist an appropriate message is displayed. If it is,
then the system displays the Student details. Use sequential file to main the data.
*/

#include <iostream>
#include <string.h>
#include <fstream>

using namespace std;


class Student
{
    int roll;
    char name[20], div;
    string address;

public:
    Student()
    {
        roll=0;
        div=' ';
        strcpy(name,"");
        address = "";
    }

    void input();
    void display();

    int getroll()
    {
        return roll;
    }

};

void Student::input()
{
    cout<<"\n---------------------Enter Student Details-------------------";
    cout<<"\n| Enter Student Roll No.: ";
    cin>>roll;


    cout<<"\n| Enter Student Name: ";
    cin>>name;


    cout<<"\n| Enter Student Division: ";
    cin>>div;


    cout<<"\n| Enter Student address: ";
    getline(cin>>ws, address);
}


void Student::display()
{
    cout<<"      "<<roll<<"     "<<name<<"  "<<div<<"  "<<address<<endl;
}


class SeqFile
{
    fstream file;
    Student obj;

public:
    void create();
    void add();
    void search();
    void del();
    void print();
};

void SeqFile::create()
{
    char ch='y';
    file.open("student_data.txt", ios::out|ios::binary);
    while(ch=='y'||ch=='Y')
    {
        obj.input();
        file.write((char*)&obj, sizeof(obj));
        cout<<"\nWant to enter more entries? (y/n): ";
        cin>>ch;
    }
    file.close();

}

void SeqFile::add()
{
    char ch='y';
    file.open("student_data.txt", ios::app|ios::out|ios::binary);
    while(ch=='y'||ch=='Y')
    {
        obj.input();
        file.write((char*)&obj, sizeof(obj));
        cout<<"\nWant to enter more entries? (y/n):";
        cin>>ch;
    }
    file.close();

}

void SeqFile::print()
{
    file.open("student_data.txt", ios::in|ios::binary);
    if(!file)
    {
        cout<<"File Not Found!";
    }
    else
    {
        cout<<"| Roll No. | Name | Div | Address |\n";
        file.read((char*)&obj,sizeof(obj));
        while(!file.eof())
        {
            obj.display();
            file.read((char*)&obj,sizeof(obj));
        }
        }
        file.close();
}

void SeqFile::search()
{
 int n,fl=0;
 cout<<"Enter roll no. to be searched :";
 cin>>n;
 file.open("student_data.txt",ios::in|ios::binary);
 if(!file)
 {
     cout<<"File Not Found!";
     exit(0);

 }
 else
 {
     file.read((char*)&obj,sizeof(obj));
     while(!file.eof())
     {
         if(n==obj.getroll())
         {
             obj.display();
             fl=1;
             break;
         }
         else
            file.read((char*)&obj,sizeof(obj));
    }
    
    if(fl==0)
    {
        cout<<"Record Not Found!";
    }


 }
}

int main()
{
    Student obj;
    SeqFile sobj;
    int ch;
    char ans = 'y';

    do
    {
        cout<<"\n1. Write\n2. Append\n3. Read\n4. Search\nEnter choice: ";
        cin>>ch;
        
        switch(ch)
        {
            case 1:
            sobj.create();
            break;

            case 2:
            sobj.add();
            break;

            case 3:
            sobj.print();
            break;

            case 4:
            sobj.search();
            break;

            default:
            cout<<"\nInvalid choice!";
            break;
        }

        cout<<"\nContinue? (y/n): ";
        cin>>ans;
    } while(ans=='y');

    return 0;
}