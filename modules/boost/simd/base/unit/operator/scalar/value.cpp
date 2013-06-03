/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 0x01.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#define NT2_UNIT_MODULE "boost::simd::value"

#include <boost/mpl/integral_c.hpp>
#include <boost/simd/include/functions/value.hpp>
#include <boost/simd/sdk/config/types.hpp>
#include <boost/simd/sdk/config/type_lists.hpp>
#include <boost/simd/sdk/simd/logical.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>

NT2_TEST_CASE_TPL(scalar, BOOST_SIMD_TYPES)
{
  using boost::simd::value;
  using boost::simd::tag::value_;

  NT2_TEST_TYPE_IS( typename boost::dispatch::meta::call<value_(T&)>::type, T&);
  NT2_TEST_TYPE_IS( typename boost::dispatch::meta::call<value_(T const&)>::type, T const&);
  NT2_TEST_EQUAL(value(T(42)), T(42));
}

NT2_TEST_CASE_TPL(pointer, BOOST_SIMD_TYPES)
{
  using boost::simd::value;
  using boost::simd::tag::value_;

  NT2_TEST_TYPE_IS( typename boost::dispatch::meta::call<value_(T*&)>::type
                  , T*&
                  );

  NT2_TEST_TYPE_IS( typename boost::dispatch::meta::call<value_(T* const&)>::type
                  , T* const&
                  );

  T v = 42;
  NT2_TEST_EQUAL(value(&v), &v);
}

NT2_TEST_CASE_TPL(logical, BOOST_SIMD_TYPES)
{
  using boost::simd::value;
  using boost::simd::logical;
  using boost::simd::tag::value_;

  NT2_TEST_TYPE_IS( typename boost::dispatch::meta
                    ::call<value_(logical<T> const&)>::type
                  , bool
                  );

  NT2_TEST_TYPE_IS( typename boost::dispatch::meta
                    ::call<value_(logical<T>&)>::type
                  , bool
                  );

  NT2_TEST_EQUAL(value(logical<T>(true)), true);
}

NT2_TEST_CASE_TPL(mpl_int, BOOST_SIMD_INTEGRAL_TYPES)
{
  using boost::simd::value;
  using boost::mpl::integral_c;
  using boost::simd::tag::value_;

  NT2_TEST_TYPE_IS( typename boost::dispatch::meta
                    ::call<value_(integral_c<T,42> const&)>::type
                  , T
                  );

  NT2_TEST_TYPE_IS( typename boost::dispatch::meta
                    ::call<value_(integral_c<T,42>&)>::type
                  , T
                  );

  NT2_TEST_EQUAL(value(integral_c<T,42>()), T(42));
}
