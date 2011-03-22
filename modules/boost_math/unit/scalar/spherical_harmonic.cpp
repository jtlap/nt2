//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#define NT2_UNIT_MODULE "nt2 boost_math toolbox - spherical_harmonic/scalar Mode"

//////////////////////////////////////////////////////////////////////////////
// Test behavior of boost_math components in scalar mode
//////////////////////////////////////////////////////////////////////////////
/// created  by jt the 07/03/2011
/// modified by jt the 23/03/2011
#include <boost/type_traits/is_same.hpp>
#include <nt2/sdk/functor/meta/call.hpp>
#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/memory/buffer.hpp>
#include <nt2/sdk/constant/real.hpp>
#include <nt2/sdk/constant/infinites.hpp>
#include <nt2/include/functions/ulpdist.hpp>
#include <nt2/toolbox/boost_math/include/spherical_harmonic.hpp>

NT2_TEST_CASE_TPL ( spherical_harmonic_real__4_0,  NT2_REAL_TYPES)
{
  
  using nt2::boost_math::spherical_harmonic;
  using nt2::boost_math::tag::spherical_harmonic_;
  typedef typename nt2::meta::as_integer<T>::type iT;
  typedef typename nt2::meta::call<spherical_harmonic_(iT,iT,T,T)>::type r_t;
  typedef typename nt2::meta::upgrade<T>::type u_t;
  typedef T wished_r_t;


  // return type conformity test 
  NT2_TEST( (boost::is_same < r_t, wished_r_t >::value) );
  std::cout << std::endl; 
  double ulpd;
  ulpd=0.0;

  // random verifications
  static const uint32_t NR = NT2_NB_RANDOM_TEST;
  {
    NT2_CREATE_BUF(tab_a0,iT, NR, T(0), T(10));
    NT2_CREATE_BUF(tab_a1,iT, NR, T(0), T(10));
    NT2_CREATE_BUF(tab_a2,T, NR, T(-10), T(10));
    NT2_CREATE_BUF(tab_a3,T, NR, T(-10), T(10));
    double ulp0, ulpd ; ulpd=ulp0=0.0;
    iT a0;
    iT a1;
    T a2;
    T a3;
    for (uint32_t j =0; j < NR; ++j )
      {
        std::cout << "for params "
                  << "  a0 = "<< u_t(a0 = tab_a0[j])
                  << ", a1 = "<< u_t(a1 = tab_a1[j])
                  << ", a2 = "<< u_t(a2 = tab_a2[j])
                  << ", a3 = "<< u_t(a3 = tab_a3[j])
                  << std::endl;
        NT2_TEST_ULP_EQUAL( nt2::boost_math::spherical_harmonic(a0,a1,a2,a3),nt2::boost_math::spherical_harmonic(a0,a1,a2,a3),1);
        ulp0=nt2::max(ulpd,ulp0);
     }
     std::cout << "max ulp found is: " << ulp0 << std::endl;
   }
} // end of test for real_
