//==============================================================================
//         Copyright 2003 - 2013   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/include/functions/proj.hpp>

#include <boost/dispatch/functor/meta/call.hpp>
#include <nt2/sdk/functor/meta/call.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>
#include <complex>
#include <nt2/sdk/complex/complex.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <boost/simd/sdk/config.hpp>

#include <nt2/include/constants/mone.hpp>
#include <nt2/include/constants/inf.hpp>
#include <nt2/include/constants/minf.hpp>
#include <nt2/include/constants/nan.hpp>

NT2_TEST_CASE_TPL ( proj_real,  BOOST_SIMD_REAL_TYPES)
{
  using nt2::proj;
  using nt2::tag::proj_;
  typedef typename std::complex<T> cT;

  // specific values tests
#ifndef BOOST_SIMD_NO_INVALIDS
  NT2_TEST_EQUAL(nt2::proj(cT(nt2::Inf<T>())), nt2::Inf<cT>());
  NT2_TEST_EQUAL(nt2::proj(cT(nt2::Minf<T>(), T(1))), nt2::Inf<cT>());
  NT2_TEST_EQUAL(nt2::proj(cT(nt2::Nan<T>())), nt2::Nan<cT>());
#endif
  NT2_TEST_EQUAL(nt2::proj(cT(1)), cT(1));
  NT2_TEST_EQUAL(nt2::proj(cT(nt2::Mone<T>())), nt2::Mone<cT>());
  NT2_TEST_EQUAL(nt2::proj(cT(T(1), T(2))),cT(T(1), T(2)));
}
