//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#define NT2_UNIT_MODULE "nt2 trigonometric toolbox - sin/scalar Mode"

//////////////////////////////////////////////////////////////////////////////
// unit test behavior of trigonometric components in scalar mode
//////////////////////////////////////////////////////////////////////////////
/// created  by jt the 11/02/2011
/// 
#include <nt2/toolbox/trigonometric/include/functions/sin.hpp>
#include <nt2/include/functions/ulpdist.hpp>
#include <nt2/toolbox/trigonometric/constants.hpp>
extern "C" {extern long double cephes_sinl(long double);}

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


NT2_TEST_CASE_TPL ( sin_real__1_0,  NT2_REAL_TYPES)
{
  
  using nt2::sin;
  using nt2::tag::sin_;
  typedef typename nt2::meta::as_integer<T>::type iT;
  typedef typename nt2::meta::call<sin_(T)>::type r_t;
  typedef typename nt2::meta::scalar_of<r_t>::type ssr_t;
  typedef typename nt2::meta::upgrade<T>::type u_t;
  typedef typename boost::dispatch::meta::as_floating<T>::type wished_r_t;


  // return type conformity test 
  NT2_TEST( (boost::is_same < r_t, wished_r_t >::value) );
  std::cout << std::endl; 

  // specific values tests
  NT2_TEST_ULP_EQUAL(sin(-nt2::Pi<T>()/T(2)), nt2::Mone<r_t>(), 0.5);
  NT2_TEST_ULP_EQUAL(sin(-nt2::Pi<T>()/T(4)), -nt2::Sqrt_2o_2<r_t>(), 0.5);
  NT2_TEST_ULP_EQUAL(sin(nt2::Inf<T>()), nt2::Nan<r_t>(), 0.5);
  NT2_TEST_ULP_EQUAL(sin(nt2::Minf<T>()), nt2::Nan<r_t>(), 0.5);
  NT2_TEST_ULP_EQUAL(sin(nt2::Nan<T>()), nt2::Nan<r_t>(), 0.5);
  NT2_TEST_ULP_EQUAL(sin(nt2::Pi<T>()/T(2)), nt2::One<r_t>(), 0.5);
  NT2_TEST_ULP_EQUAL(sin(nt2::Pi<T>()/T(4)), nt2::Sqrt_2o_2<r_t>(), 0.5);
  NT2_TEST_ULP_EQUAL(sin(nt2::Zero<T>()), nt2::Zero<r_t>(), 0.5);

} // end of test for floating_

NT2_TEST_CASE_TPL ( sin_unsigned_int__1_0,  NT2_UNSIGNED_TYPES)
{
  
  using nt2::sin;
  using nt2::tag::sin_;
  typedef typename nt2::meta::as_integer<T>::type iT;
  typedef typename nt2::meta::call<sin_(T)>::type r_t;
  typedef typename nt2::meta::scalar_of<r_t>::type ssr_t;
  typedef typename nt2::meta::upgrade<T>::type u_t;
  typedef typename boost::dispatch::meta::as_floating<T>::type wished_r_t;


  // return type conformity test 
  NT2_TEST( (boost::is_same < r_t, wished_r_t >::value) );
  std::cout << std::endl; 


  // specific values tests
  NT2_TEST_ULP_EQUAL(sin(nt2::Zero<T>()), nt2::Zero<r_t>(), 0.5);
} // end of test for unsigned_int_

NT2_TEST_CASE_TPL ( sin_signed_int__1_0,  NT2_INTEGRAL_SIGNED_TYPES)
{
  
  using nt2::sin;
  using nt2::tag::sin_;
  typedef typename nt2::meta::as_integer<T>::type iT;
  typedef typename nt2::meta::call<sin_(T)>::type r_t;
  typedef typename nt2::meta::scalar_of<r_t>::type ssr_t;
  typedef typename nt2::meta::upgrade<T>::type u_t;
  typedef typename boost::dispatch::meta::as_floating<T>::type wished_r_t;


  // return type conformity test 
  NT2_TEST( (boost::is_same < r_t, wished_r_t >::value) );
  std::cout << std::endl; 

  // specific values tests
  NT2_TEST_ULP_EQUAL(sin(nt2::Zero<T>()), nt2::Zero<r_t>(), 0.5);
} // end of test for signed_int_


NT2_TEST_CASE ( sin_special)
{
  
  using nt2::sin;
  using nt2::tag::sin_;

  NT2_TEST_ULP_EQUAL(sin(1.0e22), -0.852200849767188801772705893753, 0.5);
  NT2_TEST_ULP_EQUAL(sin(10000000000000000000000.0), -0.852200849767188801772705893753, 0.5);
  NT2_TEST_ULP_EQUAL(sin(1.0e22f),-0.734081535296101525955768907693f, 0.5);
  NT2_TEST_ULP_EQUAL(sin(9999999778196308361216.0f),-0.734081535296101525955768907693f, 0.5);
  std::cout << "Note that these results are due to the fact that 1.0e22f is 9999999778196308361216," << std::endl; 
  std::cout << " not 10000000000000000000000, alas!" << std::endl;
  std::cout << " The next result is the kahan worst case for which one need ~128 bits of 2/pi"<< std::endl; 
  NT2_TEST_ULP_EQUAL(sin(5.31937264832654141671e+255), 0.999999999999999999999999999999999999890152377992531312498043, 0.5);
  
} // end of test for signed_int_
