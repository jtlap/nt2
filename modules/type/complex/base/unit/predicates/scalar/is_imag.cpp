//==============================================================================
//         Copyright 2003 - 2013   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/include/functions/is_imag.hpp>

#include <boost/dispatch/functor/meta/call.hpp>
#include <nt2/sdk/functor/meta/call.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>
#include <complex>
#include <nt2/sdk/complex/complex.hpp>
#include <boost/simd/sdk/simd/logical.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <boost/simd/sdk/config.hpp>

#include <nt2/include/constants/one.hpp>
#include <nt2/include/constants/two.hpp>
#include <nt2/include/constants/zero.hpp>

NT2_TEST_CASE_TPL ( is_imag_real,  BOOST_SIMD_REAL_TYPES)
{
  using nt2::is_imag;
  using nt2::tag::is_imag_;
  typedef typename std::complex<T> cT;
  typedef typename boost::dispatch::meta::call<is_imag_(cT)>::type r_t;

  // return type conformity test
  NT2_TEST_TYPE_IS(r_t, nt2::logical<T>);

  // specific values tests
  NT2_TEST_EQUAL(is_imag(nt2::One<T>()), r_t(false));
  NT2_TEST_EQUAL(is_imag(nt2::Two<T>()), r_t(false));
  NT2_TEST_EQUAL(is_imag(nt2::Zero<T>()), r_t(true));
  NT2_TEST_EQUAL(is_imag(cT(0, 0)), r_t(true));
  NT2_TEST_EQUAL(is_imag(cT(1, 0)), r_t(false));
  NT2_TEST_EQUAL(is_imag(cT(0, 2)), r_t(true));
  NT2_TEST_EQUAL(is_imag(cT(0, 1)), r_t(true));
  NT2_TEST_EQUAL(is_imag(cT(2, 1)), r_t(false));
}
