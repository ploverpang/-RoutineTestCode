#include <iostream>
#include <stdio.h>

using namespace std;

class A
{
public:
    A(int _a):a(_a){}
private:
    int a;
public:
  virtual void print() {};

};

class B: public A
{
public:
    //B(int _a, int _b):a(_a), b(_b){}

    B(int _a, int _b) : A(_a)
    {
        b = _b;
    }
private:
    int a;
    int b;
public:
    void print()
    {
        printf("a = %d, b= %d\n", a, b);
    }

};


void printClass(A &a)
{
    a.print();
}

int main()
{
    B b(1,2);
    printClass(b);

}


