// Usually defined on command line
#define NT2_ASSERTS_AS_EXCEPTIONS
#define BOOST_ENABLE_ASSERT_HANDLER

#include <boost/assert.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/exceptions.hpp>

void f(bool b)
{
  BOOST_ASSERT_MSG( b
                  , "Some condition was not met."
                  );
}

NT2_TEST_CASE(nt2_test_no_assert)
{
  NT2_TEST_NO_ASSERT(f(true));
  NT2_TEST_NO_ASSERT(f(false));
}
