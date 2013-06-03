//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/include/constants/digits.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>

#include "../constant.hpp"

#ifdef BOOST_MSVC
  #pragma warning(disable: 4309) // truncation of constant value
#endif

NT2_TEST_CASE_TPL( digit_value, BOOST_SIMD_TYPES(char) )
{
  NT2_CHECK_CONSTANT(Mten     , -10, T);
  NT2_CHECK_CONSTANT(Mnine    , -9 , T);
  NT2_CHECK_CONSTANT(Meight   , -8 , T);
  NT2_CHECK_CONSTANT(Mseven   , -7 , T);
  NT2_CHECK_CONSTANT(Msix     , -6 , T);
  NT2_CHECK_CONSTANT(Mfive    , -5 , T);
  NT2_CHECK_CONSTANT(Mfour    , -4 , T);
  NT2_CHECK_CONSTANT(Mthree   , -3 , T);
  NT2_CHECK_CONSTANT(Mtwo     , -2 , T);
  NT2_CHECK_CONSTANT(Mone     , -1 , T);
  NT2_CHECK_CONSTANT(Zero     ,  0 , T);
  NT2_CHECK_CONSTANT(One      ,  1 , T);
  NT2_CHECK_CONSTANT(Two      ,  2 , T);
  NT2_CHECK_CONSTANT(Three    ,  3 , T);
  NT2_CHECK_CONSTANT(Four     ,  4 , T);
  NT2_CHECK_CONSTANT(Five     ,  5 , T);
  NT2_CHECK_CONSTANT(Six      ,  6 , T);
  NT2_CHECK_CONSTANT(Seven    ,  7 , T);
  NT2_CHECK_CONSTANT(Eight    ,  8 , T);
  NT2_CHECK_CONSTANT(Nine     ,  9 , T);
  NT2_CHECK_CONSTANT(Ten      , 10 , T);
  NT2_CHECK_CONSTANT(Eleven   , 11 , T);
  NT2_CHECK_CONSTANT(Twelve   , 12 , T);
  NT2_CHECK_CONSTANT(Fifteen  , 15 , T);
  NT2_CHECK_CONSTANT(Twenty   , 20 , T);
  NT2_CHECK_CONSTANT(Hundred  , 100 , T);
  NT2_CHECK_CONSTANT(Thousand , 1000 , T);
}

NT2_TEST_CASE_TPL( fact_value, BOOST_SIMD_TYPES(char) )
{
  NT2_CHECK_CONSTANT(Fact_4    ,        24, T);
  NT2_CHECK_CONSTANT(Fact_5    ,       120, T);
  NT2_CHECK_CONSTANT(Fact_6    ,       720, T);
  NT2_CHECK_CONSTANT(Fact_7    ,      5040, T);
  NT2_CHECK_CONSTANT(Fact_8    ,     40320, T);
  NT2_CHECK_CONSTANT(Fact_9    ,    362880, T);
  NT2_CHECK_CONSTANT(Fact_10   ,   3628800, T);
  NT2_CHECK_CONSTANT(Fact_11   ,  39916800, T);
  NT2_CHECK_CONSTANT(Fact_12   , 479001600, T);
}

NT2_TEST_CASE_TPL( integral_constant, BOOST_SIMD_INTEGRAL_TYPES(char) )
{
  NT2_TEST_EXPR_TYPE((nt2::integral_constant<T,42>()), boost::mpl::_, T);

  NT2_TEST_EQUAL( (nt2::integral_constant<T,42>()), static_cast<T>(42) );
}
