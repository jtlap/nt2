//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#define NT2_UNIT_MODULE "nt2 bitwise toolbox - rol/simd Mode"

//////////////////////////////////////////////////////////////////////////////
// Test behavior of bitwise components in simd mode
//////////////////////////////////////////////////////////////////////////////
/// created  by jt the 18/02/2011
/// modified by jt the 05/04/2011
#include <nt2/sdk/memory/is_aligned.hpp>
#include <nt2/sdk/memory/aligned_type.hpp>
#include <nt2/sdk/memory/load.hpp>
#include <nt2/sdk/memory/buffer.hpp>
#include <boost/type_traits/is_same.hpp>
#include <nt2/sdk/functor/meta/call.hpp>
#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/module.hpp> 
#include <nt2/sdk/constant/real.hpp>
#include <nt2/sdk/constant/infinites.hpp>
#include <nt2/include/functions/max.hpp>
#include <nt2/toolbox/bitwise/include/rol.hpp>

NT2_TEST_CASE_TPL ( rol_integer__2_0,  NT2_INTEGRAL_TYPES)
{
  using nt2::rol;
  using nt2::tag::rol_;
  using nt2::load; 
  using nt2::simd::native;
  using nt2::meta::cardinal_of;
  typedef NT2_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef typename nt2::meta::upgrade<T>::type   u_t;
  typedef native<T,ext_t>                        n_t;
  typedef n_t                                     vT;
  typedef typename nt2::meta::as_integer<T>::type iT;
  typedef native<iT,ext_t>                       ivT;
  typedef typename nt2::meta::call<rol_(vT,ivT)>::type r_t;
  typedef typename nt2::meta::call<rol_(T,iT)>::type sr_t;
  typedef typename nt2::meta::scalar_of<r_t>::type ssr_t;
  double ulpd;
  ulpd=0.0;


  // specific values tests
  NT2_TEST_EQUAL(rol(nt2::Mone<vT>(),nt2::splat<vT>(1))[0], nt2::Mone<sr_t>());
  NT2_TEST_EQUAL(rol(nt2::Mone<vT>(),nt2::splat<vT>(5))[0], nt2::Mone<sr_t>());
  NT2_TEST_EQUAL(rol(nt2::One<vT>(), nt2::One<vT>())[0], nt2::Two<sr_t>());
  NT2_TEST_EQUAL(rol(nt2::Zero<vT>(), nt2::Zero<vT>())[0], nt2::Zero<sr_t>());
} // end of test for integer_
