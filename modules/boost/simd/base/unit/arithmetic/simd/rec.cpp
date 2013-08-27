//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <boost/simd/arithmetic/include/functions/rec.hpp>
#include <boost/simd/sdk/simd/native.hpp>
#include <boost/dispatch/functor/meta/call.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/ulp.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <boost/simd/include/functions/simd/plus.hpp>
#include <boost/simd/include/constants/zero.hpp>
#include <boost/simd/include/constants/mzero.hpp>
#include <boost/simd/include/constants/one.hpp>
#include <boost/simd/include/constants/mone.hpp>
#include <boost/simd/include/constants/two.hpp>
#include <boost/simd/include/constants/mtwo.hpp>
#include <boost/simd/include/constants/inf.hpp>
#include <boost/simd/include/constants/minf.hpp>
#include <boost/simd/include/constants/nan.hpp>
#include <boost/simd/sdk/config.hpp>
#include <boost/simd/sdk/simd/io.hpp>

NT2_TEST_CASE_TPL ( rec,  BOOST_SIMD_SIMD_REAL_TYPES)
{
  using boost::simd::rec;
  using boost::simd::tag::rec_;
  using boost::simd::native;

  typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef native<T,ext_t>               vT;

  // specific values tests
#ifndef BOOST_SIMD_NO_INVALIDS

  // 1/+-inf = 0
  NT2_TEST_ULP_EQUAL(rec(boost::simd::Inf<vT>()) , boost::simd::Zero<vT>(), 0.5);
  NT2_TEST_ULP_EQUAL(rec(boost::simd::Minf<vT>()), boost::simd::Zero<vT>(), 0.5);

  // 1/+-0 = +-inf
  NT2_TEST_ULP_EQUAL(rec(boost::simd::Mzero<vT>()), boost::simd::Minf<vT>(), 0.5);
  NT2_TEST_ULP_EQUAL(rec(boost::simd::Zero<vT>()), boost::simd::Inf<vT>(), 0.5);

  // 1/Nan = Nan
  NT2_TEST_ULP_EQUAL(rec(boost::simd::Nan<vT>()), boost::simd::Nan<vT>(), 0.5);
#endif

  // 1/+-1 = +-1
  NT2_TEST_ULP_EQUAL(rec(boost::simd::Mone<vT>()), boost::simd::Mone<vT>(), 0.5);
  NT2_TEST_ULP_EQUAL(rec(boost::simd::One<vT>()), boost::simd::One<vT>(), 0.5);

  // 1/(1/x) = x
  NT2_TEST_ULP_EQUAL(rec(rec(boost::simd::Ten<vT>())), boost::simd::Ten<vT>(), 0.5);
}
