//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#define NT2_UNIT_MODULE "nt2 trigonometric toolbox - sincos/scalar Mode"

//////////////////////////////////////////////////////////////////////////////
// cover test behavior of trigonometric components in scalar mode
//////////////////////////////////////////////////////////////////////////////
/// created  by jt the 11/02/2011
/// 
#include <nt2/toolbox/arithmetic/include/rem_pio2.hpp>
#include <nt2/include/functions/ulpdist.hpp>
#include <nt2/include/functions/max.hpp>
#include <boost/fusion/tuple.hpp>
#include <nt2/toolbox/trigonometric/include/constants.hpp>

#include <boost/type_traits/is_same.hpp>
#include <nt2/sdk/functor/meta/call.hpp>
#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/memory/buffer.hpp>
#include <nt2/include/constants/real.hpp>
#include <nt2/include/constants/infinites.hpp>

//COMMENTED

NT2_TEST_CASE_TPL ( rem_pio2__1_0,  NT2_REAL_TYPES)
{
  
  using nt2::rem_pio2;
  using nt2::tag::rem_pio2_;
  typedef typename boost::result_of<nt2::meta::floating(T)>::type ftype;
  typedef typename nt2::meta::as_integer<T>::type iT;
  typedef typename nt2::meta::call<rem_pio2_(T, T, T)>::type r_t;
  typedef typename nt2::meta::upgrade<T>::type u_t;
  typedef int32_t wished_r_t;


  // return type conformity test 
  NT2_TEST( (boost::is_same < r_t, wished_r_t >::value) );
  std::cout << std::endl; 
  double ulpd;
  ulpd=0.0;
  T a0 = 0, a1, a2;
  int32_t n = nt2::rem_pio2(a0, a1, a2);
  std::cout << "a0 " << a0 << std::endl;
  std::cout << "n  " << n  << std::endl;   
  std::cout << "a1 " << a1 << std::endl;    
  std::cout << "a2 " << a2 << std::endl;
  a0 =  nt2::Pi<T>(); 
  n = nt2::rem_pio2(a0, a1, a2);
  std::cout << "a0 " << a0 << std::endl;
  std::cout << "n  " << n  << std::endl;   
  std::cout << "a1 " << a1 << std::endl;    
  std::cout << "a2 " << a2 << std::endl;
  a0 =  nt2::Pi<T>()/4; 
  n = nt2::rem_pio2(a0, a1, a2);
  std::cout << "a0 " << a0 << std::endl;
  std::cout << "n  " << n  << std::endl;   
  std::cout << "a1 " << a1 << std::endl;    
  std::cout << "a2 " << a2 << std::endl;
  a0 =  nt2::Pi<T>()*10+T(0.5); 
  n = nt2::rem_pio2(a0, a1, a2);
  std::cout << "a0 " << a0 << std::endl;
  std::cout << "n  " << n  << std::endl;   
  std::cout << "a1 " << a1 << std::endl;    
  std::cout << "a2 " << a2 << std::endl;
//   // random verifications
//   static const nt2::uint32_t NR = NT2_NB_RANDOM_TEST;
//   {
//     typedef typename boost::result_of<nt2::meta::floating(T)>::type ftype;
//     NT2_CREATE_BUF(tab_a0,T, NR, -20*nt2::Pi<T>(), 20*nt2::Pi<T>());
//     double ulp0, ulpd ; ulpd=ulp0=0.0;
//     T a0;
//     for(nt2::uint32_t j =0; j < NR; ++j )
//       {
//         std::cout << "for param "
//                   << "  a0 = "<< u_t(a0 = tab_a0[j])
//                   << std::endl;
//         r_t r = nt2::sincos(a0);
//         typedef typename nt2::meta::strip<typename boost::fusion::result_of::at_c<r_t,0>::type>::type r_t0;
//         typedef typename nt2::meta::strip<typename boost::fusion::result_of::at_c<r_t,1>::type>::type r_t1;
//         r_t0 r0 = boost::fusion::get<0>(r);
//         r_t1 r1 = boost::fusion::get<1>(r);
//         NT2_TEST_TUPLE_ULP_EQUAL( r0, (T)::sinl(a0), 0.5);
//         NT2_TEST_TUPLE_ULP_EQUAL( r1, (T)::cosl(a0), 0.5);
//      }
//      std::cout << "max ulp found is: " << ulp0 << std::endl;
//    }
} // end of test for real_
