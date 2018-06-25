#include <iostream>
#include <vector>
#include <memory>

using namespace std;

class A
{
    public:
    virtual ~A() = default;
    virtual void print()
    {
        cout << "a" << endl;
    }
};

class B : public A
{
  public:
    virtual void print()
    {
        cout << "b" << endl;
    }
    void bprint()
    {
        cout << "only on b" << endl;
    }

};

typedef std::shared_ptr<A> APtr;
typedef std::shared_ptr<B> BPtr;

int main(int argc, char const *argv[])
{
    vector<APtr> vec_a;
    APtr a(new A() );
    BPtr b(new B() );
    APtr c = dynamic_pointer_cast<A>(b);

    BPtr d = dynamic_pointer_cast<B>(a);
    if(not d)
    {
        cout << "downcast failed" << endl;
    }

    vec_a.push_back(a);
    vec_a.push_back(b);
    vec_a.push_back(c);

    for(auto &t : vec_a)
    {
        t->print();
    }
    
    return 0;
}
