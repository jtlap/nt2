//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#define NT2_UNIT_MODULE "nt2 polynomials toolbox - polevl/scalar Mode"

//////////////////////////////////////////////////////////////////////////////
// cover test behavior of polynomials components in scalar mode
//////////////////////////////////////////////////////////////////////////////
/// created  by jt the 06/03/2011
///
#include <nt2/toolbox/polynomials/include/functions/polevl.hpp>
#include <nt2/include/functions/max.hpp>
//#include <nt2/toolbox/cephes/include/functions/polevl.hpp>

#include <boost/type_traits/is_same.hpp>
#include <nt2/sdk/functor/meta/call.hpp>
#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/memory/buffer.hpp>
#include <nt2/include/constants/real.hpp>
#include <nt2/include/constants/infinites.hpp>
//COMMENTED


NT2_TEST_CASE_TPL ( polevl_real__2_0,  NT2_REAL_TYPES)
{

//   using nt2::polevl;
//   using nt2::tag::polevl_;
//   typedef typename nt2::meta::as_integer<T>::type iT;
//   typedef typename nt2::meta::call<polevl_(T,T)>::type r_t;
//   typedef typename nt2::meta::upgrade<T>::type u_t;
//   typedef typename boost::dispatch::meta::as_floating<T>::type wished_r_t;


//   // return type conformity test
//   NT2_TEST( (boost::is_same < r_t, wished_r_t >::value) );
//   std::cout << std::endl;
//   double ulpd;
//   ulpd=0.0;

//   // random verifications
//   static const nt2::uint32_t NR = NT2_NB_RANDOM_TEST;
//   {
//     NT2_CREATE_BUF(tab_a0,T, NR, T(-10), T(10));
//     NT2_CREATE_BUF(tab_a1,T, NR, T(-10), T(10));
//     double ulp0, ulpd ; ulpd=ulp0=0.0;
//     T a0;
//     T a1;
//     for(nt2::uint32_t j =0; j < NR; ++j )
//       {
//         std::cout << "for params "
//                   << "  a0 = "<< u_t(a0 = tab_a0[j])
//                   << ", a1 = "<< u_t(a1 = tab_a1[j])
//                   << std::endl;
//         NT2_TEST_ULP_EQUAL( nt2::polevl(a0,a1),nt2::cephes::polevl(a0,a1),0.5);
//         ulp0=nt2::max(ulpd,ulp0);
//      }
//      std::cout << "max ulp found is: " << ulp0 << std::endl;
//    }
// } // end of test for floating_

// NT2_TEST_CASE_TPL ( polevl_unsigned_int__2_0,  NT2_UNSIGNED_TYPES)
// {

//   using nt2::polevl;
//   using nt2::tag::polevl_;
//   typedef typename nt2::meta::as_integer<T>::type iT;
//   typedef typename nt2::meta::call<polevl_(T,T)>::type r_t;
//   typedef typename nt2::meta::upgrade<T>::type u_t;
//   typedef typename boost::dispatch::meta::as_floating<T>::type wished_r_t;


//   // return type conformity test
//   NT2_TEST( (boost::is_same < r_t, wished_r_t >::value) );
//   std::cout << std::endl;
//   double ulpd;
//   ulpd=0.0;

// } // end of test for unsigned_int_

// NT2_TEST_CASE_TPL ( polevl_signed_int__2_0,  NT2_INTEGRAL_SIGNED_TYPES)
// {

//   using nt2::polevl;
//   using nt2::tag::polevl_;
//   typedef typename nt2::meta::as_integer<T>::type iT;
//   typedef typename nt2::meta::call<polevl_(T,T)>::type r_t;
//   typedef typename nt2::meta::upgrade<T>::type u_t;
//   typedef typename boost::dispatch::meta::as_floating<T>::type wished_r_t;


//   // return type conformity test
//   NT2_TEST( (boost::is_same < r_t, wished_r_t >::value) );
//   std::cout << std::endl;
//   double ulpd;
//   ulpd=0.0;

} // end of test for signed_int_
