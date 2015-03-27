//==============================================================================
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
#include <boost/simd/sdk/simd/io.hpp>
#include <boost/simd/sdk/simd/native.hpp>
#include <complex>
#include <nt2/sdk/complex/complex.hpp>
#include <nt2/sdk/complex/dry.hpp>
#include <nt2/sdk/unit/tests/ulp.hpp>
#include <nt2/sdk/meta/as_integer.hpp>
#include <nt2/include/functions/splat.hpp>
#include <nt2/include/functions/minus.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <boost/simd/sdk/config.hpp>

#include <nt2/include/constants/mone.hpp>
#include <nt2/include/constants/mhalf.hpp>
#include <nt2/include/constants/half.hpp>
#include <nt2/include/constants/one.hpp>
#include <nt2/include/constants/zero.hpp>
#include <nt2/include/constants/inf.hpp>
#include <nt2/include/constants/minf.hpp>
#include <nt2/include/constants/nan.hpp>
#include <nt2/include/constants/maxflint.hpp>

NT2_TEST_CASE_TPL ( round_cplx,  BOOST_SIMD_SIMD_REAL_TYPES)
{
  using nt2::round;
  using nt2::tag::round_;
  typedef typename std::complex<T> cT;
  using boost::simd::native;
  typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef native<cT,ext_t>                vcT;
  typedef typename nt2::dry<T>             dT;
  typedef native<dT,ext_t>                vdT;

  // specific values tests
#ifndef BOOST_SIMD_NO_INVALIDS
    NT2_TEST_ULP_EQUAL(nt2::round(nt2::Inf<vcT>()), nt2::Inf<vcT>(),0);
    NT2_TEST_ULP_EQUAL(nt2::round(nt2::Minf<vcT>()), nt2::Minf<vcT>(),0);
    NT2_TEST_ULP_EQUAL(nt2::round(nt2::Nan<vcT>()), nt2::Nan<vcT>(),0);
    NT2_TEST_ULP_EQUAL(nt2::round(nt2::Inf<vdT>()), nt2::Inf<vdT>(),0);
    NT2_TEST_ULP_EQUAL(nt2::round(nt2::Minf<vdT>()), nt2::Minf<vdT>(),0);
    NT2_TEST_ULP_EQUAL(nt2::round(nt2::Nan<vdT>()), nt2::Nan<vdT>(),0);
#endif
    NT2_TEST_ULP_EQUAL(nt2::round(nt2::splat<vcT>(cT(-1.1, -1.6))), nt2::splat<vcT>(cT(-1, -2)),0);
    NT2_TEST_ULP_EQUAL(nt2::round(nt2::splat<vcT>(cT(1.1, 1.6))),  nt2::splat<vcT>(cT(1, 2)),0);
    NT2_TEST_ULP_EQUAL(nt2::round(nt2::Mone<vcT>()), nt2::Mone<vcT>(),0);
    NT2_TEST_ULP_EQUAL(nt2::round(nt2::One<vcT>()), nt2::One<vcT>(),0);
    NT2_TEST_ULP_EQUAL(nt2::round(nt2::Zero<vcT>()), nt2::Zero<vcT>(),0);
    NT2_TEST_ULP_EQUAL(nt2::round(nt2::splat<vdT>(dT(-1.1))), nt2::Mone<vdT>(),0);
    NT2_TEST_ULP_EQUAL(nt2::round(nt2::splat<vdT>(dT(1.1))), nt2::One<vdT>(),0);
    NT2_TEST_ULP_EQUAL(nt2::round(nt2::Mone<vdT>()), nt2::Mone<vdT>(),0);
    NT2_TEST_ULP_EQUAL(nt2::round(nt2::One<vdT>()), nt2::One<vdT>(),0);
    NT2_TEST_ULP_EQUAL(nt2::round(nt2::Zero<vdT>()), nt2::Zero<vdT>(),0);
}

NT2_TEST_CASE_TPL ( round_real2,  BOOST_SIMD_SIMD_REAL_TYPES)
{

  using nt2::round;
  using nt2::tag::round_;
  typedef typename std::complex<T> cT;
  using boost::simd::native;
  typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef native<cT,ext_t>                vcT;
  typedef nt2::dry<T>                      dT;
  typedef native<dT,ext_t>                vdT;

  // specific values tests
#ifndef BOOST_SIMD_NO_INVALIDS
  NT2_TEST_EQUAL(round(nt2::Inf<vcT>(), 2), nt2::Inf<vcT>());
  NT2_TEST_EQUAL(round(nt2::Minf<vcT>(), 2), nt2::Minf<vcT>());
  NT2_TEST_EQUAL(round(nt2::Nan<vcT>(), 2), nt2::Nan<vcT>());
#endif
  NT2_TEST_EQUAL(round(nt2::Mhalf<vcT>(), 2), nt2::Mhalf<vcT>());
  NT2_TEST_EQUAL(round(nt2::Mone<vcT>(), 2), nt2::Mone<vcT>());
  NT2_TEST_EQUAL(round(nt2::One<vcT>(), 2), nt2::One<vcT>());
  NT2_TEST_EQUAL(round(nt2::Zero<vcT>(), 2), nt2::Zero<vcT>());
  NT2_TEST_EQUAL(round(nt2::Maxflint<vcT>()-nt2::Half<vcT>(), 2),nt2::Maxflint<vcT>());
  NT2_TEST_EQUAL(round(nt2::Maxflint<vcT>(), 2),nt2::Maxflint<vcT>());
  NT2_TEST_EQUAL(round(nt2::splat<vcT>(cT(1.44, 1.44)), 1), nt2::splat<vcT>(cT(1.4,1.4 )));
  NT2_TEST_EQUAL(round(nt2::splat<vcT>(cT(1.45, 1.45)), 1), nt2::splat<vcT>(cT(1.5,1.5 )));
  NT2_TEST_EQUAL(round(nt2::splat<vcT>(cT(1.46, 1.46)), 1), nt2::splat<vcT>(cT(1.5,1.5 )));
  NT2_TEST_EQUAL(round(nt2::splat<vcT>(cT(2.45, 2.45)), 1), nt2::splat<vcT>(cT(2.5,2.5 )));
  NT2_TEST_EQUAL(round(nt2::splat<vcT>(cT(-1.44,-1.44)), 1), nt2::splat<vcT>(cT(-1.4,-1.4)));
  NT2_TEST_EQUAL(round(nt2::splat<vcT>(cT(-1.45,-1.45)), 1), nt2::splat<vcT>(cT(-1.5,-1.5)));
  NT2_TEST_EQUAL(round(nt2::splat<vcT>(cT(-1.46,-1.46)), 1), nt2::splat<vcT>(cT(-1.5,-1.5)));
  NT2_TEST_EQUAL(round(nt2::splat<vcT>(cT(-2.45,-2.45)), 1), nt2::splat<vcT>(cT(-2.5,-2.5)));
  NT2_TEST_ULP_EQUAL(round(nt2::splat<vcT>(cT(145,145)), -2), nt2::splat<vcT>(cT(100,100)), 0.5);
  NT2_TEST_ULP_EQUAL(round(nt2::splat<vcT>(cT(150,150)), -2), nt2::splat<vcT>(cT(200,200)), 0.5);
  NT2_TEST_ULP_EQUAL(round(nt2::splat<vcT>(cT(156,156)), -2), nt2::splat<vcT>(cT(200,200)), 0.5);
  NT2_TEST_ULP_EQUAL(round(nt2::splat<vcT>(cT(250,250)), -2), nt2::splat<vcT>(cT(300,300)), 0.5);
  NT2_TEST_ULP_EQUAL(round(nt2::splat<vcT>(cT(-145,-145)), -2), nt2::splat<vcT>(cT(-100,-100)), 0.5);
  NT2_TEST_ULP_EQUAL(round(nt2::splat<vcT>(cT(-155,-155)), -2), nt2::splat<vcT>(cT(-200,-200)), 0.5);
  NT2_TEST_ULP_EQUAL(round(nt2::splat<vcT>(cT(-156,-156)), -2), nt2::splat<vcT>(cT(-200,-200)), 0.5);
  NT2_TEST_ULP_EQUAL(round(nt2::splat<vcT>(cT(-255,-255)), -2), nt2::splat<vcT>(cT(-300,-300)), 0.5);
  NT2_TEST_ULP_EQUAL(nt2::round(nt2::splat<vdT>(dT(-1.11)), 1),  nt2::splat<vdT>(dT(-1.1)),0);
} // end of test for floating_

NT2_TEST_CASE_TPL ( round_real2b,  BOOST_SIMD_SIMD_REAL_TYPES)
{

  using nt2::round;
  using nt2::tag::round_;
  typedef typename std::complex<T> cT;
  using boost::simd::native;
  typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef native<cT,ext_t>                vcT;
  typedef native<T ,ext_t>                vT;
  typedef typename nt2::meta::as_integer<vT>::type viT;
  typedef nt2::dry<T>                      dT;
  typedef native<dT ,ext_t>               vdT;

  // specific values tests
#ifndef BOOST_SIMD_NO_INVALIDS
  NT2_TEST_EQUAL(nt2::round(nt2::Inf<vcT>(), nt2::splat<viT>(2)), nt2::Inf<vcT>());
  NT2_TEST_EQUAL(nt2::round(nt2::Minf<vcT>(), nt2::splat<viT>(2)), nt2::Minf<vcT>());
  NT2_TEST_EQUAL(nt2::round(nt2::Nan<vcT>(), nt2::splat<viT>(2)), nt2::Nan<vcT>());
#endif
  NT2_TEST_EQUAL(nt2::round(nt2::Mhalf<vcT>(), nt2::splat<viT>(2)), nt2::Mhalf<vcT>());
  NT2_TEST_EQUAL(nt2::round(nt2::Mone<vcT>(), nt2::splat<viT>(2)), nt2::Mone<vcT>());
  NT2_TEST_EQUAL(nt2::round(nt2::One<vcT>(), nt2::splat<viT>(2)), nt2::One<vcT>());
  NT2_TEST_EQUAL(nt2::round(nt2::Zero<vcT>(), nt2::splat<viT>(2)), nt2::Zero<vcT>());
  NT2_TEST_EQUAL(nt2::round(nt2::Maxflint<vcT>()-nt2::Half<vcT>(), nt2::splat<viT>(2)),nt2::Maxflint<vcT>());
  NT2_TEST_EQUAL(nt2::round(nt2::Maxflint<vcT>(), nt2::splat<viT>(2)),nt2::Maxflint<vcT>());
  NT2_TEST_EQUAL(nt2::round(nt2::splat<vcT>(cT(1.44, 1.44)), nt2::splat<viT>(1)), nt2::splat<vcT>(cT(1.4,1.4 )));
  NT2_TEST_EQUAL(nt2::round(nt2::splat<vcT>(cT(1.45, 1.45)), nt2::splat<viT>(1)), nt2::splat<vcT>(cT(1.5,1.5 )));
  NT2_TEST_EQUAL(nt2::round(nt2::splat<vcT>(cT(1.46, 1.46)), nt2::splat<viT>(1)), nt2::splat<vcT>(cT(1.5,1.5 )));
  NT2_TEST_EQUAL(nt2::round(nt2::splat<vcT>(cT(2.45, 2.45)), nt2::splat<viT>(1)), nt2::splat<vcT>(cT(2.5,2.5 )));
  NT2_TEST_EQUAL(nt2::round(nt2::splat<vcT>(cT(-1.44,-1.44)), nt2::splat<viT>(1)), nt2::splat<vcT>(cT(-1.4,-1.4)));
  NT2_TEST_EQUAL(nt2::round(nt2::splat<vcT>(cT(-1.45,-1.45)), nt2::splat<viT>(1)), nt2::splat<vcT>(cT(-1.5,-1.5)));
  NT2_TEST_EQUAL(nt2::round(nt2::splat<vcT>(cT(-1.46,-1.46)), nt2::splat<viT>(1)), nt2::splat<vcT>(cT(-1.5,-1.5)));
  NT2_TEST_EQUAL(nt2::round(nt2::splat<vcT>(cT(-2.45,-2.45)), nt2::splat<viT>(1)), nt2::splat<vcT>(cT(-2.5,-2.5)));
  NT2_TEST_ULP_EQUAL(nt2::round(nt2::splat<vcT>(cT(145,145)), nt2::splat<viT>(-2)), nt2::splat<vcT>(cT(100,100)), 0.5);
  NT2_TEST_ULP_EQUAL(nt2::round(nt2::splat<vcT>(cT(150,150)), nt2::splat<viT>(-2)), nt2::splat<vcT>(cT(200,200)), 0.5);
  NT2_TEST_ULP_EQUAL(nt2::round(nt2::splat<vcT>(cT(156,156)), nt2::splat<viT>(-2)), nt2::splat<vcT>(cT(200,200)), 0.5);
  NT2_TEST_ULP_EQUAL(nt2::round(nt2::splat<vcT>(cT(250,250)), nt2::splat<viT>(-2)), nt2::splat<vcT>(cT(300,300)), 0.5);
  NT2_TEST_ULP_EQUAL(nt2::round(nt2::splat<vcT>(cT(-145,-145)), nt2::splat<viT>(-2)), nt2::splat<vcT>(cT(-100,-100)), 0.5);
  NT2_TEST_ULP_EQUAL(nt2::round(nt2::splat<vcT>(cT(-155,-155)), nt2::splat<viT>(-2)), nt2::splat<vcT>(cT(-200,-200)), 0.5);
  NT2_TEST_ULP_EQUAL(nt2::round(nt2::splat<vcT>(cT(-156,-156)), nt2::splat<viT>(-2)), nt2::splat<vcT>(cT(-200,-200)), 0.5);
  NT2_TEST_ULP_EQUAL(nt2::round(nt2::splat<vcT>(cT(-255,-255)), nt2::splat<viT>(-2)), nt2::splat<vcT>(cT(-300,-300)), 0.5);
  NT2_TEST_ULP_EQUAL(nt2::round(nt2::splat<vdT>(dT(-1.11)), nt2::splat<viT>(1)),  nt2::splat<vdT>(dT(-1.1)),0);
} // end of test for floating_

