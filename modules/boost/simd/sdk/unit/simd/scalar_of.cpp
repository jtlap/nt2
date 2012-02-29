/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#define NT2_UNIT_MODULE "boost::simd::meta::scalar_of SIMD"

#include <boost/simd/sdk/simd/logical.hpp>
#include <boost/simd/sdk/simd/native.hpp>
#include <boost/simd/sdk/simd/pack.hpp>
#include <boost/dispatch/meta/scalar_of.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>

#include <nt2/sdk/unit/tests/basic.hpp>
#include <nt2/sdk/unit/module.hpp>

////////////////////////////////////////////////////////////////////////////////
// Test that scalar_of on native
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE_TPL(scalar_of_native, BOOST_SIMD_TYPES)
{
  using boost::simd::native;
  using boost::dispatch::meta::scalar_of;
  using boost::mpl::_;

  typedef BOOST_SIMD_DEFAULT_EXTENSION      ext_t;
  typedef native<T,ext_t>                 native_t;

  native_t a0;
  NT2_TEST_EXPR_TYPE( a0, scalar_of<_>, T );
}

////////////////////////////////////////////////////////////////////////////////
// Test that scalar_of on native
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE_TPL(scalar_of_logical_native, BOOST_SIMD_TYPES)
{
  using boost::simd::native;
  using boost::simd::logical;
  using boost::dispatch::meta::scalar_of;
  using boost::mpl::_;

  typedef BOOST_SIMD_DEFAULT_EXTENSION      ext_t;
  typedef native<logical<T>,ext_t>                 native_t;

  native_t a0;
  NT2_TEST_EXPR_TYPE( a0, scalar_of<_>, logical<T> );
}

////////////////////////////////////////////////////////////////////////////////
// Test that scalar_of on pack
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE_TPL(scalar_of_logical_pack, BOOST_SIMD_TYPES)
{
  using boost::simd::pack;
  using boost::simd::logical;
  using boost::dispatch::meta::scalar_of;
  using boost::mpl::_;

  typedef pack< logical<T> > pack_t;

  pack_t a0;
  NT2_TEST_EXPR_TYPE( a0, scalar_of<_>, logical<T> );
}


////////////////////////////////////////////////////////////////////////////////
// Test that scalar_of on pack
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE_TPL(scalar_of_pack, BOOST_SIMD_TYPES)
{
  using boost::simd::pack;
  using boost::simd::logical;
  using boost::dispatch::meta::scalar_of;
  using boost::mpl::_;

  typedef pack<T> pack_t;

  pack_t a0;
  NT2_TEST_EXPR_TYPE( a0, scalar_of<_>, T );
}
