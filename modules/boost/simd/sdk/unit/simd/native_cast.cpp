/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 0x01.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#define NT2_UNIT_MODULE "boost::simd::native_cast"

#include <boost/simd/sdk/simd/native.hpp>
#include <boost/simd/sdk/simd/native_cast.hpp>
#include <boost/simd/include/functions/store.hpp>
#include <boost/simd/sdk/memory/is_aligned.hpp>
#include <boost/simd/sdk/memory/aligned_type.hpp>

#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/module.hpp>

////////////////////////////////////////////////////////////////////////////////
// Test pack default ctor
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE_TPL(native_cast, BOOST_SIMD_TYPES )
{
  using boost::simd::native;
  using boost::simd::native_cast;

  native<T,BOOST_SIMD_DEFAULT_EXTENSION>  x;
  native<boost::simd::int8_t  ,BOOST_SIMD_DEFAULT_EXTENSION>    y;
  y = native_cast< native<boost::simd::int8_t,BOOST_SIMD_DEFAULT_EXTENSION> >(x);
}
