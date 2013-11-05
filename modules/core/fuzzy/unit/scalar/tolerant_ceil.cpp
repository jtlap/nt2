//==============================================================================
//         Copyright 2003 - 2013   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/fuzzy/include/functions/tolerant_ceil.hpp>

#include <nt2/sdk/functor/meta/call.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>
#include <nt2/sdk/unit/tests/basic.hpp>
#include <nt2/sdk/meta/as_integer.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <boost/simd/sdk/config.hpp>
#include <nt2/sdk/simd/logical.hpp>

#include <nt2/include/constants/eps.hpp>
#include <nt2/include/constants/four.hpp>
#include <nt2/include/constants/one.hpp>
#include <nt2/include/constants/three.hpp>
#include <nt2/include/constants/two.hpp>
#include <nt2/include/constants/zero.hpp>

NT2_TEST_CASE_TPL ( tolerant_ceil_real,  NT2_REAL_TYPES)
{
  using nt2::tolerant_ceil;
  using nt2::tag::tolerant_ceil_;

  typedef typename nt2::meta::call<tolerant_ceil_(T)>::type r_t;
  typedef T wished_r_t;

  // return type conformity test
  NT2_TEST_TYPE_IS(r_t, wished_r_t);

  // specific values tests
  NT2_TEST_EQUAL(tolerant_ceil(T(0)), nt2::Zero<r_t>());
  NT2_TEST_EQUAL(tolerant_ceil(nt2::Eps<T>()), nt2::Zero<r_t>());
  NT2_TEST_EQUAL(tolerant_ceil(nt2::Two<T>()*nt2::Eps<T>()), nt2::Zero<r_t>());
  NT2_TEST_EQUAL(tolerant_ceil(nt2::Three<T>()*nt2::Eps<T>()), nt2::Zero<r_t>());
  NT2_TEST_EQUAL(tolerant_ceil(nt2::Four<T>()*nt2::Eps<T>()), nt2::One<r_t>());
}
