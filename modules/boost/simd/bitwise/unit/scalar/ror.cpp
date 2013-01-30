//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#define NT2_UNIT_MODULE "nt2 boost.simd.bitwise toolbox - ror/scalar Mode"

//////////////////////////////////////////////////////////////////////////////
// unit test behavior of boost.simd.bitwise components in scalar mode
//////////////////////////////////////////////////////////////////////////////
/// created  by jt the 18/02/2011
///
#include <boost/simd/toolbox/bitwise/include/functions/ror.hpp>
#include <boost/simd/sdk/simd/native.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/dispatch/functor/meta/call.hpp>
#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <boost/simd/toolbox/constant/constant.hpp>


NT2_TEST_CASE_TPL ( ror_integer__2_0,  BOOST_SIMD_INTEGRAL_TYPES)
{

  using boost::simd::ror;
  using boost::simd::tag::ror_;
  typedef typename boost::dispatch::meta::as_integer<T>::type iT;
  typedef typename boost::dispatch::meta::call<ror_(T,iT)>::type r_t;
  typedef typename boost::simd::meta::scalar_of<r_t>::type sr_t;
  typedef typename boost::simd::meta::scalar_of<r_t>::type ssr_t;
  typedef typename boost::dispatch::meta::upgrade<T>::type u_t;
  typedef T wished_r_t;


  // return type conformity test
  NT2_TEST( (boost::is_same < r_t, wished_r_t >::value) );
  std::cout << std::endl;


  // specific values tests
  NT2_TEST_EQUAL(ror(T(2),T(2)), r_t(boost::simd::One<T>()<<(sizeof(T)*8-1)));
  NT2_TEST_EQUAL(ror(boost::simd::Mone<T>(),T(1)), boost::simd::Mone<T>());
  NT2_TEST_EQUAL(ror(boost::simd::Mone<T>(),T(5)), boost::simd::Mone<T>());
  NT2_TEST_EQUAL(ror(boost::simd::One<T>(),T(1)), r_t(boost::simd::One<T>()<<(sizeof(T)*8-1)));
  NT2_TEST_EQUAL(ror(boost::simd::Zero<T>(),T(1)), boost::simd::Zero<T>());
} // end of test for integer_
