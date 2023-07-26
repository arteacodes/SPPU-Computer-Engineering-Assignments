/*
Implement all the functions of a dictionary (ADT) using open hashing technique: separate chaining 
using linked list data: set of (key, value) pairs, keys are mapped to values keys must be comparable
and keys must be unique. Standard Operations: Insert (key, value), Find(key), Delete(key)
*/


#include<iostream>
using namespace std;

#define size 10

class HNode
{
    string key;
    string value;
    HNode *next;

    public:
    HNode() {
        key = "";
        value = "";
        next = NULL;
    }

    HNode(string k, string v)
    {
        key = k;
        value = v;
        next = NULL;
    }

    friend class Hash;
};


class Hash
{
    HNode *htable[size];
    public:
    Hash()
    {
        for (int i=0; i<size; i++)
        {
            htable[i] = NULL;
        }
    }

    int hashcode(string);
    void insert(string, string);
    void display();
    void search(string);
    void del(string);
};


// hash method that computes sum of ascii values of string and takes mod
int Hash::hashcode(string key)
{
    int sum = 0;
    for (int i=0; i<key.length(); i++)
    {
        sum = sum + key[i];
    }

    return sum%10;
}


void Hash::insert(string key, string value)
{
    int index = hashcode(key);

    HNode *temp = htable[index];
    HNode *newnode = new HNode(key, value);

    if (temp==NULL)
    {
        htable[index] = newnode;
    }
    else
    {
        HNode* curr = temp;
        while (curr->next!=NULL)
        {
            curr = curr->next;
        }
        curr->next = newnode;
    }
}


void Hash::search(string key)
{
    int index = hashcode(key);
    bool flag = false;

    HNode *curr = htable[index];
    while (curr != NULL)
    {
        if (curr->key == key)
        {
            flag = true;
            break;
        }
        curr = curr->next;
    }

    if (curr == NULL || flag == false)
    {
        cout<<"\nNot found in table!";
    }
    else
    {
        cout<<"\nFound!\nKey: "<<curr->key<<"  Value: "<<curr->value;
    }
}


void Hash::del(string key)
{
    int index = hashcode(key);
    bool flag = false;

    HNode *curr = htable[index];

    if (curr == NULL)
    {
        cout<<"\nError! Not found.";
    }
    else if (curr->key == key)
    {
        HNode *nextnode = curr->next;
        htable[index] = nextnode;
        delete curr;
    }
    else
    {

        HNode *prevnode = NULL;
        while (curr != NULL)
        {
            if (curr->key == key)
            {
                flag = true;
                break;
            }
            prevnode = curr;
            curr = curr->next;
        }

        if (flag)
        {
            prevnode->next = curr->next;
            delete curr;
            cout<<"\nDeleted!";
        }
        else
        {
            cout<<"\nError! Not found.";
        }
    }
}


void Hash::display()
{
    cout<<"\nNo. | Key:Value\n";
    for (int i=0; i<size; i++)
    {
        cout<<i<<" - ";
        HNode *curr = htable[i];
        while (curr != NULL)
        {
            cout<<curr->key<<":"<<curr->value<<"--> ";
            curr = curr->next;
        }
        cout<<endl;
    }
}


int main()
{
    Hash h;
    int ch;
    string key, value;
    char ans = 'y';

    do 
    {
        cout<<"\n1. Insert\n2. Display\n3. Search\n4. Delete\nEnter choice: ";
        cin>>ch;

        switch(ch)
        {
            case 1:
            cout<<"\nEnter key: ";
            cin>>key;
            cout<<"Enter value: ";
            cin>>value;
            h.insert(key, value);
            break;
            
            case 2:
            h.display();
            break;

            case 3:
            cout<<"Enter key to be searched: ";
            cin>>key;
            h.search(key);
            break;

            case 4:
            cout<<"Enter key to be deleted: ";
            cin>>key;
            h.del(key);
            break;

            default:
            cout<<"Invalid!";
            break;
        }

        cout<<"\nContinue? (y/n): ";
        cin>>ans;

    } while (ans=='y');
} 
    