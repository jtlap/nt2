//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#define NT2_UNIT_MODULE "nt2::constants infinites"

#include <nt2/include/constants/infinites.hpp>
#include <limits>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>

////////////////////////////////////////////////////////////////////////////////
// Test value of infinites for every base real types
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE_TPL( real_inf, NT2_REAL_TYPES )
{
  NT2_TEST_EQUAL( nt2::Inf<T>() , std::numeric_limits<T>::infinity()  );
  NT2_TEST_EQUAL( nt2::Minf<T>(), -std::numeric_limits<T>::infinity() );
}

////////////////////////////////////////////////////////////////////////////////
// Test value of infinites for every base integral types
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE_TPL( int_inf, NT2_INTEGRAL_TYPES )
{
  NT2_TEST_EQUAL( nt2::Inf<T>() , nt2::Valmax<T>()  );
  NT2_TEST_EQUAL( nt2::Minf<T>(), nt2::Valmin<T>()  );
}
