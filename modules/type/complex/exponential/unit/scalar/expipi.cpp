//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#define NT2_UNIT_MODULE "nt2 complex.expipionential toolbox - expipi/scalar Mode"

//////////////////////////////////////////////////////////////////////////////
// unit test behavior of expipionential components in scalar mode
//////////////////////////////////////////////////////////////////////////////
/// created by jt the 08/12/2010
///
#include <nt2/include/functions/expipi.hpp>
#include <nt2/include/functions/exp.hpp>
#include <nt2/include/functions/mul_i.hpp>
#include <nt2/sdk/functor/meta/call.hpp>
#include <nt2/sdk/unit/tests/ulp.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/memory/buffer.hpp>
#include <nt2/toolbox/constant/constant.hpp>

NT2_TEST_CASE_TPL ( expipi_real__1_0,  NT2_REAL_TYPES)
{
  using nt2::expipi;
  using nt2::tag::expipi_;
  typedef std::complex<T> cT;

//#define EXPIPI(val) nt2::exp(nt2::mul_i(val))

  // return type conformity test
  NT2_TEST_TYPE_IS( typename nt2::meta::call<expipi_(cT)>::type, cT );

  // specific values tests
  NT2_TEST_ULP_EQUAL(nt2::expipi(cT(nt2::Inf<T>()))  , nt2::exp(nt2::Pi<T>()*nt2::mul_i(cT(nt2::Inf<T>())))  , 10);
  NT2_TEST_ULP_EQUAL(nt2::expipi(cT(nt2::Minf<T>())) , nt2::exp(nt2::Pi<T>()*nt2::mul_i(cT(nt2::Minf<T>())) ), 10);
  NT2_TEST_ULP_EQUAL(nt2::expipi(cT(nt2::Mone<T>())) , nt2::exp(nt2::Pi<T>()*nt2::mul_i(cT(nt2::Mone<T>())) ), 10);
  NT2_TEST_ULP_EQUAL(nt2::expipi(cT(nt2::Nan<T>()))  , nt2::exp(nt2::Pi<T>()*nt2::mul_i(cT(nt2::Nan<T>()))  ), 10);
  NT2_TEST_ULP_EQUAL(nt2::expipi(cT(nt2::One<T>()))  , nt2::exp(nt2::Pi<T>()*nt2::mul_i(cT(nt2::One<T>()))  ), 10);
  NT2_TEST_ULP_EQUAL(nt2::expipi(cT(nt2::Zero<T>())) , nt2::exp(nt2::Pi<T>()*nt2::mul_i(cT(nt2::Zero<T>())) ), 10);
  NT2_TEST_ULP_EQUAL(nt2::expipi(cT(nt2::Pi<T>())), nt2::exp(nt2::Pi<T>()*nt2::mul_i(cT(nt2::Pi<T>()))), 10);

  NT2_TEST_ULP_EQUAL(nt2::expipi(T(nt2::Inf<T>()))  , nt2::exp(nt2::Pi<T>()*nt2::mul_i(cT(nt2::Inf<T>())))  , 10);
  NT2_TEST_ULP_EQUAL(nt2::expipi(T(nt2::Minf<T>())) , nt2::exp(nt2::Pi<T>()*nt2::mul_i(cT(nt2::Minf<T>())) ), 10);
  NT2_TEST_ULP_EQUAL(nt2::expipi(T(nt2::Mone<T>())) , nt2::exp(nt2::Pi<T>()*nt2::mul_i(cT(nt2::Mone<T>())) ), 10);
  NT2_TEST_ULP_EQUAL(nt2::expipi(T(nt2::Nan<T>()))  , nt2::exp(nt2::Pi<T>()*nt2::mul_i(cT(nt2::Nan<T>()))  ), 10);
  NT2_TEST_ULP_EQUAL(nt2::expipi(T(nt2::One<T>()))  , nt2::exp(nt2::Pi<T>()*nt2::mul_i(cT(nt2::One<T>()))  ), 10);
  NT2_TEST_ULP_EQUAL(nt2::expipi(T(nt2::Zero<T>())) , nt2::exp(nt2::Pi<T>()*nt2::mul_i(cT(nt2::Zero<T>())) ), 10);
  NT2_TEST_ULP_EQUAL(nt2::expipi(T(nt2::Pi<T>()))   , nt2::exp(nt2::Pi<T>()*nt2::mul_i(cT(nt2::Pi<T>()))), 10);

  NT2_TEST_ULP_EQUAL(nt2::expipi(cT(0, nt2::Inf<T>()))  , nt2::exp(nt2::Pi<T>()*nt2::mul_i(cT(0, nt2::Inf<T>())))  , 10);
  NT2_TEST_ULP_EQUAL(nt2::expipi(cT(0, nt2::Minf<T>())) , nt2::exp(nt2::Pi<T>()*nt2::mul_i(cT(0, nt2::Minf<T>())) ), 10);
  NT2_TEST_ULP_EQUAL(nt2::expipi(cT(0, nt2::Mone<T>())) , nt2::exp(nt2::Pi<T>()*nt2::mul_i(cT(0, nt2::Mone<T>())) ), 10);
  NT2_TEST_ULP_EQUAL(nt2::expipi(cT(0, nt2::Nan<T>()))  , nt2::exp(nt2::Pi<T>()*nt2::mul_i(cT(0, nt2::Nan<T>()))  ), 10);
  NT2_TEST_ULP_EQUAL(nt2::expipi(cT(0, nt2::One<T>()))  , nt2::exp(nt2::Pi<T>()*nt2::mul_i(cT(0, nt2::One<T>()))  ), 10);
  NT2_TEST_ULP_EQUAL(nt2::expipi(cT(0, nt2::Zero<T>())) , nt2::exp(nt2::Pi<T>()*nt2::mul_i(cT(0, nt2::Zero<T>())) ), 10);
  NT2_TEST_ULP_EQUAL(nt2::expipi(cT(0, nt2::Pi<T>()))   , nt2::exp(nt2::Pi<T>()*nt2::mul_i(cT(0, nt2::Pi<T>()))), 10);
} // end of test for floating_ c




