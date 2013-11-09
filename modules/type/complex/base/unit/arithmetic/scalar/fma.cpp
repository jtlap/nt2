//==============================================================================
//         Copyright 2003 - 2013   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/include/functions/fma.hpp>

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
#include <nt2/include/constants/two.hpp>
#include <nt2/include/constants/zero.hpp>
#include <nt2/include/constants/inf.hpp>
#include <nt2/include/constants/minf.hpp>
#include <nt2/include/constants/nan.hpp>

NT2_TEST_CASE_TPL ( fma_real, BOOST_SIMD_REAL_TYPES)
{
  using nt2::fma;
  using nt2::tag::fma_;
  typedef typename std::complex<T> cT;
  typedef typename boost::dispatch::meta::call<fma_(cT,cT,cT)>::type r_t;

  // return type conformity test
  NT2_TEST_TYPE_IS(r_t, cT);

  // specific values tests
#ifndef BOOST_SIMD_NO_INVALIDS
  NT2_TEST_ULP_EQUAL(fma(cT(nt2::Inf<T>()), cT(nt2::Inf<T>()), cT(nt2::Inf<T>())), cT(nt2::Inf<T>()), 0);
  NT2_TEST_EQUAL(fma(cT(nt2::Minf<T>()), cT(nt2::Minf<T>()), cT(nt2::Minf<T>())), cT(nt2::Nan<T>()));
  NT2_TEST_EQUAL(fma(cT(nt2::Nan<T>()), cT(nt2::Nan<T>()), cT(nt2::Nan<T>())), cT(nt2::Nan<T>()));
#endif
  NT2_TEST_EQUAL(fma(cT(nt2::Mone<T>()), cT(nt2::Mone<T>()), cT(nt2::Mone<T>())), cT(nt2::Zero<T>()));
  NT2_TEST_EQUAL(fma(cT(nt2::One<T>()), cT(nt2::One<T>()), cT(nt2::One<T>())), cT(nt2::Two<T>()));
  NT2_TEST_EQUAL(fma(cT(nt2::Zero<T>()), cT(nt2::Zero<T>()), cT(nt2::Zero<T>())), cT(nt2::Zero<T>()));
}

NT2_TEST_CASE_TPL ( fma_various,  BOOST_SIMD_REAL_TYPES)
{
  using nt2::fma;
  using nt2::tag::fma_;
  typedef typename std::complex<T> cT;

  // specific values tests
  NT2_TEST_EQUAL(fma(T(2), T(3), T(4)), T(10));
  NT2_TEST_EQUAL(fma(cT(2), cT(3), cT(4)), cT(10));
  NT2_TEST_EQUAL(    cT(2)*cT(3)+cT(4), cT(10));
  NT2_TEST_EQUAL(fma(cT(2), cT(3), cT(0, 4)), cT(6, 4));
  NT2_TEST_EQUAL(    cT(2)*cT(3)+cT(0, 4), cT(6, 4));
  NT2_TEST_EQUAL(fma(cT(2), cT(0, 3), cT(4)), cT(4, 6));
  NT2_TEST_EQUAL((cT(2)*cT(0, 3)+cT(4)), cT(4, 6));
  NT2_TEST_EQUAL(fma(cT(0, 2), cT(3), cT(4)), cT(4, 6));
  NT2_TEST_EQUAL((cT(0, 2)* cT(3)+cT(4)), cT(4, 6));
  NT2_TEST_EQUAL(fma(cT(2), cT(0, 3), cT(0, 4)), cT(0, 10));
  NT2_TEST_EQUAL((cT(2)* cT(0, 3)+ cT(0, 4)), cT(0, 10));
  NT2_TEST_EQUAL(fma(cT(0, 2), cT(0, 3), cT(4, 5)), cT(-2, 5));
  NT2_TEST_EQUAL((cT(0, 2)* cT(0, 3)+ cT(4, 5)), cT(-2, 5));
  NT2_TEST_EQUAL(fma(cT(0, 2), cT(3, 5), cT(0, 4)), cT(-10, 10));
  NT2_TEST_EQUAL((cT(0, 2)* cT(3, 5)+ cT(0, 4)), cT(-10, 10));
  NT2_TEST_EQUAL(fma(cT(0, 2), cT(0, 3), cT(0, 4)), cT(-6, 4));
  NT2_TEST_EQUAL((cT(0, 2)*cT(0, 3)+cT(0, 4)), cT(-6, 4));
  NT2_TEST_EQUAL(fma(T(2), cT(5, 3),cT(6, 4)), cT(16, 10));
  NT2_TEST_EQUAL(fma(cT(2), cT(5, 3), cT(6, 4)), cT(16, 10));
  NT2_TEST_EQUAL((cT(2)*cT(5, 3)+cT(6, 4)), cT(16, 10));
  NT2_TEST_EQUAL(fma(T(2), cT(5, 3),cT(6, 4)), cT(16, 10));
  NT2_TEST_EQUAL(fma(cT(2), cT(5, 3), cT(6, 4)), cT(16, 10));
  NT2_TEST_EQUAL((cT(2)*cT(5, 3)+cT(6, 4)), cT(16, 10));
  NT2_TEST_EQUAL(fma(cT(2, 3), cT(5, 3),T(6)), cT(7, 21));
  NT2_TEST_EQUAL(fma(cT(2, 3), cT(5, 3), cT(6)), cT(7, 21));
  NT2_TEST_EQUAL((cT(2, 3)*cT(5, 3)+cT(6)), cT(7, 21));
  NT2_TEST_EQUAL(fma(cT(2, 3), T(5),T(6)), cT(16, 15));
  NT2_TEST_EQUAL(fma(cT(2, 3), cT(5), cT(6)), cT(16, 15));
  NT2_TEST_EQUAL((cT(2, 3)*cT(5)+cT(6)), cT(16, 15));
  NT2_TEST_EQUAL(fma(T(2), cT(5, 3),T(6)), cT(16, 6));
  NT2_TEST_EQUAL(fma(cT(2), cT(5, 3), cT(6)), cT(16, 6));
  NT2_TEST_EQUAL((cT(2)*cT(5, 3)+cT(6)), cT(16, 6));
  NT2_TEST_EQUAL(fma(T(2), T(5),cT(6, 2)), cT(16, 2));
  NT2_TEST_EQUAL(fma(cT(2), cT(5), cT(6, 2)), cT(16, 2));
  NT2_TEST_EQUAL((cT(2)*cT(5)+cT(6, 2)), cT(16, 2));
  NT2_TEST_EQUAL(fma(cT(2), cT(0, 5), cT(6, 2)), cT(6, 12));
  NT2_TEST_EQUAL((cT(2)*cT(0, 5)+cT(6, 2)), cT(6, 12));
  NT2_TEST_EQUAL(fma(cT(2), cT(2, 5), cT(0, 2)), cT(4, 12));
  NT2_TEST_EQUAL((cT(2)*cT(2, 5)+cT(0, 2)), cT(4, 12));
  NT2_TEST_EQUAL(fma(cT(2, 5), cT(0, 5), cT(2)), cT(-23, 10));
  NT2_TEST_EQUAL((cT(2, 5)*cT(0, 5)+cT(2)), cT(-23, 10));
  NT2_TEST_EQUAL(fma(cT(0, 5), cT(2, 5), cT(2)), cT(-23, 10));
  NT2_TEST_EQUAL((cT(0, 5)*cT(2, 5)+cT(2)), cT(-23, 10));
  NT2_TEST_EQUAL(fma(cT(2, 5), cT(3, 0), cT(0, 2)), cT(6, 17));
  NT2_TEST_EQUAL((cT(2, 5)*cT(3, 0)+cT(0, 2)), cT(6, 17));
  NT2_TEST_EQUAL(fma(cT(0, 5), cT(3), cT(6, 2)), cT(6, 17));
  NT2_TEST_EQUAL((cT(0, 5)*cT(3, 0)+cT(6, 2)), cT(6, 17));
}

NT2_TEST_CASE_TPL ( fma_various_invalid, (float))//BOOST_SIMD_REAL_TYPES)
{
  using nt2::fma;
  using nt2::tag::fma_;
  typedef typename std::complex<T> cT;

  // specific values tests
#ifndef BOOST_SIMD_NO_INVALIDS
  NT2_TEST_EQUAL(fma(nt2::Inf<cT>(), cT(3), cT(4)), nt2::Inf<cT>());
  NT2_TEST_EQUAL(fma(nt2::Inf<cT>(), cT(3), cT(4)), nt2::Inf<cT>());
  NT2_TEST_EQUAL(fma(cT(0, nt2::Inf<T>()), cT(0), cT(3, 4)), cT(3, nt2::Nan<T>()));
  NT2_TEST_EQUAL(fma(cT(0),cT(0, nt2::Inf<T>()), cT(4)), cT(4, nt2::Nan<T>()));
  NT2_TEST_EQUAL(fma(cT(1, nt2::Inf<T>()), cT(0), cT(3, nt2::Minf<T>())), cT(3, nt2::Nan<T>()));
  NT2_TEST_EQUAL(fma(cT(0),cT(1, nt2::Inf<T>()), cT(4)), cT(4, nt2::Nan<T>()));
  NT2_TEST_EQUAL(fma(nt2::Inf<T>(), T(3), T(4)), nt2::Inf<T>());
  NT2_TEST_EQUAL(fma(nt2::Inf<cT>(), cT(3), cT(nt2::Minf<T>())), nt2::Nan<cT>());
  NT2_TEST_EQUAL(fma(cT(1),nt2::Inf<cT>(), cT(nt2::Minf<T>())), cT(nt2::Nan<T>(), 0));
  NT2_TEST_EQUAL(fma(cT(1),cT(0, nt2::Inf<T>()), cT(nt2::Minf<T>())), cT(nt2::Minf<T>(), nt2::Inf<T>()));
  NT2_TEST_EQUAL(   nt2::multiplies(nt2::Inf<cT>(), cT(3))+cT(4), nt2::Inf<cT>());
  NT2_TEST_EQUAL(fma(nt2::Inf<T>(), cT(0),cT(6, 4)),     cT(nt2::Nan<T>(), 4));
  NT2_TEST_EQUAL(fma(nt2::Inf<T>(), cT(0, 3),cT(6, 4)),  cT(6, nt2::Inf<T>()));
  NT2_TEST_EQUAL(fma(T(0),          nt2::Inf<cT>(),      cT(6, 4)), cT(nt2::Nan<T>(), 4));
  NT2_TEST_EQUAL(fma(nt2::Inf<T>(),  cT(1), cT( 3, 4)), cT(nt2::Inf<T>(), 4));
  NT2_TEST_EQUAL(fma(T(1), cT(nt2::Inf<T>()),  cT(4, 4)), cT(nt2::Inf<T>(), 4));
  NT2_TEST_EQUAL(fma( cT(0)                ,nt2::Inf<T>(),cT(6, 4)),     cT(nt2::Nan<T>(), 4));
  NT2_TEST_EQUAL(fma( cT(0, 3)             ,nt2::Inf<T>(),cT(6, 4)),  cT(6, nt2::Inf<T>()));
  NT2_TEST_EQUAL(fma( nt2::Inf<cT>(),       T(0),         cT(6, 4)), cT(nt2::Nan<T>(), 4));
  NT2_TEST_EQUAL(fma(nt2::Inf<cT>(), cT(3), T(4)),                     nt2::Inf<cT>());
  NT2_TEST_EQUAL(fma(cT(3),                     nt2::Inf<cT>(), T(4)), nt2::Inf<cT>());
  NT2_TEST_EQUAL(fma(cT(4),                     nt2::Inf<cT>(), cT(3)), nt2::Inf<cT>());
  NT2_TEST_EQUAL(fma(nt2::Inf<cT>(), T(4), cT(3)),                     nt2::Inf<cT>());
  NT2_TEST_EQUAL(fma(nt2::Inf<cT>(), cT(0), T(4)),                     nt2::Nan<cT>());
  NT2_TEST_EQUAL(fma(cT(0),                     nt2::Inf<cT>(), T(4)), nt2::Nan<cT>());
  NT2_TEST_EQUAL(fma(cT(0),                     nt2::Inf<cT>(), cT(3)), nt2::Nan<cT>());
  NT2_TEST_EQUAL(fma(nt2::Inf<cT>(), T(4), cT(3)),                     nt2::Inf<cT>());
  NT2_TEST_EQUAL(fma(nt2::Inf<cT>(), T(3),           T(4)), nt2::Inf<cT>());
  NT2_TEST_EQUAL(fma(cT(3, 4),        nt2::Inf<T>(), T(4)), cT(nt2::Inf<T>(), nt2::Inf<T>()));
  NT2_TEST_EQUAL(fma(cT(4),           nt2::Inf<T>(), T(3)), nt2::Inf<cT>());
  NT2_TEST_EQUAL(fma(nt2::Inf<cT>(),  T(0),          T(4)), nt2::Nan<cT>());
  NT2_TEST_EQUAL(fma(cT(0),           nt2::Inf<T>(), T(4)), nt2::Nan<cT>());
  NT2_TEST_EQUAL(fma(nt2::Inf<cT>(),  T(4),          T(3)), nt2::Inf<cT>());
  NT2_TEST_EQUAL(fma(cT(0, nt2::Inf<T>()), T(4),     T(3)), cT(3, nt2::Inf<T>()));
  NT2_TEST_EQUAL(fma(T(3),         nt2::Inf<cT>(),   T(4)), nt2::Inf<cT>());
  NT2_TEST_EQUAL(fma(nt2::Inf<T>(),cT(3, 4),         T(4)), cT(nt2::Inf<T>(), nt2::Inf<T>()));
  NT2_TEST_EQUAL(fma(nt2::Inf<T>(),cT(4),            T(3)), nt2::Inf<cT>());
  NT2_TEST_EQUAL(fma(T(0),         nt2::Inf<cT>(),   T(4)), nt2::Nan<cT>());
  NT2_TEST_EQUAL(fma(nt2::Inf<T>(),cT(0),            T(4)), nt2::Nan<cT>());
  NT2_TEST_EQUAL(fma(T(4),         nt2::Inf<cT>(),   T(3)), nt2::Inf<cT>());
  NT2_TEST_EQUAL(fma(T(4), cT(0, nt2::Inf<T>()), T(3)), cT(3, nt2::Inf<T>()));
  NT2_TEST_EQUAL(fma(nt2::Inf<T>(),  T(0), cT(6, 4)), cT(nt2::Nan<T>(), 4));
  NT2_TEST_EQUAL(fma(T(0), nt2::Inf<T>(),  cT(6, 4)), cT(nt2::Nan<T>(), 4));
  NT2_TEST_EQUAL(fma(nt2::Inf<T>(),  T(1), cT(6, 4)), cT(nt2::Inf<T>(), 4));
  NT2_TEST_EQUAL(fma(T(1), nt2::Inf<T>(),  cT(6, 4)), cT(nt2::Inf<T>(), 4));
#endif
  NT2_TEST_EQUAL(fma(cT(2), cT(3), cT(4)), cT(10));
  NT2_TEST_EQUAL(fma(cT(2, 3), cT(3, 1), cT(2, 4)), cT(5, 15));
}
