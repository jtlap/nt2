//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#define NT2_UNIT_MODULE "nt2 swar toolbox - lookup/scalar Mode"

//////////////////////////////////////////////////////////////////////////////
// Test behavior of swar components in scalar mode
//////////////////////////////////////////////////////////////////////////////
/// created  by jt the 24/02/2011
/// modified by jt the 04/03/2011
#include <boost/type_traits/is_same.hpp>
#include <nt2/sdk/functor/meta/call.hpp>
#include <nt2/sdk/unit/no_ulp_tests.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/memory/buffer.hpp>
#include <nt2/sdk/constant/real.hpp>
#include <nt2/sdk/constant/infinites.hpp>
#include <nt2/include/functions/ulpdist.hpp>
#include <nt2/toolbox/swar/include/lookup.hpp>

NT2_TEST_CASE_TPL ( lookup_real__2,  NT2_REAL_TYPES)
{
  
  using nt2::lookup;
  using nt2::tag::lookup_;
  typedef typename nt2::meta::as_integer<T>::type iT;
  typedef typename nt2::meta::call<lookup_(T,iT)>::type r_t;
  typedef typename nt2::meta::upgrade<T>::type u_t;
  typedef T wished_r_t;


  // return type conformity test 
  NT2_TEST( (boost::is_same < r_t, wished_r_t >::value) );
  std::cout << std::endl; 
  double ulpd;


  // specific values tests
  NT2_TEST_EQUAL(lookup(nt2::Inf<T>(),0), nt2::Inf<r_t>());
  NT2_TEST_EQUAL(lookup(nt2::Minf<T>(),0), nt2::Minf<r_t>());
  NT2_TEST_EQUAL(lookup(nt2::Mone<T>(),0), nt2::Mone<r_t>());
  NT2_TEST_EQUAL(lookup(nt2::Nan<T>(),0), nt2::Nan<r_t>());
  NT2_TEST_EQUAL(lookup(nt2::One<T>(),0), nt2::One<r_t>());
  NT2_TEST_EQUAL(lookup(nt2::Zero<T>(),0), nt2::Zero<r_t>());
  // random verifications
  static const uint32_t NR = NT2_NB_RANDOM_TEST;
  {
    NT2_CREATE_BUF(tab_a0,T, NR, T(-100), T(100));
    NT2_CREATE_BUF(tab_a1,iT, NR, T(-100), T(100));
    double ulp0 = 0.0, ulpd = 0.0;
    T a0;
    iT a1;
    for (int j =0; j < NR; ++j )
      {
        std::cout << "for params "
                  << "  a0 = "<< u_t(a0 = tab_a0[j])
                  << ", a1 = "<< u_t(a1 = tab_a1[j])
                  << std::endl;
        NT2_TEST_EQUAL( nt2::lookup(a0,a1),a0);
     }
     
   }
} // end of test for real_
