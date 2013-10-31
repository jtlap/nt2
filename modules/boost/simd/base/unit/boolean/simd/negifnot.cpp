//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <boost/simd/boolean/include/functions/negifnot.hpp>
#include <boost/simd/include/functions/is_nez.hpp>
#include <boost/simd/sdk/simd/native.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/dispatch/functor/meta/call.hpp>
#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <boost/simd/constant/constant.hpp>

NT2_TEST_CASE_TPL ( negifnot_real__2_0,  BOOST_SIMD_SIMD_REAL_TYPES)
{
  using boost::simd::negifnot;
  using boost::simd::tag::negifnot_;
  using boost::simd::native;
  using boost::simd::meta::cardinal_of;
  using boost::simd::logical;
  typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef native<T,ext_t>                        n_t;
  typedef n_t                                     vT;
  typedef native< logical<T>, ext_t>             vlT;
  typedef typename boost::dispatch::meta::call<negifnot_(vlT,vT)>::type r_t;
  typedef typename boost::simd::meta::scalar_of<r_t>::type sr_t;
  typedef typename boost::simd::meta::scalar_of<r_t>::type ssr_t;

  // specific values tests
   NT2_TEST_EQUAL(negifnot(boost::simd::False<vlT>(),boost::simd::splat<vT>(1))[0], -1);
   NT2_TEST_EQUAL(negifnot(boost::simd::True<vlT>(),boost::simd::splat<vT>(1))[0], 1);
   NT2_TEST_EQUAL(negifnot((boost::simd::splat<vlT>(T(1))),boost::simd::splat<vT>(1))[0], 1);
} // end of test for floating_

NT2_TEST_CASE_TPL ( negifnot_signed_int__2_0,  BOOST_SIMD_SIMD_INTEGRAL_SIGNED_TYPES)
{
  using boost::simd::negifnot;
  using boost::simd::tag::negifnot_;
  using boost::simd::native;
  using boost::simd::meta::cardinal_of;
  using boost::simd::logical;
  typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef native<T,ext_t>                        n_t;
  typedef n_t                                     vT;
  typedef native< logical<T>, ext_t>             vlT;
  typedef typename boost::dispatch::meta::call<negifnot_(vlT,vT)>::type r_t;
  typedef typename boost::simd::meta::scalar_of<r_t>::type sr_t;
  typedef typename boost::simd::meta::scalar_of<r_t>::type ssr_t;

  // specific values tests
  NT2_TEST_EQUAL(negifnot(boost::simd::False<vlT>(),boost::simd::splat<vT>(1))[0], -1);
  NT2_TEST_EQUAL(negifnot(boost::simd::True<vlT>(),boost::simd::splat<vT>(1))[0], 1);
  NT2_TEST_EQUAL(negifnot((boost::simd::splat<vlT>(1)),boost::simd::splat<vT>(1))[0], 1);
} // end of test for signed_int_
