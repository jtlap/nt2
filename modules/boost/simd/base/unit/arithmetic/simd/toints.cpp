//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================

#include <boost/simd/arithmetic/include/functions/toints.hpp>
#include <boost/simd/sdk/simd/native.hpp>
#include <boost/dispatch/functor/meta/call.hpp>
#include <boost/simd/include/functions/splat.hpp>
#include <boost/simd/include/functions/multiplies.hpp>
#include <boost/simd/include/functions/load.hpp>
#include <boost/simd/include/functions/ldexp.hpp>
#include <boost/simd/include/constants/inf.hpp>
#include <boost/simd/include/constants/minf.hpp>
#include <boost/simd/include/constants/nan.hpp>
#include <boost/simd/include/constants/zero.hpp>
#include <boost/simd/include/constants/one.hpp>
#include <boost/simd/include/constants/two.hpp>
#include <boost/simd/include/constants/mone.hpp>
#include <boost/simd/sdk/simd/io.hpp>
#include <algorithm>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>

NT2_TEST_CASE_TPL ( toints_real,  BOOST_SIMD_SIMD_REAL_TYPES)
{
  using boost::simd::toints;
  using boost::simd::tag::toints_;
  using boost::simd::native;
  typedef BOOST_SIMD_DEFAULT_EXTENSION                                ext_t;
  typedef native<T,ext_t>                                                vT;
  typedef typename boost::dispatch::meta::as_integer<vT, signed>::type   wished_r_t;
  typedef typename boost::dispatch::meta::call<toints_(vT)>::type       r_t;
  typedef typename boost::dispatch::meta::call<toints_(T)>::type       sr_t;

  // return type conformity test
  NT2_TEST_TYPE_IS(r_t, wished_r_t);

  // specific values tests
  NT2_TEST_EQUAL(toints(boost::simd::splat<vT>(T(1.5)*boost::simd::Valmax<sr_t>())),  boost::simd::Valmax<r_t>());
  NT2_TEST_EQUAL(toints(boost::simd::splat<vT>(T(1.5)*boost::simd::Valmin<sr_t>())),  boost::simd::Valmin<r_t>());
  NT2_TEST_EQUAL(toints(boost::simd::splat<vT>(T(2)*boost::simd::Valmax<sr_t>())),  boost::simd::Valmax<r_t>());
  NT2_TEST_EQUAL(toints(boost::simd::splat<vT>(T(2)*boost::simd::Valmin<sr_t>())),  boost::simd::Valmin<r_t>());
  NT2_TEST_EQUAL(toints(boost::simd::Inf<vT>()),  boost::simd::Inf<r_t>());
  NT2_TEST_EQUAL(toints(boost::simd::Minf<vT>()), boost::simd::Minf<r_t>());
  NT2_TEST_EQUAL(toints(boost::simd::Mone<vT>()), boost::simd::Mone<r_t>());
  NT2_TEST_EQUAL(toints(boost::simd::Nan<vT>()),  boost::simd::Zero<r_t>());
  NT2_TEST_EQUAL(toints(boost::simd::One<vT>()),  boost::simd::One<r_t>());
  NT2_TEST_EQUAL(toints(boost::simd::Zero<vT>()), boost::simd::Zero<r_t>());

  vT v = boost::simd::One<vT>();
  r_t iv = boost::simd::One<r_t>();
  int N = sizeof(T)*8-2;
  for(int i=0; i < N ; i++)
  {
    NT2_TEST_EQUAL(toints(v), iv);
    NT2_TEST_EQUAL(toints(-v), -iv);
    v *= boost::simd::Two<vT>();
    iv *= boost::simd::Two<r_t>();
  }
  NT2_TEST_EQUAL(toints(boost::simd::ldexp(boost::simd::One<vT>(), N+1)), boost::simd::Valmax<r_t>());
  NT2_TEST_EQUAL(toints(boost::simd::ldexp(boost::simd::One<vT>(), N+2)), boost::simd::Valmax<r_t>());
  NT2_TEST_EQUAL(toints(-boost::simd::ldexp(boost::simd::One<vT>(), N+1)), boost::simd::Valmin<r_t>());
  NT2_TEST_EQUAL(toints(-boost::simd::ldexp(boost::simd::One<vT>(), N+2)), boost::simd::Valmin<r_t>());
}

NT2_TEST_CASE_TPL ( toints_real2,   BOOST_SIMD_SIMD_REAL_TYPES)
{
  using boost::simd::toints;
  using boost::simd::tag::toints_;
  using boost::simd::native;
  typedef BOOST_SIMD_DEFAULT_EXTENSION                                ext_t;
  typedef native<T,ext_t>                                                vT;
  typedef typename boost::dispatch::meta::call<toints_(T)>::type        iT;
  typedef native<iT,ext_t>                                              ivT;

  static const std::size_t NR = boost::simd::meta::cardinal_of<vT>::value > std::size_t(8) ? boost::simd::meta::cardinal_of<vT>::value : std::size_t(8);

  T data[NR] = { boost::simd::One<T>(), boost::simd::Inf<T>(), boost::simd::Minf<T>(), boost::simd::Nan<T>(),boost::simd::One<T>(), boost::simd::Inf<T>(), boost::simd::Minf<T>(), boost::simd::Nan<T>() };
  iT idat[NR] = { boost::simd::One<iT>(), boost::simd::Inf<iT>(), boost::simd::Minf<iT>(), boost::simd::Nan<iT>(), boost::simd::One<iT>(), boost::simd::Inf<iT>(), boost::simd::Minf<iT>(), boost::simd::Nan<iT>() };

  for(std::size_t j = 0; j < NR; j+=boost::simd::meta::cardinal_of<vT>::value)
  {
    vT   a =  boost::simd::load<vT>(&data[0],j);
    ivT ia =  boost::simd::load<ivT>(&idat[0],j);
    NT2_TEST_EQUAL(toints(a), ia);
  }
}

NT2_TEST_CASE_TPL ( toints_unsigned_int,  BOOST_SIMD_SIMD_UNSIGNED_TYPES)
{

  using boost::simd::toints;
  using boost::simd::tag::toints_;
  using boost::simd::native;
  typedef BOOST_SIMD_DEFAULT_EXTENSION                                ext_t;
  typedef native<T,ext_t>                                                vT;
  typedef typename boost::dispatch::meta::as_integer<vT, signed>::type   wished_r_t;
  typedef typename boost::dispatch::meta::call<toints_(vT)>::type       r_t;

  // return type conformity test
  NT2_TEST_TYPE_IS(r_t, wished_r_t);

  // specific values tests
  NT2_TEST_EQUAL(toints(boost::simd::One<vT>()),  boost::simd::One<r_t>());
  NT2_TEST_EQUAL(toints(boost::simd::Zero<vT>()), boost::simd::Zero<r_t>());
} // end of test for unsigned_int_

NT2_TEST_CASE_TPL ( toints_signed,  BOOST_SIMD_SIMD_INTEGRAL_SIGNED_TYPES)
{

  using boost::simd::toints;
  using boost::simd::tag::toints_;
  using boost::simd::native;
  typedef BOOST_SIMD_DEFAULT_EXTENSION                                ext_t;
  typedef native<T,ext_t>                                                vT;
  typedef typename boost::dispatch::meta::as_integer<vT, signed>::type   wished_r_t;
  typedef typename boost::dispatch::meta::call<toints_(vT)>::type       r_t;

  // return type conformity test
  NT2_TEST_TYPE_IS(r_t, wished_r_t);

  // specific values tests
  NT2_TEST_EQUAL(toints(boost::simd::Mone<vT>()), boost::simd::Mone<r_t>());
  NT2_TEST_EQUAL(toints(boost::simd::One<vT>()),  boost::simd::One<r_t>());
  NT2_TEST_EQUAL(toints(boost::simd::Zero<vT>()), boost::simd::Zero<r_t>());
} // end of test for signed_int_
