#include <iostream>
#include <tuple>
#include <vector>
#include <functional>

using namespace std;

struct A {
    A() = default;
    tuple<vector<int>, vector<float>> foo()
    {
        // return make_tuple(m_int, m_float);
        return tie(m_int, m_float);
    }
    // tuple<vector<int> &, vector<float> &> foo()
    // {
    //     return make_tuple(ref(m_int), ref(m_float));
    // }
    vector<int> m_int;
    vector<float> m_float;
    void gen_data()
    {
        m_int = {1, 2, 3, 4};
        m_float = {1.f, 2.f, 3.f, 4.f};
    }
    static constexpr float m_cf = 1.0;

};

int main(int, char**) {
   std::cout << "Hello, world!\n";
   A a;
   a.gen_data();
   vector<int> vint;
   vector<float> vfloat;
//    tie(vint, vfloat) = a.foo();
   auto t = a.foo();
   vint = get<0>(t);
   vfloat = get<1>(t);

   for (auto& i : vint) {
       cout << "i: " << i << endl;
   }
   for (auto& f : vfloat) {
       cout << "f: " << f << endl;
   }

   cout << A::m_cf << endl;
}