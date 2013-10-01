//==============================================================================
//         Copyright 2003 - 2013   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <boost/simd/operator/include/functions/bitwise_or.hpp>

#include <boost/dispatch/functor/meta/call.hpp>
#include <boost/simd/sdk/simd/native.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <boost/simd/sdk/config.hpp>
#include <boost/simd/sdk/simd/io.hpp>

#include <boost/simd/include/constants/mone.hpp>
#include <boost/simd/include/constants/one.hpp>
#include <boost/simd/include/constants/zero.hpp>
#include <boost/simd/include/constants/two.hpp>
#include <boost/simd/include/constants/three.hpp>
#include <boost/simd/include/constants/inf.hpp>
#include <boost/simd/include/constants/minf.hpp>
#include <boost/simd/include/constants/nan.hpp>
#include <boost/simd/include/constants/valmax.hpp>
#include <boost/simd/include/constants/valmin.hpp>

NT2_TEST_CASE_TPL(bitwise_or_real, BOOST_SIMD_SIMD_REAL_TYPES)
{
  using boost::simd::bitwise_or;
  using boost::simd::tag::bitwise_or_;
  using boost::simd::native;
  typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef native<T,ext_t>                  vT;
  typedef typename boost::dispatch::meta::call<bitwise_or_(vT,vT)>::type r_t;

  // specific values tests
#ifndef BOOST_SIMD_NO_INVALIDS
  NT2_TEST_EQUAL(bitwise_or(boost::simd::Inf<vT>(), boost::simd::Inf<vT>()), boost::simd::Inf<r_t>());
  NT2_TEST_EQUAL(bitwise_or(boost::simd::Minf<vT>(), boost::simd::Minf<vT>()), boost::simd::Minf<r_t>());
  NT2_TEST_EQUAL(bitwise_or(boost::simd::Nan<vT>(), boost::simd::Nan<vT>()), boost::simd::Nan<r_t>());
#endif
  NT2_TEST_EQUAL(bitwise_or(boost::simd::Zero<vT>(), boost::simd::Zero<vT>()), boost::simd::Zero<r_t>());
}


NT2_TEST_CASE_TPL(bitwise_or_ui, BOOST_SIMD_SIMD_UNSIGNED_TYPES)
{
  using boost::simd::bitwise_or;
  using boost::simd::tag::bitwise_or_;
  using boost::simd::native;
  typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef native<T,ext_t>                  vT;
  typedef typename boost::dispatch::meta::call<bitwise_or_(vT,vT)>::type r_t;

  // specific values tests
  NT2_TEST_EQUAL(bitwise_or(boost::simd::Zero<vT>(), boost::simd::Zero<vT>()), boost::simd::Zero<r_t>());
}

NT2_TEST_CASE_TPL(bitwise_or_si, BOOST_SIMD_SIMD_INTEGRAL_SIGNED_TYPES)
{
  using boost::simd::bitwise_or;
  using boost::simd::tag::bitwise_or_;
  using boost::simd::native;
  typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef native<T,ext_t>                  vT;
  typedef typename boost::dispatch::meta::call<bitwise_or_(vT,vT)>::type r_t;

  // specific values tests
  NT2_TEST_EQUAL(bitwise_or(boost::simd::Zero<vT>(), boost::simd::Zero<vT>()), boost::simd::Zero<r_t>());
  NT2_TEST_EQUAL(bitwise_or(boost::simd::One <vT>(), boost::simd::Two <vT>()), boost::simd::Three<r_t>());
}


NT2_TEST_CASE_TPL(bitwise_or_mix, BOOST_SIMD_SIMD_REAL_TYPES)
{
  using boost::simd::bitwise_or;
  using boost::simd::tag::bitwise_or_;
  using boost::simd::native;
  typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef native<T, ext_t>                  vT;
  typedef typename  boost::dispatch::meta::as_integer<vT>::type sivT;
  typedef typename  boost::dispatch::meta::as_integer<vT, unsigned>::type uivT;

  // return type conformity test
  NT2_TEST_TYPE_IS(typename boost::dispatch::meta::call<bitwise_or_(vT,uivT)>::type, vT);
  NT2_TEST_TYPE_IS(typename boost::dispatch::meta::call<bitwise_or_(vT,sivT)>::type, vT);
  NT2_TEST_TYPE_IS(typename boost::dispatch::meta::call<bitwise_or_(uivT, vT)>::type, uivT);
  NT2_TEST_TYPE_IS(typename boost::dispatch::meta::call<bitwise_or_(sivT, vT)>::type, sivT);

  // specific values tests
  NT2_TEST_EQUAL(bitwise_or(boost::simd::Zero<vT>(),boost::simd::Zero<uivT>()), boost::simd::Zero<vT>());
  NT2_TEST_EQUAL(bitwise_or(boost::simd::Zero<vT>(), boost::simd::Zero<sivT>()), boost::simd::Zero<vT>());
  NT2_TEST_EQUAL(bitwise_or(boost::simd::Valmin<sivT>(),boost::simd::Nan<vT>()), boost::simd::Mone<sivT>());
  NT2_TEST_EQUAL(bitwise_or(boost::simd::Zero<uivT>(), boost::simd::Nan<vT>()), boost::simd::Valmax<uivT>());
}
