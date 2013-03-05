//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#define NT2_UNIT_MODULE "nt2::constants true/false"

#include <nt2/include/constants/true_false.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/simd/logical.hpp>

////////////////////////////////////////////////////////////////////////////////
// Test value of true/false constants
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE_TPL  (  true_false_value, BOOST_SIMD_TYPES )
{
  NT2_TEST_EQUAL( nt2::False< nt2::logical<T> >() , nt2::logical<T>(false) );
  NT2_TEST_EQUAL( nt2::True< nt2::logical<T> >()  , nt2::logical<T>(true)  );
}
