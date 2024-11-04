#include <iostream>
using namespace std;

int fibonacci_recursive(int num) {
    if (num == 0) {
        return 0;
    }
    if (num == 1) {
        return 1;
    }
    
    return fibonacci_recursive(num-1) + fibonacci_recursive(num-2);
}

// to print recursive result
void print(int num) {
    for(int i=0; i<num; i++) {
        cout<<fibonacci_recursive(i)<<" ";
    }
}

void fibonacci_iterative(int num) {
    int a = 0;
    int b = 1;
    int c;
    for (int i=0; i<num; i++) {
        cout<<a<<" ";
        c = a + b;
        a = b;
        b = c;
    }
}

int main() {
    int choice;
    int result;

    while(true) {
        int num;
        cout<<"\n\nEnter the no. of fibonacci digits to print: ";
        cin>>num;

        cout<<"\n1. Recursive\n2. Iterative\n3. Exit";
        cout<<"\nEnter your choice: ";
        cin>>choice;

        switch(choice) {
            case 1: 
                print(num);
                break;
            case 2:
                fibonacci_iterative(num);
                break;
            case 3: 
                exit(0);
                break;
        }
    }
}
