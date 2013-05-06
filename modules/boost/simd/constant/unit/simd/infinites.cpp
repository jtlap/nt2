//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <boost/simd/include/constants/infinites.hpp>
#include <boost/simd/include/constants/properties.hpp>
#include <boost/simd/include/functions/splat.hpp>
#include <boost/simd/sdk/simd/native.hpp>
#include <boost/simd/sdk/simd/io.hpp>
#include <limits>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>

#include "../constant.hpp"

NT2_TEST_CASE_TPL( real_inf, BOOST_SIMD_REAL )
{
  typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef boost::simd::native<T,ext_t>  n_t;

  NT2_CHECK_CONSTANT(Inf  ,   std::numeric_limits<T>::infinity(), n_t);
  NT2_CHECK_CONSTANT(Minf ,  -std::numeric_limits<T>::infinity(), n_t);
}

NT2_TEST_CASE_TPL( int_inf, BOOST_SIMD_INTEGRAL_TYPES(char) )
{
  typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef boost::simd::native<T,ext_t>  n_t;

  NT2_CHECK_CONSTANT(Inf  , boost::simd::Valmax<T>(), n_t);
  NT2_CHECK_CONSTANT(Minf , boost::simd::Valmin<T>(), n_t);
}

