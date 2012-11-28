//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#define NT2_UNIT_MODULE "nt2 combinatorial toolbox - factorial/simd Mode"

//////////////////////////////////////////////////////////////////////////////
// unit test behavior of combinatorial components in simd mode
//////////////////////////////////////////////////////////////////////////////
/// created  by jt the 07/03/2011
///
#include <nt2/toolbox/combinatorial/include/functions/factorial.hpp>
#include <nt2/include/functions/ulpdist.hpp>
#include <nt2/include/functions/min.hpp>
#include <nt2/include/functions/saturate.hpp>

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
#include <nt2/sdk/memory/buffer.hpp>
#include <nt2/toolbox/constant/constant.hpp>
#include <nt2/sdk/meta/cardinal_of.hpp>
#include <nt2/include/functions/splat.hpp>
#include <nt2/include/functions/load.hpp>
#include <nt2/toolbox/constant/constant.hpp>


NT2_TEST_CASE_TPL ( factorial_real__1_0,  NT2_SIMD_REAL_TYPES)
{
  using nt2::factorial;
  using nt2::tag::factorial_;
  using nt2::load;
  using boost::simd::native;
  using nt2::meta::cardinal_of;
  typedef NT2_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef typename nt2::meta::upgrade<T>::type   u_t;
  typedef native<T,ext_t>                        n_t;
  typedef n_t                                     vT;
  typedef typename nt2::meta::as_integer<T>::type iT;
  typedef native<iT,ext_t>                       ivT;
  typedef typename nt2::meta::call<factorial_(vT)>::type r_t;
  typedef typename nt2::meta::call<factorial_(T)>::type sr_t;
  typedef typename nt2::meta::scalar_of<r_t>::type ssr_t;
  double ulpd;
  ulpd=0.0;


  // specific values tests
  NT2_TEST_ULP_EQUAL(factorial(nt2::Eight<vT>())[0], nt2::min((T(40320ll    )),nt2::Valmax<T>()), 0);
  NT2_TEST_ULP_EQUAL(factorial(nt2::Eleven<vT>())[0], nt2::min((T(39916800ll )),nt2::Valmax<T>()), 0);
  NT2_TEST_ULP_EQUAL(factorial(nt2::Five<vT>())[0], T(120), 0);
  NT2_TEST_ULP_EQUAL(factorial(nt2::Four<vT>())[0], T(24), 0);
  NT2_TEST_ULP_EQUAL(factorial(nt2::Inf<vT>())[0], nt2::Inf<T>(), 0);
  NT2_TEST_ULP_EQUAL(factorial(nt2::Nan<vT>())[0], nt2::Nan<T>(), 0);
  NT2_TEST_ULP_EQUAL(factorial(nt2::Nine<vT>())[0], nt2::min((T(362880ll   )),nt2::Valmax<T>()), 0);
  NT2_TEST_ULP_EQUAL(factorial(nt2::One<vT>())[0], nt2::One<T>(), 0);
  NT2_TEST_ULP_EQUAL(factorial(nt2::Seven<vT>())[0], nt2::min((T(5040ll     )),nt2::Valmax<T>()), 0);
  NT2_TEST_ULP_EQUAL(factorial(nt2::Six<vT>())[0], nt2::min((T(720ll      )),nt2::Valmax<T>()), 0);
  NT2_TEST_ULP_EQUAL(factorial(nt2::Ten<vT>())[0], nt2::min((T(3628800ll  )),nt2::Valmax<T>()), 0);
  NT2_TEST_ULP_EQUAL(factorial(nt2::Three<vT>())[0], nt2::Six<T>(), 0);
  NT2_TEST_ULP_EQUAL(factorial(nt2::Twelve<vT>())[0], nt2::min((T(479001600ll)),nt2::Valmax<T>()), 0);
  NT2_TEST_ULP_EQUAL(factorial(nt2::Two<vT>())[0], nt2::Two<T>(), 0);
  NT2_TEST_ULP_EQUAL(factorial(nt2::Zero<vT>())[0], nt2::One<T>(), 0);
} // end of test for floating_

NT2_TEST_CASE_TPL ( factorial_integer__1_0,  NT2_SIMD_INTEGRAL_TYPES)
{
  using nt2::factorial;
  using nt2::tag::factorial_;
  using nt2::load;
  using boost::simd::native;
  using nt2::meta::cardinal_of;
  typedef NT2_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef typename nt2::meta::upgrade<T>::type   u_t;
  typedef native<T,ext_t>                        n_t;
  typedef n_t                                     vT;
  typedef typename nt2::meta::as_integer<T>::type iT;
  typedef native<iT,ext_t>                       ivT;
  typedef typename nt2::meta::call<factorial_(vT)>::type r_t;
  typedef typename nt2::meta::call<factorial_(T)>::type sr_t;
  typedef typename nt2::meta::scalar_of<r_t>::type ssr_t;
  double ulpd;
  ulpd=0.0;


  // specific values tests
  NT2_TEST_ULP_EQUAL(factorial(nt2::Eight<vT>())[0], T(nt2::saturate<T>(40320ull    )), 0);
  NT2_TEST_ULP_EQUAL(factorial(nt2::Eleven<vT>())[0], T(nt2::saturate<T>(39916800ull )), 0);
  NT2_TEST_ULP_EQUAL(factorial(nt2::Five<vT>())[0], T(120), 0);
  NT2_TEST_ULP_EQUAL(factorial(nt2::Four<vT>())[0], T(24), 0);
  NT2_TEST_ULP_EQUAL(factorial(nt2::Nine<vT>())[0], T(nt2::saturate<T>(362880ull   )), 0);
  NT2_TEST_ULP_EQUAL(factorial(nt2::One<vT>())[0], nt2::One<T>(), 0);
  NT2_TEST_ULP_EQUAL(factorial(nt2::Seven<vT>())[0], T(nt2::saturate<T>(5040ull     )), 0);
  NT2_TEST_ULP_EQUAL(factorial(nt2::Six<vT>())[0], T(nt2::saturate<T>(720ull      )), 0);
  NT2_TEST_ULP_EQUAL(factorial(nt2::Ten<vT>())[0], T(nt2::saturate<T>(3628800ull  )), 0);
  NT2_TEST_ULP_EQUAL(factorial(nt2::Three<vT>())[0], nt2::Six<T>(), 0);
  NT2_TEST_ULP_EQUAL(factorial(nt2::Twelve<vT>())[0], T(nt2::saturate<T>(479001600ull)), 0);
  NT2_TEST_ULP_EQUAL(factorial(nt2::Zero<vT>())[0], nt2::One<T>(), 0);
} // end of test for integer_
