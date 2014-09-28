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

#include <boost/simd/include/constants/valmax.hpp>
#include <boost/simd/include/constants/mindenormal.hpp>
#include <boost/simd/include/constants/minexponent.hpp>
#include <boost/simd/include/constants/halfeps.hpp>
#include <boost/simd/include/constants/smallestposval.hpp>
#include <boost/simd/include/constants/maxexponent.hpp>
#include <boost/simd/include/constants/limitexponent.hpp>

#include <boost/simd/include/constants/one.hpp>
#include <boost/simd/include/constants/zero.hpp>
#include <boost/simd/include/constants/mone.hpp>
#include <boost/simd/include/constants/two.hpp>
#include <boost/simd/include/constants/four.hpp>
#include <boost/simd/include/constants/inf.hpp>
#include <boost/simd/include/constants/minf.hpp>
#include <boost/simd/include/constants/nan.hpp>

NT2_TEST_CASE_TPL ( ldexp_real,  BOOST_SIMD_SIMD_REAL_TYPES)
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

#ifndef BOOST_SIMD_NO_INVALIDS
  NT2_TEST_EQUAL(ldexp(boost::simd::Inf<vT>(),  Two<ivT>()), boost::simd::Inf<r_t>());
  NT2_TEST_EQUAL(ldexp(boost::simd::Minf<vT>(), Two<ivT>()), boost::simd::Minf<r_t>());
  NT2_TEST_EQUAL(ldexp(boost::simd::Nan<vT>(),  Two<ivT>()), boost::simd::Nan<r_t>());
#endif
  NT2_TEST_EQUAL(ldexp(boost::simd::Mone<vT>(), Two<ivT>()), -boost::simd::Four<r_t>());
  NT2_TEST_EQUAL(ldexp(boost::simd::One<vT>(),  Two<ivT>()), boost::simd::Four<r_t>());
  NT2_TEST_EQUAL(ldexp(boost::simd::Zero<vT>(), Two<ivT>()), boost::simd::Zero<r_t>());
  NT2_TEST_EQUAL(ldexp(boost::simd::One <vT>(), boost::simd::Minexponent<vT>()), boost::simd::Smallestposval<r_t>());
  NT2_TEST_EQUAL(ldexp(boost::simd::One<vT>()-boost::simd::Halfeps<vT>(),  boost::simd::Maxexponent<vT>()), boost::simd::Valmax<vT>()/Two<vT>());
  NT2_TEST_EQUAL(ldexp(boost::simd::One<vT>()-boost::simd::Halfeps<vT>(),  boost::simd::Limitexponent<vT>()), boost::simd::Valmax<vT>());
#ifndef BOOST_SIMD_NO_DENORMALS
  NT2_TEST_EQUAL(ldexp(boost::simd::One <vT>(), dec(boost::simd::Minexponent<vT>())), boost::simd::Smallestposval<vT>()/Two<vT>());
  NT2_TEST_EQUAL(ldexp(boost::simd::Two <vT>(), dec(boost::simd::Minexponent<vT>())), boost::simd::Smallestposval<vT>());
  NT2_TEST_EQUAL(ldexp(boost::simd::Two <vT>(), dec(dec(boost::simd::Minexponent<vT>()))), boost::simd::Smallestposval<vT>()/Two<vT>());
#endif
}
