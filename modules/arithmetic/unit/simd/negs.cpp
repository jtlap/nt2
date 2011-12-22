//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#define NT2_UNIT_MODULE "nt2 arithmetic toolbox - negs/simd Mode"

//////////////////////////////////////////////////////////////////////////////
// unit test behavior of arithmetic components in simd mode
//////////////////////////////////////////////////////////////////////////////
/// created by jt the 30/11/2010
/// 
#include <nt2/toolbox/arithmetic/include/functions/negs.hpp>
#include <nt2/include/functions/ulpdist.hpp>
#include <boost/type_traits/is_same.hpp>
#include <nt2/sdk/functor/meta/call.hpp>
#include <nt2/sdk/meta/as_integer.hpp>
#include <nt2/sdk/meta/as_floating.hpp>
#include <nt2/sdk/meta/as_signed.hpp>
#include <nt2/sdk/meta/upgrade.hpp>
#include <nt2/sdk/meta/downgrade.hpp>
#include <nt2/sdk/meta/scalar_of.hpp>
#include <nt2/sdk/meta/floating.hpp>
#include <boost/type_traits/common_type.hpp>
#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/memory/buffer.hpp>
#include <nt2/toolbox/constant/constant.hpp>
#include <nt2/sdk/meta/cardinal_of.hpp>
#include <nt2/include/functions/splat.hpp>
#include <nt2/sdk/memory/is_aligned.hpp>
#include <nt2/sdk/memory/aligned_type.hpp>
#include <nt2/include/functions/load.hpp>


NT2_TEST_CASE_TPL ( negs_real__1_0,  NT2_SIMD_REAL_TYPES)
{
  using nt2::negs;
  using nt2::tag::negs_;
  using nt2::load; 
  using boost::simd::native;
  using nt2::meta::cardinal_of;
  typedef NT2_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef typename nt2::meta::upgrade<T>::type   u_t;
  typedef native<T,ext_t>                        n_t;
  typedef n_t                                     vT;
  typedef typename nt2::meta::as_integer<T>::type iT;
  typedef native<iT,ext_t>                       ivT;
  typedef typename nt2::meta::call<negs_(vT)>::type r_t;
  typedef typename nt2::meta::call<negs_(T)>::type sr_t;
  typedef typename nt2::meta::scalar_of<r_t>::type ssr_t;
  double ulpd;
  ulpd=0.0;


  // specific values tests
  NT2_TEST_EQUAL(negs(nt2::splat<vT>(100))[0], T(-100));
  NT2_TEST_EQUAL(negs(nt2::Inf<vT>())[0], nt2::Minf<T>());
  NT2_TEST_EQUAL(negs(nt2::Minf<vT>())[0], nt2::Inf<T>());
  NT2_TEST_EQUAL(negs(nt2::Mone<vT>())[0], nt2::One<T>());
  NT2_TEST_EQUAL(negs(nt2::Nan<vT>())[0], nt2::Nan<T>());
  NT2_TEST_EQUAL(negs(nt2::One<vT>())[0], nt2::Mone<T>());
  NT2_TEST_EQUAL(negs(nt2::Valmax<vT>())[0], nt2::Valmin<T>());
  NT2_TEST_EQUAL(negs(nt2::Valmin<vT>())[0], nt2::Valmax<T>());
  NT2_TEST_EQUAL(negs(nt2::Zero<vT>())[0], nt2::Zero<T>());
} // end of test for floating_

NT2_TEST_CASE_TPL ( negs_signed_int__1_0,  NT2_SIMD_INTEGRAL_SIGNED_TYPES)
{
  using nt2::negs;
  using nt2::tag::negs_;
  using nt2::load; 
  using boost::simd::native;
  using nt2::meta::cardinal_of;
  typedef NT2_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef typename nt2::meta::upgrade<T>::type   u_t;
  typedef native<T,ext_t>                        n_t;
  typedef n_t                                     vT;
  typedef typename nt2::meta::as_integer<T>::type iT;
  typedef native<iT,ext_t>                       ivT;
  typedef typename nt2::meta::call<negs_(vT)>::type r_t;
  typedef typename nt2::meta::call<negs_(T)>::type sr_t;
  typedef typename nt2::meta::scalar_of<r_t>::type ssr_t;
  double ulpd;
  ulpd=0.0;


  // specific values tests
  NT2_TEST_EQUAL(negs(nt2::splat<vT>(100))[0], T(-100));
  NT2_TEST_EQUAL(negs(nt2::Mone<vT>())[0], nt2::One<T>());
  NT2_TEST_EQUAL(negs(nt2::One<vT>())[0], nt2::Mone<T>());
  NT2_TEST_EQUAL(negs(nt2::Valmax<vT>())[0], -nt2::Valmax<T>());
  NT2_TEST_EQUAL(negs(nt2::Valmin<vT>())[0], nt2::Valmax<T>());
  NT2_TEST_EQUAL(negs(nt2::Zero<vT>())[0], nt2::Zero<T>());
} // end of test for signed_int_
