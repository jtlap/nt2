//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#define NT2_UNIT_MODULE "nt2 bitwise toolbox - ffs/scalar Mode"

//////////////////////////////////////////////////////////////////////////////
// unit test behavior of bitwise components in scalar mode
//////////////////////////////////////////////////////////////////////////////
/// created  by jt the 18/02/2011
///
#include <nt2/toolbox/bitwise/include/functions/ffs.hpp>
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


NT2_TEST_CASE_TPL ( ffs_float_1_0,  (float))
{

  using nt2::ffs;
  using nt2::tag::ffs_;
  typedef typename nt2::meta::as_integer<T>::type iT;
  typedef typename nt2::meta::call<ffs_(T)>::type r_t;
  typedef typename nt2::meta::scalar_of<r_t>::type ssr_t;
  typedef typename nt2::meta::upgrade<T>::type u_t;
  typedef typename nt2::meta::as_integer<T, unsigned>::type wished_r_t;


  // return type conformity test
  NT2_TEST( (boost::is_same < r_t, wished_r_t >::value) );
  std::cout << std::endl;
  double ulpd;
  ulpd=0.0;


  // specific values tests
  NT2_TEST_EQUAL(ffs(nt2::Inf<T>()), 24u);
  NT2_TEST_EQUAL(ffs(nt2::Minf<T>()), 24u);
  NT2_TEST_EQUAL(ffs(nt2::Nan<T>()), nt2::One<r_t>());
  NT2_TEST_EQUAL(ffs(nt2::Signmask<T>()), sizeof(T)*8);
  NT2_TEST_EQUAL(ffs(nt2::Zero<T>()), nt2::Zero<r_t>());
} // end of test for float

NT2_TEST_CASE_TPL ( ffs_double_1_0,  (double))
{

  using nt2::ffs;
  using nt2::tag::ffs_;
  typedef typename nt2::meta::as_integer<T>::type iT;
  typedef typename nt2::meta::call<ffs_(T)>::type r_t;
  typedef typename nt2::meta::scalar_of<r_t>::type ssr_t;
  typedef typename nt2::meta::upgrade<T>::type u_t;
  typedef typename nt2::meta::as_integer<T, unsigned>::type wished_r_t;


  // return type conformity test
  NT2_TEST( (boost::is_same < r_t, wished_r_t >::value) );
  std::cout << std::endl;
  double ulpd;
  ulpd=0.0;


  // specific values tests
  NT2_TEST_EQUAL(ffs(nt2::Inf<T>()), 53u);
  NT2_TEST_EQUAL(ffs(nt2::Minf<T>()), 53u);
  NT2_TEST_EQUAL(ffs(nt2::Nan<T>()), nt2::One<r_t>());
  NT2_TEST_EQUAL(ffs(nt2::Signmask<T>()), sizeof(T)*8);
  NT2_TEST_EQUAL(ffs(nt2::Zero<T>()), nt2::Zero<r_t>());
} // end of test for double

NT2_TEST_CASE_TPL ( ffs_signed_int__1_0,  NT2_INTEGRAL_SIGNED_TYPES)
{

  using nt2::ffs;
  using nt2::tag::ffs_;
  typedef typename nt2::meta::as_integer<T>::type iT;
  typedef typename nt2::meta::call<ffs_(T)>::type r_t;
  typedef typename nt2::meta::scalar_of<r_t>::type ssr_t;
  typedef typename nt2::meta::upgrade<T>::type u_t;
  typedef typename nt2::meta::as_integer<T, unsigned>::type wished_r_t;


  // return type conformity test
  NT2_TEST( (boost::is_same < r_t, wished_r_t >::value) );
  std::cout << std::endl;
  double ulpd;
  ulpd=0.0;


  // specific values tests
  NT2_TEST_EQUAL(ffs(nt2::One<T>()), nt2::One<r_t>());
  NT2_TEST_EQUAL(ffs(nt2::Signmask<T>()), sizeof(T)*8);
  NT2_TEST_EQUAL(ffs(nt2::Zero<T>()), nt2::Zero<r_t>());
} // end of test for signed_int_

NT2_TEST_CASE_TPL ( ffs_unsigned_int__1_0,  NT2_UNSIGNED_TYPES)
{

  using nt2::ffs;
  using nt2::tag::ffs_;
  typedef typename nt2::meta::as_integer<T>::type iT;
  typedef typename nt2::meta::call<ffs_(T)>::type r_t;
  typedef typename nt2::meta::scalar_of<r_t>::type ssr_t;
  typedef typename nt2::meta::upgrade<T>::type u_t;
  typedef typename nt2::meta::as_integer<T, unsigned>::type wished_r_t;


  // return type conformity test
  NT2_TEST( (boost::is_same < r_t, wished_r_t >::value) );
  std::cout << std::endl;
  double ulpd;
  ulpd=0.0;


  // specific values tests
  NT2_TEST_EQUAL(ffs(nt2::One<T>()), nt2::One<r_t>());
  NT2_TEST_EQUAL(ffs(nt2::Zero<T>()), nt2::Zero<r_t>());
} // end of test for unsigned_int_
