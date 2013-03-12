//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/toolbox/reduction/include/functions/hmsb.hpp>
#include <boost/simd/sdk/simd/native.hpp>
#include <boost/simd/sdk/simd/logical.hpp>
#include <nt2/include/functions/bits.hpp>
#include <nt2/include/functions/shri.hpp>

#include <boost/dispatch/functor/meta/call.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/toolbox/constant/constant.hpp>

NT2_TEST_CASE_TPL ( hmsb_real__1_0,  BOOST_SIMD_SIMD_REAL_TYPES)
{
  using nt2::hmsb;
  using nt2::tag::hmsb_;
  using boost::simd::native;
  using boost::simd::meta::cardinal_of;
  typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef native<T,ext_t>                        vT;
  typedef typename boost::dispatch::meta::call<hmsb_(vT)>::type r_t;

  // specific values tests
  NT2_TEST_EQUAL(hmsb(nt2::Allbits<vT>()), r_t((1ull << cardinal_of<vT>::value) - 1));
  NT2_TEST_EQUAL(hmsb(nt2::Inf<vT>()), nt2::Zero<r_t>());
  NT2_TEST_EQUAL(hmsb(nt2::Minf<vT>()), r_t(nt2::shri(nt2::Mone<nt2::int32_t>(),32-cardinal_of<vT>::value)));
  NT2_TEST_EQUAL(hmsb(nt2::Mone<vT>()), r_t(nt2::shri(nt2::Mone<nt2::int32_t>(),32-cardinal_of<vT>::value)));
  NT2_TEST_EQUAL(hmsb(nt2::Nan<vT>()), r_t(nt2::shri(nt2::Mone<nt2::int32_t>(),32-cardinal_of<vT>::value)));
  NT2_TEST_EQUAL(hmsb(nt2::One<vT>()), nt2::Zero<r_t>());
  NT2_TEST_EQUAL(hmsb(nt2::Signmask<vT>()), r_t((1ull << cardinal_of<vT>::value) - 1));
  NT2_TEST_EQUAL(hmsb(nt2::Zero<vT>()), nt2::Zero<r_t>());
} // end of test for real_

NT2_TEST_CASE_TPL ( hmsb_signed_int__1_0,  BOOST_SIMD_SIMD_INTEGRAL_SIGNED_TYPES)
{
  using nt2::hmsb;
  using nt2::tag::hmsb_;
  using boost::simd::native;
  using boost::simd::meta::cardinal_of;
  typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef native<T,ext_t>                        vT;
  typedef typename boost::dispatch::meta::call<hmsb_(vT)>::type r_t;

  // specific values tests
  NT2_TEST_EQUAL(hmsb(nt2::Allbits<vT>()), r_t((1ull << cardinal_of<vT>::value) - 1));
  NT2_TEST_EQUAL(hmsb(nt2::One<vT>()), nt2::Zero<r_t>());
  NT2_TEST_EQUAL(hmsb(nt2::Signmask<vT>()), r_t((1ull << cardinal_of<vT>::value) - 1));
  NT2_TEST_EQUAL(hmsb(nt2::Zero<vT>()), nt2::Zero<r_t>());
} // end of test for signed_int_

NT2_TEST_CASE_TPL ( hmsb_unsigned_int__1_0,  BOOST_SIMD_SIMD_UNSIGNED_TYPES)
{
  using nt2::hmsb;
  using nt2::tag::hmsb_;
  using boost::simd::native;
  using boost::simd::meta::cardinal_of;
  typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef native<T,ext_t>                        vT;
  typedef typename boost::dispatch::meta::call<hmsb_(vT)>::type r_t;

  // specific values tests
  NT2_TEST_EQUAL(hmsb(nt2::Allbits<vT>()), r_t((1ull << cardinal_of<vT>::value) - 1));
  NT2_TEST_EQUAL(hmsb(nt2::One<vT>()), nt2::Zero<r_t>());
  NT2_TEST_EQUAL(hmsb(nt2::Zero<vT>()), nt2::Zero<r_t>());
} // end of test for unsigned_int_

NT2_TEST_CASE_TPL ( hmsb_logical, BOOST_SIMD_SIMD_TYPES)
{
  using nt2::hmsb;
  using nt2::tag::hmsb_;
  using boost::simd::native;
  using boost::simd::logical;
  using boost::simd::meta::cardinal_of;
  typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef native<logical<T>,ext_t>                          vT;
  typedef typename boost::dispatch::meta::call<hmsb_(vT)>::type r_t;

  // specific values tests
  NT2_TEST_EQUAL(hmsb(nt2::True<vT>())  , r_t((1ull << cardinal_of<vT>::value) - 1));
  NT2_TEST_EQUAL(hmsb(nt2::False<vT>()) , nt2::Zero<r_t>());
}
