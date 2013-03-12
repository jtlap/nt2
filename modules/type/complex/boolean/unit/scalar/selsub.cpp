//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#define NT2_UNIT_MODULE "nt2 boost.simd.boolean toolbox - selsub/scalar Mode"

//////////////////////////////////////////////////////////////////////////////
// unit test behavior of boost.simd.boolean components in scalar mode
//////////////////////////////////////////////////////////////////////////////

#include <nt2/include/functions/selsub.hpp>
#include <nt2/include/constants/nan.hpp>
#include <nt2/include/constants/inf.hpp>
#include <nt2/include/constants/minf.hpp>
#include <nt2/include/constants/zero.hpp>
#include <nt2/include/constants/true.hpp>
#include <nt2/include/constants/false.hpp>
#include <nt2/toolbox/constant/common.hpp>
#include <nt2/sdk/functor/meta/call.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <complex>

NT2_TEST_CASE_TPL ( selsub_real__2_0,  NT2_REAL_TYPES)
{
  using nt2::selsub;
  using nt2::tag::selsub_;
  using nt2::logical;

  typedef std::complex<T> cT;
  NT2_TEST_TYPE_IS( typename nt2::meta::call<selsub_(logical<T>, cT, cT)>::type
                  , cT
                  );

  // specific values tests
  NT2_TEST_EQUAL(selsub(nt2::False< logical<T> >(), cT(1), cT(0, 1)), cT(1));
  NT2_TEST_EQUAL(selsub(nt2::True< logical<T> >(),cT(1),cT(0, 1)), cT(1, -1));
  NT2_TEST_EQUAL(selsub(nt2::Inf<cT>(), cT(1),cT(0, 1)), cT(1, -1));
  NT2_TEST_EQUAL(selsub(nt2::Minf<cT>(), cT(1),cT(0, 1)),  cT(1, -1));
  NT2_TEST_EQUAL(selsub(nt2::Nan<cT>(), cT(1),cT(0, 1)) ,  cT(1, -1));
  NT2_TEST_EQUAL(selsub(nt2::Zero<cT>(), cT(1),cT(0, 1)),  cT(1));

  NT2_TEST_EQUAL(selsub(nt2::False< logical<T> >(), T(1), cT(0, 1)), cT(1));
  NT2_TEST_EQUAL(selsub(nt2::True< logical<T> >(),T(1),cT(0, 1)), cT(1, -1));
  NT2_TEST_EQUAL(selsub(nt2::Inf<cT>(), T(1),cT(0, 1)), cT(1, -1));
  NT2_TEST_EQUAL(selsub(nt2::Minf<cT>(), T(1),cT(0, 1)),  cT(1, -1));
  NT2_TEST_EQUAL(selsub(nt2::Nan<cT>(), T(1),cT(0, 1)) ,  cT(1, -1));
  NT2_TEST_EQUAL(selsub(nt2::Zero<cT>(), T(1),cT(0, 1)),  cT(1));

  NT2_TEST_EQUAL(selsub(nt2::False< logical<T> >(),cT(0, 1),  T(1)),  cT(0, 1));
  NT2_TEST_EQUAL(selsub(nt2::True< logical<T> >(), cT(0, 1),  T(1)),  cT(-1, 1));
  NT2_TEST_EQUAL(selsub(nt2::Inf<cT>(),            cT(0, 1),  T(1)),  cT(-1, 1));
  NT2_TEST_EQUAL(selsub(nt2::Minf<cT>(),           cT(0, 1),  T(1)),  cT(-1, 1));
  NT2_TEST_EQUAL(selsub(nt2::Nan<cT>(),            cT(0, 1),  T(1)),  cT(-1, 1));
  NT2_TEST_EQUAL(selsub(nt2::Zero<cT>(),           cT(0, 1),  T(1)),  cT(0, 1));

  NT2_TEST_EQUAL(selsub(nt2::Inf<T>(),             cT(0, 1),  T(1)),  cT(-1, 1));
  NT2_TEST_EQUAL(selsub(nt2::Minf<T>(),            cT(0, 1),  T(1)),  cT(-1, 1));
  NT2_TEST_EQUAL(selsub(nt2::Nan<T>(),             cT(0, 1),  T(1)),  cT(-1, 1));
  NT2_TEST_EQUAL(selsub(nt2::Zero<T>(),            cT(0, 1),  T(1)),  cT(0, 1));

} // end of test for floating_
