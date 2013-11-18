//==============================================================================
//         Copyright 2003 - 2013   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/include/functions/ifnotinc.hpp>

#include <boost/dispatch/functor/meta/call.hpp>
#include <nt2/sdk/functor/meta/call.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>
#include <complex>
#include <nt2/sdk/complex/complex.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <boost/simd/sdk/config.hpp>

#include <nt2/include/constants/mone.hpp>
#include <nt2/include/constants/one.hpp>
#include <nt2/include/constants/two.hpp>
#include <nt2/include/constants/valmax.hpp>
#include <nt2/include/constants/zero.hpp>

NT2_TEST_CASE_TPL( ifnotinc_floating, BOOST_SIMD_REAL_TYPES)
{
  using nt2::ifnotinc;
  using nt2::tag::ifnotinc_;
  typedef typename std::complex<T> cT;

  // specific values tests
  NT2_TEST_EQUAL(ifnotinc(nt2::Zero<cT>(), nt2::Mone<cT>()), nt2::Zero<cT>());
  NT2_TEST_EQUAL(ifnotinc(nt2::Zero<cT>(), nt2::One<cT>()), nt2::Two<cT>());
  NT2_TEST_EQUAL(ifnotinc(nt2::Zero<cT>(), nt2::Valmax<cT>()), nt2::Valmax<cT>());
  NT2_TEST_EQUAL(ifnotinc(nt2::Zero<cT>(), nt2::Zero<cT>()), nt2::One<cT>());
  NT2_TEST_EQUAL(ifnotinc(nt2::One<cT>(), nt2::Mone<cT>()), nt2::Mone<cT>());
  NT2_TEST_EQUAL(ifnotinc(nt2::One<cT>(), nt2::Zero<cT>()), nt2::Zero<cT>());
  NT2_TEST_EQUAL(ifnotinc(nt2::One<cT>(), nt2::Valmax<cT>()), nt2::Valmax<cT>());
  NT2_TEST_EQUAL(ifnotinc(nt2::One<cT>(), nt2::Zero<cT>()), nt2::Zero<cT>());
}
