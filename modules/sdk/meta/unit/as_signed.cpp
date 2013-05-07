//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#define NT2_UNIT_MODULE "nt2::meta::as_signed"

#include <nt2/sdk/config/types.hpp>
#include <nt2/sdk/meta/as_signed.hpp>
#include <boost/type_traits/is_same.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/basic.hpp>

////////////////////////////////////////////////////////////////////////////////
// Test that as_integer is correct w/r to original sign
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE(as_signed)
{
  using nt2::meta::as_signed;
  using boost::is_same;

  NT2_TEST( (is_same<as_signed<double        >::type,double     >::value ));
  NT2_TEST( (is_same<as_signed<float         >::type,float      >::value ));
  NT2_TEST( (is_same<as_signed<nt2::int64_t >::type,nt2::int64_t>::value ));
  NT2_TEST( (is_same<as_signed<nt2::int32_t >::type,nt2::int32_t>::value ));
  NT2_TEST( (is_same<as_signed<nt2::int16_t >::type,nt2::int16_t>::value ));
  NT2_TEST( (is_same<as_signed<nt2::int8_t  >::type,nt2::int8_t >::value ));
  NT2_TEST( (is_same<as_signed<nt2::uint64_t>::type,nt2::int64_t>::value ));
  NT2_TEST( (is_same<as_signed<nt2::uint32_t>::type,nt2::int32_t>::value ));
  NT2_TEST( (is_same<as_signed<nt2::uint16_t>::type,nt2::int16_t>::value ));
  NT2_TEST( (is_same<as_signed<nt2::uint8_t >::type,nt2::int8_t >::value ));
  NT2_TEST( (is_same<as_signed<bool         >::type,bool        >::value ));
}
