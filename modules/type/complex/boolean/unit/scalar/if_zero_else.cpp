//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#define NT2_UNIT_MODULE "nt2 boost.simd.boolean toolbox - if_zero_else/scalar Mode"

//////////////////////////////////////////////////////////////////////////////
// unit test behavior of boost.simd.boolean components in scalar mode
//////////////////////////////////////////////////////////////////////////////
/// created  by jt the 18/02/2011
///
#include <nt2/include/functions/if_zero_else.hpp>
#include <nt2/include/constants/nan.hpp>
#include <nt2/include/constants/allbits.hpp>
#include <nt2/include/constants/allbits.hpp>
#include <nt2/include/constants/cnan.hpp>
#include <nt2/include/constants/inf.hpp>
#include <nt2/include/constants/minf.hpp>
#include <nt2/include/constants/true.hpp>
#include <nt2/include/constants/false.hpp>
#include <nt2/toolbox/constant/common.hpp>
#include <nt2/sdk/functor/meta/call.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <complex>

NT2_TEST_CASE_TPL ( if_zero_else_real__2_0,  NT2_REAL_TYPES)
{
  using boost::simd::if_zero_else;
  using boost::simd::tag::if_zero_else_;
  using boost::simd::logical;

  typedef std::complex<T> cT;
  typedef typename nt2::meta::call<if_zero_else_(cT, cT)>::type r_t;

  //  return type conformity test
  //  return type conformity test
  NT2_TEST_TYPE_IS( typename nt2::meta::call<if_zero_else_(cT, cT)>::type
                  , std::complex<T>
                  );

  // specific values tests
  NT2_TEST_EQUAL(if_zero_else(nt2::False< nt2::logical<T> >(), cT(1)), cT(1));
  NT2_TEST_EQUAL(if_zero_else(nt2::True< nt2::logical<T> >(),cT(1)), cT(0));
  NT2_TEST_EQUAL(if_zero_else(nt2::Inf<cT>(), cT(1)), cT(0));
  NT2_TEST_EQUAL(if_zero_else(nt2::Minf<cT>(), cT(1)),  cT(0));
  NT2_TEST_EQUAL(if_zero_else(nt2::Nan<cT>(), cT(1)) ,  cT(0));
  NT2_TEST_EQUAL(if_zero_else(nt2::Zero<cT>(), cT(1)),  cT(1));
} // end of test for floating_

