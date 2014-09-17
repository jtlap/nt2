//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/include/functions/sinh.hpp>
#include <nt2/include/functions/sin.hpp>
#include <nt2/include/functions/mul_i.hpp>
#include <nt2/include/functions/mul_minus_i.hpp>
#include <nt2/sdk/functor/meta/call.hpp>
#include <nt2/sdk/meta/as_integer.hpp>
#include <nt2/sdk/meta/as_floating.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/ulp.hpp>
#include <nt2/sdk/unit/module.hpp>

#include <nt2/constant/constant.hpp>

NT2_TEST_CASE_TPL ( sinh_real__1_0, (double))
{
  using nt2::sinh;
  using nt2::tag::sinh_;
  typedef std::complex<T> cT;

  {
    const int N = 2;
    cT inputs[] =
      { cT(nt2::Zero<T>(),nt2::Zero<T>()),
        cT(nt2::Zero<T>(),nt2::Pi <T>()),
      };

    cT results[] =
      { cT(nt2::Zero<T>(),nt2::Zero<T>()),
        cT(nt2::Zero<T>(),nt2::Zero<T>())
      };

    for(int i=0; i < N; i++)
    {
      NT2_TEST_ULP_EQUAL(nt2::sinh(inputs[i]), results[i], 1);
      NT2_TEST_ULP_EQUAL(nt2::sinh(-inputs[i]), -results[i], 1);
    }
  }
#ifndef BOOST_SIMD_NO_INVALIDS
  {
    const int N = 20;
    cT inputs[N] =
      { cT(nt2::Zero<T>(),nt2::Zero<T>()),cT(nt2::Inf<T>(),nt2::Zero<T>()),cT(nt2::Minf<T>(),nt2::Zero<T>()),cT(nt2::Nan<T>(),nt2::Zero<T>()),
        cT(nt2::Zero<T>(),nt2::Inf<T>()), cT(nt2::Inf<T>(),nt2::Inf<T>()), cT(nt2::Minf<T>(),nt2::Inf<T>()), cT(nt2::Nan<T>(),nt2::Inf<T>()),
        cT(nt2::Zero<T>(),nt2::Minf<T>()),cT(nt2::Inf<T>(),nt2::Minf<T>()),cT(nt2::Minf<T>(),nt2::Minf<T>()),cT(nt2::Nan<T>(),nt2::Minf<T>()),
        cT(nt2::Zero<T>(),nt2::Nan<T>()), cT(nt2::Inf<T>(),nt2::Nan<T>()), cT(nt2::Minf<T>(),nt2::Nan<T>()), cT(nt2::Nan<T>(),nt2::Nan<T>()),
        cT(nt2::Zero<T>(),nt2::Pi <T>()), cT(nt2::Inf<T>(),nt2::Pi <T>()), cT(nt2::Minf<T>(),nt2::Pi <T>()), cT(nt2::Nan<T>(),nt2::Pi <T>()),
      };

    cT results[N] =
      { cT(nt2::Zero<T>(),nt2::Zero<T>()),cT(nt2::Inf<T>(),nt2::Zero<T>()),cT(nt2::Minf<T>(),nt2::Zero<T>()),cT(nt2::Nan<T>(),nt2::Zero<T>()),
        cT(nt2::Zero<T>(),nt2::Nan<T>()),cT(nt2::Inf<T>(),nt2::Nan<T>()), cT(nt2::Minf<T>(),nt2::Nan<T>()), cT(nt2::Nan<T>(),nt2::Nan<T>()),
        cT(nt2::Zero<T>(),nt2::Nan<T>()),cT(nt2::Inf<T>(),nt2::Nan<T>()), cT(nt2::Minf<T>(),nt2::Nan<T>()), cT(nt2::Nan<T>(),nt2::Nan<T>()),
        cT(nt2::Zero<T>(),nt2::Nan<T>()), cT(nt2::Inf<T>(),nt2::Nan<T>()), cT(nt2::Minf<T>(),nt2::Nan<T>()),cT(nt2::Nan<T>(),nt2::Nan<T>()),
        cT(nt2::Zero<T>(),nt2::Zero<T>()),cT(nt2::Minf<T>(),nt2::Inf<T>()),cT(nt2::Inf<T>(),nt2::Inf<T>()),cT(nt2::Nan<T>(),nt2::Nan <T>()),
      };

    for(int i=0; i < N; i++)
    {
      NT2_TEST_ULP_EQUAL(nt2::sinh(inputs[i]), results[i], 1);
      NT2_TEST_ULP_EQUAL(nt2::sinh(-inputs[i]), -results[i], 1);
    }
  }
#endif

} // end of test for floating_
