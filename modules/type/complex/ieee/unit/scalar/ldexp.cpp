//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#define NT2_UNIT_MODULE "nt2 complex.ieee toolbox - ldexp/scalar Mode"

//////////////////////////////////////////////////////////////////////////////
// unit test behavior of ieee components in scalar mode
//////////////////////////////////////////////////////////////////////////////
/// created by jt the 04/12/2010
///

#include <nt2/toolbox/ieee/include/functions/ldexp.hpp>
#include <nt2/sdk/complex/meta/as_imaginary.hpp>
#include <nt2/sdk/complex/meta/as_dry.hpp>
#include <nt2/sdk/functor/meta/call.hpp>
#include <nt2/sdk/meta/as_integer.hpp>

#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/include/constants/inf.hpp>
#include <nt2/include/constants/nan.hpp>
#include <nt2/include/constants/one.hpp>
#include <nt2/include/constants/zero.hpp>
#include <nt2/include/constants/minf.hpp>
#include <nt2/include/constants/mone.hpp>
#include <nt2/include/constants/four.hpp>
#include <nt2/toolbox/constant/common.hpp>

NT2_TEST_CASE_TPL ( ldexp_real__2_0,  NT2_REAL_TYPES)
{
  using nt2::ldexp;
  using nt2::tag::ldexp_;
  typedef std::complex<T>                           cT;
  typedef typename boost::dispatch::meta::as_integer<T>::type iT;
  typedef typename nt2::meta::as_imaginary<T>::type ciT;
  typedef typename nt2::meta::as_dry<T>::type       dT;

  // return type conformity test
  NT2_TEST_TYPE_IS( (typename nt2::meta::call<ldexp_(cT, iT)>::type), cT );

  // specific values tests
  NT2_TEST_EQUAL(ldexp(nt2::Inf<cT>(),  iT(2)), nt2::Inf<cT>());
  NT2_TEST_EQUAL(ldexp(nt2::Minf<cT>(), 2), nt2::Minf<cT>());
  NT2_TEST_EQUAL(ldexp(nt2::Nan<cT>(),  2), nt2::Nan<cT>());
  NT2_TEST_EQUAL(ldexp(nt2::One<cT>(),  2), nt2::Four<cT>());
  NT2_TEST_EQUAL(ldexp(nt2::Zero<cT>(), 2), nt2::Zero<cT>());
  NT2_TEST_EQUAL(ldexp(cT(nt2::One<T>(),nt2::One<T>()) ,  2), cT(nt2::Four<T>(),nt2::Four<T>()) );

  NT2_TEST_EQUAL(ldexp(nt2::Inf<ciT>(),  2), nt2::Inf<ciT>());
  NT2_TEST_EQUAL(ldexp(nt2::Minf<ciT>(), 2), nt2::Minf<ciT>());
  NT2_TEST_EQUAL(ldexp(nt2::Nan<ciT>(),  2), nt2::Nan<ciT>());
  NT2_TEST_EQUAL(ldexp(nt2::One<ciT>(),  2), nt2::Four<ciT>());
  NT2_TEST_EQUAL(ldexp(nt2::Zero<ciT>(), 2), nt2::Zero<ciT>());

  NT2_TEST_EQUAL(ldexp(nt2::Inf<dT>(),  2), nt2::Inf<dT>());
  NT2_TEST_EQUAL(ldexp(nt2::Minf<dT>(), 2), nt2::Minf<dT>());
  NT2_TEST_EQUAL(ldexp(nt2::Nan<dT>(),  2), nt2::Nan<dT>());
  NT2_TEST_EQUAL(ldexp(nt2::One<dT>(),  2), nt2::Four<dT>());
  NT2_TEST_EQUAL(ldexp(nt2::Zero<dT>(), 2), nt2::Zero<dT>());
}
