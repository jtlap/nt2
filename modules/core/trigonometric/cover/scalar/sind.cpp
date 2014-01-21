//==============================================================================
//         Copyright 2003 - 2013   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/trigonometric/include/functions/sind.hpp>

#include <nt2/sdk/unit/tests/cover.hpp>
#include <nt2/sdk/unit/tests/ulp.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <iostream>
extern "C" {extern long double cephes_sinl(long double);}


NT2_TEST_CASE_TPL ( sind_real__1_0,  NT2_REAL_TYPES)
{
  using nt2::sind;
  using nt2::tag::sind_;

  static const nt2::uint32_t NR = NT2_NB_RANDOM_TEST;
  {
    const long double long_deginrad = 0.017453292519943295769236907684886l;
    NT2_CREATE_BUF(tab_a0,T, NR, T(-2000), T(2000));
    T a0;
    for(nt2::uint32_t j =0; j < NR; ++j )
      {
        std::cout << "for param "
                  << "  a0 = "<< (a0 = tab_a0[j])
                  << std::endl;
        NT2_TEST_ULP_EQUAL( nt2::sind(a0),::cephes_sinl(a0*long_deginrad),1.0);
     }
   }
} // end of test for floating_
