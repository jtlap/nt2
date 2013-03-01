#include "some_exception.hpp"
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/exceptions.hpp>

void f()
{
  throw some_exception();
}

NT2_TEST_CASE(nt2_test_error)
{
  NT2_TEST_THROW(f(), some_exception);
}
