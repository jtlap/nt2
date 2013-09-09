//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <boost/simd/include/constants/eps_related.hpp>
#include <boost/simd/include/functions/splat.hpp>
#include <boost/simd/sdk/simd/native.hpp>
#include <boost/simd/sdk/simd/io.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>

#include "../constant.hpp"

// floating point underflow when inputting Mindenormal value
#ifdef __ICC
#pragma warning(disable: 239)
#endif

NT2_TEST_CASE_TPL( eps_value, BOOST_SIMD_SIMD_TYPES )
{
  typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef boost::simd::native<T,ext_t>  n_t;

  NT2_CHECK_CONSTANT(Eps            , boost::simd::Eps<T>()           , n_t);
  NT2_CHECK_CONSTANT(Halfeps        , boost::simd::Halfeps<T>()       , n_t);
  NT2_CHECK_CONSTANT(Threeeps       , boost::simd::Threeeps<T>()      , n_t);
  NT2_CHECK_CONSTANT(Sqrteps        , boost::simd::Sqrteps<T>()       , n_t);
  NT2_CHECK_CONSTANT(Fourthrooteps  , boost::simd::Fourthrooteps<T>() , n_t);
  NT2_CHECK_CONSTANT(Thirdrooteps   , boost::simd::Thirdrooteps<T>()  , n_t);
  NT2_CHECK_CONSTANT(Mlogeps2       , boost::simd::Mlogeps2<T>()      , n_t);
  NT2_CHECK_CONSTANT(Smallestposval , boost::simd::Smallestposval<T>(), n_t);
  NT2_CHECK_CONSTANT(Sqrtsmallestposval , boost::simd::Sqrtsmallestposval<T>(), n_t);
  NT2_CHECK_CONSTANT(Mindenormal    , boost::simd::Mindenormal<T>()   , n_t);
}
