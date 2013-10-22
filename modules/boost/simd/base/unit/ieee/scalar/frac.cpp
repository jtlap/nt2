//==============================================================================
//         Copyright 2003 - 2013   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <boost/simd/ieee/include/functions/frac.hpp>
#include <boost/simd/sdk/simd/logical.hpp>

#include <boost/dispatch/functor/meta/call.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <boost/simd/sdk/config.hpp>

#include <boost/simd/include/constants/mone.hpp>
#include <boost/simd/include/constants/one.hpp>
#include <boost/simd/include/constants/zero.hpp>
#include <boost/simd/include/constants/inf.hpp>
#include <boost/simd/include/constants/minf.hpp>
#include <boost/simd/include/constants/nan.hpp>
#include <boost/simd/include/constants/half.hpp>
#include <boost/simd/include/constants/mhalf.hpp>

NT2_TEST_CASE_TPL ( frac_real,  BOOST_SIMD_REAL_TYPES)
{
  using boost::simd::frac;
  using boost::simd::tag::frac_;
  typedef typename boost::dispatch::meta::call<frac_(T)>::type r_t;
  typedef T wished_r_t;

  // return type conformity test
  NT2_TEST_TYPE_IS(r_t, wished_r_t);

  // specific values tests
#ifndef BOOST_SIMD_NO_INVALIDS
  NT2_TEST_EQUAL(frac(boost::simd::Inf<T>()), boost::simd::Nan<r_t>());
  NT2_TEST_EQUAL(frac(boost::simd::Minf<T>()), boost::simd::Nan<r_t>());
  NT2_TEST_EQUAL(frac(boost::simd::Nan<T>()), boost::simd::Nan<r_t>());
#endif
  NT2_TEST_EQUAL(frac(boost::simd::Mone<T>()), boost::simd::Zero<r_t>());
  NT2_TEST_EQUAL(frac(boost::simd::One<T>()), boost::simd::Zero<r_t>());
  NT2_TEST_EQUAL(frac(boost::simd::Zero<T>()), boost::simd::Zero<r_t>());
  NT2_TEST_EQUAL(frac(T(1.5)),  boost::simd::Half<r_t>());
  NT2_TEST_EQUAL(frac(T(-1.5)),  boost::simd::Mhalf<r_t>());
}

NT2_TEST_CASE_TPL ( frac_unsigned_int,  BOOST_SIMD_UNSIGNED_TYPES)
{
  using boost::simd::frac;
  using boost::simd::tag::frac_;
  typedef typename boost::dispatch::meta::call<frac_(T)>::type r_t;
  typedef T wished_r_t;

  // return type conformity test
  NT2_TEST_TYPE_IS(r_t, wished_r_t);

  // specific values tests
  NT2_TEST_EQUAL(frac(boost::simd::One<T>()), boost::simd::Zero<r_t>());
  NT2_TEST_EQUAL(frac(boost::simd::Zero<T>()), boost::simd::Zero<r_t>());
}

NT2_TEST_CASE_TPL ( frac_signed_int,  BOOST_SIMD_INTEGRAL_SIGNED_TYPES)
{
  using boost::simd::frac;
  using boost::simd::tag::frac_;
  typedef typename boost::dispatch::meta::call<frac_(T)>::type r_t;
  typedef T wished_r_t;

  // return type conformity test
  NT2_TEST_TYPE_IS(r_t, wished_r_t);

  // specific values tests
  NT2_TEST_EQUAL(frac(boost::simd::Mone<T>()), boost::simd::Zero<r_t>());
  NT2_TEST_EQUAL(frac(boost::simd::One<T>()), boost::simd::Zero<r_t>());
  NT2_TEST_EQUAL(frac(boost::simd::Zero<T>()), boost::simd::Zero<r_t>());
}
