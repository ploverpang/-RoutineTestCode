#include "A.hpp"
#include "A_impl.hpp"

A::A(){}

A::~A()
{

}


void A::print()
{
    pimpl->print();
}

void A::override_print()
{
    pimpl->override_print();
}