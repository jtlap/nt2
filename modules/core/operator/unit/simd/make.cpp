//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#define NT2_UNIT_MODULE "nt2 operator toolbox - make/simd Mode"

//////////////////////////////////////////////////////////////////////////////
// unit test behavior of operator components in simd mode
//////////////////////////////////////////////////////////////////////////////
/// created  by jt the 18/02/2011
///
#include <nt2/toolbox/operator/include/functions/make.hpp>
#include <boost/simd/sdk/simd/native.hpp>

#include <boost/type_traits/is_same.hpp>
#include <nt2/sdk/functor/meta/call.hpp>
#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/memory/buffer.hpp>
#include <nt2/include/constants/real.hpp>
#include <nt2/include/constants/infinites.hpp>
#include <nt2/include/functions/load.hpp>

//COMMENTED
NT2_TEST_CASE_TPL ( make_real__2_0,  NT2_REAL_TYPES)
{
//   using nt2::make;
//   using nt2::tag::make_;
//   using nt2::load;
//   using boost::simd::native;
//   using nt2::meta::cardinal_of;
//   typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
//   typedef typename nt2::meta::upgrade<T>::type   u_t;
//   typedef native<T,ext_t>                        n_t;
//   typedef n_t                                     vT;
//   typedef typename nt2::meta::as_integer<T>::type iT;
//   typedef native<iT,ext_t>                       ivT;
//   typedef typename nt2::meta::call<make_(vT,vT)>::type r_t;
//   typedef typename nt2::meta::call<make_(T,T)>::type sr_t;
//   typedef typename nt2::meta::scalar_of<r_t>::type ssr_t;
//   double ulpd;
//   ulpd=0.0;


//   // specific values tests
//   NT2_TEST_EQUAL(make(nt2::Inf<vT>(), nt2::Inf<vT>())[0], nt2::Inf<sr_t>());
//   NT2_TEST_EQUAL(make(nt2::Minf<vT>(), nt2::Minf<vT>())[0], nt2::Minf<sr_t>());
//   NT2_TEST_EQUAL(make(nt2::Nan<vT>(), nt2::Nan<vT>())[0], nt2::Nan<sr_t>());
//   NT2_TEST_EQUAL(make(nt2::One<vT>(),nt2::Zero<vT>())[0], nt2::Zero<sr_t>());
//   NT2_TEST_EQUAL(make(nt2::Zero<vT>(), nt2::Zero<vT>())[0], nt2::Zero<sr_t>());
 } // end of test for floating_
