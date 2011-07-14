//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
//#define NT2_UNIT_MODULE "nt2 trigonometric toolbox - cos/scalar Mode"

//////////////////////////////////////////////////////////////////////////////
// cover test behavior of trigonometric components in scalar mode
//////////////////////////////////////////////////////////////////////////////
/// created  by jt the 11/02/2011
/// 
#include <nt2/toolbox/trigonometric/include/cos.hpp>
#include <nt2/toolbox/exponential/include/exp.hpp>
#include <nt2/toolbox/trigonometric/include/fast_cos.hpp>
#include <nt2/toolbox/standard/include/cos.hpp>
#include <nt2/include/functions/next.hpp>
#include <cmath>
#include <iomanip>

int main(){
  {
    float a0;
    int res[11] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    //    nt2::ctic();
    long long int j = 0;
    double t = 0.0; 
    //  for(a0 = 0.0f; a0 <= nt2::Pi<float>()/(4.0f*1024.0f); ) //= nt2::next(a0))
    nt2::ctic(); 
    for(j = 0;  j < 1955733432ll; ++j)
      {
	const float z = nt2::cos((nt2::Pio_4<float >())*j/1.95573432e+09f);
	++res[int(z)];
	// 	++j;
	//	++res[int(a0)%2];
	//	a0 = ::nextafterf(a0, nt2::Inf<float>()); 
      }
    t = nt2::ctoc()/j;
    std::cout << "cycles/elt = " << t << std::endl; 
    std::cout << "j         " << j   << std::endl; 
    for(int i =  0;  i <  10; ++i) if(true || res[i]) std::cout << res[i] << " values with error less than " << float(i)/2 << " ulp(s)" << std::endl;
    if(true || res[10])
      {
	std::cout << res[10] << " values with error bigger than " << float(10)/2 << " ulp(s)" << std::endl;
      }
  }
 //  {
//     typedef NT2_SIMD_DEFAULT_EXTENSION  ext_t;
//     typedef nt2::simd::native<float,ext_t>                        n_t;
//     float a0;
//     int res[11] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
//     //    nt2::ctic();
//     long long int j = 0;
//     double t = 0.0; 
//     for(a0 = 0.0f; a0 <= nt2::Pi<float>()/(4.0f*1024.0f);)// a0+= 1.0e-7) //= nt2::next(a0))
//       {
// 	n_t aa0 =  nt2::splat<n_t>(a0); 
// 	//	const n_t z = nt2::fast_cos(aa0);
// 	//	++res[int(z[0])%2];
// 	++res[int(j%2)]; 
// 	++j;
// 	a0 = ::nextafter(a0, nt2::Inf<float>()); 
//      }
// //     double cpe = nt2::ctoc()/j;
//      std::cout << "j         " << j   << std::endl; 
// //     std::cout << "cycle/elt " << cpe << std::endl;
// //     std::cout << "t/elt    " << t/j << std::endl;  
//     std::cout << std::endl; 
//     for(int i =  0;  i <  10; ++i) if(true || res[i]) std::cout << res[i] << " values with error less than " << float(i)/2 << " ulp(s)" << std::endl;
//     if(true || res[10])
//       {
// 	std::cout << res[10] << " values with error bigger than " << float(10)/2 << " ulp(s)" << std::endl;
//       }
//    }
//   return 0; 
  
 } // end of test for real_

