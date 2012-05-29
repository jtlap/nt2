#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <boost/type_traits/add_pointer.hpp>

NT2_TEST_CASE(nt2_test_lesser)
{
  NT2_TEST_LESSER(0.f, 3);
}
