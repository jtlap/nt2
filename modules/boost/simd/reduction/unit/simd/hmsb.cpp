//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#define NT2_UNIT_MODULE "nt2 boost.simd.reduction toolbox - hmsb/simd Mode"

//////////////////////////////////////////////////////////////////////////////
// unit test behavior of boost.simd.reduction components in simd mode
//////////////////////////////////////////////////////////////////////////////
/// created  by jt the 24/02/2011
///
#include <boost/simd/toolbox/reduction/include/functions/hmsb.hpp>
#include <boost/simd/sdk/simd/native.hpp>
#include <boost/simd/include/functions/bits.hpp>
#include <boost/simd/include/functions/shri.hpp>

#include <boost/dispatch/functor/meta/call.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <boost/simd/toolbox/constant/constant.hpp>

NT2_TEST_CASE_TPL ( hmsb_real__1_0,  BOOST_SIMD_SIMD_REAL_TYPES)
{
  using boost::simd::hmsb;
  using boost::simd::tag::hmsb_;
  using boost::simd::native;
  using boost::simd::meta::cardinal_of;
  typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef native<T,ext_t>                        vT;
  typedef typename boost::dispatch::meta::call<hmsb_(vT)>::type r_t;

  // specific values tests
  NT2_TEST_EQUAL(hmsb(boost::simd::Allbits<vT>()), r_t((1ull << boost::simd::meta::cardinal_of<vT>::value) - 1));
  NT2_TEST_EQUAL(hmsb(boost::simd::Inf<vT>()), boost::simd::Zero<r_t>());
  NT2_TEST_EQUAL(hmsb(boost::simd::Minf<vT>()), r_t(boost::simd::shri(boost::simd::Mone<boost::simd::int32_t>(),32-boost::simd::meta::cardinal_of<vT>::value)));
  NT2_TEST_EQUAL(hmsb(boost::simd::Mone<vT>()), r_t(boost::simd::shri(boost::simd::Mone<boost::simd::int32_t>(),32-boost::simd::meta::cardinal_of<vT>::value)));
  NT2_TEST_EQUAL(hmsb(boost::simd::Nan<vT>()), r_t(boost::simd::shri(boost::simd::Mone<boost::simd::int32_t>(),32-boost::simd::meta::cardinal_of<vT>::value)));
  NT2_TEST_EQUAL(hmsb(boost::simd::One<vT>()), boost::simd::Zero<r_t>());
  NT2_TEST_EQUAL(hmsb(boost::simd::Signmask<vT>()), r_t((1ull << boost::simd::meta::cardinal_of<vT>::value) - 1));
  NT2_TEST_EQUAL(hmsb(boost::simd::Zero<vT>()), boost::simd::Zero<r_t>());
} // end of test for real_

NT2_TEST_CASE_TPL ( hmsb_signed_int__1_0,  BOOST_SIMD_SIMD_INTEGRAL_SIGNED_TYPES)
{
  using boost::simd::hmsb;
  using boost::simd::tag::hmsb_;
  using boost::simd::native;
  using boost::simd::meta::cardinal_of;
  typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef native<T,ext_t>                        vT;
  typedef typename boost::dispatch::meta::call<hmsb_(vT)>::type r_t;

  // specific values tests
  NT2_TEST_EQUAL(hmsb(boost::simd::Allbits<vT>()), r_t((1ull << boost::simd::meta::cardinal_of<vT>::value) - 1));
  NT2_TEST_EQUAL(hmsb(boost::simd::One<vT>()), boost::simd::Zero<r_t>());
  NT2_TEST_EQUAL(hmsb(boost::simd::Signmask<vT>()), r_t((1ull << boost::simd::meta::cardinal_of<vT>::value) - 1));
  NT2_TEST_EQUAL(hmsb(boost::simd::Zero<vT>()), boost::simd::Zero<r_t>());
} // end of test for signed_int_

NT2_TEST_CASE_TPL ( hmsb_unsigned_int__1_0,  BOOST_SIMD_SIMD_UNSIGNED_TYPES)
{
  using boost::simd::hmsb;
  using boost::simd::tag::hmsb_;
  using boost::simd::native;
  using boost::simd::meta::cardinal_of;
  typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef native<T,ext_t>                        vT;
  typedef typename boost::dispatch::meta::call<hmsb_(vT)>::type r_t;

  // specific values tests
  NT2_TEST_EQUAL(hmsb(boost::simd::Allbits<vT>()), r_t((1ull << boost::simd::meta::cardinal_of<vT>::value) - 1));
  NT2_TEST_EQUAL(hmsb(boost::simd::One<vT>()), boost::simd::Zero<r_t>());
  NT2_TEST_EQUAL(hmsb(boost::simd::Zero<vT>()), boost::simd::Zero<r_t>());
} // end of test for unsigned_int_

NT2_TEST_CASE_TPL ( hmsb_logical, BOOST_SIMD_SIMD_TYPES)
{
  using boost::simd::hmsb;
  using boost::simd::tag::hmsb_;
  using boost::simd::native;
  using boost::simd::logical;
  using boost::simd::meta::cardinal_of;
  typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef native<logical<T>,ext_t>                          vT;
  typedef typename boost::dispatch::meta::call<hmsb_(vT)>::type r_t;

  // specific values tests
  NT2_TEST_EQUAL(hmsb(boost::simd::True<vT>())  , r_t((1ull << boost::simd::meta::cardinal_of<vT>::value) - 1));
  NT2_TEST_EQUAL(hmsb(boost::simd::False<vT>()) , boost::simd::Zero<r_t>());
}
