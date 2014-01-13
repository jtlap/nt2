//==============================================================================
//         Copyright 2003 - 2013   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/include/functions/sind.hpp>

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

#include <nt2/include/constants/zero.hpp>
#include <nt2/include/constants/inf.hpp>
#include <nt2/include/constants/minf.hpp>
#include <nt2/include/constants/nan.hpp>
#include <nt2/include/constants/i.hpp>


NT2_TEST_CASE_TPL ( sind,  NT2_REAL_TYPES)
{

  using nt2::sind;
  using nt2::tag::sind_;
  typedef std::complex<T> cT;
  typedef typename nt2::meta::call<sind_(cT)>::type r_t;
  typedef typename nt2:: meta::as_complex<T>::type wished_r_t;
  NT2_TEST_TYPE_IS(r_t, wished_r_t);


  // specific values tests
  NT2_TEST_ULP_EQUAL(nt2::sind(cT(nt2::Inf<T>())), cT(nt2::Nan<T>()), 3);
  NT2_TEST_ULP_EQUAL(nt2::sind(cT(nt2::Minf<T>())), cT(nt2::Nan<T>()), 3);
  NT2_TEST_ULP_EQUAL(nt2::sind(cT(1, 1)),std::sin(nt2::Deginrad<T>()*cT(1.0, 1.0)), 3);
  NT2_TEST_ULP_EQUAL(nt2::sind(cT(1, 10)),std::sin(nt2::Deginrad<T>()*cT(1.0, 10.0)), 3);
  NT2_TEST_ULP_EQUAL(nt2::sind(cT(10, 1)),std::sin(nt2::Deginrad<T>()*cT(10.0, 1.0)), 3);
  NT2_TEST_ULP_EQUAL(nt2::sind(cT(10, 10)),std::sin(nt2::Deginrad<T>()*cT(10.0, 10.0)), 3);
  NT2_TEST_ULP_EQUAL(nt2::sind(cT(0, 1)),std::sin(nt2::Deginrad<T>()*cT(0.0, 1.0)), 3);
  NT2_TEST_ULP_EQUAL(nt2::sind(cT(0, 10)),std::sin(nt2::Deginrad<T>()*cT(0.0, 10.0)), 3);
  NT2_TEST_ULP_EQUAL(nt2::sind(cT(10, 0)),std::sin(nt2::Deginrad<T>()*cT(10.0, 0.0)), 3);



  const int N = 20;
  cT inputs[N] =
    { cT(nt2::Zero<T>(),nt2::Zero<T>()),cT(nt2::Inf<T>(),nt2::Zero<T>()),cT(nt2::Minf<T>(),nt2::Zero<T>()),cT(nt2::Nan<T>(),nt2::Zero<T>()),
      cT(nt2::Zero<T>(),nt2::Inf<T>()), cT(nt2::Inf<T>(),nt2::Inf<T>()), cT(nt2::Minf<T>(),nt2::Inf<T>()), cT(nt2::Nan<T>(),nt2::Inf<T>()),
      cT(nt2::Zero<T>(),nt2::Minf<T>()),cT(nt2::Inf<T>(),nt2::Minf<T>()),cT(nt2::Minf<T>(),nt2::Minf<T>()),cT(nt2::Nan<T>(),nt2::Minf<T>()),
      cT(nt2::Zero<T>(),nt2::Nan<T>()), cT(nt2::Inf<T>(),nt2::Nan<T>()), cT(nt2::Minf<T>(),nt2::Nan<T>()), cT(nt2::Nan<T>(),nt2::Nan<T>()),
      cT(nt2::Zero<T>(),180), cT(nt2::Inf<T>(),180), cT(nt2::Minf<T>(),180), cT(nt2::Nan<T>(),180),
    };

  for(int i=0; i < N; i++)
   {
     std::cout <<   "input " << inputs[i] << std::endl;
     NT2_TEST_ULP_EQUAL(nt2::sind(nt2::unary_minus(inputs[i])), nt2::unary_minus(nt2::sind(inputs[i])), 4);
     NT2_TEST_ULP_EQUAL(nt2::sind(inputs[i]), nt2::sin(nt2::multiplies(nt2::Deginrad<T>(), inputs[i])), 3);
     std::cout <<   "---------------------------- " << inputs[i] << std::endl;
   }

} // end of test for floating_

