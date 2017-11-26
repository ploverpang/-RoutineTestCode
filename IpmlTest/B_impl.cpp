#include "B.hpp"
#include "B_impl.hpp"

#include <iostream>

B_impl::B_impl():
A_impl()
{
}

B_impl::~B_impl()
{

}

void B_impl::override_print()
{
    std::cout << "override: " << m_str << std::endl;
}


