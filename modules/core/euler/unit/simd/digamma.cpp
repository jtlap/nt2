//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================

#include <nt2/euler/include/functions/digamma.hpp>
#include <boost/simd/sdk/simd/native.hpp>
#include <nt2/sdk/functor/meta/call.hpp>
#include <nt2/sdk/unit/tests/ulp.hpp>
#include <nt2/sdk/unit/module.hpp>

#include <nt2/constant/constant.hpp>
#include <nt2/include/functions/splat.hpp>


NT2_TEST_CASE_TPL ( digamma_real__1_0,  NT2_SIMD_REAL_TYPES)
{
  using nt2::digamma;
  using nt2::tag::digamma_;
  using boost::simd::native;
  typedef NT2_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef native<T,ext_t>                vT;

  // specific values tests
  NT2_TEST_ULP_EQUAL(digamma(nt2::One<vT>()), nt2::splat<vT>(-0.57721566490153286555), 0.5);
} // end of test for floating_
