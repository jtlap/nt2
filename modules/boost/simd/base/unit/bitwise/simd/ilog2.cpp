//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <boost/simd/bitwise/include/functions/ilog2.hpp>
#include <boost/simd/sdk/simd/native.hpp>

#include <boost/dispatch/functor/meta/call.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <boost/simd/include/functions/splat.hpp>
#include <boost/simd/include/constants/one.hpp>
#include <boost/simd/include/constants/mone.hpp>
#include <boost/simd/include/constants/zero.hpp>
#include <boost/simd/include/constants/inf.hpp>
#include <boost/simd/include/constants/minf.hpp>
#include <boost/simd/include/constants/nan.hpp>
#include <boost/simd/sdk/config.hpp>
#include <boost/simd/sdk/simd/io.hpp>

NT2_TEST_CASE_TPL ( ilog2_real__1_0,  BOOST_SIMD_SIMD_REAL_TYPES)
{
  using boost::simd::ilog2;
  using boost::simd::tag::ilog2_;
  using boost::simd::native;
  typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef native<T,ext_t>                  vT;
  typedef typename boost::dispatch::meta::call<ilog2_(vT)>::type r_t;


  // specific values tests
  NT2_TEST_EQUAL(ilog2(boost::simd::Minf<vT>()), boost::simd::Zero<r_t>());
  NT2_TEST_EQUAL(ilog2(boost::simd::Mone<vT>()), boost::simd::Zero<r_t>());
  NT2_TEST_EQUAL(ilog2(boost::simd::One<vT>()), boost::simd::Zero<r_t>());
  NT2_TEST_EQUAL(ilog2(boost::simd::Zero<vT>()), boost::simd::Zero<r_t>());
} // end of test for floating_

NT2_TEST_CASE_TPL ( ilog2_ints,  BOOST_SIMD_SIMD_TYPES)
{
  using boost::simd::ilog2;
  using boost::simd::tag::ilog2_;
  using boost::simd::native;
  using boost::simd::meta::cardinal_of;
  typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef native<T,ext_t>                  vT;
  typedef typename boost::dispatch::meta::call<ilog2_(vT)>::type r_t;

  // specific values tests
  NT2_TEST_EQUAL(ilog2(boost::simd::One<vT>()), boost::simd::Zero<r_t>());
  NT2_TEST_EQUAL(ilog2(boost::simd::Two<vT>()), boost::simd::One<r_t>());
  for (T i =  2;  i < boost::simd::Valmax<T>()/2; i*= 2)
    {
      NT2_TEST_EQUAL(ilog2(boost::simd::splat<vT>(i)), boost::simd::splat<r_t>(ilog2(i)));
      NT2_TEST_EQUAL(ilog2(boost::simd::splat<vT>(i+1)), boost::simd::splat<r_t>(ilog2(i)));
    }
} // end of test for floating_
