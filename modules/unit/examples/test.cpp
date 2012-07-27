#include <iostream>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/basic.hpp>

NT2_TEST_CASE(nt2_test)
{
  NT2_TEST( true );
  NT2_TEST( sizeof(float) >= sizeof(char) );
  NT2_TEST( false );
}
