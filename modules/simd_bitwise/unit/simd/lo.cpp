//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#define BOOST_SIMD_UNIT_MODULE "nt2 bitwise toolbox - lo/simd Mode"

//////////////////////////////////////////////////////////////////////////////
// unit test behavior of bitwise components in simd mode
//////////////////////////////////////////////////////////////////////////////
/// created  by jt the 18/02/2011
/// 
#include <boost/simd/toolbox/bitwise/include/lo.hpp>
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


BOOST_SIMD_TEST_CASE_TPL ( lo_real__1_0,  BOOST_SIMD_REAL_TYPES)
{
  using boost::simd::lo;
  using boost::simd::tag::lo_;
  using boost::simd::load; 
  using boost::simd::native;
  using boost::simd::meta::cardinal_of;
  typedef typename boost::dispatch::meta::as_integer<T,unsigned>::type ir_t;
  typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef typename boost::dispatch::meta::upgrade<T>::type   u_t;
  typedef native<T,ext_t>                        n_t;
  typedef n_t                                     vT;
  typedef typename boost::dispatch::meta::as_integer<T>::type iT;
  typedef native<iT,ext_t>                       ivT;
  typedef typename boost::dispatch::meta::call<lo_(vT)>::type r_t;
  typedef typename boost::dispatch::meta::call<lo_(T)>::type sr_t;
  typedef typename boost::dispatch::meta::scalar_of<r_t>::type ssr_t;
  double ulpd;
  ulpd=0.0;


  // specific values tests
  BOOST_SIMD_TEST_EQUAL(lo(boost::simd::Nan<vT>())[0], boost::simd::Mone<sr_t>());
  BOOST_SIMD_TEST_EQUAL(lo(boost::simd::One<vT>())[0], boost::simd::Zero<sr_t>());
  BOOST_SIMD_TEST_EQUAL(lo(boost::simd::Zero<vT>())[0], boost::simd::Zero<sr_t>());
} // end of test for real_

BOOST_SIMD_TEST_CASE_TPL ( lo_int64__1_0,  (boost::simd::int64_t)(boost::simd::uint64_t))
{
  using boost::simd::lo;
  using boost::simd::tag::lo_;
  using boost::simd::load; 
  using boost::simd::native;
  using boost::simd::meta::cardinal_of;
  typedef typename boost::dispatch::meta::as_integer<T,unsigned>::type ir_t;
  typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef typename boost::dispatch::meta::upgrade<T>::type   u_t;
  typedef native<T,ext_t>                        n_t;
  typedef n_t                                     vT;
  typedef typename boost::dispatch::meta::as_integer<T>::type iT;
  typedef native<iT,ext_t>                       ivT;
  typedef typename boost::dispatch::meta::call<lo_(vT)>::type r_t;
  typedef typename boost::dispatch::meta::call<lo_(T)>::type sr_t;
  typedef typename boost::dispatch::meta::scalar_of<r_t>::type ssr_t;
  double ulpd;
  ulpd=0.0;


  // specific values tests
  BOOST_SIMD_TEST_EQUAL(lo(boost::simd::One<vT>())[0], boost::simd::One<sr_t>());
  BOOST_SIMD_TEST_EQUAL(lo(boost::simd::Zero<vT>())[0], boost::simd::Zero<sr_t>());
} // end of test for int64_

BOOST_SIMD_TEST_CASE_TPL ( lo_int32__1_0,  (boost::simd::int32_t)(boost::simd::uint32_t))
{
  using boost::simd::lo;
  using boost::simd::tag::lo_;
  using boost::simd::load; 
  using boost::simd::native;
  using boost::simd::meta::cardinal_of;
  typedef typename boost::dispatch::meta::as_integer<T,unsigned>::type ir_t;
  typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef typename boost::dispatch::meta::upgrade<T>::type   u_t;
  typedef native<T,ext_t>                        n_t;
  typedef n_t                                     vT;
  typedef typename boost::dispatch::meta::as_integer<T>::type iT;
  typedef native<iT,ext_t>                       ivT;
  typedef typename boost::dispatch::meta::call<lo_(vT)>::type r_t;
  typedef typename boost::dispatch::meta::call<lo_(T)>::type sr_t;
  typedef typename boost::dispatch::meta::scalar_of<r_t>::type ssr_t;
  double ulpd;
  ulpd=0.0;


  // specific values tests
  BOOST_SIMD_TEST_EQUAL(lo(boost::simd::One<vT>())[0], boost::simd::One<sr_t>());
  BOOST_SIMD_TEST_EQUAL(lo(boost::simd::Zero<vT>())[0], boost::simd::Zero<sr_t>());
} // end of test for int32_

BOOST_SIMD_TEST_CASE_TPL ( lo_int16__1_0,  (boost::simd::int16_t)(boost::simd::uint16_t))
{
  using boost::simd::lo;
  using boost::simd::tag::lo_;
  using boost::simd::load; 
  using boost::simd::native;
  using boost::simd::meta::cardinal_of;
  typedef typename boost::dispatch::meta::as_integer<T,unsigned>::type ir_t;
  typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef typename boost::dispatch::meta::upgrade<T>::type   u_t;
  typedef native<T,ext_t>                        n_t;
  typedef n_t                                     vT;
  typedef typename boost::dispatch::meta::as_integer<T>::type iT;
  typedef native<iT,ext_t>                       ivT;
  typedef typename boost::dispatch::meta::call<lo_(vT)>::type r_t;
  typedef typename boost::dispatch::meta::call<lo_(T)>::type sr_t;
  typedef typename boost::dispatch::meta::scalar_of<r_t>::type ssr_t;
  double ulpd;
  ulpd=0.0;


  // specific values tests
  BOOST_SIMD_TEST_EQUAL(lo(boost::simd::One<vT>())[0], boost::simd::One<sr_t>());
  BOOST_SIMD_TEST_EQUAL(lo(boost::simd::Zero<vT>())[0], boost::simd::Zero<sr_t>());
} // end of test for int16_
