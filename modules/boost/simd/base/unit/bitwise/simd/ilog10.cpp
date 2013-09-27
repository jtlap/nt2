//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <boost/simd/bitwise/include/functions/ilog10.hpp>
#include <boost/simd/sdk/simd/native.hpp>
#include <boost/simd/include/constants/one.hpp>
#include <boost/simd/include/constants/mone.hpp>
#include <boost/simd/include/constants/zero.hpp>

#include <boost/dispatch/functor/meta/call.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <boost/simd/sdk/config.hpp>
#include <boost/simd/sdk/simd/io.hpp>
#include <boost/type_traits/is_same.hpp>

NT2_TEST_CASE_TPL ( ilog10_ints,  BOOST_SIMD_SIMD_INTEGRAL_TYPES)
{
  using boost::simd::ilog10;
  using boost::simd::tag::ilog10_;
  using boost::simd::native;
  typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef native<T,ext_t>                  vT;
  typedef typename boost::dispatch::meta::call<ilog10_(vT)>::type r_t;

  // specific values tests
  NT2_TEST_EQUAL(ilog10(boost::simd::One<vT>()), boost::simd::Zero<r_t>());
  NT2_TEST_EQUAL(ilog10(boost::simd::Two<vT>()), boost::simd::Zero<r_t>());
  for (T i =  2;  i < boost::simd::Valmax<T>()/10; i*= 10)
  {
    NT2_TEST_EQUAL(ilog10(boost::simd::splat<vT>(i)), boost::simd::splat<r_t>(ilog10(i)));
    NT2_TEST_EQUAL(ilog10(boost::simd::splat<vT>(i+1)), boost::simd::splat<r_t>(ilog10(i)));
  }
} // end of test for floating_

