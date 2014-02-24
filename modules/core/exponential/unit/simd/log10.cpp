//==============================================================================
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/exponential/include/functions/log10.hpp>

#include <nt2/sdk/functor/meta/call.hpp>
#include <boost/simd/sdk/simd/native.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>
#include <nt2/sdk/unit/tests/ulp.hpp>
#include <nt2/include/functions/splat.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <boost/simd/sdk/config.hpp>
#include <boost/simd/sdk/simd/io.hpp>

#include <nt2/include/constants/mone.hpp>
#include <nt2/include/constants/one.hpp>
#include <nt2/include/constants/zero.hpp>
#include <nt2/include/constants/inf.hpp>
#include <nt2/include/constants/minf.hpp>
#include <nt2/include/constants/nan.hpp>
#include <nt2/include/constants/ten.hpp>
#include <nt2/include/constants/two.hpp>
#include <nt2/include/constants/hundred.hpp>

NT2_TEST_CASE_TPL ( log10,  NT2_SIMD_REAL_TYPES)
{
  using nt2::log10;
  using nt2::tag::log10_;
  using boost::simd::native;
  typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef native<T,ext_t>                  vT;

  typedef typename nt2::meta::call<log10_(vT)>::type r_t;
  typedef vT wished_r_t;

  // return type conformity test
  NT2_TEST_TYPE_IS(r_t, wished_r_t);


  // specific values tests
#ifndef BOOST_SIMD_NO_INVALIDS
  NT2_TEST_ULP_EQUAL(log10(nt2::Inf<vT>()), nt2::Inf<r_t>(), 0);
  NT2_TEST_ULP_EQUAL(log10(nt2::Minf<vT>()), nt2::Nan<r_t>(), 0);
  NT2_TEST_ULP_EQUAL(log10(nt2::Nan<vT>()), nt2::Nan<r_t>(), 0);
  NT2_TEST_ULP_EQUAL(log10(nt2::Mone<vT>()), nt2::Nan<r_t>(), 0);
  NT2_TEST_ULP_EQUAL(log10(nt2::Zero<vT>()), nt2::Minf<r_t>(), 0);
#endif
  NT2_TEST_ULP_EQUAL(log10(nt2::One<vT>()), nt2::Zero<r_t>(), 0);
}

NT2_TEST_CASE_TPL ( log10_unsigned_uint8,  (uint8_t))
{
  using nt2::log10;
  using nt2::tag::log10_;
  using boost::simd::native;
  using boost::simd::meta::vector_of;
  typedef typename vector_of<T, BOOST_SIMD_BYTES/sizeof(T)>::type vT;

  typedef typename nt2::meta::call<log10_(vT)>::type r_t;
  typedef vT wished_r_t;

  // return type conformity test
  NT2_TEST_TYPE_IS(r_t, wished_r_t);

  // specific values tests
  NT2_TEST_ULP_EQUAL(log10(nt2::One<vT>()), nt2::Zero<r_t>(), 0);
  NT2_TEST_ULP_EQUAL(log10(nt2::Ten<vT>()), nt2::One<r_t>(), 0);
  NT2_TEST_ULP_EQUAL(log10(nt2::Hundred<vT>()), nt2::Two<vT>(), 0);
}


NT2_TEST_CASE_TPL ( log10_unsigned_int,  (uint16_t))
{
  using nt2::log10;
  using nt2::tag::log10_;
  using boost::simd::native;
  using boost::simd::meta::vector_of;
  typedef typename vector_of<T, BOOST_SIMD_BYTES/sizeof(T)>::type vT;

  typedef typename nt2::meta::call<log10_(vT)>::type r_t;
  typedef vT wished_r_t;

  // return type conformity test
  NT2_TEST_TYPE_IS(r_t, wished_r_t);

  // specific values tests
  NT2_TEST_ULP_EQUAL(log10(nt2::One<vT>()), nt2::Zero<r_t>(), 0);
  NT2_TEST_ULP_EQUAL(log10(nt2::Ten<vT>()), nt2::One<r_t>(), 0);
  NT2_TEST_ULP_EQUAL(log10(nt2::splat<vT>(100)), nt2::splat<vT>(2), 0);
  NT2_TEST_ULP_EQUAL(log10(nt2::splat<vT>(1000)), nt2::splat<vT>(3), 0);
  NT2_TEST_ULP_EQUAL(log10(nt2::splat<vT>(10000)), nt2::splat<vT>(4), 0);
}

NT2_TEST_CASE_TPL ( log10_unsigned_uint32,  (uint32_t))
{
  using nt2::log10;
  using nt2::tag::log10_;
  using boost::simd::native;
  using boost::simd::meta::vector_of;
  typedef typename vector_of<T, BOOST_SIMD_BYTES/sizeof(T)>::type vT;

  typedef typename nt2::meta::call<log10_(vT)>::type r_t;
  typedef vT wished_r_t;

  // return type conformity test
  NT2_TEST_TYPE_IS(r_t, wished_r_t);

  // specific values tests
  NT2_TEST_ULP_EQUAL(log10(nt2::One<vT>()), nt2::Zero<r_t>(), 0);
  NT2_TEST_ULP_EQUAL(log10(nt2::Ten<vT>()), nt2::One<r_t>(), 0);
  NT2_TEST_ULP_EQUAL(log10(nt2::splat<vT>(100)), nt2::splat<vT>(2), 0);
  NT2_TEST_ULP_EQUAL(log10(nt2::splat<vT>(1000)), nt2::splat<vT>(3), 0);
  NT2_TEST_ULP_EQUAL(log10(nt2::splat<vT>(10000)), nt2::splat<vT>(4), 0);
  NT2_TEST_ULP_EQUAL(log10(nt2::splat<vT>(100000)), nt2::splat<vT>(5), 0);
  NT2_TEST_ULP_EQUAL(log10(nt2::splat<vT>(1000000)), nt2::splat<vT>(6), 0);
  NT2_TEST_ULP_EQUAL(log10(nt2::splat<vT>(10000000)), nt2::splat<vT>(7), 0);
  NT2_TEST_ULP_EQUAL(log10(nt2::splat<vT>(100000000)), nt2::splat<vT>(8), 0);
  NT2_TEST_ULP_EQUAL(log10(nt2::splat<vT>(1000000000)), nt2::splat<vT>(9), 0);
}

NT2_TEST_CASE_TPL ( log10_unsigned_uint64,  (uint64_t))
{
  using nt2::log10;
  using nt2::tag::log10_;
  using boost::simd::meta::vector_of;
  typedef typename vector_of<T, BOOST_SIMD_BYTES/sizeof(T)>::type vT;
  typedef typename nt2::meta::call<log10_(vT)>::type r_t;
  typedef vT wished_r_t;

  // return type conformity test
  NT2_TEST_TYPE_IS(r_t, wished_r_t);

  // specific values tests
  NT2_TEST_ULP_EQUAL(log10(nt2::One<vT>()), nt2::Zero<r_t>(), 0);
  NT2_TEST_ULP_EQUAL(log10(nt2::Ten<vT>()), nt2::One<r_t>(), 0);
  NT2_TEST_ULP_EQUAL(log10(nt2::splat<vT>(100ull)), nt2::splat<vT>(2), 0);
  NT2_TEST_ULP_EQUAL(log10(nt2::splat<vT>(1000ull)), nt2::splat<vT>(3), 0);
  NT2_TEST_ULP_EQUAL(log10(nt2::splat<vT>(10000ull)), nt2::splat<vT>(4), 0);
  NT2_TEST_ULP_EQUAL(log10(nt2::splat<vT>(100000ull)), nt2::splat<vT>(5), 0);
  NT2_TEST_ULP_EQUAL(log10(nt2::splat<vT>(1000000ull)), nt2::splat<vT>(6), 0);
  NT2_TEST_ULP_EQUAL(log10(nt2::splat<vT>(10000000ull)), nt2::splat<vT>(7), 0);
  NT2_TEST_ULP_EQUAL(log10(nt2::splat<vT>(100000000ull)), nt2::splat<vT>(8), 0);
  NT2_TEST_ULP_EQUAL(log10(nt2::splat<vT>(1000000000ull)), nt2::splat<vT>(9), 0);
  NT2_TEST_ULP_EQUAL(log10(nt2::splat<vT>(10000000000ull)), nt2::splat<vT>(10), 0);
  NT2_TEST_ULP_EQUAL(log10(nt2::splat<vT>(100000000000ull)), nt2::splat<vT>(11), 0);
  NT2_TEST_ULP_EQUAL(log10(nt2::splat<vT>(1000000000000ull)), nt2::splat<vT>(12), 0);
  NT2_TEST_ULP_EQUAL(log10(nt2::splat<vT>(10000000000000ull)), nt2::splat<vT>(13), 0);
  NT2_TEST_ULP_EQUAL(log10(nt2::splat<vT>(100000000000000ull)), nt2::splat<vT>(14), 0);
  NT2_TEST_ULP_EQUAL(log10(nt2::splat<vT>(1000000000000000ull)), nt2::splat<vT>(15), 0);
  NT2_TEST_ULP_EQUAL(log10(nt2::splat<vT>(10000000000000000ull)), nt2::splat<vT>(16), 0);
  NT2_TEST_ULP_EQUAL(log10(nt2::splat<vT>(100000000000000000ull)), nt2::splat<vT>(17), 0);
  NT2_TEST_ULP_EQUAL(log10(nt2::splat<vT>(1000000000000000000ull)), nt2::splat<vT>(18), 0);
  NT2_TEST_ULP_EQUAL(log10(nt2::splat<vT>(10000000000000000000ull)), nt2::splat<vT>(19), 0);
}

NT2_TEST_CASE_TPL ( log10_signed_int,  NT2_INTEGRAL_SIGNED_TYPES)
{
  using nt2::log10;
  using nt2::tag::log10_;
  using boost::simd::native;
  typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef native<T,ext_t>                  vT;

  typedef typename nt2::meta::call<log10_(vT)>::type r_t;
  typedef vT wished_r_t;

  // return type conformity test
  NT2_TEST_TYPE_IS(r_t, wished_r_t);

  // specific values tests
  NT2_TEST_ULP_EQUAL(log10(nt2::One<vT>()), nt2::Zero<r_t>(), 0);
  NT2_TEST_ULP_EQUAL(log10(nt2::Ten<vT>()), nt2::One<r_t>(), 0);
}
