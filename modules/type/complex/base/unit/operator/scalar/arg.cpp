//==============================================================================
//         Copyright 2003 - 2013   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/include/functions/arg.hpp>

#include <boost/dispatch/functor/meta/call.hpp>
#include <nt2/sdk/functor/meta/call.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>
#include <complex>
#include <nt2/sdk/complex/complex.hpp>
#include <nt2/sdk/unit/tests/basic.hpp>
#include <nt2/sdk/meta/as_integer.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <boost/simd/sdk/config.hpp>

#include <nt2/include/constants/one.hpp>
#include <nt2/include/constants/pi.hpp>
#include <nt2/include/constants/pio_2.hpp>
#include <nt2/include/constants/zero.hpp>
#include <nt2/include/constants/inf.hpp>
#include <nt2/include/constants/minf.hpp>
#include <nt2/include/constants/nan.hpp>

NT2_TEST_CASE_TPL ( arg_real,  BOOST_SIMD_REAL_TYPES)
{
  using nt2::arg;
  using nt2::tag::arg_;
  typedef typename std::complex<T> cT;
  typedef typename boost::dispatch::meta::call<arg_(cT)>::type r_t;

  // return type conformity test
  NT2_TEST_TYPE_IS(r_t, T);

  // specific values tests
#ifndef BOOST_SIMD_NO_INVALIDS
  NT2_TEST_EQUAL(arg(cT(nt2::Inf<T>())), nt2::Zero<T>());
  NT2_TEST_EQUAL(arg(cT(nt2::Minf<T>())),nt2::Pi<T>());
  NT2_TEST_EQUAL(arg(cT(nt2::Nan<T>())), nt2::Nan<T>());
#endif
  NT2_TEST_EQUAL(arg(cT(nt2::One<T>())), nt2::Zero<T>());
  NT2_TEST_EQUAL(arg(cT(nt2::Zero<T>())),nt2::Zero<T>());
  NT2_TEST_EQUAL(arg(cT(0, 1)), nt2::Pio_2<T>());
  NT2_TEST_EQUAL(arg(cT(1, 0)), nt2::Zero<T>());
  NT2_TEST_EQUAL(arg(cT(2, 2)), nt2::Pio_2<T>()/2);
  NT2_TEST_EQUAL(arg(cT(2,-2)),-nt2::Pio_2<T>()/2);
}
