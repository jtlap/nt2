//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#define NT2_UNIT_MODULE "boost::dispatch::meta::is_scalar"

#include <boost/simd/sdk/config/types.hpp>
#include <boost/dispatch/meta/is_scalar.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/basic.hpp>

////////////////////////////////////////////////////////////////////////////////
// Test that scalar are scalar (dur)
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE(is_scalar_scalar)
{
  using boost::dispatch::meta::is_scalar;

  NT2_TEST( is_scalar<double>::value        );
  NT2_TEST( is_scalar<float>::value         );
  NT2_TEST( is_scalar<boost::simd::uint64_t>::value );
  NT2_TEST( is_scalar<boost::simd::uint32_t>::value );
  NT2_TEST( is_scalar<boost::simd::uint16_t>::value );
  NT2_TEST( is_scalar<boost::simd::uint8_t>::value  );
  NT2_TEST( is_scalar<boost::simd::int64_t>::value  );
  NT2_TEST( is_scalar<boost::simd::int32_t>::value  );
  NT2_TEST( is_scalar<boost::simd::int16_t>::value  );
  NT2_TEST( is_scalar<boost::simd::int8_t>::value   );
  NT2_TEST( is_scalar<bool>::value          );
}

////////////////////////////////////////////////////////////////////////////////
// Test that non-scalar types are not scalar
////////////////////////////////////////////////////////////////////////////////
struct foo {};  // type of unknown hierarchy

NT2_TEST_CASE(is_nonscalar)
{
  using boost::dispatch::meta::is_scalar;
  NT2_TEST( !is_scalar<foo>::value );
}
