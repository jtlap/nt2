//==============================================================================
//         Copyright 2003 - 2013   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/trigonometric/include/functions/proper_tanpi.hpp>

#include <nt2/sdk/unit/tests/cover.hpp>
#include <nt2/sdk/unit/tests/ulp.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <iostream>
extern "C" {extern long double cephes_tanl(long double);}
static const long double long_pi = 3.141592653589793238462643383279502884197l;


NT2_TEST_CASE_TPL ( proper_tanpi_real__1_0,  NT2_REAL_TYPES)
{
  using nt2::proper_tanpi;
  using nt2::tag::proper_tanpi_;

  static const nt2::uint32_t NR = NT2_NB_RANDOM_TEST;
  {
    NT2_CREATE_BUF(tab_a0,T, NR, T(-0.5), T(0.5));
    T a0;
    for(nt2::uint32_t j =0; j < NR; ++j )
      {
        std::cout << "for param "
                  << "  a0 = "<< (a0 = tab_a0[j])
                  << std::endl;
        NT2_TEST_ULP_EQUAL( nt2::proper_tanpi(a0),::cephes_tanl(long_pi*a0),10.0);
     }
   }
} // end of test for floating_

