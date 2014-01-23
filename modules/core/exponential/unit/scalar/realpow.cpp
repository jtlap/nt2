//         Copyright 2003 - 2013   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/exponential/include/functions/realpow.hpp>

#include <nt2/sdk/functor/meta/call.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>
#include <nt2/sdk/unit/tests/ulp.hpp>
#include <nt2/sdk/unit/tests/exceptions.hpp>
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

NT2_TEST_CASE_TPL ( realpow_real,  NT2_REAL_TYPES)
{
  using nt2::realpow;
  using nt2::tag::realpow_;

  typedef typename nt2::meta::call<realpow_(T,T)>::type r_t;
  typedef T wished_r_t;

  // return type conformity test
  NT2_TEST_TYPE_IS(r_t, wished_r_t);

  // specific values tests
#ifndef BOOST_SIMD_NO_INVALIDS
  NT2_TEST_ULP_EQUAL(realpow(nt2::Inf<T>(), nt2::Inf<T>()), nt2::Inf<r_t>(), 0);
  NT2_TEST_ASSERT(realpow(nt2::Minf<T>(), nt2::Minf<T>()));
  NT2_TEST_ULP_EQUAL(realpow(nt2::Nan<T>(), nt2::Nan<T>()), nt2::Nan<r_t>(), 0);
#endif
  NT2_TEST_ASSERT(realpow(T(-1), T(0.5)));
  NT2_TEST_ULP_EQUAL(realpow(nt2::Mone<T>(), nt2::Mone<T>()), nt2::Mone<r_t>(), 0);
  NT2_TEST_ULP_EQUAL(realpow(nt2::One<T>(), nt2::One<T>()), nt2::One<r_t>(), 0);
  NT2_TEST_ULP_EQUAL(realpow(nt2::Zero<T>(), nt2::Zero<T>()), nt2::One<r_t>(), 0);
  NT2_TEST_ULP_EQUAL(realpow(T(-1),T(5)), T(-1), 0);
  NT2_TEST_ULP_EQUAL(realpow(T(-1),T(6)), T(1), 0);
}
