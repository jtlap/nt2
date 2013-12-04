//==============================================================================
//         Copyright 2003 - 2013   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/include/functions/sec.hpp>

#include <boost/dispatch/functor/meta/call.hpp>
#include <nt2/sdk/functor/meta/call.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>
#include <complex>
#include <nt2/sdk/complex/complex.hpp>
#include <nt2/sdk/complex/dry.hpp>
#include <nt2/sdk/unit/tests/ulp.hpp>
#include <nt2/sdk/unit/tests/basic.hpp>
#include <nt2/sdk/meta/as_integer.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <boost/simd/sdk/config.hpp>

#include <nt2/include/constants/pi.hpp>
#include <nt2/include/constants/zero.hpp>
#include <nt2/include/constants/inf.hpp>
#include <nt2/include/constants/minf.hpp>
#include <nt2/include/constants/nan.hpp>
#include <nt2/include/constants/i.hpp>

#include <nt2/include/functions/rec.hpp>
#include <nt2/include/functions/mul_i.hpp>
#include <nt2/include/functions/mul_minus_i.hpp>


NT2_TEST_CASE_TPL ( sec,  NT2_REAL_TYPES)
{

  using nt2::sec;
  using nt2::tag::sec_;
  typedef std::complex<T> cT;
  typedef typename nt2::meta::call<sec_(cT)>::type r_t;
  typedef typename nt2:: meta::as_complex<T>::type wished_r_t;
  typedef typename nt2:: meta::as_dry<T>::type dT;

  // return type conformity test
  NT2_TEST_TYPE_IS(r_t, wished_r_t);

  // specific values tests
  NT2_TEST_ULP_EQUAL(nt2::sec(cT(nt2::Inf<T>())), cT(nt2::Nan<T>()), 2);
  NT2_TEST_ULP_EQUAL(nt2::sec(cT(nt2::Minf<T>())), cT(nt2::Nan<T>()), 2);
  NT2_TEST_ULP_EQUAL(nt2::sec(cT(1, 1)),nt2::rec(nt2::cos(cT(1.0, 1.0))), 2);
  NT2_TEST_ULP_EQUAL(nt2::sec(cT(1, 2)),nt2::rec(nt2::cos(cT(1.0, 2.0))), 2);
  NT2_TEST_ULP_EQUAL(nt2::sec(cT(2, 1)),nt2::rec(nt2::cos(cT(2.0, 1.0))), 2);
  NT2_TEST_ULP_EQUAL(nt2::sec(cT(2, 2)),nt2::rec(nt2::cos(cT(2.0, 2.0))), 2);
  NT2_TEST_ULP_EQUAL(nt2::sec(cT(0, 1)),nt2::rec(nt2::cos(cT(0.0, 1.0))), 2);
  NT2_TEST_ULP_EQUAL(nt2::sec(cT(0, 2)),nt2::rec(nt2::cos(cT(0.0, 2.0))), 2);
  NT2_TEST_ULP_EQUAL(nt2::sec(cT(2, 0)),nt2::rec(nt2::cos(cT(2.0, 0.0))), 2);

  const int N = 20;
  cT inputs[N] =
    { cT(nt2::Zero<T>(),nt2::Zero<T>()),cT(nt2::Inf<T>(),nt2::Zero<T>()),cT(nt2::Minf<T>(),nt2::Zero<T>()),cT(nt2::Nan<T>(),nt2::Zero<T>()),
      cT(nt2::Zero<T>(),nt2::Inf<T>()), cT(nt2::Inf<T>(),nt2::Inf<T>()), cT(nt2::Minf<T>(),nt2::Inf<T>()), cT(nt2::Nan<T>(),nt2::Inf<T>()),
      cT(nt2::Zero<T>(),nt2::Minf<T>()),cT(nt2::Inf<T>(),nt2::Minf<T>()),cT(nt2::Minf<T>(),nt2::Minf<T>()),cT(nt2::Nan<T>(),nt2::Minf<T>()),
      cT(nt2::Zero<T>(),nt2::Nan<T>()), cT(nt2::Inf<T>(),nt2::Nan<T>()), cT(nt2::Minf<T>(),nt2::Nan<T>()), cT(nt2::Nan<T>(),nt2::Nan<T>()),
      cT(nt2::Zero<T>(),nt2::Pi <T>()), cT(nt2::Inf<T>(),nt2::Pi <T>()), cT(nt2::Minf<T>(),nt2::Pi <T>()), cT(nt2::Nan<T>(),nt2::Pi <T>()),
    };


  for(int i=0; i < N; i++)
    {
      std::cout << "i = " << i << " -> " << inputs[i] << std::endl;
      NT2_TEST_ULP_EQUAL(nt2::sec(-inputs[i]), nt2::sec(inputs[i]), 3.5);
      NT2_TEST_ULP_EQUAL(nt2::sec(inputs[i]), nt2::rec(nt2::cos(inputs[i])), 3);
    }
  NT2_TEST_ULP_EQUAL(nt2::sec(dT(nt2::Inf<T>())),   dT(nt2::Nan<T>()), 2);
} // end of test for floating_


