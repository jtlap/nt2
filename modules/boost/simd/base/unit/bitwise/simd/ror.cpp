//==============================================================================
//         Copyright 2003 - 2013   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <boost/simd/bitwise/include/functions/ror.hpp>

#include <boost/dispatch/functor/meta/call.hpp>
#include <boost/simd/sdk/simd/native.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <boost/simd/sdk/config.hpp>
#include <boost/simd/sdk/simd/io.hpp>

#include <boost/simd/include/functions/splat.hpp>
#include <boost/simd/include/constants/mone.hpp>
#include <boost/simd/include/constants/one.hpp>
#include <boost/simd/include/constants/zero.hpp>


NT2_TEST_CASE_TPL ( ror_integer,  BOOST_SIMD_SIMD_INTEGRAL_TYPES)
{
  using boost::simd::ror;
  using boost::simd::tag::ror_;
  using boost::simd::native;
  typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef native<T,ext_t>                  vT;
  typedef typename boost::dispatch::meta::as_integer<vT>::type ivT;
  typedef typename boost::dispatch::meta::call<ror_(vT,ivT)>::type r_t;

  // specific values tests
  NT2_TEST_EQUAL(ror(boost::simd::splat<vT>(2),boost::simd::splat<ivT>(2)), boost::simd::splat<r_t>(T(1)<<(sizeof(T)*8-1)));
  NT2_TEST_EQUAL(ror(boost::simd::Mone<vT>(),boost::simd::splat<ivT>(1)), boost::simd::Mone<r_t>());
  NT2_TEST_EQUAL(ror(boost::simd::Mone<vT>(),boost::simd::splat<ivT>(5)), boost::simd::Mone<r_t>());
  NT2_TEST_EQUAL(ror(boost::simd::One<vT>(),boost::simd::splat<ivT>(1)), boost::simd::splat<r_t>(T(1)<<(sizeof(T)*8-1)));
  NT2_TEST_EQUAL(ror(boost::simd::Zero<vT>(),boost::simd::splat<ivT>(1)), boost::simd::Zero<r_t>());
} // end of test for integer_
