//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#define NT2_UNIT_MODULE "nt2 complex.ieee toolbox - sign/scalar Mode"

//////////////////////////////////////////////////////////////////////////////
// unit test behavior of ieee components in scalar mode
//////////////////////////////////////////////////////////////////////////////
/// created by jt the 04/12/2010
///
#include <nt2/toolbox/ieee/include/functions/sign.hpp>
#include <nt2/include/functions/sign.hpp>
#include <nt2/sdk/functor/meta/call.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/include/constants/one.hpp>
#include <nt2/include/constants/mone.hpp>
#include <nt2/include/constants/nan.hpp>
#include <nt2/include/constants/zero.hpp>
#include <nt2/include/constants/inf.hpp>
#include <nt2/include/constants/cnan.hpp>


NT2_TEST_CASE_TPL ( sign_real__2_0,  (float))//NT2_REAL_TYPES)
{

  using nt2::sign;
  using nt2::tag::sign_;
  typedef std::complex<T> cT;
  typedef typename nt2::meta::call<sign_(cT)>::type r_t;


  // return type conformity test
  NT2_TEST_TYPE_IS(r_t, cT);


  // specific values tests
   NT2_TEST_EQUAL(sign(nt2::Inf<cT>()  ), nt2::One<r_t>());
  NT2_TEST_EQUAL(sign(nt2::Minf<cT>() ), nt2::Mone<r_t>());
  NT2_TEST_EQUAL(sign(nt2::Mone<cT>() ), nt2::Mone<r_t>());
  NT2_TEST_EQUAL(sign(nt2::Nan<cT>()  ), nt2::Nan<r_t>());
  NT2_TEST_EQUAL(sign(nt2::One<cT>()  ), nt2::One<r_t>());
  NT2_TEST_EQUAL(sign(nt2::Zero<cT>() ), nt2::Zero<r_t>());

  NT2_TEST_EQUAL(sign(cT(3, 4)), cT(3.0/5.0, 4.0/5.0));
  NT2_TEST_EQUAL(sign(cT(nt2::Inf<T>(), nt2::Inf<T>())), nt2::Cnan<cT>());
  NT2_TEST_EQUAL(sign(cT(nt2::Inf<T>(), 1)), cT(1));
  NT2_TEST_EQUAL(sign(cT(1, nt2::Inf<T>())), cT(0, 1));
  NT2_TEST_EQUAL(sign(cT(0, nt2::Inf<T>())), cT(0, 1));
  NT2_TEST_EQUAL(sign(cT(1, nt2::Nan<T>())), nt2::Cnan<cT>());
  NT2_TEST_EQUAL(sign(cT(0, nt2::Nan<T>())), cT(0, nt2::Nan<T>()));
} // end of test for floating_
