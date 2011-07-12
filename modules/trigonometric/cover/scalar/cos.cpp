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
//#include <nt2/toolbox/trigonometric/include/cos.hpp>
#include <nt2/toolbox/trigonometric/include/fast_cos.hpp>
// #include <nt2/include/functions/ulpdist.hpp>
// #include <nt2/include/functions/max.hpp>
// #include <nt2/toolbox/trigonometric/include/constants.hpp>
// extern "C" {extern long double cephes_cosl(long double);}

// #include <boost/type_traits/is_same.hpp>
// #include <nt2/sdk/functor/meta/call.hpp>
// #include <nt2/sdk/unit/tests.hpp>
// #include <nt2/sdk/unit/module.hpp>
// #include <nt2/sdk/memory/buffer.hpp>
// #include <nt2/include/constants/real.hpp>
// #include <nt2/include/constants/infinites.hpp>
// #include <nt2/toolbox/libc/include/cos.hpp>
// #include <nt2/toolbox/crlibm/include/cos_rn.hpp>
// #include <nt2/toolbox/cephes/include/cos.hpp>
// #include <nt2/toolbox/standard/include/cos.hpp>
#include <nt2/include/functions/next.hpp>
//#include <nt2/include/functions/ulpdist.hpp>
//#include <nt2/include/functions/max.hpp>
// #include <nt2/include/functions/iceil.hpp>
// #include <cmath>

int main(){
  {
    float a0;
    int res[11] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}; 
    for(a0 = 0.0f; a0 <= nt2::Pi<float>()/4; a0 = nt2::next(a0))
      {
	++res[int(nt2::fast_cos(a0))];
     }
    std::cout << std::endl; 
    for(int i =  0;  i <  10; ++i) if(res[i]) std::cout << res[i] << " values with error less than " << float(i)/2 << " ulp(s)" << std::endl;
    if(res[10])
      {
	std::cout << res[10] << " values with error bigger than " << float(10)/2 << " ulp(s)" << std::endl;
      }
   }
  return 0; 
  
} // end of test for real_

