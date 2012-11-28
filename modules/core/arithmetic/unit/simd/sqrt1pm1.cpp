//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#define NT2_UNIT_MODULE "nt2 arithmetic toolbox - sqrt1pm1/simd Mode"

//////////////////////////////////////////////////////////////////////////////
// Test behavior of arithmetic components in simd mode
//////////////////////////////////////////////////////////////////////////////
/// created by jt the 01/12/2010
/// modified by jt the 06/04/2011

#include <nt2/include/functions/load.hpp>

#include <boost/type_traits/is_same.hpp>
#include <nt2/sdk/functor/meta/call.hpp>
#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/include/constants/real.hpp>
#include <nt2/include/constants/infinites.hpp>
#include <nt2/include/functions/max.hpp>
#include <nt2/toolbox/arithmetic/include/functions/sqrt1pm1.hpp>

NT2_TEST_CASE_TPL ( sqrt1pm1_real__1_0,  NT2_REAL_TYPES)
{
  using nt2::sqrt1pm1;
  using nt2::tag::sqrt1pm1_;
  using nt2::load;
  using boost::simd::native;
  using nt2::meta::cardinal_of;
  typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef typename nt2::meta::upgrade<T>::type   u_t;
  typedef native<T,ext_t>                        n_t;
  typedef n_t                                     vT;
  typedef typename nt2::meta::as_integer<T>::type iT;
  typedef native<iT,ext_t>                       ivT;
  typedef typename nt2::meta::call<sqrt1pm1_(vT)>::type r_t;
  typedef typename nt2::meta::call<sqrt1pm1_(T)>::type sr_t;
  typedef typename nt2::meta::scalar_of<r_t>::type ssr_t;
  double ulpd;
  ulpd=0.0;


  // specific values tests
  NT2_TEST_ULP_EQUAL(sqrt1pm1(nt2::Inf<vT>())[0], nt2::Inf<sr_t>(), 0);
  NT2_TEST_ULP_EQUAL(sqrt1pm1(nt2::Minf<vT>())[0], nt2::Nan<sr_t>(), 0);
  NT2_TEST_ULP_EQUAL(sqrt1pm1(nt2::Mone<vT>())[0], nt2::Mone<sr_t>(), 0);
  NT2_TEST_ULP_EQUAL(sqrt1pm1(nt2::Nan<vT>())[0], nt2::Nan<sr_t>(), 0);
  NT2_TEST_ULP_EQUAL(sqrt1pm1(nt2::One<vT>())[0], nt2::Sqrt_2<sr_t>()-nt2::One<sr_t>(), 2);
  NT2_TEST_ULP_EQUAL(sqrt1pm1(nt2::Zero<vT>())[0], nt2::Zero<sr_t>(), 0);
} // end of test for floating_
