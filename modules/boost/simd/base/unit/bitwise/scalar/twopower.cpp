//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <boost/simd/bitwise/include/functions/twopower.hpp>
#include <boost/simd/sdk/simd/io.hpp>
#include <boost/dispatch/meta/as_integer.hpp>
#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>
#include <boost/simd/include/constants/one.hpp>
#include <boost/simd/include/constants/zero.hpp>


NT2_TEST_CASE_TPL ( twopower_ui,  BOOST_SIMD_UNSIGNED_TYPES)
{

  using boost::simd::twopower;
  using boost::simd::tag::twopower_;
  typedef typename boost::dispatch::meta::call<twopower_(T)>::type r_t;
  typedef typename boost::common_type<T>::type wished_r_t;

  // return type conformity test
  NT2_TEST_TYPE_IS( r_t, wished_r_t );

  // specific values tests
  NT2_TEST_EQUAL(twopower(boost::simd::Zero<T>()), boost::simd::One<r_t>());

  for(unsigned int i=0; i < sizeof(T)*8 ; i++)
 {
   NT2_TEST_EQUAL(twopower(T(i)), T(1) << i);
 }
} // end of test for unsigned_int_

NT2_TEST_CASE_TPL ( twopower_si,  BOOST_SIMD_INTEGRAL_SIGNED_TYPES)
{

  using boost::simd::twopower;
  using boost::simd::tag::twopower_;
  typedef typename boost::dispatch::meta::call<twopower_(T)>::type r_t;
  typedef T wished_r_t;

  // return type conformity test
  NT2_TEST_TYPE_IS( r_t, wished_r_t );

  // specific values tests
  NT2_TEST_EQUAL(twopower(boost::simd::Zero<T>()), boost::simd::One<r_t>());
  NT2_TEST_EQUAL(twopower(boost::simd::Mone<T>()), boost::simd::Zero<r_t>());

  for(unsigned int i=0; i < sizeof(T)*8-1 ; i++)
  {
    NT2_TEST_EQUAL(twopower(T(i)), T(1) << i);
  }

} // end of test for unsigned_int_
