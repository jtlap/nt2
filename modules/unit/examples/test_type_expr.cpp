#include <typeinfo>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>
#include <boost/mpl/placeholders.hpp>
#include <boost/type_traits/remove_pointer.hpp>

NT2_TEST_CASE(nt2_test_type_info)
{
  float* ptr;
  NT2_TEST_EXPR_TYPE( ptr
                    , boost::remove_pointer<boost::mpl::_>
                    , float
                    );
}
