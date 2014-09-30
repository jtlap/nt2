//==============================================================================
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/exponential/include/functions/pow2.hpp>
#include <boost/simd/sdk/simd/native.hpp>
#include <boost/simd/sdk/simd/io.hpp>

#include <nt2/include/functions/splat.hpp>
#include <nt2/include/functions/unary_minus.hpp>
#include <nt2/include/constants/four.hpp>
#include <nt2/include/constants/mone.hpp>
#include <nt2/include/constants/one.hpp>
#include <nt2/include/constants/two.hpp>
#include <nt2/include/constants/zero.hpp>
#include <nt2/include/constants/inf.hpp>
#include <nt2/include/constants/minf.hpp>
#include <nt2/include/constants/nan.hpp>
#include <nt2/sdk/meta/as_integer.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/ulp.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/exceptions.hpp>


NT2_TEST_CASE_TPL ( pow2,  NT2_SIMD_REAL_TYPES)
{
  using nt2::pow2;
  using nt2::tag::pow2_;
  using boost::simd::native;
  typedef NT2_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef native<T,ext_t>                         vT;
  typedef typename nt2::meta::as_integer<T>::type iT;
  typedef native<iT,ext_t>                       viT;
  typedef typename nt2::meta::call<pow2_(vT)>::type r_t;

  // specific values tests
#ifndef BOOST_SIMD_NO_INVALIDS
  NT2_TEST_ASSERT(pow2(nt2::Inf<vT>()));
  NT2_TEST_ASSERT(pow2(nt2::Minf<vT>()));
  NT2_TEST_ASSERT(pow2(nt2::Nan<vT>()));
  NT2_TEST_ASSERT(pow2(nt2::One<vT>(), nt2::Inf<vT>()));
  NT2_TEST_ASSERT(pow2(nt2::One<vT>(), nt2::Minf<vT>()));
  NT2_TEST_ASSERT(pow2(nt2::One<vT>(), nt2::Nan<vT>()));
#endif
  NT2_TEST_EQUAL(pow2(nt2::Inf<vT>(),  nt2::Two<viT>()), nt2::Inf<r_t>());
  NT2_TEST_EQUAL(pow2(nt2::Minf<vT>(), nt2::Two<viT>()), nt2::Minf<r_t>());
  NT2_TEST_EQUAL(pow2(nt2::Nan<vT>(),  nt2::Two<viT>()), nt2::Nan<r_t>());
  NT2_TEST_EQUAL(pow2(nt2::Inf<vT>(),  nt2::splat<vT>(T(2.5))), nt2::Inf<r_t>());
  NT2_TEST_EQUAL(pow2(nt2::Minf<vT>(), nt2::splat<vT>(T(2.5))), nt2::Minf<r_t>());
  NT2_TEST_EQUAL(pow2(nt2::Nan<vT>(),  nt2::splat<vT>(T(2.5))), nt2::Nan<r_t>());
  NT2_TEST_EQUAL(pow2(nt2::Mone<vT>(), nt2::Two<viT>()), -nt2::Four<r_t>());
  NT2_TEST_EQUAL(pow2(nt2::One<vT>(),  nt2::Two<viT>()), nt2::Four<r_t>());
  NT2_TEST_EQUAL(pow2(nt2::Zero<vT>(), nt2::Two<viT>()), nt2::Zero<r_t>());
  NT2_TEST_EQUAL(pow2(nt2::Mone<vT>(), nt2::splat<vT>(T(2.5))), -nt2::Four<r_t>());
  NT2_TEST_EQUAL(pow2(nt2::One<vT>(),  nt2::splat<vT>(T(2.5))), nt2::Four<r_t>());
  NT2_TEST_EQUAL(pow2(nt2::Zero<vT>(), nt2::splat<vT>(T(2.5))), nt2::Zero<r_t>());
}
