//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <boost/simd/operator/include/functions/bitwise_and.hpp>

#include <boost/dispatch/functor/meta/call.hpp>
#include <boost/simd/sdk/simd/native.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <boost/simd/sdk/config.hpp>
#include <boost/simd/sdk/simd/io.hpp>

#include <boost/simd/include/constants/one.hpp>
#include <boost/simd/include/constants/mone.hpp>
#include <boost/simd/include/constants/three.hpp>
#include <boost/simd/include/constants/zero.hpp>
#include <boost/simd/include/constants/inf.hpp>
#include <boost/simd/include/constants/minf.hpp>
#include <boost/simd/include/constants/nan.hpp>
#include <boost/simd/include/constants/valmax.hpp>

NT2_TEST_CASE_TPL(bitwise_and_real, BOOST_SIMD_SIMD_REAL_TYPES)
{
  using boost::simd::bitwise_and;
  using boost::simd::tag::bitwise_and_;
  using boost::simd::native;
  typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef native<T,ext_t>                  vT;
  typedef typename boost::dispatch::meta::call<bitwise_and_(vT,vT)>::type r_t;

  // specific values tests
#ifndef BOOST_SIMD_NO_INVALIDS
  NT2_TEST_EQUAL(bitwise_and(boost::simd::Inf<vT>(), boost::simd::Inf<vT>()), boost::simd::Inf<r_t>());
  NT2_TEST_EQUAL(bitwise_and(boost::simd::Minf<vT>(), boost::simd::Minf<vT>()), boost::simd::Minf<r_t>());
  NT2_TEST_EQUAL(bitwise_and(boost::simd::Nan<vT>(), boost::simd::Nan<vT>()), boost::simd::Nan<r_t>());
#endif
  NT2_TEST_EQUAL(bitwise_and(boost::simd::One<vT>(),boost::simd::Zero<vT>()), boost::simd::Zero<r_t>());
  NT2_TEST_EQUAL(bitwise_and(boost::simd::Zero<vT>(), boost::simd::Zero<vT>()), boost::simd::Zero<r_t>());
}


NT2_TEST_CASE_TPL(bitwise_and_ui, BOOST_SIMD_SIMD_UNSIGNED_TYPES)
{
  using boost::simd::bitwise_and;
  using boost::simd::tag::bitwise_and_;
  using boost::simd::native;
  typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef native<T,ext_t>                  vT;
  typedef typename boost::dispatch::meta::call<bitwise_and_(vT,vT)>::type r_t;

  // specific values tests
  NT2_TEST_EQUAL(bitwise_and(boost::simd::One<vT>(),boost::simd::Three<vT>()), boost::simd::One<r_t>());
  NT2_TEST_EQUAL(bitwise_and(boost::simd::Zero<vT>(), boost::simd::Zero<vT>()), boost::simd::Zero<r_t>());
}

NT2_TEST_CASE_TPL(bitwise_and_si, BOOST_SIMD_SIMD_INTEGRAL_SIGNED_TYPES)
{
  using boost::simd::bitwise_and;
  using boost::simd::tag::bitwise_and_;
  using boost::simd::native;
  typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef native<T,ext_t>                  vT;
  typedef typename boost::dispatch::meta::call<bitwise_and_(vT,vT)>::type r_t;

  // specific values tests
  NT2_TEST_EQUAL(bitwise_and(boost::simd::One<vT>(),boost::simd::One<vT>()), boost::simd::One<r_t>());
  NT2_TEST_EQUAL(bitwise_and(boost::simd::Zero<vT>(), boost::simd::Zero<vT>()), boost::simd::Zero<r_t>());
}

NT2_TEST_CASE_TPL(bitwise_and_mix, BOOST_SIMD_SIMD_REAL_TYPES)
{
  using boost::simd::bitwise_and;
  using boost::simd::tag::bitwise_and_;
  using boost::simd::native;
  typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef native<T, ext_t>                  vT;
  typedef typename  boost::dispatch::meta::as_integer<vT>::type sivT;
  typedef typename  boost::dispatch::meta::as_integer<vT, unsigned>::type uivT;

  // return type conformity test
  NT2_TEST_TYPE_IS(typename boost::dispatch::meta::call<bitwise_and_(vT,uivT)>::type, vT);
  NT2_TEST_TYPE_IS(typename boost::dispatch::meta::call<bitwise_and_(vT,sivT)>::type, vT);
  NT2_TEST_TYPE_IS(typename boost::dispatch::meta::call<bitwise_and_(uivT, vT)>::type, uivT);
  NT2_TEST_TYPE_IS(typename boost::dispatch::meta::call<bitwise_and_(sivT, vT)>::type, sivT);

  // specific values tests
  NT2_TEST_EQUAL(bitwise_and(boost::simd::Nan<vT>(),boost::simd::Valmax<uivT>()), boost::simd::Nan<vT>());
  NT2_TEST_EQUAL(bitwise_and(boost::simd::Nan<vT>(), boost::simd::Mone<sivT>()), boost::simd::Nan<vT>());
  NT2_TEST_EQUAL(bitwise_and(boost::simd::Mone<sivT>(),boost::simd::Zero<vT>()), boost::simd::Zero<sivT>());
  NT2_TEST_EQUAL(bitwise_and(boost::simd::Valmax<uivT>(), boost::simd::Zero<vT>()), boost::simd::Zero<uivT>());
}
