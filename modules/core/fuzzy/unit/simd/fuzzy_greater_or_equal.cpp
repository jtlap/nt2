//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/fuzzy/include/functions/fuzzy_greater_or_equal.hpp>
#include <boost/simd/sdk/simd/native.hpp>
#include <nt2/sdk/functor/meta/call.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <boost/simd/sdk/simd/io.hpp>
#include <nt2/constant/constant.hpp>
#include <nt2/include/functions/splat.hpp>
#include <nt2/include/functions/simd/plus.hpp>


NT2_TEST_CASE_TPL ( fuzzy_greater_or_equal_real__3_0,  NT2_SIMD_REAL_TYPES)
{
  using nt2::fuzzy_greater_or_equal;
  using nt2::tag::fuzzy_greater_or_equal_;
  using boost::simd::native;
  typedef NT2_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef native<T,ext_t>                vT;
  typedef typename nt2::meta::call<fuzzy_greater_or_equal_(vT,vT,vT)>::type r_t;

  // specific values tests
  NT2_TEST_EQUAL(fuzzy_greater_or_equal(nt2::splat<vT>(0),nt2::splat<vT>(0),nt2::splat<vT>(1)), nt2::True<r_t>());
  NT2_TEST_EQUAL(fuzzy_greater_or_equal(nt2::splat<vT>(1),nt2::splat<vT>(1)+nt2::Eps<vT>(),nt2::Eps<vT>()), nt2::True<r_t>());
  NT2_TEST_EQUAL(fuzzy_greater_or_equal(nt2::splat<vT>(1),nt2::splat<vT>(2),nt2::splat<vT>(0.25)), nt2::False<r_t>());
  NT2_TEST_EQUAL(fuzzy_greater_or_equal(nt2::splat<vT>(1),nt2::splat<vT>(2),nt2::splat<vT>(1)), nt2::True<r_t>());
} // end of test for floating_
