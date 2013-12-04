//==============================================================================
//         Copyright 2003 - 2013   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/include/functions/cscpi.hpp>

#include <boost/dispatch/functor/meta/call.hpp>
#include <nt2/sdk/functor/meta/call.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>
#include <complex>
#include <nt2/sdk/complex/complex.hpp>
#include <nt2/sdk/unit/tests/ulp.hpp>
#include <nt2/sdk/unit/tests/basic.hpp>
#include <nt2/sdk/meta/as_integer.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <boost/simd/sdk/config.hpp>

#include <nt2/include/constants/one.hpp>
#include <nt2/include/constants/zero.hpp>
#include <nt2/include/constants/inf.hpp>
#include <nt2/include/constants/minf.hpp>
#include <nt2/include/constants/nan.hpp>
#include <nt2/include/constants/i.hpp>

#include <nt2/include/functions/rec.hpp>
#include <nt2/include/functions/mul_i.hpp>
#include <nt2/include/functions/mul_minus_i.hpp>

NT2_TEST_CASE_TPL ( cscpi,  NT2_REAL_TYPES)
{

  using nt2::cscpi;
  using nt2::tag::cscpi_;
  typedef std::complex<T> cT;
  typedef typename nt2::meta::call<cscpi_(cT)>::type r_t;
  typedef typename nt2:: meta::as_complex<T>::type wished_r_t;

  // return type conformity test
  NT2_TEST_TYPE_IS(r_t, wished_r_t);

  // specific values tests
  NT2_TEST_ULP_EQUAL(nt2::cscpi(cT(nt2::Inf<T>())), cT(nt2::Nan<T>()), 2);
  NT2_TEST_ULP_EQUAL(nt2::cscpi(cT(nt2::Minf<T>())), cT(nt2::Nan<T>()), 2);
  NT2_TEST_ULP_EQUAL(nt2::cscpi(cT(1, 1)),nt2::rec(nt2::sinpi(cT(1.0, 1.0))), 2);
  NT2_TEST_ULP_EQUAL(nt2::cscpi(cT(1, 2)),nt2::rec(nt2::sinpi(cT(1.0, 2.0))), 2);
  NT2_TEST_ULP_EQUAL(nt2::cscpi(cT(2, 1)),nt2::rec(nt2::sinpi(cT(2.0, 1.0))), 2);
  NT2_TEST_ULP_EQUAL(nt2::cscpi(cT(2, 2)),nt2::rec(nt2::sinpi(cT(2.0, 2.0))), 2);
  NT2_TEST_ULP_EQUAL(nt2::cscpi(cT(0, 1)),nt2::rec(nt2::sinpi(cT(0.0, 1.0))), 2);
  NT2_TEST_ULP_EQUAL(nt2::cscpi(cT(0, 2)),nt2::rec(nt2::sinpi(cT(0.0, 2.0))), 2);
  NT2_TEST_ULP_EQUAL(nt2::cscpi(cT(2, 0)),nt2::rec(nt2::sinpi(cT(2.0, 0.0))), 2);

  const int N = 20;
  cT inputs[N] =
    { cT(nt2::Zero<T>(),nt2::Zero<T>()),cT(nt2::Inf<T>(),nt2::Zero<T>()),cT(nt2::Minf<T>(),nt2::Zero<T>()),cT(nt2::Nan<T>(),nt2::Zero<T>()),
      cT(nt2::Zero<T>(),nt2::Inf<T>()), cT(nt2::Inf<T>(),nt2::Inf<T>()), cT(nt2::Minf<T>(),nt2::Inf<T>()), cT(nt2::Nan<T>(),nt2::Inf<T>()),
      cT(nt2::Zero<T>(),nt2::Minf<T>()),cT(nt2::Inf<T>(),nt2::Minf<T>()),cT(nt2::Minf<T>(),nt2::Minf<T>()),cT(nt2::Nan<T>(),nt2::Minf<T>()),
      cT(nt2::Zero<T>(),nt2::Nan<T>()), cT(nt2::Inf<T>(),nt2::Nan<T>()), cT(nt2::Minf<T>(),nt2::Nan<T>()), cT(nt2::Nan<T>(),nt2::Nan<T>()),
      cT(nt2::Zero<T>(),nt2::One <T>()), cT(nt2::Inf<T>(),nt2::One <T>()), cT(nt2::Minf<T>(),nt2::One <T>()), cT(nt2::Nan<T>(),nt2::One <T>()),
    };

  NT2_TEST_ULP_EQUAL(nt2::cscpi(-inputs[0]), cT(nt2::Nan<T>(),nt2::Nan<T>()) , 3.5);
  NT2_TEST_EQUAL(nt2::cscpi(cT(0.0, 0.0)), cT(nt2::Nan<T>(),nt2::Nan<T>()));
  NT2_TEST_EQUAL(nt2::cscpi(cT(-0.0, 0.0)), cT(nt2::Nan<T>(),nt2::Nan<T>()));
  NT2_TEST_EQUAL(nt2::cscpi(cT(-0.0,-0.0)), cT(nt2::Nan<T>(),nt2::Nan<T>()));
  NT2_TEST_EQUAL(nt2::cscpi(cT( 0.0,-0.0)), cT(nt2::Nan<T>(),nt2::Nan<T>()));
  for(int i=1; i < N; i++)
    {
      std::cout << "i = " << i << " -> " << inputs[i] << std::endl;
      NT2_TEST_ULP_EQUAL(nt2::cscpi(-inputs[i]), -nt2::cscpi(inputs[i]), 3.5);
      NT2_TEST_ULP_EQUAL(nt2::cscpi(inputs[i]), nt2::rec(nt2::sinpi(inputs[i])), 3);
    }
} // end of test for floating_


