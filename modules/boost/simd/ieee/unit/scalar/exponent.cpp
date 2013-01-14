//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#define NT2_UNIT_MODULE "nt2 boost.simd.ieee toolbox - exponent/scalar Mode"

//////////////////////////////////////////////////////////////////////////////
// unit test behavior of boost.simd.ieee components in scalar mode
//////////////////////////////////////////////////////////////////////////////
/// created by jt the 04/12/2010
///
#include <boost/simd/toolbox/ieee/include/functions/exponent.hpp>
#include <boost/simd/sdk/simd/native.hpp>
#include <boost/simd/include/functions/ulpdist.hpp>
#include <boost/simd/include/functions/ilogb.hpp>
#include <boost/simd/include/functions/abs.hpp>

#include <boost/type_traits/is_same.hpp>
#include <boost/dispatch/functor/meta/call.hpp>
#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <boost/simd/toolbox/constant/constant.hpp>


NT2_TEST_CASE_TPL ( exponent_real__1_0,  BOOST_SIMD_REAL_TYPES)
{

  using boost::simd::exponent;
  using boost::simd::tag::exponent_;
  typedef typename boost::dispatch::meta::as_integer<T>::type iT;
  typedef typename boost::dispatch::meta::call<exponent_(T)>::type r_t;
  typedef typename boost::simd::meta::scalar_of<r_t>::type sr_t;
  typedef typename boost::simd::meta::scalar_of<r_t>::type ssr_t;
  typedef typename boost::dispatch::meta::upgrade<T>::type u_t;
  typedef typename boost::dispatch::meta::as_integer<T, signed>::type wished_r_t;


  // return type conformity test
  NT2_TEST( (boost::is_same < r_t, wished_r_t >::value) );
  std::cout << std::endl;

  // specific values tests
  NT2_TEST_EQUAL(exponent(boost::simd::Minf<T>()), boost::simd::Zero<r_t>());
  NT2_TEST_EQUAL(exponent(boost::simd::Mone<T>()), boost::simd::Zero<r_t>());
  NT2_TEST_EQUAL(exponent(boost::simd::One<T>()), boost::simd::Zero<r_t>());
  NT2_TEST_EQUAL(exponent(boost::simd::Zero<T>()), boost::simd::Zero<r_t>());
} // end of test for floating_
