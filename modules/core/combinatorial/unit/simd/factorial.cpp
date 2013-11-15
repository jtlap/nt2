//==============================================================================
//         Copyright 2003 - 2013   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/combinatorial/include/functions/factorial.hpp>

#include <nt2/sdk/functor/meta/call.hpp>
#include <boost/simd/sdk/simd/native.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <boost/simd/sdk/config.hpp>
#include <boost/simd/sdk/simd/io.hpp>

#include <nt2/include/constants/eight.hpp>
#include <nt2/include/constants/eleven.hpp>
#include <nt2/include/constants/five.hpp>
#include <nt2/include/constants/four.hpp>
#include <nt2/include/constants/nine.hpp>
#include <nt2/include/constants/one.hpp>
#include <nt2/include/constants/seven.hpp>
#include <nt2/include/constants/six.hpp>
#include <nt2/include/constants/ten.hpp>
#include <nt2/include/constants/three.hpp>
#include <nt2/include/constants/twelve.hpp>
#include <nt2/include/constants/two.hpp>
#include <nt2/include/constants/valmax.hpp>
#include <nt2/include/constants/zero.hpp>
#include <nt2/include/constants/inf.hpp>
#include <nt2/include/constants/nan.hpp>
#include <nt2/include/functions/min.hpp>
#include <nt2/include/functions/splat.hpp>
#include <nt2/include/functions/saturate.hpp>


NT2_TEST_CASE_TPL ( factorial_real,  NT2_SIMD_REAL_TYPES)
{
  using nt2::factorial;
  using nt2::tag::factorial_;
  using boost::simd::native;
  typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef native<T,ext_t>                  vT;


  // specific values tests
#ifndef BOOST_SIMD_NO_INVALIDS
  NT2_TEST_EQUAL(factorial(nt2::Inf<vT>()), nt2::Inf<vT>());
  NT2_TEST_EQUAL(factorial(nt2::Nan<vT>()), nt2::Nan<vT>());
#endif
  NT2_TEST_EQUAL(factorial(nt2::Eight<vT>()), nt2::min((nt2::splat<vT>(40320ll)),nt2::Valmax<vT>()));
  NT2_TEST_EQUAL(factorial(nt2::Eleven<vT>()), nt2::min((nt2::splat<vT>(39916800ll)),nt2::Valmax<vT>()));
  NT2_TEST_EQUAL(factorial(nt2::Five<vT>()), nt2::splat<vT>(120));
  NT2_TEST_EQUAL(factorial(nt2::Four<vT>()), nt2::splat<vT>(24));
  NT2_TEST_EQUAL(factorial(nt2::Nine<vT>()), nt2::min((nt2::splat<vT>(362880ll)),nt2::Valmax<vT>()));
  NT2_TEST_EQUAL(factorial(nt2::One<vT>()), nt2::One<vT>());
  NT2_TEST_EQUAL(factorial(nt2::Seven<vT>()), nt2::min((nt2::splat<vT>(5040ll)),nt2::Valmax<vT>()));
  NT2_TEST_EQUAL(factorial(nt2::Six<vT>()), nt2::min((nt2::splat<vT>(720ll)),nt2::Valmax<vT>()));
  NT2_TEST_EQUAL(factorial(nt2::Ten<vT>()), nt2::min((nt2::splat<vT>(3628800ll  )),nt2::Valmax<vT>()));
  NT2_TEST_EQUAL(factorial(nt2::Three<vT>()), nt2::Six<vT>());
  NT2_TEST_EQUAL(factorial(nt2::Twelve<vT>()), nt2::min((nt2::splat<vT>(479001600ll)),nt2::Valmax<vT>()));
  NT2_TEST_EQUAL(factorial(nt2::Two<vT>()), nt2::Two<vT>());
  NT2_TEST_EQUAL(factorial(nt2::Zero<vT>()), nt2::One<vT>());
}
NT2_TEST_CASE_TPL ( factorial_int,  NT2_SIMD_INTEGRAL_TYPES)
{
  using nt2::factorial;
  using nt2::tag::factorial_;
  using boost::simd::native;
  typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef native<T,ext_t>                  vT;


  // specific values tests
  NT2_TEST_EQUAL(factorial(nt2::Eight<vT>()),nt2::splat<vT>(nt2::saturate<vT>(40320ull)));
  NT2_TEST_EQUAL(factorial(nt2::Eleven<vT>()),nt2::splat<vT>(nt2::saturate<vT>(39916800ull)));
  NT2_TEST_EQUAL(factorial(nt2::Five<vT>()),nt2::splat<vT>(nt2::saturate<vT>(120)));
  NT2_TEST_EQUAL(factorial(nt2::Four<vT>()),nt2::splat<vT>(nt2::saturate<vT>(24)));
  NT2_TEST_EQUAL(factorial(nt2::Nine<vT>()),nt2::splat<vT>(nt2::saturate<vT>(362880ull)));
  NT2_TEST_EQUAL(factorial(nt2::One<vT>()),nt2::One<vT>());
  NT2_TEST_EQUAL(factorial(nt2::Seven<vT>()),nt2::splat<vT>(nt2::saturate<vT>(5040ull)));
  NT2_TEST_EQUAL(factorial(nt2::Six<vT>()),nt2::splat<vT>(nt2::saturate<vT>(720ull)));
  NT2_TEST_EQUAL(factorial(nt2::Ten<vT>()),nt2::splat<vT>(nt2::saturate<vT>(3628800ull)));
  NT2_TEST_EQUAL(factorial(nt2::Three<vT>()),nt2::Six<vT>());
  NT2_TEST_EQUAL(factorial(nt2::Twelve<vT>()),nt2::splat<vT>(nt2::saturate<vT>(479001600ull)));
  NT2_TEST_EQUAL(factorial(nt2::Zero<vT>()),nt2::One<vT>());
}
