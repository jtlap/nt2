// Usually defined on command line
#define NT2_ASSERTS_AS_EXCEPTIONS
#define BOOST_ENABLE_ASSERT_HANDLER

#include <boost/assert.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/exceptions.hpp>

void f()
{
  BOOST_ASSERT_MSG( sizeof(void*) == 0
                  , "Some condition was not met."
                  );
}

NT2_TEST_CASE(nt2_test_error)
{
  NT2_TEST_ASSERT(f());
}
