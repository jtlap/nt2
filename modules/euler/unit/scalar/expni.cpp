//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#define NT2_UNIT_MODULE "nt2 euler toolbox - expni/scalar Mode"

//////////////////////////////////////////////////////////////////////////////
// Test behavior of euler components in scalar mode
//////////////////////////////////////////////////////////////////////////////
/// created by jt the 08/12/2010
/// modified by jt the 23/03/2011
#include <boost/type_traits/is_same.hpp>
#include <nt2/sdk/functor/meta/call.hpp>
#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/memory/buffer.hpp>
#include <nt2/sdk/constant/real.hpp>
#include <nt2/sdk/constant/infinites.hpp>
#include <nt2/include/functions/ulpdist.hpp>
#include <nt2/toolbox/euler/include/expni.hpp>

NT2_TEST_CASE_TPL ( expni_real__2_0,  NT2_REAL_TYPES)
{
  
  using nt2::expni;
  using nt2::tag::expni_;
  typedef typename nt2::meta::as_integer<T>::type iT;
  typedef typename nt2::meta::call<expni_(iT,T)>::type r_t;
  typedef typename nt2::meta::upgrade<T>::type u_t;
  typedef T wished_r_t;


  // return type conformity test 
  NT2_TEST( (boost::is_same < r_t, wished_r_t >::value) );
  std::cout << std::endl; 
  double ulpd;
  ulpd=0.0;


  // specific values tests
  NT2_TEST_ULP_EQUAL(expni(1,nt2::Inf<T>()), nt2::Zero<r_t>(), 0);
  NT2_TEST_ULP_EQUAL(expni(1,nt2::Minf<T>()), nt2::Nan<r_t>(), 0);
  NT2_TEST_ULP_EQUAL(expni(1,nt2::Mone<T>()), nt2::Nan<r_t>(), 0);
  NT2_TEST_ULP_EQUAL(expni(1,nt2::Nan<T>()), nt2::Nan<r_t>(), 0);
  NT2_TEST_ULP_EQUAL(expni(1,nt2::Zero<T>()), nt2::Inf<r_t>(), 0);
  // random verifications
  static const uint32_t NR = NT2_NB_RANDOM_TEST;
  {
    NT2_CREATE_BUF(tab_a0,iT, NR, T(-10), T(10));
    NT2_CREATE_BUF(tab_a1,T, NR, T(-10), T(10));
    double ulp0, ulpd ; ulpd=ulp0=0.0;
    iT a0;
    T a1;
    for (uint32_t j =0; j < NR; ++j )
      {
        std::cout << "for params "
                  << "  a0 = "<< u_t(a0 = tab_a0[j])
                  << ", a1 = "<< u_t(a1 = tab_a1[j])
                  << std::endl;
        NT2_TEST_ULP_EQUAL( nt2::expni(a0,a1),nt2::expni(a0,a1),10);
        ulp0=nt2::max(ulpd,ulp0);
     }
     std::cout << "max ulp found is: " << ulp0 << std::endl;
   }
} // end of test for real_
