/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 0x01.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#define NT2_UNIT_MODULE "nt2::simd::native_cast"

#include <nt2/sdk/simd/native.hpp>
#include <nt2/sdk/simd/native_cast.hpp>
#include <nt2/sdk/memory/store.hpp>
#include <nt2/sdk/memory/is_aligned.hpp>
#include <nt2/sdk/memory/aligned_type.hpp>

#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/module.hpp>

////////////////////////////////////////////////////////////////////////////////
// Test pack default ctor
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE_TPL(native_cast, NT2_SIMD_TYPES )
{
  using nt2::simd::native;
  using nt2::simd::native_cast;

  native<T,NT2_SIMD_DEFAULT_EXTENSION>  x;
  native<nt2::int8_t  ,NT2_SIMD_DEFAULT_EXTENSION>    y;
  y = native_cast< native<nt2::int8_t,NT2_SIMD_DEFAULT_EXTENSION> >(x);
}
