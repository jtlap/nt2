//==============================================================================
//         Copyright 2003 - 2013   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/euler/include/functions/erfc.hpp>

#include <nt2/sdk/functor/meta/call.hpp>
#include <boost/simd/sdk/simd/native.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>
#include <nt2/sdk/unit/tests/basic.hpp>
#include <nt2/sdk/unit/tests/ulp.hpp>
#include <nt2/include/functions/splat.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <boost/simd/sdk/config.hpp>
#include <boost/simd/sdk/simd/io.hpp>

#include <nt2/include/functions/splat.hpp>
#include <nt2/include/functions/all.hpp>
#include <nt2/include/functions/is_less.hpp>
#include <nt2/include/constants/eps.hpp>
#include <nt2/include/constants/half.hpp>
#include <nt2/include/constants/mzero.hpp>
#include <nt2/include/constants/one.hpp>
#include <nt2/include/constants/ten.hpp>
#include <nt2/include/constants/two.hpp>
#include <nt2/include/constants/zero.hpp>
#include <nt2/include/constants/inf.hpp>
#include <nt2/include/constants/nan.hpp>
#include <nt2/include/constants/two.hpp>

NT2_TEST_CASE_TPL ( erfc_real,  NT2_SIMD_REAL_TYPES)
{
  using nt2::erfc;
  using nt2::tag::erfc_;
  using boost::simd::native;
  typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef native<T,ext_t>                  vT;
  typedef typename nt2::meta::call<erfc_(vT)>::type r_t;
  typedef vT wished_r_t;

  // return type conformity test
  NT2_TEST_TYPE_IS(r_t, wished_r_t);


  // specific values tests
#ifndef BOOST_SIMD_NO_INVALIDS
  NT2_TEST_ULP_EQUAL(erfc(nt2::Inf<vT>()), nt2::Zero<r_t>(), 200);
  NT2_TEST_ULP_EQUAL(erfc(nt2::Nan<vT>()), nt2::Nan<r_t>(), 200);
#endif
  NT2_TEST_ULP_EQUAL(erfc(nt2::Mzero<vT>()), nt2::One<r_t>(), 200);
  NT2_TEST_ULP_EQUAL(erfc(nt2::One<vT>()), nt2::splat<vT>(0.157299207050285), 200);
  NT2_TEST_ULP_EQUAL(erfc(nt2::Half<vT>()), nt2::splat<vT>(0.479500122186953), 200);
  NT2_TEST_ULP_EQUAL(erfc(nt2::Two<vT>()), nt2::splat<vT>(0.004677734981047), 200);
  NT2_TEST_ULP_EQUAL(erfc(nt2::Zero<vT>()), nt2::One<r_t>(), 200);
  NT2_TEST(nt2::all(nt2::is_less(erfc((nt2::Ten<vT>())- nt2::splat<vT>(2.088487583762545e-45)), nt2::Eps<T>())));
  NT2_TEST(nt2::all(nt2::is_less(erfc(nt2::splat<vT>(15))- nt2::splat<vT>(7.212994172451206e-100), nt2::Eps<T>())));
  NT2_TEST_ULP_EQUAL(erfc(nt2::splat<vT>(-6)), nt2::Two<r_t>(), 4);
}
