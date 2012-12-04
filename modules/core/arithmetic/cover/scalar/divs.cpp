//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#define NT2_UNIT_MODULE "nt2 arithmetic toolbox - divs/scalar Mode"

//////////////////////////////////////////////////////////////////////////////
// cover test behavior of arithmetic components in scalar mode
//////////////////////////////////////////////////////////////////////////////
/// created by jt the 28/11/2010
///
#include <nt2/toolbox/arithmetic/include/functions/divs.hpp>
#include <nt2/include/functions/ulpdist.hpp>
#include <nt2/include/functions/max.hpp>
#include <boost/type_traits/is_same.hpp>
#include <nt2/sdk/functor/meta/call.hpp>
#include <nt2/sdk/meta/as_integer.hpp>
#include <nt2/sdk/meta/as_floating.hpp>
#include <nt2/sdk/meta/as_signed.hpp>
#include <nt2/sdk/meta/upgrade.hpp>
#include <nt2/sdk/meta/downgrade.hpp>
#include <nt2/sdk/meta/scalar_of.hpp>
#include <boost/dispatch/meta/as_floating.hpp>
#include <boost/type_traits/common_type.hpp>
#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/module.hpp>

#include <nt2/toolbox/constant/constant.hpp>


NT2_TEST_CASE_TPL ( divs_signed_int__2_0,  NT2_INTEGRAL_SIGNED_TYPES)
{

  using nt2::divs;
  using nt2::tag::divs_;
  typedef typename nt2::meta::as_integer<T>::type iT;
  typedef typename nt2::meta::call<divs_(T,T)>::type r_t;
  typedef typename nt2::meta::scalar_of<r_t>::type ssr_t;
  typedef typename nt2::meta::upgrade<T>::type u_t;
  typedef T wished_r_t;


  // return type conformity test
  NT2_TEST( (boost::is_same < r_t, wished_r_t >::value) );
  std::cout << std::endl;
  double ulpd;
  ulpd=0.0;

  // random verifications
  static const nt2::uint32_t NR = NT2_NB_RANDOM_TEST;
  {
    NT2_CREATE_BUF(tab_a0,T, NR, 3*(nt2::Valmin<T>()/4), 3*(nt2::Valmax<T>()/4));
    NT2_CREATE_BUF(tab_a1,T, NR, 3*(nt2::Valmin<T>()/4), 3*(nt2::Valmax<T>()/4));
    double ulp0, ulpd ; ulpd=ulp0=0.0;
    T a0;
    T a1;
    for(nt2::uint32_t j =0; j < NR; ++j )
      {
        std::cout << "for params "
                  << "  a0 = "<< u_t(a0 = tab_a0[j])
                  << ", a1 = "<< u_t(a1 = tab_a1[j])
                  << std::endl;
        NT2_TEST_EQUAL( nt2::divs(a0,a1),(a1) ? a0/a1 :( (a0>0) ? nt2::Valmax<T>() : ((a0) ? nt2::Valmin<T>() : nt2::Zero<T>())));
     }

   }
} // end of test for signed_int_

NT2_TEST_CASE_TPL ( divs_unsigned_int__2_0,  NT2_UNSIGNED_TYPES)
{

  using nt2::divs;
  using nt2::tag::divs_;
  typedef typename nt2::meta::as_integer<T>::type iT;
  typedef typename nt2::meta::call<divs_(T,T)>::type r_t;
  typedef typename nt2::meta::scalar_of<r_t>::type ssr_t;
  typedef typename nt2::meta::upgrade<T>::type u_t;
  typedef T wished_r_t;


  // return type conformity test
  NT2_TEST( (boost::is_same < r_t, wished_r_t >::value) );
  std::cout << std::endl;
  double ulpd;
  ulpd=0.0;

  // random verifications
  static const nt2::uint32_t NR = NT2_NB_RANDOM_TEST;
  {
    NT2_CREATE_BUF(tab_a0,T, NR, 3*(nt2::Valmin<T>()/4), 3*(nt2::Valmax<T>()/4));
    NT2_CREATE_BUF(tab_a1,T, NR, 3*(nt2::Valmin<T>()/4), 3*(nt2::Valmax<T>()/4));
    double ulp0, ulpd ; ulpd=ulp0=0.0;
    T a0;
    T a1;
    for(nt2::uint32_t j =0; j < NR; ++j )
      {
        std::cout << "for params "
                  << "  a0 = "<< u_t(a0 = tab_a0[j])
                  << ", a1 = "<< u_t(a1 = tab_a1[j])
                  << std::endl;
        NT2_TEST_EQUAL( nt2::divs(a0,a1),(a1) ? a0/a1 : ( (a0>0) ? nt2::Valmax<T>() : nt2::Zero<T>() ));
     }

   }
} // end of test for unsigned_int_
