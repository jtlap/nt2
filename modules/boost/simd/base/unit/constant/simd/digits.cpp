//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#define NT2_UNIT_MODULE "boost::simd::constants digits"

#include <boost/simd/include/constants/digits.hpp>
#include <boost/simd/include/functions/splat.hpp>
#include <boost/simd/sdk/simd/native.hpp>
#include <boost/simd/sdk/simd/io.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>

#include "../constant.hpp"

NT2_TEST_CASE_TPL( digit_value, BOOST_SIMD_SIMD_TYPES )
{
  typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef boost::simd::native<T,ext_t>  n_t;

  NT2_CHECK_CONSTANT(Mten     , -10  , n_t);
  NT2_CHECK_CONSTANT(Mnine    , -9   , n_t);
  NT2_CHECK_CONSTANT(Meight   , -8   , n_t);
  NT2_CHECK_CONSTANT(Mseven   , -7   , n_t);
  NT2_CHECK_CONSTANT(Msix     , -6   , n_t);
  NT2_CHECK_CONSTANT(Mfive    , -5   , n_t);
  NT2_CHECK_CONSTANT(Mfour    , -4   , n_t);
  NT2_CHECK_CONSTANT(Mthree   , -3   , n_t);
  NT2_CHECK_CONSTANT(Mtwo     , -2   , n_t);
  NT2_CHECK_CONSTANT(Mone     , -1   , n_t);
  NT2_CHECK_CONSTANT(Zero     ,  0   , n_t);
  NT2_CHECK_CONSTANT(One      ,  1   , n_t);
  NT2_CHECK_CONSTANT(Two      ,  2   , n_t);
  NT2_CHECK_CONSTANT(Three    ,  3   , n_t);
  NT2_CHECK_CONSTANT(Four     ,  4   , n_t);
  NT2_CHECK_CONSTANT(Five     ,  5   , n_t);
  NT2_CHECK_CONSTANT(Six      ,  6   , n_t);
  NT2_CHECK_CONSTANT(Seven    ,  7   , n_t);
  NT2_CHECK_CONSTANT(Eight    ,  8   , n_t);
  NT2_CHECK_CONSTANT(Nine     ,  9   , n_t);
  NT2_CHECK_CONSTANT(Ten      , 10   , n_t);
  NT2_CHECK_CONSTANT(Eleven   , 11   , n_t);
  NT2_CHECK_CONSTANT(Twelve   , 12   , n_t);
  NT2_CHECK_CONSTANT(Fifteen  , 15   , n_t);
  NT2_CHECK_CONSTANT(Twenty   , 20   , n_t);
  NT2_CHECK_CONSTANT(Hundred  , 100  , n_t);
  NT2_CHECK_CONSTANT(Thousand , 1000 , n_t);
}

NT2_TEST_CASE_TPL( fact_value, BOOST_SIMD_SIMD_TYPES )
{
  typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef boost::simd::native<T,ext_t>  n_t;

  NT2_CHECK_CONSTANT(Fact_4    ,        24, n_t);
  NT2_CHECK_CONSTANT(Fact_5    ,       120, n_t);
  NT2_CHECK_CONSTANT(Fact_6    ,       720, n_t);
  NT2_CHECK_CONSTANT(Fact_7    ,      5040, n_t);
  NT2_CHECK_CONSTANT(Fact_8    ,     40320, n_t);
  NT2_CHECK_CONSTANT(Fact_9    ,    362880, n_t);
  NT2_CHECK_CONSTANT(Fact_10   ,   3628800, n_t);
  NT2_CHECK_CONSTANT(Fact_11   ,  39916800, n_t);
  NT2_CHECK_CONSTANT(Fact_12   , 479001600, n_t);
}

NT2_TEST_CASE_TPL( integral_constant, BOOST_SIMD_SIMD_INTEGRAL_TYPES )
{
  typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef boost::simd::native<T,ext_t>  n_t;

  NT2_TEST_EXPR_TYPE( (boost::simd::integral_constant<n_t,42>())
                    , boost::mpl::_
                    , n_t
                    );

  NT2_TEST_EQUAL( (boost::simd::integral_constant<n_t,42>())
                , boost::simd::splat<n_t>(42)
                );
}
