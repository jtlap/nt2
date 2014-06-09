//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/include/functions/size.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>

NT2_TEST_CASE( fundamental_size )
{
  using nt2::size;

  NT2_TEST_EQUAL( size( 3 , 1 ), 1u);
  NT2_TEST_EQUAL( size( 3 , 2 ), 1u);
  NT2_TEST_EQUAL( size( 3 , 3 ), 1u);
}
