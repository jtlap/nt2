//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/table.hpp>
#include <nt2/include/functions/ofsameheight.hpp>
#include <nt2/include/functions/ones.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/basic.hpp>

NT2_TEST_CASE( container_ofsameheight )
{
  using nt2::_;
  nt2::table<float> a = nt2::ones(4, nt2::meta::as_<float>());
  nt2::table<float> b = nt2::ones(4, 3, nt2::meta::as_<float>());

  NT2_TEST( nt2::ofsameheight( a, b) );
  b = nt2::ones(3, 4, nt2::meta::as_<float>());
  NT2_TEST( !nt2::ofsameheight( a, b) );

}

NT2_TEST_CASE( container_scalar_ofsameheight )
{
  using nt2::_;
  float a = 4.0f;
  nt2::table<float> b = nt2::ones(1, 3, nt2::meta::as_<float>());

  NT2_TEST( nt2::ofsameheight( a, b) );
  NT2_TEST( nt2::ofsameheight( b, a) );

}

NT2_TEST_CASE( container_multi_ofsameheight )
{
  using nt2::_;
  nt2::table<float> a = nt2::ones(3, 3, nt2::meta::as_<float>());
  nt2::table<float> b = nt2::ones(3, 4, nt2::meta::as_<float>());
  nt2::table<float> c = nt2::ones(3, 5, nt2::meta::as_<float>());
  nt2::table<float> d = nt2::ones(4, 5, nt2::meta::as_<float>());

  NT2_TEST( nt2::ofsameheight( a, b, c) );
  NT2_TEST( !nt2::ofsameheight( a, b, d) );
}
