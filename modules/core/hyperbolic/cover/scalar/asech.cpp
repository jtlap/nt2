//==============================================================================
//         Copyright 2003 - 2013   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/hyperbolic/include/functions/asech.hpp>

#include <nt2/sdk/unit/tests/cover.hpp>
#include <nt2/sdk/unit/tests/ulp.hpp>
#include <nt2/sdk/unit/module.hpp>

#include <iostream>

#include <nt2/boost_math/include/functions/acosh.hpp>
extern "C" { long double cephes_acoshl(long double); }
#include <nt2/include/functions/rec.hpp>

NT2_TEST_CASE_TPL ( asech,  NT2_REAL_TYPES)
{
  using nt2::asech;
  using nt2::tag::asech_;
  static const nt2::uint32_t NR = NT2_NB_RANDOM_TEST;
  {
    NT2_CREATE_BUF(tab_a0,T, NR, T(0), T(0.9));
    T a0;
    for(nt2::uint32_t j =0; j < NR; ++j )
      {
        std::cout << "for param "
                  << "  a0 = "<< (a0 = tab_a0[j])
                  << std::endl;
        NT2_TEST_ULP_EQUAL( nt2::asech(a0),nt2::boost_math::acosh(nt2::rec(a0)),5.0);
        NT2_TEST_ULP_EQUAL( nt2::asech(a0),::cephes_acoshl(nt2::rec(a0)),1.0);
     }
   }
} // end of test for floating_
