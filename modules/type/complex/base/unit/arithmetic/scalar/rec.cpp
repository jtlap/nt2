//==============================================================================
//         Copyright 2003 - 2013   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/include/functions/rec.hpp>

#include <boost/dispatch/functor/meta/call.hpp>
#include <nt2/sdk/functor/meta/call.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>
#include <complex>
#include <nt2/sdk/complex/complex.hpp>
#include <nt2/sdk/complex/dry.hpp>
#include <nt2/sdk/unit/tests/ulp.hpp>
#include <nt2/sdk/meta/as_integer.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <boost/simd/sdk/config.hpp>

#include <nt2/include/constants/mzero.hpp>
#include <nt2/include/constants/one.hpp>
#include <nt2/include/constants/zero.hpp>
#include <nt2/include/constants/inf.hpp>
#include <nt2/include/constants/minf.hpp>
#include <nt2/include/constants/nan.hpp>

NT2_TEST_CASE_TPL ( rec_real,  BOOST_SIMD_REAL_TYPES)
{
  using nt2::rec;
  using nt2::tag::rec_;
  typedef typename std::complex<T> cT;
  typedef typename boost::dispatch::meta::call<rec_(cT)>::type r_t;

  // return type conformity test
  NT2_TEST_TYPE_IS(r_t, cT);

  // specific values tests
#ifndef BOOST_SIMD_NO_INVALIDS
   NT2_TEST_EQUAL(nt2::rec(cT(nt2::Inf<T>(), nt2::Inf<T>())), cT(nt2::Zero<cT>()));
   NT2_TEST_EQUAL(nt2::rec(cT(nt2::Minf<T>(), nt2::Minf<T>())), cT(nt2::Zero<cT>()));
   NT2_TEST_EQUAL(nt2::rec(cT(nt2::Inf<T>(), nt2::Zero<T>())), cT(nt2::Zero<cT>()));
   NT2_TEST_EQUAL(nt2::rec(cT(nt2::Zero<T>(), nt2::Inf<T>())), cT(nt2::Zero<cT>()));
   NT2_TEST_EQUAL(nt2::rec(cT(nt2::Minf<T>(), nt2::Zero<T>())), cT(nt2::Zero<cT>()));
   NT2_TEST_EQUAL(nt2::rec(cT(nt2::Zero<T>(), nt2::Minf<T>())), cT(nt2::Zero<cT>()));
   NT2_TEST_EQUAL(nt2::rec(cT(nt2::Zero<T>(), nt2::Zero<T>())), cT(nt2::Inf<cT>()));
   NT2_TEST_EQUAL(nt2::rec(cT(nt2::Mzero<T>(), nt2::Zero<T>())), cT(nt2::Minf<cT>()));
   NT2_TEST_EQUAL(nt2::rec(cT(nt2::Nan<T>(), nt2::Nan<T>())), cT(nt2::Nan<T>(), nt2::Nan<T>()));
   NT2_TEST_EQUAL(nt2::rec(cT(nt2::Nan<T>(), nt2::One<T>())), cT(nt2::Nan<T>(), nt2::Nan<T>()));
   NT2_TEST_EQUAL(nt2::rec(cT(nt2::One<T>(), nt2::Nan<T>())), cT(nt2::Nan<T>(), nt2::Nan<T>()));
   NT2_TEST_EQUAL(nt2::rec(cT(nt2::Nan<T>(), nt2::Zero<T>())), cT(nt2::Nan<cT>()));
   NT2_TEST_EQUAL(nt2::rec(cT(nt2::Zero<T>(), nt2::Nan<T>())), cT(nt2::Zero<T>(), nt2::Nan<T>()));
#endif
   std::complex < T > a(1, 0);
   NT2_TEST_EQUAL(nt2::rec(a), nt2::One<T>());
   std::complex < T > b(1, 1);
   NT2_TEST_ULP_EQUAL(nt2::rec(b), cT(0.5, -0.5), 0);

}
