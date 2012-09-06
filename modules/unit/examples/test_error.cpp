#include <iostream>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/basic.hpp>

NT2_TEST_CASE(nt2_test_error)
{
  NT2_TEST_ERROR( This is a real serious failure );
}
