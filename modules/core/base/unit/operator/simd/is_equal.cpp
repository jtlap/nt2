//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/operator/include/functions/is_equal.hpp>
#include <boost/simd/sdk/simd/native.hpp>
#include <boost/simd/sdk/simd/logical.hpp>

#include <boost/dispatch/functor/meta/call.hpp>
#include <boost/simd/sdk/simd/native.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <boost/simd/sdk/config.hpp>
#include <boost/simd/sdk/simd/io.hpp>

#include <nt2/include/constants/one.hpp>
#include <nt2/include/constants/mone.hpp>
#include <nt2/include/constants/zero.hpp>
#include <nt2/include/constants/inf.hpp>
#include <nt2/include/constants/minf.hpp>
#include <nt2/include/constants/nan.hpp>
#include <nt2/include/constants/false.hpp>
#include <nt2/include/constants/true.hpp>
#include <nt2/include/constants/valmax.hpp>
#include <nt2/include/constants/valmin.hpp>

NT2_TEST_CASE_TPL ( is_equal_integer,  NT2_SIMD_TYPES)
{
  using nt2::is_equal;
  using nt2::tag::is_equal_;
  using boost::simd::native;
  using nt2::True;
  using nt2::False;
  typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef native<T,ext_t>                  vT;
  typedef typename boost::dispatch::meta::call<is_equal_(vT,vT)>::type r_t;

  NT2_TEST_EQUAL(is_equal(nt2::Valmax<vT>(), nt2::Valmin<vT>()), False<r_t>());
  NT2_TEST_EQUAL(is_equal(nt2::Valmax<vT>(), nt2::Valmax<vT>()), True<r_t>());
  NT2_TEST_EQUAL(is_equal(nt2::Valmin<vT>(), nt2::Valmax<vT>()), False<r_t>());
}

NT2_TEST_CASE_TPL ( is_equal_signed_integer,  NT2_SIMD_INTEGRAL_SIGNED_TYPES)
{
  using nt2::is_equal;
  using nt2::tag::is_equal_;
  using boost::simd::native;
  using nt2::True;
  using nt2::False;
  typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef native<T,ext_t>                  vT;
  typedef typename boost::dispatch::meta::call<is_equal_(vT,vT)>::type r_t;

  NT2_TEST_EQUAL(is_equal(nt2::Zero<vT>(), nt2::Mone<vT>()), False<r_t>());
  NT2_TEST_EQUAL(is_equal(nt2::Zero<vT>(), nt2::One<vT>()) , False<r_t>());
}

NT2_TEST_CASE_TPL ( is_equal_real,  NT2_SIMD_REAL_TYPES)
{
  using nt2::is_equal;
  using nt2::tag::is_equal_;
  using boost::simd::native;
  using nt2::True;
  using nt2::False;
  typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef native<T,ext_t>                  vT;
  typedef typename boost::dispatch::meta::call<is_equal_(vT,vT)>::type r_t;

  NT2_TEST_EQUAL(is_equal(nt2::Inf<vT>() , nt2::Inf<vT>()) , True<r_t>());
  NT2_TEST_EQUAL(is_equal(nt2::Minf<vT>(), nt2::Minf<vT>()), True<r_t>());
  NT2_TEST_EQUAL(is_equal(nt2::Inf<vT>() , nt2::Minf<vT>()), False<r_t>());
  NT2_TEST_EQUAL(is_equal(nt2::Nan<vT>() , nt2::Nan<vT>()) , False<r_t>());
  NT2_TEST_EQUAL(is_equal(nt2::Zero<vT>(), nt2::Mone<vT>()), False<r_t>());
  NT2_TEST_EQUAL(is_equal(nt2::Zero<vT>(), nt2::One<vT>()) , False<r_t>());
}


NT2_TEST_CASE_TPL ( is_equall,  NT2_SIMD_TYPES)
{
  using nt2::is_equal;
  using nt2::tag::is_equal_;
  using boost::simd::native;
  using nt2::True;
  using nt2::False;
  typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef native<T,ext_t>                  vT;
  typedef native< nt2::logical<T>, ext_t> vlT;
  typedef typename boost::dispatch::meta::call<is_equal_(vT,vT)>::type r_t;

  // specific values tests
  NT2_TEST_EQUAL(is_equal(nt2::True<vlT>(),nt2::False<vlT>()), False<r_t>());
  NT2_TEST_EQUAL(is_equal(nt2::True<vlT>(), nt2::True<vlT>()), True<r_t>());
  NT2_TEST_EQUAL(is_equal(nt2::False<vlT>(),nt2::False<vlT>()), True<r_t>());
  NT2_TEST_EQUAL(is_equal(nt2::False<vlT>(), nt2::True<vlT>()), False<r_t>());
} // end of test for floating_
