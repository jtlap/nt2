//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#define NT2_UNIT_MODULE "nt2::meta::as_real"

#include <nt2/sdk/config/types.hpp>
#include <nt2/sdk/meta/as_floating.hpp>
#include <boost/type_traits/is_same.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/basic.hpp>

////////////////////////////////////////////////////////////////////////////////
// Test that as_floating is correct w/r to original sign
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE(as_floating)
{
  using nt2::meta::as_floating;
  using boost::is_same;

  NT2_TEST( (is_same<as_floating<double       >::type,double  >::value ));
  NT2_TEST( (is_same<as_floating<float        >::type,float   >::value ));
  NT2_TEST( (is_same<as_floating<nt2::int64_t >::type,double  >::value ));
  NT2_TEST( (is_same<as_floating<nt2::int32_t >::type,float   >::value ));
  NT2_TEST( (is_same<as_floating<nt2::uint64_t>::type,double  >::value ));
  NT2_TEST( (is_same<as_floating<nt2::uint32_t>::type,float   >::value ));
}
