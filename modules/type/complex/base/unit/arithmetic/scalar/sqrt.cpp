//==============================================================================
//         Copyright 2003 - 2013   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/include/functions/sqrt.hpp>

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

#include <nt2/include/constants/mone.hpp>
#include <nt2/include/constants/mzero.hpp>
#include <nt2/include/constants/one.hpp>
#include <nt2/include/constants/zero.hpp>
#include <nt2/include/constants/inf.hpp>
#include <nt2/include/constants/minf.hpp>
#include <nt2/include/constants/nan.hpp>
#include <nt2/include/functions/sqr.hpp>

NT2_TEST_CASE_TPL ( sqrt_real,  (double))//BOOST_SIMD_REAL_TYPES)
{
  using nt2::sqrt;
  using nt2::tag::sqrt_;
  typedef typename std::complex<T> cT;
  typedef typename boost::dispatch::meta::call<sqrt_(cT)>::type r_t;

  // return type conformity test
  NT2_TEST_TYPE_IS(r_t, cT);

  // specific values testss
#ifndef BOOST_SIMD_NO_INVALIDS
  NT2_TEST_EQUAL(nt2::sqrt(cT(nt2::Inf<T>())), cT(nt2::Inf<T>()));
  NT2_TEST_EQUAL(nt2::sqrt(cT(nt2::Inf<T>(),nt2::Inf<T>())),cT(nt2::Inf<T>(),nt2::Inf<T>()));
  NT2_TEST_EQUAL(nt2::sqrt(cT(nt2::Nan<T>(),nt2::Nan<T>())),cT(nt2::Nan<T>(),nt2::Nan<T>()));
  NT2_TEST_EQUAL(nt2::sqrt(cT(nt2::Inf<T>(),nt2::Nan<T>())),cT(nt2::Nan<T>(),nt2::Nan<T>()));
  NT2_TEST_EQUAL(nt2::sqrt(cT(nt2::Zero<T>(),nt2::Inf<T>())),cT(nt2::Inf<T>(),nt2::Inf<T>()));
  NT2_TEST_EQUAL(nt2::sqrt(cT(nt2::Minf<T>())), cT(0, nt2::Inf<T>()));
  NT2_TEST_EQUAL(nt2::sqrt(cT(nt2::Nan<T>())), cT(nt2::Nan<T>(),nt2::Nan<T>()));
  std::complex < T > b(nt2::Zero<T>(), nt2::Inf<T>());
  NT2_TEST_EQUAL(nt2::sqrt(nt2::pure(b)), cT(nt2::Inf<T>(), nt2::Inf<T>()));
  NT2_TEST_EQUAL(nt2::sqrt(cT(nt2::Minf<T>(),nt2::Zero<T>())), cT(nt2::Zero<T>(),nt2::Inf<T>()));
  NT2_TEST_EQUAL(nt2::sqrt(cT(nt2::One<T>(), nt2::Inf<T>())), cT(nt2::Inf<T>(),nt2::Inf<T>()));
  NT2_TEST_EQUAL(nt2::sqrt(cT(nt2::Inf<T>(), nt2::Inf<T>())), cT(nt2::Inf<T>(),nt2::Inf<T>()));
  NT2_TEST_EQUAL(nt2::sqrt(cT(nt2::Minf<T>(),nt2::Inf<T>())), cT(nt2::Inf<T>(),nt2::Inf<T>()));
  NT2_TEST_EQUAL(nt2::sqrt(cT(nt2::Nan <T>(),nt2::Inf<T>())), cT(nt2::Nan<T>(),nt2::Nan<T>()));
  NT2_TEST_EQUAL(nt2::sqrt(cT(nt2::One<T>(), nt2::Nan<T>())), cT(nt2::Nan<T>(),nt2::Nan<T>()));
  NT2_TEST_EQUAL(nt2::sqrt(cT(nt2::Inf<T>(), nt2::Nan<T>())), cT(nt2::Nan<T>(),nt2::Nan<T>()));
  NT2_TEST_EQUAL(nt2::sqrt(cT(nt2::Minf<T>(),nt2::Nan<T>())), cT(nt2::Nan<T>(),nt2::Nan<T>()));
  NT2_TEST_EQUAL(nt2::sqrt(cT(nt2::Nan <T>(),nt2::Nan<T>())), cT(nt2::Nan<T>(),nt2::Nan<T>()));
  NT2_TEST_EQUAL(nt2::sqrt(cT(nt2::Minf<T>(),nt2::One<T>())), cT(nt2::Zero<T>(),nt2::Inf<T>()));
  NT2_TEST_EQUAL(nt2::sqrt(cT(nt2::Minf<T>(),nt2::Mone<T>())),cT(nt2::Zero<T>(),nt2::Minf<T>()));
  NT2_TEST_EQUAL(nt2::sqrt(cT(nt2::Inf<T>(),nt2::Nan<T>())),  cT(nt2::Nan<T>(),nt2::Nan<T>()));
  NT2_TEST_EQUAL(nt2::sqrt(cT(nt2::Nan<T>(),nt2::One<T>())),  cT(nt2::Nan<T>(),nt2::Nan<T>()));
  NT2_TEST_EQUAL(nt2::sqrt(cT(nt2::Nan<T>(),nt2::Nan<T>())),  cT(nt2::Nan<T>(),nt2::Nan<T>()));
  NT2_TEST_EQUAL(nt2::sqrt(cT(nt2::One<T>(), -nt2::Inf<T>())), cT(nt2::Inf<T>(),-nt2::Inf<T>()));
  NT2_TEST_EQUAL(nt2::sqrt(cT(nt2::Inf<T>(), -nt2::Inf<T>())), cT(nt2::Inf<T>(),-nt2::Inf<T>()));
  NT2_TEST_EQUAL(nt2::sqrt(cT(nt2::Minf<T>(),-nt2::Inf<T>())), cT(nt2::Inf<T>(),-nt2::Inf<T>()));
  NT2_TEST_EQUAL(nt2::sqrt(cT(nt2::Nan <T>(),-nt2::Inf<T>())), cT(nt2::Nan<T>(),-nt2::Nan<T>()));
  NT2_TEST_EQUAL(nt2::sqrt(cT(nt2::One<T>(), -nt2::Nan<T>())), cT(nt2::Nan<T>(),-nt2::Nan<T>()));
  NT2_TEST_EQUAL(nt2::sqrt(cT(nt2::Inf<T>(), -nt2::Nan<T>())), cT(nt2::Nan<T>(),-nt2::Nan<T>()));
  NT2_TEST_EQUAL(nt2::sqrt(cT(nt2::Minf<T>(),-nt2::Nan<T>())), cT(nt2::Nan<T>(),-nt2::Nan<T>()));
  NT2_TEST_EQUAL(nt2::sqrt(cT(nt2::Nan <T>(),-nt2::Nan<T>())), cT(nt2::Nan<T>(),-nt2::Nan<T>()));
  NT2_TEST_EQUAL(nt2::sqrt(cT(nt2::Minf<T>(),-nt2::One<T>())), cT(nt2::Zero<T>(),-nt2::Inf<T>()));
  NT2_TEST_EQUAL(nt2::sqrt(cT(nt2::Minf<T>(),-nt2::Mone<T>())),cT(nt2::Zero<T>(),-nt2::Minf<T>()));
  NT2_TEST_EQUAL(nt2::sqrt(cT(nt2::Inf<T>(), -nt2::Nan<T>())), cT(nt2::Nan<T>(),nt2::Nan<T>()));
  NT2_TEST_EQUAL(nt2::sqrt(cT(nt2::Nan<T>(), -nt2::One<T>())), cT(nt2::Nan<T>(),-nt2::Nan<T>()));
  NT2_TEST_EQUAL(nt2::sqrt(cT(nt2::Nan<T>(), -nt2::Nan<T>())), cT(nt2::Nan<T>(),-nt2::Nan<T>()));
#endif
   NT2_TEST_ULP_EQUAL(nt2::sqrt(cT(1)), cT(1), 0);
   NT2_TEST_EQUAL(nt2::sqrt(cT(nt2::Mone<T>())), cT(0, nt2::One<T>()));
   NT2_TEST_EQUAL(nt2::sqrt(cT(nt2::One<T>())), cT(nt2::One<T>()));
   NT2_TEST_EQUAL(nt2::sqrt(cT(nt2::Zero<T>())), cT(nt2::Zero<T>()));
   NT2_TEST_EQUAL(nt2::sqrt(cT(nt2::Zero<T>(),nt2::Zero<T>())), cT(nt2::Zero<T>(),nt2::Zero<T>()));
   NT2_TEST_EQUAL(nt2::sqrt(cT(nt2::Mzero<T>(),nt2::Zero<T>())),cT(nt2::Zero<T>(),nt2::Zero<T>()));
   NT2_TEST_ULP_EQUAL(nt2::sqrt(cT(0, 2)), cT(1, 1), 1);
   for(T i=-5; i <=  T(5) ; i+= T(0.5))
   {
     for(T j =-5; j < T(5); j+= T(0.5))
     {
       std::cout << i << "+i*(" << j << ") -> " << nt2::sqrt(cT(i, j)) << std::endl;
       NT2_TEST_ULP_EQUAL(nt2::sqr(nt2::sqrt(cT(i, j))), cT(i, j), 10);
     }
   }
}
