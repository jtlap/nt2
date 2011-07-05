//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#define BOOST_SIMD_UNIT_MODULE "nt2 bitwise toolbox - firstbitset/simd Mode"

//////////////////////////////////////////////////////////////////////////////
// unit test behavior of bitwise components in simd mode
//////////////////////////////////////////////////////////////////////////////
/// created  by jt the 18/02/2011
/// 
#include <boost/simd/toolbox/bitwise/include/firstbitset.hpp>
#include <boost/simd/include/functions/ulpdist.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/simd/sdk/functor/meta/call.hpp>
#include <boost/simd/sdk/unit/tests.hpp>
#include <boost/simd/sdk/unit/module.hpp>
#include <boost/simd/sdk/memory/buffer.hpp>
#include <boost/simd/include/constants/real.hpp>
#include <boost/simd/include/constants/infinites.hpp>
#include <boost/simd/sdk/memory/is_aligned.hpp>
#include <boost/simd/sdk/memory/aligned_type.hpp>
#include <boost/simd/include/functions/load.hpp>


BOOST_SIMD_TEST_CASE_TPL ( firstbitset_float_1_0,  (float))
{
  using boost::simd::firstbitset;
  using boost::simd::tag::firstbitset_;
  using boost::simd::load; 
  using boost::simd::native;
  using boost::simd::meta::cardinal_of;
  typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef typename boost::simd::meta::upgrade<T>::type   u_t;
  typedef native<T,ext_t>                        n_t;
  typedef n_t                                     vT;
  typedef typename boost::simd::meta::as_integer<T>::type iT;
  typedef native<iT,ext_t>                       ivT;
  typedef typename boost::simd::meta::call<firstbitset_(vT)>::type r_t;
  typedef typename boost::simd::meta::call<firstbitset_(T)>::type sr_t;
  typedef typename boost::simd::meta::scalar_of<r_t>::type ssr_t;
  double ulpd;
  ulpd=0.0;


  // specific values tests
  BOOST_SIMD_TEST_EQUAL(firstbitset(boost::simd::Inf<vT>())[0], 8388608u);
  BOOST_SIMD_TEST_EQUAL(firstbitset(boost::simd::Minf<vT>())[0], 8388608u);
  BOOST_SIMD_TEST_EQUAL(firstbitset(boost::simd::Nan<vT>())[0], boost::simd::One<sr_t>());
  BOOST_SIMD_TEST_EQUAL(firstbitset(boost::simd::Signmask<vT>())[0], boost::simd::One<sr_t>()+boost::simd::Valmax<sr_t>()/2);
  BOOST_SIMD_TEST_EQUAL(firstbitset(boost::simd::Zero<vT>())[0], boost::simd::Zero<sr_t>());
} // end of test for float

BOOST_SIMD_TEST_CASE_TPL ( firstbitset_double_1_0,  (double))
{
  using boost::simd::firstbitset;
  using boost::simd::tag::firstbitset_;
  using boost::simd::load; 
  using boost::simd::native;
  using boost::simd::meta::cardinal_of;
  typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef typename boost::simd::meta::upgrade<T>::type   u_t;
  typedef native<T,ext_t>                        n_t;
  typedef n_t                                     vT;
  typedef typename boost::simd::meta::as_integer<T>::type iT;
  typedef native<iT,ext_t>                       ivT;
  typedef typename boost::simd::meta::call<firstbitset_(vT)>::type r_t;
  typedef typename boost::simd::meta::call<firstbitset_(T)>::type sr_t;
  typedef typename boost::simd::meta::scalar_of<r_t>::type ssr_t;
  double ulpd;
  ulpd=0.0;


  // specific values tests
  BOOST_SIMD_TEST_EQUAL(firstbitset(boost::simd::Inf<vT>())[0], 4503599627370496ull);
  BOOST_SIMD_TEST_EQUAL(firstbitset(boost::simd::Minf<vT>())[0], 4503599627370496ull);
  BOOST_SIMD_TEST_EQUAL(firstbitset(boost::simd::Nan<vT>())[0], boost::simd::One<sr_t>());
  BOOST_SIMD_TEST_EQUAL(firstbitset(boost::simd::Signmask<vT>())[0], boost::simd::One<sr_t>()+boost::simd::Valmax<sr_t>()/2);
  BOOST_SIMD_TEST_EQUAL(firstbitset(boost::simd::Zero<vT>())[0], boost::simd::Zero<sr_t>());
} // end of test for double

BOOST_SIMD_TEST_CASE_TPL ( firstbitset_signed_int__1_0,  BOOST_SIMD_INTEGRAL_SIGNED_TYPES)
{
  using boost::simd::firstbitset;
  using boost::simd::tag::firstbitset_;
  using boost::simd::load; 
  using boost::simd::native;
  using boost::simd::meta::cardinal_of;
  typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef typename boost::simd::meta::upgrade<T>::type   u_t;
  typedef native<T,ext_t>                        n_t;
  typedef n_t                                     vT;
  typedef typename boost::simd::meta::as_integer<T>::type iT;
  typedef native<iT,ext_t>                       ivT;
  typedef typename boost::simd::meta::call<firstbitset_(vT)>::type r_t;
  typedef typename boost::simd::meta::call<firstbitset_(T)>::type sr_t;
  typedef typename boost::simd::meta::scalar_of<r_t>::type ssr_t;
  double ulpd;
  ulpd=0.0;


  // specific values tests
  BOOST_SIMD_TEST_EQUAL(firstbitset(boost::simd::One<vT>())[0], boost::simd::One<sr_t>());
  BOOST_SIMD_TEST_EQUAL(firstbitset(boost::simd::Signmask<vT>())[0], boost::simd::One<sr_t>()+boost::simd::Valmax<sr_t>()/2);
  BOOST_SIMD_TEST_EQUAL(firstbitset(boost::simd::Zero<vT>())[0], boost::simd::Zero<sr_t>());
} // end of test for signed_int_

BOOST_SIMD_TEST_CASE_TPL ( firstbitset_unsigned_int__1_0,  BOOST_SIMD_UNSIGNED_TYPES)
{
  using boost::simd::firstbitset;
  using boost::simd::tag::firstbitset_;
  using boost::simd::load; 
  using boost::simd::native;
  using boost::simd::meta::cardinal_of;
  typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef typename boost::simd::meta::upgrade<T>::type   u_t;
  typedef native<T,ext_t>                        n_t;
  typedef n_t                                     vT;
  typedef typename boost::simd::meta::as_integer<T>::type iT;
  typedef native<iT,ext_t>                       ivT;
  typedef typename boost::simd::meta::call<firstbitset_(vT)>::type r_t;
  typedef typename boost::simd::meta::call<firstbitset_(T)>::type sr_t;
  typedef typename boost::simd::meta::scalar_of<r_t>::type ssr_t;
  double ulpd;
  ulpd=0.0;


  // specific values tests
  BOOST_SIMD_TEST_EQUAL(firstbitset(boost::simd::One<vT>())[0], boost::simd::One<sr_t>());
  BOOST_SIMD_TEST_EQUAL(firstbitset(boost::simd::Zero<vT>())[0], boost::simd::Zero<sr_t>());
} // end of test for unsigned_int_
