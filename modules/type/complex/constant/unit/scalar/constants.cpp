//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#define NT2_UNIT_MODULE "nt2 complex.constant toolbox - cmplx_testing/scalar Mode"

//////////////////////////////////////////////////////////////////////////////
// unit test behavior of complex.arithmetic components in scalar  mode
//////////////////////////////////////////////////////////////////////////////

#include <nt2/include/constants/one.hpp>
#include <nt2/include/constants/zero.hpp>
#include <nt2/include/constants/i.hpp>
#include <nt2/include/constants/cnan.hpp>
#include <nt2/toolbox/constant/common.hpp>
#include <nt2/include/functions/real.hpp>
#include <nt2/include/functions/imag.hpp>
#include <nt2/include/functions/is_nan.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/basic.hpp>
#include <nt2/sdk/unit/module.hpp>

#include <nt2/sdk/complex/meta/as_imaginary.hpp>
#include <nt2/sdk/complex/meta/as_dry.hpp>

NT2_TEST_CASE_TPL ( abs_cplx__1_0,  BOOST_SIMD_SIMD_REAL_TYPES)
{
  using boost::simd::native;
  typedef NT2_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef std::complex<T>                              cT;
  typedef typename nt2::meta::as_imaginary<T>::type   ciT;
  typedef typename nt2::meta::as_dry<T>::type          dT;

  NT2_TEST_EQUAL(nt2::real(nt2::One<cT>()), nt2::One<T>());
  NT2_TEST_EQUAL(nt2::imag(nt2::One<cT>()), nt2::Zero<T>());
  NT2_TEST_EQUAL(nt2::real(nt2::One<dT>()), nt2::One<T>());
  NT2_TEST_EQUAL(nt2::imag(nt2::One<dT>()), nt2::Zero<T>());
  NT2_TEST_EQUAL(nt2::real(nt2::One<ciT>()), nt2::Zero<T>());
  NT2_TEST_EQUAL(nt2::imag(nt2::One<ciT>()), nt2::One<T>());
  NT2_TEST_EQUAL(nt2::real(nt2::I<cT>()), nt2::Zero<T>());
  NT2_TEST_EQUAL(nt2::imag(nt2::I<cT>()), nt2::One<T>());
  NT2_TEST_EQUAL(nt2::real(nt2::I<ciT>()), nt2::Zero<T>());
  NT2_TEST_EQUAL(nt2::imag(nt2::I<ciT>()), nt2::One<T>());
  NT2_TEST(nt2::is_nan(nt2::real(nt2::Cnan<cT>())));
  NT2_TEST(nt2::is_nan(nt2::imag(nt2::Cnan<cT>())));

}


