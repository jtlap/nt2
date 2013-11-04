//==============================================================================
//         Copyright 2003 - 2013   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/exponential/include/functions/pow2.hpp>

#include <nt2/sdk/functor/meta/call.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>
#include <nt2/sdk/meta/as_integer.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <boost/simd/sdk/config.hpp>
#include <nt2/sdk/meta/as_integer.hpp>

#include <nt2/include/constants/four.hpp>
#include <nt2/include/constants/mone.hpp>
#include <nt2/include/constants/one.hpp>
#include <nt2/include/constants/zero.hpp>
#include <nt2/include/constants/inf.hpp>
#include <nt2/include/constants/minf.hpp>
#include <nt2/include/constants/nan.hpp>

NT2_TEST_CASE_TPL ( pow2_real,  BOOST_SIMD_REAL_TYPES)
{
  using nt2::pow2;
  using nt2::tag::pow2_;
  typedef typename nt2::meta::as_integer<T>::type          iT;
  typedef typename boost::dispatch::meta::call<pow2_(T,iT)>::type r_t;
  typedef T wished_r_t;

  // return type conformity test
  NT2_TEST_TYPE_IS(r_t, wished_r_t);

  // specific values tests
  NT2_TEST_EQUAL(pow2(nt2::Inf<T>(),  2), nt2::Inf<r_t>());
  NT2_TEST_EQUAL(pow2(nt2::Minf<T>(), 2), nt2::Minf<r_t>());
  NT2_TEST_EQUAL(pow2(nt2::Nan<T>(),  2), nt2::Nan<r_t>());
  NT2_TEST_EQUAL(pow2(nt2::Inf<T>(),  T(2.5)), nt2::Inf<r_t>());
  NT2_TEST_EQUAL(pow2(nt2::Minf<T>(), T(2.5)), nt2::Minf<r_t>());
  NT2_TEST_EQUAL(pow2(nt2::Nan<T>(),  T(2.5)), nt2::Nan<r_t>());
  NT2_TEST_EQUAL(pow2(nt2::Mone<T>(), 2), -nt2::Four<r_t>());
  NT2_TEST_EQUAL(pow2(nt2::One<T>(),  2), nt2::Four<r_t>());
  NT2_TEST_EQUAL(pow2(nt2::Zero<T>(), 2), nt2::Zero<r_t>());
  NT2_TEST_EQUAL(pow2(nt2::Mone<T>(), T(2.5)), -nt2::Four<r_t>());
  NT2_TEST_EQUAL(pow2(nt2::One<T>(),  T(2.5)), nt2::Four<r_t>());
  NT2_TEST_EQUAL(pow2(nt2::Zero<T>(), T(2.5)), nt2::Zero<r_t>());
}
