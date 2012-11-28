//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#define NT2_UNIT_MODULE "nt2 boost.simd.swar toolbox - lookup/simd Mode"

//////////////////////////////////////////////////////////////////////////////
// unit test behavior of boost.simd.swar components in simd mode
//////////////////////////////////////////////////////////////////////////////
/// created  by jt the 24/02/2011
///
#include <boost/simd/toolbox/swar/include/functions/lookup.hpp>
#include <boost/simd/include/functions/ulpdist.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/dispatch/functor/meta/call.hpp>
#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <boost/simd/toolbox/constant/constant.hpp>
#include <boost/simd/sdk/memory/is_aligned.hpp>
#include <boost/simd/sdk/memory/aligned_type.hpp>
#include <boost/simd/include/functions/load.hpp>
#include <boost/simd/toolbox/constant/constant.hpp>


NT2_TEST_CASE_TPL ( lookup_real__2_0,  BOOST_SIMD_SIMD_REAL_TYPES)
{
  using boost::simd::lookup;
  using boost::simd::tag::lookup_;
  using boost::simd::load;
  using boost::simd::native;
  using boost::simd::meta::cardinal_of;
  typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef typename boost::dispatch::meta::upgrade<T>::type   u_t;
  typedef native<T,ext_t>                        n_t;
  typedef n_t                                     vT;
  typedef typename boost::dispatch::meta::as_integer<T>::type iT;
  typedef native<iT,ext_t>                       ivT;
  typedef typename boost::dispatch::meta::call<lookup_(vT,ivT)>::type r_t;
  typedef typename boost::simd::meta::scalar_of<r_t>::type sr_t;
  typedef typename boost::simd::meta::scalar_of<r_t>::type ssr_t;

  // specific values tests
  NT2_TEST_EQUAL(lookup(boost::simd::Inf<vT>(),boost::simd::Zero<ivT>())[0], boost::simd::Inf<sr_t>());
  NT2_TEST_EQUAL(lookup(boost::simd::Minf<vT>(),boost::simd::Zero<ivT>())[0], boost::simd::Minf<sr_t>());
  NT2_TEST_EQUAL(lookup(boost::simd::Mone<vT>(),boost::simd::Zero<ivT>())[0], boost::simd::Mone<sr_t>());
  NT2_TEST_EQUAL(lookup(boost::simd::Nan<vT>(),boost::simd::Zero<ivT>())[0], boost::simd::Nan<sr_t>());
  NT2_TEST_EQUAL(lookup(boost::simd::One<vT>(),boost::simd::Zero<ivT>())[0], boost::simd::One<sr_t>());
  NT2_TEST_EQUAL(lookup(boost::simd::Zero<vT>(),boost::simd::Zero<ivT>())[0], boost::simd::Zero<sr_t>());
  NT2_TEST_EQUAL(lookup(boost::simd::Inf<vT>(),boost::simd::One<ivT>())[0], boost::simd::Inf<sr_t>());
  NT2_TEST_EQUAL(lookup(boost::simd::Minf<vT>(),boost::simd::One<ivT>())[0], boost::simd::Minf<sr_t>());
  NT2_TEST_EQUAL(lookup(boost::simd::Mone<vT>(),boost::simd::One<ivT>())[0], boost::simd::Mone<sr_t>());
  NT2_TEST_EQUAL(lookup(boost::simd::Nan<vT>(),boost::simd::One<ivT>())[0], boost::simd::Nan<sr_t>());
  NT2_TEST_EQUAL(lookup(boost::simd::One<vT>(),boost::simd::One<ivT>())[0], boost::simd::One<sr_t>());
  NT2_TEST_EQUAL(lookup(boost::simd::Zero<vT>(),boost::simd::One<ivT>())[0], boost::simd::Zero<sr_t>());
} // end of test for floating_

NT2_TEST_CASE_TPL ( lookup_integer__2_0,  BOOST_SIMD_SIMD_INTEGRAL_TYPES)
{
  using boost::simd::lookup;
  using boost::simd::tag::lookup_;
  using boost::simd::load;
  using boost::simd::native;
  using boost::simd::meta::cardinal_of;
  typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef typename boost::dispatch::meta::upgrade<T>::type   u_t;
  typedef native<T,ext_t>                        n_t;
  typedef n_t                                     vT;
  typedef typename boost::dispatch::meta::as_integer<T>::type iT;
  typedef native<iT,ext_t>                       ivT;
  typedef typename boost::dispatch::meta::call<lookup_(vT,ivT)>::type r_t;
  typedef typename boost::simd::meta::scalar_of<r_t>::type sr_t;
  typedef typename boost::simd::meta::scalar_of<r_t>::type ssr_t;

  // specific values tests
  NT2_TEST_EQUAL(lookup(boost::simd::One<vT>(),boost::simd::Zero<ivT>())[0], boost::simd::One<sr_t>());
  NT2_TEST_EQUAL(lookup(boost::simd::Zero<vT>(),boost::simd::Zero<ivT>())[0], boost::simd::Zero<sr_t>());
  NT2_TEST_EQUAL(lookup(boost::simd::One<vT>(),boost::simd::One<ivT>())[0], boost::simd::One<sr_t>());
  NT2_TEST_EQUAL(lookup(boost::simd::Zero<vT>(),boost::simd::One<ivT>())[0], boost::simd::Zero<sr_t>());
} // end of test for integer_
