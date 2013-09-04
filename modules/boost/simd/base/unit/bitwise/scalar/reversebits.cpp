//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <boost/simd/bitwise/include/functions/reversebits.hpp>
#include <boost/dispatch/functor/meta/call.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <boost/simd/include/constants/zero.hpp>
#include <boost/simd/include/constants/one.hpp>
#include <boost/simd/include/constants/mone.hpp>
#include <boost/simd/include/constants/nan.hpp>
#include <boost/simd/sdk/config.hpp>

NT2_TEST_CASE_TPL ( reversebits_integer,  BOOST_SIMD_INTEGRAL_TYPES)
{

  using boost::simd::reversebits;
  using boost::simd::tag::reversebits_;
  typedef typename boost::dispatch::meta::call<reversebits_(T)>::type r_t;
  typedef T wished_r_t;

  // return type conformity test
  NT2_TEST_TYPE_IS(r_t, wished_r_t);

  // specific values tests
  NT2_TEST_EQUAL(reversebits(boost::simd::Mone<T>()), boost::simd::Mone<r_t>());
  NT2_TEST_EQUAL(reversebits(boost::simd::One<T>()), r_t(boost::simd::One<r_t>()<<(sizeof(r_t)*8-1)));
  NT2_TEST_EQUAL(reversebits(boost::simd::Zero<T>()), boost::simd::Zero<r_t>());
} // end of test for integer_
