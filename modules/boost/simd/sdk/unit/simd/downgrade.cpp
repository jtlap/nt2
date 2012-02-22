/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#define NT2_UNIT_MODULE "boost::simd::meta::downgrade SIMD"

#include <boost/simd/sdk/simd/pack.hpp>
#include <boost/simd/sdk/simd/logical.hpp>
#include <boost/simd/sdk/simd/native.hpp>
#include <boost/dispatch/meta/downgrade.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>

#include <nt2/sdk/unit/tests/basic.hpp>
#include <nt2/sdk/unit/module.hpp>

////////////////////////////////////////////////////////////////////////////////
// Test that downgrade is correct for SIMD types
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE_TPL(downgrade_native, BOOST_SIMD_TYPES)
{
  using boost::simd::native;
  using boost::dispatch::meta::downgrade;
  using boost::mpl::_;

  typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef native<T,ext_t>             native_t;
  typedef typename downgrade<T>::type   base_t;

  native_t a0; 
  NT2_TEST_EXPR_TYPE( a0, downgrade<_>, (native<base_t,ext_t>) );
}

////////////////////////////////////////////////////////////////////////////////
// Test that downgrade is correct for SIMD logical types
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE_TPL(downgrade_logical_native, BOOST_SIMD_TYPES)
{
  using boost::simd::logical;
  using boost::simd::native;
  using boost::dispatch::meta::downgrade;
  using boost::mpl::_;

  typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef native<logical<T>,ext_t>      native_t;
  typedef typename downgrade<T>::type   base_t;

  native_t a0; 
  NT2_TEST_EXPR_TYPE( a0, downgrade<_>, (native<logical<base_t>,ext_t>) );
}

////////////////////////////////////////////////////////////////////////////////
// Test that downgrade is correct for SIMD pack types
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE_TPL(downgrade_pack, BOOST_SIMD_TYPES)
{
  using boost::simd::pack;
  using boost::dispatch::meta::downgrade;
  using boost::mpl::_;

  typedef BOOST_SIMD_DEFAULT_EXTENSION      ext_t;
  typedef pack<T>                           pack_t;
  typedef typename downgrade<T>::type       base_t;

  pack_t a0;
  NT2_TEST_EXPR_TYPE( a0, downgrade<_>, pack<base_t> );
}

////////////////////////////////////////////////////////////////////////////////
// Test that downgrade is correct for SIMD logical pack types
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE_TPL(downgrade_logical_pack, BOOST_SIMD_TYPES)
{
  using boost::simd::logical;
  using boost::simd::pack;
  using boost::dispatch::meta::downgrade;
  using boost::mpl::_;

  typedef BOOST_SIMD_DEFAULT_EXTENSION      ext_t;
  typedef pack< logical<T> >                pack_t;
  typedef typename downgrade<T>::type       base_t;

  pack_t a0;
  NT2_TEST_EXPR_TYPE( a0, downgrade<_>, pack< logical<base_t> > );
}
