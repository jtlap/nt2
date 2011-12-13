//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#define NT2_UNIT_MODULE "boost::simd::meta::sign_of SIMD"

#include <boost/simd/sdk/simd/native.hpp>
#include <boost/simd/sdk/simd/logical.hpp>
#include <boost/simd/sdk/simd/pack.hpp>
#include <boost/dispatch/meta/sign_of.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>
#include <nt2/sdk/unit/tests/basic.hpp>
#include <nt2/sdk/unit/module.hpp>

////////////////////////////////////////////////////////////////////////////////
// Test that sign_of on SIMD
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE_TPL(sign_of_simd_native, BOOST_SIMD_TYPES)
{
  using boost::simd::native;
  using boost::dispatch::meta::sign_of;
  using boost::mpl::_;

  typedef BOOST_SIMD_DEFAULT_EXTENSION      ext_t;
  typedef native<T,ext_t>                 native_t;

  native_t a0;
  NT2_TEST_EXPR_TYPE( a0, sign_of<_>, typename sign_of<T>::type );
}

////////////////////////////////////////////////////////////////////////////////
// Test that sign_of on SIMD logical
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE_TPL(sign_of_simd_native_logical, BOOST_SIMD_TYPES)
{
  using boost::simd::logical;
  using boost::simd::native;
  using boost::dispatch::meta::sign_of;
  using boost::mpl::_;

  typedef BOOST_SIMD_DEFAULT_EXTENSION      ext_t;
  typedef native<logical<T>,ext_t>          native_t;

  native_t a0;
  NT2_TEST_EXPR_TYPE( a0, sign_of<_>, typename sign_of< T>::type );
}

////////////////////////////////////////////////////////////////////////////////
// Test that scalar_of on pack
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE_TPL(sign_of_simd, BOOST_SIMD_TYPES)
{
  using boost::simd::pack;
  using boost::dispatch::meta::sign_of;
  using boost::mpl::_;

  typedef BOOST_SIMD_DEFAULT_EXTENSION      ext_t;
  typedef pack<T>                          pack_t;

  pack_t a0;
  NT2_TEST_EXPR_TYPE( a0, sign_of<_>, typename sign_of<T>::type );
}


////////////////////////////////////////////////////////////////////////////////
// Test that scalar_of on logical pack
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE_TPL(sign_of_logical_simd, BOOST_SIMD_TYPES)
{
  using boost::simd::pack;
  using boost::simd::logical;
  using boost::dispatch::meta::sign_of;
  using boost::mpl::_;

  typedef BOOST_SIMD_DEFAULT_EXTENSION      ext_t;
  typedef pack< logical<T> >                pack_t;

  pack_t a0;
  NT2_TEST_EXPR_TYPE( a0, sign_of<_>, typename sign_of<T>::type );
}
