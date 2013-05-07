//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#define NT2_UNIT_MODULE "boost::simd::meta::is_signed SIMD"

#include <boost/simd/sdk/simd/native.hpp>
#include <boost/simd/sdk/simd/pack.hpp>
#include <boost/dispatch/meta/is_signed.hpp>
#include <boost/type_traits/is_same.hpp>

#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/module.hpp>

////////////////////////////////////////////////////////////////////////////////
// Test that is_signed on SIMD
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE_TPL(is_signed_simd_native, BOOST_SIMD_TYPES)
{
  using boost::simd::native;
  using boost::dispatch::meta::is_signed;
  using boost::is_same;

  typedef BOOST_SIMD_DEFAULT_EXTENSION      ext_t;
  typedef native<T,ext_t>                 native_t;

  NT2_TEST_EQUAL( is_signed<native_t>::value, is_signed<T>::value );
}

////////////////////////////////////////////////////////////////////////////////
// Test that is_signed on pack
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE_TPL(is_signed_simd_pack, BOOST_SIMD_TYPES)
{
  using boost::simd::pack;
  using boost::dispatch::meta::is_signed;
  using boost::is_same;

  typedef pack<T>                          pack_t;

  NT2_TEST_EQUAL( is_signed<pack_t>::value, is_signed<T>::value );
}
