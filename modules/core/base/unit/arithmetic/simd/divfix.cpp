#include <nt2/arithmetic/include/functions/divfix.hpp>
#include <boost/simd/sdk/simd/native.hpp>
#include <nt2/include/functions/toint.hpp>

#include <boost/type_traits/is_same.hpp>
#include <nt2/sdk/functor/meta/call.hpp>
#include <nt2/sdk/meta/as_integer.hpp>
#include <nt2/sdk/meta/as_floating.hpp>
#include <nt2/sdk/meta/as_signed.hpp>
#include <nt2/sdk/meta/upgrade.hpp>
#include <nt2/sdk/meta/downgrade.hpp>
#include <nt2/sdk/meta/scalar_of.hpp>
#include <boost/dispatch/meta/as_floating.hpp>
#include <boost/type_traits/common_type.hpp>
#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/module.hpp>

#include <nt2/constant/constant.hpp>
#include <nt2/sdk/meta/cardinal_of.hpp>
#include <nt2/include/functions/splat.hpp>

NT2_TEST_CASE_TPL ( divfix_real__2_0,  NT2_SIMD_REAL_TYPES)
{
  using nt2::divfix;
  using nt2::tag::divfix_;
  using boost::simd::native;
  using nt2::meta::cardinal_of;
  typedef NT2_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef native<T,ext_t>                        n_t;
  typedef n_t                                     vT;
  typedef typename nt2::meta::call<divfix_(T,T)>::type sr_t;



  // specific values tests
  NT2_TEST_ULP_EQUAL(divfix(nt2::Four<vT>(),nt2::Three<vT>())[0], nt2::One<sr_t>(), 0);
  NT2_TEST_ULP_EQUAL(divfix(nt2::Four<vT>(),nt2::Zero<vT>())[0], nt2::Inf<sr_t>(), 0);
  NT2_TEST_ULP_EQUAL(divfix(nt2::Inf<vT>(), nt2::Inf<vT>())[0], nt2::Nan<T>(), 0);
  NT2_TEST_ULP_EQUAL(divfix(nt2::Mfour<vT>(),nt2::Zero<vT>())[0], nt2::Minf<sr_t>(), 0);
  NT2_TEST_ULP_EQUAL(divfix(nt2::Minf<vT>(), nt2::Minf<vT>())[0], nt2::Nan<T>(), 0);
  NT2_TEST_ULP_EQUAL(divfix(nt2::Mone<vT>(), nt2::Mone<vT>())[0], nt2::One<T>(), 0);
  NT2_TEST_ULP_EQUAL(divfix(nt2::Nan<vT>(), nt2::Nan<vT>())[0], nt2::Nan<T>(), 0);
  NT2_TEST_ULP_EQUAL(divfix(nt2::One<vT>(), nt2::One<vT>())[0], nt2::One<T>(), 0);
  NT2_TEST_ULP_EQUAL(divfix(nt2::Zero<vT>(), nt2::Zero<vT>())[0], nt2::Nan<T>(), 0);
} // end of test for floating_
