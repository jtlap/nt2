//==============================================================================
//         Copyright 2003 - 2013   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/include/functions/ceil.hpp>

#include <boost/dispatch/functor/meta/call.hpp>
#include <nt2/sdk/functor/meta/call.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>
#include <complex>
#include <nt2/sdk/complex/complex.hpp>
#include <nt2/sdk/complex/dry.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <boost/simd/sdk/config.hpp>

#include <nt2/include/constants/mone.hpp>
#include <nt2/include/constants/one.hpp>
#include <nt2/include/constants/zero.hpp>
#include <nt2/include/constants/inf.hpp>
#include <nt2/include/constants/minf.hpp>
#include <nt2/include/constants/nan.hpp>

NT2_TEST_CASE_TPL ( ceil_real,  BOOST_SIMD_REAL_TYPES)
{
  using nt2::ceil;
  using nt2::tag::ceil_;
  typedef typename std::complex<T> cT;
  typedef typename nt2::dry<T> dT;

  // specific values tests
#ifndef BOOST_SIMD_NO_INVALIDS
  NT2_TEST_EQUAL(ceil(nt2::Inf<cT>()), nt2::Inf<cT>());
  NT2_TEST_EQUAL(ceil(nt2::Minf<cT>()), nt2::Minf<cT>());
  NT2_TEST_EQUAL(ceil(nt2::Nan<cT>()), nt2::Nan<cT>());
  NT2_TEST_EQUAL(ceil(dT(nt2::Inf<T>())), dT(nt2::Inf<T>()));
  NT2_TEST_EQUAL(ceil(dT(nt2::Minf<T>())), dT(nt2::Minf<T>()));
  NT2_TEST_EQUAL(ceil(dT(nt2::Nan<T>())), dT(nt2::Nan<T>()));
#endif
  NT2_TEST_EQUAL(ceil(cT(T(-1.1))), T(-1));
  NT2_TEST_EQUAL(ceil(cT(T(1.1))), T(2));
  NT2_TEST_EQUAL(ceil(nt2::Mone<cT>()), nt2::Mone<cT>());
  NT2_TEST_EQUAL(ceil(nt2::One<cT>()), nt2::One<cT>());
  NT2_TEST_EQUAL(ceil(nt2::Zero<cT>()), nt2::Zero<cT>());
  NT2_TEST_EQUAL(ceil(dT(T(-1.1))), T(-1));
  NT2_TEST_EQUAL(ceil(dT(T(1.1))), T(2));
  NT2_TEST_EQUAL(ceil(dT(nt2::Mone<T>())), dT(nt2::Mone<T>()));
  NT2_TEST_EQUAL(ceil(dT(nt2::One<T>())), dT(nt2::One<T>()));
  NT2_TEST_EQUAL(ceil(dT(nt2::Zero<T>())), dT(nt2::Zero<T>()));
}
