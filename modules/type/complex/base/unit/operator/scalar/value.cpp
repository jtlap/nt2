/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 0x01.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#define NT2_UNIT_MODULE "boost::simd::value"

#include <nt2/include/functions/value.hpp>
#include <nt2/sdk/complex/dry.hpp>
#include <nt2/sdk/complex/complex.hpp>
#include <nt2/sdk/complex/imaginary.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>

NT2_TEST_CASE_TPL(complex, BOOST_SIMD_REAL_TYPES)
{
  using std::complex;
  using boost::simd::value;
  using boost::simd::tag::value_;

  NT2_TEST_TYPE_IS( typename boost::dispatch::meta
                    ::call<value_(complex<T> const&)>::type
                  , complex<T> const&
                  );

  NT2_TEST_EQUAL(value(complex<T>(4,2)), complex<T>(4,2));
}

NT2_TEST_CASE_TPL(dry, BOOST_SIMD_REAL_TYPES)
{
  using nt2::dry;
  using boost::simd::value;
  using boost::simd::tag::value_;

  NT2_TEST_TYPE_IS( typename boost::dispatch::meta
                    ::call<value_(dry<T>)>::type
                  , T
                  );

  NT2_TEST_EQUAL(value(dry<T>(4)), T(4));
}

NT2_TEST_CASE_TPL(imaginary, BOOST_SIMD_REAL_TYPES)
{
  using nt2::imaginary;
  using boost::simd::value;
  using boost::simd::tag::value_;

  NT2_TEST_TYPE_IS( typename boost::dispatch::meta
                    ::call<value_(imaginary<T>)>::type
                  , T
                  );

  NT2_TEST_EQUAL(value(imaginary<T>(4)), T(4));
}
