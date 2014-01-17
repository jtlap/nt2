//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/include/functions/dist.hpp>
#include <nt2/include/functions/splat.hpp>
#include <boost/simd/sdk/simd/native.hpp>
#include <boost/simd/sdk/simd/io.hpp>

#include <nt2/include/constants/three.hpp>
#include <nt2/include/constants/two.hpp>
#include <nt2/include/constants/one.hpp>
#include <nt2/include/constants/mone.hpp>
#include <nt2/include/constants/valmax.hpp>
#include <nt2/include/constants/valmin.hpp>
#include <nt2/include/constants/ten.hpp>
#include <nt2/include/constants/mten.hpp>
#include <nt2/include/constants/inf.hpp>
#include <nt2/include/constants/minf.hpp>
#include <nt2/include/constants/nan.hpp>

#include <boost/dispatch/functor/meta/call.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>

NT2_TEST_CASE_TPL ( dist_real,  BOOST_SIMD_SIMD_REAL_TYPES)
{
  using nt2::dist;
  using nt2::tag::dist_;
  using boost::simd::native;

  typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef native<T,ext_t>                  vT;

  NT2_TEST_TYPE_IS( typename boost::dispatch::meta::call<dist_(vT,vT)>::type
                  , vT
                  );

#ifndef BOOST_SIMD_NO_INVALIDS
  NT2_TEST_EQUAL(dist(nt2::Inf<vT>() , nt2::Inf<vT>()) , nt2::Nan<vT>());
  NT2_TEST_EQUAL(dist(nt2::Minf<vT>(), nt2::Minf<vT>()), nt2::Nan<vT>());
  NT2_TEST_EQUAL(dist(nt2::Nan<vT>() , nt2::Nan<vT>()) , nt2::Nan<vT>());
#endif

  NT2_TEST_EQUAL(dist(nt2::Zero<vT>(), nt2::Zero<vT>()), nt2::Zero<vT>());
  NT2_TEST_EQUAL(dist(nt2::Mone<vT>(), nt2::One<vT>()), nt2::Two<vT>());
  NT2_TEST_EQUAL(dist(nt2::One<vT>(), nt2::Three<vT>()), nt2::Two<vT>());
}

NT2_TEST_CASE_TPL ( dist_integer_ui,  BOOST_SIMD_SIMD_UNSIGNED_TYPES)
{
  using nt2::dist;
  using nt2::tag::dist_;
  using boost::simd::native;

  typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef native<T,ext_t>                  vT;

  NT2_TEST_TYPE_IS( typename boost::dispatch::meta::call<dist_(vT,vT)>::type
                  , vT
                  );

  NT2_TEST_EQUAL(dist(nt2::Zero<vT>(), nt2::Zero<vT>()), nt2::Zero<vT>());
  NT2_TEST_EQUAL(dist(nt2::One<vT>(), nt2::Three<vT>()), nt2::Two<vT>());
  NT2_TEST_EQUAL(dist(nt2::Valmax<vT>(), nt2::Zero<vT>()), nt2::Valmax<vT>());
  NT2_TEST_EQUAL(dist(nt2::Zero<vT>(), nt2::Valmax<vT>()), nt2::Valmax<vT>());
}

NT2_TEST_CASE_TPL ( dist_integer_si,  BOOST_SIMD_SIMD_INTEGRAL_SIGNED_TYPES)
{
  using nt2::dist;
  using nt2::tag::dist_;
  using boost::simd::native;

  typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef native<T,ext_t>                  vT;

  NT2_TEST_TYPE_IS( typename boost::dispatch::meta::call<dist_(vT,vT)>::type
                  , vT
                  );

  NT2_TEST_EQUAL(dist(nt2::Zero<vT>(), nt2::Zero<vT>()), nt2::Zero<vT>());
  NT2_TEST_EQUAL(dist(nt2::Mone<vT>(), nt2::One<vT>()), nt2::Two<vT>());
  NT2_TEST_EQUAL(dist(nt2::One<vT>(), nt2::Three<vT>()), nt2::Two<vT>());
  NT2_TEST_EQUAL(dist(nt2::Valmax<vT>(), nt2::Zero<vT>()), nt2::Valmax<vT>());
  NT2_TEST_EQUAL(dist(nt2::Zero<vT>(), nt2::Valmax<vT>()), nt2::Valmax<vT>());

  NT2_TEST_EQUAL(dist(nt2::Ten<vT>(), nt2::Mten<vT>()), nt2::splat<vT>(20));
  NT2_TEST_EQUAL(dist(nt2::Mten<vT>(), nt2::Ten<vT>()), nt2::splat<vT>(20));
}
