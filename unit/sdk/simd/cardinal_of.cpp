/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#define NT2_UNIT_MODULE "nt2::meta::cardinal_of SIMD"

#include <boost/type_traits/is_same.hpp>
#include <nt2/sdk/meta/cardinal_of.hpp>
#include <nt2/sdk/simd/native.hpp>

#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/module.hpp>

////////////////////////////////////////////////////////////////////////////////
// Test that scalar_of on scalar is idempotent
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE(cardinal_of)
{
  using nt2::simd::native;
  using nt2::meta::cardinal_of;
  using boost::is_same;

  typedef NT2_SIMD_DEFAULT_EXTENSION ext_t;

  #if defined(NT2_SIMD_SSE_FAMILY)
  #if defined(NT2_SIMD_AVX)
  NT2_TEST_EQUAL( (cardinal_of< native<double       ,ext_t> >::value)  , 4   );
  NT2_TEST_EQUAL( (cardinal_of< native<nt2::uint64_t,ext_t> >::value)  , 4   );
  NT2_TEST_EQUAL( (cardinal_of< native<nt2::int64_t ,ext_t> >::value)  , 4   );
  NT2_TEST_EQUAL( (cardinal_of<native<float         ,ext_t> >::value)  , 8   );
  NT2_TEST_EQUAL( (cardinal_of<native<nt2::uint32_t ,ext_t> >::value)  , 8   );
  NT2_TEST_EQUAL( (cardinal_of<native<nt2::uint16_t ,ext_t> >::value)  , 16  );
  NT2_TEST_EQUAL( (cardinal_of<native<nt2::uint8_t  ,ext_t> >::value)  , 32  );
  NT2_TEST_EQUAL( (cardinal_of<native<nt2::int32_t  ,ext_t> >::value)  , 8   );
  NT2_TEST_EQUAL( (cardinal_of<native<nt2::int16_t  ,ext_t> >::value)  , 16  );
  NT2_TEST_EQUAL( (cardinal_of<native<nt2::int8_t   ,ext_t> >::value)  , 32  );
  #else
  NT2_TEST_EQUAL( (cardinal_of< native<double       ,ext_t> >::value)  , 2   );
  NT2_TEST_EQUAL( (cardinal_of< native<nt2::uint64_t,ext_t> >::value)  , 2   );
  NT2_TEST_EQUAL( (cardinal_of< native<nt2::int64_t ,ext_t> >::value)  , 2   );
  NT2_TEST_EQUAL( (cardinal_of<native<float         ,ext_t> >::value)  , 4   );
  NT2_TEST_EQUAL( (cardinal_of<native<nt2::uint32_t ,ext_t> >::value)  , 4   );
  NT2_TEST_EQUAL( (cardinal_of<native<nt2::uint16_t ,ext_t> >::value)  , 8   );
  NT2_TEST_EQUAL( (cardinal_of<native<nt2::uint8_t  ,ext_t> >::value)  , 16  );
  NT2_TEST_EQUAL( (cardinal_of<native<nt2::int32_t  ,ext_t> >::value)  , 4   );
  NT2_TEST_EQUAL( (cardinal_of<native<nt2::int16_t  ,ext_t> >::value)  , 8   );
  NT2_TEST_EQUAL( (cardinal_of<native<nt2::int8_t   ,ext_t> >::value)  , 16  );
  #endif
  #endif

  #if defined(NT2_SIMD_VMX_FAMILY)
  NT2_TEST_EQUAL( (cardinal_of<native<float         ,ext_t> >::value)  , 4   );
  NT2_TEST_EQUAL( (cardinal_of<native<nt2::uint32_t ,ext_t> >::value)  , 4   );
  NT2_TEST_EQUAL( (cardinal_of<native<nt2::uint16_t ,ext_t> >::value)  , 8   );
  NT2_TEST_EQUAL( (cardinal_of<native<nt2::uint8_t  ,ext_t> >::value)  , 16  );
  NT2_TEST_EQUAL( (cardinal_of<native<nt2::int32_t  ,ext_t> >::value)  , 4   );
  NT2_TEST_EQUAL( (cardinal_of<native<nt2::int16_t  ,ext_t> >::value)  , 8   );
  NT2_TEST_EQUAL( (cardinal_of<native<nt2::int8_t   ,ext_t> >::value)  , 16  );
  #endif
}
