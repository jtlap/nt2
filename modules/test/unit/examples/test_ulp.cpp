#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/ulp.hpp>

NT2_TEST_CASE(nt2_test_ulp)
{
  NT2_TEST_ULP_EQUAL(1.f, 1.0000001f, 0.5);
}
