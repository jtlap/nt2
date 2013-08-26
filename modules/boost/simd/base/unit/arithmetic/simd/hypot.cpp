//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <boost/simd/arithmetic/include/functions/hypot.hpp>
#include <boost/simd/sdk/simd/native.hpp>
#include <boost/dispatch/functor/meta/call.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/ulp.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <boost/simd/include/functions/simd/plus.hpp>
#include <boost/simd/include/constants/one.hpp>
#include <boost/simd/include/constants/two.hpp>
#include <boost/simd/include/constants/mone.hpp>
#include <boost/simd/include/constants/mtwo.hpp>
#include <boost/simd/include/constants/inf.hpp>
#include <boost/simd/include/constants/minf.hpp>
#include <boost/simd/include/constants/nan.hpp>
#include <boost/simd/include/constants/sqrt_2.hpp>
#include <boost/simd/include/constants/valmax.hpp>
#include <boost/simd/include/constants/valmin.hpp>
#include <boost/simd/sdk/config.hpp>
#include <boost/simd/sdk/simd/io.hpp>

NT2_TEST_CASE_TPL ( hypot_real,  BOOST_SIMD_SIMD_REAL_TYPES)
{
  using boost::simd::hypot;
  using boost::simd::tag::hypot_;
  using boost::simd::native;
  typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef native<T,ext_t>                  vT;
  typedef typename boost::dispatch::meta::call<hypot_(vT,vT)>::type r_t;

  // specific values tests
  NT2_TEST_ULP_EQUAL(hypot(boost::simd::Inf<vT>(), boost::simd::Inf<vT>()), boost::simd::Inf<r_t>(), 0);
  NT2_TEST_ULP_EQUAL(hypot(boost::simd::Minf<vT>(), boost::simd::Minf<vT>()), boost::simd::Inf<r_t>(), 0);
  NT2_TEST_ULP_EQUAL(hypot(boost::simd::Mone<vT>(), boost::simd::Mone<vT>()), boost::simd::Sqrt_2<r_t>(), 0.5);
  NT2_TEST_ULP_EQUAL(hypot(boost::simd::Nan<vT>(), boost::simd::Nan<vT>()), boost::simd::Nan<r_t>(), 0);
  NT2_TEST_ULP_EQUAL(hypot(boost::simd::One<vT>(), boost::simd::One<vT>()), boost::simd::Sqrt_2<r_t>(), 0.5);
  NT2_TEST_ULP_EQUAL(hypot(boost::simd::Zero<vT>(), boost::simd::Zero<vT>()), boost::simd::Zero<r_t>(), 0);
} // end of test for floating_
