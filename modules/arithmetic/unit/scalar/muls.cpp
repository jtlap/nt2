//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#define NT2_UNIT_MODULE "nt2 arithmetic toolbox - muls/scalar Mode"

//////////////////////////////////////////////////////////////////////////////
// Test behavior of arithmetic components in scalar mode
//////////////////////////////////////////////////////////////////////////////
/// created by jt the 28/11/2010
/// modified by jt the 06/04/2011
#include <boost/type_traits/is_same.hpp>
#include <nt2/sdk/functor/meta/call.hpp>
#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/memory/buffer.hpp>
#include <nt2/include/constants/real.hpp>
#include <nt2/include/constants/infinites.hpp>
#include <nt2/include/functions/ulpdist.hpp>
#include <nt2/toolbox/arithmetic/include/muls.hpp>

NT2_TEST_CASE_TPL ( muls_signed_int__2_0,  NT2_INTEGRAL_SIGNED_TYPES)
{
  
  using nt2::muls;
  using nt2::tag::muls_;
  typedef typename nt2::meta::as_integer<T>::type iT;
  typedef typename nt2::meta::call<muls_(T,T)>::type r_t;
  typedef typename nt2::meta::upgrade<T>::type u_t;
  typedef T wished_r_t;


  // return type conformity test 
  NT2_TEST( (boost::is_same < r_t, wished_r_t >::value) );
  std::cout << std::endl; 
  double ulpd;
  ulpd=0.0;


  // specific values tests
  NT2_TEST_EQUAL(muls(nt2::Mone<T>(), nt2::Mone<T>()), nt2::One<T>());
  NT2_TEST_EQUAL(muls(nt2::One<T>(), nt2::One<T>()), nt2::One<T>());
  NT2_TEST_EQUAL(muls(nt2::Valmax<T>(), nt2::Valmax<T>()), nt2::Valmax<T>());
  NT2_TEST_EQUAL(muls(nt2::Valmax<T>(),T(2)), nt2::Valmax<T>());
  NT2_TEST_EQUAL(muls(nt2::Valmax<T>(),nt2::Mone<T>()), nt2::Valmin<T>()+nt2::One<T>());
  NT2_TEST_EQUAL(muls(nt2::Valmax<T>(),nt2::One<T>()), nt2::Valmax<T>());
  NT2_TEST_EQUAL(muls(nt2::Valmin<T>(),nt2::Mone<T>()), nt2::Valmax<T>());
  NT2_TEST_EQUAL(muls(nt2::Zero<T>(), nt2::Zero<T>()), nt2::Zero<T>());
} // end of test for signed_int_

NT2_TEST_CASE_TPL ( muls_unsigned_int__2_0,  NT2_UNSIGNED_TYPES)
{
  
  using nt2::muls;
  using nt2::tag::muls_;
  typedef typename nt2::meta::as_integer<T>::type iT;
  typedef typename nt2::meta::call<muls_(T,T)>::type r_t;
  typedef typename nt2::meta::upgrade<T>::type u_t;
  typedef T wished_r_t;


  // return type conformity test 
  NT2_TEST( (boost::is_same < r_t, wished_r_t >::value) );
  std::cout << std::endl; 
  double ulpd;
  ulpd=0.0;


  // specific values tests
  NT2_TEST_EQUAL(muls(nt2::One<T>(), nt2::One<T>()), nt2::One<T>());
  NT2_TEST_EQUAL(muls(nt2::Valmax<T>(),T(2)), nt2::Valmax<T>());
  NT2_TEST_EQUAL(muls(nt2::Zero<T>(), nt2::Zero<T>()), nt2::Zero<T>());
} // end of test for unsigned_int_
