#include <iostream>
#include <fstream>
#include "address.pb.h"

using namespace std;

int main()
{
    tutorial::Person person;
    ifstream ifs("bitfile", ios_base::binary);
    person.ParseFromIstream(&ifs);
    
    cout << person.name() << endl;
    cout << person.age() << endl;
    return 0;
    
}
