//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#define NT2_UNIT_MODULE "nt2 gsl_specfun toolbox - gsl_sf_legendre_sphplm/scalar Mode"

//////////////////////////////////////////////////////////////////////////////
// Test behavior of gsl_specfun components in scalar mode
//////////////////////////////////////////////////////////////////////////////
/// created  by jt the 10/03/2011
/// modified by jt the 18/03/2011
#include <boost/type_traits/is_same.hpp>
#include <nt2/sdk/functor/meta/call.hpp>
#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/memory/buffer.hpp>
#include <nt2/sdk/constant/real.hpp>
#include <nt2/sdk/constant/infinites.hpp>
#include <nt2/toolbox/gsl_specfun/include/gsl_sf_legendre_sphplm.hpp>

NT2_TEST_CASE_TPL ( gsl_sf_legendre_sphplm_real__3_0,  NT2_REAL_TYPES)
{
  
  using nt2::gsl_specfun::gsl_sf_legendre_sphplm;
  using nt2::gsl_specfun::tag::gsl_sf_legendre_sphplm_;
  typedef typename nt2::meta::as_integer<T>::type iT;
  typedef typename nt2::meta::call<gsl_sf_legendre_sphplm_(iT,iT,T)>::type r_t;
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
    NT2_CREATE_BUF(tab_a0,iT, NR, iT(0), iT(10));
    NT2_CREATE_BUF(tab_a1,iT, NR, iT(0), iT(10));
    NT2_CREATE_BUF(tab_a2,T, NR, T(-1), T(1));
    double ulp0, ulpd ; ulpd=ulp0=0.0;
    iT a0;
    iT a1;
    T a2;
    for (uint32_t j =0; j < NR; ++j )
      {
        std::cout << "for params "
                  << "  a0 = "<< u_t(a0 = tab_a0[j])
                  << ", a1 = "<< u_t(a1 = tab_a1[j])
                  << ", a2 = "<< u_t(a2 = tab_a2[j])
                  << std::endl;
        NT2_TEST_ULP_EQUAL( nt2::gsl_specfun::gsl_sf_legendre_sphplm(a0+a1,a0,a2),nt2::gsl_specfun::gsl_sf_legendre_sphplm(a0+a1,a0,a2),1);
        ulp0=std::max(ulpd,ulp0);
     }
     std::cout << "max ulp found is: " << ulp0 << std::endl;
   }
} // end of test for real_
