//==============================================================================
//         Copyright 2003 - 2013   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/include/functions/seldec.hpp>

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

#include <nt2/include/constants/mone.hpp>
#include <nt2/include/constants/mtwo.hpp>
#include <nt2/include/constants/one.hpp>
#include <nt2/include/constants/valmax.hpp>
#include <nt2/include/constants/zero.hpp>

NT2_TEST_CASE_TPL( seldec_floating, BOOST_SIMD_SIMD_REAL_TYPES)
{
  using nt2::seldec;
  using nt2::tag::seldec_;
  using boost::simd::native;
  typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef native<T,ext_t>                  vT;

  // specific values tests
  NT2_TEST_EQUAL(seldec(nt2::One<vT>(), nt2::Mone<vT>()), nt2::Mtwo<vT>());
  NT2_TEST_EQUAL(seldec(nt2::One<vT>(), nt2::One<vT>()), nt2::Zero<vT>());
  NT2_TEST_EQUAL(seldec(nt2::One<vT>(), nt2::Valmax<vT>()), nt2::Valmax<vT>());
  NT2_TEST_EQUAL(seldec(nt2::One<vT>(), nt2::Zero<vT>()), nt2::Mone<vT>());
  NT2_TEST_EQUAL(seldec(nt2::Zero<vT>(), nt2::Mone<vT>()), nt2::Mone<vT>());
  NT2_TEST_EQUAL(seldec(nt2::Zero<vT>(), nt2::Zero<vT>()), nt2::Zero<vT>());
  NT2_TEST_EQUAL(seldec(nt2::Zero<vT>(), nt2::Valmax<vT>()), nt2::Valmax<vT>());
  NT2_TEST_EQUAL(seldec(nt2::Zero<vT>(), nt2::Zero<vT>()), nt2::Zero<vT>());
}
