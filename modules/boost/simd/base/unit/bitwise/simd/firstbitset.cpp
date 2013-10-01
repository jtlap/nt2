//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <boost/simd/bitwise/include/functions/firstbitset.hpp>
#include <boost/simd/sdk/simd/native.hpp>

#include <boost/dispatch/functor/meta/call.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <boost/simd/include/functions/splat.hpp>
#include <boost/simd/include/functions/plus.hpp>
#include <boost/simd/include/functions/divides.hpp>
#include <boost/simd/include/constants/one.hpp>
#include <boost/simd/include/constants/two.hpp>
#include <boost/simd/include/constants/mone.hpp>
#include <boost/simd/include/constants/zero.hpp>
#include <boost/simd/include/constants/inf.hpp>
#include <boost/simd/include/constants/minf.hpp>
#include <boost/simd/include/constants/nan.hpp>
#include <boost/simd/include/constants/valmax.hpp>
#include <boost/simd/include/constants/signmask.hpp>
#include <boost/simd/include/constants/nbmantissabits.hpp>
#include <boost/simd/sdk/config.hpp>
#include <boost/simd/sdk/simd/io.hpp>

NT2_TEST_CASE_TPL ( firstbitset_real,  BOOST_SIMD_SIMD_REAL_TYPES)
{
  using boost::simd::firstbitset;
  using boost::simd::tag::firstbitset_;
  using boost::simd::native;
  typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef native<T,ext_t>                  vT;
  typedef typename boost::dispatch::meta::call<firstbitset_(vT)>::type r_t;

  // specific values tests
  NT2_TEST_EQUAL(firstbitset(boost::simd::Inf<vT>()), boost::simd::splat<r_t>(1ull<<boost::simd::Nbmantissabits<T>()));
  NT2_TEST_EQUAL(firstbitset(boost::simd::Minf<vT>()), boost::simd::splat<r_t>(1ull<<boost::simd::Nbmantissabits<T>()));
  NT2_TEST_EQUAL(firstbitset(boost::simd::Nan<vT>()), boost::simd::One<r_t>());
  NT2_TEST_EQUAL(firstbitset(boost::simd::Signmask<vT>()), boost::simd::One<r_t>()+boost::simd::Valmax<r_t>()/boost::simd::Two<r_t>());
  NT2_TEST_EQUAL(firstbitset(boost::simd::Zero<vT>()), boost::simd::Zero<r_t>());
} // end of test for real_

NT2_TEST_CASE_TPL ( firstbitset_signed_int,  BOOST_SIMD_SIMD_INTEGRAL_SIGNED_TYPES)
{
  using boost::simd::firstbitset;
  using boost::simd::tag::firstbitset_;
  using boost::simd::native;
  typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef native<T,ext_t>                  vT;
  typedef typename boost::dispatch::meta::call<firstbitset_(vT)>::type r_t;

  // specific values tests
  NT2_TEST_EQUAL(firstbitset(boost::simd::One<vT>()), boost::simd::One<r_t>());
  NT2_TEST_EQUAL(firstbitset(boost::simd::Signmask<vT>()), boost::simd::One<r_t>()+boost::simd::Valmax<r_t>()/boost::simd::Two<r_t>());
  NT2_TEST_EQUAL(firstbitset(boost::simd::Zero<vT>()), boost::simd::Zero<r_t>());
} // end of test for signed_int_

NT2_TEST_CASE_TPL ( firstbitset_unsigned_int,  BOOST_SIMD_SIMD_UNSIGNED_TYPES)
{
  using boost::simd::firstbitset;
  using boost::simd::tag::firstbitset_;
  using boost::simd::native;
  typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef native<T,ext_t>                  vT;
  typedef typename boost::dispatch::meta::call<firstbitset_(vT)>::type r_t;

  // specific values tests
  NT2_TEST_EQUAL(firstbitset(boost::simd::One<vT>()), boost::simd::One<r_t>());
  NT2_TEST_EQUAL(firstbitset(boost::simd::Zero<vT>()), boost::simd::Zero<r_t>());
} // end of test for unsigned_int_
