/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#define NT2_UNIT_MODULE "boost::simd::meta::cardinal_of SIMD"

#include <boost/simd/sdk/simd/native.hpp>
#include <boost/simd/sdk/simd/pack.hpp>
#include <boost/simd/sdk/meta/cardinal_of.hpp>
#include <boost/type_traits/is_same.hpp>

#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/module.hpp>

////////////////////////////////////////////////////////////////////////////////
// Test that cardinal_of on SIMD types
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE_TPL(cardinal_of_native, BOOST_SIMD_SIMD_TYPES )
{
  using boost::simd::native;
  using boost::simd::meta::cardinal_of;
  using boost::is_same;

  typedef BOOST_SIMD_DEFAULT_EXTENSION      ext_t;
  typedef native<T,ext_t>                 native_t;
  std::cout << ( (cardinal_of<native_t>::value) == BOOST_SIMD_BYTES/sizeof(T) ) << std::endl;
  NT2_TEST_EQUAL( (cardinal_of<native_t>::value), BOOST_SIMD_BYTES/sizeof(T) );
}

NT2_TEST_CASE_TPL(cardinal_of_pack, BOOST_SIMD_SIMD_TYPES )
{
  using boost::simd::pack;
  using boost::simd::meta::cardinal_of;
  using boost::is_same;

  typedef pack<T> pack_;
  NT2_TEST_EQUAL( (cardinal_of<pack_>::value), BOOST_SIMD_BYTES/sizeof(T) );
  std::cout << ( (cardinal_of<pack_>::value) == BOOST_SIMD_BYTES/sizeof(T) ) << std::endl;
}

NT2_TEST_CASE_TPL(cardinal_of_cref, BOOST_SIMD_TYPES)
{
  using boost::simd::native;
  using boost::simd::meta::cardinal_of;

  typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef native<T,ext_t>               n_t;

  NT2_TEST_EQUAL( cardinal_of<n_t&>::value      , cardinal_of<n_t>::value );
  NT2_TEST_EQUAL( cardinal_of<n_t const>::value , cardinal_of<n_t>::value );
  NT2_TEST_EQUAL( cardinal_of<n_t const&>::value, cardinal_of<n_t>::value );
}
