//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2014   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012 - 2014   MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/table.hpp>
#include <nt2/include/functions/ofsamewidth.hpp>
#include <nt2/include/functions/ones.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/basic.hpp>

NT2_TEST_CASE( container )
{
  using nt2::_;
  nt2::table<float> a = nt2::ones(4, nt2::meta::as_<float>());
  nt2::table<float> b = nt2::ones(4, 3, nt2::meta::as_<float>());

  NT2_TEST( !nt2::ofsamewidth( a, b) );
  b = nt2::ones(3, 4, nt2::meta::as_<float>());
  NT2_TEST( nt2::ofsamewidth( a, b) );

}
