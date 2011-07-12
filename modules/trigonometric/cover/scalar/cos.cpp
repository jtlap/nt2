//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#define NT2_UNIT_MODULE "nt2 trigonometric toolbox - cos/scalar Mode"

//////////////////////////////////////////////////////////////////////////////
// cover test behavior of trigonometric components in scalar mode
//////////////////////////////////////////////////////////////////////////////
/// created  by jt the 11/02/2011
/// 
#include <nt2/toolbox/trigonometric/include/cos.hpp>
#include <nt2/toolbox/trigonometric/include/fast_cos.hpp>
#include <nt2/include/functions/ulpdist.hpp>
#include <nt2/include/functions/max.hpp>
#include <nt2/toolbox/trigonometric/include/constants.hpp>
extern "C" {extern long double cephes_cosl(long double);}

#include <boost/type_traits/is_same.hpp>
#include <nt2/sdk/functor/meta/call.hpp>
#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/memory/buffer.hpp>
#include <nt2/include/constants/real.hpp>
#include <nt2/include/constants/infinites.hpp>
#include <nt2/toolbox/libc/include/cos.hpp>
#include <nt2/toolbox/crlibm/include/cos_rn.hpp>
#include <nt2/toolbox/cephes/include/cos.hpp>
#include <nt2/toolbox/standard/include/cos.hpp>
#include <nt2/include/functions/next.hpp>
#include <nt2/include/functions/ulpdist.hpp>
#include <nt2/include/functions/max.hpp>
#include <nt2/include/functions/iceil.hpp>
#include <cmath>
NT2_TEST_CASE_TPL ( cos_real__1_0,  (float))
{
  
  using nt2::cos;
  using nt2::tag::cos_;
  typedef typename nt2::meta::as_integer<T>::type iT;
  typedef typename nt2::meta::call<cos_(T)>::type r_t;
  typedef typename nt2::meta::upgrade<T>::type u_t;
  typedef typename boost::result_of<nt2::meta::floating(T)>::type wished_r_t;


  // return type conformity test 
  NT2_TEST( (boost::is_same < r_t, wished_r_t >::value) );
  std::cout << std::endl; 
  double ulpd;
  ulpd=0.0;

  static const nt2::uint32_t NR = NT2_NB_RANDOM_TEST;
  {
    double ulp0, ulpd ; ulpd=ulp0=0.0;
    T a0;
    int res[11] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}; 
    for(a0 = 0.0f; a0 <= nt2::Pi<T>()/4; a0 = nt2::next(a0))
      {
	T r = nt2::ulpdist(nt2::fast_cos(a0),std::cos(a0)); 
// 	if (r > 1)
// 	  {
// 	    std::cout << "for a0 = " << std::setprecision(10) << a0 <<  " error if of " << r << " ulps" << std::endl;
// 	  }
	++res[nt2::min(int(2*r), 10)]; 
     }
    std::cout << std::endl; 
    for(int i =  0;  i <  10; ++i) if(res[i]) std::cout << res[i] << " values with error less than " << float(i)/2 << " ulp(s)" << std::endl;
    if(res[10])
      {
	std::cout << res[10] << " values with error bigger than " << float(10)/2 << " ulp(s)" << std::endl;
      }
   }
//   // random verifications
//   static const nt2::uint32_t NR = NT2_NB_RANDOM_TEST;
//   {
//     NT2_CREATE_BUF(tab_a0,T, NR, -100000*nt2::Pi<T>(), 100000*nt2::Pi<T>());
//     double ulp0, ulpd ; ulpd=ulp0=0.0;
//     T a0;
//     for(nt2::uint32_t j =0; j < NR; ++j )
//       {
//         std::cout << "for param "
//                   << "  a0 = "<< u_t(a0 = tab_a0[j])
//                   << std::endl;
//         NT2_TEST_ULP_EQUAL( nt2::cos(a0),nt2::crlibm::cos_rn(a0),0.5);
//         ulp0=nt2::max(ulpd,ulp0);
//      }
//      std::cout << "max ulp found is: " << ulp0 << std::endl;
//    }
//    static const nt2::uint32_t NR = NT2_NB_RANDOM_TEST;
//   {
//     NT2_CREATE_BUF(tab_a0,T, NR, -100000*nt2::Pi<T>(), 100000*nt2::Pi<T>());
//     double ulp0, ulpd ; ulpd=ulp0=0.0;
//     T a0;
//     for(nt2::uint32_t j =0; j < NR; ++j )
//       {
//         std::cout << "for param "
//                   << "  a0 = "<< u_t(a0 = tab_a0[j])
//                   << std::endl;
//         NT2_TEST_ULP_EQUAL( nt2::cos(a0),nt2::crlibm::cos_rn(a0),1);
//         ulp0=nt2::max(ulpd,ulp0);
//      }
//      std::cout << "max ulp found is: " << ulp0 << std::endl;
//    }
//   {
//     NT2_CREATE_BUF(tab_a0,T, NR, -200*T(1), 200*T(1));
//     double ulp0, ulpd ; ulpd=ulp0=0.0;
//     T a0;
//     for(nt2::uint32_t j =0; j < NR; ++j )
//       {
//         std::cout << "for param "
//                   << "  a0 = "<< u_t(a0 = tab_a0[j])
//                   << std::endl;
//         NT2_TEST_ULP_EQUAL( nt2::cos(a0),nt2::crlibm::cos_rn(a0),1);
//         ulp0=nt2::max(ulpd,ulp0);
//      }
//      std::cout << "max ulp found is: " << ulp0 << std::endl;
//    }
//   {
//     NT2_CREATE_BUF(tab_a0,T, NR, -100*nt2::Pi<T>(), 100*nt2::Pi<T>());
//     double ulp0, ulpd ; ulpd=ulp0=0.0;
//     T a0;
//     for(nt2::uint32_t j =0; j < NR; ++j )
//       {
//         std::cout << "for param "
//                   << "  a0 = "<< u_t(a0 = tab_a0[j])
//                   << std::endl;
//         NT2_TEST_ULP_EQUAL( nt2::cos(a0),nt2::crlibm::cos_rn(a0),1);
//         ulp0=nt2::max(ulpd,ulp0);
//      }
//      std::cout << "max ulp found is: " << ulp0 << std::endl;
//    }
//   {
//     NT2_CREATE_BUF(tab_a0,T, NR, -1000*nt2::Pi<T>(), 1000*nt2::Pi<T>());
//     double ulp0, ulpd ; ulpd=ulp0=0.0;
//     T a0;
//     for(nt2::uint32_t j =0; j < NR; ++j )
//       {
//         std::cout << "for param "
//                   << "  a0 = "<< u_t(a0 = tab_a0[j])
//                   << std::endl;
//         NT2_TEST_ULP_EQUAL( nt2::cos(a0),nt2::crlibm::cos_rn(a0),1);
//         ulp0=nt2::max(ulpd,ulp0);
//      }
//      std::cout << "max ulp found is: " << ulp0 << std::endl;
//    }
//   {
//     NT2_CREATE_BUF(tab_a0,T, NR, -T(1.0e35), T(1.0e35));
//     double ulp0, ulpd ; ulpd=ulp0=0.0;
//     T a0;
//     for(nt2::uint32_t j =0; j < NR; ++j )
//       {
//         std::cout << "for param "
//                   << "  a0 = "<< u_t(a0 = tab_a0[j])
// 	          << "  nt2::cos(a0)  "<<nt2::cos(a0)
// 	          << "  nt2::crlibm::cos_rn(a0) "<<nt2::crlibm::cos_rn(a0)
//                   << std::endl;
//         NT2_TEST_ULP_EQUAL( nt2::cos(a0),nt2::crlibm::cos_rn(a0),1);
//         ulp0=nt2::max(ulpd,ulp0);
//      }
//      std::cout << "max ulp found is: " << ulp0 << std::endl;
//    }

  
} // end of test for real_

