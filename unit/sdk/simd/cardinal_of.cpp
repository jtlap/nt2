/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#define NT2_UNIT_MODULE "nt2::meta::cardinal_of SIMD"

#include <nt2/sdk/simd/native.hpp>
#include <nt2/sdk/meta/cardinal_of.hpp>
#include <boost/type_traits/is_same.hpp>

#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/module.hpp>

////////////////////////////////////////////////////////////////////////////////
// Test that cardinal_of on SIMD types
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE_TPL(cardinal_of, NT2_SIMD_TYPES )
{
  using nt2::simd::native;
  using nt2::meta::cardinal_of;
  using boost::is_same;

  typedef NT2_SIMD_DEFAULT_EXTENSION      ext_t;
  typedef native<T,ext_t>                 native_t;
  NT2_TEST_EQUAL( (cardinal_of<native_t>::value), NT2_SIMD_BYTES/sizeof(T) );
}
