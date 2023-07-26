/*
The ticket booking system of Cinemax theater has to be implemented using C++ program. There are 10 rows and 7 seats in each row. Doubly circular linked list has to be maintained to keep track of free seats at rows. Assume some random booking to start with. Use array to store pointers (Head pointer) to each row. On demand:
  a) The list of available seats is to be displayed
  b) The seats are to be booked
  c) The booking can be cancelled
*/

#include <iostream>
using namespace std;

struct Node {
    Node* next;
    Node* prev;
    int seat;
    int status;
};

class Cinemax {
public:
    Node *head, *tail, *temp;

    Cinemax() { // @suppress("Class members should be properly initialized")
        head=NULL;
    }

    void create_arr();
    void display();
    void book();
    void cancel();
};


void Cinemax::create_arr() {
    temp = new Node;
    temp->seat = 1;
    temp->status = 0;
    tail = head = temp;

    for (int i=2; i<=70; i++) {
        Node *p;
        p = new Node;
        p->seat = i;
        p->status = 0;
        tail->next = p;
        p->prev = tail;
        tail = p;
        tail->next = head;
        head->prev = tail;
    }
}


void Cinemax::display() {
    Node* temp;
    temp=head;
    int count=0;

    cout<<"\n---------------------------------------------------------------\n";
    cout.width(40);
    cout<<"Screen this way\n";
    cout<<"---------------------------------------------------------------\n";

    while(temp->next!=head) {
        if(temp->seat/10==0)
            cout<<"0"<<temp->seat<<": ";
        else
            cout<<temp->seat<<": ";

        if(temp->status==0)
            cout<<"|__| ";
        else
            cout<<"|**| ";
        count++;
        if(count%7==0) {
            cout<<endl;
        }
        temp=temp->next;
    }

    // to print last seat
    cout<<temp->seat<<": ";
    if(temp->status==0)
        cout<<"|__| ";
    else
        cout<<"|**| ";
    cout<<endl;
}



void Cinemax::book() {
    int x;
    label1:
    cout<<"\nEnter seat number to be booked: ";
    cin>>x;
    if(x<1||x>70) {
        cout<<"Enter correct seat number! (1-70)";
        goto label1;
    }

    Node *temp;
    temp=new Node;
    temp=head;

    while(temp->seat!=x) {
        temp=temp->next;
    }

    if(temp->status==1)
        cout<<"Seat already booked!\n";
    else {
    temp->status=1;
    cout<<"Seat no. "<<x<<" booked!\n";
    }
}



void Cinemax::cancel() {
    int x;
    label2:
    cout<<"\nEnter seat number to cancel booking: ";
    cin>>x;
    if(x<1||x>70) {
        cout<<"Enter correct seat number! (1-70)\n";
        goto label2;
    }

    Node *temp;
    temp=new Node;
    temp=head;
    while(temp->seat!=x) {
        temp=temp->next;
    }

    if(temp->status==0) {
        cout<<"Cannot cancel unbooked seat!\n";
    }
    else {
        temp->status=0;
        cout<<"Booking cancelled!\n";
    }
}


int main() {
    Cinemax obj;
    obj.create_arr();
    int ch;
    char ans = 'y';
    while(ans =='y') {
        obj.display();
        cout<<"\n\nCINEMAX MOVIE THEATRE\n";
        cout<<"1.Display Seats\n2.Book Seat\n3.Cancel Seat\nEnter Choice: ";
        cin>>ch;
        cout<<endl;

        switch(ch) {
        case 1:obj.display();
        break;
        case 2: obj.book();
        break;
        case 3:obj.cancel();
        break;
        default: cout<<"Invalid input!\n";
        }

        cout<<"\nContinue performing operations? (y/n): ";
        cin>>ans;
    }
}
