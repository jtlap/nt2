//==============================================================================
//         Copyright 2003 - 2013   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/euler/include/functions/erfcx.hpp>

#include <nt2/sdk/functor/meta/call.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>
#include <nt2/sdk/unit/tests/ulp.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <boost/simd/sdk/config.hpp>
#include <boost/simd/sdk/simd/io.hpp>

#include <nt2/include/functions/splat.hpp>
#include <nt2/include/constants/half.hpp>
#include <nt2/include/constants/mzero.hpp>
#include <nt2/include/constants/one.hpp>
#include <nt2/include/constants/two.hpp>
#include <nt2/include/constants/zero.hpp>
#include <nt2/include/constants/inf.hpp>
#include <nt2/include/constants/nan.hpp>

NT2_TEST_CASE_TPL ( erfcx_real,  NT2_REAL_TYPES)
{
  using nt2::erfcx;
  using nt2::tag::erfcx_;
  using boost::simd::native;
  typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef native<T,ext_t>                  vT;
  typedef typename nt2::meta::call<erfcx_(vT)>::type r_t;
  typedef vT wished_r_t;

  // return type conformity test
  NT2_TEST_TYPE_IS(r_t, wished_r_t);

  // specific values tests
#ifndef BOOST_SIMD_NO_INVALIDS
  NT2_TEST_ULP_EQUAL(erfcx(nt2::Inf<vT>()), nt2::Zero<r_t>(), 0);
  NT2_TEST_ULP_EQUAL(erfcx(nt2::Nan<vT>()), nt2::Nan<r_t>(), 0);
#endif
  NT2_TEST_ULP_EQUAL(erfcx(nt2::Mzero<vT>()), nt2::One<r_t>(), 2);
  NT2_TEST_ULP_EQUAL(erfcx(nt2::Half<vT>()), nt2::splat<vT>( 6.156903441929259e-01), 10);
  NT2_TEST_ULP_EQUAL(erfcx(nt2::One<vT>()), nt2::splat<vT>(4.275835761558071e-01), 10);
  NT2_TEST_ULP_EQUAL(erfcx(nt2::Two<vT>()), nt2::splat<vT>( 2.553956763105057e-01), 10);
  NT2_TEST_ULP_EQUAL(erfcx(nt2::Zero<vT>()), nt2::One<r_t>(), 2);
  NT2_TEST_ULP_EQUAL(erfcx(nt2::splat<vT>(6)), nt2::splat<vT>(9.277656780053835e-02), 4);
  NT2_TEST_ULP_EQUAL(erfcx(nt2::splat<vT>(-6)), nt2::splat<vT>(8.622463094230390e+15), 4);
  NT2_TEST_ULP_EQUAL(erfcx(nt2::splat<vT>(7)), nt2::splat<vT>(7.980005432915294e-02), 4);
  NT2_TEST_ULP_EQUAL(erfcx(nt2::splat<vT>(15)), nt2::splat<vT>( 3.752960638850577e-02), 4);
}
