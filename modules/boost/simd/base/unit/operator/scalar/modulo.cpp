//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <boost/simd/operator/include/functions/modulo.hpp>
#include <boost/dispatch/functor/meta/call.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <boost/simd/sdk/config.hpp>
#include <boost/simd/sdk/simd/io.hpp>

#include <boost/simd/include/constants/one.hpp>
#include <boost/simd/include/constants/two.hpp>
#include <boost/simd/include/constants/zero.hpp>

NT2_TEST_CASE_TPL ( modulo_integer,  BOOST_SIMD_INTEGRAL_TYPES)
{

  using boost::simd::modulo;
  using boost::simd::tag::modulo_;
  typedef typename boost::dispatch::meta::call<modulo_(T,T)>::type r_t;
  typedef T wished_r_t;

  // return type conformity test
  NT2_TEST_TYPE_IS(r_t, wished_r_t);
  // specific values tests
  NT2_TEST_EQUAL(modulo(boost::simd::One<T>(), boost::simd::One<T>()), boost::simd::Zero<r_t>());
  NT2_TEST_EQUAL(modulo(boost::simd::One<T>(),boost::simd::Two<T>()), boost::simd::One<r_t>());
  NT2_TEST_EQUAL(modulo(boost::simd::Zero<T>(),boost::simd::Two<T>()), boost::simd::Zero<r_t>());
} // end of test for integer_
