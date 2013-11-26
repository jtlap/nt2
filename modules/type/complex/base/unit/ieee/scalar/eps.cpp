//==============================================================================
//         Copyright 2003 - 2013   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/include/functions/eps.hpp>

#include <boost/dispatch/functor/meta/call.hpp>
#include <nt2/sdk/functor/meta/call.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>
#include <complex>
#include <nt2/sdk/complex/complex.hpp>
#include <nt2/sdk/unit/tests/basic.hpp>
#include <nt2/sdk/meta/as_integer.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <boost/simd/sdk/config.hpp>

#include <nt2/include/constants/mone.hpp>
#include <nt2/include/constants/one.hpp>
#include <nt2/include/constants/sqrt_2.hpp>
#include <nt2/include/constants/zero.hpp>
#include <nt2/include/constants/inf.hpp>
#include <nt2/include/constants/minf.hpp>
#include <nt2/include/constants/nan.hpp>
#include <nt2/include/constants/i.hpp>

NT2_TEST_CASE_TPL ( eps_real,  NT2_REAL_TYPES)
{
  using nt2::eps;
  using nt2::tag::eps_;
  typedef typename std::complex<T> cT;
  typedef typename nt2::meta::call<eps_(cT)>::type r_t;

  // return type conformity test
  NT2_TEST_TYPE_IS(r_t, T);

  // specific values tests
#ifndef BOOST_SIMD_NO_INVALIDS
  NT2_TEST_EQUAL(eps(nt2::Inf<cT>() ), eps(nt2::Inf<T>() ));
  NT2_TEST_EQUAL(eps(nt2::Minf<cT>()), eps(nt2::Minf<T>()));
  NT2_TEST_EQUAL(eps(nt2::Nan<cT>() ), eps(nt2::Nan<T>() ));
  NT2_TEST_EQUAL(eps(cT(nt2::Inf<T>(), nt2::Inf<T>() )), eps(nt2::Inf<T>() ));
  NT2_TEST_EQUAL(eps(cT(nt2::Minf<T>(),nt2::Minf<T>())), eps(nt2::Minf<T>()));
  NT2_TEST_EQUAL(eps(cT(nt2::Nan<T>() ,nt2::Nan<T>()) ), eps(nt2::Nan<T>() ));
#endif
  NT2_TEST_EQUAL(eps(nt2::Mone<cT>()), eps(nt2::Mone<T>()));
  NT2_TEST_EQUAL(eps(nt2::One<cT>() ), eps(nt2::One<T>() ));
  NT2_TEST_EQUAL(eps(nt2::Zero<cT>()), eps(nt2::Zero<T>()));
  NT2_TEST_EQUAL(eps(cT(nt2::Mone<T>(),nt2::Mone<T>())), eps(nt2::Sqrt_2<T>()));
  NT2_TEST_EQUAL(eps(cT(nt2::One<T>() ,nt2::One<T>()) ), eps(nt2::Sqrt_2<T>() ));
  NT2_TEST_EQUAL(eps(cT(nt2::Zero<T>(),nt2::Zero<T>())), eps(nt2::Zero<T>()));
}
