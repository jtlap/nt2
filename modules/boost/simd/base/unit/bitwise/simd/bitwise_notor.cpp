//==============================================================================
//         Copyright 2003 - 2013   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <boost/simd/bitwise/include/functions/bitwise_notor.hpp>

#include <boost/dispatch/functor/meta/call.hpp>
#include <boost/simd/sdk/simd/native.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>
#include <boost/simd/sdk/config.hpp>
#include <boost/simd/sdk/simd/io.hpp>

#include <boost/simd/include/constants/mone.hpp>
#include <boost/simd/include/constants/one.hpp>
#include <boost/simd/include/constants/zero.hpp>
#include <boost/simd/include/constants/inf.hpp>
#include <boost/simd/include/constants/minf.hpp>
#include <boost/simd/include/constants/nan.hpp>
#include <boost/simd/include/constants/bitincrement.hpp>
#include <boost/simd/include/constants/valmin.hpp>

NT2_TEST_CASE_TPL(bitwise_notor_real, BOOST_SIMD_REAL_TYPES)
{
  using boost::simd::bitwise_notor;
  using boost::simd::tag::bitwise_notor_;
  using boost::simd::native;
  typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef native<T,ext_t>                  vT;
  typedef typename boost::dispatch::meta::call<bitwise_notor_(vT,vT)>::type r_t;

  // specific values tests
#ifndef BOOST_SIMD_NO_INVALIDS
  NT2_TEST_EQUAL(bitwise_notor(boost::simd::Inf<vT>(), boost::simd::Inf<vT>()), boost::simd::Nan<r_t>());
  NT2_TEST_EQUAL(bitwise_notor(boost::simd::Minf<vT>(), boost::simd::Minf<vT>()), boost::simd::Nan<r_t>());
  NT2_TEST_EQUAL(bitwise_notor(boost::simd::Nan<vT>(), boost::simd::Nan<vT>()), boost::simd::Nan<r_t>());
#endif
  NT2_TEST_EQUAL(bitwise_notor(boost::simd::Zero<vT>(), boost::simd::Zero<vT>()), boost::simd::Nan<r_t>());
}



NT2_TEST_CASE_TPL(bitwise_notor_ui, BOOST_SIMD_UNSIGNED_TYPES)
{
  using boost::simd::bitwise_notor;
  using boost::simd::tag::bitwise_notor_;
  using boost::simd::native;
  typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef native<T,ext_t>                  vT;
  typedef typename boost::dispatch::meta::call<bitwise_notor_(vT,vT)>::type r_t;

  // specific values tests
  NT2_TEST_EQUAL(bitwise_notor(boost::simd::Zero<vT>(), boost::simd::Zero<vT>()), boost::simd::Valmax<r_t>());
}

NT2_TEST_CASE_TPL(bitwise_notor_si, BOOST_SIMD_INTEGRAL_SIGNED_TYPES)
{
  using boost::simd::bitwise_notor;
  using boost::simd::tag::bitwise_notor_;
  using boost::simd::native;
  typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef native<T,ext_t>                  vT;
  typedef typename boost::dispatch::meta::call<bitwise_notor_(vT,vT)>::type r_t;

  // specific values tests
  NT2_TEST_EQUAL(bitwise_notor(boost::simd::Zero<vT>(), boost::simd::Zero<vT>()), boost::simd::Mone<r_t>());
}

NT2_TEST_CASE_TPL(bitwise_notor_mix, BOOST_SIMD_REAL_TYPES)
{
  using boost::simd::bitwise_notor;
  using boost::simd::tag::bitwise_notor_;
  using boost::simd::native;
  typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef native<T, ext_t>                  vT;
  typedef typename  boost::dispatch::meta::as_integer<vT>::type sivT;
  typedef typename  boost::dispatch::meta::as_integer<vT, unsigned>::type uivT;

  // return type conformity test
  NT2_TEST_TYPE_IS(typename boost::dispatch::meta::call<bitwise_notor_(vT,uivT)>::type, vT);
  NT2_TEST_TYPE_IS(typename boost::dispatch::meta::call<bitwise_notor_(vT,sivT)>::type, vT);
  NT2_TEST_TYPE_IS(typename boost::dispatch::meta::call<bitwise_notor_(uivT, vT)>::type, uivT);
  NT2_TEST_TYPE_IS(typename boost::dispatch::meta::call<bitwise_notor_(sivT, vT)>::type, sivT);

  // specific values tests
  NT2_TEST_EQUAL(bitwise_notor(boost::simd::Nan<vT>(),boost::simd::One<uivT>()), boost::simd::Bitincrement<vT>());
  NT2_TEST_EQUAL(bitwise_notor(boost::simd::Nan<vT>(), boost::simd::One<sivT>()), boost::simd::Bitincrement<vT>());
  NT2_TEST_EQUAL(bitwise_notor(boost::simd::Valmin<sivT>(),boost::simd::Zero<vT>()), boost::simd::Valmax<sivT>());
  NT2_TEST_EQUAL(bitwise_notor(boost::simd::Zero<uivT>(), boost::simd::Zero<vT>()), boost::simd::Valmax<uivT>());
}
