//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#define NT2_UNIT_MODULE "nt2 boost.simd.predicates toolbox - is_real/scalar Mode"

//////////////////////////////////////////////////////////////////////////////
// unit test behavior of boost.simd.predicates components in scalar mode
//////////////////////////////////////////////////////////////////////////////
/// created  by jt the 21/02/2011
/// 
#include <nt2/toolbox/predicates/include/functions/is_real.hpp>
#include <nt2/include/functions/ulpdist.hpp>
#include <boost/simd/sdk/simd/logical.hpp>

#include <boost/type_traits/is_same.hpp>
#include <boost/dispatch/functor/meta/call.hpp>
#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <boost/simd/sdk/memory/buffer.hpp>
#include <nt2/toolbox/constant/constant.hpp>


NT2_TEST_CASE_TPL ( is_real_real__1_0,  BOOST_SIMD_REAL_TYPES)
{
  
  using nt2::is_real;
  using nt2::tag::is_real_;
  typedef typename boost::dispatch::meta::as_integer<T>::type iT;
  typedef typename boost::dispatch::meta::call<is_real_(T)>::type r_t;
  typedef typename nt2::meta::scalar_of<r_t>::type sr_t;
  typedef typename nt2::meta::scalar_of<r_t>::type ssr_t;
  typedef typename boost::dispatch::meta::upgrade<T>::type u_t;
  typedef nt2::logical<T> wished_r_t;
  typedef std::complex<T> cT; 
  typedef nt2::imaginary<T> ciT; 


  // return type conformity test 
  NT2_TEST( (boost::is_same < r_t, wished_r_t >::value) );
  std::cout << std::endl; 
  double ulpd;
  ulpd=0.0;


  // specific values tests
  NT2_TEST_EQUAL(is_real(nt2::One<T>()), r_t(true));
  NT2_TEST_EQUAL(is_real(nt2::Two<T>()), r_t(true));
  NT2_TEST_EQUAL(is_real(nt2::Zero<T>()), r_t(true));
  NT2_TEST_EQUAL(is_real(cT(0, 0)), r_t(true));
  NT2_TEST_EQUAL(is_real(cT(1, 0))    , r_t(true));
  NT2_TEST_EQUAL(is_real(cT(0, 2)), r_t(false));
  NT2_TEST_EQUAL(is_real(cT(0, 1))   , r_t(false)); 
  NT2_TEST_EQUAL(is_real(ciT(1))     , r_t(false)); 
  NT2_TEST_EQUAL(is_real(ciT(0))     , r_t(true)); 
 } // end of test for unsigned_int_
