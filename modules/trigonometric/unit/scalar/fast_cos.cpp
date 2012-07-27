//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#define NT2_UNIT_MODULE "nt2 trigonometric toolbox - fast_cos/scalar Mode"

//////////////////////////////////////////////////////////////////////////////
// unit test behavior of trigonometric components in scalar mode
//////////////////////////////////////////////////////////////////////////////
/// created  by jt the 11/02/2011
/// 
#include <nt2/toolbox/trigonometric/include/functions/fast_cos.hpp>
#include <nt2/include/functions/ulpdist.hpp>
#include <nt2/toolbox/trigonometric/constants.hpp>
extern "C" {extern long double cephes_cosl(long double);}

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


NT2_TEST_CASE_TPL ( fast_cos_real__1_0,  NT2_REAL_TYPES)
{
  
  using nt2::fast_cos;
  using nt2::tag::fast_cos_;
  typedef typename nt2::meta::as_integer<T>::type iT;
  typedef typename nt2::meta::call<fast_cos_(T)>::type r_t;
  typedef typename nt2::meta::scalar_of<r_t>::type ssr_t;
  typedef typename nt2::meta::upgrade<T>::type u_t;
  typedef typename boost::dispatch::meta::as_floating<T>::type wished_r_t;


  // return type conformity test 
  NT2_TEST( (boost::is_same < r_t, wished_r_t >::value) );
  std::cout << std::endl; 

  // specific values tests
  NT2_TEST_ULP_EQUAL(fast_cos(-nt2::Pi<T>()), nt2::Nan<r_t>(), 0.5);
  NT2_TEST_ULP_EQUAL(fast_cos(-nt2::Pi<T>()/T(2)), nt2::Nan<r_t>(), 0.5);
  NT2_TEST_ULP_EQUAL(fast_cos(-nt2::Pi<T>()/T(4)), nt2::Sqrt_2o_2<r_t>(), 0.5);
  NT2_TEST_ULP_EQUAL(fast_cos(nt2::Inf<T>()), nt2::Nan<r_t>(), 0.5);
  NT2_TEST_ULP_EQUAL(fast_cos(nt2::Minf<T>()), nt2::Nan<r_t>(), 0.5);
  NT2_TEST_ULP_EQUAL(fast_cos(nt2::Nan<T>()), nt2::Nan<r_t>(), 0.5);
  NT2_TEST_ULP_EQUAL(fast_cos(nt2::Pi<T>()), nt2::Nan<r_t>(), 0.5);
  NT2_TEST_ULP_EQUAL(fast_cos(nt2::Pi<T>()/T(2)), nt2::Nan<r_t>(), 0.5);
  NT2_TEST_ULP_EQUAL(fast_cos(nt2::Pi<T>()/T(4)), nt2::Sqrt_2o_2<r_t>(), 0.5);
  NT2_TEST_ULP_EQUAL(fast_cos(nt2::Zero<T>()), nt2::One<r_t>(), 0.5);
} // end of test for floating_
