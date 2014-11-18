//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#define NT2_UNIT_MODULE "nt2 boost.simd.arithmetic toolbox - touints/simd Mode"

//////////////////////////////////////////////////////////////////////////////
// unit test behavior of boost.simd.arithmetic components in simd mode
//////////////////////////////////////////////////////////////////////////////

#include <nt2/arithmetic/include/functions/touints.hpp>
#include <boost/simd/sdk/simd/native.hpp>
#include <boost/dispatch/functor/meta/call.hpp>
#include <nt2/sdk/meta/cardinal_of.hpp>
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
#include <nt2/include/functions/load.hpp>


NT2_TEST_CASE_TPL ( touints_real,  BOOST_SIMD_SIMD_REAL_TYPES)
{
  using nt2::touints;
  using nt2::tag::touints_;
  using boost::simd::native;
  typedef BOOST_SIMD_DEFAULT_EXTENSION                                ext_t;
  typedef native<T,ext_t>                                                vT;
  typedef typename boost::dispatch::meta::as_integer<vT, unsigned>::type   wished_r_t;
  typedef typename boost::dispatch::meta::call<touints_(vT)>::type       r_t;

  // return type conformity test
  NT2_TEST_TYPE_IS(r_t, wished_r_t);

  // specific values tests
  NT2_TEST_EQUAL(touints(nt2::Inf<vT>()),  nt2::Inf<r_t>());
  NT2_TEST_EQUAL(touints(nt2::Minf<vT>()), nt2::Minf<r_t>());
  NT2_TEST_EQUAL(touints(nt2::Mone<vT>()), nt2::Zero<r_t>());
  NT2_TEST_EQUAL(touints(nt2::Nan<vT>()),  nt2::Zero<r_t>());
  NT2_TEST_EQUAL(touints(nt2::One<vT>()),  nt2::One<r_t>());
  NT2_TEST_EQUAL(touints(nt2::Zero<vT>()), nt2::Zero<r_t>());
} // end of test for floating_

NT2_TEST_CASE_TPL ( touints_real2,   BOOST_SIMD_SIMD_REAL_TYPES)
{
  using nt2::touints;
  using nt2::tag::touints_;
  using boost::simd::native;
  typedef BOOST_SIMD_DEFAULT_EXTENSION                                ext_t;
  typedef native<T,ext_t>                                                vT;
  typedef typename boost::dispatch::meta::call<touints_(T)>::type        iT;
  typedef native<iT,ext_t>                                              ivT;

  T data[] = {nt2::One<T>(), nt2::Inf<T>(), nt2::Minf<T>(), nt2::Nan<T>(),nt2::One<T>(), nt2::Inf<T>(), nt2::Minf<T>(), nt2::Nan<T>(), };
  iT idat[] = {nt2::One<iT>(), nt2::Inf<iT>(), nt2::Minf<iT>(), nt2::Nan<iT>(), nt2::One<iT>(), nt2::Inf<iT>(), nt2::Minf<iT>(), nt2::Nan<iT>()};
  nt2::uint32_t NR =  (sizeof(data)/sizeof(T));
  for(nt2::uint32_t j = 0; j < NR;j+=nt2::meta::cardinal_of<vT>::value)
  {
    vT   a =  nt2::load<vT>(&data[0],j);
    ivT ia =  nt2::load<ivT>(&idat[0],j);
    NT2_TEST_EQUAL(touints(a), ia);
  }
}

NT2_TEST_CASE_TPL ( touints_unsigned_int,  BOOST_SIMD_SIMD_UNSIGNED_TYPES)
{

  using nt2::touints;
  using nt2::tag::touints_;
  using boost::simd::native;
  typedef BOOST_SIMD_DEFAULT_EXTENSION                                ext_t;
  typedef native<T,ext_t>                                                vT;
  typedef typename boost::dispatch::meta::as_integer<vT, unsigned>::type   wished_r_t;
  typedef typename boost::dispatch::meta::call<touints_(vT)>::type       r_t;

  // return type conformity test
  NT2_TEST_TYPE_IS(r_t, wished_r_t);

  // specific values tests
  NT2_TEST_EQUAL(touints(nt2::One<vT>()),  nt2::One<r_t>());
  NT2_TEST_EQUAL(touints(nt2::Zero<vT>()), nt2::Zero<r_t>());
} // end of test for unsigned_int_

NT2_TEST_CASE_TPL ( touints_signed,  BOOST_SIMD_SIMD_INTEGRAL_SIGNED_TYPES)
{

  using nt2::touints;
  using nt2::tag::touints_;
  using boost::simd::native;
  typedef BOOST_SIMD_DEFAULT_EXTENSION                                ext_t;
  typedef native<T,ext_t>                                                vT;
  typedef typename boost::dispatch::meta::as_integer<vT, unsigned>::type   wished_r_t;
  typedef typename boost::dispatch::meta::call<touints_(vT)>::type       r_t;

  // return type conformity test
  NT2_TEST_TYPE_IS(r_t, wished_r_t);

  // specific values tests
  NT2_TEST_EQUAL(touints(nt2::Mone<vT>()), nt2::Zero<r_t>());
  NT2_TEST_EQUAL(touints(nt2::One<vT>()),  nt2::One<r_t>());
  NT2_TEST_EQUAL(touints(nt2::Zero<vT>()), nt2::Zero<r_t>());
} // end of test for signed_int_
