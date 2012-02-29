//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#define NT2_UNIT_MODULE "nt2::memory dimensions_of"

#include <nt2/sdk/meta/dimensions_of.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>

////////////////////////////////////////////////////////////////////////////////
// Random type has 0 dimensions
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE( not_a_buffer )
{
  using nt2::meta::dimensions_of;

  NT2_TEST_EQUAL( dimensions_of<int>::value, 0UL );
  NT2_TEST_EQUAL( dimensions_of<long&>::value, 0UL );
  NT2_TEST_EQUAL( dimensions_of<float const&>::value, 0UL );
}
