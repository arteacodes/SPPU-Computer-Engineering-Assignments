#include <iostream>
using namespace std;

// time complexity = best case O(1) when num is 0/1, worst case O(2^n) because each function call results in two more recursive calls.
// space complexity = best case O(1) when num is 0/1, worst case O(n) as the recursive stack can go as deep as num in the worst case.
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

// time complexity = best, average and worst case O(n) as it iterates once from 0 to num, performing a constant amount of work in each iteration.
// space complexity = best, average and worst case O(1) as only a few integer variables (a, b, and c) are used, independent of num.
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
