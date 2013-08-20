//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/bessel/include/functions/y0.hpp>
#include <boost/simd/sdk/simd/native.hpp>
#include <nt2/sdk/functor/meta/call.hpp>
#include <nt2/sdk/unit/tests/ulp.hpp>
#include <nt2/sdk/unit/module.hpp>

#include <nt2/constant/constant.hpp>
#include <nt2/include/functions/splat.hpp>

NT2_TEST_CASE_TPL ( y0_real__1_0,  NT2_SIMD_REAL_TYPES)
{
  using nt2::y0;
  using nt2::tag::y0_;
  using boost::simd::native;
  typedef NT2_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef native<T,ext_t>                vT;
  typedef typename nt2::meta::call<y0_(vT)>::type r_t;

  // specific values tests
  NT2_TEST_ULP_EQUAL(y0(nt2::One<vT>()), nt2::splat<r_t>( 8.825696421567700e-02), 2);
  NT2_TEST_ULP_EQUAL(y0(nt2::Zero<vT>()), nt2::Minf<r_t>(), 0);
} // end of test for real_
