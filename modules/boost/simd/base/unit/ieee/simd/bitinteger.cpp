//==============================================================================
//         Copyright 2003 - 2013   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <boost/simd/ieee/include/functions/bitinteger.hpp>

#include <boost/dispatch/functor/meta/call.hpp>
#include <boost/simd/sdk/simd/native.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <boost/simd/sdk/config.hpp>
#include <boost/simd/sdk/simd/io.hpp>

#include <boost/simd/include/constants/mone.hpp>
#include <boost/simd/include/constants/one.hpp>
#include <boost/simd/include/constants/valmax.hpp>
#include <boost/simd/include/constants/zero.hpp>
#include <boost/simd/include/constants/inf.hpp>
#include <boost/simd/include/constants/minf.hpp>
#include <boost/simd/include/constants/nan.hpp>
#include <boost/simd/include/constants/bitincrement.hpp>

NT2_TEST_CASE_TPL ( bitinteger_real,  BOOST_SIMD_SIMD_REAL_TYPES)
{
  using boost::simd::bitinteger;
  using boost::simd::tag::bitinteger_;
  using boost::simd::native;
  typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef native<T,ext_t>                  vT;
  typedef typename boost::dispatch::meta::call<bitinteger_(vT)>::type r_t;

  // specific values tests
#ifndef BOOST_SIMD_NO_INVALIDS
  NT2_TEST_EQUAL(bitinteger(boost::simd::Nan<vT>() )   ,-bitinteger(boost::simd::Valmax<r_t>())   );
#endif
#if !defined(BOOST_SIMD_NO_DENORMALS)
  NT2_TEST_EQUAL(bitinteger(boost::simd::Bitincrement<vT>()), boost::simd::One<r_t>());
  NT2_TEST_EQUAL(bitinteger(-boost::simd::Bitincrement<vT>()), boost::simd::Mone<r_t>());
#endif
  NT2_TEST_EQUAL(bitinteger(boost::simd::Zero<vT>()), boost::simd::Zero<r_t>());
}
