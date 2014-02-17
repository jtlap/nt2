//==============================================================================
//         Copyright 2003 - 2013   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/hyperbolic/include/functions/tanh.hpp>

#include <nt2/sdk/unit/tests/cover.hpp>
#include <nt2/sdk/unit/tests/ulp.hpp>
#include <nt2/sdk/unit/module.hpp>

#include <iostream>

extern "C" { long double cephes_tanhl(long double); }

NT2_TEST_CASE_TPL ( tanh, NT2_REAL_TYPES)
{
  using nt2::tanh;
  using nt2::tag::tanh_;
  static const nt2::uint32_t NR = NT2_NB_RANDOM_TEST;
  {
    NT2_CREATE_BUF(tab_a0,T, NR, T(-0.625), T(0.625));
    NT2_CREATE_BUF(tab_a1,T, NR, T( 0.625), T(10));
    NT2_CREATE_BUF(tab_a2,T, NR, T(-10),    T(-0.625));
    T a0, a1, a2;
    for(nt2::uint32_t j =0; j < NR; ++j )
      {
        std::cout << "for param "
                  << "  a0 = "<< (a0 = tab_a0[j])
                  << "  a1 = "<< (a1 = tab_a1[j])
                  << "  a2 = "<< (a2 = tab_a2[j])
                  << std::endl;
        NT2_TEST_ULP_EQUAL( nt2::tanh(a0),::cephes_tanhl(a0),1.0);
        NT2_TEST_ULP_EQUAL( nt2::tanh(a1),::cephes_tanhl(a1),1.0);
        NT2_TEST_ULP_EQUAL( nt2::tanh(a2),::cephes_tanhl(a2),1.0);
      }
   }
} // end of test for floating_
