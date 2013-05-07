#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>
#include <boost/type_traits/add_pointer.hpp>

NT2_TEST_CASE(nt2_test_type_is)
{
  NT2_TEST_TYPE_IS(float*, boost::add_pointer<float>::type);
}
