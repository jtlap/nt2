//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#define NT2_UNIT_MODULE "nt2 boost.simd.ieee toolbox - ldexp/scalar Mode"

//////////////////////////////////////////////////////////////////////////////
// unit test behavior of boost.simd.ieee components in scalar mode
//////////////////////////////////////////////////////////////////////////////
/// created by jt the 04/12/2010
///
#include <boost/simd/toolbox/ieee/include/functions/ldexp.hpp>
#include <boost/simd/sdk/simd/native.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/dispatch/functor/meta/call.hpp>
#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <boost/simd/toolbox/constant/constant.hpp>


NT2_TEST_CASE_TPL ( ldexp_real__2_0,  BOOST_SIMD_REAL_TYPES)
{

  using boost::simd::ldexp;
  using boost::simd::tag::ldexp_;
  typedef typename boost::dispatch::meta::as_integer<T>::type iT;
  typedef typename boost::dispatch::meta::call<ldexp_(T,iT)>::type r_t;
  typedef typename boost::simd::meta::scalar_of<r_t>::type sr_t;
  typedef typename boost::simd::meta::scalar_of<r_t>::type ssr_t;
  typedef typename boost::dispatch::meta::upgrade<T>::type u_t;
  typedef T wished_r_t;


  // return type conformity test
  NT2_TEST( (boost::is_same < r_t, wished_r_t >::value) );
  std::cout << std::endl;
  NT2_TEST_EQUAL(ldexp(boost::simd::Inf<T>(),  2), boost::simd::Inf<r_t>());
  NT2_TEST_EQUAL(ldexp(boost::simd::Minf<T>(), 2), boost::simd::Minf<r_t>());
  NT2_TEST_EQUAL(ldexp(boost::simd::Mone<T>(), 2), -boost::simd::Four<r_t>());
  NT2_TEST_EQUAL(ldexp(boost::simd::Nan<T>(),  2), boost::simd::Nan<r_t>());
  NT2_TEST_EQUAL(ldexp(boost::simd::One<T>(),  2), boost::simd::Four<r_t>());
  NT2_TEST_EQUAL(ldexp(boost::simd::Zero<T>(), 2), boost::simd::Zero<r_t>());
} // end of test for floating_
