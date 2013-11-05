//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <boost/simd/boolean/include/functions/if_zero_else.hpp>
#include <boost/simd/sdk/simd/native.hpp>
#include <boost/dispatch/functor/meta/call.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <boost/simd/include/constants/zero.hpp>
#include <boost/simd/include/constants/one.hpp>
#include <boost/simd/include/constants/mone.hpp>
#include <boost/simd/include/constants/inf.hpp>
#include <boost/simd/include/constants/minf.hpp>
#include <boost/simd/include/constants/nan.hpp>
#include <boost/simd/include/constants/true.hpp>
#include <boost/simd/include/constants/false.hpp>
#include <boost/simd/sdk/config.hpp>
#include <boost/simd/sdk/simd/io.hpp>

NT2_TEST_CASE_TPL ( if_zero_else_real,  BOOST_SIMD_SIMD_REAL_TYPES)
{
  using boost::simd::if_zero_else;
  using boost::simd::tag::if_zero_else_;
  using boost::simd::native;
  using boost::simd::logical;
  typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef native<T,ext_t>                  vT;
  typedef native< logical<T>, ext_t>             vlT;

  // specific values tests
  NT2_TEST_EQUAL(if_zero_else(boost::simd::False<vlT>(),boost::simd::One<vT>()), boost::simd::One<vT>());
  NT2_TEST_EQUAL(if_zero_else(boost::simd::False<vlT>(),boost::simd::Nan<vT>()), boost::simd::Nan<vT>());
  NT2_TEST_EQUAL(if_zero_else(boost::simd::True<vlT>(),boost::simd::One<vT>()), boost::simd::Zero<vT>());
  NT2_TEST_EQUAL(if_zero_else(boost::simd::True<vlT>(),boost::simd::Nan<vT>()), boost::simd::Zero<vT>());
} // end of test for floating_

NT2_TEST_CASE_TPL ( if_zero_else_signed_int, BOOST_SIMD_SIMD_INTEGRAL_SIGNED_TYPES)
{
  using boost::simd::if_zero_else;
  using boost::simd::tag::if_zero_else_;
  using boost::simd::native;
  using boost::simd::logical;
  typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef native<T,ext_t>                        vT;
  typedef native< logical<T>, ext_t>             vlT;

  // specific values tests
  NT2_TEST_EQUAL(if_zero_else(boost::simd::False<vlT>(),boost::simd::One<vT>()), boost::simd::One<vT>());
  NT2_TEST_EQUAL(if_zero_else(boost::simd::True<vlT>(),boost::simd::One<vT>()), boost::simd::Zero<vT>());
} // end of test for signed_int_
