//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <boost/simd/ieee/include/functions/negate.hpp>
#include <boost/simd/sdk/simd/native.hpp>
#include <boost/simd/include/functions/sign.hpp>
#include <boost/simd/sdk/simd/io.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/dispatch/functor/meta/call.hpp>
#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <boost/simd/constant/constant.hpp>

NT2_TEST_CASE_TPL ( negate_real__2_0,  BOOST_SIMD_SIMD_REAL_TYPES)
{
  using boost::simd::negate;
  using boost::simd::tag::negate_;
  using boost::simd::native;
  typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef native<T,ext_t>                  vT;
  typedef typename boost::dispatch::meta::call<negate_(vT,vT)>::type r_t;

  // specific values tests
  NT2_TEST_EQUAL(negate(boost::simd::Inf<vT>(), boost::simd::Inf<vT>()), boost::simd::Inf<r_t>());
  NT2_TEST_EQUAL(negate(boost::simd::Minf<vT>(), boost::simd::Minf<vT>()), boost::simd::Inf<r_t>());
  NT2_TEST_EQUAL(negate(boost::simd::Mone<vT>(), boost::simd::Mone<vT>()), boost::simd::One<r_t>());
  NT2_TEST_EQUAL(negate(boost::simd::Nan<vT>(), boost::simd::Nan<vT>()), boost::simd::Nan<r_t>());
  NT2_TEST_EQUAL(negate(boost::simd::One<vT>(), boost::simd::One<vT>()), boost::simd::One<r_t>());
  NT2_TEST_EQUAL(negate(boost::simd::Zero<vT>(), boost::simd::Zero<vT>()), boost::simd::Zero<r_t>());
  NT2_TEST_EQUAL(negate(boost::simd::Nan<vT>(), boost::simd::Zero<vT>()), boost::simd::Nan<r_t>());
  NT2_TEST_EQUAL(negate(boost::simd::Zero<vT>(), boost::simd::Nan<vT>()), boost::simd::Nan<r_t>());
  NT2_TEST_EQUAL(negate(boost::simd::Nan<vT>(), boost::simd::Zero<vT>()), boost::simd::Nan<r_t>());
  NT2_TEST_EQUAL(negate(boost::simd::One<vT>(), boost::simd::Nan<vT>()), boost::simd::Nan<r_t>());
  NT2_TEST_EQUAL(negate(boost::simd::Nan<vT>(), boost::simd::One<vT>()), boost::simd::Nan<r_t>());
} // end of test for floating_
