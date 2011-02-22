//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#define NT2_UNIT_MODULE "nt2 elliptic toolbox - ellipke/simd Mode"

//////////////////////////////////////////////////////////////////////////////
// Test behavior of elliptic components in simd mode
//////////////////////////////////////////////////////////////////////////////
/// created  by jt the 21/02/2011
/// modified by jt the 21/02/2011
#include <nt2/sdk/memory/is_aligned.hpp>
#include <nt2/sdk/memory/aligned_type.hpp>
#include <nt2/sdk/memory/load.hpp>
#include <nt2/sdk/memory/buffer.hpp>
#include <boost/type_traits/is_same.hpp>
#include <nt2/sdk/functor/meta/call.hpp>
#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/constant/real.hpp>
#include <nt2/sdk/constant/infinites.hpp>
#include <nt2/include/functions/max.hpp>
#include <nt2/toolbox/elliptic/include/ellipke.hpp>
#include <boost/fusion/tuple.hpp>
#include <boost/fusion/tuple.hpp>

NT2_TEST_CASE_TPL ( ellipke_real__1,  NT2_REAL_TYPES)
{
  using nt2::ellipke;
  using nt2::tag::ellipke_;
  using nt2::load; 
  using nt2::simd::native;
  using nt2::meta::cardinal_of;
  typedef NT2_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef typename nt2::meta::upgrade<T>::type   u_t;
  typedef native<T,ext_t>                        n_t;
  typedef n_t                                     vT;
  typedef typename nt2::meta::as_integer<T>::type iT;
  typedef native<iT,ext_t>                       ivT;
  typedef typename nt2::meta::call<ellipke_(vT)>::type r_t;
  typedef typename nt2::meta::call<ellipke_(T)>::type sr_t;
  typedef typename nt2::meta::scalar_of<r_t>::type ssr_t;

  // random verifications
  static const uint32_t NR = NT2_NB_RANDOM_TEST;
  {
    NT2_CREATE_BUF(tab_a0,T, NR, T(0), T(1));
    NT2_CREATE_BUF(tab_a1,T, NR, T(0), T(1));
    double ulp0 = 0.0, ulpd = 0.0;

     for(int j = 0; j < NR/cardinal_of<n_t>::value; j++)
      {
        vT a0 = load<vT>(&tab_a0[0],j);
        r_t r = nt2::ellipke(a0);  
        for(int i = 0; i< cardinal_of<n_t>::value; i++)
         {
          int k = i+j*cardinal_of<n_t>::value;
          sr_t sr =  nt2::ellipke(tab_a0[k]);
	  std::cout << a0 << "         " << tab_a0[k] << std::endl; 
	  std::cout << boost::fusion::get<0>(r) << "         " << boost::fusion::get<1>(r) << std::endl; 
	  std::cout << boost::fusion::get<0>(sr) << "         " << boost::fusion::get<1>(sr) << std::endl; 
           NT2_TEST_TUPLE_ULP_EQUAL( boost::fusion::get<0>(r)[i],
                                    boost::fusion::get<0>(sr), 1.5);
          ulp0 = nt2::max(ulpd,ulp0);
          NT2_TEST_TUPLE_ULP_EQUAL( boost::fusion::get<1>(r)[i],
                                    boost::fusion::get<1>(sr), 1.5);
          ulp0 = nt2::max(ulpd,ulp0);
        }
      }  
    std::cout << "max ulp found is: " << ulp0 << std::endl;
  }
} // end of test for real_
 
// NT2_TEST_CASE_TPL ( ellipke_real__2,  NT2_REAL_TYPES)
// {
//   using nt2::ellipke;
//   using nt2::tag::ellipke_;
//   using nt2::load; 
//   using nt2::simd::native;
//   using nt2::meta::cardinal_of;
//   typedef NT2_SIMD_DEFAULT_EXTENSION  ext_t;
//   typedef typename nt2::meta::upgrade<T>::type   u_t;
//   typedef native<T,ext_t>                        n_t;
//   typedef n_t                                     vT;
//   typedef typename nt2::meta::as_integer<T>::type iT;
//   typedef native<iT,ext_t>                       ivT;
//   typedef typename nt2::meta::call<ellipke_(vT,vT)>::type r_t;
//   typedef typename nt2::meta::call<ellipke_(T,T)>::type sr_t;
//   typedef typename nt2::meta::scalar_of<r_t>::type ssr_t;

//   // random verifications
//   static const uint32_t NR = NT2_NB_RANDOM_TEST;
//   {
//     NT2_CREATE_BUF(tab_a0,T, NR, T(0), T(1));
//     NT2_CREATE_BUF(tab_a1,T, NR/cardinal_of<n_t>::value, T(0), T(0.01));
//     double ulp0 = 0.0, ulpd = 0.0;
//     for(int j = 0; j < NR/cardinal_of<n_t>::value; j++)
//       {
//         vT a0 = load<vT>(&tab_a0[0],j);
//         T a1 = tab_a1[j];
//         r_t r = nt2::ellipke(a0,a1);
//         for(int i = 0; i< cardinal_of<n_t>::value; i++)
//         {
//           int k = i+j*cardinal_of<n_t>::value;
//           sr_t sr =  nt2::ellipke(tab_a0[k],tab_a1[j]);
//           NT2_TEST_TUPLE_ULP_EQUAL( boost::fusion::get<0>(r)[i],
//                                     boost::fusion::get<0>(sr), 1.5);
//           ulp0 = nt2::max(ulpd,ulp0);
//           NT2_TEST_TUPLE_ULP_EQUAL( boost::fusion::get<1>(r)[i],
//                                     boost::fusion::get<1>(sr), 1.5);
//           ulp0 = nt2::max(ulpd,ulp0);
//         }
//       }
//     std::cout << "max ulp found is: " << ulp0 << std::endl;
//   }
// } // end of test for real_
