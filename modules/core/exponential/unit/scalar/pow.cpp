//==============================================================================
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/exponential/include/functions/pow.hpp>

#include <nt2/sdk/functor/meta/call.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>
#include <nt2/sdk/unit/tests/ulp.hpp>
#include <nt2/sdk/meta/as_integer.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <boost/simd/sdk/config.hpp>
#include <nt2/sdk/meta/as_floating.hpp>

#include <nt2/include/constants/eight.hpp>
#include <nt2/include/constants/mone.hpp>
#include <nt2/include/constants/one.hpp>
#include <nt2/include/constants/three.hpp>
#include <nt2/include/constants/two.hpp>
#include <nt2/include/constants/zero.hpp>
#include <nt2/include/constants/inf.hpp>
#include <nt2/include/constants/minf.hpp>
#include <nt2/include/constants/nan.hpp>

NT2_TEST_CASE_TPL(pow,  NT2_REAL_TYPES)
{
  using nt2::pow;
  using nt2::tag::pow_;

  typedef typename nt2::meta::call<pow_(T,T)>::type r_t;
  typedef T wished_r_t;

  // return type conformity test
  NT2_TEST_TYPE_IS(r_t, wished_r_t);

  // specific values tests
#ifndef BOOST_SIMD_NO_INVALIDS
  NT2_TEST_ULP_EQUAL(pow(nt2::Inf<T>(), nt2::Inf<T>()), nt2::Inf<r_t>(), 0);
  NT2_TEST_ULP_EQUAL(pow(nt2::Nan<T>(), nt2::Nan<T>()), nt2::Nan<r_t>(), 0);
  NT2_TEST_ULP_EQUAL(pow(nt2::Minf<T>(), nt2::Minf<T>()), nt2::Nan<r_t>(), 0);
  NT2_TEST_ULP_EQUAL(pow(nt2::Inf<T>(), nt2::Minf<T>()), nt2::Zero<r_t>(), 0);
#endif
  NT2_TEST_ULP_EQUAL(pow(T(-1),T(6)), T(1), 0);
  NT2_TEST_ULP_EQUAL(pow(nt2::Mone<T>(), nt2::Mone<T>()), nt2::Mone<r_t>(), 0);
  NT2_TEST_ULP_EQUAL(pow(nt2::One<T>(), nt2::One<T>()), nt2::One<r_t>(), 0);
  NT2_TEST_ULP_EQUAL(pow(nt2::Zero<T>(), nt2::Zero<T>()), nt2::One<r_t>(), 0);
  NT2_TEST_ULP_EQUAL(pow(T(-1),T(5)), T(-1), 0);
  NT2_TEST_ULP_EQUAL(pow(nt2::Zero<T>(), nt2::One<T>()), nt2::Zero<r_t>(), 0);
}

NT2_TEST_CASE_TPL(pow_real_int,  NT2_REAL_TYPES)
{
  using nt2::pow;
  using nt2::tag::pow_;
  using boost::simd::native;
  typedef typename nt2::meta::as_integer<T>::type          iT;
  typedef typename nt2::meta::call<pow_(T,iT)>::type r_t;
  typedef T wished_r_t;

  // return type conformity test
  NT2_TEST_TYPE_IS(r_t, wished_r_t);

  // specific values tests
  #ifndef BOOST_SIMD_NO_INVALIDS
  NT2_TEST_ULP_EQUAL(pow(nt2::Inf<T>(),3), nt2::Inf<r_t>(), 0);
  NT2_TEST_ULP_EQUAL(pow(nt2::Minf<T>(),3), nt2::Minf<r_t>(), 0);
  NT2_TEST_ULP_EQUAL(pow(nt2::Nan<T>(),3), nt2::Nan<r_t>(), 0);
  #endif

  NT2_TEST_ULP_EQUAL(pow(nt2::Two<T>(),-3), 1/nt2::Eight<r_t>(),  0);
}

NT2_TEST_CASE_TPL(pow_int,  NT2_TYPES)
{
  using nt2::pow;
  using nt2::tag::pow_;
  using boost::simd::native;
  typedef typename nt2::meta::as_integer<T>::type          iT;
  typedef typename nt2::meta::call<pow_(T,iT)>::type r_t;
  typedef T wished_r_t;

  // return type conformity test
  NT2_TEST_TYPE_IS(r_t, wished_r_t);

  // specific values tests
  NT2_TEST_ULP_EQUAL(pow(nt2::Mone<T>(),3), nt2::Mone<r_t>(),     0);
  NT2_TEST_ULP_EQUAL(pow(nt2::Mone<T>(),4), nt2::One<r_t>(),      0);
  NT2_TEST_ULP_EQUAL(pow(nt2::One<T>(),3),  nt2::One<r_t>(),      0);
  NT2_TEST_ULP_EQUAL(pow(nt2::Two<T>(),3),  nt2::Eight<r_t>(),    0);
  NT2_TEST_ULP_EQUAL(pow(nt2::Zero<T>(),0), nt2::One<r_t>(),      0);
  NT2_TEST_ULP_EQUAL(pow(nt2::Zero<T>(),3), nt2::Zero<r_t>(),     0);
}
