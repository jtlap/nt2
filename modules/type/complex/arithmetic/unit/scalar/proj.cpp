//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#define NT2_UNIT_MODULE "nt2 complex.arithmetic toolbox - proj/scalar Mode"

//////////////////////////////////////////////////////////////////////////////
// unit test behavior of boost.simd.arithmetic components in scalar mode
//////////////////////////////////////////////////////////////////////////////
/// created by jt the 30/11/2010
///
#include <nt2/include/functions/proj.hpp>
#include <nt2/include/constants/inf.hpp>
#include <nt2/include/constants/mone.hpp>
#include <nt2/include/constants/minf.hpp>
#include <nt2/include/constants/nan.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/complex/meta/as_imaginary.hpp>
#include <nt2/toolbox/constant/common.hpp>

NT2_TEST_CASE_TPL ( proj_real__1_0,  BOOST_SIMD_REAL_TYPES)
{
  using nt2::proj;
  using nt2::tag::proj_;
  typedef typename std::complex<T> cT;
  typedef typename nt2::meta::as_imaginary<T>::type ciT;

  // specific values tests
  NT2_TEST_EQUAL(nt2::proj(cT(1)), cT(1));
  NT2_TEST_EQUAL(nt2::proj(cT(nt2::Inf<T>())), nt2::Inf<cT>());
  NT2_TEST_EQUAL(nt2::proj(cT(nt2::Minf<T>(), T(1))), nt2::Inf<cT>());
  NT2_TEST_EQUAL(nt2::proj(cT(nt2::Mone<T>())), nt2::Mone<cT>());
  NT2_TEST_EQUAL(nt2::proj(cT(nt2::Nan<T>())), nt2::Nan<cT>());
  NT2_TEST_EQUAL(nt2::proj(cT(T(1), T(2))),cT(T(1), T(2)));
  NT2_TEST_EQUAL(nt2::proj(ciT(nt2::Minf<T>())),  nt2::Inf<cT>());
  NT2_TEST_EQUAL(nt2::proj(ciT(T(1))), cT(T(0), T(1)));
} // end of test for floating_


