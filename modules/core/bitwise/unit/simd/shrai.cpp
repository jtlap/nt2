//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#define NT2_UNIT_MODULE "nt2 bitwise toolbox - shrai/simd Mode"

//////////////////////////////////////////////////////////////////////////////
// unit test behavior of bitwise components in simd mode
//////////////////////////////////////////////////////////////////////////////
/// created  by jt the 18/02/2011
///
#include <nt2/toolbox/bitwise/include/functions/shrai.hpp>
#include <boost/simd/sdk/simd/native.hpp>
#include <nt2/include/functions/ulpdist.hpp>
#include <nt2/include/functions/twopower.hpp>

#include <boost/type_traits/is_same.hpp>
#include <nt2/sdk/functor/meta/call.hpp>
#include <nt2/sdk/meta/as_integer.hpp>
#include <nt2/sdk/meta/as_floating.hpp>
#include <nt2/sdk/meta/as_signed.hpp>
#include <nt2/sdk/meta/upgrade.hpp>
#include <nt2/sdk/meta/downgrade.hpp>
#include <nt2/sdk/meta/scalar_of.hpp>
#include <boost/dispatch/meta/as_floating.hpp>
#include <boost/type_traits/common_type.hpp>
#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/module.hpp>

#include <nt2/toolbox/constant/constant.hpp>
#include <nt2/sdk/meta/cardinal_of.hpp>
#include <nt2/include/functions/splat.hpp>

#include <nt2/include/functions/load.hpp>


NT2_TEST_CASE_TPL ( shrai_unsigned_int__2_0,  NT2_SIMD_UNSIGNED_TYPES)
{
  using nt2::shrai;
  using nt2::tag::shrai_;
  using nt2::load;
  using boost::simd::native;
  using nt2::meta::cardinal_of;
  typedef T r_type;
  typedef NT2_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef typename nt2::meta::upgrade<T>::type   u_t;
  typedef native<T,ext_t>                        n_t;
  typedef n_t                                     vT;
  typedef typename nt2::meta::as_integer<T>::type iT;
  typedef native<iT,ext_t>                       ivT;
  typedef typename nt2::meta::call<shrai_(vT,iT)>::type r_t;
  typedef typename nt2::meta::call<shrai_(T,iT)>::type sr_t;
  typedef typename nt2::meta::scalar_of<r_t>::type ssr_t;
  double ulpd;
  ulpd=0.0;


  // specific values tests
  NT2_TEST_EQUAL(shrai(nt2::splat<vT>(2),(1))[0], nt2::One<T>());
  NT2_TEST_EQUAL(shrai(nt2::Mone<vT>(),(sizeof(r_type)*8-1))[0], nt2::One<sr_t>());
  NT2_TEST_EQUAL(shrai(nt2::Mone<vT>(),(sizeof(r_type)*8-2))[0], nt2::Three<sr_t>());
  NT2_TEST_EQUAL(shrai(nt2::One<vT>(),(1))[0], nt2::Zero<sr_t>());
  NT2_TEST_EQUAL(shrai(nt2::Zero<vT>(),(1))[0], nt2::Zero<sr_t>());
} // end of test for unsigned_int_

NT2_TEST_CASE_TPL ( shrai_signed_int__2_0,  NT2_SIMD_INTEGRAL_SIGNED_TYPES)
{
  using nt2::shrai;
  using nt2::tag::shrai_;
  using nt2::load;
  using boost::simd::native;
  using nt2::meta::cardinal_of;
  typedef T r_type;
  typedef NT2_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef typename nt2::meta::upgrade<T>::type   u_t;
  typedef native<T,ext_t>                        n_t;
  typedef n_t                                     vT;
  typedef typename nt2::meta::as_integer<T>::type iT;
  typedef native<iT,ext_t>                       ivT;
  typedef typename nt2::meta::call<shrai_(vT,iT)>::type r_t;
  typedef typename nt2::meta::call<shrai_(T,iT)>::type sr_t;
  typedef typename nt2::meta::scalar_of<r_t>::type ssr_t;
  double ulpd;
  ulpd=0.0;


  // specific values tests
  NT2_TEST_EQUAL(shrai(-nt2::Four<vT>(),1)[0], -nt2::Two<sr_t>());
  NT2_TEST_EQUAL(shrai(nt2::splat<vT>(-2),(1))[0], nt2::Mone<sr_t>());
  NT2_TEST_EQUAL(shrai(nt2::splat<vT>(-3),(1))[0], -nt2::Two<sr_t>());
  NT2_TEST_EQUAL(shrai(nt2::splat<vT>(2),(1))[0], nt2::One<T>());
  NT2_TEST_EQUAL(shrai(nt2::Mone<vT>(),(sizeof(r_type)*8-1))[0], nt2::Mone<sr_t>());
  NT2_TEST_EQUAL(shrai(nt2::Mone<vT>(),(sizeof(r_type)*8-2))[0], nt2::Mone<sr_t>());
  NT2_TEST_EQUAL(shrai(nt2::One<vT>(),1)[0], nt2::Zero<sr_t>());
  NT2_TEST_EQUAL(shrai(nt2::Zero<vT>(),1)[0], nt2::Zero<sr_t>());
} // end of test for signed_int_
