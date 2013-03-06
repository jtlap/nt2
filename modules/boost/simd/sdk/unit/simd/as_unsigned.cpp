//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#define NT2_UNIT_MODULE "boost::simd::meta::as_unsigned SIMD"

#include <boost/simd/sdk/simd/native.hpp>
#include <boost/simd/sdk/simd/pack.hpp>
#include <boost/dispatch/meta/as_unsigned.hpp>
#include <boost/type_traits/is_same.hpp>

#include <nt2/sdk/unit/tests/basic.hpp>
#include <nt2/sdk/unit/module.hpp>

////////////////////////////////////////////////////////////////////////////////
// Test that as_unsigned is correct on ntive
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE_TPL(as_unsigned_native, BOOST_SIMD_TYPES)
{
	using boost::simd::native;
  using boost::dispatch::meta::as_unsigned;
  using boost::is_same;
  using boost::mpl::_;

  typedef BOOST_SIMD_DEFAULT_EXTENSION                ext_t;
  typedef native<typename as_unsigned<T>::type,ext_t> dst_t;

  NT2_TEST( (is_same< typename as_unsigned< native<T,ext_t> >::type, dst_t>::value	));
}

////////////////////////////////////////////////////////////////////////////////
// Test that as_unsigned is correct on pack
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE_TPL(as_unsigned_pack, BOOST_SIMD_TYPES)
{
  using boost::simd::pack;
  using boost::dispatch::meta::as_unsigned;
  using boost::is_same;
  using boost::mpl::_;

  typedef pack<typename as_unsigned<T>::type> dst_t;

  NT2_TEST( (is_same< typename as_unsigned< pack<T> >::type, dst_t>::value  ));
}
