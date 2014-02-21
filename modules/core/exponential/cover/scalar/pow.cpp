//==============================================================================
//         Copyright 2003 - 2013   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/exponential/include/functions/pow.hpp>

#include <nt2/sdk/unit/tests/cover.hpp>
#include <nt2/sdk/unit/tests/ulp.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/include/constants/half.hpp>
#include <nt2/include/constants/two.hpp>

#include <iostream>

extern "C" { long double cephes_powl(long double,long double); }
extern "C" { long double cephes_powil(long double,int); }
extern "C" { long double cephes_powil(long double,int); }

NT2_TEST_CASE_TPL ( pow_real,  NT2_REAL_TYPES)
{
  using nt2::pow;
  using nt2::tag::pow_;
  static const nt2::uint32_t NR = NT2_NB_RANDOM_TEST;
  {
    NT2_CREATE_BUF(tab_a0,T, NR, T(0), T(10));
    NT2_CREATE_BUF(tab_a1,T, NR, T(-10), T(10));
    T a0;
    T a1;
    for(nt2::uint32_t j =0; j < NR; ++j )
      {
        std::cout << "for params "
                  << "  a0 = "<< (a0 = tab_a0[j])
                  << ", a1 = "<< (a1 = tab_a1[j])
                  << std::endl;
        std::cout<< ", p1 = "<< nt2::pow(a0,a1)
                 << ", p2 = "<< ::cephes_powl(a0,a1)
                 << std::endl;
        NT2_TEST_ULP_EQUAL( nt2::pow(a0,a1),::cephes_powl(a0,a1),12.5);
        NT2_TEST_ULP_EQUAL( nt2::pow(a0,nt2::Two<T>()),nt2::sqr(a0),1);
        NT2_TEST_ULP_EQUAL( nt2::pow(a0,nt2::Half<T>()),nt2::sqrt(a0),1);
     }
   }
}

NT2_TEST_CASE_TPL ( pow_real1,  NT2_REAL_TYPES)
{
  using nt2::pow;
  using nt2::tag::pow_;
  static const nt2::uint32_t NR = NT2_NB_RANDOM_TEST;
  typedef typename nt2::meta::as_integer<T>::type iT;
  {
    NT2_CREATE_BUF(tab_a0,T, NR, T(0), T(10));
    NT2_CREATE_BUF(tab_a1,iT, NR, iT(-10), iT(10));
    T a0;
    iT a1;
    for(nt2::uint32_t j =0; j < NR; ++j )
      {
        std::cout << "for params "
                  << "  a0 = "<< (a0 = tab_a0[j])
                  << ", a1 = "<< (a1 = tab_a1[j])
                  << std::endl;
        std::cout<< ", p1 = "<< nt2::pow(a0,a1)
                 << ", p2 = "<< ::cephes_powl(a0,(long double)a1)
                 << std::endl;
        NT2_TEST_ULP_EQUAL( nt2::pow(a0,a1),::cephes_powl(a0,(long double)a1),12.5);
        NT2_TEST_ULP_EQUAL( nt2::pow(a0,nt2::Two<T>()),nt2::sqr(a0),1);
        NT2_TEST_ULP_EQUAL( nt2::pow(a0,nt2::Half<T>()),nt2::sqrt(a0),1);
     }
   }
}
