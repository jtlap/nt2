//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#define NT2_UNIT_MODULE "nt2 boost.simd.ieee toolbox - modf/scalar Mode"

//////////////////////////////////////////////////////////////////////////////
// unit test behavior of boost.simd.ieee components in scalar mode
//////////////////////////////////////////////////////////////////////////////
/// created by jt the 04/12/2010
///
#include <boost/simd/toolbox/ieee/include/functions/modf.hpp>
#include <boost/simd/include/functions/ulpdist.hpp>
#include <boost/fusion/tuple.hpp>
#include <boost/simd/include/functions/trunc.hpp>
#include <boost/simd/include/functions/frac.hpp>

#include <boost/type_traits/is_same.hpp>
#include <boost/dispatch/functor/meta/call.hpp>
#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <boost/simd/toolbox/constant/constant.hpp>


NT2_TEST_CASE_TPL ( modf_real__1_0,  BOOST_SIMD_REAL_TYPES)
{

  using boost::simd::modf;
  using boost::simd::tag::modf_;
  typedef typename boost::dispatch::meta::as_floating<T>::type ftype;
  typedef typename boost::dispatch::meta::as_integer<T>::type iT;
  typedef typename boost::dispatch::meta::call<modf_(T)>::type r_t;
  typedef typename boost::simd::meta::scalar_of<r_t>::type sr_t;
  typedef typename boost::simd::meta::scalar_of<r_t>::type ssr_t;
  typedef typename boost::dispatch::meta::upgrade<T>::type u_t;
  typedef boost::fusion::vector<T,T> wished_r_t;


  // return type conformity test
  NT2_TEST( (boost::is_same < r_t, wished_r_t >::value) );
   T f, n;
  T a[6] = {T(0), T(1), T(1.5), boost::simd::Inf<T>(), boost::simd::Minf<T>(), boost::simd::Nan<T>()};

  for(int i=0; i < 6; i++)
    {
      modf(a[i], n, f);
      NT2_TEST_EQUAL(f, boost::simd::frac(a[i]));
      NT2_TEST_EQUAL(n, boost::simd::trunc(a[i]));
    }
} // end of test for floating_

NT2_TEST_CASE_TPL ( modf_unsigned_int__1_0,  BOOST_SIMD_UNSIGNED_TYPES)
{

  using boost::simd::modf;
  using boost::simd::tag::modf_;
  typedef typename boost::dispatch::meta::as_floating<T>::type ftype;
  typedef typename boost::dispatch::meta::as_integer<T>::type iT;
  typedef typename boost::dispatch::meta::call<modf_(T)>::type r_t;
  typedef typename boost::simd::meta::scalar_of<r_t>::type sr_t;
  typedef typename boost::simd::meta::scalar_of<r_t>::type ssr_t;
  typedef typename boost::dispatch::meta::upgrade<T>::type u_t;
  typedef boost::fusion::vector<T,T> wished_r_t;


  // return type conformity test
  NT2_TEST( (boost::is_same < r_t, wished_r_t >::value) );
  T f, n;
  T a[6] = {T(0), T(1), T(10), T(-10), boost::simd::Valmin<T>(), boost::simd::Valmax<T>()};

  for(int i=0; i < 6; i++)
    {
      modf(a[i], n, f);
      NT2_TEST_EQUAL(f, boost::simd::Zero<T>());
      NT2_TEST_EQUAL(n, boost::simd::trunc(a[i]));
    }
} // end of test for unsigned_int_

NT2_TEST_CASE_TPL ( modf_signed_int__1_0,  BOOST_SIMD_INTEGRAL_SIGNED_TYPES)
{

  using boost::simd::modf;
  using boost::simd::tag::modf_;
  typedef typename boost::dispatch::meta::as_floating<T>::type ftype;
  typedef typename boost::dispatch::meta::as_integer<T>::type iT;
  typedef typename boost::dispatch::meta::call<modf_(T)>::type r_t;
  typedef typename boost::simd::meta::scalar_of<r_t>::type sr_t;
  typedef typename boost::simd::meta::scalar_of<r_t>::type ssr_t;
  typedef typename boost::dispatch::meta::upgrade<T>::type u_t;
  typedef boost::fusion::vector<T,T> wished_r_t;


  // return type conformity test
  NT2_TEST( (boost::is_same < r_t, wished_r_t >::value) );
  T f, n;
  T a[6] = {T(0), T(1), T(10), boost::simd::Valmin<T>(), boost::simd::Valmax<T>()};

  for(int i=0; i < 5; i++)
    {
      modf(a[i], n, f);
      NT2_TEST_EQUAL(f, boost::simd::Zero<T>());
      NT2_TEST_EQUAL(n, boost::simd::trunc(a[i]));
    }

} // end of test for signed_int_
