//==============================================================================
//         Copyright 2015 J.T. Lapreste
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/exponential/include/functions/significants.hpp>

#include <nt2/sdk/functor/meta/call.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>
#include <nt2/sdk/unit/tests/ulp.hpp>
#include <nt2/sdk/meta/as_integer.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <boost/simd/sdk/config.hpp>
#include <nt2/sdk/meta/as_floating.hpp>
#include <nt2/sdk/meta/as_integer.hpp>

NT2_TEST_CASE_TPL ( significants,  BOOST_SIMD_REAL_TYPES)
{

  using nt2::significants;
  using nt2::tag::significants_;
  typedef typename nt2::meta::as_integer<T>::type iT;
  typedef typename boost::dispatch::meta::call<significants_(T, iT)>::type r_t;
  typedef T wished_r_t;


  // return type conformity test
  NT2_TEST_TYPE_IS( r_t, wished_r_t );

#ifndef BOOST_SIMD_NO_INVALIDS
  NT2_TEST_ULP_EQUAL(significants(nt2::Inf<T>(), 1), nt2::Inf<r_t>(), 0.5);
  NT2_TEST_ULP_EQUAL(significants(nt2::Minf<T>(), 1), nt2::Minf<r_t>(), 0.5);
  NT2_TEST_ULP_EQUAL(significants(nt2::Nan<T>(), 1), nt2::Nan<r_t>(), 0.5);
#endif
  NT2_TEST_ULP_EQUAL(significants(T(0), 1), T(0), 0.5);
  NT2_TEST_ULP_EQUAL(significants(T(25.34), 1), T(30), 0.5);
  NT2_TEST_ULP_EQUAL(significants(T(25.34), 2), T(25), 0.5);
  NT2_TEST_ULP_EQUAL(significants(T(25.34), 3), T(25.3), 0.5);
  NT2_TEST_ULP_EQUAL(significants(T(25.34), 4), T(25.34), 0.5);
  NT2_TEST_ULP_EQUAL(significants(T(-25.34), 1), T(-30), 0.5);
  NT2_TEST_ULP_EQUAL(significants(T(-25.34), 2), T(-25), 0.5);
  NT2_TEST_ULP_EQUAL(significants(T(-25.34), 3), T(-25.3), 0.5);
  NT2_TEST_ULP_EQUAL(significants(T(-25.34), 4), T(-25.34), 0.5);
}

