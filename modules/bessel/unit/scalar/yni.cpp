//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#define NT2_UNIT_MODULE "nt2 bessel toolbox - yni/scalar Mode"

//////////////////////////////////////////////////////////////////////////////
// Test behavior of bessel components in scalar mode
//////////////////////////////////////////////////////////////////////////////
/// created  by jt the 16/02/2011
/// modified by jt the 23/03/2011
#include <boost/type_traits/is_same.hpp>
#include <nt2/sdk/functor/meta/call.hpp>
#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/memory/buffer.hpp>
#include <nt2/sdk/constant/real.hpp>
#include <nt2/sdk/constant/infinites.hpp>
#include <nt2/include/functions/max.hpp>
#include <nt2/toolbox/bessel/include/yni.hpp>
// specific includes for arity 2 tests
extern "C" {long double cephes_ynl(int,long double);}

NT2_TEST_CASE_TPL ( yni_real__2_0,  NT2_REAL_TYPES)
{
  
  using nt2::yni;
  using nt2::tag::yni_;
  typedef typename nt2::meta::as_integer<T>::type iT;
  typedef typename nt2::meta::call<yni_(iT,T)>::type r_t;
  typedef typename nt2::meta::upgrade<T>::type u_t;
  typedef typename boost::result_of<nt2::meta::floating(T)>::type wished_r_t;


  // return type conformity test 
  NT2_TEST( (boost::is_same < r_t, wished_r_t >::value) );
  std::cout << std::endl; 
  double ulpd;
  ulpd=0.0;


  // specific values tests
  NT2_TEST_ULP_EQUAL(yni(0,nt2::Inf<T>()), nt2::Zero<r_t>(), 0.5);
  NT2_TEST_ULP_EQUAL(yni(0,nt2::Zero<T>()), nt2::Minf<r_t>(), 0.5);
  NT2_TEST_ULP_EQUAL(yni(1,nt2::Inf<T>()), nt2::Zero<r_t>(), 0.5);
  NT2_TEST_ULP_EQUAL(yni(1,nt2::Zero<T>()), nt2::Minf<r_t>(), 0.5);
  // random verifications
  static const uint32_t NR = NT2_NB_RANDOM_TEST;
  {
    NT2_CREATE_BUF(tab_a0,iT, NR, 1, 10);
    NT2_CREATE_BUF(tab_a1,T, NR, T(0), T(10));
    double ulp0, ulpd ; ulpd=ulp0=0.0;
    iT a0;
    T a1;
    for (uint32_t j =0; j < NR; ++j )
      {
        std::cout << "for params "
                  << "  a0 = "<< u_t(a0 = tab_a0[j])
                  << ", a1 = "<< u_t(a1 = tab_a1[j])
                  << std::endl;
        NT2_TEST_ULP_EQUAL( nt2::yni(a0,a1),::cephes_ynl(a0,a1),200);
        ulp0=nt2::max(ulpd,ulp0);
     }
     std::cout << "max ulp found is: " << ulp0 << std::endl;
   }
} // end of test for real_
