//==============================================================================
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/exponential/include/functions/realpow.hpp>

#include <nt2/sdk/functor/meta/call.hpp>
#include <boost/simd/sdk/simd/native.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>
#include <nt2/sdk/unit/tests/ulp.hpp>
#include <nt2/sdk/unit/tests/exceptions.hpp>
#include <nt2/include/functions/splat.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <boost/simd/sdk/config.hpp>
#include <boost/simd/sdk/simd/io.hpp>

#include <nt2/include/constants/half.hpp>
#include <nt2/include/constants/mone.hpp>
#include <nt2/include/constants/one.hpp>
#include <nt2/include/constants/two.hpp>
#include <nt2/include/constants/zero.hpp>
#include <nt2/include/constants/inf.hpp>
#include <nt2/include/constants/minf.hpp>
#include <nt2/include/constants/nan.hpp>

NT2_TEST_CASE_TPL ( realpow,  NT2_SIMD_REAL_TYPES)
{
  using nt2::realpow;
  using nt2::tag::realpow_;
  using boost::simd::native;
  typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef native<T,ext_t>                  vT;

  typedef typename nt2::meta::call<realpow_(vT,vT)>::type r_t;
  typedef vT wished_r_t;

  // return type conformity test
  NT2_TEST_TYPE_IS(r_t, wished_r_t);


  // specific values tests
#ifndef BOOST_SIMD_NO_INVALIDS
  NT2_TEST_ULP_EQUAL(realpow(nt2::Inf<vT>(), nt2::Inf<vT>()), nt2::Inf<r_t>(), 0);
  NT2_TEST_ASSERT(realpow(nt2::Minf<vT>(), nt2::Minf<vT>()));
  NT2_TEST_ULP_EQUAL(realpow(nt2::Nan<vT>(), nt2::Nan<vT>()), nt2::Nan<r_t>(), 0);
#endif
  NT2_TEST_ASSERT(realpow(nt2::Mone<vT>(), nt2::Half<vT>()));
  NT2_TEST_ULP_EQUAL(realpow(nt2::One<vT>(), nt2::One<vT>()), nt2::One<r_t>(), 0);
  NT2_TEST_ULP_EQUAL(realpow(nt2::Zero<vT>(), nt2::Zero<vT>()), nt2::One<r_t>(), 0);
  NT2_TEST_ULP_EQUAL(realpow(nt2::splat<vT>(-1),nt2::splat<vT>(5)),nt2::splat<vT> (-1), 0);
  NT2_TEST_ULP_EQUAL(realpow(nt2::splat<vT>(-1),nt2::splat<vT>(6)), nt2::splat<vT>(1), 0);
}

NT2_TEST_CASE_TPL ( realpow_1,  NT2_SIMD_REAL_TYPES)
{
  using nt2::realpow;
  using nt2::tag::realpow_;
  using boost::simd::native;
  typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef native<T,ext_t>                  vT;
  typedef typename nt2::meta::as_integer<vT>::type          ivT;
  typedef typename nt2::meta::call<realpow_(vT,ivT)>::type r_t;
  typedef vT wished_r_t;

  // return type conformity test
  NT2_TEST_TYPE_IS(r_t, wished_r_t);


  // specific values tests
#ifndef BOOST_SIMD_NO_INVALIDS
  NT2_TEST_ULP_EQUAL(realpow(nt2::Inf<vT>(),3), nt2::Inf<r_t>(), 0);
  NT2_TEST_ULP_EQUAL(realpow(nt2::Minf<vT>(),3), nt2::Minf<r_t>(), 0);
  NT2_TEST_ULP_EQUAL(realpow(nt2::Nan<vT>(),3), nt2::Nan<r_t>(), 0);
#endif
  NT2_TEST_ULP_EQUAL(realpow(nt2::Mone<vT>(),3),nt2::splat<vT>(-1), 0);
  NT2_TEST_ULP_EQUAL(realpow(nt2::One<vT>(),3), nt2::One<r_t>(), 0);
  NT2_TEST_ULP_EQUAL(realpow(nt2::Two <vT>(),3), nt2::splat<vT>(8), 0);
  NT2_TEST_ULP_EQUAL(realpow(nt2::Zero<vT>(),0), nt2::One<r_t>(), 0);
  NT2_TEST_ULP_EQUAL(realpow(nt2::Zero<vT>(),3), nt2::Zero<r_t>(), 0);
}
