#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class lambda_test
{
public:
    lambda_test ():a(123){};
    virtual ~lambda_test () {};
    void print()
    {
        cout << "hello lambda" << endl;
    }
    void lambda_print(){
        auto fun = [this] {
            this->print();
            cout << "member valiable a: " << this->a << endl;
        };
        fun();
    }
private:
    int a;
    /* data */
};

int main(int argc, char *argv[])
{
    int ret = 123;
    std::string str("world");
    auto fun = [&](std::string &str) {
        printf("Hello %s \n", str.c_str());
        cout << "before add : " << ret << endl;
        ret ++;
    };
    fun(str);
    cout << "after add: " << ret << endl;

    int x = 1;
    int y = 2;

    cout << "OUTSIDE:" << endl;
    cout << "x: " << x << "\tx add: " << &x << endl;
    cout << "y: " << y << "\ty add: " << &y << endl;
    auto fun2 = [=,&y]() {
        cout << "x: " << x << "\tx add: " << &x << endl;
        cout << "y: " << y << "\ty add: " << &y << endl;
    };
    fun2();

    lambda_test t;
    t.lambda_print();

    return 0;
}
