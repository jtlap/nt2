#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/exceptions.hpp>

void f(bool b)
{
  BOOST_ASSERT_MSG( b
                  , "Some condition was not met."
                  );
}

NT2_TEST_CASE(nt2_test_error)
{
  NT2_TEST_NO_ASSERT(f(true));
  NT2_TEST_NO_ASSERT(f(false));
}
