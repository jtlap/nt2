//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#define NT2_UNIT_MODULE "boost::simd::meta::upgrade SIMD"

#include <boost/simd/sdk/simd/logical.hpp>
#include <boost/simd/sdk/simd/native.hpp>
#include <boost/simd/sdk/simd/pack.hpp>
#include <boost/dispatch/meta/upgrade.hpp>
#include <boost/simd/sdk/meta/cardinal_of.hpp>
#include <boost/type_traits/is_same.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>
#include <nt2/sdk/unit/tests/basic.hpp>
#include <nt2/sdk/unit/module.hpp>

////////////////////////////////////////////////////////////////////////////////
// Test that upgrade is correct for SIMD types
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE_TPL(upgrade_native, BOOST_SIMD_SIMD_SPLITABLE_TYPES)
{
  using boost::simd::native;
  using boost::dispatch::meta::upgrade;
  using boost::simd::meta::vector_of;
  using boost::simd::meta::cardinal_of;
  using boost::mpl::_;

  typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef native<T,ext_t>             native_t;
  typedef typename upgrade<T>::type   base_t;
  typedef typename upgrade<T,unsigned>::type   ubase_t;
  
  typedef typename
  vector_of<base_t, cardinal_of< native_t >::value/2 >::type upgraded_t;

  typedef typename
  vector_of<ubase_t, cardinal_of< native_t >::value/2 >::type uupgraded_t;

  native_t a0;
  NT2_TEST_EXPR_TYPE( a0, upgrade<_>, upgraded_t );
  NT2_TEST_EXPR_TYPE( a0, (upgrade<_,unsigned>), uupgraded_t );
}

////////////////////////////////////////////////////////////////////////////////
// Test that upgrade is correct for SIMD logical types
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE_TPL(upgrade_logical_native, BOOST_SIMD_SIMD_SPLITABLE_TYPES)
{
  using boost::simd::logical;
  using boost::simd::native;
  using boost::dispatch::meta::upgrade;
  using boost::simd::meta::vector_of;
  using boost::simd::meta::cardinal_of;
  using boost::mpl::_;

  typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef native<logical<T>,ext_t>      native_t;
  typedef typename upgrade<T>::type     base_t;
  typedef typename upgrade<T,unsigned>::type   ubase_t;

  typedef typename
  vector_of<base_t, cardinal_of< native< logical<T>, ext_t> >::value/2 >::type upgraded_t;

  typedef typename
  vector_of<ubase_t, cardinal_of< native< logical<T>, ext_t> >::value/2 >::type uupgraded_t;

  native_t a0;

  NT2_TEST_EXPR_TYPE( a0, upgrade<_>, upgraded_t );
  NT2_TEST_EXPR_TYPE( a0, (upgrade<_,unsigned>), uupgraded_t );
}

////////////////////////////////////////////////////////////////////////////////
// Test that upgrade is correct for pack
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE_TPL(upgrade_pack, BOOST_SIMD_SIMD_SPLITABLE_TYPES)
{
  using boost::simd::pack;
  using boost::dispatch::meta::upgrade;
  using boost::simd::meta::vector_of;
  using boost::simd::meta::cardinal_of;
  using boost::mpl::_;

  typedef pack<T>                       pack_t;
  typedef typename upgrade<T>::type     base_t;
  typedef typename upgrade<T,unsigned>::type   ubase_t;

  typedef pack<base_t,  cardinal_of< pack<T> >::value/2> upgraded_t;
  typedef pack<ubase_t, cardinal_of< pack<T> >::value/2> uupgraded_t;

  pack_t a0;
  NT2_TEST_EXPR_TYPE( a0, upgrade<_>, upgraded_t );
  NT2_TEST_EXPR_TYPE( a0, (upgrade<_,unsigned>), uupgraded_t );
}

////////////////////////////////////////////////////////////////////////////////
// Test that upgrade is correct for pack logical types
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE_TPL(upgrade_logical_pack, BOOST_SIMD_SIMD_SPLITABLE_TYPES)
{
  using boost::simd::logical;
  using boost::simd::pack;
  using boost::dispatch::meta::upgrade;
  using boost::simd::meta::vector_of;
  using boost::simd::meta::cardinal_of;
  using boost::mpl::_;

  typedef pack< logical<T> >            pack_t;
  typedef typename upgrade<T>::type     base_t;
  typedef typename upgrade<T,unsigned>::type   ubase_t;

  typedef pack< logical<base_t>,  cardinal_of< pack< logical<T> > >::value/2> upgraded_t;
  typedef pack< logical<ubase_t>, cardinal_of< pack< logical<T> > >::value/2> uupgraded_t;

  pack_t a0;
  NT2_TEST_EXPR_TYPE( a0, upgrade<_>, upgraded_t );
  NT2_TEST_EXPR_TYPE( a0, (upgrade<_,unsigned>), uupgraded_t );
}

