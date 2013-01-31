#include "some_exception.hpp"
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/error/exception.hpp>
#include <nt2/sdk/unit/tests/exceptions.hpp>

void f(bool b)
{
  if(b) throw some_exception();
}

NT2_TEST_CASE(nt2_test_error)
{
  NT2_TEST_NO_THROW(f(true));
  NT2_TEST_NO_THROW(f(false));
}
