//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/boolean/include/functions/ifnotdec.hpp>

#include <nt2/include/constants/mone.hpp>
#include <nt2/include/constants/one.hpp>
#include <nt2/include/constants/two.hpp>
#include <nt2/include/constants/mtwo.hpp>
#include <nt2/include/constants/zero.hpp>
#include <nt2/include/constants/valmax.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/basic.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/complex/complex.hpp>
#include <nt2/sdk/complex/meta/as_complex.hpp>
#include <boost/simd/sdk/simd/io.hpp>
#include <boost/simd/sdk/simd/native.hpp>

NT2_TEST_CASE_TPL( ifnotdec_floating, BOOST_SIMD_SIMD_REAL_TYPES)
{
  using nt2::ifnotdec;
  using nt2::tag::ifnotdec_;
  typedef NT2_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef std::complex<T>                              cT;
  typedef boost::simd::native<T ,ext_t>                vT;

  // specific values tests
  NT2_TEST_EQUAL(ifnotdec(nt2::Zero<vT>(), nt2::Mone<vT>()), nt2::Mtwo<vT>());
  NT2_TEST_EQUAL(ifnotdec(nt2::Zero<vT>(), nt2::One<vT>()), nt2::Zero<vT>());
  NT2_TEST_EQUAL(ifnotdec(nt2::Zero<vT>(), nt2::Valmax<vT>()), nt2::Valmax<vT>());
  NT2_TEST_EQUAL(ifnotdec(nt2::Zero<vT>(), nt2::Zero<vT>()), nt2::Mone<vT>());
  NT2_TEST_EQUAL(ifnotdec(nt2::One<vT>(), nt2::Mone<vT>()), nt2::Mone<vT>());
  NT2_TEST_EQUAL(ifnotdec(nt2::One<vT>(), nt2::Zero<vT>()), nt2::Zero<vT>());
  NT2_TEST_EQUAL(ifnotdec(nt2::One<vT>(), nt2::Valmax<vT>()), nt2::Valmax<vT>());
  NT2_TEST_EQUAL(ifnotdec(nt2::One<vT>(), nt2::Zero<vT>()), nt2::Zero<vT>());
}
