/*
Implement the Heap  sort algorithm using Heap  data structure with modularity of programming language.
*/

#include<iostream>
using namespace std;

class Heap 
{
    public:
    int arr[25];
    
    
    int n;

    Heap ()
    {
        cout<<"Enter no. of values: ";
        cin>>n;
        for (int i=0; i<n; i++){
            arr[i] = 0;
        }
        cout<<endl;
    }

    void read()
    {
        for (int i=0; i<n; i++){
            int a;
            cout<<"Enter data: ";
            cin>>a;
            arr[i] = a;
        }
    }

    // min heap for ascending order
    void heapify(int arr[], int n, int root)
    {
        int min = root;
        int l = (2*min) +1;
        int r = (2*min) +2;

        if(l<n && arr[l]<arr[min]){
            min = l;
        }
        if(r<n && arr[r]<arr[min]){
            min = r;
        }
        if(min != root){
            int temp = arr[root];
            arr[root] = arr[min];
            arr[min] = temp;
            heapify(arr,n,min);
        }
    }

    void heapsort()
    {
        for(int i=(n/2)-1; i>=0; i--)
        {
            heapify(arr, n,i);
        }

        cout<<"\nSorted values: ";
        for(int i=n-1; i>=0; i--)
        {
            cout<<arr[0]<<" ";
            int temp=arr[0];
			arr[0]=arr[i];
			arr[i]=temp;
			heapify(arr,i,0);  
        }
    }
};


int main()
{
	Heap h;
	h.read();
	h.heapsort();
	return 0;
}