//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#define NT2_UNIT_MODULE "nt2 boost.simd.reduction toolbox - inbtrue/simd Mode"

//////////////////////////////////////////////////////////////////////////////
// unit test behavior of boost.simd.reduction components in simd mode
//////////////////////////////////////////////////////////////////////////////
/// created  by jt the 24/02/2011
///
#include <boost/simd/toolbox/reduction/include/functions/inbtrue.hpp>
#include <boost/simd/include/functions/ulpdist.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/dispatch/functor/meta/call.hpp>
#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <boost/simd/sdk/memory/buffer.hpp>
#include <boost/simd/toolbox/constant/constant.hpp>
#include <boost/simd/sdk/memory/is_aligned.hpp>
#include <boost/simd/sdk/memory/aligned_type.hpp>
#include <boost/simd/include/functions/load.hpp>

NT2_TEST_CASE_TPL ( inbtrue_real__1_0,  BOOST_SIMD_SIMD_REAL_TYPES)
{
  using boost::simd::inbtrue;
  using boost::simd::tag::inbtrue_;
  using boost::simd::load;
  using boost::simd::native;
  using boost::simd::meta::cardinal_of;
  typedef typename boost::dispatch::meta::scalar_of<T>::type sT;
  typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef typename boost::dispatch::meta::upgrade<T>::type   u_t;
  typedef native<T,ext_t>                        n_t;
  typedef n_t                                     vT;
  typedef typename boost::dispatch::meta::as_integer<T>::type iT;
  typedef native<iT,ext_t>                       ivT;
  typedef typename boost::dispatch::meta::call<inbtrue_(vT)>::type r_t;
  typedef typename boost::simd::meta::scalar_of<r_t>::type sr_t;
  typedef typename boost::simd::meta::scalar_of<r_t>::type ssr_t;

  // specific values tests
  NT2_TEST_EQUAL(inbtrue(boost::simd::Inf<vT>()) , cardinal_of<vT>::value);
  NT2_TEST_EQUAL(inbtrue(boost::simd::Minf<vT>()), cardinal_of<vT>::value);
  NT2_TEST_EQUAL(inbtrue(boost::simd::Mone<vT>()), cardinal_of<vT>::value);
  NT2_TEST_EQUAL(inbtrue(boost::simd::Nan<vT>()) , cardinal_of<vT>::value);
  NT2_TEST_EQUAL(inbtrue(boost::simd::One<vT>()) , cardinal_of<vT>::value);
  NT2_TEST_EQUAL(inbtrue(boost::simd::Zero<vT>()), boost::simd::Zero<sr_t>());
} // end of test for floating_

NT2_TEST_CASE_TPL ( inbtrue_integer,  BOOST_SIMD_SIMD_INTEGRAL_TYPES)
{
  using boost::simd::inbtrue;
  using boost::simd::tag::inbtrue_;
  using boost::simd::load;
  using boost::simd::native;
  using boost::simd::meta::cardinal_of;
  typedef typename boost::dispatch::meta::scalar_of<T>::type sT;
  typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef typename boost::dispatch::meta::upgrade<T>::type   u_t;
  typedef native<T,ext_t>                        n_t;
  typedef n_t                                     vT;
  typedef typename boost::dispatch::meta::as_integer<T>::type iT;
  typedef native<iT,ext_t>                       ivT;
  typedef typename boost::dispatch::meta::call<inbtrue_(vT)>::type r_t;
  typedef typename boost::simd::meta::scalar_of<r_t>::type sr_t;
  typedef typename boost::simd::meta::scalar_of<r_t>::type ssr_t;

  // specific values tests
  NT2_TEST_EQUAL(inbtrue(boost::simd::Mone<vT>()), cardinal_of<vT>::value);
  NT2_TEST_EQUAL(inbtrue(boost::simd::One<vT>()) , cardinal_of<vT>::value);
  NT2_TEST_EQUAL(inbtrue(boost::simd::Zero<vT>()), boost::simd::Zero<sr_t>());
}
