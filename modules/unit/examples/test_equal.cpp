#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <boost/type_traits/add_pointer.hpp>

NT2_TEST_CASE(nt2_test_equal)
{
  NT2_TEST_EQUAL(4, 4.f);
}
