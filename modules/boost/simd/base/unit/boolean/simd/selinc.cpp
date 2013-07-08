//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#define NT2_UNIT_MODULE "nt2 boost.simd.boolean toolbox - selinc/scalar Mode"

//////////////////////////////////////////////////////////////////////////////
// unit test behavior of boost.simd.boolean components in scalar mode
//////////////////////////////////////////////////////////////////////////////

#include <boost/simd/boolean/include/functions/selinc.hpp>
#include <boost/simd/sdk/simd/native.hpp>
#include <boost/simd/sdk/simd/io.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/simd/constant/constant.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/basic.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>

NT2_TEST_CASE_TPL ( selinc_signed_int__2_0,  BOOST_SIMD_SIMD_INTEGRAL_SIGNED_TYPES)
{
  typedef boost::simd::native<T, BOOST_SIMD_DEFAULT_EXTENSION> vT;

  using boost::simd::selinc;
  using boost::simd::tag::selinc_;
  typedef typename boost::dispatch::meta::as_integer<T>::type iT;
  typedef typename boost::dispatch::meta::call<selinc_(vT, vT)>::type r_t;
  typedef typename boost::simd::meta::scalar_of<r_t>::type sr_t;
  typedef typename boost::simd::meta::scalar_of<r_t>::type ssr_t;
  typedef vT wished_r_t;


  // return type conformity test
  NT2_TEST( (boost::is_same < r_t, wished_r_t >::value) );
  std::cout << std::endl;

  // specific values tests
  NT2_TEST_EQUAL(selinc(boost::simd::One<vT>(), boost::simd::Mone<vT>()), boost::simd::Zero<vT>());
  NT2_TEST_EQUAL(selinc(boost::simd::One<vT>(), boost::simd::One<vT>()), boost::simd::Two<vT>());
  NT2_TEST_EQUAL(selinc(boost::simd::One<vT>(), boost::simd::Valmax<vT>()), boost::simd::Valmin<vT>());
  NT2_TEST_EQUAL(selinc(boost::simd::One<vT>(), boost::simd::Zero<vT>()), boost::simd::One<vT>());
}

NT2_TEST_CASE_TPL ( selinc_unsigned_int__2_0,  BOOST_SIMD_SIMD_UNSIGNED_TYPES)
{
  typedef boost::simd::native<T, BOOST_SIMD_DEFAULT_EXTENSION> vT;

  using boost::simd::selinc;
  using boost::simd::tag::selinc_;
  typedef typename boost::dispatch::meta::call<selinc_(vT, vT)>::type r_t;
  typedef typename boost::simd::meta::scalar_of<r_t>::type sr_t;
  typedef typename boost::simd::meta::scalar_of<r_t>::type ssr_t;
  typedef vT wished_r_t;


  // return type conformity test
  NT2_TEST( (boost::is_same < r_t, wished_r_t >::value) );
  std::cout << std::endl;

  // specific values tests
  NT2_TEST_EQUAL(selinc(boost::simd::One<vT>(), boost::simd::One<vT>()), boost::simd::Two<vT>());
  NT2_TEST_EQUAL(selinc(boost::simd::One<vT>(), boost::simd::Valmax<vT>()), boost::simd::Zero<vT>());
  NT2_TEST_EQUAL(selinc(boost::simd::One<vT>(), boost::simd::Zero<vT>()), boost::simd::One<vT>());
}

NT2_TEST_CASE_TPL( selinc_floating, BOOST_SIMD_SIMD_REAL_TYPES)
{
  typedef boost::simd::native<T, BOOST_SIMD_DEFAULT_EXTENSION> vT;

  using boost::simd::selinc;
  using boost::simd::tag::selinc_;
  typedef typename boost::dispatch::meta::call<selinc_(vT, vT)>::type r_t;
  typedef typename boost::simd::meta::scalar_of<r_t>::type sr_t;
  typedef typename boost::simd::meta::scalar_of<r_t>::type ssr_t;
  typedef vT wished_r_t;


  // return type conformity test
  NT2_TEST( (boost::is_same < r_t, wished_r_t >::value) );
  std::cout << std::endl;

  // specific values tests
  NT2_TEST_EQUAL(selinc(boost::simd::One<vT>(), boost::simd::Mone<vT>()), boost::simd::Zero<vT>());
  NT2_TEST_EQUAL(selinc(boost::simd::One<vT>(), boost::simd::One<vT>()), boost::simd::Two<vT>());
  NT2_TEST_EQUAL(selinc(boost::simd::One<vT>(), boost::simd::Valmax<vT>()), boost::simd::Valmax<vT>());
  NT2_TEST_EQUAL(selinc(boost::simd::One<vT>(), boost::simd::Zero<vT>()), boost::simd::One<vT>());
}
