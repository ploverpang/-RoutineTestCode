#ifndef B_IMPL_HPP
#define B_IMPL_HPP

#include "A_impl.hpp"

class B_impl : public A_impl {
public:
    B_impl();
    ~B_impl();
    
    void override_print();
    
};

#endif