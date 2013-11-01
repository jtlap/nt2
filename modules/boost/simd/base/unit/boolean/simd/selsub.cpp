//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <boost/simd/boolean/include/functions/selsub.hpp>
#include <boost/simd/sdk/simd/native.hpp>
#include <boost/dispatch/functor/meta/call.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <boost/simd/include/constants/zero.hpp>
#include <boost/simd/include/constants/one.hpp>
#include <boost/simd/include/constants/two.hpp>
#include <boost/simd/include/constants/four.hpp>
#include <boost/simd/include/constants/mone.hpp>
#include <boost/simd/include/constants/three.hpp>
#include <boost/simd/include/constants/inf.hpp>
#include <boost/simd/include/constants/minf.hpp>
#include <boost/simd/include/constants/nan.hpp>
#include <boost/simd/include/constants/true.hpp>
#include <boost/simd/include/constants/false.hpp>
#include <boost/simd/sdk/config.hpp>
#include <boost/simd/sdk/simd/io.hpp>

NT2_TEST_CASE_TPL ( selsub_real,  BOOST_SIMD_SIMD_REAL_TYPES)
{
  using boost::simd::selsub;
  using boost::simd::tag::selsub_;
  using boost::simd::native;
  using boost::simd::logical;
  typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef native<T,ext_t>                  vT;
  typedef native<logical<T> ,ext_t>              vlT;

  // specific values tests
  NT2_TEST_EQUAL(selsub(boost::simd::False<vlT>(),boost::simd::One<vT>(),boost::simd::Two<vT>()), boost::simd::One<vT>());
  NT2_TEST_EQUAL(selsub(boost::simd::True<vlT>(),boost::simd::One<vT>(),boost::simd::Two<vT>()), boost::simd::Mone<vT>());
  NT2_TEST_EQUAL(selsub(boost::simd::True<vlT>(),boost::simd::Inf<vT>(),boost::simd::Inf<vT>()), boost::simd::Nan<vT>());
  NT2_TEST_EQUAL(selsub(boost::simd::True<vlT>(),boost::simd::One<vT>(), boost::simd::Inf<vT>()), boost::simd::Minf<vT>());
  NT2_TEST_EQUAL(selsub(boost::simd::True<vlT>(),boost::simd::Minf<vT>(),boost::simd::Minf<vT>()), boost::simd::Nan<vT>());
  NT2_TEST_EQUAL(selsub(boost::simd::True<vlT>(),boost::simd::Nan<vT>(),boost::simd::Nan<vT>()), boost::simd::Nan<vT>());
  NT2_TEST_EQUAL(selsub(boost::simd::True<vlT>(),boost::simd::Zero<vT>(),boost::simd::Zero<vT>()), boost::simd::Zero<vT>());
} // end of test for floating_

NT2_TEST_CASE_TPL ( selsub_signed_int,  BOOST_SIMD_SIMD_INTEGRAL_SIGNED_TYPES)
{
  using boost::simd::selsub;
  using boost::simd::tag::selsub_;
  using boost::simd::native;
  using boost::simd::logical;
  typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef native<T,ext_t>                  vT;
  typedef native<logical<T> ,ext_t>              vlT;

  // specific values tests
  NT2_TEST_EQUAL(selsub(boost::simd::True<vlT>(),boost::simd::Four<vT>(),boost::simd::Two<vT>()), boost::simd::Two<vT>());
  NT2_TEST_EQUAL(selsub(boost::simd::False<vlT>(),boost::simd::Four<vT>(),boost::simd::Two<vT>()), boost::simd::Four<vT>());
  NT2_TEST_EQUAL(selsub(boost::simd::False<vlT>(), boost::simd::Zero<vT>(), boost::simd::Zero<vT>()), boost::simd::Zero<vT>());
} // end of test for signed_int_

NT2_TEST_CASE_TPL ( selsub_unsigned_int,  BOOST_SIMD_SIMD_UNSIGNED_TYPES)
{
  using boost::simd::selsub;
  using boost::simd::tag::selsub_;
  using boost::simd::native;
  using boost::simd::logical;
  typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef native<T,ext_t>                  vT;
  typedef native<logical<T> ,ext_t>              vlT;

  // specific values tests
  NT2_TEST_EQUAL(selsub(boost::simd::True<vlT>(),boost::simd::Four<vT>(),boost::simd::Two<vT>()), boost::simd::Two<vT>());
  NT2_TEST_EQUAL(selsub(boost::simd::False<vlT>(),boost::simd::Four<vT>(),boost::simd::Two<vT>()), boost::simd::Four<vT>());
  NT2_TEST_EQUAL(selsub(boost::simd::False<vlT>(), boost::simd::Zero<vT>(), boost::simd::Zero<vT>()),  boost::simd::Zero<vT>());
} // end of test for unsigned_int_
