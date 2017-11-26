#ifndef A_HPP
#define A_HPP

#include <iostream>
#include <memory>

class A_impl;

class A
{
public:
    A();
    ~A();
    void print();
    void override_print();
    
protected:
    std::unique_ptr<A_impl> pimpl;
    
};

#endif



