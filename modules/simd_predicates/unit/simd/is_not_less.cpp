//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#define BOOST_SIMD_UNIT_MODULE "nt2 predicates toolbox - is_not_less/simd Mode"

//////////////////////////////////////////////////////////////////////////////
// unit test behavior of predicates components in simd mode
//////////////////////////////////////////////////////////////////////////////
/// created  by jt the 21/02/2011
/// 
#include <boost/simd/toolbox/predicates/include/is_not_less.hpp>
#include <boost/simd/include/functions/ulpdist.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/dispatch/functor/meta/call.hpp>
#include <boost/simd/sdk/unit/tests.hpp>
#include <boost/simd/sdk/unit/module.hpp>
#include <boost/simd/sdk/memory/buffer.hpp>
#include <boost/simd/include/constants/real.hpp>
#include <boost/simd/include/constants/infinites.hpp>
#include <boost/simd/sdk/memory/is_aligned.hpp>
#include <boost/simd/sdk/memory/aligned_type.hpp>
#include <boost/simd/include/functions/load.hpp>


BOOST_SIMD_TEST_CASE_TPL ( is_not_less_real__2_0,  BOOST_SIMD_REAL_TYPES)
{
  using boost::simd::is_not_less;
  using boost::simd::tag::is_not_less_;
  using boost::simd::load; 
  using boost::simd::native;
  using boost::simd::meta::cardinal_of;
  typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef typename boost::dispatch::meta::upgrade<T>::type   u_t;
  typedef native<T,ext_t>                        n_t;
  typedef n_t                                     vT;
  typedef typename boost::dispatch::meta::as_integer<T>::type iT;
  typedef native<iT,ext_t>                       ivT;
  typedef typename boost::dispatch::meta::call<is_not_less_(vT,vT)>::type r_t;
  typedef typename boost::dispatch::meta::call<is_not_less_(T,T)>::type sr_t;
  typedef typename boost::dispatch::meta::scalar_of<r_t>::type ssr_t;
  double ulpd;
  ulpd=0.0;


  // specific values tests
  BOOST_SIMD_TEST_EQUAL(is_not_less(-boost::simd::Zero<vT>(), -boost::simd::Zero<vT>())[0]!=0, boost::simd::True<sr_t>());
  BOOST_SIMD_TEST_EQUAL(is_not_less(boost::simd::Half<vT>(), boost::simd::Half<vT>())[0]!=0, boost::simd::True<sr_t>());
  BOOST_SIMD_TEST_EQUAL(is_not_less(boost::simd::Inf<vT>(), boost::simd::Inf<vT>())[0]!=0, boost::simd::True<sr_t>());
  BOOST_SIMD_TEST_EQUAL(is_not_less(boost::simd::Minf<vT>(), boost::simd::Minf<vT>())[0]!=0, boost::simd::True<sr_t>());
  BOOST_SIMD_TEST_EQUAL(is_not_less(boost::simd::Mone<vT>(), boost::simd::Mone<vT>())[0]!=0, boost::simd::True<sr_t>());
  BOOST_SIMD_TEST_EQUAL(is_not_less(boost::simd::Nan<vT>(), boost::simd::Nan<vT>())[0]!=0, boost::simd::True<sr_t>());
  BOOST_SIMD_TEST_EQUAL(is_not_less(boost::simd::One<vT>(), boost::simd::One<vT>())[0]!=0, boost::simd::True<sr_t>());
  BOOST_SIMD_TEST_EQUAL(is_not_less(boost::simd::Quarter<vT>(), boost::simd::Quarter<vT>())[0]!=0, boost::simd::True<sr_t>());
  BOOST_SIMD_TEST_EQUAL(is_not_less(boost::simd::Two<vT>(), boost::simd::Two<vT>())[0]!=0, boost::simd::True<sr_t>());
  BOOST_SIMD_TEST_EQUAL(is_not_less(boost::simd::Zero<vT>(), boost::simd::Zero<vT>())[0]!=0, boost::simd::True<sr_t>());
} // end of test for real_
