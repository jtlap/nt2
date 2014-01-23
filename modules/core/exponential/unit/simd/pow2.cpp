//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/exponential/include/functions/pow2.hpp>
#include <nt2/exponential/include/functions/logspace_sub.hpp>
#include <nt2/sdk/functor/meta/call.hpp>
#include <nt2/sdk/unit/tests/ulp.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/meta/as_integer.hpp>

#include <nt2/constant/constant.hpp>
#include <nt2/include/functions/splat.hpp>
#include <nt2/sdk/meta/as_integer.hpp>

NT2_TEST_CASE_TPL ( pow2,  NT2_SIMD_REAL_TYPES)
{
  using nt2::pow2;
  using nt2::tag::pow2_;
  using boost::simd::native;
  typedef NT2_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef typename nt2::meta::upgrade<T>::type   u_t;
  typedef native<T,ext_t>                         vT;
  typedef typename nt2::meta::as_integer<T>::type iT;
  typedef native<iT,ext_t>                       ivT;
  typedef typename nt2::meta::call<pow2_(vT)>::type r_t;

  // specific values tests
#ifndef BOOST_SIMD_NO_INVALIDS
   NT2_TEST_ULP_EQUAL(pow2(nt2::Inf<vT>()), nt2::Inf<r_t>(), 0);
   NT2_TEST_ULP_EQUAL(pow2(nt2::Minf<vT>()), nt2::Zero<r_t>(), 0);
   NT2_TEST_ULP_EQUAL(pow2(nt2::Nan<vT>()), nt2::Nan<r_t>(), 0);
#endif
   NT2_TEST_ULP_EQUAL(pow2(nt2::One<vT>()), nt2::Two<r_t>(), 0);
   NT2_TEST_ULP_EQUAL(pow2(nt2::Zero<vT>()), nt2::One<r_t>(), 0);
   NT2_TEST_ULP_EQUAL(pow2(nt2::Mone<vT>()), nt2::Half<r_t>(), 0);;
} // end of test for floating_
