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
#include <nt2/include/functions/ulpdist.hpp>
#include <boost/simd/include/functions/bits.hpp>
#include <boost/simd/include/functions/shri.hpp>

#include <boost/type_traits/is_same.hpp>
#include <nt2/sdk/functor/meta/call.hpp>
#include <nt2/sdk/meta/as_integer.hpp>
#include <nt2/sdk/meta/as_real.hpp>
#include <nt2/sdk/meta/as_signed.hpp>
#include <nt2/sdk/meta/upgrade.hpp>
#include <nt2/sdk/meta/downgrade.hpp>
#include <nt2/sdk/meta/scalar_of.hpp>
#include <nt2/sdk/meta/floating.hpp>
#include <nt2/sdk/meta/arithmetic.hpp>
#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/memory/buffer.hpp>
#include <nt2/toolbox/constant/constant.hpp>
#include <nt2/sdk/meta/cardinal_of.hpp>
#include <nt2/include/functions/splat.hpp>
#include <nt2/sdk/memory/is_aligned.hpp>
#include <nt2/sdk/memory/aligned_type.hpp>
#include <nt2/include/functions/load.hpp>
#include <nt2/toolbox/constant/constant.hpp>


NT2_TEST_CASE_TPL ( hmsb_real__1_0,  NT2_SIMD_REAL_TYPES)
{
  using nt2::hmsb;
  using nt2::tag::hmsb_;
  using nt2::load; 
  using boost::simd::native;
  using nt2::meta::cardinal_of;
  typedef NT2_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef typename nt2::meta::upgrade<T>::type   u_t;
  typedef native<T,ext_t>                        n_t;
  typedef n_t                                     vT;
  typedef typename nt2::meta::as_integer<T>::type iT;
  typedef native<iT,ext_t>                       ivT;
  typedef typename nt2::meta::call<hmsb_(vT)>::type r_t;
  typedef typename nt2::meta::call<hmsb_(T)>::type sr_t;
  typedef typename nt2::meta::scalar_of<r_t>::type ssr_t;
  double ulpd;
  ulpd=0.0;


  // specific values tests
  NT2_TEST_EQUAL(hmsb(boost::simd::Allbits<vT>()), sr_t((1ul << boost::simd::meta::cardinal_of<vT>::value) - 1));
  NT2_TEST_EQUAL(hmsb(boost::simd::Inf<vT>()), boost::simd::Zero<sr_t>());
  NT2_TEST_EQUAL(hmsb(boost::simd::Minf<vT>()), boost::simd::shri(boost::simd::Mone<boost::simd::int32_t>(),int(32-boost::simd::meta::cardinal_of<vT>::value)));
  NT2_TEST_EQUAL(hmsb(boost::simd::Mone<vT>()), boost::simd::shri(boost::simd::Mone<boost::simd::int32_t>(),int(32-boost::simd::meta::cardinal_of<vT>::value)));
  NT2_TEST_EQUAL(hmsb(boost::simd::Nan<vT>()), boost::simd::shri(boost::simd::Mone<boost::simd::int32_t>(),int(32-boost::simd::meta::cardinal_of<vT>::value)));
  NT2_TEST_EQUAL(hmsb(boost::simd::One<vT>()), boost::simd::Zero<sr_t>());
  NT2_TEST_EQUAL(hmsb(boost::simd::Signmask<vT>()), sr_t((1ul << boost::simd::meta::cardinal_of<vT>::value) - 1));
  NT2_TEST_EQUAL(hmsb(boost::simd::Zero<vT>()), boost::simd::Zero<sr_t>());
} // end of test for real_

NT2_TEST_CASE_TPL ( hmsb_uint64_t_1_0,  (nt2::uint64_t))
{
  using nt2::hmsb;
  using nt2::tag::hmsb_;
  using nt2::load; 
  using boost::simd::native;
  using nt2::meta::cardinal_of;
  typedef NT2_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef typename nt2::meta::upgrade<T>::type   u_t;
  typedef native<T,ext_t>                        n_t;
  typedef n_t                                     vT;
  typedef typename nt2::meta::as_integer<T>::type iT;
  typedef native<iT,ext_t>                       ivT;
  typedef typename nt2::meta::call<hmsb_(vT)>::type r_t;
  typedef typename nt2::meta::call<hmsb_(T)>::type sr_t;
  typedef typename nt2::meta::scalar_of<r_t>::type ssr_t;
  double ulpd;
  ulpd=0.0;


  // specific values tests
  NT2_TEST_EQUAL(hmsb(boost::simd::Allbits<vT>()), sr_t((1ul << boost::simd::meta::cardinal_of<vT>::value) - 1));
  NT2_TEST_EQUAL(hmsb(boost::simd::One<vT>()), boost::simd::Zero<sr_t>());
  NT2_TEST_EQUAL(hmsb(boost::simd::Zero<vT>()), boost::simd::Zero<sr_t>());
} // end of test for uint64_t

NT2_TEST_CASE_TPL ( hmsb_int64_t_1_0,  (nt2::int64_t))
{
  using nt2::hmsb;
  using nt2::tag::hmsb_;
  using nt2::load; 
  using boost::simd::native;
  using nt2::meta::cardinal_of;
  typedef NT2_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef typename nt2::meta::upgrade<T>::type   u_t;
  typedef native<T,ext_t>                        n_t;
  typedef n_t                                     vT;
  typedef typename nt2::meta::as_integer<T>::type iT;
  typedef native<iT,ext_t>                       ivT;
  typedef typename nt2::meta::call<hmsb_(vT)>::type r_t;
  typedef typename nt2::meta::call<hmsb_(T)>::type sr_t;
  typedef typename nt2::meta::scalar_of<r_t>::type ssr_t;
  double ulpd;
  ulpd=0.0;


  // specific values tests
  NT2_TEST_EQUAL(hmsb(boost::simd::Allbits<vT>()), sr_t((1ul << boost::simd::meta::cardinal_of<vT>::value) - 1));
  NT2_TEST_EQUAL(hmsb(boost::simd::One<vT>()), boost::simd::Zero<sr_t>());
  NT2_TEST_EQUAL(hmsb(boost::simd::Signmask<vT>()), sr_t((1ul << boost::simd::meta::cardinal_of<vT>::value) - 1));
  NT2_TEST_EQUAL(hmsb(boost::simd::Zero<vT>()), boost::simd::Zero<sr_t>());
} // end of test for int64_t

NT2_TEST_CASE_TPL ( hmsb_uint32_t_1_0,  (nt2::uint32_t))
{
  using nt2::hmsb;
  using nt2::tag::hmsb_;
  using nt2::load; 
  using boost::simd::native;
  using nt2::meta::cardinal_of;
  typedef NT2_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef typename nt2::meta::upgrade<T>::type   u_t;
  typedef native<T,ext_t>                        n_t;
  typedef n_t                                     vT;
  typedef typename nt2::meta::as_integer<T>::type iT;
  typedef native<iT,ext_t>                       ivT;
  typedef typename nt2::meta::call<hmsb_(vT)>::type r_t;
  typedef typename nt2::meta::call<hmsb_(T)>::type sr_t;
  typedef typename nt2::meta::scalar_of<r_t>::type ssr_t;
  double ulpd;
  ulpd=0.0;


  // specific values tests
  NT2_TEST_EQUAL(hmsb(boost::simd::Allbits<vT>()), sr_t((1ul << boost::simd::meta::cardinal_of<vT>::value) - 1));
  NT2_TEST_EQUAL(hmsb(boost::simd::One<vT>()), boost::simd::Zero<sr_t>());
  NT2_TEST_EQUAL(hmsb(boost::simd::Zero<vT>()), boost::simd::Zero<sr_t>());
} // end of test for uint32_t

NT2_TEST_CASE_TPL ( hmsb_int32_t_1_0,  (nt2::int32_t))
{
  using nt2::hmsb;
  using nt2::tag::hmsb_;
  using nt2::load; 
  using boost::simd::native;
  using nt2::meta::cardinal_of;
  typedef NT2_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef typename nt2::meta::upgrade<T>::type   u_t;
  typedef native<T,ext_t>                        n_t;
  typedef n_t                                     vT;
  typedef typename nt2::meta::as_integer<T>::type iT;
  typedef native<iT,ext_t>                       ivT;
  typedef typename nt2::meta::call<hmsb_(vT)>::type r_t;
  typedef typename nt2::meta::call<hmsb_(T)>::type sr_t;
  typedef typename nt2::meta::scalar_of<r_t>::type ssr_t;
  double ulpd;
  ulpd=0.0;


  // specific values tests
  NT2_TEST_EQUAL(hmsb(boost::simd::Allbits<vT>()), sr_t((1ul << boost::simd::meta::cardinal_of<vT>::value) - 1));
  NT2_TEST_EQUAL(hmsb(boost::simd::One<vT>()), boost::simd::Zero<sr_t>());
  NT2_TEST_EQUAL(hmsb(boost::simd::Signmask<vT>()), sr_t((1ul << boost::simd::meta::cardinal_of<vT>::value) - 1));
  NT2_TEST_EQUAL(hmsb(boost::simd::Zero<vT>()), boost::simd::Zero<sr_t>());
} // end of test for int32_t

NT2_TEST_CASE_TPL ( hmsb_uint8_t_1_0,  (nt2::uint8_t))
{
  using nt2::hmsb;
  using nt2::tag::hmsb_;
  using nt2::load; 
  using boost::simd::native;
  using nt2::meta::cardinal_of;
  typedef NT2_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef typename nt2::meta::upgrade<T>::type   u_t;
  typedef native<T,ext_t>                        n_t;
  typedef n_t                                     vT;
  typedef typename nt2::meta::as_integer<T>::type iT;
  typedef native<iT,ext_t>                       ivT;
  typedef typename nt2::meta::call<hmsb_(vT)>::type r_t;
  typedef typename nt2::meta::call<hmsb_(T)>::type sr_t;
  typedef typename nt2::meta::scalar_of<r_t>::type ssr_t;
  double ulpd;
  ulpd=0.0;


  // specific values tests
  NT2_TEST_EQUAL(hmsb(boost::simd::Allbits<vT>()), 4294967295ull);
  NT2_TEST_EQUAL(hmsb(boost::simd::One<vT>()), boost::simd::Zero<sr_t>());
  NT2_TEST_EQUAL(hmsb(boost::simd::Zero<vT>()), boost::simd::Zero<sr_t>());
} // end of test for uint8_t

NT2_TEST_CASE_TPL ( hmsb_int8_t_1_0,  (nt2::int8_t))
{
  using nt2::hmsb;
  using nt2::tag::hmsb_;
  using nt2::load; 
  using boost::simd::native;
  using nt2::meta::cardinal_of;
  typedef NT2_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef typename nt2::meta::upgrade<T>::type   u_t;
  typedef native<T,ext_t>                        n_t;
  typedef n_t                                     vT;
  typedef typename nt2::meta::as_integer<T>::type iT;
  typedef native<iT,ext_t>                       ivT;
  typedef typename nt2::meta::call<hmsb_(vT)>::type r_t;
  typedef typename nt2::meta::call<hmsb_(T)>::type sr_t;
  typedef typename nt2::meta::scalar_of<r_t>::type ssr_t;
  double ulpd;
  ulpd=0.0;


  // specific values tests
  NT2_TEST_EQUAL(hmsb(boost::simd::Allbits<vT>()), sr_t((1ul << boost::simd::meta::cardinal_of<vT>::value) - 1));
  NT2_TEST_EQUAL(hmsb(boost::simd::One<vT>()), boost::simd::Zero<sr_t>());
  NT2_TEST_EQUAL(hmsb(boost::simd::Signmask<vT>()), sr_t((1ul << boost::simd::meta::cardinal_of<vT>::value) - 1));
  NT2_TEST_EQUAL(hmsb(boost::simd::Zero<vT>()), boost::simd::Zero<sr_t>());
} // end of test for int8_t
