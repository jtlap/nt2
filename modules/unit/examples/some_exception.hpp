#ifndef SOME_EXCEPTION_HPP_INCLUDED
#define SOME_EXCEPTION_HPP_INCLUDED

#include <nt2/sdk/error/exception.hpp>

struct some_exception : nt2::exception
{
  some_exception() : nt2::exception("some exception was thrown") {}
};

#endif
