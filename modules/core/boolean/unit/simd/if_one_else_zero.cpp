//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#define NT2_UNIT_MODULE "nt2 boolean toolbox - if_one_else_zero/simd Mode"

//////////////////////////////////////////////////////////////////////////////
// unit test behavior of boolean components in simd mode
//////////////////////////////////////////////////////////////////////////////
/// created  by jt the 21/02/2011
///
#include <nt2/boolean/include/functions/if_one_else_zero.hpp>
#include <boost/simd/sdk/simd/io.hpp>
#include <nt2/sdk/meta/as_integer.hpp>
#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>
#include <boost/simd/sdk/simd/native.hpp>
#include <nt2/constant/constant.hpp>
#include <nt2/include/constants/one.hpp>
#include <nt2/include/constants/two.hpp>
#include <nt2/include/constants/inf.hpp>
#include <nt2/include/constants/zero.hpp>
#include <nt2/include/constants/minf.hpp>
#include <nt2/include/constants/mone.hpp>
#include <nt2/include/constants/nan.hpp>
#include <nt2/include/constants/true.hpp>
#include <nt2/include/constants/false.hpp>

NT2_TEST_CASE_TPL ( if_one_else_zero_real__1_0,  BOOST_SIMD_SIMD_REAL_TYPES)
{
  using nt2::if_one_else_zero;
  using nt2::tag::if_one_else_zero_;
  using boost::simd::native;

  typedef NT2_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef native<T,ext_t>                        vT;
  typedef typename nt2::meta::call<if_one_else_zero_(vT)>::type r_t;

  // specific values tests
  NT2_TEST_EQUAL(if_one_else_zero(nt2::Mzero<vT>()), nt2::Zero<r_t>());
  NT2_TEST_EQUAL(if_one_else_zero(nt2::Half<vT>()), nt2::One<r_t>());
  NT2_TEST_EQUAL(if_one_else_zero(nt2::Inf<vT>()), nt2::One<r_t>());
  NT2_TEST_EQUAL(if_one_else_zero(nt2::Minf<vT>()), nt2::One<r_t>());
  NT2_TEST_EQUAL(if_one_else_zero(nt2::Mone<vT>()), nt2::One<r_t>());
  NT2_TEST_EQUAL(if_one_else_zero(nt2::Nan<vT>()), nt2::One<r_t>());
  NT2_TEST_EQUAL(if_one_else_zero(nt2::One<vT>()), nt2::One<r_t>());
  NT2_TEST_EQUAL(if_one_else_zero(nt2::Quarter<vT>()), nt2::One<r_t>());
  NT2_TEST_EQUAL(if_one_else_zero(nt2::Two<vT>()), nt2::One<r_t>());
   NT2_TEST_EQUAL(if_one_else_zero(nt2::Zero<vT>()), nt2::Zero<r_t>());
 } // end of test for floating_
