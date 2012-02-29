//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#define NT2_UNIT_MODULE "boost::simd::meta::make_floating SIMD"

#include <boost/simd/sdk/simd/native.hpp>
#include <boost/simd/sdk/simd/pack.hpp>
#include <boost/dispatch/meta/make_floating.hpp>
#include <boost/type_traits/is_same.hpp>

#include <nt2/sdk/unit/tests/basic.hpp>
#include <nt2/sdk/unit/module.hpp>

////////////////////////////////////////////////////////////////////////////////
// Test that make_floating on SIMD
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE_TPL(make_real_simd_native, BOOST_SIMD_REAL_TYPES)
{
  using boost::simd::native;
  using boost::dispatch::meta::make_floating;
  using boost::is_same;

  typedef BOOST_SIMD_DEFAULT_EXTENSION                ext_t;
  typedef native<typename make_floating<sizeof(T)>::type,ext_t> dst_t;
  typedef typename boost::dispatch::meta::factory_of<dst_t>::type fact_t;

  NT2_TEST( (is_same< typename make_floating<sizeof(T), fact_t>::type
                    , dst_t
                    >::value
            )
          );
}

////////////////////////////////////////////////////////////////////////////////
// Test that make_floating on pack
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE_TPL(make_real_simd, BOOST_SIMD_REAL_TYPES)
{
  using boost::simd::pack;
  using boost::dispatch::meta::make_floating;
  using boost::is_same;

  typedef pack<typename make_floating<sizeof(T)>::type>            dst_t;
  typedef typename boost::dispatch::meta::factory_of<dst_t>::type fact_t;

  NT2_TEST( (is_same< typename make_floating<sizeof(T), fact_t>::type
                    , dst_t
                    >::value
            )
          );
}
