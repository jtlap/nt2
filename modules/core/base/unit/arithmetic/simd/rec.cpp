//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/include/functions/rec.hpp>
#include <boost/simd/sdk/simd/native.hpp>
#include <boost/simd/sdk/simd/io.hpp>

#include <boost/dispatch/functor/meta/call.hpp>
#include <boost/simd/constant/constant.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/ulp.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>

NT2_TEST_CASE_TPL ( rec,  BOOST_SIMD_SIMD_REAL_TYPES)
{
  using nt2::rec;
  using nt2::tag::rec_;
  using boost::simd::native;

  typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef native<T,ext_t>               vT;

  NT2_TEST_TYPE_IS( typename boost::dispatch::meta::call<rec_(vT)>::type
                  , (native<T,ext_t>)
                  );

  // specific values tests

  // 1/+-inf = 0
  NT2_TEST_ULP_EQUAL(rec(boost::simd::Inf<vT>()) , boost::simd::Zero<vT>(), 0.5);
  NT2_TEST_ULP_EQUAL(rec(boost::simd::Minf<vT>()), boost::simd::Zero<vT>(), 0.5);

  // 1/+-0 = +-inf
  NT2_TEST_ULP_EQUAL(rec(boost::simd::Mzero<vT>()), boost::simd::Minf<vT>(), 0.5);
  NT2_TEST_ULP_EQUAL(rec(boost::simd::Zero<vT>()), boost::simd::Inf<vT>(), 0.5);

  // 1/Nan = Nan
  NT2_TEST_ULP_EQUAL(rec(boost::simd::Nan<vT>()), boost::simd::Nan<vT>(), 0.5);

  // 1/+-1 = +-1
  NT2_TEST_ULP_EQUAL(rec(boost::simd::Mone<vT>()), boost::simd::Mone<vT>(), 0.5);
  NT2_TEST_ULP_EQUAL(rec(boost::simd::One<vT>()), boost::simd::One<vT>(), 0.5);

  // 1/(1/x) = x
  NT2_TEST_ULP_EQUAL(rec(rec(boost::simd::Ten<vT>())), boost::simd::Ten<vT>(), 0.5);
}
