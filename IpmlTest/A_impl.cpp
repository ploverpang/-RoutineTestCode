#include "A_impl.hpp"
#include <iostream>

A_impl::A_impl():m_str("A_impl")
{

}

A_impl::~A_impl()
{

}

void A_impl::print()
{
    std::cout << m_str << std::endl;
}

void A_impl::override_print()
{
    std::cout << m_str << std::endl;
}





