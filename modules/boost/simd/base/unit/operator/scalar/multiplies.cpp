//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <boost/simd/operator/include/functions/multiplies.hpp>
#include <boost/dispatch/functor/meta/call.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <boost/simd/sdk/config.hpp>
#include <boost/simd/sdk/simd/io.hpp>

#include <boost/simd/include/functions/plus.hpp>
#include <boost/simd/include/constants/one.hpp>
#include <boost/simd/include/constants/two.hpp>
#include <boost/simd/include/constants/mone.hpp>
#include <boost/simd/include/constants/zero.hpp>
#include <boost/simd/include/constants/mzero.hpp>
#include <boost/simd/include/constants/inf.hpp>
#include <boost/simd/include/constants/minf.hpp>
#include <boost/simd/include/constants/nan.hpp>
#include <boost/simd/include/constants/valmax.hpp>

NT2_TEST_CASE_TPL ( multiplies_real,  BOOST_SIMD_REAL_TYPES)
{

  using boost::simd::multiplies;
  using boost::simd::tag::multiplies_;
  typedef typename boost::dispatch::meta::call<multiplies_(T,T)>::type r_t;
  typedef T wished_r_t;


  // return type conformity test
  NT2_TEST_TYPE_IS(r_t, wished_r_t);

  // specific values tests
  NT2_TEST_EQUAL(multiplies(boost::simd::Inf<T>(), boost::simd::Inf<T>()), boost::simd::Inf<r_t>());
  NT2_TEST_EQUAL(multiplies(boost::simd::Minf<T>(), boost::simd::Minf<T>()), boost::simd::Inf<r_t>());
  NT2_TEST_EQUAL(multiplies(boost::simd::Nan<T>(), boost::simd::Nan<T>()), boost::simd::Nan<r_t>());
  NT2_TEST_EQUAL(multiplies(boost::simd::One<T>(),boost::simd::Zero<T>()), boost::simd::Zero<r_t>());
  NT2_TEST_EQUAL(multiplies(boost::simd::Zero<T>(), boost::simd::Zero<T>()), boost::simd::Zero<r_t>());
  NT2_TEST_EQUAL(multiplies(boost::simd::Mzero<T>(), boost::simd::One<T>()), boost::simd::Mzero<r_t>());
} // end of test for floating_

NT2_TEST_CASE_TPL ( multiplies_sinteger,  BOOST_SIMD_INTEGRAL_SIGNED_TYPES)
{

  using boost::simd::multiplies;
  using boost::simd::tag::multiplies_;
  typedef typename boost::dispatch::meta::call<multiplies_(T,T)>::type r_t;
  typedef T wished_r_t;

  // return type conformity test
  NT2_TEST_TYPE_IS(r_t, wished_r_t);

  // specific values tests
  NT2_TEST_EQUAL(multiplies(boost::simd::One<T>(), boost::simd::One<T>()), boost::simd::One<r_t>());
  NT2_TEST_EQUAL(multiplies(boost::simd::One<T>(),boost::simd::Zero<T>()), boost::simd::Zero<r_t>());
  NT2_TEST_EQUAL(multiplies(boost::simd::Zero<T>(), boost::simd::Zero<T>()), boost::simd::Zero<r_t>());
  NT2_TEST_EQUAL(multiplies(boost::simd::Mzero<T>(), boost::simd::One<T>()), boost::simd::Mzero<r_t>());
} // end of test for integer_

NT2_TEST_CASE_TPL ( multiplies_uinteger,  BOOST_SIMD_INTEGRAL_UNSIGNED_TYPES)
{

  using boost::simd::multiplies;
  using boost::simd::tag::multiplies_;
  typedef typename boost::dispatch::meta::call<multiplies_(T,T)>::type r_t;
  typedef T wished_r_t;

  // return type conformity test
  NT2_TEST_TYPE_IS(r_t, wished_r_t);

  // specific values tests
  NT2_TEST_EQUAL(multiplies(boost::simd::One<T>(), boost::simd::One<T>()), boost::simd::One<r_t>());
  NT2_TEST_EQUAL(multiplies(boost::simd::One<T>(),boost::simd::Zero<T>()), boost::simd::Zero<r_t>());
  NT2_TEST_EQUAL(multiplies(boost::simd::Zero<T>(), boost::simd::Zero<T>()), boost::simd::Zero<r_t>());
  NT2_TEST_EQUAL(multiplies(boost::simd::Mzero<T>(), boost::simd::One<T>()), boost::simd::Mzero<r_t>());
  NT2_TEST_EQUAL(multiplies(boost::simd::Valmax<T>(), boost::simd::Two<T>()), boost::simd::Valmax<T>()-boost::simd::One<r_t>());
  NT2_TEST_EQUAL(multiplies(boost::simd::Valmax<T>(), boost::simd::Two<T>()), boost::simd::plus(boost::simd::Valmax<T>(), boost::simd::Valmax<T>()));
} // end of test for integer_
