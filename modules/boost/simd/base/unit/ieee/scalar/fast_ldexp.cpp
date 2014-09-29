#include <boost/simd/ieee/include/functions/fast_ldexp.hpp>

#include <boost/dispatch/functor/meta/call.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <boost/simd/sdk/config.hpp>
#include <boost/dispatch/meta/as_integer.hpp>

#include <boost/simd/include/constants/mone.hpp>
#include <boost/simd/include/constants/four.hpp>
#include <boost/simd/include/constants/mfour.hpp>
#include <boost/simd/include/constants/one.hpp>
#include <boost/simd/include/constants/zero.hpp>
#include <boost/simd/include/constants/quarter.hpp>


NT2_TEST_CASE_TPL ( fast_ldexp_real,  BOOST_SIMD_REAL_TYPES)
{

  using boost::simd::fast_ldexp;
  using boost::simd::tag::fast_ldexp_;
  typedef typename boost::dispatch::meta::as_integer<T>::type iT;
  typedef typename boost::dispatch::meta::call<fast_ldexp_(T,iT)>::type r_t;
  typedef T wished_r_t;


  // return type conformity test
  NT2_TEST_TYPE_IS(r_t, wished_r_t);

  NT2_TEST_EQUAL(fast_ldexp(boost::simd::Mone<T>(), 2), boost::simd::Mfour<r_t>());
  NT2_TEST_EQUAL(fast_ldexp(boost::simd::One<T>(),  2), boost::simd::Four<r_t>());
  NT2_TEST_EQUAL(fast_ldexp(boost::simd::One<T>(), -2), boost::simd::Quarter<r_t>());
}

NT2_TEST_CASE_TPL ( fast_ldexp_si,  BOOST_SIMD_SIMD_INTEGRAL_SIGNED_TYPES)
{

  using boost::simd::fast_ldexp;
  using boost::simd::tag::fast_ldexp_;
  typedef typename boost::dispatch::meta::as_integer<T>::type iT;
  typedef typename boost::dispatch::meta::call<fast_ldexp_(T,iT)>::type r_t;
  typedef T wished_r_t;


  // return type conformity test
  NT2_TEST_TYPE_IS(r_t, wished_r_t);

  NT2_TEST_EQUAL(fast_ldexp(boost::simd::Mone<T>(), 2), boost::simd::Mfour<r_t>());
  NT2_TEST_EQUAL(fast_ldexp(boost::simd::One<T>(),  2), boost::simd::Four<r_t>());
  NT2_TEST_EQUAL(fast_ldexp(boost::simd::Zero<T>(), 2), boost::simd::Zero<r_t>());
}

NT2_TEST_CASE_TPL ( fast_ldexp_ui,  BOOST_SIMD_SIMD_UNSIGNED_TYPES)
{

  using boost::simd::fast_ldexp;
  using boost::simd::tag::fast_ldexp_;
  typedef typename boost::dispatch::meta::as_integer<T>::type iT;
  typedef typename boost::dispatch::meta::call<fast_ldexp_(T,iT)>::type r_t;
  typedef T wished_r_t;


  // return type conformity test
  NT2_TEST_TYPE_IS(r_t, wished_r_t);

  NT2_TEST_EQUAL(fast_ldexp(boost::simd::One<T>(),  2), boost::simd::Four<r_t>());
  NT2_TEST_EQUAL(fast_ldexp(boost::simd::Zero<T>(), 2), boost::simd::Zero<r_t>());
}
