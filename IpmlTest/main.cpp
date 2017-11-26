#include <iostream>

#include "A.hpp"
#include "B.hpp"

int main(int argc, char **argv) {
    
    std::shared_ptr<A> b = std::shared_ptr<A>(new B());
    b->print();
    b->override_print();
}
