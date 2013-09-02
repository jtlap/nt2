//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/arithmetic/include/functions/rsqrt.hpp>
#include <boost/simd/sdk/simd/native.hpp>
#include <boost/simd/sdk/simd/io.hpp>
#include <nt2/sdk/functor/meta/call.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/ulp.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>

#include <nt2/include/constants/inf.hpp>
#include <nt2/include/constants/one.hpp>
#include <nt2/include/constants/nan.hpp>
#include <nt2/include/constants/minf.hpp>
#include <nt2/include/constants/zero.hpp>

NT2_TEST_CASE_TPL ( rsqrt,  NT2_SIMD_REAL_TYPES)
{
  using nt2::rsqrt;
  using nt2::tag::rsqrt_;
  using boost::simd::native;

  typedef NT2_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef native<T,ext_t>             vT;

  NT2_TEST_TYPE_IS( typename nt2::meta::call<rsqrt_(vT)>::type
                  , vT
                  );

  // specific values tests
  NT2_TEST_ULP_EQUAL(rsqrt(nt2::Inf<vT>()), nt2::Zero<vT>(), 0);
  NT2_TEST_ULP_EQUAL(rsqrt(nt2::Minf<vT>()), nt2::Nan<vT>(), 0);
  NT2_TEST_ULP_EQUAL(rsqrt(nt2::Mone<vT>()), nt2::Nan<vT>(), 0);
  NT2_TEST_ULP_EQUAL(rsqrt(nt2::Nan<vT>()), nt2::Nan<vT>(), 0);
  NT2_TEST_ULP_EQUAL(rsqrt(nt2::One<vT>()), nt2::One<vT>(), 0);
  NT2_TEST_ULP_EQUAL(rsqrt(nt2::Zero<vT>()), nt2::Inf<vT>(), 0);
}
