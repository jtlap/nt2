//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#define NT2_UNIT_MODULE "nt2 euler toolbox - erfc/scalar Mode"

//////////////////////////////////////////////////////////////////////////////
// unit test behavior of euler components in scalar mode
//////////////////////////////////////////////////////////////////////////////
/// created  by jt the 22/02/2011
///
#include <nt2/toolbox/euler/include/functions/erfc.hpp>
#include <nt2/include/functions/ulpdist.hpp>

extern "C" {long double cephes_erfcl(long double);}

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
#include <nt2/sdk/memory/buffer.hpp>
#include <nt2/toolbox/constant/constant.hpp>


NT2_TEST_CASE_TPL ( erfc_real__1_0,  NT2_SIMD_REAL_TYPES)
{

  using nt2::erfc;
  using nt2::tag::erfc_;
  using boost::simd::native;
  using nt2::meta::cardinal_of;
  typedef NT2_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef typename nt2::meta::upgrade<T>::type   u_t;
  typedef native<T,ext_t>                        n_t;
  typedef n_t                                     vT;
  typedef typename nt2::meta::as_integer<T>::type iT;
  typedef native<iT,ext_t>                       ivT;
  typedef typename nt2::meta::call<erfc_(vT)>::type r_t;
  typedef typename nt2::meta::call<erfc_(T)>::type sr_t;
  typedef typename nt2::meta::scalar_of<r_t>::type ssr_t;
  double ulpd;
  ulpd=0.0;

  // specific values tests
  NT2_TEST_ULP_EQUAL(erfc(nt2::Inf<vT>())[0], nt2::Zero<sr_t>(), 200);
  NT2_TEST_ULP_EQUAL(erfc(nt2::Mzero<vT>())[0], nt2::One<sr_t>(), 200);
  NT2_TEST_ULP_EQUAL(erfc(nt2::Nan<vT>()[0]), nt2::Nan<sr_t>(), 200);
  NT2_TEST_ULP_EQUAL(erfc(nt2::One<vT>())[0], T(1-0.842700792949715), 200);
  NT2_TEST_ULP_EQUAL(erfc(nt2::Half<vT>())[0], T(1- 0.520499877813047), 200);
  NT2_TEST_ULP_EQUAL(erfc(nt2::Two<vT>())[0], T(1-0.995322265018953), 200);
  NT2_TEST_ULP_EQUAL(erfc(nt2::Ten<vT>())[0],  nt2::Zero <sr_t>(), 200);
  NT2_TEST_ULP_EQUAL(erfc(nt2::Zero<vT>())[0], nt2::One<sr_t>(), 200);
} // end of test for floating_
