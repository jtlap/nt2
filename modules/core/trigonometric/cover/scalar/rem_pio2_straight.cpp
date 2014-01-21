//==============================================================================
//         Copyright 2003 - 2013   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/trigonometric/include/functions/rem_pio2_straight.hpp>
#include <nt2/trigonometric/include/functions/rem_pio2_medium.hpp>

#include <nt2/sdk/unit/tests/cover.hpp>
#include <nt2/sdk/unit/tests/ulp.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <iostream>
#include <nt2/include/constants/pio_4.hpp>
#include <nt2/include/constants/pio_2.hpp>
#include <nt2/sdk/functor/meta/call.hpp>

NT2_TEST_CASE_TPL ( rem_pio2_straight_real__1_0,  NT2_REAL_TYPES)
{
  using nt2::rem_pio2_straight;
  using nt2::tag::rem_pio2_straight_;
  typedef typename nt2::meta::call<rem_pio2_straight_(T)>::type r_t;

  static const nt2::uint32_t NR = NT2_NB_RANDOM_TEST;
  {
    NT2_CREATE_BUF(tab_a0,T, NR, nt2::Pio_4<T>(), nt2::Pio_2<T>());
    T a0;
    for(nt2::uint32_t j =0; j < NR; ++j )
      {
        std::cout << "for param "
                  << "  a0 = "<< (a0 = tab_a0[j])
                  << std::endl;
        r_t r = nt2::rem_pio2_straight(a0);
        r_t rm= nt2::rem_pio2_medium(a0);
        NT2_TEST_ULP_EQUAL( r.second, rm.second, 0.5);
        NT2_TEST_ULP_EQUAL( r.first, rm.first, 0);
     }
   }
} // end of test for floating_
