//==============================================================================
//         Copyright 2003 - 2013   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/include/functions/sin.hpp>

#include <boost/dispatch/functor/meta/call.hpp>
#include <nt2/sdk/functor/meta/call.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>
#include <complex>
#include <nt2/sdk/complex/complex.hpp>
#include <nt2/sdk/unit/tests/ulp.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <boost/simd/sdk/config.hpp>

#include <nt2/include/constants/pi.hpp>
#include <nt2/include/constants/zero.hpp>
#include <nt2/include/constants/inf.hpp>
#include <nt2/include/constants/minf.hpp>
#include <nt2/include/constants/nan.hpp>
#include <nt2/include/constants/i.hpp>

#include <nt2/include/functions/mul_i.hpp>
#include <nt2/include/functions/mul_minus_i.hpp>

NT2_TEST_CASE_TPL ( sin,  NT2_REAL_TYPES)
{

  using nt2::sin;
  using nt2::tag::sin_;
  typedef std::complex<T> cT;
  typedef typename nt2::meta::call<sin_(cT)>::type r_t;
  typedef typename nt2:: meta::as_complex<T>::type wished_r_t;

  // return type conformity test
  NT2_TEST_TYPE_IS(r_t, wished_r_t);

  // specific values tests
  NT2_TEST_ULP_EQUAL(nt2::sin(cT(nt2::Inf<T>())), cT(nt2::Nan<T>()), 2);
  NT2_TEST_ULP_EQUAL(nt2::sin(cT(nt2::Minf<T>())), cT(nt2::Nan<T>()), 2);
  NT2_TEST_ULP_EQUAL(nt2::sin(cT(1, 1)),std::sin(cT(1.0, 1.0)), 2);
  NT2_TEST_ULP_EQUAL(nt2::sin(cT(1, 2)),std::sin(cT(1.0, 2.0)), 2);
  NT2_TEST_ULP_EQUAL(nt2::sin(cT(2, 1)),std::sin(cT(2.0, 1.0)), 2);
  NT2_TEST_ULP_EQUAL(nt2::sin(cT(2, 2)),std::sin(cT(2.0, 2.0)), 2);
  NT2_TEST_ULP_EQUAL(nt2::sin(cT(0, 1)),std::sin(cT(0.0, 1.0)), 2);
  NT2_TEST_ULP_EQUAL(nt2::sin(cT(0, 2)),std::sin(cT(0.0, 2.0)), 2);
  NT2_TEST_ULP_EQUAL(nt2::sin(cT(2, 0)),std::sin(cT(2.0, 0.0)), 2);

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
     NT2_TEST_ULP_EQUAL(nt2::sin(-inputs[i]), -nt2::sin(inputs[i]), 3.5);
     NT2_TEST_ULP_EQUAL(nt2::sin(inputs[i]), nt2::mul_minus_i(nt2::sinh(nt2::mul_i(inputs[i]))), 3);
   }
 } // end of test for floating_

