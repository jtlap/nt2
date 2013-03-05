//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#define NT2_UNIT_MODULE "boost::simd::meta::as_integer SIMD"

#include <boost/simd/sdk/simd/native.hpp>
#include <boost/simd/sdk/simd/pack.hpp>
#include <boost/dispatch/meta/as_integer.hpp>
#include <boost/type_traits/is_same.hpp>

#include <nt2/sdk/unit/tests/basic.hpp>
#include <nt2/sdk/unit/module.hpp>

////////////////////////////////////////////////////////////////////////////////
// Test that as_integer on SIMD with unsigned target
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE_TPL(as_uinteger_simd_native, BOOST_SIMD_TYPES)
{
  using boost::simd::native;
  using boost::dispatch::meta::as_integer;
  using boost::is_same;
  using boost::mpl::_;

  typedef BOOST_SIMD_DEFAULT_EXTENSION                ext_t;
  typedef native<typename as_integer<T,unsigned>::type,ext_t> dst_t;

  NT2_TEST( (is_same< typename as_integer<native<T,ext_t>,unsigned>::type
                    , dst_t
                    >::value
            )
          );
}

////////////////////////////////////////////////////////////////////////////////
// Test that as_integer on pack with signed target
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE_TPL(as_integer_simd_pack, BOOST_SIMD_TYPES)
{
  using boost::simd::pack;
  using boost::dispatch::meta::as_integer;
  using boost::is_same;
  using boost::mpl::_;

  typedef pack<typename as_integer<T,signed>::type>   dst_t;

  NT2_TEST( (is_same< typename as_integer< pack<T>,signed >::type
                    , dst_t
                    >::value
            )
          );
}
