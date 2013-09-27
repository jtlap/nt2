//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <boost/simd/bitwise/include/functions/ilog10.hpp>
#include <boost/dispatch/functor/meta/call.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <boost/simd/include/constants/two.hpp>
#include <boost/simd/include/constants/one.hpp>
#include <boost/simd/include/constants/mone.hpp>
#include <boost/simd/include/constants/inf.hpp>
#include <boost/simd/include/constants/minf.hpp>
#include <boost/simd/include/constants/nan.hpp>
#include <boost/simd/sdk/config.hpp>
#include <math.h>

// NT2_TEST_CASE_TPL ( ilog10_real,  BOOST_SIMD_REAL_TYPES)
// {

//   using boost::simd::ilog10;
//   using boost::simd::tag::ilog10_;
//   typedef typename boost::dispatch::meta::call<ilog10_(T)>::type r_t;
//   typedef typename boost::dispatch::meta::as_integer<T>::type wished_r_t;


//   // return type conformity test
//   NT2_TEST_TYPE_IS(r_t, wished_r_t);

//   // specific values tests
//   NT2_TEST_EQUAL(ilog10(boost::simd::Two<T>()), 1);
//   NT2_TEST_EQUAL(ilog10(boost::simd::Three<T>()), 1);
//   NT2_TEST_EQUAL(ilog10(boost::simd::Four<T> ()), 1);
//   NT2_TEST_EQUAL(ilog10(boost::simd::Pi<T> ()), 1);
//   NT2_TEST_EQUAL(ilog10(boost::simd::One<T>()), 0);
// } // end of test for real_

// NT2_TEST_CASE_TPL ( ilog10_signed_int,  BOOST_SIMD_INTEGRAL_SIGNED_TYPES)
// {

//   using boost::simd::ilog10;
//   using boost::simd::tag::ilog10_;
//   typedef typename boost::dispatch::meta::call<ilog10_(T)>::type r_t;
//   typedef typename boost::dispatch::meta::as_integer<T>::type wished_r_t;

//   // return type conformity test
//   NT2_TEST_TYPE_IS(r_t, wished_r_t);

//   // specific values tests
//   NT2_TEST_EQUAL(ilog10(boost::simd::One<T>()), 0);
//   NT2_TEST_EQUAL(ilog10(boost::simd::Two<T>()), 1);
// } // end of test for signed_int_

NT2_TEST_CASE_TPL ( ilog10_unsigned_int,  BOOST_SIMD_UNSIGNED_TYPES)
 {

  using boost::simd::ilog10;
  using boost::simd::tag::ilog10_;
  typedef typename boost::dispatch::meta::call<ilog10_(T)>::type r_t;
  typedef typename boost::dispatch::meta::as_integer<T, unsigned>::type wished_r_t;

  // return type conformity test
  NT2_TEST_TYPE_IS(r_t, wished_r_t);

  // specific values tests
//   NT2_TEST_EQUAL(ilog10(boost::simd::One<T>()), 0u);
//   NT2_TEST_EQUAL(ilog10(boost::simd::Two<T>()),1u);

  T j = 0;
  for(T i=1; i < boost::simd::Valmax<T>()/10; i*= 10)
    {
      std::cout << "i = " << i << " j = " <<  j << " log10 = " << ::log10(double(i)) << std::endl;
      NT2_TEST_EQUAL(ilog10(T(i)),j);
      NT2_TEST_EQUAL(ilog10(T(i+1)),j);
      ++j;
    }
 } // end of test for unsigned_int_
