//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#define NT2_UNIT_MODULE "nt2 boost.simd.swar toolbox - group/simd Mode"

//////////////////////////////////////////////////////////////////////////////
// unit test behavior of boost.simd.swar components in simd mode
//////////////////////////////////////////////////////////////////////////////
/// created  by jt the 24/02/2011
///
#include <boost/simd/toolbox/swar/include/functions/group.hpp>
#include <boost/simd/sdk/simd/native.hpp>
#include <boost/simd/include/functions/enumerate.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/dispatch/functor/meta/call.hpp>
#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <boost/simd/toolbox/constant/constant.hpp>
#include <boost/simd/sdk/memory/is_aligned.hpp>
#include <boost/simd/sdk/memory/aligned_type.hpp>
#include <boost/simd/include/functions/load.hpp>
#include <boost/simd/include/functions/divides.hpp>

NT2_TEST_CASE_TPL ( group_groupable__2_0, BOOST_SIMD_SIMD_GROUPABLE_TYPES)
{
  using boost::simd::group;
  using boost::simd::tag::group_;
  using boost::simd::load;
  using boost::simd::native;
  using boost::simd::meta::cardinal_of;
  using boost::simd::Two;
  using boost::simd::Valmax;
  using boost::simd::Valmin;
  using boost::simd::One;
  using boost::simd::Zero;
  using boost::simd::Inf;
  using boost::simd::Minf;
  typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef typename boost::dispatch::meta::upgrade<T>::type   u_t;
  typedef native<T,ext_t>                        n_t;
  typedef n_t                                     vT;
  typedef typename boost::dispatch::meta::as_integer<T>::type iT;
  typedef native<iT,ext_t>                       ivT;
  typedef typename boost::dispatch::meta::call<group_(vT,vT)>::type r_t;
  typedef typename boost::simd::meta::scalar_of<r_t>::type sr_t;
  typedef typename boost::simd::meta::scalar_of<r_t>::type ssr_t;

  // specific values tests
  NT2_TEST_EQUAL(group(One<vT>(),  One<vT>())[0],  One<sr_t>());
  NT2_TEST_EQUAL(group(Zero<vT>(), Zero<vT>())[0], Zero<sr_t>());
  NT2_TEST_EQUAL(group(Valmax<vT>()/Two<vT>(), Valmax<vT>()/Two<vT>())[0], Inf<sr_t>());
  NT2_TEST_EQUAL(group(Valmin<vT>()/Two<vT>(), Valmin<vT>()/Two<vT>())[0], Minf<sr_t>());
  NT2_TEST_EQUAL(group(Valmax<vT>(), Valmax<vT>())[0], Inf<sr_t>());
  NT2_TEST_EQUAL(group(Valmin<vT>(), Valmin<vT>())[0], Minf<sr_t>());
} // end of test for groupable_

NT2_TEST_CASE_TPL ( group_groupable__2_1,  BOOST_SIMD_SIMD_GROUPABLE_TYPES)
{
  using boost::simd::group;
  using boost::simd::tag::group_;
  using boost::simd::load;
  using boost::simd::native;
  using boost::simd::meta::cardinal_of;
  using boost::simd::Two;
  using boost::simd::Valmax;
  using boost::simd::Valmin;
  using boost::simd::One;
  using boost::simd::Zero;
  using boost::simd::Inf;
  using boost::simd::Minf;
  typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef typename boost::dispatch::meta::upgrade<T>::type   u_t;
  typedef native<T,ext_t>                        n_t;
  typedef n_t                                     vT;
  typedef typename boost::dispatch::meta::as_integer<T>::type iT;
  typedef native<iT,ext_t>                       ivT;
  typedef typename boost::dispatch::meta::call<group_(vT,vT)>::type r_t;
  typedef typename boost::simd::meta::scalar_of<r_t>::type sr_t;
  typedef typename boost::simd::meta::scalar_of<r_t>::type ssr_t;

  // specific values tests
  NT2_TEST_EQUAL(group(One<vT>(),  One<vT>())[1],  One<sr_t>());
  NT2_TEST_EQUAL(group(Zero<vT>(), Zero<vT>())[1], Zero<sr_t>());
  NT2_TEST_EQUAL(group(Valmax<vT>()/Two<vT>(), Valmax<vT>()/Two<vT>())[1], Inf<sr_t>());
  NT2_TEST_EQUAL(group(Valmin<vT>()/Two<vT>(), Valmin<vT>()/Two<vT>())[1], Minf<sr_t>());
  NT2_TEST_EQUAL(group(Valmax<vT>(), Valmax<vT>())[1], Inf<sr_t>());
  NT2_TEST_EQUAL(group(Valmin<vT>(), Valmin<vT>())[1], Minf<sr_t>());
} // end of test for groupable_

NT2_TEST_CASE_TPL ( group_groupable__3_1,  BOOST_SIMD_SIMD_GROUPABLE_TYPES)
{
  using boost::simd::group;
  using boost::simd::tag::group_;
  using boost::simd::load;
  using boost::simd::native;
  using boost::simd::meta::cardinal_of;
  using boost::simd::Two;
  using boost::simd::Valmax;
  using boost::simd::Valmin;
  using boost::simd::One;
  using boost::simd::Zero;
  using boost::simd::Inf;
  using boost::simd::Minf;
  typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef typename boost::dispatch::meta::upgrade<T>::type   u_t;
  typedef native<T,ext_t>                        n_t;
  typedef n_t                                     vT;
  typedef typename boost::dispatch::meta::as_integer<T>::type iT;
  typedef native<iT,ext_t>                       ivT;
  typedef typename boost::dispatch::meta::call<group_(vT,vT)>::type r_t;
  typedef typename boost::simd::meta::scalar_of<r_t>::type sr_t;
  typedef typename boost::simd::meta::scalar_of<r_t>::type ssr_t;

  // specific values tests

  size_t n = cardinal_of<vT>::value;
  for(size_t i=0; i < cardinal_of<vT>::value; i++)
  {
    NT2_TEST_EQUAL(group(boost::simd::enumerate<vT>(T(0)),  boost::simd::enumerate<vT>(T(n)))[i],  T(i));
  }
} // end of test for groupable_

NT2_TEST_CASE_TPL ( group_groupable__4_1,  (int32_t))
{
  using boost::simd::group;
  using boost::simd::tag::group_;
  using boost::simd::load;
  using boost::simd::native;
  using boost::simd::meta::cardinal_of;
  using boost::simd::Two;
  using boost::simd::Valmax;
  using boost::simd::Valmin;
  using boost::simd::One;
  using boost::simd::Zero;
  using boost::simd::Inf;
  using boost::simd::Minf;
  typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef typename boost::dispatch::meta::upgrade<T>::type   u_t;
  typedef native<T,ext_t>                        n_t;
  typedef n_t                                     vT;
  typedef typename boost::dispatch::meta::as_integer<T>::type iT;
  typedef native<iT,ext_t>                       ivT;
  typedef typename boost::dispatch::meta::call<group_(vT,vT)>::type r_t;
  typedef typename boost::simd::meta::scalar_of<r_t>::type sr_t;
  typedef typename boost::simd::meta::scalar_of<r_t>::type ssr_t;

  // specific values tests

  size_t n = cardinal_of<vT>::value;
  int32_t s = 32767 - n;
  for(size_t i=0; i < cardinal_of<vT>::value; i++)
  {
    NT2_TEST_EQUAL(group(boost::simd::enumerate<vT>(T(s)),  boost::simd::enumerate<vT>(T(s+n)))[i],  T(s+i));
  }
} // end of test for groupable_
