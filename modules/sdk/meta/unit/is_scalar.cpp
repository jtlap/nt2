/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#define NT2_UNIT_MODULE "nt2::meta::is_scalar"

#include <nt2/sdk/config/types.hpp>
#include <nt2/sdk/meta/is_scalar.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/basic.hpp>

////////////////////////////////////////////////////////////////////////////////
// Test that scalar are scalar (dur)
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE(is_scalar_scalar)
{
  using nt2::meta::is_scalar;

  NT2_TEST( is_scalar<double>::value        );
  NT2_TEST( is_scalar<float>::value         );
  NT2_TEST( is_scalar<nt2::uint64_t>::value );
  NT2_TEST( is_scalar<nt2::uint32_t>::value );
  NT2_TEST( is_scalar<nt2::uint16_t>::value );
  NT2_TEST( is_scalar<nt2::uint8_t>::value  );
  NT2_TEST( is_scalar<nt2::int64_t>::value  );
  NT2_TEST( is_scalar<nt2::int32_t>::value  );
  NT2_TEST( is_scalar<nt2::int16_t>::value  );
  NT2_TEST( is_scalar<nt2::int8_t>::value   );
  NT2_TEST( is_scalar<bool>::value          );
}

////////////////////////////////////////////////////////////////////////////////
// Test that non-scalar types are not scalar
////////////////////////////////////////////////////////////////////////////////
struct foo {};  // type of unknown hierarchy

NT2_TEST_CASE(is_nonscalar)
{
  using nt2::meta::is_scalar;
  NT2_TEST( !is_scalar<foo>::value );
}
