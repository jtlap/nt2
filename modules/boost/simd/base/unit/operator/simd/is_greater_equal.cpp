//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <boost/simd/operator/include/functions/is_greater_equal.hpp>
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
#include <boost/simd/include/constants/valmax.hpp>
#include <boost/simd/include/constants/valmin.hpp>

NT2_TEST_CASE_TPL ( is_greater_equal_integer,  BOOST_SIMD_SIMD_TYPES)
{
  using boost::simd::is_greater_equal;
  using boost::simd::tag::is_greater_equal_;
  using boost::simd::native;
  using boost::simd::True;
  using boost::simd::False;
  typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef native<T,ext_t>                  vT;
  typedef typename boost::dispatch::meta::call<is_greater_equal_(vT,vT)>::type r_t;

  NT2_TEST_EQUAL(is_greater_equal(boost::simd::Valmax<vT>(), boost::simd::Valmin<vT>()), True<r_t>());
  NT2_TEST_EQUAL(is_greater_equal(boost::simd::Valmax<vT>(), boost::simd::Valmax<vT>()), True<r_t>());
  NT2_TEST_EQUAL(is_greater_equal(boost::simd::Valmin<vT>(), boost::simd::Valmax<vT>()), False<r_t>());
}

NT2_TEST_CASE_TPL ( is_greater_equal_signed_integer,  BOOST_SIMD_SIMD_INTEGRAL_SIGNED_TYPES)
{
  using boost::simd::is_greater_equal;
  using boost::simd::tag::is_greater_equal_;
  using boost::simd::native;
  using boost::simd::True;
  using boost::simd::False;
  typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef native<T,ext_t>                  vT;
  typedef typename boost::dispatch::meta::call<is_greater_equal_(vT,vT)>::type r_t;

  NT2_TEST_EQUAL(is_greater_equal(boost::simd::Zero<vT>()  , boost::simd::Mone<vT>()), True<r_t>());
  NT2_TEST_EQUAL(is_greater_equal(boost::simd::Zero<vT>()  , boost::simd::One<vT>()), False<r_t>());
}

NT2_TEST_CASE_TPL ( is_greater_equal_real,  BOOST_SIMD_SIMD_REAL_TYPES)
{
  using boost::simd::is_greater_equal;
  using boost::simd::tag::is_greater_equal_;
  using boost::simd::native;
  using boost::simd::True;
  using boost::simd::False;
  typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef native<T,ext_t>                  vT;
  typedef typename boost::dispatch::meta::call<is_greater_equal_(vT,vT)>::type r_t;

  NT2_TEST_EQUAL(is_greater_equal(boost::simd::Inf<vT>() , boost::simd::Inf<vT>()) , True<r_t>());
  NT2_TEST_EQUAL(is_greater_equal(boost::simd::Minf<vT>(), boost::simd::Minf<vT>()), True<r_t>());
  NT2_TEST_EQUAL(is_greater_equal(boost::simd::Inf<vT>() , boost::simd::Minf<vT>()), True<r_t>());
  NT2_TEST_EQUAL(is_greater_equal(boost::simd::Nan<vT>() , boost::simd::Nan<vT>()) , False<r_t>());
  NT2_TEST_EQUAL(is_greater_equal(boost::simd::Zero<vT>()  , boost::simd::Mone<vT>()), True<r_t>());
  NT2_TEST_EQUAL(is_greater_equal(boost::simd::Zero<vT>()  , boost::simd::One<vT>()), False<r_t>());
}
