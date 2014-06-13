//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/include/functions/arecatcompatible.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/basic.hpp>

NT2_TEST_CASE( fundamental )
{
  NT2_TEST( nt2::arecatcompatible('e', 'e', 1));
  NT2_TEST( nt2::arecatcompatible(1,   1  , 1));
  NT2_TEST( nt2::arecatcompatible(1.,  1. , 1));
  NT2_TEST( nt2::arecatcompatible(1.f, 1.f, 1));
}
