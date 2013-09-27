//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <boost/simd/bitwise/include/functions/rshr.hpp>
#include <boost/dispatch/functor/meta/call.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <boost/simd/include/constants/zero.hpp>
#include <boost/simd/include/constants/two.hpp>
#include <boost/simd/include/constants/one.hpp>
#include <boost/simd/sdk/config.hpp>

NT2_TEST_CASE_TPL ( rshr_integer,  BOOST_SIMD_INTEGRAL_TYPES)
{

  using boost::simd::rshr;
  using boost::simd::tag::rshr_;
  typedef typename boost::dispatch::meta::call<rshr_(T,int)>::type r_t;
  typedef T wished_r_t;

  // return type conformity test
  NT2_TEST_TYPE_IS(r_t, wished_r_t);
  std::cout << std::endl;

  // specific values tests
  NT2_TEST_EQUAL(rshr(boost::simd::Zero<T>(), boost::simd::Zero<T>()), boost::simd::Zero<r_t>());
  NT2_TEST_EQUAL(rshr(boost::simd::One<T>(), -1), boost::simd::Two<r_t>());
  NT2_TEST_EQUAL(rshr(boost::simd::One<T>(), 1), boost::simd::Zero<r_t>());
} // end of test for integer_
