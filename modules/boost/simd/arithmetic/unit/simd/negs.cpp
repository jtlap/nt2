//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#define BOOST_SIMD_UNIT_MODULE "nt2 arithmetic toolbox - negs/simd Mode"

//////////////////////////////////////////////////////////////////////////////
// unit test behavior of arithmetic components in simd mode
//////////////////////////////////////////////////////////////////////////////
/// created by jt the 30/11/2010
/// 
#include <boost/simd/toolbox/arithmetic/include/negs.hpp>
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


BOOST_SIMD_TEST_CASE_TPL ( negs_real__1_0,  BOOST_SIMD_REAL_TYPES)
{
  using boost::simd::negs;
  using boost::simd::tag::negs_;
  using boost::simd::load; 
  using boost::simd::native;
  using boost::simd::meta::cardinal_of;
  typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef typename boost::dispatch::meta::upgrade<T>::type   u_t;
  typedef native<T,ext_t>                        n_t;
  typedef n_t                                     vT;
  typedef typename boost::dispatch::meta::as_integer<T>::type iT;
  typedef native<iT,ext_t>                       ivT;
  typedef typename boost::dispatch::meta::call<negs_(vT)>::type r_t;
  typedef typename boost::dispatch::meta::call<negs_(T)>::type sr_t;
  typedef typename boost::dispatch::meta::scalar_of<r_t>::type ssr_t;
  double ulpd;
  ulpd=0.0;


  // specific values tests
  BOOST_SIMD_TEST_EQUAL(negs(boost::simd::splat<vT>(100))[0], T(-100));
  BOOST_SIMD_TEST_EQUAL(negs(boost::simd::Inf<vT>())[0], boost::simd::Minf<T>());
  BOOST_SIMD_TEST_EQUAL(negs(boost::simd::Minf<vT>())[0], boost::simd::Inf<T>());
  BOOST_SIMD_TEST_EQUAL(negs(boost::simd::Mone<vT>())[0], boost::simd::One<T>());
  BOOST_SIMD_TEST_EQUAL(negs(boost::simd::Nan<vT>())[0], boost::simd::Nan<T>());
  BOOST_SIMD_TEST_EQUAL(negs(boost::simd::One<vT>())[0], boost::simd::Mone<T>());
  BOOST_SIMD_TEST_EQUAL(negs(boost::simd::Valmax<vT>())[0], boost::simd::Valmin<T>());
  BOOST_SIMD_TEST_EQUAL(negs(boost::simd::Valmin<vT>())[0], boost::simd::Valmax<T>());
  BOOST_SIMD_TEST_EQUAL(negs(boost::simd::Zero<vT>())[0], boost::simd::Zero<T>());
} // end of test for real_

BOOST_SIMD_TEST_CASE_TPL ( negs_signed_int__1_0,  BOOST_SIMD_INTEGRAL_SIGNED_TYPES)
{
  using boost::simd::negs;
  using boost::simd::tag::negs_;
  using boost::simd::load; 
  using boost::simd::native;
  using boost::simd::meta::cardinal_of;
  typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef typename boost::dispatch::meta::upgrade<T>::type   u_t;
  typedef native<T,ext_t>                        n_t;
  typedef n_t                                     vT;
  typedef typename boost::dispatch::meta::as_integer<T>::type iT;
  typedef native<iT,ext_t>                       ivT;
  typedef typename boost::dispatch::meta::call<negs_(vT)>::type r_t;
  typedef typename boost::dispatch::meta::call<negs_(T)>::type sr_t;
  typedef typename boost::dispatch::meta::scalar_of<r_t>::type ssr_t;
  double ulpd;
  ulpd=0.0;


  // specific values tests
  BOOST_SIMD_TEST_EQUAL(negs(boost::simd::splat<vT>(100))[0], T(-100));
  BOOST_SIMD_TEST_EQUAL(negs(boost::simd::Mone<vT>())[0], boost::simd::One<T>());
  BOOST_SIMD_TEST_EQUAL(negs(boost::simd::One<vT>())[0], boost::simd::Mone<T>());
  BOOST_SIMD_TEST_EQUAL(negs(boost::simd::Valmax<vT>())[0], -boost::simd::Valmax<T>());
  BOOST_SIMD_TEST_EQUAL(negs(boost::simd::Valmin<vT>())[0], boost::simd::Valmax<T>());
  BOOST_SIMD_TEST_EQUAL(negs(boost::simd::Zero<vT>())[0], boost::simd::Zero<T>());
} // end of test for signed_int_
