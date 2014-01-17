//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <boost/simd/include/functions/dist.hpp>
#include <boost/simd/include/functions/splat.hpp>

#include <boost/simd/include/constants/three.hpp>
#include <boost/simd/include/constants/two.hpp>
#include <boost/simd/include/constants/one.hpp>
#include <boost/simd/include/constants/mone.hpp>
#include <boost/simd/include/constants/valmin.hpp>
#include <boost/simd/include/constants/valmax.hpp>
#include <boost/simd/include/constants/ten.hpp>
#include <boost/simd/include/constants/mten.hpp>
#include <boost/simd/include/constants/inf.hpp>
#include <boost/simd/include/constants/minf.hpp>
#include <boost/simd/include/constants/nan.hpp>

#include <boost/dispatch/functor/meta/call.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>

NT2_TEST_CASE_TPL ( dist_real,  BOOST_SIMD_SIMD_REAL_TYPES)
{
  using boost::simd::dist;
  using boost::simd::tag::dist_;
  using boost::simd::native;

  NT2_TEST_TYPE_IS( typename boost::dispatch::meta::call<dist_(T,T)>::type
                  , T
                  );

#ifndef BOOST_SIMD_NO_INVALIDS
  NT2_TEST_EQUAL(dist(boost::simd::Inf<T>() , boost::simd::Inf<T>()) , boost::simd::Nan<T>());
  NT2_TEST_EQUAL(dist(boost::simd::Minf<T>(), boost::simd::Minf<T>()), boost::simd::Nan<T>());
  NT2_TEST_EQUAL(dist(boost::simd::Nan<T>() , boost::simd::Nan<T>()) , boost::simd::Nan<T>());
#endif

  NT2_TEST_EQUAL(dist(boost::simd::Zero<T>(), boost::simd::Zero<T>()), boost::simd::Zero<T>());
  NT2_TEST_EQUAL(dist(boost::simd::Mone<T>(), boost::simd::One<T>()), boost::simd::Two<T>());
  NT2_TEST_EQUAL(dist(boost::simd::One<T>(), boost::simd::Three<T>()), boost::simd::Two<T>());
}

NT2_TEST_CASE_TPL ( dist_integer_ui,  BOOST_SIMD_SIMD_UNSIGNED_TYPES)
{
  using boost::simd::dist;
  using boost::simd::tag::dist_;

  NT2_TEST_TYPE_IS( typename boost::dispatch::meta::call<dist_(T,T)>::type
                  , T
                  );

  NT2_TEST_EQUAL(dist(boost::simd::Zero<T>(), boost::simd::Zero<T>()), boost::simd::Zero<T>());
  NT2_TEST_EQUAL(dist(boost::simd::One<T>(), boost::simd::Three<T>()), boost::simd::Two<T>());
  NT2_TEST_EQUAL(dist(boost::simd::Valmax<T>(), boost::simd::Zero<T>()), boost::simd::Valmax<T>());
  NT2_TEST_EQUAL(dist(boost::simd::Zero<T>(), boost::simd::Valmax<T>()), boost::simd::Valmax<T>());
}

NT2_TEST_CASE_TPL ( dist_integer_si,  BOOST_SIMD_SIMD_INTEGRAL_SIGNED_TYPES)
{
  using boost::simd::dist;
  using boost::simd::tag::dist_;

  NT2_TEST_TYPE_IS( typename boost::dispatch::meta::call<dist_(T,T)>::type
                  , T
                  );

  NT2_TEST_EQUAL(dist(boost::simd::Zero<T>(), boost::simd::Zero<T>()), boost::simd::Zero<T>());
  NT2_TEST_EQUAL(dist(boost::simd::Mone<T>(), boost::simd::One<T>()), boost::simd::Two<T>());
  NT2_TEST_EQUAL(dist(boost::simd::One<T>(), boost::simd::Three<T>()), boost::simd::Two<T>());
  NT2_TEST_EQUAL(dist(boost::simd::Valmax<T>(), boost::simd::Zero<T>()), boost::simd::Valmax<T>());
  NT2_TEST_EQUAL(dist(boost::simd::Zero<T>(), boost::simd::Valmax<T>()), boost::simd::Valmax<T>());

  NT2_TEST_EQUAL(dist(boost::simd::Ten<T>(), boost::simd::Mten<T>()), boost::simd::splat<T>(20));
  NT2_TEST_EQUAL(dist(boost::simd::Mten<T>(), boost::simd::Ten<T>()), boost::simd::splat<T>(20));
}
