//==============================================================================
//         Copyright 2003 - 2013   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/trigonometric/include/functions/fast_cot.hpp>

#include <nt2/sdk/unit/tests/cover.hpp>
#include <nt2/sdk/unit/tests/ulp.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/meta/cardinal_of.hpp>
#include <nt2/include/functions/aligned_load.hpp>
#include <iostream>
#include <nt2/include/constants/pi.hpp>

NT2_TEST_CASE_TPL ( fast_cot_real__1_0,  NT2_SIMD_REAL_TYPES)
{
  using nt2::fast_cot;
  using nt2::tag::fast_cot_;
  using boost::simd::native;
  using nt2::meta::cardinal_of;
  using nt2::aligned_load;
  typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef native<T,ext_t>                  vT;

  static const nt2::uint32_t NR = NT2_NB_RANDOM_TEST;
  {
    NT2_CREATE_BUF(tab_a0,T, NR, -nt2::Pi<T>()/4, nt2::Pi<T>()/4);
    for(nt2::uint32_t j = 0; j < NR;j+=cardinal_of<vT>::value)
      {
        vT a0 = aligned_load<vT>(&tab_a0[0],j);
        vT v = fast_cot(a0);
        for(nt2::uint32_t i = 0; i< cardinal_of<vT>::value; i++)
        {

          NT2_TEST_ULP_EQUAL( v[i],T(nt2::fast_cot (a0[i])), 1.0);
        }
      }
  }
} // end of test for floating_
