//==============================================================================
//         Copyright 2003 - 2013   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/include/functions/abs.hpp>

#include <boost/dispatch/functor/meta/call.hpp>
#include <nt2/sdk/functor/meta/call.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>
#include <complex>
#include <nt2/sdk/complex/complex.hpp>
#include <nt2/sdk/complex/dry.hpp>
#include <nt2/sdk/unit/tests/ulp.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <boost/simd/sdk/config.hpp>

#include <nt2/include/constants/mone.hpp>
#include <nt2/include/constants/one.hpp>
#include <nt2/include/constants/valmax.hpp>
#include <nt2/include/constants/valmin.hpp>
#include <nt2/include/constants/zero.hpp>
#include <nt2/include/constants/inf.hpp>
#include <nt2/include/constants/minf.hpp>
#include <nt2/include/constants/nan.hpp>

NT2_TEST_CASE_TPL(abs_real,  BOOST_SIMD_REAL_TYPES)
{
  using nt2::abs;
  using nt2::tag::abs_;
  typedef typename std::complex<T> cT;
  typedef typename boost::dispatch::meta::call<abs_(cT)>::type r_t;

  // return type conformity test
  NT2_TEST_TYPE_IS(r_t, T);

  // specific values tests
#ifndef BOOST_SIMD_NO_INVALIDS
   NT2_TEST_EQUAL(nt2::abs(cT(nt2::Inf<T>())), nt2::Inf<T>());
   NT2_TEST_EQUAL(nt2::abs(cT(nt2::Minf<T>())), nt2::Inf<T>());
   NT2_TEST_EQUAL(nt2::abs(cT(nt2::Nan<T>())), nt2::Nan<T>());
#endif
   NT2_TEST_ULP_EQUAL(nt2::abs(cT(1)), T(1), 0);
   NT2_TEST_EQUAL(nt2::abs(cT(nt2::Mone<T>())), nt2::One<T>());
   NT2_TEST_EQUAL(nt2::abs(cT(nt2::One<T>())), nt2::One<T>());
   NT2_TEST_EQUAL(nt2::abs(cT(nt2::Valmax<T>())), nt2::Valmax<T>());
   NT2_TEST_EQUAL(nt2::abs(cT(nt2::Valmin<T>())), nt2::Valmax<T>());
   NT2_TEST_EQUAL(nt2::abs(cT(nt2::Zero<T>())), nt2::Zero<T>());
   std::complex < T > b(3, 4);
   NT2_TEST_EQUAL(nt2::abs(b), T(5));
   for(int i=-10; i < 10; i++)
   {
     for(int j=-10; j < 10; j++)
     {
       T ti = T(i);
       T tj = T(j);
       NT2_TEST_EQUAL(nt2::abs(cT(ti, tj)), nt2::hypot(ti, tj));
     }
   }
}

NT2_TEST_CASE_TPL(abs_dry,  BOOST_SIMD_REAL_TYPES)
{
  using nt2::abs;
  using nt2::tag::abs_;
  typedef typename nt2::dry<T> dT;
  typedef typename boost::dispatch::meta::call<abs_(dT)>::type r_t;

  // return type conformity test
  NT2_TEST_TYPE_IS(r_t, T);

  // specific values tests
#ifndef BOOST_SIMD_NO_INVALIDS
   NT2_TEST_EQUAL(nt2::abs(dT(nt2::Inf<T>())), nt2::Inf<T>());
   NT2_TEST_EQUAL(nt2::abs(dT(nt2::Minf<T>())), nt2::Inf<T>());
   NT2_TEST_EQUAL(nt2::abs(dT(nt2::Nan<T>())), nt2::Nan<T>());
#endif
   NT2_TEST_ULP_EQUAL(nt2::abs(dT(1)), T(1), 0);
   NT2_TEST_EQUAL(nt2::abs(dT(nt2::Mone<T>())), nt2::One<T>());
   NT2_TEST_EQUAL(nt2::abs(dT(nt2::One<T>())), nt2::One<T>());
   NT2_TEST_EQUAL(nt2::abs(dT(nt2::Valmax<T>())), nt2::Valmax<T>());
   NT2_TEST_EQUAL(nt2::abs(dT(nt2::Valmin<T>())), nt2::Valmax<T>());
   NT2_TEST_EQUAL(nt2::abs(dT(nt2::Zero<T>())), nt2::Zero<T>());
}
