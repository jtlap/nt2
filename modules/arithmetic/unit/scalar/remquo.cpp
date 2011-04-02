//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#define NT2_UNIT_MODULE "nt2 arithmetic toolbox - remquo/scalar Mode"

//////////////////////////////////////////////////////////////////////////////
// Test behavior of arithmetic components in scalar mode
//////////////////////////////////////////////////////////////////////////////
/// created by jt the 01/12/2010
/// modified by jt the 23/03/2011
#include <boost/type_traits/is_same.hpp>
#include <nt2/sdk/functor/meta/call.hpp>
#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/memory/buffer.hpp>
#include <nt2/sdk/constant/real.hpp>
#include <nt2/sdk/constant/infinites.hpp>
#include <nt2/include/functions/max.hpp>
#include <nt2/toolbox/arithmetic/include/remquo.hpp>
#include <boost/fusion/tuple.hpp>
// specific includes for arity 2 tests
#include <boost/fusion/tuple.hpp>
#include <nt2/include/functions/remainder.hpp>
#include <nt2/include/functions/idivround.hpp>

NT2_TEST_CASE_TPL ( remquo_real__2_0,  NT2_REAL_TYPES)
{
  
  using nt2::remquo;
  using nt2::tag::remquo_;
  typedef typename nt2::meta::as_integer<T>::type iT;
  typedef typename nt2::meta::call<remquo_(T,T)>::type r_t;
  typedef typename nt2::meta::upgrade<T>::type u_t;
  typedef boost::fusion::tuple<T,typename nt2::meta::as_integer<T,signed>::type> wished_r_t;


  // return type conformity test 
  NT2_TEST( (boost::is_same < r_t, wished_r_t >::value) );
  std::cout << std::endl; 
  double ulpd;
  ulpd=0.0;

  // random verifications
  static const uint32_t NR = NT2_NB_RANDOM_TEST;
  {
    NT2_CREATE_BUF(tab_a0,T, NR, T(0), T(10));
    NT2_CREATE_BUF(tab_a1,T, NR, T(0), T(10));
    double ulp0, ulpd ; ulpd=ulp0=0.0;
    T a0;
    T a1;
    for (uint32_t j =0; j < NR; ++j )
      {
        std::cout << "for params "
                  << "  a0 = "<< u_t(a0 = tab_a0[j])
                  << ", a1 = "<< u_t(a1 = tab_a1[j])
                  << std::endl;
        r_t r = nt2::remquo(a0,a1);
        typedef typename nt2::meta::strip<typename boost::fusion::result_of::at_c<r_t,0>::type>::type r_t0;
        typedef typename nt2::meta::strip<typename boost::fusion::result_of::at_c<r_t,1>::type>::type r_t1;
        r_t0 r0 = boost::fusion::get<0>(r);
        r_t1 r1 = boost::fusion::get<1>(r);
        NT2_TEST_TUPLE_ULP_EQUAL( r0, nt2::remainder(a0,a1), 0);
        NT2_TEST_TUPLE_ULP_EQUAL( r1, nt2::idivround(a0,a1), 0);
     }
     std::cout << "max ulp found is: " << ulp0 << std::endl;
   }
} // end of test for real_
