//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#define NT2_UNIT_MODULE "nt2 complex toolbox - cot/scalar Mode"

//////////////////////////////////////////////////////////////////////////////
// unit test behavior of cot  components in scalar mode
//////////////////////////////////////////////////////////////////////////////
/// created by jt the 08/12/2010
/// 
#include <nt2/include/functions/cot.hpp>
#include <nt2/include/functions/ulpdist.hpp>
#include <nt2/include/functions/rec.hpp>
#include <nt2/include/functions/tan.hpp>
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
#include <complex>


NT2_TEST_CASE_TPL ( cot_real__1_0,  NT2_REAL_TYPES)
{
  
  using nt2::cot;
  using nt2::tag::cot_;
  typedef std::complex<T> cT; 
  typedef typename nt2::meta::as_integer<T>::type iT;
  typedef typename nt2::meta::call<cot_(cT)>::type r_t;
  typedef typename nt2::meta::scalar_of<r_t>::type ssr_t;
  typedef typename nt2::meta::upgrade<T>::type u_t;
  typedef typename nt2:: meta::as_complex<T>::type wished_r_t;


  // return type conformity test 
  NT2_TEST( (boost::is_same < r_t, wished_r_t >::value) );
  std::cout << std::endl; 
  double ulpd;
  ulpd=0.0;


  // specific values tests
  NT2_TEST_ULP_EQUAL(nt2::cot(cT(nt2::Inf<T>())), cT(nt2::Nan<T>()), 1);
  NT2_TEST_ULP_EQUAL(nt2::cot(cT(nt2::Minf<T>())), cT(nt2::Nan<T>()), 1);
  NT2_TEST_ULP_EQUAL(nt2::cot(cT(1, 1)),nt2::rec(nt2::tan(cT(1.0, 1.0))), 1);
  NT2_TEST_ULP_EQUAL(nt2::cot(cT(1, 10)),nt2::rec(nt2::tan(cT(1.0, 10.0))), 1);
  NT2_TEST_ULP_EQUAL(nt2::cot(cT(10, 1)),nt2::rec(nt2::tan(cT(10.0, 1.0))), 1);
  NT2_TEST_ULP_EQUAL(nt2::cot(cT(10, 10)),nt2::rec(nt2::tan(cT(10.0, 10.0))), 1);
  NT2_TEST_ULP_EQUAL(nt2::cot(cT(0, 1)),nt2::rec(nt2::tan(cT(0.0, 1.0))), 1);
  NT2_TEST_ULP_EQUAL(nt2::cot(cT(0, 10)),nt2::rec(nt2::tan(cT(0.0, 10.0))), 1);
  NT2_TEST_ULP_EQUAL(nt2::cot(cT(10, 0)),nt2::rec(nt2::tan(cT(10.0, 0.0))), 1);
 } // end of test for floating_

