//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <boost/simd/include/constants/eps_related.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>

#include "../constant.hpp"

 // floating point underflow when inputting Mindenormal value
#ifdef __ICC
#pragma warning(disable: 239)
#endif

NT2_TEST_CASE( double_eps_value )
{
  NT2_CHECK_CONSTANT(Eps            , 2.220446049250313e-16   , double);
  NT2_CHECK_CONSTANT(Halfeps        , 1.1102230246251565e-16  , double);
  NT2_CHECK_CONSTANT(Threeeps       , 6.661338147750939e-16   , double);
  NT2_CHECK_CONSTANT(Sqrteps        , 1.4901161193847656e-8   , double);
  NT2_CHECK_CONSTANT(Fourthrooteps  , 1.2207031250000000e-4   , double);
  NT2_CHECK_CONSTANT(Thirdrooteps   , 6.0554544523933440e-6   , double);
  NT2_CHECK_CONSTANT(Mlogeps2       , 18.021826694558580      , double);
  NT2_CHECK_CONSTANT(Smallestposval , 2.2250738585072014e-308 , double);
  NT2_CHECK_CONSTANT(Sqrtsmallestposval , 1.4916681462400413487e-154 , double);

  #ifdef BOOST_SIMD_NO_DENORMALS
  NT2_CHECK_CONSTANT(Mindenormal    , 2.2250738585072014e-308 , double);
  #else
  NT2_CHECK_CONSTANT(Mindenormal    , 5.0000000000000000e-324 , double);
  #endif
}

NT2_TEST_CASE( float_eps_value )
{
  NT2_CHECK_CONSTANT(Eps            , 1.1920928955078125e-7   , float);
  NT2_CHECK_CONSTANT(Halfeps        , 5.960464477539063e-8    , float);
  NT2_CHECK_CONSTANT(Threeeps       , 3.5762786865234375e-7   , float);
  NT2_CHECK_CONSTANT(Sqrteps        , 0.0003452669770922512   , float);
  NT2_CHECK_CONSTANT(Fourthrooteps  , 0.018581360578536987    , float);
  NT2_CHECK_CONSTANT(Thirdrooteps   , 0.004921566694974899    , float);
  NT2_CHECK_CONSTANT(Mlogeps2       , 7.971192359924316       , float);
  NT2_CHECK_CONSTANT(Smallestposval , 1.1754943508222875e-38  , float);
  NT2_CHECK_CONSTANT(Sqrtsmallestposval , 1.084202172485504434e-19, float);

  #ifdef BOOST_SIMD_NO_DENORMALS
  NT2_CHECK_CONSTANT(Mindenormal    , 1.1754943508222875e-38  , float);
  #else
  NT2_CHECK_CONSTANT(Mindenormal    , 1.401298464324817e-45   , float);
  #endif
}

NT2_TEST_CASE_TPL( real_value, BOOST_SIMD_INTEGRAL_TYPES )
{
  NT2_CHECK_CONSTANT(Eps            , T(1), T);
  NT2_CHECK_CONSTANT(Halfeps        , T(1), T);
  NT2_CHECK_CONSTANT(Threeeps       , T(3), T);
  NT2_CHECK_CONSTANT(Sqrteps        , T(1), T);
  NT2_CHECK_CONSTANT(Fourthrooteps  , T(1), T);
  NT2_CHECK_CONSTANT(Thirdrooteps   , T(1), T);
  NT2_CHECK_CONSTANT(Mlogeps2       , T(0), T);
  NT2_CHECK_CONSTANT(Smallestposval , T(1), T);
  NT2_CHECK_CONSTANT(Mindenormal    , T(1), T);
}
