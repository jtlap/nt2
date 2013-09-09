//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/include/constants/eps_related.hpp>
#include <nt2/include/functions/splat.hpp>
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

  NT2_CHECK_CONSTANT(Eps            , nt2::Eps<T>()           , n_t);
  NT2_CHECK_CONSTANT(Halfeps        , nt2::Halfeps<T>()       , n_t);
  NT2_CHECK_CONSTANT(Threeeps       , nt2::Threeeps<T>()      , n_t);
  NT2_CHECK_CONSTANT(Sqrteps        , nt2::Sqrteps<T>()       , n_t);
  NT2_CHECK_CONSTANT(Fourthrooteps  , nt2::Fourthrooteps<T>() , n_t);
  NT2_CHECK_CONSTANT(Thirdrooteps   , nt2::Thirdrooteps<T>()  , n_t);
  NT2_CHECK_CONSTANT(Mlogeps2       , nt2::Mlogeps2<T>()      , n_t);
  NT2_CHECK_CONSTANT(Smallestposval , nt2::Smallestposval<T>(), n_t);
  NT2_CHECK_CONSTANT(Sqrtsmallestposval , nt2::Sqrtsmallestposval<T>(), n_t);
  NT2_CHECK_CONSTANT(Mindenormal    , nt2::Mindenormal<T>()   , n_t);
}
