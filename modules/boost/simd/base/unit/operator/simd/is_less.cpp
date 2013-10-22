//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <boost/simd/operator/include/functions/is_less.hpp>
#include <boost/simd/sdk/simd/native.hpp>
#include <boost/simd/sdk/simd/logical.hpp>

#include <boost/dispatch/functor/meta/call.hpp>
#include <boost/simd/sdk/simd/native.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <boost/simd/sdk/config.hpp>
#include <boost/simd/sdk/simd/io.hpp>

#include <boost/simd/include/constants/one.hpp>
#include <boost/simd/include/constants/mone.hpp>
#include <boost/simd/include/constants/zero.hpp>
#include <boost/simd/include/constants/inf.hpp>
#include <boost/simd/include/constants/minf.hpp>
#include <boost/simd/include/constants/nan.hpp>
#include <boost/simd/include/constants/false.hpp>
#include <boost/simd/include/constants/true.hpp>

NT2_TEST_CASE_TPL ( is_less_integer,  BOOST_SIMD_SIMD_INTEGRAL_TYPES)
{
  using boost::simd::is_less;
  using boost::simd::tag::is_less_;
  using boost::simd::native;
  using boost::simd::True;
  using boost::simd::False;
  typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef native<T,ext_t>                  vT;
  typedef typename boost::dispatch::meta::call<is_less_(vT,vT)>::type r_t;

  // specific values tests
  NT2_TEST_EQUAL(is_less(boost::simd::One<vT>(), boost::simd::One<vT>()), False<r_t>());
  NT2_TEST_EQUAL(is_less(boost::simd::One<vT>(),boost::simd::Zero<vT>()), False<r_t>());
  NT2_TEST_EQUAL(is_less(boost::simd::Zero<vT>(), boost::simd::Zero<vT>()), False<r_t>());
} // end of test for integer_

NT2_TEST_CASE_TPL ( is_less_signed_integer,  BOOST_SIMD_SIMD_INTEGRAL_SIGNED_TYPES)
{
  using boost::simd::splat;
  using boost::simd::is_less;
  using boost::simd::tag::is_less_;
  using boost::simd::logical;
  using boost::simd::True;
  typedef boost::simd::native<T, BOOST_SIMD_DEFAULT_EXTENSION> vT;
  typedef typename boost::dispatch::meta::call<is_less_(vT,vT)>::type r_t;

  T hvalmin = T(1) << (sizeof(T)*CHAR_BIT/2-1);
  NT2_TEST_EQUAL( is_less(splat<vT>(hvalmin-1), splat<vT>(hvalmin)),  True<r_t>() );
}

NT2_TEST_CASE_TPL ( is_less_real,  BOOST_SIMD_SIMD_REAL_TYPES)
{
  using boost::simd::is_less;
  using boost::simd::tag::is_less_;
  using boost::simd::native;
  using boost::simd::True;
  using boost::simd::False;
  typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef native<T,ext_t>                  vT;
  typedef typename boost::dispatch::meta::call<is_less_(vT,vT)>::type r_t;

  // specific values tests
  NT2_TEST_EQUAL(is_less(boost::simd::Inf<vT>(), boost::simd::Inf<vT>()), False<r_t>());
  NT2_TEST_EQUAL(is_less(boost::simd::Minf<vT>(), boost::simd::Minf<vT>()), False<r_t>());
  NT2_TEST_EQUAL(is_less(boost::simd::Nan<vT>(), boost::simd::Nan<vT>()), False<r_t>());
  NT2_TEST_EQUAL(is_less(boost::simd::One<vT>(),boost::simd::Zero<vT>()), False<r_t>());
  NT2_TEST_EQUAL(is_less(boost::simd::Zero<vT>(), boost::simd::Zero<vT>()), False<r_t>());
} // end of test for floating_
