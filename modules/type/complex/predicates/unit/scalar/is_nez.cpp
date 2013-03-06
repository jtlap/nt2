//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#define NT2_UNIT_MODULE "nt2 boost.simd.predicates toolbox - is_nez/scalar Mode"

//////////////////////////////////////////////////////////////////////////////
// unit test behavior of boost.simd.predicates components in scalar mode
//////////////////////////////////////////////////////////////////////////////
/// created  by jt the 21/02/2011
///
#include <nt2/toolbox/predicates/include/functions/is_nez.hpp>
#include <boost/simd/sdk/simd/logical.hpp>

#include <boost/dispatch/functor/meta/call.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/include/constants/inf.hpp>
#include <nt2/include/constants/nan.hpp>
#include <nt2/include/constants/one.hpp>
#include <nt2/include/constants/zero.hpp>
#include <nt2/include/constants/minf.hpp>
#include <nt2/toolbox/constant/common.hpp>

NT2_TEST_CASE_TPL ( is_nez_real__1_0,  BOOST_SIMD_REAL_TYPES)
{
  using nt2::is_nez;
  using nt2::tag::is_nez_;
  typedef std::complex<T> cT;
  typedef nt2::imaginary<T> ciT;
  typedef typename boost::dispatch::meta::call<is_nez_(cT)>::type r_t;

  // return type conformity test
  NT2_TEST_TYPE_IS( typename boost::dispatch::meta::call<is_nez_(cT)>::type, nt2::logical<T> );

  // specific values tests
  NT2_TEST_EQUAL(is_nez(cT(nt2::Inf<T>())),  r_t(true));
  NT2_TEST_EQUAL(is_nez(cT(nt2::Minf<T>())),  r_t(true));
  NT2_TEST_EQUAL(is_nez(cT(nt2::Nan<T>())),  r_t(true));
  NT2_TEST_EQUAL(is_nez(cT(nt2::One<T>())), r_t(true));
  NT2_TEST_EQUAL(is_nez(cT(nt2::Zero<T>())), r_t(false));
  NT2_TEST_EQUAL(is_nez(cT(0, 0)), r_t(false));
  NT2_TEST_EQUAL(is_nez(cT(1, 0))    , r_t(true));
  NT2_TEST_EQUAL(is_nez(cT(0, 2)), r_t(true));
  NT2_TEST_EQUAL(is_nez(cT(0, 1))   , r_t(true));
  NT2_TEST_EQUAL(is_nez(ciT(1))     , r_t(true));
  NT2_TEST_EQUAL(is_nez(ciT(0))     , r_t(false));
}
