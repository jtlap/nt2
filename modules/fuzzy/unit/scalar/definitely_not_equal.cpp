//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#define NT2_UNIT_MODULE "nt2 fuzzy toolbox - definitely_not_equal/scalar Mode"

//////////////////////////////////////////////////////////////////////////////
// unit test behavior of fuzzy components in scalar mode
//////////////////////////////////////////////////////////////////////////////
/// created  by jt the 04/03/2011
/// 
#include <nt2/toolbox/fuzzy/include/functions/definitely_not_equal.hpp>
#include <nt2/include/functions/ulpdist.hpp>
#include <nt2/sdk/simd/logical.hpp>

#include <boost/type_traits/is_same.hpp>
#include <nt2/sdk/functor/meta/call.hpp>
#include <nt2/sdk/meta/as_integer.hpp>
#include <nt2/sdk/meta/as_floating.hpp>
#include <nt2/sdk/meta/as_signed.hpp>
#include <nt2/sdk/meta/upgrade.hpp>
#include <nt2/sdk/meta/downgrade.hpp>
#include <nt2/sdk/meta/scalar_of.hpp>
#include <nt2/sdk/meta/floating.hpp>
#include <nt2/sdk/meta/arithmetic.hpp>
#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/memory/buffer.hpp>
#include <nt2/toolbox/constant/constant.hpp>


NT2_TEST_CASE_TPL ( definitely_not_equal_real__3_0,  NT2_REAL_TYPES)
{
  
  using nt2::definitely_not_equal;
  using nt2::tag::definitely_not_equal_;
  typedef typename nt2::meta::as_integer<T>::type iT;
  typedef typename nt2::meta::call<definitely_not_equal_(T,T,iT)>::type r_t;
  typedef typename nt2::meta::scalar_of<r_t>::type ssr_t;
  typedef typename nt2::meta::upgrade<T>::type u_t;
  typedef typename nt2::meta::as_logical<T>::type wished_r_t;


  // return type conformity test 
  NT2_TEST( (boost::is_same < r_t, wished_r_t >::value) );
  std::cout << std::endl; 
  double ulpd;
  ulpd=0.0;


  // specific values tests
  NT2_TEST_EQUAL(definitely_not_equal(T(0),T(0),iT(1)), nt2::False<T>());
  NT2_TEST_EQUAL(definitely_not_equal(T(0),T(1),iT(1)), nt2::True<T>());
} // end of test for floating_

NT2_TEST_CASE_TPL ( definitely_not_equal_signed_int__3_0,  NT2_INTEGRAL_SIGNED_TYPES)
{
  
  using nt2::definitely_not_equal;
  using nt2::tag::definitely_not_equal_;
  typedef typename nt2::meta::as_integer<T>::type iT;
  typedef typename nt2::meta::call<definitely_not_equal_(T,T,iT)>::type r_t;
  typedef typename nt2::meta::scalar_of<r_t>::type ssr_t;
  typedef typename nt2::meta::upgrade<T>::type u_t;
  typedef typename nt2::meta::as_logical<T>::type wished_r_t;


  // return type conformity test 
  NT2_TEST( (boost::is_same < r_t, wished_r_t >::value) );
  std::cout << std::endl; 
  double ulpd;
  ulpd=0.0;


  // specific values tests
  NT2_TEST_EQUAL(definitely_not_equal(T(0),T(0),iT(1)), nt2::False<T>());
  NT2_TEST_EQUAL(definitely_not_equal(T(0),T(1),iT(1)), nt2::False<T>());
} // end of test for signed_int_

NT2_TEST_CASE_TPL ( definitely_not_equal_unsigned_int__3_0,  NT2_UNSIGNED_TYPES)
{
  
  using nt2::definitely_not_equal;
  using nt2::tag::definitely_not_equal_;
  typedef typename nt2::meta::as_integer<T>::type iT;
  typedef typename nt2::meta::call<definitely_not_equal_(T,T,iT)>::type r_t;
  typedef typename nt2::meta::scalar_of<r_t>::type ssr_t;
  typedef typename nt2::meta::upgrade<T>::type u_t;
  typedef typename nt2::meta::as_logical<T>::type wished_r_t;


  // return type conformity test 
  NT2_TEST( (boost::is_same < r_t, wished_r_t >::value) );
  std::cout << std::endl; 
  double ulpd;
  ulpd=0.0;


  // specific values tests
  NT2_TEST_EQUAL(definitely_not_equal(T(0),T(0),iT(1)), nt2::False<T>());
  NT2_TEST_EQUAL(definitely_not_equal(T(0),T(1),iT(1)), nt2::False<T>());
} // end of test for unsigned_int_
