//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#define NT2_UNIT_MODULE "nt2 polynomials toolbox - polevl/simd Mode"

//////////////////////////////////////////////////////////////////////////////
// unit test behavior of polynomials components in simd mode
//////////////////////////////////////////////////////////////////////////////
/// created  by jt the 06/03/2011
/// 
#include <nt2/toolbox/polynomials/include/functions/polevl.hpp>
#include <nt2/include/functions/ulpdist.hpp>

#include <boost/type_traits/is_same.hpp>
#include <nt2/sdk/functor/meta/call.hpp>
#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/memory/buffer.hpp>
#include <nt2/include/constants/real.hpp>
#include <nt2/include/constants/infinites.hpp>
#include <nt2/include/functions/load.hpp>

//COMMENTED
NT2_TEST_CASE_TPL ( polevl_real__2_0,  NT2_REAL_TYPES)
{
//   using nt2::polevl;
//   using nt2::tag::polevl_;
//   using nt2::load; 
//   using nt2::simd::native;
//   using nt2::meta::cardinal_of;
//   typedef NT2_SIMD_DEFAULT_EXTENSION  ext_t;
//   typedef typename nt2::meta::upgrade<T>::type   u_t;
//   typedef native<T,ext_t>                        n_t;
//   typedef n_t                                     vT;
//   typedef typename nt2::meta::as_integer<T>::type iT;
//   typedef native<iT,ext_t>                       ivT;
//   typedef typename nt2::meta::call<polevl_(vT,vT)>::type r_t;
//   typedef typename nt2::meta::call<polevl_(T,T)>::type sr_t;
//   typedef typename nt2::meta::scalar_of<r_t>::type ssr_t;


  // specific values tests
//   NT2_TEST_ULP_EQUAL(polevl(nt2::Inf<vT>(), nt2::Inf<vT>())[0], nt2::Inf<sr_t>(), 0.5);
//   NT2_TEST_ULP_EQUAL(polevl(nt2::Minf<vT>(), nt2::Minf<vT>())[0], nt2::Zero<sr_t>(), 0.5);
//   NT2_TEST_ULP_EQUAL(polevl(nt2::Nan<vT>(), nt2::Nan<vT>())[0], nt2::Nan<sr_t>(), 0.5);
//   NT2_TEST_ULP_EQUAL(polevl(nt2::Zero<vT>(), nt2::Zero<vT>())[0], nt2::Zero<sr_t>(), 0.5);
} // end of test for floating_
