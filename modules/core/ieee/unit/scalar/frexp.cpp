//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#define NT2_UNIT_MODULE "nt2 ieee toolbox - frexp/scalar Mode"

//////////////////////////////////////////////////////////////////////////////
// unit test behavior of ieee components in scalar mode
//////////////////////////////////////////////////////////////////////////////
/// created by jt the 04/12/2010
///
#include <nt2/toolbox/ieee/include/functions/frexp.hpp>
#include <nt2/include/functions/ulpdist.hpp>
#include <boost/fusion/tuple.hpp>
#include <nt2/include/functions/mantissa.hpp>
#include <nt2/include/functions/exponent.hpp>
#include <nt2/include/functions/linspace.hpp>

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
#include <nt2/table.hpp>

NT2_TEST_CASE_TPL ( frexp_real__1_0,  NT2_REAL_TYPES)
{

  using nt2::frexp;
  using nt2::tag::frexp_;
  typedef typename nt2::meta::as_integer<T>::type iT;
  typedef typename nt2::meta::call<frexp_(T)>::type r_t;
  typedef typename nt2::meta::scalar_of<r_t>::type ssr_t;
  typedef typename nt2::meta::upgrade<T>::type u_t;
  typedef boost::fusion::vector<T,typename nt2::meta::as_integer<T,signed>::type> wished_r_t;


  // return type conformity test
  NT2_TEST( (boost::is_same < r_t, wished_r_t >::value) );
  // return type conformity test

  iT e;
  T m = frexp(boost::simd::One<T>(), e);
  NT2_TEST_EQUAL(m, boost::simd::Half<T>());
  NT2_TEST_EQUAL(e, 1);
} // end of test for floating_

// NT2_TEST_CASE_TPL ( frexp_table__1_0,  NT2_REAL_TYPES) //this one doesn't compile
// {

//   using nt2::frexp;
//   using nt2::tag::frexp_;
//   typedef typename nt2::meta::as_integer<T>::type iT;
//   typedef typename nt2::meta::call<frexp_(T)>::type r_t;
//   typedef typename nt2::meta::scalar_of<r_t>::type ssr_t;
//   typedef typename nt2::meta::upgrade<T>::type u_t;
//   typedef boost::fusion::vector<T,typename nt2::meta::as_integer<T,signed>::type> wished_r_t;


//   // return type conformity test
//   NT2_TEST( (boost::is_same < r_t, wished_r_t >::value) );
//   nt2::table<T> v = nt2::linspace(T(1), T(5), 10);
//   nt2::table<T> m(nt2::of_size(1, 10)), im(nt2::of_size(1, 10));
//   nt2::table<iT> e(nt2::of_size(1, 10)), ie(nt2::of_size(1, 10));
//   m = nt2::frexp(v, e);

//   for(int i=1; i <= 10; ++i)
//   {
//     im(i) = nt2::frexp(v(i), ie(i));
//   }
//   NT2_TEST_EQUAL(m, im);
//   NT2_TEST_EQUAL(e, ie);
// } // end of test for table_


NT2_TEST_CASE_TPL ( frexp_table__2_0,  NT2_REAL_TYPES) //this one  compiles but fails
{

  using nt2::frexp;
  using nt2::tag::frexp_;
  typedef typename nt2::meta::as_integer<T>::type iT;
  typedef typename nt2::meta::call<frexp_(T)>::type r_t;
  typedef typename nt2::meta::scalar_of<r_t>::type ssr_t;
  typedef typename nt2::meta::upgrade<T>::type u_t;
  typedef boost::fusion::vector<T,typename nt2::meta::as_integer<T,signed>::type> wished_r_t;


  // return type conformity test
  NT2_TEST( (boost::is_same < r_t, wished_r_t >::value) );
  nt2::table<T> v = nt2::linspace(T(1), T(5), 10);
  nt2::table<T> m(nt2::of_size(1, 10)), im(nt2::of_size(1, 10));
  nt2::table<iT> e(nt2::of_size(1, 10)), ie(nt2::of_size(1, 10));
  nt2::frexp(v, m, e);

  for(int i=1; i <= 10; ++i)
  {
    im(i) = nt2::frexp(v(i), ie(i));
  }
  NT2_TEST_EQUAL(m, im);
  NT2_TEST_EQUAL(e, ie);
} // end of test for table_
