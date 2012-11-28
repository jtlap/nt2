//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#define NT2_UNIT_MODULE "nt2 reduction toolbox - hmsb/simd Mode"

//////////////////////////////////////////////////////////////////////////////
// unit test behavior of reduction components in simd mode
//////////////////////////////////////////////////////////////////////////////
/// created  by jt the 24/02/2011
/// 
#include <nt2/toolbox/reduction/include/functions/hmsb.hpp>
#include <nt2/include/functions/bits.hpp>
#include <nt2/include/functions/shri.hpp>

#include <boost/type_traits/is_same.hpp>
#include <boost/dispatch/functor/meta/call.hpp>
#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <boost/simd/toolbox/constant/constant.hpp>
#include <boost/dispatch/details/ignore_unused.hpp>
#include <boost/simd/sdk/memory/is_aligned.hpp>
#include <boost/simd/sdk/memory/aligned_type.hpp>
#include <boost/simd/include/functions/load.hpp>
#include <boost/simd/toolbox/constant/constant.hpp>
#include <boost/dispatch/details/ignore_unused.hpp>


NT2_TEST_CASE_TPL ( hmsb_real__1_0,  BOOST_SIMD_SIMD_REAL_TYPES)
{
  using boost::simd::hmsb;
  using boost::simd::tag::hmsb_;
  using boost::simd::load; 
  using boost::simd::native;
  using boost::simd::meta::cardinal_of;
  typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef typename boost::dispatch::meta::upgrade<T>::type   u_t;
  typedef native<T,ext_t>                        n_t;
  typedef n_t                                     vT;
  typedef typename boost::dispatch::meta::as_integer<T>::type iT;
  typedef native<iT,ext_t>                       ivT;
  typedef typename boost::dispatch::meta::call<hmsb_(vT)>::type r_t;
  typedef typename boost::simd::meta::scalar_of<r_t>::type sr_t;
  typedef typename boost::simd::meta::scalar_of<r_t>::type ssr_t;

  // specific values tests
  NT2_TEST_EQUAL(hmsb(boost::simd::Allbits<vT>()), sr_t((1ull << boost::simd::meta::cardinal_of<vT>::value) - 1));
  NT2_TEST_EQUAL(hmsb(boost::simd::Inf<vT>()), boost::simd::Zero<sr_t>());
  NT2_TEST_EQUAL(hmsb(boost::simd::Minf<vT>()), sr_t(boost::simd::shri(boost::simd::Mone<boost::simd::int32_t>(),32-boost::simd::meta::cardinal_of<vT>::value)));
  NT2_TEST_EQUAL(hmsb(boost::simd::Mone<vT>()), sr_t(boost::simd::shri(boost::simd::Mone<boost::simd::int32_t>(),32-boost::simd::meta::cardinal_of<vT>::value)));
  NT2_TEST_EQUAL(hmsb(boost::simd::Nan<vT>()),  sr_t(boost::simd::shri(boost::simd::Mone<boost::simd::int32_t>() ,32-boost::simd::meta::cardinal_of<vT>::value)));
  NT2_TEST_EQUAL(hmsb(boost::simd::One<vT>()), boost::simd::Zero<sr_t>());
  NT2_TEST_EQUAL(hmsb(boost::simd::Signmask<vT>()), sr_t((1ull << boost::simd::meta::cardinal_of<vT>::value) - 1));
  NT2_TEST_EQUAL(hmsb(boost::simd::Zero<vT>()), boost::simd::Zero<sr_t>());
} // end of test for real_

NT2_TEST_CASE_TPL ( hmsb_signed_int__1_0,  BOOST_SIMD_SIMD_INTEGRAL_SIGNED_TYPES)
{
  using boost::simd::hmsb;
  using boost::simd::tag::hmsb_;
  using boost::simd::load; 
  using boost::simd::native;
  using boost::simd::meta::cardinal_of;
  typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef typename boost::dispatch::meta::upgrade<T>::type   u_t;
  typedef native<T,ext_t>                        n_t;
  typedef n_t                                     vT;
  typedef typename boost::dispatch::meta::as_integer<T>::type iT;
  typedef native<iT,ext_t>                       ivT;
  typedef typename boost::dispatch::meta::call<hmsb_(vT)>::type r_t;
  typedef typename boost::simd::meta::scalar_of<r_t>::type sr_t;
  typedef typename boost::simd::meta::scalar_of<r_t>::type ssr_t;

  // specific values tests
  NT2_TEST_EQUAL(hmsb(boost::simd::Allbits<vT>()), sr_t((1ull << boost::simd::meta::cardinal_of<vT>::value) - 1));
  NT2_TEST_EQUAL(hmsb(boost::simd::One<vT>()), boost::simd::Zero<sr_t>());
  NT2_TEST_EQUAL(hmsb(boost::simd::Signmask<vT>()), sr_t((1ull << boost::simd::meta::cardinal_of<vT>::value) - 1));
  NT2_TEST_EQUAL(hmsb(boost::simd::Zero<vT>()), boost::simd::Zero<sr_t>());
} // end of test for signed_int_

NT2_TEST_CASE_TPL ( hmsb_unsigned_int__1_0,  BOOST_SIMD_SIMD_UNSIGNED_TYPES)
{
  using boost::simd::hmsb;
  using boost::simd::tag::hmsb_;
  using boost::simd::load; 
  using boost::simd::native;
  using boost::simd::meta::cardinal_of;
  typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef typename boost::dispatch::meta::upgrade<T>::type   u_t;
  typedef native<T,ext_t>                        n_t;
  typedef n_t                                     vT;
  typedef typename boost::dispatch::meta::as_integer<T>::type iT;
  typedef native<iT,ext_t>                       ivT;
  typedef typename boost::dispatch::meta::call<hmsb_(vT)>::type r_t;
  typedef typename boost::simd::meta::scalar_of<r_t>::type sr_t;
  typedef typename boost::simd::meta::scalar_of<r_t>::type ssr_t;

  // specific values tests
  NT2_TEST_EQUAL(hmsb(boost::simd::Allbits<vT>()), sr_t((1ull << boost::simd::meta::cardinal_of<vT>::value) - 1));
  NT2_TEST_EQUAL(hmsb(boost::simd::One<vT>()), boost::simd::Zero<sr_t>());
  NT2_TEST_EQUAL(hmsb(boost::simd::Zero<vT>()), boost::simd::Zero<sr_t>());
} // end of test for unsigned_int_
