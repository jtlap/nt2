//==============================================================================
//         Copyright 2015 J.T. Lapreste
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/exponential/include/functions/significants.hpp>

#include <boost/dispatch/functor/meta/call.hpp>
#include <nt2/sdk/functor/meta/call.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>
#include <boost/simd/sdk/simd/io.hpp>
#include <boost/simd/sdk/simd/native.hpp>
#include <complex>
#include <nt2/sdk/complex/complex.hpp>
#include <nt2/sdk/complex/dry.hpp>
#include <nt2/sdk/unit/tests/ulp.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <boost/simd/sdk/config.hpp>
#include <nt2/include/functions/splat.hpp>


#include <nt2/include/constants/mone.hpp>
#include <nt2/include/constants/one.hpp>
#include <nt2/include/constants/zero.hpp>
#include <nt2/include/constants/inf.hpp>
#include <nt2/include/constants/minf.hpp>
#include <nt2/include/constants/nan.hpp>


NT2_TEST_CASE_TPL ( significants,  NT2_SIMD_REAL_TYPES)
{
  using nt2::significants;
  using nt2::tag::significants_;
  using boost::simd::native;
  typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef std::complex<T> cT;
  typedef native<cT,ext_t>                cvT;

  // specific values tests
#ifndef BOOST_SIMD_NO_INVALIDS
  NT2_TEST_ULP_EQUAL(significants(nt2::Inf<cvT>(), 1), nt2::Inf<cvT>(), 0.5);
  NT2_TEST_ULP_EQUAL(significants(nt2::Minf<cvT>(), 1), nt2::Minf<cvT>(), 0.5);
  NT2_TEST_ULP_EQUAL(significants(nt2::Nan<cvT>(), 1), nt2::Nan<cvT>(), 0.5);
#endif
  NT2_TEST_ULP_EQUAL(significants(nt2::splat<cvT>(cT(25.34)),  1), nt2::splat<cvT>(30), 0.5);
  NT2_TEST_ULP_EQUAL(significants(nt2::splat<cvT>(cT(25.34)),  2), nt2::splat<cvT>(25), 0.5);
  NT2_TEST_ULP_EQUAL(significants(nt2::splat<cvT>(cT(25.34)),  3), nt2::splat<cvT>(25.3), 0.5);
  NT2_TEST_ULP_EQUAL(significants(nt2::splat<cvT>(cT(25.34)),  4), nt2::splat<cvT>(25.34), 0.5);
  NT2_TEST_ULP_EQUAL(significants(nt2::splat<cvT>(cT(-25.34)), 1), nt2::splat<cvT>(-30), 0.5);
  NT2_TEST_ULP_EQUAL(significants(nt2::splat<cvT>(cT(-25.34)), 2), nt2::splat<cvT>(-25), 0.5);
  NT2_TEST_ULP_EQUAL(significants(nt2::splat<cvT>(cT(-25.34)), 3), nt2::splat<cvT>(-25.3), 0.5);
  NT2_TEST_ULP_EQUAL(significants(nt2::splat<cvT>(cT(-25.34)), 4), nt2::splat<cvT>(-25.34), 0.5);
}
