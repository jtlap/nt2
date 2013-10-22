//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <boost/simd/boolean/include/functions/mask2logical.hpp>
#include <boost/simd/sdk/simd/io.hpp>
#include <boost/dispatch/meta/as_integer.hpp>
#include <boost/simd/sdk/meta/as_logical.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>

#include <boost/simd/include/constants/one.hpp>
#include <boost/simd/include/constants/mone.hpp>
#include <boost/simd/include/constants/zero.hpp>
#include <boost/simd/include/constants/nan.hpp>
#include <boost/simd/include/constants/false.hpp>
#include <boost/simd/include/constants/true.hpp>


NT2_TEST_CASE_TPL ( mask2logical_real,  BOOST_SIMD_REAL_TYPES)
{

  using boost::simd::mask2logical;
  using boost::simd::tag::mask2logical_;
  using boost::simd::logical;
  typedef typename boost::dispatch::meta::call<mask2logical_(T)>::type r_t;
  typedef logical<T> lT;

  // return type conformity test
  NT2_TEST_TYPE_IS( r_t, lT );

  // specific values tests
  NT2_TEST_EQUAL(mask2logical(T(0)), boost::simd::False<lT>());
  NT2_TEST_EQUAL(mask2logical(boost::simd::Nan<T>()) , boost::simd::True<lT>());
} // end of test for floating_

NT2_TEST_CASE_TPL ( mask2logical_signed_int,  BOOST_SIMD_INTEGRAL_SIGNED_TYPES)
{

  using boost::simd::mask2logical;
  using boost::simd::tag::mask2logical_;
  using boost::simd::logical;
  typedef typename boost::dispatch::meta::call<mask2logical_(T)>::type r_t;
  typedef logical<T> lT;

  // return type conformity test
  NT2_TEST_TYPE_IS( r_t, lT );

  // specific values tests
  NT2_TEST_EQUAL(mask2logical(T(0)), boost::simd::False<lT>());
  NT2_TEST_EQUAL(mask2logical(T(-1)), boost::simd::True<lT>());
} // end of test for signed_int_

