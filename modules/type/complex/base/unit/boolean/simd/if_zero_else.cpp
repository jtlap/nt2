//==============================================================================
//         Copyright 2003 - 2013   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/include/functions/if_zero_else.hpp>

#include <boost/dispatch/functor/meta/call.hpp>
#include <nt2/sdk/functor/meta/call.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>
#include <boost/simd/sdk/simd/io.hpp>
#include <boost/simd/sdk/simd/native.hpp>
#include <complex>
#include <nt2/sdk/complex/complex.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <boost/simd/sdk/config.hpp>

#include <nt2/include/constants/zero.hpp>
#include <nt2/include/constants/false.hpp>
#include <nt2/include/constants/true.hpp>
#include <nt2/include/constants/zero.hpp>
#include <nt2/include/constants/one.hpp>
#include <nt2/include/constants/inf.hpp>
#include <nt2/include/constants/minf.hpp>
#include <nt2/include/constants/nan.hpp>
#include <nt2/include/constants/i.hpp>
#include <nt2/sdk/simd/logical.hpp>

NT2_TEST_CASE_TPL ( if_zero_else_real,  NT2_SIMD_REAL_TYPES)
{
  using nt2::if_zero_else;
  using nt2::tag::if_zero_else_;
  typedef typename std::complex<T> cT;
  using boost::simd::native;
  typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef native<cT,ext_t>                vcT;
  typedef native<nt2::logical<T>,ext_t>      vclT;

  // specific values tests
#ifndef BOOST_SIMD_NO_INVALIDS
  NT2_TEST_EQUAL(if_zero_else(nt2::Inf<vcT>(), nt2::One<vcT>()), nt2::Zero<vcT>());
  NT2_TEST_EQUAL(if_zero_else(nt2::Minf<vcT>(), nt2::One<vcT>()),  nt2::Zero<vcT>());
  NT2_TEST_EQUAL(if_zero_else(nt2::Nan<vcT>(), nt2::One<vcT>()) ,  nt2::Zero<vcT>());
#endif
  NT2_TEST_EQUAL(if_zero_else(nt2::False<vclT>(), nt2::I<vcT>()), nt2::I<vcT>());
  NT2_TEST_EQUAL(if_zero_else(nt2::True<vclT>(), nt2::One<vcT>()), nt2::Zero<vcT>());
  NT2_TEST_EQUAL(if_zero_else(nt2::Zero<vcT>(), nt2::One<vcT>()),  nt2::One<vcT>());
  NT2_TEST_EQUAL(if_zero_else(nt2::One<vcT>(), nt2::One<vcT>()),  nt2::Zero<vcT>());
}
