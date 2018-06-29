#include <iostream>
#include <map>
#include <cassert>

using namespace std;

int main(int, char**) {
    map<int, int> m;

    for (size_t i = 0; i < 5; i++) {
        m[i] = i;
    }

    cout << "map size: " << m.size() << endl;

    if(m.count(0))
    {
       cout << "exist"  << endl;
    }
    else {
        cout << "not exist" << endl;
    }

    auto it = m.find(0);
    m.erase(it);

    if(m.count(0))
    {
       cout << "exist"  << endl;
    }
    else {
        cout << "not exist" << endl;
    }
    
    
    cout << "after erase 0, it is " << it->second << endl;

    for(auto mit = m.begin(); mit != m.end(); ++mit)
    {
        if(not (mit->second % 2))
        {
            m.erase(mit);
        }
        else {
            
        }
        cout << "idx: " << mit->first << " ; num: " << mit->second << endl;
    }

    // for(auto mit = m.begin(); mit != m.end(); ++mit)
    // {
    //     cout << "idx: " << mit->first << " ; num: " << mit->second << endl;
    //     assert(mit->second %2);
    // }

    return 0;
}
