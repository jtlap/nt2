//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#define NT2_UNIT_MODULE "nt2 boost.simd.boolean toolbox - ifnotdec/complex Mode"

//////////////////////////////////////////////////////////////////////////////
// unit test behavior of boost.simd.boolean components in scalar mode
//////////////////////////////////////////////////////////////////////////////

#include <nt2/boolean/include/functions/ifnotdec.hpp>
#include <boost/type_traits/is_same.hpp>
#include <nt2/constant/constant.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/basic.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>



NT2_TEST_CASE_TPL( ifnotdec_floating, BOOST_SIMD_REAL_TYPES)
{
  using nt2::ifnotdec;
  using nt2::tag::ifnotdec_;
  typedef std::complex<T> cT;

  // specific values tests
  NT2_TEST_EQUAL(ifnotdec(nt2::Zero<cT>(), nt2::Mone<cT>()), nt2::Mtwo<cT>());
  NT2_TEST_EQUAL(ifnotdec(nt2::Zero<cT>(), nt2::One<cT>()), nt2::Zero<cT>());
  NT2_TEST_EQUAL(ifnotdec(nt2::Zero<cT>(), nt2::Valmax<cT>()), nt2::Valmax<cT>());
  NT2_TEST_EQUAL(ifnotdec(nt2::Zero<cT>(), nt2::Zero<cT>()), nt2::Mone<cT>());
  NT2_TEST_EQUAL(ifnotdec(nt2::One<cT>(), nt2::Mone<cT>()), nt2::Mone<cT>());
  NT2_TEST_EQUAL(ifnotdec(nt2::One<cT>(), nt2::Zero<cT>()), nt2::Zero<cT>());
  NT2_TEST_EQUAL(ifnotdec(nt2::One<cT>(), nt2::Valmax<cT>()), nt2::Valmax<cT>());
  NT2_TEST_EQUAL(ifnotdec(nt2::One<cT>(), nt2::Zero<cT>()), nt2::Zero<cT>());
}
