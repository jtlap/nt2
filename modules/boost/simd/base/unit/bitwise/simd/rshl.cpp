//==============================================================================
//         Copyright 2003 - 2013   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <boost/simd/bitwise/include/functions/rshl.hpp>

#include <boost/dispatch/functor/meta/call.hpp>
#include <boost/simd/sdk/simd/native.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <boost/simd/sdk/config.hpp>
#include <boost/simd/sdk/simd/io.hpp>

#include <boost/simd/include/constants/mone.hpp>
#include <boost/simd/include/constants/one.hpp>
#include <boost/simd/include/constants/three.hpp>
#include <boost/simd/include/constants/two.hpp>
#include <boost/simd/include/constants/four.hpp>
#include <boost/simd/include/constants/zero.hpp>
#include <boost/simd/include/constants/valmin.hpp>

NT2_TEST_CASE_TPL ( rshl_ui_1,  BOOST_SIMD_SIMD_UNSIGNED_TYPES)
{
  using boost::simd::rshl;
  using boost::simd::tag::rshl_;
  using boost::simd::native;
  typedef BOOST_SIMD_DEFAULT_EXTENSION                          ext_t;
  typedef native<T,ext_t>                                          vT;
  typedef typename boost::dispatch::meta::as_integer<T>::type      iT;
  typedef typename boost::dispatch::meta::call<rshl_(vT,iT)>::type r_t;

  // specific values tests
  NT2_TEST_EQUAL(rshl(boost::simd::Two<vT>(),1), boost::simd::Four<r_t>());
  NT2_TEST_EQUAL(rshl(boost::simd::One<vT>(),1), boost::simd::Two<r_t>());
  NT2_TEST_EQUAL(rshl(boost::simd::Zero<vT>(),1), boost::simd::Zero<r_t>());
  NT2_TEST_EQUAL(rshl(boost::simd::Two<vT>(),-1), boost::simd::One<r_t>());
  NT2_TEST_EQUAL(rshl(boost::simd::One<vT>(),-1), boost::simd::Zero<r_t>());
  NT2_TEST_EQUAL(rshl(boost::simd::Zero<vT>(),-1), boost::simd::Zero<r_t>());


} // end of test for unsigned_int_

NT2_TEST_CASE_TPL ( rshl_si_1,  BOOST_SIMD_SIMD_INTEGRAL_SIGNED_TYPES)
{
  using boost::simd::rshl;
  using boost::simd::tag::rshl_;
  using boost::simd::native;
  typedef BOOST_SIMD_DEFAULT_EXTENSION                          ext_t;
  typedef native<T,ext_t>                                          vT;
  typedef typename boost::dispatch::meta::as_integer<T>::type      iT;
  typedef typename boost::dispatch::meta::call<rshl_(vT,iT)>::type r_t;

  // specific values tests
  NT2_TEST_EQUAL(rshl(boost::simd::Two<vT>(),-1), boost::simd::One<r_t>());
  NT2_TEST_EQUAL(rshl(boost::simd::Mone<vT>(),-int(sizeof(T)*8-1)), boost::simd::One<r_t>());
  NT2_TEST_EQUAL(rshl(boost::simd::Mone<vT>(),-int(sizeof(T)*8-2)), boost::simd::Three<r_t>());
  NT2_TEST_EQUAL(rshl(boost::simd::One<vT>(),-1), boost::simd::Zero<r_t>());
  NT2_TEST_EQUAL(rshl(boost::simd::Zero<vT>(),-1), boost::simd::Zero<r_t>());
  NT2_TEST_EQUAL(rshl(boost::simd::Two<vT>(),1), boost::simd::Four<r_t>());
  NT2_TEST_EQUAL(rshl(boost::simd::One<vT>(),1), boost::simd::Two<r_t>());
  NT2_TEST_EQUAL(rshl(boost::simd::Zero<vT>(),1), boost::simd::Zero<r_t>());
  NT2_TEST_EQUAL(rshl(boost::simd::Mone<vT>(),(sizeof(T)*8-1)), boost::simd::Valmin<r_t>());
} // end of test for unsigned_int_

