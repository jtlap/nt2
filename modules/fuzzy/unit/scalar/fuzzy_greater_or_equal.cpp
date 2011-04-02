//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#define NT2_UNIT_MODULE "nt2 fuzzy toolbox - fuzzy_greater_or_equal/scalar Mode"

//////////////////////////////////////////////////////////////////////////////
// Test behavior of fuzzy components in scalar mode
//////////////////////////////////////////////////////////////////////////////
/// created  by jt the 04/03/2011
/// modified by jt the 21/03/2011
#include <boost/type_traits/is_same.hpp>
#include <nt2/sdk/functor/meta/call.hpp>
#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/memory/buffer.hpp>
#include <nt2/sdk/constant/real.hpp>
#include <nt2/sdk/constant/infinites.hpp>
#include <nt2/include/functions/ulpdist.hpp>
#include <nt2/toolbox/fuzzy/include/fuzzy_greater_or_equal.hpp>
// specific includes for arity 3 tests
#include <nt2/sdk/meta/logical.hpp>

NT2_TEST_CASE_TPL ( fuzzy_greater_or_equal_real__3_0,  NT2_REAL_TYPES)
{
  
  using nt2::fuzzy_greater_or_equal;
  using nt2::tag::fuzzy_greater_or_equal_;
  typedef typename nt2::meta::as_integer<T>::type iT;
  typedef typename nt2::meta::call<fuzzy_greater_or_equal_(T,T,T)>::type r_t;
  typedef typename nt2::meta::upgrade<T>::type u_t;
  typedef typename nt2::meta::logical<T>::type wished_r_t;


  // return type conformity test 
  NT2_TEST( (boost::is_same < r_t, wished_r_t >::value) );
  std::cout << std::endl; 
  double ulpd;
  ulpd=0.0;


  // specific values tests
  NT2_TEST_EQUAL(fuzzy_greater_or_equal(T(0),T(0),T(1)), nt2::True<r_t>());
  NT2_TEST_EQUAL(fuzzy_greater_or_equal(T(1),1+nt2::Eps<T>(),nt2::Eps<T>()), nt2::True<r_t>());
  NT2_TEST_EQUAL(fuzzy_greater_or_equal(T(1),T(2),T(0.25)), nt2::False<r_t>());
  NT2_TEST_EQUAL(fuzzy_greater_or_equal(T(1),T(2),T(1)), nt2::True<r_t>());
  // random verifications
  static const uint32_t NR = NT2_NB_RANDOM_TEST;
  {
    NT2_CREATE_BUF(tab_a0,T, NR, T(-10), T(10));
    NT2_CREATE_BUF(tab_a1,T, NR, T(-10), T(10));
    NT2_CREATE_BUF(tab_a2,T, NR, T(-10), T(10));
    double ulp0, ulpd ; ulpd=ulp0=0.0;
    T a0;
    T a1;
    T a2;
    for (uint32_t j =0; j < NR; ++j )
      {
        std::cout << "for params "
                  << "  a0 = "<< u_t(a0 = tab_a0[j])
                  << ", a1 = "<< u_t(a1 = tab_a1[j])
                  << ", a2 = "<< u_t(a2 = tab_a2[j])
                  << std::endl;
        NT2_TEST_EQUAL( nt2::fuzzy_greater_or_equal(a0,a1,a2),nt2::fuzzy_greater_or_equal(a0,a1,a2));
     }
     
   }
} // end of test for real_
