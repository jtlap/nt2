//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <boost/simd/operator/include/functions/is_equal.hpp>
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
#include <boost/simd/include/constants/zero.hpp>
#include <boost/simd/include/constants/inf.hpp>
#include <boost/simd/include/constants/minf.hpp>
#include <boost/simd/include/constants/nan.hpp>
#include <boost/simd/include/constants/false.hpp>
#include <boost/simd/include/constants/true.hpp>

NT2_TEST_CASE_TPL ( is_equal_integer, BOOST_SIMD_SIMD_INTEGRAL_TYPES)
{
  using boost::simd::is_equal;
  using boost::simd::tag::is_equal_;
  using boost::simd::native;
  using boost::simd::True;
  using boost::simd::False;
  typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef native<T,ext_t>                  vT;
  typedef native< boost::simd::logical<T>, ext_t> vlT;
  typedef typename boost::dispatch::meta::call<is_equal_(vT,vT)>::type r_t;

  // specific values tests
   NT2_TEST_EQUAL(is_equal(boost::simd::One<vT>(), boost::simd::One<vT>()), True<r_t>());
   NT2_TEST_EQUAL(is_equal(boost::simd::One<vT>(),boost::simd::Zero<vT>()), False<r_t>());
   NT2_TEST_EQUAL(is_equal(boost::simd::Zero<vT>(), boost::simd::Zero<vT>()), True<r_t>());
} // end of test for integer_

NT2_TEST_CASE_TPL ( is_equal_real,  BOOST_SIMD_SIMD_REAL_TYPES)
{
  using boost::simd::is_equal;
  using boost::simd::tag::is_equal_;
  using boost::simd::native;
  using boost::simd::True;
  using boost::simd::False;
  typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef native<T,ext_t>                  vT;
  typedef native< boost::simd::logical<T>, ext_t> vlT;
  typedef typename boost::dispatch::meta::call<is_equal_(vT,vT)>::type r_t;

  // specific values tests
  NT2_TEST_EQUAL(is_equal(boost::simd::Inf<vT>(), boost::simd::Inf<vT>()), True<r_t>());
  NT2_TEST_EQUAL(is_equal(boost::simd::Minf<vT>(), boost::simd::Minf<vT>()), True<r_t>());
  NT2_TEST_EQUAL(is_equal(boost::simd::Nan<vT>(), boost::simd::Nan<vT>()), False<r_t>());
  NT2_TEST_EQUAL(is_equal(boost::simd::One<vT>(),boost::simd::Zero<vT>()), False<r_t>());
  NT2_TEST_EQUAL(is_equal(boost::simd::Zero<vT>(), boost::simd::Zero<vT>()), True<r_t>());
} // end of test for floating_

NT2_TEST_CASE_TPL ( is_equall,  BOOST_SIMD_SIMD_TYPES)
{
  using boost::simd::is_equal;
  using boost::simd::tag::is_equal_;
  using boost::simd::native;
  using boost::simd::True;
  using boost::simd::False;
  typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef native<T,ext_t>                  vT;
  typedef native< boost::simd::logical<T>, ext_t> vlT;
  typedef typename boost::dispatch::meta::call<is_equal_(vT,vT)>::type r_t;

  // specific values tests
  NT2_TEST_EQUAL(is_equal(boost::simd::True<vlT>(),boost::simd::False<vlT>()), False<r_t>());
  NT2_TEST_EQUAL(is_equal(boost::simd::True<vlT>(), boost::simd::True<vlT>()), True<r_t>());
  NT2_TEST_EQUAL(is_equal(boost::simd::False<vlT>(),boost::simd::False<vlT>()), True<r_t>());
  NT2_TEST_EQUAL(is_equal(boost::simd::False<vlT>(), boost::simd::True<vlT>()), False<r_t>());
} // end of test for floating_
