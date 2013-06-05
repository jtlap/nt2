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

#include <nt2/arithmetic/include/functions/toints.hpp>
#include <boost/simd/sdk/simd/native.hpp>
#include <boost/dispatch/functor/meta/call.hpp>
#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/include/functions/splat.hpp>
#include <nt2/include/constants/inf.hpp>
#include <nt2/include/constants/minf.hpp>
#include <nt2/include/constants/nan.hpp>
#include <nt2/include/constants/zero.hpp>
#include <nt2/include/constants/one.hpp>
#include <nt2/include/constants/mone.hpp>
#include <boost/simd/sdk/simd/io.hpp>
#include <nt2/include/functions/simd/make.hpp>



NT2_TEST_CASE_TPL ( toints_real,  BOOST_SIMD_SIMD_REAL_TYPES)
{
  using nt2::toints;
  using nt2::tag::toints_;
  using boost::simd::native;
  typedef BOOST_SIMD_DEFAULT_EXTENSION                                ext_t;
  typedef native<T,ext_t>                                                vT;
  typedef typename boost::dispatch::meta::as_integer<vT>::type   wished_r_t;
  typedef typename boost::dispatch::meta::call<toints_(vT)>::type       r_t;

  // return type conformity test
  NT2_TEST_TYPE_IS(r_t, wished_r_t);

  // specific values tests
  NT2_TEST_EQUAL(toints(nt2::Inf<vT>()),  nt2::Inf<r_t>());
  NT2_TEST_EQUAL(toints(nt2::splat<vT>(T(1)/T(0))),  nt2::Inf<r_t>());
  NT2_TEST_EQUAL(toints(nt2::Minf<vT>()), nt2::Minf<r_t>());
  NT2_TEST_EQUAL(toints(nt2::splat<vT>(T(-1)/T(0))),  nt2::Minf<r_t>());
  NT2_TEST_EQUAL(toints(nt2::Mone<vT>()), nt2::Mone<r_t>());
  NT2_TEST_EQUAL(toints(nt2::splat<vT>(T(0)/T(0))),  nt2::Zero<r_t>());
  NT2_TEST_EQUAL(toints(nt2::Nan<vT>()),  nt2::Zero<r_t>());
  NT2_TEST_EQUAL(toints(nt2::One<vT>()),  nt2::One<r_t>());
  NT2_TEST_EQUAL(toints(nt2::Zero<vT>()), nt2::Zero<r_t>());
} // end of test for floating_

NT2_TEST_CASE_TPL ( toints_realf,  (float))
{
  using nt2::toints;
  using nt2::tag::toints_;
  using boost::simd::native;
  typedef BOOST_SIMD_DEFAULT_EXTENSION                                ext_t;
  typedef native<T,ext_t>                                                vT;
  typedef typename boost::dispatch::meta::call<toints_(vT)>::type       r_t;
  typedef typename boost::dispatch::meta::call<toints_(T)>::type         iT;

  vT  a =  nt2::make<vT> (nt2::One<float>(), nt2::Inf<float>(), nt2::Minf<float>(), nt2::Nan<float>());
  r_t b =  nt2::make<r_t>(nt2::One<iT>()   , nt2::Inf<iT>(),    nt2::Minf<iT>(),    nt2::Nan<iT>()   );
  NT2_TEST_EQUAL(toints(a), b);
}
NT2_TEST_CASE_TPL ( toints_reald,  (double))
{
  using nt2::toints;
  using nt2::tag::toints_;
  using boost::simd::native;
  typedef BOOST_SIMD_DEFAULT_EXTENSION                                ext_t;
  typedef native<T,ext_t>                                                vT;
  typedef typename boost::dispatch::meta::call<toints_(vT)>::type       r_t;
  typedef typename boost::dispatch::meta::call<toints_(T)>::type         iT;

  vT  a1 =  nt2::make<vT> (nt2::One<float>(), nt2::Inf<float>());
  vT  a2 =  nt2::make<vT> (nt2::Minf<float>(), nt2::Nan<float>());
  r_t b1 =  nt2::make<r_t>(nt2::One<iT>()   , nt2::Inf<iT>());
  r_t b2 =  nt2::make<r_t>(nt2::Minf<iT>(), nt2::Nan<iT>());
  NT2_TEST_EQUAL(toints(a1), b1);
  NT2_TEST_EQUAL(toints(a2), b2);
}



NT2_TEST_CASE_TPL ( toints_unsigned_int,  BOOST_SIMD_UNSIGNED_TYPES)
{

  using nt2::toints;
  using nt2::tag::toints_;
  using boost::simd::native;
  typedef BOOST_SIMD_DEFAULT_EXTENSION                                ext_t;
  typedef native<T,ext_t>                                                vT;
  typedef typename boost::dispatch::meta::as_integer<vT>::type   wished_r_t;
  typedef typename boost::dispatch::meta::call<toints_(vT)>::type       r_t;

  // return type conformity test
  NT2_TEST_TYPE_IS(r_t, wished_r_t);

  // specific values tests
  NT2_TEST_EQUAL(toints(nt2::One<vT>()),  nt2::One<r_t>());
  NT2_TEST_EQUAL(toints(nt2::Zero<vT>()), nt2::Zero<r_t>());
} // end of test for unsigned_int_

NT2_TEST_CASE_TPL ( toints_signed,  BOOST_SIMD_INTEGRAL_SIGNED_TYPES)
{

  using nt2::toints;
  using nt2::tag::toints_;
  using boost::simd::native;
  typedef BOOST_SIMD_DEFAULT_EXTENSION                                ext_t;
  typedef native<T,ext_t>                                                vT;
  typedef typename boost::dispatch::meta::as_integer<vT>::type   wished_r_t;
  typedef typename boost::dispatch::meta::call<toints_(vT)>::type       r_t;

  // return type conformity test
  NT2_TEST_TYPE_IS(r_t, wished_r_t);

  // specific values tests
  NT2_TEST_EQUAL(toints(nt2::Mone<vT>()), nt2::Mone<r_t>());
  NT2_TEST_EQUAL(toints(nt2::One<vT>()),  nt2::One<r_t>());
  NT2_TEST_EQUAL(toints(nt2::Zero<vT>()), nt2::Zero<r_t>());
} // end of test for signed_int_
