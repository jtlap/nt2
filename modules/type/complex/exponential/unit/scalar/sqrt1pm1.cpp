//==============================================================================
//         Copyright 2003 - 2013   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/include/functions/sqrt1pm1.hpp>

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

#include <nt2/include/constants/eps.hpp>
#include <nt2/include/constants/half.hpp>
#include <nt2/include/constants/mone.hpp>
#include <nt2/include/constants/one.hpp>
#include <nt2/include/constants/sqrt_2.hpp>
#include <nt2/include/constants/zero.hpp>
#include <nt2/include/constants/inf.hpp>
#include <nt2/include/constants/minf.hpp>
#include <nt2/include/constants/nan.hpp>
#include <nt2/include/constants/i.hpp>

NT2_TEST_CASE_TPL ( sqrt1pm1_real,  NT2_REAL_TYPES)
{
  using nt2::sqrt1pm1;
  using nt2::tag::sqrt1pm1_;
  typedef typename std::complex<T> cT;
  typedef typename nt2::meta::call<sqrt1pm1_(cT)>::type r_t;

  // return type conformity test
  NT2_TEST_TYPE_IS(r_t, cT);

  // specific values tests
#ifndef BOOST_SIMD_NO_INVALIDS
    NT2_TEST_ULP_EQUAL(sqrt1pm1(nt2::Inf<cT>()),  cT(nt2::Inf<T>()), 0);
    NT2_TEST_ULP_EQUAL(sqrt1pm1(nt2::Minf<cT>()),  cT(-1, nt2::Inf<T>()), 0);
    NT2_TEST_ULP_EQUAL(sqrt1pm1(nt2::Nan<cT>()),  cT(nt2::Nan<T>(), nt2::Nan<T>()), 0);
#endif
    NT2_TEST_ULP_EQUAL(sqrt1pm1(nt2::Mone<cT>()),  cT(nt2::Mone<T>()), 0);
    NT2_TEST_ULP_EQUAL(sqrt1pm1(nt2::One<cT>()),  cT(nt2::Sqrt_2<T>()-nt2::One<T>()), 2);
    NT2_TEST_ULP_EQUAL(sqrt1pm1(cT(nt2::Eps<T>())), cT(nt2::Eps<T>()*nt2::Half<T>()), 2);
    NT2_TEST_ULP_EQUAL(sqrt1pm1(cT(-1, 2)), cT(0, 1), 2);
    NT2_TEST_ULP_EQUAL(sqrt1pm1(nt2::Zero<cT>()),  cT(nt2::Zero<T>()), 0);
}
