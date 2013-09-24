//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <boost/simd/bitwise/include/functions/clz.hpp>
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
#include <boost/simd/include/constants/valmax.hpp>
#include <boost/simd/sdk/config.hpp>
#include <boost/simd/sdk/simd/io.hpp>


NT2_TEST_CASE_TPL ( clz_real__1_0,  BOOST_SIMD_SIMD_REAL_TYPES)
{
  using boost::simd::clz;
  using boost::simd::tag::clz_;
  using boost::simd::native;
  typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef native<T,ext_t>                  vT;
  typedef typename boost::dispatch::meta::call<clz_(vT)>::type r_t;

  // specific values tests
#ifndef BOOST_SIMD_NO_INVALIDS
  NT2_TEST_EQUAL(clz(boost::simd::Minf<vT>()), boost::simd::splat<r_t>(clz(boost::simd::Minf<T>())));
#endif
  NT2_TEST_EQUAL(clz(boost::simd::Mone<vT>()), boost::simd::splat<r_t>(clz(boost::simd::Mone<T>())));
  NT2_TEST_EQUAL(clz(boost::simd::One<vT>()),  boost::simd::splat<r_t>(clz(boost::simd::One<T>())));
} // end of test for floating_

NT2_TEST_CASE_TPL ( clz_ints,  BOOST_SIMD_SIMD_UNSIGNED_TYPES)
{
  using boost::simd::clz;
  using boost::simd::tag::clz_;
  using boost::simd::native;
  typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef native<T,ext_t>                  vT;
  typedef typename boost::dispatch::meta::call<clz_(vT)>::type r_t;

  NT2_TEST_EQUAL(clz(boost::simd::splat<vT>(1)),  boost::simd::splat<r_t>(clz(T(1))));

  // specific values tests
  for (T i =  2;  i < boost::simd::Valmax<T>()/2; i*= 2)
    {
      NT2_TEST_EQUAL(clz(boost::simd::splat<vT>(i)),  boost::simd::splat<r_t>(clz(i)));
      NT2_TEST_EQUAL(clz(boost::simd::splat<vT>(i+1)),  boost::simd::splat<r_t>(clz(i)));
    }
} // end of test for floating_
