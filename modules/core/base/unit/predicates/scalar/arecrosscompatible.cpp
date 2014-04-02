//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2014   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2011 - 2014   MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/include/functions/arecrosscompatible.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/basic.hpp>

NT2_TEST_CASE( fundamental )
{
  NT2_TEST( !nt2::arecrosscompatible('e', 'e', 1));
  NT2_TEST( !nt2::arecrosscompatible(1,   1  , 1));
  NT2_TEST( !nt2::arecrosscompatible(1.,  1. , 1));
  NT2_TEST( !nt2::arecrosscompatible(1.f, 1.f, 1));
}
