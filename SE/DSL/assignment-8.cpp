/*
Write C++ program for storing appointment schedule for day. Appointments are booked randomly using linked list. Set start and end time and min and max duration for visit slot. Write functions for: a) Display free slots b) Book appointment c) Cancel appointment (check validity, time bounds, availability) d) Sort list based on time e) Sort list based on time using pointer manipulation
*/

#include<iostream>
using namespace std;

struct SLL_Node	// Node Structure of each Appointment
{
    int start;
    int end;
    int min;
    int max;
    int flag;
    struct SLL_Node *next;
}*head;


class App_Shedule
{
    int size;
  public:
	void create();

	void display();

	void book_App();

	void cancel_App();

	void sort_App();

}A1;


int main()
{
   int ch;
   char ans;

   do
   {
      cout<<"\n\n MENU ";
      cout<<"\n 1. Create Appointment Schedule";
      cout<<"\n 2. Display Free Slots";
      cout<<"\n 3. Book an Appointment";
      cout<<"\n 4. Cancel an Appointment";
      cout<<"\n 5. Sort Appointment Slots";


      cout<<"\nEnter your choice: ";
      cin>>ch;

      switch(ch)
      {
         case 1: A1.create();
         	 break;

         case 2: A1.display();
         	 break;

         case 3: A1.book_App();
         	 break;

         case 4: A1.cancel_App();
         	 break;

         case 5: A1.sort_App();
         	 break;

         default: cout<<"\nWrong choice!!!";

      }

      cout<<"\nDo you want to continue? (y/n) : ";
      cin>>ans;
   }while(ans == 'y');

}


void App_Shedule :: create()           //Function Definition to create Appointment Schedule
{
    int i;
    struct SLL_Node *temp, *last;

    head = NULL;

    cout<<"\nHow many Appointment Slots: ";
    cin>>size;

    for(i=0; i<size; i++)
    {
       cout<<"Slot "<<i+1<<":";
       temp = new(struct SLL_Node);         // Step 1: Dynamic Memory Allocation

       cout<<"\nEnter Start Time: ";   // Step 2: Assign Data & Address
       cin>>temp->start;
       cout<<"Enter End Time: ";
       cin>>temp->end;
       cout<<"Enter Minimum Duration: ";
       cin>>temp->min;
       cout<<"Enter Maximum Duration: ";
       cin>>temp->max;
       cout<<endl;
       temp->flag = 0;
       temp->next = NULL;

       if(head == NULL)
       {
          head = temp;
          last = head;
       }
       else
       {
          last->next = temp;
          last = last->next;
       }

    }
}


void App_Shedule :: display()          //Function Definition to Display Appointment Schedule
{
   int cnt = 1;
   struct SLL_Node *temp;

   cout<<"\n****Appointment Schdule****";
   cout<<"\nSrno.\tStart\tEnd\tMin_Dur\tMax_Dur\tStatus";

   temp = head;
   while(temp != NULL)
   {
      cout<<"\n"<<cnt<<"\t";
      cout<<temp->start<<"\t";
      cout<<temp->end<<"\t";
      cout<<temp->min<<"\t";
      cout<<temp->max<<"\t";

      if(temp->flag)
         cout<<" Booked \n";
      else
         cout<<"  Free  \n";

      temp = temp->next;
      cnt++;
   }
}


void App_Shedule :: book_App()              //Function Definition to Book Appointment
{
    int start;
    struct SLL_Node *temp;

    cout<<"\nPlease enter Appointment time: ";
    cin>>start;

   temp = head;

   while(temp != NULL)
   {
      if(start == temp->start)
      {
         if(temp->flag == 0)
         {
            cout<<"\nAppointment Slot is Booked!!!";
            temp->flag = 1;
         }
         else
            cout<<"\nAppointment Slot is not Available!!!";
      }

      temp = temp->next;
   }

}



void App_Shedule :: cancel_App()            //Function Definition to Cancel Appointment
{
    int start;
    struct SLL_Node *temp;

    cout<<"\nPlease enter Appointment time to Cancel: ";
    cin>>start;

   temp = head;

   while(temp != NULL)
   {
      if(start == temp->start)
      {
         if(temp->flag == 1)
         {
            cout<<"\nYour Appointment Slot is Canceled!!!";
            temp->flag = 0;
         }
         else
            cout<<"\nYour Appointment was not Booked!!!";
      }

      temp = temp->next;
   }
}


void App_Shedule :: sort_App()              //Function Definition to Sort Appointments
{
   int i,val;
   struct SLL_Node *temp;


   for(i=0; i < size-1; i++)
   {
       temp = head;
       while(temp->next != NULL)
       {
          if(temp->start > temp->next->start)
          {
              val = temp->start;
	      temp->start = temp->next->start;
	      temp->next->start = val;

              val = temp->end;
	      temp->end = temp->next->end;
	      temp->next->end = val;

              val = temp->min;
	      temp->min = temp->next->min;
	      temp->next->min = val;

              val = temp->max;
	      temp->max = temp->next->max;
	      temp->next->max = val;

          }
          temp = temp->next;
       }
   }

   cout<<"\nThe Appointments got Sorted!!!";

}
