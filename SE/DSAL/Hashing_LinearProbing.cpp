/*
Consider telephone book database of N clients. Make use of a hash table implementation to quickly look up client’s telephone number. Make use of two collision handling techniques and compare them using number of comparisons required to find a set of telephone numbers.
(Note: Use linear probing with replacement and without replacement)
*/

#include<iostream>
#include<iomanip>
using namespace std;

#define size 10

class Item
{
    long int ph;
    string name;
    
    public:
    Item()
    {
        ph = -1;
        name = "-";
    };
    friend class Hash;
};


class Hash
{
    Item hashtable[size];
    
    public:
    int hashcode(long int key);
    void insert1(string, long int);  //without replacement
    void insert2(string, long int);  //with replacement
    void display();
    void search(long int phone);
    void del(long int phone);
};


// hash method that generates hash code 
int Hash::hashcode(long int key)
{
    return key%size;
}


void Hash::insert1(string name, long int ph)  // without replacement
{   
    Item it;
    it.name = name;
    it.ph = ph;
    int index;
    
    // get index by passing phone no. as key
    index = hashcode(it.ph);
    
    if (hashtable[index].ph == -1)  // if row is empty
    {  
        hashtable[index] = it;  // insert object
    }
    else   // if not empty go to next empty row
    {
        while (hashtable[index].ph != -1)
        {
            index = (index+1)%size;
        }
        hashtable[index] = it;
    }
}


void Hash::insert2(string name, long int ph)  // with replacement
{
    Item it, temp;
    it.name = name;
    it.ph = ph;
    int index;
    
    index = hashcode(it.ph);
    
    if (hashtable[index].ph == -1)  // if row is empty
    {  
       hashtable[index] = it;  // insert object
    }
    else  
    {
        temp = hashtable[index];  // store current row in temp
        if (hashcode(temp.ph) == index)  // if temp is at correct index
        {
            // insert new entry at next free spot
            while (hashtable[index].ph != -1)
            {
                index = (index+1)%size;
            }
            hashtable[index] = it;
        }
        else  // if temp is not at correct index
        {
            // insert new entry at that position
            hashtable[index] = it;
            // find next free spot for temp
            while (hashtable[index].ph != -1)
            {
                index = (index+1)%size;
            }
            hashtable[index] = temp;
        }
    }
}


void Hash::search(long int phone)
{
    int index;
    int a = 0;
    int count = 1;
    bool found = false;
    
    index = hashcode(phone);
    
    while(a!=9)
    {
        if(hashtable[index].ph == phone) {
            cout<<"Found at index="<<index<<endl;
            found = true;
            break;
        }
        else {
            index = (index+1)%size;
        }
        a++;
        count++;
    }
    if (found == false)
    {
        cout<<"Not found!"<<endl;
    }
    cout<<"No. of comparisons = "<<count<<endl;
}


void Hash::del(long int phone)
{
    bool found = false;

    for(int i=0; i<size; i++)
    {
        if (hashtable[i].ph == phone) {
            cout<<"Deleted!"<<endl;
            found = true;
            hashtable[i].ph = -1;
        }
    }
    if(found == false)
    {
        cout<<"Not found!"<<endl;
    }
}


void Hash::display()
{
    cout<<"\n| No. |"<<setw(12)<<"| Name |"<<setw(20)<<"| Phone No. |\n";
    for (int i=0; i<size; i++)
    {
        cout<<setw(3)<<i<<setw(15)<<hashtable[i].name<<setw(20)<<hashtable[i].ph<<endl;
    }
}


int main()
{
    Hash h1, h2;
    int ch;
    char ans = 'y';
    string name;
    long int phone;
    
    do
    {
        cout<<"\n\n*** Telephone Directory ***\n1. Insert\n2. Display\n3. Search\n4. Delete";
        
        cout<<"\nEnter choice: ";
        cin>>ch;
        
        switch (ch)
        {
            case 1:
            cout<<"Enter Name: ";
            cin>>name;
            cout<<"Enter Phone Number: ";
            cin>>phone;
            h1.insert1(name, phone);
            h2.insert2(name, phone);
            cout<<"Inserted!"<<endl;
            break;
            
            case 2:
            h1.display();
            cout<<endl;
            h2.display();
            break;
            
            case 3:
            cout<<"Enter phone no. to search for: "<<endl;
            cin>>phone;
            h1.search(phone);
            h2.search(phone);
            break;
            
            case 4:
            cout<<"Enter phone no. to be deleted : "<<endl;
            cin>>phone;
            h1.del(phone);
            h2.del(phone);
            break;
        }

        cout<<"\nContinue? (y/n): ";
        cin>>ans;
        
    } while (ans == 'y' || ans == 'Y');
}