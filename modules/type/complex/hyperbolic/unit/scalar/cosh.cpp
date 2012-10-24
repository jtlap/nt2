//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#define NT2_UNIT_MODULE "nt2 complex.exponential toolbox - cosh/scalar Mode"

//////////////////////////////////////////////////////////////////////////////
// unit test behavior of exponential components in scalar mode
//////////////////////////////////////////////////////////////////////////////
/// created by jt the 08/12/2010
/// 
#include <nt2/include/functions/cosh.hpp>
#include <nt2/include/functions/cos.hpp>
#include <nt2/include/functions/mul_i.hpp>
#include <nt2/include/functions/ulpdist.hpp>
#include <boost/type_traits/is_same.hpp>
#include <nt2/sdk/functor/meta/call.hpp>
#include <nt2/sdk/meta/as_integer.hpp>
#include <nt2/sdk/meta/as_floating.hpp>
#include <nt2/sdk/meta/as_signed.hpp>
#include <nt2/sdk/meta/upgrade.hpp>
#include <nt2/sdk/meta/downgrade.hpp>
#include <nt2/sdk/meta/scalar_of.hpp>
#include <boost/dispatch/meta/as_floating.hpp>
#include <boost/type_traits/common_type.hpp>
#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/memory/buffer.hpp>
#include <nt2/toolbox/constant/constant.hpp>


NT2_TEST_CASE_TPL ( cosh_real__1_0,  NT2_REAL_TYPES)
{
  
  using nt2::cosh;
  using nt2::tag::cosh_;
  typedef std::complex<T> cT; 
  double ulpd;
  ulpd=0.0;
  const int N = 20;
  T Pie =  nt2::Pi <T>()-nt2::Eps<T>(); 
  cT inputs[N] =
    { cT(nt2::Zero<T>(),nt2::Zero<T>()),//0   cT(nt2::One<T>(), nt2::Zero<T>()),//0 ok
      cT(nt2::Inf<T>(),nt2::Zero<T>()), //1   cT(nt2::Inf<T>(),nt2::Zero<T>()), //1 ok
      cT(nt2::Minf<T>(),nt2::Zero<T>()),//2   cT(nt2::Inf<T>(),nt2::Zero<T>()), //2 ok
      cT(nt2::Nan<T>(),nt2::Zero<T>()), //3   cT(nt2::Nan<T>(),nt2::Zero<T>()), //3 ok
      cT(nt2::Zero<T>(),nt2::Inf<T>()), //4   cT(nt2::Nan<T>(), nt2::Zero<T>()),//4 ok
      cT(nt2::Inf<T>(),nt2::Inf<T>()),  //5   cT(nt2::Inf<T>(),nt2::Nan<T>()),  //5 ok 
      cT(nt2::Minf<T>(),nt2::Inf<T>()), //6   cT(nt2::Inf<T>(),nt2::Nan<T>()),  //6 
      cT(nt2::Nan<T>(),nt2::Inf<T>()),  //7   cT(nt2::Nan<T>(),nt2::Nan<T>()),  //7 
      cT(nt2::Zero<T>(),nt2::Minf<T>()),//8   cT(nt2::Nan<T>(), nt2::Zero<T>()),//8 
      cT(nt2::Inf<T>(),nt2::Minf<T>()), //9   cT(nt2::Inf<T>(),nt2::Nan<T>()),  //9 
      cT(nt2::Minf<T>(),nt2::Minf<T>()),//10  cT(nt2::Inf<T>(),nt2::Nan<T>()),  //10
      cT(nt2::Nan<T>(),nt2::Minf<T>()), //11  cT(nt2::Nan<T>(),nt2::Nan<T>()), //11
      cT(nt2::Zero<T>(),nt2::Nan<T>()), //12  cT(nt2::Zero<T>(),nt2::Nan<T>()), //12
      cT(nt2::Inf<T>(),nt2::Nan<T>()),  //13  cT(nt2::Inf<T>(),nt2::Nan<T>()),  //13
      cT(nt2::Minf<T>(),nt2::Nan<T>()), //14  cT(nt2::Inf<T>(),nt2::Nan<T>()), //14
      cT(nt2::Nan<T>(),nt2::Nan<T>()),  //15  cT(nt2::Nan<T>(),nt2::Nan<T>()),  //15
      cT(nt2::Zero<T>(),Pie),           //16  cT(nt2::Mone<T>(),nt2::Zero<T>()),//16
      cT(nt2::Inf<T>(),Pie),            //17  cT(nt2::Minf<T>(),nt2::Inf<T>()), //17
      cT(nt2::Minf<T>(),Pie),           //18  cT(nt2::Minf<T>(),nt2::Minf<T>()),//18
      cT(nt2::Nan<T>(),Pie),            //19  cT(nt2::Nan<T>(),nt2::Nan <T>()),  //19
    }; 

  cT results[N] = 
    { cT(nt2::One<T>(), nt2::Zero<T>()),//0 
      cT(nt2::Inf<T>(),nt2::Zero<T>()), //1 
      cT(nt2::Inf<T>(),nt2::Zero<T>()), //2 
      cT(nt2::Nan<T>(),nt2::Zero<T>()), //3 
      cT(nt2::Nan<T>(), nt2::Zero<T>()),//4 
      cT(nt2::Inf<T>(),nt2::Nan<T>()),  //5 
      cT(nt2::Inf<T>(),nt2::Nan<T>()),  //6 
      cT(nt2::Nan<T>(),nt2::Nan<T>()),  //7 
      cT(nt2::Nan<T>(), nt2::Zero<T>()),//8 
      cT(nt2::Inf<T>(),nt2::Nan<T>()),  //9 
      cT(nt2::Inf<T>(),nt2::Nan<T>()),  //10
      cT(nt2::Nan<T>(),nt2::Nan<T>()),  //11
      cT(nt2::Nan<T>(),nt2::Zero<T>()), //12
      cT(nt2::Inf<T>(),nt2::Nan<T>()),  //13
      cT(nt2::Inf<T>(),nt2::Nan<T>()),  //14
      cT(nt2::Nan<T>(),nt2::Nan<T>()),  //15
      cT(nt2::Mone<T>(),nt2::Zero<T>()),//16
      cT(nt2::Minf<T>(),nt2::Inf<T>()), //17
      cT(nt2::Minf<T>(),nt2::Minf<T>()),//18
      cT(nt2::Nan<T>(),nt2::Nan <T>()), //19
    }; 

  for(int i=0; i < N; i++)
   {
     std::cout << i << " input = " << inputs[i] << " -> " << results[i] << std::endl; 
     NT2_TEST_EQUAL(nt2::cosh(inputs[i]), results[i]);
     NT2_TEST_EQUAL(nt2::cosh(-inputs[i]), nt2::cosh(inputs[i]));  
     NT2_TEST_EQUAL(nt2::cosh(inputs[i]), std::cos(nt2::mul_i(inputs[i]))); 
   }

} // end of test for floating_
