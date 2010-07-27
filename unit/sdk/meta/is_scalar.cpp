/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#define NT2_UNIT_MODULE "nt2::meta::is_scalar"

#include <nt2/sdk/meta/is_scalar.hpp>
#include <nt2/sdk/functor/category.hpp>

#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/module.hpp>

////////////////////////////////////////////////////////////////////////////////
// Test that scalar are scalar (dur)
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE(is_scalar_scalar)
{
  using nt2::meta::is_scalar;
  using namespace nt2;

  NT2_TEST( is_scalar<double>::value   );
  NT2_TEST( is_scalar<float>::value    );
  NT2_TEST( is_scalar<uint64_t>::value );
  NT2_TEST( is_scalar<uint32_t>::value );
  NT2_TEST( is_scalar<uint16_t>::value );
  NT2_TEST( is_scalar<uint8_t>::value  );
  NT2_TEST( is_scalar<int64_t>::value  );
  NT2_TEST( is_scalar<int32_t>::value  );
  NT2_TEST( is_scalar<int16_t>::value  );
  NT2_TEST( is_scalar<int8_t>::value   );
  NT2_TEST( is_scalar<bool>::value     );
}

////////////////////////////////////////////////////////////////////////////////
// Test that types with a scalar category are scalar
////////////////////////////////////////////////////////////////////////////////
struct bar
{
  typedef nt2::functors::scalar_<nt2::tag::arithmetic_,10> nt2_category_tag;
};

NT2_TEST_CASE(is_category_scalar)
{
  using nt2::meta::is_scalar;
  NT2_TEST( is_scalar<bar>::value );
}

////////////////////////////////////////////////////////////////////////////////
// Test that non-scalar types are not scalar
////////////////////////////////////////////////////////////////////////////////
struct foo {};  // type of unknown category

NT2_TEST_CASE(is_nonscalar)
{
  using nt2::meta::is_scalar;
  NT2_TEST( !is_scalar<foo>::value );
}
