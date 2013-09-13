//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <boost/simd/include/functions/scalar/fast_divides.hpp>
#include <boost/dispatch/functor/meta/call.hpp>
#include <boost/simd/include/constants/nan.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/ulp.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>

NT2_TEST_CASE_TPL ( fast_divides_real,  BOOST_SIMD_REAL_TYPES)
{
  using boost::simd::fast_divides;
  using boost::simd::tag::fast_divides_;

  // return type conformity test
  NT2_TEST_TYPE_IS( typename boost::dispatch::meta::call<fast_divides_(T,T)>::type
                  , T
                  );

  NT2_TEST_ULP_EQUAL(fast_divides(T(1) , T(2) ), T(0.5)  , 0.5);
  NT2_TEST_ULP_EQUAL(fast_divides(T(1) , T(10)), T(0.1)  , 0.5);
  NT2_TEST_ULP_EQUAL(fast_divides(T(2) , T(3) ), T(2./3.), 0.5);
}

NT2_TEST_CASE_TPL ( fast_divides_ints,  BOOST_SIMD_INTEGRAL_TYPES)
{
  using boost::simd::fast_divides;
  using boost::simd::tag::fast_divides_;

  // return type conformity test
  NT2_TEST_TYPE_IS( typename boost::dispatch::meta::call<fast_divides_(T,T)>::type
                  , T
                  );

  NT2_TEST_EQUAL(fast_divides(T(1) , T(2) ), T(0) );
  NT2_TEST_EQUAL(fast_divides(T(5) , T(2) ), T(2) );
  NT2_TEST_EQUAL(fast_divides(T(9) , T(3) ), T(3) );
}
