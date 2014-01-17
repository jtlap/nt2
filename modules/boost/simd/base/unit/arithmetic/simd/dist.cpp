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
#include <boost/simd/sdk/simd/native.hpp>
#include <boost/simd/sdk/simd/io.hpp>

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

  typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef native<T,ext_t>                  vT;

  NT2_TEST_TYPE_IS( typename boost::dispatch::meta::call<dist_(vT,vT)>::type
                  , vT
                  );

#ifndef BOOST_SIMD_NO_INVALIDS
  NT2_TEST_EQUAL(dist(boost::simd::Inf<vT>() , boost::simd::Inf<vT>()) , boost::simd::Nan<vT>());
  NT2_TEST_EQUAL(dist(boost::simd::Minf<vT>(), boost::simd::Minf<vT>()), boost::simd::Nan<vT>());
  NT2_TEST_EQUAL(dist(boost::simd::Nan<vT>() , boost::simd::Nan<vT>()) , boost::simd::Nan<vT>());
#endif

  NT2_TEST_EQUAL(dist(boost::simd::Zero<vT>(), boost::simd::Zero<vT>()), boost::simd::Zero<vT>());
  NT2_TEST_EQUAL(dist(boost::simd::Mone<vT>(), boost::simd::One<vT>()), boost::simd::Two<vT>());
  NT2_TEST_EQUAL(dist(boost::simd::One<vT>(), boost::simd::Three<vT>()), boost::simd::Two<vT>());
}

NT2_TEST_CASE_TPL ( dist_integer_ui,  BOOST_SIMD_SIMD_UNSIGNED_TYPES)
{
  using boost::simd::dist;
  using boost::simd::tag::dist_;
  using boost::simd::native;

  typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef native<T,ext_t>                  vT;

  NT2_TEST_TYPE_IS( typename boost::dispatch::meta::call<dist_(vT,vT)>::type
                  , vT
                  );

  NT2_TEST_EQUAL(dist(boost::simd::Zero<vT>(), boost::simd::Zero<vT>()), boost::simd::Zero<vT>());
  NT2_TEST_EQUAL(dist(boost::simd::One<vT>(), boost::simd::Three<vT>()), boost::simd::Two<vT>());
  NT2_TEST_EQUAL(dist(boost::simd::Valmax<vT>(), boost::simd::Zero<vT>()), boost::simd::Valmax<vT>());
  NT2_TEST_EQUAL(dist(boost::simd::Zero<vT>(), boost::simd::Valmax<vT>()), boost::simd::Valmax<vT>());
}

NT2_TEST_CASE_TPL ( dist_integer_si,  BOOST_SIMD_SIMD_INTEGRAL_SIGNED_TYPES)
{
  using boost::simd::dist;
  using boost::simd::tag::dist_;
  using boost::simd::native;

  typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef native<T,ext_t>                  vT;

  NT2_TEST_TYPE_IS( typename boost::dispatch::meta::call<dist_(vT,vT)>::type
                  , vT
                  );

  NT2_TEST_EQUAL(dist(boost::simd::Zero<vT>(), boost::simd::Zero<vT>()), boost::simd::Zero<vT>());
  NT2_TEST_EQUAL(dist(boost::simd::Mone<vT>(), boost::simd::One<vT>()), boost::simd::Two<vT>());
  NT2_TEST_EQUAL(dist(boost::simd::One<vT>(), boost::simd::Three<vT>()), boost::simd::Two<vT>());
  NT2_TEST_EQUAL(dist(boost::simd::Valmax<vT>(), boost::simd::Zero<vT>()), boost::simd::Valmax<vT>());
  NT2_TEST_EQUAL(dist(boost::simd::Zero<vT>(), boost::simd::Valmax<vT>()), boost::simd::Valmax<vT>());

  NT2_TEST_EQUAL(dist(boost::simd::Ten<vT>(), boost::simd::Mten<vT>()), boost::simd::splat<vT>(20));
  NT2_TEST_EQUAL(dist(boost::simd::Mten<vT>(), boost::simd::Ten<vT>()), boost::simd::splat<vT>(20));
}
