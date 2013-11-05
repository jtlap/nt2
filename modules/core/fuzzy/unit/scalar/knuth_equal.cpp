//==============================================================================
//         Copyright 2003 - 2013   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/fuzzy/include/functions/knuth_equal.hpp>

#include <nt2/sdk/functor/meta/call.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>
#include <nt2/sdk/unit/tests/basic.hpp>
#include <nt2/sdk/meta/as_integer.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <boost/simd/sdk/config.hpp>
#include <nt2/sdk/simd/logical.hpp>

#include <nt2/include/constants/false.hpp>
#include <nt2/include/constants/true.hpp>

NT2_TEST_CASE_TPL ( knuth_equal_real,  NT2_REAL_TYPES)
{
  using nt2::knuth_equal;
  using nt2::tag::knuth_equal_;

  typedef typename nt2::meta::call<knuth_equal_(T,T,T)>::type r_t;
  typedef typename nt2::meta::as_logical<T>::type wished_r_t;

  // return type conformity test
  NT2_TEST_TYPE_IS(r_t, wished_r_t);

  // specific values tests
  NT2_TEST_EQUAL(knuth_equal(T(0),T(0),T(1)), nt2::True<r_t>());
  NT2_TEST_EQUAL(knuth_equal(T(0),T(1),T(0.5)), nt2::False<r_t>());
  NT2_TEST_EQUAL(knuth_equal(T(0),T(1),T(1)), nt2::True<r_t>());
}
