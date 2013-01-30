//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#define NT2_UNIT_MODULE "nt2 boost.simd.boolean toolbox - selsub/simd Mode"

//////////////////////////////////////////////////////////////////////////////
// unit test behavior of boost.simd.boolean components in simd mode
//////////////////////////////////////////////////////////////////////////////
/// created  by jt the 18/02/2011
///
#include <boost/simd/toolbox/boolean/include/functions/selsub.hpp>
#include <boost/simd/sdk/simd/native.hpp>
#include <boost/simd/toolbox/predicates/include/functions/is_nez.hpp>

#include <boost/type_traits/is_same.hpp>
#include <boost/dispatch/functor/meta/call.hpp>
#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <boost/simd/toolbox/constant/constant.hpp>
#include <boost/simd/sdk/memory/is_aligned.hpp>
#include <boost/simd/sdk/memory/aligned_type.hpp>
#include <boost/simd/include/functions/load.hpp>
#include <boost/simd/include/functions/is_nez.hpp>


NT2_TEST_CASE_TPL ( selsub_real__3_0,  BOOST_SIMD_SIMD_REAL_TYPES)
{
  using boost::simd::selsub;
  using boost::simd::tag::selsub_;
  using boost::simd::load;
  using boost::simd::native;
  using boost::simd::meta::cardinal_of;
  using boost::simd::logical;
  typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef typename boost::dispatch::meta::upgrade<T>::type   u_t;
  typedef native<T,ext_t>                        n_t;
  typedef n_t                                     vT;
  typedef typename boost::dispatch::meta::as_integer<T>::type iT;
  typedef native<iT,ext_t>                       ivT;
  typedef native<logical<T> ,ext_t>              vlT;
  typedef typename boost::dispatch::meta::call<selsub_(vlT,vT,vT)>::type r_t;
  typedef typename boost::simd::meta::scalar_of<r_t>::type sr_t;
  typedef typename boost::simd::meta::scalar_of<r_t>::type ssr_t;

  // specific values tests
  NT2_TEST_EQUAL(selsub(boost::simd::False<vlT>(),boost::simd::splat<vT>(1),boost::simd::splat<vT>(2))[0], T(1));
  NT2_TEST_EQUAL(selsub(boost::simd::True<vlT>(),boost::simd::splat<vT>(1),boost::simd::splat<vT>(2))[0], T(-1));
  NT2_TEST_EQUAL(selsub(boost::simd::True<vlT>(),boost::simd::Inf<vT>(),boost::simd::Inf<vT>())[0], boost::simd::Nan<sr_t>());
  NT2_TEST_EQUAL(selsub(boost::simd::True<vlT>(),boost::simd::One<vT>(), boost::simd::Inf<vT>())[0], boost::simd::Minf<sr_t>());
  NT2_TEST_EQUAL(selsub(boost::simd::True<vlT>(),boost::simd::Minf<vT>(),boost::simd::Minf<vT>())[0], boost::simd::Nan<sr_t>());
  NT2_TEST_EQUAL(selsub(boost::simd::True<vlT>(),boost::simd::Nan<vT>(),boost::simd::Nan<vT>())[0], boost::simd::Nan<sr_t>());
  NT2_TEST_EQUAL(selsub(boost::simd::True<vlT>(),boost::simd::Zero<vT>(),boost::simd::Zero<vT>())[0], boost::simd::Zero<sr_t>());
} // end of test for floating_

NT2_TEST_CASE_TPL ( selsub_signed_int__3_0,  BOOST_SIMD_SIMD_INTEGRAL_SIGNED_TYPES)
{
  using boost::simd::selsub;
  using boost::simd::tag::selsub_;
  using boost::simd::load;
  using boost::simd::native;
  using boost::simd::meta::cardinal_of;
  using boost::simd::logical;
  typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef typename boost::dispatch::meta::upgrade<T>::type   u_t;
  typedef native<T,ext_t>                        n_t;
  typedef n_t                                     vT;
  typedef typename boost::dispatch::meta::as_integer<T>::type iT;
  typedef native<iT,ext_t>                       ivT;
  typedef native<logical<T> ,ext_t>              vlT;
  typedef typename boost::dispatch::meta::call<selsub_(vlT,vT,vT)>::type r_t;
  typedef typename boost::simd::meta::scalar_of<r_t>::type sr_t;
  typedef typename boost::simd::meta::scalar_of<r_t>::type ssr_t;

  // specific values tests
  NT2_TEST_EQUAL(selsub(boost::simd::True<vlT>(),boost::simd::splat<vT>(4),boost::simd::splat<vT>(2))[0], T(2));
  NT2_TEST_EQUAL(selsub(boost::simd::False<vlT>(),boost::simd::splat<vT>(4),boost::simd::splat<vT>(2))[0], T(4));
  NT2_TEST_EQUAL(selsub(boost::simd::False<vlT>(), boost::simd::Zero<vT>(), boost::simd::Zero<vT>())[0], T(0));
} // end of test for signed_int_

NT2_TEST_CASE_TPL ( selsub_unsigned_int__3_0,  BOOST_SIMD_SIMD_UNSIGNED_TYPES)
{
  using boost::simd::selsub;
  using boost::simd::tag::selsub_;
  using boost::simd::load;
  using boost::simd::native;
  using boost::simd::meta::cardinal_of;
  using boost::simd::logical;
  typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef typename boost::dispatch::meta::upgrade<T>::type   u_t;
  typedef native<T,ext_t>                        n_t;
  typedef n_t                                     vT;
  typedef typename boost::dispatch::meta::as_integer<T>::type iT;
  typedef native<iT,ext_t>                       ivT;
  typedef native<logical<T> ,ext_t>              vlT;
  typedef typename boost::dispatch::meta::call<selsub_(vlT,vT,vT)>::type r_t;
  typedef typename boost::simd::meta::scalar_of<r_t>::type sr_t;
  typedef typename boost::simd::meta::scalar_of<r_t>::type ssr_t;

  // specific values tests
  NT2_TEST_EQUAL(selsub(boost::simd::True<vlT>(),boost::simd::splat<vT>(4),boost::simd::splat<vT>(2))[0], T(2));
  NT2_TEST_EQUAL(selsub(boost::simd::False<vlT>(),boost::simd::splat<vT>(4),boost::simd::splat<vT>(2))[0], T(4));
  NT2_TEST_EQUAL(selsub(boost::simd::False<vlT>(), boost::simd::Zero<vT>(), boost::simd::Zero<vT>())[0], T(0));
} // end of test for unsigned_int_
