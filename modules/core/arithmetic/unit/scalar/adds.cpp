//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#define NT2_UNIT_MODULE "nt2 arithmetic toolbox - adds/scalar Mode"

//////////////////////////////////////////////////////////////////////////////
// unit test behavior of arithmetic components in scalar mode
//////////////////////////////////////////////////////////////////////////////
/// created by jt the 28/11/2010
///
#include <nt2/toolbox/arithmetic/include/functions/adds.hpp>
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

#include <nt2/toolbox/constant/constant.hpp>


NT2_TEST_CASE_TPL ( adds_signed_int__2_0,  NT2_INTEGRAL_SIGNED_TYPES)
{

  using nt2::adds;
  using nt2::tag::adds_;
  typedef typename nt2::meta::as_integer<T>::type iT;
  typedef typename nt2::meta::call<adds_(T,T)>::type r_t;
  typedef typename nt2::meta::scalar_of<r_t>::type ssr_t;
  typedef typename nt2::meta::upgrade<T>::type u_t;
  typedef T wished_r_t;


  // return type conformity test
  NT2_TEST( (boost::is_same < r_t, wished_r_t >::value) );
  std::cout << std::endl;
  double ulpd;
  ulpd=0.0;


  // specific values tests
  NT2_TEST_EQUAL(adds(nt2::Mone<T>(), nt2::Mone<T>()), -nt2::Two<T>());
  NT2_TEST_EQUAL(adds(nt2::One<T>(), nt2::One<T>()), nt2::Two<T>());
  NT2_TEST_EQUAL(adds(nt2::Valmax<T>(),nt2::One<T>()), nt2::Valmax<T>());
  NT2_TEST_EQUAL(adds(nt2::Valmin<T>(),nt2::Mone<T>()), nt2::Valmin<T>());
  NT2_TEST_EQUAL(adds(nt2::Zero<T>(), nt2::Zero<T>()), nt2::Zero<T>());
} // end of test for signed_int_

NT2_TEST_CASE_TPL ( adds_unsigned_int__2_0,  NT2_UNSIGNED_TYPES)
{

  using nt2::adds;
  using nt2::tag::adds_;
  typedef typename nt2::meta::as_integer<T>::type iT;
  typedef typename nt2::meta::call<adds_(T,T)>::type r_t;
  typedef typename nt2::meta::scalar_of<r_t>::type ssr_t;
  typedef typename nt2::meta::upgrade<T>::type u_t;
  typedef T wished_r_t;


  // return type conformity test
  NT2_TEST( (boost::is_same < r_t, wished_r_t >::value) );
  std::cout << std::endl;
  double ulpd;
  ulpd=0.0;


  // specific values tests
  NT2_TEST_EQUAL(adds(nt2::One<T>(), nt2::One<T>()), nt2::Two<T>());
  NT2_TEST_EQUAL(adds(nt2::Valmax<T>(),nt2::One<T>()), nt2::Valmax<T>());
  NT2_TEST_EQUAL(adds(nt2::Zero<T>(), nt2::Zero<T>()), nt2::Zero<T>());
} // end of test for unsigned_int_
