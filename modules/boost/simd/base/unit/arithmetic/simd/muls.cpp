//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <boost/simd/arithmetic/include/functions/muls.hpp>
#include <boost/simd/sdk/simd/native.hpp>
#include <boost/simd/sdk/simd/io.hpp>
#include <boost/dispatch/functor/meta/call.hpp>
#include <boost/simd/include/constants/zero.hpp>
#include <boost/simd/include/constants/one.hpp>
#include <boost/simd/include/constants/mone.hpp>
#include <boost/simd/include/constants/two.hpp>
#include <boost/simd/include/constants/mtwo.hpp>
#include <boost/simd/include/constants/inf.hpp>
#include <boost/simd/include/constants/minf.hpp>
#include <boost/simd/include/constants/nan.hpp>
#include <boost/simd/include/constants/valmin.hpp>
#include <boost/simd/include/constants/valmax.hpp>
#include <boost/simd/include/functions/make.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>

NT2_TEST_CASE_TPL ( muls_signed_int,  BOOST_SIMD_SIMD_INTEGRAL_SIGNED_TYPES)
{
  using boost::simd::muls;
  using boost::simd::tag::muls_;
  using boost::simd::native;
  typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef native<T,ext_t>                  vT;

  // specific values tests
  NT2_TEST_EQUAL(muls(boost::simd::Mone<vT>(), boost::simd::Mone<vT>()), boost::simd::One<vT>());
  NT2_TEST_EQUAL(muls(boost::simd::One<vT>(), boost::simd::One<vT>()), boost::simd::One<vT>());
  NT2_TEST_EQUAL(muls(boost::simd::Valmax<vT>(), boost::simd::Valmax<vT>()), boost::simd::Valmax<vT>());
  NT2_TEST_EQUAL(muls(boost::simd::Valmax<vT>(),boost::simd::splat<vT>(2)), boost::simd::Valmax<vT>());
  NT2_TEST_EQUAL(muls(boost::simd::Valmax<vT>(),boost::simd::Mone<vT>()), boost::simd::Valmin<vT>()+boost::simd::One<vT>());
  NT2_TEST_EQUAL(muls(boost::simd::Valmax<vT>(),boost::simd::One<vT>()), boost::simd::Valmax<vT>());
  NT2_TEST_EQUAL(muls(boost::simd::Valmin<vT>(),boost::simd::Mone<vT>()), boost::simd::Valmax<vT>());
  NT2_TEST_EQUAL(muls(boost::simd::Valmin<vT>(),boost::simd::Valmin<vT>()), boost::simd::Valmax<vT>());
  NT2_TEST_EQUAL(muls(boost::simd::Zero<vT>(), boost::simd::Zero<vT>()), boost::simd::Zero<vT>());
} // end of test for signed_int_

NT2_TEST_CASE_TPL ( muls_unsigned_int,  BOOST_SIMD_SIMD_UNSIGNED_TYPES)
{
  using boost::simd::muls;
  using boost::simd::tag::muls_;
  using boost::simd::native;
  typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef native<T,ext_t>                  vT;
  typedef typename boost::dispatch::meta::call<muls_(vT,vT)>::type r_t;

  // specific values tests
  NT2_TEST_EQUAL(muls(boost::simd::One<vT>(), boost::simd::One<vT>()), boost::simd::One<r_t>());
  NT2_TEST_EQUAL(muls(boost::simd::Valmax<vT>(),boost::simd::splat<vT>(2)), boost::simd::Valmax<r_t>());
  NT2_TEST_EQUAL(muls(boost::simd::Zero<vT>(), boost::simd::Zero<vT>()), boost::simd::Zero<r_t>());
} // end of test for unsigned_int_

NT2_TEST_CASE(muls_special)
{
  using boost::simd::muls;
  using boost::simd::splat;
  using boost::simd::make;
  using boost::simd::Valmin;
  using boost::simd::Valmax;

#ifndef BOOST_SIMD_HAS_MIC_SUPPORT
  typedef boost::simd::native<short int, BOOST_SIMD_DEFAULT_EXTENSION> vT1;
  NT2_TEST_EQUAL(muls(splat<vT1>(-5165), splat<vT1>(23258)), Valmin<vT1>());
#endif

  typedef boost::simd::native<int, BOOST_SIMD_DEFAULT_EXTENSION> vT2;
  NT2_TEST_EQUAL(muls(splat<vT2>(-1306766858), splat<vT2>(1550772331)), Valmin<vT2>());
  NT2_TEST_EQUAL(muls(splat<vT2>(1467238299), splat<vT2>(-900961598)), Valmin<vT2>());

#ifdef BOOST_SIMD_HAS_AVX_SUPPORT
  typedef int T2;
  vT2 a = make<vT2>(853350212, 191584584, 1467238299, -1306766858, 991230901, 146415451, 154742226, 1320298211);
  vT2 b = make<vT2>(1557885369, 1394765115, -900961598, 1550772331, 1563251902, -50470159, -76281765, 405234440);

  vT2 c = make<vT2>(Valmax<T2>(), Valmax<T2>(), Valmin<T2>(), Valmin<T2>(), Valmax<T2>(), Valmin<T2>(), Valmin<T2>(), Valmax<T2>());
  NT2_TEST_EQUAL(muls(a, b), c);
#endif
}
