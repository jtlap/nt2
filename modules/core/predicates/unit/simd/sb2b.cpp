//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#define NT2_UNIT_MODULE "nt2 predicates toolbox - sb2b/simd Mode"

//////////////////////////////////////////////////////////////////////////////
// unit test behavior of predicates components in simd mode
//////////////////////////////////////////////////////////////////////////////
/// created  by jt the 21/02/2011
///
#include <nt2/toolbox/predicates/include/functions/sb2b.hpp>
#include <boost/simd/sdk/simd/native.hpp>
#include <nt2/sdk/simd/logical.hpp>
#include <nt2/sdk/functor/meta/call.hpp>
#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/toolbox/constant/constant.hpp>

NT2_TEST_CASE_TPL ( sb2b_real__1_0,  BOOST_SIMD_SIMD_REAL_TYPES)
{
  using nt2::sb2b;
  using nt2::tag::sb2b_;
  using boost::simd::native;

  typedef NT2_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef native<T,ext_t>                        vT;
  typedef typename nt2::meta::call<sb2b_(vT)>::type r_t;
  typedef typename nt2::meta::scalar_of<r_t>::type sr_t;

  // specific values tests
  NT2_TEST_EQUAL(sb2b(nt2::Mzero<vT>())[0], nt2::Zero<sr_t>());
  NT2_TEST_EQUAL(sb2b(nt2::Half<vT>())[0], nt2::One<sr_t>());
  NT2_TEST_EQUAL(sb2b(nt2::Inf<vT>())[0], nt2::One<sr_t>());
  NT2_TEST_EQUAL(sb2b(nt2::Minf<vT>())[0], nt2::One<sr_t>());
  NT2_TEST_EQUAL(sb2b(nt2::Mone<vT>())[0], nt2::One<sr_t>());
  NT2_TEST_EQUAL(sb2b(nt2::Nan<vT>())[0], nt2::One<sr_t>());
  NT2_TEST_EQUAL(sb2b(nt2::One<vT>())[0], nt2::One<sr_t>());
  NT2_TEST_EQUAL(sb2b(nt2::Quarter<vT>())[0], nt2::One<sr_t>());
  NT2_TEST_EQUAL(sb2b(nt2::Two<vT>())[0], nt2::One<sr_t>());
   NT2_TEST_EQUAL(sb2b(nt2::Zero<vT>())[0], nt2::Zero<sr_t>());
 } // end of test for floating_
