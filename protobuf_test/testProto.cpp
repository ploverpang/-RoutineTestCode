#include <iostream>
#include "address.pb.h"
#include <fstream>

using namespace std;

int main()
{
    tutorial::AddressBook address;
    tutorial::Person person;
    person.set_name("PangBo");
    person.set_age(28);
    
    ofstream output("bitfile", ios_base::out | ios_base::binary);
    person.SerializeToOstream(&output);

    return 0;
    
}
