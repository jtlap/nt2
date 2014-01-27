//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <boost/simd/ieee/include/functions/ldexp.hpp>
#include <boost/simd/sdk/simd/native.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/dispatch/functor/meta/call.hpp>
#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <boost/simd/constant/constant.hpp>
#include <boost/simd/sdk/meta/cardinal_of.hpp>
#include <boost/simd/include/functions/simd/dec.hpp>
#include <boost/simd/include/functions/simd/divides.hpp>
#include <boost/simd/sdk/config.hpp>
#include <boost/simd/sdk/simd/io.hpp>

NT2_TEST_CASE_TPL ( ldexp_real__2_0,  BOOST_SIMD_SIMD_REAL_TYPES)
{
  using boost::simd::ldexp;
  using boost::simd::tag::ldexp_;
  using boost::simd::native;
  using boost::simd::meta::cardinal_of;
  using boost::simd::Two;
  typedef typename boost::dispatch::meta::as_integer<T>::type iT;
  typedef BOOST_SIMD_DEFAULT_EXTENSION                     ext_t;
  typedef native<T,ext_t>                                     vT;
  typedef typename boost::dispatch::meta::as_integer<T>::type iT;
  typedef native<iT,ext_t>                                   ivT;
  typedef typename boost::dispatch::meta::call<ldexp_(vT,ivT)>::type r_t;
  typedef typename boost::simd::meta::scalar_of<r_t>::type sr_t;


#ifndef BOOST_SIMD_NO_INVALIDS
  NT2_TEST_EQUAL(ldexp(boost::simd::Inf<T>(),  Two<ivT>()), boost::simd::Inf<r_t>());
  NT2_TEST_EQUAL(ldexp(boost::simd::Minf<T>(), Two<ivT>()), boost::simd::Minf<r_t>());
  NT2_TEST_EQUAL(ldexp(boost::simd::Nan<T>(),  Two<ivT>()), boost::simd::Nan<r_t>());
#endif
  NT2_TEST_EQUAL(ldexp(boost::simd::Mone<T>(), Two<ivT>()), -boost::simd::Four<r_t>());
  NT2_TEST_EQUAL(ldexp(boost::simd::One<T>(),  Two<ivT>()), boost::simd::Four<r_t>());
  NT2_TEST_EQUAL(ldexp(boost::simd::Zero<T>(), Two<ivT>()), boost::simd::Zero<r_t>());
  NT2_TEST_EQUAL(ldexp(boost::simd::One <T>(), boost::simd::Minexponent<vT>()), boost::simd::Smallestposval<r_t>());
  NT2_TEST_EQUAL(ldexp(boost::simd::One <T>(), dec(boost::simd::Minexponent<vT>())), boost::simd::Smallestposval<vT>()/Two<vT>());
  NT2_TEST_EQUAL(ldexp(boost::simd::Two <T>(), dec(boost::simd::Minexponent<vT>())), boost::simd::Smallestposval<vT>());
  NT2_TEST_EQUAL(ldexp(boost::simd::Two <T>(), dec(dec(boost::simd::Minexponent<vT>()))), boost::simd::Smallestposval<vT>()/Two<vT>());
}
