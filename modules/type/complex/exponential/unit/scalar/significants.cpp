//==============================================================================
//         Copyright 2015 J.T. Lapreste
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/include/functions/significants.hpp>

#include <boost/dispatch/functor/meta/call.hpp>
#include <nt2/sdk/functor/meta/call.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>
#include <nt2/sdk/unit/tests/ulp.hpp>
#include <nt2/sdk/meta/as_integer.hpp>
#include <boost/simd/sdk/config.hpp>
#include <complex>
#include <nt2/sdk/complex/complex.hpp>
#include <nt2/include/constants/inf.hpp>
#include <nt2/include/constants/minf.hpp>
#include <nt2/include/constants/nan.hpp>

NT2_TEST_CASE_TPL ( significants,  BOOST_SIMD_REAL_TYPES)
{

  using nt2::significants;
  using nt2::tag::significants_;
  typedef std::complex<T> cT;


#ifndef BOOST_SIMD_NO_INVALIDS
  NT2_TEST_EQUAL(significants(nt2::Inf<cT>(), 1), nt2::Inf<cT>());
  NT2_TEST_EQUAL(significants(nt2::Minf<cT>(), 1), nt2::Minf<cT>());
  NT2_TEST_EQUAL(significants(nt2::Nan<cT>(), 1), nt2::Nan<cT>());
#endif
  NT2_TEST_ULP_EQUAL(significants(cT(0), 1), cT(0), 0.5);
  NT2_TEST_ULP_EQUAL(significants(cT(25.34), 1), cT(30), 0.5);
  NT2_TEST_ULP_EQUAL(significants(cT(25.34), 2), cT(25), 0.5);
  NT2_TEST_ULP_EQUAL(significants(cT(25.34), 3), cT(25.3), 0.5);
  NT2_TEST_ULP_EQUAL(significants(cT(25.34), 4), cT(25.34), 0.5);
  NT2_TEST_ULP_EQUAL(significants(cT(-25.34), 1), cT(-30), 0.5);
  NT2_TEST_ULP_EQUAL(significants(cT(-25.34), 2), cT(-25), 0.5);
  NT2_TEST_ULP_EQUAL(significants(cT(-25.34), 3), cT(-25.3), 0.5);
  NT2_TEST_ULP_EQUAL(significants(cT(-25.34), 4), cT(-25.34), 0.5);
}

