//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#define NT2_UNIT_MODULE "nt2 bessel toolbox - j1/simd Mode"

//////////////////////////////////////////////////////////////////////////////
// unit test behavior of bessel components in simd mode
//////////////////////////////////////////////////////////////////////////////
/// created  by jt the 16/02/2011
///
#include <nt2/toolbox/bessel/include/functions/j1.hpp>
#include <boost/simd/sdk/simd/native.hpp>

extern "C" {long double cephes_j1l(long double);}

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

NT2_TEST_CASE_TPL ( j1_real__1_0,  NT2_SIMD_REAL_TYPES)
{
  using nt2::j1;
  using nt2::tag::j1_;
  using boost::simd::native;

  typedef NT2_SIMD_DEFAULT_EXTENSION              ext_t;
  typedef native<T,ext_t>                         vT;
  typedef typename nt2::meta::call<j1_(vT)>::type r_t;
  typedef typename nt2::meta::call<j1_(T)>::type  sr_t;

  // specific values tests
  NT2_TEST_ULP_EQUAL(j1(nt2::Inf<vT>())[0], nt2::Zero<sr_t>(), 0.5);
  NT2_TEST_ULP_EQUAL(j1(nt2::One<vT>())[0], sr_t(4.400505857449336e-01), 1.5);
  NT2_TEST_ULP_EQUAL(j1(nt2::Zero<vT>())[0], nt2::Zero<sr_t>(), 0.5);
} // end of test for floating_
