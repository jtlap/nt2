//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#define NT2_UNIT_MODULE "nt2 boost.simd.ieee toolbox - nextafter/scalar Mode"

//////////////////////////////////////////////////////////////////////////////
// unit test behavior of boost.simd.ieee components in scalar mode
//////////////////////////////////////////////////////////////////////////////
/// created by jt the 04/12/2010
/// 
#include <boost/simd/toolbox/ieee/include/functions/nextafter.hpp>
#include <boost/simd/include/functions/ulpdist.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/dispatch/functor/meta/call.hpp>
#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <boost/simd/toolbox/constant/constant.hpp>


NT2_TEST_CASE_TPL ( nextafter_real__2_0,  (float))
{
  using boost::simd::nextafter;
  using boost::simd::tag::nextafter_;
  typedef typename boost::dispatch::meta::as_integer<T>::type iT;
  typedef typename boost::dispatch::meta::call<nextafter_(T,T)>::type r_t;
  typedef typename boost::simd::meta::scalar_of<r_t>::type sr_t;
  typedef typename boost::simd::meta::scalar_of<r_t>::type ssr_t;
  typedef typename boost::dispatch::meta::upgrade<T>::type u_t;
  typedef T wished_r_t;

  
  // return type conformity test 
  NT2_TEST( (boost::is_same < r_t, wished_r_t >::value) );
  NT2_TEST_EQUAL(nextafter(boost::simd::Inf<T>(), boost::simd::Inf<T>()), boost::simd::Inf<r_t>());
  NT2_TEST_EQUAL(nextafter(boost::simd::Minf<T>(), boost::simd::One<T>()), boost::simd::Valmin<r_t>());
  NT2_TEST_EQUAL(nextafter(boost::simd::Mone<T>(), boost::simd::One<T>()), boost::simd::Mone<r_t>()+boost::simd::Eps<r_t>()/2);
  NT2_TEST_EQUAL(nextafter(boost::simd::Nan<T>(), boost::simd::One<T>()), boost::simd::Nan<r_t>());
  NT2_TEST_EQUAL(nextafter(boost::simd::One<T>(), boost::simd::Inf<T>()), boost::simd::One<r_t>()+boost::simd::Eps<r_t>());
  NT2_TEST_EQUAL(nextafter(boost::simd::Valmax<T>(), boost::simd::Inf<T>()), boost::simd::Inf<r_t>());
  NT2_TEST_EQUAL(nextafter(boost::simd::Zero<T>(), boost::simd::One<T>()), boost::simd::Bitincrement<T>());
} // end of test for floating_
NT2_TEST_CASE_TPL ( nextafter_real__2_0d,  (double))
{
  
  using boost::simd::nextafter;
  using boost::simd::tag::nextafter_;
  typedef typename boost::dispatch::meta::as_integer<T>::type iT;
  typedef typename boost::dispatch::meta::call<nextafter_(T,T)>::type r_t;
  typedef typename boost::simd::meta::scalar_of<r_t>::type sr_t;
  typedef typename boost::simd::meta::scalar_of<r_t>::type ssr_t;
  typedef typename boost::dispatch::meta::upgrade<T>::type u_t;
  typedef T wished_r_t;


  // return type conformity test 
  NT2_TEST( (boost::is_same < r_t, wished_r_t >::value) );
  NT2_TEST_EQUAL(nextafter(boost::simd::Inf<T>(), boost::simd::Inf<T>()), boost::simd::Inf<r_t>());
  NT2_TEST_EQUAL(nextafter(boost::simd::Minf<T>(), boost::simd::One<T>()), boost::simd::Valmin<r_t>());
  NT2_TEST_EQUAL(nextafter(boost::simd::Mone<T>(), boost::simd::One<T>()), boost::simd::Mone<r_t>()+boost::simd::Eps<r_t>()/2);
  NT2_TEST_EQUAL(nextafter(boost::simd::Nan<T>(), boost::simd::One<T>()), boost::simd::Nan<r_t>());
  NT2_TEST_EQUAL(nextafter(boost::simd::One<T>(), boost::simd::Inf<T>()), boost::simd::One<r_t>()+boost::simd::Eps<r_t>());
  NT2_TEST_EQUAL(nextafter(boost::simd::Valmax<T>(), boost::simd::Inf<T>()), boost::simd::Inf<r_t>());
  NT2_TEST_EQUAL(nextafter(boost::simd::Zero<T>(), boost::simd::One<T>()), boost::simd::Bitincrement<T>());
  
} // end of test for floating_
