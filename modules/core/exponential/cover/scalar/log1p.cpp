//==============================================================================
//         Copyright 2003 - 2013   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/exponential/include/functions/log1p.hpp>

#include <nt2/sdk/unit/tests/cover.hpp>
#include <nt2/sdk/unit/tests/ulp.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/include/constants/half.hpp>

#include <iostream>

#include <nt2/include/functions/expm1.hpp>
#include <nt2/include/functions/log1p.hpp>
#include <nt2/include/functions/sqrt1pm1.hpp>
extern "C" { long double cephes_log1pl(long double); }

NT2_TEST_CASE_TPL ( log1p,  NT2_REAL_TYPES)
{
  using nt2::log1p;
  using nt2::tag::log1p_;
  static const nt2::uint32_t NR = NT2_NB_RANDOM_TEST;
  {
    NT2_CREATE_BUF(tab_a0,T, NR, T(0.1), T(10));
    T a0;
    for(nt2::uint32_t j =0; j < NR; ++j )
      {
        std::cout << "for param "
                  << "  a0 = "<< (a0 = tab_a0[j])
                  << std::endl;
        NT2_TEST_ULP_EQUAL( nt2::log1p(a0),::cephes_log1pl(a0),1);
        NT2_TEST_ULP_EQUAL( nt2::log1p(nt2::expm1(a0)),a0,1.5);
        NT2_TEST_ULP_EQUAL( nt2::log1p(nt2::sqrt1pm1(a0)),nt2::Half<T>()*nt2::log1p(a0),2.0);
     }
   }
} // end of test for floating_
