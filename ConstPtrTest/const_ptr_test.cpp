#include <iostream>
#include <memory>

using namespace std;

int main(int argc, char const *argv[])
{
    typedef shared_ptr<int> Ptr;
    typedef shared_ptr<const int> ConstPtr; // 指的内容可以被改变
    // typedef const shared_ptr<int> ConstPtr;

    const int *pi;  //指针指向的内存的值不能被改变, pi是一个指针，指向const int类型
    // int const *cpi = new int(1); // 这种写法和上面的是一样

    int* const cpi = new int(1); // const 指针，　
    // cpi = new int(2);

    Ptr p = Ptr(new int(1));
    cout << "Before: " << *p << endl;
    *p = 2;
    cout << "After: " << *p << endl;

    ConstPtr cp = ConstPtr(new int(1));
    cout << "Before: " << *cp << endl;
    // *cp = 2; // error
    cout << "After: " << *cp << endl;

    // cp = ConstPtr(new int(2));


    return 0;
}
