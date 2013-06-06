//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#define NT2_UNIT_MODULE "nt2 boost.simd.operator toolbox - shift_right/simd Mode"

//////////////////////////////////////////////////////////////////////////////
// unit test behavior of boost.simd.operator components in simd mode
//////////////////////////////////////////////////////////////////////////////
/// created  by jt the 18/02/2011
///
#include <boost/simd/operator/include/functions/shift_right.hpp>
#include <boost/simd/sdk/simd/native.hpp>
#include <boost/simd/sdk/simd/io.hpp>
#include <boost/simd/constant/constant.hpp>
#include <boost/dispatch/functor/meta/call.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>

NT2_TEST_CASE_TPL ( shift_right_unsigned__2_0,  BOOST_SIMD_SIMD_INTEGRAL_UNSIGNED_TYPES)
{
  using boost::simd::shift_right;
  using boost::simd::tag::shift_right_;
  using boost::simd::native;
  typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef typename boost::dispatch::meta::upgrade<T>::type   u_t;
  typedef native<T,ext_t>                        n_t;
  typedef n_t                                     vT;
  typedef typename boost::dispatch::meta::as_integer<T>::type iT;
  typedef native<iT,ext_t>                       ivT;
  typedef typename boost::dispatch::meta::call<shift_right_(vT,ivT)>::type r_t;

  // specific values tests
  NT2_TEST_EQUAL(shift_right(boost::simd::One<vT>(),boost::simd::One<ivT>()), boost::simd::Zero<r_t>());
  NT2_TEST_EQUAL(shift_right(boost::simd::One<vT>(),boost::simd::Zero<ivT>()), boost::simd::One<r_t>());
  NT2_TEST_EQUAL(shift_right(boost::simd::splat<vT>(17),boost::simd::splat<ivT>(2)), boost::simd::splat<r_t>(4));
  NT2_TEST_EQUAL(shift_right(boost::simd::Zero<vT>(),boost::simd::One<ivT>()), boost::simd::Zero<r_t>());
  NT2_TEST_EQUAL(shift_right(boost::simd::Allbits<vT>(),boost::simd::splat<ivT>(sizeof(T)*CHAR_BIT-1)), boost::simd::One<r_t>());
}

NT2_TEST_CASE_TPL ( shift_right_signed__2_0,  BOOST_SIMD_SIMD_INTEGRAL_SIGNED_TYPES)
{
  using boost::simd::shift_right;
  using boost::simd::tag::shift_right_;
  using boost::simd::native;
  typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef typename boost::dispatch::meta::upgrade<T>::type   u_t;
  typedef native<T,ext_t>                        n_t;
  typedef n_t                                     vT;
  typedef typename boost::dispatch::meta::as_integer<T>::type iT;
  typedef native<iT,ext_t>                       ivT;
  typedef typename boost::dispatch::meta::call<shift_right_(vT,ivT)>::type r_t;

  // specific values tests
  NT2_TEST_EQUAL(shift_right(boost::simd::One<vT>(),boost::simd::One<ivT>()), boost::simd::Zero<r_t>());
  NT2_TEST_EQUAL(shift_right(boost::simd::One<vT>(),boost::simd::Zero<ivT>()), boost::simd::One<r_t>());
  NT2_TEST_EQUAL(shift_right(boost::simd::splat<vT>(17),boost::simd::splat<ivT>(2)), boost::simd::splat<r_t>(4));
  NT2_TEST_EQUAL(shift_right(boost::simd::Zero<vT>(),boost::simd::One<ivT>()), boost::simd::Zero<r_t>());
  NT2_TEST_EQUAL(shift_right(boost::simd::Allbits<vT>(),boost::simd::splat<ivT>(sizeof(T)*CHAR_BIT-1)), boost::simd::Allbits<r_t>());
}

NT2_TEST_CASE_TPL ( shift_right_real__2_0,  BOOST_SIMD_SIMD_REAL_TYPES)
{
  using boost::simd::shift_right;
  using boost::simd::tag::shift_right_;
  using boost::simd::native;
  typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef typename boost::dispatch::meta::upgrade<T>::type   u_t;
  typedef native<T,ext_t>                        n_t;
  typedef n_t                                     vT;
  typedef typename boost::dispatch::meta::as_integer<T>::type iT;
  typedef native<iT,ext_t>                       ivT;
  typedef typename boost::dispatch::meta::call<shift_right_(vT,ivT)>::type r_t;

  // specific values tests
  NT2_TEST_EQUAL(shift_right(boost::simd::One<vT>(),boost::simd::Zero<ivT>()), boost::simd::One<r_t>());
  NT2_TEST_EQUAL(shift_right(boost::simd::Zero<vT>(),boost::simd::One<ivT>()), boost::simd::Zero<r_t>());
}

NT2_TEST_CASE_TPL ( shift_right_unsigned_scalar_2_0,  BOOST_SIMD_SIMD_INTEGRAL_UNSIGNED_TYPES)
{
  using boost::simd::shift_right;
  using boost::simd::tag::shift_right_;
  using boost::simd::native;
  typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef typename boost::dispatch::meta::upgrade<T>::type   u_t;
  typedef native<T,ext_t>                        n_t;
  typedef n_t                                     vT;
  typedef typename boost::dispatch::meta::as_integer<T>::type iT;
  typedef typename boost::dispatch::meta::call<shift_right_(vT,iT)>::type r_t;

  // specific values tests
  NT2_TEST_EQUAL(shift_right(boost::simd::One<vT>(),boost::simd::One<iT>()), boost::simd::Zero<r_t>());
  NT2_TEST_EQUAL(shift_right(boost::simd::One<vT>(),boost::simd::Zero<iT>()), boost::simd::One<r_t>());
  NT2_TEST_EQUAL(shift_right(boost::simd::splat<vT>(17),boost::simd::splat<iT>(2)), boost::simd::splat<r_t>(4));
  NT2_TEST_EQUAL(shift_right(boost::simd::Zero<vT>(),boost::simd::One<iT>()), boost::simd::Zero<r_t>());
  NT2_TEST_EQUAL(shift_right(boost::simd::Allbits<vT>(),boost::simd::splat<iT>(sizeof(T)*CHAR_BIT-1)), boost::simd::One<r_t>());
}

NT2_TEST_CASE_TPL ( shift_right_signed_scalar_2_0,  BOOST_SIMD_SIMD_INTEGRAL_SIGNED_TYPES)
{
  using boost::simd::shift_right;
  using boost::simd::tag::shift_right_;
  using boost::simd::native;
  typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef typename boost::dispatch::meta::upgrade<T>::type   u_t;
  typedef native<T,ext_t>                        n_t;
  typedef n_t                                     vT;
  typedef typename boost::dispatch::meta::as_integer<T>::type iT;
  typedef typename boost::dispatch::meta::call<shift_right_(vT,iT)>::type r_t;

  // specific values tests
  NT2_TEST_EQUAL(shift_right(boost::simd::One<vT>(),boost::simd::One<iT>()), boost::simd::Zero<r_t>());
  NT2_TEST_EQUAL(shift_right(boost::simd::One<vT>(),boost::simd::Zero<iT>()), boost::simd::One<r_t>());
  NT2_TEST_EQUAL(shift_right(boost::simd::splat<vT>(17),boost::simd::splat<iT>(2)), boost::simd::splat<r_t>(4));
  NT2_TEST_EQUAL(shift_right(boost::simd::Zero<vT>(),boost::simd::One<iT>()), boost::simd::Zero<r_t>());
  NT2_TEST_EQUAL(shift_right(boost::simd::Allbits<vT>(),boost::simd::splat<iT>(sizeof(T)*CHAR_BIT-1)), boost::simd::Allbits<r_t>());
}

NT2_TEST_CASE_TPL ( shift_right_real_scalar_2_0,  BOOST_SIMD_SIMD_REAL_TYPES)
{
  using boost::simd::shift_right;
  using boost::simd::tag::shift_right_;
  using boost::simd::native;
  typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef typename boost::dispatch::meta::upgrade<T>::type   u_t;
  typedef native<T,ext_t>                        n_t;
  typedef n_t                                     vT;
  typedef typename boost::dispatch::meta::as_integer<T>::type iT;
  typedef typename boost::dispatch::meta::call<shift_right_(vT,iT)>::type r_t;

  // specific values tests
  NT2_TEST_EQUAL(shift_right(boost::simd::One<vT>(),boost::simd::Zero<iT>()), boost::simd::One<r_t>());
  NT2_TEST_EQUAL(shift_right(boost::simd::Zero<vT>(),boost::simd::One<iT>()), boost::simd::Zero<r_t>());
}
