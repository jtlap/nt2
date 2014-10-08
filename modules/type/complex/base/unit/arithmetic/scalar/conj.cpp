//==============================================================================
//         Copyright 2003 - 2013   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/include/functions/conj.hpp>

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

NT2_TEST_CASE_TPL(conj_real,  BOOST_SIMD_REAL_TYPES)
{
  using nt2::conj;
  using nt2::tag::conj_;
  typedef typename std::complex<T> cT;
  typedef typename boost::dispatch::meta::call<conj_(cT)>::type r_t;

  // return type conformity test
  NT2_TEST_TYPE_IS(r_t, cT);

  // specific values tests
#ifndef BOOST_SIMD_NO_INVALIDS
   NT2_TEST_EQUAL(nt2::conj(cT(nt2::Inf<T>())), nt2::Inf<cT>());
   NT2_TEST_EQUAL(nt2::conj(cT(nt2::Minf<T>())), nt2::Minf<cT>());
   NT2_TEST_EQUAL(nt2::conj(cT(nt2::Nan<T>())), nt2::Nan<cT>());
#endif
   NT2_TEST_EQUAL(nt2::conj(cT(nt2::Mone<T>())), nt2::Mone<cT>());
   NT2_TEST_EQUAL(nt2::conj(cT(nt2::One<T>())), nt2::One<cT>());
   NT2_TEST_EQUAL(nt2::conj(cT(nt2::Valmax<T>())), nt2::Valmax<cT>());
   NT2_TEST_EQUAL(nt2::conj(cT(nt2::Valmin<T>())), nt2::Valmin<cT>());
   NT2_TEST_EQUAL(nt2::conj(cT(nt2::Zero<T>())), nt2::Zero<cT>());
   for(int i=-10; i < 10; i++)
   {
     for(int j=-10; j < 10; j++)
     {
       T ti = T(i);
       T tj = T(j);
       NT2_TEST_EQUAL(nt2::conj(cT(ti, tj)), cT(ti, -tj));
     }
   }
}

NT2_TEST_CASE_TPL(conj_dry,  BOOST_SIMD_REAL_TYPES)
{
  using nt2::conj;
  using nt2::tag::conj_;
  typedef typename nt2::dry<T> dT;
  typedef typename boost::dispatch::meta::call<conj_(dT)>::type r_t;

  // return type conformity test
  NT2_TEST_TYPE_IS(r_t, dT);

  // specific values tests
#ifndef BOOST_SIMD_NO_INVALIDS
   NT2_TEST_EQUAL(nt2::conj(dT(nt2::Inf<T>())), nt2::Inf<dT>());
   NT2_TEST_EQUAL(nt2::conj(dT(nt2::Minf<T>())), nt2::Minf<dT>());
   NT2_TEST_EQUAL(nt2::conj(dT(nt2::Nan<T>())), nt2::Nan<dT>());
#endif
   NT2_TEST_ULP_EQUAL(nt2::conj(dT(1)), T(1), 0);
   NT2_TEST_EQUAL(nt2::conj(dT(nt2::Mone<T>())), nt2::Mone<dT>());
   NT2_TEST_EQUAL(nt2::conj(dT(nt2::One<T>())), nt2::One<dT>());
   NT2_TEST_EQUAL(nt2::conj(dT(nt2::Valmax<T>())), nt2::Valmax<dT>());
   NT2_TEST_EQUAL(nt2::conj(dT(nt2::Valmin<T>())), nt2::Valmin<dT>());
   NT2_TEST_EQUAL(nt2::conj(dT(nt2::Zero<T>())), nt2::Zero<dT>());
}
