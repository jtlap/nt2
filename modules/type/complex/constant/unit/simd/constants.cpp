//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#define NT2_UNIT_MODULE "nt2 complex.arithmetic toolbox - cmplx_testing/simd Mode"

//////////////////////////////////////////////////////////////////////////////
// unit test behavior of complex.arithmetic components in simd  mode
//////////////////////////////////////////////////////////////////////////////

#include <boost/simd/sdk/simd/io.hpp>
#include <boost/simd/sdk/simd/native.hpp>
#include <nt2/include/constants/one.hpp>
#include <nt2/include/constants/zero.hpp>
#include <nt2/toolbox/constant/common.hpp>
#include <nt2/include/constants/i.hpp>
#include <nt2/include/functions/real.hpp>
#include <nt2/include/functions/imag.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/complex/meta/as_imaginary.hpp>
#include <nt2/sdk/complex/meta/as_dry.hpp>

NT2_TEST_CASE_TPL ( abs_cplx__1_0,  BOOST_SIMD_SIMD_REAL_TYPES)
{
  using boost::simd::native;
  typedef NT2_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef std::complex<T>                              cT;
  typedef native<T ,ext_t>                             vT;
  typedef native<cT ,ext_t>                           vcT;
  typedef typename nt2::meta::as_imaginary<T>::type   ciT;
  typedef native<ciT ,ext_t>                         vciT;
  typedef typename nt2::meta::as_dry<T>::type          dT;
  typedef native<dT ,ext_t>                           vdT;

  NT2_TEST_EQUAL(nt2::real(nt2::One<vcT>()), nt2::One<vT>());
  NT2_TEST_EQUAL(nt2::imag(nt2::One<vcT>()), nt2::Zero<vT>());
  NT2_TEST_EQUAL(nt2::real(nt2::One<vdT>()), nt2::One<vT>());
  NT2_TEST_EQUAL(nt2::imag(nt2::One<vdT>()), nt2::Zero<vT>());
  NT2_TEST_EQUAL(nt2::real(nt2::One<vciT>()), nt2::Zero<vT>());
  NT2_TEST_EQUAL(nt2::imag(nt2::One<vciT>()), nt2::One<vT>());
  NT2_TEST_EQUAL(nt2::real(nt2::I<vcT>()), nt2::Zero<vT>());
  NT2_TEST_EQUAL(nt2::imag(nt2::I<vcT>()), nt2::One<vT>());
  NT2_TEST_EQUAL(nt2::real(nt2::I<vciT>()), nt2::Zero<vT>());
  NT2_TEST_EQUAL(nt2::imag(nt2::I<vciT>()), nt2::One<vT>());


}


