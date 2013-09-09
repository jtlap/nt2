//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <boost/simd/arithmetic/include/functions/inc.hpp>
#include <boost/simd/sdk/simd/native.hpp>
#include <boost/dispatch/functor/meta/call.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <boost/simd/include/constants/one.hpp>
#include <boost/simd/include/constants/mone.hpp>
#include <boost/simd/include/constants/two.hpp>
#include <boost/simd/include/constants/mtwo.hpp>
#include <boost/simd/include/constants/inf.hpp>
#include <boost/simd/include/constants/minf.hpp>
#include <boost/simd/include/constants/nan.hpp>
#include <boost/simd/sdk/config.hpp>
#include <boost/simd/sdk/simd/io.hpp>

NT2_TEST_CASE_TPL ( inc_signed_int,  BOOST_SIMD_SIMD_INTEGRAL_SIGNED_TYPES)
{
  typedef boost::simd::native<T, BOOST_SIMD_DEFAULT_EXTENSION> vT;

  using boost::simd::inc;
  using boost::simd::tag::inc_;

  // specific values tests
  NT2_TEST_EQUAL(inc(boost::simd::Mone<vT>()), boost::simd::Zero<vT>());
  NT2_TEST_EQUAL(inc(boost::simd::One<vT>()), boost::simd::Two<vT>());
  NT2_TEST_EQUAL(inc(boost::simd::Valmax<vT>()), boost::simd::Valmin<vT>());
  NT2_TEST_EQUAL(inc(boost::simd::Zero<vT>()), boost::simd::One<vT>());
}

NT2_TEST_CASE_TPL ( inc_unsigned_int,  BOOST_SIMD_SIMD_UNSIGNED_TYPES)
{
  typedef boost::simd::native<T, BOOST_SIMD_DEFAULT_EXTENSION> vT;

  using boost::simd::inc;
  using boost::simd::tag::inc_;

  // specific values tests
  NT2_TEST_EQUAL(inc(boost::simd::One<vT>()), boost::simd::Two<vT>());
  NT2_TEST_EQUAL(inc(boost::simd::Valmax<vT>()), boost::simd::Zero<vT>());
  NT2_TEST_EQUAL(inc(boost::simd::Zero<vT>()), boost::simd::One<vT>());
}

NT2_TEST_CASE_TPL( inc_floating, BOOST_SIMD_SIMD_REAL_TYPES)
{
  typedef boost::simd::native<T, BOOST_SIMD_DEFAULT_EXTENSION> vT;

  using boost::simd::inc;
  using boost::simd::tag::inc_;

  // specific values tests
  NT2_TEST_EQUAL(inc(boost::simd::Mone<vT>()), boost::simd::Zero<vT>());
  NT2_TEST_EQUAL(inc(boost::simd::One<vT>()), boost::simd::Two<vT>());
  NT2_TEST_EQUAL(inc(boost::simd::Valmax<vT>()), boost::simd::Valmax<vT>());
  NT2_TEST_EQUAL(inc(boost::simd::Zero<vT>()), boost::simd::One<vT>());
}
