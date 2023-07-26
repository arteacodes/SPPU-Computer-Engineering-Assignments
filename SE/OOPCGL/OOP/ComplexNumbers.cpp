/*
Implement a class Complex which represents the Complex Number data type. Implement the following
1. Constructor (including a default constructor which creates the complex number 0+0i).
2. Overload operator+ to add two complex numbers.
3. Overload operator* to multiply two complex numbers.
4. Overload operators << and >> to print and read Complex Numbers.
 */

#include<iostream>
using namespace std;

class Complex {
    private:
        float real, img;

    public:
        Complex() {  //default constructor
            this->real = 0;
            this->img = 0;
        }

        Complex(float r, float i) {  //parametrized constructor
            this->real = r;
            this->img = i;
        }


        Complex operator+ (Complex);
        Complex operator* (Complex);

        friend ostream &operator<< (ostream &out, Complex &obj) {
            if (obj.img>0)
                out<<obj.real<<" + "<<obj.img<<"i";
            else
                out<<obj.real<<" - "<<obj.img<<"i";
            return(out);
        }

        friend istream &operator>> (istream &in, Complex &obj) {
            in>>obj.real;
            in>>obj.img;
            return(in);
        }
};


Complex Complex::operator+ (Complex c) {
    Complex temp;
    temp.real = real + c.real;
    temp.img = img + c.img;
    return(temp);
}

Complex Complex::operator* (Complex c) {
    Complex temp;
    temp.real = real*c.real - img*c.img;
    temp.img = real*c.img + img*c.real;
    return(temp);
}



int main() {

    Complex c1, c2, c3, c4;

    cout<<"Enter real & imaginary part of 1st number: ";
    cin>>c1;

    cout<<"Enter real & imaginary part of 2nd number: ";
    cin>>c2;

    c3 = c1+c2;
    cout<<"Addition = ";
    cout<<c3<<endl;

    c4 = c1*c2;
    cout<<"Multiplication = ";
    cout<<c4;
}
