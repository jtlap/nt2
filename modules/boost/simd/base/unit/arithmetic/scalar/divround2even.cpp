//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <boost/simd/arithmetic/include/functions/divround2even.hpp>
#include <boost/simd/sdk/config.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/ulp.hpp>

#include <boost/simd/include/constants/one.hpp>
#include <boost/simd/include/constants/inf.hpp>
#include <boost/simd/include/constants/zero.hpp>
#include <boost/simd/include/constants/minf.hpp>
#include <boost/simd/include/constants/mone.hpp>
#include <boost/simd/include/constants/nan.hpp>
#include <boost/simd/include/constants/valmin.hpp>
#include <boost/simd/include/constants/valmax.hpp>

NT2_TEST_CASE_TPL ( divround2even_real,  BOOST_SIMD_REAL_TYPES)
{
  using boost::simd::divround2even;
  using boost::simd::tag::divround2even_;
  typedef typename boost::dispatch::meta::call<divround2even_(T,T)>::type r_t;
  typedef T wished_r_t;

  // return type conformity test
  NT2_TEST_TYPE_IS( r_t, wished_r_t );

  // specific values tests
  NT2_TEST_EQUAL(divround2even(boost::simd::Inf<T>(), boost::simd::Inf<T>()), boost::simd::Nan<r_t>());
  NT2_TEST_EQUAL(divround2even(boost::simd::Minf<T>(), boost::simd::Minf<T>()), boost::simd::Nan<r_t>());
  NT2_TEST_EQUAL(divround2even(boost::simd::Mone<T>(), boost::simd::Mone<T>()), boost::simd::One<r_t>());
  NT2_TEST_EQUAL(divround2even(boost::simd::Nan<T>(), boost::simd::Nan<T>()), boost::simd::Nan<r_t>());
  NT2_TEST_EQUAL(divround2even(boost::simd::One<T>(), boost::simd::One<T>()), boost::simd::One<r_t>());
} // end of test for floating_

NT2_TEST_CASE_TPL ( divround2even_unsigned_int,  BOOST_SIMD_UNSIGNED_TYPES)
{

  using boost::simd::divround2even;
  using boost::simd::tag::divround2even_;
  typedef typename boost::dispatch::meta::call<divround2even_(T,T)>::type r_t;
  typedef T wished_r_t;


  // return type conformity test
  NT2_TEST_TYPE_IS( r_t, wished_r_t );

  // specific values tests
  NT2_TEST_EQUAL(divround2even(boost::simd::One<T>(), boost::simd::One<T>()), boost::simd::One<r_t>());
  NT2_TEST_EQUAL(divround2even(T(5), T(2)), T(2));
  NT2_TEST_EQUAL(divround2even(T(7), T(2)), T(4));
  NT2_TEST_EQUAL(divround2even(T(9), T(3)), T(3));
  NT2_TEST_EQUAL(divround2even(T(10), T(3)), T(3));
  NT2_TEST_EQUAL(divround2even(T(11), T(3)), T(4));
  NT2_TEST_EQUAL(divround2even(T(12), T(3)), T(4));
  NT2_TEST_EQUAL(divround2even(T(18), T(6)), T(3));
  NT2_TEST_EQUAL(divround2even(T(20), T(6)), T(3));
  NT2_TEST_EQUAL(divround2even(T(22), T(6)), T(4));
  NT2_TEST_EQUAL(divround2even(T(24), T(6)), T(4));
  NT2_TEST_EQUAL(divround2even(boost::simd::Valmax<T>(),boost::simd::Two<T>()), boost::simd::Valmax<T>()/boost::simd::Two<T>()+boost::simd::One<T>());

} // end of test for unsigned_int_

NT2_TEST_CASE_TPL ( divround2even_signed_int, BOOST_SIMD_INTEGRAL_SIGNED_TYPES)
{

  using boost::simd::divround2even;
  using boost::simd::tag::divround2even_;
  typedef typename boost::dispatch::meta::call<divround2even_(T,T)>::type r_t;
  typedef T wished_r_t;


  // return type conformity test
  NT2_TEST_TYPE_IS( r_t, wished_r_t );

  // specific values tests
  NT2_TEST_EQUAL(divround2even(boost::simd::Mone<T>(), boost::simd::Mone<T>()), boost::simd::One<r_t>());
  NT2_TEST_EQUAL(divround2even(boost::simd::One<T>(), boost::simd::One<T>()), boost::simd::One<r_t>());
  NT2_TEST_EQUAL(divround2even(T(5), T(2)), T(2));
  NT2_TEST_EQUAL(divround2even(T(7), T(2)), T(4));
  NT2_TEST_EQUAL(divround2even(T(-5), T(2)), T(-2));
  NT2_TEST_EQUAL(divround2even(T(-7), T(2)), T(-4));
  NT2_TEST_EQUAL(divround2even(T(-4),T(0)), boost::simd::Valmin<r_t>());
  NT2_TEST_EQUAL(divround2even(T(4),T(0)), boost::simd::Valmax<r_t>());
  NT2_TEST_EQUAL(divround2even(T(4),T(3)), T(1));
  NT2_TEST_EQUAL(divround2even(T(-4),T(-3)), T(1));
  NT2_TEST_EQUAL(divround2even(T(4),T(-3)), T(-1));
  NT2_TEST_EQUAL(divround2even(T(-4),T(3)), T(-1));
  NT2_TEST_EQUAL(divround2even(T(5),T(3)), T(2));
  NT2_TEST_EQUAL(divround2even(T(-5),T(-3)), T(2));
  NT2_TEST_EQUAL(divround2even(T(5),T(-3)), T(-2));
  NT2_TEST_EQUAL(divround2even(T(-5),T(3)), T(-2));

  NT2_TEST_EQUAL(divround2even(T(5),T(4)), T(1));
  NT2_TEST_EQUAL(divround2even(T(-5),T(-4)), T(1));
  NT2_TEST_EQUAL(divround2even(T(5),T(-4)), T(-1));
  NT2_TEST_EQUAL(divround2even(T(-5),T(4)), T(-1));
  NT2_TEST_EQUAL(divround2even(T(6),T(4)), T(2));
  NT2_TEST_EQUAL(divround2even(T(-6),T(-4)), T(2));
  NT2_TEST_EQUAL(divround2even(T(6),T(-4)), T(-2));
  NT2_TEST_EQUAL(divround2even(T(-6),T(4)), T(-2));
  NT2_TEST_EQUAL(divround2even(T(8),T(4)), T(2));
  NT2_TEST_EQUAL(divround2even(T(-8),T(-4)), T(2));
  NT2_TEST_EQUAL(divround2even(T(8),T(-4)), T(-2));
  NT2_TEST_EQUAL(divround2even(T(-8),T(4)), T(-2));
  NT2_TEST_EQUAL(divround2even(T(9),T(4)), T(2));
  NT2_TEST_EQUAL(divround2even(T(-9),T(-4)), T(2));
  NT2_TEST_EQUAL(divround2even(T(9),T(-4)), T(-2));
  NT2_TEST_EQUAL(divround2even(T(-9),T(4)), T(-2));
  NT2_TEST_EQUAL(divround2even(T(10),T(4)), T(2));
  NT2_TEST_EQUAL(divround2even(T(-10),T(-4)), T(2));
  NT2_TEST_EQUAL(divround2even(T(10),T(-4)), T(-2));
  NT2_TEST_EQUAL(divround2even(T(-10),T(4)), T(-2));

} // end of test for signed_int_
