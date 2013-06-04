//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#define NT2_UNIT_MODULE "nt2 boost.simd.arithmetic toolbox - toints/simd Mode"

//////////////////////////////////////////////////////////////////////////////
// unit test behavior of boost.simd.arithmetic components in simd mode
//////////////////////////////////////////////////////////////////////////////

#include <boost/simd/arithmetic/include/functions/toints.hpp>
#include <boost/simd/sdk/simd/native.hpp>
#include <boost/dispatch/functor/meta/call.hpp>
#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <boost/simd/include/functions/splat.hpp>
#include <boost/simd/include/constants/inf.hpp>
#include <boost/simd/include/constants/minf.hpp>
#include <boost/simd/include/constants/nan.hpp>
#include <boost/simd/include/constants/zero.hpp>
#include <boost/simd/include/constants/one.hpp>
#include <boost/simd/include/constants/mone.hpp>
#include <boost/simd/sdk/simd/io.hpp>
#include <boost/simd/include/functions/simd/make.hpp>



NT2_TEST_CASE_TPL ( toints_real,  BOOST_SIMD_SIMD_REAL_TYPES)
{
  using boost::simd::toints;
  using boost::simd::tag::toints_;
  using boost::simd::native;
  typedef BOOST_SIMD_DEFAULT_EXTENSION                                ext_t;
  typedef native<T,ext_t>                                                vT;
  typedef typename boost::dispatch::meta::as_integer<vT>::type   wished_r_t;
  typedef typename boost::dispatch::meta::call<toints_(vT)>::type       r_t;

  // return type conformity test
  NT2_TEST_TYPE_IS(r_t, wished_r_t);

  // specific values tests
  NT2_TEST_EQUAL(toints(boost::simd::Inf<vT>()),  boost::simd::Inf<r_t>());
  NT2_TEST_EQUAL(toints(boost::simd::splat<vT>(T(1)/T(0))),  boost::simd::Inf<r_t>());
  NT2_TEST_EQUAL(toints(boost::simd::Minf<vT>()), boost::simd::Minf<r_t>());
  NT2_TEST_EQUAL(toints(boost::simd::splat<vT>(T(-1)/T(0))),  boost::simd::Minf<r_t>());
  NT2_TEST_EQUAL(toints(boost::simd::Mone<vT>()), boost::simd::Mone<r_t>());
  NT2_TEST_EQUAL(toints(boost::simd::splat<vT>(T(0)/T(0))),  boost::simd::Zero<r_t>());
  NT2_TEST_EQUAL(toints(boost::simd::Nan<vT>()),  boost::simd::Zero<r_t>());
  NT2_TEST_EQUAL(toints(boost::simd::One<vT>()),  boost::simd::One<r_t>());
  NT2_TEST_EQUAL(toints(boost::simd::Zero<vT>()), boost::simd::Zero<r_t>());
} // end of test for floating_

NT2_TEST_CASE_TPL ( toints_realf,  (float))
{
  using boost::simd::toints;
  using boost::simd::tag::toints_;
  using boost::simd::native;
  typedef BOOST_SIMD_DEFAULT_EXTENSION                                ext_t;
  typedef native<T,ext_t>                                                vT;
  typedef typename boost::dispatch::meta::call<toints_(vT)>::type       r_t;
  typedef typename boost::dispatch::meta::call<toints_(T)>::type         iT;

  vT  a =  boost::simd::make<vT> (boost::simd::One<float>(), boost::simd::Inf<float>(), boost::simd::Minf<float>(), boost::simd::Nan<float>());
  r_t b =  boost::simd::make<r_t>(boost::simd::One<iT>()   , boost::simd::Inf<iT>(),    boost::simd::Minf<iT>(),    boost::simd::Nan<iT>()   );
  NT2_TEST_EQUAL(toints(a), b);
}
NT2_TEST_CASE_TPL ( toints_reald,  (double))
{
  using boost::simd::toints;
  using boost::simd::tag::toints_;
  using boost::simd::native;
  typedef BOOST_SIMD_DEFAULT_EXTENSION                                ext_t;
  typedef native<T,ext_t>                                                vT;
  typedef typename boost::dispatch::meta::call<toints_(vT)>::type       r_t;
  typedef typename boost::dispatch::meta::call<toints_(T)>::type         iT;

  vT  a1 =  boost::simd::make<vT> (boost::simd::One<float>(), boost::simd::Inf<float>());
  vT  a2 =  boost::simd::make<vT> (boost::simd::Minf<float>(), boost::simd::Nan<float>());
  r_t b1 =  boost::simd::make<r_t>(boost::simd::One<iT>()   , boost::simd::Inf<iT>());
  r_t b2 =  boost::simd::make<r_t>(boost::simd::Minf<iT>(), boost::simd::Nan<iT>());
  NT2_TEST_EQUAL(toints(a1), b1);
  NT2_TEST_EQUAL(toints(a2), b2);
}



NT2_TEST_CASE_TPL ( toints_unsigned_int,  BOOST_SIMD_UNSIGNED_TYPES)
{

  using boost::simd::toints;
  using boost::simd::tag::toints_;
  using boost::simd::native;
  typedef BOOST_SIMD_DEFAULT_EXTENSION                                ext_t;
  typedef native<T,ext_t>                                                vT;
  typedef typename boost::dispatch::meta::as_integer<vT>::type   wished_r_t;
  typedef typename boost::dispatch::meta::call<toints_(vT)>::type       r_t;

  // return type conformity test
  NT2_TEST_TYPE_IS(r_t, wished_r_t);

  // specific values tests
  NT2_TEST_EQUAL(toints(boost::simd::One<vT>()),  boost::simd::One<r_t>());
  NT2_TEST_EQUAL(toints(boost::simd::Zero<vT>()), boost::simd::Zero<r_t>());
} // end of test for unsigned_int_

NT2_TEST_CASE_TPL ( toints_signed,  BOOST_SIMD_INTEGRAL_SIGNED_TYPES)
{

  using boost::simd::toints;
  using boost::simd::tag::toints_;
  using boost::simd::native;
  typedef BOOST_SIMD_DEFAULT_EXTENSION                                ext_t;
  typedef native<T,ext_t>                                                vT;
  typedef typename boost::dispatch::meta::as_integer<vT>::type   wished_r_t;
  typedef typename boost::dispatch::meta::call<toints_(vT)>::type       r_t;

  // return type conformity test
  NT2_TEST_TYPE_IS(r_t, wished_r_t);

  // specific values tests
  NT2_TEST_EQUAL(toints(boost::simd::Mone<vT>()), boost::simd::Mone<r_t>());
  NT2_TEST_EQUAL(toints(boost::simd::One<vT>()),  boost::simd::One<r_t>());
  NT2_TEST_EQUAL(toints(boost::simd::Zero<vT>()), boost::simd::Zero<r_t>());
} // end of test for signed_int_
