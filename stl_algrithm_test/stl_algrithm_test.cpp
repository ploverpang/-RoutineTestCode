#include <iostream>
#include <vector>
#include <algorithm>
#include <memory>

using namespace std;

namespace mtk {

constexpr int get_1plus2()
{
    return 1+2;
}

}

class ABC {
public:
    ABC();
    ~ABC();

private:
    
};

ABC::ABC() {
}

ABC::~ABC() {
}

typedef unsigned short ushort;

constexpr int test_const_fun(int i)
{
    return i+1;
}

template <typename T>
struct st_type
{
    T x;
};

typedef st_type<int> STint;
typedef st_type<float> STfloat;

class CC
{
  public:
    CC(){};
    CC(int i){}
    // CC(const CC& cc) = delete;
    virtual int pfunction() = 0;
};

class CC_Derive : public CC
{
  public:
    CC_Derive() {

    }
    int pfunction()
    {
        cout << "pfunction " << endl;
        int a = 1>2 ? 0 : 1;
        return 0;
    }

    CC_Derive(int i)
    {
        cout << "CC_Derive i: " << i << endl;
    }

    CC_Derive& operator=(CC_Derive&& other) {
        
        return *this;
    }


};

void const_print(int *p)
{
    cout << "const print: " << *p << endl;
}

enum class Color
{
    Red,
    Blue,
    Green
};

void test_const_cast()
{
    const int cnum = 1;

    const_print(const_cast<int*>(&cnum));

    #pragma region RegionName
        
    #pragma endregion RegionName

    if (true) {
        
    }
    else {
        
    }
    
    // const int *ref_c = &cnum;
    // int *modify = const_cast<int*>(ref_c);

    // cout << "before modify" << cnum << endl;

    // *modify = 2;

    // cout << "after modify" << cnum << endl;
    return;

}

int main(int argc, char const *argv[])
{
    using namespace mtk;
    cout << "Hello World" << endl;

    Color cl = Color::Red;

    int cl_int = static_cast<int>(Color::Red);

    cout << "cl_int : " << cl_int << endl;
    {
        cout << "brace" << endl;
    }
    auto lmd = [&](int aa) -> int {
       return 0; 
    };

    cout << "lmd: " << lmd(1) << endl;

    #pragma region RegionName
    cout << "Hello Region" << endl;
        
    #pragma endregion RegionName

    STint st;
    st.x = 1;

    cout << "st.x: " << st.x << endl;

    std::vector<int> v{ 3, 1, 4, 1, 9, 5, 9 };

    CC_Derive a;

    CC_Derive c = 1;
    // CC_Derive d = 'c';

    shared_ptr<CC> cp(new CC_Derive());

    cp->pfunction();

    for(auto&& i : v)
    {
        cout << i << endl;
    }

    shared_ptr<int> aaa(new int());


    v.erase(std::remove(std::begin(v), std::end(v), 9), std::end(v));

    cout << "After pop" << endl;
    int len = v.size();
    for (size_t i = 0; i < len; i++)
    {
        cout << v.front() << endl;
        std::pop_heap(std::begin(v), std::end(v));
        v.pop_back();
    }

    cout << "1+2=" << get_1plus2() << endl;

    int i=0;

    cout << "test_const_fun: " << test_const_fun(i) << endl;

    if (std::all_of(std::begin(v), std::end(v), [](int i) {
        cout << "i: " << i << endl;
        return i == 9;
    })) {
        cout << "delete success" << endl;
    }
    else {
        cout << "delete failed" << endl;
    }

    return 0;
}
