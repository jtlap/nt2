//==============================================================================
//         Copyright 2015          J.T. Lapreste
//         Copyright 2003 - 2013   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/include/functions/round.hpp>

#include <boost/dispatch/functor/meta/call.hpp>
#include <nt2/sdk/functor/meta/call.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/ulp.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>
#include <complex>
#include <nt2/sdk/complex/complex.hpp>
#include <nt2/sdk/complex/dry.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <boost/simd/sdk/config.hpp>

#include <nt2/include/constants/half.hpp>
#include <nt2/include/constants/mhalf.hpp>
#include <nt2/include/constants/mone.hpp>
#include <nt2/include/constants/one.hpp>
#include <nt2/include/constants/zero.hpp>
#include <nt2/include/constants/inf.hpp>
#include <nt2/include/constants/minf.hpp>
#include <nt2/include/constants/nan.hpp>

NT2_TEST_CASE_TPL ( round_real,  BOOST_SIMD_REAL_TYPES)
{
  using nt2::round;
  using nt2::tag::round_;
  typedef typename std::complex<T> cT;

  // specific values tests
#ifndef BOOST_SIMD_NO_INVALIDS
  NT2_TEST_EQUAL(round(nt2::Inf<cT>()), nt2::Inf<cT>());
  NT2_TEST_EQUAL(round(nt2::Minf<cT>()), nt2::Minf<cT>());
  NT2_TEST_EQUAL(round(nt2::Nan<cT>()), nt2::Nan<cT>());
#endif
  NT2_TEST_EQUAL(round(cT(T(-1.1))), cT(-1));
  NT2_TEST_EQUAL(round(cT(T(1.1))), cT(1));
  NT2_TEST_EQUAL(round(cT(T(-1.1), T(1.1))), cT(-1, 1));
  NT2_TEST_EQUAL(round(cT(T(1.4))), cT(1));
  NT2_TEST_EQUAL(round(cT(T(1.5))), cT(2));
  NT2_TEST_EQUAL(round(cT(T(1.6))), cT(2));
  NT2_TEST_EQUAL(round(cT(T(2.5))), cT(3));
  NT2_TEST_EQUAL(round(nt2::Half<cT>()), nt2::One<cT>());
  NT2_TEST_EQUAL(round(nt2::Mhalf<cT>()), nt2::Mone<cT>());
  NT2_TEST_EQUAL(round(nt2::Mone<cT>()), nt2::Mone<cT>());
  NT2_TEST_EQUAL(round(nt2::One<cT>()), nt2::One<cT>());
  NT2_TEST_EQUAL(round(nt2::Zero<cT>()), nt2::Zero<cT>());
}

NT2_TEST_CASE_TPL ( round_real2,  BOOST_SIMD_REAL_TYPES)
{

  using boost::simd::round;
  using boost::simd::tag::round_;
 typedef typename std::complex<T> cT;

  // specific values tests
#ifndef BOOST_SIMD_NO_INVALIDS
  NT2_TEST_EQUAL(round(boost::simd::Inf<cT>(), 2), boost::simd::Inf<cT>());
  NT2_TEST_EQUAL(round(boost::simd::Minf<cT>(), 2), boost::simd::Minf<cT>());
  NT2_TEST_EQUAL(round(boost::simd::Nan<cT>(), 2), boost::simd::Nan<cT>());
#endif
  NT2_TEST_EQUAL(round(boost::simd::Mhalf<cT>(), 2), boost::simd::Mhalf<cT>());
  NT2_TEST_EQUAL(round(boost::simd::Mone<cT>(), 2), boost::simd::Mone<cT>());
  NT2_TEST_EQUAL(round(boost::simd::One<cT>(), 2), boost::simd::One<cT>());
  NT2_TEST_EQUAL(round(boost::simd::Zero<cT>(), 2), boost::simd::Zero<cT>());
  NT2_TEST_EQUAL(round(boost::simd::Maxflint<cT>()-boost::simd::Half<cT>(), 2),boost::simd::Maxflint<cT>());
  NT2_TEST_EQUAL(round(boost::simd::Maxflint<cT>(), 2),boost::simd::Maxflint<cT>());
  NT2_TEST_EQUAL(round(cT(1.44, 1.44), 1), cT(1.4,1.4 ));
  NT2_TEST_EQUAL(round(cT(1.45, 1.45), 1), cT(1.5,1.5 ));
  NT2_TEST_EQUAL(round(cT(1.46, 1.46), 1), cT(1.5,1.5 ));
  NT2_TEST_EQUAL(round(cT(2.45, 2.45), 1), cT(2.5,2.5 ));
  NT2_TEST_EQUAL(round(cT(-1.44,-1.44), 1), cT(-1.4,-1.4));
  NT2_TEST_EQUAL(round(cT(-1.45,-1.45), 1), cT(-1.5,-1.5));
  NT2_TEST_EQUAL(round(cT(-1.46,-1.46), 1), cT(-1.5,-1.5));
  NT2_TEST_EQUAL(round(cT(-2.45,-2.45), 1), cT(-2.5,-2.5));
  NT2_TEST_ULP_EQUAL(round(cT(145,145), -2), cT(100,100), 0.5);
  NT2_TEST_ULP_EQUAL(round(cT(150,150), -2), cT(200,200), 0.5);
  NT2_TEST_ULP_EQUAL(round(cT(156,156), -2), cT(200,200), 0.5);
  NT2_TEST_ULP_EQUAL(round(cT(250,250), -2), cT(300,300), 0.5);
  NT2_TEST_ULP_EQUAL(round(cT(-145,-145), -2), cT(-100,-100), 0.5);
  NT2_TEST_ULP_EQUAL(round(cT(-155,-155), -2), cT(-200,-200), 0.5);
  NT2_TEST_ULP_EQUAL(round(cT(-156,-156), -2), cT(-200,-200), 0.5);
  NT2_TEST_ULP_EQUAL(round(cT(-255,-255), -2), cT(-300,-300), 0.5);
} // end of test for floating_
