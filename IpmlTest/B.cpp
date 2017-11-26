#include "B.hpp"
#include "B_impl.hpp"

B::B()
{
    pimpl = std::unique_ptr<A_impl>(new B_impl());
}
