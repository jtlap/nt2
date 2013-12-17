//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/include/functions/fastnormcdf.hpp>
#include <nt2/include/constants/nan.hpp>
#include <nt2/include/constants/one.hpp>
#include <nt2/include/constants/mone.hpp>
#include <nt2/include/constants/zero.hpp>
#include <nt2/include/constants/inf.hpp>
#include <nt2/include/constants/minf.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/ulp.hpp>

NT2_TEST_CASE_TPL ( fastnormcdf_1,  (float))//NT2_REAL_TYPES)
{
  using nt2::fastnormcdf;
  using nt2::tag::fastnormcdf_;

  // specific values tests
  NT2_TEST_ULP_EQUAL(fastnormcdf(nt2::Nan<T>()), nt2::Nan<T>(), 0.5);
  NT2_TEST_ULP_EQUAL(fastnormcdf(nt2::One<T>()), T(0.841344746068542948585232545632), 1.5);
  NT2_TEST_ULP_EQUAL(fastnormcdf(nt2::Mone<T>()), T(0.158655253931457051414767454368), 5.5);
  NT2_TEST_ULP_EQUAL(fastnormcdf(nt2::Zero<T>()), nt2::Half<T>(), 0.5);
  NT2_TEST_ULP_EQUAL(fastnormcdf(nt2::Inf<T>()), nt2::One<T>(), 0.5);
  NT2_TEST_ULP_EQUAL(fastnormcdf(nt2::Minf<T>()), nt2::Zero<T>(), 0.5);
}
