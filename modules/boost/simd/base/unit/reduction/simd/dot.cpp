//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <boost/simd/reduction/include/functions/dot.hpp>
#include <boost/simd/sdk/simd/native.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/dispatch/functor/meta/call.hpp>
#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <boost/simd/constant/constant.hpp>

NT2_TEST_CASE_TPL ( dot_real__2_0,  BOOST_SIMD_SIMD_REAL_TYPES)
{
  using boost::simd::dot;
  using boost::simd::tag::dot_;
  using boost::simd::native;
  using boost::simd::meta::cardinal_of;
  typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef native<T,ext_t>                        n_t;
  typedef n_t                                     vT;
  typedef typename boost::dispatch::meta::call<dot_(vT,vT)>::type r_t;
  typedef typename boost::simd::meta::scalar_of<r_t>::type sr_t;

  // specific values tests
  NT2_TEST_EQUAL(dot(boost::simd::Inf<vT>(), boost::simd::Inf<vT>()), boost::simd::Inf<sr_t>());
  NT2_TEST_EQUAL(dot(boost::simd::Minf<vT>(), boost::simd::Minf<vT>()), boost::simd::Inf<sr_t>());
  NT2_TEST_EQUAL(dot(boost::simd::Mone<vT>(), boost::simd::Mone<vT>()), boost::simd::meta::cardinal_of<vT>::value);
  NT2_TEST_EQUAL(dot(boost::simd::Nan<vT>(), boost::simd::Nan<vT>()), boost::simd::Nan<sr_t>());
  NT2_TEST_EQUAL(dot(boost::simd::One<vT>(), boost::simd::One<vT>()), boost::simd::meta::cardinal_of<vT>::value);
  NT2_TEST_EQUAL(dot(boost::simd::Zero<vT>(), boost::simd::Zero<vT>()), boost::simd::Zero<sr_t>());
} // end of test for floating_
