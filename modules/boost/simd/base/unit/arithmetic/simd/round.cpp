//==============================================================================
//         Copyright 2015          J.T. Lapreste
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <boost/simd/arithmetic/include/functions/round.hpp>
#include <boost/simd/sdk/simd/native.hpp>
#include <boost/dispatch/functor/meta/call.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/ulp.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <boost/simd/include/constants/zero.hpp>
#include <boost/simd/include/constants/one.hpp>
#include <boost/simd/include/constants/mone.hpp>
#include <boost/simd/include/constants/inf.hpp>
#include <boost/simd/include/constants/minf.hpp>
#include <boost/simd/include/constants/nan.hpp>
#include <boost/simd/include/constants/valmax.hpp>
#include <boost/simd/include/constants/valmin.hpp>
#include <boost/simd/include/constants/maxflint.hpp>
#include <boost/simd/include/constants/half.hpp>

#include <boost/simd/sdk/config.hpp>
#include <boost/simd/sdk/simd/io.hpp>
#include <boost/simd/include/functions/prev.hpp>
#include <boost/simd/include/functions/next.hpp>
#include <boost/simd/include/functions/splat.hpp>
#include <boost/simd/include/functions/multiplies.hpp>
#include <boost/simd/include/functions/plus.hpp>
#include <boost/simd/include/functions/splat.hpp>

NT2_TEST_CASE_TPL ( round_real, BOOST_SIMD_SIMD_REAL_TYPES)
{
  using boost::simd::round;
  using boost::simd::tag::round_;
  using boost::simd::next;
  using boost::simd::prev;
  using boost::simd::native;
  typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef native<T,ext_t>                  vT;
  typedef typename boost::dispatch::meta::call<round_(vT)>::type r_t;

  // specific values tests
#ifndef BOOST_SIMD_NO_INVALIDS
  NT2_TEST_EQUAL(round(boost::simd::Inf<vT>()), boost::simd::Inf<r_t>());
  NT2_TEST_EQUAL(round(boost::simd::Minf<vT>()), boost::simd::Minf<r_t>());
  NT2_TEST_EQUAL(round(boost::simd::Nan<vT>()), boost::simd::Nan<r_t>());
#endif
  NT2_TEST_EQUAL(round(boost::simd::splat<vT>(1.4)), boost::simd::One<r_t>());
  NT2_TEST_EQUAL(round(boost::simd::splat<vT>(1.5)), boost::simd::Two<r_t>());
  NT2_TEST_EQUAL(round(boost::simd::splat<vT>(1.6)), boost::simd::Two<r_t>());
  NT2_TEST_EQUAL(round(boost::simd::splat<vT>(2.5)), boost::simd::Three<r_t>());
  NT2_TEST_EQUAL(round(boost::simd::Half<vT>()), boost::simd::One<r_t>());
  NT2_TEST_EQUAL(round(boost::simd::Mhalf<vT>()), boost::simd::Mone<r_t>());
  NT2_TEST_EQUAL(round(boost::simd::Mone<vT>()), boost::simd::Mone<r_t>());
  NT2_TEST_EQUAL(round(boost::simd::One<vT>()), boost::simd::One<r_t>());
  NT2_TEST_EQUAL(round(boost::simd::Zero<vT>()), boost::simd::Zero<r_t>());
  NT2_TEST_EQUAL(round(boost::simd::Maxflint<vT>()-boost::simd::Half<T>()),boost::simd::Maxflint<vT>());
  NT2_TEST_EQUAL(round(boost::simd::Maxflint<vT>()),boost::simd::Maxflint<vT>());
  NT2_TEST_EQUAL(round(prev(prev(boost::simd::Half<vT>()))),  boost::simd::Zero<vT>());
  NT2_TEST_EQUAL(round(prev(boost::simd::Half<vT>())),  boost::simd::Zero<vT>());
  NT2_TEST_EQUAL(round(     boost::simd::Half<vT>()) ,  boost::simd::One <vT>());
  NT2_TEST_EQUAL(round(next(boost::simd::Half<vT>())),  boost::simd::One <vT>());
  vT z = boost::simd::Maxflint <vT>()*boost::simd::Half<vT>()+boost::simd::One<vT>();
  NT2_TEST_EQUAL(round(z), z);
} // end of test for floating_

NT2_TEST_CASE_TPL ( round_real2,  BOOST_SIMD_SIMD_REAL_TYPES)
{

  using boost::simd::round;
  using boost::simd::tag::round_;
  using boost::simd::native;
  typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef native<T,ext_t>                  vT;
  typedef typename boost::dispatch::meta::call<round_(vT)>::type r_t;

  // specific values tests
#ifndef BOOST_SIMD_NO_INVALIDS
  NT2_TEST_EQUAL(round(boost::simd::Inf<vT>(), 2), boost::simd::Inf<r_t>());
  NT2_TEST_EQUAL(round(boost::simd::Minf<vT>(), 2), boost::simd::Minf<r_t>());
  NT2_TEST_EQUAL(round(boost::simd::Nan<vT>(), 2), boost::simd::Nan<r_t>());
#endif
  NT2_TEST_EQUAL(round(boost::simd::Mhalf<vT>(), 2), boost::simd::Mhalf<r_t>());
  NT2_TEST_EQUAL(round(boost::simd::Mone<vT>(), 2), boost::simd::Mone<r_t>());
  NT2_TEST_EQUAL(round(boost::simd::One<vT>(), 2), boost::simd::One<r_t>());
  NT2_TEST_EQUAL(round(boost::simd::Zero<vT>(), 2), boost::simd::Zero<r_t>());
  NT2_TEST_EQUAL(round(boost::simd::Maxflint<vT>()-boost::simd::Half<vT>(), 2),boost::simd::Maxflint<vT>());
  NT2_TEST_EQUAL(round(boost::simd::Maxflint<vT>(), 2),boost::simd::Maxflint<vT>());
  NT2_TEST_EQUAL(round(boost::simd::splat<vT>(1.44), 1), boost::simd::splat<vT>(1.4));
  NT2_TEST_EQUAL(round(boost::simd::splat<vT>(1.45), 1), boost::simd::splat<vT>(1.5));
  NT2_TEST_EQUAL(round(boost::simd::splat<vT>(1.46), 1), boost::simd::splat<vT>(1.5));
  NT2_TEST_EQUAL(round(boost::simd::splat<vT>(2.45), 1), boost::simd::splat<vT>(2.5));
  NT2_TEST_EQUAL(round(boost::simd::splat<vT>(-1.44), 1), boost::simd::splat<vT>(-1.4));
  NT2_TEST_EQUAL(round(boost::simd::splat<vT>(-1.45), 1), boost::simd::splat<vT>(-1.5));
  NT2_TEST_EQUAL(round(boost::simd::splat<vT>(-1.46), 1), boost::simd::splat<vT>(-1.5));
  NT2_TEST_EQUAL(round(boost::simd::splat<vT>(-2.45), 1), boost::simd::splat<vT>(-2.5));
  NT2_TEST_ULP_EQUAL(round(boost::simd::splat<vT>(145), -2), boost::simd::splat<vT>(100), 0.5);
  NT2_TEST_ULP_EQUAL(round(boost::simd::splat<vT>(150), -2), boost::simd::splat<vT>(200), 0.5);
  NT2_TEST_ULP_EQUAL(round(boost::simd::splat<vT>(156), -2), boost::simd::splat<vT>(200), 0.5);
  NT2_TEST_ULP_EQUAL(round(boost::simd::splat<vT>(250), -2), boost::simd::splat<vT>(300), 0.5);
  NT2_TEST_ULP_EQUAL(round(boost::simd::splat<vT>(-145), -2), boost::simd::splat<vT>(-100), 0.5);
  NT2_TEST_ULP_EQUAL(round(boost::simd::splat<vT>(-155), -2), boost::simd::splat<vT>(-200), 0.5);
  NT2_TEST_ULP_EQUAL(round(boost::simd::splat<vT>(-156), -2), boost::simd::splat<vT>(-200), 0.5);
  NT2_TEST_ULP_EQUAL(round(boost::simd::splat<vT>(-255), -2), boost::simd::splat<vT>(-300), 0.5);
} // end of test for floating_

NT2_TEST_CASE_TPL ( round_real2b,  BOOST_SIMD_SIMD_REAL_TYPES)
{

  using boost::simd::round;
  using boost::simd::tag::round_;
  using boost::simd::native;
  using boost::simd::splat;
  typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef native<T,ext_t>                  vT;
  typedef typename boost::dispatch::meta::as_integer<vT>::type viT;
  typedef typename boost::dispatch::meta::call<round_(vT)>::type r_t;

  // specific values tests
#ifndef BOOST_SIMD_NO_INVALIDS
  NT2_TEST_EQUAL(round(boost::simd::Inf<vT>(), splat<viT>(2)), boost::simd::Inf<r_t>());
  NT2_TEST_EQUAL(round(boost::simd::Minf<vT>(), splat<viT>(2)), boost::simd::Minf<r_t>());
  NT2_TEST_EQUAL(round(boost::simd::Nan<vT>(), splat<viT>(2)), boost::simd::Nan<r_t>());
#endif
  NT2_TEST_EQUAL(round(boost::simd::Mhalf<vT>(), splat<viT>(2)), boost::simd::Mhalf<r_t>());
  NT2_TEST_EQUAL(round(boost::simd::Mone<vT>(), splat<viT>(2)), boost::simd::Mone<r_t>());
  NT2_TEST_EQUAL(round(boost::simd::One<vT>(), splat<viT>(2)), boost::simd::One<r_t>());
  NT2_TEST_EQUAL(round(boost::simd::Zero<vT>(), splat<viT>(2)), boost::simd::Zero<r_t>());
  NT2_TEST_EQUAL(round(boost::simd::Maxflint<vT>()-boost::simd::Half<vT>(), splat<viT>(2)),boost::simd::Maxflint<vT>());
  NT2_TEST_EQUAL(round(boost::simd::Maxflint<vT>(), splat<viT>(2)),boost::simd::Maxflint<vT>());
  NT2_TEST_EQUAL(round(boost::simd::splat<vT>(1.44), splat<viT>(1)), boost::simd::splat<vT>(1.4));
  NT2_TEST_EQUAL(round(boost::simd::splat<vT>(1.45), splat<viT>(1)), boost::simd::splat<vT>(1.5));
  NT2_TEST_EQUAL(round(boost::simd::splat<vT>(1.46), splat<viT>(1)), boost::simd::splat<vT>(1.5));
  NT2_TEST_EQUAL(round(boost::simd::splat<vT>(2.45), splat<viT>(1)), boost::simd::splat<vT>(2.5));
  NT2_TEST_EQUAL(round(boost::simd::splat<vT>(-1.44), splat<viT>(1)), boost::simd::splat<vT>(-1.4));
  NT2_TEST_EQUAL(round(boost::simd::splat<vT>(-1.45), splat<viT>(1)), boost::simd::splat<vT>(-1.5));
  NT2_TEST_EQUAL(round(boost::simd::splat<vT>(-1.46), splat<viT>(1)), boost::simd::splat<vT>(-1.5));
  NT2_TEST_EQUAL(round(boost::simd::splat<vT>(-2.45), splat<viT>(1)), boost::simd::splat<vT>(-2.5));
  NT2_TEST_ULP_EQUAL(round(boost::simd::splat<vT>(145), splat<viT>(-2)), boost::simd::splat<vT>(100), 0.5);
  NT2_TEST_ULP_EQUAL(round(boost::simd::splat<vT>(150), splat<viT>(-2)), boost::simd::splat<vT>(200), 0.5);
  NT2_TEST_ULP_EQUAL(round(boost::simd::splat<vT>(156), splat<viT>(-2)), boost::simd::splat<vT>(200), 0.5);
  NT2_TEST_ULP_EQUAL(round(boost::simd::splat<vT>(250), splat<viT>(-2)), boost::simd::splat<vT>(300), 0.5);
  NT2_TEST_ULP_EQUAL(round(boost::simd::splat<vT>(-145), splat<viT>(-2)), boost::simd::splat<vT>(-100), 0.5);
  NT2_TEST_ULP_EQUAL(round(boost::simd::splat<vT>(-155), splat<viT>(-2)), boost::simd::splat<vT>(-200), 0.5);
  NT2_TEST_ULP_EQUAL(round(boost::simd::splat<vT>(-156), splat<viT>(-2)), boost::simd::splat<vT>(-200), 0.5);
  NT2_TEST_ULP_EQUAL(round(boost::simd::splat<vT>(-255), splat<viT>(-2)), boost::simd::splat<vT>(-300), 0.5);
} // end of test for floating_

NT2_TEST_CASE_TPL ( round_unsigned_int,  BOOST_SIMD_SIMD_UNSIGNED_TYPES)
{
  using boost::simd::round;
  using boost::simd::tag::round_;
  using boost::simd::native;
  typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef native<T,ext_t>                  vT;
  typedef typename boost::dispatch::meta::call<round_(vT)>::type r_t;

  // specific values tests
  NT2_TEST_EQUAL(round(boost::simd::One<vT>()), boost::simd::One<r_t>());
  NT2_TEST_EQUAL(round(boost::simd::Valmax<vT>()), boost::simd::Valmax<r_t>());
  NT2_TEST_EQUAL(round(boost::simd::Valmin<vT>()), boost::simd::Valmin<r_t>());
  NT2_TEST_EQUAL(round(boost::simd::Zero<vT>()), boost::simd::Zero<r_t>());
} // end of test for unsigned_int_

NT2_TEST_CASE_TPL ( round_signed_int,  BOOST_SIMD_SIMD_INTEGRAL_SIGNED_TYPES)
{
  using boost::simd::round;
  using boost::simd::tag::round_;
  using boost::simd::native;
  typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef native<T,ext_t>                  vT;
  typedef typename boost::dispatch::meta::call<round_(vT)>::type r_t;

  // specific values tests
  NT2_TEST_EQUAL(round(boost::simd::Mone<vT>()), boost::simd::Mone<r_t>());
  NT2_TEST_EQUAL(round(boost::simd::One<vT>()), boost::simd::One<r_t>());
  NT2_TEST_EQUAL(round(boost::simd::Valmax<vT>()), boost::simd::Valmax<r_t>());
  NT2_TEST_EQUAL(round(boost::simd::Valmin<vT>()), boost::simd::Valmin<r_t>());
  NT2_TEST_EQUAL(round(boost::simd::Zero<vT>()), boost::simd::Zero<r_t>());
} // end of test for signed_int_

