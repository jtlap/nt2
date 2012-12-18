//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#define NT2_UNIT_MODULE "nt2 boost.simd.arithmetic toolbox - sqrt/simd Mode"

//////////////////////////////////////////////////////////////////////////////
// unit test behavior of boost.simd.arithmetic components in scalar mode
//////////////////////////////////////////////////////////////////////////////
/// created by jt the 30/11/2010
///
#include <nt2/include/functions/bitwise_cast.hpp>
#include <boost/simd/sdk/simd/native.hpp>
#include <nt2/include/functions/extract.hpp>
#include <nt2/include/functions/imag.hpp>
#include <nt2/include/functions/real.hpp>
#include <nt2/include/functions/sqrt.hpp>
#include <nt2/include/functions/cos.hpp>
#include <nt2/include/functions/splat.hpp>
#include <nt2/include/functions/ulpdist.hpp>
#include <nt2/include/functions/real.hpp>
#include <boost/type_traits/is_same.hpp>
#include <nt2/sdk/functor/meta/call.hpp>
#include <nt2/sdk/meta/as_integer.hpp>
#include <nt2/sdk/meta/as_floating.hpp>
#include <nt2/sdk/meta/as_signed.hpp>
#include <nt2/sdk/meta/upgrade.hpp>
#include <nt2/sdk/meta/downgrade.hpp>
#include <nt2/sdk/meta/scalar_of.hpp>
#include <boost/dispatch/meta/as_floating.hpp>
#include <boost/type_traits/common_type.hpp>
#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/module.hpp>

#include <nt2/toolbox/constant/constant.hpp>
#include <nt2/include/constants/cnan.hpp>
#include <nt2/sdk/meta/cardinal_of.hpp>
#include <nt2/include/functions/splat.hpp>

#include <nt2/include/functions/load.hpp>
#include <nt2/sdk/complex/complex.hpp>
#include <nt2/sdk/complex/dry.hpp>
#include <nt2/sdk/complex/imaginary.hpp>
#include <nt2/sdk/complex/meta/as_complex.hpp>
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
  double ulpd;
  ulpd=0.0;

  {
    typedef vcT r_t;
    NT2_TEST_ULP_EQUAL(nt2::sqrt(nt2::Inf<vcT>())[0], cT(nt2::Inf<cT>()),0);
    NT2_TEST_ULP_EQUAL(nt2::sqrt(nt2::Minf<vcT>())[0], cT(0, nt2::Inf<T>()),0);
    NT2_TEST_ULP_EQUAL(nt2::sqrt(nt2::Mone<vcT>())[0], cT(0, 1),0);
    NT2_TEST_ULP_EQUAL(nt2::sqrt(nt2::Nan<vcT>())[0], cT(nt2::Cnan<cT>()),0);
    NT2_TEST_ULP_EQUAL(nt2::sqrt(nt2::One<vcT>())[0], cT(nt2::One<cT>()),0);
    NT2_TEST_ULP_EQUAL(nt2::sqrt(nt2::Zero<vcT>())[0], cT(nt2::Zero<cT>()),0);
  }
  {
    typedef vcT r_t;
    NT2_TEST_ULP_EQUAL(nt2::sqrt(nt2::Inf<vciT>())[0],  cT(nt2::Inf<T>(), nt2::Inf<T>()),0);
    NT2_TEST_ULP_EQUAL(nt2::sqrt(nt2::Minf<vciT>())[0], cT(nt2::Inf<T>(),nt2::Minf<T>()),0);
    NT2_TEST_ULP_EQUAL(nt2::sqrt(nt2::Mone<vciT>())[0], cT(nt2::Sqrt_2o_2<T>(), -nt2::Sqrt_2o_2<T>()) ,0);
    NT2_TEST_ULP_EQUAL(nt2::sqrt(nt2::Nan<vciT>())[0],  cT(nt2::Nan<T>(), nt2::Nan<T>()),0);
    NT2_TEST_ULP_EQUAL(nt2::sqrt(nt2::One<vciT>())[0],  cT(nt2::Sqrt_2o_2<T>(), nt2::Sqrt_2o_2<T>()),0);
    NT2_TEST_ULP_EQUAL(nt2::sqrt(nt2::Zero<vciT>())[0], nt2::Zero<cT>(),0);
  }
  {
    typedef vcT r_t;
    NT2_TEST_ULP_EQUAL(nt2::sqrt(nt2::Inf<vdT>())[0], nt2::Inf<cT>(),0);
    NT2_TEST_ULP_EQUAL(nt2::sqrt(nt2::Minf<vdT>())[0], cT(nt2::Zero<T>(), nt2::Inf<T>()),0);
    NT2_TEST_ULP_EQUAL(nt2::sqrt(nt2::Mone<vdT>())[0], cT(nt2::Zero<T>(), nt2::One<T>()),0);
    NT2_TEST_ULP_EQUAL(nt2::sqrt(nt2::Nan<vdT>())[0], nt2::Nan<cT>(),0);
    NT2_TEST_ULP_EQUAL(nt2::sqrt(nt2::One<vdT>())[0], nt2::One<cT>(),0);
    NT2_TEST_ULP_EQUAL(nt2::sqrt(nt2::Zero<vdT>())[0], nt2::Zero<cT>(),0);
  }
} // end of test for floating_


