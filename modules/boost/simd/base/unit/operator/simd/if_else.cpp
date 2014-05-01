//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <boost/simd/operator/include/functions/if_else.hpp>
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
#include <boost/simd/include/constants/two.hpp>
#include <boost/simd/include/constants/zero.hpp>
#include <boost/simd/include/constants/inf.hpp>
#include <boost/simd/include/constants/minf.hpp>
#include <boost/simd/include/constants/nan.hpp>
#include <boost/simd/include/constants/false.hpp>
#include <boost/simd/include/constants/true.hpp>

NT2_TEST_CASE_TPL ( if_else_integer,  BOOST_SIMD_SIMD_INTEGRAL_TYPES)
{
  using boost::simd::if_else;
  using boost::simd::tag::if_else_;
  using boost::simd::native;
  typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef native<T,ext_t>                  vT;
  typedef native<boost::simd::logical<T>, ext_t>                vlT;
  typedef typename boost::dispatch::meta::call<if_else_(vlT,vT,vT)>::type r_t;

  // specific values tests
  NT2_TEST_EQUAL(if_else(boost::simd::True<vlT>(), boost::simd::One<vT>(), boost::simd::Two<vT>()), boost::simd::One<r_t>());
  NT2_TEST_EQUAL(if_else(boost::simd::True<vlT>(),boost::simd::Zero<vT>(),boost::simd::Two<vT>()), boost::simd::Zero<r_t>());
  NT2_TEST_EQUAL(if_else(boost::simd::False<vlT>(), boost::simd::Zero<vT>(), boost::simd::Zero<vT>()), boost::simd::Zero<r_t>());
  NT2_TEST_EQUAL(if_else(boost::simd::False<vlT>(), boost::simd::False<vlT>(), boost::simd::False<vlT>()), boost::simd::False<vlT>());
  NT2_TEST_EQUAL(if_else(boost::simd::True<vlT>(), boost::simd::True<vlT>(), boost::simd::False<vlT>()), boost::simd::True<vlT>());
  NT2_TEST_EQUAL(if_else(boost::simd::One<vT>(), boost::simd::True<vlT>(), boost::simd::False<vlT>()), boost::simd::True<vlT>());
} // end of test for integer_

NT2_TEST_CASE_TPL ( if_else_real,  BOOST_SIMD_SIMD_REAL_TYPES)
{
  using boost::simd::if_else;
  using boost::simd::tag::if_else_;
  using boost::simd::native;
  typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef native<T,ext_t>                  vT;
  typedef native<boost::simd::logical<T>, ext_t>                vlT;
  typedef typename boost::dispatch::meta::call<if_else_(vlT,vT,vT)>::type r_t;


  // specific values tests
  NT2_TEST_EQUAL(if_else(boost::simd::True<vlT>(), boost::simd::Inf<vT>(), boost::simd::One<vT>()), boost::simd::Inf<r_t>());
  NT2_TEST_EQUAL(if_else(boost::simd::True<vlT>(), boost::simd::Minf<vT>(), boost::simd::One<vT>()), boost::simd::Minf<r_t>());
  NT2_TEST_EQUAL(if_else(boost::simd::True<vlT>(), boost::simd::Nan<vT>(), boost::simd::One<vT>()), boost::simd::Nan<r_t>());
  NT2_TEST_EQUAL(if_else(boost::simd::True<vlT>(),boost::simd::Zero<vT>(),boost::simd::Two<vT>()), boost::simd::Zero<r_t>());
  NT2_TEST_EQUAL(if_else(boost::simd::False<vlT>(), boost::simd::One<vT>(), boost::simd::Zero<vT>()), boost::simd::Zero<r_t>());
  NT2_TEST_EQUAL(if_else(boost::simd::One<vT>(), boost::simd::True<vlT>(), boost::simd::False<vlT>()), boost::simd::True<vlT>());
} // end of test for floating_
