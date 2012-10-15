//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#define NT2_UNIT_MODULE "nt2 euler toolbox - erfcinv/simd Mode"

//////////////////////////////////////////////////////////////////////////////
// unit test behavior of euler components in simd mode
//////////////////////////////////////////////////////////////////////////////
/// created  by jt the 22/02/2011
///
#include <nt2/toolbox/euler/include/functions/erfcinv.hpp>
#include <nt2/include/functions/ulpdist.hpp>
#include <nt2/include/functions/splat.hpp>
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
#include <nt2/include/constants/pi.hpp>
#include <nt2/include/constants/three.hpp>
#include <nt2/include/constants/four.hpp>
#include <nt2/include/constants/eight.hpp>


NT2_TEST_CASE_TPL ( erfcinv_real__1_0, NT2_SIMD_REAL_TYPES)
{

  using nt2::erfcinv;
  using nt2::tag::erfcinv_;
  using boost::simd::native;
  using nt2::meta::cardinal_of;
  typedef NT2_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef typename nt2::meta::upgrade<T>::type   u_t;
  typedef native<T,ext_t>                        n_t;
  typedef n_t                                     vT;
  typedef typename nt2::meta::as_integer<T>::type iT;
  typedef native<iT,ext_t>                       ivT;
  typedef typename nt2::meta::call<erfcinv_(vT)>::type r_t;
  typedef typename nt2::meta::call<erfcinv_(T)>::type sr_t;
  typedef typename nt2::meta::scalar_of<r_t>::type ssr_t;

   // specific values tests
  NT2_TEST_ULP_EQUAL(erfcinv(nt2::Zero<vT>()      )[0],  nt2::Inf<sr_t>()   , 10);
  NT2_TEST_ULP_EQUAL(erfcinv(nt2::One<vT>()     )[0],  nt2::Mzero<sr_t>() , 10);
  NT2_TEST_ULP_EQUAL(erfcinv(nt2::Nan<vT>()      )[0],  nt2::Nan<sr_t>()   , 10);
  NT2_TEST_ULP_EQUAL(erfcinv(nt2::splat<vT>(1-0.52049987781304653768274665389196) )[0],  nt2::Half<sr_t>()  , 10);
  NT2_TEST_ULP_EQUAL(erfcinv(nt2::splat<vT>(1-0.842700792949714869341220635082610) )[0],  nt2::One<sr_t>()   , 10);
  NT2_TEST_ULP_EQUAL(erfcinv(nt2::splat<vT>(1-0.99532226501895273416206925636725) )[0],  nt2::Two<sr_t>()   , 10);
} // end of test for floating_
