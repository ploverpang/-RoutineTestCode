#ifndef A_IMPL_HPP
#define A_IMPL_HPP

#include <string>

class A_impl{
public:
    A_impl();
    virtual ~A_impl();
    
    virtual void print();
    virtual void override_print();
    
protected:
    std::string m_str;
};

#endif