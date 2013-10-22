//==============================================================================
//         Copyright 2003 - 2013   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <boost/simd/ieee/include/functions/ulp.hpp>
#include <boost/simd/sdk/simd/logical.hpp>

#include <boost/dispatch/functor/meta/call.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <boost/simd/sdk/config.hpp>

#include <boost/simd/include/constants/eps.hpp>
#include <boost/simd/include/constants/mindenormal.hpp>
#include <boost/simd/include/constants/mone.hpp>
#include <boost/simd/include/constants/one.hpp>
#include <boost/simd/include/constants/zero.hpp>
#include <boost/simd/include/constants/inf.hpp>
#include <boost/simd/include/constants/minf.hpp>
#include <boost/simd/include/constants/nan.hpp>

NT2_TEST_CASE_TPL ( ulp_real,  BOOST_SIMD_REAL_TYPES)
{
  using boost::simd::ulp;
  using boost::simd::tag::ulp_;
  typedef typename boost::dispatch::meta::call<ulp_(T)>::type r_t;
  typedef T wished_r_t;

  // return type conformity test
  NT2_TEST_TYPE_IS(r_t, wished_r_t);

  // specific values tests
#ifndef BOOST_SIMD_NO_INVALIDS
  NT2_TEST_EQUAL(ulp(boost::simd::Inf<T>()), boost::simd::Nan<r_t>());
  NT2_TEST_EQUAL(ulp(boost::simd::Minf<T>()), boost::simd::Nan<r_t>());
  NT2_TEST_EQUAL(ulp(boost::simd::Nan<T>()), boost::simd::Nan<r_t>());
#endif
  NT2_TEST_EQUAL(ulp(boost::simd::Mone<T>()), boost::simd::Eps<r_t>()/2);
  NT2_TEST_EQUAL(ulp(boost::simd::One<T>()), boost::simd::Eps<r_t>()/2);
  NT2_TEST_EQUAL(ulp(boost::simd::Zero<T>()), boost::simd::Mindenormal<r_t>());
}

NT2_TEST_CASE_TPL ( ulp_unsigned_int,  BOOST_SIMD_UNSIGNED_TYPES)
{
  using boost::simd::ulp;
  using boost::simd::tag::ulp_;
  typedef typename boost::dispatch::meta::call<ulp_(T)>::type r_t;
  typedef T wished_r_t;

  // return type conformity test
  NT2_TEST_TYPE_IS(r_t, wished_r_t);

  // specific values tests
  NT2_TEST_EQUAL(ulp(boost::simd::One<T>()), boost::simd::One<r_t>());
  NT2_TEST_EQUAL(ulp(boost::simd::Zero<T>()), boost::simd::One<r_t>());
}

NT2_TEST_CASE_TPL ( ulp_signed_int,  BOOST_SIMD_INTEGRAL_SIGNED_TYPES)
{
  using boost::simd::ulp;
  using boost::simd::tag::ulp_;
  typedef typename boost::dispatch::meta::call<ulp_(T)>::type r_t;
  typedef T wished_r_t;

  // return type conformity test
  NT2_TEST_TYPE_IS(r_t, wished_r_t);

  // specific values tests
  NT2_TEST_EQUAL(ulp(boost::simd::Mone<T>()), boost::simd::One<r_t>());
  NT2_TEST_EQUAL(ulp(boost::simd::One<T>()), boost::simd::One<r_t>());
  NT2_TEST_EQUAL(ulp(boost::simd::Zero<T>()), boost::simd::One<r_t>());
}
