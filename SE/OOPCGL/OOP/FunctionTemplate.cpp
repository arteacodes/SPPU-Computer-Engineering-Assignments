/*
Write a function template selection sort.
Write a program that inputs, sorts and outputs an integer array and a float array.
 */


#include<iostream>
#include<stdlib.h>
using namespace std;

template <typename T>
void selectionSort(T arr[], int n) {

    //accept data
	cout<<"Enter elements: ";
	for (int i=0; i<n; i++) {
		cin>>arr[i];
	}
	cout<<endl;

	// sort data
	int min;
	T temp;
	for (int i=0; i<n-1; i++) {
	    min = i;
	    for (int j=i+1; j<n; j++) {
		    if (arr[j]<arr[min]) {
			    min = j;
		    }
	    }
	    // swap
	    temp = arr[i];
	    arr[i] = arr[min];
	    arr[min] = temp;
	}

	// display data
	cout<<"Sorted array: ";
	for (int i=0; i<n; i++) {
		cout<<arr[i]<<" ";
	}
	cout<<endl;
}


int main() {
	cout<<"Sorting Operation\n";

	int n,ch;

	cout<<"\n1.Sort Integers\n2.Sort Float Numbers\nEnter choice: ";
	cin>>ch;
	cout<<endl;
    cout<<"Enter number of elements: ";
    cin>>n;
    cout<<endl;
    int A[n];
    float B[n];

	switch (ch) {
	case 1:
		selectionSort(A, n);
    	break;
	case 2:
		selectionSort(B, n);
		break;
	default:
		cout<<"Invalid input!"<<endl;
		break;
	}

	return 0;
}