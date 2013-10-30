//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <boost/simd/arithmetic/include/functions/fnma.hpp>
#include <boost/dispatch/functor/meta/call.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>

NT2_TEST_CASE_TPL( fnma,  BOOST_SIMD_TYPES)
{
  using boost::simd::fnma;
  using boost::simd::tag::fnma_;

  NT2_TEST_TYPE_IS(typename boost::dispatch::meta::call<fnma_(T,T,T)>::type, T);

  NT2_TEST_EQUAL(fnma(T(2),T(2),T(4)) , T(-8));
  NT2_TEST_EQUAL(fnma(T(-2),T(2),T(4)), T(0));
  NT2_TEST_EQUAL(fnma(T(2),T(-2),T(4)), T(0));
  NT2_TEST_EQUAL(fnma(T(-2),T(-2),T(4)), T(-8));
}
