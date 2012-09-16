//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#define NT2_UNIT_MODULE "nt2 boost.simd.operator toolbox - is_less/simd Mode"

//////////////////////////////////////////////////////////////////////////////
// unit test behavior of boost.simd.operator components in simd mode
//////////////////////////////////////////////////////////////////////////////
/// created  by jt the 18/02/2011
///
#include <boost/simd/toolbox/predicates/include/functions/is_less.hpp>
#include <boost/simd/include/functions/ulpdist.hpp>
#include <boost/simd/sdk/simd/logical.hpp>

#include <boost/type_traits/is_same.hpp>
#include <boost/dispatch/functor/meta/call.hpp>
#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <boost/simd/sdk/memory/buffer.hpp>
#include <boost/simd/toolbox/constant/constant.hpp>
#include <boost/simd/sdk/memory/is_aligned.hpp>
#include <boost/simd/sdk/memory/aligned_type.hpp>
#include <boost/simd/include/functions/load.hpp>


NT2_TEST_CASE_TPL ( is_less_integer__2_0,  BOOST_SIMD_SIMD_INTEGRAL_TYPES)
{
  using boost::simd::is_less;
  using boost::simd::tag::is_less_;
  using boost::simd::load;
  using boost::simd::native;
  using boost::simd::meta::cardinal_of;
  typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef typename boost::dispatch::meta::upgrade<T>::type   u_t;
  typedef native<T,ext_t>                        n_t;
  typedef n_t                                     vT;
  typedef typename boost::dispatch::meta::as_integer<T>::type iT;
  typedef native<iT,ext_t>                       ivT;
  typedef typename boost::dispatch::meta::call<is_less_(vT,vT)>::type r_t;
  typedef typename boost::simd::meta::scalar_of<r_t>::type sr_t;
  typedef typename boost::simd::meta::scalar_of<r_t>::type ssr_t;

  // specific values tests
  NT2_TEST_EQUAL(is_less(boost::simd::One<vT>(), boost::simd::One<vT>())[0], ssr_t(false));
  NT2_TEST_EQUAL(is_less(boost::simd::One<vT>(),boost::simd::Zero<vT>())[0], ssr_t(false));
  NT2_TEST_EQUAL(is_less(boost::simd::Zero<vT>(), boost::simd::Zero<vT>())[0], ssr_t(false));
} // end of test for integer_

NT2_TEST_CASE_TPL ( is_less_signed_integer,  BOOST_SIMD_SIMD_INTEGRAL_SIGNED_TYPES)
{
  typedef boost::simd::native<T, BOOST_SIMD_DEFAULT_EXTENSION> vT;
  using boost::simd::splat;
  using boost::simd::is_less;
  using boost::simd::logical;

  T hvalmin = T(1) << (sizeof(T)*CHAR_BIT/2-1);
  NT2_TEST_EQUAL( is_less(splat<vT>(hvalmin-1), splat<vT>(hvalmin))[0], logical<T>(true) );
}

NT2_TEST_CASE_TPL ( is_less_real__2_0,  BOOST_SIMD_SIMD_REAL_TYPES)
{
  using boost::simd::is_less;
  using boost::simd::tag::is_less_;
  using boost::simd::load;
  using boost::simd::native;
  using boost::simd::meta::cardinal_of;
  typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef typename boost::dispatch::meta::upgrade<T>::type   u_t;
  typedef native<T,ext_t>                        n_t;
  typedef n_t                                     vT;
  typedef typename boost::dispatch::meta::as_integer<T>::type iT;
  typedef native<iT,ext_t>                       ivT;
  typedef typename boost::dispatch::meta::call<is_less_(vT,vT)>::type r_t;
  typedef typename boost::simd::meta::scalar_of<r_t>::type sr_t;
  typedef typename boost::simd::meta::scalar_of<r_t>::type ssr_t;

  // specific values tests
  NT2_TEST_EQUAL(is_less(boost::simd::Inf<vT>(), boost::simd::Inf<vT>())[0], ssr_t(false));
  NT2_TEST_EQUAL(is_less(boost::simd::Minf<vT>(), boost::simd::Minf<vT>())[0], ssr_t(false));
  NT2_TEST_EQUAL(is_less(boost::simd::Nan<vT>(), boost::simd::Nan<vT>())[0], ssr_t(false));
  NT2_TEST_EQUAL(is_less(boost::simd::One<vT>(),boost::simd::Zero<vT>())[0], ssr_t(false));
  NT2_TEST_EQUAL(is_less(boost::simd::Zero<vT>(), boost::simd::Zero<vT>())[0], ssr_t(false));
} // end of test for floating_
