//==============================================================================
//         Copyright 2003 - 2013   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <boost/simd/ieee/include/functions/bitfloating.hpp>

#include <boost/dispatch/functor/meta/call.hpp>
#include <boost/simd/sdk/simd/native.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <boost/simd/sdk/config.hpp>
#include <boost/simd/sdk/simd/io.hpp>

#include <boost/simd/include/constants/mone.hpp>
#include <boost/simd/include/constants/one.hpp>
#include <boost/simd/include/constants/valmax.hpp>
#include <boost/simd/include/constants/valmin.hpp>
#include <boost/simd/include/constants/zero.hpp>
#include <boost/simd/include/constants/bitincrement.hpp>


NT2_TEST_CASE_TPL ( bitfloating_int_convert,  BOOST_SIMD_INT_CONVERT_TYPES)
{
  using boost::simd::bitfloating;
  using boost::simd::tag::bitfloating_;
  using boost::simd::native;
  typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef native<T,ext_t>                  vT;
  typedef typename boost::dispatch::meta::call<bitfloating_(vT)>::type r_t;

  // specific values tests
#if !defined(BOOST_SIMD_NO_DENORMALS)
  NT2_TEST_EQUAL(bitfloating(boost::simd::One<vT>()), boost::simd::Bitincrement<r_t>());
  NT2_TEST_EQUAL(bitfloating(boost::simd::Mone<vT>()), -boost::simd::Bitincrement<r_t>());
#endif
  NT2_TEST_EQUAL(bitfloating(boost::simd::Zero<vT>()), boost::simd::Zero<r_t>());
}

NT2_TEST_CASE_TPL ( bitfloating_uint_convert,  BOOST_SIMD_UINT_CONVERT_TYPES)
{
  using boost::simd::bitfloating;
  using boost::simd::tag::bitfloating_;
  using boost::simd::native;
  typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef native<T,ext_t>                  vT;
  typedef typename boost::dispatch::meta::call<bitfloating_(vT)>::type r_t;

  // specific values tests
  NT2_TEST_EQUAL(bitfloating(boost::simd::One<vT>()), boost::simd::Bitincrement<r_t>());
  NT2_TEST_EQUAL(bitfloating(boost::simd::Zero<vT>()), boost::simd::Zero<r_t>());
}
