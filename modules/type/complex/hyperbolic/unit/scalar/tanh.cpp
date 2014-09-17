//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/include/functions/tanh.hpp>
#include <nt2/include/functions/sin.hpp>
#include <nt2/include/functions/mul_i.hpp>
#include <nt2/include/functions/mul_minus_i.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/ulp.hpp>
#include <nt2/sdk/unit/module.hpp>

#include <nt2/constant/constant.hpp>


NT2_TEST_CASE_TPL ( tanh_real__1_0, NT2_REAL_TYPES)
{

  using nt2::tanh;
  using nt2::tag::tanh_;
  typedef std::complex<T> cT;

  {
    const int N = 2;
    cT inputs[N] =
      { cT(nt2::Zero<T>(),nt2::Zero<T>()), //0
        cT(nt2::Zero<T>(),nt2::Pi <T>()),  //16
      };

    cT results[N] =
      { cT(nt2::Zero<T>(),nt2::Zero<T>()),//0
        cT(nt2::Zero<T>(),nt2::Zero<T>()),//16
      };

    for(int i=0; i < N; i++)
    {
      std::cout << i << "  input = " << inputs[i] << " -> " << results[i] << " <-> " << nt2::tanh(inputs[i]) << std::endl;
      NT2_TEST_ULP_EQUAL(nt2::tanh(inputs[i]), results[i], 1);
      NT2_TEST_ULP_EQUAL(nt2::tanh(-inputs[i]), -results[i], 1);
    }
  }
#ifndef BOOST_SIMD_NO_INVALIDS
  {
    const int N = 20;
    cT inputs[N] =
      { cT(nt2::Zero<T>(),nt2::Zero<T>()), //0
        cT(nt2::Inf<T>(),nt2::Zero<T>()),  //1
        cT(nt2::Minf<T>(),nt2::Zero<T>()), //2
        cT(nt2::Nan<T>(),nt2::Zero<T>()),  //3
        cT(nt2::Zero<T>(),nt2::Inf<T>()),  //4
        cT(nt2::Inf<T>(),nt2::Inf<T>()),   //5
        cT(nt2::Minf<T>(),nt2::Inf<T>()),  //6
        cT(nt2::Nan<T>(),nt2::Inf<T>()),   //7
        cT(nt2::Zero<T>(),nt2::Minf<T>()), //8
        cT(nt2::Inf<T>(),nt2::Minf<T>()),  //9
        cT(nt2::Minf<T>(),nt2::Minf<T>()), //10
        cT(nt2::Nan<T>(),nt2::Minf<T>()),  //11
        cT(nt2::Zero<T>(),nt2::Nan<T>()),  //12
        cT(nt2::Inf<T>(),nt2::Nan<T>()),   //13
        cT(nt2::Minf<T>(),nt2::Nan<T>()),  //14
        cT(nt2::Nan<T>(),nt2::Nan<T>()),   //15
        cT(nt2::Zero<T>(),nt2::Pi <T>()),  //16
        cT(nt2::Inf<T>(),nt2::Pi <T>()),   //17
        cT(nt2::Minf<T>(),nt2::Pi <T>()),  //18
        cT(nt2::Nan<T>(),nt2::Pi <T>()),   //19
      };

    cT results[N] =
      { cT(nt2::Zero<T>(),nt2::Zero<T>()),//0
        cT(nt2::Nan<T>(),nt2::Zero<T>()), //1
        cT(nt2::Nan<T>(),nt2::Zero<T>()), //2
        cT(nt2::Nan<T>(),nt2::Zero<T>()), //3
        cT(nt2::Zero<T>(),nt2::Nan<T>()), //4
        cT(nt2::Nan<T>(),nt2::Nan<T>()),  //5
        cT(nt2::Nan<T>(),nt2::Nan<T>()),  //6
        cT(nt2::Nan<T>(),nt2::Nan<T>()),  //7
        cT(nt2::Zero<T>(),nt2::Nan<T>()), //8
        cT(nt2::Nan<T>(),nt2::Nan<T>()),  //9
        cT(nt2::Nan<T>(),nt2::Nan<T>()),  //10
        cT(nt2::Nan<T>(),nt2::Nan<T>()),  //11
        cT(nt2::Zero<T>(),nt2::Nan<T>()), //12
        cT(nt2::Nan<T>(),nt2::Nan<T>()),  //13
        cT(nt2::Nan<T>(),nt2::Nan<T>()),  //14
        cT(nt2::Nan<T>(),nt2::Nan<T>()),  //15
        cT(nt2::Zero<T>(),nt2::Zero<T>()),//16
        cT(nt2::Nan<T>(),nt2::Zero<T>()), //17
        cT(nt2::Nan<T>(),nt2::Zero<T>()), //18
        cT(nt2::Nan<T>(),nt2::Nan <T>()), //19
      };

    for(int i=0; i < N; i++)
    {
      std::cout << i << "  input = " << inputs[i] << " -> " << results[i] << " <-> " << nt2::tanh(inputs[i]) << std::endl;
      NT2_TEST_ULP_EQUAL(nt2::tanh(inputs[i]), results[i], 1);
      NT2_TEST_ULP_EQUAL(nt2::tanh(-inputs[i]), -results[i], 1);
    }
#endif
  }

} // end of test for floating_
