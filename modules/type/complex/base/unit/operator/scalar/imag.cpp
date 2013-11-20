//==============================================================================
//         Copyright 2003 - 2013   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/include/functions/imag.hpp>

#include <boost/dispatch/functor/meta/call.hpp>
#include <nt2/sdk/functor/meta/call.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>
#include <complex>
#include <nt2/sdk/complex/complex.hpp>
#include <nt2/sdk/complex/dry.hpp>
#include <nt2/sdk/unit/tests/basic.hpp>
#include <nt2/sdk/meta/as_integer.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <boost/simd/sdk/config.hpp>
#include <nt2/sdk/complex/meta/as_dry.hpp>


#include <nt2/include/constants/mtwo.hpp>
#include <nt2/include/constants/one.hpp>
#include <nt2/include/constants/two.hpp>
#include <nt2/include/constants/zero.hpp>
#include <nt2/include/constants/inf.hpp>
#include <nt2/include/constants/minf.hpp>
#include <nt2/include/constants/nan.hpp>

NT2_TEST_CASE_TPL ( imag_real,  BOOST_SIMD_REAL_TYPES)
{
  using nt2::imag;
  using nt2::tag::imag_;
  typedef typename std::complex<T> cT;
  typedef typename nt2::meta::as_dry<T> ::type cdT;
  typedef typename boost::dispatch::meta::call<imag_(cT)>::type r_t;

  // return type conformity test
  NT2_TEST_TYPE_IS(r_t, T);

  // specific values tests
#ifndef BOOST_SIMD_NO_INVALIDS
  NT2_TEST_EQUAL(nt2::imag(cT(nt2::Inf<T>())), nt2::Zero<T>());
  NT2_TEST_EQUAL(nt2::imag(cT(nt2::Minf<T>())),nt2::Zero<T>());
  NT2_TEST_EQUAL(nt2::imag(cT(nt2::Nan<T>())), nt2::Zero<T>());
  NT2_TEST_EQUAL(nt2::imag(cdT(nt2::Inf<T>())), nt2::Zero<T>());
  NT2_TEST_EQUAL(nt2::imag(cdT(nt2::Minf<T>())),nt2::Zero<T>());
  NT2_TEST_EQUAL(nt2::imag(cdT(nt2::Nan<T>())), nt2::Zero<T>());
#endif
  NT2_TEST_EQUAL(nt2::imag(cT(nt2::One<T>())), nt2::Zero<T>());
  NT2_TEST_EQUAL(nt2::imag(cT(nt2::Zero<T>())),nt2::Zero<T>());
  NT2_TEST_EQUAL(nt2::imag(cT(0, 1)), nt2::One<T>());
  NT2_TEST_EQUAL(nt2::imag(cT(1, 0)), nt2::Zero<T>());
  NT2_TEST_EQUAL(nt2::imag(cT(2, 2)), nt2::Two<T>());
  NT2_TEST_EQUAL(nt2::imag(cT(2,-2)), nt2::Mtwo<T>());
  NT2_TEST_EQUAL(nt2::imag(cdT(nt2::One<T>())), nt2::Zero<T>());
  NT2_TEST_EQUAL(nt2::imag(cdT(nt2::Zero<T>())),nt2::Zero<T>());
}
