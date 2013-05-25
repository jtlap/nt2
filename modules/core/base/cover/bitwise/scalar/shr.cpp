//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#define NT2_UNIT_MODULE "nt2 bitwise toolbox - shr/scalar Mode"

//////////////////////////////////////////////////////////////////////////////
// cover test behavior of bitwise components in scalar mode
//////////////////////////////////////////////////////////////////////////////
/// created  by jt the 18/02/2011
///
#include <nt2/bitwise/include/functions/shr.hpp>
#include <nt2/include/functions/max.hpp>
#include <nt2/include/functions/twopower.hpp>
#include <boost/simd/sdk/simd/io.hpp>
#include <boost/dispatch/meta/as_integer.hpp>
#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>
#include <nt2/include/constants/valmin.hpp>
#include <nt2/include/constants/valmax.hpp>

NT2_TEST_CASE_TPL ( shr_unsigned_int__2_0,  NT2_UNSIGNED_TYPES)
{

  using nt2::shr;
  using nt2::tag::shr_;
  typedef typename nt2::meta::as_integer<T>::type iT;
  typedef typename nt2::meta::call<shr_(T,iT)>::type r_t;
  typedef T wished_r_t;


  // return type conformity test
  NT2_TEST_TYPE_IS( r_t, wished_r_t );


  // random verifications
  static const nt2::uint32_t NR = NT2_NB_RANDOM_TEST;
  {
    typedef T r_type;
    NT2_CREATE_BUF(tab_a0,T, NR, nt2::Valmin<T>()/2, nt2::Valmax<T>()/2);
    NT2_CREATE_BUF(tab_a1,iT, NR, T(0), sizeof(T)*8-1);
    double ulp0, ulpd ; ulpd=ulp0=0.0;
    T a0;
    iT a1;
    for(nt2::uint32_t j =0; j < NR; ++j )
      {
        std::cout << "for params "
                  << "  a0 = "<< (a0 = tab_a0[j])
                  << ", a1 = "<< (a1 = tab_a1[j])
                  << std::endl;
        NT2_TEST_EQUAL( nt2::shr(a0,a1),a0/nt2::twopower(a1));
     }

   }
} // end of test for unsigned_int_
