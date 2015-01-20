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
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>
#include <nt2/sdk/unit/tests/basic.hpp>
#include <nt2/sdk/unit/tests/ulp.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <boost/simd/sdk/config.hpp>
#include <nt2/include/functions/is_less.hpp>
#include <nt2/include/constants/half.hpp>
#include <nt2/include/constants/mzero.hpp>
#include <nt2/include/constants/one.hpp>
#include <nt2/include/constants/two.hpp>
#include <nt2/include/constants/zero.hpp>
#include <nt2/include/constants/inf.hpp>
#include <nt2/include/constants/nan.hpp>
#include <nt2/include/constants/ten.hpp>
#include <nt2/include/constants/eps.hpp>

NT2_TEST_CASE_TPL ( erfc_real,  NT2_REAL_TYPES)
{
  using nt2::erfc;
  using nt2::tag::erfc_;
  typedef typename nt2::meta::call<erfc_(T)>::type r_t;
  typedef T wished_r_t;

  // return type conformity test
  NT2_TEST_TYPE_IS(r_t, wished_r_t);

  // specific values tests
#ifndef BOOST_SIMD_NO_INVALIDS
  NT2_TEST_ULP_EQUAL(erfc(nt2::Inf<T>()), nt2::Zero<r_t>(), 200);
  NT2_TEST_ULP_EQUAL(erfc(nt2::Nan<T>()), nt2::Nan<r_t>(), 200);
#endif
  NT2_TEST_ULP_EQUAL(erfc(nt2::Mzero<T>()), nt2::One<r_t>(), 200);
  NT2_TEST_ULP_EQUAL(erfc(nt2::Half<T>()), T(0.479500122186953), 200);
  NT2_TEST_ULP_EQUAL(erfc(nt2::One<T>()), T(0.157299207050285), 200);
  NT2_TEST_ULP_EQUAL(erfc(nt2::Two<T>()), T(0.004677734981047), 200);
  NT2_TEST_ULP_EQUAL(erfc(nt2::Zero<T>()), nt2::One<r_t>(), 200);
  NT2_TEST_ULP_EQUAL(erfc(T(6)), T(2.151973671249892e-17), 200);
  NT2_TEST(nt2::is_less(erfc((nt2::Ten<T>())- T(2.088487583762545e-45)), nt2::Eps<T>()));
  NT2_TEST(nt2::is_less(erfc(T(15))- T(7.212994172451206e-100), nt2::Eps<T>()));
}

