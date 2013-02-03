//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#define NT2_UNIT_MODULE "nt2 boost.simd.arithmetic toolbox - fma/simd Mode"

//////////////////////////////////////////////////////////////////////////////
// unit test behavior of boost.simd.arithmetic components in scalar mode
//////////////////////////////////////////////////////////////////////////////
/// created by jt the 01/12/2010
///
#include <nt2/toolbox/arithmetic/include/functions/fma.hpp>
#include <boost/simd/sdk/simd/native.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/dispatch/functor/meta/call.hpp>
#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/include/constants/inf.hpp>
#include <nt2/include/constants/minf.hpp>
#include <nt2/include/constants/nan.hpp>
#include <nt2/include/constants/zero.hpp>
#include <nt2/include/constants/one.hpp>
#include <nt2/include/constants/two.hpp>
#include <nt2/include/constants/mone.hpp>
#include <nt2/toolbox/constant/common.hpp>

NT2_TEST_CASE_TPL ( fma_real__3_0,  BOOST_SIMD_SIMD_REAL_TYPES)
{
  using nt2::fma;
  using nt2::tag::fma_;
  typedef std::complex<T> cT;

  // return type conformity test
  NT2_TEST_TYPE_IS(  typename boost::dispatch::meta::call<fma_(cT,cT,cT)>::type, cT );

  // specific values tests
  NT2_TEST_EQUAL(fma(cT(nt2::Inf<T>()), cT(nt2::Inf<T>()), cT(nt2::Inf<T>())), cT(nt2::Inf<T>()));
  NT2_TEST_EQUAL(fma(cT(nt2::Minf<T>()), cT(nt2::Minf<T>()), cT(nt2::Minf<T>())), cT(nt2::Nan<T>()));
  NT2_TEST_EQUAL(fma(cT(nt2::Mone<T>()), cT(nt2::Mone<T>()), cT(nt2::Mone<T>())), cT(nt2::Zero<T>()));
  NT2_TEST_EQUAL(fma(cT(nt2::Nan<T>()), cT(nt2::Nan<T>()), cT(nt2::Nan<T>())), cT(nt2::Nan<T>()));
  NT2_TEST_EQUAL(fma(cT(nt2::One<T>()), cT(nt2::One<T>()), cT(nt2::One<T>())), cT(nt2::Two<T>()));
  NT2_TEST_EQUAL(fma(cT(nt2::Zero<T>()), cT(nt2::Zero<T>()), cT(nt2::Zero<T>())), cT(nt2::Zero<T>()));
} // end of test for floating_

